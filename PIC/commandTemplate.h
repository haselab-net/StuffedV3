#ifndef COMMAND_TEMPLATE_H
#define COMMAND_TEMPLATE_H
#include "env.h"
#include "fixed.h"

#define sizeof_field(s,m) (sizeof((((s*)0)->m)))

#ifdef __cplusplus
#define BOARDINFOFUNCS(BOARD)	\
	static const char* GetBoardName(){ return #BOARD;}				\
	static int GetModelNumber(){ return BOARD##_MODEL_NUMBER;}		\
	static int GetNTarget(){ return BOARD##_NTARGET;}				\
	static int GetNMotor(){ return BOARD##_NMOTOR;}					\
	static int GetNCurrent(){ return BOARD##_NCURRENT;}				\
	static int GetNForce(){ return BOARD##_NFORCE;}					\
	static int GetNTouch(){ return BOARD##_NTOUCH;}					\

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
		unsigned char bytes[1 + BOARD##_NMOTOR*2 * 2];      		\
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
			struct { /*	 CI_ALL */									\
				unsigned char controlMode;							\
				unsigned char count;								\
				short period;		/*	period to interpolate */	\
				union {                                             \
                    SDEC current[BOARD##_NMOTOR];					\
                    struct{                                         \
                        SDEC pos[BOARD##_NMOTOR];					\
                        union {                                     \
                            SDEC vel[BOARD##_NMOTOR];				\
                            SDEC jacob[BOARD##_NFORCE][BOARD##_NMOTOR];	\
                        }__attribute__((__packed__));               \
                    } __attribute__((__packed__));                  \
                }__attribute__((__packed__));                       \
			} __attribute__((__packed__)) all;						\
			struct {/*  CI_DIRECT	*/								\
				SDEC pos[BOARD##_NMOTOR];							\
				SDEC vel[BOARD##_NMOTOR];							\
			} __attribute__((__packed__)) direct;					\
			struct {/*  CI_CURRENT  */								\
				SDEC current[BOARD##_NMOTOR];						\
			} __attribute__((__packed__)) current;					\
			struct { /*	 CI_INTERPOLATE */							\
				SDEC pos[BOARD##_NMOTOR];							\
				short period;		/*	period to interpolate */	\
				unsigned char count;								\
			} __attribute__((__packed__)) interpolate;				\
			struct { /*	 CI_FORCE_CONTROL */						\
				SDEC pos[BOARD##_NMOTOR];							\
				SDEC jacob[BOARD##_NFORCE][BOARD##_NMOTOR];			\
				short period;		/*	period to interpolate */	\
				unsigned char count;								\
			} __attribute__((__packed__)) forceControl;				\
			struct {    /*	 CI_SETPARAM */                         \
				unsigned char type;                                 \
                union {                                             \
                    struct {                                        \
                        SDEC k[BOARD##_NMOTOR];	/* P */             \
                        SDEC b[BOARD##_NMOTOR];	/* D */     		\
                    }__attribute__((__packed__)) pd;                \
                    struct {                                        \
                        SDEC min[BOARD##_NMOTOR];	/* Tq min */    \
                        SDEC max[BOARD##_NMOTOR];	/* Tq max */    \
                    }__attribute__((__packed__)) torque;            \
                    SDEC a[BOARD##_NMOTOR];	/* Current */           \
                    unsigned char boardId;	/* boardId */           \
                } __attribute__((__packed__));                      \
			} __attribute__((__packed__)) param;					\
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
	BOARD##_CLEN_ALL = 1+sizeof_field(union CommandPacket##BOARD, all),						\
    BOARD##_CLEN_SENSOR = 1,																\
	BOARD##_CLEN_DIRECT = 1+sizeof_field(union CommandPacket##BOARD, direct),				\
	BOARD##_CLEN_CURRENT = 1+sizeof_field(union CommandPacket##BOARD, current),				\
    BOARD##_CLEN_INTERPOLATE = 1+sizeof_field(union CommandPacket##BOARD, interpolate),		\
    BOARD##_CLEN_FORCE_CONTROL = 1+sizeof_field(union CommandPacket##BOARD, forceControl),	\
    BOARD##_CLEN_SET_PARAM = 1+sizeof_field(union CommandPacket##BOARD, param),             \
	BOARD##_CLEN_RESET_SENSOR = 1+sizeof_field(union CommandPacket##BOARD, resetSensor),	\
};																	\
const unsigned char cmdPacketLen##BOARD[CI_NCOMMAND] = {			\
    BOARD##_CLEN_NONE,												\
    BOARD##_CLEN_BOARD_INFO,										\
	BOARD##_CLEN_SET_CMDLEN,										\
	BOARD##_CLEN_ALL,												\
	BOARD##_CLEN_SENSOR,											\
    BOARD##_CLEN_DIRECT,											\
    BOARD##_CLEN_CURRENT,											\
    BOARD##_CLEN_INTERPOLATE,										\
    BOARD##_CLEN_FORCE_CONTROL,										\
    BOARD##_CLEN_SET_PARAM,											\
	BOARD##_CLEN_RESET_SENSOR,  									\
};																	\

#define DEFINE_ReturnPacket(BOARD) \
union ReturnPacket##BOARD {										\
	BOARDINFOFUNCS(BOARD)										\
	struct {													\
		unsigned char bytes_pad[3];								\
		unsigned char bytes[1 + BOARD##_NMOTOR*2*2 + BOARD##_NCURRENT*2 + BOARD##_NFORCE*2];		\
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
				unsigned char nCurrent;							\
				unsigned char nForce;							\
				unsigned char nTouch;							\
			}__attribute__((__packed__)) boardInfo;				\
			struct {		 /*	 CI_ALL */						\
				unsigned char controlMode;						\
				unsigned char countOfRead;						\
				unsigned short tick;							\
				SDEC pos[BOARD##_NMOTOR];						\
				SDEC vel[BOARD##_NMOTOR];						\
				SDEC current[BOARD##_NCURRENT];					\
				SDEC force[BOARD##_NFORCE];						\
				SDEC touch[BOARD##_NTOUCH];						\
			}__attribute__((__packed__)) all;					\
			struct {		 /*	 CI_SENSOR */					\
				SDEC pos[BOARD##_NMOTOR];						\
				SDEC current[BOARD##_NCURRENT];					\
				SDEC force[BOARD##_NFORCE];						\
				SDEC touch[BOARD##_NTOUCH];						\
			}__attribute__((__packed__)) sensor;				\
			struct {		 /*	 CI_DIRECT */					\
				SDEC pos[BOARD##_NMOTOR];						\
				SDEC vel[BOARD##_NMOTOR];						\
			}__attribute__((__packed__)) direct;				\
			struct {		 /*	 CI_CURRENT	*/					\
				SDEC pos[BOARD##_NMOTOR];						\
				SDEC vel[BOARD##_NMOTOR];						\
				SDEC current[BOARD##_NMOTOR];					\
			}__attribute__((__packed__)) current;				\
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
	BOARD##_RLEN_ALL = 1 + sizeof_field(union ReturnPacket##BOARD, all),				\
	BOARD##_RLEN_SENSOR = 1 + sizeof_field(union ReturnPacket##BOARD, sensor),			\
	BOARD##_RLEN_DIRECT = 1+sizeof_field(union ReturnPacket##BOARD, direct),			\
	BOARD##_RLEN_CURRENT = 1+sizeof_field(union ReturnPacket##BOARD, current),			\
    BOARD##_RLEN_INTERPOLATE = 1+sizeof_field(union ReturnPacket##BOARD, interpolate),	\
    BOARD##_RLEN_FORCE_CONTROL = 1+sizeof_field(union ReturnPacket##BOARD, interpolate),\
    BOARD##_RLEN_NORETURN = 0,															\
};																						\
const unsigned char retPacketLen##BOARD[CI_NCOMMAND]={									\
    BOARD##_RLEN_NONE,																	\
    BOARD##_RLEN_BOARD_INFO,															\
    BOARD##_RLEN_NONE,																	\
	BOARD##_RLEN_ALL,																	\
	BOARD##_RLEN_SENSOR,																\
    BOARD##_RLEN_DIRECT,																\
    BOARD##_RLEN_CURRENT,																\
    BOARD##_RLEN_INTERPOLATE,															\
    BOARD##_RLEN_FORCE_CONTROL,															\
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
    NCURRENT = BOARD##_NCURRENT,       							\
    NTOUCH = BOARD##_NTOUCH        								\
};																\
typedef union CommandPacket##BOARD CommandPacket;				\
typedef union ReturnPacket##BOARD ReturnPacket;					\
const unsigned char* const cmdPacketLen = cmdPacketLen##BOARD;	\
const unsigned char* const retPacketLen = retPacketLen##BOARD;	\

#endif
