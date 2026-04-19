//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2015 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:103$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2014/03/04 14:32:02 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: Operate_MT_Type2.h,v $                                              
// $Revision: 1.6 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_OPERATE_MT_TYPE2_H
#define FILE_OPERATE_MT_TYPE2_H

#include <lib_main.h>


// ---------------------------------------------------------------------
// Only this module use these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

STATUS Operate_MT_Type2(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);
extern STATUS OperateMenuAppInit(U8 ModuleState, OS_MEMORY_POOL *MemPool);

// ---------------------------------------------------------------------
// Other modules may use these variables and functions.
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Only this module use these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------
#define SCAN_20MSEC              20
#define OPERATE_SCAN_TIME        SCAN_20MSEC

// ---------------------------------------------------------------------
// Other modules may use these variables and functions.
// ---------------------------------------------------------------------

extern void Starting(BOOL firstentry);
extern void Service(BOOL firstentry);
extern void YawIntoWind(BOOL firstentry);
extern void SelftestCheck(BOOL firstentry);
extern void SelftestBC(BOOL firstentry);
extern void SelftestBrake(BOOL firstentry);
extern void Selftest1(BOOL firstentry);
extern void Selftest2(BOOL firstentry);
extern void Selftest3(BOOL firstentry);
extern void SelftestSkip(BOOL firstentry);
extern void Startup(BOOL firstentry);
extern void OperationG1(BOOL firstentry);
extern void LVRTState(BOOL firstentry);
extern void TorqueTableChangeOperG1(BOOL firstentry);
extern void LowWind(BOOL firstentry);

extern void BrakeProgram200(BOOL firstentry);
extern void BrakeProgram199(BOOL firstentry);
extern void BrakeProgram99(BOOL firstentry);
extern void BrakeProgram50(BOOL firstentry);
extern void MDSPitchJogMove(BOOL firstentry);
extern void MDSBatteryTest(BOOL firstentry);
extern void PitchServiceTest(BOOL firstentry);
extern void (*OperateState)(BOOL firstentry);
extern void (*GetOperateState(void))(BOOL firstentry);

U8 BrakingProgramActive(void);

extern U32 GetOperateStep(void);
extern void BladeCtrlResetKeyPressed(void);
extern void BladeCtrlProtocolReset   (void);

// ---------------------------------------------------------------------
// This module use these variables and functions from other modules.
// ---------------------------------------------------------------------
extern void SetGeneratorBrake(U8 State);
extern BOOL GridErrorActive(void);
extern void ForceYawToStartNow(void);
extern U8 GeneratorBrakeReleased(void);
extern STATUS SafetyChainOperate(U8 Signal);
// The following definitions are also presented in
//	Brake and should also be corrected there.

U8 WPlineError(void);
U8 CnvSystem_State( U8 request );

#define BRAKE_CLOSE              1
#endif

