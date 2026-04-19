//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2015 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:103$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2014/03/04 14:23:36 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: Generator.h,v $                                                     
// $Revision: 1.4 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <lib_main.h>


// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

STATUS Generator(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
extern U8 BrakingProgramActive(void);

U8 BrakingProgramActive(void);
extern void(*GetOperateState(void))(U8 InitState);
extern void Service(U8 InitState);
U8 WPlineError(void);

extern void Service(U8 InitState);
extern void BrakeProgram200(U8 InitState);
extern void BrakeProgram199(U8 InitState);
extern void BrakeProgram99(U8 InitState);
extern void BrakeProgram50(U8 InitState);

extern void InfoMessage(char*, U8);
#endif
