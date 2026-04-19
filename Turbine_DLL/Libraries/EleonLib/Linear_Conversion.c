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
#include <Linear_Conversion.h>



S32 Linear_Conversion(S32 Input, S32 InLow, S32 InHigh, S32 OutLow, S32 OutHigh)
{
	S32 Result;

	if (InHigh != InLow)
	{
		S64 result_x10 = ((S64)Input - InLow) * ((S64)(OutHigh - OutLow) * 10) / (InHigh - InLow);		// x10 is for added precision
		// round value up when last digit >= 5 and down when < 5
		// rounding is needed for correct conversion result; otherwise result is always lagging input by 1 digit when input value is exactly at step
		if (result_x10 >= 0)
		{
			result_x10+= 5;		// rounding positive values
		}
		else
		{
			result_x10-= 5;		// rounding negative values
		}
		Result = OutLow + (S32)(result_x10 / 10);	
	}
	else { Result = OutLow; }

	// check limits
	if (OutLow < OutHigh)
	{
		if (Result < OutLow) { Result = OutLow; }
		else if (Result > OutHigh) { Result = OutHigh; }
	}
	else
	{
		if (Result < OutHigh) { Result = OutHigh; }
		else if (Result > OutLow) { Result = OutLow; }
	}

	return Result;
}


S32 Linear_Conversion_Unlimited(S32 Input, S32 InLow, S32 InHigh, S32 OutLow, S32 OutHigh)
{
	if (InHigh != InLow)
	{
		S64 result_x10 = ((S64)Input - InLow) * ((S64)(OutHigh - OutLow) * 10) / (InHigh - InLow);		// x10 is for added precision
		// round value up when last digit >= 5 and down when < 5
		// rounding is needed for correct conversion result; otherwise result is always lagging input by 1 digit when input value is exactly at step
		if (result_x10 >= 0) {
			result_x10+= 5;		// rounding positive values
		}
		else {
			result_x10-= 5;		// rounding negative values
		}
		return OutLow + (S32)(result_x10 / 10);
	}
	else {
        return OutLow;
    }
}


F32 Linear_Conversion_F32(F32 Input, F32 InLow, F32 InHigh, F32 OutLow, F32 OutHigh)
{
	F32 Result;

	if (InHigh != InLow)
	{
		Result = (Input - InLow) * (OutHigh - OutLow) / (InHigh - InLow);
		Result += OutLow;	
	}
	else { Result = OutLow; }

	// check limits
	if (OutLow < OutHigh)
	{
		if (Result < OutLow) { Result = OutLow; }
		else if (Result > OutHigh) { Result = OutHigh; }
	}
	else
	{
		if (Result < OutHigh) { Result = OutHigh; }
		else if (Result > OutLow) { Result = OutLow; }
	}

	return Result;
}


F32 Linear_Conversion_F32_Unlimited(F32 Input, F32 InLow, F32 InHigh, F32 OutLow, F32 OutHigh)
{
	if (InHigh != InLow) {
		return OutLow + ((Input - InLow) * (OutHigh - OutLow) / (InHigh - InLow));
	}
	else {
        return OutLow;
    }
}
