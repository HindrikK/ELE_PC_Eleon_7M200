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
#include "Acceleration_Limiter.h"


struct AccLim
{
	U8 Type;			// This variable is initialized during _New() function and helps to validate the structure(object) used in functions

	//Inputs
	U32 TimeBase;		// time base for rate up/down parameter in [ms]; "TimeBase" should be multiple of "TimeStep" or rate limiter will not give exactly correct rate; "TimeBase" must be greater than "TimeStep"
	U32 TimeStep;		// function calling time step(scantime) in [ms]

	//Outputs
	F32 Output;			// resulting value

	//Internal
	U32 sampleRate;			// how many function calls take place in "TimeBase" time
	F32 speedOutput;			// current speed of Output value change
	F32 accOutput;				// max increase of speedOutput per step
	F32 decOutput;				// max decrease of speedOutput per step
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL AccLim_ValidateObject(Acceleration_Limiter accLim)
{
	if (accLim->Type == 137) return true;
	else return false;
}


// Load parameters
S32 AccLim_LoadParameters(Acceleration_Limiter accLim, F32 accel, F32 decel)
{
	if (!AccLim_ValidateObject(accLim)) return -1;			   // pointer to invalid object structure
	accLim->accOutput = accel / accLim->sampleRate;
	accLim->decOutput = decel / accLim->sampleRate;
	//if (accLim->accOutput == 0 || accLim->decOutput == 0)
	//{
	//	return -2;		// invalid values
	//}

	return 0;
}


// Reset output value.
S32 AccLim_Reset(Acceleration_Limiter accLim, F32 output)
{
	if (!AccLim_ValidateObject(accLim)) return -1;			// pointer to invalid object structure
	accLim->Output = output;
	accLim->speedOutput = 0;

	return 0;
}


// Creates new object with specified parameters. Returns pointer to the new object structure. Returns NULL in case of error
Acceleration_Limiter AccLim_New(F32 accel, F32 decel, U32 timeBase, U32 timeStep)
{
	void* accLim;

	int result = OS_Allocate_Memory(GetMemPool(), &accLim, sizeof(struct AccLim), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((Acceleration_Limiter)accLim)->Type = 137;
	((Acceleration_Limiter)accLim)->TimeBase = timeBase;
	((Acceleration_Limiter)accLim)->TimeStep = timeStep;
	if (timeStep == 0) { return NULL; }
	((Acceleration_Limiter)accLim)->sampleRate = timeBase / timeStep;
	if (((Acceleration_Limiter)accLim)->sampleRate == 0) { return NULL; }
	((Acceleration_Limiter)accLim)->accOutput = accel / ((Acceleration_Limiter)accLim)->sampleRate;
	((Acceleration_Limiter)accLim)->decOutput = decel / ((Acceleration_Limiter)accLim)->sampleRate;
	((Acceleration_Limiter)accLim)->Output = 0;
	((Acceleration_Limiter)accLim)->speedOutput = 0;

	return (Acceleration_Limiter)accLim;
}


// Free memory and dispose the object structure
S32 AccLim_Dispose(Acceleration_Limiter accLim)
{
	if (!AccLim_ValidateObject(accLim)) return -1;			// pointer to invalid object structure

	int result = OS_Deallocate_Memory(accLim);
	if (result != OS_SUCCESS) { return result; }
	return 0;
}


// Main control function. Returns process value
F32 AccLim_Control(Acceleration_Limiter accLim, F32 Input)
{
	if (!AccLim_ValidateObject(accLim)) return -1;	   // pointer to invalid object structure
   
   
   // how many cycles it takes to reach Input with current Output speed when input speed = 0
   F32 time_1;
   if(Input > accLim->Output + accLim->decOutput)
   {
      if(accLim->speedOutput > 0)
      {
         time_1 = (Input - accLim->Output) / accLim->speedOutput;
      }
      else
      {
         time_1 = 1000000000;    // "indefinetly" long time
      }
   }
   else if (Input < accLim->Output - accLim->decOutput)
   {
      if(accLim->speedOutput < 0)
      {
         time_1 = (accLim->Output - Input) / -(accLim->speedOutput);
      }
      else
      {
         time_1 = 1000000000;    // "indefinetly" long time
      }
   }
   else     // input and output values are closer than accOutput and decOutput
   {
      accLim->speedOutput = 0;
      accLim->Output = Input;
      return accLim->Output;
   }
   
   // how many cycles it takes to ramp current Output speed to 0
   F32 time_2 = 0;
   if(accLim->speedOutput > 0)
   {
      time_2 = accLim->speedOutput / accLim->decOutput;
   }
   else if(accLim->speedOutput < 0)
   {
      time_2 = -(accLim->speedOutput) / accLim->decOutput;
   }
   
   // prevent overshoot by reducing speed
   if(time_2 >= time_1)
   {
      if(accLim->speedOutput > 0) { accLim->speedOutput -= accLim->decOutput; }
      else if(accLim->speedOutput < 0){ accLim->speedOutput += accLim->decOutput; }
      accLim->Output += accLim->speedOutput;
      return accLim->Output;
   }
   

   F32 speed = Input - accLim->Output;                // calculate changeSpeed
	F32 accel = speed - accLim->speedOutput;           // calculate acceleration
   
   if(accel > accLim->accOutput)
   {
      accel = accLim->accOutput;
   }
   else if(accel < -(accLim->decOutput))
   {
      accel = -(accLim->decOutput);
   }
   
	accLim->speedOutput += accel;
   accLim->Output += accLim->speedOutput;

	return accLim->Output;
}
