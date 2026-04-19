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
#ifndef FILE_HYSTERESISUPDOWN_H
#define FILE_HYSTERESISUPDOWN_H

#include <lib_main.h>


typedef struct Hyst_UpDown* Hysteresis_UpDown;


//*******************************************************************************************
// Hysteresis is applied to Output value either Input value is increasing or decreasing (going UP or DOWN).
// It means with increasing Input value, Output value is always lower than Input value by Hyst value.
// With decreasing Input value, Output value is always higher than Input value by Hyst value.
// Output value is set to Low_Limit value when Input <= Low_Limit.
// Output value is set to High_Limit value when Input >= High_Limit
//*******************************************************************************************

Hysteresis_UpDown HystUpDown_New(S32/*hysteresis*/, S32/*low_Limit*/, S32/*high_Limit*/);			// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error
S32 HystUpDown_Dispose(Hysteresis_UpDown);															// Free memory and dispose object
S32 HystUpDown_LoadParameters(Hysteresis_UpDown, S32/*hyst*/, S32/*low_Limit*/, S32/*high_Limit*/);	// Load parameters
S32 HystUpDown_Reset(Hysteresis_UpDown, S32/*output*/);												// Reset output value
S32 HystUpDown_Control(Hysteresis_UpDown, S32/*input value*/);
S32 HystUpDown_Set_Hysteresis(Hysteresis_UpDown, S32/*hysteresis*/);								// Set Hysteresis value
S32 HystUpDown_Set_LowLimit(Hysteresis_UpDown, S32/*low_Limit*/);									// Set Low_Limit value
S32 HystUpDown_Set_HighLimit(Hysteresis_UpDown, S32/*high_Limit*/);									// Set High_Limit value

#endif
