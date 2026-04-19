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
// $Date: 2014/03/04 14:24:27 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: Grid.h,v $                                                          
// $Revision: 1.2 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_GRID_H
#define FILE_GRID_H

// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------
STATUS GridSummation_t1_v2_lib(U8 ModuleState, OS_MEMORY_POOL *MemoryPool);
STATUS Grid(U8 ModuleState, OS_MEMORY_POOL *MemPool);

/*
extern struct  S32Buffer      GridRealPowerAverBuf;

#define     GridRealPower100ms() ( GetS32_100msAverage (&     GridRealPowerAverBuf ))
#define     GridRealPower3s()    ( GetS32_3sAverage    (&     GridRealPowerAverBuf ))
#define     GridRealPower1s()    ( GetS32_1sAverage    (&     GridRealPowerAverBuf ))
#define     GridRealPower30s()   ( GetS32_30sAverage   (&     GridRealPowerAverBuf ))
#define     GridRealPower10m()   ( GetS32_10mAverage   (&     GridRealPowerAverBuf ))
#define     GridRealPower1h()    ( GetS32_1hAverage    (&     GridRealPowerAverBuf ))
#define     GridRealPower24h()   ( GetS32_24hAverage   (&     GridRealPowerAverBuf ))

extern struct  S32Buffer      GridReactivePowerAverBuf;

#define     GridReactivePower100ms() ( GetS32_100msAverage (&     GridReactivePowerAverBuf ))
#define     GridReactivePower3s()    ( GetS32_3sAverage    (&     GridReactivePowerAverBuf ))
#define     GridReactivePower1s()    ( GetS32_1sAverage    (&     GridReactivePowerAverBuf ))
#define     GridReactivePower30s()   ( GetS32_30sAverage   (&     GridReactivePowerAverBuf ))
#define     GridReactivePower10m()   ( GetS32_10mAverage   (&     GridReactivePowerAverBuf ))
*/

extern struct  Avg_S32Buffer      GridRealPowerAverBuf;


#define     GridRealPower100ms() ( Avg_GetS32_100msAverage (&     GridRealPowerAverBuf ))
#define     GridRealPower3s()    ( Avg_GetS32_3sAverage    (&     GridRealPowerAverBuf ))
#define     GridRealPower1s()    ( Avg_GetS32_1sAverage    (&     GridRealPowerAverBuf ))
#define     GridRealPower30s()   ( Avg_GetS32_30sAverage   (&     GridRealPowerAverBuf ))
#define     GridRealPower10m()   ( Avg_GetS32_10mAverage   (&     GridRealPowerAverBuf ))
#define     GridRealPower1h()    ( Avg_GetS32_1hAverage    (&     GridRealPowerAverBuf ))
#define     GridRealPower24h()   ( Avg_GetS32_24hAverage   (&     GridRealPowerAverBuf ))

extern struct  Avg_S32Buffer      GridReactivePowerAverBuf;


#define     GridReactivePower100ms() ( Avg_GetS32_100msAverage (&     GridReactivePowerAverBuf ))
#define     GridReactivePower3s()    ( Avg_GetS32_3sAverage    (&     GridReactivePowerAverBuf ))
#define     GridReactivePower1s()    ( Avg_GetS32_1sAverage    (&     GridReactivePowerAverBuf ))
#define     GridReactivePower30s()   ( Avg_GetS32_30sAverage   (&     GridReactivePowerAverBuf ))
#define     GridReactivePower10m()   ( Avg_GetS32_10mAverage   (&     GridReactivePowerAverBuf ))

BOOL GridErrorActive(void);

struct GridSumInputNamesStruct
{
   const char *Name;
   varid_t Id;
   SUBSCRIPTION LocalGridSumSubscription;
   U32 OldPowerDelta;
   U32 LocalDeltaTotalPower;
   U32 LocalPowerDelta;
   U64 NewTimeStamp;
   U64 OldTimeStamp;
   U64 PowerFactor;
};

struct GridSumOutputNamesStruct
{
   const char *Name;
   varid_t Id;
   U32 Value;
};

// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

extern OS_TASK GridSumOsVar;
extern OS_QUEUE LocalGridSumQueue;

#endif
