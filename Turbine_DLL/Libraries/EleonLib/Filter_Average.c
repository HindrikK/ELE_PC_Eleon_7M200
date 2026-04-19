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


#include <Filter_Average.h>

//#define FILTAVG_DEBUG
#define _S32MAX ((U32)2147483648)


S32 FilterAvg_Control_Type1(Filter_Average, S32);
S32 FilterAvg_Control_Type2(Filter_Average, S32);

struct Filter_Avg
{
    U8 Type;            // This variable is initialized with TYPE_ID during _New() function and helps to validate the structure(object) used in functions

    U32 AvgCount;       // number of values in average buffer
    U32 AvgPeriod;      // time period (ms) which buffer covers; must be multiple of TimeStep x avgCount x n.
    U32 TimeStep;       // function calling time step(scantime) in [ms]
    U32 Divider;        // when value needs to updated only after every "n" function calls, Divider == "n"
    U32 Sampler;        // counts function calls when Divider > 1
    S32 Output;
    S64 Sum;
    S32* Buffer;        // pointer to buffer for holding the values
    S32((*ControlFunctionPointer)(Filter_Average, S32));        // pointer to the control function
};


// Validate object reference; Returns FALSE if invalid object reference
static BOOL FilterAvg_ValidateObject(Filter_Average filter)
{
    if (filter->Type == 130) { return true; }
    else { return false; }
}


S32 FilterAvg_Reset(Filter_Average filter, S32 resetValue)
{
    // set entire buffer to defined value
    int i;
    for (i = (filter->AvgCount - 1); i > -1; i--)
    {
        (filter->Buffer)[i] = resetValue;
    }
    filter->Sampler = 0;
    filter->Sum = resetValue * filter->AvgCount;
    filter->Output = resetValue;

    return 0;
}


// Load parameters
S32 FilterAvg_LoadParameters(Filter_Average filter, U32 avgCount, U32 avgPeriod)
{
	if (!FilterAvg_ValidateObject(filter)) { return -1; }         // pointer to invalid object structure


    if (avgCount > _S32MAX || avgCount < 1) { return -2; }              // avgCount illegal value
    // calculate Divider value
    S32 divider = avgPeriod / avgCount / filter->TimeStep;

    // check if avgPeriod divides perfectly - if "n" is integer
    if ((avgPeriod / avgCount) % filter->TimeStep == 0)
    {
        // check if avgPeriod equals TimeStep x avgCount, it means Divider = 1 and value is updated with each function call
        if (divider == 1)
        {
            filter->ControlFunctionPointer = FilterAvg_Control_Type1;
        }
        else
        {
            filter->ControlFunctionPointer = FilterAvg_Control_Type2;
        }
        filter->Divider = divider;
    }
    else
    {
#ifdef FILTAVG_DEBUG
        OS_com_printf("\navgPeriod is not multiple of TimeStep x avgCount\n");
#endif
        return -3;      // avgPeriod is not exactly multiple of TimeStep x avgCount x n
    }
    
    // check if avgCount changed, then need to create different size buffer
    if (avgCount != filter->AvgCount)
    {
        int result = OS_Deallocate_Memory(filter->Buffer);
        if (result != OS_SUCCESS)
        {
#ifdef FILTAVG_DEBUG
            OS_com_printf("\nDeallocation of filter buffer failed\n");
#endif
            return result;
        }

        void* buffer;
        result = OS_Allocate_Memory(GetMemPool(), &buffer, sizeof(S32) * avgCount, OS_NO_SUSPEND);
        if (result != OS_SUCCESS)
        {
#ifdef FILTAVG_DEBUG
            OS_com_printf("\nNew filter buffer allocation failed\n");
#endif
            return NULL;
        }
        ((Filter_Average)filter)->Buffer = (S32*)buffer;
    }
    
    filter->AvgCount = avgCount;
    filter->AvgPeriod = avgPeriod;
    
    FilterAvg_Reset(filter, filter->Output);

#ifdef FILTAVG_DEBUG
    OS_com_printf("\nAvgCount: %d\n", filter->AvgCount);
    OS_com_printf("\nAvgPeriod: %d\n", filter->AvgPeriod);
    OS_com_printf("\nDivider: %d\n", filter->Divider);
    OS_com_printf("\nSampler: %d\n", filter->Sampler);
    OS_com_printf("\nBuffer[0]: %d\n", filter->Buffer[0]);
    OS_com_printf("\nBuffer[1]: %d\n", filter->Buffer[1]);
    OS_com_printf("\nBuffer[2]: %d\n", filter->Buffer[2]);
#endif

    return 0;
}


// Creates new Filter_Average with specified parameters. Returns pointer to the new Filter_Average structure. Returns NULL in case of error.
Filter_Average FilterAvg_New(U32 avgCount, U32 avgPeriod, U32 timeStep)
{
    void* filter;
    void* buffer;

    int result = OS_Allocate_Memory(GetMemPool(), &filter, sizeof(struct Filter_Avg), OS_NO_SUSPEND);
    if (result != OS_SUCCESS) { return NULL; }
    // reserve memory for buffer
    result = OS_Allocate_Memory(GetMemPool(), &buffer, sizeof(S32) * avgCount, OS_NO_SUSPEND);
    if (result != OS_SUCCESS) { return NULL; }
    ((Filter_Average)filter)->Buffer = (S32*)buffer;
    
    ((Filter_Average)filter)->Type = 130;
    if (timeStep < 1) { return NULL; }  // invalid timeStep value
    ((Filter_Average)filter)->TimeStep = timeStep;
    FilterAvg_LoadParameters((Filter_Average)filter, avgCount, avgPeriod);
    FilterAvg_Reset((Filter_Average)filter, 0);

    return (Filter_Average)filter;
}


// Free memory and dispose the structure.
S32 FilterAvg_Dispose(Filter_Average filter)
{
	if (!FilterAvg_ValidateObject(filter)) { return -1; }         // pointer to invalid object structure
    int result = OS_Deallocate_Memory(filter->Buffer);
    if (result != OS_SUCCESS) { return result; }
    else { return 0; }
    result = OS_Deallocate_Memory(filter);
    if (result != OS_SUCCESS) { return result; }
    else { return 0; }
}


S32 FilterAvg_Control(Filter_Average filter, S32 Input)
{
    return (*filter->ControlFunctionPointer)(filter, Input);
}


S32 FilterAvg_Control_Type1(Filter_Average filter, S32 Input)
{
	if (!FilterAvg_ValidateObject(filter)) { return -1; }         // pointer to invalid object structure

    filter->Sum -= (filter->Buffer)[filter->AvgCount - 1];
    int i;
    for (i = (filter->AvgCount - 1); i > 0; i--)
    {
        (filter->Buffer)[i] = (filter->Buffer)[i - 1];
    }
    (filter->Buffer)[0] = Input;
    filter->Sum += Input;
    filter->Output = filter->Sum / filter->AvgCount;

#ifdef FILTAVG_DEBUG
    OS_com_printf("\nFilterAvg_Control_Type1 - Output: %d\n", filter->Output);
#endif

    return filter->Output;
}


S32 FilterAvg_Control_Type2(Filter_Average filter, S32 Input)
{
    if (!FilterAvg_ValidateObject(filter)) { return -1; }         // pointer to invalid object structure

    filter->Sampler++;
    if (filter->Sampler >= filter->Divider)
    {
#ifdef FILTAVG_DEBUG
        OS_com_printf("\nFilterAvg_Control_Type2 - Sampler: %d\n", filter->Sampler);
#endif

        filter->Sampler = 0;
        return FilterAvg_Control_Type1(filter, Input);
    }

    return filter->Output;
}


S32 FilterAvg_GetAvg(Filter_Average filter)
{
    return filter->Output;
}
