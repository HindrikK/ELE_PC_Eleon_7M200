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
// $Date: 2012/09/11 11:18:38 $                                                  
// $Author: MITA\bho $                                                                
// $RCSfile: os_main.h,v $                                                       
// $Revision: 1.1 $                                                             
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef OS_MAIN
#define OS_MAIN

//#define INCLUDE_DEBUG		// Enable this to activate debug mode for all objects (Eleon specific)
#define DLL_SIMU			// this define compiles turbine application in DLL mode
#define DLL_SIMU_EXTERNALPITCH    // this means blade movement is simulated externally and DLL receives actual blade angles as input

#include <os_lib.h>
#include <menudefs.h>
#include <app_cmd.h>
#include <versiontest.inc>
#include <password.h>
#include <unit.h>

#endif

