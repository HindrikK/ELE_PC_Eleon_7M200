/********************************************************************/
/*                                                                  */
/*            Copyright (c) 2003 Mita-Teknik a/s                    */
/*                                                                  */
/********************************************************************/
/*  $Date$
 *  $Author$
 *  $RCSfile$
 *  $Revision$ */
/********************************************************************/
/*                                                                  */
/* DESCRIPTION                                                      */
/*                                                                  */
/*     Functional description                                       */
/*     Data structure and defines for SW Watchdog interface         */
/*                                                                  */
/* FUNCTIONS                                                        */
/*                                                                  */
/*     <Function name>      <Ultra short description>               */
/*                                                                  */
/********************************************************************/

#ifndef __OS_WD_H_
#define __OS_WD_H_

/* Old definitions for backwards compatibilty */
#define WD_UNCHANGED 0
#define WD_DISABLED  1
#define WD_ENABLED   2

/* Possible states for the options */
/* Safety chain actions on watchdog trig */
#define WD_SAFETY_CHAIN_OPEN_DISABLE 0
#define WD_SAFETY_CHAIN_OPEN_ENABLE  1


/* WP-Line actions on exception */
#define WD_WP_LINE_ON           0
#define WD_WP_LINE_OFF          1
#define WD_WP_LINE_INPUT        2

/* Reboot action on exception */
#define WD_REBOOT_OFF           0
#define WD_REBOOT_NORMAL        1
#define WD_REBOOT_FAST          2

/* Statuscode action if WD trig */
#define WD_STATUSCODE_DISABLE   0
#define WD_STATUSCODE_ENABLE    1

/* Options that might be enabled on a watchdog (> 0).
   Options are by default disabled (0) and must be 
   enabled explicitely (>0).
 */
enum WD_Options
{
   WD_SAFETY_CHAIN = 0,
   WD_WP_LINE,
   WD_REBOOT,
   WD_STATUSCODE
};

#endif
