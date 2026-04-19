/********************************************************************/
/*                                                                  */
/*            Copyright (c) 2002 Mita-Teknik a/s                    */
/*                                                                  */
/********************************************************************/
/********************************************************************/
/*                                                                  */
/* FILE NAME                                            VERSION     */
/*                                                                  */
/*       password.h                                                 */
/*                                                                  */
/* DESCRIPTION                                                      */
/*       Table of passwordlevels in WP4000                          */
/*                                                                  */
/* AUTHOR   Mita-teknik a/s                                         */
/*                                                                  */
/* DATA STRUCTURES                                                  */
/*                                                                  */
/* DEPENDENCIES                                                     */
/*                                                                  */
/* HISTORY                                                          */
/*       NAME      DATE         REMARKS                             */
/*       BJE       2002-01-26   Created                             */
/*                                                                  */
/********************************************************************/
#ifndef __password_h
#define __password_h

/* Password levels */

#define PASSWORD_LEVEL_UNLOGGED_IN           ((access_t)0)
#define PASSWORD_LEVEL_GUEST                 ((access_t)10)
#define PASSWORD_LEVEL_END_CUSTOMER          ((access_t)30)
#define PASSWORD_LEVEL_LICENCE_CUSTOMER      ((access_t)50)
#define PASSWORD_LEVEL_SERVICE               ((access_t)80)
#define PASSWORD_LEVEL_SUPERVISOR            ((access_t)90)
#define PASSWORD_LEVEL_ADMINISTRATOR         ((access_t)100)
#define PASSWORD_LEVEL_LICENCE_PROGRAMMER    ((access_t)190)
#define PASSWORD_LEVEL_MITA_PROGRAMMER       ((access_t)200)

#endif
