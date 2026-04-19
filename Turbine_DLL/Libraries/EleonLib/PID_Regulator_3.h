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
#ifndef FILE_PID_REGULATOR_3__H
#define FILE_PID_REGULATOR_3__H

#include <lib_main.h>


typedef struct PID_Reg_3* PID_Regulator_3;


//*******************************************************************************************
// Functions for PID controller with different P, I and D gain values for positive or
// negative error(Setpoint - Feedback).
// This PID function includes internal rate limiter for positive or negative error(Setpoint - Feedback).
// Positive or negative error means the same thing as if PID output is decreased or increased.
//
// This PID controller uses F32 type values. It does not have internal sampling time
// processing, so the time period with which the main function( PID_Control_3() ) is called,
// defines the calculation time step.
// Integration and derivate time periods have to be set by parameters.
// Gain values can be adjusted by adjust parameters. adjust values <1.0 reduce gain and
// values >1.0 increase gain
//*******************************************************************************************


PID_Regulator_3 PID_New_3(F32/*KpInc*/, F32/*KpDec*/, F32/*KiInc*/, F32/*KiDec*/, F32/*KdInc*/, F32/*KdDec*/, U16 /*D_period*/, F32/*Min*/, F32/*Max*/, F32/*RateInc*/, F32/*RateDec*/, U32/*TimeBase*/, U32/*TimeStep*/);		// Creates new PID regulator with specified parameters. Returns pointer to the new PID structure. Returns NULL in case of error.
S32 PID_Dispose_3(PID_Regulator_3);											   // Free memory and dispose the PID structure.
S32 PID_LoadParameters_3(PID_Regulator_3, F32/*KpInc*/, F32/*KpDec*/, F32/*KiInc*/, F32/*KiDec*/, F32/*KdInc*/, F32/*KdDec*/, F32/*Min*/, F32/*Max*/, F32/*RateInc*/, F32/*RateDec*/, U32/*TimeBase*/, U32/*TimeStep*/);		// Load PI regulator parameters.
S32 PID_Reset_3(PID_Regulator_3);							               // Reset PID regulator process values
S32 PID_Preset_3(PID_Regulator_3, F32/*Setpoint*/, F32/*Feedback*/, F32/*Output*/);			// Preset PID regulator process values
F32 PID_Control_3(PID_Regulator_3, F32/*Setpoint*/, F32/*Feedback*/);		// Main control program for PID controller. Returns PID controller Output value.
S32 PID_Set_KpInc_3(PID_Regulator_3, F32/*Kp*/);							// Set Kp value for increasing PID regulator Output(error is negative).
S32 PID_Set_KpDec_3(PID_Regulator_3, F32/*Kp*/);							// Set Kp value for decreasing PID regulator Output(error is positive).
S32 PID_Set_KiInc_3(PID_Regulator_3, F32/*Ki*/);							// Set Ki value for increasing PID regulator Output(error is negative).
S32 PID_Set_KiDec_3(PID_Regulator_3, F32/*Ki*/);							// Set Ki value for decreasing PID regulator Output(error is positive).
S32 PID_Set_KdInc_3(PID_Regulator_3, F32/*Kd*/);							// Set Kd value for increasing PID regulator Output(error is negative).
S32 PID_Set_KdDec_3(PID_Regulator_3, F32/*Kd*/);							// Set Kd value for decreasing PID regulator Output(error is positive).
S32 PID_Set_D_period_3(PID_Regulator_3, U16/*D_period*/);				// Set time period over which to calculate derivate D in number of TimeStep (1-20); e.g. 5 = 5 x 20(TimeStep) = 100 ms
S32 PID_Set_IsaturLimMin_3(PID_Regulator_3, F32/*I_saturLim*/);		// Set I saturation limit
S32 PID_Set_IsaturLimMax_3(PID_Regulator_3, F32/*I_saturLim*/);		// Set I saturation limit
S32 PID_Set_Min_3(PID_Regulator_3, F32/*Min*/);								// Set Min output value for PID regulator
S32 PID_Set_Max_3(PID_Regulator_3, F32/*Max*/);								// Set Max output value for PID regulator
S32 PID_Set_RateInc_3(PID_Regulator_3, F32/*RateInc*/);					// Set output RateInc value for PID regulator
S32 PID_Set_RateDec_3(PID_Regulator_3, F32/*RateDec*/);					// Set output RateDec value for PID regulator
S32 PID_Set_TimeBase_3(PID_Regulator_3, U32/*TimeBase*/);				// Set TimeBase value for PID regulator
S32 PID_Set_TimeStep_3(PID_Regulator_3, U32/*TimeStep*/);				// Set TimeStep value for PID regulator
S32 PID_Set_Adjust_3(PID_Regulator_3, F32/*kpAdj*/, F32/*kiAdj*/, F32/*kdAdj*/);        // Adjust gain values

F32 PID_Get_P_3(PID_Regulator_3);											// Return P value of PID regulator
F32 PID_Get_I_3(PID_Regulator_3);											// Return I value of PID regulator
F32 PID_Get_D_3(PID_Regulator_3);											// Return D value of PID regulator
F32 PID_Get_KpInc_3(PID_Regulator_3);										// Return KpInc value of PID regulator
F32 PID_Get_KpDec_3(PID_Regulator_3);										// Return KpDec value of PID regulator
F32 PID_Get_KiInc_3(PID_Regulator_3);										// Return KiInc value of PID regulator
F32 PID_Get_KiDec_3(PID_Regulator_3);										// Return KiDec value of PID regulator
F32 PID_Get_KdInc_3(PID_Regulator_3);										// Return KdInc value of PID regulator
F32 PID_Get_KdDec_3(PID_Regulator_3);										// Return KdDec value of PID regulator
U16 PID_Get_D_period_3(PID_Regulator_3);									// Return D_period.
F32 PID_Get_IsaturLimMin_3(PID_Regulator_3);								// Return I saturation limit value
F32 PID_Get_IsaturLimMax_3(PID_Regulator_3);								// Return I saturation limit value
F32 PID_Get_Min_3(PID_Regulator_3);											// Return Min value of PID regulator
F32 PID_Get_Max_3(PID_Regulator_3);											// Return Max value of PID regulator
F32 PID_Get_RateInc_3(PID_Regulator_3);									// Return RateInc value of PID regulator
F32 PID_Get_RateDec_3(PID_Regulator_3);									// Return RateDec value of PID regulator

#endif