//*****************************PEPTOOL Header Start******************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <IEC104_Client.h>

#define M_EI_NA_1					70		// End of Initialisation (70)
#define C_IC_NA_1					100		// Interrogation command (100)
#define C_CI_NA_1					101		// Counter interrogation command (101)
#define C_RD_NA_1					102		// Read Command (102)
#define C_CS_NA_1					103		// Clock synchronisation command (103)
#define C_TS_NA_1					104		// Test command (104)
#define C_RP_NA_1					105		// Reset process command (105)
#define C_CD_NA_1					106		// C_CD_NA_1 Delay acquisition command (106)
#define C_TS_TA_1					107		// Test command with time tag CP56Time2a (107)
#define P_ME_NA_1					110		// Parameter of measured values, normalized value (110)
#define P_ME_NB_1					111		// Parameter of measured values, scaled value (111)
#define P_ME_NC_1					112		// Parameter of measured values, short floating point number (112)
#define P_AC_NA_1					113		// Parameter activation
#define F_FR_NA_1					120		// File ready
#define F_SR_NA_1					121		// Section ready
#define F_SC_NA_1					122		// Call directory, select file, call file, call section
#define F_LS_NA_1					123		// Last section, last segment
#define F_FA_NA_1					124		// ACK file ACK section
#define F_SG_NA_1					125		// Segment
#define F_DR_TA_1					126		// Directory
//#define F_SC_NB_1					127		// Query log - request archive file

#define eIEC870_COT_UNUSED			0		// Not used (0)
#define eIEC870_COT_CYCLIC			1		// Cyclic data (1)
#define eIEC870_COT_BACKGROUND		2		// Background request (2)
#define eIEC870_COT_SPONTAN			3		// Spontaneous data (3)
#define eIEC870_COT_INIT			4		// End of initialisation (4)
#define eIEC870_COT_REQ				5		// Read-Request (5)
#define eIEC870_COT_ACT				6		// Command activation (6)
#define eIEC870_COT_ACT_CON			7		// Acknowledgement of command activation (7)
#define eIEC870_COT_DEACT			8		// Command abort (8)
#define eIEC870_COT_DEACT_CON		9		// Acknowledgement of command deactivation (9)
#define eIEC870_COT_ACT_TERM		10		// Termination of command activation (10)
#define eIEC870_COT_RETREM			11		// Return because of remote command (11)
#define eIEC870_COT_RETLOC			12		// Return because of local command (12)
#define eIEC870_COT_FILE			13		// File access (13)
#define eIEC870_COT_14				14		// Reserved/not used (14)
#define eIEC870_COT_15				15		// Reserved/not used (15)
#define eIEC870_COT_16				16		// Reserved/not used (16)
#define eIEC870_COT_17				17		// Reserved/not used (17)
#define eIEC870_COT_18				18		// Reserved/not used (18)
#define eIEC870_COT_19				19		// Reserved/not used (19)
#define eIEC870_COT_INROGEN			20		// Station interrogation (general) (20)
#define eIEC870_COT_INRO1			21		// Station interrogation of group 1 (21)
#define eIEC870_COT_INRO2			22		// Station interrogation of group 2 (22)
#define eIEC870_COT_INRO3			23		// Station interrogation of group 3 (23)
#define eIEC870_COT_INRO4			24		// Station interrogation of group 4 (24)
#define eIEC870_COT_INRO5			25		// Station interrogation of group 5 (25)
#define eIEC870_COT_INRO6			26		// Station interrogation of group 6 (26)
#define eIEC870_COT_INRO7			27		// Station interrogation of group 7 (27)
#define eIEC870_COT_INRO8			28		// Station interrogation of group 8 (28)
#define eIEC870_COT_INRO9			29		// Station interrogation of group 9 (29)
#define eIEC870_COT_INRO10			30		// Station interrogation of group 10 (30)
#define eIEC870_COT_INRO11			31		// Station interrogation of group 11 (31)
#define eIEC870_COT_INRO12			32		// Station interrogation of group 12 (32)
#define eIEC870_COT_INRO13			33		// Station interrogation of group 13 (33)
#define eIEC870_COT_INRO14			34		// Station interrogation of group 14 (34)
#define eIEC870_COT_INRO15			35		// Station interrogation of group 15 (35)
#define eIEC870_COT_INRO16			36		// Station interrogation of group 16 (36)
#define eIEC870_COT_REQCOGEN		37		// Counter request (general) (37)
#define eIEC870_COT_REQCO1			38		// Counter request of group 1 (38)
#define eIEC870_COT_REQCO2			39		// Counter request of group 2 (39)
#define eIEC870_COT_REQCO3			40		// Counter request of group 3 (40)
#define eIEC870_COT_REQCO4			41		// Counter request of group 4 (41)
#define eIEC870_COT_42				42		// Reserved/not used (42)
#define eIEC870_COT_43				43		// Reserved/not used (43)
#define eIEC870_COT_UNKNOWN_TYPE	44		// Unknown type (44)
#define eIEC870_COT_UNKNOWN_CAUSE	45		// Unknown transmission cause (45)
#define eIEC870_COT_UNKNOWN_ASDU_ADDRESS	46	// Unknown collective ASDU (46)
#define eIEC870_COT_UNKNOWN_OBJECT_ADDRESS	47	// Unknown object address (47)
#define eIEC870_COT_48				48		// Reserved/not used (48)
#define eIEC870_COT_49				49		// Reserved/not used (49)
#define eIEC870_COT_50				50		// Reserved/not used (50)
#define eIEC870_COT_51				51		// Reserved/not used (51)
#define eIEC870_COT_52				52		// Reserved/not used (52)
#define eIEC870_COT_53				53		// Reserved/not used (53)
#define eIEC870_COT_54				54		// Reserved/not used (54)
#define eIEC870_COT_55				55		// Reserved/not used (55)
#define eIEC870_COT_56				56		// Reserved/not used (56)
#define eIEC870_COT_57				57		// Reserved/not used (57)
#define eIEC870_COT_58				58		// Reserved/not used (58)
#define eIEC870_COT_59				59		// Reserved/not used (59)
#define eIEC870_COT_60				60		// Reserved/not used (60)
#define eIEC870_COT_61				61		// Reserved/not used (61)
#define eIEC870_COT_62				62		// Reserved/not used (62)
#define eIEC870_COT_63				63		// Reserved/not used (63)

#define I104C_DEBUG
#define IEC104C_TYPE_CHECK      // this enables the validation of object structure by checking the "Type" value
#define IEC104C_TYPE 169
#define IEC104C_DEFAULT_ASDU 3
#define IEC104C_DEFAULT_ORIGINATOR 0
#define IEC104C_DEFAULT_STATION 1
#define IEC104C_DEFAULT_PORT 2404
#define IEC104C_KEEPALIVE_PERIOD (20*1000)
#define IEC104_CONNECT_TIMEOUT (2*1000)
#define IEC104C_RECONNECT_TIMEOUT (10*1000)
#define IEC104C_ACKNOWLEDGE_TIMEOUT (10*1000)
#define IEC104C_ACKNOWLEDGE_COUNT_W 8
#define IEC104C_ACKNOWLEDGE_COUNT_K 12

#define I104C_RECV_BUFFER_TCP_SIZE 256
#define I104C_SEND_BUFFER_TCP_SIZE 256

#define CONNECTING_TASK_STACK_SZ        0x10000
#define CONNECTING_TASK_PRIORITY        100
#define CONNECTING_TASK_AUTOSTART       OS_START


// function declarations
static void Disabled_State(BOOL, IEC104Client);
static void WaitingForReconnect_State(BOOL, IEC104Client);
static void Connecting_State(BOOL, IEC104Client);
static void Operational_State(BOOL, IEC104Client);

struct IEC104_Client
{
	U8 Type;            // This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	struct IEC104Client_Info* Info;
	BOOL InfoEnabled;
	U32 Task_Scantime;
	IEC104Database Database;
	OS_TASK TCPConnectingTask;
	INT Socket;
	
	int LocalIP;
	struct addr_struct ServerAddr;
	U16 ServerPortTCP;
	U8 ASDU;
	U8 originatorAdr;
	U16 StationAddress; //The station address of the IEC60870 - 5 - 104 server station, the common address of ASDU in an IEC message.
	
	U16 ConnectTimeout;					// Defines the timeout of the TCP Connect operation in milliseconds.
	U16 ReconnectTimeout;				// The interval of reconnecting attempt while communication is not established.
    U32 KeepAlivePeriod;                // When nothing has been transmit within this timeout, then TEST ACT frame is sent as keepalive.
	//U16 CommunicationTestInterval;		// Time interval for communication test messages in seconds.
	//U8 ResponseTimeout;					// Timeout in seconds for send or test APDUs. If no response is received within this timeout, the connection will be closed.
	U8 AcknowledgeTimeout;				// The timeout for sending an acknowledgement if the amount of APDUs defined by the Unacknowledge Receive property is not received.
	//U8 ActivationReplyTime;				// The maximum time the IEC client station waits for an activation confirmation message from the IEC server.
	//U8 ActivationTerminationTimeout;	// The maximum time the IEC client station waits for an activation termination message from the IEC server.
	//BOOL ActivationTerminationWaited;	// The waiting of the activation termination message.With value false, the timer length defined with the CT attribute is
										// not started.False is needed with some IEC60870-5-104 server implementations, which do no send activation termination messages at all.
	//BOOL DisableautGISendingDurInit;	// Sending of the general interrogation command when the client gets the zero(OK) status. When this is false, a general
										// interrogation command is always sent when the object status of the IEC client station gets the value zero, e.g.when
										// set in use or after a suspension. When this is true, general interrogation is not sent automatically at zero status.
	//BOOL DisableSendingGIWhenASDU70;	// Sending of the general interrogation command when the client receives ASDU 70. When this is false, a general interrogation
										// command is always sent when the end of initialization message(ASDU 70) is received from the IEC server.
										// When this is true, general interrogation is not sent automatically when receiving ASDU 70.
	//BOOL EnablePrivateAsduHandling;		// Private ASDU handling. When this is true, the private range ASDUs 146, 148 and 160 are handled as unknown ASDUs. 
										// Thus, the contents of these ASDUs are sent to a bitstream process object if the Unrecognized Command Handling is set to true.
	U16 UnacknowledgeReceive;			// The maximum number of APDUs that are received without acknowledging them to the remote host.
	//U16 UnacknowledgeSent;				// The maximum number of APDUs sent without receiving acknowledgment from the remote host.

	BOOL Connected;
	BOOL Connecting;
	BOOL ConnectingError;

	U16 ConnectTimeoutTimer; 
	U16 ReconnectTimeoutTimer;
	U32 KeepAliveTimer;
    U32 AcknowledgeTimer;
    U16 UnacknowledgeCounter;
	BOOL StartDT;
	BOOL StartDTReceived;
	BOOL StopDTReceived;
	BOOL TestFRReceived;
    BOOL DebugPrintRawFrames;
    BOOL DebugPrintInfo;
	
	char Recv_Buffer_TCP[I104C_RECV_BUFFER_TCP_SIZE];
	char Send_Buffer_TCP[I104C_SEND_BUFFER_TCP_SIZE];

	U16 SendSequence;          // counts sent frames; bit 0 is always zero - basically needs to be incremented by 2
	U16 ReceiveSequence;       // counts received frames; bit 0 is always zero - basically needs to be incremented by 2

	BOOL IEC104ClientEnabled;
	BOOL IEC104ClientEnabled_prev;

	void(*StateFunctionPointer)(BOOL, IEC104Client);
	void(*StateFunctionPointer_Prev)(BOOL, IEC104Client);
};



#ifdef IEC104C_TYPE_CHECK
// Validate object reference; Returns FALSE if invalid object reference
static BOOL IEC104Client_ValidateObject(IEC104Client client)
{
	if (client->Type == IEC104C_TYPE) { return true; }
	else { return false; }
}
#endif


IEC104Client IEC104Client_New(char* varName, U32 scantime, S32 localIP)
{
	IEC104Client newIEC104Client;

	int result = OS_Allocate_Memory(GetMemPool(), &newIEC104Client, sizeof(struct IEC104_Client), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }
    
    memset(newIEC104Client, 0, sizeof(struct IEC104_Client));  // clear object memory
	((IEC104Client)newIEC104Client)->Type = IEC104C_TYPE;
	((IEC104Client)newIEC104Client)->Task_Scantime = scantime;
	((IEC104Client)newIEC104Client)->Database = NULL;

	((IEC104Client)newIEC104Client)->ASDU = IEC104C_DEFAULT_ASDU;
	((IEC104Client)newIEC104Client)->LocalIP = localIP;
	((IEC104Client)newIEC104Client)->ServerPortTCP = IEC104C_DEFAULT_PORT;
	((IEC104Client)newIEC104Client)->StationAddress = IEC104C_DEFAULT_STATION;
	((IEC104Client)newIEC104Client)->originatorAdr = IEC104C_DEFAULT_ORIGINATOR;

	((IEC104Client)newIEC104Client)->ConnectTimeout = IEC104_CONNECT_TIMEOUT;
	((IEC104Client)newIEC104Client)->ReconnectTimeout = IEC104C_RECONNECT_TIMEOUT;

	//((IEC104Client)newIEC104Client)->CommunicationTestInterval = 20;
	//((IEC104Client)newIEC104Client)->ResponseTimeout = 15*1000;
	((IEC104Client)newIEC104Client)->AcknowledgeTimeout = IEC104C_ACKNOWLEDGE_TIMEOUT;
	//((IEC104Client)newIEC104Client)->ActivationReplyTime = 10;
	//((IEC104Client)newIEC104Client)->ActivationTerminationTimeout = 60;
	//((IEC104Client)newIEC104Client)->ActivationTerminationWaited = true;
	//((IEC104Client)newIEC104Client)->DisableautGISendingDurInit = false;
	//((IEC104Client)newIEC104Client)->DisableSendingGIWhenASDU70 = false;
	//((IEC104Client)newIEC104Client)->EnablePrivateAsduHandling = false;
	((IEC104Client)newIEC104Client)->UnacknowledgeReceive = IEC104C_ACKNOWLEDGE_COUNT_W;
	//((IEC104Client)newIEC104Client)->UnacknowledgeSent = 12;

	((IEC104Client)newIEC104Client)->TestFRReceived = true;

	((IEC104Client)newIEC104Client)->DebugPrintRawFrames = false;
    ((IEC104Client)newIEC104Client)->StartDT = true;
	((IEC104Client)newIEC104Client)->KeepAliveTimer = 0;
	((IEC104Client)newIEC104Client)->KeepAlivePeriod = IEC104C_KEEPALIVE_PERIOD;
    ((IEC104Client)newIEC104Client)->ReceiveSequence = 0;
    ((IEC104Client)newIEC104Client)->SendSequence = 0;
    ((IEC104Client)newIEC104Client)->AcknowledgeTimer = 0;
    ((IEC104Client)newIEC104Client)->UnacknowledgeCounter = 0;
	((IEC104Client)newIEC104Client)->ServerAddr.family = OS_FAMILY_IP;
	((IEC104Client)newIEC104Client)->Socket = NULL;
	((IEC104Client)newIEC104Client)->Connecting = false;
	((IEC104Client)newIEC104Client)->ConnectingError = false;
	((IEC104Client)newIEC104Client)->Connected = false;
	((IEC104Client)newIEC104Client)->Info = NULL;
    ((IEC104Client)newIEC104Client)->Info->InterfaceEventLog = NULL;
	((IEC104Client)newIEC104Client)->InfoEnabled = false;
	((IEC104Client)newIEC104Client)->StateFunctionPointer = Connecting_State;
	((IEC104Client)newIEC104Client)->StateFunctionPointer_Prev = 0;


	// clear buffers
	memset(((IEC104Client)newIEC104Client)->Recv_Buffer_TCP, 0, sizeof(((IEC104Client)newIEC104Client)->Recv_Buffer_TCP));
	memset(((IEC104Client)newIEC104Client)->Send_Buffer_TCP, 0, sizeof(((IEC104Client)newIEC104Client)->Send_Buffer_TCP));
    
    //create var in database for storing pointer to IEC104Slave to share with other programs(ie "IEC104_Slave_Interface")
	if (strlen(varName) >= 31 || strlen(varName) == 0)
	{
        AppSystemLog(7, "IEC104C vName fail");
        return NULL;
	}
    struct os_db_local myVars[] =
    {
       VAR_ELEMENT_LOCAL(varName, TYPE_U32, 200/*level read*/, 200/*level write*/, SCALE_NONE, 0, UNIT_NONE, 0, 0, 0, 0, NULL, NOLOG_ENABLE)

    };

    struct os_db_local* newIEC104Slavedatabasevar;
    result = OS_Allocate_Memory(GetMemPool(), &newIEC104Slavedatabasevar, sizeof(struct os_db_local), OS_NO_SUSPEND);
    if (result != OS_SUCCESS) { return NULL; }
    
    newIEC104Slavedatabasevar->c = myVars->c;
    newIEC104Slavedatabasevar->l = myVars->l;
    
    size_t ErrorEntry = 0;
    result = OS_VarDB_CreateLocals(newIEC104Slavedatabasevar, sizeof(myVars) / sizeof(myVars[0]), &ErrorEntry, AppLocalParameterPosition());
    if (result != 0)
    {
        AppSystemLog(7, "IEC104S vC fail: %d", result);
        return NULL;
    }
    else
    {
        OS_VarDB_UpdateVariableByName(varName, &newIEC104Client, sizeof(newIEC104Client));
    }

	return ((IEC104Client)newIEC104Client);
}


S32 IEC104Client_LoadParameters(IEC104Client client, BOOL Enable, S32 localIP, const char* serverIP, U16 serverPortTCP, U8 ASDU)
{
#ifdef IEC104C_TYPE_CHECK
	if (!IEC104Client_ValidateObject(client)) { return -1; }         // pointer to invalid object structure
#endif

	client->ServerPortTCP = serverPortTCP;
	client->ASDU = ASDU;
	client->IEC104ClientEnabled = Enable;

	client->LocalIP = localIP;

	// extract IP address from "serverIP" string
	U8 ip_addr[4];
	int result = sscanf(serverIP, "%u.%u.%u.%u", &ip_addr[0], &ip_addr[1], &ip_addr[2], &ip_addr[3]);
	if (result != 4)
	{
#ifdef MBM_DEBUG
		OS_com_printf("\n\rInvalid IP address: %d\n\r", result);
#endif
		return -2;	// invalid IP address
	}

	// check if IP or port has changed and decide if needs to reconnect
	BOOL updateConnection = false;
	if ((client->ServerAddr).port != serverPortTCP)
	{
		updateConnection = true;
	}
	else
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			if ((client->ServerAddr).id.is_ip_addrs[i] != ip_addr[i])
			{
				updateConnection = true;
				break;
			}
		}
	}

	(client->ServerAddr).id.is_ip_addrs[0] = ip_addr[0];
	(client->ServerAddr).id.is_ip_addrs[1] = ip_addr[1];
	(client->ServerAddr).id.is_ip_addrs[2] = ip_addr[2];
	(client->ServerAddr).id.is_ip_addrs[3] = ip_addr[3];
	(client->ServerAddr).port = serverPortTCP;

	if (client->InfoEnabled)
	{
		sprintf(client->Info->ServerIPString, "%u.%u.%u.%u", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
		ip_addr[0] = (client->LocalIP & 0x000000ff);
		ip_addr[1] = (client->LocalIP & 0x0000ff00) >> 8;
		ip_addr[2] = (client->LocalIP & 0x00ff0000) >> 16;
		ip_addr[3] = (client->LocalIP & 0xff000000) >> 24;
		sprintf(client->Info->LocalIPString, "%u.%u.%u.%u", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);

		client->Info->ServerPortTCP = client->ServerPortTCP;
		client->Info->ASDU = client->ASDU;
	}

	return 0;
}


S32 IEC104Client_SetDatabase(IEC104Client client, IEC104Database database)
{
#ifdef IEC104C_TYPE_CHECK
	if (!IEC104Client_ValidateObject(client)) { return -1; }         // pointer to invalid object structure
#endif
	client->Database = database;
	return 0;
}

IEC104Client_Info *IEC104Client_GetInfo(IEC104Client client, CustomLog customLog)
{
    // if Info struct had already been initialized
    if (client->Info != NULL)
    {
        // if customLog is invalid then logging is not used, but other info will still work
        // check if the object is valid (type==118)
        if (customLog != NULL)
        {
            // validate given CustomLog object by making entry and checking for success
            if ( CustomLog_MakeEntry(customLog, "Client Manager attached") == 0)
            {
                client->Info->InterfaceEventLog = customLog;
            }
            else
            {
                client->Info->InterfaceEventLog = NULL;
            }
        }
        else
        {
            client->Info->InterfaceEventLog = NULL;
        }
        
        return client->Info;
    }
    
	int result = OS_Allocate_Memory(GetMemPool(), (void *)&client->Info, sizeof(IEC104Client_Info), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	//set Info default values
    client->Info->Type = 123456;
	client->Info->ReceivedCounter = 0;
	client->Info->SentCounter = 0;

	U8 ip_addr[4];
	ip_addr[0] = (client->ServerAddr).id.is_ip_addrs[0];
	ip_addr[1] = (client->ServerAddr).id.is_ip_addrs[1];
    ip_addr[2] = (client->ServerAddr).id.is_ip_addrs[2];
    ip_addr[3] = (client->ServerAddr).id.is_ip_addrs[3];
	sprintf(client->Info->ServerIPString, "%u.%u.%u.%u", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
	ip_addr[0] = (client->LocalIP & 0x000000ff);
	ip_addr[1] = (client->LocalIP & 0x0000ff00) >> 8;
	ip_addr[2] = (client->LocalIP & 0x00ff0000) >> 16;
	ip_addr[3] = (client->LocalIP & 0xff000000) >> 24;
	sprintf(client->Info->LocalIPString, "%u.%u.%u.%u", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    
    client->Info->ServerPortTCP = client->ServerPortTCP;
	client->Info->ASDU = client->ASDU;
    
    // if customLog is invalid then logging is not used, but other info will still work
    // check if the object is valid (type==118)
    if (customLog != NULL)
    {
        // validate given CustomLog object by making entry and checking for success
        if ( CustomLog_MakeEntry(customLog, "Client Manager attached") == 0)
        {
            client->Info->InterfaceEventLog = customLog;
        }
        else
        {
            client->Info->InterfaceEventLog = NULL;
        }
    }
    else
    {
        client->Info->InterfaceEventLog = NULL;
    }

	client->InfoEnabled = true;
	return client->Info;
}


// Disconnect from IEC104 server
S32 Disconnect(IEC104Client client)
{
    client->Connected = false;
	OS_Abort(client->Socket);
	client->Socket = NULL;
	return 0;
}


static void ConnectingTaskEntry(UNSIGNED args, void* argv)
{
	IEC104Client client = argv;

	OS_Fcntl(client->Socket, OS_SETFLAG, OS_BLOCK);			// make the socket blocking

	// Connect to server
	int result = OS_Connect(client->Socket, &(client->ServerAddr), 0);
	if (result < 0)
	{
		Disconnect(client);
        if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Connect failed"); }
#ifdef I104C_DEBUG
		OS_com_printf("\n\rI104C connecting failed: %d\n\r", result);
#endif
	}
#ifdef I104C_DEBUG
	else
	{
		OS_com_printf("\n\rI104C connected\n\r");
        OS_Fcntl(client->Socket, OS_SETFLAG, OS_NO_BLOCK);		// make the socket non blocking
        client->ReceiveSequence = 0;
        client->SendSequence = 0;
        client->AcknowledgeTimer = 0;
        client->UnacknowledgeCounter = 0;
        client->Connected = true;
	}
#endif
	return;
}

static S32 Connect(IEC104Client client)
{
	int result;

	// Create socket for connection when it does not already exist
	if (client->Socket < 0)
	{
		//check if socket has been aborted by connecting task
		if (client->Connecting)
		{
			client->Connecting = false;
			return -1;
		}
		client->Connecting = true;
		client->ConnectTimeoutTimer = 0;
		result = OS_Socket(OS_FAMILY_IP, OS_TYPE_STREAM, OS_NONE);
		if (result < 0)
		{
			OS_DEBUGLOG_make_entry(0, "Can't create IEC104Client socket: %d\n\r", result);
#ifdef I104C_DEBUG
			OS_com_printf("\n\rCan't create IEC104Client socket: %d\n\r", result);
#endif			
			return result;
		}
		client->Socket = result;
		OS_DEBUGLOG_make_entry(0, "IEC104Client socket created: %d\n\r", result);
#ifdef I104C_DEBUG
		OS_com_printf("\n\rIEC104Client socket created: %d\n\r", result);
#endif
		result = OS_module_task_create(&(client->TCPConnectingTask), "I104C_TCP", ConnectingTaskEntry, 0, client, CONNECTING_TASK_STACK_SZ, CONNECTING_TASK_PRIORITY, 0, OS_PREEMPT, CONNECTING_TASK_AUTOSTART, GetMemPool());
		if (result < 0)
		{
#ifdef I104C_DEBUG
			OS_com_printf("IEC104Client connect task create failed: %d\n\r", result);
#endif
			return result;
		}
		return 0;
	}

	client->ConnectTimeoutTimer += client->Task_Scantime;
	if (client->ConnectTimeoutTimer >= client->ConnectTimeout)
	{
		return OS_TIMEOUT;	// timeout
	}
    
	return 0;
}


static void Send_StartDT(IEC104Client client)
{
	client->Send_Buffer_TCP[0] = 0x68;
	client->Send_Buffer_TCP[1] = 0x04;
	client->Send_Buffer_TCP[2] = 0x07;
	client->Send_Buffer_TCP[3] = 0x00;
	client->Send_Buffer_TCP[4] = 0x00;
	client->Send_Buffer_TCP[5] = 0x00;

	OS_Send(client->Socket, client->Send_Buffer_TCP, 6, 0);
    
    // TX printout
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\n\rI104C TX: ");
        int j;
        for (j = 0; j < client->Send_Buffer_TCP[1] + 2; j++)
        {
            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
        }
    }
    if (client->DebugPrintInfo)
    {
        OS_com_printf("\n\r -> I104C TX: START DT");
    }
    
	if (client->InfoEnabled)
	{
		client->Info->SentCounter += 1;
	}
}

static void Send_StopDT(IEC104Client client)
{
	client->Send_Buffer_TCP[0] = 0x68;
	client->Send_Buffer_TCP[1] = 0x04;
	client->Send_Buffer_TCP[2] = 0x19;
	client->Send_Buffer_TCP[3] = 0x00;
	client->Send_Buffer_TCP[4] = 0x00;
	client->Send_Buffer_TCP[5] = 0x00;

	OS_Send(client->Socket, client->Send_Buffer_TCP, 6, 0);
    
    // TX printout
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\n\rI104C TX: ");
        int j;
        for (j = 0; j < client->Send_Buffer_TCP[1] + 2; j++)
        {
            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
        }
    }
    if (client->DebugPrintInfo)
    {
        OS_com_printf("\n\r -> I104C TX: STOP DT");
    }
    
	if (client->InfoEnabled)
	{
		client->Info->SentCounter += 1;
	}
}

static void Send_TestFR(IEC104Client client) 
{
	
	// preload some answer bytes
	client->Send_Buffer_TCP[0] = 0x68;
	client->Send_Buffer_TCP[1] = 0x04;
	client->Send_Buffer_TCP[2] = 0x43;
	client->Send_Buffer_TCP[3] = 0x00;
	client->Send_Buffer_TCP[4] = 0x00;
	client->Send_Buffer_TCP[5] = 0x00;

    OS_Send(client->Socket, client->Send_Buffer_TCP, 6, 0);
    
    // TX printout
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\n\rI104C TX: ");
        int j;
        for (j = 0; j < client->Send_Buffer_TCP[1] + 2; j++)
        {
            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
        }
    }
    if (client->DebugPrintInfo)
    {
        OS_com_printf("\n\r -> I104C TX: TEST FR");
    }
	
	if (client->InfoEnabled)
	{
		client->Info->SentCounter += 1;
	}
}

static void Send_SFrame(IEC104Client client)
{
	// S-format APDUs need to be sent before timeout, buffer overflow or crossed max num of allowed i format APDUs without acknowledgment.
	client->Send_Buffer_TCP[0] = 0x68;
	client->Send_Buffer_TCP[1] = 0x04;
	client->Send_Buffer_TCP[2] = 0x01;
	client->Send_Buffer_TCP[3] = 0x00;
	client->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	client->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);


	OS_Send(client->Socket, client->Send_Buffer_TCP, 6, 0);
    
    // TX printout
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\n\rI104C TX: ");
        int j;
        for (j = 0; j < client->Send_Buffer_TCP[1] + 2; j++)
        {
            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
        }
    }
    if (client->DebugPrintInfo)
    {
        OS_com_printf("\n\r -> I104C TX: S-FRAME(%u)", client->ReceiveSequence);
    }
    
	if (client->InfoEnabled)
	{
		client->Info->SentCounter += 1;
	}
}

void IEC104Client_SendGeneralInterrogation(IEC104Client client)
{
	client->Send_Buffer_TCP[0] = 0x68;                  // Start byte
	client->Send_Buffer_TCP[1] = 0x0E;                  // Length
	// Control field
    client->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00FF);
    client->Send_Buffer_TCP[3] = (U8)(client->SendSequence >> 8);
    client->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00FF);
    client->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence >> 8);
    // ASDU header
    client->Send_Buffer_TCP[6] = C_IC_NA_1;             // ASDU type
    client->Send_Buffer_TCP[7] = (U8)0x01;;             // VSQ
    client->Send_Buffer_TCP[8] = eIEC870_COT_ACT;       // COT
    client->Send_Buffer_TCP[9] = client->originatorAdr;
    client->Send_Buffer_TCP[10] = (U8)0xFF;
    client->Send_Buffer_TCP[11] = (U8)0xFF;
    // IOA
    client->Send_Buffer_TCP[12] = (U8)0x00;
    client->Send_Buffer_TCP[13] = (U8)0x00;
    client->Send_Buffer_TCP[14] = (U8)0x00;
    
    client->Send_Buffer_TCP[15] = (U8)0x14;
    
    U8 totalLen = client->Send_Buffer_TCP[1] + 2;
	OS_Send(client->Socket, client->Send_Buffer_TCP, totalLen, 0);
    client->SendSequence += 2;  // Increment the sequence number for I-frames
    
    // TX printout
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\n\rI104C TX: ");
        int j;
        for (j = 0; j < totalLen; j++)
        {
            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
        }
    }
    if (client->DebugPrintInfo)
    {
        OS_com_printf("\n\r -> I104C TX: GEN INTERRO");
    }
    
	if (client->InfoEnabled)
	{
		client->Info->SentCounter += 1;
	}
}

//void IEC104Client_SendGeneralInterrogation(IEC104Client client)
//{
//	client->Send_Buffer_TCP[0] = 0x68;                  // Start byte
//	client->Send_Buffer_TCP[1] = 0x0D;                  // Length
//	// Control field
//    client->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00FF);
//    client->Send_Buffer_TCP[3] = (U8)(client->SendSequence >> 8);
//    client->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00FF);
//    client->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence >> 8);
//    // ASDU header
//    client->Send_Buffer_TCP[6] = C_IC_NA_1;             // ASDU type
//    client->Send_Buffer_TCP[7] = (U8)0x01;;             // VSQ
//    client->Send_Buffer_TCP[8] = eIEC870_COT_ACT;       // COT
//    client->Send_Buffer_TCP[9] = client->originatorAdr;
//    client->Send_Buffer_TCP[10] = client->ASDU;
//    client->Send_Buffer_TCP[11] = (U8)0x00;
//    // IOA
//    client->Send_Buffer_TCP[12] = (U8)0x00;
//    client->Send_Buffer_TCP[13] = (U8)0x00;
//    client->Send_Buffer_TCP[14] = (U8)0x00;
    
//    U8 totalLen = client->Send_Buffer_TCP[1] + 2;
//	OS_Send(client->Socket, client->Send_Buffer_TCP, totalLen, 0);
//    client->SendSequence += 2;  // Increment the sequence number for I-frames
    
//    // TX printout
//    if (client->DebugPrintRawFrames)
//    {
//        OS_com_printf("\n\n\rI104C TX: ");
//        int j;
//        for (j = 0; j < totalLen; j++)
//        {
//            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
//        }
//    }
//    if (client->DebugPrintInfo)
//    {
//        OS_com_printf("\n\r -> I104C TX: GEN INTERRO");
//    }
    
//	if (client->InfoEnabled)
//	{
//		client->Info->SentCounter += 1;
//	}
//}


STATUS IEC104Client_SendValues(IEC104Client client, const U32 *ioas, U32 count)
{
    if (count == 0)
        return -1;

    // Get the type for the first IOA.
    S32 type = IEC104Database_GetType(client->Database, ioas[0]);
    if (type < 0)
    {
#if defined I104C_DEBUG
        OS_com_printf("\n\rI104C IOA(%u) DB get type error: %d\n\r", ioas[0], type);
#endif
        return -1;
    }

    // Optionally, check that all IOAs in the list have the same type.
    U32 i;
    for (i = 1; i < count; i++) {
        S32 t = IEC104Database_GetType(client->Database, ioas[i]);
        if (t != type)
        {
#if defined I104C_DEBUG
            OS_com_printf("\n\rI104C IOA(%u) type mismatch: expected %d, got %d\n\r", ioas[i], type, t);
#endif
            return -1;
        }
    }

    // Start building the frame.
    client->Send_Buffer_TCP[0] = (U8)0x68;              // Start-of-frame

    // Control field: send and receive sequence numbers.
    client->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00FF);
    client->Send_Buffer_TCP[3] = (U8)(client->SendSequence >> 8);
    client->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00FF);
    client->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence >> 8);

    // ASDU header (bytes 6-11)
    client->Send_Buffer_TCP[6] = (U8)type;
    client->Send_Buffer_TCP[7] = (U8)count;             // Number of objects
    client->Send_Buffer_TCP[8] = eIEC870_COT_ACT;       // COT
    client->Send_Buffer_TCP[9] = client->originatorAdr;
    client->Send_Buffer_TCP[10] = client->ASDU;
    client->Send_Buffer_TCP[11] = (U8)0x00;

    // Determine the value format based on the variable type.
    int variableType = IEC104Database_GetVariableType(type);
    int objectDataLength = 0; // Number of bytes per object entry (IOA + value (+ QDS))
    switch(variableType)
    {
        case IEC104_BOOL:
        case IEC104_BYTE:
            // Each object: 3 bytes IOA + 1 byte value.
            objectDataLength = 3 + 1;
            break;
        case IEC104_INTEGER:
            // Each object: 3 bytes IOA + 2 bytes value + 1 byte QDS.
            objectDataLength = 3 + 2 + 1;
            break;
        case IEC104_FLOAT:
            // Each object: 3 bytes IOA + 4 bytes value + 1 byte QDS.
            objectDataLength = 3 + 4 + 1;
            break;
        default:
            return -1;
    }

    // The APDU length (in byte 1) is the sum of the fixed header (from index 2 to 11, i.e. 10 bytes)
    // plus the length of all object entries.
    int apduLength = 10 + (objectDataLength * count);
    client->Send_Buffer_TCP[1] = (U8)apduLength;

    // Starting index for the object entries.
    int index = 12;
    union {
        U8    byteV;
        S16   integerV;
        F32   floatV;
        U8    bytes[4];
    } value;

    // Loop over each IOA in the array.
    for (i = 0; i < count; i++)
    {
        U32 ioa = ioas[i];

        // Write the 3-byte IOA (LSB first).
        client->Send_Buffer_TCP[index++] = (U8)(ioa & 0xFF);
        client->Send_Buffer_TCP[index++] = (U8)((ioa >> 8) & 0xFF);
        client->Send_Buffer_TCP[index++] = (U8)((ioa >> 16) & 0xFF);

        // Retrieve the value from the database and append it according to the type.
        int dbResult;
        switch(variableType)
        {
            case IEC104_BOOL:
            case IEC104_BYTE:
                dbResult = IEC104Database_Get(client->Database, &value.byteV, sizeof(BOOL), type, ioa);
                if (dbResult < 0)
                {
#if defined I104C_DEBUG
                    OS_com_printf("\n\rI104C TX IOA(%u) DB read error: %d\n\r", ioa, dbResult);
#endif
                    return -1;
                }
                client->Send_Buffer_TCP[index++] = value.bytes[0];
                break;

            case IEC104_INTEGER:
                dbResult = IEC104Database_Get(client->Database, &value.integerV, sizeof(S16), type, ioa);
                if (dbResult < 0)
                {
#if defined I104C_DEBUG
                    OS_com_printf("\n\rI104C TX IOA(%u) DB read error: %d\n\r", ioa, dbResult);
#endif
                    return -1;
                }
                client->Send_Buffer_TCP[index++] = value.bytes[0];
                client->Send_Buffer_TCP[index++] = value.bytes[1];
                client->Send_Buffer_TCP[index++] = 0x00;  // QDS = Quality descriptor
                break;

            case IEC104_FLOAT:
                dbResult = IEC104Database_Get(client->Database, &value.floatV, sizeof(F32), type, ioa);
                if (dbResult < 0)
                {
#if defined I104C_DEBUG
                    OS_com_printf("\n\rI104C TX IOA(%u) DB read error: %d\n\r", ioa, dbResult);
#endif
                    return -1;
                }
                client->Send_Buffer_TCP[index++] = value.bytes[0];
                client->Send_Buffer_TCP[index++] = value.bytes[1];
                client->Send_Buffer_TCP[index++] = value.bytes[2];
                client->Send_Buffer_TCP[index++] = value.bytes[3];
                client->Send_Buffer_TCP[index++] = 0x00;  // QDS = Quality descriptor
                break;
        }
    }

    // Optionally, add a CP56Time2a time tag if the type is one that requires it.
    if (type >= C_SC_TA_1 && type <= C_BO_TA_1)
    {
        IEC104Database_Get_CP56Time2a((IEC104_CP56Time2A *)&(client->Send_Buffer_TCP[index]));
        index += 7;
        client->Send_Buffer_TCP[1] += 7;
    }
    else if (type < C_SC_NA_1 && type > C_BO_NA_1)
    {
        return -2; // Not a valid command type for sending values.
    }

    // Send the frame over TCP.
    int total_length = client->Send_Buffer_TCP[1] + 2; // APDU length + start(0x68) and length bytes.
    int sendResult = OS_Send(client->Socket, client->Send_Buffer_TCP, total_length, 0);
    if (sendResult < 0)
    {
        return -3; // Send failed.
    }
    client->SendSequence += 2;

    // Debug printout, if enabled.
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\n\rI104C TX: ");
        int j;
        for (j = 0; j < total_length; j++)
        {
            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
        }
    }

    if (client->InfoEnabled)
    {
        client->Info->SentCounter += 1;
    }

    return 0;
}


STATUS IEC104Client_ReadValues(IEC104Client client, const U32 *ioas, U32 count)
{
    int i;
    // Check if the IOA array is sequential
    U8 isSequential = 1;
    for (i = 1; i < count; i++)
    {
        if (ioas[i] != ioas[i - 1] + 1)
        {
            isSequential = 0;
            break;
        }
    }

    U8 apdu_length;
    if (isSequential)
    {
        // In sequential mode (SQ = 1), only one IOA is provided.
        apdu_length = 6 + 4 + 3;  // ASDU header (6 bytes) + control field (4 bytes) + one IOA (3 bytes)
    }
    else
    {
        // In non-sequential mode, each IOA requires 3 bytes.
        apdu_length = 6 + 4 + (3 * count);
    }

    // Build the frame header
    client->Send_Buffer_TCP[0] = (U8)0x68;              // Start-of-frame marker
    client->Send_Buffer_TCP[1] = apdu_length;           // APDU length
    client->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00FF);
    client->Send_Buffer_TCP[3] = (U8)(client->SendSequence >> 8);
    client->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00FF);
    client->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence >> 8);
    
    client->Send_Buffer_TCP[8] = eIEC870_COT_REQ;           // Cause of transmission
    client->Send_Buffer_TCP[9] = client->originatorAdr;     // Originator address
    client->Send_Buffer_TCP[10] = client->ASDU;             // ASDU address
    client->Send_Buffer_TCP[11] = (U8)0x00;                 // Reserved/Additional address field
    
    // Build the APDU header (bytes 6 to 11)
    client->Send_Buffer_TCP[6] = C_RD_NA_1;                 // Command type (read request)
    if (isSequential)
    {
        // Set the VSQ byte with SQ = 1 (bit7) and lower 7 bits = count
        client->Send_Buffer_TCP[7] = (U8)(0x80 | (count & 0x7F));
        
        // Add the first IOA
        U32 ioa = ioas[0];
        client->Send_Buffer_TCP[12]     = (U8)(ioa & 0x000000FF);
        client->Send_Buffer_TCP[12 + 1] = (U8)((ioa & 0x0000FF00) >> 8);
        client->Send_Buffer_TCP[12 + 2] = (U8)((ioa & 0x00FF0000) >> 16);
    }
    else
    {
        // No sequential addressing, just the count.
        client->Send_Buffer_TCP[7] = (U8)(count & 0x7F);
        
        // Add IOAs
        for (i = 0; i < count; i++)
        {
            U32 ioa = ioas[i];
            client->Send_Buffer_TCP[12 + i * 3]     = (U8)(ioa & 0x000000FF);
            client->Send_Buffer_TCP[12 + i * 3 + 1] = (U8)((ioa & 0x0000FF00) >> 8);
            client->Send_Buffer_TCP[12 + i * 3 + 2] = (U8)((ioa & 0x00FF0000) >> 16);
        }
    }
    
    // Total frame length is APDU length plus the 2 header bytes (0x68 and length)
    int total_length = apdu_length + 2;

    int result = OS_Send(client->Socket, client->Send_Buffer_TCP, total_length, 0);
    if (result < 0)
    {
        return -1;
    }
    client->SendSequence += 2;  // Increment the sequence number by 2 for I-frames

    // Optional TX printout for debugging
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\n\rI104C TX: ");
        int j;
        for (j = 0; j < total_length; j++)
        {
            OS_com_printf("%02X ", client->Send_Buffer_TCP[j]);
        }
    }
    if (client->DebugPrintInfo)
    {
        OS_com_printf("\n\r -> I104C TX: READ_REQ(%u)", count);
        int j;
        for (j = 0; j < count; j++)
        {
            OS_com_printf("\n\r   - %u", ioas[j]);
        }
    }

    if (client->InfoEnabled)
    {
        client->Info->SentCounter += 1;
    }

    return 0;
}


STATUS IEC104Client_StartDT(IEC104Client client)
{
	client->StartDT = true;
	
	return 0;
}

STATUS IEC104Client_StopDT(IEC104Client client)
{
	client->StartDT = false;
	
	return 0;
}

void IEC104Client_EnableDebugPrintRawFrames(IEC104Client client)
{
    client->DebugPrintRawFrames = true;
    return;
}

void IEC104Client_DisableDebugPrintRawFrames(IEC104Client client)
{
    client->DebugPrintRawFrames = false;
    return;
}

void IEC104Client_EnableDebugPrintInfo(IEC104Client client)
{
    client->DebugPrintInfo = true;
    return;
}

void IEC104Client_DisableDebugPrintInfo(IEC104Client client)
{
    client->DebugPrintInfo = false;
    return;
}

//returns 0 on success, -1 on error
static S32 Process_Send(IEC104Client client)
{
	// Keepalive
	client->KeepAliveTimer += client->Task_Scantime;
	if (client->KeepAliveTimer >= client->KeepAlivePeriod)
	{
		client->KeepAliveTimer = 0;
		if (!client->TestFRReceived) {
			return -1;
		}
		client->TestFRReceived = false;
		Send_TestFR(client);
		return 0;
	}
	// StartDT
	if (client->StartDT && !client->StartDTReceived) {
		Send_StartDT(client);
		return 0;
	}
	// StopDT
	if (!client->StartDT && !client->StopDTReceived) {
		Send_StopDT(client);
		return 0;
	}
    
    // acknowledgement
    client->AcknowledgeTimer += client->Task_Scantime;
    if (/*client->AcknowledgeTimer >= client->AcknowledgeTimeout || */client->UnacknowledgeCounter >= client->UnacknowledgeReceive)
    {
        client->AcknowledgeTimer = 0;
        client->UnacknowledgeCounter = 0;
        Send_SFrame(client);
    }

	return 0;

}

// returns length of timetag or 0 in case type does not need timetag
static U8 GetTimeTagLength(U8 type) {

	switch (type) //add time tag 
	{
		//Add short timetag
	case M_SP_TA_1:
	case M_DP_TA_1:
	case M_ST_TA_1:
	case M_BO_TA_1:
	case M_ME_TA_1:
	case M_ME_TB_1:
	case M_ME_TC_1:
	case M_IT_TA_1:
	case M_EP_TA_1:
	case M_EP_TB_1:
	case M_EP_TC_1:
		return 3; // length of CP26 timetag
		//Add long timetag
	case M_SP_TB_1:
	case M_DP_TB_1:
	case M_ST_TB_1:
	case M_BO_TB_1:
	case M_ME_TD_1:
	case M_ME_TE_1:
	case M_ME_TF_1:
	case M_IT_TB_1:
	case M_EP_TD_1:
	case M_EP_TE_1:
	case M_EP_TF_1:
		return 7; // length of CP26 timetag	
	default:
		return 0;
	}
}


static S32 Process_IOA(IEC104Client client, int Length)
{
    U8 i;
    int bytecount;
    U8 ASDUType;
    U8 dataCount;
    U8 SQ;         // SQ bit: 0 = individual IOAs, 1 = sequential addressing
    U32 ioa, first_ioa = 0;
    
    union {
        U8 byteV;
        S16 integerV;
        F32 floatV;
        unsigned char bytes[4];
    } value;
    
    if (Length < 11) { return -1; }
    bytecount = client->Recv_Buffer_TCP[1] + 2;
    ASDUType = client->Recv_Buffer_TCP[6];
    // VSQ: Bit 7 is SQ; lower 7 bits give the number of objects.
    SQ = (client->Recv_Buffer_TCP[7] & 0x80) >> 7;
    dataCount = client->Recv_Buffer_TCP[7] & 0x7F;
    
    int bufferPosition = 12;
    int lengthOfSingleData;
    int result = IEC104Database_GetVariableType(ASDUType);
    
    switch (result)
    {
    case IEC104_BOOL:
    case IEC104_BYTE:
    {
        // For BOOL/Byte, each block normally has 3 bytes IOA + 1 byte value, plus any time tag.
        lengthOfSingleData = 4 + GetTimeTagLength(ASDUType);
        if (SQ == 0) {
            // Each object has its own IOA field.
            for (i = 0; i < dataCount; i++)
            {
                if (Length < bufferPosition + lengthOfSingleData) { return -1; }
                ioa = ((U8)client->Recv_Buffer_TCP[bufferPosition + 2] << 16) +
                      ((U8)client->Recv_Buffer_TCP[bufferPosition + 1] << 8) +
                      (U8)client->Recv_Buffer_TCP[bufferPosition];
                value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition + 3];
                value.bytes[1] = 0;
                value.bytes[2] = 0;
                value.bytes[3] = 0;
                result = IEC104Database_Set(client->Database, &value.byteV, sizeof(value.byteV), ASDUType, ioa);
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX IOA: %u | value: %02X | type: %u", ioa, value.byteV, ASDUType);
                }
#if defined I104C_DEBUG
                if (result < 0)
                {
                    OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                }
#endif
                bufferPosition += lengthOfSingleData;
            }
        } else {
            // SQ==1: Only the first object has an explicit IOA.
            if (dataCount > 0) {
                if (Length < bufferPosition + lengthOfSingleData) { return -1; }
                ioa = ((U8)client->Recv_Buffer_TCP[bufferPosition + 2] << 16) +
                      ((U8)client->Recv_Buffer_TCP[bufferPosition + 1] << 8) +
                      (U8)client->Recv_Buffer_TCP[bufferPosition];
                first_ioa = ioa;
                value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition + 3];
                value.bytes[1] = 0;
                value.bytes[2] = 0;
                value.bytes[3] = 0;
                result = IEC104Database_Set(client->Database, &value.byteV, sizeof(value.byteV), ASDUType, ioa);
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX IOA: %u | value: %02X | type: %u", ioa, value.byteV, ASDUType);
                }
#if defined I104C_DEBUG
                if (result < 0)
                {
                    OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                }
#endif
                bufferPosition += lengthOfSingleData;
                // For subsequent objects, the IOA is not included in the message.
                int subsequentBlockLength = lengthOfSingleData - 3;
                for (i = 1; i < dataCount; i++)
                {
                    if (Length < bufferPosition + subsequentBlockLength) { return -1; }
                    ioa = first_ioa + i;
                    // For BOOL/Byte, only 1 data byte is present.
                    value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition];
                    value.bytes[1] = 0;
                    value.bytes[2] = 0;
                    value.bytes[3] = 0;
                    result = IEC104Database_Set(client->Database, &value.byteV, sizeof(value.byteV), ASDUType, ioa);
                    if (client->DebugPrintInfo)
                    {
                        OS_com_printf("\n\r -> I104C RX IOA: %u | value: %02X | type: %u", ioa, value.byteV, ASDUType);
                    }
#if defined I104C_DEBUG
                    if (result < 0)
                    {
                        OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                    }
#endif
                    bufferPosition += subsequentBlockLength;
                }
            }
        }
        break;
    }
    case IEC104_INTEGER:
    {
        // For INTEGER, each block normally has 3 bytes IOA + 2 value bytes + 1 QDS, plus time tag.
        lengthOfSingleData = 6 + GetTimeTagLength(ASDUType);
        if (SQ == 0) {
            for (i = 0; i < dataCount; i++)
            {
                if (Length < bufferPosition + lengthOfSingleData) { return -1; }
                ioa = ((U8)client->Recv_Buffer_TCP[bufferPosition + 2] << 16) +
                      ((U8)client->Recv_Buffer_TCP[bufferPosition + 1] << 8) +
                      (U8)client->Recv_Buffer_TCP[bufferPosition];
                value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition + 3];
                value.bytes[1] = client->Recv_Buffer_TCP[bufferPosition + 4];
                value.bytes[2] = 0;
                value.bytes[3] = 0;
                result = IEC104Database_Set(client->Database, &value.integerV, sizeof(value.integerV), ASDUType, ioa);
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX IOA: %u | value: %d | type: %u", ioa, value.integerV, ASDUType);
                }
#if defined I104C_DEBUG
                if (result < 0)
                {
                    OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                }
#endif
                bufferPosition += lengthOfSingleData;
            }
        } else {
            if (dataCount > 0) {
                if (Length < bufferPosition + lengthOfSingleData) { return -1; }
                ioa = ((U8)client->Recv_Buffer_TCP[bufferPosition + 2] << 16) +
                      ((U8)client->Recv_Buffer_TCP[bufferPosition + 1] << 8) +
                      (U8)client->Recv_Buffer_TCP[bufferPosition];
                first_ioa = ioa;
                value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition + 3];
                value.bytes[1] = client->Recv_Buffer_TCP[bufferPosition + 4];
                value.bytes[2] = 0;
                value.bytes[3] = 0;
                result = IEC104Database_Set(client->Database, &value.integerV, sizeof(value.integerV), ASDUType, ioa);
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX IOA: %u | value: %d | type: %u", ioa, value.integerV, ASDUType);
                }
#if defined I104C_DEBUG
                if (result < 0)
                {
                    OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                }
#endif
                bufferPosition += lengthOfSingleData;
                int subsequentBlockLength = lengthOfSingleData - 3;
                for (i = 1; i < dataCount; i++)
                {
                    if (Length < bufferPosition + subsequentBlockLength) { return -1; }
                    ioa = first_ioa + i;
                    value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition];
                    value.bytes[1] = client->Recv_Buffer_TCP[bufferPosition + 1];
                    value.bytes[2] = 0;
                    value.bytes[3] = 0;
                    result = IEC104Database_Set(client->Database, &value.integerV, sizeof(value.integerV), ASDUType, ioa);
                    if (client->DebugPrintInfo)
                    {
                        OS_com_printf("\n\r -> I104C RX IOA: %u | value: %d | type: %u", ioa, value.integerV, ASDUType);
                    }
#if defined I104C_DEBUG
                    if (result < 0)
                    {
                        OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                    }
#endif
                    bufferPosition += subsequentBlockLength;
                }
            }
        }
        break;
    }
    case IEC104_FLOAT:
    {
        // For FLOAT, each block normally has 3 bytes IOA + 4 value bytes + 1 QDS, plus time tag.
        lengthOfSingleData = 8 + GetTimeTagLength(ASDUType);
        if (SQ == 0) {
            for (i = 0; i < dataCount; i++)
            {
                if (Length < bufferPosition + lengthOfSingleData) { return -1; }
                ioa = ((U8)client->Recv_Buffer_TCP[bufferPosition + 2] << 16) +
                      ((U8)client->Recv_Buffer_TCP[bufferPosition + 1] << 8) +
                      (U8)client->Recv_Buffer_TCP[bufferPosition];
                value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition + 3];
                value.bytes[1] = client->Recv_Buffer_TCP[bufferPosition + 4];
                value.bytes[2] = client->Recv_Buffer_TCP[bufferPosition + 5];
                value.bytes[3] = client->Recv_Buffer_TCP[bufferPosition + 6];
                result = IEC104Database_Set(client->Database, &value.floatV, sizeof(value.floatV), ASDUType, ioa);
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX IOA: %u | value: %f | type: %u", ioa, value.floatV, ASDUType);
                }
#if defined I104C_DEBUG
                if (result < 0)
                {
                    OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                }
#endif
                bufferPosition += lengthOfSingleData;
            }
        } else {
            if (dataCount > 0) {
                if (Length < bufferPosition + lengthOfSingleData) { return -1; }
                ioa = ((U8)client->Recv_Buffer_TCP[bufferPosition + 2] << 16) +
                      ((U8)client->Recv_Buffer_TCP[bufferPosition + 1] << 8) +
                      (U8)client->Recv_Buffer_TCP[bufferPosition];
                first_ioa = ioa;
                value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition + 3];
                value.bytes[1] = client->Recv_Buffer_TCP[bufferPosition + 4];
                value.bytes[2] = client->Recv_Buffer_TCP[bufferPosition + 5];
                value.bytes[3] = client->Recv_Buffer_TCP[bufferPosition + 6];
                result = IEC104Database_Set(client->Database, &value.floatV, sizeof(value.floatV), ASDUType, ioa);
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX IOA: %u | value: %f | type: %u", ioa, value.floatV, ASDUType);
                }
#if defined I104C_DEBUG
                if (result < 0)
                {
                    OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                }
#endif
                bufferPosition += lengthOfSingleData;
                int subsequentBlockLength = lengthOfSingleData - 3;
                for (i = 1; i < dataCount; i++)
                {
                    if (Length < bufferPosition + subsequentBlockLength) { return -1; }
                    ioa = first_ioa + i;
                    value.bytes[0] = client->Recv_Buffer_TCP[bufferPosition];
                    value.bytes[1] = client->Recv_Buffer_TCP[bufferPosition + 1];
                    value.bytes[2] = client->Recv_Buffer_TCP[bufferPosition + 2];
                    value.bytes[3] = client->Recv_Buffer_TCP[bufferPosition + 3];
                    result = IEC104Database_Set(client->Database, &value.floatV, sizeof(value.floatV), ASDUType, ioa);
                    if (client->DebugPrintInfo)
                    {
                        OS_com_printf("\n\r -> I104C RX IOA: %u | value: %f | type: %u", ioa, value.floatV, ASDUType);
                    }
#if defined I104C_DEBUG
                    if (result < 0)
                    {
                        OS_com_printf("\n\rI104C IOA(%u) DB write error: %d\n\r", ioa, result);
                    }
#endif
                    bufferPosition += subsequentBlockLength;
                }
            }
        }
        break;
    }
    default:
        return -1;
    }
    
    return 0;
}



static S32 Process_Receive(IEC104Client client)
{
	int received = 0;
    
	// receive 2 bytes to get packet length, in case multiple packets together
    received = OS_Recv(client->Socket, client->Recv_Buffer_TCP, 2, 0);
    if (received <= 0)
    {
        if (received == OS_NOT_CONNECTED)
        {
#if defined I104C_DEBUG
            OS_com_printf("\n\rI104C OS_Recv() error: %d\n\r", received);
#endif
            if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Connection lost"); }
            return received;
        }
        else if (received < 0 && received != OS_WOULD_BLOCK)
        {
#if defined I104C_DEBUG
            OS_com_printf("\n\rI104C OS_Recv() error: %d\n\r", received);
#endif
            if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Receive error"); }
            return received;
        }
        return 0;
    }
    
    // RX printout
    if (client->DebugPrintRawFrames)
    {
        OS_com_printf("\n\rI104C RX: %02X %02X ", client->Recv_Buffer_TCP[0], client->Recv_Buffer_TCP[1]);
    }

    if (received != 2 || client->Recv_Buffer_TCP[0] != 0x68)		// FAULT invalid frame
    {
#if defined I104C_DEBUG
        OS_com_printf("\n\rI104C invalid frame, received: %d\n\r", received);
#endif
        // empty receive buffer
        OS_Recv(client->Socket, client->Recv_Buffer_TCP, I104C_RECV_BUFFER_TCP_SIZE, 0);
        return 0;
    }
    
    U8 apduLen = client->Recv_Buffer_TCP[1];
    if (apduLen > I104C_RECV_BUFFER_TCP_SIZE - 2)
    {
#if defined I104C_DEBUG
        OS_com_printf("\n\rI104C frame too big: %d\n\r", apduLen);
#endif
        return 0;
    }

    received = OS_Recv(client->Socket, &client->Recv_Buffer_TCP[2], apduLen, 0);
    if (received > 0)
    {
        // RX printout
        if (client->DebugPrintRawFrames)
        {
            int j;
            for (j = 0; j < received; j++)
            {
                OS_com_printf("%02X ", client->Recv_Buffer_TCP[j+2]);
            }
        }
        
        received += 2;
        if (client->InfoEnabled)
        {
            client->Info->ReceivedCounter += 1;
        }
        
        // extract cause of transmission, confirmation and test flag
        U8 cot = client->Recv_Buffer_TCP[8] & 0x3F;                     // COT (bits 0..5)
        U8 confirmFlag = (client->Recv_Buffer_TCP[8] & 0x40) >> 6;      // confirmation flag (bit 6)
        U8 testFlag = (client->Recv_Buffer_TCP[8] & 0x80) >> 7;         // test flag (bit 7)

        if (apduLen == 4)       // fixed length frame (4 bytes)
        {
            switch ((U8)(client->Recv_Buffer_TCP[2]))
            {
            case 0x0B: // if STARTDT
                client->StartDTReceived = true;
                client->StopDTReceived = false;
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX: START DT\n\r");
                }
                break;
            case 0x31:	// if STOPDT
                client->StopDTReceived = true;
                client->StartDTReceived = false;
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX: STOP DT\n\r");
                }
                break;
            case 0x83:  // if TESTFR request
                client->TestFRReceived = true;
                if (client->DebugPrintInfo)
                {
                    OS_com_printf("\n\r -> I104C RX: TEST FR\n\r");
                }
                break;
            default:
                break;
            }
        }
        else if (apduLen > 12)   // dynamic length frame
        {
            client->ReceiveSequence += 2;
            client->UnacknowledgeCounter += 1;
            
            if (client->Recv_Buffer_TCP[10] == client->ASDU)
            {
                U8 ASDUType = client->Recv_Buffer_TCP[6];
                switch (ASDUType)
                {
                    case C_IC_NA_1: // general interrogation
                    {
                        // Optional TX printout for debugging
                        if (client->DebugPrintInfo)
                        {
                            OS_com_printf("\n\r -> I104C RX: GEN INTERRO (COT: %u, CON: %u, TEST: %u)\n\r", cot, confirmFlag, testFlag);
                        }
                        break;
                    }
                    default:
                    {
                        client->TestFRReceived = true;
                        switch (cot)
                        {
                            case eIEC870_COT_CYCLIC:
                            case eIEC870_COT_SPONTAN:
                                if (client->StartDT)     // check if start transmission is set to allow transmission
                                {
                                    Process_IOA(client, received);
                                }
                                break;
                            case eIEC870_COT_INROGEN:
                                Process_IOA(client, received);
                            default:
                                break;
                        }
                        break;
                    }
                }
                
                return 0;
            }
        }
        else
        {
#if defined I104C_DEBUG
            OS_com_printf("\n\rI104C RX invalid APDU len(%u)\n\r", apduLen);
#endif
            return 0;
        }
    }
    else if (received == OS_NOT_CONNECTED)
    {
#if defined I104C_DEBUG
        OS_com_printf("\n\rI104C OS_Recv() error: %d\n\r", received);
#endif
        if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Connection lost"); }
        return received;
    }
    else if (received < 0 && received != OS_WOULD_BLOCK)
    {
#if defined I104C_DEBUG
        OS_com_printf("\n\rI104C OS_Recv() error: %d\n\r", received);
#endif
        if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Receive error"); }
        return received;
    }
    else
    {
        return 0;
    }

	return 0;
}

//***********************************************************************
// STATE : Communication interface is disabled, waiting for enable command
//***********************************************************************
static void Disabled_State(BOOL firstentry, IEC104Client client)
{
	//-----------------------------------------------------------------------
	// ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (client->InfoEnabled) {
			strcpy(client->Info->StatusTxt, "Disabled");
            if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Interface disabled"); }
		}
		Disconnect(client);
	}

	//-----------------------------------------------------------------------
	// EXIT CONDITIONS
	//-----------------------------------------------------------------------

	if (client->IEC104ClientEnabled) // enabling
	{
		client->StateFunctionPointer = Connecting_State;
	}
}

//***********************************************************************
// STATE : Reconnect delay state
//***********************************************************************
static void WaitingForReconnect_State(BOOL firstentry, IEC104Client client)
{
	//-----------------------------------------------------------------------
	// ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Wait for reconnect..."); }
		client->IEC104ClientEnabled_prev = client->IEC104ClientEnabled;
		client->ReconnectTimeoutTimer = 0;
	}
	if (client->InfoEnabled) { 
		int timeLeft =  client->ReconnectTimeout- client->ReconnectTimeoutTimer;
		if (timeLeft < 0) { timeLeft = 0; }
		snprintf(client->Info->StatusTxt, sizeof(client->Info->StatusTxt), "Reconnecting in: %d ms", timeLeft);
	}
	//-----------------------------------------------------------------------
	// EXIT CONDITIONS
	//-----------------------------------------------------------------------
	if (!(client->IEC104ClientEnabled)) // disabling
	{
		client->StateFunctionPointer = Disabled_State;
	}

	client->ReconnectTimeoutTimer += client->Task_Scantime;
	if (client->ReconnectTimeoutTimer >= client->ReconnectTimeout)
	{
		client->StateFunctionPointer = Connecting_State;
	}

	return;
}

//***********************************************************************
// STATE : Connecting State
//***********************************************************************
static void Connecting_State(BOOL firstentry, IEC104Client client)
{
	//-----------------------------------------------------------------------
	// ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (client->InfoEnabled) {
			strcpy(client->Info->StatusTxt, "Connecting...");
            if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Connecting"); }
		}
	}

	if (client->InfoEnabled) {
		snprintf(client->Info->StatusTxt, sizeof(client->Info->StatusTxt), "Connecting: %d ms", client->ConnectTimeoutTimer);
	}

	//-----------------------------------------------------------------------
	// EXIT CONDITIONS
	//-----------------------------------------------------------------------
    if (!(client->IEC104ClientEnabled)) // disabling
    {
        client->StateFunctionPointer = Disabled_State;
        return;
    }

    int result = Connect(client);
    if(result < 0)
    {
        OS_module_task_destruct(&(client->TCPConnectingTask));
        Disconnect(client);
        client->StateFunctionPointer = WaitingForReconnect_State;
    }
    else if (client->Connected)
    {
        OS_module_task_destruct(&(client->TCPConnectingTask));
        
        client->TestFRReceived = true;
        client->StartDTReceived = false;
        client->StopDTReceived = true;
        client->StateFunctionPointer = Operational_State;
        client->Connecting = false;
    }
    return;

}

//***********************************************************************
// STATE : Interface is operational
//***********************************************************************
static void Operational_State(BOOL firstentry, IEC104Client client)
{

	//-----------------------------------------------------------------------
	// ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (client->InfoEnabled) {
			strcpy(client->Info->StatusTxt, "Interface operational");

			if (client->Info->InterfaceEventLog) { CustomLog_MakeEntry(client->Info->InterfaceEventLog, "Interface operational"); }
		}
	}

	//-----------------------------------------------------------------------
	//CONTROL
	//-----------------------------------------------------------------------
    int result = Process_Receive(client);
    if (result < 0) {
        Disconnect(client);
        client->StateFunctionPointer = WaitingForReconnect_State;
        return;
    }

    result = Process_Send(client);
    if (result < 0) {
        Disconnect(client);
        client->StateFunctionPointer = WaitingForReconnect_State;
        return;
    }

	//-----------------------------------------------------------------------
	// EXIT CONDITIONS
	//-----------------------------------------------------------------------
		
	if (!(client->IEC104ClientEnabled)) // disabling
	{
		Disconnect(client);
		client->StateFunctionPointer = Disabled_State;
	}
}

S32 IEC104Client_Control(IEC104Client client) {

	STATUS LocalStatus = 0;
	if (client == NULL) {
		return -1;
	}
    
	//***********************************************************************
   // Function call to operating state functions - uses pointer to function
   // "StateFunctionPointer" points to the mode function that should be called
   //***********************************************************************

	if (client->StateFunctionPointer != client->StateFunctionPointer_Prev)
	{
		client->StateFunctionPointer_Prev = client->StateFunctionPointer;
		(*(client->StateFunctionPointer))(true, client);
	}
	else
	{
		(*(client->StateFunctionPointer))(false, client);
	}

	return LocalStatus;
}
