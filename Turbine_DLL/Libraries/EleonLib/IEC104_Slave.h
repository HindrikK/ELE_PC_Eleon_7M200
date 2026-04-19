//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_IEC104_SLAVE_H
#define FILE_IEC104_SLAVE_H

#include <lib_main.h>
#include <CustomLog.h>
#include <List.h>
#include <IEC104_Database.h>




typedef struct IEC104_Slave *IEC104Slave;

struct IEC104SlaveClientStatus
{
	char ClientIp[16];
	U16 Received;
	U16 Sent;
	U16 srcPortTCP;
};

struct IEC104SlaveStatusInfo
{
	U8 Type;
	char StatusTxt[31];
	char LocalIPString[16];
	CustomLog InterfaceEventLog;
	U8 NumOfClients;
	struct IEC104SlaveClientStatus Clients[10];
};

typedef struct IEC104SlaveStatusInfo * IEC104Slave_StatusInfo;


//Returns Null if failed
IEC104Slave IEC104Slave_New(char* /*varName*/, U32 /*scantime*/, S32 /*localIP*/, const char * /*ParamID*/);

// returns -1 if pointer is to invalid object struct
S32 IEC104Slave_Control(IEC104Slave /*slave*/);

// returns 0 on success
// returns -1 if num of clients exceeds limit(10)
S32 IEC104Slave_LoadParameters(IEC104Slave /*slave*/, BOOL /*IEC104SlaveEnabled*/, S32 /*localIP*/, U16 /*localPortTCP*/, U8 /*maxNumOfClients*/, U8 /*ASDU*/);

//returns -1 if database  pointer points to invalid object structure
S32 IEC104Slave_SetDatabase(IEC104Slave /*slave*/, IEC104Database /*database*/);

//OPTIONAL for external use; set Status and Log structures for IEC104S to start getting status data and logs externally
//should be called immediately after "IEC104Slave_New()" when Status and Log data wanted
//retuns: 0-success; -1-invalid Slave; -2-invalid StatusInfo; -3-CustomLog NULL
S32 IEC104Slave_EnableStatusData(IEC104Slave/*slave*/, IEC104Slave_StatusInfo/*statusInfo*/, CustomLog/*customLog*/);

// returns -1 if pointer is to invalid object struct
// returns -2 if index exceeds max num of interrogationgroups(13)
S32 IEC104Slave_AddToInterrogationGroup0(IEC104Slave /*slave*/, U8 /*type*/, int /*index*/);

S32 IEC104Slave_StartCyclic(IEC104Slave /*slave*/, U32 /*period*/);

S32 IEC104Slave_StopCyclic(IEC104Slave /*slave*/);

S32 IEC104Slave_StartUpdatedCyclic(IEC104Slave /*slave*/, U32 /*period*/);

S32 IEC104Slave_StopUpdatedCyclic(IEC104Slave /*slave*/);

#endif
