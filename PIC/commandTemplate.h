#ifndef COMMAND_TEMPLATE_H
#define COMMAND_TEMPLATE_H
#include "env.h"
#include "decimal.h"

#define sizeof_field(s,m) (sizeof((((s*)0)->m)))

#ifdef __cplusplus
#define BOARDINFOFUNCS(BOARD)	\
	static const char* GetBoardName(){ return #BOARD;}				\
	static int GetModelNumber(){ return BOARD##_MODEL_NUMBER;}		\
	static int GetNTarget(){ return BOARD##_NTARGET;}				\
	static int GetNMotor(){ return BOARD##_NMOTOR;}					\
	static int GetNForce(){ return BOARD##_NFORCE;}					\

#else
#define BOARDINFOFUNCS(BOARD)
#endif

#define MAXBOARDID	7
#define BORADIDBITS 3

union CommandHeader{
	unsigned char header;
	struct {
		unsigned boardId : 3;
		unsigned commandId : 5;
	} __attribute__((__packed__));
} __attribute__((__packed__));

#define DEFINE_CommandPacket(BOARD)									\
union CommandPacket##BOARD {										\
	BOARDINFOFUNCS(BOARD)											\
	struct {														\
		unsigned char bytes_pad[3];									\
		unsigned char bytes[1 + BOARD##_NMOTOR * 2 * 2];			\
	} __attribute__((__packed__));									\
	struct {														\
		unsigned char header_pad[3];								\
		union {														\
			unsigned char header;									\
			struct {												\
				unsigned boardId : 3;								\
				unsigned commandId : 5;								\
			} __attribute__((__packed__));							\
		} __attribute__((__packed__));								\
		union {														\
			struct {/*  CI_SET_CMDLEN	*/							\
				unsigned char len[CI_NCOMMAND];						\
			} __attribute__((__packed__)) cmdLen;					\
			struct {/*  CI_DIRECT	*/								\
				SDEC pos[BOARD##_NMOTOR];							\
				SDEC vel[BOARD##_NMOTOR];							\
			} __attribute__((__packed__)) direct;					\
			struct { /*	 CI_INTERPOLATE */							\
				SDEC pos[BOARD##_NMOTOR];							\
				short period;		/*	period to interpolate */	\
				unsigned char count;								\
			} __attribute__((__packed__)) interpolate;				\
			struct { /*	 CI_FORCE_CONTROL */						\
				SDEC pos[BOARD##_NMOTOR];							\
				SDEC Jacob[BOARD##_NFORCE][BOARD##_NMOTOR];			\
				short period;		/*	period to interpolate */	\
				unsigned char count;								\
			} __attribute__((__packed__)) forceControl;				\
			struct {				 /*	 CI_PDPARAM */				\
				SDEC k[BOARD##_NMOTOR];								\
				SDEC b[BOARD##_NMOTOR];								\
			} __attribute__((__packed__)) pdParam;					\
			struct {				 /*	 CI_TORQUE_LIMIT	 */		\
				SDEC min[BOARD##_NMOTOR];							\
				SDEC max[BOARD##_NMOTOR];							\
			} __attribute__((__packed__)) torqueLimit;				\
			struct {				 /*	 CI_RESET_SENSOR	 */		\
                short flags;                                        \
			} __attribute__((__packed__)) resetSensor;				\
		};															\
	};																\
};																	\
enum BOARD##CommandLenEnum{																	\
	BOARD##_CLEN_NONE = 1,																	\
	BOARD##_CLEN_BOARD_INFO = 1,															\
	BOARD##_CLEN_SET_CMDLEN = 1+sizeof_field(union CommandPacket##BOARD, cmdLen),			\
    BOARD##_CLEN_SENSOR = 1,																\
	BOARD##_CLEN_DIRECT = 1+sizeof_field(union CommandPacket##BOARD, direct),				\
    BOARD##_CLEN_INTERPOLATE = 1+sizeof_field(union CommandPacket##BOARD, interpolate),		\
    BOARD##_CLEN_FORCE_CONTROL = 1+sizeof_field(union CommandPacket##BOARD, forceControl),	\
    BOARD##_CLEN_PD_PARAM = 1+sizeof_field(union CommandPacket##BOARD, pdParam),			\
    BOARD##_CLEN_TORQUE_LIMIT = 1+sizeof_field(union CommandPacket##BOARD, torqueLimit),	\
	BOARD##_CLEN_RESET_SENSOR = 1+sizeof_field(union CommandPacket##BOARD, resetSensor),	\
};																	\
const unsigned char cmdPacketLen##BOARD[CI_NCOMMAND] = {			\
    BOARD##_CLEN_NONE,												\
    BOARD##_CLEN_BOARD_INFO,										\
	BOARD##_CLEN_SET_CMDLEN,										\
	BOARD##_CLEN_SENSOR,											\
    BOARD##_CLEN_DIRECT,											\
    BOARD##_CLEN_INTERPOLATE,										\
    BOARD##_CLEN_FORCE_CONTROL,										\
    BOARD##_CLEN_PD_PARAM,											\
    BOARD##_CLEN_TORQUE_LIMIT,										\
	BOARD##_CLEN_RESET_SENSOR,  									\
};																	\

#define DEFINE_ReturnPacket(BOARD) \
union ReturnPacket##BOARD {										\
	BOARDINFOFUNCS(BOARD)										\
	struct {													\
		unsigned char bytes_pad[3];								\
		unsigned char bytes[1 + BOARD##_NMOTOR * 2 * 2];		\
	}__attribute__((__packed__));								\
	struct {													\
		unsigned char header_pad[3];							\
		union {													\
			unsigned char header;								\
			struct {											\
				unsigned boardId : 3;							\
				unsigned commandId : 5;							\
			}__attribute__((__packed__));						\
		}__attribute__((__packed__));							\
		union {													\
			struct {		 /*	 CI_BOARD_INFO */				\
				unsigned char modelNumber;						\
				unsigned char nTarget;							\
				unsigned char nMotor;							\
				unsigned char nForce;							\
			}__attribute__((__packed__)) boardInfo;				\
			struct {		 /*	 CI_SENSOR */					\
				SDEC pos[BOARD##_NMOTOR];						\
				SDEC force[BOARD##_NFORCE];						\
			}__attribute__((__packed__)) sensor;				\
			struct {		 /*	 CI_DIRECT */					\
				SDEC pos[BOARD##_NMOTOR];						\
				SDEC vel[BOARD##_NMOTOR];						\
			}__attribute__((__packed__)) direct;				\
			struct {		 /*	 CI_INTERPOLATE */				\
				SDEC pos[BOARD##_NMOTOR];						\
				unsigned short tick;							\
				unsigned char countOfRead;						\
			}__attribute__((__packed__)) interpolate;			\
		};														\
	};															\
};																\
enum BOARD##ReturnLenEnum{										\
	BOARD##_RLEN_NONE = 0,										\
	BOARD##_RLEN_BOARD_INFO = 1+sizeof_field(union ReturnPacket##BOARD, boardInfo),		\
	BOARD##_RLEN_SENSOR = 1 + sizeof_field(union ReturnPacket##BOARD, sensor),			\
	BOARD##_RLEN_DIRECT = 1+sizeof_field(union ReturnPacket##BOARD, direct),			\
    BOARD##_RLEN_INTERPOLATE = 1+sizeof_field(union ReturnPacket##BOARD, interpolate),	\
    BOARD##_RLEN_FORCE_CONTROL = 1+sizeof_field(union ReturnPacket##BOARD, interpolate),\
    BOARD##_RLEN_NORETURN = 0,															\
};																						\
const unsigned char retPacketLen##BOARD[CI_NCOMMAND]={									\
    BOARD##_RLEN_NONE,																	\
    BOARD##_RLEN_BOARD_INFO,															\
    BOARD##_RLEN_NONE,																	\
	BOARD##_RLEN_SENSOR,																\
    BOARD##_RLEN_DIRECT,																\
    BOARD##_RLEN_INTERPOLATE,															\
    BOARD##_RLEN_FORCE_CONTROL,															\
    BOARD##_RLEN_NORETURN,																\
    BOARD##_RLEN_NORETURN,																\
    BOARD##_RLEN_NORETURN,																\
};


#define DEFINE_Packets(BOARD)				\
DEFINE_CommandPacket(BOARD)					\
DEFINE_ReturnPacket(BOARD)					\


#define CHOOSE_BoardInfo(BOARD)     							\
enum BoardInfo{                     							\
    MODEL_NUMBER = BOARD##_MODEL_NUMBER,					 	\
    NTARGET = BOARD##_NTARGET,        							\
    NMOTOR = BOARD##_NMOTOR,        							\
    NFORCE = BOARD##_NFORCE,         							\
};																\
typedef union CommandPacket##BOARD CommandPacket;				\
typedef union ReturnPacket##BOARD ReturnPacket;					\
const unsigned char* const cmdPacketLen = cmdPacketLen##BOARD;	\
const unsigned char* const retPacketLen = retPacketLen##BOARD;	\

#endif
