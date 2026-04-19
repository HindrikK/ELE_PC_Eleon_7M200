//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2014 Mita-Teknik.                         
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
// $RCSfile: VibrationMonitoringEmulator.h,v $                                   
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_VIBRATIONMONITORINGEMULATOR_H
#define FILE_VIBRATIONMONITORINGEMULATOR_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS VibrationMonitoringEmulator( U8 ModuleState, U8 *DoneState , U32 Interval );


// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

#endif
