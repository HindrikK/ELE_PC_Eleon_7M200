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
// $Date: 2014/03/04 14:22:32 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: FeConConverter_FeConGmbH_Type1.h,v $                                
// $Revision: 1.10 $                                                             
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_LIEBHERRCONVERTER_H
#define FILE_LIEBHERRCONVERTER_H

#include <lib_main.h>

// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS LiebherrConverter( U8 ModuleState, U8 *DoneState , U32 Interval );

// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

extern void InfoMessage(char*, U8);

#endif
