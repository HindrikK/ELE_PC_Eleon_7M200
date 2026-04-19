/*********************************************************************/
/*                                                                   */
/*            Copyright (c) 2001 Mita-Teknik a/s                     */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/* FILE NAME         os_sts.h                              VERSION   */
/*                                                                   */
/* COMPONENT                                                         */
/*                                                                   */
/* DESCRIPTION                                                       */
/*                                                                   */
/*     Defines for status codes                                      */
/*                                                                   */
/* AUTHOR    Mita-Teknik a/s                                         */
/*                                                                   */
/* HISTORY                                                           */
/*     NAME  DATE        REMARKS                                     */
/*     SAL   2003-01-29  Created                                     */
/*                                                                   */
/*********************************************************************/

#ifndef __os_sts_h
#define __os_sts_h

#include "m_def.h"
#include <stdlib.h>
#include <stddef.h>
#include "types.h"

//#define STS_REMOVE_UPDATE_TYPES_REPEAT_TIMEOUT
//#define STS_REMOVE_LOGFLAG_FROM_STRUCTURES

#define STATUSCODE_INTERFACE_VERSION 3

#define STATUSCODE_UPDATE_TYPE_POLLING   (U8)0
#define STATUSCODE_UPDATE_TYPE_AUTOMATIC (U8)1

#ifndef STS_REMOVE_UPDATE_TYPES_REPEAT_TIMEOUT
#define STATUSCODE_UPDATE_TYPE_REPEAT    (U8)2
#define STATUSCODE_UPDATE_TYPE_TIMEOUT   (U8)3
#endif

#define STATUSCODE_TIMER_TYPE_CONSTANT (U8)0
#define STATUSCODE_TIMER_TYPE_UP_DOWN  (U8)1

/* The numerically order of the reset types is used and important.
   A higher number overrules a lower number */
#define STATUSCODE_RESET_TYPE_AUTOMATIC  		(U8)0
#define STATUSCODE_RESET_TYPE_CMS        		(U8)1
#define STATUSCODE_RESET_TYPE_NO_ACTIVE_USER 	(U8)4
#define STATUSCODE_RESET_TYPE_RESERVED_1 		(U8)8
#define STATUSCODE_RESET_TYPE_RESERVED_2 		(U8)0x10
#define STATUSCODE_RESET_TYPE_RESERVED_3 		(U8)0x20
#define STATUSCODE_RESET_TYPE_RESERVED_4 		(U8)0x40
#define STATUSCODE_RESET_TYPE_DISPLAY 			(U8)0x80

#define STATUSCODE_PRIORITY_HIGH         (U8)255
#define STATUSCODE_PRIORITY_SUB          (U8)100
#define STATUSCODE_PRIORITY_WARNING      (U8)30
#define STATUSCODE_PRIORITY_LOW          (U8)0

#define STATUSCODE_NO_ALARM              (U8)0


/*********************************************************************/
/*                                                                   */
/*  The type STSCODE_CONTROL_BLOCK is used to contain housekeeping   */
/*  information about status codes maintained by the OS.             */
/*  Applications should create one instance of this type and give    */
/*  the OS a pointer to it. The application should not use nor       */
/*  otherwise access the contents.                                   */
/*                                                                   */
/*********************************************************************/
typedef
struct stscode_control_block_struct
{
      void *table;
      size_t entries;
      struct stscode_control_block_struct *next;
} STATUS_CODE_CONTROL_BLOCK;


/*********************************************************************/
/*                                                                   */
/*  The struct sts_statuscode_structure struct contains all stored   */
/*  information about a status code                                  */
/*                                                                   */
/*********************************************************************/
struct sts_statuscode_structure
{
      /* Constant section - These values should not be changed once
         a status code is initialised */
      char StsText[30];      /* Statuscode text */
      U32 StsPowerUpDelay;   /* Power up delay - do not test the status code
                             this number of ms after power up. */
      U16 StsStatuscodeNo;   /* Statuscode number */
      U8 StsUpdateType;      /* Use STATUSCODE_UPDATE_TYPE_POLLING or
                             STATUSCODE_UPDATE_TYPE_AUTOMATIC. Only
                             polling is implemented at start. */
      U8 StsResetPasswordLevel;
                 /* Password level to reset the status code */
      U8 StsSetTimerType;
                 /* STATUSCODE_TIMER_TYPE_CONSTANT or
                    STATUSCODE_TIMER_TYPE_UP_DOWN - decides if the delay
                    timer for setting the status code will be reset or
                    counted down when SetFunc() returns FALSE. */
      U8 StsResetTimerType;
                 /* STATUSCODE_TIMER_TYPE_CONSTANT or
                    STATUSCODE_TIMER_TYPE_UP_DOWN - decides if the delay
                    timer for resetting the status code will be reset or
                    counted down when ResetFunc() returns FALSE. */
      U8 StsResetType;
                 /* STATUSCODE_RESET_TYPE_AUTOMATIC = 0 (automatic reset
                    via reset function or manual),
                    STATUSCODE_RESET_TYPE_CMS = 1 (reset via CMS system or
                    display) or STATUSCODE_RESET_TYPE_DISPLAY = 2 (reset
                    via local or remote display only). */
      U8 StsPriority;              /* Display priority */
      U8 StsAvailabilityGroup;     /* Availability group */
#ifdef STS_SET_CLEAR_FUNC_WITH_STS_NUMBER_AS_PARAMETER
      U8 (*StsSetFunc)(U16);      /* Function to test for set condition */
      U8 (*StsResetFunc)(U16);    /* Function to test for reset condition */
#else
      U8 (*StsSetFunc)(void);      /* Function to test for set condition */
      U8 (*StsResetFunc)(void);    /* Function to test for reset condition */
#endif
      /* Parameter section - There will be created parameters for the
         fields in this section with the indicated default value and
         password levels. The names of the created parameters will be
         P_StatusCodeX_Name where X is the status code number and Name is
         the specific name of the field. */

      U8 StsControlProgram1;       /* Control Program 1 */
      access_t StsControlProgram1AccessRead;
      access_t StsControlProgram1AccessWrite;
      U8 StsControlProgram2;       /* Control Program 2 */
      access_t StsControlProgram2AccessRead;
      access_t StsControlProgram2AccessWrite;
      U8 StsControlProgram3;       /* Control Program 3 */
      access_t StsControlProgram3AccessRead;
      access_t StsControlProgram3AccessWrite;
      U8 StsCodeEnable;          /* Enable status code. */
      access_t StsCodeEnableAccessRead;
      access_t StsCodeEnableAccessWrite;

#ifndef STS_REMOVE_LOGFLAG_FROM_STRUCTURES
      log_t StsLogFlags;         /* Indicates what and where to log changes
                    in the status code. It is also used for all parameters
                    to the status code. */
      access_t StsLogFlagsAccessRead;
      access_t StsLogFlagsAccessWrite;
#endif

      U32 StsUpdateInterval;     /* UpdateInterval (20, 100 or 1000 ms) is
                    used if UpdateType is polling. */
      access_t StsUpdateIntervalAccessRead;
      access_t StsUpdateIntervalAccessWrite;

      U32 StsSetDelay;           /* SetDelay is a measure in milliseconds
                    for how long a set condition may be true before
                    setting the status code. */
      access_t StsSetDelayAccessRead;
      access_t StsSetDelayAccessWrite;

      U32 StsResetDelay;         /* ResetDelay is a measure in milliseconds
                    for how long a clear condition may be true before
                    reseting the status code. */
      access_t StsResetDelayAccessRead;
      access_t StsResetDelayAccessWrite;

      /* ActiveRepeatTimes, ActiveRepeatPeriod and ActiveRepeatCode. If
         the status code is activated more ActiveRepeatTimes times within
         a ActiveRepeatPeriod period, then set status code
         ActiveRepeatCode. */
      U32 StsActiveRepeatTimes;  /* Repeat times */
      access_t StsActiveRepeatTimesAccessRead;
      access_t StsActiveRepeatTimesAccessWrite;
      U32 StsActiveRepeatPeriod; /* Repeat time period in milliseconds */
      access_t StsActiveRepeatPeriodAccessRead;
      access_t StsActiveRepeatPeriodAccessWrite;
      U16 StsActiveRepeatCode;   /* Repeat status code */
      access_t StsActiveRepeatCodeAccessRead;
      access_t StsActiveRepeatCodeAccessWrite;

      /* ActiveTimeoutPeriod and ActiveTimeoutCode. If the status code is
         active for the ActiveTimeoutPeriod at a stretch, then set status
         code ActiveTimeoutCode. */
      U32 StsActiveTimeoutPeriod; /* Timeout period in milliseconds */
      access_t StsActiveTimeoutPeriodAccessRead;
      access_t StsActiveTimeoutPeriodAccessWrite;
      U16 StsActiveTimeoutCode;   /* Timeout status code */
      access_t StsActiveTimeoutCodeAccessRead;
      access_t StsActiveTimeoutCodeAccessWrite;

      char *StsVarDBBackupFileName;/* pointer to vardb backup file name */

      U8 CP1_Min;                            /* ControlProgram1 parameter Minimum value - not parameter yet */
      U8 CP1_Max;                            /* ControlProgram1 parameter Maximum value - not parameter yet */
      U8 CP2_Min;                            /* ControlProgram2 parameter Minimum value - not parameter yet */
      U8 CP2_Max;                            /* ControlProgram2 parameter Maximum value - not parameter yet */
      U8 CP3_Min;                            /* ControlProgram3 parameter Minimum value - not parameter yet */
      U8 CP3_Max;                            /* ControlProgram3 parameter Maximum value - not parameter yet */
      U8 Availability_Min;                   /* AvailabilityGroup parameter Minimum value */
      U8 Availability_Max;                   /* AvailabilityGroup parameter Maximum value */
      U32 UpdateInterval_Min;                /* UpdateInterval parameter Minimum value - not parameter yet */
      U32 UpdateInterval_Max;                /* UpdateInterval parameter Maximum value - not parameter yet */
      U32 SetDelay_Min;                      /* SetDelay parameter Minimum value */
      U32 SetDelay_Max;                      /* SetDelay parameter Maximum value */
      U32 ResetDelay_Min;                    /* ResetDelay parameter Minimum value */
      U32 ResetDelay_Max;                    /* ResetDelay parameter Maximum value */
      U32 RepeatTimes_Min;                   /* RepeatTimes parameter Minimum value - not parameter yet */
      U32 RepeatTimes_Max;                   /* RepeatTimes parameter Maximum value - not parameter yet */
      U16 RepeatPeriod_Min;                  /* RepeatPeriod parameter Minimum value - not parameter yet */
      U16 RepeatPeriod_Max;                  /* RepeatPeriod parameter Maximum value - not parameter yet */
      U16 RepeatCode_Min;                    /* RepeatCode parameter Minimum value - not parameter yet */
      U16 RepeatCode_Max;                    /* RepeatCode parameter Maximum value - not parameter yet */
      U32 TimeoutPeriod_Min;                 /* TimeoutPeriod parameter Minimum value - not parameter yet */
      U32 TimeoutPeriod_Max;                 /* TimeoutPeriod parameter Maximum value - not parameter yet */
      U16 TimeoutCode_Min;                   /* TimeoutCode parameter Minimum value - not parameter yet */
      U16 TimeoutCode_Max;                   /* TimeoutCode parameter Maximum value - not parameter yet */

      void *Availability_SelectionList;      /* AvailabilityGroup parameter SelectionList - not implemented yet - set to NULL */
      void *CP1_SelectionList;               /* ControlProgram1 parameter SelectionList - not implemented yet - set to NULL */
      void *CP2_SelectionList;               /* ControlProgram2 parameter SelectionList - not implemented yet - set to NULL */
      void *CP3_SelectionList;               /* ControlProgram3 parameter SelectionList - not implemented yet - set to NULL */
      void *UpdateInterval_SelectionList;    /* UpdateInterval parameter SelectionList - not implemented yet - set to NULL */
      void *SetDelay_SelectionList;          /* SetDelay parameter SelectionList - not implemented yet - set to NULL */
      void *ResetDelay_SelectionList;        /* ResetDelay parameter SelectionList - not implemented yet - set to NULL */
      void *RepeatTimes_SelectionList;       /* RepeatTimes parameter SelectionList - not implemented yet - set to NULL */
      void *RepeatPeriod_SelectionList;      /* RepeatPeriod parameter SelectionList - not implemented yet - set to NULL */
      void *RepeatCode_SelectionList;        /* RepeatCode parameter SelectionList - not implemented yet - set to NULL */
      void *TimeoutPeriod_SelectionList;     /* TimeoutPeriod parameter SelectionList - not implemented yet - set to NULL */
      void *TimeoutCode_SelectionList;       /* TimeoutCode parameter SelectionList - not implemented yet - set to NULL */

      access_t ActivateCounterAccessRead;    /* Access code to read ActivateCounter backup*/
      access_t ActivateCounterAccessWrite;   /* Access code to write ActivateCounter backup */
      access_t AvailabilityGroupAccessRead;  /* Access code to read AvailabilityGroup parameter */
      access_t AvailabilityGroupAccessWrite; /* Access code to write AvailabilityGroup parameter */

      void *InternalData;                    /* Pointer to internal data - allocated and maintained by the OS */
};

#endif
