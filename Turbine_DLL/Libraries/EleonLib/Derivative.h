//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_DERIVATIVE__H
#define FILE_DERIVATIVE__H

#include <lib_main.h>


typedef struct Deriv* Derivative;


//*******************************************************************************************
// Function calculates derivate over specified TimeBase
//*******************************************************************************************
// D_period - specifies the time period over which to calculate derivate D in number of TimeStep (1-20); e.g. 5 = 5 x 20(TimeStep) = 100 ms
// TimeBase - time base in [ms] for derivate/rate calculation; "TimeBase" should be multiple of "TimeStep" or rate limiter will not give exactly correct rate; "TimeBase" must be greater than "TimeStep"
// TimeStep - function calling time step(scantime) in [ms]
//*******************************************************************************************


Derivative Derivative_New(U16 /*D_period*/, U32/*TimeBase*/, U32/*TimeStep*/, F32/*InitValue*/);
S32 Derivative_Dispose(Derivative);																	// Free memory and dispose the Derivative structure
S32 Derivative_LoadParameters(Derivative, U16 /*D_period*/, U32/*TimeBase*/, U32/*TimeStep*/);		// Load parameters
S32 Derivative_Reset(Derivative, F32/*InitValue*/);
F32 Derivative_Control(Derivative, F32/*Value*/);                 									// Main control program for Derivative, returns derivate/change rate value
S32 Derivative_Set_TimeBase(Derivative, U32/*TimeBase*/);
S32 Derivative_Set_TimeStep(Derivative, U32/*TimeStep*/);

#endif
