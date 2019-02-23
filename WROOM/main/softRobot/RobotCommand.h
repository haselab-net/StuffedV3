#pragma once
#include "BoardBase.h"
extern "C" {
#include "../../PIC/control.h"
}

class RobotCommand: public BoardCmdBase{
public:
	ControlMode mode;							//	set SKIP not to add target
	tiny::vector<SDEC> targetPosition;			//	motor's target position
	tiny::vector<SDEC> targetVelocity;			//	motor's target velocitry
	tiny::vector<SDEC> forceControlJacobian;	//	jacobian for force control
	short targetPeriod;							//	period to interpolate to acheive the target
	short targetCount;							//	count of the target to overwrite a target in the queue.

	//	To be implemnented 
	tiny::vector<SDEC> controlK;
	tiny::vector<SDEC> controlB;
	tiny::vector<SDEC> torqueMin;
	tiny::vector<SDEC> torqueMax;
	ResetSensorFlags resetSensorFlags;

	RobotCommand();

	/**	Set control mode and add motor target angles.
	mode can be CM_DIRECT, CM_INTERPOLATE, CM_FORCE_CONTROL.
	In the case of CM_DIRECT, The controller uses "targetPosition" and "targetVelocity" to set control target angles immediately.
	in the case of CM_INTERPOLATE and CM_FORCE_CONTROL, targetPeriod
	new motor angle targets are added. In this case, targetCountWrite should be RobotState::targetCountWrite + 1.
	"targetPosition" is the goal and "targetPeriod" is dulation to acheive to the goal in 1/3 ms.
	*/
	void AddTarget(ControlMode mode);

	//	implementation for BoardCmdBase
	short GetControlMode(){ return mode; }
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
