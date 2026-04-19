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
#ifndef FILE_HYSTERESISDOWN_H
#define FILE_HYSTERESISDOWN_H

#include <lib_main.h>


typedef struct Hyst_Down* Hysteresis_Down;


//*******************************************************************************************
// Hysteresis is applied to Output value when Input value is increasing(going DOWN).
// It means with decreasing Input value, Output value is always higher than Input value by Hyst value.
// With increasing Input value, Output value always equals Input value.
// Output value is set to Low_Limit value when Input <= Low_Limit.
// Output value is set to High_Limit value when Input >= High_Limit
//*******************************************************************************************

Hysteresis_Down HystDown_New(S32/*hysteresis*/, S32/*low_Limit*/, S32/*high_Limit*/);				// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error
S32 HystDown_Dispose(Hysteresis_Down);																// Free memory and dispose object
S32 HystDown_LoadParameters(Hysteresis_Down, S32/*hyst*/, S32/*low_Limit*/, S32/*high_Limit*/);	// Load parameters
S32 HystDown_Reset(Hysteresis_Down, S32/*output*/);												// Reset output value
S32 HystDown_Control(Hysteresis_Down, S32/*input value*/);
S32 HystDown_Set_Hysteresis(Hysteresis_Down, S32/*hysteresis*/);									// Set Hysteresis value
S32 HystDown_Set_LowLimit(Hysteresis_Down, S32/*low_Limit*/);										// Set Low_Limit value
S32 HystDown_Set_HighLimit(Hysteresis_Down, S32/*high_Limit*/);									// Set High_Limit value

#endif
