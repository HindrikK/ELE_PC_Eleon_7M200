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
#include <Hysteresis_v2.h>
#include <Buffer_FIFO.h>

struct Hyst_v2
{
	U8 Type;			   // This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	F32 Hysteresis;	// Parameter that defines hysteresis value
	F32 Low_Limit;		// Hysteresis is not used if input is LOWER or equal with this limit
	F32 High_Limit;	// Hysteresis is not used if input is HIGER or equal with this limit
   BufferFIFO Buffer;
   F32 Mid_Step;
   U16 SampleRate;
	F32 Output;
};




// Validate object reference; Returns FALSE if invalid object reference
static BOOL Hyst_v2_ValidateObject(Hysteresis_v2 hyst)
{
   if(hyst->Type == 104) return true;
   else return false;
}


// Load parameters
S32 Hyst_v2_LoadParameters(Hysteresis_v2 hyst, F32 hysteresis, F32 low_Limit, F32 high_Limit, U16 mid_delay)
{
	if (!Hyst_v2_ValidateObject(hyst)) return -6;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
	hyst->Low_Limit = low_Limit;
	hyst->High_Limit = high_Limit;
   hyst->Mid_Step = hysteresis / (mid_delay / 1000 * hyst->SampleRate);
	return 0;
}


// Reset output value
S32 Hyst_v2_Reset(Hysteresis_v2 hyst, F32 output)
{
	if (!Hyst_v2_ValidateObject(hyst)) return -7;			// hyst points to invalid object structure
	hyst->Output = output;
   BufferFIFO_Clear(hyst->Buffer);
   // prefill buffer
   int i;
   int count = BufferFIFO_Capacity(hyst->Buffer);
   for(i = 0; i < count; i++)
   {
      BufferFIFO_Push(hyst->Buffer, output);
   }
	return 0;
}


// Creates new object with specified parameters. Returns pointer to the new object. Returns NULL in case of error.
Hysteresis_v2 Hyst_v2_New(F32 hysteresis, F32 low_Limit, F32 high_Limit, U16 mid_period, U16 mid_delay, U32 timeStep)
{
	void* hyst;

	int result = OS_Allocate_Memory(GetMemPool(), &hyst, sizeof(struct Hyst_v2), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }
   
   ((Hysteresis_v2)hyst)->SampleRate = 1000 / timeStep;
   U16 capacity = mid_period / timeStep;
   result = BufferFIFO_New(capacity);
   if (result == NULL) { return NULL; }
   ((Hysteresis_v2)hyst)->Buffer = result;

	((Hysteresis_v2)hyst)->Type = 104;
	Hyst_v2_LoadParameters((Hysteresis_v2)hyst, hysteresis, low_Limit, high_Limit, mid_delay);
	Hyst_v2_Reset((Hysteresis_v2)hyst, 0);
	
	return (Hysteresis_v2)hyst;
}


F32 Hyst_v2_Control(Hysteresis_v2 hyst, F32 Input)
{
	if (!Hyst_v2_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
   
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
   
   BufferFIFO_PushPop(hyst->Buffer, Input);
   F32 mid = BufferFIFO_Min(hyst->Buffer) + ( (BufferFIFO_Max(hyst->Buffer) - BufferFIFO_Min(hyst->Buffer) ) / 2 );
   //OS_com_printf("mid: %f\n", mid);//DEBUG
   if(hyst->Output > mid && Input < hyst->Output)
   {
      if( (hyst->Output - hyst->Mid_Step) > mid) hyst->Output -= hyst->Mid_Step;
      else hyst->Output = mid;
   }
   else if(hyst->Output < mid && Input > hyst->Output)
   {
      if( (hyst->Output + hyst->Mid_Step) < mid) hyst->Output += hyst->Mid_Step;
      else hyst->Output = mid;
   }
   
	return hyst->Output;
}


// Set Hysteresis value
S32 Hyst_v2_Set_Hysteresis(Hysteresis_v2 hyst, F32 hysteresis)
{
	if (!Hyst_v2_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Hysteresis = hysteresis;
   return 0;
}


// Set Low_Limit value
S32 Hyst_v2_Set_LowLimit(Hysteresis_v2 hyst, F32 low_Limit)
{
	if (!Hyst_v2_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Low_Limit = low_Limit;
	return 0;
}


// Set High_Limit value
S32 Hyst_v2_Set_HighLimit(Hysteresis_v2 hyst, F32 high_Limit)
{
	if (!Hyst_v2_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->High_Limit = high_Limit;
	return 0;
}


// Set mid_delay value
S32 Hyst_v2_Set_MidDelay(Hysteresis_v2 hyst, U16 mid_Delay)
{
	if (!Hyst_v2_ValidateObject(hyst)) return -1;			// hyst points to invalid object structure
	hyst->Mid_Step = hyst->Hysteresis / (mid_Delay / 1000 * hyst->SampleRate);
	return 0;
}
