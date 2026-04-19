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
#ifndef FILE_HYSTERESIS_V2_H
#define FILE_HYSTERESIS_V2_H

#include <lib_main.h>


typedef struct Hyst_v2* Hysteresis_v2;


//*******************************************************************************************
// Hysteresis is applied to Output value either Input value is increasing or decreasing (going UP or DOWN).
// It means with increasing Input value, Output value is lower than Input value by Hyst value.
// With decreasing Input value, Output value is higher than Input value by Hyst value.
// Output value is set to Low_Limit value when Input <= Low_Limit.
// Output value is set to High_Limit value when Input >= High_Limit
// Mid value is calculated over a period of mid_period[ms]; Mid value equals (max - min) / 2
// Output is always trying to reach Mid value during the delay set by mid_delay; eg. when
// Input(Min and Max) remains unchanged then Output will reach Input in mid_delay from
// full hysteresis.
//*******************************************************************************************

Hysteresis_v2 Hyst_v2_New(F32/*hysteresis*/, F32/*low_Limit*/, F32/*high_Limit*/, U16/*mid_period*/, U16/*mid_delay*/, U32/*timeStep*/);		// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error
S32 Hyst_v2_LoadParameters(Hysteresis_v2, F32/*hyst*/, F32/*low_Limit*/, F32/*high_Limit*/, U16/*mid_delay*/);	// Load parameters
S32 Hyst_v2_Reset(Hysteresis_v2, F32/*output*/);												   // Reset output value
F32 Hyst_v2_Control(Hysteresis_v2, F32/*input value*/);
S32 Hyst_v2_Set_Hysteresis(Hysteresis_v2, F32/*hysteresis*/);								   // Set Hysteresis value
S32 Hyst_v2_Set_LowLimit(Hysteresis_v2, F32/*low_Limit*/);									   // Set Low_Limit value
S32 Hyst_v2_Set_HighLimit(Hysteresis_v2, F32/*high_Limit*/);									// Set High_Limit value
S32 Hyst_v2_Set_MidDelay(Hysteresis_v2, U16/*mid_Delay*/);

#endif
