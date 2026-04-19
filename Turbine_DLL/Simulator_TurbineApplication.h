//***********************************************************************
//
//            Copyright (c) Eleon a/s
//
//***********************************************************************
//
// $Date: 2014/09/17 00:00:00 $
// $Author: Hindrik $
// $RCSfile: Simulator_TurbineApplication.h,v $
// $Revision: 1.0 $
//
//***********************************************************************

//***********************************************************************
#ifndef FILE_SIMULATOR_TURBINEAPPLICATION_H
#define FILE_SIMULATOR_TURBINEAPPLICATION_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Variables and functions
// ----------------------------------------------------------------------

extern STATUS Simulator_TurbineApplication_Initialize(void);
extern void Simulator_TurbineApplication_Control(void);

/*extern BOOL Sim_ModeChanged;
extern BOOL * V_SimStartTurbine_value;
extern BOOL * V_SimStopTurbine_value;
extern char * V_SimulationModeTxt_value;
extern char * V_SimulationStateTxt_value;*/

#endif
