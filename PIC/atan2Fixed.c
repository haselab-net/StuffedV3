/* ************************************************************************** */
/** Descriptive File Name

  @Company
 Hasegawa Lab.

  @File Name
 atan2 for fixed point number
 * 
  @Summary
   
 * 
  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
#include "decimal.h"
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#ifdef DEBUG
#include <assert.h>
#endif

//  theta = 0 to 45 degree = 0 to 1/8  14 bit decimal
const int atanThetas[17] = {0, 163, 324, 483, 639, 790, 936, 1075, 1209, 
1336, 1457, 1571, 1678, 1779, 1874, 1964, 2048};

//  angles are represented by rotation 1.0 = 360 degree = 2*pi
//  compute arctangent only for 1.0 >= c >= s >= 0.0
int atan45(int s, int c){
#ifdef DEBUG
    assert(s >= 0);
    assert(c >= 0);
    assert(c >= s);
#endif
	if (c==0){
		#ifdef __DEBUG
		  __builtin_software_breakpoint();
		  /* If we are in debug mode, cause a software breakpoint in the debugger */
		#endif
	}
    int tan = (s << SDEC_BITS) / c;
    int index = tan >> (SDEC_BITS - 4);   //  tan = 0..1 -> index = 0..15
    if (index > 15) index = 15;
    int rest = (tan - (index << (SDEC_BITS - 4))) << 4;
    int theta = atanThetas[index] * (SDEC_ONE - rest) + atanThetas[index+1] * rest;
    theta = theta >> 14;
    return theta;
}

/** 
  @Function
    int atan2SDEC (int s, int c) 

  @Summary
 fixed point version of tangent^-1 

  @Remarks
 */
short atan2SDEC (short s, short c) 
{
    if (s >= 0){
        if (c >= 0){    //  1st quadrant
            if (s <= c) return atan45(s, c);
            else return ((1<<SDEC_BITS)/4) - atan45(c, s);
        }else{          //  2nd quadrant
            if (s <= -c) return ((1<<SDEC_BITS)/2) - atan45(s, -c);
            else return ((1<<SDEC_BITS)/4) + atan45(-c, s);
        }
    }else{
        if (c >= 0){    //  4th quadrant
            if (-s<=c) return -atan45(-s, c);
            else return -((1<<SDEC_BITS)/4 - atan45(c, -s));
        }else{          //  3rd quadrant
            if (-s<=-c) return -((1<<SDEC_BITS)/2) + atan45(-s, -c);
            else return -(((1<<SDEC_BITS)/4) + atan45(-c, -s));            
        }
    }
}

#ifdef MODULETEST
#include <stdio.h>
#include <math.h>

static int fint(float f){
    return (int)f;
}
static int fdec3(float f){
    return (f-(int)f) * 1000.0f;
}
static void atan2FixedTestPrint(int s, int c){
    short th = atan2SDEC(s, c);
    double sin = s;
    sin /= SDEC_ONE;
    double cos = c;
    cos /= SDEC_ONE;
    double theta = th;
    theta /= SDEC_ONE;
//    printf("s:%f  c:%f  theta:%f\n", sin, cos, theta);
    printf("%f\t%f\t%f\n", sin, cos, theta);
}
void atan2FixedTest(){
    short one = SDEC_ONE;
    printf("%d degree step:\n", 45);
    atan2FixedTestPrint(0, one);
    atan2FixedTestPrint(one, one);
    atan2FixedTestPrint(one, 0);
    atan2FixedTestPrint(one, -one);
    atan2FixedTestPrint(0, -one);
    atan2FixedTestPrint(-one, -one);
    atan2FixedTestPrint(-one, 0);
    atan2FixedTestPrint(-one, one);
    printf("\n%d degree step\n",5);
    double rad = 0;
    int i;
    for(i=0; i< 100; ++i){
        rad = M_PI*2*i/100;
        atan2FixedTestPrint( (short)(sin(rad) * one), (short)(cos(rad) * one));
    }
}
#endif
/* *****************************************************************************
 End of File
 */
