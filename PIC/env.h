#ifndef ENV_H
#define ENV_H

//	Macro
#define PICUARTINT		//	use interrupt for pic-host communication

//#define DEBUG
//#define MODULETEST    //  module test mode for debugging


#ifdef MODULETEST
#define DEBUG
#endif

#endif
