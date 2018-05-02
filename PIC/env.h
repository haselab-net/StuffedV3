#ifndef ENV_H
#define ENV_H

//	Macro

//#define DEBUG
//#define MODULETEST    //  module test mode for debugging


#ifdef MODULETEST
#define DEBUG
#endif

extern int traceLevel;

#endif
