//*****************************PEPTOOL Header Start******************************
//
//                         Copyright © 2014 Mita-Teknik.
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//
//*******************************************************************************
//
// $PEPTOOL version:7.0$
// $PEPTOOL file version:103$
//
//*******************************************************************************
//                                                                               
// $Date: 2014/03/04 13:22:47 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: Brake.h,v $                                                         
// $Revision: 1.3 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_BRAKE_H
#define FILE_BRAKE_H

#include <lib_main.h>


// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

STATUS Brake(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------
extern U8 GeneratorBrakeReleased(void);
// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

// Mechanical braking states
#define BRAKE_OPEN               0
#define BRAKE_CLOSE              1

// Brake modes
#define BRAKE_MODE_AUTO          0
#define BRAKE_MODE_MANUAL        1

void SetGeneratorBrake(U8 State);

// Brake programs
#define BRAKE_PROG_201    ((U8)201)   //Safety chain opened, Pitch angle = 90�, no service.

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------

extern void Starting(U8 InitState);
extern void Service(U8 InitState);
extern void YawIntoWind(U8 InitState);
extern void SelftestCheck(U8 InitState);
extern void Selftest1(U8 InitState);
extern void Selftest2(U8 InitState);
extern void Selftest3(U8 InitState);
extern void SelftestSkip(U8 InitState);
extern void FreewheelInit(U8 InitState);
extern void FreewheelG1(U8 InitState);
extern void GridConnectG1(U8 InitState);
extern void OperationG1(U8 InitState);
extern void TorqueTableChangeOperG1(U8 InitState);
extern void FreewheelG1G1(U8 InitState);

extern void BrakeProgram200(U8 InitState);
extern void BrakeProgram199(U8 InitState);
extern void BrakeProgram99(U8 InitState);
extern void BrakeProgram50(U8 InitState);
extern void PitchJogMove(U8 InitState);
extern void BatteryTest(U8 InitState);
extern void PitchServiceTest(U8 InitState);

extern BOOL GridErrorActive(void);
extern U8 WPlineError(void);
extern U8 ZeroRpm(void);
extern void (*GetOperateState(void))(U8 InitState);

#endif

