#ifndef FILE_MENU_SERVER_H
#define FILE_MENU_SERVER_H


#include <lib_main.h>
#include <CustomLog.h>
#include <List.h>


typedef struct Menu_Server *MenuServer;



struct MenuServerClientStatus
{
	char ClientIp[16];
	U16 Received;
	U16 Sent;
	U16 srcPortTCP;
};

struct MenuServerStatusInfo
{
	U8 Type;        // MUST initialize to value 139; this variable helps to validate the structure
	char StatusTxt[31];
	char LocalIPString[16];
	CustomLog InterfaceEventLog;
	U8 NumOfClients;
	struct MenuServerClientStatus Clients[10];
};

typedef struct MenuServerStatusInfo * MenuServer_StatusInfo;

MenuServer MenuServer_New(struct menu_group_struct *OS_MenuGroups, U32 scantime, S32 localIP);
S32 MenuServer_EnableStatusData(MenuServer server, MenuServer_StatusInfo statusInfo, CustomLog customLog);
S32 MenuServer_StartCyclic(MenuServer server, U32 period);
S32 MenuServer_StopCyclic(MenuServer server);
S32 MenuServer_StartUpdatedCyclic(MenuServer server, U32 period);
S32 MenuServer_StopUpdatedCyclic(MenuServer server);
S32 MenuServer_Control(MenuServer server);
S32 MenuServer_LoadParameters(MenuServer server, BOOL serverEnabled, S32 localIP, U16 localPortTCP, U8 maxNumOfClients);
int OS_Internal_MenuServer_ForceUpdateMenuLines();
#endif