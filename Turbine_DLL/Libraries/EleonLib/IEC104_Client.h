//*****************************PEPTOOL Header Start******************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_IEC104_CLIENT_H
#define FILE_IEC104_CLIENT_H

#include <lib_main.h>
#include <IEC104_Database.h>
#include <CustomLog.h>



typedef struct IEC104_Client* IEC104Client;


typedef struct IEC104Client_Info
{
    U32 Type;           // for object validation - value must be "123456"
	char StatusTxt[31];
	char LocalIPString[16];
	char ServerIPString[16];
	U16 ServerPortTCP;
	U8 ASDU;
	U16 ReceivedCounter;
	U16 SentCounter;
	CustomLog InterfaceEventLog;
}IEC104Client_Info;

// returns Null if failed
IEC104Client IEC104Client_New(char* /*varName*/, U32 /*scantime*/, S32 /*localIP*/);
// returns -1 if pointer is to invalid object struct
S32 IEC104Client_Control(IEC104Client /*client*/);
// returns 0 on success
S32 IEC104Client_LoadParameters(IEC104Client /*client*/, BOOL /*Enable*/, S32 /*localIP*/, const char* /*serverIP*/, U16 /*serverPortTCP*/, U8 /*ASDU*/);
// returns -1 if database  pointer is to to invalid object structure
S32 IEC104Client_SetDatabase(IEC104Client /*client*/, IEC104Database /*database*/);
// creates new info struct and returns pointer to it
IEC104Client_Info *IEC104Client_GetInfo(IEC104Client /*client*/, CustomLog /*customLog*/);
// returns 0 on successful send, -1 if not connected
STATUS IEC104Client_ReadValues(IEC104Client /*client*/, const U32* /*ioas*/, U32 /*count*/);
// returns 0 on successful send, -1 if not connected 
STATUS IEC104Client_SendValues(IEC104Client /*client*/, const U32* /*ioas*/, U32 /*count*/);
// returns 0 on success
STATUS IEC104Client_StartDT(IEC104Client /*client*/);
// returns 0 on success
STATUS IEC104Client_StopDT(IEC104Client /*client*/);
void IEC104Client_SendGeneralInterrogation(IEC104Client /*client*/);
void IEC104Client_EnableDebugPrintRawFrames(IEC104Client /*client*/);
void IEC104Client_DisableDebugPrintRawFrames(IEC104Client /*client*/);
void IEC104Client_EnableDebugPrintInfo(IEC104Client /*client*/);
void IEC104Client_DisableDebugPrintInfo(IEC104Client /*client*/);

#endif
