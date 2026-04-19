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
#include <PID_Regulator_3.h>


struct PID_Reg_3
{
	U8 Type;		// This variable is initialized during _New() function and helps to validate the structure(object) used in functions

	//Inputs
	F32 KpInc;		// P - gain for increasing P-component (this means feedback smaller than setpoint)
	F32 KpDec;		// P - gain for decreasing P-component (this means feedback greater than setpoint)
	F32 KiInc;		// I - gain for increasing I-component (this means feedback smaller than setpoint)
	F32 KiDec;		// I - gain for decreasing I-component (this means feedback greater than setpoint)
	F32 KdInc;		// D - gain for increasing D-component (situation when feedback is decreasing)
	F32 KdDec;		// D - gain for decreasing D-component (situation when feedback is increasing)
	F32 KpAdj;     // factor for adjusting P gain; <1.0 decreases gain and >1.0 increases gain
	F32 KiAdj;     // factor for adjusting I gain; <1.0 decreases gain and >1.0 increases gain
	F32 KdAdj;     // factor for adjusting D gain; <1.0 decreases gain and >1.0 increases gain
	U16 D_period;	// specifies the time period over which to calculate derivate D in number of TimeStep; e.g. 5 = 5 x 20(TimeStep) = 100 ms
	F32 Min;		// Min output value limit
	F32 Max;		// Max output value limit
	F32 I_saturLimMin;	// Saturation limit for integrator
	F32 I_saturLimMax;	// Saturation limit for integrator
	F32 RateInc;	// Output value increasing rate limit
	F32 RateDec;	// Output value decreasing rate limit
	U32 TimeBase;	// time base for rate inc/dec parameter in [ms]; "TimeBase" should be multiple of "TimeStep" or rate limiter will not give exactly correct rate; "TimeBase" must be greater than "TimeStep"
	U32 TimeStep;	// function calling time step(scantime) in [ms]

	//Outputs
	F32 Output;		// Corrected process value. Equals P + I + D

	//Internal
	F32 P_value;
	F32 I_value;
	F32 D_value;
	F32 maxStepUp;		      // max increase in one time step
	F32 maxStepDown;	      // max decrease in one time step
	U32 sampleRate;		   // how many function calls take place in "TimeBase" time
	F32* ErrorBufferArray;	// previous error values for D calculation
	int push_Index;
	int pop_Index;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL PID_ValidateObject_3(PID_Regulator_3 pid_reg)
{
	if (pid_reg->Type == 113) return true;
	else return false;
}


// Load PID regulator parameters.
S32 PID_LoadParameters_3(PID_Regulator_3 pid_reg, F32 kpInc, F32 kpDec, F32 kiInc, F32 kiDec, F32 kdInc, F32 kdDec, F32 min, F32 max, F32 rateInc, F32 rateDec, U32 timeBase, U32 timeStep)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KpInc = kpInc;
	pid_reg->KpDec = kpDec;
	pid_reg->KiInc = kiInc;
	pid_reg->KiDec = kiDec;
	pid_reg->KdInc = kdInc;
	pid_reg->KdDec = kdDec;
	pid_reg->Min = min;
	pid_reg->Max = max;
	pid_reg->RateInc = rateInc;
	pid_reg->RateDec = rateDec;

	pid_reg->TimeBase = timeBase;
	pid_reg->TimeStep = timeStep;
	pid_reg->sampleRate = timeBase / timeStep;
	pid_reg->maxStepUp = pid_reg->RateInc / pid_reg->sampleRate;
	pid_reg->maxStepDown = pid_reg->RateDec / pid_reg->sampleRate;
	return 0;
}


// Reset PID regulator process values.
S32 PID_Reset_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->I_value = 0;
	pid_reg->Output = 0;

	// prefill error buffer
	int i;
	for (i = 0; i < pid_reg->D_period; i++)
	{
		pid_reg->ErrorBufferArray[i] = 0;
	}

	return 0;
}


// Preset PID regulator process values based on desired output value
S32 PID_Preset_3(PID_Regulator_3 pid_reg, F32 Setpoint, F32 Feedback, F32 Output)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->Output = Output;
	F32 Error = Setpoint - Feedback;

	// preset P component
	if (Error > 0)
	{
		pid_reg->P_value = pid_reg->KpInc * Error * pid_reg->KpAdj;
	}
	else
	{
		pid_reg->P_value = pid_reg->KpDec * Error * pid_reg->KpAdj;
	}
	
	// preset D buffer
	F32 change = Error - pid_reg->ErrorBufferArray[pid_reg->push_Index];  // find the change between last error value in buffer and error of preset values
	// adjust error buffer based on the new preset value error
	int i;
	for (i = 0; i < pid_reg->D_period; i++)
	{
		pid_reg->ErrorBufferArray[i] += change;
	}
	pid_reg->D_value = 0;
	
	// preset I component
	pid_reg->I_value = Output - pid_reg->P_value - pid_reg->D_value;
	if (pid_reg->I_value > pid_reg->I_saturLimMax)
	{
		pid_reg->I_value = pid_reg->I_saturLimMax;
		pid_reg->Output = pid_reg->P_value + pid_reg->I_value + pid_reg->D_value;
	}
	else if (pid_reg->I_value < pid_reg->I_saturLimMin)
	{
		pid_reg->I_value = pid_reg->I_saturLimMin;
		pid_reg->Output = pid_reg->P_value + pid_reg->I_value + pid_reg->D_value;
	}
   
   // check output limits
	if (pid_reg->Output < pid_reg->Min) { pid_reg->Output = pid_reg->Min; }
	else if (pid_reg->Output > pid_reg->Max) { pid_reg->Output = pid_reg->Max; }
	pid_reg->Output = pid_reg->Output;

	return 0;
}


// Creates new PID regulator with specified parameters. Returns pointer to the new PID structure. Returns NULL in case of error.
PID_Regulator_3 PID_New_3(F32 kpInc, F32 kpDec, F32 kiInc, F32 kiDec, F32 kdInc, F32 kdDec, U16 d_period, F32 min, F32 max, F32 rateInc, F32 rateDec, U32 timeBase, U32 timeStep)
{
	void* pid_reg;

	int result = OS_Allocate_Memory(GetMemPool(), &pid_reg, sizeof(struct PID_Reg_3), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	if (d_period < 1) return NULL;	// min d_period is 1

	((PID_Regulator_3)pid_reg)->Type = 113;
	((PID_Regulator_3)pid_reg)->D_period = d_period;
   
   void* buffer;
   
	// reserve memory for BufferArray
	result = OS_Allocate_Memory(GetMemPool(), (void**)& buffer, sizeof(F32) * d_period, OS_NO_SUSPEND);
	if (result != OS_SUCCESS) return NULL;

	((PID_Regulator_3)pid_reg)->ErrorBufferArray = buffer;

	PID_LoadParameters_3((PID_Regulator_3)pid_reg, kpInc, kpDec, kiInc, kiDec, kdInc, kdDec, min, max, rateInc, rateDec, timeBase, timeStep);
	((PID_Regulator_3)pid_reg)->KpAdj = 1.0;
	((PID_Regulator_3)pid_reg)->KiAdj = 1.0;
	((PID_Regulator_3)pid_reg)->KdAdj = 1.0;
	((PID_Regulator_3)pid_reg)->I_saturLimMax = max;
	((PID_Regulator_3)pid_reg)->I_saturLimMin = min;
	((PID_Regulator_3)pid_reg)->push_Index = d_period - 1;
	((PID_Regulator_3)pid_reg)->pop_Index = 0;
	PID_Reset_3((PID_Regulator_3)pid_reg);

	return (PID_Regulator_3)pid_reg;
}


// Free memory and dispose the PID structure.
S32 PID_Dispose_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	int result = OS_Deallocate_Memory(pid_reg->ErrorBufferArray);
	if (result != OS_SUCCESS) { return result; }
	result = OS_Deallocate_Memory(pid_reg);
	if (result != OS_SUCCESS) { return result; }

	return 0;
}


// Main control program for PID controller. Returns PID controller Output value.
F32 PID_Control_3(PID_Regulator_3 pid_reg, F32 Setpoint, F32 Feedback)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure


	F32 _Output = pid_reg->Output;
	F32 _I_value = pid_reg->I_value;

	F32 Error = Setpoint - Feedback;

	// check which kp and ki parameters to use(Inc/Dec), if Output should be increased or decreased - Error is positive or negative
	if (Error > 0)
	{
		//******************************************************************
		// calculate P component
		//******************************************************************
		pid_reg->P_value = pid_reg->KpInc * Error * pid_reg->KpAdj;

		//******************************************************************
		// calculate I component
		//******************************************************************
		// if output already in max limit then don't update I component
		if (_Output < pid_reg->Max)
		{
			_I_value = _I_value + (pid_reg->KiInc * Error * pid_reg->KiAdj);
			if (_I_value > pid_reg->I_saturLimMax)
			{
				_I_value = pid_reg->I_saturLimMax;
			}
			else if (_I_value < pid_reg->I_saturLimMin)
			{
				_I_value = pid_reg->I_saturLimMin;
			}
			
			// trim I component if output exceeds max limit
			if ((pid_reg->P_value + _I_value) > pid_reg->Max)
			{
				_I_value = pid_reg->Max - pid_reg->P_value;
			}

			pid_reg->I_value = _I_value;
		}
	}
	else
	{
		//******************************************************************
		// calculate P component
		//******************************************************************
		pid_reg->P_value = pid_reg->KpDec * Error * pid_reg->KpAdj;

		//******************************************************************
		// calculate I component
		//******************************************************************
		// if output already in min limit then don't update I component
		if (_Output > pid_reg->Min)
		{
			_I_value = _I_value + (pid_reg->KiDec * Error * pid_reg->KiAdj);
			if (_I_value > pid_reg->I_saturLimMax)
			{
				_I_value = pid_reg->I_saturLimMax;
			}
			else if (_I_value < pid_reg->I_saturLimMin)
			{
				_I_value = pid_reg->I_saturLimMin;
			}

			// trim I component if output exceeds min limit
			if ((pid_reg->P_value + _I_value) < pid_reg->Min)
			{
				_I_value = pid_reg->Min - pid_reg->P_value;
			}

			pid_reg->I_value = _I_value;
		}
	}


	//******************************************************************
	// calculate D component
	//******************************************************************
	pid_reg->push_Index++;
	pid_reg->push_Index %= pid_reg->D_period;
	F32 change = Error - pid_reg->ErrorBufferArray[pid_reg->pop_Index];
	pid_reg->pop_Index++;
	pid_reg->pop_Index %= pid_reg->D_period;

	pid_reg->ErrorBufferArray[pid_reg->push_Index] = Error;

	if (change > 0)
	{
		pid_reg->D_value = change * pid_reg->KdInc * pid_reg->KdAdj;
	}
	else
	{
		pid_reg->D_value = change * pid_reg->KdDec * pid_reg->KdAdj;
	}
	//******************************************************************
	//******************************************************************

	_Output = pid_reg->P_value + pid_reg->I_value + pid_reg->D_value;



	// values limiter
	F32 changeSpeed = (_Output - pid_reg->Output) * pid_reg->sampleRate;

	if (changeSpeed > 0)
	{
		if (changeSpeed > pid_reg->RateInc)
		{
			pid_reg->Output += pid_reg->maxStepUp;

			// check output limits
			if (pid_reg->Output < pid_reg->Min) { pid_reg->Output = pid_reg->Min; }
			else if (pid_reg->Output > pid_reg->Max) { pid_reg->Output = pid_reg->Max; }
		}
		else
		{
			// check output limits
			if (_Output < pid_reg->Min) { _Output = pid_reg->Min; }
			else if (_Output > pid_reg->Max) { _Output = pid_reg->Max; }
			pid_reg->Output = _Output;
		}
	}
	else if (changeSpeed < 0)
	{
		if (changeSpeed < -pid_reg->RateDec)
		{
			pid_reg->Output -= pid_reg->maxStepDown;

			// check output limits
			if (pid_reg->Output < pid_reg->Min) { pid_reg->Output = pid_reg->Min; }
			else if (pid_reg->Output > pid_reg->Max) { pid_reg->Output = pid_reg->Max; }
		}
		else
		{
			// check output limits
			if (_Output < pid_reg->Min) { _Output = pid_reg->Min; }
			else if (_Output > pid_reg->Max) { _Output = pid_reg->Max; }
			pid_reg->Output = _Output;
		}
	}

	return pid_reg->Output;
}


// Set KpInc value
S32 PID_Set_KpInc_3(PID_Regulator_3 pid_reg, F32 kp)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KpInc = kp;
	return 0;
}


// Set KpDec value
S32 PID_Set_KpDec_3(PID_Regulator_3 pid_reg, F32 kp)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KpDec = kp;
	return 0;
}


// Set KiInc value
S32 PID_Set_KiInc_3(PID_Regulator_3 pid_reg, F32 ki)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KiInc = ki;
	return 0;
}


// Set KiDec value
S32 PID_Set_KiDec_3(PID_Regulator_3 pid_reg, F32 ki)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KiDec = ki;
	return 0;
}


// Set KdInc value
S32 PID_Set_KdInc_3(PID_Regulator_3 pid_reg, F32 kd)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KdInc = kd;
	return 0;
}


// Set KdDec value
S32 PID_Set_KdDec_3(PID_Regulator_3 pid_reg, F32 kd)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KdDec = kd;
	return 0;
}


// Set I saturation limit min
S32 PID_Set_IsaturLimMin_3(PID_Regulator_3 pid_reg, F32 lim)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->I_saturLimMin = lim;
	return 0;
}


// Set I saturation limit max
S32 PID_Set_IsaturLimMax_3(PID_Regulator_3 pid_reg, F32 lim)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->I_saturLimMax = lim;
	return 0;
}


// Set Min output value
S32 PID_Set_Min_3(PID_Regulator_3 pid_reg, F32 min)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->Min = min;
	return 0;
}


// Set Max output value
S32 PID_Set_Max_3(PID_Regulator_3 pid_reg, F32 max)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->Max = max;
	return 0;
}


// Set RateInc value
S32 PID_Set_RateInc_3(PID_Regulator_3 pid_reg, F32 rateInc)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->RateInc = rateInc;
	pid_reg->maxStepUp = pid_reg->RateInc / pid_reg->sampleRate;
	return 0;
}

// Set RateDec value
S32 PID_Set_RateDec_3(PID_Regulator_3 pid_reg, F32 rateDec)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->RateDec = rateDec;
	pid_reg->maxStepDown = pid_reg->RateDec / pid_reg->sampleRate;
	return 0;
}


// Set TimeBase value
S32 PID_Set_TimeBase_3(PID_Regulator_3 pid_reg, U32 timeBase)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->TimeBase = timeBase;
	pid_reg->sampleRate = pid_reg->TimeBase / pid_reg->TimeStep;
	pid_reg->maxStepUp = pid_reg->RateInc / pid_reg->sampleRate;
	pid_reg->maxStepDown = pid_reg->RateDec / pid_reg->sampleRate;
	return 0;
}

// Set TimeStep value
S32 PID_Set_TimeStep_3(PID_Regulator_3 pid_reg, U32 timeStep)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->TimeStep = timeStep;
	pid_reg->sampleRate = pid_reg->TimeBase / pid_reg->TimeStep;
	pid_reg->maxStepUp = pid_reg->RateInc / pid_reg->sampleRate;
	pid_reg->maxStepDown = pid_reg->RateDec / pid_reg->sampleRate;
	return 0;
}


// Set gain adjust values
S32 PID_Set_Adjust_3(PID_Regulator_3 pid_reg, F32 kpAdj, F32 kiAdj, F32 kdAdj)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	pid_reg->KpAdj = kpAdj;
	pid_reg->KiAdj = kiAdj;
	pid_reg->KdAdj = kdAdj;
	return 0;
}


// Return P value
F32 PID_Get_P_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->P_value;
}


// Return I value
F32 PID_Get_I_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->I_value;
}


// Return D value
F32 PID_Get_D_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->D_value;
}


// Return KpInc value
F32 PID_Get_KpInc_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->KpInc;
}


// Return KpDec value
F32 PID_Get_KpDec_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->KpDec;
}


// Return KiInc value
F32 PID_Get_KiInc_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->KiInc;
}


// Return KiDec value
F32 PID_Get_KiDec_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->KiDec;
}


// Return KdInc value
F32 PID_Get_KdInc_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->KdInc;
}


// Return KdDec value
F32 PID_Get_KdDec_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->KdDec;
}


// Return D period
U16 PID_Get_D_period_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->D_period;
}


// Return I saturation limit value
F32 PID_Get_IsaturLimMin_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->I_saturLimMin;
}


// Return I saturation limit value
F32 PID_Get_IsaturLimMax_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->I_saturLimMax;
}


// Return Min value
F32 PID_Get_Min_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->Min;
}


// Return Max value
F32 PID_Get_Max_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->Max;
}


// Return RateInc value
F32 PID_Get_RateInc_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->RateInc;
}


// Return RateDec value
F32 PID_Get_RateDec_3(PID_Regulator_3 pid_reg)
{
	if (!PID_ValidateObject_3(pid_reg)) return -1;			// pointer to invalid object structure
	return pid_reg->RateDec;
}