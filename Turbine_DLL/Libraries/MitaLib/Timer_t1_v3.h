//********************************************************************
//
//            Copyright (c) 2003 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date$
// $Author$
// $RCSfile$
// $Revision$
//
//*******************************************************************
#ifndef FILE_TIMER_T1_V3_H
#define FILE_TIMER_T1_V3_H
#include <os_lib.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------


// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------
#define TIMER_10MS   10
#define TIMER_20MS   20
#define TIMER_100MS  100
#define TIMER_1000MS 1000

#define TIMER_DOWN   -1
#define TIMER_STOP    0
#define TIMER_UP      1

#define TIMER_DOWN_END   -1
#define TIMER_NONE_END    0
#define TIMER_UP_END      1

#define TIME_OUT_VARIABLE 0
#define TIME_OUT_POINTER  1

/********************************************************************

 STURCT NAME      StandardTimerVarStruct
 -----------
This struct is made in the application. All the timer functions uses this struct.

 FEELDS
 ------
   TimerValue     Timer value [ms]

   TimeOutPointer Pointer to the timeout variable [ms]

   IntervalTime   Timer interval [ms]. The function "StandardTimer" is called
                  with this interval.
                  Value: Internal variable, always set to 0

   Start          Value: TIMER_DOWN / TIMER_STOP / TIMER_UP

   StandardTimerCalled
                  Is used to check if the "StandardTimer" function is called.

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New struct.
*******************************************************************/
struct StandardTimerVarStruct
{
   U32 TimerValue;
   const U32 *TimeOutPointer;
   U16  IntervalTime;
   S8  Start;
   U8 StandardTimerCalled;
   U8  OldStart;
};

/********************************************************************

 FUNCTION NAME    StandardTimer
 -------------
 DESCRIPTION
 -----------
 The main timer function. Must be called every run through if the timer shall
 work. Increments or decrements the timer.
 "StandardTimerCalled" is set to 1.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------
   TIMER_DOWN_END    The timer is counted down to zero.
   TIMER_NONE_END    The timer is unequal to zero or the timer is unequal to
                     "TimeOutValue" or "Start" = TIMER_STOP.
   TIMER_UP_END      The timer is counted up to "TimeOutValue".

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/
S8 StandardTimer(struct StandardTimerVarStruct *StandardTimerVars);

/********************************************************************

 FUNCTION NAME    StandardTimerNotCalled
 -------------
 DESCRIPTION
 -----------
 Is used to check if the "StandardTimer" function is called. This function MUST
 use the same run through time as the "StandardTimer" function.
 "StandardTimerCalled" is set to 0.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------
   0              If the "StandardTimer" function was not called since last time
                  the "StandardTimerNotCalled" was called.

   1              If the "StandardTimer" function was called since last time
                  the "StandardTimerNotCalled" was called.

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/
U8 StandardTimerNotCalled(struct StandardTimerVarStruct *StandardTimerVars);

/********************************************************************

 FUNCTION NAME    StopTimer
 -------------
 DESCRIPTION
 -----------
 Stops the timer. The timer stayes at the value where it is stopped.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/
void StopTimer(struct StandardTimerVarStruct *StandardTimerVars);

/********************************************************************

 FUNCTION NAME    SetTimer
 -------------
 DESCRIPTION
 -----------
 Set the timer to a specific value.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

   SetValue       Set value for the timer.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/


#define SetTimer settimerredefined  //changes names

void SetTimer(struct StandardTimerVarStruct *StandardTimerVars, U32 SetValue);

/********************************************************************

 FUNCTION NAME    GetTimer
 -------------
 DESCRIPTION
 -----------
                  Returns the actual timer value

 ARGUMENTS
 ---------
   TimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.



*******************************************************************/
U32 GetTimer(struct StandardTimerVarStruct *Delay );

/********************************************************************

 FUNCTION NAME    ResetTimer
 -------------
 DESCRIPTION
 -----------
 Resets the timer to zero and stops the timer.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/
void ResetTimer(struct StandardTimerVarStruct *StandardTimerVars);

/********************************************************************

 FUNCTION NAME    StartTimer
 -------------
 DESCRIPTION
 -----------
 Is only used for normal up counter functions.
 When the function is called, the timer will start counting up.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/
void StartTimer(struct StandardTimerVarStruct *StandardTimerVars);

/********************************************************************

 FUNCTION NAME    StartTimerUp
 -------------
 DESCRIPTION
 -----------
 Is only used for up/down counter functions.
 When the function is called, the timer will start counting up.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/
void StartTimerUp(struct StandardTimerVarStruct *StandardTimerVars);

/********************************************************************

 FUNCTION NAME    StartTimerDown
 -------------
 DESCRIPTION
 -----------
 Is only used for up/down counter functions.
 When the function is called, the timer will start counting down.

 ARGUMENTS
 ---------
   StandardTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN           2002-01-22  New function.

*******************************************************************/
void StartTimerDown(struct StandardTimerVarStruct *StandardTimerVars);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------

/********************************************************************

 STURCT NAME      VdbTimerVarStruct
 -----------
 This struct is made in the application.
 All the Vdb timer functions uses this struct.

 FEELDS
 ------
   TimerValue     Timer value [ms]

   TimeOutPointer Pointer to the timeout variable [ms]

   IntervalTime   Timer interval [ms]. The function "VdbTimer" is called
                  with this interval.
                  Value: Internal variable, always set to 0

   Start          Value: TIMER_DOWN / TIMER_STOP / TIMER_UP

   VdbTimerCalled
                  Is used to check if the "VdbTimer" function is called.

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.
*******************************************************************/
struct VdbTimerVarStruct
{
   U32     TimerValue;
   const   U32 *TimeOutPointer;
   U16     IntervalTime;
   S8      Start;
   U8      VdbTimerCalled;
   varid_t TimerSaved;
   U8      OldStart;
};

/********************************************************************

 FUNCTION NAME    VdbTimer
 -------------
 DESCRIPTION
 -----------
 The main timer function. Must be called every run through if the timer shall
 work. Increments or decrements the timer.
 "VdbTimerCalled" is set to 1.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------
   TIMER_DOWN_END    The timer is counted down to zero.
   TIMER_NONE_END    The timer is unequal to zero or the timer is unequal to
                     "TimeOutValue" or "Start" = TIMER_STOP.
   TIMER_UP_END      The timer is counted up to "TimeOutValue".

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
S8 VdbTimer(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    VdbTimerNotCalled
 -------------
 DESCRIPTION
 -----------
 Is used to check if the "VdbTimer" function is called. This function MUST
 use the same run through time as the "VdbTimer" function.
 "VdbTimerCalled" is set to 0.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------
   0              If the "VdbTimer" function was not called since last time
                  the "VdbTimerNotCalled" was called.

   1              If the "VdbTimer" function was called since last time
                  the "VdbTimerNotCalled" was called.

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
U8 VdbTimerNotCalled(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    StopVdbTimer
 -------------
 DESCRIPTION
 -----------
 Stops the timer. The timer stayes at the value where it is stopped.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
void StopVdbTimer(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    SetVdbTimer
 -------------
 DESCRIPTION
 -----------
 Set the timer to a specific value.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

   SetValue       Set value for the timer.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
void SetVdbTimer(struct VdbTimerVarStruct *VdbTimerVars, U32 SetValue);

/********************************************************************

 FUNCTION NAME    GetVdbTimer
 -------------
 DESCRIPTION
 -----------
 Returns the actual timer value

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.



*******************************************************************/
U32 GetVdbTimer(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    ResetVdbTimer
 -------------
 DESCRIPTION
 -----------
 Resets the timer to zero and stops the timer.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
void ResetVdbTimer(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    StartVdbTimer
 -------------
 DESCRIPTION
 -----------
 Is only used for normal up counter functions.
 When the function is called, the timer will start counting up.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
void StartVdbTimer(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    StartVdbTimerUp
 -------------
 DESCRIPTION
 -----------
 Is only used for up/down counter functions.
 When the function is called, the timer will start counting up.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
void StartVdbTimerUp(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    StartVdbTimerDown
 -------------
 DESCRIPTION
 -----------
 Is only used for up/down counter functions.
 When the function is called, the timer will start counting down.

 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
void StartVdbTimerDown(struct VdbTimerVarStruct *VdbTimerVars);

/********************************************************************

 FUNCTION NAME    InitVdbTimerSave
 -------------
 DESCRIPTION
 -----------
                  Is used to initialize VdbTimerStruct
                  with information on backup variable Id
                  based upon actual backup variable name
 ARGUMENTS
 ---------
   VdbTimerVars
                  Pointer to struct in the application.

 RETURN VALUES
 -------------

 HISTORY
 -------
    NAME         DATE        REMARKS
    PHa          2005-10-13  New function.

*******************************************************************/
STATUS InitVdbTimerSave(struct VdbTimerVarStruct *Delay, char *VdbName);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------

#endif
