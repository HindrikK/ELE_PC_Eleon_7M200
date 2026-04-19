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
// $Date: 2014/03/04 14:35:39 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: Torque.h,v $                                                        
// $Revision: 1.3 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_TORQUE_H
#define FILE_TORQUE_H

#include <lib_main.h>


// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------
#define PI_S64   (S64) 31416
#define SAMPLE_TIME             0.02

#define SCAN_20MSEC                                 20

STATUS Torque(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);


// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

// Max number of entries in the active torque table.
#define TORQUE_TBL_MAX 11

// Control routine of this module.
extern STATUS TorqueTblLookUp(U8 ModuleState);

// Torque table lookup function - returns a (possibly interpolated) torque
// corresponding to specified rpm value.
extern S32 GetTorqueFromRpmActTbl(U32 GeneratorRpm);
extern S32 GetTorqueFromRpmNewTbl(U32 GeneratorRpm);
extern S32 GetRpmFromPowerActTbl(U32 PowerLimit);

// Call this function from Torque table when updated.
extern void SetupActTorqueTable(U8 TblSelect);
extern void SetupNewTorqueTable(U8 TblSelect);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
#endif
