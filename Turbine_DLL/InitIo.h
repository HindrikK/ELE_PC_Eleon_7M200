//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2014 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:7.0$                                                         
// $PEPTOOL file version:102$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2014/03/04 14:36:07 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: InitIo.h,v $                                                        
// $Revision: 1.2 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

#ifndef FILE_INITIO_H
#define FILE_INITIO_H

#include <os_lib.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------
STATUS InitIo();

STATUS SetValue    (char VarName[], size_t Type, U64 SetValue);
STATUS SetLockValue(char VarName[], size_t Type, U64 SetValue);
U8     WPlineError(void);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------

#endif
