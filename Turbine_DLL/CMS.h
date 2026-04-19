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
// $Date: 2014/03/04 13:22:50 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: CMS.h,v $                                                           
// $Revision: 1.2 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_CMS_H
#define FILE_CMS_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS CMS(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);

STATUS InOutCMS_PitchAngleToCurrentDrv(U16 Counter, struct IoDriverStruct *IoDriverTable);

#define CMS_INPUT_NAMES_DEF1 \
struct InputNamesStruct CMSHwDrvPitchAngleInputs[] = \
{ \
	{"V_PitchAngle"}, \
	{"P_CMSPitchAngleMin"}, \
	{"P_CMSPitchAngleMax"}, \
	{"P_CMSPitchAngleMinCurrent"}, \
	{"P_CMSPitchAngleMaxCurrent"}, \
	{NULL}, \
};

#define CMS_OUTPUT_NAMES_DEF1 \
struct OutputNamesStruct CMSHwDrvPitchAngleOutputs[] = \
{ \
	{"AO_CMSActualPitchAngle"}, \
	{NULL}, \
};

#define CMS_DRIVER_STRUCT1 \
{ \
	"V_PitchAngle", \
	20, \
	5, \
	CMSHwDrvPitchAngleInputs, \
	InOutCMS_PitchAngleToCurrentDrv, \
	CMSHwDrvPitchAngleOutputs, \
},


STATUS InOutCMS_RotorRpmToCurrentDrv(U16 Counter, struct IoDriverStruct *IoDriverTable);

#define CMS_INPUT_NAMES_DEF2 \
struct InputNamesStruct CMSHwDrvRotorRpmInputs[] = \
{ \
	{"V_ControllerRpm"}, \
	{"P_CMSRotorRpmMin"}, \
	{"P_CMSRotorRpmMax"}, \
	{"P_CMSRotorRpmMinCurrent"}, \
	{"P_CMSRotorRpmMaxCurrent"}, \
	{NULL}, \
};

#define CMS_OUTPUT_NAMES_DEF2 \
struct OutputNamesStruct CMSHwDrvRotorRpmOutputs[] = \
{ \
	{"AO_CMSRotorRpm"}, \
	{NULL}, \
};

#define CMS_DRIVER_STRUCT2 \
{ \
	"V_ControllerRpm", \
	20, \
	5, \
	CMSHwDrvRotorRpmInputs, \
	InOutCMS_RotorRpmToCurrentDrv, \
	CMSHwDrvRotorRpmOutputs, \
},


STATUS InOutCMS_PowerToCurrentDrv(U16 Counter, struct IoDriverStruct *IoDriverTable);

#define CMS_INPUT_NAMES_DEF3 \
struct InputNamesStruct CMSHwDrvPowerInputs[] = \
{ \
	{"V_GridRealPower"}, \
	{"P_CMSPowerMin"}, \
	{"P_CMSPowerMax"}, \
	{"P_CMSPowerMinCurrent"}, \
	{"P_CMSPowerMaxCurrent"}, \
	{NULL}, \
};

#define CMS_OUTPUT_NAMES_DEF3 \
struct OutputNamesStruct CMSHwDrvPowerOutputs[] = \
{ \
	{"AO_CMSActualPower"}, \
	{NULL}, \
};

#define CMS_DRIVER_STRUCT3 \
{ \
	"V_GridRealPower", \
	20, \
	5, \
	CMSHwDrvPowerInputs, \
	InOutCMS_PowerToCurrentDrv, \
	CMSHwDrvPowerOutputs, \
},


STATUS InOutCMS_YawAngleToCurrentDrv(U16 Counter, struct IoDriverStruct *IoDriverTable);

#define CMS_INPUT_NAMES_DEF4 \
struct InputNamesStruct CMSHwDrvYawDirectionInputs[] = \
{ \
	{"V_NacelleDirection"}, \
	{"P_CMSYawAngleMin"}, \
	{"P_CMSYawAngleMax"}, \
	{"P_CMSYawAngleMinCurrent"}, \
	{"P_CMSYawAngleMaxCurrent"}, \
	{NULL}, \
};

#define CMS_OUTPUT_NAMES_DEF4 \
struct OutputNamesStruct CMSHwDrvYawDirectionOutputs[] = \
{ \
	{"AO_CMSYawAngle"}, \
	{NULL}, \
};

#define CMS_DRIVER_STRUCT4 \
{ \
	"V_NacelleDirection", \
	20, \
	5, \
	CMSHwDrvYawDirectionInputs, \
	InOutCMS_YawAngleToCurrentDrv, \
	CMSHwDrvYawDirectionOutputs,\
},


// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

#endif
