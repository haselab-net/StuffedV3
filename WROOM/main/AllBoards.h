#pragma once
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "freertos/FreeRTOS.h"
#include "TinyContainer.h"
#include "WroomEnv.h"
#include "BoardBase.h"
extern "C"{
#include "../../PIC/control.h"
}

class DeviceMap {
public:
	int board;
	int id;
	DeviceMap(int b, int m): board(b), id(m){
	}
};

class UartForBoards;
class BoardDirect;
class UdpCmdPacket;
class UdpRetPacket;

struct RobotCommand: public BoardCmdBase{
	RobotCommand();
	tiny::vector<SDEC> targetPosition;	//	motor's target position
	tiny::vector<SDEC> targetVelocity;	//	motor's target velocitry
	tiny::vector<SDEC> forceControlJacobian;	
										//	jacobian for force control
	short targetPeriod;					//	period to interpolate to acheive the target
	short targetCount;					//	count of the target to overwrite a target in the queue. 	
	tiny::vector<SDEC> controlK;
	tiny::vector<SDEC> controlB;
	tiny::vector<SDEC> torqueMin;
	tiny::vector<SDEC> torqueMax;
	ResetSensorFlags resetSensorFlags;
	ControlMode controlMode;

	short GetControlMode(){ return controlMode; }
	short GetMotorPos(int i){ return targetPosition[i]; }
	short GetMotorVel(int i){ return targetVelocity[i]; }
	short GetPeriod(){ return targetPeriod; }
	short GetTargetCount(){ return targetCount; }
	short GetForceControlJacob(int j, int i) { return  forceControlJacobian[j*3+i]; }
	short GetControlK(int i){ return controlK[i]; }
	short GetControlB(int i){ return controlB[i]; }
	short GetTorqueMin(int i){ return torqueMin[i]; }
	short GetTorqueMax(int i){ return torqueMax[i]; }
	short GetResetSensorFlags(){
		return resetSensorFlags;
	}
};
struct RobotState: public BoardRetBase{
	RobotState();
	//	robot's state
	enum ControlMode mode;				//	PIC/control.h
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

//
class AllBoards{
	SemaphoreHandle_t mutex;
public:
	RobotState state;
	RobotCommand command;
	int nBoard;
	static const int NUART = 2;
	tiny::vector<DeviceMap> motorMap;
	tiny::vector<DeviceMap> forceMap;
	tiny::vector<DeviceMap> currentMap;
	UartForBoards* uart[NUART];
	BoardDirect* boardDirect;
	SemaphoreHandle_t seUartFinished;
	#if UDP_UART_ASYNC
	TaskHandle_t taskExec; 
	#endif
	int GetNTotalMotor() { return motorMap.size(); }
	int GetNTotalCurrent() { return currentMap.size(); }
	int GetNTotalForce() { return forceMap.size(); }
	int GetNTarget() { return state.nTargetMin; }
	int GetSystemId() { return 0; }
	AllBoards();
	~AllBoards();
	void EnumerateBoard();	
	void Init();
	bool HasRet(unsigned short id);
	///	Write contents of the UdpCmdPacket to all boards. 
	void WriteCmd(unsigned short commandId, BoardCmdBase& packet);	
	///	Read returns of all boards to  UdpRetPacket.   bNext: start to read next UART data (send notify to recvTask).
	void ReadRet(unsigned short commandId, BoardRetBase& packet);

	void ExecLoop();
};
extern AllBoards allBoards;
