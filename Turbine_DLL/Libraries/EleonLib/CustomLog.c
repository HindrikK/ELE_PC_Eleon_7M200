//*****************************PEPTOOL Header Start******************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************


//***********************************************************************
#include <CustomLog.h>

#define CUSTOMLOG_TYPE 118
#define CUSTOMLOG_STRINGLEN_MAX 128

struct _customLog
{
	U8 Type;					   // This variable is initialized during _New() function and helps to validate the structure(object) used in functions
	
	int Capacity;				// max num of lines(entries) in log
	int StringSize;				// max number of characters in one log line
	varid_t MenuLines[];		// variable IDs of actual log menu lines
};



// Validate object reference; Returns FALSE if invalid object reference
static BOOL CustomLog_ValidateObject(CustomLog customlog)
{
   if(customlog->Type == CUSTOMLOG_TYPE) return true;
   else return false;
}

static void ShiftLogs(CustomLog customlog)
{
	char tempString[CUSTOMLOG_STRINGLEN_MAX];
	int i;
	for(i = customlog->Capacity - 1; i > 0; i--)
	{
		OS_VarDB_ReadVariable(customlog->MenuLines[i-1], tempString, customlog->StringSize, NULL);
		OS_VarDB_UpdateVariable(customlog->MenuLines[i], tempString, customlog->StringSize);
	}
}

int CustomLog_MakeEntry(CustomLog customlog, const char* text)
{
	if (!CustomLog_ValidateObject(customlog)) return -1;			// pointer to invalid object structure
	
	time_t RawTime;
	char TimeString[15];				// contains time string (hh:mm:ss DD-MM)
	char FinalString[CUSTOMLOG_STRINGLEN_MAX];

	RawTime = OS_GetTimeInMs();			// get the current time
	strftime(TimeString, 15, "%H:%M:%S %d-%m", localtime(&RawTime));

	snprintf(FinalString, customlog->StringSize, "%s | %s", text, TimeString);
	ShiftLogs(customlog);
	OS_VarDB_UpdateVariable(customlog->MenuLines[0], FinalString, customlog->StringSize);
	
	return 0;
}

int CustomLog_ClearAll(CustomLog customlog)
{
	if (!CustomLog_ValidateObject(customlog)) return -1;			// pointer to invalid object structure
	
	char nullChar = 0;
	int i;
	for(i = 0; i < customlog->Capacity; i++)
	{
		OS_VarDB_UpdateVariable(customlog->MenuLines[i], &nullChar, 1);
	}
	
	return 0;
}


// Creates new log, returns pointer to the new CustomLog structure. Returns NULL in case of error.
CustomLog CustomLog_New(const char* logVarName, int capacity, int stringSize)
{
	CustomLog customlog;

	if (capacity > 0 && stringSize > 0 && stringSize <= CUSTOMLOG_STRINGLEN_MAX)
	{
		int structSize = sizeof(struct _customLog) + sizeof(varid_t) * capacity;
		if(OS_Allocate_Memory(GetMemPool(), (void**) &customlog, structSize , OS_NO_SUSPEND) != OS_SUCCESS) return NULL;
	}
	else
	{
		return NULL;
	}


	char varName[50];
	int i;
	for(i=0; i < capacity; i++)
	{
		sprintf(varName, "%s_%u", logVarName, i);
		if(OS_VarDB_GetVariableID(varName, &customlog->MenuLines[i]) != OS_SUCCESS) return NULL;
	}

	customlog->Type = CUSTOMLOG_TYPE;
	customlog->Capacity = capacity;
	customlog->StringSize = stringSize;


	return customlog;
}


// Free memory and dispose the structure.
int CustomLog_Dispose(CustomLog customlog)
{
	if (!CustomLog_ValidateObject(customlog)) return -1;			// pointer to invalid object structure
	
	int result = OS_Deallocate_Memory(customlog);
	if (result != OS_SUCCESS) { return -2; }
	
	return 0;
}


int CustomLog_Capacity(CustomLog customlog)
{
	if (!CustomLog_ValidateObject(customlog)) return -1;			// pointer to invalid object structure
	return customlog->Capacity;
}


int CustomLog_StringSize(CustomLog customlog)
{
	if (!CustomLog_ValidateObject(customlog)) return -1;			// pointer to invalid object structure
	return customlog->StringSize;
}
