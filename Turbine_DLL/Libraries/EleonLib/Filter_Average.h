//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_FILTER_AVERAGE_H
#define FILE_FILTER_AVERAGE_H

#include <lib_main.h>

typedef struct Filter_Avg* Filter_Average;

//*******************************************************************************************
// Calculates Moving Average
// Must be called periodically
// Alows to define number of values in average buffer and time pweriod over which averaging takes place
//
// avgCount - number of values in average buffer
// avgPeriod - time period (ms) which buffer covers; must be multiple of TimeStep x avgCount x n
// timeStep - function calling time step(scantime) in [ms]
// 
//*******************************************************************************************


S32 FilterAvg_LoadParameters(Filter_Average/*filter*/, U32/*avgCount*/, U32/*avgPeriod*/);		// Load parameters
S32 FilterAvg_Reset(Filter_Average/*filter*/, S32/*resetValue*/);								// Reset output value
Filter_Average FilterAvg_New(U32/*avgCount*/, U32/*avgPeriod*/, U32/*timeStep*/);				// Creates new Filter_Average with specified parameters. Returns pointer to the new Filter_Average structure. Returns NULL in case of error.
S32 FilterAvg_Dispose(Filter_Average/*filter*/);												// Free memory and dispose the structure.
S32 FilterAvg_Control(Filter_Average/*filter*/, S32/*Input*/);									// Returns and updates average value. Must be called periodically.
S32 FilterAvg_GetAvg(Filter_Average/*filter*/);													// Get average value without inserting new

#endif
