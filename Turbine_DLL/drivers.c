//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2015 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:101$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2014/03/04 14:44:49 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: drivers.c,v $                                                       
// $Revision: 1.1 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

// OS header files
#include <os_main.h>
// AppLib header files
#include <lib_main.h>
// App header files
#include <turbdef.h>
#include <VarMacros.h>

#include <drivers.h>

//-----------------------------------------------------------------------
// DRIVER FUNCTION DRIVER FUNCTION DRIVER FUNCTION DRIVER FUNCTION
//-----------------------------------------------------------------------
#define DRIVER

CMS_INPUT_NAMES_DEF1
CMS_OUTPUT_NAMES_DEF1

CMS_INPUT_NAMES_DEF2
CMS_OUTPUT_NAMES_DEF2

CMS_INPUT_NAMES_DEF3
CMS_OUTPUT_NAMES_DEF3

CMS_INPUT_NAMES_DEF4
CMS_OUTPUT_NAMES_DEF4

AIR_PRESSURE_INPUT_NAMES_DEF1
AIR_PRESSURE_OUTPUT_NAMES_DEF1

static struct IoDriverStruct IoDriverTable[] =
{
   CMS_DRIVER_STRUCT1
   CMS_DRIVER_STRUCT2
   CMS_DRIVER_STRUCT3
   CMS_DRIVER_STRUCT4

   AIR_PRESSURE_DRIVER_STRUCT1
}; 

struct os_db_local IoDriverLocalVars[] =
{
VAR_ELEMENT_LOCAL
(
   "V_"APP_ID"temp",                    /* Variable name                                                              */ \
   TYPE_U8,                             /* Variable type                                                              */ \
   0,                                   /* Access read level, 255 High priority                                       */ \
   0,                                   /* Access write level, 255 High priority                                      */ \
   SCALE_NONE,                          /* Scale type (SCALE_NONE, SCALE_DIV, SCALE_MUL, SCALE_EXPMUL, SCALE_EXPDIV)  */ \
   0,                                   /* Scale value (Maximum string length for strings)                            */ \
   UNIT_NONE,                           /* unit type                                                                  */ \
   0,                                   /* precision                                                                  */ \
   0,                                   /* init value (Allocate memmory)                                              */ \
   0,                                   /* Minimum value                                                              */ \
   0,                                   /* Maximum value                                                              */ \
   NULL,                                /* Select list                                                                */ \
   NOLOG_ENABLE                         /* Log flag                                                                   */ \
),
};

 const unsigned int IoDriverLocalVarsSize = sizeof(IoDriverLocalVars)/sizeof(IoDriverLocalVars[0]);
 struct os_db_local *IoDriverLocalVarsPtr = &IoDriverLocalVars[0];

#define MESSAGE_SIZE 4
const U8 MessageSize = MESSAGE_SIZE;


#define NUMBER_OF_IO_DRIVERS (sizeof(IoDriverTable)/sizeof(IoDriverTable[0]))
const U16 NumberOfIoDrivers = NUMBER_OF_IO_DRIVERS;

#define ENTRIES (NUMBER_OF_IO_DRIVERS * 2)
const U16 Entries = ENTRIES;

UNSIGNED MyQueue[MESSAGE_SIZE * ENTRIES];
SUBSCRIPTION LocalSubscription[NUMBER_OF_IO_DRIVERS];
UNSIGNED Message[MESSAGE_SIZE];

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------
// SELECTOR FUNCTION SELECTOR FUNCTION SELECTOR FUNCTION
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
// CONTROL                CONTROL                 CONTROL
//-----------------------------------------------------------------------

STATUS InitDrivers (U8 ModuleState, OS_MEMORY_POOL *MemPool)
{
    STATUS Status = OS_SUCCESS;
#ifdef DRIVER
   return InitIoDriver(  MemPool,
                         Entries,
                         MyQueue,
                         LocalSubscription,
                         NumberOfIoDrivers,
                         Message,
                         MessageSize,
                         IoDriverTable,
                         ModuleState );
#endif
    return Status;
}



static STATUS LocalCtrl( U32 Interval )
{
    STATUS LocalStatus = 0;

    return LocalStatus;
}


static STATUS ShutdownCtrl( U8 ModuleState, U8 *DoneState, U32 Interval )
{
    STATUS LocalStatus = 0;

    switch( ModuleState )
    {
        case AS_SHUTDOWN:
        {

            *DoneState = AS_SHUTDOWN;
            break;
        }
        case AS_REBOOT:
        {

            *DoneState = AS_REBOOT;
            break;
        }

        case AS_SHUTDOWN_FAST:
        {

            *DoneState = AS_SHUTDOWN_FAST;
            break;
        }
        default:
        {
		
            *DoneState = ModuleState;
            break;
        }
    }
    return LocalStatus;
}

  
//-----------------------------------------------------------------------
// MAIN CALL             MAIN CALL               MAIN CALL
//-----------------------------------------------------------------------
STATUS InitIoDrivers( U8 ModuleState, U8 *DoneState , U32 Interval )
{
    STATUS LocalStatus = 0;

    switch( ModuleState )
    {
        //__________________________________________________________________________
        case APP_RUN:
        {
            LocalStatus = LocalCtrl( Interval );
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)

            *DoneState = APP_RUN;

            break;
        }
        //__________________________________________________________________________
        case APP_INIT1:
        {
            // Version check
            LocalStatus = OS_ValidateAPI( API_VERSION_MAJOR,
                                          API_VERSION_MINOR,
                                          OS_LinkTime,
                                          ReleaseTag,
                                          __MODULE__
                                         );
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)

            LocalStatus = InitDrivers ( ModuleState,  GetMemPool());
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)
			
            *DoneState = APP_INIT1;
            break;
        }
        //__________________________________________________________________________
        case APP_INIT2:
        {
            LocalStatus = InitDrivers ( ModuleState,  GetMemPool());
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)
			
            *DoneState = APP_INIT2;
            break;
        }
        //__________________________________________________________________________
        case APP_INIT3 :
        {

            *DoneState = APP_INIT3;
            break;
        }
        //__________________________________________________________________________
        case APP_INIT4:
        {

            *DoneState = APP_INIT4;
            break;
        }
        //__________________________________________________________________________
        case APP_INIT5:
        {

            *DoneState = APP_INIT5_DONE;
            break;
        }
        //__________________________________________________________________________
        //Other initialization round can be inserted here
        //__________________________________________________________________________
        case AS_SHUTDOWN:
        {
            LocalStatus = LocalCtrl( Interval );
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)
			
            LocalStatus = ShutdownCtrl ( ModuleState, DoneState, Interval );
			      STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)

            break;
        }
        //__________________________________________________________________________
        case AS_REBOOT:
        {
            LocalStatus = LocalCtrl( Interval );
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)
			
            LocalStatus = ShutdownCtrl ( ModuleState, DoneState, Interval );
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)
            break;
        }
        //__________________________________________________________________________
        case AS_SHUTDOWN_FAST:
        {
            LocalStatus = LocalCtrl( Interval );
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)
			
            LocalStatus = ShutdownCtrl ( ModuleState, DoneState, Interval );
            STATUS_LINE_VAR_RETURN_VALUE(LocalStatus)
            break;
        }
        default:
        {
            *DoneState = ModuleState;

            break;
        }
    }
    return OS_SUCCESS;
}

//-----------------------------------------------------------------------
