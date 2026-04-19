//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2017 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:110$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: DESKTOP-3H3JCEK\jaakl $                                                           
// $RCSfile: VarArrayMacros.c,v $                                                
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

#include "VarArrayMacros.h"

//=======================================Helper functions for dynamicaly creation of VarDb=======================================
struct os_db_subparameter getSubparameter(\
      value_t Minimum,\
      value_t Maximum)
{

   struct os_db_subparameter subparameter;

   subparameter.FileID       = NULL;
   subparameter.Minimum      = Minimum;
   subparameter.Maximum      = Maximum;
   subparameter.Lists        = NULL;
   subparameter.DefaultValue.u64 = 0;
   subparameter.ChangeFlag   = 0;

   return subparameter;
}

struct os_db_subbackup getSubbackup(\
                                    value_t Minimum,\
                                    value_t Maximum)
{

   struct os_db_subbackup subbackup;

   subbackup.LogFlags     = NULL;
   subbackup.FileID       = NULL;
   subbackup.ChangeFlag   = 0;
   subbackup.Minimum      = Minimum;
   subbackup.Maximum      = Maximum;
   subbackup.Lists        = NULL;
   subbackup.DefaultValue.u64 = 0;

   return subbackup;
}

struct os_db_sublocal getSublocal(\
                                  value_t Minimum,\
                                  value_t Maximum)
{

   struct os_db_sublocal sublocal;

   sublocal.LogFlags = NULL;
   sublocal.Minimum = Minimum;
   sublocal.Maximum = Maximum;
   sublocal.Lists = NULL;

   return sublocal;
}

struct os_db_common_fields getCommonFields(\
      OS_MEMORY_POOL* pPool,\
      enum update Update,\
      const char* Name,\
      type_t Type,\
      access_t AccessRead,\
      access_t AccessWrite,\
      scaletype_t ScaleType,\
      scalevalue_t ScaleValue,\
      unit_t Unit,\
      precision_t Precision,\
      value_t Value,\
      time_t LogFlag)
{

   struct os_db_common_fields commonFields;

   commonFields.MagicNumber       = VAR_MAGIC_NUMBER;
   commonFields.HashValue         = 0;
   commonFields.NextName          = NULL;
   commonFields.Name              = myStrDup(pPool, Name);
   commonFields.Type              = Type;
   commonFields.AccessRead        = AccessRead;
   commonFields.AccessWrite       = AccessWrite;
   commonFields.ScaleType         = ScaleType;
   commonFields.ScaleValue        = ScaleValue;
   commonFields.Unit              = Unit;
   commonFields.Precision         = Precision;
   commonFields.Value             = Value;
   commonFields.TimeStamp         = LogFlag;
   commonFields.DisplayScaleType  = (scaletype_t)0;
   commonFields.DisplayScaleValue = (scalevalue_t)0;
   commonFields.DisplayUnit       = (unit_t)0;
   commonFields.DisplayPrecision  = 0;
   commonFields.Update            = Update;
   commonFields.FirstSubscriber   = NULL;
   commonFields.PreviousVariable  = NULL;
   commonFields.NextVariable      = NULL;
   commonFields.ActiveReaders     = 0;
   commonFields.OldValueBeingRead = 0;
   commonFields.TotalLogID        = 0;
   commonFields.FiveMinLogID      = 0;

   return commonFields;
}

STATUS createVarDB_Parameter(\
                             OS_MEMORY_POOL* pPool,\
                             const char* Name,\
                             type_t Type,\
                             access_t AccessRead,\
                             access_t AccessWrite,\
                             scaletype_t ScaleType,\
                             scalevalue_t ScaleValue,\
                             unit_t Unit,\
                             precision_t Precision,\
                             value_t Value,\
                             value_t Minimum,\
                             value_t Maximum,\
                             time_t LogFlag)
{

   STATUS Status = OS_SUCCESS;

   varid_t VarId;
   size_t ErrorEntry;

   struct os_db_parameter* parameterVarStruct = (struct os_db_parameter*)SysAllocDataMemory(pPool, sizeof(struct os_db_parameter));
   if (parameterVarStruct)
   {
      memset(parameterVarStruct, 0, sizeof(struct os_db_parameter));
      parameterVarStruct->c = getCommonFields(pPool, (enum update)PARAMETER, Name, Type, AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, Value, LogFlag);
      parameterVarStruct->l = getSubparameter(Minimum, Maximum);
   }
   else
   {
      Status = ERR_MEMORY_NOT_FOUND;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
   }

   STATUS CreationStatus = OS_VarDB_CreateParameters(parameterVarStruct, 1, &ErrorEntry, AppLocalParameterPosition());
   Status = OS_VarDB_GetVariableID(Name, &VarId);
   if (Status == ERR_VARDB_NOT_FOUND)
   {
      SysFreeDataMemory(parameterVarStruct, sizeof(struct os_db_parameter));
      AppDebugLog(7777, "Cant create Var %s", Name);
      STATUS_LINE_VAR_RETURN_VALUE(CreationStatus);
   }

   return Status;
}

STATUS createVarDB_Backup(\
                          OS_MEMORY_POOL* pPool,\
                          const char* Name,\
                          type_t Type,\
                          access_t AccessRead,\
                          access_t AccessWrite,\
                          scaletype_t ScaleType,\
                          scalevalue_t ScaleValue,\
                          unit_t Unit,\
                          precision_t Precision,\
                          value_t Value,\
                          value_t Minimum,\
                          value_t Maximum,
                          time_t LogFlag)
{

   STATUS Status = OS_SUCCESS;

   varid_t VarId;
   size_t ErrorEntry;

   struct os_db_backup* backupVarStruct = (struct os_db_backup*)SysAllocDataMemory(pPool, sizeof(struct os_db_backup));
   if (backupVarStruct)
   {
      memset(backupVarStruct, 0, sizeof(struct os_db_backup));
      backupVarStruct->c = getCommonFields(pPool, (enum update)BACKUP, Name, Type, AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, Value, LogFlag);
      backupVarStruct->l = getSubbackup(Minimum, Maximum);
   }
   else
   {
      Status = ERR_MEMORY_NOT_FOUND;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
   }

   STATUS CreationStatus = OS_VarDB_CreateBackups(backupVarStruct, 1, &ErrorEntry, AppLocalParameterPosition(), AppBackupPosition());
   Status = OS_VarDB_GetVariableID(Name, &VarId);
   if (Status == ERR_VARDB_NOT_FOUND)
   {
      SysFreeDataMemory(backupVarStruct, sizeof(struct os_db_backup));
      AppDebugLog(7777, "Cant create Var %s", Name);
      STATUS_LINE_VAR_RETURN_VALUE(CreationStatus);
   }

   return Status;
}

STATUS createVarDB_Local(\
                         OS_MEMORY_POOL* pPool,\
                         const char* Name,\
                         type_t Type,\
                         access_t AccessRead,\
                         access_t AccessWrite,\
                         scaletype_t ScaleType,\
                         scalevalue_t ScaleValue,\
                         unit_t Unit,\
                         precision_t Precision,\
                         value_t Value,\
                         value_t Minimum,\
                         value_t Maximum,
                         time_t LogFlag)
{

   STATUS Status = OS_SUCCESS;

   varid_t VarId;
   size_t ErrorEntry;

   struct os_db_local* localVarStruct = (struct os_db_local*)SysAllocDataMemory(pPool, sizeof(struct os_db_local));
   if (localVarStruct)
   {
      memset(localVarStruct, 0, sizeof(struct os_db_local));
      localVarStruct->c = getCommonFields(pPool, (enum update)LOCAL, Name, Type, AccessRead, AccessWrite, ScaleType, ScaleValue, Unit, Precision, Value, LogFlag);
      localVarStruct->l = getSublocal(Minimum, Maximum);
   }
   else
   {
      Status = ERR_MEMORY_NOT_FOUND;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
   }

   STATUS CreationStatus = OS_VarDB_CreateLocals(localVarStruct, 1, &ErrorEntry, AppBackupPosition());
   Status = OS_VarDB_GetVariableID(Name, &VarId);
   if (Status == ERR_VARDB_NOT_FOUND)
   {
      SysFreeDataMemory(localVarStruct, sizeof(struct os_db_local));
      AppDebugLog(7777, "Cant create Var %s", Name);
      STATUS_LINE_VAR_RETURN_VALUE(CreationStatus);
   }

   return Status;
}

char* GetArrayElemName(char* ArrName, int Index)
{
   static char ArrElemName[50];
   sprintf(ArrElemName, "%s_%d", ArrName, Index);
   return ArrElemName;
}

int GetLength(char* Len)
{
   STATUS Status = OS_SUCCESS;
   varid_t VarId;
   type_t  VarType;

   S32    LengthDigit  = 0;
   char*  EndPtr = NULL;
   LengthDigit = strtol(Len, &EndPtr, 10);

   if (!strcmp(EndPtr, "\0")) //conversion successful
   {
      return LengthDigit;
   }

   Status = OS_VarDB_GetVariableID(Len, &VarId);
   STATUS_LINE_VAR_RETURN_VALUE(Status);

   Status = OS_VarDB_GetVariableType(VarId, &VarType);
   STATUS_LINE_VAR_RETURN_VALUE(Status);

   if (!(VarType & TYP_INT))
   {
      return -1;
   }

   Status =  OS_VarDB_ReadVariable(VarId, &LengthDigit, GET_VAR_LENGTH(VarType), 0);
   STATUS_LINE_VAR_RETURN_VALUE(Status);

   if (LengthDigit < 0)
   {
      return -2;
   }

   return LengthDigit;
}

STATUS AllocVdbIdsArray(OS_MEMORY_POOL* pPool, varid_t** ArrId, int Length)
{
   STATUS Status = OS_SUCCESS;

   *ArrId = SysAllocDataMemory(pPool, sizeof(varid_t) * Length);
   if (!*ArrId)
   {
      SysFreeDataMemory(*ArrId, sizeof(varid_t) * Length);
      Status = ERR_MEMORY_NOT_FOUND;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
   }

   return Status;
}

STATUS AllocVdbDataArray(OS_MEMORY_POOL* pPool, void** ArrName, int Length, int ElemSize)
{
   STATUS Status = OS_SUCCESS;
   int totalSize = ElemSize * Length;
   if (totalSize == 0)
   {
      *ArrName = NULL;
      return Status;
   }

   *ArrName = SysAllocDataMemory(pPool, totalSize);
   if (!*ArrName)
   {
      Status = ERR_MEMORY_NOT_FOUND;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
   }

   return Status;
}
