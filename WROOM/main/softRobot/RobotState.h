#pragma once
#include "BoardBase.h"
extern "C" {
#include "../../../PIC/control.h"
}

struct RobotState: public BoardRetBase{
	RobotState();
	//	robot's state
	ControlMode mode;				//	PIC/control.h
	unsigned char nTargetMin;			//	nTaret for all board
	unsigned char targetCountWrite;		//	targetCount for next writing. 
	unsigned char targetCountReadMin;	//	targetCount for read of one of the board.
	unsigned char targetCountReadMax;	//	targetCount for read of one of the board.
	unsigned short tickMin;
	unsigned short tickMax;
	tiny::vector<SDEC> position;		//	motor position
	tiny::vector<SDEC> velocity;		//	motor velocitry
	tiny::vector<SDEC> current;			//	current sensor for motor;
	tiny::vector<SDEC> force;			//	force sensor
	tiny::vector<SDEC> touch;			//	touch sensor

	virtual void SetAll(ControlMode cm, unsigned char tcrMin, unsigned char tcrMax, 
		unsigned short tkMin, unsigned short tkMax, 
		SDEC* pos, SDEC* vel, SDEC* current, SDEC* f, SDEC* t){
		mode = cm;
		targetCountReadMax = tcrMax;
		targetCountReadMin = tcrMin;
		tickMin = tkMin; tickMax = tkMax;
		if (pos){
			for(int i=0; i!=position.size(); ++i){
				position[i] = pos[i];
			}
		}
		if (vel){
			for(int i=0; i!=velocity.size(); ++i){
				velocity[i] = vel[i];
			}
		}
		if (f){
			for(int i=0; i!=force.size(); ++i){
				force[i] = f[i];
			}
		}
		if (t){
			for(int i=0; i!=touch.size(); ++i){
				touch[i] = t[i];
			}
		}		
	}
	void SetMotorPos(short p, int i) {
		position[i] = p;
	}
	void SetMotorVel(short v, int i) {
		velocity[i] = v;
	}
	//	for interpolate and force control
	virtual void SetTargetCountReadMin(unsigned char c){
		targetCountReadMin = c;
	}
	virtual void SetTargetCountReadMax(unsigned char c){
		targetCountReadMax = c;
	}	
	void SetTickMin(unsigned short t) {
		tickMin = t;
	}
	void SetTickMax(unsigned short t) {
		tickMax = t;
	}
	//	sense
	void SetCurrent(short c, int i) {
		current[i] = c;
	}
	void SetForce(short f, int i) {
		force[i] = f;
	}
	void SetTouch(short t, int i) {
		touch[i] = t;
	}
	void SetBoardInfo(int systemId, int nTarget, int nMotor, int nCurrent, int nForce, int nTouch) {
		//	Do nothing. Only one instance (AllBoards::state is initialzed in AllBoards::EnumerateBoards() ). 
	}
};
