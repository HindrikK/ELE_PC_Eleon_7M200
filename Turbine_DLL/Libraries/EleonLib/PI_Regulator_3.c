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
#include <PI_Regulator_3.h>


struct PI_Reg_3
{
	U8 Type;			// This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	
	//Inputs
	F32 KpInc;		// P - gain for increasing Output (this means feedback smaller than setpoint)
	F32 KpDec;		// P - gain for decreasing Output (this means feedback greater than setpoint)
	F32 KiInc;		// I - gain for increasing Output (this means feedback smaller than setpoint)
	F32 KiDec;		// I - gain for decreasing Output (this means feedback greater than setpoint)
	F32 Min;		// Min output value limit
	F32 Max;		// Max output value limit
	F32 RateInc;	// Output value increasing rate limit
	F32 RateDec;	// Output value decreasing rate limit
	U32 TimeBase;	// time base for rate inc/dec parameter in [ms]; "TimeBase" should be multiple of "TimeStep" or rate limiter will not give exactly correct rate; "TimeBase" must be greater than "TimeStep"
	U32 TimeStep;	// function calling time step(scantime) in [ms]

	//Outputs
	F32 Output;		// Corrected process value. Equals P + I

	//Internal
	F32 P_value;
	F32 I_value;
	F32 maxStepUp;		// max increase in one time step
	F32 maxStepDown;	// max decrease in one time step
	U32 sampleRate;		// how many function calls take place in "TimeBase" time
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL PI_ValidateObject_3(PI_Regulator_3 pi_reg)
{
   if(pi_reg->Type == 112) return true;
   else return false;
}


// Load PI regulator parameters.
S32 PI_LoadParameters_3(PI_Regulator_3 pi_reg, F32 kpInc, F32 kpDec, F32 kiInc, F32 kiDec, F32 min, F32 max, F32 rateInc, F32 rateDec, U32 timeBase, U32 timeStep)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->KpInc = kpInc;
	pi_reg->KpDec = kpDec;
	pi_reg->KiInc = kiInc;
	pi_reg->KiDec = kiDec;
	pi_reg->Min = min;
	pi_reg->Max = max;
	pi_reg->RateInc = rateInc;
	pi_reg->RateDec = rateDec;

	pi_reg->TimeBase = timeBase;
	pi_reg->TimeStep = timeStep;
	pi_reg->sampleRate = timeBase / timeStep;
	pi_reg->maxStepUp = (F32)(pi_reg->RateInc) / pi_reg->sampleRate;
	pi_reg->maxStepDown = (F32)(pi_reg->RateDec) / pi_reg->sampleRate;
	return 0;
}


// Reset PI regulator process values.
S32 PI_Reset_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->Output = 0;
	pi_reg->P_value = 0;
	pi_reg->I_value = 0;
	return 0;
}


// Creates new PI regulator with specified parameters. Returns pointer to the new PI structure. Returns NULL in case of error.
PI_Regulator_3 PI_New_3(F32 kpInc, F32 kpDec, F32 kiInc, F32 kiDec, F32 min, F32 max, F32 rateInc, F32 rateDec, U32 timeBase, U32 timeStep)
{
	void* pi_reg;

	int result = OS_Allocate_Memory(GetMemPool(), &pi_reg, sizeof(struct PI_Reg_3), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }


	((PI_Regulator_3)pi_reg)->Type = 112;
	PI_LoadParameters_3((PI_Regulator_3)pi_reg, kpInc, kpDec, kiInc, kiDec, min, max, rateInc, rateDec, timeBase, timeStep);
	PI_Reset_3((PI_Regulator_3)pi_reg);

	return (PI_Regulator_3)pi_reg;
}


// Free memory and dispose the PI structure.
S32 PI_Dispose_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	int result = OS_Deallocate_Memory(pi_reg);
	if (result != OS_SUCCESS) { return result; }
	else { return 0; }
}


// Main control program for PI controller. Returns PI controller Output value.
F32 PI_Control_3(PI_Regulator_3 pi_reg, F32 Setpoint, F32 Feedback)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	F32 _Output = pi_reg->Output;
	F32 _P_value = pi_reg->P_value;
	F32 _I_value = pi_reg->I_value;

	F32 Error = Setpoint - Feedback;


	// check which kp and ki parameters to use(Inc/Dec), if Output should be increased or decreased - Error is positive or negative
	if (Error > 0)
	{
		// calculate new values
		_P_value = pi_reg->KpInc * Error;
		_I_value = _I_value + (pi_reg->KiInc * Error);
	}
	else
	{
		// calculate new values
		_P_value = pi_reg->KpDec * Error;
		_I_value = _I_value + (pi_reg->KiDec * Error);
	}
	_Output = _P_value + _I_value;


	// limit output change rate
	F32 changeSpeed = (_Output - pi_reg->Output) * pi_reg->sampleRate;

	if (changeSpeed > 0)
	{
		if (changeSpeed > pi_reg->RateInc)
		{
			pi_reg->Output += pi_reg->maxStepUp;

			// check output limits
			if (pi_reg->Output < pi_reg->Min) { pi_reg->Output = pi_reg->Min; }
			else if (pi_reg->Output > pi_reg->Max) { pi_reg->Output = pi_reg->Max; }
		}
		else
		{
			// check output limits
			if (_Output >= pi_reg->Min && _Output <= pi_reg->Max)
			{
				pi_reg->P_value = _P_value;
				pi_reg->I_value = _I_value;
			}
			else if (_Output < pi_reg->Min) { _Output = pi_reg->Min; }
			else if (_Output > pi_reg->Max) { _Output = pi_reg->Max; }
			pi_reg->Output = _Output;
		}
	}
	else if (changeSpeed < 0)
	{
		if (changeSpeed < -pi_reg->RateDec)
		{
			pi_reg->Output -= pi_reg->maxStepDown;

			// check output limits
			if (pi_reg->Output < pi_reg->Min) { pi_reg->Output = pi_reg->Min; }
			else if (pi_reg->Output > pi_reg->Max) { pi_reg->Output = pi_reg->Max; }
		}
		else
		{
			// check output limits
			if (_Output >= pi_reg->Min && _Output <= pi_reg->Max)
			{
				pi_reg->P_value = _P_value;
				pi_reg->I_value = _I_value;
			}
			else if (_Output < pi_reg->Min) { _Output = pi_reg->Min; }
			else if (_Output > pi_reg->Max) { _Output = pi_reg->Max; }
			pi_reg->Output = _Output;
		}
	}

	return pi_reg->Output;
}


// Set KpInc value
S32 PI_Set_KpInc_3(PI_Regulator_3 pi_reg, F32 kp)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->KpInc = kp;
	return 0;
}


// Set KpDec value
S32 PI_Set_KpDec_3(PI_Regulator_3 pi_reg, F32 kp)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->KpDec = kp;
	return 0;
}


// Set KiInc value
S32 PI_Set_KiInc_3(PI_Regulator_3 pi_reg, F32 ki)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->KiInc = ki;
	return 0;
}


// Set KiDec value
S32 PI_Set_KiDec_3(PI_Regulator_3 pi_reg, F32 ki)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->KiDec = ki;
	return 0;
}


// Set Min output value
S32 PI_Set_Min_3(PI_Regulator_3 pi_reg, F32 min)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->Min = min;
	return 0;
}


// Set Max output value
S32 PI_Set_Max_3(PI_Regulator_3 pi_reg, F32 max)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->Max = max;
	return 0;
}


// Set RateInc value
S32 PI_Set_RateInc_3(PI_Regulator_3 pi_reg, F32 rateInc)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->RateInc = rateInc;
	pi_reg->maxStepUp = (F32)pi_reg->RateInc / pi_reg->sampleRate;
	return 0;
}

// Set RateDec value
S32 PI_Set_RateDec_3(PI_Regulator_3 pi_reg, F32 rateDec)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->RateDec = rateDec;
	pi_reg->maxStepDown = pi_reg->RateDec / pi_reg->sampleRate;
	return 0;
}


// Set TimeBase value
S32 PI_Set_TimeBase_3(PI_Regulator_3 pi_reg, U32 timeBase)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->TimeBase = timeBase;
	pi_reg->sampleRate = pi_reg->TimeBase / pi_reg->TimeStep;
	pi_reg->maxStepUp = (F32)pi_reg->RateInc / pi_reg->sampleRate;
	pi_reg->maxStepDown = (F32)pi_reg->RateDec / pi_reg->sampleRate;
	return 0;
}

// Set TimeStep value for
S32 PI_Set_TimeStep_3(PI_Regulator_3 pi_reg, U32 timeStep)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	pi_reg->TimeStep = timeStep;
	pi_reg->sampleRate = pi_reg->TimeBase / pi_reg->TimeStep;
	pi_reg->maxStepUp = (F32)pi_reg->RateInc / pi_reg->sampleRate;
	pi_reg->maxStepDown = (F32)pi_reg->RateDec / pi_reg->sampleRate;
	return 0;
}


// Return KpInc value
F32 PI_Get_KpInc_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KpInc;
}


// Return KpDec value
F32 PI_Get_KpDec_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KpDec;
}


// Return KiInc value
F32 PI_Get_KiInc_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KiInc;
}


// Return KiDec value
F32 PI_Get_KiDec_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KiDec;
}


// Return Min value
F32 PI_Get_Min_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->Min;
}


// Return Max value
F32 PI_Get_Max_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->Max;
}


// Return RateInc value
F32 PI_Get_RateInc_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->RateInc;
}


// Return RateDec value
F32 PI_Get_RateDec_3(PI_Regulator_3 pi_reg)
{
	if (!PI_ValidateObject_3(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->RateDec;
}
