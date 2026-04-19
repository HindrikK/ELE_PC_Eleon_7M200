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
// $Date: 2014/03/04 14:27:27 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: LubricationYaw_MT_Type1.h,v $                                       
// $Revision: 1.2 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_YAWLUBRICATION_MT_TYPE1_H
#define FILE_YAWLUBRICATION_MT_TYPE1_H

// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS LubricationYaw_MT_Type1(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);

// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------
U8 WPlineError(void);

#endif
