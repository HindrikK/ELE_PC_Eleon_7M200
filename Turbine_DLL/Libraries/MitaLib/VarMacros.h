//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2017 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:104$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2015/11/04 12:49:42 $                                                  
// $Author: DESKTOP-3H3JCEK\jaakl $                                                           
// $RCSfile: VarMacros.h,v $                                                     
// $Revision: 1.1 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#include "VarArrayMacros.h"
#include "VarArrayMenus.h"

#define VERIFY_INPUT_REF_ID(VarType, VarName, VarsReadId) \
   VarsReadReturnStatus += OS_VarDB_GetVariableType(VarsReadId, &ReadVarType); \
   if(VarsReadReturnStatus != 0) AppSystemLog (54443, MODULE_NAME " ReadVarErr."); \
   if(ReadVarType != TYPE_##VarType) \
   {\
      AppSystemLog(54444, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54445, #VarType " %s", VarName);\
   }

#define VERIFY_INPUT_REF(VarType, VarName) \
   VarsReadReturnStatus = OS_VarDB_GetVariableID(VarName, &VarsReadId); \
   VarsReadReturnStatus += OS_VarDB_GetVariableType(VarsReadId, &ReadVarType); \
   if(VarsReadReturnStatus != 0) AppSystemLog (54443, MODULE_NAME " ReadVarErr."); \
   if(ReadVarType != TYPE_##VarType) \
   {\
      AppSystemLog(54444, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54445, #VarType " " VarName);\
   }

#define VERIFY_INPUT_CREATE_NO_VAR_REF_ID(VarType, VarDbName, VarId, LocalVarName)

#define VERIFY_INPUT_CREATE_NO_VAR_REF(VarType, VarDbName, LocalVarName)

#define VERIFY_INPUT_STRING_REF_ID(VarType, VarName, VarsReadId) \
   VarsReadReturnStatus += OS_VarDB_GetVariableType(VarsReadId, &ReadVarType); \
   if(VarsReadReturnStatus != 0) AppSystemLog (54443, MODULE_NAME " ReadVarErr."); \
   if((ReadVarType & TYPE_TYPE_MASK) != TYPE_##VarType) \
   {\
      AppSystemLog(54444, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54445, #VarType " %s", VarName);\
   }

#define VERIFY_INPUT_STRING_REF(VarType, VarName, VarSize)

#define VERIFY_PARAMETER_STRING_ID(VarType, VarName, ParaVarsReadId) \
   ParaVarsReadReturnStatus += OS_VarDB_GetVariableType(ParaVarsReadId, &ParaReadVarType); \
   if(ParaVarsReadReturnStatus != 0) AppSystemLog (54453, MODULE_NAME " ReadVarErr."); \
   if((ParaReadVarType & TYPE_TYPE_MASK) != TYPE_##VarType) \
   {\
      AppSystemLog(54454, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54455, #VarType " %s", VarName);\
   }

#define VERIFY_PARAMETER_STRING(VarType, VarName)

#define VERIFY_PARAMETER_ID(VarType, VarName, ParaVarsReadId) \
   ParaVarsReadReturnStatus += OS_VarDB_GetVariableType(ParaVarsReadId, &ParaReadVarType); \
   if(ParaVarsReadReturnStatus != 0) AppSystemLog (54453, MODULE_NAME " ReadVarErr."); \
   if(ParaReadVarType != TYPE_##VarType) \
   {\
      AppSystemLog(54454, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54455, #VarType " %s", VarName);\
   }

#define VERIFY_PARAMETER(VarType, VarName) \
   ParaVarsReadReturnStatus = OS_VarDB_GetVariableID(VarName, &ParaVarsReadId); \
   ParaVarsReadReturnStatus += OS_VarDB_GetVariableType(ParaVarsReadId, &ParaReadVarType); \
   if(ParaVarsReadReturnStatus != 0) AppSystemLog (54453, MODULE_NAME " ReadVarErr."); \
   if(ParaReadVarType != TYPE_##VarType) \
   {\
      AppSystemLog(54454, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54455, #VarType " " VarName);\
   }

#define VERIFY_OUTPUT_REF_ID(VarType, VarName, VarsWriteId, ForcedUpdate) \
   VarsWriteReturnStatus += OS_VarDB_GetVariableType(VarsWriteId, &WriteVarType); \
   if(VarsWriteReturnStatus != 0) AppSystemLog(54463, MODULE_NAME " WriteVarErr."); \
   if(WriteVarType != TYPE_##VarType) \
   {\
      AppSystemLog(54464, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54465, #VarType " %s", VarName);\
   }

#define VERIFY_OUTPUT_REF(VarType, VarName, ForcedUpdate) \
   VarsWriteReturnStatus = OS_VarDB_GetVariableID(VarName, &VarsWriteId); \
   VarsWriteReturnStatus += OS_VarDB_GetVariableType(VarsWriteId, &WriteVarType); \
   if(VarsWriteReturnStatus != 0) AppSystemLog(54463, MODULE_NAME " WriteVarErr."); \
   if(WriteVarType != TYPE_##VarType) \
   {\
      AppSystemLog(54464, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54465, #VarType " " VarName);\
   }

#define VERIFY_OUTPUT_TIME_REF_ID(VarType, VarName, VarsWriteId, ForcedUpdate) \
   VarsWriteReturnStatus += OS_VarDB_GetVariableType(VarsWriteId, &WriteVarType); \
   if(VarsWriteReturnStatus != 0) AppSystemLog(54463, MODULE_NAME " WriteVarErr."); \
   if(WriteVarType != TYPE_TIME) \
   {\
      AppSystemLog(54464, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54465, #VarType " %s", VarName);\
   }

#define VERIFY_OUTPUT_TIME_REF(VarType, VarName, ForcedUpdate) \
   VarsWriteReturnStatus = OS_VarDB_GetVariableID(VarName, &VarsWriteId); \
   VarsWriteReturnStatus += OS_VarDB_GetVariableType(VarsWriteId, &WriteVarType); \
   if(VarsWriteReturnStatus != 0) AppSystemLog(54463, MODULE_NAME " WriteVarErr."); \
   if(WriteVarType != TYPE_TIME) \
   {\
      AppSystemLog(54464, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54465, #VarType " " VarName);\
   }

#define VERIFY_OUTPUT_STRING_REF_ID(VarType, VarName, VarsWriteId, ForcedUpdate) \
   VarsWriteReturnStatus += OS_VarDB_GetVariableType(VarsWriteId, &WriteVarType); \
   if(VarsWriteReturnStatus != 0) AppSystemLog(54463, MODULE_NAME " WriteVarErr."); \
   if((WriteVarType & TYPE_TYPE_MASK) != TYPE_##VarType) \
   {\
      AppSystemLog(54464, MODULE_NAME " VarTypeErr."); \
      AppSystemLog(54465, #VarType " %s", VarName);\
   }

#define VERIFY_OUTPUT_STRING_REF(VarType, VarName, VarSize, ForcedUpdate)
