#include <MitaOSApps_main.h>
#include <VarMacros.h>


#define APP_ID "0"
#include <StatusCodes_Eleon.h>


#define APP_CAPTION        N_("SYSTEM MENU")
#define APP_RETURN_CAPTION N_("SYSTEM MENU")
#define APP_MENU_NAME      "M_"APP_ID"AppMain"
#define APP_GROUP_NAME     "G_"APP_ID"App"

//----------------------------------------------------------------------------------------------------------------------
//                                APPLICATION MAIN MENU
//----------------------------------------------------------------------------------------------------------------------
static struct line_struct LinkToLocalMenu[] =          //Menu line and link to local menu
{
   MENU_ELEMENT_LINE_LINK(APP_CAPTION,              PASSWORD_LEVEL_UNLOGGED_IN, APP_MENU_NAME, APP_GROUP_NAME),
};

static struct menu_struct AppMenu[] =                                                           // Local menu
{
   MENU_ELEMENT_MENU_TEXT(APP_MENU_NAME,  PASSWORD_LEVEL_UNLOGGED_IN),
};

static struct line_struct AppMenuLines[] =                                                      // Menu lines
{
   MENU_ELEMENT_LINE_LINK(APP_RETURN_CAPTION, PASSWORD_LEVEL_UNLOGGED_IN,  "main", "os"),
};

static struct menu_group_struct AppGroup[1];                                                    // Memory reservation


void delay(unsigned int milliseconds) {

	clock_t start = clock();

	while ((clock() - start) * 1000 / CLOCKS_PER_SEC < (int)milliseconds) {
		OS_Sleep(10000);
	}
}


static STATUS AppMenuInit(void)
{
	STATUS Status;

	Status = OS_CreateMenuGroup(AppGroup, APP_GROUP_NAME);   STATUS_LINE_VAR_RETURN_VALUE(Status);
	Status = OS_CreateMenus(APP_GROUP_NAME, ELEMENT(AppMenu));   STATUS_LINE_VAR_RETURN_VALUE(Status);
	Status = OS_AddLines("os", "main", ELEMENT(LinkToLocalMenu));   STATUS_LINE_VAR_RETURN_VALUE(Status);
	Status = OS_AddLines(APP_GROUP_NAME, APP_MENU_NAME, ELEMENT(AppMenuLines));   STATUS_LINE_VAR_RETURN_VALUE(Status);

	return OS_SUCCESS;
}



U8 GetNewAppState(U8 App_State) {
	switch (App_State)
	{
	case APP_INIT1_DONE:
		return APP_INIT2;
	case APP_INIT2_DONE:
		return APP_INIT3;
	case APP_INIT3_DONE:
		return APP_INIT4;
	case APP_INIT4_DONE:
		return APP_INIT5;
	case APP_INIT5_DONE:
		return APP_RUN;
	case APP_RUN:
		return APP_RUN;
	default:
		return 0;
	}
}

BOOL IsAppAllowedToRun(U8 App_State)
{
	switch (App_State)
	{
	case APP_INIT1:
	case APP_INIT2:
	case APP_INIT3:
	case APP_INIT4:
	case APP_INIT5:
	case APP_RUN:
		return true;
	default:
		return false;
	}

}


U8 RunAPP(INT(*Function)(), U32 interval, U8* State) {
	U8 doneState = 0;
	if (IsAppAllowedToRun(*State))
	{
		*State = Function(*State, &doneState, interval);
		if (*State == OS_SUCCESS) {
			*State = GetNewAppState(doneState);

		}
		else {
			*State = 0;
		}
	}
	else
	{
		return -1;
	}

	return doneState;
}



U8 StatusCodesState = APP_INIT1;

int RunApps() {
	STATUS LocalState = 0;
	int minState = 255;
	
	LocalState = RunAPP(StatusCodes_Eleon, 20, &StatusCodesState);
	if (LocalState < minState) { minState = LocalState; }
	return LocalState;
}


static void runOSAppsInterval()
{
	U32 interval = 20;
	time_t rawtime;

	struct tm * timeinfo;

	while (true)
	{

		RunApps(); // call for menu to work 20ms
		delay(interval);
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		//printf("Current local time and date: %s", asctime(timeinfo));
	}
}

static OS_TASK OS_mainTask;

//int MitaOSApps_Init() {
//	STATUS LocalStatus;
//	AppMenuInit();
//	while (true)
//	{
//		LocalStatus = RunApps();
//		if (LocalStatus == 90) {
//			LocalStatus = OS_module_task_create(&OS_mainTask, "OS_mainT", runOSAppsInterval, 0, 0, 0x10000, 15, 0, OS_PREEMPT, OS_START, GetMemPool());
//			return LocalStatus;
//		}
//	}
//	return 0;
//}

int MitaOSApps_Initialize() {
	STATUS LocalStatus;
	AppMenuInit();
	while (true)
	{
		LocalStatus = RunApps();
		if (LocalStatus == 90) {
			return LocalStatus;
		}
	}
	return -1;

}

int MitaOSApps_20msCall() {
	int LocalStatus = 0;
	LocalStatus = RunApps();
		return LocalStatus;
}



#undef APP_ID