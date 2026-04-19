//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_BUFFIFOS32_H
#define FILE_BUFFIFOS32_H

#include <lib_main.h>


typedef struct BufferFIFOS32_Struct* BufferFIFOS32;


BufferFIFOS32 BufferFIFOS32_New(int/*capacity*/);				// Creates new buffer and returns pointer for this.
S32 BufferFIFOS32_Select(BufferFIFOS32, int/*index*/);			// Returns the value in specific index. Returns 0 when index is out of range.
BOOL BufferFIFOS32_Push(BufferFIFOS32, S32/*value*/);			// Insert new value into buffer.
S32 BufferFIFOS32_Pop(BufferFIFOS32);							// Returns value from buffer.
S32 BufferFIFOS32_PushPop(BufferFIFOS32, S32/*value*/);			// Does the push and pop command in same function.
BOOL BufferFIFOS32_Clear(BufferFIFOS32);						// Removes all values from buffer.
S32 BufferFIFOS32_Count(BufferFIFOS32);							// Returns the number of values in buffer.
S32 BufferFIFOS32_Capacity(BufferFIFOS32);						// Returns the max size of buffer.
S32 BufferFIFOS32_First(BufferFIFOS32);							// Returns first value in buffer.
S32 BufferFIFOS32_Last(BufferFIFOS32);							// Returns last value in buffer.

#endif
