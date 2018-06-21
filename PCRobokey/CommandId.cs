
enum CommandId {
	CI_NONE,				//0	As reset makes 0 and 0xFF, must avoid use of them in header. 
	CI_BOARD_INFO,          //1 Board information.
	CI_SET_CMDLEN,			//2	Set command length for each board id.
	CI_SENSOR,				//3	Return sensor data
	CI_DIRECT,              //4 Directly set servo targets (positions and velicities).
	CI_INTERPOLATE,         //5 Send new frame for interpolation.
	CI_FORCE_CONTROL,		//6	Position and force control with interpolation.
	CI_PDPARAM,             //7 Set control parameter.
	CI_TORQUE_LIMIT,        //8 Set min and max torques.
    CI_RESET_SENSOR,        //9 Reset sensor.
    CI_NCOMMAND,
    CIU_TEXT = CI_NCOMMAND,	//10 return text message: cmd, type, length, bytes
	CIU_SET_IPADDRESS,		//11 Set ip address to return the packet
    CIU_GET_IPADDRESS,      //12 Get ip address to return the packet

	CIU_NCOMMAND,           //13 number of commands
	CIU_NONE = -1           //  no command is in receiving state.
};
