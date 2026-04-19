//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <List.h>


typedef struct
{
	int Prev;			// Index of previous element in list
	int Next;			// Index of next element in list
	void* Value;		// Pointer to element value/data
}ListElement;


struct ListStruct
{
	int Capacity;					// Max number of elements list
	int Count;						// Number of elements in list
	int First;						// Index of first element in list
	int Last;						// Index of last element in list
	int ElementSize;				// Size of element in bytes
	ListElement* Elements[];		// Pointers to all elements in list
};



// Creates new list and returns pointer to this list.
List List_New(int capacity, int elementsize)
{
	List list;

	if (capacity > 0 && elementsize > 0)
	{
		int result = OS_Allocate_Memory(GetMemPool(), (void**)&list, ((sizeof(struct ListStruct) + (sizeof(ListElement*) * capacity))), OS_NO_SUSPEND);
		if (result != OS_SUCCESS) return NULL;
	}
	else
	{
		return NULL;
	}

	//if (list == NULL) { return NULL; }

	list->Capacity = capacity;
	list->Count = 0;
	list->First = 0;
	list->Last = 0;
	list->ElementSize = elementsize;

	//set all element pointers to NULL
	int i;
	for (i = 0; i < capacity; i++)
	{
		list->Elements[i] = NULL;
	}

	return list;
}


// Returns pointer to the element (value) in specific index.
void* List_Select(List list, int index)
{
	if (index < 0 || index > (list->Capacity-1)) { return NULL; }  // invalid index
	if (list->Elements[index] == NULL) { return NULL; }            // element does not exist
	return list->Elements[index]->Value;
}


// Adds an element to the end of the list. Returns the index of new element in list. Returns -1 if error.
S32 List_Add(List list, void* element)
{
	if (list == NULL || element == NULL) { return -1; }   // invalid input parameters
	if (list->Count == list-> Capacity) { return -1; }    // list is full
	
	ListElement* structPointer;
	int result = OS_Allocate_Memory(GetMemPool(), (void**)&structPointer, sizeof(ListElement), OS_NO_SUSPEND);	// allocate memory for new list element struct
	if (result != OS_SUCCESS) return -1;
	if (structPointer == NULL) { return -1; }  // failed to allocate memory for new element
	
	list->Count++;
	if (list->Count == 1)
	{
		list->Elements[0] = structPointer;		// set pointer for new element
		list->Elements[0]->Prev = 0;
		list->Elements[0]->Next = 0;
		list->Elements[0]->Value = element;
		return 0;
	}

	list->Last++;
	list->Elements[list->Last] = structPointer;		// set pointer for new element
	// reassign Prev and Next values for elements that are affected
	list->Elements[list->First]->Prev = list->Last;
	list->Elements[list->Last - 1]->Next = list->Last;
	list->Elements[list->Last]->Prev = list->Last - 1;
	list->Elements[list->Last]->Next = list->First;
	list->Elements[list->Last]->Value = element;

	return list->Last;
}


//// Inserts an element into list, to specified index.
//BOOL List_Insert(List list, void* element, int index)
//{
//	if (list == NULL || element == NULL || index >= list->Capacity) { return false; } // invalid input parameters
//
//	ListElement* structPointer;
//	int result = OS_Allocate_Memory(GetMemPool(), (void**)&structPointer, sizeof(ListElement), OS_NO_SUSPEND);	// allocate memory for new list element struct
//	if (result != OS_SUCCESS) return false;
//
//	if (structPointer == NULL) { return false; }  // failed to allocate memory for new element
//
//	list->Elements[index] = structPointer; // set pointer
//	list->Count++;
//
//	structPointer->Value = element;  // set pointer to element value
//	structPointer->Index = index;
//	structPointer->Prev = 0;
//	structPointer->Next = 0;
//
//	int i;
//	// look for index of previous existing element in list
//	for (i = index - 1; i >= 0; i--)
//	{
//		if (list->Elements[i] > 0)
//		{
//			structPointer->Prev = i;
//			list->Elements[i]->Next = index;	// update the Next value of previous element
//			i = -1;	// exit FOR loop
//		}
//	}
//
//
//	// look for index of next existing element in list
//	for (i = index + 1; i < list->Capacity; i++)
//	{
//		if (list->Elements[i] > 0)
//		{
//			structPointer->Next = i;
//			list->Elements[i]->Prev = index;	// update the Prev value of next element
//			i = list->Capacity;	// exit FOR loop
//		}
//	}
//
//	if (index < list->First) { list->First = index; }
//	if (index > list->Last) { list->Last = index; }
//
//
//	return true;
//}


// Remove an element from specified index in list.
S32 List_Remove(List list, int index)
{
	if (list->Elements[index] != NULL)	// check if element exists on that index
	{
		if (index == list->First) list->First = list->Elements[index]->Next;
		if (index == list->Last) list->Last = list->Elements[index]->Prev;
		int prev = list->Elements[index]->Prev;
		int next = list->Elements[index]->Next;
		list->Elements[prev]->Next = next;
		list->Elements[next]->Prev = prev;

		//OS_Deallocate_Memory(list->Elements[index]->Value); // free element data memory
		OS_Deallocate_Memory(list->Elements[index]);        // free element structure memory
		list->Elements[index] = NULL;
		list->Count--;
		if (list->Count == 0)
		{
			list->First = 0;
			list->Last = 0;
		}
		return 0;
	}
	else
	{
		return -1;  // can not remove, no element on that index
	}
}


// Removes all elements from the list. Returns num of elements removed.
S32 List_Clear(List list)
{
	int listCount = list->Count;
	int i;
	for (i = 0; i < list->Capacity; i++)
	{
		if (list->Elements[i] != NULL)
		{
			OS_Deallocate_Memory(list->Elements[i]);        // free element structure memory
			list->Elements[i] = NULL;
		}
	}

	list->Count = 0;
	list->First = 0;
	list->Last = 0;

	return listCount;
}


// Removes all empty indexes(gaps) from list. Returns the number of empty indexes removed.
S32 List_Trim(List list)
{
	if (list->Count == 0) return 0;		// don't trim, if no elements in list

	// check if and how many empty slots exist inside list
	int trimCount = list->Last + 1 - list->Count;
	if (trimCount == 0) return 0;	// no need to trim
	
	int lastIndex = list->Last;
	list->Last = list->Count - 1;
	
	// set element at 0 index
	if (list->First != 0)
	{
		list->Elements[0] = list->Elements[list->First];
		list->Elements[list->First] = NULL;
		list->First = 0;
	}
	list->Elements[0]->Prev = list->Last;
	list->Elements[0]->Next = 0;
	
	int j = 1;	// counts the trimmed index
	int i;
	for (i = 1; i < lastIndex; i++)
	{
		if (list->Elements[i] != NULL)
		{
			list->Elements[j] = list->Elements[i];
			if (j != i) list->Elements[i] = NULL;	// prevents erasing itself when no gaps removed yet (j == i)
			list->Elements[j]->Prev = j - 1;
			list->Elements[j - 1]->Next = j;
			j++;
		}
	}

	// set last element
	if (list->Count > 1)
	{
		list->Elements[list->Last] = list->Elements[lastIndex];
		list->Elements[list->Last]->Prev = list->Last - 1;
		list->Elements[list->Last]->Next = 0;
		list->Elements[list->Last - 1]->Next = list->Last;
	}
	list->Elements[lastIndex] = NULL;

	return trimCount;
}


// Returns the number of elements in list.
S32 List_Count(List list)
{
	return list->Count;
}


// Returns the index of first element in list.
S32 List_First(List list)
{
	return list->First;
}


// Returns the index of last element in list.
S32 List_Last(List list)
{
	return list->Last;
}


// Returns the index of previous element in list.
S32 List_Prev(List list, int index)
{
	return list->Elements[index]->Prev;
}


// Returns the index of next element in list.
S32 List_Next(List list, int index)
{
	return list->Elements[index]->Next;
}


// Returns the index of element in list. Returns -1 when element not found.
S32 List_Find(List list, void* element)
{
	if (list == NULL || element == NULL) { return -2; } // invalid input parameters
	
	int count = 0;
	int i;
	for (i = 0; i <= list->Last; i++)
	{
		if (list->Elements[i] != NULL)
		{
			count++;
			if (list->Elements[i]->Value == element) return i;
			if (count >= list->Count) return -3;
		}
	}
   
   return -1;
}
