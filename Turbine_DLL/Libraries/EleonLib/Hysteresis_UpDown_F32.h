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
#ifndef FILE_HYSTERESISUPDOWNF32_H
#define FILE_HYSTERESISUPDOWNF32_H

#include <lib_main.h>


typedef struct Hyst_UpDown_F32* Hysteresis_UpDown_F32;


//*******************************************************************************************
// Hysteresis is applied to Output value either Input value is increasing or decreasing (going UP or DOWN).
// It means with increasing Input value, Output value is always lower than Input value by Hyst value.
// With decreasing Input value, Output value is always higher than Input value by Hyst value.
// Output value is set to Low_Limit value when Input <= Low_Limit.
// Output value is set to High_Limit value when Input >= High_Limit
//*******************************************************************************************

Hysteresis_UpDown_F32 HystUpDown_F32_New(F32/*hysteresis*/, F32/*low_Limit*/, F32/*high_Limit*/);		// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error
S32 HystUpDown_F32_Dispose(Hysteresis_UpDown_F32);															         // Free memory and dispose object
S32 HystUpDown_F32_LoadParameters(Hysteresis_UpDown_F32, F32/*hyst*/, F32/*low_Limit*/, F32/*high_Limit*/);	// Load parameters
S32 HystUpDown_F32_Reset(Hysteresis_UpDown_F32, F32/*output*/);												   // Reset output value
F32 HystUpDown_F32_Control(Hysteresis_UpDown_F32, F32/*input value*/);
S32 HystUpDown_F32_Set_Hysteresis(Hysteresis_UpDown_F32, F32/*hysteresis*/);								   // Set Hysteresis value
S32 HystUpDown_F32_Set_LowLimit(Hysteresis_UpDown_F32, F32/*low_Limit*/);									   // Set Low_Limit value
S32 HystUpDown_F32_Set_HighLimit(Hysteresis_UpDown_F32, F32/*high_Limit*/);									// Set High_Limit value

#endif
