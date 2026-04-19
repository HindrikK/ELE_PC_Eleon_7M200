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
// $Date: 2014/03/04 14:27:06 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: Info.h,v $                                                          
// $Revision: 1.2 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <lib_main.h>

#define SCANTIME_INFO 100		// Scan time period for Info object, in [ms]

#define	MESSAGE_SPACES_LENGTH					10		//Length of spaces between end of info message and begining of new one. Must be in range 1..58
#define	OPERATE_SPACES_LENGTH					5		//Length of spaces between end of operate state and begining of new one. Must be in range 1..12
#define	SYMBOLS_SEPARATOR				'|'		//Separator symbol between information in status line
#define	LAST_SYMBOL_SEPARATOR 			'|'		//Separator symbol before operate state in status line
#define	YAW_STOPPED_SYMBOL	 			'.'		//Symbol presenting stopped yaw in status line
#define	YAW_CW_SYMBOL		 			'>'		//Symbol presenting yawing cw in status line
#define	YAW_CCW_SYMBOL				 	'<'		//Symbol presenting yawing ccw in status line




// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS Info(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);

// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

void InfoMessage(char*/*message string to display*/, U8/*duration in [s] to display message*/);

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------
BOOL GridErrorActive(void);

#endif
