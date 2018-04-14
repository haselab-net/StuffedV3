
enum CommandId {
	CI_NONE,				//	As reset makes 0 and 0xFF, must avoid use of them in header. 
	CI_BOARD_INFO,          //  Board information.
	CI_SET_CMDLEN,			//	Set command length for each board id.
	CI_SENSOR,				//	Return sensor data
	CI_DIRECT,              //  Directly set servo targets (positions and velicities).
	CI_INTERPOLATE,         //  Send new frame for interpolation.
	CI_FORCE_CONTROL,		//	Position and force control with interpolation.
	CI_PDPARAM,             //  Set control parameter.
	CI_TORQUE_LIMIT,        //  Set min and max torques.
    CI_NCOMMAND,
    CIU_TEXT = CI_NCOMMAND,	//	return text message: cmd, type, length, bytes
	CIU_SET_IPADDRESS,		//  Set ip address to return the packet
    CIU_GET_IPADDRESS,      //  Get ip address to return the packet

	CIU_NCOMMAND,           //  number of commands
	CIU_NONE = -1           //  no command is in receiving state.
};
