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
#ifndef FILE_BUFFER_FIFO_H
#define FILE_BUFFER_FIFO_H

#include <lib_main.h>


#define BUFFIFO_USE_MINMAX		   // by defining this, add calculation of min and max values in buffer
//#define BUFFIFO_USE_SUMAVERAGE	// by defining this, add calculation of buffer sum and average value

typedef struct BufferFIFO_Struct* BufferFIFO;


BufferFIFO BufferFIFO_New(int/*capacity*/);			   // Creates new buffer and returns pointer for this.
F32 BufferFIFO_Select(BufferFIFO, int/*index*/);	   // Returns the value in specific index. Returns 0 when index is out of range.
BOOL BufferFIFO_Push(BufferFIFO, F32/*value*/);		   // Insert new value into buffer.
F32 BufferFIFO_Pop(BufferFIFO);							   // Returns value from buffer.
F32 BufferFIFO_PushPop(BufferFIFO, F32/*value*/);	   // Does the push and pop command in same function.
BOOL BufferFIFO_Clear(BufferFIFO);						// Removes all values from buffer.
S32 BufferFIFO_Count(BufferFIFO);						// Returns the number of values in buffer.
S32 BufferFIFO_Capacity(BufferFIFO);					// Returns the max size of buffer.
F32 BufferFIFO_First(BufferFIFO);						// Returns first value in buffer.
F32 BufferFIFO_Last(BufferFIFO);							// Returns last value in buffer.
#ifdef BUFFIFO_USE_MINMAX
F32 BufferFIFO_Max(BufferFIFO);
F32 BufferFIFO_Min(BufferFIFO);
#endif
#ifdef BUFFIFO_USE_SUMAVERAGE
F32 BufferFIFO_Average(BufferFIFO);
F32 BufferFIFO_Sum(BufferFIFO);
#endif

#endif
