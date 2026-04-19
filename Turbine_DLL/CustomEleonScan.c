
#include <os_main.h>
// AppLib header files
#include <lib_main.h>
// App header files
#include <turbdef.h>
#include <VarMacros.h>
#include <CustomEleonScan.h>


#define MAX_VDB_LENGTH                  40
#define MENU_NAME_LENGTH                20
#define TASK_NAME_LENGTH                 8
#define MAILBOX_NAME_LENGTH              8
#define EVGR_NAME_LENGTH                 8
#define WD_NAME_LENGTH                   8
#define NUMBER_OF_VDB_VARIABLES_IN_TASK  7
#define VDB_NAME_LENGTH                 40

#define INIT_ROUND_REQEST                555



#define OS_MENUGROUPNAME           "os"
#define APP_STATISTIC_MENU_NAME    "M_"APP_ID"AppMainStat"

#define VDB_TIMER_TEMPLATE         "App_"APP_ID"%s_Timer"
#define VDB_INTERVAL_TEMPLATE      "V_"APP_ID"%s_Interval"
#define VDB_INTERVAL_MIN_TEMPLATE  "V_"APP_ID"%s_Interval_Min"
#define VDB_INTERVAL_MAX_TEMPLATE  "V_"APP_ID"%s_Interval_Max"

#define VDB_NUMBEOFCALLS_TEMPLATE  "V_"APP_ID"%s_NumberOfCalls"

#define VDB_CALLTIME_TEMPLATE      "V_"APP_ID"%s_CallTime"
#define VDB_CALLTIME_MIN_TEMPLATE  "V_"APP_ID"%s_CallTime_Min"
#define VDB_CALLTIME_MAX_TEMPLATE  "V_"APP_ID"%s_CallTime_Max"

#define REQ_EVENT_TEMPLATE         "ReqEv_%u"
#define STATE_EVENT_TEMPLATE       "StEv_%u"
#define WD_NAME_TEMPLATE           "AWd_%u"

#define STAT_MENUNAME_TEMPLATE     "M_"APP_ID"_%s"

#define APPSYSLOGCODE       50000
#define APPDEBUGLOGCODE     50000
#define APPEVENTLOGCODE     50000

#define NEW_FUNC 1
#define OLD_FUNC 0

typedef enum
{
   TASK_TYPE_CYCLIC,
   TASK_TYPE_EVENT,
   TASK_TYPE_FREEWHEELING,
   TASK_TYPE_NO_SCAN,
} TASK_TYPE;

typedef  struct FuncStruct* pFuncStructType;
typedef  struct TaskStruct* pTaskStructType;


typedef struct FuncStruct
{
   pTaskStructType   pAppTask;                   // pointer to task structure
   U16               SeqN_InAppTaskList;         // sequence number in task call
   U32               f_call_time;
   U32               f_call_time_max;
   U32               f_call_time_min;
   U8                req_state;
   U8                cur_state;
   U16               init_seq_number;
   U16               menu_seq_number;

   //Call Function Style
   STATUS(*OldObjFunc1)(U8 Arg1);
   STATUS(*OldObjFunc2)(U8 Arg1,     OS_MEMORY_POOL* Arg2);
   STATUS(*OldObjFunc3)(U8 Arg1,     OS_MEMORY_POOL* Arg2, U32* Arg3);
   STATUS(*NewObjeFunc)(U8 ReqState, U8* DoneSate, U32 Interval);
   //call function
   STATUS(*call_func)(pFuncStructType pFuctInfo);

   //-------------------------------------------------------------------------------
   // Old structure
   U32               scan_time;                   // scan time > 0  than old style task creation is used
   //void           (*Function)();                // Function pointer
   U32               Argc;                        // Number of parameters
   U8*               Arg1;                        // Request
   OS_MEMORY_POOL*   Arg2;                        // Memory pool
   U32*              Arg3;                        // Other Arguments
   U32*              FunctionCallArg;             // Arguments used to control Object function calls
   U32*              Enable;
} FuncStructType;



typedef struct TaskStruct
{
   char                Name      [ TASK_NAME_LENGTH ];  // Task Name
   U16                 i;                               // index
   TASK_TYPE           Type;                          // Task Type
   U8                  Sync;                          // Is Task Sync
   U32                 Interval;                        // Task Interval
   U8                  AppRunPriority;                  // App Task Priority
   //---------------------------------------------------------------
   U32                 WD_Enable;                       // Is watch dog enabled
   UNSIGNED            WD_Timeout;                      // Watch dog timeout
   UNSIGNED            WD_MaxTimeOuts;                  // Watch dog number of timeou
   U32                 WD_SafetyChain;                  // Watch dog safety chain options
   U32                 WD_WpLine;                       // Watch dog WP-Line options
   U32                 WD_Reboot;                       // Watch dog reboot options
   U32                 WD_Statuscode;                   // Watch dog statuscode
   char                AppWD_Name [ WD_NAME_LENGTH ];
   U32                 AppWD;
   //---------------------------------------------------------------
   pFuncStructType     pFirstFunc;                 // Pointer to first function
   U32                 NumberOfFunc;               // Number of functions
   //---------------------------------------------------------------
   U8                  inited;
   time_t              curr_time;
   time_t              prev_time;
   U32                 interval_ms;
   U32                 interval_max_ms;
   U32                 interval_min_ms;
   U32                 number_of_calls;
   U32                 call_time;
   U32                 call_time_max;
   U32                 call_time_min;
   time_t              time_point1;
   time_t              time_point2;
   //---------------------------------------------------------------
   U8                  req_state;
   U8                  cur_state_old;
   U8                  cur_state;
   //---------------------------------------------------------------
   OS_TASK             Tsk_AppTasks;
   struct task_info    TskInf_AppTasks;
   //---------------------------------------------------------------
   OS_TIMER            OS_AppEventTimer;
   struct os_db_timer  AppEventTimer;
   //---------------------------------------------------------------
   char                MlBx_EvName                [ MAILBOX_NAME_LENGTH ];
   OS_MAILBOX          MlBox_Ev;
   struct mailbox_info MlBxInf_Ev;
   //---------------------------------------------------------------
   char                MlBx_CurStateName          [ MAILBOX_NAME_LENGTH ];
   OS_MAILBOX          MlBox_CurState;
   struct mailbox_info MlBxInf_CurState;
   //---------------------------------------------------------------
   char                AppEv_VDB_name             [ VDB_NAME_LENGTH     ];
   varid_t             AppEv_VDB_id;
   SUBSCRIPTION        Sbs_AppEv;
   //---------------------------------------------------------------
   char                MenuName                   [ MENU_NAME_LENGTH    ];
   struct menu_struct  TaskStatMenu;
   struct line_struct  LinkToTaskStatMenu;
   struct line_struct  LinkToAppStatMenu          [ NUMBER_OF_VDB_VARIABLES_IN_TASK + 1 ];
   //---------------------------------------------------------------
   char                VDB_interval_name          [ VDB_NAME_LENGTH ];
   char                VDB_interval_min_name      [ VDB_NAME_LENGTH ];
   char                VDB_interval_max_name      [ VDB_NAME_LENGTH ];
   char                VDB_call_num_name          [ VDB_NAME_LENGTH ];
   char                VDB_call_time_name         [ VDB_NAME_LENGTH ];
   char                VDB_call_time_min_name     [ VDB_NAME_LENGTH ];
   char                VDB_call_time_max_name     [ VDB_NAME_LENGTH ];
   //----------------------------------
   varid_t             interval_id;
   varid_t             interval_min_id;
   varid_t             interval_max_id;
   varid_t             call_num_id;
   varid_t             call_time_id;
   varid_t             call_time_max_id;
   varid_t             call_time_min_id;
   //----------------------------------
   struct os_db_local  VDB_interval;
   struct os_db_local  VDB_interval_min;
   struct os_db_local  VDB_interval_max;
   struct os_db_local  VDB_call_num;
   struct os_db_local  VDB_call_time;
   struct os_db_local  VDB_call_time_min;
   struct os_db_local  VDB_call_time_max;
   
   	//---------------------------------- additional by eleon
	int timeUntilNextCall;
} TaskStructType;

static TaskStructType AppTasksList [ MAX_TASKS ];
static FuncStructType FuncList     [ MAX_FUCT  ];

static U16 task_counter  = 0;
static U16 funct_counter = 0;



//Find pointer to Task
static S16 find_the_task(char* TaskName)
{
	U16 i;
	for (i = 0; i < task_counter; ++i)
	{
		if (0 == strcmp(AppTasksList[i].Name, TaskName))
		{
			return i;
		}
	}
	return (-1);
}

static S16 find_the_function_by_pointer(void(*Function)())
{
	U16 i;

	for (i = 0; i < funct_counter; ++i)
	{
		if (((void(*)())FuncList[i].OldObjFunc1 == Function)
			|| ((void(*)())FuncList[i].OldObjFunc2 == Function)
			|| ((void(*)())FuncList[i].OldObjFunc3 == Function)
			|| ((void(*)())FuncList[i].NewObjeFunc == Function)
			)
		{
			return i;
		}
	}
	return (-1);
}


static STATUS add_task(char*       TaskName,
	TASK_TYPE   TaskType,
	U8          Priority,
	U32         StackSize,
	char*       EventName,
	U32         Interval,
	U8          WD_Enable,
	U32         WD_Timeout,
	U16         WD_MaxTimeOuts,
	U32         WD_SafetyChain,
	U32         WD_WpLine,
	U32         WD_Reboot,
	U32         WD_Statuscode,
	U8          Is_Sync)
{
	S16 task_idx = find_the_task(TaskName);

	if (0 <= task_idx)  //Task exists
	{
		AppSystemLog(APPSYSLOGCODE, APP_ID": AppTask %s[%d] already exist", TaskName, task_idx);

		return ERR_TASK_EXIST;
	}

	if (MAX_TASKS <= task_counter)  //Max number of tasks are reached
	{
		AppSystemLog(APPSYSLOGCODE, APP_ID": Cann't create AppTask %s[%u]", TaskName, task_counter);
		AppSystemLog(APPSYSLOGCODE, APP_ID": Max number of AppTasks reached");

		return ERR_TO_MANY_TASKS;
	}

	AppTasksList[task_counter].Type = TaskType;
	AppTasksList[task_counter].AppRunPriority = Priority;

	//Task Information
	strncpy(AppTasksList[task_counter].Name, TaskName, TASK_NAME_LENGTH);
	AppTasksList[task_counter].TskInf_AppTasks.object_type = TASK_INFO;
	AppTasksList[task_counter].TskInf_AppTasks.task = &AppTasksList[task_counter].Tsk_AppTasks;
	AppTasksList[task_counter].TskInf_AppTasks.name = AppTasksList[task_counter].Name;
	AppTasksList[task_counter].TskInf_AppTasks.argc = 1;
	AppTasksList[task_counter].TskInf_AppTasks.argv = &AppTasksList[task_counter];
	AppTasksList[task_counter].TskInf_AppTasks.priority = (U8)APP_INIT_PRIORITY;
	AppTasksList[task_counter].TskInf_AppTasks.time_slice = TIME_SLICE;
	AppTasksList[task_counter].TskInf_AppTasks.preempt = OS_PREEMPT;

	if (!StackSize) { AppTasksList[task_counter].TskInf_AppTasks.stack_size = DEFAULT_STACK_SIZE; }
	else { AppTasksList[task_counter].TskInf_AppTasks.stack_size = StackSize; }

	if (TASK_TYPE_CYCLIC == TaskType)
	{
		AppTasksList[task_counter].Interval = Interval;
		AppTasksList[task_counter].WD_Enable = WD_Enable;
		AppTasksList[task_counter].WD_Timeout = (UNSIGNED)WD_Timeout;
		AppTasksList[task_counter].WD_MaxTimeOuts = (UNSIGNED)WD_MaxTimeOuts;
		AppTasksList[task_counter].WD_SafetyChain = WD_SafetyChain;
		AppTasksList[task_counter].WD_WpLine = WD_WpLine;
		AppTasksList[task_counter].WD_Reboot = WD_Reboot;
		AppTasksList[task_counter].WD_Statuscode = WD_Statuscode;

		AppTasksList[task_counter].timeUntilNextCall = 0;
		//AppTasksList[task_counter].TskInf_AppTasks.task_entry = app_task_event_or_cyclic;
	}
	else if (TASK_TYPE_EVENT == TaskType)
	{
		strncpy(AppTasksList[task_counter].AppEv_VDB_name, EventName, MAX_VDB_LENGTH);
		AppTasksList[task_counter].Interval = 0;
		AppTasksList[task_counter].WD_Enable = WD_Enable;
		AppTasksList[task_counter].WD_Timeout = (UNSIGNED)WD_Timeout;
		AppTasksList[task_counter].WD_MaxTimeOuts = (UNSIGNED)WD_MaxTimeOuts;
		AppTasksList[task_counter].WD_SafetyChain = WD_SafetyChain;
		AppTasksList[task_counter].WD_WpLine = WD_WpLine;
		AppTasksList[task_counter].WD_Reboot = WD_Reboot;
		AppTasksList[task_counter].WD_Statuscode = WD_Statuscode;
		//AppTasksList[task_counter].TskInf_AppTasks.task_entry = app_task_event_or_cyclic;
	}
	else if (TASK_TYPE_FREEWHEELING == TaskType)
	{
		AppTasksList[task_counter].Interval = 1;
		AppTasksList[task_counter].WD_Enable = WD_Enable;
		AppTasksList[task_counter].WD_Timeout = (UNSIGNED)WD_Timeout;
		AppTasksList[task_counter].WD_MaxTimeOuts = (UNSIGNED)WD_MaxTimeOuts;
		AppTasksList[task_counter].WD_SafetyChain = WD_SafetyChain;
		AppTasksList[task_counter].WD_WpLine = WD_WpLine;
		AppTasksList[task_counter].WD_Reboot = WD_Reboot;
		AppTasksList[task_counter].WD_Statuscode = WD_Statuscode;
		//AppTasksList[task_counter].TskInf_AppTasks.task_entry = app_task_free_wheeling;
	}
	else if (TASK_TYPE_NO_SCAN == TaskType)
	{
		AppTasksList[task_counter].Interval = 0;
		AppTasksList[task_counter].WD_Enable = 0;
		AppTasksList[task_counter].WD_Timeout = 0;
		AppTasksList[task_counter].WD_MaxTimeOuts = 0;
		AppTasksList[task_counter].WD_SafetyChain = 0;
		AppTasksList[task_counter].WD_WpLine = 0;
		AppTasksList[task_counter].WD_Reboot = 0;
		AppTasksList[task_counter].WD_Statuscode = 0;
		//AppTasksList[task_counter].TskInf_AppTasks.task_entry = app_task_no_scan;
	}
	else
	{
		AppSystemLog(APPSYSLOGCODE, APP_ID": AppTask %s[%u] unknown task type", TaskName, task_counter);
		return ERR_UNKNOWN_TASK_TYPE;
	}
	task_counter++;

	return OS_SUCCESS;
}


static STATUS AddNoScanCustomTask(char* TaskName, U8    Priority) {
	int LocalStatus = 0;

	return  AddCyclicCustomTask(TaskName, Priority, 0);
}

STATUS AddCyclicTask(char* TaskName,
	U8    Priority,
	U32   StackSize,
	U32   Interval,
	U8    WD_Enable,
	U32   WD_Timeout,
	U16   WD_MaxTimeOuts,
	U32   WD_SafetyChain,
	U32   WD_WpLine,
	U32   WD_Reboot,
	U32   WD_Statuscode,
	U8    IsSync
)
{
	return add_task(TaskName, TASK_TYPE_CYCLIC, Priority, StackSize,
		NULL, Interval, WD_Enable, WD_Timeout, WD_MaxTimeOuts, WD_SafetyChain, WD_WpLine, WD_Reboot, WD_Statuscode, IsSync);
}



STATUS call_old_one_arg_func(pFuncStructType pFuctInfo)
{
	if (APP_RUN == pFuctInfo->req_state)
	{
		//run state
		return (*pFuctInfo->OldObjFunc1)(pFuctInfo->req_state);
	}
	//In Init and shut down states call object only if state is not done.
	else if (pFuctInfo->req_state > pFuctInfo->cur_state)
	{
		//Emulation of init rounds for older objects
		if (APP_INIT5 == pFuctInfo->req_state)   //5 is the last Init round for old objects
		{
			pFuctInfo->cur_state = AS_LAST_BEFORE_RUN;
		}
		else
		{
			pFuctInfo->cur_state = pFuctInfo->req_state;
		}

		return (*pFuctInfo->OldObjFunc1)(pFuctInfo->req_state);
	}
	else
	{
		//Init or shutdown state is done: object call is skipped
		return OS_SUCCESS;
	}
}

//_____________________________________________________________________________________________________
STATUS call_old_two_arg_func(pFuncStructType pFuctInfo)   //support only 5 init rounds
{
	if (APP_RUN == pFuctInfo->req_state)
	{
		//run state
		return (*pFuctInfo->OldObjFunc2)(pFuctInfo->req_state, pFuctInfo->Arg2);
	}
	//In init and shut down states call object only if state is not finished.
	else if (pFuctInfo->req_state > pFuctInfo->cur_state)
	{
		//Emulation of init rounds for older objects
		if (APP_INIT5 == pFuctInfo->req_state)   //5 is the last Init round for old objects
		{
			pFuctInfo->cur_state = AS_LAST_BEFORE_RUN;
		}
		else
		{
			pFuctInfo->cur_state = pFuctInfo->req_state;
		}

		return (*pFuctInfo->OldObjFunc2)(pFuctInfo->req_state, pFuctInfo->Arg2);
	}
	else
	{
		//Init or shutdown state is done: object call is skipped.
		return OS_SUCCESS;
	}
}

//_____________________________________________________________________________________________________
//Call function
STATUS call_old_three_arg_func(pFuncStructType pFuctInfo)
{
	if (APP_RUN == pFuctInfo->req_state)
	{
		//run state
		return (*pFuctInfo->OldObjFunc3)(pFuctInfo->req_state, pFuctInfo->Arg2, pFuctInfo->Arg3);
	}
	//In Init and shut down states call object only if state is not done.
	else if (pFuctInfo->req_state > pFuctInfo->cur_state)
	{
		//Emulation of init rounds for older objects
		if (APP_INIT5 == pFuctInfo->req_state)   //5 is the last Init round for old objects
		{
			pFuctInfo->cur_state = AS_LAST_BEFORE_RUN;
		}
		else
		{
			pFuctInfo->cur_state = pFuctInfo->req_state;
		}

		return (*pFuctInfo->OldObjFunc3)(pFuctInfo->req_state, pFuctInfo->Arg2, pFuctInfo->Arg3);
	}
	else
	{
		//Init or shutdown state is done: object call is skipped
		return OS_SUCCESS;
	}
}

//_____________________________________________________________________________________________________
//Call function
static STATUS call_func(pFuncStructType pFuctInfo)
{
	if (APP_RUN == pFuctInfo->req_state)
	{
		return (*pFuctInfo->NewObjeFunc)(pFuctInfo->req_state, &pFuctInfo->cur_state, pFuctInfo->pAppTask->interval_ms);
	}
	else if (pFuctInfo->req_state > pFuctInfo->cur_state)
	{
		//call object only if state is not done
		return (*pFuctInfo->NewObjeFunc)(pFuctInfo->req_state, &pFuctInfo->cur_state, pFuctInfo->pAppTask->interval_ms);
	}
	else
	{
		//don't call object if state is done
		return OS_SUCCESS;
	}
}




static STATUS add_function_call(char* TaskName, U8 is_new, void(*Function)(), U8* Arg1, OS_MEMORY_POOL* Arg2, U32* Arg3, U32* Enable)
{

	if (MAX_FUCT <= funct_counter)
	{
		AppSystemLog(APPSYSLOGCODE, APP_ID": Cann't add function call [%u]", funct_counter);
		AppSystemLog(APPSYSLOGCODE, APP_ID": Max number of function calls reached");

		return ERR_TO_MANY_FUNCTIONS;
	}

	S16 task_idx = find_the_task(TaskName);

	if ((0 > task_idx) || (MAX_TASKS <= task_idx))
	{
		AppSystemLog(APPSYSLOGCODE, APP_ID": Cann't assign new function[%u]", funct_counter);
		AppSystemLog(APPSYSLOGCODE, APP_ID": AppTask %s[%d] not found ", TaskName, task_idx);

		return ERR_TASK_NOT_FOUND;
	}

	//remember the number in task in function list
	FuncList[funct_counter].SeqN_InAppTaskList = AppTasksList[task_idx].NumberOfFunc;
	//increment the counter of assign function calls
	AppTasksList[task_idx].NumberOfFunc++;
	//remember the pointer to task
	FuncList[funct_counter].pAppTask = &AppTasksList[task_idx];

	//enable/disable object execution
	FuncList[funct_counter].Enable = Enable;

	//Set init state
	FuncList[funct_counter].req_state = 0;
	FuncList[funct_counter].cur_state = 0;

	if (is_new)
	{
		FuncList[funct_counter].call_func = call_func;
		FuncList[funct_counter].NewObjeFunc = ((STATUS(*)(U8 req_state, U8 *done_state, U32 interval))Function);
	}
	else
	{
		if (Arg1 != NULL)
		{
			FuncList[funct_counter].call_func = call_old_one_arg_func;
			FuncList[funct_counter].Arg1 = Arg1;
			FuncList[funct_counter].OldObjFunc1 = ((STATUS(*)(U8 Arg1))Function);

		}
		if (Arg2 != NULL)
		{
			FuncList[funct_counter].call_func = call_old_two_arg_func;
			FuncList[funct_counter].Arg2 = Arg2;
			FuncList[funct_counter].OldObjFunc2 = ((STATUS(*)(U8 Arg1, OS_MEMORY_POOL *Arg2))Function);

		}
		if (Arg3 != NULL)
		{
			FuncList[funct_counter].call_func = call_old_three_arg_func;
			FuncList[funct_counter].Arg3 = Arg3;
			FuncList[funct_counter].OldObjFunc3 = ((STATUS(*)(U8 Arg1, OS_MEMORY_POOL *Arg2, U32 *Arg3))Function);
		}
	}

	funct_counter++;

	return OS_SUCCESS;
}

//Sort criteria
static int func_init_order(const void* elem1, const void* elem2)
{
	pFuncStructType pFunctCall_1 = (pFuncStructType)elem1;
	pFuncStructType pFunctCall_2 = (pFuncStructType)elem2;

	if (pFunctCall_1->init_seq_number > pFunctCall_2->init_seq_number)
	{
		return 1;
	}
	else if (pFunctCall_1->init_seq_number < pFunctCall_2->init_seq_number)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

//_____________________________________________________________________________________________________
//Sort criteria
static int func_menu_order(const void* elem1, const void* elem2)
{
	pFuncStructType pFunctCall_1 = (pFuncStructType)elem1;
	pFuncStructType pFunctCall_2 = (pFuncStructType)elem2;

	if (pFunctCall_1->menu_seq_number > pFunctCall_2->menu_seq_number)
	{
		return 1;
	}
	else if (pFunctCall_1->menu_seq_number < pFunctCall_2->menu_seq_number)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


STATUS AddNoScanTask(char* TaskName, U8 Priority, U32 StackSize)
{
	return add_task(TaskName, TASK_TYPE_NO_SCAN, Priority, StackSize, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 1);
}

STATUS AddFunctionCall(char* TaskName, STATUS(*Function)(U8 req_state, U8* done_state, U32 interval), U32* Enable)
{
	return add_function_call(TaskName, NEW_FUNC, (void(*)())(Function), NULL, NULL, NULL, Enable);
}


STATUS AddBackCompFunctionCall(char* TaskName, void(*Function)(), U8* Arg1, OS_MEMORY_POOL* Arg2, U32* Arg3, U32* Enable)
{
	return add_function_call(TaskName, OLD_FUNC, Function, Arg1, Arg2, Arg3, Enable);
}

STATUS Set_Init_Order(void(*Function)(), U16 Order)
{
	S16 funct_idx = find_the_function_by_pointer(Function);

	if (0 <= funct_idx && MAX_FUCT > funct_idx)
	{
		FuncList[funct_idx].init_seq_number = Order;

		return OS_SUCCESS;
	}
	else
	{
		return ERR_FUNC_NOT_FOUND;
	}
}


STATUS Set_Menu_Order(void(*Function)(), U16 Order)
{
	S16 funct_idx = find_the_function_by_pointer(Function);

	if (0 <= funct_idx && MAX_FUCT > funct_idx)
	{
		FuncList[funct_idx].menu_seq_number = Order;

		return OS_SUCCESS;
	}
	else
	{
		return ERR_FUNC_NOT_FOUND;
	}
}

STATUS AppTasks_InitCall(U8 req_state, U8* done_state)
{
	STATUS Status = OS_SUCCESS;

	U8 min_done_state = 255;
	static U8 first_time = 1;

	if (APP_RUN <= req_state)
	{
		return OS_SUCCESS;
	}

	if (first_time)               //sort in initialization order
	{
		first_time = 0;
		qsort((void*)FuncList, funct_counter, sizeof(FuncList[0]), func_init_order);
	}

	if (APP_INIT4 == req_state)   //sort in menu linking order
	{
		first_time = 1;
		qsort((void*)FuncList, funct_counter, sizeof(FuncList[0]), func_menu_order);
	}

	U16 i;
	for (i = 0; i < funct_counter; ++i)
	{
		//printf("app nr %d\n",i);
		if ((NULL != FuncList[i].Enable)
			&& (0 == *FuncList[i].Enable))
		{
			//skip disabled
			continue;
		}
		else
		{
			//call enabled functions
			FuncList[i].req_state = req_state;
			Status = (*(FuncList[i].call_func))(&FuncList[i]);
			if (Status < 0)
			{
				printf("\nObject nr %d initialization failed. (%d)\n\n", i, Status);
			}
			STATUS_LINE_VAR_RETURN_VALUE(Status);

			if (FuncList[i].cur_state < min_done_state)
			{
				min_done_state = FuncList[i].cur_state;
			}
		}
	}

	*done_state = min_done_state;

	return OS_SUCCESS;
}


static STATUS app_funct_call(pTaskStructType pAppTaskInfo)
{
	STATUS Status = OS_SUCCESS;

	U16 i;

	pAppTaskInfo->cur_state = 255;

	if (0 == pAppTaskInfo->NumberOfFunc)
	{
		if (APP_RUN > pAppTaskInfo->req_state)
		{
			pAppTaskInfo->cur_state = AS_LAST_BEFORE_RUN;
		}
		else
		{
			pAppTaskInfo->cur_state = pAppTaskInfo->req_state;
		}
	}


	for (i = 0; i < pAppTaskInfo->NumberOfFunc; ++i) {
		//pAppTaskInfo->time_point2 = OS_GetTimeInMs();

		//-------------------------------------------------------
		if (NULL != (pAppTaskInfo->pFirstFunc + i)->call_func)  //if pointer to function not zero
		{
			if ((NULL != (pAppTaskInfo->pFirstFunc + i)->Enable)
				&& (0 == *(pAppTaskInfo->pFirstFunc + i)->Enable))
			{
				//disabled by configurator
				continue;
			}
			else
			{
				(pAppTaskInfo->pFirstFunc + i)->req_state = pAppTaskInfo->req_state;
				Status = (*(*(pAppTaskInfo->pFirstFunc)[i].call_func))(pAppTaskInfo->pFirstFunc + i);

				STATUS_LINE_VAR_RETURN_VALUE(Status);
			}
		}
		else
		{
			AppSystemLog(APPSYSLOGCODE, APP_ID" Task %s, pointer to Funct[%u] is NULL", pAppTaskInfo->Name, i);
			return -1;
		}

		//remember the lowest state of the attached functions
		if ((pAppTaskInfo->pFirstFunc + i)->cur_state < pAppTaskInfo->cur_state)
		{
			pAppTaskInfo->cur_state = (pAppTaskInfo->pFirstFunc + i)->cur_state;
		}

		//-------------------------------------------------------
		//pAppTaskInfo->pFirstFunc->f_call_time = (U32)(OS_GetTimeInMs() - pAppTaskInfo->time_point2);

		//if (pAppTaskInfo->pFirstFunc->f_call_time > pAppTaskInfo->pFirstFunc->f_call_time_max)
	//	{
		//	pAppTaskInfo->pFirstFunc->f_call_time_max = pAppTaskInfo->pFirstFunc->f_call_time;
	//	}

	//	if (pAppTaskInfo->pFirstFunc->f_call_time < pAppTaskInfo->pFirstFunc->f_call_time_min)
		//{
			//pAppTaskInfo->pFirstFunc->f_call_time_min = pAppTaskInfo->pFirstFunc->f_call_time;
	//	}
	}
	return Status;
}

static int task_sort_creteria(const void* elem1, const void* elem2)
{
	pFuncStructType pFunctCall_1 = (pFuncStructType)elem1;
	pFuncStructType pFunctCall_2 = (pFuncStructType)elem2;

	if (pFunctCall_1->pAppTask > pFunctCall_2->pAppTask)
	{
		return 1;
	}
	else if (pFunctCall_1->pAppTask < pFunctCall_2->pAppTask)
	{
		return -1;
	}
	else
	{
		if (pFunctCall_1->SeqN_InAppTaskList > pFunctCall_2->SeqN_InAppTaskList)
		{
			return 1;
		}
		else if (pFunctCall_1->SeqN_InAppTaskList < pFunctCall_2->SeqN_InAppTaskList)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

STATUS AppTasks_Create(OS_MEMORY_POOL* MemPool)
{
	STATUS Status = OS_SUCCESS;
	U16 i;

	//Sort FunctionList by pointer to tasks and sequence number in task application list
	qsort((void*)FuncList, funct_counter, sizeof(FuncList[0]), task_sort_creteria);

	//Each task must point to the first function call in application task list
	for (i = 0; i < funct_counter; ++i)
	{
		if (0 == FuncList[i].SeqN_InAppTaskList)
		{
			FuncList[i].pAppTask->pFirstFunc = &FuncList[i];

			FuncList[i].pAppTask->req_state = APP_RUN;

		}
	}

	return Status;
}



STATUS CustomEleonScan_20msCall() {
	int Status = 0;
	int i;
	for (i = 0; i < task_counter; i++) {
		if (AppTasksList[i].Type == TASK_TYPE_CYCLIC) {

			AppTasksList[i].timeUntilNextCall -= 20;	// in DLL simulation each call makes like 20 ms has passed
			if (AppTasksList[i].timeUntilNextCall <= 0) {
				AppTasksList[i].timeUntilNextCall = AppTasksList[i].Interval;
				Status = app_funct_call(&AppTasksList[i]);
				STATUS_LINE_VAR_RETURN(Status);
			}
		}

	}

	STATUS_LINE_VAR_RETURN(Status);

	return Status;
}
