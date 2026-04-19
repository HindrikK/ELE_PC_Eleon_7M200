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

//****************************************************************************
//
// LIST FUNCTIONS FOR HOLDING VOID POINTERS OF SIZE SPECIFIED BY ELEMENT SIZE
// DYNAMIC MEMORY HANDLING FOR LIST ELEMENTS
//
//****************************************************************************

#ifndef FILE_LIST_H
#define FILE_LIST_H

#include <lib_main.h>


typedef struct ListStruct* List;


List List_New(int/*capacity*/, int/*elementsize*/);				// Creates new list and returns pointer to this list.
void* List_Select(List, int/*index*/);							// Returns pointer to the element in specific index. Returns 0, if no element on this index.
S32 List_Add(List, void*/*element*/);							// Adds an element to the end of the list. Returns the index of new element in list. Returns -1 if error.
//BOOL List_Insert(List, void*/*element*/, int/*index*/);			// Inserts an element into list, to specified index.
S32 List_Remove(List, int/*index*/);							// Remove an element from specified index in list.
S32 List_Clear(List);											// Removes all elements from the list.
S32 List_Trim(List);											// Removes all empty indexes(gaps) from list. Returns the number of empty indexes removed.
S32 List_Count(List);											// Returns the number of elements in list.
S32 List_First(List);											// Returns the index of first element in list.
S32 List_Last(List);											// Returns the index of last element in list.
S32 List_Prev(List, int/*index*/);								// Returns the index of previous element in list.
S32 List_Next(List, int/*index*/);								// Returns the index of next element in list.
S32 List_Find(List, void*/*element*/);							// Returns the index of element in list. Returns 0 when element not found.

#endif
