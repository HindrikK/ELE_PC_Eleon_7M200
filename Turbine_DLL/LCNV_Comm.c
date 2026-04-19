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
// $RCSfile: LCNV_Comm.c,v $                                                     
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#include "LCNV_Comm.h"


#define LCNV_COMM_DEBUG
#define LCNV_COMM_SCAN_TIME 20

#define LCNV_COMM_CONTROLPACKET_SIZE (LCNV_COMM_CONTROLDATA_VARCOUNT * 2 + 2)
#define LCNV_COMM_STATUSPACKET_SIZE (LCNV_COMM_STATUSDATA_VARCOUNT * 2 + 2)
#define LCNV_COMM_SLOWPACKET_SIZE (LCNV_COMM_SLOWDATA_VARCOUNT * 2 + 2)
#define LCNV_COMM_STATUSLOGPACKET_SIZE (LCNV_COMM_STATUSLOGDATA_VARCOUNT * 2 + 2)
#define LCNV_COMM_DEBUGPACKET_SIZE (LCNV_COMM_DEBUGDATA_VARCOUNT * 2 + 2)




S32 LCNVComm_LoadParameters(LCNVComm* commObject, const char* targetIP, U16 targetPort, U16 localPort)
{
	// extract IP address from "serverIP" string
	U32 ip_addr[4];
	int result = sscanf(targetIP, "%u.%u.%u.%u", &ip_addr[0], &ip_addr[1], &ip_addr[2], &ip_addr[3]);
	if (result != 4)
	{
#ifdef LCNV_COMM_DEBUG
		OS_com_printf("\nInvalid IP address: %d\n", result);
#endif
		return -2;	// invalid IP address
	}

//	// check if IP or port has changed and decide if needs to reconnect
//	BOOL updateConnection = false;
//	if (commObject.TargetAddr.port != targetPort)
//	{
//		updateConnection = true;
//	}
//	else
//	{
//		int i;
//		for (i = 0; i < 4; i++)
//		{
//			if (commObject.TargetAddr.id.is_ip_addrs[i] != ip_addr[i])
//			{
//				updateConnection = true;
//				break;
//			}
//		}
//	}

	commObject->TargetAddr.id.is_ip_addrs[0] = ip_addr[0];
	commObject->TargetAddr.id.is_ip_addrs[1] = ip_addr[1];
	commObject->TargetAddr.id.is_ip_addrs[2] = ip_addr[2];
	commObject->TargetAddr.id.is_ip_addrs[3] = ip_addr[3];
	commObject->TargetAddr.port = targetPort;
    //commObject->TargetAddr.name = "LCNV_UDP_TARGET";
    
    commObject->LocalAddr.port = localPort;

#ifdef LCNV_COMM_DEBUG
	OS_com_printf("\nLoading new LCNV Comm parameters success\n");
	//OS_com_printf("Type: %d\n", commObject.Type);
	//OS_com_printf("Target name: %s\n", commObject.TargetAddr.name);
	OS_com_printf("IP: %u.%u.%u.%u\n", commObject->TargetAddr.id.is_ip_addrs[0], commObject->TargetAddr.id.is_ip_addrs[1], commObject->TargetAddr.id.is_ip_addrs[2], commObject->TargetAddr.id.is_ip_addrs[3]);
	OS_com_printf("Port: %d\n\n", commObject->TargetAddr.port);
#endif
    
	return 0;	// SUCCESS
}


void LCNVComm_Initialize(LCNVComm* commObject)
{
	//commObject.TargetAddr.name = "LCNV_TARGET";
	commObject->TargetAddr.family = OS_FAMILY_IP;
    commObject->TargetAddr.port = 7236;
    
    //commObject->LocalAddr.name = "LCNV_LOCAL";
    commObject->LocalAddr.family = OS_FAMILY_IP;
    commObject->LocalAddr.port = 7236;
    
	commObject->Socket = NULL;
	commObject->ReceiveCounter = 0;
	commObject->SendCounter = 0;
	commObject->ReceiveErrorCounter = 0;
    commObject->SendErrorCounter = 0;
    commObject->_receiveErrorCounter = 0;
    commObject->_sendErrorCounter = 0;
    commObject->ReceiveCounter = 0;
    commObject->SendCounter = 0;
    commObject->RX_DebugOut = false;
    commObject->TX_DebugOut = false;
    
    commObject->RX_status_Counter = 0;
    commObject->RX_slow_Counter = 0;
    commObject->RX_debug_Counter = 0;
}


// create socket - only for internal use
static S32 CreateUDPSocket(LCNVComm* commObject)
{
	int result;
    int socket;

#ifdef LCNV_COMM_DEBUG
    OS_com_printf("\n\nCreate UDP local UDP socket\n\r");
#endif
	socket = OS_Socket(OS_FAMILY_IP, OS_TYPE_DGRAM, OS_NONE);
	if (socket < 0)
	{
		OS_DEBUGLOG_make_entry(0, "Can't create UDP socket: %d\r\n", socket);
#ifdef LCNV_COMM_DEBUG
		OS_com_printf("Can't create UDP socket: %d\n", socket);
#endif
		return socket;
	}
#ifdef LCNV_COMM_DEBUG
	OS_com_printf("UDP socket created: %d\n", socket);
#endif
    
    // make the socket non-blocking
    OS_Fcntl(socket, OS_SETFLAG, OS_NO_BLOCK);
    
    // Get local IP address of controller
    varid_t varid;
    char WP4000_IP[21];
    int LocalIP = 0;
    //strcpy(WP4000_IP, "WP4000_ETH0_IP_Addr\0");   // park network
    strcpy(WP4000_IP, "WP4000_ETH1_IP_Addr\0");     // backbone
    result = OS_VarDB_GetVariableID(WP4000_IP, &varid);
    if (result != OS_SUCCESS) return -3;    // could not get varID
    result = OS_VarDB_ReadVariable(varid, &LocalIP, sizeof(LocalIP), NULL);
    if (result != OS_SUCCESS) return -4;    // could not get local IP
    
    // Initialize local UDP address
    commObject->LocalAddr.id.is_ip_addrs[0] = (LocalIP & 0x000000ff);
    commObject->LocalAddr.id.is_ip_addrs[1] = (LocalIP & 0x0000ff00) >> 8;
    commObject->LocalAddr.id.is_ip_addrs[2] = (LocalIP & 0x00ff0000) >> 16;
    commObject->LocalAddr.id.is_ip_addrs[3] = (LocalIP & 0xff000000) >> 24;
    //commObject->LocalAddr.name = "LCNV_UDP_LOCAL";
    
#ifdef LCNV_COMM_DEBUG
    OS_com_printf("Local IP: %u.%u.%u.%u\n\r", commObject->LocalAddr.id.is_ip_addrs[0], commObject->LocalAddr.id.is_ip_addrs[1], commObject->LocalAddr.id.is_ip_addrs[2], commObject->LocalAddr.id.is_ip_addrs[3]);
	OS_com_printf("Local Port: %d\n\n", commObject->LocalAddr.port);
#endif
    
    // Bind local endpoint to socket
    result = OS_Bind(socket, &commObject->LocalAddr, 0);
    if (result <= 0)
	{
		OS_DEBUGLOG_make_entry(0, "Can't bind UDP socket: %d\r\n", result);
#ifdef LCNV_COMM_DEBUG
		OS_com_printf("Can't bind UDP socket: %d\n", result);
#endif
		OS_Abort(socket);
        commObject->Socket = NULL;
        return result;
	}
#ifdef LCNV_COMM_DEBUG
		OS_com_printf("UDP socket binded: %d\n", result);
#endif

	commObject->Socket = socket;
	return 0;
}



static LCNVComm_Unpack_STATUS(LCNVComm* commObject, U16 startByte)
{
	int i;
	int j = startByte;
	for (i = 0; i < LCNV_COMM_STATUSDATA_VARCOUNT; i++)
	{
        j += 2;
        *(commObject->StatusData[i]) = *(U16*)(&commObject->receiveBuffer[j]);
	}
}

static LCNVComm_Unpack_SLOW(LCNVComm* commObject, U16 startByte)
{
	int i;
	int j = startByte;
	for (i = 0; i < LCNV_COMM_SLOWDATA_VARCOUNT; i++)
	{
        j += 2;
        *(commObject->SlowData[i]) = *(U16*)(&commObject->receiveBuffer[j]);
        //*(commObject->SlowData[i]) = commObject->receiveBuffer[j] + (commObject->receiveBuffer[j + 1] * 256);
	}
}

static LCNVComm_Unpack_DEBUG(LCNVComm* commObject, U16 startByte)
{
	int i;
	int j = startByte;
	for (i = 0; i < LCNV_COMM_DEBUGDATA_VARCOUNT; i++)
	{
        j += 2;
        *(commObject->DebugData[i]) = *(U16*)(&commObject->receiveBuffer[j]);
	}
}

static LCNVComm_Unpack_STATUSLOG(LCNVComm* commObject, U16 startByte)
{
	int i;
	int j = startByte;
	for (i = 0; i < LCNV_COMM_STATUSLOGDATA_VARCOUNT; i++)
	{
        j += 2;
        *(commObject->StatusLogData[i]) = *(U16*)(&commObject->receiveBuffer[j]);
	}
}



// Receive incoming data
S32 LCNVComm_Receive(LCNVComm* commObject)
{
    if (commObject->Socket == NULL) return -1;

	int startIndex = 0;
    int count = OS_Recv_From(commObject->Socket, commObject->receiveBuffer, LCNV_COMM_RECEIVEBUFF_SIZE, 0, &(commObject->TargetAddr), 0);

    if (count > 0)
	{
        // debug output
        if (commObject->RX_DebugOut)
        {
            OS_com_printf("\n\rLCNV Received %d bytes\n\r", count);
            int i;
            for (i = 0; i < count; i++)
            {
                OS_com_printf("%d: %X\n\r", i, commObject->receiveBuffer[i]);
            }
            OS_com_printf("END_OF_DATA\n\r");
        }
        
        // do while all packets extracted from receive buffer
        while (count > 0)
        {
            if (commObject->receiveBuffer[startIndex] == LCNV_COMM_STATUSPACKET_ID)
            {
                if (count < LCNV_COMM_STATUSPACKET_SIZE)
                {
                    commObject->ReceiveErrorCounter++;
                    commObject->_receiveErrorCounter++;
                    return -2;	// INVALID DATA
                }
                LCNVComm_Unpack_STATUS(commObject, startIndex);
                commObject->RX_status_Counter++;
                commObject->ReceiveCounter++;
                commObject->_receiveErrorCounter = 0;
                commObject->receiveTimer = LCNV_COMM_TIMEOUT;
                count -= LCNV_COMM_STATUSPACKET_SIZE;
                startIndex += LCNV_COMM_STATUSPACKET_SIZE;
            }
            else if (commObject->receiveBuffer[startIndex] == LCNV_COMM_SLOWPACKET_ID)
            {
                if (count < LCNV_COMM_SLOWPACKET_SIZE)
                {
                    commObject->ReceiveErrorCounter++;
                    commObject->_receiveErrorCounter++;
                    return 2;	// INVALID DATA
                }
                LCNVComm_Unpack_SLOW(commObject, startIndex);
                commObject->RX_slow_Counter++;
                commObject->ReceiveCounter++;
                commObject->_receiveErrorCounter = 0;
                commObject->receiveTimer = LCNV_COMM_TIMEOUT;
                count -= LCNV_COMM_SLOWPACKET_SIZE;
                startIndex += LCNV_COMM_SLOWPACKET_SIZE;
            }
            else if (commObject->receiveBuffer[startIndex] == LCNV_COMM_DEBUGPACKET_ID)
            {
                if (count < LCNV_COMM_DEBUGPACKET_SIZE)
                {
                    commObject->ReceiveErrorCounter++;
                    commObject->_receiveErrorCounter++;
                    return 2;	// INVALID DATA
                }
                LCNVComm_Unpack_DEBUG(commObject, startIndex);
                commObject->RX_debug_Counter++;
                commObject->ReceiveCounter++;
                commObject->_receiveErrorCounter = 0;
                commObject->receiveTimer = LCNV_COMM_TIMEOUT;
                count -= LCNV_COMM_DEBUGPACKET_SIZE;
                startIndex += LCNV_COMM_DEBUGPACKET_SIZE;
            }
            else if (commObject->receiveBuffer[startIndex] == LCNV_COMM_STATUSLOGPACKET_ID)
            {
                if (count < LCNV_COMM_STATUSLOGPACKET_SIZE)
                {
                    commObject->ReceiveErrorCounter++;
                    commObject->_receiveErrorCounter++;
                    return 2;	// INVALID DATA
                }
                LCNVComm_Unpack_STATUSLOG(commObject, startIndex);
                commObject->RX_log_Counter++;
                commObject->ReceiveCounter++;
                commObject->_receiveErrorCounter = 0;
                commObject->receiveTimer = LCNV_COMM_TIMEOUT;
                count -= LCNV_COMM_STATUSLOGPACKET_SIZE;
                startIndex += LCNV_COMM_STATUSLOGPACKET_SIZE;
            }
            else
            {
                commObject->ReceiveErrorCounter++;
                commObject->_receiveErrorCounter++;
                return 3;	// UNKNOWN FRAME TYPE
            }
        }
	}
	else if (count < 0)
	{
		return -1;	// RECEIVING ERROR
	}
    else if (count == 0)
    {
        return 1;	// NO DATA
    }
    
    return 0;	// SUCCESS
}



// Send CONTROL data packet
S32 LCNVComm_Send_CONTROL(LCNVComm* commObject)
{
    if (commObject->Socket == NULL) return -1;
    
    commObject->sendBuffer[0] = LCNV_COMM_CONTROLPACKET_ID;
    commObject->sendBuffer[1] = 0;

	int i;
	int j = 0;
	for (i = 0; i < LCNV_COMM_CONTROLDATA_VARCOUNT; i++)
	{
        j += 2;
        *(U16*)(&commObject->sendBuffer[j]) = *(commObject->ControlData[i]);
	}
	
    // debug output
    if (commObject->TX_DebugOut)
    {
        OS_com_printf("\n\rLCNV Send %d bytes\n\r", LCNV_COMM_CONTROLPACKET_SIZE);
        int i;
        for (i = 0; i < LCNV_COMM_CONTROLPACKET_SIZE; i++)
        {
            OS_com_printf("%d: %X\n\r", i, commObject->sendBuffer[i]);
        }
        OS_com_printf("END_OF_DATA\n\r");
    }

	int result = OS_Send_To(commObject->Socket, commObject->sendBuffer, LCNV_COMM_CONTROLPACKET_SIZE, 0, &(commObject->TargetAddr), 0);
	if (result < 0)
	{
        commObject->SendErrorCounter++;
        commObject->_sendErrorCounter++;
		return result;
	}
    commObject->SendCounter++;
    commObject->_sendErrorCounter = 0;
	return 0;
}


// Handle communication with converters
void LCNVComm_Control(LCNVComm* commObject)
{
	static U8 step = 0;
	static S32 timer;
	S32 result;

	switch (step)
	{
	case 0:

		if (commObject->VarsInitialized) step = 1;
		break;

	case 1:     // initializing connection

        if (commObject->EnableCommunication)
        {
            // Create socket for connection when it does not already exist
            if (commObject->Socket == NULL)
            {
                result = CreateUDPSocket(commObject);
                if (result < 0)
                {
                    OS_com_printf("\nLCNVcomm socket failed: %d\n", result);
                    step = 10;
                }
                else
                {
                    OS_com_printf("\nLCNVcomm socket created\n");
                    commObject->RX_status_Counter = 0;
                    commObject->RX_slow_Counter = 0;
                    commObject->RX_debug_Counter = 0;
                    step = 100;
                }
            }
        }
		break;

	case 10:

		OS_Abort(commObject->Socket);
		commObject->Socket = NULL;
		timer = LCNV_COMM_SOCKRETRY_DELAY;
		step = 11;
		break;

	case 11:  // waiting to re-assign socket

		timer -= LCNV_COMM_SCAN_TIME;
		if (timer <= 0) { step = 1; }
		break;

	case 100:  // communication running

		commObject->receiveTimer -= LCNV_COMM_SCAN_TIME;
        // comm timeout
		if (commObject->receiveTimer <= 0)
		{
			commObject->CommStatus = false;
            commObject->SendCounter = 0;
            commObject->ReceiveCounter = 0;
			step = 110;
		}
        
        // too many errors in a row
		if (commObject->_sendErrorCounter > LCNV_COMM_ERROR_LIMIT)
		{
			commObject->CommStatus = false;
            commObject->SendCounter = 0;
            commObject->ReceiveCounter = 0;
            step = 110;
		}
        
        // comm disabled
        if (!commObject->EnableCommunication)
        {
            OS_Abort(commObject->Socket);
            commObject->Socket = NULL;
            step = 1;
        }
		break;

	case 110:  // communication lost, waiting for recover
        
        if (commObject->SendCounter > 0 && commObject->ReceiveCounter > 0)
		{
            // when errorCounter overflows, add 1 to prevent false recovery of comm
            if (commObject->_sendErrorCounter == 65535) commObject->_sendErrorCounter = 1;
            if (commObject->_receiveErrorCounter == 65535) commObject->_receiveErrorCounter = 1;
            
            if (commObject->_sendErrorCounter == 0 && commObject->_receiveErrorCounter == 0 &&
                commObject->SendCounter >= LCNV_COMM_RECOVER_LIMIT && commObject->ReceiveCounter >= LCNV_COMM_RECOVER_LIMIT)
            {
                commObject->CommStatus = true;
                step = 100;
                break;
            }
        }
        else
        {
            commObject->SendCounter = 0;
            commObject->ReceiveCounter = 0;
        }
        
        if (commObject->_sendErrorCounter == 0 && commObject->_receiveErrorCounter == 0)
		{
            commObject->CommStatus = true;
			step = 100;
            break;
		}
        
        // comm disabled
        if (!commObject->EnableCommunication)
        {
            OS_Abort(commObject->Socket);
            commObject->Socket = NULL;
            step = 1;
        }
		break;
	}
}
