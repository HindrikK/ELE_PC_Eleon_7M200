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
#include <Hysteresis_UpDown_F32.h>


struct Hyst_UpDown_F32
{
	U8 Type;			   // This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	F32 Hysteresis;	// Parameter that defines hysteresis value
	F32 Low_Limit;		// Hysteresis is not used if input is LOWER or equal with this limit
	F32 High_Limit;	// Hysteresis is not used if input is HIGER or equal with this limit
	F32 Output;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL HystUpDown_F32_ValidateObject(Hysteresis_UpDown_F32 hyst)
{
   if(hyst->Type == 103) return true;
   else return false;
}


// Load parameters.
S32 HystUpDown_F32_LoadParameters(Hysteresis_UpDown_F32 hyst, F32 hysteresis, F32 low_Limit, F32 high_Limit)
{
	if (!HystUpDown_F32_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	hyst->Low_Limit = low_Limit;
	hyst->High_Limit = high_Limit;
	return 0;
}


// Reset output value.
S32 HystUpDown_F32_Reset(Hysteresis_UpDown_F32 hyst, F32 output)
{
	if (!HystUpDown_F32_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Output = output;
	return 0;
}


// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error.
Hysteresis_UpDown_F32 HystUpDown_F32_New(F32 hysteresis, F32 low_Limit, F32 high_Limit)
{
	void* hyst;

	int result = OS_Allocate_Memory(GetMemPool(), &hyst, sizeof(struct Hyst_UpDown_F32), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((Hysteresis_UpDown_F32)hyst)->Type = 103;
	HystUpDown_F32_LoadParameters((Hysteresis_UpDown_F32)hyst, hysteresis, low_Limit, high_Limit);
	HystUpDown_F32_Reset((Hysteresis_UpDown_F32)hyst, 0);
	
	return (Hysteresis_UpDown_F32)hyst;
}


// Free memory and dispose the structure.
S32 HystUpDown_F32_Dispose(Hysteresis_UpDown_F32 hyst)
{
	if (!HystUpDown_F32_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	int result = OS_Deallocate_Memory(hyst);
	if (result != OS_SUCCESS) { return result; }
	else { return 0; }
}


F32 HystUpDown_F32_Control(Hysteresis_UpDown_F32 hyst, F32 Input)
{
	if (!HystUpDown_F32_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	
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
S32 HystUpDown_F32_Set_Hysteresis(Hysteresis_UpDown_F32 hyst, F32 hysteresis)
{
	if (!HystUpDown_F32_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	return 0;
}


// Set Low_Limit value
S32 HystUpDown_F32_Set_LowLimit(Hysteresis_UpDown_F32 hyst, F32 low_Limit)
{
	if (!HystUpDown_F32_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Low_Limit = low_Limit;
	return 0;
}


// Set High_Limit value
S32 HystUpDown_F32_Set_HighLimit(Hysteresis_UpDown_F32 hyst, F32 high_Limit)
{
	if (!HystUpDown_F32_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->High_Limit = high_Limit;
	return 0;
}
