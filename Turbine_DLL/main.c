#include <stdlib.h>
#include <stdio.h>

//#define MITALIB_DEBUG_FILE_OUTPUT		// this must be defined in file "Mita.c"
//#define MITALIB_DEBUG_CONSOLE_OUTPUT	// this must be defined in file "Mita.c"
//#define ELEONMITALIBDEBUG //use this to debug mita os functions

#define ELEON_DLL_EXPORTS
#include <DLL/DLL_InOut.h>
#include <time.h>
#include <Mita.h>
#include <Parameter_Import.h>

#include <MitaOSApps_main.h>

#define STRINGIPTOINTEGER(a,b,c,d) ( a | (b << 8 )| (c << 16) | (d << 24))
#define LOCALIPADDRESS STRINGIPTOINTEGER(127,0,0,1)  //use commas
//#define LOCALIPADDRESS STRINGIPTOINTEGER(192,168,1,135)  //use commas



static struct os_db_local LocalVars[] =
{
	VAR_ELEMENT_LOCAL("V_OS_APP1_RequestId",TYPE_U8,     PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_ADMINISTRATOR,      SCALE_NONE,   0,     UNIT_NONE,          0,   AS_RUN,         0,         1,         NULL,  NOLOG_ENABLE),
	VAR_ELEMENT_LOCAL("V_OS_APP1_StateID",  TYPE_U8,     PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_ADMINISTRATOR,      SCALE_NONE,   0,     UNIT_NONE,          0,   APP_INIT1,         0,         1,         NULL,  NOLOG_ENABLE)
};

static struct application_arguments Argv =
{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	&LocalVars[0],
	&LocalVars[1],
};

typedef enum
{
	DLL_IF_NA = 0,
	DLL_IF_ELEON_API = 1,
	DLL_IF_BLADED_DISCON = 2,
	DLL_IF_BLADED_API = 3
}DllInterface_t;

static OS_TASK OS_APP1_Task;
unsigned char MenuServer_enabled = false;
static DllInterface_t dll_interface = DLL_IF_NA;



int InitializeApps()
{
	int LocalStatus = 0;
	if (MenuServer_enabled) {
		LocalStatus = MitaMenuMenuInitialize(LOCALIPADDRESS);
		printf("Menu server enabled\n");
	}
	LocalStatus = MitaOSApps_Initialize();
	if (LocalStatus != 90) {
		return LocalStatus;
	}
	LocalStatus = 0;
	LocalStatus = app_mainApplication(NULL, &Argv);
	if (LocalStatus < 0) {
		return LocalStatus;
	}
	return 0;
}



int MainCall() {
	STATUS LocalStatus=0;
	static BOOL firstentry = true;

	
	if (firstentry)
	{
		printf("System starting...\n");
		firstentry = false;
		int LocalStatus = 0;

		SetMemPool(1);    // some functions check if mem pool exists
		size_t ErrorEntry;
		LocalStatus = OS_VarDB_CreateLocals(LocalVars, sizeof(LocalVars) / sizeof(LocalVars[0]), &ErrorEntry, AppLocalParameterPosition());
		if (LocalStatus != 0) {
			return LocalStatus - 1000;
		}
		LocalStatus = MITALIB_Init(LOCALIPADDRESS);
		if (LocalStatus != 0) {
			return LocalStatus - 2000;
		}
		
		OS_internal_AddBackupFileNames((varid_t)&LocalVars[1], "I:\\Backup\\P12608\\Parameters\\Exports.App\0", "I:\\Backup\\P12608\\Parameters\\Locals.App\0", "I:\\Backup\\P12608\\General_Backups\\BA190709112344.App\0");
		
		LocalStatus = InitializeApps();
		if (LocalStatus != 0) {
			return LocalStatus - 3000;
		}

		LocalStatus = DLL_Initialize_Variables();
		if (LocalStatus != 0) {
			return LocalStatus - 4000;
		}

		printf("Loading parameter file... ");
		char param_file_path[512];
		if (root_folder[0] == '\0') {  // when no root folder set then assume parameter file is in the same currently active folder
			sprintf(param_file_path, "DLL_parameters.par");
		}
		else {
			sprintf(param_file_path, "%s\\DLL_parameters.par", root_folder);
		}
		int result = Import_Parameters_File(param_file_path, 1000);
		if (result < 0) {
			printf("Failed\n");
			return LocalStatus - 5000;
		}

		// force to reload updated parameters in application
		BOOL value_BOOL = true;
		OS_VarDB_UpdateVariableByName("V_GEN_Load_Parameters", &value_BOOL, sizeof(value_BOOL));
		OS_VarDB_UpdateVariableByName("V_CNV_Load_Parameters", &value_BOOL, sizeof(value_BOOL));
		OS_VarDB_UpdateVariableByName("V_PAT_LoadParameters", &value_BOOL, sizeof(value_BOOL));
		OS_VarDB_UpdateVariableByName("V_PM_LoadParameters", &value_BOOL, sizeof(value_BOOL));

		printf("%d parameters loaded\n", result);

		printf("System started\n");

		return LocalStatus;
	}

	LocalStatus = DLL_UpdateINPUT();
	if (LocalStatus < 0) {
		return LocalStatus;
	}
	if (MenuServer_enabled) {
		MitaMenuMenu_ctrl();
	}
	LocalStatus = MitaOSApps_20msCall();
	if (LocalStatus < 0) {
		return LocalStatus;
	}
	LocalStatus = mainApplication20msCall();
	if (LocalStatus < 0) {
		return LocalStatus;
	}
	LocalStatus = DLL_UpdateOUTPUT();
	if (LocalStatus < 0) {
		return LocalStatus;
	}
	
	return 0;
}



int main()
{
	STATUS LocalStatus;
	clock_t current_time;
	clock_t nextCall_time;

	MenuServer_enabled = true;
	LocalStatus = MainCall();
	if (LocalStatus < 0)
	{
		printf("ERROR - MainCall() returned: %d\n", LocalStatus);
		printf("\npress ENTER to exit");
		getchar();

		return 0;
	}

	current_time = clock();
	nextCall_time = current_time + 20;

	while (true)
	{
		current_time = clock();
		if (current_time >= nextCall_time)
		{
			//printf("%d\n", current_time);
			nextCall_time = current_time + 20;
			LocalStatus = MainCall();
			if (LocalStatus < 0)
			{
				printf("ERROR - MainCall() returned: %d\n", LocalStatus);
				break;
			}
			
			long reserve_time = nextCall_time - clock();
			if (reserve_time > 0)
			{
				Sleep(reserve_time);
			}
		}
	}

	printf("\npress ENTER to exit");
	getchar();

	return 0;
}



