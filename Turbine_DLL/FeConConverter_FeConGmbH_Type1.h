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
#ifndef FILE_FECONCONVERTER_FECONGMBH_TYPE1_H
#define FILE_FECONCONVERTER_FECONGMBH_TYPE1_H

#include <lib_main.h>

#ifndef WRDEBUG
#define WRDEBUG 1
#endif

#ifndef DDEBUG
#define DDEBUG(act,txt) if (WRDEBUG == act) { OS_com_printf txt; OS_com_printf("\r\n"); } (void)0
#endif

#ifndef DBGPOINT
#define DBGPOINT(act) if (WRDEBUG == act) { OS_com_printf("%s:%d ",__FILE__,__LINE__); OS_com_printf("\r\n"); } (void)0
#endif

// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------

STATUS FeConConverter_FeConGmbH_Type1(U8 ModuleState, OS_MEMORY_POOL *MemPool, U32 *Arg3);

#define CNV_EVENTLOG_ID 1

//Grid-side
#define GS_SW_VER_CTRL_CARD             9       //0.9
#define GS_XML_INTERFACE_DEFINITION     4       //0.4
#define GS_VENDOR_ID                    531     //531 (0x213) (FeCon GmbH)
#define GS_PROD_CODE                    196608  //196608 (0x30000)
#define GS_REV_NUMBER                   131076  // 131076 (0x20004)

//Machine-side
#define MS_SW_VER_CTRL_CARD             17      //1.7
#define MS_XML_INTERFACE_DEFINITION     6       //0.6
#define MS_VENDOR_ID                    531     //531 (0x213) (FeCon GmbH)
#define MS_PROD_CODE                    200704  //200704 (0x31000)
#define MS_REV_NUMBER                   131078  //131078 (0x20006)

// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------
U8 CnvSystem_State( U8 request );   //Return count of the converter unit in requested state
U8 Set_CnvSystem_State( U8 state);  //Function set required state, return TRUE when request is fulfilled
// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------

extern void InfoMessage(char*, U8);

#endif
