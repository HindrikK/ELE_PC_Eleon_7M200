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
#ifndef FILE_PI_REGULATOR_2_H
#define FILE_PI_REGULATOR_2_H

#include <lib_main.h>


typedef struct PI_Reg_2* PI_Regulator_2;


//*******************************************************************************************
// Functions for PI controller with different P and I gain values for positive or
// negative error(Setpoint - Feedback).
// Positive or negative error means the same thing as if PI output is decreased or increased.
//
// This PI controller uses F32 type values. It does not have internal sampling time
// processing, so the time period with which the main function( PI_Control() ) is called,
// defines the calculation time step.
//*******************************************************************************************

//*******************************************************************************************
//	HELP
//		Output - Output = Kp_effect + Ki_effect;
//		Feedback - error input for PI controller; PI controller adjusts Output value
//				   as long as error != 0.
//		Kp - calculates Kp_effect value per one error(Setpoint - Feedback) unit
//		Ki - calculates how much to increase or decrease Ki_effect value per one error(Setpoint - Feedback) unit.
//			 Integrating step time is defined by function call time.
//
//	EXAMPLE 1: Ki_effect_prev = 20; Kp = 100; Ki = 4
//		If error((Setpoint - Feedback)) = 3, then
//		Output = (error x Kp) + (Ki_effect_prev + (error x Ki)) = (3 x 100) + (20 + (3 x 4)) = 300 + 32 = 332
//
//	EXAMPLE 2: Ki_effect_prev = 20; Kp = -10; Ki = -5
//		If error((Setpoint - Feedback)) = 3, then
//		Output = (error x Kp) + (Ki_effect_prev + (error x Ki)) = (3 x -10) + (20 + (3 x -5)) = -30 + 5 = -25
//*******************************************************************************************


PI_Regulator_2 PI_New_2(F32/*KpInc*/, F32/*KpDec*/, F32/*KiInc*/, F32/*KiDec*/, F32/*Min*/, F32/*Max*/);		// Creates new PI regulator with specified parameters. Returns pointer to the new PI structure. Returns NULL in case of error.
S32 PI_Dispose_2(PI_Regulator_2);											// Free memory and dispose the PI structure.
S32 PI_LoadParameters_2(PI_Regulator_2, F32/*KpInc*/, F32/*KpDec*/, F32/*KiInc*/, F32/*KiDec*/, F32/*Min*/, F32/*Max*/);		// Load PI regulator parameters.
S32 PI_Reset_2(PI_Regulator_2);											// Reset PI regulator process values.
F32 PI_Control_2(PI_Regulator_2, F32/*Setpoint*/, F32/*Feedback*/);			// Main control program for PI controller. Returns PI controller Output value.
S32 PI_Set_KpInc_2(PI_Regulator_2, F32/*Kp*/);								// Set Kp value for increasing PI regulator Output(feedback smaller than setpoint).
S32 PI_Set_KpDec_2(PI_Regulator_2, F32/*Kp*/);								// Set Kp value for decreasing PI regulator Output(feedback greater than setpoint).
S32 PI_Set_KiInc_2(PI_Regulator_2, F32/*Kp*/);								// Set Ki value for increasing PI regulator Output(feedback smaller than setpoint).
S32 PI_Set_KiDec_2(PI_Regulator_2, F32/*Kp*/);								// Set Ki value for decreasing PI regulator Output(feedback greater than setpoint).
S32 PI_Set_Min_2(PI_Regulator_2, F32/*Min*/);								// Set Min output value for PI regulator.
S32 PI_Set_Max_2(PI_Regulator_2, F32/*Max*/);								// Set Max output value for PI regulator.

F32 PI_Get_KpInc_2(PI_Regulator_2);											// Return KpInc value of PI regulator.
F32 PI_Get_KpDec_2(PI_Regulator_2);											// Return KpDec value of PI regulator.
F32 PI_Get_KiInc_2(PI_Regulator_2);											// Return KiInc value of PI regulator.
F32 PI_Get_KiDec_2(PI_Regulator_2);											// Return KiDec value of PI regulator.
F32 PI_Get_Min_2(PI_Regulator_2);											// Return Min value of PI regulator.
F32 PI_Get_Max_2(PI_Regulator_2);											// Return Max value of PI regulator.

#endif
