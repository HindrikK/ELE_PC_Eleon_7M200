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
#include <Hysteresis_UpDown.h>


struct Hyst_UpDown
{
	U8 Type;			// This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	S32 Hysteresis;		// Parameter that defines hysteresis value
	S32 Low_Limit;		// Hysteresis is not used if input is LOWER or equal with this limit
	S32 High_Limit;		// Hysteresis is not used if input is HIGER or equal with this limit
	S32 Output;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL HystUpDown_ValidateObject(Hysteresis_UpDown hyst)
{
   if(hyst->Type == 100) return true;
   else return false;
}


// Load parameters.
S32 HystUpDown_LoadParameters(Hysteresis_UpDown hyst, S32 hysteresis, S32 low_Limit, S32 high_Limit)
{
	if (!HystUpDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	hyst->Low_Limit = low_Limit;
	hyst->High_Limit = high_Limit;
	return 0;
}


// Reset output value.
S32 HystUpDown_Reset(Hysteresis_UpDown hyst, S32 output)
{
	if (!HystUpDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Output = output;
	return 0;
}


// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error.
Hysteresis_UpDown HystUpDown_New(S32 hysteresis, S32 low_Limit, S32 high_Limit)
{
	void* hyst;

	int result = OS_Allocate_Memory(GetMemPool(), &hyst, sizeof(struct Hyst_UpDown), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((Hysteresis_UpDown)hyst)->Type = 100;
	HystUpDown_LoadParameters((Hysteresis_UpDown)hyst, hysteresis, low_Limit, high_Limit);
	HystUpDown_Reset((Hysteresis_UpDown)hyst, 0);
	
	return (Hysteresis_UpDown)hyst;
}


// Free memory and dispose the structure.
S32 HystUpDown_Dispose(Hysteresis_UpDown hyst)
{
	if (!HystUpDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	int result = OS_Deallocate_Memory(hyst);
	if (result != OS_SUCCESS) { return result; }
	else { return 0; }
}


S32 HystUpDown_Control(Hysteresis_UpDown hyst, S32 Input)
{
	if (!HystUpDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	
	if (Input > hyst->Output && Input >= hyst->High_Limit)
	{
		hyst->Output = Input;
	}
	else if (Input < hyst->Output && Input <= hyst->Low_Limit)
	{
		hyst->Output = Input;
	}
	else if (Input >(hyst->Output + hyst->Hysteresis))
	{
		hyst->Output = Input - hyst->Hysteresis;
	}
	else if (Input < (hyst->Output - hyst->Hysteresis))
	{
		hyst->Output = Input + hyst->Hysteresis;
	}

	return hyst->Output;
}


// Set Hysteresis value
S32 HystUpDown_Set_Hysteresis(Hysteresis_UpDown hyst, S32 hysteresis)
{
	if (!HystUpDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	return 0;
}


// Set Low_Limit value
S32 HystUpDown_Set_LowLimit(Hysteresis_UpDown hyst, S32 low_Limit)
{
	if (!HystUpDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Low_Limit = low_Limit;
	return 0;
}


// Set High_Limit value
S32 HystUpDown_Set_HighLimit(Hysteresis_UpDown hyst, S32 high_Limit)
{
	if (!HystUpDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->High_Limit = high_Limit;
	return 0;
}
