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
#include <PI_Regulator_2.h>


struct PI_Reg_2
{
   U8 Type;			// This variable is initialized during _New() function and helps to validate the structure(object) used in functions
   
   //Inputs
   F32 KpInc;		// P - gain for increasing Output (this means feedback smaller than setpoint)
   F32 KpDec;		// P - gain for decreasing Output (this means feedback greater than setpoint)
   F32 KiInc;		// I - gain for increasing Output (this means feedback smaller than setpoint)
   F32 KiDec;		// I - gain for decreasing Output (this means feedback greater than setpoint)
   F32 Min;    		// Min output value limit
   F32 Max;    		// Max output value limit

   //Outputs
   F32 Output;    // Corrected process value. Equals P + I

   //Internal
   F32 P_value;
   F32 I_value;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL PI_ValidateObject_2(PI_Regulator_2 pi_reg)
{
   if(pi_reg->Type == 111) return true;
   else return false;
}


// Load PI regulator parameters.
S32 PI_LoadParameters_2(PI_Regulator_2 pi_reg, F32 kpInc, F32 kpDec, F32 kiInc, F32 kiDec, F32 min, F32 max)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->KpInc = kpInc;
   pi_reg->KpDec = kpDec;
   pi_reg->KiInc = kiInc;
   pi_reg->KiDec = kiDec;
   pi_reg->Min = min;
   pi_reg->Max = max;
   return 0;
}


// Reset PI regulator process values.
S32 PI_Reset_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->Output = 0;
   pi_reg->P_value = 0;
   pi_reg->I_value = 0;
   return 0;
}


// Creates new PI regulator with specified parameters. Returns pointer to the new PI structure. Returns NULL in case of error.
PI_Regulator_2 PI_New_2(F32 kpInc, F32 kpDec, F32 kiInc, F32 kiDec, F32 min, F32 max)
{
   void *pi_reg;

   int result = OS_Allocate_Memory(GetMemPool(), &pi_reg, sizeof(struct PI_Reg_2), OS_NO_SUSPEND);
   if (result != OS_SUCCESS) { return NULL; }


   ((PI_Regulator_2)pi_reg)->Type = 111;
   PI_LoadParameters_2((PI_Regulator_2)pi_reg, kpInc, kpDec, kiInc, kiDec, min, max);
   PI_Reset_2((PI_Regulator_2)pi_reg);

   return (PI_Regulator_2)pi_reg;
}


// Free memory and dispose the PI structure.
S32 PI_Dispose_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   int result = OS_Deallocate_Memory(pi_reg);
   if (result != OS_SUCCESS) { return result; }
   else { return 0; }
}


// Main control program for PI controller. Returns PI controller Output value.
F32 PI_Control_2(PI_Regulator_2 pi_reg, F32 Setpoint, F32 Feedback)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   
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

   // apply new values only if output fits into limits
   if (_Output >= pi_reg->Min && _Output <= pi_reg->Max)
   {
      pi_reg->Output = _Output;
      pi_reg->P_value = _P_value;
      pi_reg->I_value = _I_value;
   }
   else if (_Output < pi_reg->Min) { pi_reg->Output = pi_reg->Min; }
   else if (_Output > pi_reg->Max) { pi_reg->Output = pi_reg->Max; }

   return pi_reg->Output;
}


// Set KpInc value for PI regulator.
S32 PI_Set_KpInc_2(PI_Regulator_2 pi_reg, F32 kp)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->KpInc = kp;
   return 0;
}


// Set KpDec value for PI regulator.
S32 PI_Set_KpDec_2(PI_Regulator_2 pi_reg, F32 kp)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->KpDec = kp;
   return 0;
}


// Set KiInc value for PI regulator.
S32 PI_Set_KiInc_2(PI_Regulator_2 pi_reg, F32 ki)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->KiInc = ki;
   return 0;
}


// Set KiDec value for PI regulator.
S32 PI_Set_KiDec_2(PI_Regulator_2 pi_reg, F32 ki)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->KiDec = ki;
   return 0;
}


// Set Min output value for PI regulator.
S32 PI_Set_Min_2(PI_Regulator_2 pi_reg, F32 min)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->Min = min;
   return 0;
}


// Set Max output value for PI regulator.
S32 PI_Set_Max_2(PI_Regulator_2 pi_reg, F32 max)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
   pi_reg->Max = max;
   return 0;
}


// Return KpInc value of PI regulator.
F32 PI_Get_KpInc_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KpInc;
}


// Return KpDec value of PI regulator.
F32 PI_Get_KpDec_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KpDec;
}


// Return KiInc value of PI regulator.
F32 PI_Get_KiInc_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KiInc;
}


// Return KiDec value of PI regulator.
F32 PI_Get_KiDec_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->KiDec;
}


// Return Min value of PI regulator.
F32 PI_Get_Min_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->Min;
}


// Return Max value of PI regulator.
F32 PI_Get_Max_2(PI_Regulator_2 pi_reg)
{
	if (!PI_ValidateObject_2(pi_reg)) return -1;			// pointer to invalid object structure
	return pi_reg->Max;
}
