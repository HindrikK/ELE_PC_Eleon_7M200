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
// $Date: 2014/03/04 14:22:43 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: FlightWarningLight.h,v $                                            
// $Revision: 1.3 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_FLIGHTWARNINGLIGHT_H
#define FILE_FLIGHTWARNINGLIGHT_H

#include <lib_main.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

STATUS FlightWarningLight( U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3 );

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
U8 WPlineError( void );

#endif
