//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2018 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:8.4$                                                         
// $PEPTOOL file version:104$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2014/03/04 14:36:07 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: InitIo.c,v $                                                        
// $Revision: 1.8 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <os_main.h>
// AppLib header files
#include <lib_main.h>
// App header files
#include <turbdef.h>
#include <VarMacros.h>
// Object header file
#include <InitIo.h>
#include <main.h>

#define MODULE_NAME "InitIoA"

#define MAX_GROUPS            10
#define MAX_MODULES_IN_GROUP  16
#define MAX_MODULES           MAX_GROUPS * MAX_MODULES_IN_GROUP

typedef struct HWModuleStruct
{
    U16          GroupNumber;
    U16          NodeNumber;
    char         ModuleType[10];
    //--------------------------
    U8           Mod_Failed;
    U8           Mod_Failed_Enabled;
    //--------------------------
    varid_t      Mod_Failed_id;
    varid_t      Mod_Failed_Enabled_id;
    //--------------------------
    SUBSCRIPTION Sbs_Failed;
    SUBSCRIPTION Sbs_Failed_Enabled;

} HWModuleStructType;

typedef  struct HWModuleStruct *pHWModuleStructType;

static HWModuleStructType  HWModuleList [ MAX_MODULES ]; //Array of modules data
static pHWModuleStructType pHWModuleList[ MAX_MODULES ]; //Array of pointers to module data

static U16 module_count;
static U8  module_state_changed;
static U8  module_cfg_err;

#ifdef MAIN_APP
static varid_t V_WPlineError_ID = 0;
#endif


static STATUS on_mod_failed_change( varid_t VariableId, void* Message, U16 Length, UNSIGNED Ref1, UNSIGNED Ref2 )
{

    if( NULL == ((pHWModuleStructType)Ref1) )
    {
        AppSystemLog( 12525, "Function On_Mod_Fail_Change: executed with err" );
        return OS_SUCCESS;
    }

    ((pHWModuleStructType)Ref1)->Mod_Failed = *((U8*)Message);

    AppSystemLog( 12525, "[%u][%u]Mod_Failed = %u", ((pHWModuleStructType)Ref1)->GroupNumber,((pHWModuleStructType)Ref1)->NodeNumber, ((pHWModuleStructType)Ref1)->Mod_Failed );


    //Check for error in all modules
    U16 i;
    module_cfg_err = 0;
    for ( i = 0; i < module_count; ++i )
    {
        if ( HWModuleList[ i ].Mod_Failed && HWModuleList[ i ].Mod_Failed_Enabled )
        {
            module_cfg_err = 1;
        }
    }

#ifdef MAIN_APP
    // Update V_WPlineError
    OS_VarDB_UpdateVariableConditional(V_WPlineError_ID, &module_cfg_err, sizeof(module_cfg_err));
#endif

    module_state_changed = 1;
    return OS_SUCCESS;
}

static STATUS on_mod_failed_enable_change( varid_t VariableId, void* Message, U16 Length, UNSIGNED Ref1, UNSIGNED Ref2 )
{
    if( NULL == ((pHWModuleStructType)Ref1) )
    {
        AppSystemLog( 12525, "Function On_Mod_Failed_Enable_Change: executed with err" );
        return OS_SUCCESS;
    }

    ((pHWModuleStructType)Ref1)->Mod_Failed_Enabled = *((U8*)Message);

    AppSystemLog( 12525, "[%u][%u] Mod_Failed_Enabled = %u", ((pHWModuleStructType)Ref1)->GroupNumber,((pHWModuleStructType)Ref1)->NodeNumber, ((pHWModuleStructType)Ref1)->Mod_Failed_Enabled );


    //Check for error in all modules
    U16 i;
    module_cfg_err = 0;
    for ( i = 0; i < module_count; ++i )
    {
        if ( HWModuleList[ i ].Mod_Failed && HWModuleList[ i ].Mod_Failed_Enabled )
        {
            module_cfg_err = 1;
        }
    }
#ifdef MAIN_APP
    // Update V_WPlineError
    OS_VarDB_UpdateVariableConditional(V_WPlineError_ID, &module_cfg_err, sizeof(module_cfg_err));
#endif
    module_state_changed = 1;
    return OS_SUCCESS;
}

static STATUS hw_modules_autodetection()
{
    STATUS Status    = OS_SUCCESS;
    U16 Group_Number = 0;
    U16 Node_Number  = 0;
    U16 StsBaseNum   = 0;
    char Temp[ 40 ]     ;

    for( Group_Number = 1; Group_Number <= MAX_GROUPS; ++Group_Number )
    {
        for( Node_Number = 1; Node_Number <= MAX_MODULES_IN_GROUP; ++Node_Number )
        {
            //Check Module Type
            snprintf( Temp, sizeof Temp, "%03u_%02u_Type", Group_Number, Node_Number );
            Status = OS_VarDB_ReadVariableByName( Temp, HWModuleList[ module_count ].ModuleType, sizeof HWModuleList[ module_count ].ModuleType, NULL);

			//STATUS OS_VarDB_ReadVariableByName(const char *VariableName, void *Value, size_t len, time_t *TimeStamp)
            //If module exist subscribe to module status codes
            if( OS_SUCCESS == Status ) //Module Exist
            {

                StsBaseNum = 4000 + Group_Number * 16 + Node_Number;
                //----------------------------------------------------------------------------------------
                snprintf( Temp, sizeof Temp, "Sts%04u0_CurrentState", StsBaseNum );
                Status = OS_VarDB_GetVariableID( Temp, &HWModuleList[ module_count ].Mod_Failed_id );
                STATUS_LINE_VAR_RETURN_VALUE(Status);

                Status = OS_VarDB_ReadVariable( HWModuleList[ module_count ].Mod_Failed_id ,
                                                &HWModuleList[ module_count ].Mod_Failed,
                                                sizeof HWModuleList[ module_count ].Mod_Failed, NULL );
                STATUS_LINE_VAR_RETURN_VALUE(Status);

                snprintf( Temp, sizeof Temp, "Sts%04u0_Enable", StsBaseNum );
                Status = OS_VarDB_GetVariableID( Temp, &HWModuleList[ module_count ].Mod_Failed_Enabled_id );
                STATUS_LINE_VAR_RETURN_VALUE(Status);

                Status = OS_VarDB_ReadVariable( HWModuleList[ module_count ].Mod_Failed_Enabled_id,
                                                &HWModuleList[ module_count ].Mod_Failed_Enabled,
                                                sizeof HWModuleList[ module_count ].Mod_Failed_Enabled, NULL);
                STATUS_LINE_VAR_RETURN_VALUE(Status);

                pHWModuleList[ module_count ] = &HWModuleList[ module_count ];

                Status = OS_SubHandl_SubscribeFunctionWithRef( &HWModuleList[ module_count ].Sbs_Failed, 1,
                                                               &HWModuleList[ module_count ].Mod_Failed_id,
                                                               (UNSIGNED*)(&pHWModuleList[ module_count ]),
                                                               (UNSIGNED*)(&pHWModuleList[ module_count ]),
                                                               on_mod_failed_change );
                STATUS_LINE_VAR_RETURN_VALUE(Status);

                Status = OS_SubHandl_SubscribeFunctionWithRef( &HWModuleList[ module_count ].Sbs_Failed_Enabled, 1,
                                                               &HWModuleList[ module_count ].Mod_Failed_Enabled_id,
                                                               (UNSIGNED*)&pHWModuleList[ module_count ],
                                                               (UNSIGNED*)&pHWModuleList[ module_count ],
                                                               on_mod_failed_enable_change );
                STATUS_LINE_VAR_RETURN_VALUE(Status);

                HWModuleList[ module_count ].GroupNumber = Group_Number;
                HWModuleList[ module_count ].NodeNumber  = Node_Number;

                module_count++;
            }
        }
    }

    //Check for error in all modules
    U16 i;    
    module_cfg_err = 0;
    for ( i = 0; i < module_count; ++i )
    {
        if ( HWModuleList[ i ].Mod_Failed && HWModuleList[ i ].Mod_Failed_Enabled )
        {
            module_cfg_err = 1;
        }
    }
#ifdef MAIN_APP
    // Update V_WPlineError
    OS_VarDB_UpdateVariableConditional(V_WPlineError_ID, &module_cfg_err, sizeof(module_cfg_err));
#endif
    module_state_changed = 1;

    return OS_SUCCESS;
}

/*
static STATUS unsubscribe()
{
    U16 i;
    STATUS Status;
    for ( i = 0; i < module_count; ++i )
    {
        Status = OS_SubHandl_Unsubscribe ( &HWModuleList[ module_count ].Sbs_Failed, 1 );
        STATUS_LINE_VAR_RETURN_VALUE(Status);

        Status = OS_SubHandl_Unsubscribe ( &HWModuleList[ module_count ].Sbs_Failed_Enabled, 1 );
        STATUS_LINE_VAR_RETURN_VALUE(Status);
    }

    return Status;
}

static void print_module_config()
{
    U16 i;

    for ( i = 0; i < module_count; ++i )
    {
        AppDebugLog( 0,"[%u][%u] - %s-%u-%u ",  HWModuleList[ i ].GroupNumber, HWModuleList[ i ].NodeNumber, HWModuleList[ i ].ModuleType, HWModuleList[ i ].Mod_Failed, HWModuleList[ i ].Mod_Failed_Enabled );
    }

    return;
}

static void print_module_state()
{
    U16 i;
    for ( i = 0; i < module_count; ++i )
    {
        AppDebugLog( 0,"[%u][%u] - Fail[%u], E[%u]", HWModuleList[ i ].GroupNumber, HWModuleList[ i ].NodeNumber, HWModuleList[ i ].Mod_Failed, HWModuleList[ i ].Mod_Failed_Enabled );
    }

    return;
}
*/
//_____________________________________________________________________________
// Write new value to variable with this name. (only if the value is changed)
STATUS SetValue( char VarName[ ], size_t Type, U64 SetValue )
{
    STATUS Status = OS_VarDB_UpdateVariableConditionalByName( VarName, &SetValue, Type );

    if( OS_SUCCESS != Status )
    {
        AppSystemLog( 0, "InitIo: %d = SetValue(%s)", Status, VarName );
        STATUS_LINE_VAR_RETURN_VALUE(Status);
    }

    return Status;
}

//_____________________________________________________________________________
// Lock variable and write new value to variable with this name.
// (variable can only be changed again if the same ObjectId is used)
STATUS SetLockValue( char VarName[ ], size_t Type, U64 SetValue )
{
    STATUS Status = 0;
    U32 ObjectId = 0x3800000;
    varid_t VarId;

    Status = OS_VarDB_GetVariableID( VarName, &VarId );
    if( OS_SUCCESS != Status )
    {
        AppSystemLog( 1, "InitIo: %d = SetLockValue(%s)", Status, VarName );
        STATUS_LINE_VAR_RETURN_VALUE(Status);
    }

    Status = OS_VarDB_LockOutputParameter( VarId, ObjectId );
    if( OS_SUCCESS != Status )
    {
        AppSystemLog( 2, "InitIo: %d = SetLockValue(%s)", Status, VarName );
        STATUS_LINE_VAR_RETURN_VALUE(Status);
    }

    Status = OS_VarDB_UpdateLockedOutputParameter( VarId, &SetValue, Type, ObjectId );
    if( OS_SUCCESS != Status )
    {
        AppSystemLog( 3, "InitIo: %d = SetLockValue(%s)", Status, VarName );
        STATUS_LINE_VAR_RETURN_VALUE(Status);
    }

    return Status;
}

U8 WPlineError(void)
{
   return module_cfg_err;
}

//-----------------------------------------------------------------------
// MAIN CALL             MAIN CALL               MAIN CALL
//-----------------------------------------------------------------------

STATUS InitIo(void)
{
  STATUS Status = OS_SUCCESS;

  Status = hw_modules_autodetection ();
#ifdef MAIN_APP
  // Create variable V_WPlineError
  value_t val, min, max;                                                                                        
  val.u8 = 0;                                                                                          
  min.u8 = 0;                                                                                           
  max.u8 = 1;
  createVarDB_Local( GetMemPool(),
               "V_WPlineError",
               TYPE_U8,
               PASSWORD_LEVEL_END_CUSTOMER,
               PASSWORD_LEVEL_END_CUSTOMER,
               SCALE_NONE,
               0,
               UNIT_NONE,
               0,
               val,
               min,
               max,
               TOTLOG_ENABLE );

  // Get ID for V_WPlineError
  OS_VarDB_GetVariableID("V_WPlineError", &V_WPlineError_ID);
#endif
  //print_module_config();

  return Status;
}
//--------------------------------------------------------------


