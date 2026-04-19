//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2015 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:8.0$                                                         
// $PEPTOOL file version:103$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: XXXX\XXX $                                                           
// $RCSfile: Yaw_MK1.h,v $                                                       
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_YAW_MK1_H
#define FILE_YAW_MK1_H

#include <lib_main.h>

//#ifndef FILE_YAWMOTORCONTROL_MK1_H
//#include "../YawMotorControl_MK1/YawMotorControl_MK1.h"
//#endif


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS Yaw_MK1( U8 ModuleState, U8 *DoneState , U32 Interval );


// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

void ForceYawToStartNow(void);

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------
extern void InfoMessage(char*, U8);

//extern void Set_OneMotorSpeedAndTorque(U8/*motorID*/, S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
extern void Set_AllMotorsSpeedAndTorque(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueQ*/);
extern void Set_Group1MotorsSpeedAndTorque(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
extern void Set_Group2MotorsSpeedAndTorque(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
extern void Set_AllMotorsSpeedAndTorqueNoRamp(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);

extern void Apply_AllBrakes(void);
extern void Release_AllBrakes(void);
extern int Run_AllMotors(BOOL/*firstentry*/);
extern int Run_AllMotors_SpdTrq(BOOL/*firstentry*/, S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
extern int Stop_AllMotors(BOOL/*firstentry*/);
extern int Stop_AllMotors_Trq(BOOL/*firstentry*/, S16/*Torque*/);
extern int Stop_AllMotorsNoRamp(BOOL/*firstentry*/);
extern void ResetAllMotorPositions(void);
extern U8 CheckAllMotorPositions(S32/*positionLimit*/);
extern S16 GetMaxSpeedPct(void);
extern U8 GetRunDirection(void);
extern U8 CheckMotorsSpeedPct(S16/*speedLimitPct*/);
extern U8 CheckMotorsSpeedRpm(S16/*speedLimitRpm*/);
#endif
