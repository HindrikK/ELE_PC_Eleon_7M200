/*************************************************************************/
/*                                                                       */
/*            Copyright (c) 2000 Mita-Teknik a/s                         */
/*                                                                       */
/*************************************************************************/

/*************************************************************************/
/*                                                                       */
/* FILE NAME                                            VERSION          */
/*                                                                       */
/*      app_cmd.h                                       MITA 1.0         */
/*                                                                       */
/* COMPONENT                                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/* AUTHOR       Mita-Teknik a/s                                          */
/*                                                                       */
/* DATA STRUCTURES                                                       */
/*                                                                       */
/* FUNCTIONS                                                             */
/*                                                                       */
/* DEPENDENCIES                                                          */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/* NAME DATE        REMARKS                                              */
/* --------------------------------------------------------------------- */
/* FKl  30-03-2001  Created                                              */
/* PBA  11-04-2001  Added application request/state definitions          */
/* PBA  04-12-2001  Added Appstate Load- og Init-errors                  */
/* PBA  17-01-2002  Added Yaw request/state definitions                  */
/* BN   17-10-2002  Removed old appstate/apprequest and                  */
/*                  added new StopState and RequestStop                  */
/* PBA  21-10-2002  Added StopRequest                                    */
/* PBA  28-10-2002  Added new definitions for STOPSTATE AND SHOTDOWN     */
/* SAL  26-02-2003  Added enum RequestReset.                             */
/*************************************************************************/
#ifndef __app_cmd_h
#define __app_cmd_h


// Shared commands between OS and App
#define APP_INIT1                          1
#define APP_INIT1_DONE                     1
#define AS_LAST_BEFORE_RUN                89
#define AS_RUN                            90

#define AS_SHUTDOWN                       92
#define AS_REBOOT                         94
#define AS_SHUTDOWN_FAST                  96
#define AS_SHUTDOWN_DONE                  98
#define AS_FAILED                         99
#define AS_TERMINATED					  100	

#define APP_STATE_UNKNOWN                  0
#define APP_REQUEST_IDLE                   0

#define APP_STOP_BUTTON_UNPRESSED          0
#define APP_START_BUTTON_PRESSED           1
#define APP_STOP_BUTTON_PRESSED            2

#define APP_RESET_BUTTON_UNPRESSED         0
#define APP_RESET_BUTTON_PRESSED           1

// Definition of possible causes for last reboot.
enum RebootCause
{
   REBOOT_CAUSE_UNKNOWN,
   REBOOT_CAUSE_MANUAL_SHUTDOWN,
   REBOOT_CAUSE_CPU_HW_WATCHDOG,
   REBOOT_CAUSE_OS_REQUEST,
   REBOOT_CAUSE_SW_WATCHDOG,
   REBOOT_CAUSE_MANUAL_REBOOT,
   REBOOT_CAUSE_POWER_FAIL,
   REBOOT_CAUSE_POWER_ON,
   REBOOT_CAUSE_APP_REQUEST,
   NO_OF_REBOOT_CAUSES                  /* ! MUST be the last element in enum RebootCause ! */
};


#endif

