#pragma once
#include "BoardBase.h"
extern "C" {
#include "../../PIC/control.h"
}

struct RobotState: public BoardRetBase{
	RobotState();
	//	robot's state
	ControlMode mode;				//	PIC/control.h
	unsigned char nTargetMin;			//	nTaret for all board
	unsigned char nTargetVacancy;		//	nTargetVecancy for all board
	unsigned char nTargetRemain;		//	minimum remaining targets in the board. Must be >= 3.
	unsigned char targetCountWrite;		//	targetCount for next writing. 
	unsigned char targetCountReadMax;	//	targetCount for read of one of the board.
	unsigned short tickMin;
	unsigned short tickMax;
	tiny::vector<SDEC> position;		//	motor position
	tiny::vector<SDEC> velocity;		//	motor velocitry
	tiny::vector<SDEC> current;			//	current sensor for motor;
	tiny::vector<SDEC> force;			//	force sensor

	void SetControlMode(short cm){
		mode = (ControlMode)cm;
	}
	void SetMotorPos(short p, int i) {
		position[i] = p;
	}
	void SetMotorVel(short v, int i) {
		velocity[i] = v;
	}
	//	for interpolate and force control
	void SetTargetCountRead(short c) {
		targetCountReadMax = c;
	}
	void SetTickMin(short t) {
		tickMin = t;
	}
	void SetTickMax(short t) {
		tickMax = t;
	}
	void SetNTargetRemain(short t){
		nTargetRemain = t;
	}
	void SetNTargetVacancy(short t){
		nTargetVacancy = t;
	}
	//	sense
	void SetCurrent(short c, int i) {
		current[i] = c;
	}
	void SetForce(short f, int i) {
		force[i] = f;
	}
	void SetBoardInfo(int systemId, int nTarget, int nMotor, int nCurrent, int nForce) {
		// nothing to be done.
	}
};
