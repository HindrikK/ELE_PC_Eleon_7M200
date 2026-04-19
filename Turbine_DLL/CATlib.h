//********************************************************************
//
//            Copyright (c) 2006 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date: 2013/03/06 07:45:09 $
// $Author: MITA\ihn $
// $RCSfile: CATlib.h,v $
// $Revision: 1.2 $
//
//*******************************************************************
#ifndef FILE_CATLIB_H
#define FILE_CATLIB_H


#include <turbdef.h>
#include <os_lib.h>


//-----------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------

#define COM_DEBUG

#ifdef COM_DEBUG

#ifndef DBG_LEVEL
#define DBG_LEVEL 0
#endif

#ifndef LDEBUG
#define LDEBUG(lvl,txt) if (DBG_LEVEL >= lvl) { OS_com_printf("%s:%d ",__FILE__,__LINE__); OS_com_printf txt; OS_com_printf("\r\n"); } (void)0
#endif

#ifndef LDEBUG_RAW
#define LDEBUG_RAW(lvl,txt) if (DBG_LEVEL >= lvl) {  OS_com_printf txt; } (void)0
#endif

#else // COM_DEBUG

#ifndef LDEBUG
#define LDEBUG(lvl,txt)
#endif

#ifndef LDEBUG_RAW
#define LDEBUG_RAW(lvl,txt)
#endif

#endif // COM_DEBUG


// Abstract: Error constants.
// 12-Feb-07 FEV - Now part of sockdefs.h in WP4000/Include dir
//#define OS_WOULD_BLOCK (-319)


// Index locations of the LSB and MSB bytes as they would
// appear e.g. in the host order array "U8 Bytes[2]".
#define HOST_LSB 0
#define HOST_MSB 1

#define MIN_CHK_LIMIT 1 // In buffer comparisons: don't look at buffer segments smaller than this,
                        // just consider them different!

// Watch dog
#define WD_MAX_TIME 2000                // mSec
extern UNSIGNED Wd_Counttime_Receive;
extern U32 Receive_WD;



//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------

typedef enum
{
   FECON_CNV
} TASK_TYPE_T;


// Conversion types supported by this module.
typedef enum
{
   HOST_TO_NETWORK, // Convert HOST ORDER byte sequences to NETWORK ORDER.
   NETWORK_TO_HOST  // Convert NETWORK ORDER byte sequences to HOST ORDER.
} CONVERSION_T;




//-----------------------------------------------------------------------
// Public function prototypes
//-----------------------------------------------------------------------

// Abstract: Get the name of the current task.
//
#ifndef EMULATOR
STATUS GetTaskName(char Name[9]);
#endif // EMULATOR

// Abstract: Copy a U16 value from the "SrcBuf" array into the "DstBuf" array, converting
//           as specified in the "Conversion" flag.
//
STATUS CopyU16(/*In*/ const CONVERSION_T Conversion, /*In*/ const U16 *SrcBuf, /*Out*/ U16 *DstBuf);

// Abstract: Copy a U32 value from the "SrcBuf" array into the "DstBuf" array, converting
//           as specified in the "Conversion" flag.
//
STATUS CopyU32(/*In*/ const CONVERSION_T Conversion, /*In*/ const U32 *SrcBuf, /*Out*/ U32 *DstBuf);

// Abstract: Copy an S16 value from the "SrcBuf" array into the "DstBuf" array, converting
//           as specified in the "Conversion" flag.
//
STATUS CopyS16(/*In*/ const CONVERSION_T Conversion, /*In*/ const S16 *SrcBuf, /*Out*/ S16 *DstBuf);

// Abstract: Copy an S32 value from the "SrcBuf" array into the "DstBuf" array, converting
//           as specified in the "Conversion" flag.
//
STATUS CopyS32(/*In*/ const CONVERSION_T Conversion, /*In*/ const S32 *SrcBuf, /*Out*/ S32 *DstBuf);


#endif // FILE_CATLIB_H

