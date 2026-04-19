//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <Buffer_FIFO_S32.h>


struct BufferFIFOS32_Struct
{
	int MagicNumber;			// for structure verification
	int Capacity;				// Max number of values in buffer
	int Count;					// Number of values in buffer
	S32* BufferArray;			// this is pointer to buffer array

	// using circular buffer method, thats why we need buffer beginning and end indexes
	int push_Index;
	int pop_Index;
};



// Creates new buffer and returns pointer for this.
BufferFIFOS32 BufferFIFOS32_New(int capacity)
{
	BufferFIFOS32 buffer;

	if (capacity < 3) return NULL;	// min capacity is 3

	// reserve memory for buffer struct
	int result = OS_Allocate_Memory(GetMemPool(), (void**)&buffer, sizeof(struct BufferFIFOS32_Struct), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) return NULL;

	buffer->MagicNumber = 12345;
	buffer->Capacity = capacity;
	buffer->Count = 0;
	buffer->push_Index = 0;
	buffer->pop_Index = 0;

	// reserve memory for BufferArray
	result = OS_Allocate_Memory(GetMemPool(), (void**)&buffer->BufferArray, sizeof(S32) * capacity, OS_NO_SUSPEND);
	if (result != OS_SUCCESS) return NULL;


	return buffer;
}


// Returns the value in specific index. Returns 0 when index is out of range.
S32 BufferFIFOS32_Select(BufferFIFOS32 buffer, int index)
{
	if (index >= buffer->Count) { return 0; }  // check if index is in range
	int select_index = buffer->pop_Index - index;
	if (select_index < 0) select_index = buffer->Capacity + select_index;
	return buffer->BufferArray[select_index];
}


// Insert new value into buffer.
BOOL BufferFIFOS32_Push(BufferFIFOS32 buffer, S32 value)
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
		return true;
	}
	
	return false;
}


// Returns value from buffer.
S32 BufferFIFOS32_Pop(BufferFIFOS32 buffer)
{
	// CHECK FOR MAGIC NUMBER IN BUFFER STRUCTURE
	if (buffer->MagicNumber != 12345) return 0;

	if (buffer->Count > 0)
	{
		S32 value = buffer->BufferArray[buffer->pop_Index];
		//S32 value = *(buffer->BufferArray + buffer->pop_Index);
		buffer->Count--;
		buffer->pop_Index++;
		if (buffer->pop_Index >= buffer->Capacity) buffer->pop_Index = 0;
		return value;
	}

	return 0;
}


// Does the push and pop command in same function.
S32 BufferFIFOS32_PushPop(BufferFIFOS32 buffer, S32 value)
{
	S32 x = BufferFIFOS32_Pop(buffer);
	if ( BufferFIFOS32_Push(buffer, value) )
	{
		return x;
	}

	return 0;
}


// Removes all values from buffer.
BOOL BufferFIFOS32_Clear(BufferFIFOS32 buffer)
{
	// CHECK FOR MAGIC NUMBER IN BUFFER STRUCTURE
	if (buffer->MagicNumber != 12345) return false;
	
	buffer->Count = 0;
	buffer->pop_Index = 0;
	buffer->push_Index = 0;
	
	return true;
}


// Returns the number of values in buffer.
S32 BufferFIFOS32_Count(BufferFIFOS32 buffer)
{
	return buffer->Count;
}


// Returns the max size of buffer.
S32 BufferFIFOS32_Capacity(BufferFIFOS32 buffer)
{
	return buffer->Capacity;
}


// Returns first value in buffer.
S32 BufferFIFOS32_First(BufferFIFOS32 buffer)
{
	return BufferFIFOS32_Select(buffer, 0);
}


// Returns last value in buffer.
S32 BufferFIFOS32_Last(BufferFIFOS32 buffer)
{
	return BufferFIFOS32_Select(buffer, buffer->Count - 1);
}
