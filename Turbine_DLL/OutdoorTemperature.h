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
// $Date: 2014/03/04 14:32:08 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: OutdoorTemperature.h,v $                                            
// $Revision: 1.2 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_OUTDOORTEMPERATURE_H
#define FILE_OUTDOORTEMPERATURE_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS OutdoorTemperature(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);

#define OutdoorTemp1s()    ( GetS32_1sAverage    (&OutdoorTempAverBuf ))
#define OutdoorTemp3s()    ( GetS32_3sAverage    (&OutdoorTempAverBuf ))
#define OutdoorTemp30s()   ( GetS32_30sAverage   (&OutdoorTempAverBuf ))
#define OutdoorTemp10m()   ( GetS32_10mAverage   (&OutdoorTempAverBuf ))

// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

#endif
