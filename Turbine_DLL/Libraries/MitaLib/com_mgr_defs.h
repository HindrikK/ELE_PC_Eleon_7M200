/*********************************************************************/
/*                                                                   */
/*            Copyright (c) 2001 Mita-Teknik a/s                     */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/* FILE NAME                                            VERSION      */
/*                                                                   */
/*     com_mgr.h                                                     */
/*                                                                   */
/* DESCRIPTION                                                       */
/*                                                                   */
/*     Definitions used by com manager API                           */
/*                                                                   */
/* HISTORY                                                           */
/*     NAME  DATE        REMARKS                                     */
/*     CLJ   2005-02-02  Created                                     */
/*                                                                   */
/*********************************************************************/

#ifndef __com_mgr_defs_h__
#define __com_mgr_defs_h__

#include "m_def.h"

// Clients should use this data type for holding "tokens of ownership"
// regarding communication resources.
#define TOKEN_TYPE TYPE_U32
typedef U32 TOKEN_T;

// One-based, enumerated list of COM port resources managed by these routines.
typedef enum {comm_COM1=1, comm_COM2=2,comm_END=3} COMM_RESOURCE_T;



#endif // __com_mgr_defs_h__
