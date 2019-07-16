#include "Movement.h"
#include "UdpCom.h"
#include "../../../PIC/control.h"

static const char* LOG_TAG = "Movement";

typedef struct MotorKeyframeNode MotorKeyframeNode;
typedef struct MotorHead MotorHead;
typedef struct PausedMovementHead PausedMovementHead;

typedef struct InterpolateState InterpolateState;

////////////////////////////////////////// data structure for interpolate ///////////////////////////////////////////

static uint16_t movementTime = 0;                // current time in movement tick
static bool tickPaused = false;

static xSemaphoreHandle tickSemaphore;		// semaphore for lock movement linked list

struct MotorKeyframeNode {
	uint16_t id;              // id of the keyframe (movement id + index)
	uint16_t start;           // start time
	uint16_t end;          // end time = start time + period
	int16_t pose;                     // target pose
	MotorKeyframeNode* next; // next node
};

struct MotorHead {
	uint8_t nOccupied;        // count of occupied buffer, includes paused keyframes

	// interpolate parameters, please refer to Bresenham's Line Algorithm
	int16_t currentPose;	// current pose of motor
	uint16_t nextTime;	// the differntial should change when time exceeds nextTime
	bool minus;
	uint8_t slopeInteger;
	uint16_t slopeDecimal;
	uint16_t slopeError;

	MotorKeyframeNode* head; // head of linked list of keyframes
	MotorKeyframeNode* read; // last node of read (since multi keyframes is used in interpolate)
};

vector<MotorHead> motorHeads;

struct PausedMovementHead {
	uint8_t motorId;
	uint16_t pausedTime;			// time when the keyframes are paused
	MotorKeyframeNode* head;

	PausedMovementHead* next;
};

PausedMovementHead* pausedMovements = NULL;

static void initMotorHead(uint8_t motorId) {
	MotorHead& head = motorHeads[motorId];

	head.nOccupied = 0;

	head.currentPose = 0;
	head.nextTime = movementTime - 1;
	head.minus = 0;
	head.slopeInteger = 0;
	head.slopeDecimal = 0;
	head.slopeError = 0x8000;

	head.head = NULL;
	head.read = NULL;
}
static void initMotorHeads() {
	motorHeads.clear();
	motorHeads.reserve(allBoards.GetNTotalMotor());
	for (int i = 0; i < allBoards.GetNTotalMotor(); i++) {
		MotorHead head;
		motorHeads.push_back(head);
		initMotorHead(i);
	}

	movementQueryInterpolateState();
}
static void initPausedMovements() {
	pausedMovements = (struct PausedMovementHead*)malloc(sizeof(struct PausedMovementHead));	//empty head
	pausedMovements->next = NULL;
}

/////////////////////////////////////////// api for accessing PIC ///////////////////////////////////////////////
static xSemaphoreHandle picQuerySemaphore;
static bool receivedReturn = true;		// if not received the return of formal command, not execute command this time

static uint8_t targetCountReadMin = 0xfe, targetCountReadMax = 0xfe, targetWrite = 0xff;
static uint16_t tickMin, tickMax;

static bool calibrateCurrentPose = false;		// set current pose once with return packet of CI_INTERPOLATE

// return the count of remaining empty buffer
static short getInterpolateBufferVacancy() {
	return (short)allBoards.GetNTarget() - (uint8_t)(targetWrite - targetCountReadMin + 1);
}

void movementQueryInterpolateState() {
	xSemaphoreTake(picQuerySemaphore, portMAX_DELAY);

	UdpCmdPacket cmd;
	cmd.command = CI_INTERPOLATE;
	cmd.length = cmd.CommandLen();
	cmd.SetPeriod(0);
	UdpCom_ReceiveCommand((void*)(cmd.bytes+2), cmd.CommandLen(), CS_MOVEMENT_MANAGER);

	xSemaphoreTake(picQuerySemaphore, portMAX_DELAY);
	xSemaphoreGive(picQuerySemaphore);
}

static void movementUpdateInterpolateState(UdpRetPacket& pkt) {
	if (calibrateCurrentPose) {
		xSemaphoreTake(tickSemaphore, portMAX_DELAY);
		for(int i=0; i<allBoards.GetNTotalMotor(); i++) {
			motorHeads[i].currentPose = pkt.GetMotorPos(i);
		}
		xSemaphoreGive(tickSemaphore);
		calibrateCurrentPose = false;
	}

	targetCountReadMin = pkt.GetTargetCountReadMin();
	targetCountReadMax = pkt.GetTargetCountReadMax();
	tickMin = pkt.GetTickMin();
	tickMax = pkt.GetTickMax();
}
void movementOnGetPICInfo(UdpRetPacket& pkt) {
	switch (pkt.command)
	{
	case CI_INTERPOLATE:
		movementUpdateInterpolateState(pkt);
		receivedReturn = true;
		break;
	
	default:
		break;
	}

	xSemaphoreGive(picQuerySemaphore);
}
void initPICPacketHandler() {
	picQuerySemaphore = xSemaphoreCreateMutex();
}

/////////////////////////////////////////// basic api ////////////////////////////////////////////////

static uint8_t getMovementId(uint16_t id) {
	return (id >> 8);
}

static uint8_t getKeyframeId(uint16_t id) {
	return (id & 0x00ff);
}

static MotorKeyframeNode* getNode(uint8_t motorId, uint16_t id) {
	MotorHead& head = motorHeads[motorId];
	MotorKeyframeNode* res = head.head;
	while (res)
	{
		if (res->id == id) return res;
		res = res->next;
	}
	return res;
}

uint16_t minTime(uint16_t time1, uint16_t time2, uint16_t minimum) {
	if ((time1 < minimum && time2 < minimum)
		|| (time1 >= minimum && time2 >= minimum))
		return time1 < time2 ? time1 : time2;
	else
		return time1 >= minimum ? time1 : time2;
}

static void getInterpolateParams(uint8_t motorId) {
	MotorHead &head = motorHeads[motorId];
	if (!head.read) {
		head.slopeDecimal = 0;
		head.slopeInteger = 0;
		if (!head.head) head.nextTime = movementTime - 1;	// ok to overflow
		else head.nextTime = head.head->start;
		return;
	}

	// differential
	uint16_t count = 0;
	int32_t dif_sum = 0;

	// nextTime
	uint16_t minimum = movementTime;
	uint16_t min_time = movementTime - 1;

	MotorKeyframeNode* tmp = head.head;
	while (1) {
		// get dif for every keyframe
		int32_t dif = ((int32_t)(tmp->pose - head.currentPose)<<16) / (tmp->end - movementTime);

		dif_sum += dif;
		count += 1;

		// get min nextTime for every keyframe
		min_time = minTime(min_time, tmp->end, minimum);

		// increase pointer
		if (tmp == head.read) break;
		tmp = tmp->next;
	 }

	if (tmp->next) min_time = minTime(min_time, tmp->next->start, minimum);

	dif_sum = dif_sum / count;

	if (dif_sum < 0) {
		head.minus = true;
		dif_sum = -dif_sum;
	}
	else {
		head.minus = false;
	}
	head.slopeInteger = (dif_sum >> 16) & 0x00ff;
	head.slopeDecimal = dif_sum & 0xffff;
	head.slopeError = 0x8000;
	head.nextTime = min_time;
}

static MotorKeyframeNode* lastSmallerNode(MotorKeyframeNode* smallerNode, MotorKeyframeNode* node) {
	MotorKeyframeNode* res = smallerNode;

	if (node->start < res->start) {		// the time is have been moded
		while (res->next && res->next->start >= res->start) res = res->next;
	}
	while (res->next && res->next->start < node->start && 
		(res->next->start >= res->start || node->start < res->start)) res = res->next;

	return res;
}

// add [ behind the same movement ] || [ at current time if no same movement ]
static void addNodeDefault(uint8_t motorId, MotorKeyframeNode* node, bool recalInterParams) {
	MotorHead &head = motorHeads[motorId];
	bool changeDifferential = false;

	// insert node
	if (head.head == NULL) {	// the keyframe list is empty
		head.head = node;
		node->next = NULL;

		node->start = movementTime;
		changeDifferential = true;
		head.read = node;
	}
	else {
		MotorKeyframeNode* tmp = head.head;
		MotorKeyframeNode *last_movement = NULL, *last_smaller = NULL;
		while (tmp != NULL) {
			if (getMovementId(tmp->id) == getMovementId(node->id)) last_movement = tmp;
			tmp = tmp->next;
		}

		if (last_movement == NULL) {	// no same movement
			node->start = movementTime;
			changeDifferential = true;

			// insert into list
			if (head.read) {
				tmp = head.read->next;
				head.read->next = node;
				node->next = tmp;
				head.read = node;
			}
			else {
				tmp = head.head;
				head.head = node;
				node->next = tmp;
				head.read = node;
			}
		}
		else {
			node->start = last_movement->end;

			// insert into list
			last_smaller = lastSmallerNode(last_movement, node);
			tmp = last_smaller->next;
			last_smaller->next = node;
			node->next = tmp;
		}
	}
	node->end = node->start + node->end;

	// alter head
	head.nOccupied += 1;
	if (changeDifferential && recalInterParams) getInterpolateParams(motorId);
}

// add node with absolute time
static void addNodeAtTime(uint8_t motorId, MotorKeyframeNode* node, bool recalInterParams, uint16_t abTime) {
	MotorHead &head = motorHeads[motorId];
	node->start = abTime;
	node->end = node->start + node->end;

	bool changeDifferential = false;

	uint16_t minimum =minTime(node->end, movementTime, abTime) != node->end ? abTime : movementTime;		// judge wether time is larger than abTime through judge whether the new node should interpolate right now
	if (!head.head) {		// array is empty
		head.head = node;
		node->next = NULL;

		if (minimum == abTime) {
			changeDifferential = true;
			head.read = node;
		}
	}
	else {
		MotorKeyframeNode* tmp = head.head;
		if (minTime(tmp->start, abTime, minimum) == abTime) {		// add to first
			head.head = node;
			node->next = tmp;
			if (!head.read && minimum == abTime) {
				head.read = node;
			}
		}
		else {
			MotorKeyframeNode* last_smaller = lastSmallerNode(head.head, node);
			MotorKeyframeNode* tmp = last_smaller->next;
			last_smaller->next = node;
			node->next = tmp;

			if (head.read == last_smaller && minimum == abTime) {
				head.read = node;
			}
		}

		if (minimum == abTime) changeDifferential = true;
	}

	// alter head
	head.nOccupied += 1;
	if (changeDifferential && recalInterParams) getInterpolateParams(motorId);
}

static void deleteNode(uint8_t motorId, MotorKeyframeNode* node, bool recalInterParams) {
	MotorHead &head = motorHeads[motorId];
	// judge wether the node participate in the interpolate
	bool changeDifferential = true;

	// find node before this node
	MotorKeyframeNode* nodeBefore;
	if (head.head == node) nodeBefore = NULL;
	else {
		nodeBefore = head.head;
		while (nodeBefore->next != node) {
			if (nodeBefore == head.read) changeDifferential = false;
			nodeBefore = nodeBefore->next;
		}
	}

	if (!head.read) changeDifferential = false;

	// change read pointer if needed
	if (head.read == node) head.read = nodeBefore;

	// delete node
	if (head.head == node) {
		head.head = node->next;
	}
	else {
		nodeBefore->next = node->next;
	}

	free((void*)node);

	// change interpolate parameters
	if (changeDifferential && recalInterParams) getInterpolateParams(motorId);

	head.nOccupied -= 1;
}

// clear the nodes that finished interpolate
static void cleanInterpolatedKeyframes(uint8_t motorId) {
	MotorHead &head = motorHeads[motorId];
	if (head.read) {
		MotorKeyframeNode* node = head.head;
		while (node != NULL) {
			MotorKeyframeNode* tmp = node->next;
			if (minTime(node->end, head.nextTime, head.head->start) == node->end) deleteNode(motorId, node, false);	// TODO inform js

			// increase node
			if (node == head.read) break;
			node = tmp;
		}
	}
}
// increase the read pointer to include new interpolate nodes
static void increaseReadPointer(uint8_t motorId) {
	MotorHead &head = motorHeads[motorId];
	MotorKeyframeNode* newRead = head.read;
	if (!head.read) {
		if (!head.head || head.head->start > movementTime) return;
		else newRead = head.head;
	}
	while (newRead->next && newRead->next->start <= movementTime) newRead = newRead->next;
	head.read = newRead;
}
// called when nextTime arrives
static void finishKeyframe(uint8_t motorId) {
	// delete nodes
	cleanInterpolatedKeyframes(motorId);

	// increase read pointer
	increaseReadPointer(motorId);

	// recalculate interpolate parameters
	getInterpolateParams(motorId);
}

// clear all keyframes on certain motor with specified movementId
static void clearMotorMovement(uint8_t motorId, uint8_t movementId) {
	MotorHead &head = motorHeads[motorId];
	MotorKeyframeNode* node = head.head;
	while (node) {
		MotorKeyframeNode *tmp = node->next;

		if (getMovementId(node->id) == movementId) deleteNode(motorId, node, false);

		node = tmp;
	}
	getInterpolateParams(motorId);
}

/////////////////////////////////////////// basic api for pause & resume //////////////////////////////////////////
// pick out keyframes with specified movementId on one motor
static MotorKeyframeNode* pickMotorKeyframes(uint8_t motorId, uint8_t movementId) {
	MotorHead &head = motorHeads[motorId];
	if (!head.head) return NULL;
	MotorKeyframeNode* res = NULL;
	MotorKeyframeNode* res_tail = NULL;
	MotorKeyframeNode* node = head.head, *before_node = NULL;
	uint16_t minimum = head.read ? head.head->start : movementTime;

	while (node) {
		if (getMovementId(node->id) == movementId) {	// find one
			if (!res && minTime(movementTime, node->start, minimum) != movementTime) {		// the first keyframe of movement might have been interpolated a bit
				node->start = movementTime;
			}

			MotorKeyframeNode* tmp = node;
			node = node->next;
			if (tmp == head.head) head.head = node;
			else before_node->next = node;

			if (!res) {
				res = tmp;
				res_tail = tmp;
			}
			else {
				res_tail->next = tmp;
				res_tail = tmp;
			}
			tmp->next = NULL;

			if (tmp == head.read) head.read = before_node;
		}
		else {
			if (node == head.head) before_node = head.head;
			else before_node = before_node->next;
			node = node->next;
		}
	}

	getInterpolateParams(motorId);

	return res;
}

// insert the picked keyframes to paused list
static void insertToPausedMovementList(uint8_t motorId, MotorKeyframeNode* motorKeyframes) {
	PausedMovementHead* next = pausedMovements->next;
	pausedMovements->next = (struct PausedMovementHead*)malloc(sizeof(struct PausedMovementHead));
	pausedMovements->next->motorId = motorId;
	pausedMovements->next->head = motorKeyframes;
	pausedMovements->next->pausedTime = movementTime;
	pausedMovements->next->next = next;
}

// insert ordered keyframes into specified motor (NOTE: min time in the keyframes is current time)
static void insertMotorKeyframes(uint8_t motorId, MotorKeyframeNode* keyframes) {
	MotorHead &head = motorHeads[motorId];
	if (!head.head) head.head = keyframes;
	uint16_t minimum = head.read ? head.head->start : movementTime;
	MotorKeyframeNode* before_node = NULL, *next_node = head.head;

	head.read = keyframes;
	if (minTime(keyframes->start, head.head->start, minimum) != head.head->start) {
		head.head = keyframes;
		before_node = keyframes;
		keyframes = keyframes->next;
		before_node->next = next_node;
	}
	else {
		before_node = head.head;
		next_node = before_node->next;
	}

	while (next_node && keyframes) {
		if (minTime(next_node->start, keyframes->start, minimum) != next_node->start) {	// insert one
			before_node->next = keyframes;
			before_node = keyframes;
			keyframes = keyframes->next;
			before_node->next = next_node;
		}
		else {
			before_node = before_node->next;
			next_node = before_node->next;
		}
	}

	if (!next_node) before_node->next = keyframes;

	getInterpolateParams(motorId);
}

// clear all keyframes on specified motor
static void clearMotorKeyframes(uint8_t motorId, MotorKeyframeNode* keyframes) {
	MotorHead &head = motorHeads[motorId];
	uint8_t count = 0;
	while (keyframes) {
		MotorKeyframeNode* tmp = keyframes->next;
		free((void*)keyframes);
		keyframes = tmp;
		count++;
	}
	uint8_t newOccipied = head.nOccupied - count;
    initMotorHead(motorId);
    head.nOccupied = newOccipied;
}

static void shiftMotorKeyframes(MotorKeyframeNode* keyframes, uint16_t timeOffset) {
	while (keyframes) {
		keyframes->start += timeOffset;
		keyframes->end += timeOffset;
		keyframes = keyframes->next;
	}
}

/////////////////////////////////////////// debug ///////////////////////////////////////////////////////
void printNode(MotorKeyframeNode* node, bool isHead) {
	printf("[id: %d, %d - %d, pose: %d]", getMovementId(node->id), node->start, node->end, node->pose);
	if (isHead) printf("(READ)");
}

void printMotorKeyframes(uint8_t motorId) {
	MotorHead &head = motorHeads[motorId];

	printf("currentTime: %d, nextTime: %d \r\n", movementTime, head.nextTime);

	MotorKeyframeNode* node = head.head;
	while (node) {
		printNode(node, node == head.read);
		printf(" -> ");
		node = node->next;
	}
	printf("NULL \r\n");
}

void printAllMotorKeyframes() {
	for (int i=0; i<allBoards.GetNTotalMotor(); i++) {
		printf("=== motor %i === \n", i);
		printMotorKeyframes(i);
	}
}

void printInterpolateParams() {
	for (int i=0; i<allBoards.GetNTotalMotor(); i++) {
		printf("motor %i: slopeInteger: %i, slopeDecimal: %i\n", i, motorHeads[i].slopeInteger, motorHeads[i].slopeDecimal);
	}
}

/////////////////////////////////////////// interface to hardware ///////////////////////////////////////

static xSemaphoreHandle intervalSemaphore;	// semaphore to allow movement manager send interpolate buffer in specified interval
static xTaskHandle movementManagerTask;

static void movementTick() {
	xSemaphoreTake(tickSemaphore, portMAX_DELAY);

	if (tickPaused) {
		xSemaphoreGive(tickSemaphore);
        return;
    }

	movementTime++;

	// prepare command
	UdpCmdPacket cmd;
	cmd.command = CI_INTERPOLATE; 
	cmd.length = cmd.CommandLen();
	cmd.SetPeriod(MS_PER_MOVEMENT_TICK * 3);
	cmd.SetTargetCountWrite(++targetWrite);

	for (int i = 0; i < allBoards.GetNTotalMotor(); i++) {
		// change pose
		MotorHead &head = motorHeads[i];
		uint8_t differece = head.slopeInteger;
		uint16_t newError = head.slopeError + head.slopeDecimal;
		if (newError < head.slopeError) differece += 1;
		head.slopeError = newError;
		head.currentPose += head.minus ? -differece : differece;

		// update motor
		cmd.SetMotorPos(head.currentPose, i);

		// change interpolating keyframes
		if (movementTime == motorHeads[i].nextTime && motorHeads[i].head) finishKeyframe(i);
	}

	UdpCom_ReceiveCommand(cmd.bytes+2, cmd.length, CS_MOVEMENT_MANAGER);

	xSemaphoreGive(tickSemaphore);
}

static bool skippedOneLoop = false;		// forbid continuous skip (because the targetWrite will not be updated)
static void movementManager(void* arg) {
	while(1) {
		xSemaphoreTake(intervalSemaphore, portMAX_DELAY);	// tick when timer alarm
		if (!receivedReturn) {								// not tick if return packet for last command not come
			ESP_LOGD(LOG_TAG, "Skip one loop because no return CI_INTERPOLATED received in %i ms", MS_PER_MOVEMENT_TICK);
			continue;
		}

		short nVacancy = getInterpolateBufferVacancy();

		// the interpolate buffer have been changed by except this task		// TODO more precise way
		if (nVacancy < 0 || nVacancy > allBoards.GetNTarget()-2) {
			ESP_LOGD(LOG_TAG, "interpolate buffer vacany: %i, recalibrate pose", nVacancy);

			// get new current pose
			calibrateCurrentPose = true;
			movementQueryInterpolateState();

			// recalculate interpolate params according to new current pose
			xSemaphoreTake(tickSemaphore, portMAX_DELAY);
			for (int i=0; i<allBoards.GetNTotalMotor(); i++) getInterpolateParams(i);
			xSemaphoreGive(tickSemaphore);

			// shift target write
			targetWrite = targetCountReadMax + 2;
		}

		// avoid overflow of interpolate buffer in PIC
		if (nVacancy <= PIC_INTERPOLATE_BUFFER_VACANCY_MIN && !skippedOneLoop) {
			ESP_LOGD(LOG_TAG, "interpolate buffer vacancy: %i, skip one loop", nVacancy);
			skippedOneLoop = true;
			continue;
		} else if (skippedOneLoop) skippedOneLoop = false;

		// do tick
		receivedReturn = false;
		movementTick();
	}
}

static void IRAM_ATTR onTimerTriggered(void* arg) {
	TIMERG0.int_clr_timers.t0 = 1;
	TIMERG0.hw_timer[MOVEMENT_MANAGER_TIMER_IDX].config.alarm_en = TIMER_ALARM_EN;
	
	xSemaphoreGive(intervalSemaphore);
}

static void initTimer() {
	/* Select and initialize basic parameters of the timer */
    timer_config_t config;
    config.divider = MOVEMENT_MANAGER_TIMER_DIVIDER;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_EN;
    config.intr_type = TIMER_INTR_LEVEL;
    config.auto_reload = TIMER_AUTORELOAD_EN;
    timer_init(MOVEMENT_MANAGER_TIMER_GROUP, MOVEMENT_MANAGER_TIMER_IDX, &config);

	/* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    timer_set_counter_value(MOVEMENT_MANAGER_TIMER_GROUP, MOVEMENT_MANAGER_TIMER_IDX, 0x00000000ULL);

	/* Configure the alarm value and the interrupt on alarm. */
    timer_set_alarm_value(MOVEMENT_MANAGER_TIMER_GROUP, MOVEMENT_MANAGER_TIMER_IDX, MS_PER_MOVEMENT_TICK * MOVEMENT_MANAGER_TIMER_SCALE);
    timer_enable_intr(MOVEMENT_MANAGER_TIMER_GROUP, MOVEMENT_MANAGER_TIMER_IDX);
    timer_isr_register(MOVEMENT_MANAGER_TIMER_GROUP, MOVEMENT_MANAGER_TIMER_IDX, onTimerTriggered, NULL, ESP_INTR_FLAG_IRAM, NULL);

    timer_start(MOVEMENT_MANAGER_TIMER_GROUP, MOVEMENT_MANAGER_TIMER_IDX);
}

static void initMovementManager() {
	tickSemaphore = xSemaphoreCreateMutex();
	vSemaphoreCreateBinary(intervalSemaphore);

	xTaskCreate(movementManager, "movement_manager", 1024*3, NULL, tskIDLE_PRIORITY+2, &movementManagerTask);

	initTimer();
}

// init data structure for movement interpolation
void initMovementDS() {
	initPICPacketHandler();

	initMotorHeads();
	initPausedMovements();

	initMovementManager();
}

/////////////////////////////////////////// api for WROOM ///////////////////////////////////////////////

bool canAddKeyframe(MovementKeyframe& keyframe) {
	vector<uint8_t> &motorId = keyframe.motorId;

	// check motor
	for (int i=0; i<keyframe.motorCount; i++) {
		if (motorId[i] >= allBoards.GetNTotalMotor()) return false;	// wrong motor id
		else if (motorHeads[motorId[i]].nOccupied == MOTOR_KEYFRAME_BUFFER_SIZE) return false;	// keyframe list is full
	}
	
	// check ref
	if (keyframe.refId && !getNode(keyframe.refMotorId, keyframe.id)) return false;	// can not find reference node

	return true;
}

void addKeyframe(MovementKeyframe& keyframe) {
	xSemaphoreTake(tickSemaphore, portMAX_DELAY);

	for (int i=0; i<keyframe.motorCount; i++) {
		// init node
		struct MotorKeyframeNode* node = (struct MotorKeyframeNode*)malloc(sizeof(struct MotorKeyframeNode));
		node->id = keyframe.id;
		node->pose = keyframe.pose[i];
		node->end = keyframe.period;
		node->next = NULL;

		// add node
		if (!keyframe.refId) addNodeDefault(keyframe.motorId[i], node, true);
		else {
			MotorKeyframeNode* refNode = getNode(keyframe.motorId[i], keyframe.id);
			addNodeAtTime(keyframe.motorId[i], node, true, refNode->start + keyframe.timeOffset);
		}
	}

	xSemaphoreGive(tickSemaphore);

	printAllMotorKeyframes();
}

// pause one movement
void pauseMovement(uint8_t movementId, uint8_t motorCount, const vector<uint8_t> &motorId) {
	#ifdef WROOM
	    xSemaphoreTake(tickSemaphore, portMAX_DELAY);
    #endif

	for (int i=0; i<motorCount; i++) {
		MotorKeyframeNode* pausedNode = pickMotorKeyframes(motorId[i], movementId);
		if(pausedNode) insertToPausedMovementList(motorId[i], pausedNode);
	}

	#ifdef WROOM
	    xSemaphoreGive(tickSemaphore);
    #endif
}
// pause interpolate
void pauseInterpolate() {
	#ifdef WROOM
	    xSemaphoreTake(tickSemaphore, portMAX_DELAY);
    #endif

	tickPaused = true;

	#ifdef WROOM
	    xSemaphoreGive(tickSemaphore);
    #endif
}
// resume one movement
void resumeMovement(uint8_t movementId, uint8_t motorCount) {
	#ifdef WROOM
	    xSemaphoreTake(tickSemaphore, portMAX_DELAY);
    #endif

	PausedMovementHead* head = pausedMovements;
	while (motorCount && head->next) {
		MotorKeyframeNode* pausedNode = head->next->head;

		// resume one motor keyframes
		if (getMovementId(pausedNode->id) == movementId) {
			// insert to interpolate list
			uint8_t motorId = head->next->motorId;
			shiftMotorKeyframes(pausedNode, movementTime - head->next->pausedTime);
			insertMotorKeyframes(motorId, pausedNode);

			// delete node
			PausedMovementHead* next = head->next->next;
			free(head->next);
			head->next = next;

			// decrease count
			motorCount--;
		}

		head = head->next;
	}

	#ifdef WROOM
	    xSemaphoreGive(tickSemaphore);
    #endif
}
// resume interpolate
void resumeInterpolate() {
	#ifdef WROOM
	    xSemaphoreTake(tickSemaphore, portMAX_DELAY);
    #endif

	// the current pos of every motor might have been changed
	for (int i=0; i<allBoards.GetNTotalMotor(); i++) {
		motorHeads[i].currentPose = motorState.pos[i];
		getInterpolateParams(i);
	}

	tickPaused = false;

	#ifdef WROOM
	    xSemaphoreGive(tickSemaphore);
    #endif
}

// clear specified movement in the buffer (interpolate list & paused list)
void clearMovement(uint8_t movementId, uint8_t motorCount, const vector<uint8_t> motorId) {
	#ifdef WROOM
	    xSemaphoreTake(tickSemaphore, portMAX_DELAY);
    #endif

	// clear interpolate list
	for (int i=0; i<motorCount; i++) {
		MotorKeyframeNode* keyframes = pickMotorKeyframes(motorId[i], movementId);
		clearMotorKeyframes(i, keyframes);
	}

	// clear paused list
	PausedMovementHead* head = pausedMovements;
	while (motorCount && head->next) {
		MotorKeyframeNode* pausedNode = head->next->head;

		// find one motor keyframes
		if (getMovementId(pausedNode->id) == movementId) {
			// clear interpolate list
			uint8_t motorId = head->next->motorId;
			clearMotorKeyframes(motorId, pausedNode);

			// delete node
			PausedMovementHead* next = head->next->next;
			free(head->next);
			head->next = next;

			// decrease count
			motorCount--;
		}

		head = head->next;
	}

	#ifdef WROOM
	    xSemaphoreGive(tickSemaphore);
    #endif
}

// clear paused list
void clearPausedMovements() {
	PausedMovementHead* tmp = pausedMovements->next;

	// clear sub keyframes
	while (tmp) {
		clearMotorKeyframes(tmp->motorId, tmp->head);
		tmp = tmp->next;
	}

	// clear heads
	tmp = pausedMovements->next;
	while (tmp) {
		pausedMovements->next = tmp->next;
		free(tmp);

		tmp = pausedMovements->next;
	}
}

// clear interpolate list & paused list
void clearInterpolateBuffer() {
	clearPausedMovements();

	#ifdef WROOM
	    xSemaphoreTake(tickSemaphore, portMAX_DELAY);
    #endif

	// clear interpolate list
	for (int i=0; i<allBoards.GetNTotalMotor(); i++) {
		clearMotorKeyframes(i, motorHeads[i].head);
	}

	initMotorHeads();

	#ifdef WROOM
	    xSemaphoreGive(tickSemaphore);
    #endif
}

// query interpolate state (return the head node of all motors)
void queryInterpolateState(InterpolateState* interpolateState) {
	for (int i=0; i<allBoards.GetNTotalMotor(); i++) {
		interpolateState->nOccupied[i] = motorHeads[i].nOccupied;

		if (!motorHeads[i].head) {
			interpolateState->id[i] = 0;
			continue;
		};
		interpolateState->id[i] = motorHeads[i].head->id;
	}
}