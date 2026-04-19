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
// $Date: 2014/03/04 14:32:13 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: Panels.h,v $                                                        
// $Revision: 1.5 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_PANELS_H
#define FILE_PANELS_H

#include <lib_main.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

STATUS Panels( U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3 );

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
BOOL SafetyChainOpen( void );
U8 WPlineError(void);
BOOL GridErrorActive(void);

#endif
