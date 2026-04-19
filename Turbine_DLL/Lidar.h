//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2016 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:8.0$                                                         
// $PEPTOOL file version:103$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2012/11/27 13:18:42 $                                                  
// $Author: MITA\jks $                                                           
// $RCSfile: WindMonitoring_Windar_LIDAR.h,v $                                   
// $Revision: 1.1 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_LIDAR_H
#define FILE_LIDAR_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS Lidar(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);


// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

#endif
