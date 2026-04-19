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
#ifndef FILE_RATE_LIMITER_H
#define FILE_RATE_LIMITER_H

#include <lib_main.h>


typedef struct Rate_Lim* Rate_Limiter;


//*******************************************************************************************
// Limits the rate of change of value.
// 
// RateUp - maximum increase of output value per "TimeBase" time
// RateDown - maximum decrease of output value per "TimeBase" time
// TimeBase - time value in [ms] that specifies base time for "RateUp" and "RateDown" values
// TimeStep - time value in [ms] that specifies often the function(RateLim_Control) is called; this functions has to be called always with this rate
//
// "TimeBase" should be multiple of "TimeStep" or rate limiter will not give exactly correct rate; "TimeBase" MUST be greater than "TimeStep"
//
//*******************************************************************************************

Rate_Limiter RateLim_New(S32/*RateUp*/, S32/*RateDown*/, U32/*TimeBase*/, U32/*TimeStep*/);						// Creates new Rate_Limiter with specified parameters. Returns pointer to the new Rate_Limiter structure. Returns NULL in case of error.
S32 RateLim_Dispose(Rate_Limiter);																				// Free memory and dispose the structure.
S32 RateLim_LoadParameters(Rate_Limiter, S32/*RateUp*/, S32/*RateDown*/, U32/*TimeBase*/, U32/*TimeStep*/);		// Load parameters.
S32 RateLim_Reset(Rate_Limiter, S32/*Output*/);																	// Reset output value.
S32 RateLim_Control(Rate_Limiter, S32/*Input*/);																// Main control program for Rate Limiter. Returns Output value.
S32 RateLim_Set_RateUp(Rate_Limiter, S32/*RateUp*/);															// Set RateUp value
S32 RateLim_Set_RateDown(Rate_Limiter, S32/*RateDown*/);														// Set RateDown value
S32 RateLim_Set_TimeBase(Rate_Limiter, U32/*TimeBase*/);														// Set TimeBase value
S32 RateLim_Set_TimeStep(Rate_Limiter, U32/*TimeStep*/);														// Set TimeStep value

#endif
