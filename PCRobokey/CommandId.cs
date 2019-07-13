
enum CommandId {
	CI_NONE,				//0	As reset makes 0 and 0xFF, must avoid use of them in header. 
	CI_BOARD_INFO,          //1 Board information.
	CI_SET_CMDLEN,			//2	Set command length for each board id.
	CI_ALL,					//3 Send all data and return all status.
	CI_SENSOR,				//4	Return sensor data
	CI_DIRECT,              //5 Directly set servo targets (positions and velicities).
	CI_CURRENT,             //6 Set currents as servo targets.
	CI_INTERPOLATE,         //7 Send new frame for interpolation.
	CI_FORCE_CONTROL,		//8	Position and force control with interpolation.
	CI_SETPARAM,            //9 Set parameter.
    CI_RESET_SENSOR,        //10 Reset sensor.
    CI_NCOMMAND,
    CIU_TEXT = CI_NCOMMAND,	//11 return text message: cmd, type, length, bytes
	CIU_SET_IPADDRESS,		//12 Set ip address to return the packet
    CIU_GET_IPADDRESS,      //13 Get ip address to return the packet
    CIU_GET_SUBBOARD_INFO,  //14 Get sub board info
	CIU_MOVEMENT,			//15 movement command

	CIU_NCOMMAND,           //15 number of commands
	CIU_NONE = -1           //  no command is in receiving state.
};
enum SetParamType{
	PT_PD,
    PT_CURRENT,
	PT_TORQUE_LIMIT,
	PT_BOARD_ID,
};
enum ResetSensorFlags {
	RSF_NONE=0,
	RSF_MOTOR=1,
	RSF_FORCE=2,
};
enum MovementCommandId {
	MCI_NONE = 0,
	MCI_ADD_KEYFRAME = 1
}
