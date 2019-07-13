#ifndef _SR_MOVEMENT_H
#define _SR_MOVEMENT_H

#include <stdio.h>
#include <vector>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "AllBoards.h"
#include "UdpCom.h"

using namespace std;

///////////////////////////////////////// data structure for WROOM interface ///////////////////////////// 

struct MovementKeyframe {
	uint16_t id;				// 8-bit movement id + 8-bit keyframe id
	uint8_t motorCount;			// count of motors used in the movement
	vector<uint8_t> motorId;	// the motorIds used
	uint16_t period;			// note that the sum of period in list could not larger than UINT16_MAX (or the sorting might fail)
	vector<short> pose;			// the poses correspond with motorIds

	uint16_t refId;             // 0 if no ref (movement id should start from 1)
	uint8_t refMotorId;
	short timeOffset;
}__attribute__((packed));

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

/////////////////////////////////////////// interface to hardware ///////////////////////////////////////
void movementTick();
void initMovementDS();

/////////////////////////////////////////// api for WROOM ///////////////////////////////////////////////

bool canAddKeyframe(struct MovementKeyframe* keyframe);
void addKeyframe(struct MovementKeyframe* keyframe);

void pauseInterpolate();
void resumeInterpolate();

#endif