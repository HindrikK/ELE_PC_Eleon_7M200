//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************


//***********************************************************************
#include <Hysteresis_Up.h>


struct Hyst_Up
{
	U8 Type;			// This variable is initialized during _New() function and indicates if correct structure(object) is created
	S32 Hysteresis;		// Parameter that defines hysteresis value
	S32 Low_Limit;		// Hysteresis is not used if input is LOWER or equal with this limit
	S32 High_Limit;		// Hysteresis is not used if input is HIGER or equal with this limit
	S32 Output;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL HystUp_ValidateObject(Hysteresis_Up hyst)
{
   if(hyst->Type == 101) return true;
   else return false;
}


// Load parameters.
S32 HystUp_LoadParameters(Hysteresis_Up hyst, S32 hysteresis, S32 low_Limit, S32 high_Limit)
{
	if (!HystUp_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	hyst->Low_Limit = low_Limit;
	hyst->High_Limit = high_Limit;
	return 0;
}


// Reset output value.
S32 HystUp_Reset(Hysteresis_Up hyst, S32 output)
{
	if (!HystUp_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Output = output;
	return 0;
}


// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error.
Hysteresis_Up HystUp_New(S32 hysteresis, S32 low_Limit, S32 high_Limit)
{
	void* hyst;

	int result = OS_Allocate_Memory(GetMemPool(), &hyst, sizeof(struct Hyst_Up), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((Hysteresis_Up)hyst)->Type = 101;
	HystUp_LoadParameters((Hysteresis_Up)hyst, hysteresis, low_Limit, high_Limit);
	HystUp_Reset((Hysteresis_Up)hyst, 0);

	return (Hysteresis_Up)hyst;
}


// Free memory and dispose the structure.
S32 HystUp_Dispose(Hysteresis_Up hyst)
{
	if (!HystUp_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	int result = OS_Deallocate_Memory(hyst);
	if (result != OS_SUCCESS) { return result; }
	else { return 0; }
}


S32 HystUp_Control(Hysteresis_Up hyst, S32 Input)
{
	if (!HystUp_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure

	if (Input > hyst->Output && Input >= hyst->High_Limit)
	{
		hyst->Output = Input;
	}
	else if (Input < hyst->Output && Input <= hyst->Low_Limit)
	{
		hyst->Output = Input;
	}
	else if (Input > (hyst->Output + hyst->Hysteresis))
	{
		hyst->Output = Input - hyst->Hysteresis;
	}
	else if (Input < hyst->Output)
	{
		hyst->Output = Input;
	}

	return hyst->Output;
}


// Set Hysteresis value
S32 HystUp_Set_Hysteresis(Hysteresis_Up hyst, S32 hysteresis)
{
	if (!HystUp_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	return 0;
}


// Set Low_Limit value
S32 HystUp_Set_LowLimit(Hysteresis_Up hyst, S32 low_Limit)
{
	if (!HystUp_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Low_Limit = low_Limit;
	return 0;
}


// Set High_Limit value
S32 HystUp_Set_HighLimit(Hysteresis_Up hyst, S32 high_Limit)
{
	if (!HystUp_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->High_Limit = high_Limit;
	return 0;
}
