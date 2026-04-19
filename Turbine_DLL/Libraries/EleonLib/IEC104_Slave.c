//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <IEC104_Slave.h>
#include <List.h>


#define         M_EI_NA_1 ((U8)70)        // End of Initialisation (70)
#define         C_IC_NA_1 ((U8)100)       // Interrogation command (100)
#define         C_CI_NA_1 ((U8)101)       // Counter interrogation command (101)
#define         C_RD_NA_1 ((U8)102)       // Read Command (102)
#define         C_CS_NA_1 ((U8)103)       // Clock synchronisation command (103)
#define         C_TS_NA_1 ((U8)104)       // Test command (104)
#define         C_RP_NA_1 ((U8)105)       // Reset process command (105)
#define         C_CD_NA_1 ((U8)106)       // C_CD_NA_1 Delay acquisition command (106)
#define         C_TS_TA_1 ((U8)107)       // Test command with time tag CP56Time2a (107)
#define         P_ME_NA_1 ((U8)110)       // Parameter of measured values) normalized value (110)
#define         P_ME_NB_1 ((U8)111)       // Parameter of measured values) scaled value (111)
#define         P_ME_NC_1 ((U8)112)       // Parameter of measured values) short floating point number (112)
#define         P_AC_NA_1 ((U8)113)       // Parameter activation (113)
#define         F_FR_NA_1 ((U8)120)       // File ready (120)
#define         F_SR_NA_1 ((U8)121)       // Section ready (121)
#define         F_SC_NA_1 ((U8)122)       // Call directory) select file) call file) call section (122)
#define         F_LS_NA_1 ((U8)123)       // Last section) last segment (123)
#define         F_FA_NA_1 ((U8)124)       // ACK file) ACK section (124)
#define         F_SG_NA_1 ((U8)125)       // Segment (125)
#define         F_DR_TA_1 ((U8)126)       // Directory (126)
//#define         //F_SC_NB_1 ((U8)127       // Query log - request archive file (127)

#define        eIEC870_COT_UNUSED ((U8)0)       // Not used (0)
#define        eIEC870_COT_CYCLIC ((U8)1)       // Cyclic data (1)
#define        eIEC870_COT_BACKGROUND ((U8)2)       // Background request (2)
#define        eIEC870_COT_SPONTAN ((U8)3)       // Spontaneous data (3)
#define        eIEC870_COT_INIT ((U8)4)       // End of initialisation (4)
#define        eIEC870_COT_REQ ((U8)5)       // Read-Request (5)
#define        eIEC870_COT_ACT ((U8)6)       // Command activation (6)
#define        eIEC870_COT_ACT_CON ((U8)7)       // Acknowledgement of command activation (7)
#define        eIEC870_COT_DEACT ((U8)8)       // Command abort (8)
#define        eIEC870_COT_DEACT_CON ((U8)9)       // Acknowledgement of command activation (9)
#define        eIEC870_COT_ACT_TERM ((U8)10)       // Termination of command activation (10)
#define        eIEC870_COT_RETREM ((U8)11)       // Return because of remote command (11)
#define        eIEC870_COT_RETLOC ((U8)12)       // Return because of local command (12)
#define        eIEC870_COT_FILE ((U8)13)       // File access (13)
#define        eIEC870_COT_14 ((U8)14)       // Reserved/not used (14)
#define        eIEC870_COT_15 ((U8)15)       // Reserved/not used (15)
#define        eIEC870_COT_16 ((U8)16)       // Reserved/not used (16)
#define        eIEC870_COT_17 ((U8)17)       // Reserved/not used (17)
#define        eIEC870_COT_18 ((U8)18)       // Reserved/not used (18)
#define        eIEC870_COT_19 ((U8)19)       // Reserved/not used (19)
#define        eIEC870_COT_INROGEN ((U8)20)       // Station interrogation (general) (20)
#define        eIEC870_COT_INRO1 ((U8)21)       // Station interrogation of group 1 (21)
#define        eIEC870_COT_INRO2 ((U8)22)       // Station interrogation of group 2 (22)
#define        eIEC870_COT_INRO3 ((U8)23)       // Station interrogation of group 3 (23)
#define        eIEC870_COT_INRO4 ((U8)24)       // Station interrogation of group 4 (24)
#define        eIEC870_COT_INRO5 ((U8)25)       // Station interrogation of group 5 (25)
#define        eIEC870_COT_INRO6 ((U8)26)       // Station interrogation of group 6 (26)
#define        eIEC870_COT_INRO7 ((U8)27)       // Station interrogation of group 7 (27)
#define        eIEC870_COT_INRO8 ((U8)28)       // Station interrogation of group 8 (28)
#define        eIEC870_COT_INRO9 ((U8)29)       // Station interrogation of group 9 (29)
#define        eIEC870_COT_INRO10 ((U8)30)       // Station interrogation of group 10 (30)
#define        eIEC870_COT_INRO11 ((U8)31)       // Station interrogation of group 11 (31)
#define        eIEC870_COT_INRO12 ((U8)32)       // Station interrogation of group 12 (32)
#define        eIEC870_COT_INRO13 ((U8)33)       // Station interrogation of group 13 (33)
#define        eIEC870_COT_INRO14 ((U8)34)       // Station interrogation of group 14 (34)
#define        eIEC870_COT_INRO15 ((U8)35)       // Station interrogation of group 15 (35)
#define        eIEC870_COT_INRO16 ((U8)36)       // Station interrogation of group 16 (36)
#define        eIEC870_COT_REQCOGEN ((U8)37)       // Counter request (general) (37)
#define        eIEC870_COT_REQCO1 ((U8)38)       // Counter request of group 1 (38)
#define        eIEC870_COT_REQCO2 ((U8)39)       // Counter request of group 2 (39)
#define        eIEC870_COT_REQCO3 ((U8)40)       // Counter request of group 3 (40)
#define        eIEC870_COT_REQCO4 ((U8)41)       // Counter request of group 4 (41)
#define        eIEC870_COT_42 ((U8)42)       // Reserved/not used (42)
#define        eIEC870_COT_43 ((U8)43)       // Reserved/not used (43)
#define        eIEC870_COT_UNKNOWN_TYPE ((U8)44)       // Unknown type (44)
#define        eIEC870_COT_UNKNOWN_CAUSE ((U8)45)       // Unknown transmission cause (45)
#define        eIEC870_COT_UNKNOWN_ASDU_ADDRESS ((U8)46)       // Unknown collective ASDU (46)
#define        eIEC870_COT_UNKNOWN_OBJECT_ADDRESS ((U8)47)       // Unknown object address (47)
#define        eIEC870_COT_48 ((U8)48)       // Reserved/not used (48)
#define        eIEC870_COT_49 ((U8)49)       // Reserved/not used (49)
#define        eIEC870_COT_50 ((U8)50)       // Reserved/not used (50)
#define        eIEC870_COT_51 ((U8)51)       // Reserved/not used (51)
#define        eIEC870_COT_52 ((U8)52)       // Reserved/not used (52)
#define        eIEC870_COT_53 ((U8)53)       // Reserved/not used (53)
#define        eIEC870_COT_54 ((U8)54)       // Reserved/not used (54)
#define        eIEC870_COT_55 ((U8)55)       // Reserved/not used (55)
#define        eIEC870_COT_56 ((U8)56)       // Reserved/not used (56)
#define        eIEC870_COT_57 ((U8)57)       // Reserved/not used (57)
#define        eIEC870_COT_58 ((U8)58)       // Reserved/not used (58)
#define        eIEC870_COT_59 ((U8)59)       // Reserved/not used (59)
#define        eIEC870_COT_60 ((U8)60)       // Reserved/not used (60)
#define        eIEC870_COT_61 ((U8)61)       // Reserved/not used (61)
#define        eIEC870_COT_62 ((U8)62)       // Reserved/not used (62)
#define        eIEC870_COT_63 ((U8)63)       // Reserved/not used (63)



#define I104S_DEBUG
#define I104S_TYPE_CHECK      // this enables the validation of object structure by checking the "Type" value

#define I104S_TYPE 138
#define I104S_RECV_BUFFER_TCP_SIZE 1024
#define I104S_SEND_BUFFER_TCP_SIZE 1024
#define I104S_CLIENTSLISTCAPACITY 10
#define I104S_INTERROGATIONCAPACITY 13


// function declarations
static void Disabled_State(BOOL, IEC104Slave);
static void InterfaceError_State(BOOL, IEC104Slave);
static void Startup_State(BOOL, IEC104Slave);
static void Operational_State(BOOL, IEC104Slave);


// structure definitions

typedef struct
{
	U64 privateKey;
	struct addr_struct ClientAddressTCP;
	U16 TCP_Socket;            // TCP socket is used for protocol commands, control and data transmission

	U32 KeepAlive_Timer;       // watchdog timer for closing session when no activity
	U16 ReceivedCounter;
	U16 SentCounter;
	U8 StartDT;                // checks if STARTDT command received and allowed to transmit
	U16 SendSequence;          // counts sent frames; bit 0 is always zero - basically needs to be incremented by 2
	U16 ReceiveSequence;       // counts received frames; bit 0 is always zero - basically needs to be incremented by 2

	U32 AutoTimer;             // timer [ms] for triggering periodic packets
	U32 onUpdateAutoTimer;     // timer [ms] for triggering updated packets
	BOOL UpdatedDataSent;
	IEC104Slave Slave;
} Client;

struct IEC104_Slave
{
	U8 Type;            // This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	char IEC104_Slave_varName[31];      // during initialization, a variable of type U32 with given name is created in varDB with a value of created IEC104_Slave address/pointer.
										// this variable can be used by other programs(ie "IEC104_Slave_Interface") to get the address of this IEC104_Slave
	IEC104Slave_StatusInfo Status;
	BOOL StatusInfoEnabled;
	IEC104Database Database;

	U32 Task_Scantime;
	// parameters
	U16 LocalPortTCP;
	U8 MaxNumOfClients;

	U8 ASDU;                            // default ASDU address used for all channels here is 3
	U8 originatorAdr;                   // originator address
	int LocalIP;
	struct addr_struct LocalAddressTCP;
	U16 ListenTCP_Socket;					// socket for listening client connection requests
	char Recv_Buffer_TCP[I104S_RECV_BUFFER_TCP_SIZE];
	char Send_Buffer_TCP[I104S_SEND_BUFFER_TCP_SIZE];
	U8 NumOfClients;
	U8 Interrogation0GroupTypes[I104S_INTERROGATIONCAPACITY];
	U32 periodicPeriod;
	BOOL periodicEnabled;
	U32 onUpdatePeriodicPeriod;
	BOOL onUpdatePeriodicEnabled;
	BOOL updateDatabaseValues;

	BOOL IEC104SlaveEnabled;
	BOOL IEC104SlaveEnabled_prev;

	List myClients;

	void(*StateFunctionPointer)(BOOL, IEC104Slave);
	void(*StateFunctionPointer_Prev)(BOOL, IEC104Slave);
};


#ifdef I104S_TYPE_CHECK
// Validate object reference; Returns FALSE if invalid object reference
static BOOL IEC104Slave_ValidateObject(IEC104Slave slave)
{
	if (slave->Type == I104S_TYPE) { return true; }
	else { return false; }
}
#endif


// updates all clients IP addresses in menu lines
static void UpdateAllClientsIPTxt(IEC104Slave slave)
{
	if (!slave->StatusInfoEnabled) { return; }

	Client* client;

	int i;
	for (i = 0; i < slave->MaxNumOfClients; i++)
	{
		client = List_Select(slave->myClients, i);     // get client
		if (client != NULL)
		{
			snprintf((char *)&(slave->Status->Clients[i].ClientIp), sizeof(slave->Status->LocalIPString), "%u.%u.%u.%u", client->ClientAddressTCP.id.is_ip_addrs[0], client->ClientAddressTCP.id.is_ip_addrs[1],
				client->ClientAddressTCP.id.is_ip_addrs[2], client->ClientAddressTCP.id.is_ip_addrs[3]);
			slave->Status->Clients[i].srcPortTCP = client->ClientAddressTCP.port;
		}
		else
		{
			snprintf((char *)&(slave->Status->Clients[i].ClientIp), sizeof(slave->Status->LocalIPString), "\0");	// no client
			slave->Status->Clients[i].srcPortTCP = 0;
		}
	}
}


IEC104Slave IEC104Slave_New(char* varName, U32 scantime, S32 localIP, const char *ParamID)
{
	void* newIEC104Slave;
	int i;
	int Status;

	int result = OS_Allocate_Memory(GetMemPool(), &newIEC104Slave, sizeof(struct IEC104_Slave), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((IEC104Slave)newIEC104Slave)->Type = I104S_TYPE;
	((IEC104Slave)newIEC104Slave)->Database = NULL;
	((IEC104Slave)newIEC104Slave)->ASDU = 1;                      // default ASDU address used for all channels here is 1
	((IEC104Slave)newIEC104Slave)->originatorAdr = 4;             // originator address
	((IEC104Slave)newIEC104Slave)->LocalIP = localIP;
	((IEC104Slave)newIEC104Slave)->NumOfClients = 0;
	for (i = 0; i < I104S_INTERROGATIONCAPACITY; i++)
	{
		((IEC104Slave)newIEC104Slave)->Interrogation0GroupTypes[i] = 0;
	}

	((IEC104Slave)newIEC104Slave)->Task_Scantime = scantime;
	((IEC104Slave)newIEC104Slave)->periodicEnabled = false;
	((IEC104Slave)newIEC104Slave)->onUpdatePeriodicEnabled = false;
	((IEC104Slave)newIEC104Slave)->Status = NULL;
	((IEC104Slave)newIEC104Slave)->StatusInfoEnabled = false;
	((IEC104Slave)newIEC104Slave)->periodicPeriod = 5000;
	((IEC104Slave)newIEC104Slave)->onUpdatePeriodicPeriod = 1000;
	((IEC104Slave)newIEC104Slave)->MaxNumOfClients = I104S_CLIENTSLISTCAPACITY;
	((IEC104Slave)newIEC104Slave)->StateFunctionPointer = Startup_State;
	((IEC104Slave)newIEC104Slave)->StateFunctionPointer_Prev = 0;


	// create new list
	((IEC104Slave)newIEC104Slave)->myClients = List_New(I104S_CLIENTSLISTCAPACITY, sizeof(Client *));
	if (((IEC104Slave)newIEC104Slave)->myClients == NULL)
	{
#if defined I104S_DEBUG
		OS_com_printf("List_New failed\n");
#endif
		OS_DEBUGLOG_make_entry(0, "List_New failed in Eleon Interface");

		return NULL;
	}

	// clear buffers
	memset(((IEC104Slave)newIEC104Slave)->Recv_Buffer_TCP, 0, sizeof(((IEC104Slave)newIEC104Slave)->Recv_Buffer_TCP));
	memset(((IEC104Slave)newIEC104Slave)->Send_Buffer_TCP, 0, sizeof(((IEC104Slave)newIEC104Slave)->Send_Buffer_TCP));
	
	//create var in database for storing pointer to IEC104Slave to share with other programs(ie "IEC104_Slave_Interface")
	if (strlen(varName) < 31)
	{
		 
		 struct os_db_local myVars[] =
		{
		   VAR_ELEMENT_LOCAL(varName, TYPE_U32, 200/*level read*/, 200/*level write*/, SCALE_NONE, 0, UNIT_NONE, 0, 0, 0, 0, NULL, NOLOG_ENABLE)

		};

		 struct os_db_local* newIEC104Slavedatabasevar;
		int result = OS_Allocate_Memory(GetMemPool(), &newIEC104Slavedatabasevar, sizeof(struct os_db_local), OS_NO_SUSPEND);
		if (result != OS_SUCCESS) { return NULL; }
		
		newIEC104Slavedatabasevar->c = myVars->c;
		newIEC104Slavedatabasevar->l = myVars->l;
			

		size_t ErrorEntry = 0;
		Status = OS_VarDB_CreateLocals(newIEC104Slavedatabasevar, sizeof(myVars) / sizeof(myVars[0]), &ErrorEntry, ParamID);
		if (Status != 0)
		{
			AppSystemLog(7, "IEC104S vC fail: %d", Status);
		}
		else
		{
			OS_VarDB_UpdateVariableByName(varName, &newIEC104Slave, sizeof(newIEC104Slave));
		}
	}

	return (IEC104Slave)newIEC104Slave;
}



S32 IEC104Slave_SetDatabase(IEC104Slave slave, IEC104Database database)
{
#ifdef I104S_TYPE_CHECK
	if (!IEC104Slave_ValidateObject(slave)) { return -1; }         // pointer to invalid object structure
#endif
	slave->Database = database;
	return 0;
}



S32 IEC104Slave_EnableStatusData(IEC104Slave slave, IEC104Slave_StatusInfo statusInfo, CustomLog customLog)
{
#ifdef I104S_TYPE_CHECK
	if (!IEC104Slave_ValidateObject(slave)) { return -1; }         // pointer to invalid Slave structure
#endif
	if (statusInfo->Type != 139) { return -2; }         // pointer to invalid StatusInfo structure
	if (customLog == NULL) { return -3; }               // CustomLog NULL

	slave->Status = statusInfo;
	//set Status default values
	slave->Status->NumOfClients = 0;
	strcpy(slave->Status->StatusTxt, "Not Initalized\0");
	strcpy(slave->Status->LocalIPString, "000.000.000.000\0");
	int i;
	for (i = 0; i < I104S_CLIENTSLISTCAPACITY; i++) {
		slave->Status->Clients[i].Received = 0;
		slave->Status->Clients[i].Sent = 0;
		snprintf((char *)&(slave->Status->Clients[i].ClientIp), sizeof(slave->Status->LocalIPString), "\0");	// no client
		slave->Status->Clients[i].srcPortTCP = 0;
	}
	slave->Status->InterfaceEventLog = customLog;
	slave->StatusInfoEnabled = true;
	if (slave->Status->InterfaceEventLog == NULL)
	{
#if defined I104S_DEBUG
		OS_com_printf("IEC104S eventlog NULL\n");
#endif
		OS_DEBUGLOG_make_entry(0, "IEC104S eventlog NULL");

		return -4;
	}

	return 0;
}



//returns -1 if pointer is to invalid object struct, returns -2 if index exceeds max num of interrogation groups(13)
S32 IEC104Slave_AddToInterrogationGroup0(IEC104Slave slave, U8 type, int index)
{
#ifdef I104S_TYPE_CHECK
	if (!IEC104Slave_ValidateObject(slave)) { return -1; }         // pointer to invalid object structure
#endif
	if (index < 0 || index >= I104S_INTERROGATIONCAPACITY)
	{
		return -2;
	}
	slave->Interrogation0GroupTypes[index] = type;
	return 0;
}

S32 IEC104Slave_StartCyclic(IEC104Slave slave, U32 period) {
	slave->periodicPeriod = period;
	slave->periodicEnabled = true;
	return 0;
}

S32 IEC104Slave_StopCyclic(IEC104Slave slave) {

	slave->periodicEnabled = false;
	return 0;
}

S32 IEC104Slave_StartUpdatedCyclic(IEC104Slave slave, U32 period) {
	slave->onUpdatePeriodicPeriod = period;
	slave->onUpdatePeriodicEnabled = true;
	return 0;
}

S32 IEC104Slave_StopUpdatedCyclic(IEC104Slave slave) {

	slave->onUpdatePeriodicPeriod = false;
	return 0;
}
//-----------------------------------------------------------------------
// CONTROL                CONTROL                 CONTROL
//-----------------------------------------------------------------------

static S32 myOS_Receive(U16 tcp_socket, char* data)
{
    int received = OS_Recv(tcp_socket, data, I104S_RECV_BUFFER_TCP_SIZE, 0);
    if (received > 0) {
#if defined I104S_DEBUG
        OS_com_printf("\n\rRX  IEC104S(%d): ", received);
        int y;
        for (y = 0; y < received; y++) {
            OS_com_printf(" %02X", data[y]);
        }
        OS_com_printf("\n\r");
#endif
    }

    return received;
}


static S32 myOS_Send(U16 tcp_socket, char* data, U16 size)
{
    OS_Send(tcp_socket, data, size, 0);
#if defined I104S_DEBUG
    OS_com_printf("\n\rTX  IEC104S(%d): ", size);
    int y;
    for (y = 0; y < size; y++) {
        OS_com_printf(" %02X", data[y]);
    }
    OS_com_printf("\n\r");
#endif
}


static void AbortClient(Client *client)
{
	IEC104Slave slave = client->Slave;
	int Status = 0;

#if defined I104S_DEBUG
	OS_com_printf("I104S starting abort\r\n");
#endif
	Status = OS_Abort(client->TCP_Socket);
	if (Status != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error aborting service TCP socket: %d\r\n", Status);
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Error aborting TCP"); }
#if defined I104S_DEBUG
		OS_com_printf("I104S abort failed\r\n");
#endif
	}

	int index = List_Find(slave->myClients, client);
#if defined I104S_DEBUG
	OS_com_printf("\nI104S remove client id: %d\r\n", index);
#endif
	List_Remove(slave->myClients, index); // remove disconnected client from list
	slave->NumOfClients = List_Count(slave->myClients);
	if (slave->StatusInfoEnabled) {
		slave->Status->NumOfClients = slave->NumOfClients;
	}
	UpdateAllClientsIPTxt(slave);
	// reset counters
	client->ReceivedCounter = 0;
	client->SentCounter = 0;
	OS_Deallocate_Memory(client); // deallocate client struct data memory
	if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Client aborted"); }
#if defined I104S_DEBUG
	OS_com_printf("I104S abort success\r\n");
#endif
}



static void AbortAllConnections(IEC104Slave slave)
{
	int Status = 0;
	int index;
	int nextIndex;

	// abort listening socket
	if (slave->ListenTCP_Socket)
	{
		Status = OS_Abort(slave->ListenTCP_Socket);
		if (Status != OS_SUCCESS)
		{
			OS_DEBUGLOG_make_entry(0, "Error closing listen TCP socket: %d\r\n", Status);
			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Error closing TCP listener"); }
#if defined I104S_DEBUG
			OS_com_printf("Error aborting listen TCP socket: %d\r\n", Status);
#endif
		}
	}

	if (slave->NumOfClients > 0)
	{
		// get first client
		index = List_First(slave->myClients);                  // get index of first client in list

		int clientsCount = slave->NumOfClients;
		int i;
		for (i = 0; i < clientsCount; i++)
		{
			nextIndex = List_Next(slave->myClients, index);    // get index of next client in list
			AbortClient(List_Select(slave->myClients, index));
			index = nextIndex;
		}
	}

#if defined I104S_DEBUG
	OS_com_printf("All connections closed\r\n");
#endif
}

static STATUS StartListeningIncoming_TCP(IEC104Slave slave)
{
	STATUS LocalStatus = 0;
	int result;

	// Create new socket for listening inbound TCP connections
	result = OS_Socket(OS_FAMILY_IP, OS_TYPE_STREAM, OS_NONE);
	if (result < 0)
	{
		OS_DEBUGLOG_make_entry(0, "Can't create \"ListenTCP_Socket\" socket: %d\r\n", result);
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Error creating TCP socket"); }
#if defined I104S_DEBUG
		OS_com_printf("Can't create \"ListenTCP_Socket\" socket: %d\r\n", result);
#endif
		return result;
	}
	else
	{
		slave->ListenTCP_Socket = result;
		OS_DEBUGLOG_make_entry(0, "Socket \"ListenTCP_Socket\" created: %d\r\n", result);
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "TCP socket created"); }
#if defined I104S_DEBUG
		OS_com_printf("Socket \"ListenTCP_Socket\" created: %d\r\n", result);
#endif
	}



	// Initialize local TCP endpoint
	slave->LocalAddressTCP.family = OS_FAMILY_IP;
	slave->LocalAddressTCP.port = slave->LocalPortTCP;
	slave->LocalAddressTCP.id.is_ip_addrs[0] = (slave->LocalIP & 0x000000ff);
	slave->LocalAddressTCP.id.is_ip_addrs[1] = (slave->LocalIP & 0x0000ff00) >> 8;
	slave->LocalAddressTCP.id.is_ip_addrs[2] = (slave->LocalIP & 0x00ff0000) >> 16;
	slave->LocalAddressTCP.id.is_ip_addrs[3] = (slave->LocalIP & 0xff000000) >> 24;
	slave->LocalAddressTCP.name = "WP4x00_TCP";
	if (slave->StatusInfoEnabled) {
		sprintf((slave->Status->LocalIPString), "%u.%u.%u.%u", slave->LocalAddressTCP.id.is_ip_addrs[0], slave->LocalAddressTCP.id.is_ip_addrs[1], slave->LocalAddressTCP.id.is_ip_addrs[2], slave->LocalAddressTCP.id.is_ip_addrs[3]);
	}
	// Bind local endpoint to socket
	LocalStatus = OS_Bind(slave->ListenTCP_Socket, &slave->LocalAddressTCP, 0);
	if (LocalStatus <= 0)
	{
		OS_DEBUGLOG_make_entry(0, "Error binding TCP socket: %d, localIP: %s\r\n", LocalStatus, (slave->Status->LocalIPString));
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "TCP socket binding failed"); }
#if defined I104S_DEBUG
		OS_com_printf("Error binding TCP socket: %d, localIP: %s\r\n", LocalStatus, slave->LocalIP);
#endif
		return LocalStatus;
	}
	else
	{
		OS_DEBUGLOG_make_entry(0, "TCP socket binded: %d\r\n", LocalStatus);
#if defined I104S_DEBUG
		OS_com_printf("TCP socket binded: %d\r\n", LocalStatus);
#endif
	}

	// Start listening incoming connections
	LocalStatus = OS_Listen(slave->ListenTCP_Socket, 0);
	if (LocalStatus != OS_SUCCESS)
	{
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Started listening TCP"); }
#if defined I104S_DEBUG
		OS_com_printf("Error listening TCP socket: %d\r\n", LocalStatus);
#endif
		return LocalStatus;
	}
	else
	{
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Started listening TCP"); }
#if defined I104S_DEBUG
		OS_com_printf("Started listening TCP socket\r\n");
#endif
	}

	return LocalStatus;
}

// accept incoming connections and handle LogIn procedure
static void AcceptConnection(IEC104Slave slave)
{
	int result;
	struct addr_struct address;
	U16 TCP_Socket;
	Client* newClient;

	result = 0;
	OS_Fcntl(slave->ListenTCP_Socket, OS_SETFLAG, OS_NO_BLOCK);
	result = OS_Accept(slave->ListenTCP_Socket, &address, 0);
	OS_Fcntl(slave->ListenTCP_Socket, OS_SETFLAG, OS_BLOCK);

	// new client connection received
	if (result >= 0)
	{
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "New incoming connection"); }

		if (slave->NumOfClients < slave->MaxNumOfClients)     // don't accept any new connection when already max number of clients
		{
			TCP_Socket = result;

		}
		else
		{
			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Connection refused(max limit)"); }
			OS_Close_Socket(result);
			return;
		}

		// create new client in memory
		result = OS_Allocate_Memory(GetMemPool(), (void**)&newClient, sizeof(Client), OS_NO_SUSPEND);  // allocate memory for new client struct
		if (result != OS_SUCCESS)
		{
			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Failed to allocate memory for new client struct"); }
			OS_Close_Socket(TCP_Socket);
			return;
		}

		// PRESET VALUES
		newClient->ClientAddressTCP.family = OS_FAMILY_IP;
		newClient->ClientAddressTCP.id.is_ip_addrs[0] = address.id.is_ip_addrs[0];
		newClient->ClientAddressTCP.id.is_ip_addrs[1] = address.id.is_ip_addrs[1];
		newClient->ClientAddressTCP.id.is_ip_addrs[2] = address.id.is_ip_addrs[2];
		newClient->ClientAddressTCP.id.is_ip_addrs[3] = address.id.is_ip_addrs[3];
		newClient->ClientAddressTCP.name = "WP4x00_TCP";
		newClient->ClientAddressTCP.port = address.port;
		newClient->TCP_Socket = TCP_Socket;
		newClient->Slave = slave;
		newClient->KeepAlive_Timer = 0;
		newClient->ReceivedCounter = 0;
		newClient->SentCounter = 0;
		newClient->StartDT = false;
		newClient->ReceiveSequence = 0;
		newClient->SendSequence = 0;
		newClient->AutoTimer = 0;
		newClient->onUpdateAutoTimer = 0;
		newClient->UpdatedDataSent = true;

		// add new client to the list
		List_Trim(slave->myClients);	// trim the list just in case some clients have dropped and the list is not continuous
		result = List_Add(slave->myClients, newClient);

		if (result < 0) // when adding new client into list fails
		{
			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Failed to add new client to list"); }
			OS_Deallocate_Memory(newClient);
			OS_Close_Socket(TCP_Socket);
			return;
		}

		slave->NumOfClients = List_Count(slave->myClients);
		if (slave->StatusInfoEnabled) {
			slave->Status->NumOfClients = slave->NumOfClients;
		}
		UpdateAllClientsIPTxt(slave);

		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Client accepted"); }
		return;
	}

	return;
}

static void Send_STARTDT_Reply(Client* client)
{
	IEC104Slave slave = client->Slave;
#if defined I104S_DEBUG
	OS_com_printf("I104S Send StartDT reply\r\n");
#endif


	// preload some answer bytes
	slave->Send_Buffer_TCP[0] = 0x68;
	slave->Send_Buffer_TCP[1] = 0x04;
	slave->Send_Buffer_TCP[2] = 0x0B;
	slave->Send_Buffer_TCP[3] = 0x00;
	slave->Send_Buffer_TCP[4] = 0x00;
	slave->Send_Buffer_TCP[5] = 0x00;

	// send reply to client
	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 6);
	client->SentCounter += 1;
}

static void Send_STOPDT_Reply(Client* client)
{
	IEC104Slave slave = client->Slave;
#if defined I104S_DEBUG
	OS_com_printf("I104S Send StopDT reply\r\n");
#endif

	// preload some answer bytes
	slave->Send_Buffer_TCP[0] = 0x68;
	slave->Send_Buffer_TCP[1] = 0x04;
	slave->Send_Buffer_TCP[2] = 0x31;
	slave->Send_Buffer_TCP[3] = 0x00;
	slave->Send_Buffer_TCP[4] = 0x00;
	slave->Send_Buffer_TCP[5] = 0x00;

	// send reply to client

	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 6);
	client->SentCounter += 1;
}

static void Send_TESTFR_Reply(Client* client)
{
	IEC104Slave slave = client->Slave;
#if defined I104S_DEBUG
	OS_com_printf("I104S Send Send_TESTFR reply\r\n");
#endif

	// preload some answer bytes
	slave->Send_Buffer_TCP[0] = 0x68;
	slave->Send_Buffer_TCP[1] = 0x04;
	slave->Send_Buffer_TCP[2] = 0x83;
	slave->Send_Buffer_TCP[3] = 0x00;
	slave->Send_Buffer_TCP[4] = 0x00;
	slave->Send_Buffer_TCP[5] = 0x00;

	// send reply to client

	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 6);
	client->SentCounter += 1;

}

//returns length of timetag or 0 in case type does not need timetag
static U8 AddTimeTag(U8 type, void *timetag) {

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
		IEC104Database_Get_CP24Time2a((IEC104_CP24Time2A*)timetag);
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
		IEC104Database_Get_CP56Time2a((IEC104_CP56Time2A*)timetag);
		return 7; // length of CP26 timetag	
	default:
		return 0;
	}
}


static void Send_Confirmation_Reply(Client* client) {

	IEC104Slave slave = client->Slave;
#if defined I104S_DEBUG
	OS_com_printf("\n\rI104S Send Confirmation reply");
#endif


	// send "Acknowledgement of command activation
	slave->Send_Buffer_TCP[0] = slave->Recv_Buffer_TCP[0];
	slave->Send_Buffer_TCP[1] = slave->Recv_Buffer_TCP[1];
	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[6] = slave->Recv_Buffer_TCP[6];
	slave->Send_Buffer_TCP[7] = slave->Recv_Buffer_TCP[7];
	slave->Send_Buffer_TCP[8] = eIEC870_COT_ACT_CON;
	slave->Send_Buffer_TCP[9] = slave->Recv_Buffer_TCP[9];
	slave->Send_Buffer_TCP[10] = slave->ASDU;
	slave->Send_Buffer_TCP[11] = slave->Recv_Buffer_TCP[11];
	slave->Send_Buffer_TCP[12] = slave->Recv_Buffer_TCP[12];
	slave->Send_Buffer_TCP[13] = slave->Recv_Buffer_TCP[13];
	slave->Send_Buffer_TCP[14] = slave->Recv_Buffer_TCP[14];
	slave->Send_Buffer_TCP[15] = slave->Recv_Buffer_TCP[15];

	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 16);
	client->SentCounter += 1;
	client->SendSequence += 2;

	// send "Termination of command activation"
	slave->Send_Buffer_TCP[0] = slave->Recv_Buffer_TCP[0];
	slave->Send_Buffer_TCP[1] = slave->Recv_Buffer_TCP[1];
	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[6] = slave->Recv_Buffer_TCP[6];
	slave->Send_Buffer_TCP[7] = slave->Recv_Buffer_TCP[7];
	slave->Send_Buffer_TCP[8] = eIEC870_COT_ACT_TERM;
	slave->Send_Buffer_TCP[9] = slave->Recv_Buffer_TCP[9];
	slave->Send_Buffer_TCP[10] = slave->ASDU;
	slave->Send_Buffer_TCP[11] = slave->Recv_Buffer_TCP[11];
	slave->Send_Buffer_TCP[12] = slave->Recv_Buffer_TCP[12];
	slave->Send_Buffer_TCP[13] = slave->Recv_Buffer_TCP[13];
	slave->Send_Buffer_TCP[14] = slave->Recv_Buffer_TCP[14];
	slave->Send_Buffer_TCP[15] = slave->Recv_Buffer_TCP[15];

	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 16);
	client->SentCounter += 1;
	client->SendSequence += 2;
}


static S32 Send_Group_Data(Client *client, U8 CotType)
{
	IEC104Slave slave = client->Slave;
	int j;
	int result;
	U8 dataCount;
    U8 packetDataCount;

	union {
		U8 byteV;
		S16 integerV;
		F32 floatV;
		unsigned char bytes[4];
		int intv;
	} value;

	U8 i;
	U32 IOA;
	U32 IOA_prev;
	int bytecount;
    
    #if defined I104S_DEBUG
	OS_com_printf("\n\rI104S Send_Group_Data");
    #endif


	for (j = 0; j < I104S_INTERROGATIONCAPACITY; j++)
	{
		if (slave->Interrogation0GroupTypes[j] != 0)
		{
			dataCount = IEC104Database_GetCount(slave->Database, slave->Interrogation0GroupTypes[j]);
			if (dataCount > 0)
			{
                U8 type = IEC104Database_GetVariableType(slave->Interrogation0GroupTypes[j]);
                
				// sending SP and DP values
				if (type == IEC104_BOOL || type == IEC104_BYTE)
                {
//                    // 68 0e 22 00 06 00 01 81 01 00 03 00 d1 07 00 01
//                    slave->Send_Buffer_TCP[0] = 0x68;
//                    slave->Send_Buffer_TCP[1] = 0x0E;
//                    slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
//                    slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
//                    slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
//                    slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
//                    slave->Send_Buffer_TCP[6] = 0x01;
//                    slave->Send_Buffer_TCP[7] = 0x81;
//                    slave->Send_Buffer_TCP[8] = 0x01;
//                    slave->Send_Buffer_TCP[9] = 0x00;
//                    slave->Send_Buffer_TCP[10] = slave->ASDU;
//                    slave->Send_Buffer_TCP[11] = 0x00;
//                    slave->Send_Buffer_TCP[12] = 0xd1;
//                    slave->Send_Buffer_TCP[13] = 0x07;
//                    slave->Send_Buffer_TCP[14] = 0x00;
//                    slave->Send_Buffer_TCP[15] = 0x01;

//                    myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 16);
//                    client->SentCounter += 1;
//                    client->SendSequence += 2;
                    
                    i = 0;
                    //while (i < dataCount) {
                        bytecount = 12;     // reset byte count each time new packet starts
                        packetDataCount = 0;
                        
                        // get first element
                        IEC104Database_GetIOA(slave->Database, &IOA, slave->Interrogation0GroupTypes[j], i);
                        IEC104Database_GetValue(slave->Database, &value.byteV, slave->Interrogation0GroupTypes[j], sizeof(BOOL), i);
                        slave->Send_Buffer_TCP[bytecount] = (U8)(IOA & 0x000000ff);
                        slave->Send_Buffer_TCP[bytecount + 1] = (U8)((IOA & 0x0000ff00) >> 8);
                        slave->Send_Buffer_TCP[bytecount + 2] = (U8)((IOA & 0x00ff0000) >> 16);
                        slave->Send_Buffer_TCP[bytecount + 3] = value.bytes[0];
                        bytecount += 4;
                        bytecount += AddTimeTag(slave->Interrogation0GroupTypes[j], (void*)&(slave->Send_Buffer_TCP[bytecount]));
                        packetDataCount++;
                        i++;
                        
                        // put element values into data packet
                        while(i < dataCount)
                        {
                            IOA_prev = IOA;
                            IEC104Database_GetIOA(slave->Database, &IOA, slave->Interrogation0GroupTypes[j], i);
                            // check if addresses is continuous - otherwise don't put the value in this packet
                            if (IOA == (IOA_prev + 1) || IOA == IOA_prev) {
                                IEC104Database_GetValue(slave->Database, &value.byteV, slave->Interrogation0GroupTypes[j], sizeof(BOOL), i);
                                slave->Send_Buffer_TCP[bytecount] = value.bytes[0];
                                bytecount += 1;
                                bytecount += AddTimeTag(slave->Interrogation0GroupTypes[j], (void*)&(slave->Send_Buffer_TCP[bytecount]));
                                packetDataCount++;
                                i++;
                            }
                            else {
                                
                                slave->Send_Buffer_TCP[bytecount] = 0x00;   // QDS = Quality descriptor
                                bytecount++;
                                
                                // sending out packet
                                // split elements into different data packets when element addresses are not continuous
                                slave->Send_Buffer_TCP[0] = 0x68;
                                slave->Send_Buffer_TCP[1] = (U8)(bytecount - 1);
                                slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
                                slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
                                slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
                                slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
                                slave->Send_Buffer_TCP[6] = slave->Interrogation0GroupTypes[j];
                                slave->Send_Buffer_TCP[7] = (U8)0x80/*SQ=1*/ | (U8)packetDataCount;
                                slave->Send_Buffer_TCP[8] = CotType;
                                slave->Send_Buffer_TCP[9] = slave->originatorAdr;
                                slave->Send_Buffer_TCP[10] = slave->ASDU;
                                slave->Send_Buffer_TCP[11] = 0x00;
                                
                                myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, bytecount);
                                client->SentCounter += 1;
                                client->SendSequence += 2;
                                break;
                            }
                            
                            // sending out packet - detected last value or limit max packet size to 256 bytes
                            if (IOA != (IOA_prev + 1) || i == dataCount || bytecount >= (253) )
                            {
                                slave->Send_Buffer_TCP[bytecount] = 0x00;   // QDS = Quality descriptor
                                bytecount++;
                                
                                slave->Send_Buffer_TCP[0] = 0x68;
                                slave->Send_Buffer_TCP[1] = (U8)(bytecount - 1);
                                slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
                                slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
                                slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
                                slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
                                slave->Send_Buffer_TCP[6] = slave->Interrogation0GroupTypes[j];
                                slave->Send_Buffer_TCP[7] = (U8)0x80/*SQ=1*/ | (U8)packetDataCount;
                                slave->Send_Buffer_TCP[8] = CotType;
                                slave->Send_Buffer_TCP[9] = slave->originatorAdr;
                                slave->Send_Buffer_TCP[10] = slave->ASDU;
                                slave->Send_Buffer_TCP[11] = 0x00;
                                
                                myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, bytecount);
                                client->SentCounter += 1;
                                client->SendSequence += 2;
                                break;
                            }
                        }
                    //}
				}
				// sending float and integer values
				else
                {
                    bytecount = 12;
                    
					for (i = 0; i < dataCount; i++)
					{
						if (bytecount > I104S_SEND_BUFFER_TCP_SIZE - 16)
						{
							return -1;
						}

						IEC104Database_GetIOA(slave->Database, &IOA, slave->Interrogation0GroupTypes[j], i);

						slave->Send_Buffer_TCP[bytecount] = (U8)(IOA & 0x000000ff);
						slave->Send_Buffer_TCP[bytecount + 1] = (U8)((IOA & 0x0000ff00) >> 8);
						slave->Send_Buffer_TCP[bytecount + 2] = (U8)((IOA & 0x00ff0000) >> 16);
                        bytecount += 3;

						switch (type)
						{
						case IEC104_INTEGER:
							IEC104Database_GetValue(slave->Database, &value.integerV, slave->Interrogation0GroupTypes[j], sizeof(S16), i);
							slave->Send_Buffer_TCP[bytecount] = value.bytes[0];
							slave->Send_Buffer_TCP[bytecount + 1] = value.bytes[1];
							slave->Send_Buffer_TCP[bytecount + 2] = 0x00;   // QDS = Quality descriptor
							bytecount += 3;
                            bytecount += AddTimeTag(slave->Interrogation0GroupTypes[j], (void*)&(slave->Send_Buffer_TCP[bytecount]));
							break;
						case IEC104_FLOAT:
							IEC104Database_GetValue(slave->Database, &value.floatV, slave->Interrogation0GroupTypes[j], sizeof(F32), i);
							slave->Send_Buffer_TCP[bytecount] = value.bytes[0];
							slave->Send_Buffer_TCP[bytecount + 1] = value.bytes[1];
							slave->Send_Buffer_TCP[bytecount + 2] = value.bytes[2];
							slave->Send_Buffer_TCP[bytecount + 3] = value.bytes[3];// value MSB
							slave->Send_Buffer_TCP[bytecount + 4] = 0x00;   // QDS = Quality descriptor
                            bytecount += 5;
							bytecount += AddTimeTag(slave->Interrogation0GroupTypes[j], (void*)&(slave->Send_Buffer_TCP[bytecount]));
							break;
						default:
							return -1;
						}
					}
                    
                    slave->Send_Buffer_TCP[bytecount] = 0x00;   // QDS = Quality descriptor
                    bytecount++;
                    
					slave->Send_Buffer_TCP[0] = 0x68;
                    slave->Send_Buffer_TCP[1] = (U8)(bytecount - 1);
                    slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
                    slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
                    slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
                    slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
                    slave->Send_Buffer_TCP[6] = slave->Interrogation0GroupTypes[j];
                    slave->Send_Buffer_TCP[7] = (U8)dataCount+1;
                    slave->Send_Buffer_TCP[8] = CotType;
                    slave->Send_Buffer_TCP[9] = slave->originatorAdr;
                    slave->Send_Buffer_TCP[10] = slave->ASDU;
                    slave->Send_Buffer_TCP[11] = 0x00;

                    myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, bytecount);
                    client->SentCounter += 1;
                    client->SendSequence += 2;
				}
			}
		}
	}
	return 0;
}


//static S32 SendGroupDataWithChangedValues(Client *client)
//{
//	IEC104Slave slave = client->Slave;
//	int j;
//	int result;
//	U8 dataCount;

//	union {
//		U8 byteV;
//		S16 integerV;
//		F32 floatV;
//		unsigned char bytes[4];
//		int intv;
//	} value;

//	U8 i;
//	U32 IOA;
//	U32 IOA_prev;
//	int bytecount;
//	int updatedDataCount;

	
//	for (j = 0; j < I104S_INTERROGATIONCAPACITY; j++)
//	{
//        i = 0;
        
//		if (slave->Interrogation0GroupTypes[j] != 0)
//		{
//			dataCount = IEC104Database_GetCount(slave->Database, slave->Interrogation0GroupTypes[j]);
//			if (dataCount > 0)
//			{
//                updatedDataCount = 0;
//                bytecount = 12;
//				U8 type = IEC104Database_GetVariableType(slave->Interrogation0GroupTypes[j]);

//				// sending SP and DP values
//				if (type == IEC104_BOOL || type == IEC104_BYTE) {
					
//					// this loop sends all elements in the interrogation group and splits them into separate data packages when IOA is not continuous
//					while (i < dataCount)
//					{
//						updatedDataCount = 0;
//                        bytecount = 12;

//						// get the first element with changed value
//						for (i; i < dataCount; i++)
//						{
//							result = IEC104Database_GetIOA(slave->Database, &IOA, slave->Interrogation0GroupTypes[j], i);
//							if (result != OS_SUCCESS) { return -1; }
//							result = IEC104Database_GetValueUpdated(slave->Database, &value.byteV, slave->Interrogation0GroupTypes[j], sizeof(BOOL), i);
//							if (result != OS_SUCCESS) { return -1; }
//                            slave->Send_Buffer_TCP[bytecount] = (U8)(IOA & 0x000000ff);
//                            slave->Send_Buffer_TCP[bytecount + 1] = (U8)((IOA & 0x0000ff00) >> 8);
//                            slave->Send_Buffer_TCP[bytecount + 2] = (U8)((IOA & 0x00ff0000) >> 16);
//                            slave->Send_Buffer_TCP[bytecount + 3] = value.bytes[0];
//                            updatedDataCount++;
//                            bytecount += 4;// + AddTimeTag(slave->Interrogation0GroupTypes[j], (void*)&(slave->Send_Buffer_TCP[bytecount + 3]));
//						}

//						// get next element with changed value; continue with previous i index
//						for (i; i < dataCount; i++)
//						{
//							IOA_prev = IOA;
//							result = IEC104Database_GetIOA(slave->Database, &IOA, slave->Interrogation0GroupTypes[j], i);
//							if (result != OS_SUCCESS) { return -1; }
//							// detect if element addresses are not continuous; then send next elements in different data packets
//							if (IOA == (IOA_prev + 1))
//							{
//								result = IEC104Database_GetValueUpdated(slave->Database, &value.byteV, slave->Interrogation0GroupTypes[j], sizeof(BOOL), i);
//								if (result != 0) { break; }
//								slave->Send_Buffer_TCP[bytecount] = value.bytes[0];
//								bytecount += 1;
//							}
//						}
//                        slave->Send_Buffer_TCP[bytecount] = 0x00;                                   // QDS = Quality descriptor
//                        bytecount += 1;

//						// only fill the header and send out data packet when actual value(s) was available
//						if (updatedDataCount > 0) {
//							slave->Send_Buffer_TCP[0] = 0x68;
//							slave->Send_Buffer_TCP[1] = (U8)(bytecount - 2);
//							slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
//							slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
//							slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
//							slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
//							slave->Send_Buffer_TCP[6] = slave->Interrogation0GroupTypes[j];
//							slave->Send_Buffer_TCP[7] = (U8)updatedDataCount;
//							slave->Send_Buffer_TCP[8] = eIEC870_COT_CYCLIC;
//							slave->Send_Buffer_TCP[9] = slave->originatorAdr;
//							slave->Send_Buffer_TCP[10] = slave->ASDU;
//							slave->Send_Buffer_TCP[11] = 0x00;

//							myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, bytecount);
//							client->SentCounter += 1;
//							client->SendSequence += 2;
//						}
//					}
//				}
//				// sending float and integer values
//				else {
//					updatedDataCount = 0;

//					for (i = 0; i < dataCount; i++)
//					{
//						if (bytecount > I104S_SEND_BUFFER_TCP_SIZE - 16)
//						{
//							return -1;
//						}

//						result = IEC104Database_GetIOA(slave->Database, &IOA, slave->Interrogation0GroupTypes[j], i);
//						if (result != OS_SUCCESS) { return -1; }


//						slave->Send_Buffer_TCP[bytecount] = (U8)(IOA & 0x000000ff);
//						slave->Send_Buffer_TCP[bytecount + 1] = (U8)((IOA & 0x0000ff00) >> 8);
//						slave->Send_Buffer_TCP[bytecount + 2] = (U8)((IOA & 0x00ff0000) >> 16);

//						switch (type)
//						{
//						case IEC104_INTEGER:
//							result = IEC104Database_GetValueUpdated(slave->Database, &value.integerV, slave->Interrogation0GroupTypes[j], sizeof(S16), i);
//							if (result < 0) { break; }
//							updatedDataCount++;
//							slave->Send_Buffer_TCP[bytecount + 3] = value.bytes[0];
//							slave->Send_Buffer_TCP[bytecount + 4] = value.bytes[1];
//							slave->Send_Buffer_TCP[bytecount + 5] = 0x00;                                   // QDS = Quality descriptor
//							bytecount += 6 + AddTimeTag(slave->Interrogation0GroupTypes[j], (void*)&(slave->Send_Buffer_TCP[bytecount + 6]));
//							break;
//						case IEC104_FLOAT:
//							result = IEC104Database_GetValueUpdated(slave->Database, &value.floatV, slave->Interrogation0GroupTypes[j], sizeof(F32), i);
//							if (result < 0) { break; }
//							updatedDataCount++;
//							slave->Send_Buffer_TCP[bytecount + 3] = value.bytes[0];
//							slave->Send_Buffer_TCP[bytecount + 4] = value.bytes[1];
//							slave->Send_Buffer_TCP[bytecount + 5] = value.bytes[2];
//							slave->Send_Buffer_TCP[bytecount + 6] = value.bytes[3];// value MSB
//							slave->Send_Buffer_TCP[bytecount + 7] = 0x00;                                           // QDS = Quality descriptor
//							bytecount += 8 + AddTimeTag(slave->Interrogation0GroupTypes[j], (void*)&(slave->Send_Buffer_TCP[bytecount + 8]));
//							break;
//						default:
//							return -1;
//						}
//					}

//					// only fill the header and send out data packet when actual value(s) was available
//					if (updatedDataCount > 0) {
//						slave->Send_Buffer_TCP[0] = 0x68;
//						slave->Send_Buffer_TCP[1] = (U8)(bytecount - 2);
//						slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
//						slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
//						slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
//						slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
//						slave->Send_Buffer_TCP[6] = slave->Interrogation0GroupTypes[j];
//						slave->Send_Buffer_TCP[7] = (U8)updatedDataCount;
//						slave->Send_Buffer_TCP[8] = eIEC870_COT_CYCLIC;
//						slave->Send_Buffer_TCP[9] = slave->originatorAdr;
//						slave->Send_Buffer_TCP[10] = slave->ASDU;
//						slave->Send_Buffer_TCP[11] = 0x00;

//						myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, bytecount);
//						client->SentCounter += 1;
//						client->SendSequence += 2;
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}


static void Send_Interrogation_Reply(Client* client) {

	IEC104Slave slave = client->Slave;
#if defined I104S_DEBUG
	OS_com_printf("\n\rI104S Send Interrogation reply");
#endif


	// send "Acknowledgement of command activation
	slave->Send_Buffer_TCP[0] = slave->Recv_Buffer_TCP[0];
	slave->Send_Buffer_TCP[1] = slave->Recv_Buffer_TCP[1];
	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[6] = slave->Recv_Buffer_TCP[6];
	slave->Send_Buffer_TCP[7] = slave->Recv_Buffer_TCP[7];
	slave->Send_Buffer_TCP[8] = eIEC870_COT_ACT_CON;
	slave->Send_Buffer_TCP[9] = slave->Recv_Buffer_TCP[9];
	slave->Send_Buffer_TCP[10] = slave->ASDU;
	slave->Send_Buffer_TCP[11] = slave->Recv_Buffer_TCP[11];
	slave->Send_Buffer_TCP[12] = slave->Recv_Buffer_TCP[12];
	slave->Send_Buffer_TCP[13] = slave->Recv_Buffer_TCP[13];
	slave->Send_Buffer_TCP[14] = slave->Recv_Buffer_TCP[14];
	slave->Send_Buffer_TCP[15] = slave->Recv_Buffer_TCP[15];

	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 16);
	client->SentCounter += 1;
	client->SendSequence += 2;

	int result = Send_Group_Data(client, eIEC870_COT_INROGEN);
	if (result < 0) { return; }


	// send "Termination of command activation"
	slave->Send_Buffer_TCP[0] = slave->Recv_Buffer_TCP[0];
	slave->Send_Buffer_TCP[1] = slave->Recv_Buffer_TCP[1];
	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[6] = slave->Recv_Buffer_TCP[6];
	slave->Send_Buffer_TCP[7] = slave->Recv_Buffer_TCP[7];
	slave->Send_Buffer_TCP[8] = eIEC870_COT_ACT_TERM;
	slave->Send_Buffer_TCP[9] = slave->Recv_Buffer_TCP[9];
	slave->Send_Buffer_TCP[10] = slave->ASDU;
	slave->Send_Buffer_TCP[11] = slave->Recv_Buffer_TCP[11];
	slave->Send_Buffer_TCP[12] = slave->Recv_Buffer_TCP[12];
	slave->Send_Buffer_TCP[13] = slave->Recv_Buffer_TCP[13];
	slave->Send_Buffer_TCP[14] = slave->Recv_Buffer_TCP[14];
	slave->Send_Buffer_TCP[15] = slave->Recv_Buffer_TCP[15];

	result = myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 16);
	client->SentCounter += 1;
	client->SendSequence += 2;
}


static void Send_CounterInterrogation_Reply(Client* client) {

	IEC104Slave slave = client->Slave;
#if defined I104S_DEBUG
	OS_com_printf("\n\rI104S Send Counter Interrogation reply");
#endif


	// send "Acknowledgement of command activation
	slave->Send_Buffer_TCP[0] = slave->Recv_Buffer_TCP[0];
	slave->Send_Buffer_TCP[1] = slave->Recv_Buffer_TCP[1];
	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[6] = slave->Recv_Buffer_TCP[6];
	slave->Send_Buffer_TCP[7] = slave->Recv_Buffer_TCP[7];
	slave->Send_Buffer_TCP[8] = eIEC870_COT_ACT_CON;
	slave->Send_Buffer_TCP[9] = slave->Recv_Buffer_TCP[9];
	slave->Send_Buffer_TCP[10] = slave->ASDU;
	slave->Send_Buffer_TCP[11] = slave->Recv_Buffer_TCP[11];
	slave->Send_Buffer_TCP[12] = slave->Recv_Buffer_TCP[12];
	slave->Send_Buffer_TCP[13] = slave->Recv_Buffer_TCP[13];
	slave->Send_Buffer_TCP[14] = slave->Recv_Buffer_TCP[14];
	slave->Send_Buffer_TCP[15] = slave->Recv_Buffer_TCP[15];

	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 16);
	client->SentCounter += 1;
	client->SendSequence += 2;

	int result = Send_Group_Data(client, eIEC870_COT_INROGEN);
	if (result < 0) { return; }


	// send "Termination of command activation"
	slave->Send_Buffer_TCP[0] = slave->Recv_Buffer_TCP[0];
	slave->Send_Buffer_TCP[1] = slave->Recv_Buffer_TCP[1];
	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[6] = slave->Recv_Buffer_TCP[6];
	slave->Send_Buffer_TCP[7] = slave->Recv_Buffer_TCP[7];
	slave->Send_Buffer_TCP[8] = eIEC870_COT_ACT_TERM;
	slave->Send_Buffer_TCP[9] = slave->Recv_Buffer_TCP[9];
	slave->Send_Buffer_TCP[10] = slave->ASDU;
	slave->Send_Buffer_TCP[11] = slave->Recv_Buffer_TCP[11];
	slave->Send_Buffer_TCP[12] = slave->Recv_Buffer_TCP[12];
	slave->Send_Buffer_TCP[13] = slave->Recv_Buffer_TCP[13];
	slave->Send_Buffer_TCP[14] = slave->Recv_Buffer_TCP[14];
	slave->Send_Buffer_TCP[15] = slave->Recv_Buffer_TCP[15];

	result = myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, 16);
	client->SentCounter += 1;
	client->SendSequence += 2;
}


static S32 Send_Unknown_Reply(Client *client, int length, U8 unknownType)
{
	IEC104Slave slave = client->Slave;
	int i;
	for (i = 0; i < length; i++) {
		slave->Send_Buffer_TCP[i] = slave->Recv_Buffer_TCP[i];
	}

	slave->Send_Buffer_TCP[1] = (U8)(length - 2);
	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[8] = unknownType;

	// send reply to client
	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, length);
	client->SentCounter += 1;
	client->SendSequence += 2;
	return 0;

}

static S32 Set_Data_Command(Client *client)
{
	IEC104Slave slave = client->Slave;
	union {
		U8 byteV;
		S16 integerV;
		F32 floatV;
		unsigned char bytes[4];
		int intv;
	} value;

	S32 ioa = ((U8)slave->Recv_Buffer_TCP[14] << 16) + ((U8)slave->Recv_Buffer_TCP[13] << 8) + (U8)slave->Recv_Buffer_TCP[12];
	int result = IEC104Database_GetVariableType(slave->Recv_Buffer_TCP[6]);

	switch (result)
	{
	case IEC104_BOOL:
		value.byteV = (U8)slave->Recv_Buffer_TCP[15];
		result = IEC104Database_Set(slave->Database, &value.byteV, sizeof(value.byteV), slave->Recv_Buffer_TCP[6], ioa);
		if (result < 0) { return -1; }
		break;
	case IEC104_BYTE:
		value.byteV = (U8)slave->Recv_Buffer_TCP[15];
		result = IEC104Database_Set(slave->Database, &value.byteV, sizeof(value.byteV), slave->Recv_Buffer_TCP[6], ioa);
		if (result < 0) { return -1; }
		break;
	case IEC104_INTEGER:
		value.integerV = ((U8)slave->Recv_Buffer_TCP[16] << 8) + (U8)slave->Recv_Buffer_TCP[15];
		result = IEC104Database_Set(slave->Database, &value.integerV, sizeof(value.integerV), slave->Recv_Buffer_TCP[6], ioa);
		if (result < 0) { return -1; }
		break;
	case IEC104_FLOAT:
		//value.floatV = ((U8)Recv_Buffer_TCP[17] << 24) + ((U8)Recv_Buffer_TCP[17] << 16) + ((U8)Recv_Buffer_TCP[16] << 8) + (U8)Recv_Buffer_TCP[15];
		value.bytes[0] = slave->Recv_Buffer_TCP[15];
		value.bytes[1] = slave->Recv_Buffer_TCP[16];
		value.bytes[2] = slave->Recv_Buffer_TCP[17];
		value.bytes[3] = slave->Recv_Buffer_TCP[18];
		result = IEC104Database_Set(slave->Database, &value.floatV, sizeof(value.floatV), slave->Recv_Buffer_TCP[6], ioa);
		if (result < 0) { return -1; }
		break;
	default:
		return -1;
	}
	return 0;
}


static S32 Send_DataReply(Client* client)
{
	IEC104Slave slave = client->Slave;
	S32 ioa = ((U8)slave->Recv_Buffer_TCP[14] << 16) + ((U8)slave->Recv_Buffer_TCP[13] << 8) + (U8)slave->Recv_Buffer_TCP[12];
	S32 type = IEC104Database_GetType(slave->Database, ioa);
	if (type < 0) { return -1; }

	slave->Send_Buffer_TCP[0] = 0x68;

	slave->Send_Buffer_TCP[2] = (U8)(client->SendSequence & 0x00ff);
	slave->Send_Buffer_TCP[3] = (U8)(client->SendSequence / 256);
	slave->Send_Buffer_TCP[4] = (U8)(client->ReceiveSequence & 0x00ff);
	slave->Send_Buffer_TCP[5] = (U8)(client->ReceiveSequence / 256);
	slave->Send_Buffer_TCP[6] = type;
	slave->Send_Buffer_TCP[7] = 0x01; // set number of objects

	slave->Send_Buffer_TCP[8] = eIEC870_COT_INROGEN;
	slave->Send_Buffer_TCP[9] = slave->originatorAdr;
	slave->Send_Buffer_TCP[10] = slave->ASDU;
	slave->Send_Buffer_TCP[11] = 0x00;

	slave->Send_Buffer_TCP[12] = (U8)(ioa & 0x000000ff);
	slave->Send_Buffer_TCP[13] = (U8)((ioa & 0x0000ff00) >> 8);
	slave->Send_Buffer_TCP[14] = (U8)((ioa & 0x00ff0000) >> 16);

	union {
		U8 byteV;
		S16 integerV;
		F32 floatV;
		unsigned char bytes[4];
		int intv;
	} value;

	int result = IEC104Database_GetVariableType(type);
	switch (result)
	{
	case IEC104_BOOL:
		result = IEC104Database_Get(slave->Database, &value.byteV, sizeof(BOOL), type, ioa);
		if (result < 0) { return -1; }
		slave->Send_Buffer_TCP[1] = (U8)14;
		slave->Send_Buffer_TCP[15] = value.bytes[0];
		break;
	case IEC104_BYTE:
		result = IEC104Database_Get(slave->Database, &value.byteV, sizeof(U8), type, ioa);
		if (result < 0) { return -1; }
		slave->Send_Buffer_TCP[1] = (U8)14;
		slave->Send_Buffer_TCP[15] = value.bytes[0];
		break;
	case IEC104_INTEGER:
		result = IEC104Database_Get(slave->Database, &value.integerV, sizeof(S16), type, ioa);
		if (result < 0) { return -1; }
		slave->Send_Buffer_TCP[1] = (U8)16;
		slave->Send_Buffer_TCP[15] = value.bytes[0];
		slave->Send_Buffer_TCP[16] = value.bytes[1];
		slave->Send_Buffer_TCP[17] = 0x00;                                   // QDS = Quality descriptor	 
		break;
	case IEC104_FLOAT:
		result = IEC104Database_Get(slave->Database, &value.floatV, sizeof(F32), type, ioa);
		if (result < 0) { return -1; }
		slave->Send_Buffer_TCP[1] = (U8)18;
		slave->Send_Buffer_TCP[15] = value.bytes[0];
		slave->Send_Buffer_TCP[16] = value.bytes[1];
		slave->Send_Buffer_TCP[17] = value.bytes[2];
		slave->Send_Buffer_TCP[18] = value.bytes[3];// value MSB
		slave->Send_Buffer_TCP[19] = 0x00;                                           // QDS = Quality descriptor	 
		break;
	default:
		return -1;
	}


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
		IEC104Database_Get_CP56Time2a((IEC104_CP56Time2A *)&(slave->Send_Buffer_TCP[slave->Send_Buffer_TCP[1] + 2]));
		slave->Send_Buffer_TCP[1] += 3;
		break;
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
		IEC104Database_Get_CP56Time2a((IEC104_CP56Time2A *)&(slave->Send_Buffer_TCP[slave->Send_Buffer_TCP[1] + 2]));
		slave->Send_Buffer_TCP[1] += 7;
		break;
	default:
		break;
	}

	myOS_Send(client->TCP_Socket, slave->Send_Buffer_TCP, slave->Send_Buffer_TCP[1] + 2);
	client->SentCounter += 1;
	client->SendSequence += 2;

	return 0;
}


// Send periodic packet
static S32 SendPeriodicPacket(Client* client)
{
	IEC104Slave slave = client->Slave;

	if (!slave->periodicEnabled) { return 0; }

	if (client->StartDT)
	{
		// check if sample time period passed
		client->AutoTimer += slave->Task_Scantime;
		if (client->AutoTimer >= slave->periodicPeriod)
		{
			client->AutoTimer = 0;
		}
		else
		{
            return 0;
		}
	}
	else
	{
        return 0;
	}

	client->onUpdateAutoTimer = 0;
	client->UpdatedDataSent = true;

	Send_Group_Data(client, eIEC870_COT_CYCLIC);
	return 0;
}


//// Send periodic updated packet
//static S32 SendPeriodicUpdatePacket(Client* client)
//{
//	IEC104Slave slave = client->Slave;
//	if (!slave->onUpdatePeriodicEnabled) { return 0; }
//	if (slave->onUpdatePeriodicPeriod >= slave->periodicPeriod)
//	{
//		return 0;
//	}

//	if (client->StartDT)
//	{
//		// check if sample time period passed
//		client->onUpdateAutoTimer += slave->Task_Scantime;
//		if (client->onUpdateAutoTimer >= slave->onUpdatePeriodicPeriod)
//		{
//			client->onUpdateAutoTimer = 0;
//		}
//		else
//		{
//			return 0;
//		}
//	}
//	else
//	{
//		return 0;
//	}
//	if (!slave->periodicEnabled) {
//		SendGroupDataWithChangedValues(client);
//	}
//	else if (client->AutoTimer < (slave->periodicPeriod - slave->onUpdatePeriodicPeriod)) {
//		SendGroupDataWithChangedValues(client);
//	}
//	client->UpdatedDataSent = true;
//	return 0;
//}



// main processing function for handling client communication
static void Process(Client* client)
{
	IEC104Slave slave = client->Slave;
	int received = 0;
	int result;
    

	// receive TCP command frame
	received = myOS_Receive(client->TCP_Socket, slave->Recv_Buffer_TCP);
	if (received > 0)
	{
		client->ReceivedCounter += 1;

		if (slave->Recv_Buffer_TCP[0] != 0x68)		// FAULT invalid frame
		{
#if defined I104S_DEBUG
			OS_com_printf("\n\rI104S invalid frame, received: %d", received);
#endif
			return;
		}


		// if fixed length telegram(4 bytes: S-Format or I-Format)
		if (slave->Recv_Buffer_TCP[1] == 4)
		{
			switch (slave->Recv_Buffer_TCP[2])
			{
			case 0x07: // if STARTDT request
				Send_STARTDT_Reply(client);
				client->StartDT = true;
				break;
			case 0x19:	// if STOPDT request
				Send_STOPDT_Reply(client);
				client->StartDT = false;
				break;
			case 0x43:  // if TESTFR request
				Send_TESTFR_Reply(client);
				break;
			case 0x01:   // if S-Format received
				//Send_SFrame();
				break;
			default:
				break;
			}
		}
		// if not fixed length telegram
		else if (received > 6)
		{
			if (client->StartDT)     // check if start transmission is set to allow transmission
			{
				client->ReceivedCounter += 1;
				client->ReceiveSequence += 2;

//				if (slave->Recv_Buffer_TCP[10] == slave->ASDU)
//				{
					switch (slave->Recv_Buffer_TCP[6])
					{
                        case C_IC_NA_1:	//Interrogation Command
                            Send_Interrogation_Reply(client);
                            break;
                        case C_CI_NA_1: //Counter interrogation
                            Send_Unknown_Reply(client, received, eIEC870_COT_UNKNOWN_TYPE);
                            break;
                        case C_CS_NA_1: //Clock sync
                            //
                            break;
                        case C_RD_NA_1:	//Read Value Command
                            result = Send_DataReply(client);
                            if (result != OS_SUCCESS)
                            {
                                Send_Unknown_Reply(client, received, eIEC870_COT_UNKNOWN_OBJECT_ADDRESS);
                                return;
                            }
                            break;
                        case C_SC_NA_1:	//set value commands...
                        case C_DC_NA_1:
                        case C_RC_NA_1:
                        case C_SE_NA_1:
                        case C_SE_NB_1:
                        case C_SE_NC_1:
                        case C_BO_NA_1:
                        case C_SC_TA_1:
                        case C_DC_TA_1:
                        case C_RC_TA_1:
                        case C_SE_TA_1:
                        case C_SE_TB_1:
                        case C_SE_TC_1:
                        case C_BO_TA_1:
                            result = Set_Data_Command(client);
                            if (result != OS_SUCCESS)
                            {
                                Send_Unknown_Reply(client, received, eIEC870_COT_UNKNOWN_OBJECT_ADDRESS);
                                return;
                            }
                            Send_Confirmation_Reply(client);
                            break;
					default:
						Send_Unknown_Reply(client, received, eIEC870_COT_UNKNOWN_TYPE);
                        return;
					}

//				}
//				else
//				{
//					Send_Unknown_Reply(client, received, eIEC870_COT_UNKNOWN_ASDU_ADDRESS);
//                  return;
//				}
			}
//			else
//			{
//				// send no reply, because no STARTDT command received
//			}
		}
	}
	else if (received == OS_NOT_CONNECTED)
	{
#if defined I104S_DEBUG
		OS_com_printf("I104S client lost\n\r");
#endif
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Client lost"); }
		AbortClient(client);
		return;
	}
    
    
    SendPeriodicPacket(client);
	//SendPeriodicUpdatePacket(client);
}


//***********************************************************************
// STATE : Communication interface is disabled, waiting for enable command
//***********************************************************************
static void Disabled_State(BOOL firstentry, IEC104Slave slave)
{
	//-----------------------------------------------------------------------
	//ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (slave->StatusInfoEnabled) {
			strcpy(slave->Status->StatusTxt, "Disabled");


			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Interface disabled"); }
		}
		AbortAllConnections(slave);
	}

	//-----------------------------------------------------------------------
	// EXIT CONDITIONS
	//-----------------------------------------------------------------------

	if (slave->IEC104SlaveEnabled) // enabling
	{
		slave->StateFunctionPointer = Startup_State;
	}
}

//***********************************************************************
// STATE : Interface error state
//***********************************************************************
static void InterfaceError_State(BOOL firstentry, IEC104Slave slave)
{
	//-----------------------------------------------------------------------
	//ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (slave->StatusInfoEnabled) {
			strcpy(slave->Status->StatusTxt, "Interface error");

			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Interface error state"); }
		}
		slave->IEC104SlaveEnabled_prev = slave->IEC104SlaveEnabled;
	}

	//-----------------------------------------------------------------------
	// EXIT CONDITIONS
	//-----------------------------------------------------------------------

	if (slave->IEC104SlaveEnabled && !slave->IEC104SlaveEnabled_prev) // restarting when interface is reenabled
	{
		slave->StateFunctionPointer = Startup_State;
	}

	slave->IEC104SlaveEnabled_prev = slave->IEC104SlaveEnabled;
}

//***********************************************************************
// STATE : Starting up interface
//***********************************************************************
static void Startup_State(BOOL firstentry, IEC104Slave slave)
{
	//-----------------------------------------------------------------------
	//ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (slave->StatusInfoEnabled) {
			strcpy(slave->Status->StatusTxt, "Startup");

			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Startup"); }
		}
		if (!(slave->IEC104SlaveEnabled)) // disabling
		{
			slave->StateFunctionPointer = Disabled_State;
			return;
		}
		if (StartListeningIncoming_TCP(slave) != 0) { slave->StateFunctionPointer = InterfaceError_State; }
		slave->StateFunctionPointer = Operational_State;
		return;
	}

}

//***********************************************************************
// STATE : Interface is operational
//***********************************************************************
static void Operational_State(BOOL firstentry, IEC104Slave slave)
{

	//-----------------------------------------------------------------------
	//ENTRY ACTION
	//-----------------------------------------------------------------------
	if (firstentry)
	{
		if (slave->StatusInfoEnabled) {
			strcpy(slave->Status->StatusTxt, "Interface operational");

			if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Interface operational"); }
		}
	}

	//-----------------------------------------------------------------------
	//CONTROL
	//-----------------------------------------------------------------------

	// handle new clients
	AcceptConnection(slave);

	// main process handling for all existing clients
	if (slave->NumOfClients > 0)
	{
		BOOL resetUpdatedDataFlag = false;
		if (slave->updateDatabaseValues) {
			IEC104Database_UpdateDatabaseValues(slave->Database); //Update values if changed
			resetUpdatedDataFlag = true;
		}
		// get first client
		int index = List_First(slave->myClients);                  // get index of first client in list

		int i;
		slave->updateDatabaseValues = true;
		for (i = 0; i < slave->NumOfClients; i++)
		{
			Client* client = List_Select(slave->myClients, index);
			if (client == NULL)
			{
#if defined I104S_DEBUG
				OS_com_printf("I104S process error, no client\r\n");
#endif
				return;
			}
			if (resetUpdatedDataFlag) {
				client->UpdatedDataSent = false;
			}
			Process(client);

			// update data counters
			if (slave->StatusInfoEnabled) {
				slave->Status->Clients[index].Received = client->ReceivedCounter;
				slave->Status->Clients[index].Sent = client->SentCounter;
			}
			index = List_Next(slave->myClients, index);        // get index of next client in list
			if (!client->UpdatedDataSent) { slave->updateDatabaseValues = false; }
		}
	}


	//-----------------------------------------------------------------------
	// EXIT CONDITIONS
	//-----------------------------------------------------------------------

	if (!(slave->IEC104SlaveEnabled)) // disabling
	{
		slave->StateFunctionPointer = Disabled_State;
	}
}

S32 IEC104Slave_Control(IEC104Slave slave)
{
#ifdef I104S_TYPE_CHECK
	if (!IEC104Slave_ValidateObject(slave)) { return -1; }         // pointer to invalid object structure
#endif
	STATUS LocalStatus = 0;
	if (slave == NULL) {
		return -1;
	}
	//***********************************************************************
    // Function call to operating state functions - uses pointer to function
    // "StateFunctionPointer" points to the mode function that should be called
    //***********************************************************************

	if (slave->StateFunctionPointer != slave->StateFunctionPointer_Prev)
	{
		slave->StateFunctionPointer_Prev = slave->StateFunctionPointer;
		(*(slave->StateFunctionPointer))(true, slave);
	}
	else
	{
		(*(slave->StateFunctionPointer))(false, slave);
	}

	return LocalStatus;
}

// returns 0 on success, returns -1 if num of clients exceeds limit(10) 
S32 IEC104Slave_LoadParameters(IEC104Slave slave, BOOL IEC104SlaveEnabled, S32 localIP, U16 localPortTCP, U8 maxNumOfClients, U8 ASDU)
{
#ifdef I104S_TYPE_CHECK
	if (!IEC104Slave_ValidateObject(slave)) { return -1; }         // pointer to invalid object structure
#endif
	STATUS LocalStatus = 0;

	slave->LocalIP = localIP;


	slave->LocalPortTCP = localPortTCP;
	if (maxNumOfClients > I104S_CLIENTSLISTCAPACITY) {
		if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Parameters not reloaded, Maximum Num of clients not valid"); }
		return -1;
	}
	slave->MaxNumOfClients = maxNumOfClients;
	slave->IEC104SlaveEnabled = IEC104SlaveEnabled;
	slave->ASDU = ASDU;

	if (slave->StatusInfoEnabled) { CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Parameters reloaded"); }
	return LocalStatus;
}

