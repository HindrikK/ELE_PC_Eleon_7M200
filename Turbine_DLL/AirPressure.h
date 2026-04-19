//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2019 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:103$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: XXXX\XXX $                                                           
// $RCSfile: AirPressure.h,v $                                                   
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_AIRPRESSURE_H
#define FILE_AIRPRESSURE_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS AirPressure( U8 ModuleState, U8 *DoneState , U32 Interval );
STATUS InOutHwDriverAirPressure(U16 Counter, struct IoDriverStruct *IoDriverTable);

#define AIR_PRESSURE_INPUT_NAMES_DEF1                                      \
struct InputNamesStruct InOutHwDriverAirPressureDrvInputs[] =              \
{                                                                          \
   {"AI_AirPressure"},                                                     \
   {"P_AirPressureMBarAt4mA"},                                             \
   {"P_AirPressureMBarAt20mA"},                                            \
   {NULL},                                                                 \
};

#define AIR_PRESSURE_OUTPUT_NAMES_DEF1                                     \
struct OutputNamesStruct InOutHwDriverAirPressureDrvOutputs[] =            \
{                                                                          \
   {"V_AirPressureMeassured"},                                             \
   {NULL},                                                                 \
};

#define AIR_PRESSURE_DRIVER_STRUCT1                                        \
{                                                                          \
  {"AI_AirPressure"},                                                        \
  20,                                                                      \
  10,                                                                      \
  InOutHwDriverAirPressureDrvInputs,                                       \
  InOutHwDriverAirPressure,                                                \
  InOutHwDriverAirPressureDrvOutputs,                                      \
},

// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------

extern struct  S32Buffer      AirPressureAverBuf;

#define     AirPressure100ms() ( GetS32_100msAverage (&     AirPressureAverBuf ))
#define     AirPressure3s()    ( GetS32_3sAverage    (&     AirPressureAverBuf ))
#define     AirPressure1s()    ( GetS32_1sAverage    (&     AirPressureAverBuf ))
#define     AirPressure30s()   ( GetS32_30sAverage   (&     AirPressureAverBuf ))
#define     AirPressure10m()   ( GetS32_10mAverage   (&     AirPressureAverBuf ))
#define     AirPressure1h()    ( GetS32_1hAverage    (&     AirPressureAverBuf ))
#define     AirPressure24h()   ( GetS32_24hAverage   (&     AirPressureAverBuf ))

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------
#endif
