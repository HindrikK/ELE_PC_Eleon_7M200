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
#ifndef FILE_PI_REGULATOR_3_H
#define FILE_PI_REGULATOR_3_H

#include <lib_main.h>


typedef struct PI_Reg_3* PI_Regulator_3;


//*******************************************************************************************
// Functions for PI controller with different P and I gain values for positive or
// negative error(Setpoint - Feedback).
// This PI function includes internal rate limiter for positive or negative error(Setpoint - Feedback).
// Positive or negative error means the same thing as if PI output is decreased or increased.
//
// This PI controller uses F32 type values. It does not have internal sampling time
// processing, so the time period with which the main function( PI_Control() ) is called,
// defines the calculation time step.
//*******************************************************************************************


PI_Regulator_3 PI_New_3(F32/*KpInc*/, F32/*KpDec*/, F32/*KiInc*/, F32/*KiDec*/, F32/*Min*/, F32/*Max*/, F32/*RateInc*/, F32/*RateDec*/, U32/*TimeBase*/, U32/*TimeStep*/);		// Creates new PI regulator with specified parameters. Returns pointer to the new PI structure. Returns NULL in case of error.
S32 PI_Dispose_3(PI_Regulator_3);											// Free memory and dispose the PI structure.
S32 PI_LoadParameters_3(PI_Regulator_3, F32/*KpInc*/, F32/*KpDec*/, F32/*KiInc*/, F32/*KiDec*/, F32/*Min*/, F32/*Max*/, F32/*RateInc*/, F32/*RateDec*/, U32/*TimeBase*/, U32/*TimeStep*/);		// Load PI regulator parameters.
S32 PI_Reset_3(PI_Regulator_3);												// Reset PI regulator process values.
F32 PI_Control_3(PI_Regulator_3, F32/*Setpoint*/, F32/*Feedback*/);			// Main control program for PI controller. Returns PI controller Output value.
S32 PI_Set_KpInc_3(PI_Regulator_3, F32/*Kp*/);								// Set Kp value for increasing PI regulator Output(error is negative).
S32 PI_Set_KpDec_3(PI_Regulator_3, F32/*Kp*/);								// Set Kp value for decreasing PI regulator Output(error is positive).
S32 PI_Set_KiInc_3(PI_Regulator_3, F32/*Kp*/);								// Set Ki value for increasing PI regulator Output(error is negative).
S32 PI_Set_KiDec_3(PI_Regulator_3, F32/*Kp*/);								// Set Ki value for decreasing PI regulator Output(error is positive).
S32 PI_Set_Min_3(PI_Regulator_3, F32/*Min*/);								// Set Min output value for PI regulator.
S32 PI_Set_Max_3(PI_Regulator_3, F32/*Max*/);								// Set Max output value for PI regulator.
S32 PI_Set_RateInc_3(PI_Regulator_3, F32/*RateInc*/);						// Set output RateInc value for PI regulator.
S32 PI_Set_RateDec_3(PI_Regulator_3, F32/*RateDec*/);						// Set output RateDec value for PI regulator.
S32 PI_Set_TimeBase_3(PI_Regulator_3, U32/*TimeBase*/);					// Set TimeBase value for rate limiter
S32 PI_Set_TimeStep_3(PI_Regulator_3, U32/*TimeStep*/);					// Set TimeStep value for rate limiter

F32 PI_Get_KpInc_3(PI_Regulator_3);											// Return KpInc value of PI regulator.
F32 PI_Get_KpDec_3(PI_Regulator_3);											// Return KpDec value of PI regulator.
F32 PI_Get_KiInc_3(PI_Regulator_3);											// Return KiInc value of PI regulator.
F32 PI_Get_KiDec_3(PI_Regulator_3);											// Return KiDec value of PI regulator.
F32 PI_Get_Min_3(PI_Regulator_3);											// Return Min value of PI regulator.
F32 PI_Get_Max_3(PI_Regulator_3);											// Return Max value of PI regulator.
F32 PI_Get_RateInc_3(PI_Regulator_3);										// Return RateInc value of PI regulator.
F32 PI_Get_RateDec_3(PI_Regulator_3);										// Return RateDec value of PI regulator.

#endif
