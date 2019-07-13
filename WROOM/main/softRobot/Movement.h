#ifndef _SR_MOVEMENT_H
#define _SR_MOVEMENT_H

#include <stdio.h>
#include <vector>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>
#include <driver/periph_ctrl.h>
#include <driver/timer.h>

#include "AllBoards.h"

using namespace std;

///////////////////////////////////////// data structure for WROOM interface ///////////////////////////// 

#define MOTOR_KEYFRAME_BUFFER_SIZE 10        // size of buffer for every motor
#define MS_PER_MOVEMENT_TICK 50				// 20 ms = 1 movement tick

class MovementKeyframe {
public:
	uint16_t id;				// 8-bit movement id + 8-bit keyframe id
	uint8_t motorCount;			// count of motors used in the movement
	vector<uint8_t> motorId;	// the motorIds used
	uint16_t period;			// note that the sum of period in list could not larger than UINT16_MAX (or the sorting might fail)
	vector<short> pose;			// the poses correspond with motorIds

	uint16_t refId;             // 0 if no ref (movement id should start from 1)
	uint8_t refMotorId;
	short timeOffset;
};

struct MovementKeyframeAddState {
    uint16_t id;
    uint8_t success;
}__attribute__((packed));

struct InterpolateState {
	vector<uint16_t> id;
	vector<uint8_t> nOccupied;
};

/////////////////////////////////////////// api for accessing PIC ///////////////////////////////////////////////
static void movementQueryInterpolateState();
void movementOnGetPICInfo(UdpRetPacket& pkt);

/////////////////////////////////////////// debug ///////////////////////////////////////////////////////
void printMotorKeyframes(uint8_t motorId);
void printInterpolateParams();

/////////////////////////////////////////// interface to hardware ///////////////////////////////////////
#define MOVEMENT_MANAGER_TIMER_DIVIDER 16
#define MOVEMENT_MANAGER_TIMER_GROUP TIMER_GROUP_0
#define MOVEMENT_MANAGER_TIMER_IDX TIMER_0
#define MOVEMENT_MANAGER_TIMER_SCALE (TIMER_BASE_CLK / MOVEMENT_MANAGER_TIMER_DIVIDER / 1000)  // convert counter value to ms

void initMovementDS();

/////////////////////////////////////////// api for WROOM ///////////////////////////////////////////////

bool canAddKeyframe(MovementKeyframe& keyframe);
void addKeyframe(MovementKeyframe& keyframe);

void pauseInterpolate();
void resumeInterpolate();

#endif