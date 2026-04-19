//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2015 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:101$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: XXXX\XXX $                                                           
// $RCSfile: LCNV_Comm.h,v $                                                     
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_LCNVCOMM_H
#define FILE_LCNVCOMM_H

#include <lib_main.h>

#define LCNV_COMM_SENDBUFF_SIZE 512
#define LCNV_COMM_RECEIVEBUFF_SIZE 512
#define LCNV_COMM_TIMEOUT 200
#define LCNV_COMM_ERROR_LIMIT 3
#define LCNV_COMM_RECOVER_LIMIT 3
#define LCNV_COMM_SOCKRETRY_DELAY 10000

#define LCNV_COMM_CONTROLPACKET_ID 1
#define LCNV_COMM_STATUSPACKET_ID 2
#define LCNV_COMM_SLOWPACKET_ID 3
#define LCNV_COMM_DEBUGPACKET_ID 10
#define LCNV_COMM_STATUSLOGPACKET_ID 20

#define LCNV_COMM_CONTROLDATA_VARCOUNT 20
#define LCNV_COMM_STATUSDATA_VARCOUNT 88
#define LCNV_COMM_SLOWDATA_VARCOUNT 20
#define LCNV_COMM_STATUSLOGDATA_VARCOUNT 35
#define LCNV_COMM_DEBUGDATA_VARCOUNT 45


typedef struct LCNV_Comm
{
	BOOL VarsInitialized;

	BOOL EnableCommunication;
	struct addr_struct TargetAddr;
	struct addr_struct LocalAddr;
	INT Socket;
	U16 ReceiveCounter;
	U16 SendCounter;
	U16 ReceiveErrorCounter;
	U16 SendErrorCounter;
	U16 _receiveErrorCounter;
	U16 _sendErrorCounter;
	BOOL CommStatus;
	BOOL RX_DebugOut;
	BOOL TX_DebugOut;
    U16 RX_status_Counter;
    U16 RX_slow_Counter;
    U16 RX_debug_Counter;
    U16 RX_log_Counter;

	U16* ControlData[LCNV_COMM_CONTROLDATA_VARCOUNT];		// pointers to variables
	U16* StatusData[LCNV_COMM_STATUSDATA_VARCOUNT];			// pointers to variables
	U16* SlowData[LCNV_COMM_SLOWDATA_VARCOUNT];				// pointers to variables
	U16* StatusLogData[LCNV_COMM_STATUSLOGDATA_VARCOUNT];	// pointers to variables
	U16* DebugData[LCNV_COMM_DEBUGDATA_VARCOUNT];			// pointers to variables


	// for internal use
	char sendBuffer[LCNV_COMM_SENDBUFF_SIZE];
	char receiveBuffer[LCNV_COMM_RECEIVEBUFF_SIZE];
	S32 receiveTimer;
} LCNVComm;



void LCNVComm_Initialize(LCNVComm*);
S32 LCNVComm_LoadParameters(LCNVComm*, const char* /*targetIP*/, U16 /*targetPort*/, U16 /*localPort*/);
//S32 LCNVComm_Connect(LCNVComm*);
//S32 LCNVComm_Disconnect(LCNVComm*);
void LCNVComm_Control(LCNVComm*);
S32 LCNVComm_Receive(LCNVComm*);
S32 LCNVComm_Send_CONTROL(LCNVComm*);

#endif
