/********************************************************************/
/*                                                                  */
/*            Copyright (c) 2003 Mita-Teknik a/s                    */
/*                                                                  */
/********************************************************************/
/*  $Date$
 *  $Author$
 *  $RCSfile$
 *  $Revision$ */
/********************************************************************/
/*                                                                  */
/* DESCRIPTION                                                      */
/*                                                                  */
/*     Macros to initialize StatusCodes                             */
/*                                                                  */
/* FUNCTIONS                                                        */
/*                                                                  */
/*     NA                                                           */
/*                                                                  */
/********************************************************************/

#ifndef __STSCODE_MACROS_H__
#define __STSCODE_MACROS_H__
#include "types.h"

#ifdef __GNUC__
#define CHARPTR
#else
#define CHARPTR (char *)
#endif
/* Macro defining Status codes including Min and Max limits for parameters */

#define STS_CODE_ELEMENT(Name,                                    /* Status code text */\
                         PowerUpDelay,                            /* Status code powerup delay */\
                         No,                                      /* Status code number */\
                         UpdateType,                              /* Status code update type */\
                         ResetPasswordLevel,                      /* Status code reset access code */\
                         SetTimerType,                            /* Status code Set timer type */\
                         ResetTimerType,                          /* Status code Reset timer type */\
                         ResetType,                               /* Status code Reset type */\
                         DisplayPriority,                         /* Status code display priority */\
                         AvailabilityGroup,                       /* Status code Availability group*/\
                         Availability_Min,                        /* AvailabilityGroup parameter Minimum value */\
                         Availability_Max,                        /* AvailabilityGroup parameter Maximum value */\
                         Availability_SelectionList,              /* AvailabilityGroup parameter SelectionList - not implemented yet - set to NULL */\
                         AvailabilityAccessRead,                  /* Access code to read AvailabilityGroup parameter */\
                         AvailabilityAccessWrite,                 /* Access code to write AvailabilityGroup parameter */\
                         SetFunc,                                 /* Status code Set function pointer */\
                         ResetFunc,                               /* Status code Reset function pointer */\
                         ControlProgram1,                         /* Status code Control Program 1 parameter - not parameter yet*/\
                         CP1_Min,                                 /* ControlProgram1 parameter Minimum value - not parameter yet */\
                         CP1_Max,                                 /* ControlProgram1 parameter Maximum value - not parameter yet */\
                         CP1_SelectionList,                       /* ControlProgram1 parameter SelectionList - not implemented yet - set to NULL */\
                         ControlProgram1AccessRead,               /* Access code to read Control program 1 parameter  */\
                         ControlProgram1AccessWrite,              /* Access code to write Control program 1 parameter */\
                         ControlProgram2,                         /* Status code Control Program 2 parameter - not parameter yet*/\
                         CP2_Min,                                 /* ControlProgram2 parameter Minimum value - not parameter yet */\
                         CP2_Max,                                 /* ControlProgram2 parameter Maximum value - not parameter yet */\
                         CP2_SelectionList,                       /* ControlProgram2 parameter SelectionList - not implemented yet - set to NULL */\
                         ControlProgram2AccessRead,               /* Access code to read Control program 2 parameter  */\
                         ControlProgram2AccessWrite,              /* Access code to write Control program 2 parameter */\
                         ControlProgram3,                         /* Status code Control Program 3 parameter - not parameter yet*/\
                         CP3_Min,                                 /* ControlProgram3 parameter Minimum value - not parameter yet */                                             \
                         CP3_Max,                                 /* ControlProgram3 parameter Maximum value - not parameter yet */                                             \
                         CP3_SelectionList,                       /* ControlProgram3 parameter SelectionList - not implemented yet - set to NULL */                                           \
                         ControlProgram3AccessRead,               /* Access code to read Control program 3 parameter  */\
                         ControlProgram3AccessWrite,              /* Access code to write Control program 3 parameter */\
                         Enable,                                  /* Status code Enable/Disable parameter */\
                         EnableAccessRead,                        /* Access code to read Enable parameter  */\
                         EnableAccessWrite,                       /* Access code to write Enable parameter */\
                         UpdateInterval,                          /* Status code update interval parameter - not parameter yet */\
                         UpdateInterval_Min,                      /* UpdateInterval parameter Minimum value - not parameter yet */\
                         UpdateInterval_Max,                      /* UpdateInterval parameter Maximum value - not parameter yet */\
                         UpdateInterval_SelectionList,            /* UpdateInterval parameter SelectionList - not implemented yet - set to NULL */\
                         UpdateIntervalAccessRead,                /* Access code to read Update interval parameter  */\
                         UpdateIntervalAccessWrite,               /* Access code to write Update interval parameter */\
                         SetDelay,                                /* Status code Set delay parameter */\
                         SetDelay_Min,                            /* SetDelay parameter Minimum value */\
                         SetDelay_Max,                            /* SetDelay parameter Maximum value */\
                         SetDelay_SelectionList,                  /* SetDelay parameter SelectionList - not implemented yet - set to NULL */\
                         SetDelayAccessRead,                      /* Access code to read Set delay parameter  */\
                         SetDelayAccessWrite,                     /* Access code to write Set delay parameter */\
                         ResetDelay,                              /* Status code Reset delay parameter */\
                         ResetDelay_Min,                          /* ResetDelay parameter Minimum value */\
                         ResetDelay_Max,                          /* ResetDelay parameter Maximum value */\
                         ResetDelay_SelectionList,                /* ResetDelay parameter SelectionList - not implemented yet - set to NULL */\
                         ResetDelayAccessRead,                    /* Access code to read Reset delay parameter  */\
                         ResetDelayAccessWrite,                   /* Access code to write Reset delay parameter */\
                         RepeatTimes,                             /* Status code Repeat times parameter - not parameter yet */\
                         RepeatTimes_Min,                         /* RepeatTimes parameter Minimum value - not parameter yet */\
                         RepeatTimes_Max,                         /* RepeatTimes parameter Maximum value - not parameter yet */\
                         RepeatTimes_SelectionList,               /* RepeatTimes parameter SelectionList - not implemented yet - set to NULL */\
                         RepeatTimesAccessRead,                   /* Access code to read Repeat times parameter  */\
                         RepeatTimesAccessWrite,                  /* Access code to write Repeat times parameter */\
                         RepeatPeriod,                            /* Status code Repeat period parameter - not parameter yet */\
                         RepeatPeriod_Min,                        /* RepeatPeriod parameter Minimum value - not parameter yet */\
                         RepeatPeriod_Max,                        /* RepeatPeriod parameter Maximum value - not parameter yet */\
                         RepeatPeriod_SelectionList,              /* RepeatPeriod parameter SelectionList - not implemented yet - set to NULL */\
                         RepeatPeriodAccessRead,                  /* Access code to read RepeatPeriod parameter  */\
                         RepeatPeriodAccessWrite,                 /* Access code to write RepeatPeriod parameter */\
                         RepeatCode,                              /* Status code Repeat code parameter - not parameter yet */\
                         RepeatCode_Min,                          /* RepeatCode parameter Minimum value - not parameter yet */\
                         RepeatCode_Max,                          /* RepeatCode parameter Maximum value - not parameter yet */\
                         RepeatCode_SelectionList,                /* RepeatCode parameter SelectionList - not implemented yet - set to NULL */\
                         RepeatCodeAccessRead,                    /* Access code to read RepeatCode parameter  */\
                         RepeatCodeAccessWrite,                   /* Access code to write RepeatCode parameter */\
                         TimeoutPeriod,                           /* Status code Timeout period parameter - not parameter yet */\
                         TimeoutPeriod_Min,                       /* TimeoutPeriod parameter Minimum value - not parameter yet */\
                         TimeoutPeriod_Max,                       /* TimeoutPeriod parameter Maximum value - not parameter yet */\
                         TimeoutPeriod_SelectionList,             /* TimeoutPeriod parameter SelectionList - not implemented yet - set to NULL */\
                         TimeoutPeriodAccessRead,                 /* Access code to read TimeoutPeriod parameter  */\
                         TimeoutPeriodAccessWrite,                /* Access code to write TimeoutPeriod parameter */\
                         TimeoutCode,                             /* Status code Timeout code parameter - not parameter yet */\
                         TimeoutCode_Min,                         /* TimeoutCode parameter Minimum value - not parameter yet */\
                         TimeoutCode_Max,                         /* TimeoutCode parameter Maximum value - not parameter yet */\
                         TimeoutCode_SelectionList,               /* TimeoutCode parameter SelectionList - not implemented yet - set to NULL */\
                         TimeoutCodeAccessRead,                   /* Access code to read TimeoutCode parameter  */\
                         TimeoutCodeAccessWrite,                  /* Access code to write TimeoutCode parameter */\
                         ActivateCounterAccessRead,               /* Access code to read ActivateCounter backup*/ \
                         ActivateCounterAccessWrite,              /* Access code to write ActivateCounter backup */\
                         BackupFileName)                          /* Pointer to Status code Backup file name */  \
{                                         \
   CHARPTR Name,                          \
   PowerUpDelay,                          \
   No,                                    \
   UpdateType,                            \
   ResetPasswordLevel,                    \
   SetTimerType,                          \
   ResetTimerType,                        \
   ResetType,                             \
   DisplayPriority,                       \
   AvailabilityGroup,                     \
   (U8 (*)(void))SetFunc,                 \
   (U8 (*)(void))ResetFunc,               \
   ControlProgram1,                       \
   ControlProgram1AccessRead,             \
   ControlProgram1AccessWrite,            \
   ControlProgram2,                       \
   ControlProgram2AccessRead,             \
   ControlProgram2AccessWrite,            \
   ControlProgram3,                       \
   ControlProgram3AccessRead,             \
   ControlProgram3AccessWrite,            \
   Enable,                                \
   EnableAccessRead,                      \
   EnableAccessWrite,                     \
   0,                                     \
   0,                                     \
   0,                                     \
   UpdateInterval,                        \
   UpdateIntervalAccessRead,              \
   UpdateIntervalAccessWrite,             \
   SetDelay,                              \
   SetDelayAccessRead,                    \
   SetDelayAccessWrite,                   \
   ResetDelay,                            \
   ResetDelayAccessRead,                  \
   ResetDelayAccessWrite,                 \
   RepeatTimes,                           \
   RepeatTimesAccessRead,                 \
   RepeatTimesAccessWrite,                \
   RepeatPeriod,                          \
   RepeatPeriodAccessRead,                \
   RepeatPeriodAccessWrite,               \
   RepeatCode,                            \
   RepeatCodeAccessRead,                  \
   RepeatCodeAccessWrite,                 \
   TimeoutPeriod,                         \
   TimeoutPeriodAccessRead,               \
   TimeoutPeriodAccessWrite,              \
   TimeoutCode,                           \
   TimeoutCodeAccessRead,                 \
   TimeoutCodeAccessWrite,                \
   CHARPTR BackupFileName,                \
   CP1_Min,                               \
   CP1_Max,                               \
   CP2_Min,                               \
   CP2_Max,                               \
   CP3_Min,                               \
   CP3_Max,                               \
   Availability_Min,                      \
   Availability_Max,                      \
   UpdateInterval_Min,                    \
   UpdateInterval_Max,                    \
   SetDelay_Min,                          \
   SetDelay_Max,                          \
   ResetDelay_Min,                        \
   ResetDelay_Max,                        \
   RepeatTimes_Min,                       \
   RepeatTimes_Max,                       \
   RepeatPeriod_Min,                      \
   RepeatPeriod_Max,                      \
   RepeatCode_Min,                        \
   RepeatCode_Max,                        \
   TimeoutPeriod_Min,                     \
   TimeoutPeriod_Max,                     \
   TimeoutCode_Min,                       \
   TimeoutCode_Max,                       \
   (void *)Availability_SelectionList,    \
   (void *)CP1_SelectionList,             \
   (void *)CP2_SelectionList,             \
   (void *)CP3_SelectionList,             \
   (void *)UpdateInterval_SelectionList,  \
   (void *)SetDelay_SelectionList,        \
   (void *)ResetDelay_SelectionList,      \
   (void *)RepeatTimes_SelectionList,     \
   (void *)RepeatPeriod_SelectionList,    \
   (void *)RepeatCode_SelectionList,      \
   (void *)TimeoutPeriod_SelectionList,   \
   (void *)TimeoutCode_SelectionList,     \
   ActivateCounterAccessRead,             \
   ActivateCounterAccessWrite,            \
   AvailabilityAccessRead,                \
   AvailabilityAccessWrite,               \
   NULL,                                  \
}

#endif
