//********************************************************************
//
//            Copyright (c) 2006 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date: 2013/03/15 15:46:29 $
// $Author: MITA\ihn $
// $RCSfile: CATlib.c,v $
// $Revision: 1.3 $
//
//*******************************************************************
#include "CATlib.h"
#include "turbdef.h"

#ifndef EMULATOR

// Abstract: Get the name of the current task.
//
STATUS GetTaskName(char Name[9])
{
   OS_TASK *Task;
   DATA_ELEMENT Status;
   UNSIGNED ScheduledCount;
   OPTION Priority;
   OPTION Preempt;
   UNSIGNED TimeSlice;
   VOID *StackBase;
   UNSIGNED StackSize;
   UNSIGNED MinimumStack;

   Task = OS_Current_Task_Pointer();

   return OS_Task_Information(Task, Name, &Status, &ScheduledCount, &Priority, &Preempt,
                              &TimeSlice, &StackBase, &StackSize, &MinimumStack);
}

#endif // EMULATOR


// Abstract: Interface function
//
STATUS CopyU16(/*In*/ const CONVERSION_T Conversion, /*In*/ const U16 *SrcBuf, /*Out*/ U16 *DstBuf)
{
   U8 * Source = (U8*)SrcBuf;
   U8 * Destination = (U8*)DstBuf;

   switch (Conversion)
   {
      case HOST_TO_NETWORK:
      {
         Destination[0] = Source[HOST_LSB];
         Destination[1] = Source[HOST_MSB];
         break;
      }

      case NETWORK_TO_HOST:
      {
         Destination[HOST_LSB] = Source[0];
         Destination[HOST_MSB] = Source[1];
         break;
      }

      default:
      {
         return ERR_ETHCAT_ILLEGAL_CONVERSION_TYPE;
      }
   }

   return OS_SUCCESS;
}


// Abstract: Interface function
//
STATUS CopyU32(/*In*/ const CONVERSION_T Conversion, /*In*/ const U32 *SrcBuf, /*Out*/ U32 *DstBuf)
{
   U16 * Source = (U16*)SrcBuf;
   U16 * Destination = (U16*)DstBuf;

   switch (Conversion)
   {
      case HOST_TO_NETWORK:
      {
         if (OS_SUCCESS != CopyU16(Conversion, &Source[HOST_LSB], &Destination[0])) return ERR_ETHCAT_ILLEGAL_CONVERSION_TYPE;
         if (OS_SUCCESS != CopyU16(Conversion, &Source[HOST_MSB], &Destination[1])) return ERR_ETHCAT_ILLEGAL_CONVERSION_TYPE;
         break;
      }

      case NETWORK_TO_HOST:
      {
         if (OS_SUCCESS != CopyU16(Conversion, &Source[0], &Destination[HOST_LSB])) return ERR_ETHCAT_ILLEGAL_CONVERSION_TYPE;
         if (OS_SUCCESS != CopyU16(Conversion, &Source[1], &Destination[HOST_MSB])) return ERR_ETHCAT_ILLEGAL_CONVERSION_TYPE;
         break;
      }

      default:
      {
         return ERR_ETHCAT_ILLEGAL_CONVERSION_TYPE;
      }
   }

   return OS_SUCCESS;
}


// Abstract: Interface function
//
STATUS CopyS16(/*In*/ const CONVERSION_T Conversion, /*In*/ const S16 *SrcBuf, /*Out*/ S16 *DstBuf)
{
   return CopyU16(Conversion, (U16*)SrcBuf, (U16*)DstBuf);
}


// Abstract: Interface function
//
STATUS CopyS32(/*In*/ const CONVERSION_T Conversion, /*In*/ const S32 *SrcBuf, /*Out*/ S32 *DstBuf)
{
   return CopyU32(Conversion, (U32*)SrcBuf, (U32*)DstBuf);
}


// Abstract: Interface function
//
STATUS BufCmp(/*In*/ U32 DataSize,
              /*In*/ U8 * Buf1Ptr,
              /*In*/ U8 * Buf2Ptr,
              /*Out*/ U8 * DirtyBits)
{
   STATUS Status = OS_SUCCESS;
   U32 Split = 0;
   U32 SplitNdx = 0;

   if (0 == memcmp(Buf1Ptr, Buf2Ptr, DataSize))
   {
      // "DataSize" buffers are identical.
      memset(DirtyBits, 0, DataSize);
      return OS_SUCCESS;
   }
   else if (MIN_CHK_LIMIT >= DataSize)
   {
      // Minimum byte size buffers differ.
      memset(DirtyBits, 1, DataSize);
      return OS_SUCCESS;
   }

   // Buffers (larger than 1 byte) differ - divide and conqueror...
   // Compare left/first half of the buffers.

   Split = DataSize / 2;
   SplitNdx = DataSize - Split;

   Status = BufCmp(SplitNdx, Buf1Ptr, Buf2Ptr, DirtyBits);
   if (OS_SUCCESS != Status)
   {
      return Status;
   }

   // Compare right/last half of the buffers.
   Status = BufCmp(Split, &Buf1Ptr[SplitNdx], &Buf2Ptr[SplitNdx], &DirtyBits[SplitNdx]);
   if (OS_SUCCESS != Status)
   {
      return Status;
   }

   return OS_SUCCESS;
}


// Abstract: Interface function
//
STATUS RingBufCmp(/*In*/ U32 DataSize,
                  /*In*/ U8 * Buf1Addr, /*In*/ U32 Buf1Size, /*In*/ U8 *Buf1Ptr,
                  /*In*/ U8 * Buf2Addr, /*In*/ U32 Buf2Size, /*In*/ U8 *Buf2Ptr,
                  /*Out*/ U8 * DirtyBits)
{
   STATUS Status = OS_SUCCESS;
   U32 Buf1Cont = 0;
   U32 Buf2Cont = 0;
   U32 CmpSize = 0;
   U8 *Buf1Ptr2 = NULL;
   U8 *Buf2Ptr2 = NULL;
   U8 *DirtyBits2 = NULL;

   // If the one of the buffer pointers is NULL then the two
   // buffers are considered completely different.

   if (NULL == Buf1Ptr || NULL == Buf2Ptr)
   {
      memset(DirtyBits, 1, DataSize);
      return OS_SUCCESS;
   }

   // Determine the distance to the array boundary
   // for each of the specified buffers.

   Buf1Cont = &Buf1Addr[Buf1Size] - Buf1Ptr;
   Buf2Cont = &Buf2Addr[Buf2Size] - Buf2Ptr;

   // Get the smallest common denominator of buffer
   // sizes that can be compared at once.

   CmpSize = DataSize;

   if (CmpSize > Buf1Cont)
   {
      CmpSize = Buf1Cont;
   }

   if (CmpSize > Buf2Cont)
   {
      CmpSize = Buf2Cont;
   }

   // Now that CmpSize is fixed, locate the beginning of
   // the second segment of buffers to compare.
   // Also locate the matching position in the array of
   // DirtyBits.

   if (CmpSize == Buf1Cont)
   {
      Buf1Ptr2 = Buf1Addr; // This buffer wraps around.
   }
   else
   {
      Buf1Ptr2 = &Buf1Ptr[CmpSize];
   }

   if (CmpSize == Buf2Cont)
   {
      Buf2Ptr2 = Buf2Addr; // This buffer wraps around.
   }
   else
   {
      Buf2Ptr2 = &Buf2Ptr[CmpSize];
   }

   DirtyBits2 = &DirtyBits[CmpSize];

   // Do the comparisons.
   // First compare the initial stream of contiguous bytes.
   // In most cases, the entire comparison will be completed
   // after this step (assuming that the "DataSize" to
   // compare is much smaller then the buffer sizes).

   if (0 < CmpSize)
   {
      Status = BufCmp(CmpSize, Buf1Ptr, Buf2Ptr, DirtyBits);
   }

   if (OS_SUCCESS != Status)
   {
      return Status;
   }

   // See if there's more left to compare...

   CmpSize = DataSize - CmpSize;

   if (0 == CmpSize)
   {
      return OS_SUCCESS;
   }

   // There's more to compare. As _both_ buffers may wrap
   // around, this function will call itself recursively
   // to repeat the _entire_ setup again.
   // The level of recursion should never get any deeper
   // than two - counting the initial call to this function
   // as level zero - (since each buffer isn't supposed to
   // wrap around more than once ;)

   Status = RingBufCmp(CmpSize,
                       Buf1Addr, Buf1Size, Buf1Ptr2,
                       Buf2Addr, Buf2Size, Buf2Ptr2,
                       DirtyBits2);

   return Status;
}

