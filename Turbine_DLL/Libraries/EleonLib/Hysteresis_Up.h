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
#ifndef FILE_HYSTERESISUP_H
#define FILE_HYSTERESISUP_H

#include <lib_main.h>


typedef struct Hyst_Up* Hysteresis_Up;


//*******************************************************************************************
// Hysteresis is applied to Output value when Input value is increasing(going UP).
// It means with increasing Input value, Output value is always lower than Input value by Hyst value.
// With decreasing Input value, Output value always equals Input value.
// Output value is set to Low_Limit value when Input <= Low_Limit.
// Output value is set to High_Limit value when Input >= High_Limit
//*******************************************************************************************

Hysteresis_Up HystUp_New(S32/*hysteresis*/, S32/*low_Limit*/, S32/*high_Limit*/);			// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error
S32 HystUp_Dispose(Hysteresis_Up);															// Free memory and dispose object
S32 HystUp_LoadParameters(Hysteresis_Up, S32/*hyst*/, S32/*low_Limit*/, S32/*high_Limit*/);	// Load parameters
S32 HystUp_Reset(Hysteresis_Up, S32/*output*/);												// Reset output value
S32 HystUp_Control(Hysteresis_Up, S32/*input value*/);
S32 HystUp_Set_Hysteresis(Hysteresis_Up, S32/*hysteresis*/);								// Set Hysteresis value
S32 HystUp_Set_LowLimit(Hysteresis_Up, S32/*low_Limit*/);									// Set Low_Limit value
S32 HystUp_Set_HighLimit(Hysteresis_Up, S32/*high_Limit*/);									// Set High_Limit value

#endif
