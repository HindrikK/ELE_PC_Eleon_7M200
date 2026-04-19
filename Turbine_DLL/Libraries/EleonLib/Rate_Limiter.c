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
#include <Rate_Limiter.h>


struct Rate_Lim
{
	U8 Type;			// This variable is initialized with TYPE_ID during _New() function and helps to validate the structure(object) used in functions
	
	//Inputs
	S64 RateUp;			// maximum rate of output value increase in one second (x100, for precision)
	S64 RateDown;		// maximum rate of output value decrease in one second (x100, for precision)
	U32 TimeBase;		// time base for rate up/down parameter in [ms]; "TimeBase" should be multiple of "TimeStep" or rate limiter will not give exactly correct rate; "TimeBase" must be greater than "TimeStep"
	U32 TimeStep;		// function calling time step(scantime) in [ms]

	//Outputs
	S64 Output;			// output value with limited rate (x100, for precision)
	
	//Internal
	S64 maxStepUp;		// max increase in one time step
	S64 maxStepDown;	// max decrease in one time step
	U32 sampleRate;		// how many function calls take place in "TimeBase" time
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL RateLim_ValidateObject(Rate_Limiter rateLim)
{
   if(rateLim->Type == 120) return true;
   else return false;
}


// Load parameters.
S32 RateLim_LoadParameters(Rate_Limiter rateLim, S32 rateUp, S32 rateDown, U32 timeBase, U32 timeStep)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	rateLim->RateUp = (S64)rateUp * 100;
	rateLim->RateDown = (S64)rateDown * 100;
	rateLim->TimeBase = timeBase;
	rateLim->TimeStep = timeStep;
	rateLim->sampleRate = rateLim->TimeBase / rateLim->TimeStep;
	rateLim->maxStepUp = rateLim->RateUp / rateLim->sampleRate;
	rateLim->maxStepDown = rateLim->RateDown / rateLim->sampleRate;
	return 0;
}


// Reset output value.
S32 RateLim_Reset(Rate_Limiter rateLim, S32 output)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	rateLim->Output = (S64)output * 100;
	return 0;
}


// Creates new Rate_Limiter with specified parameters. Returns pointer to the new Rate_Limiter structure. Returns NULL in case of error.
Rate_Limiter RateLim_New(S32 rateUp, S32 rateDown, U32 timeBase, U32 timeStep)
{
	void* rateLim;

	int result = OS_Allocate_Memory(GetMemPool(), &rateLim, sizeof(struct Rate_Lim), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((Rate_Limiter)rateLim)->Type = 120;
	RateLim_LoadParameters((Rate_Limiter)rateLim, rateUp, rateDown, timeBase, timeStep);
	((Rate_Limiter)rateLim)->Output = 0;

	return (Rate_Limiter)rateLim;
}


// Free memory and dispose the structure.
S32 RateLim_Dispose(Rate_Limiter rateLim)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	int result = OS_Deallocate_Memory(rateLim);
	if (result != OS_SUCCESS) { return result; }
	else { return 0; }
}


S32 RateLim_Control(Rate_Limiter rateLim, S32 Input)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	
	S64 changeSpeed = ((S64)Input * 100 - rateLim->Output) * rateLim->sampleRate;

	if (changeSpeed > 0)
	{
		if (changeSpeed > rateLim->RateUp)
		{
		   rateLim->Output += rateLim->maxStepUp;
		}
		else
		{
		   rateLim->Output = (S64)Input * 100;
		}

	}
	else if (changeSpeed < 0)
	{
	    if (changeSpeed < -rateLim->RateDown)
		{
		   rateLim->Output -= rateLim->maxStepDown;
		}
		else
		{
		   rateLim->Output = (S64)Input * 100;
		}
	}


	return rateLim->Output / 100;
}



// Set RateUp value
S32 RateLim_Set_RateUp(Rate_Limiter rateLim, S32 rateUp)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	rateLim->RateUp = (S64)rateUp * 100;
	rateLim->maxStepUp = rateLim->RateUp / rateLim->sampleRate;
	return 0;
}

// Set RateDown value
S32 RateLim_Set_RateDown(Rate_Limiter rateLim, S32 rateDown)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	rateLim->RateDown = (S64)rateDown * 100;
	rateLim->maxStepDown = rateLim->RateDown / rateLim->sampleRate;
	return 0;
}

// Set TimeBase value
S32 RateLim_Set_TimeBase(Rate_Limiter rateLim, U32 timeBase)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	rateLim->TimeBase = timeBase;
	rateLim->sampleRate = rateLim->TimeBase / rateLim->TimeStep;
	rateLim->maxStepUp = rateLim->RateUp / rateLim->sampleRate;
	rateLim->maxStepDown = rateLim->RateDown / rateLim->sampleRate;
	return 0;
}

// Set TimeStep value
S32 RateLim_Set_TimeStep(Rate_Limiter rateLim, U32 timeStep)
{
	if (!RateLim_ValidateObject(rateLim)) return -1;			// pointer to invalid object structure
	rateLim->TimeStep = timeStep;
	rateLim->sampleRate = rateLim->TimeBase / rateLim->TimeStep;
	rateLim->maxStepUp = rateLim->RateUp / rateLim->sampleRate;
	rateLim->maxStepDown = rateLim->RateDown / rateLim->sampleRate;
	return 0;
}
