#ifndef FILE_MITA_H
#define FILE_MITA_H
#include <os_main.h>

STATUS MITALIB_Init();


//VOID va_start(va_list list, const char *format);
//VOID va_end(va_list listt);

extern char root_folder[512];    // folder where controller files are located (WP4x00)

OS_Services_T *OS_SERVICES;


STATUS OS_internal_AddBackupFileNames(varid_t StateId, char* exports, char* locals, char* backups);



OS_MEMORY_POOL *GetMemPool();	// dummy function for WP4200 compatibility
//int OS_Allocate_Memory(OS_MEMORY_POOL* /*dummy*/, void**, int, int/*dummy*/);
//int OS_Deallocate_Memory(void*);

/* Function to test if OS and APP is compatible, must be placed as first function */
STATUS OS_ValidateAPI(U16 AppMajor, U16 AppMinor, const char* AppLinkTime, const char* ReleaseTag, const char* FileName);

/* OS1 vectors */

/* Task functions */

OPTION OS_Change_Preemption(OPTION preempt);
OPTION OS_Change_Priority(OS_TASK *task, OPTION new_priority);
UNSIGNED OS_Change_Time_Slice(OS_TASK *task, UNSIGNED time_slice);
UNSIGNED OS_Check_Stack(VOID);
STATUS OS_Create_Task
(OS_TASK *task, CHAR *name,
	VOID(*task_entry)(UNSIGNED, VOID *), UNSIGNED argc,
	VOID *argv, VOID *stack_address, UNSIGNED stack_size,
	OPTION priority, UNSIGNED time_slice, OPTION preempt,
	OPTION auto_start);
OS_TASK * OS_Current_Task_Pointer(VOID);
STATUS OS_Delete_Task(OS_TASK *task);
UNSIGNED OS_Established_Tasks(VOID);
VOID OS_Relinquish(VOID);
STATUS OS_Reset_Task
(OS_TASK *task, UNSIGNED argc, VOID *argv);
STATUS OS_Resume_Task(OS_TASK *task);
STATUS OS_Sleep(UNSIGNED ticks);
STATUS OS_Suspend_Task(OS_TASK *task);
STATUS OS_Task_Information
(OS_TASK *task, CHAR *name, DATA_ELEMENT *status,
	UNSIGNED *scheduled_count, OPTION *priority,
	OPTION *preempt, UNSIGNED *time_slice, VOID **stack_base,
	UNSIGNED *stack_size, UNSIGNED *minimum_stack);
UNSIGNED OS_Task_Pointers
(OS_TASK **pointer_list, UNSIGNED maximum_pointers);
STATUS OS_Terminate_Task(OS_TASK *task);

/* Dynamic memory functions */
STATUS OS_Allocate_Memory(OS_MEMORY_POOL *pool, VOID **return_pointer,UNSIGNED size, UNSIGNED suspend);
STATUS OS_Create_Memory_Pool
(OS_MEMORY_POOL *pool, CHAR *name, VOID *start_address,
	UNSIGNED pool_size, UNSIGNED min_allocation,
	OPTION suspend_type);
STATUS OS_Deallocate_Memory(VOID *memory);
STATUS OS_Delete_Memory_Pool(OS_MEMORY_POOL *pool);
UNSIGNED OS_Established_Memory_Pools(VOID);
STATUS OS_Memory_Pool_Information
(OS_MEMORY_POOL *pool, CHAR *name, VOID **start_address,
	UNSIGNED *pool_size, UNSIGNED *min_allocation,
	UNSIGNED *available, OPTION *suspend_type,
	UNSIGNED *tasks_waiting, OS_TASK **first_task);
UNSIGNED OS_Memory_Pool_Pointers
(OS_MEMORY_POOL **pointer_list, UNSIGNED maximum_pointers);

/* Partition memory functions */

STATUS OS_Allocate_Partition(OS_PARTITION_POOL *pool, VOID **return_pointer,
	UNSIGNED suspend);
STATUS OS_Create_Partition_Pool(OS_PARTITION_POOL *pool, CHAR *name, VOID *start_address,
	UNSIGNED pool_size, UNSIGNED partition_size,
	OPTION suspend_type);
STATUS OS_Deallocate_Partition(VOID *partition);
STATUS OS_Delete_Partition_Pool(OS_PARTITION_POOL *pool);
UNSIGNED OS_Established_Partition_Pools(VOID);
STATUS OS_Partition_Pool_Information
(OS_PARTITION_POOL *pool, CHAR *name, VOID **start_address,
	UNSIGNED *pool_size, UNSIGNED *partition_size,
	UNSIGNED *available, UNSIGNED *allocated,
	OPTION *suspend_type, UNSIGNED *tasks_waiting,
	OS_TASK **first_task);
UNSIGNED OS_Partition_Pool_Pointers
(OS_PARTITION_POOL **pointer_list,
	UNSIGNED maximum_pointers);

/* Mailbox functions  */

STATUS OS_Broadcast_To_Mailbox
(OS_MAILBOX *mailbox, VOID *message, UNSIGNED suspend);
STATUS OS_Create_Mailbox
(OS_MAILBOX *mailbox, CHAR *name, OPTION suspend_type);
STATUS OS_Delete_Mailbox(OS_MAILBOX *mailbox);
UNSIGNED OS_Established_Mailboxes(VOID);
STATUS OS_Mailbox_Information(OS_MAILBOX *mailbox, CHAR *name, OPTION *suspend_type,
	OPTION *message_present, UNSIGNED *tasks_waiting,
	OS_TASK **first_task);
UNSIGNED OS_Mailbox_Pointers(OS_MAILBOX **pointer_list, UNSIGNED maximum_pointers);
STATUS OS_Receive_From_Mailbox(OS_MAILBOX *mailbox, VOID *message, UNSIGNED suspend);
STATUS OS_Reset_Mailbox(OS_MAILBOX *mailbox);
STATUS OS_Send_To_Mailbox(OS_MAILBOX *mailbox, VOID *message, UNSIGNED suspend);

/* Queue functions */

STATUS OS_Broadcast_To_Queue(OS_QUEUE *queue, VOID *message, UNSIGNED size,
	UNSIGNED suspend);
STATUS OS_Create_Queue(OS_QUEUE *queue, CHAR *name, VOID *start_address,
	UNSIGNED queue_size, OPTION message_type,
	UNSIGNED message_size, OPTION suspend_type);
STATUS OS_Delete_Queue(OS_QUEUE *queue);
UNSIGNED OS_Established_Queues(VOID);
STATUS OS_Queue_Information(OS_QUEUE *queue, CHAR *name, VOID **start_address,
	UNSIGNED *queue_size, UNSIGNED *available,
	UNSIGNED *messages, OPTION *message_type,
	UNSIGNED *message_size, OPTION *suspend_type,
	UNSIGNED *tasks_waiting, OS_TASK **first_task);
UNSIGNED OS_Queue_Pointers(OS_QUEUE **pointer_list, UNSIGNED maximum_pointers);
STATUS OS_Receive_From_Queue(OS_QUEUE *queue, VOID *message, UNSIGNED size,
	UNSIGNED *actual_size, UNSIGNED suspend);
STATUS OS_Reset_Queue(OS_QUEUE *queue);
STATUS OS_Send_To_Front_Of_Queue(OS_QUEUE *queue, VOID *message, UNSIGNED size,
	UNSIGNED suspend);
STATUS OS_Send_To_Queue(OS_QUEUE *queue, VOID *message, UNSIGNED size,
	UNSIGNED suspend);

/* Pipe functions */

STATUS OS_Broadcast_To_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size,
	UNSIGNED suspend);
STATUS OS_Create_Pipe(OS_PIPE *pipe, CHAR *name, VOID *start_address,
	UNSIGNED pipe_size, OPTION message_type,
	UNSIGNED message_size, OPTION suspend_type);
STATUS OS_Delete_Pipe(OS_PIPE *pipe);
UNSIGNED  OS_Established_Pipes(VOID);
STATUS OS_Pipe_Information(OS_PIPE *pipe, CHAR *name, VOID **start_address,
	UNSIGNED *pipe_size, UNSIGNED *available,
	UNSIGNED *messages, OPTION *message_type,
	UNSIGNED *message_size, OPTION *suspend_type,
	UNSIGNED *tasks_waiting, OS_TASK **first_task);
UNSIGNED OS_Pipe_Pointers(OS_PIPE **pointer_list, UNSIGNED maximum_pointers);
STATUS OS_Receive_From_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size,
	UNSIGNED *actual_size, UNSIGNED suspend);
STATUS OS_Reset_Pipe(OS_PIPE *pipe);
STATUS OS_Send_To_Front_Of_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size,
	UNSIGNED suspend);
STATUS OS_Send_To_Pipe(OS_PIPE *pipe, VOID *message, UNSIGNED size,
	UNSIGNED suspend);

/* Semaphore functions */

STATUS OS_Create_Semaphore(OS_SEMAPHORE *semaphore, CHAR *name,
	UNSIGNED initial_count, OPTION suspend_type);
STATUS OS_Delete_Semaphore(OS_SEMAPHORE *semaphore);
UNSIGNED OS_Established_Semaphores(VOID);
STATUS OS_Obtain_Semaphore(OS_SEMAPHORE *semaphore, UNSIGNED suspend);
STATUS OS_Release_Semaphore(OS_SEMAPHORE *semaphore);
STATUS OS_Reset_Semaphore(OS_SEMAPHORE *semaphore, UNSIGNED initial_count);
STATUS OS_Semaphore_Information(OS_SEMAPHORE *semaphore, CHAR *name,
	UNSIGNED *current_count, OPTION *suspend_type,
	UNSIGNED *tasks_waiting, OS_TASK **first_task);
UNSIGNED OS_Semaphore_Pointers(OS_SEMAPHORE **pointer_list, UNSIGNED maximum_pointers);

/* Event group functions */

STATUS OS_Create_Event_Group(OS_EVENT_GROUP *group, CHAR *name);
STATUS OS_Delete_Event_Group(OS_EVENT_GROUP *group);
UNSIGNED OS_Established_Event_Groups(VOID);
STATUS OS_Event_Group_Information(OS_EVENT_GROUP *group, CHAR *name, UNSIGNED *event_flags,
	UNSIGNED *tasks_waiting, OS_TASK **first_task);
UNSIGNED OS_Event_Group_Pointers(OS_EVENT_GROUP **pointer_list, UNSIGNED maximum_pointers);
STATUS OS_Retrieve_Events(OS_EVENT_GROUP *group, UNSIGNED requested_flags,
	OPTION operation, UNSIGNED *retrieved_flags,
	UNSIGNED suspend);
STATUS OS_Set_Events(OS_EVENT_GROUP *group, UNSIGNED events, OPTION operation);

/* Signal functions */

UNSIGNED OS_Control_Signals(UNSIGNED signal_enable_mask);
UNSIGNED OS_Receive_Signals(VOID);
STATUS OS_Register_Signal_Handler(VOID(*signal_handler)(UNSIGNED));
STATUS OS_Send_Signals(OS_TASK *task, UNSIGNED signals);

/* Timer functions */

STATUS OS_Control_Timer(OS_TIMER *timer, OPTION enable);
STATUS OS_Create_Timer(OS_TIMER *timer, CHAR *name,
	VOID(*expiration_routine)(UNSIGNED), UNSIGNED id,
	UNSIGNED initial_time, UNSIGNED reschedule_time,
	OPTION enable);
STATUS OS_Delete_Timer(OS_TIMER *timer);
UNSIGNED OS_Established_Timers(VOID);
/* Missing function?
STATUS Get_Remaining_Time(OS_TIMER *timer, UNSIGNED *remaining_time); */
STATUS OS_Reset_Timer(OS_TIMER *timer, VOID(*expiration_routine)(UNSIGNED),
	UNSIGNED initial_time, UNSIGNED reschedule_timer,
	OPTION enable);
UNSIGNED OS_Retrieve_Clock(VOID);
VOID OS_Set_Clock(UNSIGNED new_value);
STATUS OS_Timer_Information(OS_TIMER *timer, CHAR *name, OPTION *enable,
	UNSIGNED *expirations, UNSIGNED *id,
	UNSIGNED *initial_time, UNSIGNED *reschedule_time);
UNSIGNED OS_Timer_Pointers(OS_TIMER **pointer_list, UNSIGNED maximum_pointers);

/* Interrupt functions */

STATUS OS_Activate_HISR(OS_HISR *hisr);
INT OS_Control_Interrupts(INT new_level);
STATUS OS_Create_HISR(OS_HISR *hisr, CHAR *name, VOID(*hisr_entry)(VOID),
	OPTION priority, VOID *stack_address,
	UNSIGNED stack_size);
OS_HISR * OS_Current_HISR_Pointer(VOID);
STATUS OS_Delete_HISR(OS_HISR *hisr);
UNSIGNED OS_Established_HISRs(VOID);
STATUS OS_HISR_Information(OS_HISR *hisr, CHAR *name, UNSIGNED *scheduled_count,
	DATA_ELEMENT *priority, VOID **stack_base,
	UNSIGNED *stack_size, UNSIGNED *minimum_stack);
UNSIGNED OS_HISR_Pointers(OS_HISR **pointer_list, UNSIGNED maximum_pointers);
INT OS_Local_Control_Interrupts(INT new_level);
STATUS OS_Register_LISR(INT vector, VOID(*new_lisr)(INT),
	VOID(**old_lisr)(INT));
VOID * OS_Setup_Vector(INT vector, VOID *new_vector);

/* System diagnostics functions */

VOID OS_Disable_History_Saving(VOID);
VOID OS_Enable_History_Saving(VOID);
CHAR * OS_License_Information(VOID);
VOID OS_Make_History_Entry(UNSIGNED param1, UNSIGNED param2, UNSIGNED param3);
CHAR * OS_Release_Information(VOID);
STATUS OS_Retrieve_History_Entry(DATA_ELEMENT *id, UNSIGNED *param1, UNSIGNED *param2,
	UNSIGNED *param3, UNSIGNED *time, OS_TASK **task,
	OS_HISR **hisr);

/* I/O driver functions */

STATUS OS_Create_Driver(OS_DRIVER *driver, CHAR *name,
	VOID(*driver_entry)(OS_DRIVER *, OS_DRIVER_REQUEST *));
STATUS OS_Delete_Driver(OS_DRIVER *driver);
UNSIGNED OS_Driver_Pointers(OS_DRIVER **pointer_list, UNSIGNED maximum_pointers);
UNSIGNED OS_Established_Drivers(VOID);
VOID OS_Protect(OS_PROTECT *protect_struct);
STATUS OS_Request_Driver(OS_DRIVER *driver, OS_DRIVER_REQUEST *request);
STATUS OS_Resume_Driver(OS_TASK *task);
STATUS OS_Suspend_Driver(VOID(*terminate_routine)(VOID *), VOID *information,
	UNSIGNED timeout);
VOID OS_Unprotect(VOID);

/* OS2 vectors */

/* CRC functions */

unsigned int crc32(const unsigned char *address, unsigned int size,
	unsigned int crc);


/* Log functions */

STATUS OS_EVENTLOG_make_entry(U16 code, const char *text_format, ...);
STATUS OS_SYSLOG_make_entry(U16 code, const char *text_format, ...);

/* Variable DB functions */

STATUS OS_VarDB_CreateLocals(struct os_db_local Variables[],
	size_t Entries,
	size_t *ErrorEntry,
	const char* ParamID);

STATUS OS_VarDB_CreateParameters(struct os_db_parameter Variables[],
	size_t Entries,
	size_t *ErrorEntry,
	const char* ParamID);

STATUS OS_VarDB_CreateOutputParameters(struct os_db_output_parameter Variables[],
	size_t Entries,
	size_t *ErrorEntry,
	const char* ParamID);

STATUS OS_VarDB_CreateTimers(struct os_db_timer Variables[],
	size_t Entries,
	size_t *ErrorEntry);

STATUS OS_SUM_CreateSummations(struct os_db_summation Variables[],
	size_t Entries,
	size_t *ErrorEntry,
	const char* BackupID);

STATUS OS_VarDB_CreateBackups(struct os_db_backup Variables[],
	size_t Entries,
	size_t *ErrorEntry,
	const char* ParamID,
	const char* FileID);

STATUS OS_VarDB_CreateAliases(struct os_db_alias Aliases[],
	size_t Entries,
	size_t *ErrorEntry);

STATUS OS_VarDB_GetVariableID(const char *VariableName,
	varid_t *VarId);

STATUS OS_VarDB_GetVariableType(varid_t VariableId,
	type_t *Type);

STATUS OS_VarDB_ReadVariable(varid_t VariableId,
	void *Value,
	size_t Length,
	time_t *TimeStamp);

STATUS OS_VarDB_UpdateVariableByName(const char *VariableName,
	void* Value,
	size_t Length);

STATUS OS_VarDB_UpdateVariable(varid_t VariableId,
	void*   Value,
	size_t  Length);

STATUS OS_VarDB_UpdateVariableConditional(varid_t VariableId,
	void*   Value,
	size_t  Length);

STATUS OS_VarDB_UpdateVariableConditionalByName(const char* VariableName,
	void*       Value,
	size_t      Length);

STATUS OS_VarDB_UpdateReady(varid_t VariableId);

STATUS OS_VarDB_UpdateU8(varid_t VariableID, U8 Value);

STATUS OS_VarDB_UpdateS8(varid_t VariableID, S8 Value);

STATUS OS_VarDB_UpdateU16(varid_t VariableID, U16 Value);

STATUS OS_VarDB_UpdateS16(varid_t VariableID, S16 Value);

STATUS OS_VarDB_UpdateU32(varid_t VariableID, U32 Value);

STATUS OS_VarDB_UpdateS32(varid_t VariableID, S32 Value);

STATUS OS_VarDB_UpdateU64(varid_t VariableID, U64 Value);

STATUS OS_VarDB_UpdateS64(varid_t VariableID, S64 Value);

STATUS OS_VarDB_UpdateString(varid_t VariableID, const char* Value);

STATUS OS_VarDB_LockOutputParameter(varid_t VariableId, U32 ObjectID);

STATUS OS_VarDB_UpdateLockedOutputParameter(varid_t VariableId,
	void *Value,
	size_t Length,
	U32 ObjectID);


STATUS OS_VarDB_ReadVariableByName(const char *VariableName,
	void* Value,
	size_t len,
	time_t *TimeStamp);

STATUS OS_VarDB_ObtainNewObjectID(U32* ObjectID);

STATUS OS_VarDB_ParameterRestoreDefault(varid_t VariableId);

STATUS OS_ReadVariables(struct ModulInOut ModulVars[],
	size_t Entries);

STATUS OS_WriteVariables(struct ModulInOut ModulVars[],
	size_t Entries);

STATUS OS_WriteVariablesConditional(struct ModulInOut ModulVars[],
	size_t Entries);

STATUS OS_DoesVariablesExist(struct ModulInOut ModulVars[],
	size_t Entries);

/* Subscription functions */

STATUS OS_SubHandl_Subscribe(SUBSCRIPTION *subscription,
	varid_t varid,
	enum subscriber_type type,
	union subscriber subscriber);

void OS_SubHandl_InitSubscriptionBlocks(SUBSCRIPTION subscriptions[],
	size_t count);

STATUS OS_SubHandl_Unsubscribe(SUBSCRIPTION subscriptions[],
	size_t count);

STATUS OS_SubHandl_SubscribeSignal(SUBSCRIPTION subscriptions[],
	size_t count,
	varid_t varids[],
	OS_TASK *task);

STATUS OS_SubHandl_SubscribeEvent(SUBSCRIPTION subscriptions[],
	size_t count,
	varid_t varids[],
	OS_EVENT_GROUP *group);

STATUS OS_SubHandl_SubscribeMailbox(SUBSCRIPTION subscriptions[],
	size_t count,
	varid_t varids[],
	OS_MAILBOX *mailbox);

STATUS OS_SubHandl_SubscribeQueue(SUBSCRIPTION subscriptions[],
	size_t count,
	varid_t varids[],
	OS_QUEUE *queue,
	UNSIGNED message_size);

/* Obsolete functions in VarDB, may be reused */

STATUS OS_SubHandl_SubscribeFunction(SUBSCRIPTION subscriptions[],
	size_t count, varid_t varids[],
	STATUS(*Update)(varid_t VariableId,
		void* Message,
		U16 Length));

/* Task/module functions */

STATUS OS_module_task_destruct(OS_TASK *task);
STATUS OS_module_task_create(OS_TASK *task, CHAR *name, VOID(*task_entry) (UNSIGNED, VOID *), UNSIGNED argc, VOID *argv, UNSIGNED stack_size, OPTION priority, UNSIGNED time_slice, OPTION preempt, OPTION auto_start,OS_MEMORY_POOL *pool);
STATUS OS_module_HISR_destruct(OS_HISR *hisr);
STATUS OS_module_HISR_create(OS_HISR *hisr, CHAR *name, VOID(*hisr_entry) (VOID),
	OPTION priority, UNSIGNED stack_size,
	OS_MEMORY_POOL *pool);
STATUS OS_module_queue_destruct(OS_QUEUE *queue);
STATUS OS_module_queue_create(OS_QUEUE *queue, char *name, UNSIGNED queue_size,
	OPTION message_type, UNSIGNED message_size,
	OPTION suspend_type, OS_MEMORY_POOL *pool);
STATUS OS_module_destruct_all_v(int count, va_list ap);
STATUS OS_module_destruct_all(int count, ...);
STATUS OS_module_start_all(int count, ...);
STATUS OS_module_stop_all(int count, ...);
STATUS OS_module_create_all(OS_MEMORY_POOL *pool, OPTION auto_start, int count, ...);

/* Status code functions */
U8 OS_StatusCodeActive(U16 StatusCodeNo);

void OS_StatusCodeSetReset(U16 StatusCodeNo);
void OS_StatusCodeResetAll(U8 ResetPasswordLevel, U8 ResetType);
void OS_StatusCodeBlockReset(void);
void OS_StatusCodeUnblockReset(void);
void OS_DisableStatusCode(U16 StatusCodeNo);
void OS_StcodeMainScan(void);

/* Timevar functions */

STATUS OS_timevar_create_timervariable(UNSIGNED interval, varid_t varid, OS_TIMER *timer);
STATUS OS_timevar_change_timervariable(U32 interval, OS_TIMER *timer);

/* Debug functions */

void OS_com_printf(const char *format, ...);

/* New menu functions 2002-03-15 */

STATUS OS_CreateMenuGroup(struct menu_group_struct *newgroup, char *name);
STATUS OS_CreateMenus(char *groupname, struct menu_struct *newmenu,
	size_t elements);
STATUS OS_AddLines(char *groupname, char *menuname,
	struct line_struct *newline, size_t elements);
STATUS OS_CreateButtons(struct buttonlink_struct *buttonlink,
	struct button_struct *newbutton, size_t elements);

/* Clock functions */

time_t OS_GetTimeInMs(void);

/* New status code functions 2003-01-29 */
U8 OS_StatusCodeActiveErr(U16 StatusCodeNo, U8 *StsActive);
U16 OS_NoOfActiveStatusCodes(void);


/* SW Watchdog API */
STATUS OS_Watchdog_Get_Schedule_time(UNSIGNED *wd_counttime);
STATUS OS_Watchdog_Hit_Item(U32 WD_Item);
STATUS OS_Watchdog_Change_Item(U32 WD_Item, UNSIGNED count, UNSIGNED nof_timeouts, UNSIGNED enabled);
/* New Status code API function */
S32 OS_ActivateStatusCode(U16 StatusCodeNo);

/* New Status code API function */
void OS_StsDetailMenuLink(void *Info, U32 Par);

/* New log functions */
STATUS OS_ALARMLOG_make_entry(U16 code, const char *text_format, ...);
STATUS OS_CALLLOG_make_entry(U16 code, const char *text_format, ...);

/* Action server API */
//U8 OS_dataprov_register_api(const data_provider_api_t *api);
void* OS_alloc_objects(U16 count);
void* OS_alloc_bytes(U16 count);
U8 OS_dealloc_objects(void *obj, U16 count);


int InitializeWinSockets();
/* New low level OS functions */
STATUS OS_Socket(S16, S16, S16);

STATUS OS_Close_Socket(INT);

STATUS OS_Setsockopt(INT, INT, INT, VOID *, INT);

STATUS OS_Getsockopt(INT, INT, INT, VOID *, INT *);

STATUS OS_Listen(INT, U16);

STATUS OS_Bind(INT, struct addr_struct *, S16);

STATUS OS_Get_Host_By_Name(CHAR *name, OS_HOSTENT *host_entry);

STATUS OS_Accept(INT, struct addr_struct *, S16 *);

STATUS OS_Connect(INT, struct addr_struct *, S16);

STATUS OS_Abort(INT socketd);

S32 OS_Recv(INT, CHAR *, U16, S16);

U32 OS_Send(INT, CHAR *, U16, S16);

U32 OS_Recv_From(INT, CHAR *, U16, S16, struct addr_struct *, S16 *);

U32 OS_Send_To(INT, CHAR *, U16, S16, struct addr_struct *, S16);

//VOID OS_FD_Init(FD_SET *fd);

//VOID OS_FD_Set(INT, FD_SET *);

//STATUS OS_Select(INT, FD_SET *, FD_SET *, FD_SET *, UNSIGNED);

STATUS OS_Fcntl(INT, S16, S16);
INT OS_Get_Host_Name(CHAR *name, INT name_length);


/* New Nucleus FILE functions */
STATUS OS_Open_Disk(CHAR *path);

STATUS OS_Close_Disk(CHAR *path);

VOID OS_Disk_Abort(CHAR *path);

STATUS OS_Make_Dir(CHAR *name);

STATUS OS_Open(CHAR *name, U16 flag, U16 mode);

S32 OS_Read(INT fd, CHAR *buf, S32 count);

S32 OS_Write(INT fd, CHAR *buf, S32 count);

S32 OS_Seek(INT fd, INT32 offset, S16 origin);

STATUS OS_Truncate(INT fd, S32 offset);

STATUS OS_Flush(INT fd);

STATUS OS_Close(INT fd);

STATUS OS_Set_Attributes(CHAR *name, U8 newattr);

STATUS OS_Get_Attributes(U8 *attr, CHAR *name);

STATUS OS_Rename(CHAR *name, CHAR *newname);

STATUS OS_Delete(CHAR *name);

STATUS OS_Remove_Dir(CHAR *name);

STATUS OS_Format(S16 driveno, FMTPARMS *pfmt);

STATUS OS_FreeSpace(CHAR *path, U8 *secpcluster, U16 *bytepsec,
	U32 *freecluster, U32 *totalcluster);

STATUS OS_Get_First(DSTAT *statobj, CHAR *pattern);

STATUS OS_Get_Next(DSTAT *statobj);

VOID OS_Done(DSTAT *statobj);

STATUS OS_Set_Default_Drive(U16 driveno);

U16 OS_Get_Default_Drive(VOID);

STATUS OS_Set_Current_Dir(CHAR *path);

STATUS OS_Current_Dir(UINT8 *drive, CHAR *path);

INT OS_Become_File_User(VOID);

VOID OS_Release_File_User(VOID);

INT OS_Check_File_User(VOID);

/* Communication resources (COM ports) manager */
STATUS OS_CommReserve(TOKEN_T* Token, COMM_RESOURCE_T Resource, varid_t* VarId);
STATUS OS_CommRelease(TOKEN_T* Token);
STATUS OS_CommClientsWaiting(TOKEN_T Token);
STATUS OS_CommDialPPP(TOKEN_T Token, char* Number, char* Login, char* Password,
	varid_t* NotifyLinkUp, varid_t* NotifyLinkDn);
STATUS OS_CommGetLocalIp(TOKEN_T Token, U8* IpAddr);
STATUS OS_CommGetRemoteIp(TOKEN_T Token, U8* IpAddr);
STATUS OS_CommReleasePPP(TOKEN_T Token);

/* Functions to change display of variables */
STATUS OS_VarDB_GetDisplayScaleTypeValueUnitAndPrecision(varid_t VariableId,
	scaletype_t* ScaleType,
	scalevalue_t* ScaleValue,
	unit_t* Unit,
	precision_t* Precision);

STATUS OS_VarDB_SetDisplayScaleTypeValueUnitAndPrecision(varid_t VariableId,
	scaletype_t ScaleType,
	scalevalue_t ScaleValue,
	unit_t Unit,
	precision_t Precision);

/* Function for triggering total log */
STATUS OS_TOTLOG_SetTrig(void);

/* Function for adding a menu */
STATUS OS_AddMenu(struct menu_struct *NewMenu,
	struct line_struct NewLines[2],
	char *GroupName, char *ParentMenu,
	char *LinkText, char *MenuReturnText,
	char *MenuName, U8 ViewPasswordLevel);

/* Function for registering an extra password verification function */
void OS_RegisterPasswordVerifier(S16(*func)(char*, char*, U8));

/* Functions from averaging module in 5 min log */
STATUS OS_U64_multiply(U64 A, U64 B, U64* low_U64, U64* high_U64);

STATUS OS_U128_add(U64 AL, U64 AH, U64 BL, U64 BH, U64* low_U64, U64* high_U64);

STATUS OS_VarDB_GetVariableLimits(varid_t VariableId,
	value_t* Minimum,
	value_t* Maximum);

/* Missing Nucleus NET functions */
//INT OS_FD_Check(INT, FD_SET *);

STATUS OS_Is_Connected(INT);

/* New Status code API function */
STATUS OS_StatusCodeInit(int InterfaceVersion,
	STATUS_CODE_CONTROL_BLOCK *ControlBlock,
	struct sts_statuscode_structure *InitTable,
	size_t Size,
	const char *ParamameterFile,
	const char *BackupFile);

/* New functions added 040413 */
STATUS OS_DEBUGLOG_make_entry(U16 code, const char *text_format, ...);

/* New watchdog functions FKL 040913 */
STATUS OS_Watchdog_Create_Item(const char* Name, UNSIGNED Count, UNSIGNED Timeouts, UNSIGNED Enable, U32* WD);

STATUS OS_Watchdog_SetOptions(U32 WD_Item, enum WD_Options Option, U32 Action);

S32 OS_Recv_Timed(INT, CHAR *, U16, S16, UNSIGNED);

U32 OS_Recv_From_Timed(INT, CHAR *, U16, S16, struct addr_struct *, S16 *, UNSIGNED);

VOID OS_HTTP_Register_Plugin(INT(*plug_in)(OS_REQUEST *), CHAR *uri);

VOID OS_ENC_Encrypt(CHAR *, CHAR *, INT);

VOID OS_ENC_Decrypt(CHAR *, CHAR *, INT);

STATUS OS_Retrieve_Backup_File_Names(varid_t StateId, char** exports, char** locals, char** backups);

U32 OS_GetTimeTickStart(void);

U32 OS_GetTimeTickStop(U32 TimerTickStart);

VOID OS_SetSafetyChainMode(U8 Mode);

STATUS OS_SubHandl_SubscribeFunctionWithRef(SUBSCRIPTION subscriptions[],
	size_t count, varid_t varids[],
	UNSIGNED Ref1[], UNSIGNED Ref2[],
	STATUS(*Update)(varid_t VariableId,
		void* Message,
		U16 Length,
		UNSIGNED Ref1,
		UNSIGNED Ref2));

U8 OS_ModuleLastRebootCause(void);

void OS_App_Request_Reboot(void);

STATUS OS_SetupComPort
(COMM_RESOURCE_T Resource, U32 Baud, U8 Parity, U8 DataBits, U8 StopBits);

STATUS OS_RequestComportUsageAPP
(COMM_RESOURCE_T Resource);

STATUS OS_SetResourceFreeAPP
(COMM_RESOURCE_T Resource);

//STATUS OS_SendMail(EMAIL_STRUCT * pMail, MAIL_CALLBACK_FUNC pCallback);

//EMAIL_STATE_ENUM OS_GetMailStatus(U16 MailId);

VOID OS_listen_for_tcp(UNSIGNED, VOID *);

VOID OS_listen_for_udp(UNSIGNED, VOID *);

/* WP-Line functions */

STATUS OS_WPLChangeState(U16 GroupNumber, U8 NodeNumber, U8 Command);

S32 OS_Ping(U8 *, INT);


BOOL OS_ValidateUnitClock(U64 Value, U8 Precision, U16 HoursMax, U16 HoursMin);
U16 OS_GetHoursFromUnitClock(U64 Value);
U8 OS_GetMinutesFromUnitClock(U64 Value);
U8 OS_GetSecondsFromUnitClock(U64 Value);
U16 OS_GetMillisecondsFromUnitClock(U64 Value);

S32 OS_StatusCodeSetAutomatic(U16 StatusCodeNo);

S32 OS_StatusCodeResetAutomatic(U16 StatusCodeNo);

/* Additional action server API function */

STATUS VarDB_GetVariableInfo(varid_t, varid_t);

//as_string_t * _get_str_mem(U16);

//U8 STR_CONV(struct as_string *, U8 *, U8);

//U8 OS_vardb_to_object(varid_t, object_t *);

STATUS OS_GetFlashInfo(CHAR *path, INT * blocks, INT * bad_blocks,
	INT * block_size, INT *sector_size);
STATUS OS_GetFlashWearInfo
(CHAR *path, INT sizee, INT * buffer);

// add during port MMS
STATUS OS_Get_Peer_Name(INT, struct sockaddr_struct *, INT16 *);

struct tm * localtime(const time_t *timer);

//size_t strftime(char *s, size_t maxsize, const char *fmt, const struct tm *tt);

time_t mktime(struct tm *tp);

double difftime(time_t time1, time_t time0);

extern int snprintf(char *buff, size_t maxchars, const char *fmt, ...);
extern int sprintf(char *buff, const char *fmt, ...);
//extern int toupper(int c); //already in c


STATUS MITALIB_ctrl();

STATUS MitaMenuMenu_ctrl();

STATUS MitaMenuMenuInitialize(U32 IPAddress);

#endif