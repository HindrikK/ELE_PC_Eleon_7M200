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
#include "Derivative.h"


struct Deriv
{
	U8 Type;		// This variable is initialized during _New() function and helps to validate the structure(object) used in functions

	//Inputs
	U16 D_period;	// specifies the time period over which to calculate derivate D in number of TimeStep (1-20); e.g. 5 = 5 x 20(TimeStep) = 100 ms
	U32 TimeBase;	// time base in [ms] for derivate/rate calculation; "TimeBase" should be multiple of "TimeStep" or rate limiter will not give exactly correct rate; "TimeBase" must be greater than "TimeStep"
	U32 TimeStep;	// function calling time step(scantime) in [ms]

	//Outputs
	F32 Result;    // calculated derivate

	//Internal
	F32 Buffer[50];	// previous values for change calculation
	F32 timeBaseFactor;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL Derivative_ValidateObject(Derivative deri)
{
	if (deri->Type == 134) return true;
	else return false;
}


// Load Derivative parameters.
S32 Derivative_LoadParameters(Derivative deri, U16 d_period, U32 timeBase, U32 timeStep)
{
	if (!Derivative_ValidateObject(deri)) return -1;			// pointer to invalid object structure
	if (d_period < 1 || d_period > 50) d_period = 1;	         // invalid parameter value, set default value
	deri->D_period = d_period;
	deri->TimeStep = timeStep;
	deri->timeBaseFactor = (F32)timeBase / (timeStep * d_period);
	return 0;
}


// Creates new Derivative with specified parameters. Returns pointer to the new Derivative structure. Returns NULL in case of error.
Derivative Derivative_New(U16 d_period, U32 timeBase, U32 timeStep, F32 initValue)
{
	void* deri;

	int result = OS_Allocate_Memory(GetMemPool(), &deri, sizeof(struct Deriv), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }


	((Derivative)deri)->Type = 134;
	Derivative_LoadParameters((Derivative)deri, d_period, timeBase, timeStep);
	// clear buffer
	int i;
	for (i = ((Derivative)deri)->D_period - 1; i >= 0; i--)
	{
		((Derivative)deri)->Buffer[i] = initValue;
	}

	return (Derivative)deri;
}


// Free memory and dispose the Derivative structure.
S32 Derivative_Dispose(Derivative deri)
{
	if (!Derivative_ValidateObject(deri)) return -1;			// pointer to invalid object structure
	int result = OS_Deallocate_Memory(deri);
	if (result != OS_SUCCESS) { return result; }
	else { return 0; }
}


// Reset all values in buffer with initValue
S32 Derivative_Reset(Derivative deri, F32 initValue)
{
	if (!Derivative_ValidateObject(deri)) return -1;			// pointer to invalid object structure

	// clear buffer
	int i;
	for (i = ((Derivative)deri)->D_period - 1; i >= 0; i--)
	{
		((Derivative)deri)->Buffer[i] = initValue;
	}

	return 0;
}


// Main control program for Derivative. Returns derivate value.
F32 Derivative_Control(Derivative deri, F32 Value)
{
	if (!Derivative_ValidateObject(deri)) return -1;			// pointer to invalid object structure

	deri->Result = Value - deri->Buffer[deri->D_period - 1];
	// shift buffer
	int i;
	for (i = deri->D_period - 1; i > 0; i--)
	{
		deri->Buffer[i] = deri->Buffer[i - 1];
	}
	deri->Buffer[0] = Value;

	return deri->Result * deri->timeBaseFactor;
}


// Set TimeBase value
S32 Derivative_Set_TimeBase(Derivative deri, U32 timeBase)
{
	if (!Derivative_ValidateObject(deri)) return -1;			// pointer to invalid object structure
	deri->timeBaseFactor = (F32)timeBase / (deri->TimeStep * deri->D_period);
	return 0;
}

// Set TimeStep value
S32 Derivative_Set_TimeStep(Derivative deri, U32 timeStep)
{
	if (!Derivative_ValidateObject(deri)) return -1;			// pointer to invalid object structure
	deri->TimeStep = timeStep;
	deri->timeBaseFactor = (F32)deri->TimeBase / (timeStep * deri->D_period);
	return 0;
}
