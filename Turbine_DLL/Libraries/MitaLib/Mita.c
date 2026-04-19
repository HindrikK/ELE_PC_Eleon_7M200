#include <Mita.h>
#include <Various_t1_v3.h>
#include <Menu_Server.h>

//#define MITALIB_DEBUG_FILE_OUTPUT
#define MITALIB_DEBUG_CONSOLE_OUTPUT

//following magic numbers arent the same that are in mita os
#define TIMER_MAGIC_NUMBER                     0x05B5A55A

static MenuServer menuserver;

/* Task functions */


HANDLE ghMutex;

char root_folder[512] = "\0";


#pragma region Task //--------------------------------------------------------------//
// Sample custom data structure for threads to use.
// This is passed by void pointer so it can be any data type
// that can be passed using a single void pointer (LPVOID).

typedef struct OS_Task_Argument_Struct_custom
{
	UNSIGNED argc;
	U8 Task_Status;
	VOID *argv;
	void(*task_entry)(UNSIGNED, VOID *);
}OS_Task_args_custom,*OS_Task_Argument_custom;


//own task struct because mita has hidden internals max size is  45 words
typedef struct OS_internal_Task
{
	char name[8];
	void(*task_entry)(UNSIGNED, VOID *);
	DWORD   dwThreadId;
	HANDLE hThread;
	OS_Task_args_custom args;
	OPTION priority;
	OPTION auto_start;
	//UNSIGNED argc;
	//VOID *argv;

}*OS_internal_Task;


#define max_OS_CustomTaskCount 60
static OS_internal_Task OS_Tasks_custom[max_OS_CustomTaskCount];
static int OS_Tasks_custom_count = 0;



DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	//HANDLE hStdout;
	OS_Task_Argument_custom pDataArray;


	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because 
	// it was checked for NULL before the thread was created.

	pDataArray = (OS_Task_Argument_custom)lpParam;
	(*pDataArray->task_entry)(pDataArray->argc, pDataArray->argv);

	((OS_Task_Argument_custom)lpParam)->Task_Status = OS_FINISHED;
	//pDataArray->Task_Status = OS_FINISHED;
	return 0;
}



OPTION OS_Change_Priority(OS_TASK *task, OPTION new_priority)
{

	((OS_internal_Task)task)->priority = new_priority;

	return 0;
}


STATUS OS_Create_Task(OS_TASK *task, CHAR *name, VOID(*task_entry)(UNSIGNED, VOID *), UNSIGNED argc, VOID *argv, VOID *stack_address, UNSIGNED stack_size, OPTION priority, UNSIGNED time_slice, OPTION preempt, OPTION auto_start)
{

	OS_internal_Task taskCustom = ((OS_internal_Task)task);
	int i;
	for (i = 0; i < 8; i++)
	{
		taskCustom->name[i] = *(name + i);
	}
	taskCustom->task_entry = task_entry;
	taskCustom->auto_start = auto_start;
	taskCustom->priority = priority;
	taskCustom->args.argc = argc;
	taskCustom->args.argv = argv;
	taskCustom->args.task_entry = task_entry;
	taskCustom->args.Task_Status = OS_READY;
	
	taskCustom->hThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MyThreadFunction,       // thread function name
		&taskCustom->args,          // argument to thread function 
		0,//CREATE_SUSPENDED,                      // use default creation flags 
		&taskCustom->dwThreadId);   // returns the thread identifier 
	
	//SetThreadPriority(taskCustom->hThread, THREAD_PRIORITY_IDLE);

	//if (auto_start == OS_START) {
		//ResumeThread(taskCustom->hThread);
	//}
	// Check the return value for success.
	// If CreateThread fails, terminate execution. 
	// This will automatically clean up threads and memory. 

	if (taskCustom->hThread == NULL)
	{
		
		ExitProcess(3);
	}

	if (OS_Tasks_custom_count > max_OS_CustomTaskCount) { return -1; }
	OS_Tasks_custom[OS_Tasks_custom_count] = taskCustom;
	OS_Tasks_custom_count++;


	return 0;
}

STATUS OS_Delete_Task(OS_TASK *task)
{
	//TODO should add check to see if task is finished or terminated.
	if (task == NULL) { return OS_INVALID_TASK; }

	OS_internal_Task taskCustom = ((OS_internal_Task)task);
	int result=CloseHandle(taskCustom->hThread);
	if (result == 0) { return OS_INVALID_TASK; }
	if (OS_Tasks_custom_count > 0) {
		OS_Tasks_custom_count--;

	}
	return OS_SUCCESS;
}

STATUS OS_Terminate_Task(OS_TASK *task)
{
	
	if (task == NULL) { return OS_INVALID_TASK; }
	
	OS_internal_Task taskCustom = ((OS_internal_Task)task);
	int result = TerminateThread(taskCustom->hThread, 0);
	if (result != 0) { return OS_SUCCESS; }
	else { return OS_INVALID_DELETE; }
}

#pragma endregion

STATUS OS_Allocate_Memory(OS_MEMORY_POOL *x/*dummy*/, VOID** pointer, UNSIGNED size, UNSIGNED y/*dummy*/)
{
	void* region = malloc(size);
	if (region != NULL)
	{
		*pointer = region;
		return OS_SUCCESS;
	}
	else
	{
		return -1;
	}
}

int OS_Deallocate_Memory(void* region)
{
	free(region);
	return 0;
}

time_t OS_GetTimeInMs(void) {
	time_t rawtime;
	time(&rawtime);
	//SYSTEMTIME time;
	//GetSystemTime(&time);
	//LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;
	//return time_ms;
	return rawtime;
}


/* Function to test if OS and APP is compatible, must be placed as first function */
STATUS OS_ValidateAPI(U16 AppMajor, U16 AppMinor, const char* AppLinkTime, const char* ReleaseTag, const char* FileName) {
	return 0;
}


#pragma region Menu //--------------------------------------------------------------//
static struct menu_group_struct *OS_MenuGroups;
static struct menu_struct AppMenu[] =                                                           // Local menu
{
   MENU_ELEMENT_MENU_TEXT("main",  PASSWORD_LEVEL_UNLOGGED_IN),
};
static struct menu_group_struct AppGroup[1];                                                    // Memory reservation

//static struct menu_group_struct *OS_MenuGroups_for_Debug[32];
//static int OS_MenuGroups_count = 0;
/* New menu functions 2002-03-15 */


STATUS OS_CreateMenuGroup(struct menu_group_struct *newgroup, char *name) 
{
	newgroup->Name = name;
	if (OS_MenuGroups != NULL) {
		OS_MenuGroups->next = newgroup;
		newgroup->prev = OS_MenuGroups;
	}

	OS_MenuGroups = newgroup;
	return 0;

	
}
STATUS OS_CreateMenus(char *groupname, struct menu_struct *newmenu, size_t elements) {
	if (OS_MenuGroups == NULL) { return -1; }
	struct menu_group_struct *menuGroups = OS_MenuGroups;

	size_t i = 0;
	for (; menuGroups != NULL; menuGroups = menuGroups->prev) 
	{
		if (strcmp(menuGroups->Name, groupname) == 0) {
			if (menuGroups->first_menu == NULL)
			{
				menuGroups->first_menu = newmenu;
			}
			else {
				menuGroups->last_menu->next = newmenu;
			}
			
			for (i = 0; i < elements-1; i++)
			{
				
				(newmenu + i)->next = (newmenu + i+1);
				
			}
				menuGroups->last_menu = newmenu + i;

			return OS_SUCCESS;
		}

	}
	return -1;
	
}
STATUS OS_AddLines(char *groupname, char *menuname,struct line_struct *newline, size_t elements) 
{
	//uppergroup,uppermenu, newline, elements
	//"os", "main", ELEMENT(LinkToLocalMenu)
	if (OS_MenuGroups == NULL) { return -1; }
	struct menu_group_struct *menuGroups = OS_MenuGroups;
	struct menu_struct *menus;

	size_t i = 0;
	for (; menuGroups != NULL; menuGroups = menuGroups->prev)
	{
		if (strcmp(menuGroups->Name, groupname) == 0) {
			if (menuGroups->first_menu == NULL) { return -1; }
			menus = menuGroups->first_menu;
			for (; menus != NULL; menus = menus->next)
			{
				if (strcmp(menus->Name, menuname) == 0) {

					menus->Type.Text.NoOfLines += elements;

					if (menus->Type.Text.first_line == NULL)
					{
						menus->Type.Text.first_line = newline;
					}
					else {
						menus->Type.Text.last_line->nextline = newline;						
					}

					for (i = 0; i < elements - 1; i++)
					{

						(newline + i)->nextline = (newline + i + 1);

					}
					menus->Type.Text.last_line = newline + i;
				
					return OS_SUCCESS;
				}
			}
		}

	}
	return -1;
	
}
STATUS OS_CreateButtons(struct buttonlink_struct *buttonlink, struct button_struct *newbutton, size_t elements) 
{
	return 0;
}
static struct line_struct MainMenuLine[] =
{
	MENU_ELEMENT_LINE_TEXT("MAIN MENU", PASSWORD_LEVEL_END_CUSTOMER)
};

static STATUS InitializeMenu()
{
	STATUS Status;

	Status = OS_CreateMenuGroup(AppGroup, "os");   STATUS_LINE_VAR_RETURN_VALUE(Status);
	Status = OS_CreateMenus("os", ELEMENT(AppMenu));   STATUS_LINE_VAR_RETURN_VALUE(Status);
	Status = OS_AddLines("os", "main", ELEMENT(MainMenuLine));   STATUS_LINE_VAR_RETURN_VALUE(Status);

	return Status;
}
#pragma endregion

/* Log functions */
static BOOL ConsoleOutputEnabled = true;

void OS_com_printf(const char * text_format, ...)
{
#if defined(MITALIB_DEBUG_FILE_OUTPUT) || defined(MITALIB_DEBUG_CONSOLE_OUTPUT)
	time_t rawtime;
	time(&rawtime);
	va_list(args);
	va_start(args, text_format);
#endif

#ifdef MITALIB_DEBUG_CONSOLE_OUTPUT
	if (ConsoleOutputEnabled)
	{
		printf("[%d] -  OS_COM:  ", rawtime);
		vprintf(text_format, args);
	}
#endif

#ifdef MITALIB_DEBUG_FILE_OUTPUT
	int fp = OS_Open("OS_Com_Log.txt", PO_APPEND, 0);
	if (fp < 0) { return; }
	fprintf(fp,"[%d] -  ", rawtime);
	vfprintf(fp, text_format, args);
	OS_Close(fp);	
#endif

	return;
}


STATUS OS_EVENTLOG_make_entry(U16 code, const char *text_format, ...)
{
#if defined(MITALIB_DEBUG_FILE_OUTPUT) || defined(MITALIB_DEBUG_CONSOLE_OUTPUT)
	time_t rawtime;
	time(&rawtime);
	va_list(args);
	va_start(args, text_format);
#endif

#ifdef MITALIB_DEBUG_CONSOLE_OUTPUT
	if (ConsoleOutputEnabled)
	{
		printf("[%d] EVT_LOG:  (%d) ", rawtime, code);
		vprintf(text_format, args);
		printf("\n");
	}
#endif

#ifdef MITALIB_DEBUG_FILE_OUTPUT
	int fp = OS_Open("LOGS/Event_Log.txt", PO_APPEND, 0);
	if (fp < 0) { return OS_FILE_NOT_OPENED; }
	fprintf(fp, "[%d] -  (%d) ", rawtime, code);
	vfprintf(fp, text_format, args);
	fprintf(fp, "\n");
	OS_Close(fp);	
#endif

	return 0;
}


STATUS OS_SYSLOG_make_entry(U16 code, const char *text_format, ...) {
#if defined(MITALIB_DEBUG_FILE_OUTPUT) || defined(MITALIB_DEBUG_CONSOLE_OUTPUT)
	time_t rawtime;
	time(&rawtime);
	va_list(args);
	va_start(args, text_format);
#endif

#ifdef MITALIB_DEBUG_CONSOLE_OUTPUT
	if (ConsoleOutputEnabled)
	{
		printf("[%d] SYS_LOG:  (%d) ", rawtime, code);
		vprintf(text_format, args);
		printf("\n");
	}
#endif

#ifdef MITALIB_DEBUG_FILE_OUTPUT
	int fp = OS_Open("LOGS/Sys_Log.txt", PO_APPEND, 0);
	if (fp < 0) { return OS_FILE_NOT_OPENED; }
	fprintf(fp, "[%d] -  (%d) ", rawtime, code);
	vfprintf(fp, text_format, args);
	fprintf(fp, "\n");
	OS_Close(fp);
#endif

	return 0;
}


STATUS OS_DEBUGLOG_make_entry(U16 code, const char *text_format, ...) {
#if defined(MITALIB_DEBUG_FILE_OUTPUT) || defined(MITALIB_DEBUG_CONSOLE_OUTPUT)
	time_t rawtime;
	time(&rawtime);
	va_list(args);
	va_start(args, text_format);
#endif

#ifdef MITALIB_DEBUG_CONSOLE_OUTPUT
	if (ConsoleOutputEnabled)
	{
		printf("[%d] DBG_LOG:  (%d) ", rawtime, code);
		vprintf(text_format, args);
		printf("\n");
	}
#endif

#ifdef MITALIB_DEBUG_FILE_OUTPUT
	int fp = OS_Open("LOGS/Debug_Log.txt", PO_APPEND, 0);
	if (fp < 0) { return OS_FILE_NOT_OPENED; }
	fprintf(fp, "[%d] -  (%d) ", rawtime, code);
	vfprintf(fp, text_format, args);
	fprintf(fp, "\n");
	OS_Close(fp);
#endif

	return 0;
}



/* Task/module functions */


STATUS OS_module_task_destruct(OS_TASK *task)
{
	int result = OS_Terminate_Task(task);
	if (result != OS_SUCCESS) { return result; }
	result = OS_Delete_Task(task);
	if (result != OS_SUCCESS) { return result; }

	return OS_SUCCESS;
}
STATUS OS_module_task_create(OS_TASK *task, CHAR *name, VOID(*task_entry) (UNSIGNED, VOID *), UNSIGNED argc, VOID *argv, UNSIGNED stack_size, OPTION priority, UNSIGNED time_slice, OPTION preempt, OPTION auto_start, OS_MEMORY_POOL *pool)
{
	void* stack_address = 0;
	OS_Create_Task(task, name, task_entry, argc, argv, stack_address/*fix this value*/, stack_size, priority, time_slice, preempt, auto_start);
	OS_internal_Task taskCustom = ((OS_internal_Task)task);
	return 0;
}



STATUS OS_Make_Dir(CHAR *name) { return 0; }

STATUS OS_Open(CHAR *name, U16 flag, U16 mode) 
{ 
	FILE *fptr;
	//CHAR a[150] = "..\\Debug\\WP4x00\\";
	//CHAR a[150] = "..\\..\\WP4x00\\";
	CHAR a[150] = "WP4x00\\";
	CHAR flagString[3]= "r ";

	char param_file_path[512];
	sprintf(a, "%sWP4x00\\", root_folder);

	switch(flag)
	{
	case PO_RDWR:
		flagString[0] = 'r';
		flagString[1] = '+';
		flagString[2] = 'b';
			break;
	case PO_RDONLY:
		flagString[0] = 'r';

		flagString[1] = 'b';
		break;
	case PO_WRONLY:
		flagString[0] = 'a';

		flagString[1] = 'b';
		break;
	case PO_CREAT:
		flagString[0] = 'w';

		flagString[1] = 'b';
		break;
	case PO_APPEND:
		flagString[0] = 'a';

		flagString[1] = 'b';
		break;
	case PO_TRUNC:
		flagString[0] = 'w';

		flagString[1] = 'b';
		break;
	}

	if (name[0]== 'I' && name[1] == ':' && (name[2]== '/' || name[2] == '\\'))
	{
		strcat(a, &name[3]);
	}
	else {
		strcat(a, name);
	}
	fptr = fopen(a, flagString);
	if (fptr == NULL)
	{
		OS_DEBUGLOG_make_entry(0, "Can't open file - %s", name, "\n");
		return OS_FILE_NOFILE;
	}

	return (STATUS)fptr; 
}

S32 OS_Write(INT fd, CHAR *buf, S32 count)
{
	int i= fwrite(buf, 1, count, (FILE *)fd);

	return i;
}

S32 OS_Read(INT fd, CHAR *buf, S32 count) 
{
	int i = 0;
	i= fread(buf,1, count, (FILE *)fd);

	return i;
}


//S32 OS_Seek(INT fd, INT32 offset, S16 origin);

//STATUS OS_Truncate(INT fd, S32 offset);

//STATUS OS_Flush(INT fd);

STATUS OS_Close(INT fd) { 
	if (fd < 0) { return 0; }
	fclose((FILE *)fd);
	return 0; }

//STATUS OS_Set_Attributes(CHAR *name, U8 newattr);

//STATUS OS_Get_Attributes(U8 *attr, CHAR *name);

//STATUS OS_Rename(CHAR *name, CHAR *newname);

//STATUS OS_Delete(CHAR *name);

//STATUS OS_Remove_Dir(CHAR *name);

//STATUS OS_Format(S16 driveno, FMTPARMS *pfmt);

//STATUS OS_FreeSpace(CHAR *path, U8 *secpcluster, U16 *bytepsec, U32 *freecluster, U32 *totalcluster);

//STATUS OS_Get_First(DSTAT *statobj, CHAR *pattern);

//STATUS OS_Get_Next(DSTAT *statobj);

//VOID OS_Done(DSTAT *statobj);

//STATUS OS_Set_Default_Drive(U16 driveno);

//U16 OS_Get_Default_Drive(VOID);

//STATUS OS_Set_Current_Dir(CHAR *path);

//STATUS OS_Current_Dir(UINT8 *drive, CHAR *path);

INT OS_Become_File_User(VOID) { return 0; }

VOID OS_Release_File_User(VOID) { return; }

INT OS_Check_File_User(VOID) { return 0; }

/* Semaphore functions */

STATUS OS_Create_Semaphore(OS_SEMAPHORE *semaphore, CHAR *name, UNSIGNED initial_count, OPTION suspend_type) { return 0; }
STATUS OS_Obtain_Semaphore(OS_SEMAPHORE *semaphore, UNSIGNED suspend) { return 0; }
STATUS OS_Release_Semaphore(OS_SEMAPHORE *semaphore) { return 0; }



#pragma region BackupPart


struct backupParameters {
	int repeat;
	char ParameterName[100];
	value_t Value;
	type_t Type;
	char StringValue[120];

};


#define maxBackupParCount 5000

struct OS_internal_BackupFileNames
{
	varid_t StateId;
	char exports[60];
	BOOL exportsRead;
	char locals[60];
	BOOL localsRead;
	char backups[60];
	BOOL backupsRead;
	int backupParametersCount;
	struct backupParameters backupParm[maxBackupParCount];
};

static struct OS_internal_BackupFileNames OS_BackupFileNames[5];
static int backupfilenamesCount = 0;

STATUS OS_internal_AddBackupFileNames(varid_t StateId, char* exports, char* locals, char* backups)
{
	OS_BackupFileNames[backupfilenamesCount].StateId = StateId;
	strcpy(OS_BackupFileNames[backupfilenamesCount].exports, exports);
	strcpy(OS_BackupFileNames[backupfilenamesCount].locals, locals);
	strcpy(OS_BackupFileNames[backupfilenamesCount].backups, backups);
	backupfilenamesCount++;
	return 0;
}


STATUS OS_Retrieve_Backup_File_Names(varid_t StateId, char** exports, char** locals, char** backups) {

	for (int i = 0; i < backupfilenamesCount; i++)
	{
		if (StateId == OS_BackupFileNames[i].StateId) {
			*exports =(char *) &OS_BackupFileNames[i].exports;
			*locals = (char *)&OS_BackupFileNames[i].locals;
			*backups = (char *)&OS_BackupFileNames[i].backups;
			return 0;
		}

	}
	return -1;
}

static BOOL HasBackupFileBeenRead(char * FileID, struct backupParameters** backupParm, int **Entries ) 
{
	for (int i = 0; i < backupfilenamesCount; i++)
	{
		if (FileID == (char *)&OS_BackupFileNames[i].exports)
		{
			*backupParm =  OS_BackupFileNames[i].backupParm;
			*Entries = &OS_BackupFileNames[i].backupParametersCount;
			if (!OS_BackupFileNames[i].exportsRead) {
				OS_BackupFileNames[i].exportsRead = TRUE;
				return FALSE;
			}
			return TRUE;
		}
		else if (FileID == (char *)&OS_BackupFileNames[i].locals )
		{
			*backupParm = OS_BackupFileNames[i].backupParm;
			*Entries = &OS_BackupFileNames[i].backupParametersCount;
			if (!OS_BackupFileNames[i].localsRead) {
				OS_BackupFileNames[i].localsRead = TRUE;
				return FALSE;
			}
			return TRUE;
		}
		else if (FileID == (char *)&OS_BackupFileNames[i].backups )
		{
			*backupParm = OS_BackupFileNames[i].backupParm;
			*Entries = &OS_BackupFileNames[i].backupParametersCount;
			if (!OS_BackupFileNames[i].backupsRead) {
			OS_BackupFileNames[i].backupsRead = TRUE;
			return FALSE;
			}
			return TRUE;
		}
	}
	*Entries = NULL;
	*backupParm = NULL;
	return FALSE;

}

#define MAXSIZEOFPARAMETERUPDATEBUF 256
static void UpdateParameterinFile(struct os_db_parameter* Parameter)
{
	char buf[MAXSIZEOFPARAMETERUPDATEBUF];
	BOOL doesFileExist = true;
	int fp = OS_Open(Parameter->l.FileID,  PO_RDONLY, 0);
	if (fp < 0) {
		doesFileExist = false;
		buf[0] = 0x01; 
		buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = 0;
		buf[6] = 0;
		buf[7] = 0;
		buf[8] = 0x64;							
		buf[9] = 0;					
		buf[10] = 0;					
		buf[11] = 0;					
		buf[12] = 0x3B;			
		buf[13] = 0x2c;			
		buf[14] = 0xe1;			
		buf[15] = 0x2f;			
	}
	OS_Close(fp);

	fp = OS_Open(Parameter->l.FileID, PO_APPEND, 0);
	if (fp < 0) {
		return;
	}
	if (!doesFileExist) {
		OS_Write(fp, (char *)&buf, 16);
	}
	int i = 0;
	int j = 0;
	buf[0] = 0; //Length 
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = 0;
	buf[7] = 0;
	buf[8] = (U8)(Parameter->c.Type & 0xFF);							//type
	buf[9] = (U8)((Parameter->c.Type >> 8) & 0xFF);					//type
	buf[10] = (U8)((Parameter->c.Type >> 16) & 0xFF);					//type
	buf[11] = (U8)((Parameter->c.Type >> 24) & 0xFF);					//type
	buf[12] = 0;			//time
	buf[13] = 0;			//time
	buf[14] = 0;			//time
	buf[15] = 0;			//time
	buf[16] = 0;			//time	
	buf[17] = 0;			//time
	buf[18] = 0;			//time
	buf[19] = 0;			//time
	i = 20;
	do {
		buf[i++] = Parameter->c.Name[j];

	} while (Parameter->c.Name[j++] != '\0');
	int length = 0;
	if ((Parameter->c.Type >= TYPE_STRING) && (Parameter->c.Type < TYP_ESUM)) {
		length = Parameter->c.Type - TYPE_STRING;

		if (((i + length + 2) % 4) != 0) {
			do {
				buf[i++] = '\0';
			} while (((i + length + 2) % 4) != 0);
		}
		int strpos;
		for (strpos = 0; strpos < length; strpos++) {
			buf[i++] = Parameter->c.Value.string[strpos];
		}

	}
	else {
		if (i % 4 != 0) {
			do {
				buf[i++] = '\0';
			} while (i % 4 != 0);
		}
		buf[i++] = (U8)(Parameter->c.Value.u64 & 0xFF);
		buf[i++] = (U8)((Parameter->c.Value.u64 >> 8) & 0xFF);

	}
	buf[i++] = (U8)((Parameter->c.Value.u64 >> 16) & 0xFF);
	buf[i++] = (U8)((Parameter->c.Value.u64 >> 24) & 0xFF);
	buf[i++] = (U8)((Parameter->c.Value.u64 >> 32) & 0xFF);
	buf[i++] = (U8)((Parameter->c.Value.u64 >> 40) & 0xFF);
	buf[i++] = (U8)((Parameter->c.Value.u64 >> 48) & 0xFF);
	buf[i++] = (U8)((Parameter->c.Value.u64 >> 56) & 0xFF);
	i++;
	buf[i++] = '\0';
	buf[i++] = '\0';
	buf[i++] = '\0';
	buf[i - 4] = (U8)i;
	buf[0] = (U8)i;
	

	OS_Write(fp, (char *)&buf, i);
	OS_Close(fp);
	return;

}


static void ReadFromBackupFile(struct os_db_variable* Variable,  char* ParamID) {

	int* backupParametersCount;
	struct backupParameters* backupParm;

	//check if file has already been read in
	if (!HasBackupFileBeenRead(ParamID, &backupParm, &backupParametersCount)) {
		if (backupParm == NULL) {
			return;
		}
	
	CHAR buf[300];
	char VariableName[100];
	int bytesRead = 0;
	int sizeToRead = 1;
	union
	{
		char*       string;
		BOOL        bool;
		U8          u8;
		S8          s8;
		U16         u16;
		S16         s16;
		U32         u32;
		S32         s32;
		U64         u64;
		S64         s64;
		time_t      time;
		F32         f32;
		F64         f64;
		ANGLE       angle;
		ANGLE_SIGN  angle_sign;
		const char* stringconstant;
		ESUM*       esum;
		SSUM*       ssum;
		SUM*        sum;
		AVAIL*      avail;
		STATSUM*    statistic;
		unsigned char bytes[8];
	}value;
	int Length = 0;
	union {
		U32 Type;
		unsigned char bytes[4];
	}variableType;
	int fp = OS_Open(ParamID, PO_RDONLY, 0);
	if (fp < 0) {
		return;
	}
	//read first identifier
	bytesRead = OS_Read(fp, (char *)&buf, 16);
	if (bytesRead < 16) { return; OS_Close(fp); }
	do {
		//read Length
		bytesRead = OS_Read(fp, (char *)&buf, 4);
		if (bytesRead == 0) { break; }
		Length = (U8)buf[0] + ((U8)buf[1] << 8) + ((U8)buf[2] << 16) + ((U8)buf[3] << 24);
		//read first identifier
		bytesRead = OS_Read(fp, (char *)&buf, Length - 4);
		if (bytesRead == 0) { break; }
		variableType.bytes[0] = buf[4];
		variableType.bytes[1] = buf[5];
		variableType.bytes[2] = buf[6];
		variableType.bytes[3] = buf[7];
		strcpy(VariableName, &buf[16]);


		if ((variableType.Type >= TYPE_STRING) && (variableType.Type < TYP_ESUM)) {


		}
		else {
			value.bytes[0] = buf[Length - 16];
			value.bytes[1] = buf[Length - 15];
			value.bytes[2] = buf[Length - 14];
			value.bytes[3] = buf[Length - 13];
			value.bytes[4] = buf[Length - 12];
			value.bytes[5] = buf[Length - 11];
			value.bytes[6] = buf[Length - 10];
			value.bytes[7] = buf[Length - 9];

		}
		
		if (*backupParametersCount == 0) {
			strcpy((backupParm)[0].ParameterName, VariableName);
			backupParm[0].Type = variableType.Type;
			if ((variableType.Type >= TYPE_STRING) && (variableType.Type < TYP_ESUM)) {
				int startOfStr = Length - 13 - (variableType.Type - TYPE_STRING + 1);
				int readlen = variableType.Type - TYPE_STRING;
				int i = 0;
				for (i = 0; i < readlen; i++) {
					backupParm[*backupParametersCount].StringValue[i] = buf[startOfStr + i];
				}
				backupParm[*backupParametersCount].StringValue[i] = '\0';
			}
			else {
				backupParm[0].Value.u64 = value.u64;
			}
			(*backupParametersCount)++;
		}
		else {
			int bcnt;
			BOOL varfound = FALSE;
			for (bcnt = 0; bcnt < *backupParametersCount; bcnt++)
			{
				if (strcmp(backupParm[bcnt].ParameterName, VariableName) == 0) {
					backupParm[bcnt].Type = variableType.Type;
					if ((variableType.Type >= TYPE_STRING) && (variableType.Type < TYP_ESUM)) {
						int startOfStr = Length - 13 - (variableType.Type - TYPE_STRING + 1);
						int readlen = variableType.Type - TYPE_STRING;
						int i = 0;
						for (i = 0; i < readlen; i++) {
							backupParm[*backupParametersCount].StringValue[i] = buf[startOfStr + i];
						}
						backupParm[*backupParametersCount].StringValue[i] = '\0';
					}
					else {
						backupParm[bcnt].Value.u64 = value.u64;
					}
					backupParm[bcnt].repeat++;
					varfound = true;
					break;
				}
			}
			if (!varfound) {
				strcpy(backupParm[*backupParametersCount].ParameterName, VariableName);
				backupParm[*backupParametersCount].Type = variableType.Type;
				if ((variableType.Type >= TYPE_STRING) && (variableType.Type < TYP_ESUM)) {
					int startOfStr = Length - 13 - (variableType.Type - TYPE_STRING + 1);
					int readlen = variableType.Type - TYPE_STRING;
					int i = 0;
					for (i = 0; i < readlen; i++) {
						backupParm[*backupParametersCount].StringValue[i] = buf[startOfStr + i];
					}
					backupParm[*backupParametersCount].StringValue[i] =  '\0';
				}
				else {

					backupParm[*backupParametersCount].Value.u64 = value.u64;
				}
				backupParm[*backupParametersCount].repeat = 0;
				(*backupParametersCount)++;
			}
			if (*backupParametersCount >= maxBackupParCount) {
				OS_Close(fp);
				return; //too many backups

			}
		}
		
		

	} while (bytesRead != 0);

	OS_Close(fp);
	}



	//setValues
	
		for ( int k = 0; k < *backupParametersCount; k++) 
		{
			switch (Variable->c.Update)
			{
			case PARAMETER:
				if (strcmp(((struct os_db_parameter *)Variable)->c.Name, backupParm[k].ParameterName) == 0) {
					if ((backupParm[k].Type >= TYPE_STRING) && (backupParm[k].Type < TYP_ESUM)) {					
						int len;
						if (len= (size_t)(backupParm[k].Type - TYPE_STRING + 1) <= (size_t)(((struct os_db_parameter *)Variable)->c.Type - TYPE_STRING + 1)) {

							strcpy(((struct os_db_parameter *)Variable)->c.Value.string, backupParm[k].StringValue);

						}
					}
					else if (((struct os_db_parameter *)Variable)->c.Type == backupParm[k].Type) {
						((struct os_db_parameter *)Variable)->c.Value.u64 = backupParm[k].Value.u64;
					}
				}

				break;
			case LOCAL:
				if (strcmp(((struct os_db_local *)Variable)->c.Name, backupParm[k].ParameterName) == 0) {
					if ((backupParm[k].Type >= TYPE_STRING) && (backupParm[k].Type < TYP_ESUM)) {
						int len;
						if (len = (size_t)(backupParm[k].Type - TYPE_STRING + 1) <= (size_t)(((struct os_db_local *)Variable)->c.Type - TYPE_STRING + 1)) {

							strcpy(((struct os_db_local *)Variable)->c.Value.string, backupParm[k].StringValue);

						}

					}
					else if (((struct os_db_local *)Variable)->c.Type == backupParm[k].Type) {
						((struct os_db_local *)Variable)->c.Value.u64 = backupParm[k].Value.u64;
					}
				}

				break;
			case BACKUP:
				if (strcmp(((struct os_db_backup *)Variable)->c.Name, backupParm[k].ParameterName) == 0) {
					if ((backupParm[k].Type >= TYPE_STRING) && (backupParm[k].Type < TYP_ESUM)) {
						int len;
						if (len = (size_t)(backupParm[k].Type - TYPE_STRING + 1) <= (size_t)(((struct os_db_parameter *)Variable)->c.Type - TYPE_STRING + 1)) {

							strcpy(((struct os_db_backup *)Variable)->c.Value.string, backupParm[k].StringValue);

						}
					}
					else if (((struct os_db_backup *)Variable)->c.Type == backupParm[k].Type) {
						((struct os_db_backup *)Variable)->c.Value.u64 = backupParm[k].Value.u64;
					}
				}

				break;
			default:
				break;
			}

		}

	
}

#pragma endregion



/* Variable DB functions */


#pragma region Variable DB //--------------------------------------------------------------//
#include <osdb.h>
#include <string.h>
#include <errcodes.h>
static struct os_db_variable *OS_Database;


static os_db_common *OS_Database_Locals_for_Debug[30000];
static int OS_Database_Locals_count = 0;

static os_db_common *OS_Database_Parameters_for_Debug[30000];
static int OS_Database_Parameters_count = 0;


static os_db_common *OS_Database_Backups_for_Debug[30000];
static int OS_Database_Backups_count = 0;

//gets real variable if alias
static STATUS GetVariableIfAlias(struct os_db_variable** temp)
{
	if ((*temp)->c.MagicNumber == ALIAS_MAGIC_NUMBER) {
		*temp = ((struct os_db_alias*)(*temp))->Parent;
		return GetVariableIfAlias(temp);
	}
	else if ((*temp)->c.MagicNumber == VAR_MAGIC_NUMBER) {

		return OS_SUCCESS;
	}
	else
	{
		return -1;
	}

}


//Gets id that has alias/es in beginning if has
static STATUS GetVariableID(const char *VariableName, varid_t *VarId) {
	struct os_db_variable* temp = OS_Database;
	struct os_db_variable* firsttemp= OS_Database;
	if (OS_Database == NULL) {
		return ERR_VARDB_NOT_FOUND;
	}


	do {
		if (temp->c.MagicNumber == ALIAS_MAGIC_NUMBER) {
			if (strcmp(VariableName, ((struct os_db_alias*)temp)->Alias) == 0) {

				*VarId = firsttemp;
				return OS_SUCCESS;
			}
			temp = ((struct os_db_alias*)temp)->Parent;

		}
		else {
			if (strcmp(VariableName, (*temp).c.Name) == 0) {

				*VarId = firsttemp;
				return OS_SUCCESS;
			}
			temp = temp->c.NextVariable;
			firsttemp = temp;
		}
		
	} while (temp != NULL);


	return ERR_VARDB_NOT_FOUND;
}



STATUS OS_VarDB_CreateLocals(struct os_db_local Variables[], size_t Entries,size_t *ErrorEntry, const char* ParamID) 
{
	varid_t varID;
	struct os_db_variable* temp;

	if (ParamID == NULL) {
		return ERR_VARDB_BAD_BACKUP_FILE;
	}

	if (OS_VarDB_GetVariableID(Variables[0].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
		return ERR_VARDB_VARIABLE_EXISTS;
	}

	if (OS_Database != NULL) {

		(*OS_Database).c.PreviousVariable = (struct os_db_variable *)&Variables[Entries - 1];
		Variables[Entries - 1].c.NextVariable = OS_Database;
	}
	
	OS_Database = (struct os_db_variable *)Variables;

	ReadFromBackupFile(OS_Database, ParamID);
	temp= (struct os_db_variable *)&Variables[0];

	OS_Database_Locals_for_Debug[OS_Database_Locals_count] = (os_db_common *)&(Variables->c);  //for debug purposes
	OS_Database_Locals_count++; //for debug purposes

	for ( unsigned int i = 1; i < Entries; i++) {
		if (OS_VarDB_GetVariableID(Variables[i].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
			return ERR_VARDB_VARIABLE_EXISTS;
		}

		OS_Database_Locals_for_Debug[OS_Database_Locals_count] = (os_db_common *)&(Variables[i].c);  //for debug purposes
		OS_Database_Locals_count++; //for debug purposes


		(*temp).c.NextVariable = (struct os_db_variable *)&Variables[i];
		Variables[i].c.PreviousVariable = temp;

		ReadFromBackupFile((struct os_db_variable *)&Variables[i], ParamID);
		temp = (struct os_db_variable *)&Variables[i];
	}
	return 0;
}


STATUS OS_VarDB_CreateParameters(struct os_db_parameter Variables[], size_t Entries, size_t *ErrorEntry, const char* ParamID) 
{ 
	varid_t varID;
	struct os_db_variable* temp;

	if (OS_VarDB_GetVariableID(Variables[0].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
		return ERR_VARDB_VARIABLE_EXISTS;
	}

	if (OS_Database != NULL) {
		(*OS_Database).c.PreviousVariable = (struct os_db_variable*)&Variables[Entries - 1];
		Variables[Entries - 1].c.NextVariable = OS_Database;
	}

	OS_Database = (struct os_db_variable *)Variables;
	((struct os_db_parameter*) OS_Database)->l.FileID = ParamID;
	ReadFromBackupFile((struct os_db_variable *)OS_Database, ParamID);
	temp = (struct os_db_variable *)&Variables[0];

		OS_Database_Parameters_for_Debug[OS_Database_Parameters_count] = ( os_db_common *)&(Variables->c);  //for debug purposes
		OS_Database_Parameters_count++; //for debug purposes

	for (unsigned int i = 1; i < Entries; i++) {
		if (OS_VarDB_GetVariableID(Variables[i].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
			return ERR_VARDB_VARIABLE_EXISTS;
		}

		OS_Database_Parameters_for_Debug[OS_Database_Parameters_count] = (os_db_common *)&(Variables[i].c);  //for debug purposes
		OS_Database_Parameters_count++; //for debug purposes

		(*temp).c.NextVariable = (struct os_db_variable *)&Variables[i];
		Variables[i].c.PreviousVariable = temp;
		((struct os_db_parameter*) &Variables[i])->l.FileID = ParamID;
		ReadFromBackupFile((struct os_db_variable *)&Variables[i], ParamID);
		temp = (struct os_db_variable *)&Variables[i];
	}

	return OS_SUCCESS;

}

STATUS OS_VarDB_CreateBackups(struct os_db_backup Variables[], size_t Entries, size_t *ErrorEntry, const char* ParamID, const char* FileID)
{
	varid_t varID;
	struct os_db_variable* temp;

	if (OS_VarDB_GetVariableID(Variables[0].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
		return ERR_VARDB_VARIABLE_EXISTS;
	}

	if (OS_Database != NULL) {
		(*OS_Database).c.PreviousVariable = (struct os_db_variable*)&Variables[Entries - 1];
		Variables[Entries - 1].c.NextVariable = OS_Database;
	}


	OS_Database = (struct os_db_variable *)Variables;

	((struct os_db_backup*) OS_Database)->l.FileID = FileID;
	ReadFromBackupFile(OS_Database, ParamID);
	temp = (struct os_db_variable *)&Variables[0];

	OS_Database_Backups_for_Debug[OS_Database_Backups_count] = (os_db_common *)&(Variables->c);  //for debug purposes
	OS_Database_Backups_count++; //for debug purposes

	for (unsigned int i = 1; i < Entries; i++) {
		if (OS_VarDB_GetVariableID(Variables[i].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
			return ERR_VARDB_VARIABLE_EXISTS;
		}

		OS_Database_Backups_for_Debug[OS_Database_Backups_count] = (os_db_common *)&(Variables[i].c);  //for debug purposes
		OS_Database_Backups_count++; //for debug purposes

		(*temp).c.NextVariable = (struct os_db_variable *)&Variables[i];
		Variables[i].c.PreviousVariable = temp;
		((struct os_db_backup*) &Variables[i])->l.FileID = FileID;
		ReadFromBackupFile(&Variables[i], ParamID);
		temp = (struct os_db_variable *)&Variables[i];
	}

	return OS_SUCCESS;
}

STATUS OS_VarDB_GetVariableID(const char *VariableName, varid_t *VarId) {
	struct os_db_variable* temp= OS_Database;
	int dwWaitResult = 0;
	 dwWaitResult = WaitForSingleObject(
		ghMutex,    // handle to mutex
		INFINITE);  // no time-out interval
	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
	{
		__try {
		if (OS_Database == NULL) {
			*VarId = NULL;
			return ERR_VARDB_NOT_FOUND;
		}
		do {

			if (temp->c.MagicNumber == ALIAS_MAGIC_NUMBER) {
				if (strcmp(VariableName, ((struct os_db_alias*)temp)->Alias) == 0) {
					if (temp == NULL) {
						int breakpoint = 0;
					}
					STATUS result = GetVariableIfAlias(&temp);
					*VarId = temp;
					return OS_SUCCESS;
				}
				temp = ((struct os_db_alias*)temp)->Parent;

			}
			else {
				if (strcmp(VariableName, (*temp).c.Name) == 0) {

					*VarId = temp;
					return OS_SUCCESS;
				}
				temp = temp->c.NextVariable;
			}
		} while (temp != NULL);

		}
		__finally {
			// Release ownership of the mutex object
			if (!ReleaseMutex(ghMutex))
			{
				// Handle error.
			}
		}

		break;

	}
		case WAIT_ABANDONED:

			*VarId = NULL;
			return -1;
		
	}

	*VarId = NULL;
	return ERR_VARDB_NOT_FOUND;
}


STATUS OS_VarDB_GetVariableType(varid_t VariableId, type_t* type) 
{ 
	if (VariableId == NULL || !(VariableId->c.MagicNumber == VAR_MAGIC_NUMBER || VariableId->c.MagicNumber == ALIAS_MAGIC_NUMBER)) {
		return ERR_VARDB_BAD_VARIABLEID;
	}
	
	struct os_db_variable* temp = VariableId;
	if (temp == NULL) {
		int breakpoint = 0;
	}
	STATUS result = GetVariableIfAlias(&temp);
	if (result < 0) {
		return -1;
	}
	*type = (temp->c.Type);

	return 0;
}


STATUS OS_VarDB_ReadVariable(varid_t VariableId, void *Value, size_t len, time_t *TimeStamp) {

	struct os_db_variable* temp = VariableId;
	if (temp == NULL) {
		int breakpoint = 0;
	}
			STATUS result = GetVariableIfAlias(&temp);
			if (result < 0) {
				return -1;
			}
			switch (temp->c.Type) {
			case TYPE_BOOL:
				if (len != sizeof(BOOL)) { return ERR_VARDB_WRONG_LENGTH; }
				*(BOOL *)Value = temp->c.Value.bool;
				break;
			case TYPE_U8:
				if (len != sizeof(U8)) { return ERR_VARDB_WRONG_LENGTH; }
				*(U8 *)Value = temp->c.Value.u8;
				break;
			case TYPE_U16:
				if (len != sizeof(U16)) { return ERR_VARDB_WRONG_LENGTH; }
				*(U16 *)Value = temp->c.Value.u16;
				break;
			case TYPE_U32:
				if (len != sizeof(U32)) { return ERR_VARDB_WRONG_LENGTH; }
				*(U32 *)Value = temp->c.Value.u32;
				break;
			case TYPE_U64:
				if (len != sizeof(U64)) { return ERR_VARDB_WRONG_LENGTH; }
				*(U64 *)Value = temp->c.Value.u64;
				break;
			case TYPE_S8:
				if (len != sizeof(S8)) { return ERR_VARDB_WRONG_LENGTH; }
				*(S8 *)Value = temp->c.Value.s8;
				break;
			case TYPE_S16:
				if (len != sizeof(S16)) { return ERR_VARDB_WRONG_LENGTH; }
				*(S16 *)Value = temp->c.Value.s16;
				break;
			case TYPE_S32:
				if (len != sizeof(S32)) { return ERR_VARDB_WRONG_LENGTH; }
				*(S32 *)Value = temp->c.Value.s32;
				break;
			case TYPE_S64:
				if (len != sizeof(S64)) { return ERR_VARDB_WRONG_LENGTH; }
				*(S64 *)Value = temp->c.Value.s64;
				break;
			case TYPE_F32:
				if (len != sizeof(F32)) { return ERR_VARDB_WRONG_LENGTH; }
				*(F32 *)Value = temp->c.Value.f32;
				break;
			case TYPE_F64:
				if (len != sizeof(F64)) { return ERR_VARDB_WRONG_LENGTH; }
				*(F64 *)Value = temp->c.Value.f64;
				break;

			}
			if ((temp->c.Type >= TYPE_STRING) && (temp->c.Type < TYP_ESUM)) {
				if (len > (size_t)(temp->c.Type - TYPE_STRING + 1)) {
					return ERR_VARDB_WRONG_LENGTH;
				}
				UINT i;
				for (i = 0; i < len; i++)
				{
					*((char *)Value + i) = *(temp->c.Value.string + i);

				}
			}
			return OS_SUCCESS;
		

}

//reads real variableid(not alias) //variables are stored in vardb with alias in front
STATUS OS_VarDB_ReadVariableByName(const char *VariableName, void *Value, size_t len, time_t *TimeStamp)
{
	if (OS_Database == NULL) {
		return ERR_VARDB_NOT_FOUND;
	}

	struct os_db_variable* temp = OS_Database;

	do {

		if (strcmp(VariableName, (*temp).c.Name) == 0) {
			return  OS_VarDB_ReadVariable(temp, Value, len, TimeStamp);
		}
		if ((*temp).c.MagicNumber == ALIAS_MAGIC_NUMBER)
		{
			temp = ((struct os_db_alias*)temp)->Parent;
		}
		else {
			temp = temp->c.NextVariable;
		}
	} while (temp != NULL);


	return ERR_VARDB_NOT_FOUND;

}




STATUS OS_VarDB_UpdateVariable(varid_t VariableId, void*   Value, size_t  len)
{
	struct os_db_variable* temp = VariableId;
	if (temp == NULL) {
		int breakpoint = 0;
	}
	STATUS result = GetVariableIfAlias(&temp);
	if (result < 0) {
		return -1;
	}
	switch (temp->c.Type) {
	case TYPE_BOOL:
		if (len != sizeof(BOOL)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.bool = *(BOOL *)Value;
		break;
	case TYPE_U8:
		if (len != sizeof(U8)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u8 = *(U8 *)Value; 			
		break;
	case TYPE_U16:
		if (len != sizeof(U16)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u16 = *(U16 *)Value;
		break;
	case TYPE_U32:
		if (len != sizeof(U32)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u32 = *(U32 *)Value;
		break;
	case TYPE_U64:
		if (len != sizeof(U64)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u64 = *(U64 *)Value;
		break;
	case TYPE_S8:
		if (len != sizeof(S8)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s8 = *(S8 *)Value;
		break;
	case TYPE_S16:
		if (len != sizeof(S16)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s16 = *(S16 *)Value;
		break;
	case TYPE_S32:
		if (len != sizeof(S32)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s32 = *(S32 *)Value;
		break;
	case TYPE_S64:
		if (len != sizeof(S64)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s64 = *(S64 *)Value;
		break;
	case TYPE_F32:
		if (len != sizeof(F32)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.f32 = *(F32 *)Value;
		break;
	case TYPE_F64:
		if (len != sizeof(F64)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.f64 = *(F64 *)Value;
		break;
	}

	if ((temp->c.Type >= TYPE_STRING) && (temp->c.Type < TYP_ESUM)) {
		if (len > (size_t)(temp->c.Type - TYPE_STRING + 1)) {
			return ERR_VARDB_WRONG_LENGTH;
		}
		UINT i;
		for (i = 0; i < len; i++)
		{
			*(temp->c.Value.string + i) = *((char *)Value + i);

		}
	}

	//Update ParamId file
	if (temp->c.Update == (enum update)PARAMETER) {
		UpdateParameterinFile((struct os_db_parameter*)temp);
	}

	if (temp->c.FirstSubscriber == NULL) {
		return OS_SUCCESS;
	}

	struct subscription_struct *substemp;
	substemp = temp->c.FirstSubscriber;
	while (1) {
		if (substemp->type == MAILBOX) {
			static U32 message[4];
			message[0] = (U32)MESSAGETYPE_SUBSCRIBED_VARIABLE_IS_UPDATED;
			message[1] = substemp->varid;
			message[2] = substemp->subscriber.mailbox.reference;//??
			message[3] = temp->c.Value.u8; //new value??

			OS_Send_To_Mailbox(substemp->subscriber.mailbox.mailbox, message, OS_NO_SUSPEND);

		}else if (substemp->type == EVENT) {
			OS_Set_Events(substemp->subscriber.event.group, substemp->subscriber.event.events, OS_OR);
		//not tested
		
		}
		if (substemp->next == NULL) { break; }
		substemp = substemp->next;
	}

	return OS_SUCCESS;
}

STATUS OS_VarDB_UpdateVariableByName(const char *VariableName, void* Value, size_t len) {

	if (OS_Database == NULL) {
		return ERR_VARDB_NOT_FOUND;
	}

	struct os_db_variable* temp = OS_Database;
	
	do {		
		if (strcmp(VariableName, (*temp).c.Name) == 0) {
			return OS_VarDB_UpdateVariable(temp, Value, len);
		}
		if ((*temp).c.MagicNumber == ALIAS_MAGIC_NUMBER)
		{
			temp = ((struct os_db_alias*)temp)->Parent;
		}
		else {
			temp = temp->c.NextVariable;
		}
	} while (temp != NULL);

	return ERR_VARDB_NOT_FOUND;
}

STATUS OS_VarDB_UpdateVariableConditional(varid_t VariableId, void* Value, size_t  len)
{
	struct os_db_variable* temp = VariableId;
	if (temp == NULL) {
		int breakpoint = 0;
	}
	STATUS result = GetVariableIfAlias(&temp);
	if (result < 0) {
		return -1;
	}
	switch (temp->c.Type) {
	case TYPE_BOOL:
		if (len != sizeof(BOOL)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.bool = *(BOOL*)Value;
		break;
	case TYPE_U8:
		if (len != sizeof(U8)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u8 = *(U8*)Value;
		break;
	case TYPE_U16:
		if (len != sizeof(U16)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u16 = *(U16*)Value;
		break;
	case TYPE_U32:
		if (len != sizeof(U32)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u32 = *(U32*)Value;
		break;
	case TYPE_U64:
		if (len != sizeof(U64)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.u64 = *(U64*)Value;
		break;
	case TYPE_S8:
		if (len != sizeof(S8)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s8 = *(S8*)Value;
		break;
	case TYPE_S16:
		if (len != sizeof(S16)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s16 = *(S16*)Value;
		break;
	case TYPE_S32:
		if (len != sizeof(S32)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s32 = *(S32*)Value;
		break;
	case TYPE_S64:
		if (len != sizeof(S64)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.s64 = *(S64*)Value;
		break;
	case TYPE_F32:
		if (len != sizeof(F32)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.f32 = *(F32*)Value;
		break;
	case TYPE_F64:
		if (len != sizeof(F64)) { return ERR_VARDB_WRONG_LENGTH; }
		temp->c.Value.f64 = *(F64*)Value;
		break;
	}

	if ((temp->c.Type >= TYPE_STRING) && (temp->c.Type < TYP_ESUM)) {
		if (len > (size_t)(temp->c.Type - TYPE_STRING + 1)) {
			return ERR_VARDB_WRONG_LENGTH;
		}
		UINT i;
		for (i = 0; i < len; i++)
		{
			*(temp->c.Value.string + i) = *((char*)Value + i);

		}
	}

	//Update ParamId file
	if (temp->c.Update == (enum update)PARAMETER) {
		UpdateParameterinFile((struct os_db_parameter*)temp);
	}

	if (temp->c.FirstSubscriber == NULL) {
		return OS_SUCCESS;
	}

	struct subscription_struct* substemp;
	substemp = temp->c.FirstSubscriber;
	while (1) {
		if (substemp->type == MAILBOX) {
			static U32 message[4];
			message[0] = (U32)MESSAGETYPE_SUBSCRIBED_VARIABLE_IS_UPDATED;
			message[1] = substemp->varid;
			message[2] = substemp->subscriber.mailbox.reference;//??
			message[3] = temp->c.Value.u8; //new value??

			OS_Send_To_Mailbox(substemp->subscriber.mailbox.mailbox, message, OS_NO_SUSPEND);

		}
		else if (substemp->type == EVENT) {
			OS_Set_Events(substemp->subscriber.event.group, substemp->subscriber.event.events, OS_OR);
			//not tested

		}
		if (substemp->next == NULL) { break; }
		substemp = substemp->next;
	}

	return OS_SUCCESS;
}

STATUS OS_VarDB_UpdateU8(varid_t VariableID, U8 Value)
{
	return OS_VarDB_UpdateVariable(VariableID, &Value, sizeof(U8));

}

STATUS OS_VarDB_UpdateS32(varid_t VariableID, S32 Value) {

	return OS_VarDB_UpdateVariable(VariableID, &Value, sizeof(S32));
}

STATUS OS_VarDB_UpdateU32(varid_t VariableID, U32 Value) {

	return OS_VarDB_UpdateVariable(VariableID, &Value, sizeof(U32));
}


STATUS OS_ReadVariables(struct ModulInOut ModulVars[], size_t Entries) 
{
	STATUS LocalStatus = 0;
	size_t i;
	for (i = 0; i < Entries; i++) {
		LocalStatus = OS_VarDB_ReadVariable(ModulVars[i].Id, ModulVars[i].DataAdr, ModulVars[i].DataAdrSize, NULL);	
		if (LocalStatus != 0) { 
			return LocalStatus; 
		}

	}

	return LocalStatus;
}

STATUS OS_WriteVariablesConditional(struct ModulInOut ModulVars[], size_t Entries) 
{
	//TODO write only when value has changed.
	
	size_t i;
	for (i = 0; i < Entries; i++)
	{	
		 OS_VarDB_UpdateVariable(ModulVars[i].Id, ModulVars[i].DataAdr, ModulVars[i].DataAdrSize);

	}
	return 0;
}

STATUS OS_DoesVariablesExist(struct ModulInOut ModulVars[], size_t Entries) 
{
	size_t i;
	for (i = 0; i < Entries; i++) 
	{
		if (OS_VarDB_GetVariableID(ModulVars[i].Name, &(ModulVars[i].Id)) == ERR_VARDB_NOT_FOUND) {
			return i + 1;

		}

	}
	return 0;
}


STATUS OS_SUM_CreateSummations(struct os_db_summation Variables[], size_t Entries, size_t *ErrorEntry, const char* BackupID)
{

	varid_t varID;
	struct os_db_variable* temp;

	if (BackupID == NULL) {
		return ERR_VARDB_BAD_BACKUP_FILE;
	}

	if (OS_VarDB_GetVariableID(Variables[0].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
		return ERR_VARDB_VARIABLE_EXISTS;
	}

	if (OS_Database != NULL) {

		(*OS_Database).c.PreviousVariable = (struct os_db_variable *)&Variables[Entries - 1];
		Variables[Entries - 1].c.NextVariable = OS_Database;
	}

	OS_Database = (struct os_db_variable *)Variables;
	temp = (struct os_db_variable *)&Variables[0];

	OS_Database_Locals_for_Debug[OS_Database_Locals_count] = (os_db_common *)&(Variables->c);  //for debug purposes
	OS_Database_Locals_count++; //for debug purposes

	for (unsigned int i = 1; i < Entries; i++) {
		if (OS_VarDB_GetVariableID(Variables[i].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
			return ERR_VARDB_VARIABLE_EXISTS;
		}

		OS_Database_Locals_for_Debug[OS_Database_Locals_count] = (os_db_common *)&(Variables[i].c);  //for debug purposes
		OS_Database_Locals_count++; //for debug purposes


		(*temp).c.NextVariable = (struct os_db_variable *)&Variables[i];
		Variables[i].c.PreviousVariable = temp;
		temp = (struct os_db_variable *)&Variables[i];
	}
	return 0;
}


STATUS OS_VarDB_CreateTimers(struct os_db_timer Variables[],size_t Entries, size_t *ErrorEntry)
{

	varid_t varID;
	struct os_db_variable* temp;

	if (OS_VarDB_GetVariableID(Variables[0].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
		return ERR_VARDB_VARIABLE_EXISTS;
	}

	if (OS_Database != NULL) {

		(*OS_Database).c.PreviousVariable = (struct os_db_variable *)&Variables[Entries - 1];
		Variables[Entries - 1].c.NextVariable = OS_Database;
	}

	OS_Database = (struct os_db_variable *)Variables;
	temp = (struct os_db_variable *)&Variables[0];

	OS_Database_Locals_for_Debug[OS_Database_Locals_count] = (os_db_common *)&(Variables->c);  //for debug purposes
	OS_Database_Locals_count++; //for debug purposes

	for (unsigned int i = 1; i < Entries; i++) {
		if (OS_VarDB_GetVariableID(Variables[i].c.Name, &varID) != ERR_VARDB_NOT_FOUND) {
			return ERR_VARDB_VARIABLE_EXISTS;
		}

		OS_Database_Locals_for_Debug[OS_Database_Locals_count] = (os_db_common *)&(Variables[i].c);  //for debug purposes
		OS_Database_Locals_count++; //for debug purposes


		(*temp).c.NextVariable = (struct os_db_variable *)&Variables[i];
		Variables[i].c.PreviousVariable = temp;
		temp = (struct os_db_variable *)&Variables[i];
	}
	return 0;
}

STATUS OS_VarDB_CreateAliases(struct os_db_alias Aliases[], size_t Entries, size_t *ErrorEntry)
{
	STATUS result;
	int k = 2;
	size_t i;
	varid_t id ;
	varid_t id2;
	for (i = 0; i < Entries; i++)
	{
		if (GetVariableID(Aliases[i].Name, (&Aliases[i].Parent)) == ERR_VARDB_NOT_FOUND) {
			return i + 1;

		}
		id = (struct os_db_variable *)&Aliases[i];
		if (id == NULL) {
			int breakpoint = 0;
		}
		result =   GetVariableIfAlias(&id);
		if (result < 0) { return -1; }
		if (id->c.PreviousVariable != NULL) {
			id2 = id->c.PreviousVariable;
			if (id2 == NULL) {
				int breakpoint2 = 0;
			}
			result = GetVariableIfAlias(&id2);
			id2->c.NextVariable= (struct os_db_variable *)&Aliases[i];
		}
		else {
			OS_Database = (struct os_db_variable *)&Aliases[i];
		}

		if (id->c.NextVariable != NULL) {

			id2 = id->c.NextVariable;
			if (id2 == NULL) {
				int breakpoint3 = 0;
			}
			result = GetVariableIfAlias(&id2);
			id2->c.PreviousVariable = (struct os_db_variable *)&Aliases[i];
		
		}
	}
	return 0;
}

#pragma endregion
/* Task functions */

OS_TASK * OS_Current_Task_Pointer(VOID)
{

	int *pointer;

	int result = OS_Allocate_Memory(GetMemPool(), &pointer, sizeof(struct OS_TASK_STRUCT), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	
	return (struct OS_TASK_STRUCT *)pointer;
}







#pragma region Communication //--------------------------------------------------------------//
/*New low level OS functions */
//Following are local ip addresses
#define STRINGIPTOINTEGER(a,b,c,d) ( a | (b << 8 )| (c << 16) | (d << 24))
#define LOCALWPETH0ADDRESS STRINGIPTOINTEGER(192,168,1,39)  //use commas
#define LOCALWPETH1ADDRESS STRINGIPTOINTEGER(0,0,0,0)  //use commas
//1677830336 is 192.168.1.100
	static WSADATA wsaData;
	static struct os_db_local LocalVars[] =
	{
	   VAR_ELEMENT_LOCAL("WP4000_ETH0_IP_Addr",                    TYPE_U32,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   LOCALWPETH0ADDRESS,               INT_MIN,              INT_MAX,               NULL,  NOLOG_ENABLE),
	   VAR_ELEMENT_LOCAL("WP4000_ETH1_IP_Addr",                    TYPE_U32,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   LOCALWPETH1ADDRESS,				 INT_MIN,               INT_MAX,                NULL,  NOLOG_ENABLE)
	};
#undef LOCALWPETH0ADDRESS
#undef LOCALWPETH1ADDRESS
#include<general.h>

	
//need to call this to use winsockets
int InitializeWinSockets() {
	int iResult;

	STATUS Status;
	size_t ErrorEntry;

	Status = OS_VarDB_CreateLocals(LocalVars, sizeof(LocalVars) / sizeof(LocalVars[0]), &ErrorEntry, AppLocalParameterPosition());
	if (Status != 0)
	{
		AppSystemLog(ERR_7, "Error adding socket variables to variabledb: %d,%d", Status, ErrorEntry);
		return ERR_7;
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	else {

		return 0;
	}
}


STATUS OS_Socket(S16 _afamily, S16 socketType, S16 protocol) {

	SOCKET ListenSocket = INVALID_SOCKET;


	int af;
	if (_afamily == OS_FAMILY_IP) {
		af = AF_INET;
	}
	else {
		return -1;
	}


	int type;
	if (socketType == OS_TYPE_STREAM) {
		type = SOCK_STREAM;
	}
	else {
		return -1;
	}

	int proto;
	if (protocol == OS_NONE) {
		proto = IPPROTO_IP;
	}
	else {
		return -1;
	}

	// Create a SOCKET for the server to listen for client connections
	
	ListenSocket = socket(af, type, proto);

	return ListenSocket;
}

STATUS OS_Close_Socket(INT socketd) { 
	
	int result = closesocket(socketd);
	if (result == SOCKET_ERROR) {
		return -1;
	}
	//can return OS_INVALID_SOCKET,	OS_NO_PORT_NUMBER,		OS_NOT_CONNECTED.
	return OS_SUCCESS; }

//STATUS OS_Setsockopt(INT, INT, INT, VOID *, INT);

//STATUS OS_Getsockopt(INT, INT, INT, VOID *, INT *);

STATUS OS_Listen(INT socketd, U16 backlog) { 
	
	int iResult = listen(socketd, backlog);
	if (iResult == SOCKET_ERROR) {
		//printf("listen failed with error: %d\n", WSAGetLastError());
		//closesocket(socketd);
		//WSACleanup();
		return -1;
	}

	//Can return OS_INVALID_SOCKET OS_NOSOCK_MEMORY
	
	return OS_SUCCESS;;
}

STATUS OS_Bind(INT socketd, struct addr_struct * myaddr, S16 addrlen)
{ 
	
	struct sockaddr_in addr = { 0 };
	addr.sin_family = myaddr->family; //check compatibility
	addr.sin_port = htons(myaddr->port);
	char ip[16] = "000.000.000.000";
	snprintf((char *)&ip, sizeof(ip), "%u.%u.%u.%u", myaddr->id.is_ip_addrs[0], myaddr->id.is_ip_addrs[1], myaddr->id.is_ip_addrs[2], myaddr->id.is_ip_addrs[3]);
	int re= inet_pton(myaddr->family, ip, &(addr.sin_addr));
	 

	int iResult = bind(socketd, (struct sockaddr *) &addr, sizeof(addr));
	
	if (iResult == SOCKET_ERROR) {
		//printf("bind failed with error: %d\n", WSAGetLastError());

		//closesocket(socketd);
		//WSACleanup();
		return -1;
	}
	//Can return OS_INVALID_SOCKET, OS_INVALID_PARAM, OS_INVALID_PORT, OS_INVALID_ADDRESS
	return socketd; 
}

//STATUS OS_Get_Host_By_Name(CHAR *name, OS_HOSTENT *host_entry);

STATUS OS_Accept(INT socketd, struct addr_struct * peer, S16 * addrlen) {
	
	SOCKADDR_IN client_info = { 0 };
	int addrsize = sizeof(client_info);
	
	// Accept the connection.
	int result = accept(socketd, (struct sockaddr*)&client_info, &addrsize);
	
	if (result == INVALID_SOCKET) {
	//	wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
		//closesocket(socketd);
		//WSACleanup();
		return -1;
	}
	
	peer->port = client_info.sin_port;
	peer->family = client_info.sin_family;
	peer->id.is_ip_addrs[0] = client_info.sin_addr.S_un.S_un_b.s_b1;
	peer->id.is_ip_addrs[1] = client_info.sin_addr.S_un.S_un_b.s_b2;
	peer->id.is_ip_addrs[2] = client_info.sin_addr.S_un.S_un_b.s_b3;
	peer->id.is_ip_addrs[3] = client_info.sin_addr.S_un.S_un_b.s_b4;

	//can return OS_INVALID_SOCKET, OS_NO_PORT_NUMBER
	return result;
}

STATUS OS_Connect(INT socketd, struct addr_struct * servaddr, S16 addrlen) {
	struct sockaddr_in addr = { 0 };
	addr.sin_family = servaddr->family; //check compatibility
	addr.sin_port = htons(servaddr->port);
	char ip[16] = "000.000.000.000";
	snprintf((char *)&ip, sizeof(ip), "%u.%u.%u.%u", servaddr->id.is_ip_addrs[0], servaddr->id.is_ip_addrs[1], servaddr->id.is_ip_addrs[2], servaddr->id.is_ip_addrs[3]);
	int re = inet_pton(servaddr->family, ip, &(addr.sin_addr));


	int iResult = connect(socketd, (SOCKADDR *)&addr, sizeof(addr));
	if (iResult == SOCKET_ERROR) {
		int result = WSAGetLastError();
		if (result == WSAEWOULDBLOCK) { return 0; }
		return -1;
	}
	
	return 0; }

STATUS OS_Abort(INT socketd)
{ 
	u_long mode = 0;  
	int result = ioctlsocket(socketd, SO_DONTLINGER, &mode);
	result = OS_Close_Socket(socketd);
	return result; 
}

S32 OS_Recv(INT socketd, CHAR * buff, U16 nbytes, S16 flags)
{
	int result = recv(socketd, buff, nbytes, flags);
	if (result == SOCKET_ERROR) {
		switch (WSAGetLastError())
		{
		case WSAEWOULDBLOCK:
			return 0;
		case WSAENOTCONN:
			return OS_NOT_CONNECTED;
		case WSAENOTSOCK:
			return OS_INVALID_SOCKET;
		default: 
			return -1;
		}		
	}

	//can return OS_NOT_CONNECTED, OS_INVALID_SOCKET, OS_NO_PORT_NUMBER, OS_WOULD_BLOCK, OS_NO_ROUTE_TO_HOST, OS_CONNECTION_REFUSED, OS_MSG_TOO_LONG.
	return result; 
}

S32 OS_Send(INT socketd, CHAR * buff, U16 nbytes, S16 flags)
{
	int result = send(socketd, buff, nbytes, flags);
	if (result == SOCKET_ERROR) {
		switch (WSAGetLastError())
		{
		case WSAEWOULDBLOCK:
			return 0;
		case WSAENOTCONN:
			return OS_NOT_CONNECTED;
		case WSAENOTSOCK:
			return OS_INVALID_SOCKET;
		default:
			return -1;
		}
	}
	//can return also  OS_NOT_CONNECTED, OS_INVALID_SOCKET, OS_NO_PORT_NUMBER, OS_WOULD_BLOCK, OS_NO_ROUTE_TO_HOST, OS_CONNECTION_REFUSED, OS_MSG_TOO_LONG.
		return result;

}


STATUS OS_Is_Connected(INT socketd) {

	fd_set fds;
	struct timeval timeout;
	int rc, result;

	// Set time limit. 
	timeout.tv_sec = 0;
	timeout.tv_usec = 10;
	// Create a descriptor set containing our two sockets.  
	FD_ZERO(&fds);
	FD_SET(socketd, &fds);
	rc = select(sizeof(fds) * 8,NULL, &fds, NULL, &timeout);
	if (rc == -1) {
		perror("select failed");
		return -1;
	}
	result = 0;
	if (rc > 0)
	{
		if (FD_ISSET(socketd, &fds)) { 
			return 1;
		}
	}
	
	return 0;
}

//U32 OS_Recv_From(INT, CHAR *, U16, S16, struct addr_struct *, S16 *);

//U32 OS_Send_To(INT, CHAR *, U16, S16, struct addr_struct *, S16);

//VOID OS_FD_Init(FD_SET *fd);

//VOID OS_FD_Set(INT, FD_SET *);

//STATUS OS_Select(INT, FD_SET *, FD_SET *, FD_SET *, UNSIGNED);

STATUS OS_Fcntl(INT socketd, S16 command, S16 argument) 
{
	u_long mode = 1;  // 1 to enable non-blocking socket
	if (command != OS_SETFLAG) {
		return OS_NO_ACTION;
	}
	if (argument == OS_NO_BLOCK) {
		mode = 1;
	}
	else if (argument == OS_BLOCK) {
		mode = 0;
	}
	else { return OS_NO_ACTION; }
	int result= ioctlsocket(socketd, FIONBIO, &mode);


	if (result == WSAENOTSOCK) {
		return OS_INVALID_SOCKET;
	}

	if(result==0){
		return OS_SUCCESS;
	}
	else {
		return OS_NO_ACTION;
	}
}

//INT OS_Get_Host_Name(CHAR *name, INT name_length);

#pragma endregion





STATUS OS_Sleep(UNSIGNED ticks) 
{
	// windows sleep function uses ms instead of ticks
	U32 TimeInMs=0;
	if(ticks < 15000) {
		TimeInMs = 1;
	}
	else {
		TimeInMs = ticks / 10000;
	}
	Sleep(TimeInMs);
	return 0;
}

#pragma region CH19StatusCodeSystem //-----------------------------------------------------------------------------------

static const char *modulesStsNameFormat[2] = {
		"Sts%05d_CurrentState",
		"Sts%05d_Enable",
};



STATUS OS_TOTLOG_SetTrig(void)
{
	//TODO
	return 0;
}
STATUS OS_SubHandl_SubscribeFunctionWithRef(SUBSCRIPTION subscriptions[], size_t count, varid_t varids[],
	UNSIGNED Ref1[], UNSIGNED Ref2[], STATUS(*Update)(varid_t VariableId, void* Message,
		U16 Length, UNSIGNED Ref1, UNSIGNED Ref2))
{
	//TODO
	return 0;
}




STATUS OS_VarDB_UpdateVariableConditionalByName(const char* VariableName,
	void*       Value,
	size_t      Length) {
	return 0;
}


STATUS OS_VarDB_LockOutputParameter(varid_t VariableId, U32 ObjectID)
{

	return 0;
}

#pragma region Pipe //--------------------------------------------------------------//

/* Pipe functions */

static OS_PIPE *OS_pipes; // main structure to hold all status codes;
 
typedef struct OS_internal_PIPE //unsigned long*18  //this is not the real format used in mita os
{
	char name[8];


} OS_internal_PIPE;



STATUS OS_Broadcast_To_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size, UNSIGNED suspend) 
{
	//todo 
	return 0;
}
STATUS OS_Create_Pipe(OS_PIPE *pipe, CHAR *name, VOID *start_address,
	UNSIGNED pipe_size, OPTION message_type,
	UNSIGNED message_size, OPTION suspend_type)
{
	OS_internal_PIPE* internalpipe = (OS_internal_PIPE *)pipe;

	int i;
	for (i = 0; i < 8; i++)
	{
		internalpipe->name[i] = *(name + i);
	}

	//todo 
	return 0;
}
STATUS OS_Delete_Pipe(OS_PIPE *pipe)
{
	//todo 
	return 0;
}
UNSIGNED  OS_Established_Pipes(VOID)
{
	//todo 
	return 0;
}
STATUS OS_Pipe_Information(OS_PIPE *pipe, CHAR *name, VOID **start_address,
	UNSIGNED *pipe_size, UNSIGNED *available,
	UNSIGNED *messages, OPTION *message_type,
	UNSIGNED *message_size, OPTION *suspend_type,
	UNSIGNED *tasks_waiting, OS_TASK **first_task)
{
	//todo 
	return 0;
}
UNSIGNED OS_Pipe_Pointers(OS_PIPE **pointer_list, UNSIGNED maximum_pointers)
{
	//todo 
	return 0;
}
STATUS OS_Receive_From_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size, UNSIGNED *actual_size, UNSIGNED suspend)
{
	//todo 
	return 0;
}
STATUS OS_Reset_Pipe(OS_PIPE *pipe)
{
	//todo 
	return 0;
}
STATUS OS_Send_To_Front_Of_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size,
	UNSIGNED suspend)
{
	//todo 
	return 0;
}
STATUS OS_Send_To_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size,UNSIGNED suspend)
{
	//todo 
	return 0;
}


#pragma endregion

#pragma region Mailbox //--------------------------------------------------------------//


typedef struct OS_internal_MailBox OS_internal_MailBox;


struct OS_internal_MailBox //unsigned long*13  //this is not the real format used in mita os
{
	char name[8];
	U32 message[4];
	U8 messageAvailable;
	HANDLE ghMutex;
	OPTION suspend_type;
};




STATUS OS_Send_To_Mailbox(OS_MAILBOX *mailbox, VOID *message, UNSIGNED suspend)
{
	OS_internal_MailBox* box = (OS_internal_MailBox *)mailbox;
	while (true)
	{

		if (!box->messageAvailable)
		{
			box->message[0] = *((U32*)message);
			box->message[1] = *((U32*)message + 1);
			box->message[2] = *((U32*)message + 2);
			box->message[3] = *((U32*)message + 3);
			box->messageAvailable = 1;
			return 0;
		}
		Sleep(1);
	}
	return 0;
}


STATUS OS_Receive_From_Mailbox(OS_MAILBOX *mailbox, VOID *message, UNSIGNED suspend)
{
	OS_internal_MailBox* box = (OS_internal_MailBox *)mailbox;
	while (true)
	{

		if (box->messageAvailable)
		{
			*((U32*)message) = box->message[0];
			*((U32*)message + 1) = box->message[1];
			*((U32*)message + 2) = box->message[2];
			*((U32*)message + 3) = box->message[3];

			box->messageAvailable = 0;
			return 0;
		}
		Sleep(1);
	}

	return 0;
}

STATUS OS_Create_Mailbox(OS_MAILBOX *mailbox, CHAR *name, OPTION suspend_type)
{
	//Prob<bly uses pipe
	OS_internal_MailBox* box = (OS_internal_MailBox *)mailbox;

	int i;
	for (i = 0; i < 8; i++)
	{
		box->name[i] = *(name + i);
	}

	box->ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (box->ghMutex == NULL)
	{
		printf("CreateMutex error mailbox: %d\n", GetLastError());
		return -1;
	}
	box->suspend_type = suspend_type;
	return 0;
}



#pragma endregion


STATUS OS_module_create_all(OS_MEMORY_POOL *pool, OPTION auto_start, int count, ...) {
	//TODO
	int i;
	STATUS LocalStatus=0;
	U8 a,max;
	U8 *object;
	va_list ap;
	va_start(ap, count);

	object = ((va_arg(ap, U8 **)));

	for (i = 0; i < count; i++) {
		if (i > 0) {
			object = ((va_arg(ap, U8 **)));
		}
		if (*object == TASK_INFO) {
			 
			LocalStatus = OS_module_task_create(((struct task_info*)object)->task, 
												((struct task_info*)object)->name,
												((struct task_info*)object)->task_entry,
				((struct task_info*)object)->argc, 
				((struct task_info*)object)->argv,
				((struct task_info*)object)->stack_size,
				((struct task_info*)object)->priority,
				((struct task_info*)object)->time_slice,
				((struct task_info*)object)->preempt,
				auto_start,
				pool);
		}
		else if(*object == QUEUE_INFO){
			//TODO 
			//LocalStatus = OS_module_queue_create();
		}
		else if (*object == SEMAPHORE_INFO) {
			//TODO 
			//LocalStatus = OS_Create_Semaphore();
		}
		else if (*object == EVENT_GROUP_INFO) {
			//TODO 
			//LocalStatus = OS_Create_Event_Group();
		}
		else if (*object == HISR_INFO) {
			//TODO 
			//LocalStatus = OS_module_HISR_create();
		}
		else if (*object == MAILBOX_INFO) {			 
			LocalStatus = OS_Create_Mailbox(((struct mailbox_info*)object)->mailbox, ((struct mailbox_info*)object)->name, ((struct mailbox_info*)object)->suspend_type);			
		}
		else if (*object == TIMER_INFO) {
			//TODO 
			//LocalStatus = OS_Create_Timer();
		}
		else {
			LocalStatus = -1;
			break;
		}
		if (LocalStatus != 0) { break; }

	}
	va_end(ap);
	if (LocalStatus != 0) {
		return ERR_TASK_WRONG_TASK_OBJECT;
	}
	return OS_SUCCESS;
}

STATUS OS_SubHandl_SubscribeFunction(SUBSCRIPTION subscriptions[],
	size_t count, varid_t varids[],
	STATUS(*Update)(varid_t VariableId,
		void* Message,
		U16 Length))
{
	//Todo
	return 0;
}

STATUS OS_Create_Queue(OS_QUEUE *queue, CHAR *name, VOID *start_address,
	UNSIGNED queue_size, OPTION message_type,
	UNSIGNED message_size, OPTION suspend_type)
{
	return 0;
	//TODO;
}
STATUS OS_Receive_From_Queue(OS_QUEUE *queue, VOID *message, UNSIGNED size,
	UNSIGNED *actual_size, UNSIGNED suspend)
{
	return 0;
	//TODO;
}

STATUS OS_VarDB_UpdateLockedOutputParameter(varid_t VariableId,
	void *Value,
	size_t Length,
	U32 ObjectID)
{
	//TODO
	return 0;
}


typedef struct OS_internal_Event_Group OS_internal_Event_Group;

struct OS_internal_Event_Group //unsigned long*9  //this is not the real format used in mita os
{
	char name[8];
	OS_internal_Event_Group *prev; //null if first
	OS_internal_Event_Group *next;  //null if last
	U32 flags; //32 flag bits

};

static struct OS_internal_Event_Group *OS_EventGroups;

static struct SUBSCRIPTION *OS_Subscriptions;

STATUS OS_Create_Event_Group(OS_EVENT_GROUP *group, CHAR *name)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		((OS_internal_Event_Group*)group)->name[i] = *(name + i);
	}

	if (OS_EventGroups == NULL) {
		OS_EventGroups = group;
	}
	else {
		((OS_internal_Event_Group*)group)->next = OS_EventGroups;
		OS_EventGroups->prev = ((OS_internal_Event_Group*)group);
		OS_EventGroups = group;
	}
	((OS_internal_Event_Group*)group)->flags = 0;

	return 0;
}

void OS_SubHandl_InitSubscriptionBlocks(SUBSCRIPTION subscriptions[], size_t count)
{

	//TODO
	return ;

}

STATUS OS_SubHandl_Subscribe(SUBSCRIPTION *subscription, varid_t varid, enum subscriber_type type,union subscriber subscriber) {
	
	if (varid == NULL) {
		int breakpoint = 0;
	}
	STATUS result = GetVariableIfAlias(&varid);
	if (result < 0) {
		return -1;
	}
	
	subscription->type = type;
	subscription->subscriber = subscriber;
	subscription->varid = varid;
	if (varid->c.FirstSubscriber == NULL)
	{
		varid->c.FirstSubscriber = subscription;
	}
	else
	{
		subscription->next = varid->c.FirstSubscriber;
		varid->c.FirstSubscriber = subscription;
	}
	
	return 0;
}

STATUS OS_SubHandl_SubscribeEvent(SUBSCRIPTION subscriptions[], size_t count, varid_t varids[],	OS_EVENT_GROUP *group) {

	if (count > 32) { return -1; }

	/* Create Subscription info var */
	int i = 0;
	for (i = 0; i < count; i++) {
	 union subscriber SubscriptionInfo;
		OS_SubHandl_InitSubscriptionBlocks(&subscriptions[i], 1);
		SubscriptionInfo.event.group = group;
		SubscriptionInfo.event.events = 1;//((OS_internal_Event_Group*)group)->flags; ??
		OS_SubHandl_Subscribe(&subscriptions[i], varids[i], EVENT, SubscriptionInfo);
	}

	return 0;
}


STATUS OS_SubHandl_SubscribeMailbox(SUBSCRIPTION subscriptions[], size_t count, varid_t varids[], OS_MAILBOX *mailbox)
{
	if (count > 32) { return -1; }

	/* Create Subscription info var */
	int i = 0;
	for (i = 0; i < count; i++) {
		union subscriber SubscriptionInfo;
		OS_SubHandl_InitSubscriptionBlocks(&subscriptions[i], 1); 
		SubscriptionInfo.mailbox.mailbox = mailbox;
		SubscriptionInfo.mailbox.reference = i;
		OS_SubHandl_Subscribe(&subscriptions[i], varids[i], MAILBOX, SubscriptionInfo);
	}

	return 0;
}

STATUS OS_Set_Events(OS_EVENT_GROUP *group, UNSIGNED events, OPTION operation)
	{
	int i = 0;
	U32 *flags = &((OS_internal_Event_Group*)group)->flags;
	//for (int i = 0; i < 32; i++) {
	switch (operation) {
	case OS_OR:
		*flags = (*flags) | events;
		break;
	case OS_AND:
		*flags = (*flags) & events;
		break;
	}
		return OS_SUCCESS;
	}

STATUS OS_Delete_Event_Group(OS_EVENT_GROUP *group)
{
	//TODO
	return 0;
}

STATUS OS_Retrieve_Events(OS_EVENT_GROUP *group, UNSIGNED requested_flags,
	OPTION operation, UNSIGNED *retrieved_flags,
	UNSIGNED suspend)
{

	//TODO ADD timout option
	U32 *flags = &((OS_internal_Event_Group*)group)->flags;
	while (1) {
		switch (operation) {
		case OS_AND:
			if ((*flags & requested_flags) == requested_flags) {
				*retrieved_flags = requested_flags;
				return OS_SUCCESS;
			}
			else {
				if (OS_SUSPEND) {
					OS_Sleep(10000);
				}
				else  if (OS_NO_SUSPEND) {
					return OS_NOT_PRESENT;
				}
				else {
					//timeout
					return OS_TIMEOUT;
				}
			}
			break;
		case OS_OR:
			if ((*flags | requested_flags) != 0) {
				*retrieved_flags = *flags | requested_flags;
				return OS_SUCCESS;
			}
			else {
				if (OS_SUSPEND) {
					OS_Sleep(10000);
				}
				else  if (OS_NO_SUSPEND) {
					return OS_NOT_PRESENT;
				}
				else {
					//timeout
					return OS_TIMEOUT;
				}
			}
			break;
		case OS_AND_CONSUME:
			if ((*flags & requested_flags) == requested_flags) {
				*retrieved_flags = requested_flags;
				*flags = 0;
				return OS_SUCCESS;
			}
			else {
				if (OS_SUSPEND) {
					OS_Sleep(10000);
				}
				else  if (OS_NO_SUSPEND) {
					return OS_NOT_PRESENT;
				}
				else {
					//timeout
					return OS_TIMEOUT;

				}
			}
			break;
		case OS_OR_CONSUME:
			if ((*flags | requested_flags) != 0) {
				*retrieved_flags = *flags | requested_flags;
				*flags = 0;
				return OS_SUCCESS;
			}
			else {
				if (OS_SUSPEND) {
					OS_Sleep(10000);
				}
				else  if (OS_NO_SUSPEND) {
					return OS_NOT_PRESENT;
				}
				else {
					//timeout
					return OS_TIMEOUT;
				}
			}
			break;
		default:
			return OS_INVALID_OPERATION;
			
		}
	}
	return 0;
}

STATUS OS_SubHandl_Unsubscribe(SUBSCRIPTION subscriptions[],
	size_t count) {
	// first function OS_SubHandl_InitSubscriptionBlocks() needs to work
	
	//TODO
	return 0;
}










STATUS OS_module_destruct_all(int count, ...)
{
	//TODO
	return 0;
}


U32 OS_Recv_From(INT a, CHAR * b, U16 c, S16 d, struct addr_struct *e, S16 *f) {
	//todo
	return 0;
}

U32 OS_Send_To(INT a, CHAR *b, U16 c, S16 d, struct addr_struct * e, S16 f)
{
	//todo
	return 0;
}
STATUS OS_Task_Information
(OS_TASK *task, CHAR *name, DATA_ELEMENT *status,
	UNSIGNED *scheduled_count, OPTION *priority,
	OPTION *preempt, UNSIGNED *time_slice, VOID **stack_base,
	UNSIGNED *stack_size, UNSIGNED *minimum_stack) {
	//todo
	return 0;
}


static HANDLE hTimerQueue = NULL;

typedef struct OS_internal_Timer OS_internal_Timer;

struct OS_internal_Timer //unsigned long*17  //this is not the real format used in mita os
{
	/* A magic number to be checked before every operation
	 to a variable in order to detect validity of data */
	U32 MagicNumber;
	char name[8];
	OS_internal_Timer *prev; //null if first
	OS_internal_Timer *next;  //null if last
	VOID(*expiration_routine)(UNSIGNED);
	UNSIGNED id;
	UNSIGNED initial_time;
	UNSIGNED reschedule_time;
	UNSIGNED  expirations;
	OPTION enable;
	HANDLE hTimer;
};

static struct OS_internal_Timer *OS_Timers;

STATUS OS_Control_Timer(OS_TIMER *timer, OPTION enable)
{
	if (timer == NULL || ((OS_internal_Timer*)timer)->MagicNumber!= TIMER_MAGIC_NUMBER) {
		return OS_INVALID_TIMER;
	}

	if (enable != OS_ENABLE_TIMER && enable != OS_DISABLE_TIMER) {
		return OS_INVALID_ENABLE;
	}

	((OS_internal_Timer*)timer)->enable = enable;

	return 0;
}

static int arg = 124;

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	if (lpParam == NULL)
	{
		printf("TimerRoutine lpParam is NULL\n");
	}
	else
	{
		OS_internal_Timer timer = *(OS_internal_Timer*)lpParam;
	int t = 5;
	timer.expiration_routine(timer.id);
	}


}

STATUS OS_Create_Timer(OS_TIMER *timer, CHAR *name,
	VOID(*expiration_routine)(UNSIGNED), UNSIGNED id,
	UNSIGNED initial_time, UNSIGNED reschedule_time,
	OPTION enable)
{
	if (timer == NULL) {
		return OS_INVALID_TIMER;
	}

	int i;
	for (i = 0; i < 8; i++)
	{
		((OS_internal_Timer*)timer)->name[i] = *(name + i);
	}

	if (OS_Timers == NULL) {
		OS_Timers = timer;
	}
	else {
		((OS_internal_Timer*)timer)->next = OS_Timers;
		OS_Timers->prev = ((OS_internal_Timer*)timer);
		OS_Timers = timer;
	}

	((OS_internal_Timer*)timer)->MagicNumber = TIMER_MAGIC_NUMBER;
	((OS_internal_Timer*)timer)->id = id;
	((OS_internal_Timer*)timer)->enable = enable;
	((OS_internal_Timer*)timer)->reschedule_time = reschedule_time;
	((OS_internal_Timer*)timer)->initial_time = initial_time;
	((OS_internal_Timer*)timer)->expiration_routine = expiration_routine;


	DWORD InitialtimeInMs = 0;
	DWORD rescheduletimeInMs = 0;

	//InitialtimeInMs = initial_time;
	///rescheduletimeInMs = reschedule_time;

	if (initial_time < 15000) {
		InitialtimeInMs = 1;
	}
	else {
		InitialtimeInMs = initial_time / 10000;
	}

	if (reschedule_time == 0) {
		rescheduletimeInMs = 0;
	}
	else if (reschedule_time < 15000) {
		rescheduletimeInMs = 1;
	}
	else {
	rescheduletimeInMs = reschedule_time /10000;
	}
	if (!CreateTimerQueueTimer(&(((OS_internal_Timer*)timer)->hTimer), hTimerQueue, (WAITORTIMERCALLBACK)TimerRoutine , timer, InitialtimeInMs, rescheduletimeInMs, WT_EXECUTEINTIMERTHREAD))	
	{
		printf("CreateTimerQueueTimer failed (%d)\n", GetLastError());
		return 3;
	}
	return 0;
}




static VOID  HandleVariableSubscriptionsfromTimer(UNSIGNED varid)
{

	struct os_db_variable* temp = varid;
	int t = 5;
	int i;
	if (temp->c.FirstSubscriber == NULL) {
		return;
	}
	
	struct subscription_struct *substemp;
	substemp = temp->c.FirstSubscriber;
	while(1) {
		if (substemp->type == MAILBOX) {
			static U32 message[4];
			message[0] = (U32)MESSAGETYPE_SUBSCRIBED_VARIABLE_IS_UPDATED;
			message[1] = substemp->varid;
			message[2] = substemp->subscriber.mailbox.reference;//??
			message[3] = temp->c.Value.u8; //new value??

		  OS_Send_To_Mailbox(substemp->subscriber.mailbox.mailbox, message, OS_NO_SUSPEND);

		}
		if (substemp->next == NULL) { break; }
		substemp = substemp->next;
	} 

}


STATUS OS_timevar_create_timervariable(UNSIGNED interval, varid_t VariableId, OS_TIMER *timer)
{
	if (VariableId == NULL || !(VariableId->c.MagicNumber == VAR_MAGIC_NUMBER || VariableId->c.MagicNumber == ALIAS_MAGIC_NUMBER)) {
		return ERR_VARDB_BAD_VARIABLEID;
	}

	struct os_db_variable* temp = VariableId;
	if (temp == NULL) {
		int breakpoint = 0;
	}
	STATUS result = GetVariableIfAlias(&temp);
	if (result < 0) {
		return -1;
	}
	
	UNSIGNED LocalIntervaltimeinTicks = interval * 10000;
	return OS_Create_Timer(timer, temp->c.Name, HandleVariableSubscriptionsfromTimer, temp, LocalIntervaltimeinTicks, LocalIntervaltimeinTicks, OS_ENABLE_TIMER);
}



STATUS OS_Reset_Timer(OS_TIMER *timer, VOID(*expiration_routine)(UNSIGNED),
	UNSIGNED initial_time, UNSIGNED reschedule_timer,
	OPTION enable)
{
	//todo
	return 0;
}






/* SW Watchdog API */
STATUS OS_Watchdog_Get_Schedule_time(UNSIGNED *wd_counttime) {
	//TODO
	*wd_counttime = 1; // just to avoid division by zero in other code

	return 0;
}

STATUS OS_Watchdog_Hit_Item(U32 WD_Item) {
	//TODO
	return 0;
}

STATUS OS_Watchdog_Change_Item(U32 WD_Item, UNSIGNED count, UNSIGNED nof_timeouts, UNSIGNED enabled) {
	//TODO
	return 0;
}


/* New watchdog functions FKL 040913 */
STATUS OS_Watchdog_Create_Item(const char* Name, UNSIGNED Count, UNSIGNED Timeouts, UNSIGNED Enable, U32* WD)
{
	//TODO
	return 0;
}


STATUS OS_Watchdog_SetOptions(U32 WD_Item, enum WD_Options Option, U32 Action)
{
	//TODO
	return 0;
}



#define MODULE_CONFIG_FILE_TYPE_DATAID 1
#define MODULE_CONFIG_FILE_TYPE_MBCONFIG 2
#define MODULE_CONFIG_FILE_TYPE_CANOPEN 3

 typedef struct HWModuleLocalStruct
{
	U16          GroupNumber;
	U16          NodeNumber;
	char         ModuleType[10];
	//--------------------------
	U8           Mod_Failed;
	U8           Mod_Failed_Enabled;
	//--------------------------
	varid_t      Mod_Failed_id;
	varid_t      Mod_Failed_Enabled_id;
	//--------------------------
	SUBSCRIPTION Sbs_Failed;
	SUBSCRIPTION Sbs_Failed_Enabled;

	char filename[3][100];
	U8 fileType[3];
	U8 argU8[3];
	U8 argString[3][50];
	int filecount;
	BOOL hasFileName;


} HWModuleLocalStructType;



//static HWModuleLocalStructType *SYSTEM_Modules;
static HWModuleLocalStructType *SYSTEM_Modules[50];
static int SYSTEM_Modules_count = 0;


static void ProcessModulesConfigFile(char* buf, int count )
{
	int i;
	int k=0;
	char tempString[150];
	BOOL readingString= false;
	int groupnum = 0;
	int modulenum = 0;

	for (i = 0; i < count; i++,k++)
	{
		if (buf[i] == '<') 
		{
			k = -1;
			readingString = true;
		}
		else if (buf[i] == '>') {
			readingString = false;
			if ((k == 16) && (tempString[0] == 'G') && (tempString[6]=='N'))
			{
				groupnum = atoi(&tempString[14]);
			}
			else if ((k == 15) && (tempString[0] == 'M') && (tempString[7] == 'N'))
			{
				modulenum = atoi(&tempString[13]);
			}
			else if ((k == 4) && (tempString[0] == 'T') && (tempString[3] == 'e'))
			{
				int o = 0;
				char Temp[40];
				char Tempval[5];
				while (o < 5)
				{
					if (buf[i + 1] != '<') {
						Tempval[o] = buf[i + 1];
						i++;
					}
					else { Tempval[o] = '\0'; }
					o++;
				}
				//AddVariable to database;
				snprintf(Temp, sizeof Temp, "%03u_%02u_Type", groupnum, modulenum);



				struct os_db_local* newdatabasevar;
				int result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar, sizeof(struct os_db_local), OS_NO_SUSPEND);
				if (result != OS_SUCCESS) { return NULL; }

				 result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar->c.Name, 12, OS_NO_SUSPEND);
				if (result != OS_SUCCESS) { return NULL; }


				newdatabasevar->c.MagicNumber = VAR_MAGIC_NUMBER;
				newdatabasevar->c.HashValue = 0;
				newdatabasevar->c.NextName = NULL;
				strcpy(newdatabasevar->c.Name,Temp);
				newdatabasevar->c.Type = TYPE_STRING + sizeof(Temp) - 1;
				newdatabasevar->c.AccessRead = 200;
				newdatabasevar->c.AccessWrite = 200;
				newdatabasevar->c.ScaleType = SCALE_NONE;
				newdatabasevar->c.ScaleValue = 0;
				newdatabasevar->c.Unit = UNIT_NONE;
				newdatabasevar->c.Precision = 0;
				newdatabasevar->c.Value.string = Tempval;
				newdatabasevar->c.TimeStamp = NOLOG_ENABLE;
				newdatabasevar->c.ScaleType = (scaletype_t)0;  /* DisplayScaleType */      \
					newdatabasevar->c.ScaleValue = (scalevalue_t)0;   /* DisplayScaleValue */     \
					newdatabasevar->c.DisplayUnit = (unit_t)0;        /* DisplayUnit */           \
					newdatabasevar->c.DisplayPrecision = 0;                 /* DisplayPrecision*/       \
					newdatabasevar->c.Update = (enum update)LOCAL;/* Update type */           \
					newdatabasevar->c.FirstSubscriber = NULL;              /* FirstSubscriber */       \
					newdatabasevar->c.PreviousVariable = NULL;              /* PreviousVariable */      \
					newdatabasevar->c.NextVariable = NULL;              /* NextVariable */          \
					newdatabasevar->c.ActiveReaders = 0;                 /* ActiveReaders */         \
					newdatabasevar->c.OldValueBeingRead = 0;                 /* OldValueBeingRead */     \
					newdatabasevar->c.TotalLogID = 0;                 /* TotalLogID */            \
					newdatabasevar->c.FiveMinLogID = 0;     /* 5 min log ID */          \
				newdatabasevar->l.LogFlags = NULL;
				newdatabasevar->l.Minimum.string = 0;
					newdatabasevar->l.Maximum.string = 0;
					newdatabasevar->l.Lists = NULL;

					static struct os_db_local LocalnewVars[1];
					LocalnewVars[0] = *newdatabasevar;
				size_t ErrorEntry = 0;
				result = OS_VarDB_CreateLocals(newdatabasevar, 1, &ErrorEntry, AppLocalParameterPosition());
				if (result != 0)
				{
					AppSystemLog(7, "module add failed: %d", result);
				}

				//AddVariable event  to database;
				snprintf(Temp, sizeof Temp, "%u.%u.Event", groupnum, modulenum);



				 result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar, sizeof(struct os_db_local), OS_NO_SUSPEND);
				if (result != OS_SUCCESS) { return NULL; }

				result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar->c.Name, 12, OS_NO_SUSPEND);
				if (result != OS_SUCCESS) { return NULL; }


				newdatabasevar->c.MagicNumber = VAR_MAGIC_NUMBER;
				newdatabasevar->c.HashValue = 0;
				newdatabasevar->c.NextName = NULL;
				strcpy(newdatabasevar->c.Name, Temp);
				newdatabasevar->c.Type = TYPE_STRING + sizeof(Temp) - 1;
				newdatabasevar->c.AccessRead = 200;
				newdatabasevar->c.AccessWrite = 200;
				newdatabasevar->c.ScaleType = SCALE_NONE;
				newdatabasevar->c.ScaleValue = 0;
				newdatabasevar->c.Unit = UNIT_NONE;
				newdatabasevar->c.Precision = 0;
				newdatabasevar->c.Value.string = Tempval;
				newdatabasevar->c.TimeStamp = NOLOG_ENABLE;
				newdatabasevar->c.ScaleType = (scaletype_t)0;  /* DisplayScaleType */      \
					newdatabasevar->c.ScaleValue = (scalevalue_t)0;   /* DisplayScaleValue */     \
					newdatabasevar->c.DisplayUnit = (unit_t)0;        /* DisplayUnit */           \
					newdatabasevar->c.DisplayPrecision = 0;                 /* DisplayPrecision*/       \
					newdatabasevar->c.Update = (enum update)LOCAL;/* Update type */           \
					newdatabasevar->c.FirstSubscriber = NULL;              /* FirstSubscriber */       \
					newdatabasevar->c.PreviousVariable = NULL;              /* PreviousVariable */      \
					newdatabasevar->c.NextVariable = NULL;              /* NextVariable */          \
					newdatabasevar->c.ActiveReaders = 0;                 /* ActiveReaders */         \
					newdatabasevar->c.OldValueBeingRead = 0;                 /* OldValueBeingRead */     \
					newdatabasevar->c.TotalLogID = 0;                 /* TotalLogID */            \
					newdatabasevar->c.FiveMinLogID = 0;     /* 5 min log ID */          \
					newdatabasevar->l.LogFlags = NULL;
				newdatabasevar->l.Minimum.string = 0;
				newdatabasevar->l.Maximum.string = 0;
				newdatabasevar->l.Lists = NULL;

				LocalnewVars[0] = *newdatabasevar;
				ErrorEntry = 0;
				result = OS_VarDB_CreateLocals(newdatabasevar, 1, &ErrorEntry, AppLocalParameterPosition());
				if (result != 0)
				{
					AppSystemLog(7, "module add failed: %d", result);
				}


				//add module sts
				int scnt;
				for (scnt = 0; scnt < sizeof(modulesStsNameFormat) / sizeof(modulesStsNameFormat[0]); scnt++) {

				//Calculate the sts number based on the position of the module.
				int ModStatusNr = (4000 + (16 * groupnum) + modulenum)*10;
				//Calculate the sts number based on the position of the module.
				

				 result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar, sizeof(struct os_db_local), OS_NO_SUSPEND);
				if (result != OS_SUCCESS) { return NULL; }

				result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar->c.Name, 30, OS_NO_SUSPEND);
				if (result != OS_SUCCESS) { return NULL; }


				newdatabasevar->c.MagicNumber = VAR_MAGIC_NUMBER;
				newdatabasevar->c.HashValue = 0;
				newdatabasevar->c.NextName = NULL;
				
					snprintf(newdatabasevar->c.Name, 30, modulesStsNameFormat[scnt], ModStatusNr);
				

				newdatabasevar->c.Type = TYPE_STRING + 30 - 1;
				newdatabasevar->c.AccessRead = 200;
				newdatabasevar->c.AccessWrite = 200;
				newdatabasevar->c.ScaleType = SCALE_NONE;
				newdatabasevar->c.ScaleValue = 0;
				newdatabasevar->c.Unit = UNIT_NONE;
				newdatabasevar->c.Precision = 0;
				newdatabasevar->c.Value.string = Tempval;
				newdatabasevar->c.TimeStamp = NOLOG_ENABLE;
				newdatabasevar->c.ScaleType = (scaletype_t)0;  /* DisplayScaleType */      \
					newdatabasevar->c.ScaleValue = (scalevalue_t)0;   /* DisplayScaleValue */     \
					newdatabasevar->c.DisplayUnit = (unit_t)0;        /* DisplayUnit */           \
					newdatabasevar->c.DisplayPrecision = 0;                 /* DisplayPrecision*/       \
					newdatabasevar->c.Update = (enum update)LOCAL;/* Update type */           \
					newdatabasevar->c.FirstSubscriber = NULL;              /* FirstSubscriber */       \
					newdatabasevar->c.PreviousVariable = NULL;              /* PreviousVariable */      \
					newdatabasevar->c.NextVariable = NULL;              /* NextVariable */          \
					newdatabasevar->c.ActiveReaders = 0;                 /* ActiveReaders */         \
					newdatabasevar->c.OldValueBeingRead = 0;                 /* OldValueBeingRead */     \
					newdatabasevar->c.TotalLogID = 0;                 /* TotalLogID */            \
					newdatabasevar->c.FiveMinLogID = 0;     /* 5 min log ID */          \
					newdatabasevar->l.LogFlags = NULL;
				newdatabasevar->l.Minimum.string = 0;
				newdatabasevar->l.Maximum.string = 0;
				newdatabasevar->l.Lists = NULL;

				LocalnewVars[0] = *newdatabasevar;
				result = OS_VarDB_CreateLocals(newdatabasevar, 1, &ErrorEntry, AppLocalParameterPosition());
				if (result != 0)
				{
					AppSystemLog(7, "module add failed: %d", result);
				}
				}



			    HWModuleLocalStructType* newModulesVar;
				 result = OS_Allocate_Memory(GetMemPool(), &newModulesVar, sizeof( HWModuleLocalStructType), OS_NO_SUSPEND);
				if (result != OS_SUCCESS) { return NULL; }

				newModulesVar->GroupNumber = groupnum;
				newModulesVar->NodeNumber  = modulenum;
				strcpy(newModulesVar->ModuleType, Tempval);
				//loadIOs from file
				SYSTEM_Modules[SYSTEM_Modules_count] = newModulesVar;
				SYSTEM_Modules[SYSTEM_Modules_count ]->hasFileName = false;
				SYSTEM_Modules[SYSTEM_Modules_count]->filecount = 0;

				SYSTEM_Modules_count++;

			}
			else if (((k == 33) && (tempString[0] == 'M') && (tempString[8] == 'o'))) {

				SYSTEM_Modules[SYSTEM_Modules_count - 1]->argU8[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount] = atoi(&tempString[31]);
			  //address = atoi(&tempString[16]);   //comport
				//address = atoi(&tempString[31]);



				SYSTEM_Modules[SYSTEM_Modules_count - 1]->argString[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount][0] = tempString[16];
				SYSTEM_Modules[SYSTEM_Modules_count - 1]->argString[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount][1] = tempString[17];
				SYSTEM_Modules[SYSTEM_Modules_count - 1]->argString[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount][2] = tempString[18];
				SYSTEM_Modules[SYSTEM_Modules_count - 1]->argString[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount][3] = tempString[19];
				SYSTEM_Modules[SYSTEM_Modules_count - 1]->argString[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount][4] = '\0';
				int test3 = 3;
			}
			else if (((k == 10) && (tempString[0] == 'D') && (tempString[3] == 'a'))
			||((k == 7) && (tempString[0] == 'A') && (tempString[3] == 'F'))
			|| ((k == 12) && (tempString[0] == 'M') && (tempString[3] == 'o')))
			{
				int o = 0;
				i = i + 3;
				while (o < 100)
				{
					if (buf[i + 1] != '<') {
						SYSTEM_Modules[SYSTEM_Modules_count - 1]->filename[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount][o] = buf[i + 1];
						i++;
					}
					else { SYSTEM_Modules[SYSTEM_Modules_count - 1]->filename[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount][o] = '\0'; }
					o++;
				}

				if ((k == 10) && (tempString[0] == 'D') && (tempString[3] == 'a')) {
					SYSTEM_Modules[SYSTEM_Modules_count - 1]->fileType[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount] = MODULE_CONFIG_FILE_TYPE_DATAID;
				}
				else if ((k == 7) && (tempString[0] == 'A') && (tempString[3] == 'F')) {
					SYSTEM_Modules[SYSTEM_Modules_count - 1]->fileType[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount] = MODULE_CONFIG_FILE_TYPE_CANOPEN;
				}
				else if (((k == 12) && (tempString[0] == 'M') && (tempString[3] == 'o')))
				{
					SYSTEM_Modules[SYSTEM_Modules_count - 1]->fileType[SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount] = MODULE_CONFIG_FILE_TYPE_MBCONFIG;

				}

				SYSTEM_Modules[SYSTEM_Modules_count - 1]->filecount++;
				SYSTEM_Modules[SYSTEM_Modules_count - 1]->hasFileName = true;

			}


			if (tempString[0] == '?') { continue; }

		}
		else if (readingString) {
			tempString[k] = buf[i];
		}

	}


}

static void ProcessModbusConfigFile(char* buf, int count,U8 GroupNum, U8 ModuleNum, char *port, U8 Address)
{
	int i;
	int k = 0;
	char tempString[150];
	BOOL readingString = false;
	char VariableName[50] ;
	//AddVariable event  to database;
	snprintf(VariableName, sizeof VariableName, "%u.%u.%s.%u.", GroupNum, ModuleNum, port, Address);
	//strcat(newdatabasevar->c.Name, "_Ss");
	//3.3.com1.1.StatusWord
	//snprintf(newdatabasevar->c.Name, 30, modulesStsNameFormat[scnt], ModStatusNr);
	for (i = 0; i < count; i++, k++)
	{
		if (buf[i] == '<')
		{
			k = -1;
			readingString = true;
		}
		else if (buf[i] == '>') {
			readingString = false;
			if ((k == 4) && (tempString[0] == 'n') && (tempString[3] == 'e'))
			{
				int lenN;
				for (lenN = 0; lenN < 38; lenN++) {
					if (buf[i + lenN + 1] == '<') {

						VariableName[11 + lenN] = '\0';
						struct os_db_local* newdatabasevar;
						int result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar, sizeof(struct os_db_local), OS_NO_SUSPEND);
						if (result != OS_SUCCESS) { return NULL; }

						result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar->c.Name, 50, OS_NO_SUSPEND);
						if (result != OS_SUCCESS) { return NULL; }


						newdatabasevar->c.MagicNumber = VAR_MAGIC_NUMBER;
						newdatabasevar->c.HashValue = 0;
						newdatabasevar->c.NextName = NULL;
						strcpy(newdatabasevar->c.Name, VariableName);
						newdatabasevar->c.Type = TYPE_STRING + sizeof(VariableName) - 1;
						newdatabasevar->c.AccessRead = 200;
						newdatabasevar->c.AccessWrite = 200;
						newdatabasevar->c.ScaleType = SCALE_NONE;
						newdatabasevar->c.ScaleValue = 0;
						newdatabasevar->c.Unit = UNIT_NONE;
						newdatabasevar->c.Precision = 0;
						newdatabasevar->c.Value.string = VariableName;
						newdatabasevar->c.TimeStamp = NOLOG_ENABLE;
						newdatabasevar->c.ScaleType = (scaletype_t)0;  /* DisplayScaleType */      \
							newdatabasevar->c.ScaleValue = (scalevalue_t)0;   /* DisplayScaleValue */     \
							newdatabasevar->c.DisplayUnit = (unit_t)0;        /* DisplayUnit */           \
							newdatabasevar->c.DisplayPrecision = 0;                 /* DisplayPrecision*/       \
							newdatabasevar->c.Update = (enum update)LOCAL;/* Update type */           \
							newdatabasevar->c.FirstSubscriber = NULL;              /* FirstSubscriber */       \
							newdatabasevar->c.PreviousVariable = NULL;              /* PreviousVariable */      \
							newdatabasevar->c.NextVariable = NULL;              /* NextVariable */          \
							newdatabasevar->c.ActiveReaders = 0;                 /* ActiveReaders */         \
							newdatabasevar->c.OldValueBeingRead = 0;                 /* OldValueBeingRead */     \
							newdatabasevar->c.TotalLogID = 0;                 /* TotalLogID */            \
							newdatabasevar->c.FiveMinLogID = 0;     /* 5 min log ID */          \
							newdatabasevar->l.LogFlags = NULL;
						newdatabasevar->l.Minimum.string = 0;
						newdatabasevar->l.Maximum.string = 0;
						newdatabasevar->l.Lists = NULL;

						static struct os_db_local LocalnewVars[1];
						LocalnewVars[0] = *newdatabasevar;
						size_t ErrorEntry = 0;
						result = OS_VarDB_CreateLocals(newdatabasevar, 1, &ErrorEntry, AppLocalParameterPosition());
						if (result != 0)
						{
							AppSystemLog(7, "module add failed: %d", result);
						}

						break;
					}
					else {
						VariableName[11 + lenN] = buf[i + lenN + 1];
					}
				}
			}

			if (tempString[0] == '?') { continue; }

		}
		else if (readingString) {
			tempString[k] = buf[i];
		}

	}
}

GetScaleTypeFromString(char* str) {
	if (strcmp("SCALE_NONE", str) == 0) { return 0; }
	else if (strcmp("SCALE_DIV", str) == 0) { return SCALE_DIV; }
	else if (strcmp("SCALE_MUL", str) == 0) { return SCALE_MUL; }
	else if (strcmp("SCALE_EXPMUL", str) == 0) { return SCALE_EXPMUL; }
	else if (strcmp("SCALE_EXPDIV", str) == 0) { return SCALE_EXPDIV; }
	else { return 0; }
}

static U8 GetUnitFromString(char* str) {
	if (strcmp("UNIT_NONE", str) == 0)			{	return 0;	}
	else if (strcmp("UNIT_MBAR", str) == 0)		{	return 1;	}
	else if (strcmp("UNIT_MBAR", str) == 0)		{	return 2;	}
	else if (strcmp("UNIT_BPS", str) == 0)		{	return 3;	}
	else if (strcmp("UNIT_SECOND", str) == 0)	{	return 4;	}
	else if (strcmp("UNIT_MINUTE", str) == 0)	{	return 5;	}
	else if (strcmp("UNIT_HOUR", str) == 0)		{	return 6;	}
	else if (strcmp("UNIT_DAY", str) == 0)		{	return 7;	}
	else if (strcmp("UNIT_MONTH", str) == 0)	{	return 8;	}
	else if (strcmp("UNIT_YEAR", str) == 0)		{	return 9;	}
	else if (strcmp("UNIT_DECIBEL", str) == 0)	{	return 10;	}
	else if (strcmp("UNIT_CELSIUS", str) == 0)	{	return 11;	}
	else if (strcmp("UNIT_HERTZ", str) == 0)	{	return 12;	}
	else if (strcmp("UNIT_METER", str) == 0)	{	return 13;	}
	else if (strcmp("UNIT_MPS", str) == 0)		{	return 14;	}
	else if (strcmp("UNIT_RPM", str) == 0)		{	return 15;	}
	else if (strcmp("UNIT_DEGREE", str) == 0)	{	return 16;	}
	else if (strcmp("UNIT_AMPERE", str) == 0)	{	return 17;	}
	else if (strcmp("UNIT_MAMPERE", str) == 0)	{	return 18;	}
	else if (strcmp("UNIT_VOLT", str) == 0)		{	return 19;	}
	else if (strcmp("UNIT_WATT", str) == 0) { return 20; }
	else if (strcmp("UNIT_KWATT", str) == 0) { return 21; }
	else if (strcmp("UNIT_MWATT", str) == 0) { return 22; }
	else if (strcmp("UNIT_VA", str) == 0) { return 23; }
	else if (strcmp("UNIT_KVA", str) == 0) { return 24; }
	else if (strcmp("UNIT_MVA", str) == 0) { return 25; }
	else if (strcmp("UNIT_VAR", str) == 0) { return 26; }
	else if (strcmp("UNIT_KVAR", str) == 0) { return 27; }
	else if (strcmp("UNIT_MVAR", str) == 0) { return 28; }
	else if (strcmp("UNIT_WATTHOUR", str) == 0) { return 29; }
	else if (strcmp("UNIT_KWATTHOUR", str) == 0) { return 30; }
	else if (strcmp("UNIT_MWATTHOUR", str) == 0) { return 31; }
	else if (strcmp("UNIT_VAH", str) == 0) { return 32; }
	else if (strcmp("UNIT_KVAH", str) == 0) { return 33; }
	else if (strcmp("UNIT_MVAH", str) == 0) { return 34; }
	else if (strcmp("UNIT_VARH", str) == 0) { return 35; }
	else if (strcmp("UNIT_KVARH", str) == 0) { return 36; }
	else if (strcmp("UNIT_MVARH", str) == 0) { return 37; }
	else if (strcmp("UNIT_TIMES", str) == 0) { return 38; }
	else if (strcmp("UNIT_COUNT", str) == 0) { return 39; }
	else if (strcmp("UNIT_GRAVITY", str) == 0) { return 40; }
	else if (strcmp("UNIT_WATTS", str) == 0) { return 41; }
	else if (strcmp("UNIT_VAS", str) == 0) { return 42; }
	else if (strcmp("UNIT_VARS", str) == 0) { return 43; }
	else if (strcmp("UNIT_OHM", str) == 0) { return 44; }
	else if (strcmp("UNIT_DEGREESPSEC", str) == 0) { return 45; }
	else if (strcmp("UNIT_RPMPSEC", str) == 0) { return 46; }
	else if (strcmp("UNIT_HEX", str) == 0) { return 47; }
	else if (strcmp("UNIT_BIN", str) == 0) { return 48; }
	else if (strcmp("UNIT_OCT", str) == 0) { return 49; }
	else if (strcmp("UNIT_NM", str) == 0) { return 50; }
	else if (strcmp("UNIT_NMSEC", str) == 0) { return 51; }
	else if (strcmp("UNIT_NMRPM", str) == 0) { return 52; }
	else if (strcmp("UNIT_PCT", str) == 0) { return 53; }
	else if (strcmp("UNIT_BYTES", str) == 0) { return 54; }
	else if (strcmp("UNIT_KBYTES", str) == 0) { return 55; }
	else if (strcmp("UNIT_MBYTES", str) == 0) { return 56; }
	else if (strcmp("UNIT_PA", str) == 0) { return 57; }
	else if (strcmp("UNIT_HPA", str) == 0) { return 58; }
	else if (strcmp("UNIT_VERSION", str) == 0) { return 59; }
	else if (strcmp("UNIT_DEGREESPRPM", str) == 0) { return 60; }
	else if (strcmp("UNIT_DEGREESPWATT", str) == 0) { return 61; }
	else if (strcmp("UNIT_KWATTPSEC", str) == 0) { return 62; }
	else if (strcmp("UNIT_PSEC", str) == 0) { return 63; }
	else if (strcmp("UNIT_PKWATT", str) == 0) { return 64; }
	else if (strcmp("UNIT_MAC", str) == 0) { return 65; }
	else if (strcmp("UNIT_IP", str) == 0) { return 66; }
	else if (strcmp("UNIT_FARAD", str) == 0) { return 67; }
	else if (strcmp("UNIT_MS", str) == 0) { return 68; }
	else if (strcmp("UNIT_MMETER", str) == 0) { return 69; }
	else if (strcmp("UNIT_CLOCK", str) == 0) { return 70; }
	else if (strcmp("UNIT_PCTPSEC", str) == 0) { return 71; }
	else if (strcmp("UNIT_CUBICMETER", str) == 0) { return 72; }
	else if (strcmp("UNIT_CUBICMETERPH", str) == 0) { return 73; }
	else if (strcmp("UNIT_MWATTSPMIN", str) == 0) { return 74; }
	else if (strcmp("UNIT_PCTPMIN", str) == 0) { return 75; }
	else if (strcmp("UNIT_CMPPMIN", str) == 0) { return 76; }
	else if (strcmp("UNIT_CUBICMETERN", str) == 0) { return 77; }
	else if (strcmp("UNIT_KVOLT", str) == 0) { return 78; }
	else if (strcmp("UNIT_PCTPSEC2", str) == 0) { return 79; }
	else if (strcmp("UNIT_LITR", str) == 0) { return 80; }
	else if (strcmp("UNIT_DEGREESPKWATT", str) == 0) { return 81; }
	else if (strcmp("UNIT_KVARPVOLT", str) == 0) { return 82; }
	else if (strcmp("UNIT_KELVIN", str) == 0) { return 83; }
	else if (strcmp("UNIT_RPMPMPS", str) == 0) { return 84; }
	else if (strcmp("UNIT_KVARPVOLTSEC", str) == 0) { return 85; }
	else if (strcmp("UNIT_METERPSEC2", str) == 0) { return 86; }
	else if (strcmp("UNIT_AMPERESEC", str) == 0) { return 87; }
	else if (strcmp("UNIT_KGRAMMETER2", str) == 0) { return 88; }
	else if (strcmp("UNIT_NMPKWATT", str) == 0) { return 89; }
	else if (strcmp("UNIT_RADIANS", str) == 0) { return 90; }
	else if (strcmp("UNIT_NMPKWATTSEC", str) == 0) { return 91; }
	else if (strcmp("UNIT_NMPRMPSEC", str) == 0) { return 92; }
	else if (strcmp("UNIT_PSEC2", str) == 0) { return 93; }
	else if (strcmp("UNIT_PULSEPREVOLUT", str) == 0) { return 94; }
	else if (strcmp("UNIT_NMPSEC2", str) == 0) { return 95; }
	else if (strcmp("UNIT_MILIHERZ", str) == 0) { return 96; }
	else if (strcmp("UNIT_NMRAD", str) == 0) { return 97; }
	else if (strcmp("UNIT_RADPSEC", str) == 0) { return 98; }
	else if (strcmp("UNIT_PCTPHERZ", str) == 0) { return 99; }
	else if (strcmp("UNIT_PERCENTPSEC2", str) == 0) { return 100; }
	else if (strcmp("UNIT_KGRAMPMETER3", str) == 0) { return 101; }
	else { return 0; }
}

static void ReadModulesConfig()
{
	char fileName[] = "\\DATAIDS.csv";
	char fullPath[30] = "wpline\\";
	int fp;
	int s = 0;
	BOOL HasAdditionalfiles;
	for (s = 0; s < SYSTEM_Modules_count; s++) {
		HasAdditionalfiles = false;
		if (SYSTEM_Modules[s]->hasFileName && (SYSTEM_Modules[s]->fileType[0] == MODULE_CONFIG_FILE_TYPE_DATAID)) {
			if (SYSTEM_Modules[s]->filecount > 1) { HasAdditionalfiles = true; }
			 fp = OS_Open(SYSTEM_Modules[s]->filename[0], PO_RDONLY, 0);
		}
		else {
			if (SYSTEM_Modules[s]->hasFileName) {
				HasAdditionalfiles = true;
			}
			fullPath[7] = '\0';
			strcat(&fullPath, SYSTEM_Modules[s]->ModuleType);
			strcat(&fullPath, fileName);
			 fp = OS_Open(fullPath, PO_RDONLY, 0);
		}
		int bytesRead;
		CHAR buf[50000];

		bytesRead = OS_Read(fp, &buf, 50000);
		if (bytesRead > 50000) {

			OS_DEBUGLOG_make_entry(0, "Error module DATAIDS file too big\r\n");
		}
		OS_Close(fp);
		int i = 0;
		int valueindex = 0;
		int linenum = 0;
		int linevalnum = 0;
		char Temp[40];
		U8 Unit=0;
		U8 Precision = 0;
		U8 ScaleType = 0;
		U32 ScaleValue = 0;
		S64 InitialValue = 0;


		int varnamestart = 0;
		char VarNAME[60];
		snprintf(&VarNAME[0], 10, "%d", SYSTEM_Modules[s]->GroupNumber);
		if (SYSTEM_Modules[s]->GroupNumber < 10) {
			VarNAME[1] = '.';
			snprintf(&VarNAME[2], 10, "%d", SYSTEM_Modules[s]->NodeNumber);
			varnamestart = 3;
		}
		else if (SYSTEM_Modules[s]->GroupNumber < 100) {
			VarNAME[2] = '.';

			snprintf(&VarNAME[3], 10, "%d", SYSTEM_Modules[s]->NodeNumber);
			varnamestart = 4;
		}
		else if (SYSTEM_Modules[s]->GroupNumber < 1000) {

			VarNAME[3] = '.';

			snprintf(&VarNAME[4], 10, "%d", SYSTEM_Modules[s]->NodeNumber);
			varnamestart = 5;
		}
		if (SYSTEM_Modules[s]->NodeNumber > 9) {
			varnamestart++;
		}

		VarNAME[varnamestart++] = '.';

		for (i = 0; i < bytesRead; i++)
		{
			if (buf[i] == ';' || buf[i] == '\n') {
				if (linevalnum == 0 && linenum == 0)
				{
					//process file name
					int k = 1;

				}
				if (linevalnum == 0 && linenum == 1)
				{
					//process revision
					int k = 1;

				}
				if (linevalnum == 0 && linenum == 2)
				{
					//process Target
					int k = 1;

				}
				if (linevalnum == 0 && linenum == 3)
				{
					//process Project num
					int k = 1;

				}
				if (linevalnum == 0 && linenum > 5)
				{
					//process vardb variable

				}
				if (linevalnum == 3 && linenum > 5)
				{
					//process vardb variable
					strcpy(&VarNAME[varnamestart], Temp);
					//remove trailing spaces;
					int t = 0;
					for (t = varnamestart+29; t > 0; t--) 
					{
						if (VarNAME[t] != ' ') {
							break;
						}
						VarNAME[t] = '\0';
					}

				}
				if (linevalnum == 4 && linenum > 5)
				{
					//Scale Value
					ScaleValue = (U32)(atol(&Temp[0]));
				}
				if (linevalnum == 5 && linenum > 5)
				{
					//ScaleType
					//remove trailing spaces;
					int t = 0;
					for (t = 15; t > 0; t--)
					{
						if (Temp[t] != ' ') {
							break;
						}
						Temp[t] = '\0';
					}
					ScaleType = GetScaleTypeFromString(&Temp);
				}

				if (linevalnum == 6 && linenum > 5)
				{
					//Initial Value
					InitialValue = (U64)(atol(&Temp[0]));
				}

				if (linevalnum == 7 && linenum > 5)
				{
					//Precision
					Precision= (U8)(atoi(&Temp[0]));
				}
				if (linevalnum == 9 && linenum > 5)
				{
					//UNIT
					//remove trailing spaces;
					int t = 0;
					for (t = 15; t > 0; t--)
					{
						if (Temp[t] != ' ') {
							break;
						}
						Temp[t] = '\0';
					}
					Unit = GetUnitFromString(&Temp);
				}
				if (linevalnum == 18 && linenum > 5)
				{
					int l;
					for (l = 0; l < 9; l++) {
							int t = 0;
							for (t = 14; t > 0; t--)
							{
								if (Temp[t] != ' ') {
									break;
								}
								Temp[t] = '\0';
							}

							//ADD variable to database


							struct os_db_local* newdatabasevar;
							int result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar, sizeof(struct os_db_local), OS_NO_SUSPEND);
							if (result != OS_SUCCESS) { return NULL; }

							result = OS_Allocate_Memory(GetMemPool(), &newdatabasevar->c.Name, 60, OS_NO_SUSPEND);
							if (result != OS_SUCCESS) { return NULL; }


							newdatabasevar->c.MagicNumber = VAR_MAGIC_NUMBER;
							newdatabasevar->c.HashValue = 0;
							newdatabasevar->c.NextName = NULL;
							strcpy(newdatabasevar->c.Name, VarNAME);
							if (l == 1) {
								strcat(newdatabasevar->c.Name, "_Ss");
							}
							if (l == 2) {
								strcat(newdatabasevar->c.Name, "_E");
							}
							if (l == 3) {
								strcat(newdatabasevar->c.Name, "_I");
							}
							if (l == 4) {
								strcat(newdatabasevar->c.Name, "_Cm");
							}
							if (l == 5) {
								strcat(newdatabasevar->c.Name, "_Ht");
							}
							if (l == 6) {
								strcat(newdatabasevar->c.Name, "_Th");
							}
							if (l == 7) {
								strcat(newdatabasevar->c.Name, "_S");
							}

							if (l == 8) {
								strcat(newdatabasevar->c.Name, "_O");
							}

							if (strcmp("TYPE_S16", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_S16;
							}
							else if (strcmp("TYPE_U16", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_U16;
							}
							else if (strcmp("TYPE_U8", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_U8;
							}
							else if (strcmp("TYPE_S8", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_S8;
							}
							else if (strcmp("TYPE_U32", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_U32;
							}
							else if (strcmp("TYPE_COM", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_COM;
							}
							else if (strcmp("TYPE_S32", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_S32;
							}
							else if (strcmp("TYPE_U64", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_U64;
							}
							else if (strcmp("TYPE_S64", Temp) == 0) {
								newdatabasevar->c.Type = TYPE_S64;
							}
							else {
								int k = 3;
							}



							newdatabasevar->c.AccessRead = 200;
							newdatabasevar->c.AccessWrite = 200;
							newdatabasevar->c.ScaleType = ScaleType;
							newdatabasevar->c.ScaleValue = ScaleValue;
							newdatabasevar->c.Unit = Unit;
							newdatabasevar->c.Precision = Precision;
							newdatabasevar->c.Value.s64 = InitialValue;
							newdatabasevar->c.TimeStamp = NOLOG_ENABLE;
								newdatabasevar->c.DisplayUnit = (unit_t)0;        /* DisplayUnit */           \
								newdatabasevar->c.DisplayPrecision = 0;                 /* DisplayPrecision*/       \
								newdatabasevar->c.Update = (enum update)LOCAL;/* Update type */           \
								newdatabasevar->c.FirstSubscriber = NULL;              /* FirstSubscriber */       \
								newdatabasevar->c.PreviousVariable = NULL;              /* PreviousVariable */      \
								newdatabasevar->c.NextVariable = NULL;              /* NextVariable */          \
								newdatabasevar->c.ActiveReaders = 0;                 /* ActiveReaders */         \
								newdatabasevar->c.OldValueBeingRead = 0;                 /* OldValueBeingRead */     \
								newdatabasevar->c.TotalLogID = 0;                 /* TotalLogID */            \
								newdatabasevar->c.FiveMinLogID = 0;     /* 5 min log ID */          \
								newdatabasevar->l.LogFlags = NULL;
							newdatabasevar->l.Minimum.string = 0;
							newdatabasevar->l.Maximum.string = 0;
							newdatabasevar->l.Lists = NULL;

							static struct os_db_local LocalnewVars[1];
							LocalnewVars[0] = *newdatabasevar;
							size_t ErrorEntry = 0;
							result = OS_VarDB_CreateLocals(newdatabasevar, 1, &ErrorEntry, AppLocalParameterPosition());
							if (result != 0)
							{
								AppSystemLog(7, "module add failed: %d", result);
							}

						}

					int k = 3;
				}

				if (buf[i] == '\n') {
					linevalnum = 0;
					linenum++;
				}
				else {
					linevalnum++;
				}
				valueindex = 0;
			}
			else {
				Temp[valueindex++] = buf[i];

			}


		}

		if (HasAdditionalfiles) {
			int m;
			for (m = 0; m < SYSTEM_Modules[s]->filecount;m++) {
				
				if (SYSTEM_Modules[s]->fileType[m] == MODULE_CONFIG_FILE_TYPE_MBCONFIG) {

					int odf = 2;
					fp = OS_Open(SYSTEM_Modules[s]->filename[m], PO_RDONLY, 0);

					bytesRead = OS_Read(fp, &buf, 50000);
					if (bytesRead > 50000) {

						OS_DEBUGLOG_make_entry(0, "Error module DATAIDS file too big\r\n");
					}
					OS_Close(fp);

					ProcessModbusConfigFile(&buf, bytesRead, SYSTEM_Modules[s]->GroupNumber, SYSTEM_Modules[s]->NodeNumber, SYSTEM_Modules[s]->argString[m], SYSTEM_Modules[s]->argU8[m]);

				}

			}
		}

	}

}

static OS_Services_T osservices = {
	1,1
};





static AVAIL availability = {
	{0},
	0,
	0,
	{0},
	{0},
};


static struct os_db_local OS_LocalVars[] =
{
  // VAR_ELEMENT_LOCAL("V_WP4000StatusText",                    TYPE_STRING + sizeof(A_V_WP4000StatusText) - 1,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   A_V_WP4000StatusText,               0,              0,               NULL,  NOLOG_ENABLE),
  // VAR_ELEMENT_LOCAL("V_ActiveCP1CodeNo",                    TYPE_U16,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,				 U16_MIN,               U16_MAX,                NULL,  NOLOG_ENABLE),
 //  VAR_ELEMENT_LOCAL("V_ActiveCP2CodeNo",                    TYPE_U16,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U16_MIN,              U16_MAX,               NULL,  NOLOG_ENABLE),
  // VAR_ELEMENT_LOCAL("V_ActiveControlProgram1",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),
  // VAR_ELEMENT_LOCAL("V_ActiveControlProgram2",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),
	//VAR_ELEMENT_LOCAL("V_ResetButtonState",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),
	 VAR_ELEMENT_LOCAL("V_AppRequestStopButton",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),
	 VAR_ELEMENT_LOCAL("Chain_Out_Signal",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),
	 VAR_ELEMENT_LOCAL("Chain_In_Signal",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),
	 VAR_ELEMENT_LOCAL("Chain_Enable",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),
	 VAR_ELEMENT_LOCAL("AV_Availability",                    TYPE_U8,      PASSWORD_LEVEL_END_CUSTOMER,       PASSWORD_LEVEL_SUPERVISOR,         SCALE_NONE,   0,       UNIT_NONE,          0,   0,               U8_MIN,              U8_MAX,               NULL,  NOLOG_ENABLE),

	 

};


static DWORD   dwMainIntThreadId;
static HANDLE hMainInterruptThread;


DWORD WINAPI MyMAinINterruptThreadFunction(LPVOID lpParam)
{
	while (true) {
		Sleep(50);

		
	}
	return 0;
}

static void RunMainInterruptThread() {
	// if  delay has passed interrupt blocking thread..
	hMainInterruptThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MyMAinINterruptThreadFunction,       // thread function name
		NULL,          // argument to thread function 
		0,                      // use default creation flags 
		&dwMainIntThreadId);   // returns the thread identifier 

	SetThreadPriority(hMainInterruptThread, THREAD_PRIORITY_HIGHEST);
}


static DWORD   dwThreadSelectorThreadId;
static HANDLE hThreadSelectorThread;
OS_internal_Task currentRunningTask;
 static int nextthreadindex;


DWORD WINAPI MyThreadSelectorThreadFunction(LPVOID lpParam)
{
	int result = 0;
	nextthreadindex = 0;
	while (true) {
		if (currentRunningTask != NULL) {
			
			result = SuspendThread(currentRunningTask->hThread);

			result = SetThreadPriority(currentRunningTask->hThread,  THREAD_PRIORITY_IDLE);
			if(result==-1){
				DWORD dw = GetLastError();

				printf("%d\n", dw);
			}
			if (result < 1)
			{
				printf("%d\n", result);
			}
			
		}
		/*
		if (OS_Tasks_custom[nextthreadindex] != NULL && OS_Tasks_custom[nextthreadindex]->name[2] != '2') {
			nextthreadindex++;

			if (nextthreadindex > max_OS_CustomTaskCount - 1) { nextthreadindex = 0; }
		}
		*/
		if (OS_Tasks_custom[nextthreadindex] != NULL) {
			currentRunningTask = OS_Tasks_custom[nextthreadindex];
			result = SetThreadPriority(currentRunningTask->hThread,THREAD_PRIORITY_ABOVE_NORMAL);
			result = ResumeThread(currentRunningTask->hThread);
			
			Sleep(10);
		}
		
		nextthreadindex++;
		if (nextthreadindex > max_OS_CustomTaskCount-1) { nextthreadindex = 0; }
		


	}


	return 0;
}



STATUS OS_Setsockopt(INT a, INT b, INT c, VOID *d, INT e)
{
	//TODO
	return 0;
}

S32 OS_Recv_Timed(INT a, CHAR *b, U16 c, S16 d, UNSIGNED e) {
	return 0;
}

STATUS OS_SetupComPort(COMM_RESOURCE_T Resource, U32 Baud, U8 Parity, U8 DataBits, U8 StopBits) {
	return 0;
}


static void RunThreadSelectorThread() {
	hThreadSelectorThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MyThreadSelectorThreadFunction,       // thread function name
		0,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadSelectorThreadId);   // returns the thread identifier 
	SetThreadPriority(hMainInterruptThread, THREAD_PRIORITY_NORMAL);
}

void CheckSizesOfInternalstructsandmita()
{
	//size_t orig= 
	//printf("Task structure mita size is %lu and internal is %lu\n", (unsigned long)sizeof(OS_TASK), (unsigned long)sizeof(OS_internal_Task));
	//printf("Mailbox structure mita size is %lu and internal is %lu\n", (unsigned long)sizeof(OS_MAILBOX), (unsigned long)sizeof(OS_internal_MailBox));
}

STATUS MITALIB_Init(U32 IPAddress)
{
	
	STATUS LocalStatus = 0;
	varid_t varid;
    //#ifdef ELEONMITALIBDEBUG
	CheckSizesOfInternalstructsandmita();
	//#endif
	//initialize threads
	//RunMainInterruptThread();
	//RunThreadSelectorThread();

	//Create timer queue
	hTimerQueue = CreateTimerQueue();
	if (NULL == hTimerQueue)
	{
		printf("CreateTimerQueue failed (%d)\n", GetLastError());
		return -10;
	}
	ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (ghMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return -20;
	}


	OS_SERVICES = &osservices;



	size_t ErrorEntry;
	int Status = OS_VarDB_CreateLocals(OS_LocalVars, sizeof(OS_LocalVars) / sizeof(OS_LocalVars[0]), &ErrorEntry, AppLocalParameterPosition());
	if (Status != 0)
	{
		return -30;
	}

	LocalStatus = OS_VarDB_GetVariableID("AV_Availability", &varid);
	if (LocalStatus != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error getting varid for avail \r\n");
		return LocalStatus - 40;
	}
	varid->c.Value.avail = &availability;
	
	InitializeWinSockets();
	InitializeMenu();
	
	S32 LocalIP;
	// Get local IP address of controller

	char WP4000_IP[21];


	strcpy(WP4000_IP, "WP4000_ETH0_IP_Addr\0");

	LocalStatus = OS_VarDB_GetVariableID(WP4000_IP, &varid);
	if (LocalStatus != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error getting varid for local IP\r\n");
		//CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Local IP error");
#if defined I104S_DEBUG
		OS_com_printf("Error getting varid for local IP\r\n");
#endif
		return LocalStatus - 50;
	}
	LocalStatus = OS_VarDB_UpdateVariable(varid, &IPAddress, sizeof(IPAddress));
	if (LocalStatus != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error updating local IP\r\n");
		//CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Failed to read local IP");

		return LocalStatus - 60;
	}

	LocalStatus = OS_VarDB_ReadVariable(varid, &(LocalIP), sizeof(LocalIP), NULL);
	if (LocalStatus != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error reading local IP\r\n");
		//CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Failed to read local IP");
		return LocalStatus - 70;
	}
	
	menuserver = MenuServer_New(OS_MenuGroups, 20, LocalIP);
	int fp = OS_Open("wpline\\MODULE_CONFIG.XML", PO_RDONLY, 0);
	if (fp < 0) {
		OS_DEBUGLOG_make_entry(0, "Error opening module config file\r\n");
		return -80;
	}
	int bytesRead;
	CHAR buf[5000];
	bytesRead = OS_Read(fp, &buf, 5000);
	if (bytesRead > 5000) {

		OS_DEBUGLOG_make_entry(0, "Error module config file too big\r\n");
	}
	
	OS_Close(fp);
	ProcessModulesConfigFile(&buf, bytesRead);
	ReadModulesConfig();


	return 0;
}





STATUS MITALIB_ctrl()
{
	return 0;
}

STATUS MitaMenuMenu_ctrl() {
	MenuServer_Control(menuserver);
	return 0;
}

STATUS MitaMenuMenuInitialize(U32 IPAddress) {

	STATUS LocalStatus = 0;
	varid_t varid;

	S32 LocalIP;
	// Get local IP address of controller

	char WP4000_IP[21];


	strcpy(WP4000_IP, "WP4000_ETH0_IP_Addr\0");

	LocalStatus = OS_VarDB_GetVariableID(WP4000_IP, &varid);
	if (LocalStatus != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error getting varid for local IP\r\n");
		//CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Local IP error");
#if defined I104S_DEBUG
		OS_com_printf("Error getting varid for local IP\r\n");
#endif
		return LocalStatus;
	}
	LocalStatus = OS_VarDB_UpdateVariable(varid, &IPAddress, sizeof(IPAddress));
	if (LocalStatus != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error updating local IP\r\n");
		//CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Failed to read local IP");

		return LocalStatus;
	}

	LocalStatus = OS_VarDB_ReadVariable(varid, &(LocalIP), sizeof(LocalIP), NULL);
	if (LocalStatus != OS_SUCCESS)
	{
		OS_DEBUGLOG_make_entry(0, "Error reading local IP\r\n");
		//CustomLog_MakeEntry(slave->Status->InterfaceEventLog, "Failed to read local IP");
		return LocalStatus;
	}
	LocalStatus = MenuServer_LoadParameters(menuserver, true, LocalIP, 8080, 10);
	LocalStatus = MenuServer_StartCyclic(menuserver, 15);
	if (LocalStatus != OS_SUCCESS) { return LocalStatus; }
	//InitalizeTaskScheduler();
}
