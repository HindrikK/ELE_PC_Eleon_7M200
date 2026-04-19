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
#include <PI_Regulator.h>


struct PI_Reg
{
	U8 Type;			// This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	
	//Inputs
	F32 Kp;			// P - gain
	F32 Ki;			// I - gain
	F32 Min;		// Min output value limit
	F32 Max;		// Max output value limit

	//Outputs
	F32 Output;		// Corrected process value. Equals P + I

	//Internal
	F32 P_value;
	F32 I_value;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL PI_ValidateObject(PI_Regulator pi_reg)
{
   if(pi_reg->Type == 110) return true;
   else return false;
}


// Load PI regulator parameters.
S32 PI_LoadParameters(PI_Regulator pi_reg, F32 kp, F32 ki, F32 min, F32 max)
{
	if (!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->Kp = kp;
   pi_reg->Ki = ki;
   pi_reg->Min = min;
   pi_reg->Max = max;
   return 0;
}


// Reset PI regulator process values.
S32 PI_Reset(PI_Regulator pi_reg)
{
	if (!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->Output = 0;
   pi_reg->P_value = 0;
   pi_reg->I_value = 0;
   return 0;
}


// Creates new PI regulator with specified parameters. Returns pointer to the new PI structure. Returns NULL in case of error.
PI_Regulator PI_New(F32 kp, F32 ki, F32 min, F32 max)
{
	void *pi_reg;

	int result = OS_Allocate_Memory(GetMemPool(), &pi_reg, sizeof(struct PI_Reg), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) return NULL;


	((PI_Regulator)pi_reg)->Type = 110;
	PI_LoadParameters((PI_Regulator)pi_reg, kp, ki, min, max);
	PI_Reset(pi_reg);

	return (PI_Regulator)pi_reg;
}


// Free memory and dispose the PI structure.
S32 PI_Dispose(PI_Regulator pi_reg)
{
	if (!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
	int result = OS_Deallocate_Memory(pi_reg);
	if (result != OS_SUCCESS) return result;
	else return 0;
}


// Main control program for PI controller. Returns PI controller Output value.
F32 PI_Control(PI_Regulator pi_reg, F32 Setpoint, F32 Feedback)
{
	if (!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
	
	F32 _Output = pi_reg->Output;
	F32 _P_value = pi_reg->P_value;
	F32 _I_value = pi_reg->I_value;
	
	F32 Error = Setpoint - Feedback;


	// calculate new values
	_P_value = pi_reg->Kp * Error;
	_I_value = _I_value + (pi_reg->Ki * Error);
	_Output = _P_value + _I_value;

	// apply new values only if output fits into limits
	if (_Output >= pi_reg->Min && _Output <= pi_reg->Max)
	{
		pi_reg->Output = _Output;
		pi_reg->P_value = _P_value;
		pi_reg->I_value = _I_value;
	}
	else if (_Output < pi_reg->Min) pi_reg->Output = pi_reg->Min;
	else if (_Output > pi_reg->Max) pi_reg->Output = pi_reg->Max;

	return pi_reg->Output;
}


// Set Kp value for PI regulator.
S32 PI_Set_Kp(PI_Regulator pi_reg, F32 kp)
{
	if (!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->Kp = kp;
	return 0;
}


// Set Ki value for PI regulator.
S32 PI_Set_Ki(PI_Regulator pi_reg, F32 ki)
{
	if(!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->Ki = ki;
	return 0;
}


// Set Min output value for PI regulator.
S32 PI_Set_Min(PI_Regulator pi_reg, F32 min)
{
	if (!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->Min = min;
	return 0;
}


// Set Max output value for PI regulator.
S32 PI_Set_Max(PI_Regulator pi_reg, F32 max)
{
	if (!PI_ValidateObject(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->Max = max;
	return 0;
}
