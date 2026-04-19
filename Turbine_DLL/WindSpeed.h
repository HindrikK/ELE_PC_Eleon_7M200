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
// $Date: 2014/03/04 14:40:20 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: WindSpeed.h,v $                                                     
// $Revision: 1.2 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_WINDSPEED_H
#define FILE_WINDSPEED_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS WindSpeed(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);


#define WindSpeed1s()    ( GetU32_1sAverage    (&WindSpeedAverBuf ))
#define WindSpeed3s()    ( GetU32_3sAverage    (&WindSpeedAverBuf ))
#define WindSpeed30s()   ( GetU32_30sAverage   (&WindSpeedAverBuf ))
#define WindSpeed10m()   ( GetU32_10mAverage   (&WindSpeedAverBuf ))


// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

#endif
