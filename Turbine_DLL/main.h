//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright � 2012 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:6.0$                                                         
// $PEPTOOL file version:100$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2012/09/11 11:18:33 $                                                  
// $Author: MITA\bho $                                                           
// $RCSfile: main.h,v $                                                          
// $Revision: 1.1 $                                                             
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_MAIN_H
#define FILE_MAIN_H

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------
#define APP_WD_MAXTIME     100
#define APP_INIT_PRIORITY  80
#define APP_RUN_PRIORITY   30

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------
void app_mainApplication(UNSIGNED Argc, struct application_arguments *Argv);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
U8 ZeroRpm(void);

#endif

