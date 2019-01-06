
enum CommandId {
	CI_NONE,				//0	As reset makes 0 and 0xFF, must avoid use of them in header. 
	CI_BOARD_INFO,          //1 Board information.
	CI_SET_CMDLEN,			//2	Set command length for each board id.
	CI_ALL,					//3 Send all data and return all status
	CI_SENSOR,				//4	Return sensor data
	CI_DIRECT,              //5 Directly set servo targets (positions and velicities).
	CI_INTERPOLATE,         //6 Send new frame for interpolation.
	CI_FORCE_CONTROL,		//7	Position and force control with interpolation.
	CI_PDPARAM,             //8 Set control parameter.
	CI_TORQUE_LIMIT,        //9 Set min and max torques.
    CI_RESET_SENSOR,        //10 Reset sensor.
    CI_NCOMMAND,
    CIU_TEXT = CI_NCOMMAND,	//11 return text message: cmd, type, length, bytes
	CIU_SET_IPADDRESS,		//12 Set ip address to return the packet
    CIU_GET_IPADDRESS,      //13 Get ip address to return the packet

	CIU_NCOMMAND,           //14 number of commands
	CIU_NONE = -1           //  no command is in receiving state.
};
enum ResetSensorFlags {
	RSF_NONE=0,
	RSF_MOTOR=1,
	RSF_FORCE=2,
};
