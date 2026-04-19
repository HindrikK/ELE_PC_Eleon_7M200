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
#include <Hysteresis_Down.h>


struct Hyst_Down
{
	U8 Type;			// This variable is initialized during _New() function and indicates if correct structure(object) is created
	S32 Hysteresis;		// Parameter that defines hysteresis value
	S32 Low_Limit;		// Hysteresis is not used if input is LOWER or equal with this limit
	S32 High_Limit;		// Hysteresis is not used if input is HIGER or equal with this limit
	S32 Output;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL HystDown_ValidateObject(Hysteresis_Down hyst)
{
   if(hyst->Type == 102) return true;
   else return false;
}


// Load parameters.
S32 HystDown_LoadParameters(Hysteresis_Down hyst, S32 hysteresis, S32 low_Limit, S32 high_Limit)
{
	if (!HystDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	hyst->Low_Limit = low_Limit;
	hyst->High_Limit = high_Limit;
	return 0;
}


// Reset output value.
S32 HystDown_Reset(Hysteresis_Down hyst, S32 output)
{
	if (!HystDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Output = output;
	return 0;
}


// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error.
Hysteresis_Down HystDown_New(S32 hysteresis, S32 low_Limit, S32 high_Limit)
{
	void* hyst;

	int result = OS_Allocate_Memory(GetMemPool(), &hyst, sizeof(struct Hyst_Down), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((Hysteresis_Down)hyst)->Type = 102;
	HystDown_LoadParameters((Hysteresis_Down)hyst, hysteresis, low_Limit, high_Limit);
	HystDown_Reset((Hysteresis_Down)hyst, 0);

	return (Hysteresis_Down)hyst;
}


// Free memory and dispose the structure.
S32 HystDown_Dispose(Hysteresis_Down hyst)
{
	if (!HystDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	int result = OS_Deallocate_Memory(hyst);
	if (result != OS_SUCCESS) { return result; }
	else { return 0; }
}


S32 HystDown_Control(Hysteresis_Down hyst, S32 Input)
{
	if (Input > hyst->Output && Input >= hyst->High_Limit)
	{
		hyst->Output = Input;
	}
	else if (Input < hyst->Output && Input <= hyst->Low_Limit)
	{
		hyst->Output = Input;
	}
	else if (Input > hyst->Output)
	{
		hyst->Output = Input;
	}
	else if (Input < (hyst->Output - hyst->Hysteresis))
	{
		hyst->Output = Input + hyst->Hysteresis;
	}

	return hyst->Output;
}


// Set Hysteresis value
S32 HystDown_Set_Hysteresis(Hysteresis_Down hyst, S32 hysteresis)
{
	if (!HystDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	return 0;
}


// Set Low_Limit value
S32 HystDown_Set_LowLimit(Hysteresis_Down hyst, S32 low_Limit)
{
	if (!HystDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Low_Limit = low_Limit;
	return 0;
}


// Set High_Limit value
S32 HystDown_Set_HighLimit(Hysteresis_Down hyst, S32 high_Limit)
{
	if (!HystDown_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->High_Limit = high_Limit;
	return 0;
}
