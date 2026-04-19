//*****************************PEPTOOL Header Start******************************
//
//                         Copyright © 2018 Mita-Teknik.
// This software may only be used with the Controllers delivered by Mita-Teknik
//
//*******************************************************************************
//
// $PEPTOOL version:9.0$
// $PEPTOOL file version:109$
//
//*******************************************************************************
//
// $Date: XXXX/XX/XX XX:XX:XX $
// $Author: DESKTOP-3H3JCEK\jaakl $
// $RCSfile: VarArrayMacros.h,v $
// $Revision: X.X $
//
//******************************PEPTOOL Header End*******************************

#ifndef __VAR_ARRAY_MACROS_H__
#define __VAR_ARRAY_MACROS_H__

#include <os_main.h>
#include <errcodes.h>
#include <lib_main.h>

#include "general.h"

#define LOCAL_VAR    1
#define BACKUP_VAR   2
#define PARAM_VAR    3

//========================================================================================================================

//=======================================Helper macros for managing arrays of Vdb=======================================
#define MK_STR(s) # s
#define GET_VDB_ARRAY_IDENT_NAME(ArrName)                   ArrName##Idents
#define GET_VAR_ARRAY_TYPE_VAR(ArrName)                     ArrName##Type
#define GET_VAR_ARRAY_LENGTH_VAR(ArrName)                   ArrName##Length
#define GET_VAR_ARRAY_TYPE(ArrType)                         TYPE_##ArrType
#define GET_VAR_LENGTH(VarType)                             (VarType & TYPE_LENGTH_MASK)
#define GET_VAR_ELEM_NAME(ArrName, Index)                   (GetArrayElemName(MK_STR(ArrName), Index))
#define GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName)               ArrName##Length##Txt
#define GET_VDB_ARRAY_SUBSCRIPTION_NAME(ArrName)            ArrName##Subscription
#define GET_VDB_ARRAY_SUBSCRIPTION_GROUP_NUMBER(ArrName)    ArrName##SubscriptionGroup


//***********************************************************************************************************************
//
// FUNCTION:
//
//    DETERMINE_VDB_ARRAY
//
// DESCRIPTION:
//
//    This macros determine array which will mapped to VarDB (ArrName_0, ArrName_1, ...) and
//    helper variables which need to create, read, write VarDB.
//
// INPUT:
//
//    ArrName : Name of array
//    ArrType : Type of array
//    Length  : Length of array
//
//***********************************************************************************************************************
#define DETERMINE_VDB_ARRAY(ArrName, ArrType, Length)                            \
   static ArrType* ArrName = 0;                                                  \
   static varid_t* GET_VDB_ARRAY_IDENT_NAME(ArrName) = 0;                        \
   static type_t   GET_VAR_ARRAY_TYPE_VAR(ArrName) = TYPE_##ArrType;             \
   static int      GET_VAR_ARRAY_LENGTH_VAR(ArrName) = 0;                        \
   static char     GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName)[] = MK_STR(Length);     \

//***********************************************************************************************************************
//
// FUNCTION:
//
//    DETERMINE_VDB_ARRAY_WITHOUT_REF
//
// DESCRIPTION:
//
//    This macros determine array which will mapped to VarDB (ArrName_0, ArrName_1, ...) and
//    helper variables which need to create, read, write VarDB.
//
// INPUT:
//
//    ArrName : Name of array
//    ArrType : Type of array
//    Length  : Length of array
//
//***********************************************************************************************************************
#define DETERMINE_VDB_ARRAY_WITHOUT_REF(ArrName, ArrType, Length)                \
   static varid_t* GET_VDB_ARRAY_IDENT_NAME(ArrName) = 0;                        \
   static type_t   GET_VAR_ARRAY_TYPE_VAR(ArrName) = TYPE_##ArrType;             \
   static int      GET_VAR_ARRAY_LENGTH_VAR(ArrName) = 0;                        \
   static char     GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName)[] = MK_STR(Length);     \

//***********************************************************************************************************************
//
// FUNCTION:
//
//    DETERMINE_VDB_ARRAY_TIME
//
// DESCRIPTION:
//
//    This macros determine array of time_t which will mapped to Vdb (ArrName_0, ArrName_1, ...) and
//    helper variables which need to create, read, write Vdb.
//
// INPUT:
//
//    ArrName : Name of array
//    Length  : Length of array
//
//***********************************************************************************************************************
#define DETERMINE_VDB_ARRAY_TIME(ArrName, Length)                                   \
   static time_t*  ArrName = 0;                                                     \
   static varid_t* GET_VDB_ARRAY_IDENT_NAME(ArrName) = 0;                           \
   static type_t   GET_VAR_ARRAY_TYPE_VAR(ArrName) = TYPE_TIME;                     \
   static int      GET_VAR_ARRAY_LENGTH_VAR(ArrName) = 0;                           \
   static char     GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName)[] = MK_STR(Length);        \

//***********************************************************************************************************************
//
// FUNCTION:
//
//    DETERMINE_VDB_ARRAY_TIME_WITHOUT_REF
//
// DESCRIPTION:
//
//    This macros determine array of time_t which will mapped to Vdb (ArrName_0, ArrName_1, ...) and
//    helper variables which need to create, read, write Vdb.
//
// INPUT:
//
//    ArrName : Name of array
//    Length  : Length of array
//
//***********************************************************************************************************************
#define DETERMINE_VDB_ARRAY_TIME_WITHOUT_REF(ArrName, Length)                       \
   static varid_t* GET_VDB_ARRAY_IDENT_NAME(ArrName) = 0;                           \
   static type_t   GET_VAR_ARRAY_TYPE_VAR(ArrName) = TYPE_TIME;                     \
   static int      GET_VAR_ARRAY_LENGTH_VAR(ArrName) = 0;                           \
   static char     GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName)[] = MK_STR(Length);        \

//***********************************************************************************************************************
//
// FUNCTION:
//
//    DETERMINE_VDB_ARRAY_STRING
//
// DESCRIPTION:
//
//    This macros determine array of strings which will mapped to Vdb (ArrName_0, ArrName_1, ...) and
//    helper variables which need to create, read, write Vdb.
//
// INPUT:
//
//    ArrName   : Name of array
//    StrLength : Length of string
//    Length    : Length of array
//
//***********************************************************************************************************************
#define DETERMINE_VDB_ARRAY_STRING(ArrName, StrLength, Length)                     \
   static char     (*ArrName)[StrLength] = 0;                                      \
   static varid_t* GET_VDB_ARRAY_IDENT_NAME(ArrName) = 0;                          \
   static type_t   GET_VAR_ARRAY_TYPE_VAR(ArrName) = TYPE_STRING + StrLength - 1;  \
   static int      GET_VAR_ARRAY_LENGTH_VAR(ArrName) = 0;                          \
   static char     GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName)[] = MK_STR(Length);       \

//***********************************************************************************************************************
//
// FUNCTION:
//
//    DETERMINE_VDB_ARRAY_STRING_WITHOUT_REF
//
// DESCRIPTION:
//
//    This macros determine array of strings which will mapped to Vdb (ArrName_0, ArrName_1, ...) and
//    helper variables which need to create, read, write Vdb.
//
// INPUT:
//
//    ArrName   : Name of array
//    StrLength : Length of string
//    Length    : Length of array
//
//***********************************************************************************************************************
#define DETERMINE_VDB_ARRAY_STRING_WITHOUT_REF(ArrName, StrLength, Length)   \
   static varid_t* GET_VDB_ARRAY_IDENT_NAME(ArrName) = 0;                          \
   static type_t   GET_VAR_ARRAY_TYPE_VAR(ArrName) = TYPE_STRING + StrLength - 1;  \
   static int      GET_VAR_ARRAY_LENGTH_VAR(ArrName) = 0;                          \
   static char     GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName)[] = MK_STR(Length);       \


//***********************************************************************************************************************
//
// FUNCTION:
//
//    SUBSCRIBE_VDB_ARRAY
//
// DESCRIPTION:
//
//    This macros subscribe multiplexed variable to subscription group.
//
// INPUT:
//
//    pPool        : Memory pool
//    ArrName      : Name of array
//    pGroupIndex  : Subscription group index
//    FunctionName : Function name
//    Status       : Status
//
// OUTPUT:
//    Status       : Status of execution
//
//***********************************************************************************************************************
#define SUBSCRIBE_VDB_ARRAY(pPool, ArrName, pGroupIndex, FunctionName, Status)                                         \
   {                                                                                                                   \
      if (GET_VAR_ARRAY_LENGTH_VAR(ArrName) == 0)                                                                      \
      {                                                                                                                \
         GET_VDB_ARRAY_SUBSCRIPTION_NAME(ArrName) = NULL;                                                              \
      }                                                                                                                \
      else                                                                                                             \
      {                                                                                                                \
         Status = OS_Allocate_Memory(pPool,                                                                            \
                                     (void*)(&GET_VDB_ARRAY_SUBSCRIPTION_NAME(ArrName)),                               \
                                     sizeof(SUBSCRIPTION) * GET_VAR_ARRAY_LENGTH_VAR(ArrName),                         \
                                     OS_NO_SUSPEND);                                                                   \
         if (Status != OS_SUCCESS)                                                                                     \
         {                                                                                                             \
            AppDebugLog(4444, "SUBSCRIBE_VDB_ARRAY: %s Err Alloc Mem %d", MK_STR(ArrName), Status);                    \
         }                                                                                                             \
         else                                                                                                          \
         {                                                                                                             \
            U8 index;                                                                                                  \
            for (index = 0; index < GET_VAR_ARRAY_LENGTH_VAR(ArrName); index++)                                        \
            {                                                                                                          \
               Status = OS_SubHandl_SubscribeFunctionWithRef(&GET_VDB_ARRAY_SUBSCRIPTION_NAME(ArrName)[index],         \
                                                             1,                                                        \
                                                             &GET_VDB_ARRAY_IDENT_NAME(ArrName)[index],                \
                                                             pGroupIndex,                                              \
                                                             pGroupIndex,                                              \
                                                             FunctionName);                                            \
               if (Status != OS_SUCCESS)                                                                               \
               {                                                                                                       \
                  AppDebugLog(4444, "SUBSCRIBE_VDB_ARRAY: El %d Err Subscribe %d", index, Status);                     \
                  break;                                                                                               \
               }                                                                                                       \
            }                                                                                                          \
         }                                                                                                             \
      }                                                                                                                \
   }                                                                                                                   \



//***********************************************************************************************************************
//
// FUNCTION:
//
//    VERIFY_VDB_ARRAY
//
// DESCRIPTION:
//
//    This macros obtain idents of existing Vdb which mapped to array and save if in separate array
//    This needs for read/write Vdb by ident not by name
//    Used this macros in such init round, in which Vdb are created.
//
// INPUT:
//
//    ArrName : Name of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define VERIFY_VDB_ARRAY(pPool, ArrName, Status)                                                                                      \
   {                                                                                                                                  \
      do                                                                                                                              \
      {                                                                                                                               \
         int i = 0;                                                                                                                   \
         int Length = 0;                                                                                                              \
         unsigned int Alloc_length = GET_VAR_LENGTH(GET_VAR_ARRAY_TYPE_VAR(ArrName));                                                 \
         if ((GET_VAR_ARRAY_TYPE_VAR(ArrName) & TYPE_TYPE_MASK) == TYPE_STRING) Alloc_length = Alloc_length + 1;                      \
         Length = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                                   \
         if (Length <= 0)                                                                                                             \
         {                                                                                                                            \
            Status = Length;                                                                                                          \
            break;                                                                                                                    \
         }                                                                                                                            \
         GET_VAR_ARRAY_LENGTH_VAR(ArrName) = Length;                                                                                  \
         Status =  AllocVdbIdsArray(pPool, &GET_VDB_ARRAY_IDENT_NAME(ArrName), Length);                                               \
         Status =  AllocVdbDataArray(pPool, (void**)&ArrName, Length, Alloc_length);                                                  \
         \
         type_t  ArrType = GET_VAR_ARRAY_TYPE_VAR(ArrName);                                                                           \
         for (i = 0; i < Length; ++i)                                                                                                 \
         {                                                                                                                            \
            char    ArrElemName[50];                                                                                                  \
            varid_t ArrElemId;                                                                                                        \
            type_t  InitArrElemType = TYPE_NONE;                                                                                      \
            STATUS  InitArrElemStatus = OS_SUCCESS;                                                                                   \
            \
            sprintf(ArrElemName, "%s_%d", MK_STR(ArrName), i);                                                                        \
            InitArrElemStatus =  OS_VarDB_GetVariableID(ArrElemName, &ArrElemId);                                                     \
            InitArrElemStatus += OS_VarDB_GetVariableType(ArrElemId, &InitArrElemType);                                               \
            if (InitArrElemStatus != 0)                                                                                               \
            {                                                                                                                         \
               AppDebugLog(4444, "VERIFY_VDB_ARRAY:");                                                                                \
               AppDebugLog(4444, "VDB: %s", ArrElemName);                                                                             \
               AppDebugLog(4444, "Status %d", InitArrElemStatus);                                                                     \
               Status += InitArrElemStatus;                                                                                           \
               break;                                                                                                                 \
            }                                                                                                                         \
            if (InitArrElemType != ArrType)                                                                                           \
            {                                                                                                                         \
               AppDebugLog(4444, "VERIFY_VDB_ARRAY: Type Err");                                                                       \
               AppDebugLog(4444, "VDB: %s", ArrElemName);                                                                             \
               break;                                                                                                                 \
            }                                                                                                                         \
            GET_VDB_ARRAY_IDENT_NAME(ArrName)[i] = ArrElemId;                                                                         \
            READ_VDB_ELEM_ARRAY(ArrName, i, Status);                                                                                  \
         }                                                                                                                            \
      }                                                                                                                               \
      while (0);                                                                                                                      \
   }

//***********************************************************************************************************************
//
// FUNCTION:
//
//    READ_VDB_ELEM_ARRAY
//
// DESCRIPTION:
//
//    This macros read Vdb ArrName_Index and set value to elem of array ArrName[Index]
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : index of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define READ_VDB_ELEM_ARRAY(ArrName, Index, Status)                                                                   \
   {                                                                                                                  \
      varid_t ArrElemId;                                                                                              \
      STATUS  ReadArrElemStatus = 0;                                                                                  \
      type_t  ReadArrElemType = TYPE_NONE;                                                                            \
      if (Index >= 0 && Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                    \
      {                                                                                                               \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                        \
         ReadArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &ReadArrElemType);                                   \
         ReadArrElemStatus += OS_VarDB_ReadVariable(ArrElemId, &ArrName[Index], GET_VAR_LENGTH(ReadArrElemType), 0);  \
         if (ReadArrElemStatus != 0)                                                                                  \
         {                                                                                                            \
            AppDebugLog(4444, "READ_VDB_ELEM_ARRAY: Idx %d", Index);                                                  \
            AppDebugLog(4444, "%s", MK_STR(ArrName));                                                                 \
            AppDebugLog(4444, "Status %d", ReadArrElemStatus);                                                        \
         }                                                                                                            \
      }                                                                                                               \
      else                                                                                                            \
      {                                                                                                               \
         ReadArrElemStatus += ERR_VARDB_NOT_FOUND;                                                                    \
      }                                                                                                               \
      \
      Status += ReadArrElemStatus;                                                                                    \
   }

//***********************************************************************************************************************
//
// FUNCTION:
//
//    READ_VDB_ELEM_ARRAY_STRING
//
// DESCRIPTION:
//
//    This macros read string Vdb ArrName_Index and set value to elem of array ArrName[Index]
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : index of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define READ_VDB_ELEM_ARRAY_STRING(ArrName, Index, Status)                                                                         \
   {                                                                                                                               \
      varid_t ArrElemId;                                                                                                           \
      STATUS  ReadArrElemStatus = 0;                                                                                               \
      type_t  ReadArrElemType = TYPE_NONE;                                                                                         \
      if (Index >= 0 && Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                                 \
      {                                                                                                                            \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                                     \
         ReadArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &ReadArrElemType);                                                \
         ReadArrElemStatus += OS_VarDB_ReadVariable(ArrElemId, (void*)(U32)(ArrName[Index]), GET_VAR_LENGTH(ReadArrElemType), 0);  \
         if (ReadArrElemStatus != 0)                                                                                               \
         {                                                                                                                         \
            AppDebugLog(4444, "READ_VDB_ELEM_ARRAY: Id %d Status %d ", ArrElemId, ReadArrElemStatus);                              \
         }                                                                                                                         \
      }                                                                                                                            \
      else                                                                                                                         \
      {                                                                                                                            \
         ReadArrElemStatus += ERR_VARDB_NOT_FOUND;                                                                                 \
      }                                                                                                                            \
      \
      Status += ReadArrElemStatus;                                                                                                 \
   }


//***********************************************************************************************************************
//
// FUNCTION:
//
//    READ_VDB_ELEM_ARRAY_DIRECTLY
//
// DESCRIPTION:
//
//    This macros read Vdb ArrName_Index and set value to variable VarRead
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : index of array
//    VarRead : Variable to which read Vdb
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define READ_VDB_ELEM_ARRAY_DIRECTLY(ArrName, Index, VarRead, Status)                                           \
   {                                                                                                            \
      varid_t ArrElemId;                                                                                        \
      STATUS  ReadArrElemStatus = 0;                                                                            \
      type_t  ReadArrElemType = TYPE_NONE;                                                                      \
      if (Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                            \
      {                                                                                                         \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                  \
         ReadArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &ReadArrElemType);                             \
         ReadArrElemStatus += OS_VarDB_ReadVariable(ArrElemId, &VarRead, GET_VAR_LENGTH(ReadArrElemType), 0);   \
         if (ReadArrElemStatus != 0)                                                                            \
         {                                                                                                      \
            AppDebugLog(4444, "READ_VDB_ELEM_ARRAY_DIRECTLY: Id %d Status %d ", ArrElemId, ReadArrElemStatus);  \
         }                                                                                                      \
      }                                                                                                         \
      else                                                                                                      \
      {                                                                                                         \
         ReadArrElemStatus += ERR_VARDB_NOT_FOUND;                                                              \
      }                                                                                                         \
      \
      Status += ReadArrElemStatus;                                                                              \
   }

//***********************************************************************************************************************
//
// FUNCTION:
//
//    READ_VDB_ARRAY
//
// DESCRIPTION:
//
//    This macros read all Vdbs to ArrName
//
// INPUT:
//
//    ArrName : Name of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define READ_VDB_ARRAY(ArrName, Status)                            \
   {                                                               \
      int Length = GET_VAR_ARRAY_LENGTH_VAR(ArrName);              \
      int i = 0;                                                   \
      \
      if ((GET_VAR_ARRAY_TYPE_VAR(ArrName) & TYP_STR) == TYP_STR)  \
      {                                                            \
         for (i = 0; i < Length; ++i)                              \
         {                                                         \
            READ_VDB_ELEM_ARRAY_STRING(ArrName, i, Status);        \
         }                                                         \
      }                                                            \
      else                                                         \
      {                                                            \
         for (i = 0; i < Length; ++i)                              \
         {                                                         \
            READ_VDB_ELEM_ARRAY(ArrName, i, Status);               \
         }                                                         \
      }                                                            \
   }

//***********************************************************************************************************************
//
// FUNCTION:
//
//    READ_VDB_ARRAY_SUBSCRIPTION
//
// DESCRIPTION:
//
//    This macros read all Vdbs to ArrName by subscription
//
// INPUT:
//
//    ArrName : Name of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define READ_VDB_ARRAY_SUBSCRIPTION(ArrName, Group, Status)            \
   {                                                                   \
      if (Group == GET_VDB_ARRAY_SUBSCRIPTION_GROUP_NUMBER(ArrName))   \
      {                                                                \
         int Length = GET_VAR_ARRAY_LENGTH_VAR(ArrName);               \
         int i = 0;                                                    \
         \
         if ((GET_VAR_ARRAY_TYPE_VAR(ArrName) & TYP_STR) == TYP_STR)   \
         {                                                             \
            for (i = 0; i < Length; ++i)                               \
            {                                                          \
               READ_VDB_ELEM_ARRAY_STRING(ArrName, i, Status);         \
            }                                                          \
         }                                                             \
         else                                                          \
         {                                                             \
            for (i = 0; i < Length; ++i)                               \
            {                                                          \
               READ_VDB_ELEM_ARRAY(ArrName, i, Status);                \
            }                                                          \
         }                                                             \
      }                                                                \
   }


//***********************************************************************************************************************
//
// FUNCTION:
//
//    WRITE_VDB_ELEM_ARRAY
//
// DESCRIPTION:
//
//    This macros write to Vdb ArrName_Index value of array element ArrName[Index]
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : index of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define WRITE_VDB_ELEM_ARRAY(ArrName, Index, Status)                                                                             \
   {                                                                                                                             \
      varid_t ArrElemId;                                                                                                         \
      STATUS  WriteArrElemStatus = 0;                                                                                            \
      type_t  WriteArrElemType = TYPE_NONE;                                                                                      \
      \
      if (Index >= 0 && Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                               \
      {                                                                                                                          \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                                   \
         WriteArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &WriteArrElemType);                                            \
         WriteArrElemStatus += OS_VarDB_UpdateVariableConditional(ArrElemId, &ArrName[Index], GET_VAR_LENGTH(WriteArrElemType)); \
         if (WriteArrElemStatus != 0)                                                                                            \
         {                                                                                                                       \
            AppDebugLog(4444, "WRITE_VDB_ELEM_ARRAY: Idx %d", Index);                                                            \
            AppDebugLog(4444, "%s", MK_STR(ArrName));                                                                            \
            AppDebugLog(4444, "Status %d", WriteArrElemStatus);                                                                  \
         }                                                                                                                       \
      }                                                                                                                          \
      else                                                                                                                       \
      {                                                                                                                          \
         WriteArrElemStatus += ERR_VARDB_NOT_FOUND;                                                                              \
      }                                                                                                                          \
      \
      Status += WriteArrElemStatus;                                                                                              \
   }

//***********************************************************************************************************************
//
// FUNCTION:
//
//    WRITE_VDB_ELEM_ARRAY_STRING
//
// DESCRIPTION:
//
//    This macros write to string Vdb ArrName_Index value of array element ArrName[Index]
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : index of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define WRITE_VDB_ELEM_ARRAY_STRING(ArrName, Index, Status)                                                                                    \
   {                                                                                                                                           \
      varid_t ArrElemId;                                                                                                                       \
      STATUS  WriteArrElemStatus = 0;                                                                                                          \
      type_t  WriteArrElemType = TYPE_NONE;                                                                                                    \
      \
      if (Index >= 0 && Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                                             \
      {                                                                                                                                        \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                                                 \
         WriteArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &WriteArrElemType);                                                          \
         WriteArrElemStatus += OS_VarDB_UpdateVariableConditional(ArrElemId, (void*)(U32)ArrName[Index], GET_VAR_LENGTH(WriteArrElemType));    \
         if (WriteArrElemStatus != 0)                                                                                                          \
         {                                                                                                                                     \
            AppDebugLog(4444, "WRITE_VDB_ELEM_ARRAY: Id %d Status %d ", ArrElemId, WriteArrElemStatus);                                        \
         }                                                                                                                                     \
      }                                                                                                                                        \
      else                                                                                                                                     \
      {                                                                                                                                        \
         WriteArrElemStatus += ERR_VARDB_NOT_FOUND;                                                                                            \
      }                                                                                                                                        \
      \
      Status += WriteArrElemStatus;                                                                                                            \
   }


//***********************************************************************************************************************
//
// FUNCTION:
//
//    WRITE_VDB_ELEM_ARRAY_DIRECTLY
//
// DESCRIPTION:
//
//    This macros write directly to Vdb ArrName_Index value of Value.
//    This macros does not use array with values of Vdb
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : index of array
//    Value   : Value which to write to Vdb
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define WRITE_VDB_ELEM_ARRAY_DIRECTLY(ArrName, Index, Value, Status)                                                     \
   {                                                                                                                     \
      varid_t ArrElemId;                                                                                                 \
      STATUS  WriteArrElemStatus = 0;                                                                                    \
      type_t  WriteArrElemType = TYPE_NONE;                                                                              \
      \
      if (Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                                     \
      {                                                                                                                  \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                           \
         WriteArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &WriteArrElemType);                                    \
         WriteArrElemStatus += OS_VarDB_UpdateVariableConditional(ArrElemId, &Value, GET_VAR_LENGTH(WriteArrElemType));  \
         if (WriteArrElemStatus != 0)                                                                                    \
         {                                                                                                               \
            AppDebugLog(4444, "WRITE_VDB_ELEM_ARRAY_DIRECTLY: Id %d Status %d ", ArrElemId, WriteArrElemStatus);         \
         }                                                                                                               \
      }                                                                                                                  \
      else                                                                                                               \
      {                                                                                                                  \
         WriteArrElemStatus += ERR_VARDB_NOT_FOUND;                                                                      \
      }                                                                                                                  \
      \
      Status += WriteArrElemStatus;                                                                                      \
   }


//***********************************************************************************************************************
//
// FUNCTION:
//
//    WRITE_VDB_ARRAY
//
// DESCRIPTION:
//
//    This macros write to all Vdbs values from array ArrName
//
// INPUT:
//
//    ArrName : Name of array
//
// OUTPUT:
//    Status  : Status of execution
//
//***********************************************************************************************************************
#define WRITE_VDB_ARRAY(ArrName, Status)                              \
   {                                                                  \
      int Length = GET_VAR_ARRAY_LENGTH_VAR(ArrName);                 \
      int i = 0;                                                      \
      \
      if ((GET_VAR_ARRAY_TYPE_VAR(ArrName) & TYP_STR) == TYP_STR)     \
      {                                                               \
         for (i = 0; i < Length; ++i)                                 \
         {                                                            \
            WRITE_VDB_ELEM_ARRAY_STRING(ArrName, i, Status);          \
         }                                                            \
      }                                                               \
      else                                                            \
      {                                                               \
         for (i = 0; i < Length; ++i)                                 \
         {                                                            \
            WRITE_VDB_ELEM_ARRAY(ArrName, i, Status);                 \
         }                                                            \
      }                                                               \
   }

//***********************************************************************************************************************
#define ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                               \
   {                                                                                                                    \
      do                                                                                                                \
      {                                                                                                                 \
         unsigned int Alloc_length = GET_VAR_LENGTH(GET_VAR_ARRAY_TYPE_VAR(ArrName));                                   \
         if ((GET_VAR_ARRAY_TYPE_VAR(ArrName) & TYPE_TYPE_MASK) == TYPE_STRING)                                         \
         {                                                                                                              \
            Alloc_length = Alloc_length + 1;                                                                            \
         }                                                                                                              \
         U32 Length = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                 \
         Status =  AllocVdbDataArray(pPool, (void**)&ArrName, Length, Alloc_length);                                    \
         if (Status != OS_SUCCESS)                                                                                      \
         {                                                                                                              \
            AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Err Alloc Arr %d", MK_STR(ArrName), Status);                        \
            break;                                                                                                      \
         }                                                                                                              \
      }                                                                                                                 \
      while (0);                                                                                                        \
   }

//***********************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_VAL_T
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup)
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    Call CREATE_VDB_ARRAY, CREATE_VDB_ARRAY_F32 or CREATE_VDB_ARRAY_F64 instead of directly this.
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//***********************************************************************************************************************
#define CREATE_VDB_ARRAY_VAL_T(pPool,          /*Memory pool*/                                                                 \
                               ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                               ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                               ArrType,        /*Type of array*/                                                               \
                               Length,         /*Length of array*/                                                             \
                               AccessRead,     /*Access read level*/                                                           \
                               AccessWrite,    /*Access write level*/                                                          \
                               ScaleType,      /*Scale type*/                                                                  \
                               ScaleValue,     /*Scale value*/                                                                 \
                               Unit,           /*Unit type*/                                                                   \
                               Precision,      /*Precision*/                                                                   \
                               InitValue,      /*Init value*/                                                                  \
                               MinValue,       /*Minimum value*/                                                               \
                               MaxValue,       /*Maximum value*/                                                               \
                               Lists,          /*Select list*/                                                                 \
                               LogFlag,        /*Log flag*/                                                                    \
                               VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                       \
                               Status)         /*Status*/                                                                      \
{                                                                                                                              \
   do                                                                                                                          \
   {                                                                                                                           \
      int     IsString = 0;                                                                                                    \
      value_t ValueStr;                                                                                                        \
      char    ArrElemName[50];                                                                                                 \
      varid_t ArrElemId;                                                                                                       \
      STATUS  CreateArrElemStatus;                                                                                             \
      int i = 0;                                                                                                               \
      unsigned int Alloc_length = GET_VAR_LENGTH(GET_VAR_ARRAY_TYPE_VAR(ArrName));                                             \
      if ((GET_VAR_ARRAY_TYPE_VAR(ArrName) & TYPE_TYPE_MASK) == TYPE_STRING)                                                   \
      {                                                                                                                        \
         Alloc_length = Alloc_length + 1;                                                                                      \
         IsString = 1;                                                                                                         \
         ValueStr.string = InitValue.string;                                                                                   \
      }                                                                                                                        \
      \
      Length = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                               \
      if (Length <= 0)                                                                                                         \
      {                                                                                                                        \
         Status = Length;                                                                                                      \
         break;                                                                                                                \
      }                                                                                                                        \
      \
      Status =  AllocVdbIdsArray(pPool, &GET_VDB_ARRAY_IDENT_NAME(ArrName), Length);                                           \
      if (Status != OS_SUCCESS)                                                                                                \
      {                                                                                                                        \
         AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Err Alloc Arr %d", ArrElemName, Status);                                      \
         break;                                                                                                                \
      }                                                                                                                        \
      \
      for (i = 0; i < Length; ++i)                                                                                             \
      {                                                                                                                        \
         int IsVdbCreated = 0;                                                                                                 \
         sprintf(ArrElemName, "%s_%d", ArrNameString, i);/** UPDATE **/                                                        \
         CreateArrElemStatus = OS_VarDB_GetVariableID( ArrElemName, &ArrElemId );                                              \
         if (IsString)                                                                                                         \
         {                                                                                                                     \
            char* StrBuf = (char*)SysAllocDataMemory(pPool, Alloc_length);                                                     \
            if (NULL == StrBuf)                                                                                                \
            {                                                                                                                  \
               Status = ERR_MEMORY_NOT_FOUND;                                                                                  \
               AppDebugLog(4444, "CREATE_STR_BUFF: %s ", ArrElemName);                                                         \
               AppDebugLog(4444, "CREATE_STR_BUFF: Err Alloc Arr %d", Status);                                                 \
            }                                                                                                                  \
            strncpy(StrBuf, ValueStr.string, (size_t )Alloc_length);                                                           \
            InitValue.string = StrBuf;                                                                                         \
         }                                                                                                                     \
         if (CreateArrElemStatus == ERR_VARDB_NOT_FOUND)                                                                       \
         {                                                                                                                     \
            switch (VdbType)                                                                                                   \
            {                                                                                                                  \
               case LOCAL_VAR:                                                                                                 \
               {                                                                                                               \
                  CreateArrElemStatus = createVarDB_Local(pPool, ArrElemName, ArrType, AccessRead, AccessWrite,                \
                                                          ScaleType, ScaleValue, Unit, Precision,                              \
                                                          InitValue, MinValue, MaxValue, LogFlag);                             \
                  IsVdbCreated = (CreateArrElemStatus == OS_SUCCESS);                                                          \
                  break;                                                                                                       \
               }                                                                                                               \
               case BACKUP_VAR:                                                                                                \
               {                                                                                                               \
                  CreateArrElemStatus = createVarDB_Backup(pPool, ArrElemName, ArrType, AccessRead, AccessWrite,               \
                                                           ScaleType, ScaleValue, Unit, Precision,                             \
                                                           InitValue, MinValue, MaxValue, LogFlag);                            \
                  IsVdbCreated = (CreateArrElemStatus == OS_SUCCESS);                                                          \
                  break;                                                                                                       \
               }                                                                                                               \
               case PARAM_VAR:                                                                                                 \
               {                                                                                                               \
                  CreateArrElemStatus = createVarDB_Parameter(pPool, ArrElemName, ArrType, AccessRead, AccessWrite,            \
                                                              ScaleType, ScaleValue, Unit, Precision,                          \
                                                              InitValue, MinValue, MaxValue, LogFlag);                         \
                  IsVdbCreated = (CreateArrElemStatus == OS_SUCCESS);                                                          \
                  break;                                                                                                       \
               }                                                                                                               \
               default:                                                                                                        \
               {                                                                                                               \
                  AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Wrong update type: %d", ArrElemName, VdbType);                       \
                  CreateArrElemStatus = ERR_VARDB_WRONG_UPDATE;                                                                \
               }                                                                                                               \
            }                                                                                                                  \
            \
            if (IsVdbCreated)                                                                                                  \
            {                                                                                                                  \
               CreateArrElemStatus =  OS_VarDB_GetVariableID(ArrElemName, &ArrElemId);                                         \
               if (CreateArrElemStatus == OS_SUCCESS)                                                                          \
               {                                                                                                               \
                  GET_VDB_ARRAY_IDENT_NAME(ArrName)[i] = ArrElemId;                                                            \
               }                                                                                                               \
               else                                                                                                            \
               {                                                                                                               \
                  AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Err Get Id ", ArrElemName);                                          \
               }                                                                                                               \
            }                                                                                                                  \
            else                                                                                                               \
            {                                                                                                                  \
               AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Err Creation Status %d", ArrElemName, CreateArrElemStatus);             \
            }                                                                                                                  \
         }                                                                                                                     \
         else                                                                                                                  \
         {                                                                                                                     \
            AppDebugLog(4444, "CREATE_VDB_ARRAY: %s already exist!", ArrElemName);                                             \
            CreateArrElemStatus = ERR_VARDB_VARIABLE_EXISTS;                                                                   \
         }                                                                                                                     \
         \
         Status += CreateArrElemStatus;                                                                                        \
      }                                                                                                                        \
   }                                                                                                                           \
   while (0);                                                                                                                  \
}

//***********************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup)
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for init of U8-U64, S8-S64, STRING, TIME
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//*********************************************************************************************************************
#define CREATE_VDB_ARRAY(pPool,          /*Memory pool*/                                                             \
                         ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/     \
                         ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                          \
                         ArrType,        /*Type of array*/                                                           \
                         Length,         /*Length of array*/                                                         \
                         AccessRead,     /*Access read level*/                                                       \
                         AccessWrite,    /*Access write level*/                                                      \
                         ScaleType,      /*Scale type*/                                                              \
                         ScaleValue,     /*Scale value*/                                                             \
                         Unit,           /*Unit type*/                                                               \
                         Precision,      /*Precision*/                                                               \
                         InitValue,      /*Init value*/                                                              \
                         MinValue,       /*Minimum value*/                                                           \
                         MaxValue,       /*Maximum value*/                                                           \
                         Lists,          /*Select list*/                                                             \
                         LogFlag,        /*Log flag*/                                                                \
                         VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                   \
                         Status)         /*Status*/                                                                  \
{                                                                                                                    \
   do                                                                                                                \
   {                                                                                                                 \
      value_t val, min, max;                                                                                         \
      val.u64 = InitValue;                                                                                           \
      min.u64 = MinValue;                                                                                            \
      max.u64 = MaxValue;                                                                                            \
      CREATE_VDB_ARRAY_VAL_T(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                \
                             ScaleType, ScaleValue, Unit, Precision, val, min, max,                                  \
                             Lists, LogFlag, VdbType, Status);                                                       \
   }                                                                                                                 \
   while (0);                                                                                                        \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_F64
//
// DESCRIPTION:
//
//    This macros create array of VarDB (Local, Parameter, Backup)
//    Need to call this macros if Init Round 1 for creation of variables in VarDB
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for initialization of F64
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_F64(pPool,          /*Memory pool*/                                                             \
                             ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/     \
                             ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                          \
                             ArrType,        /*Type of array*/                                                           \
                             Length,         /*Length of array*/                                                         \
                             AccessRead,     /*Access read level*/                                                       \
                             AccessWrite,    /*Access write level*/                                                      \
                             ScaleType,      /*Scale type*/                                                              \
                             ScaleValue,     /*Scale value*/                                                             \
                             Unit,           /*Unit type*/                                                               \
                             Precision,      /*Precision*/                                                               \
                             InitValue,      /*Init value*/                                                              \
                             MinValue,       /*Minimum value*/                                                           \
                             MaxValue,       /*Maximum value*/                                                           \
                             Lists,          /*Select list*/                                                             \
                             LogFlag,        /*Log flag*/                                                                \
                             VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                   \
                             Status)         /*Status*/                                                                  \
{                                                                                                                        \
   do                                                                                                                    \
   {                                                                                                                     \
      value_t val, min, max;                                                                                             \
      val.f64 = InitValue;                                                                                               \
      min.f64 = MinValue;                                                                                                \
      max.f64 = MaxValue;                                                                                                \
      CREATE_VDB_ARRAY_VAL_T(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                    \
                             ScaleType, ScaleValue, Unit, Precision, val, min, max,                                      \
                             Lists, LogFlag, VdbType, Status);                                                           \
   }                                                                                                                     \
   while (0);                                                                                                            \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_F32
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup)
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for init of F32
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_F32(pPool,          /*Memory pool*/                                                             \
                             ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/     \
                             ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                          \
                             ArrType,        /*Type of array*/                                                           \
                             Length,         /*Length of array*/                                                         \
                             AccessRead,     /*Access read level*/                                                       \
                             AccessWrite,    /*Access write level*/                                                      \
                             ScaleType,      /*Scale type*/                                                              \
                             ScaleValue,     /*Scale value*/                                                             \
                             Unit,           /*Unit type*/                                                               \
                             Precision,      /*Precision*/                                                               \
                             InitValue,      /*Init value*/                                                              \
                             MinValue,       /*Minimum value*/                                                           \
                             MaxValue,       /*Maximum value*/                                                           \
                             Lists,          /*Select list*/                                                             \
                             LogFlag,        /*Log flag*/                                                                \
                             VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                   \
                             Status)         /*Status*/                                                                  \
{                                                                                                                        \
   do                                                                                                                    \
   {                                                                                                                     \
      value_t val, min, max;                                                                                             \
      val.f32 = InitValue;                                                                                               \
      min.f32 = MinValue;                                                                                                \
      max.f32 = MaxValue;                                                                                                \
      CREATE_VDB_ARRAY_VAL_T(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                    \
                             ScaleType, ScaleValue, Unit, Precision, val, min, max,                                      \
                             Lists, LogFlag, VdbType, Status);                                                           \
   }                                                                                                                     \
   while (0);                                                                                                            \
}

//**********************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_STRING
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup)
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for init of U8-U64, S8-S64, STRING, TIME
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//****************************************************************************************************************************
#define CREATE_VDB_ARRAY_STRING(pPool,          /*Memory pool*/                                                             \
                                ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/     \
                                ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                          \
                                ArrType,        /*Type of array*/                                                           \
                                Length,         /*Length of array*/                                                         \
                                AccessRead,     /*Access read level*/                                                       \
                                AccessWrite,    /*Access write level*/                                                      \
                                ScaleType,      /*Scale type*/                                                              \
                                ScaleValue,     /*Scale value*/                                                             \
                                Unit,           /*Unit type*/                                                               \
                                Precision,      /*Precision*/                                                               \
                                InitValue,      /*Init value*/                                                              \
                                MinValue,       /*Minimum value*/                                                           \
                                MaxValue,       /*Maximum value*/                                                           \
                                Lists,          /*Select list*/                                                             \
                                LogFlag,        /*Log flag*/                                                                \
                                VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                   \
                                Status)         /*Status*/                                                                  \
{                                                                                                                           \
   do                                                                                                                       \
   {                                                                                                                        \
      value_t val, min, max;                                                                                               \
      val.string = InitValue;																								\
	  min.string = MinValue;																								\
      max.string = MaxValue;																								\
      CREATE_VDB_ARRAY_VAL_T(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                       \
                             ScaleType, ScaleValue, Unit, Precision, val, min, max,                                         \
                             Lists, LogFlag, VdbType, Status);                                                              \
   }                                                                                                                        \
   while (0);                                                                                                               \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL
//
// DESCRIPTION:
//
//    This macros create array of Local Vdbs
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL(pPool,          /*Memory pool*/                                                                 \
                               ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                               ArrName,        /*Name of array, with \" stripped *//* UPDATE */                                \
                               AccessRead,     /*Access read level*/                                                           \
                               AccessWrite,    /*Access write level*/                                                          \
                               ScaleType,      /*Scale type*/                                                                  \
                               ScaleValue,     /*Scale value*/                                                                 \
                               Unit,           /*Unit type*/                                                                   \
                               Precision,      /*Precision*/                                                                   \
                               InitValue,      /*Init value*/                                                                  \
                               MinValue,       /*Minimum value*/                                                               \
                               MaxValue,       /*Maximum value*/                                                               \
                               Lists,          /*Select list*/                                                                 \
                               LogFlag,        /*Log flag*/                                                                    \
                               Status)         /*Status*/                                                                      \
{                                                                                                                              \
   CREATE_VDB_ARRAY(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                    AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                    LogFlag, LOCAL_VAR, Status)                                                                                \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                           \
}

//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                           ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                           ArrName,        /*Name of array, with \" stripped *//* UPDATE */                        \
                                           AccessRead,     /*Access read level*/                                                   \
                                           ScaleType,      /*Scale type*/                                                          \
                                           AccessWrite,    /*Access write level*/                                                  \
                                           ScaleValue,     /*Scale value*/                                                         \
                                           Unit,           /*Unit type*/                                                           \
                                           Precision,      /*Precision*/                                                           \
                                           InitValue,      /*Init value*/                                                          \
                                           MinValue,       /*Minimum value*/                                                       \
                                           MaxValue,       /*Maximum value*/                                                       \
                                           Lists,          /*Select list*/                                                         \
                                           LogFlag,        /*Log flag*/                                                            \
                                           Status)         /*Status*/                                                              \
{                                                                                                                                  \
   CREATE_VDB_ARRAY(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName),  GET_VAR_ARRAY_LENGTH_VAR(ArrName),            \
                    AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                    LogFlag, LOCAL_VAR, Status)                                                                                    \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL_F64
//
// DESCRIPTION:
//
//    This macros create array of Local F64 Vdbs
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F64(pPool,          /*Memory pool*/                                                                 \
                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                   AccessRead,     /*Access read level*/                                                           \
                                   AccessWrite,    /*Access write level*/                                                          \
                                   ScaleType,      /*Scale type*/                                                                  \
                                   ScaleValue,     /*Scale value*/                                                                 \
                                   Unit,           /*Unit type*/                                                                   \
                                   Precision,      /*Precision*/                                                                   \
                                   InitValue,      /*Init value*/                                                                  \
                                   MinValue,       /*Minimum value*/                                                               \
                                   MaxValue,       /*Maximum value*/                                                               \
                                   Lists,          /*Select list*/                                                                 \
                                   LogFlag,        /*Log flag*/                                                                    \
                                   Status)         /*Status*/                                                                      \
{                                                                                                                                  \
   CREATE_VDB_ARRAY_F64(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                        LogFlag, LOCAL_VAR, Status)                                                                                \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                               \
}

//***************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F64_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                               ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                               ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                               AccessRead,     /*Access read level*/                                                   \
                                               AccessWrite,    /*Access write level*/                                                  \
                                               ScaleType,      /*Scale type*/                                                          \
                                               ScaleValue,     /*Scale value*/                                                         \
                                               Unit,           /*Unit type*/                                                           \
                                               Precision,      /*Precision*/                                                           \
                                               InitValue,      /*Init value*/                                                          \
                                               MinValue,       /*Minimum value*/                                                       \
                                               MaxValue,       /*Maximum value*/                                                       \
                                               Lists,          /*Select list*/                                                         \
                                               LogFlag,        /*Log flag*/                                                            \
                                               Status)         /*Status*/                                                              \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F64(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                        LogFlag, LOCAL_VAR, Status)                                                                                    \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL_F32
//
// DESCRIPTION:
//
//    This macros create array of Local F32 Vdbs
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F32(pPool,          /*Memory pool*/                                                                 \
                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                   AccessRead,     /*Access read level*/                                                           \
                                   AccessWrite,    /*Access write level*/                                                          \
                                   ScaleType,      /*Scale type*/                                                                  \
                                   ScaleValue,     /*Scale value*/                                                                 \
                                   Unit,           /*Unit type*/                                                                   \
                                   Precision,      /*Precision*/                                                                   \
                                   InitValue,      /*Init value*/                                                                  \
                                   MinValue,       /*Minimum value*/                                                               \
                                   MaxValue,       /*Maximum value*/                                                               \
                                   Lists,          /*Select list*/                                                                 \
                                   LogFlag,        /*Log flag*/                                                                    \
                                   Status)         /*Status*/                                                                      \
{                                                                                                                                  \
   CREATE_VDB_ARRAY_F32(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue,            \
                        Lists, LogFlag, LOCAL_VAR, Status)                                                                         \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                               \
}

//***************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F32_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                               ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                               ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                               AccessRead,     /*Access read level*/                                                   \
                                               AccessWrite,    /*Access write level*/                                                  \
                                               ScaleType,      /*Scale type*/                                                          \
                                               ScaleValue,     /*Scale value*/                                                         \
                                               Unit,           /*Unit type*/                                                           \
                                               Precision,      /*Precision*/                                                           \
                                               InitValue,      /*Init value*/                                                          \
                                               MinValue,       /*Minimum value*/                                                       \
                                               MaxValue,       /*Maximum value*/                                                       \
                                               Lists,          /*Select list*/                                                         \
                                               LogFlag,        /*Log flag*/                                                            \
                                               Status)         /*Status*/                                                              \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F32(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                        LogFlag, LOCAL_VAR, Status)                                                                                    \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL_STRING
//
// DESCRIPTION:
//
//    This macros create array of Local String Vdbs
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
//**************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_STRING(pPool,          /*Memory pool*/                                                                 \
                                      ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                      ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                      AccessRead,     /*Access read level*/                                                           \
                                      AccessWrite,    /*Access write level*/                                                          \
                                      ScaleType,      /*Scale type*/                                                                  \
                                      ScaleValue,     /*Scale value*/                                                                 \
                                      Unit,           /*Unit type*/                                                                   \
                                      Precision,      /*Precision*/                                                                   \
                                      InitValue,      /*Init value*/                                                                  \
                                      MinValue,       /*Minimum value*/                                                               \
                                      MaxValue,       /*Maximum value*/                                                               \
                                      Lists,          /*Select list*/                                                                 \
                                      LogFlag,        /*Log flag*/                                                                    \
                                      Status)         /*Status*/                                                                      \
{                                                                                                                                     \
   CREATE_VDB_ARRAY_STRING(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                           AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                           LogFlag, LOCAL_VAR, Status)                                                                                \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                  \
}

//******************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_STRING_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                                  ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                                  ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                                  AccessRead,     /*Access read level*/                                                   \
                                                  AccessWrite,    /*Access write level*/                                                  \
                                                  ScaleType,      /*Scale type*/                                                          \
                                                  ScaleValue,     /*Scale value*/                                                         \
                                                  Unit,           /*Unit type*/                                                           \
                                                  Precision,      /*Precision*/                                                           \
                                                  InitValue,      /*Init value*/                                                          \
                                                  MinValue,       /*Minimum value*/                                                       \
                                                  MaxValue,       /*Maximum value*/                                                       \
                                                  Lists,          /*Select list*/                                                         \
                                                  LogFlag,        /*Log flag*/                                                            \
                                                  Status)         /*Status*/                                                              \
{                                                                                                                                         \
   CREATE_VDB_ARRAY_STRING(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                           AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                           LogFlag, LOCAL_VAR, Status)                                                                                    \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_BACKUP
//
// DESCRIPTION:
//
//    This macros create array of Backup Vdbs
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
//*******************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP(pPool,         /*Memory pool*/                                                                 \
                                ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                ArrName,        /*Name of array, with \" stripped *//* UPDATE */                               \
                                AccessRead,     /*Access read level*/                                                          \
                                AccessWrite,    /*Access write level*/                                                         \
                                ScaleType,      /*Scale type*/                                                                 \
                                ScaleValue,     /*Scale value*/                                                                \
                                Unit,           /*Unit type*/                                                                  \
                                Precision,      /*Precision*/                                                                  \
                                InitValue,      /*Init value*/                                                                 \
                                MinValue,       /*Minimum value*/                                                              \
                                MaxValue,       /*Maximum value*/                                                              \
                                Lists,          /*Select list*/                                                                \
                                LogFlag,        /*Log flag*/                                                                   \
                                Status)         /*Status*/                                                                     \
{                                                                                                                              \
   CREATE_VDB_ARRAY(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                    AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                    LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                           \
}

//************************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_WITHOUT_REF(pPool,         /*Memory pool*/                                                          \
                                            ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                            ArrName,        /*Name of array, with \" stripped *//* UPDATE */                        \
                                            AccessRead,     /*Access read level*/                                                   \
                                            AccessWrite,    /*Access write level*/                                                  \
                                            ScaleType,      /*Scale type*/                                                          \
                                            ScaleValue,     /*Scale value*/                                                         \
                                            Unit,           /*Unit type*/                                                           \
                                            Precision,      /*Precision*/                                                           \
                                            InitValue,      /*Init value*/                                                          \
                                            MinValue,       /*Minimum value*/                                                       \
                                            MaxValue,       /*Maximum value*/                                                       \
                                            Lists,          /*Select list*/                                                         \
                                            LogFlag,        /*Log flag*/                                                            \
                                            Status)         /*Status*/                                                              \
{                                                                                                                                   \
   CREATE_VDB_ARRAY(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),              \
                    AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                    LogFlag, BACKUP_VAR, Status)                                                                                    \
}

//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F64(pPool,         /*Memory pool*/                                                                 \
                                    ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                    ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                             \
                                    AccessRead,     /*Access read level*/                                                          \
                                    AccessWrite,    /*Access write level*/                                                         \
                                    ScaleType,      /*Scale type*/                                                                 \
                                    ScaleValue,     /*Scale value*/                                                                \
                                    Unit,           /*Unit type*/                                                                  \
                                    Precision,      /*Precision*/                                                                  \
                                    InitValue,      /*Init value*/                                                                 \
                                    MinValue,       /*Minimum value*/                                                              \
                                    MaxValue,       /*Maximum value*/                                                              \
                                    Lists,          /*Select list*/                                                                \
                                    LogFlag,        /*Log flag*/                                                                   \
                                    Status)         /*Status*/                                                                     \
{                                                                                                                                  \
   CREATE_VDB_ARRAY_F64(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                        LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                               \
}

//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F64_WITHOUT_REF(pPool,         /*Memory pool*/                                                          \
                                                ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                                ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                                AccessRead,     /*Access read level*/                                                   \
                                                AccessWrite,    /*Access write level*/                                                  \
                                                ScaleType,      /*Scale type*/                                                          \
                                                ScaleValue,     /*Scale value*/                                                         \
                                                Unit,           /*Unit type*/                                                           \
                                                Precision,      /*Precision*/                                                           \
                                                InitValue,      /*Init value*/                                                          \
                                                MinValue,       /*Minimum value*/                                                       \
                                                MaxValue,       /*Maximum value*/                                                       \
                                                Lists,          /*Select list*/                                                         \
                                                LogFlag,        /*Log flag*/                                                            \
                                                Status)         /*Status*/                                                              \
{                                                                                                                                       \
   CREATE_VDB_ARRAY_F64(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),              \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                        LogFlag, BACKUP_VAR, Status)                                                                                    \
}

//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F32(pPool,          /*Memory pool*/                                                                \
                                    ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                    ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                             \
                                    AccessRead,     /*Access read level*/                                                          \
                                    AccessWrite,    /*Access write level*/                                                         \
                                    ScaleType,      /*Scale type*/                                                                 \
                                    ScaleValue,     /*Scale value*/                                                                \
                                    Unit,           /*Unit type*/                                                                  \
                                    Precision,      /*Precision*/                                                                  \
                                    InitValue,      /*Init value*/                                                                 \
                                    MinValue,       /*Minimum value*/                                                              \
                                    MaxValue,       /*Maximum value*/                                                              \
                                    Lists,          /*Select list*/                                                                \
                                    LogFlag,        /*Log flag*/                                                                   \
                                    Status)         /*Status*/                                                                     \
{                                                                                                                                  \
   CREATE_VDB_ARRAY_F32(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                        LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                               \
}

//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F32_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                                ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                                ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                                AccessRead,     /*Access read level*/                                                   \
                                                AccessWrite,    /*Access write level*/                                                  \
                                                ScaleType,      /*Scale type*/                                                          \
                                                ScaleValue,     /*Scale value*/                                                         \
                                                Unit,           /*Unit type*/                                                           \
                                                Precision,      /*Precision*/                                                           \
                                                InitValue,      /*Init value*/                                                          \
                                                MinValue,       /*Minimum value*/                                                       \
                                                MaxValue,       /*Maximum value*/                                                       \
                                                Lists,          /*Select list*/                                                         \
                                                LogFlag,        /*Log flag*/                                                            \
                                                Status)         /*Status*/                                                              \
{                                                                                                                                       \
   CREATE_VDB_ARRAY_F32(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),              \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                        LogFlag, BACKUP_VAR, Status)                                                                                    \
}

//******************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_BACKUP_STRING
//
// DESCRIPTION:
//
//    This macros create array of Backup VarDB
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
//******************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_STRING(pPool,          /*Memory pool*/                                                                \
                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                             \
                                       AccessRead,     /*Access read level*/                                                          \
                                       AccessWrite,    /*Access write level*/                                                         \
                                       ScaleType,      /*Scale type*/                                                                 \
                                       ScaleValue,     /*Scale value*/                                                                \
                                       Unit,           /*Unit type*/                                                                  \
                                       Precision,      /*Precision*/                                                                  \
                                       InitValue,      /*Init value*/                                                                 \
                                       MinValue,       /*Minimum value*/                                                              \
                                       MaxValue,       /*Maximum value*/                                                              \
                                       Lists,          /*Select list*/                                                                \
                                       LogFlag,        /*Log flag*/                                                                   \
                                       Status)         /*Status*/                                                                     \
{                                                                                                                                     \
   CREATE_VDB_ARRAY_STRING(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                           AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                           LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                  \
}

//******************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_STRING_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                                   AccessRead,     /*Access read level*/                                                   \
                                                   AccessWrite,    /*Access write level*/                                                  \
                                                   ScaleType,      /*Scale type*/                                                          \
                                                   ScaleValue,     /*Scale value*/                                                         \
                                                   Unit,           /*Unit type*/                                                           \
                                                   Precision,      /*Precision*/                                                           \
                                                   InitValue,      /*Init value*/                                                          \
                                                   MinValue,       /*Minimum value*/                                                       \
                                                   MaxValue,       /*Maximum value*/                                                       \
                                                   Lists,          /*Select list*/                                                         \
                                                   LogFlag,        /*Log flag*/                                                            \
                                                   Status)         /*Status*/                                                              \
{                                                                                                                                          \
   CREATE_VDB_ARRAY_STRING(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),              \
                           AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                           LogFlag, BACKUP_VAR, Status)                                                                                    \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_PARAMETER
//
// DESCRIPTION:
//
//    This macros create array of Parameter VarDB
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER(pPool,         /*Memory pool*/                                                                 \
                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                   ArrName,        /*Name of array, with \" stripped *//* UPDATE */                               \
                                   AccessRead,     /*Access read level*/                                                          \
                                   AccessWrite,    /*Access write level*/                                                         \
                                   ScaleType,      /*Scale type*/                                                                 \
                                   ScaleValue,     /*Scale value*/                                                                \
                                   Unit,           /*Unit type*/                                                                  \
                                   Precision,      /*Precision*/                                                                  \
                                   InitValue,      /*Init value*/                                                                 \
                                   MinValue,       /*Minimum value*/                                                              \
                                   MaxValue,       /*Maximum value*/                                                              \
                                   Lists,          /*Select list*/                                                                \
                                   LogFlag,        /*Log flag*/                                                                   \
                                   Status)         /*Status*/                                                                     \
{                                                                                                                                 \
   CREATE_VDB_ARRAY(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),            \
                    AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,        \
                    LogFlag, PARAM_VAR, Status)                                                                                   \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                              \
}

//***************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_WITHOUT_REF(pPool,         /*Memory pool*/                                                          \
                                               ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                               ArrName,        /*Name of array, with \" stripped *//* UPDATE */                        \
                                               AccessRead,     /*Access read level*/                                                   \
                                               AccessWrite,    /*Access write level*/                                                  \
                                               ScaleType,      /*Scale type*/                                                          \
                                               ScaleValue,     /*Scale value*/                                                         \
                                               Unit,           /*Unit type*/                                                           \
                                               Precision,      /*Precision*/                                                           \
                                               InitValue,      /*Init value*/                                                          \
                                               MinValue,       /*Minimum value*/                                                       \
                                               MaxValue,       /*Maximum value*/                                                       \
                                               Lists,          /*Select list*/                                                         \
                                               LogFlag,        /*Log flag*/                                                            \
                                               Status)         /*Status*/                                                              \
{                                                                                                                                      \
   CREATE_VDB_ARRAY(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                 \
                    AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,             \
                    LogFlag, PARAM_VAR, Status)                                                                                        \
}

//***************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F64(pPool,          /*Memory pool*/                                                                 \
                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                       AccessRead,     /*Access read level*/                                                           \
                                       AccessWrite,    /*Access write level*/                                                          \
                                       ScaleType,      /*Scale type*/                                                                  \
                                       ScaleValue,     /*Scale value*/                                                                 \
                                       Unit,           /*Unit type*/                                                                   \
                                       Precision,      /*Precision*/                                                                   \
                                       InitValue,      /*Init value*/                                                                  \
                                       MinValue,       /*Minimum value*/                                                               \
                                       MaxValue,       /*Maximum value*/                                                               \
                                       Lists,          /*Select list*/                                                                 \
                                       LogFlag,        /*Log flag*/                                                                    \
                                       Status)         /*Status*/                                                                      \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F64(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                        LogFlag, PARAM_VAR, Status)                                                                                    \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                   \
}

//*******************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F64_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                                   AccessRead,     /*Access read level*/                                                   \
                                                   AccessWrite,    /*Access write level*/                                                  \
                                                   ScaleType,      /*Scale type*/                                                          \
                                                   ScaleValue,     /*Scale value*/                                                         \
                                                   Unit,           /*Unit type*/                                                           \
                                                   Precision,      /*Precision*/                                                           \
                                                   InitValue,      /*Init value*/                                                          \
                                                   MinValue,       /*Minimum value*/                                                       \
                                                   MaxValue,       /*Maximum value*/                                                       \
                                                   Lists,          /*Select list*/                                                         \
                                                   LogFlag,        /*Log flag*/                                                            \
                                                   Status)         /*Status*/                                                              \
{                                                                                                                                          \
   CREATE_VDB_ARRAY_F64(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                 \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,             \
                        LogFlag, PARAM_VAR, Status)                                                                                        \
}

//***************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F32(pPool,          /*Memory pool*/                                                                 \
                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                       AccessRead,     /*Access read level*/                                                           \
                                       AccessWrite,    /*Access write level*/                                                          \
                                       ScaleType,      /*Scale type*/                                                                  \
                                       ScaleValue,     /*Scale value*/                                                                 \
                                       Unit,           /*Unit type*/                                                                   \
                                       Precision,      /*Precision*/                                                                   \
                                       InitValue,      /*Init value*/                                                                  \
                                       MinValue,       /*Minimum value*/                                                               \
                                       MaxValue,       /*Maximum value*/                                                               \
                                       Lists,          /*Select list*/                                                                 \
                                       LogFlag,        /*Log flag*/                                                                    \
                                       Status)         /*Status*/                                                                      \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F32(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                        LogFlag, PARAM_VAR, Status)                                                                                    \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                   \
}

//*******************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F32_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                                   AccessRead,     /*Access read level*/                                                   \
                                                   AccessWrite,    /*Access write level*/                                                  \
                                                   ScaleType,      /*Scale type*/                                                          \
                                                   ScaleValue,     /*Scale value*/                                                         \
                                                   Unit,           /*Unit type*/                                                           \
                                                   Precision,      /*Precision*/                                                           \
                                                   InitValue,      /*Init value*/                                                          \
                                                   MinValue,       /*Minimum value*/                                                       \
                                                   MaxValue,       /*Maximum value*/                                                       \
                                                   Lists,          /*Select list*/                                                         \
                                                   LogFlag,        /*Log flag*/                                                            \
                                                   Status)         /*Status*/                                                              \
{                                                                                                                                          \
   CREATE_VDB_ARRAY_F32(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                 \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,             \
                        LogFlag, PARAM_VAR, Status)                                                                                        \
}

//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_STRING(pPool,          /*Memory pool*/                                                             \
                                          ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/     \
                                          ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                          \
                                          AccessRead,     /*Access read level*/                                                       \
                                          AccessWrite,    /*Access write level*/                                                      \
                                          ScaleType,      /*Scale type*/                                                              \
                                          ScaleValue,     /*Scale value*/                                                             \
                                          Unit,           /*Unit type*/                                                               \
                                          Precision,      /*Precision*/                                                               \
                                          InitValue,      /*Init value*/                                                              \
                                          MinValue,       /*Minimum value*/                                                           \
                                          MaxValue,       /*Maximum value*/                                                           \
                                          Lists,          /*Select list*/                                                             \
                                          LogFlag,        /*Log flag*/                                                                \
                                          Status)         /*Status*/                                                                  \
{                                                                                                                                     \
   CREATE_VDB_ARRAY_STRING(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                           AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                           LogFlag, PARAM_VAR, Status)                                                                                \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                  \
}

//**********************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_STRING_WITHOUT_REF(pPool,          /*Memory pool*/                                                         \
                                                      ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/ \
                                                      ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                      \
                                                      AccessRead,     /*Access read level*/                                                   \
                                                      AccessWrite,    /*Access write level*/                                                  \
                                                      ScaleType,      /*Scale type*/                                                          \
                                                      ScaleValue,     /*Scale value*/                                                         \
                                                      Unit,           /*Unit type*/                                                           \
                                                      Precision,      /*Precision*/                                                           \
                                                      InitValue,      /*Init value*/                                                          \
                                                      MinValue,       /*Minimum value*/                                                       \
                                                      MaxValue,       /*Maximum value*/                                                       \
                                                      Lists,          /*Select list*/                                                         \
                                                      LogFlag,        /*Log flag*/                                                            \
                                                      Status)         /*Status*/                                                              \
{                                                                                                                                             \
   CREATE_VDB_ARRAY_STRING(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                 \
                           AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,             \
                           LogFlag, PARAM_VAR, Status)                                                                                        \
}

//***************************************************************************************************************************************
//
// FUNCTION:
//
//    COPY_VDB_ELEM_ARRAY_TO_VDB_DIRECTLY
//
// DESCRIPTION:
//
//    This macros copy Vdb ArrName_Index value to Vbd with name VarCopy
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : Index of array
//    VarCopy : Vdb Name to which copy
//
// OUTPUT:
//    Status  : Status of execution
//
//*******************************************************************
#define COPY_VDB_ELEM_ARRAY_TO_VDB_DIRECTLY(ArrName, Index, VarCopy, Status)                                                         \
   {                                                                                                                                 \
      varid_t ArrElemId;                                                                                                             \
      STATUS  CopyArrElemStatus = 0;                                                                                                 \
      type_t  CopyArrElemType = TYPE_NONE;                                                                                           \
      char tmpVar[10];                                                                                                               \
      if (Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                                                 \
      {                                                                                                                              \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                                       \
         CopyArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &CopyArrElemType);                                                  \
         CopyArrElemStatus += OS_VarDB_ReadVariable(ArrElemId, &tmpVar, GET_VAR_LENGTH(CopyArrElemType), 0);                         \
         if (CopyArrElemStatus != 0)                                                                                                 \
         {                                                                                                                           \
            AppDebugLog(4444, "COPY_VDB_ELEM_ARRAY_TO_VDB_DIRECTLY: Id %d Status %d ", ArrElemId, CopyArrElemStatus);                \
         }                                                                                                                           \
         else                                                                                                                        \
         {                                                                                                                           \
            CopyArrElemStatus += OS_VarDB_UpdateVariableConditionalByName(#VarCopy, &tmpVar, GET_VAR_LENGTH(CopyArrElemType));       \
            if (CopyArrElemStatus != 0)                                                                                              \
            {                                                                                                                        \
               AppDebugLog(4444, "COPY_VDB_ELEM_ARRAY_TO_VDB_DIRECTLY: Id %d Status %d ", ArrElemId, CopyArrElemStatus);             \
            }                                                                                                                        \
         }                                                                                                                           \
      }                                                                                                                              \
      else                                                                                                                           \
      {                                                                                                                              \
         CopyArrElemStatus += ERR_VARDB_NOT_FOUND;                                                                                   \
      }                                                                                                                              \
      \
      Status += CopyArrElemStatus;                                                                                                   \
   }


//***************************************************************************************************************
//
// FUNCTION:
//
//    COPY_VDB_ELEM_ARRAY_TO_VAR
//
// DESCRIPTION:
//
//    This macros copy Vdb ArrName_Index value to variable with name VarCopy
//
// INPUT:
//
//    ArrName : Name of array
//    Index   : Index of array
//    VarCopy : Variable name to which copy
//
// OUTPUT:
//    Status  : Status of execution
//
//***************************************************************************************************************
#define COPY_VDB_ELEM_ARRAY_TO_VAR(ArrName, Index, VarCopy, Status)                                              \
   {                                                                                                             \
      varid_t ArrElemId;                                                                                         \
      STATUS  CopyArrElemStatus = 0;                                                                             \
      type_t  CopyArrElemType = TYPE_NONE;                                                                       \
      if (Index < GET_VAR_ARRAY_LENGTH_VAR(ArrName))                                                             \
      {                                                                                                          \
         ArrElemId = GET_VDB_ARRAY_IDENT_NAME(ArrName)[Index];                                                   \
         CopyArrElemStatus = OS_VarDB_GetVariableType(ArrElemId, &CopyArrElemType);                              \
         CopyArrElemStatus += OS_VarDB_ReadVariable(ArrElemId, &VarCopy, GET_VAR_LENGTH(CopyArrElemType), 0);    \
         if (CopyArrElemStatus != 0)                                                                             \
         {                                                                                                       \
            AppDebugLog(4444, "COPY_VDB_ELEM_ARRAY_TO_VAR: Id %d Status %d ", ArrElemId, CopyArrElemStatus);     \
         }                                                                                                       \
      }                                                                                                          \
      else                                                                                                       \
      {                                                                                                          \
         CopyArrElemStatus += ERR_VARDB_NOT_FOUND;                                                               \
      }                                                                                                          \
      \
      Status += CopyArrElemStatus;                                                                               \
   }

//
//===============Helper macros for managing arrays of VarDB with separate init values for each element===================
//

//***********************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_VAL_T_MIX
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup) with separate init values for each array element
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    Call CREATE_VDB_ARRAY_MIX, CREATE_VDB_ARRAY_F32_MIX or CREATE_VDB_ARRAY_F64_MIX instead of directly this.
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//***********************************************************************************************************************
#define CREATE_VDB_ARRAY_VAL_T_MIX(pPool,          /*Memory pool*/                                                                  \
                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/          \
                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                               \
                                   ArrType,        /*Type of array*/                                                                \
                                   Length,         /*Length of array*/                                                              \
                                   AccessRead,     /*Access read level*/                                                            \
                                   AccessWrite,    /*Access write level*/                                                           \
                                   ScaleType,      /*Scale type*/                                                                   \
                                   ScaleValue,     /*Scale value*/                                                                  \
                                   Unit,           /*Unit type*/                                                                    \
                                   Precision,      /*Precision*/                                                                    \
                                   InitValue,      /*Init value*/                                                                   \
                                   MinValue,       /*Minimum value*/                                                                \
                                   MaxValue,       /*Maximum value*/                                                                \
                                   Lists,          /*Select list*/                                                                  \
                                   LogFlag,        /*Log flag*/                                                                     \
                                   VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                        \
                                   Status)         /*Status*/                                                                       \
{                                                                                                                                   \
   do                                                                                                                               \
   {                                                                                                                                \
      int     IsString = 0;                                                                                                         \
      char    ArrElemName[50];                                                                                                      \
      varid_t ArrElemId;                                                                                                            \
      STATUS  CreateArrElemStatus;                                                                                                  \
      int i = 0;                                                                                                                    \
      unsigned int Alloc_length = GET_VAR_LENGTH(GET_VAR_ARRAY_TYPE_VAR(ArrName));                                                  \
      if ((GET_VAR_ARRAY_TYPE_VAR(ArrName) & TYPE_TYPE_MASK) == TYPE_STRING)                                                        \
      {                                                                                                                             \
         Alloc_length = Alloc_length + 1;                                                                                           \
         IsString = 1;                                                                                                              \
      }                                                                                                                             \
      \
      Length = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                                    \
      if (Length <= 0)                                                                                                              \
      {                                                                                                                             \
         Status = Length;                                                                                                           \
         break;                                                                                                                     \
      }                                                                                                                             \
      \
      Status =  AllocVdbIdsArray(pPool, &GET_VDB_ARRAY_IDENT_NAME(ArrName), Length);                                                \
      if (Status != OS_SUCCESS)                                                                                                     \
      {                                                                                                                             \
         AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Err Alloc Arr %d", ArrElemName, Status);                                           \
         break;                                                                                                                     \
      }                                                                                                                             \
      \
      for (i = 0; i < Length; ++i)                                                                                                  \
      {                                                                                                                             \
         int IsVdbCreated = 0;                                                                                                      \
         value_t ValueStr;                                                                                                          \
         sprintf(ArrElemName, "%s_%d", ArrNameString, i);/** UPDATE **/                                                             \
         CreateArrElemStatus = OS_VarDB_GetVariableID( ArrElemName, &ArrElemId );                                                   \
         if (IsString)                                                                                                              \
         {                                                                                                                          \
            ValueStr.string = InitValue[i].string;                                                                                  \
            char*  StrBuf = (char*)SysAllocDataMemory(pPool, Alloc_length);                                                         \
            if (NULL == StrBuf)                                                                                                     \
            {                                                                                                                       \
               Status = ERR_MEMORY_NOT_FOUND;                                                                                       \
               AppDebugLog(4444, "CREATE_STR_BUFF: %s ", ArrElemName);                                                              \
               AppDebugLog(4444, "CREATE_STR_BUFF: Err Alloc Arr %d", Status);                                                      \
            }                                                                                                                       \
            strncpy( StrBuf, ValueStr.string, (size_t )Alloc_length);                                                               \
            InitValue[i].string = StrBuf;                                                                                           \
         }                                                                                                                          \
         if (CreateArrElemStatus == ERR_VARDB_NOT_FOUND)                                                                            \
         {                                                                                                                          \
            switch (VdbType)                                                                                                        \
            {                                                                                                                       \
               case LOCAL_VAR:                                                                                                      \
               {                                                                                                                    \
                  CreateArrElemStatus = createVarDB_Local(pPool, ArrElemName, ArrType, AccessRead, AccessWrite,                     \
                                                          ScaleType, ScaleValue, Unit, Precision,                                   \
                                                          InitValue[i], MinValue, MaxValue, LogFlag);                               \
                  IsVdbCreated = (CreateArrElemStatus == OS_SUCCESS);                                                               \
                  break;                                                                                                            \
               }                                                                                                                    \
               case BACKUP_VAR:                                                                                                     \
               {                                                                                                                    \
                  CreateArrElemStatus = createVarDB_Backup(pPool, ArrElemName, ArrType, AccessRead, AccessWrite,                    \
                                                           ScaleType, ScaleValue, Unit, Precision,                                  \
                                                           InitValue[i], MinValue, MaxValue, LogFlag);                              \
                  IsVdbCreated = (CreateArrElemStatus == OS_SUCCESS);                                                               \
                  break;                                                                                                            \
               }                                                                                                                    \
               case PARAM_VAR:                                                                                                      \
               {                                                                                                                    \
                  CreateArrElemStatus = createVarDB_Parameter(pPool, ArrElemName, ArrType, AccessRead, AccessWrite,                 \
                                                              ScaleType, ScaleValue, Unit, Precision,                               \
                                                              InitValue[i], MinValue, MaxValue, LogFlag);                           \
                  IsVdbCreated = (CreateArrElemStatus == OS_SUCCESS);                                                               \
                  break;                                                                                                            \
               }                                                                                                                    \
               default:                                                                                                             \
               {                                                                                                                    \
                  AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Wrong update type: %d", ArrElemName, VdbType);                            \
                  CreateArrElemStatus = ERR_VARDB_WRONG_UPDATE;                                                                     \
               }                                                                                                                    \
            }                                                                                                                       \
            \
            if (IsVdbCreated)                                                                                                       \
            {                                                                                                                       \
               CreateArrElemStatus =  OS_VarDB_GetVariableID(ArrElemName, &ArrElemId);                                              \
               if (CreateArrElemStatus == OS_SUCCESS)                                                                               \
               {                                                                                                                    \
                  GET_VDB_ARRAY_IDENT_NAME(ArrName)[i] = ArrElemId;                                                                 \
               }                                                                                                                    \
               else                                                                                                                 \
               {                                                                                                                    \
                  AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Err Get Id ", ArrElemName);                                               \
               }                                                                                                                    \
            }                                                                                                                       \
            else                                                                                                                    \
            {                                                                                                                       \
               AppDebugLog(4444, "CREATE_VDB_ARRAY: %s Err Creation Status %d", ArrElemName, CreateArrElemStatus);                  \
            }                                                                                                                       \
         }                                                                                                                          \
         else                                                                                                                       \
         {                                                                                                                          \
            AppDebugLog(4444, "CREATE_VDB_ARRAY: %s already exist!", ArrElemName);                                                  \
            CreateArrElemStatus = ERR_VARDB_VARIABLE_EXISTS;                                                                        \
         }                                                                                                                          \
         \
         Status += CreateArrElemStatus;                                                                                             \
      }                                                                                                                             \
   }                                                                                                                                \
   while (0);                                                                                                                       \
}

//***********************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_MIX
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup) with separate init values for each array element
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for init of U8-U64, S8-S64, STRING, TIME
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//     Status     : Status of execution
//
//*********************************************************************************************************************
#define CREATE_VDB_ARRAY_MIX(pPool,          /*Memory pool*/                                                              \
                             ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/      \
                             ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                           \
                             ArrType,        /*Type of array*/                                                            \
                             Length,         /*Length of array*/                                                          \
                             AccessRead,     /*Access read level*/                                                        \
                             AccessWrite,    /*Access write level*/                                                       \
                             ScaleType,      /*Scale type*/                                                               \
                             ScaleValue,     /*Scale value*/                                                              \
                             Unit,           /*Unit type*/                                                                \
                             Precision,      /*Precision*/                                                                \
                             InitValue,      /*Init value*/                                                               \
                             MinValue,       /*Minimum value*/                                                            \
                             MaxValue,       /*Maximum value*/                                                            \
                             Lists,          /*Select list*/                                                              \
                             LogFlag,        /*Log flag*/                                                                 \
                             VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                    \
                             Status)         /*Status*/                                                                   \
{                                                                                                                         \
   do                                                                                                                     \
   {                                                                                                                      \
      int arrLength = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                   \
      if (arrLength <= 0)                                                                                                 \
      {                                                                                                                   \
         AppDebugLog(4444, "CREATE_VDB_ARRAY_MIX: %s Incorrect Length of Array: %s", ArrNameString, arrLength);           \
      }                                                                                                                   \
      \
      int i;                                                                                                              \
      value_t val[arrLength], min, max;                                                                                   \
      for (i = 0; i < arrLength; ++i)                                                                                     \
      {                                                                                                                   \
         val[i].u64 = InitValue[i];                                                                                       \
      }                                                                                                                   \
      min.u64 = MinValue;                                                                                                 \
      max.u64 = MaxValue;                                                                                                 \
      CREATE_VDB_ARRAY_VAL_T_MIX(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                 \
                                 ScaleType, ScaleValue, Unit, Precision, val, min, max,                                   \
                                 Lists, LogFlag, VdbType, Status);                                                        \
   }                                                                                                                      \
   while (0);                                                                                                             \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_F64_MIX
//
// DESCRIPTION:
//
//    This macros create array of VarDB (Local, Parameter, Backup) with separate init values for each array element
//    Need to call this macros if Init Round 1 for creation of variables in VarDB
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for initialization of F64
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_F64_MIX(pPool,          /*Memory pool*/                                                              \
                                 ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/      \
                                 ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                           \
                                 ArrType,        /*Type of array*/                                                            \
                                 Length,         /*Length of array*/                                                          \
                                 AccessRead,     /*Access read level*/                                                        \
                                 AccessWrite,    /*Access write level*/                                                       \
                                 ScaleType,      /*Scale type*/                                                               \
                                 ScaleValue,     /*Scale value*/                                                              \
                                 Unit,           /*Unit type*/                                                                \
                                 Precision,      /*Precision*/                                                                \
                                 InitValue,      /*Init value*/                                                               \
                                 MinValue,       /*Minimum value*/                                                            \
                                 MaxValue,       /*Maximum value*/                                                            \
                                 Lists,          /*Select list*/                                                              \
                                 LogFlag,        /*Log flag*/                                                                 \
                                 VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                    \
                                 Status)         /*Status*/                                                                   \
{                                                                                                                             \
   do                                                                                                                         \
   {                                                                                                                          \
      int arrLength = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                       \
      if (arrLength <= 0)                                                                                                     \
      {                                                                                                                       \
         AppDebugLog(4444, "CREATE_VDB_ARRAY_MIX: %s Incorrect Length of Array: %s", ArrNameString, arrLength);               \
      }                                                                                                                       \
      \
      int i;                                                                                                                  \
      value_t val[arrLength], min, max;                                                                                       \
      for (i = 0; i < arrLength; ++i)                                                                                         \
      {                                                                                                                       \
         val[i].f64 = InitValue[i];                                                                                           \
      }                                                                                                                       \
      min.f64 = MinValue;                                                                                                     \
      max.f64 = MaxValue;                                                                                                     \
      CREATE_VDB_ARRAY_VAL_T_MIX(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                     \
                                 ScaleType, ScaleValue, Unit, Precision, val, min, max,                                       \
                                 Lists, LogFlag, VdbType, Status);                                                            \
   }                                                                                                                          \
   while (0);                                                                                                                 \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_F32_MIX
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup) with separate init values for each array element
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for init of F32
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_F32_MIX(pPool,          /*Memory pool*/                                                              \
                                 ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/      \
                                 ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                           \
                                 ArrType,        /*Type of array*/                                                            \
                                 Length,         /*Length of array*/                                                          \
                                 AccessRead,     /*Access read level*/                                                        \
                                 AccessWrite,    /*Access write level*/                                                       \
                                 ScaleType,      /*Scale type*/                                                               \
                                 ScaleValue,     /*Scale value*/                                                              \
                                 Unit,           /*Unit type*/                                                                \
                                 Precision,      /*Precision*/                                                                \
                                 InitValue,      /*Init value*/                                                               \
                                 MinValue,       /*Minimum value*/                                                            \
                                 MaxValue,       /*Maximum value*/                                                            \
                                 Lists,          /*Select list*/                                                              \
                                 LogFlag,        /*Log flag*/                                                                 \
                                 VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                    \
                                 Status)         /*Status*/                                                                   \
{                                                                                                                             \
   do                                                                                                                         \
   {                                                                                                                          \
      int arrLength = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                       \
      if (arrLength <= 0)                                                                                                     \
      {                                                                                                                       \
         AppDebugLog(4444, "CREATE_VDB_ARRAY_MIX: %s Incorrect Length of Array: %s", ArrNameString, arrLength);               \
      }                                                                                                                       \
      \
      int i;                                                                                                                  \
      value_t val[arrLength], min, max;                                                                                       \
      for (i = 0; i < arrLength; ++i)                                                                                         \
      {                                                                                                                       \
         val[i].f32 = InitValue[i];                                                                                           \
      }                                                                                                                       \
      min.f32 = MinValue;                                                                                                     \
      max.f32 = MaxValue;                                                                                                     \
      CREATE_VDB_ARRAY_VAL_T_MIX(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                     \
                                 ScaleType, ScaleValue, Unit, Precision, val, min, max,                                       \
                                 Lists, LogFlag, VdbType, Status);                                                            \
   }                                                                                                                          \
   while (0);                                                                                                                 \
}

//**********************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_STRING_MIX
//
// DESCRIPTION:
//
//    This macros create array of Vdbs (Local, Parameter, Backup) with separate init values for each array element
//    Need to call this macros if Init Round 1 fro creation Vbd
//    This helper macros which used other macros for creation Locals, Parameters, Backups
//
//    USE for init of U8-U64, S8-S64, STRING, TIME
//
// INPUT:
//
//    pPool       : Memory pool
//    ArrName     : Name of array
//    ArrType     : Type of array
//    Length      : Length of array
//    AccessRead  : Access read level
//    AccessWrite : Access write level
//    ScaleType   : Scale type
//    ScaleValue  : Scale value
//    Unit        : Unit type
//    Precision   : Precision
//    InitValue   : Init value
//    MinValue    : Minimum value
//    MaxValue    : Maximum value
//    Lists       : Select list
//    LogFlag     : Log flag
//    VdbType     : Type of VDB(Local, Parameter, Backup)
//
// OUTPUT:
//    Status      : Status of execution
//
//****************************************************************************************************************************
#define CREATE_VDB_ARRAY_STRING_MIX(pPool,          /*Memory pool*/                                                              \
                                    ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/      \
                                    ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                           \
                                    ArrType,        /*Type of array*/                                                            \
                                    Length,         /*Length of array*/                                                          \
                                    AccessRead,     /*Access read level*/                                                        \
                                    AccessWrite,    /*Access write level*/                                                       \
                                    ScaleType,      /*Scale type*/                                                               \
                                    ScaleValue,     /*Scale value*/                                                              \
                                    Unit,           /*Unit type*/                                                                \
                                    Precision,      /*Precision*/                                                                \
                                    InitValue,      /*Init value*/                                                               \
                                    MinValue,       /*Minimum value*/                                                            \
                                    MaxValue,       /*Maximum value*/                                                            \
                                    Lists,          /*Select list*/                                                              \
                                    LogFlag,        /*Log flag*/                                                                 \
                                    VdbType,        /*Type of VDB(Local, Parameter, Backup)*/                                    \
                                    Status)         /*Status*/                                                                   \
{                                                                                                                                \
   do                                                                                                                            \
   {                                                                                                                             \
      int arrLength = GetLength(GET_VAR_ARRAY_LENGTH_VAR_TXT(ArrName));                                                          \
      if (arrLength <= 0)                                                                                                        \
      {                                                                                                                          \
         AppDebugLog(4444, "CREATE_VDB_ARRAY_MIX: %s Incorrect Length of Array: %s", ArrNameString, arrLength);                  \
      }                                                                                                                          \
      \
      int i;                                                                                                                     \
      value_t val[arrLength], min, max;                                                                                          \
      for (i = 0; i < arrLength; ++i)                                                                                            \
      {                                                                                                                          \
         val[i].string = InitValue[i];                                                                                           \
      }                                                                                                                          \
      CREATE_VDB_ARRAY_VAL_T_MIX(pPool, ArrNameString, ArrName, ArrType, Length, AccessRead, AccessWrite,                        \
                                 ScaleType, ScaleValue, Unit, Precision, val, min, max,                                          \
                                 Lists, LogFlag, VdbType, Status);                                                               \
   }                                                                                                                             \
   while (0);                                                                                                                    \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL_MIX
//
// DESCRIPTION:
//
//    This macros create array of Local Vdbs with separate init values for each array element
//    This macros is wrapper under CREATE_VDB_ARRAY
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_MIX(pPool,          /*Memory pool*/                                                                  \
                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/          \
                                   ArrName,        /*Name of array, with \" stripped *//* UPDATE */                                 \
                                   AccessRead,     /*Access read level*/                                                            \
                                   AccessWrite,    /*Access write level*/                                                           \
                                   ScaleType,      /*Scale type*/                                                                   \
                                   ScaleValue,     /*Scale value*/                                                                  \
                                   Unit,           /*Unit type*/                                                                    \
                                   Precision,      /*Precision*/                                                                    \
                                   InitValue,      /*Init value*/                                                                   \
                                   MinValue,       /*Minimum value*/                                                                \
                                   MaxValue,       /*Maximum value*/                                                                \
                                   Lists,          /*Select list*/                                                                  \
                                   LogFlag,        /*Log flag*/                                                                     \
                                   Status)         /*Status*/                                                                       \
{                                                                                                                                   \
   CREATE_VDB_ARRAY_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),          \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,      \
                        LogFlag, LOCAL_VAR, Status)                                                                                 \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                \
}

//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                               ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                               ArrName,        /*Name of array, with \" stripped *//* UPDATE */                         \
                                               AccessRead,     /*Access read level*/                                                    \
                                               ScaleType,      /*Scale type*/                                                           \
                                               AccessWrite,    /*Access write level*/                                                   \
                                               ScaleValue,     /*Scale value*/                                                          \
                                               Unit,           /*Unit type*/                                                            \
                                               Precision,      /*Precision*/                                                            \
                                               InitValue,      /*Init value*/                                                           \
                                               MinValue,       /*Minimum value*/                                                        \
                                               MaxValue,       /*Maximum value*/                                                        \
                                               Lists,          /*Select list*/                                                          \
                                               LogFlag,        /*Log flag*/                                                             \
                                               Status)         /*Status*/                                                               \
{                                                                                                                                       \
   CREATE_VDB_ARRAY_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName),  GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                        LogFlag, LOCAL_VAR, Status)                                                                                     \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL_F64_MIX
//
// DESCRIPTION:
//
//    This macros create array of Local F64 Vdbs with separate init values for each array element
//    This macros is wrapper under CREATE_VDB_ARRAY_MIX
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F64_MIX(pPool,          /*Memory pool*/                                                                 \
                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                       AccessRead,     /*Access read level*/                                                           \
                                       AccessWrite,    /*Access write level*/                                                          \
                                       ScaleType,      /*Scale type*/                                                                  \
                                       ScaleValue,     /*Scale value*/                                                                 \
                                       Unit,           /*Unit type*/                                                                   \
                                       Precision,      /*Precision*/                                                                   \
                                       InitValue,      /*Init value*/                                                                  \
                                       MinValue,       /*Minimum value*/                                                               \
                                       MaxValue,       /*Maximum value*/                                                               \
                                       Lists,          /*Select list*/                                                                 \
                                       LogFlag,        /*Log flag*/                                                                    \
                                       Status)         /*Status*/                                                                      \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F64_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                            LogFlag, LOCAL_VAR, Status)                                                                                \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                   \
}

//***************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F64_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                   AccessRead,     /*Access read level*/                                                    \
                                                   AccessWrite,    /*Access write level*/                                                   \
                                                   ScaleType,      /*Scale type*/                                                           \
                                                   ScaleValue,     /*Scale value*/                                                          \
                                                   Unit,           /*Unit type*/                                                            \
                                                   Precision,      /*Precision*/                                                            \
                                                   InitValue,      /*Init value*/                                                           \
                                                   MinValue,       /*Minimum value*/                                                        \
                                                   MaxValue,       /*Maximum value*/                                                        \
                                                   Lists,          /*Select list*/                                                          \
                                                   LogFlag,        /*Log flag*/                                                             \
                                                   Status)         /*Status*/                                                               \
{                                                                                                                                           \
   CREATE_VDB_ARRAY_F64_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),              \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                            LogFlag, LOCAL_VAR, Status)                                                                                     \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL_F32_MIX
//
// DESCRIPTION:
//
//    This macros create array of Local F32 Vdbs with separate init values for each array element
//    This macros is wrapper under CREATE_VDB_ARRAY_MIX
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F32_MIX(pPool,          /*Memory pool*/                                                                 \
                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                       AccessRead,     /*Access read level*/                                                           \
                                       AccessWrite,    /*Access write level*/                                                          \
                                       ScaleType,      /*Scale type*/                                                                  \
                                       ScaleValue,     /*Scale value*/                                                                 \
                                       Unit,           /*Unit type*/                                                                   \
                                       Precision,      /*Precision*/                                                                   \
                                       InitValue,      /*Init value*/                                                                  \
                                       MinValue,       /*Minimum value*/                                                               \
                                       MaxValue,       /*Maximum value*/                                                               \
                                       Lists,          /*Select list*/                                                                 \
                                       LogFlag,        /*Log flag*/                                                                    \
                                       Status)         /*Status*/                                                                      \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F32_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue,            \
                            Lists, LogFlag, LOCAL_VAR, Status)                                                                         \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                   \
}

//***************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_F32_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                   ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                   AccessRead,     /*Access read level*/                                                    \
                                                   AccessWrite,    /*Access write level*/                                                   \
                                                   ScaleType,      /*Scale type*/                                                           \
                                                   ScaleValue,     /*Scale value*/                                                          \
                                                   Unit,           /*Unit type*/                                                            \
                                                   Precision,      /*Precision*/                                                            \
                                                   InitValue,      /*Init value*/                                                           \
                                                   MinValue,       /*Minimum value*/                                                        \
                                                   MaxValue,       /*Maximum value*/                                                        \
                                                   Lists,          /*Select list*/                                                          \
                                                   LogFlag,        /*Log flag*/                                                             \
                                                   Status)         /*Status*/                                                               \
{                                                                                                                                           \
   CREATE_VDB_ARRAY_F32_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),              \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                            LogFlag, LOCAL_VAR, Status)                                                                                     \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_LOCAL_STRING_MIX
//
// DESCRIPTION:
//
//    This macros create array of Local String Vdbs with separate init values for each array element
//    This macros is wrapper under CREATE_VDB_ARRAY_MIX
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
//**************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_STRING_MIX(pPool,          /*Memory pool*/                                                                 \
                                          ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                          ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                          AccessRead,     /*Access read level*/                                                           \
                                          AccessWrite,    /*Access write level*/                                                          \
                                          ScaleType,      /*Scale type*/                                                                  \
                                          ScaleValue,     /*Scale value*/                                                                 \
                                          Unit,           /*Unit type*/                                                                   \
                                          Precision,      /*Precision*/                                                                   \
                                          InitValue,      /*Init value*/                                                                  \
                                          MinValue,       /*Minimum value*/                                                               \
                                          MaxValue,       /*Maximum value*/                                                               \
                                          Lists,          /*Select list*/                                                                 \
                                          LogFlag,        /*Log flag*/                                                                    \
                                          Status)         /*Status*/                                                                      \
{                                                                                                                                         \
   CREATE_VDB_ARRAY_STRING_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                               AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                               LogFlag, LOCAL_VAR, Status)                                                                                \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                      \
}

//******************************************************************************************************************************************
#define CREATE_VDB_ARRAY_LOCAL_STRING_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                      ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                      ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                      AccessRead,     /*Access read level*/                                                    \
                                                      AccessWrite,    /*Access write level*/                                                   \
                                                      ScaleType,      /*Scale type*/                                                           \
                                                      ScaleValue,     /*Scale value*/                                                          \
                                                      Unit,           /*Unit type*/                                                            \
                                                      Precision,      /*Precision*/                                                            \
                                                      InitValue,      /*Init value*/                                                           \
                                                      MinValue,       /*Minimum value*/                                                        \
                                                      MaxValue,       /*Maximum value*/                                                        \
                                                      Lists,          /*Select list*/                                                          \
                                                      LogFlag,        /*Log flag*/                                                             \
                                                      Status)         /*Status*/                                                               \
{                                                                                                                                              \
   CREATE_VDB_ARRAY_STRING_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),              \
                               AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,          \
                               LogFlag, LOCAL_VAR, Status)                                                                                     \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_BACKUP_MIX
//
// DESCRIPTION:
//
//    This macros create array of Backup Vdbs with separate init values for each array element
//    This macros is wrapper under CREATE_VDB_ARRAY_MIX
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
//*******************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_MIX(pPool,         /*Memory pool*/                                                                 \
                                    ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                    ArrName,        /*Name of array, with \" stripped *//* UPDATE */                               \
                                    AccessRead,     /*Access read level*/                                                          \
                                    AccessWrite,    /*Access write level*/                                                         \
                                    ScaleType,      /*Scale type*/                                                                 \
                                    ScaleValue,     /*Scale value*/                                                                \
                                    Unit,           /*Unit type*/                                                                  \
                                    Precision,      /*Precision*/                                                                  \
                                    InitValue,      /*Init value*/                                                                 \
                                    MinValue,       /*Minimum value*/                                                              \
                                    MaxValue,       /*Maximum value*/                                                              \
                                    Lists,          /*Select list*/                                                                \
                                    LogFlag,        /*Log flag*/                                                                   \
                                    Status)         /*Status*/                                                                     \
{                                                                                                                                  \
   CREATE_VDB_ARRAY_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                        LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                               \
}

//************************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_WITHOUT_REF_MIX(pPool,         /*Memory pool*/                                                           \
                                                ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                ArrName,        /*Name of array, with \" stripped *//* UPDATE */                         \
                                                AccessRead,     /*Access read level*/                                                    \
                                                AccessWrite,    /*Access write level*/                                                   \
                                                ScaleType,      /*Scale type*/                                                           \
                                                ScaleValue,     /*Scale value*/                                                          \
                                                Unit,           /*Unit type*/                                                            \
                                                Precision,      /*Precision*/                                                            \
                                                InitValue,      /*Init value*/                                                           \
                                                MinValue,       /*Minimum value*/                                                        \
                                                MaxValue,       /*Maximum value*/                                                        \
                                                Lists,          /*Select list*/                                                          \
                                                LogFlag,        /*Log flag*/                                                             \
                                                Status)         /*Status*/                                                               \
{                                                                                                                                        \
   CREATE_VDB_ARRAY_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),               \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,           \
                        LogFlag, BACKUP_VAR, Status)                                                                                     \
}

//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F64_MIX(pPool,         /*Memory pool*/                                                                 \
                                        ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                        ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                             \
                                        AccessRead,     /*Access read level*/                                                          \
                                        AccessWrite,    /*Access write level*/                                                         \
                                        ScaleType,      /*Scale type*/                                                                 \
                                        ScaleValue,     /*Scale value*/                                                                \
                                        Unit,           /*Unit type*/                                                                  \
                                        Precision,      /*Precision*/                                                                  \
                                        InitValue,      /*Init value*/                                                                 \
                                        MinValue,       /*Minimum value*/                                                              \
                                        MaxValue,       /*Maximum value*/                                                              \
                                        Lists,          /*Select list*/                                                                \
                                        LogFlag,        /*Log flag*/                                                                   \
                                        Status)         /*Status*/                                                                     \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F64_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                            LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                   \
}

//***********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F64_WITHOUT_REF_MIX(pPool,         /*Memory pool*/                                                           \
                                                    ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                    ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                    AccessRead,     /*Access read level*/                                                    \
                                                    AccessWrite,    /*Access write level*/                                                   \
                                                    ScaleType,      /*Scale type*/                                                           \
                                                    ScaleValue,     /*Scale value*/                                                          \
                                                    Unit,           /*Unit type*/                                                            \
                                                    Precision,      /*Precision*/                                                            \
                                                    InitValue,      /*Init value*/                                                           \
                                                    MinValue,       /*Minimum value*/                                                        \
                                                    MaxValue,       /*Maximum value*/                                                        \
                                                    Lists,          /*Select list*/                                                          \
                                                    LogFlag,        /*Log flag*/                                                             \
                                                    Status)         /*Status*/                                                               \
{                                                                                                                                            \
   CREATE_VDB_ARRAY_F64_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),               \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,           \
                            LogFlag, BACKUP_VAR, Status)                                                                                     \
}

//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F32_MIX(pPool,          /*Memory pool*/                                                                \
                                        ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                        ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                             \
                                        AccessRead,     /*Access read level*/                                                          \
                                        AccessWrite,    /*Access write level*/                                                         \
                                        ScaleType,      /*Scale type*/                                                                 \
                                        ScaleValue,     /*Scale value*/                                                                \
                                        Unit,           /*Unit type*/                                                                  \
                                        Precision,      /*Precision*/                                                                  \
                                        InitValue,      /*Init value*/                                                                 \
                                        MinValue,       /*Minimum value*/                                                              \
                                        MaxValue,       /*Maximum value*/                                                              \
                                        Lists,          /*Select list*/                                                                \
                                        LogFlag,        /*Log flag*/                                                                   \
                                        Status)         /*Status*/                                                                     \
{                                                                                                                                      \
   CREATE_VDB_ARRAY_F32_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                            LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                   \
}

//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_F32_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                    ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                    ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                    AccessRead,     /*Access read level*/                                                    \
                                                    AccessWrite,    /*Access write level*/                                                   \
                                                    ScaleType,      /*Scale type*/                                                           \
                                                    ScaleValue,     /*Scale value*/                                                          \
                                                    Unit,           /*Unit type*/                                                            \
                                                    Precision,      /*Precision*/                                                            \
                                                    InitValue,      /*Init value*/                                                           \
                                                    MinValue,       /*Minimum value*/                                                        \
                                                    MaxValue,       /*Maximum value*/                                                        \
                                                    Lists,          /*Select list*/                                                          \
                                                    LogFlag,        /*Log flag*/                                                             \
                                                    Status)         /*Status*/                                                               \
{                                                                                                                                            \
   CREATE_VDB_ARRAY_F32_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),               \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,           \
                            LogFlag, BACKUP_VAR, Status)                                                                                     \
}

//******************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_BACKUP_STRING_MIX
//
// DESCRIPTION:
//
//    This macros create array of Backup VarDB with separate init values for each array element
//    This macros is wrapper under CREATE_VDB_ARRAY_MIX
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
//******************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_STRING_MIX(pPool,          /*Memory pool*/                                                                \
                                           ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                           ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                             \
                                           AccessRead,     /*Access read level*/                                                          \
                                           AccessWrite,    /*Access write level*/                                                         \
                                           ScaleType,      /*Scale type*/                                                                 \
                                           ScaleValue,     /*Scale value*/                                                                \
                                           Unit,           /*Unit type*/                                                                  \
                                           Precision,      /*Precision*/                                                                  \
                                           InitValue,      /*Init value*/                                                                 \
                                           MinValue,       /*Minimum value*/                                                              \
                                           MaxValue,       /*Maximum value*/                                                              \
                                           Lists,          /*Select list*/                                                                \
                                           LogFlag,        /*Log flag*/                                                                   \
                                           Status)         /*Status*/                                                                     \
{                                                                                                                                         \
   CREATE_VDB_ARRAY_STRING_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                               AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                               LogFlag, BACKUP_VAR, Status)                                                                               \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                      \
}

//******************************************************************************************************************************
#define CREATE_VDB_ARRAY_BACKUP_STRING_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                       AccessRead,     /*Access read level*/                                                    \
                                                       AccessWrite,    /*Access write level*/                                                   \
                                                       ScaleType,      /*Scale type*/                                                           \
                                                       ScaleValue,     /*Scale value*/                                                          \
                                                       Unit,           /*Unit type*/                                                            \
                                                       Precision,      /*Precision*/                                                            \
                                                       InitValue,      /*Init value*/                                                           \
                                                       MinValue,       /*Minimum value*/                                                        \
                                                       MaxValue,       /*Maximum value*/                                                        \
                                                       Lists,          /*Select list*/                                                          \
                                                       LogFlag,        /*Log flag*/                                                             \
                                                       Status)         /*Status*/                                                               \
{                                                                                                                                               \
   CREATE_VDB_ARRAY_STRING_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),               \
                               AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,           \
                               LogFlag, BACKUP_VAR, Status)                                                                                     \
}

//*********************************************************************************************************************************
//
// FUNCTION:
//
//    CREATE_VDB_ARRAY_PARAMETER_MIX
//
// DESCRIPTION:
//
//    This macros create array of Parameter VarDB with separate init values for each array element
//    This macros is wrapper under CREATE_VDB_ARRAY_MIX
//
// INPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
// OUTPUT:
//
//    Same as in CREATE_VDB_ARRAY_MIX
//
//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_MIX(pPool,         /*Memory pool*/                                                                 \
                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/        \
                                       ArrName,        /*Name of array, with \" stripped *//* UPDATE */                               \
                                       AccessRead,     /*Access read level*/                                                          \
                                       AccessWrite,    /*Access write level*/                                                         \
                                       ScaleType,      /*Scale type*/                                                                 \
                                       ScaleValue,     /*Scale value*/                                                                \
                                       Unit,           /*Unit type*/                                                                  \
                                       Precision,      /*Precision*/                                                                  \
                                       InitValue,      /*Init value*/                                                                 \
                                       MinValue,       /*Minimum value*/                                                              \
                                       MaxValue,       /*Maximum value*/                                                              \
                                       Lists,          /*Select list*/                                                                \
                                       LogFlag,        /*Log flag*/                                                                   \
                                       Status )        /*Status*/                                                                     \
{                                                                                                                                     \
   CREATE_VDB_ARRAY_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),            \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,        \
                        LogFlag, PARAM_VAR, Status)                                                                                   \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                  \
}

//***************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_WITHOUT_REF_MIX(pPool,         /*Memory pool*/                                                           \
                                                   ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                   ArrName,        /*Name of array, with \" stripped *//* UPDATE */                         \
                                                   AccessRead,     /*Access read level*/                                                    \
                                                   AccessWrite,    /*Access write level*/                                                   \
                                                   ScaleType,      /*Scale type*/                                                           \
                                                   ScaleValue,     /*Scale value*/                                                          \
                                                   Unit,           /*Unit type*/                                                            \
                                                   Precision,      /*Precision*/                                                            \
                                                   InitValue,      /*Init value*/                                                           \
                                                   MinValue,       /*Minimum value*/                                                        \
                                                   MaxValue,       /*Maximum value*/                                                        \
                                                   Lists,          /*Select list*/                                                          \
                                                   LogFlag,        /*Log flag*/                                                             \
                                                   Status)         /*Status*/                                                               \
{                                                                                                                                           \
   CREATE_VDB_ARRAY_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                  \
                        AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,              \
                        LogFlag, PARAM_VAR, Status)                                                                                         \
}

//***************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F64_MIX(pPool,          /*Memory pool*/                                                                 \
                                           ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                           ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                           AccessRead,     /*Access read level*/                                                           \
                                           AccessWrite,    /*Access write level*/                                                          \
                                           ScaleType,      /*Scale type*/                                                                  \
                                           ScaleValue,     /*Scale value*/                                                                 \
                                           Unit,           /*Unit type*/                                                                   \
                                           Precision,      /*Precision*/                                                                   \
                                           InitValue,      /*Init value*/                                                                  \
                                           MinValue,       /*Minimum value*/                                                               \
                                           MaxValue,       /*Maximum value*/                                                               \
                                           Lists,          /*Select list*/                                                                 \
                                           LogFlag,        /*Log flag*/                                                                    \
                                           Status)         /*Status*/                                                                      \
{                                                                                                                                          \
   CREATE_VDB_ARRAY_F64_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                            LogFlag, PARAM_VAR, Status)                                                                                    \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                       \
}

//*******************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F64_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                       AccessRead,     /*Access read level*/                                                    \
                                                       AccessWrite,    /*Access write level*/                                                   \
                                                       ScaleType,      /*Scale type*/                                                           \
                                                       ScaleValue,     /*Scale value*/                                                          \
                                                       Unit,           /*Unit type*/                                                            \
                                                       Precision,      /*Precision*/                                                            \
                                                       InitValue,      /*Init value*/                                                           \
                                                       MinValue,       /*Minimum value*/                                                        \
                                                       MaxValue,       /*Maximum value*/                                                        \
                                                       Lists,          /*Select list*/                                                          \
                                                       LogFlag,        /*Log flag*/                                                             \
                                                       Status)         /*Status*/                                                               \
{                                                                                                                                               \
   CREATE_VDB_ARRAY_F64_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                  \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,              \
                            LogFlag, PARAM_VAR, Status)                                                                                         \
}

//***************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F32_MIX(pPool,          /*Memory pool*/                                                                 \
                                           ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/         \
                                           ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                              \
                                           AccessRead,     /*Access read level*/                                                           \
                                           AccessWrite,    /*Access write level*/                                                          \
                                           ScaleType,      /*Scale type*/                                                                  \
                                           ScaleValue,     /*Scale value*/                                                                 \
                                           Unit,           /*Unit type*/                                                                   \
                                           Precision,      /*Precision*/                                                                   \
                                           InitValue,      /*Init value*/                                                                  \
                                           MinValue,       /*Minimum value*/                                                               \
                                           MaxValue,       /*Maximum value*/                                                               \
                                           Lists,          /*Select list*/                                                                 \
                                           LogFlag,        /*Log flag*/                                                                    \
                                           Status)         /*Status*/                                                                      \
{                                                                                                                                          \
   CREATE_VDB_ARRAY_F32_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),             \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,         \
                            LogFlag, PARAM_VAR, Status)                                                                                    \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                       \
}

//*******************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_F32_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                       ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                       ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                       AccessRead,     /*Access read level*/                                                    \
                                                       AccessWrite,    /*Access write level*/                                                   \
                                                       ScaleType,      /*Scale type*/                                                           \
                                                       ScaleValue,     /*Scale value*/                                                          \
                                                       Unit,           /*Unit type*/                                                            \
                                                       Precision,      /*Precision*/                                                            \
                                                       InitValue,      /*Init value*/                                                           \
                                                       MinValue,       /*Minimum value*/                                                        \
                                                       MaxValue,       /*Maximum value*/                                                        \
                                                       Lists,          /*Select list*/                                                          \
                                                       LogFlag,        /*Log flag*/                                                             \
                                                       Status)         /*Status*/                                                               \
{                                                                                                                                               \
   CREATE_VDB_ARRAY_F32_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                  \
                            AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,              \
                            LogFlag, PARAM_VAR, Status)                                                                                         \
}

//*********************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_STRING_MIX(pPool,          /*Memory pool*/                                                             \
                                              ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/     \
                                              ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                          \
                                              AccessRead,     /*Access read level*/                                                       \
                                              AccessWrite,    /*Access write level*/                                                      \
                                              ScaleType,      /*Scale type*/                                                              \
                                              ScaleValue,     /*Scale value*/                                                             \
                                              Unit,           /*Unit type*/                                                               \
                                              Precision,      /*Precision*/                                                               \
                                              InitValue,      /*Init value*/                                                              \
                                              MinValue,       /*Minimum value*/                                                           \
                                              MaxValue,       /*Maximum value*/                                                           \
                                              Lists,          /*Select list*/                                                             \
                                              LogFlag,        /*Log flag*/                                                                \
                                              Status)         /*Status*/                                                                  \
{                                                                                                                                         \
   CREATE_VDB_ARRAY_STRING_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),         \
                               AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,     \
                               LogFlag, PARAM_VAR, Status)                                                                                \
   ALLOCATE_MEMORY_FOR_ARRAY(pPool, ArrName, Status)                                                                                      \
}

//**********************************************************************************************************************************************
#define CREATE_VDB_ARRAY_PARAMETER_STRING_WITHOUT_REF_MIX(pPool,          /*Memory pool*/                                                          \
                                                          ArrNameString,  /*Name of array, string full name, created name in VDB *//** UPDATE **/  \
                                                          ArrName,        /*Name of array, with \" stripped *//** UPDATE **/                       \
                                                          AccessRead,     /*Access read level*/                                                    \
                                                          AccessWrite,    /*Access write level*/                                                   \
                                                          ScaleType,      /*Scale type*/                                                           \
                                                          ScaleValue,     /*Scale value*/                                                          \
                                                          Unit,           /*Unit type*/                                                            \
                                                          Precision,      /*Precision*/                                                            \
                                                          InitValue,      /*Init value*/                                                           \
                                                          MinValue,       /*Minimum value*/                                                        \
                                                          MaxValue,       /*Maximum value*/                                                        \
                                                          Lists,          /*Select list*/                                                          \
                                                          LogFlag,        /*Log flag*/                                                             \
                                                          Status)         /*Status*/                                                               \
{                                                                                                                                                  \
   CREATE_VDB_ARRAY_STRING_MIX(pPool, ArrNameString, ArrName, GET_VAR_ARRAY_TYPE_VAR(ArrName), GET_VAR_ARRAY_LENGTH_VAR(ArrName),                  \
                               AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, InitValue, MinValue, MaxValue, Lists,              \
                               LogFlag, PARAM_VAR, Status)                                                                                         \
}


//=======================================Helper functions for dynamically creation of VarDb========================
struct os_db_subparameter getSubparameter(value_t Minimum, value_t Maximum);
struct os_db_sublocal getSublocal(value_t Minimum, value_t Maximum);
struct os_db_subbackup getSubbackup(value_t Minimum, value_t Maximum);
struct os_db_common_fields getCommonFields(\
	OS_MEMORY_POOL* pPool, \
	enum update Update, \
	const char* Name, \
	type_t Type, \
	access_t AccessRead, \
	access_t AccessWrite, \
	scaletype_t ScaleType, \
	scalevalue_t ScaleValue, \
	unit_t Unit, \
	precision_t Precision, \
	value_t Value, \
	time_t LogFlag);

STATUS createVarDB_Parameter(\
	OS_MEMORY_POOL* pPool, \
	const char* Name, \
	type_t Type, \
	access_t AccessRead, \
	access_t AccessWrite, \
	scaletype_t ScaleType, \
	scalevalue_t ScaleValue, \
	unit_t Unit, \
	precision_t Precision, \
	value_t Value, \
	value_t Minimum, \
	value_t Maximum, \
	time_t LogFlag);

STATUS createVarDB_Backup(\
	OS_MEMORY_POOL* pPool, \
	const char* Name, \
	type_t Type, \
	access_t AccessRead, \
	access_t AccessWrite, \
	scaletype_t ScaleType, \
	scalevalue_t ScaleValue, \
	unit_t Unit, \
	precision_t Precision, \
	value_t Value, \
	value_t Minimum, \
	value_t Maximum, \
	time_t LogFlag);

STATUS createVarDB_Local(\
	OS_MEMORY_POOL* pPool, \
	const char* Name, \
	type_t Type, \
	access_t AccessRead, \
	access_t AccessWrite, \
	scaletype_t ScaleType, \
	scalevalue_t ScaleValue, \
	unit_t Unit, \
	precision_t Precision, \
	value_t Value, \
	value_t Minimum, \
	value_t Maximum, \
	time_t LogFlag);
//-------------------------------------------------------------------------------------------------------------------------------
char* GetArrayElemName(char* ArrName, int Index);

int  GetLength(char* Len);
STATUS AllocVdbIdsArray(OS_MEMORY_POOL* pPool, varid_t** ArrId, int Length);
STATUS AllocVdbDataArray(OS_MEMORY_POOL* pPool, void** ArrName, int Length, int ElemSize);

#endif
