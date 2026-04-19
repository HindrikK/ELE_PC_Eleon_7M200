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
#ifndef FILE_ACCELERATIONLIMITER__H
#define FILE_ACCELERATIONLIMITER__H

#include <lib_main.h>


typedef struct AccLim* Acceleration_Limiter;


//*******************************************************************************************
// Function calculates derivate over specified TimeBase
// Limits the rate of change speed change of value. dv/dt
// 
// Accel - maximum acceleration of output value change speed in one second; positive value
// Decel - maximum deceleration of output value change speed in one second; positive value
// TimeBase - time value in [ms] that specifies base time for "Accel" and "Decel" values
// TimeStep - time value in [ms] that specifies often the control function is called; this functions has to be called always with this rate
//
// "TimeBase" should be multiple of "TimeStep" or limiter will not give exactly correct rate; "TimeBase" MUST be greater than "TimeStep"
//
//*******************************************************************************************

Acceleration_Limiter AccLim_New(F32/*accel*/, F32/*decel*/, U32/*timeBase*/, U32/*timeStep*/);
S32 AccLim_Dispose(Acceleration_Limiter);																	               // Free memory and dispose the Acceleration_Limiter structure
S32 AccLim_LoadParameters(Acceleration_Limiter/*accLim*/, F32/*accel*/, F32/*decel*/);		               // Load parameters
S32 AccLim_Reset(Acceleration_Limiter, F32/*InitValue*/);
F32 AccLim_Control(Acceleration_Limiter, F32/*Value*/);                 									      // Main control program for Acceleration_Limiter, returns limiter value

#endif
