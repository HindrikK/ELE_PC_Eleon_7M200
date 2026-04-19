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
// $RCSfile: YawMotorControl_MK1.h,v $                                           
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_YAWMOTORCONTROL_MK1_H
#define FILE_YAWMOTORCONTROL_MK1_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS YawMotorControl_MK1( U8 ModuleState, U8 *DoneState , U32 Interval );


// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

//void Set_OneMotorSpeedAndTorque(U8/*motorID*/, S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
void Set_AllMotorsSpeedAndTorque(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueQ*/);
void Set_Group1MotorsSpeedAndTorque(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
void Set_Group2MotorsSpeedAndTorque(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
void Set_AllMotorsSpeedAndTorqueNoRamp(S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);

void Apply_AllBrakes(void);
void Release_AllBrakes(void);
int Run_AllMotors(BOOL/*firstentry*/);
int Run_AllMotors_SpdTrq(BOOL/*firstentry*/, S16/*Speed*/, S16/*TorqueM*/, S16/*TorqueG*/);
int Stop_AllMotors(BOOL/*firstentry*/);
int Stop_AllMotors_Trq(BOOL/*firstentry*/, S16/*Torque*/);
int Stop_AllMotorsNoRamp(BOOL/*firstentry*/);
void ResetAllMotorPositions(void);
U8 CheckAllMotorPositions(S32/*positionLimit*/);
S16 GetMaxSpeedPct(void);
U8 GetRunDirection(void);
U8 CheckMotorsSpeedPct(S16/*speedLimitPct*/);
U8 CheckMotorsSpeedRpm(S16/*speedLimitRpm*/);

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------
extern void InfoMessage(char*, U8);

#endif
