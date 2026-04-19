//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <Buffer_FIFO.h>


struct BufferFIFO_Struct
{
	int MagicNumber;			// for structure verification
	int Capacity;				// Max number of values in buffer
	int Count;					// Number of values in buffer
	F32* BufferArray;			// this is pointer to buffer array

	// using circular buffer method, thats why we need buffer beginning and end indexes
	int push_Index;
	int pop_Index;
   
   #ifdef BUFFIFO_USE_MINMAX
   F32 Min;
   F32 Max;
   #endif
   
   #ifdef BUFFIFO_USE_SUMAVERAGE
   F32 Average;
   F32 Sum;
   #endif
};



// Creates new buffer and returns pointer for this.
BufferFIFO BufferFIFO_New(int capacity)
{
	BufferFIFO buffer;

	if (capacity < 3) return NULL;	// min capacity is 3

	// reserve memory for buffer struct
	int result = OS_Allocate_Memory(GetMemPool(), (void**)&buffer, sizeof(struct BufferFIFO_Struct), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) return NULL;

	buffer->MagicNumber = 12345;
	buffer->Capacity = capacity;
	buffer->Count = 0;
	buffer->push_Index = 0;
	buffer->pop_Index = 0;
   #ifdef BUFFIFO_USE_MINMAX
   buffer->Min = 0;
   buffer->Max = 0;
   #endif
   #ifdef BUFFIFO_USE_SUMAVERAGE
   buffer->Sum = 0;
   buffer->Average = 0;
   #endif

	// reserve memory for BufferArray
	result = OS_Allocate_Memory(GetMemPool(), (void**)&buffer->BufferArray, sizeof(F32) * capacity, OS_NO_SUSPEND);
	if (result != OS_SUCCESS) return NULL;

	return buffer;
}


// Returns the value in specific index. Returns 0 when index is out of range.
F32 BufferFIFO_Select(BufferFIFO buffer, int index)
{
	if (index >= buffer->Count) { return 0; }  // check if index is in range
	int select_index = buffer->pop_Index - index;
	if (select_index < 0) select_index = buffer->Capacity + select_index;
	return buffer->BufferArray[select_index];
}


// Find min value in buffer
F32 BufferFIFO_FindMin(BufferFIFO buffer)
{
   F32 result = F32_MAX;
   F32 value;
   U16 i;
   for(i = 0; i < buffer->Count; i++)
   {
      value = BufferFIFO_Select(buffer, i);
      if(value < result)
      {
         result = value;
      }
   }
   return result;
}


// Find max value in buffer
F32 BufferFIFO_FindMax(BufferFIFO buffer)
{
   F32 result = F32_MIN;
   F32 value;
   U16 i;
   for(i = 0; i < buffer->Count; i++)
   {
      value = BufferFIFO_Select(buffer, i);
      if(value > result)
      {
         result = value;
      }
   }
   return result;
}


// Insert new value into buffer.
BOOL BufferFIFO_Push(BufferFIFO buffer, F32 value)
{
	// CHECK FOR MAGIC NUMBER IN BUFFER STRUCTURE
	if (buffer->MagicNumber != 12345) return false;

	if (buffer->Count < buffer->Capacity)
	{
		buffer->Count++;
		buffer->BufferArray[buffer->push_Index] = value;
		//*(buffer->BufferArray + buffer->push_Index) = value;
		buffer->push_Index++;
		if (buffer->push_Index >= buffer->Capacity) buffer->push_Index = 0;
      
      #ifdef BUFFIFO_USE_MINMAX
      if(value < buffer->Min) buffer->Min = value;
      else if(value > buffer->Max) buffer->Max = value;
      #endif
      #ifdef BUFFIFO_USE_SUMAVERAGE
      buffer->Sum+= value;
      buffer->Average = buffer->Sum / buffer->Count;
      #endif
      
		return true;
	}
	
	return false;
}


// Returns value from buffer.
F32 BufferFIFO_Pop(BufferFIFO buffer)
{
	// CHECK FOR MAGIC NUMBER IN BUFFER STRUCTURE
	if (buffer->MagicNumber != 12345) return 0;

	if (buffer->Count > 0)
	{
		F32 value = buffer->BufferArray[buffer->pop_Index];
		//S32 value = *(buffer->BufferArray + buffer->pop_Index);
		buffer->Count--;
		buffer->pop_Index++;
		if (buffer->pop_Index >= buffer->Capacity) buffer->pop_Index = 0;
      
      #ifdef BUFFIFO_USE_MINMAX
      // in case min/max value popped, then need to find new min/max
      if(value == buffer->Min || value == buffer->Max)
      {
         buffer->Min = BufferFIFO_FindMin(buffer);
         buffer->Max = BufferFIFO_FindMax(buffer);
      }
      #endif
      #ifdef BUFFIFO_USE_SUMAVERAGE
      buffer->Sum-= value;
      buffer->Average = buffer->Sum / buffer->Count;
      #endif
      
		return value;
	}

	return 0;
}


// Does the push and pop command in same function.
F32 BufferFIFO_PushPop(BufferFIFO buffer, F32 value)
{
	F32 x = BufferFIFO_Pop(buffer);
	if ( BufferFIFO_Push(buffer, value) )
	{
		return x;
	}

	return 0;
}


// Removes all values from buffer.
BOOL BufferFIFO_Clear(BufferFIFO buffer)
{
	// CHECK FOR MAGIC NUMBER IN BUFFER STRUCTURE
	if (buffer->MagicNumber != 12345) return false;
	
	buffer->Count = 0;
	buffer->pop_Index = 0;
	buffer->push_Index = 0;
   
   #ifdef BUFFIFO_USE_MINMAX
   buffer->Min = 0;
   buffer->Max = 0;
   #endif
   #ifdef BUFFIFO_USE_SUMAVERAGE
   buffer->Sum = 0;
   buffer->Average = 0;
   #endif
	
	return true;
}


// Returns the number of values in buffer.
S32 BufferFIFO_Count(BufferFIFO buffer)
{
	return buffer->Count;
}


// Returns the max size of buffer.
S32 BufferFIFO_Capacity(BufferFIFO buffer)
{
	return buffer->Capacity;
}


// Returns first value in buffer.
F32 BufferFIFO_First(BufferFIFO buffer)
{
	return BufferFIFO_Select(buffer, 0);
}


// Returns last value in buffer.
F32 BufferFIFO_Last(BufferFIFO buffer)
{
	return BufferFIFO_Select(buffer, buffer->Count - 1);
}


#ifdef BUFFIFO_USE_MINMAX
// Returns max value in buffer.
F32 BufferFIFO_Max(BufferFIFO buffer)
{
	return buffer->Max;
}


// Returns min value in buffer.
F32 BufferFIFO_Min(BufferFIFO buffer)
{
	return buffer->Min;
}
#endif


#ifdef BUFFIFO_USE_SUMAVERAGE
// Returns average value in buffer.
F32 BufferFIFO_Max(BufferFIFO buffer)
{
	return buffer->Average;
}


// Returns Sum value in buffer.
F32 BufferFIFO_Sum(BufferFIFO buffer)
{
	return buffer->Sum;
}
#endif
