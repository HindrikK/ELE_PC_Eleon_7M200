//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

#include <IEC104_Database.h>

#define         M_EI_NA_1 ((U8)70)       // End of Initialisation (70)
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
// When adding elements to database, addresses should be in continuous ascending order. This makes Get.. and Set.. processing fast.




#define IDB_TYPE_CHECK      // this enables the validation of object structure by checking the "Type" value
#define IDB_Type 95
#define IEC104MAXDATABASECAPACITY 253


S32 IEC104Database_GetDatabaseObject(IEC104Database database, void** databaseObject, U8 type);

typedef struct IEC104Var //dummy variable
{
	U32 IOA;
	IEC104_CP56Time2A TimeTag;
	void *Value;
	BOOL Updated;
}IEC104Var;


typedef struct IEC104BoolVar
{
    U32 IOA;
	IEC104_CP56Time2A TimeTag;
	BOOL *Value;
	BOOL Updated;
	BOOL ValuePrev;
}IEC104BoolVar;

typedef struct IEC104ByteVar
{
    U32 IOA;
	IEC104_CP56Time2A TimeTag;
	U8 *Value;
	BOOL Updated;
	U8 ValuePrev;
}IEC104ByteVar;

typedef struct IEC104IntVar
{
    U32 IOA;
	IEC104_CP56Time2A TimeTag;
	S16 *Value;
	BOOL Updated;
	S16 ValuePrev;
}IEC104IntVar;

typedef struct IEC104FloatVar
{
    U32 IOA;
	IEC104_CP56Time2A TimeTag;
	F32 *Value;
	BOOL Updated;
	F32 ValuePrev;
}IEC104FloatVar;

typedef struct IEC104Values //dummy variable
{
	U8 Type;
	U8 Count;
	U8 Capacity;
	struct IEC104Var* Variables[];
}IEC104Values;

typedef struct BoolValues
{
    U8 Type;
    U8 Count;
	U8 Capacity;
    struct IEC104BoolVar* Variables[];    
}BoolValues;

typedef struct ByteValues
{
    U8 Type;
    U8 Count;
	U8 Capacity;
    struct IEC104ByteVar* Variables[];  
}ByteValues;

typedef struct IntegerValues
{
    U8 Type;
    U8 Count;
	U8 Capacity;
    struct IEC104IntVar* Variables[];  
}IntegerValues;

typedef struct FloatValues
{
    U8 Type;
    U8 Count;
	U8 Capacity;
    struct IEC104FloatVar* Variables[];  
}FloatValues;

struct I104Database
{
	U8 Type;
	
	//Monitoring points
	
	struct BoolValues *M_SP_TB_data;		//Single-point information
	struct ByteValues *M_DP_TB_data;		//Double-point information
	struct ByteValues *M_ST_TB_data; 		//Step position information
	struct FloatValues *M_BO_TB_data;		//Bitstring of 32 bit
	struct IntegerValues *M_ME_TD_data;		//Measured value, normalised value
	struct IntegerValues *M_ME_TE_data;	    //Measured value, scaled value
	struct FloatValues *M_ME_TF_data;		//Measured value, short floating point number
	struct FloatValues *M_IT_TB_data;		//Integrated totals
	struct BoolValues *M_EP_TD_data;		//Event of protection equipment with time tag CP56Time2a
	struct ByteValues *M_EP_TE_data;		//Packed start events of protection equipment with time tag CP56Time2a
	struct ByteValues *M_EP_TF_data;		//Packed output circuit information of protection equipment with time tag CP56Time2a
	struct FloatValues *M_PS_NA_data;		//Packed single point information with status change detection
	struct IntegerValues *M_ME_ND_data;		//Measured value, normalized value without quality descriptor

	//Control points
	struct BoolValues *C_SC_TA_data; //Single command
	struct ByteValues *C_DC_TA_data; //Double command
	struct ByteValues *C_RC_TA_data; //Regulating step command
	struct IntegerValues *C_SE_TA_data; //Set-point Command, normalised value
	struct IntegerValues *C_SE_TB_data;  //Set-point Command, scaled value
	struct FloatValues *C_SE_TC_data;  //Set point Command, short floating point command
	struct FloatValues *C_BO_TA_data; //Bitstring 32bit command
};

#ifdef IDB_TYPE_CHECK
// Validate object reference; Returns FALSE if invalid object reference
static BOOL IEC104Database_ValidateObject(IEC104Database database)
{
	if (database->Type == IDB_Type) { return true; }
	else { return false; }
}
#endif

// Initialize IEC104 variable database
IEC104Database IEC104Database_New()
{
	// allocate memory for IEC104 database struct
	void* newDatabase;
	int result = OS_Allocate_Memory(GetMemPool(), &newDatabase, sizeof(struct I104Database), OS_NO_SUSPEND);
	if (result != OS_SUCCESS) { return NULL; }

	((IEC104Database)newDatabase)->Type = IDB_Type;

	//intialize monitoring points
	((IEC104Database)newDatabase)->M_SP_TB_data = NULL;
	((IEC104Database)newDatabase)->M_DP_TB_data = NULL;
	((IEC104Database)newDatabase)->M_ST_TB_data = NULL;
	((IEC104Database)newDatabase)->M_BO_TB_data = NULL;
	((IEC104Database)newDatabase)->M_ME_TD_data = NULL;
	((IEC104Database)newDatabase)->M_ME_TE_data = NULL;
	((IEC104Database)newDatabase)->M_ME_TF_data = NULL;
	((IEC104Database)newDatabase)->M_IT_TB_data = NULL;
	((IEC104Database)newDatabase)->M_EP_TD_data = NULL;
	((IEC104Database)newDatabase)->M_EP_TE_data = NULL;
	((IEC104Database)newDatabase)->M_EP_TF_data = NULL;
	((IEC104Database)newDatabase)->M_PS_NA_data = NULL;
	((IEC104Database)newDatabase)->M_ME_ND_data = NULL;

	//Initialize control points
	((IEC104Database)newDatabase)->C_SC_TA_data = NULL;
	((IEC104Database)newDatabase)->C_DC_TA_data = NULL;
	((IEC104Database)newDatabase)->C_RC_TA_data = NULL;
	((IEC104Database)newDatabase)->C_SE_TA_data = NULL;
	((IEC104Database)newDatabase)->C_SE_TB_data = NULL;
	((IEC104Database)newDatabase)->C_SE_TC_data = NULL;
	((IEC104Database)newDatabase)->C_BO_TA_data = NULL;

	return (IEC104Database)newDatabase;
}

//Intitialize sub object by type, returns -1 if unable, each object can be initialized once(can only choose one from each data type(without timetag, short timetag, long timetag) )
//Will always use structure with long timetag, but type will be the one given
S32 IEC104Database_InitializeDatabaseASDUObject( U8 capacity, IEC104Database database, U8 Type)
{
	
	int result;
	void* pointer;
	U8 i;

	//check if object already initialized
	result = IEC104Database_GetDatabaseObject(database, &pointer, Type);
	if (result == 0) { return -1; }

	// allocate memory for variable table structs and initialize table pointers in database with null values
	result= IEC104Database_GetVariableType(Type);
	if (result < 0) { return -1; }

	switch (result) {

	case IEC104_BOOL:
		result = OS_Allocate_Memory(GetMemPool(), &pointer, sizeof(struct BoolValues) + sizeof(void*) * (capacity), OS_NO_SUSPEND);
		if (result != OS_SUCCESS) { return -51; }
		switch (Type)
		{
		case M_SP_NA_1:
		case M_SP_TA_1:
		case M_SP_TB_1:
			database->M_SP_TB_data = (struct BoolValues*)pointer;
			database->M_SP_TB_data->Type = Type;
			break;
		case M_EP_TA_1:
		case M_EP_TD_1:
			database->M_EP_TD_data = (struct BoolValues*)pointer;
			database->M_EP_TD_data->Type = Type;
			break;
		case C_SC_NA_1:
		case C_SC_TA_1:
			database->C_SC_TA_data = (struct BoolValues*)pointer;
			database->C_SC_TA_data->Type = Type;
			break;
		}
		
		((struct BoolValues*)pointer)->Capacity = capacity;

		// initialize all values in database
		((struct BoolValues*)pointer)->Count = 0;

		for (i = 0; i < capacity; i++)
		{
			((struct BoolValues*)pointer)->Variables[i] = NULL;
		}
		return result;
		break;

	case IEC104_BYTE:
		result = OS_Allocate_Memory(GetMemPool(), &pointer, sizeof(struct ByteValues) + sizeof(void*) * (capacity), OS_NO_SUSPEND);
		if (result != OS_SUCCESS) {return -51; }
		switch (Type)
		{
		case M_DP_NA_1:
		case M_DP_TA_1:
		case M_DP_TB_1:
			database->M_DP_TB_data = (struct ByteValues*)pointer;
			database->M_DP_TB_data->Type = Type;
			break;
		case M_ST_NA_1:
		case M_ST_TA_1:
		case M_ST_TB_1:
			database->M_ST_TB_data = (struct ByteValues*)pointer;
			database->M_ST_TB_data->Type = Type;
			break;
		case M_EP_TB_1:
		case M_EP_TE_1:
			database->M_EP_TE_data = (struct ByteValues*)pointer;
			database->M_EP_TE_data->Type = Type;
			break;
		case M_EP_TC_1:
		case M_EP_TF_1:
			database->M_EP_TF_data = (struct ByteValues*)pointer;
			database->M_EP_TF_data->Type = Type;
			break;
		case C_DC_NA_1:
		case C_DC_TA_1:
			database->C_DC_TA_data = (struct ByteValues*)pointer;
			database->C_DC_TA_data->Type = Type;
			break;
		case C_RC_NA_1:
		case C_RC_TA_1:
			database->C_RC_TA_data = (struct ByteValues*)pointer;
			database->C_RC_TA_data->Type = Type;
			break;
		}
		
		((struct ByteValues*)pointer)->Capacity = capacity;

		// initialize all values in database
		((struct ByteValues*)pointer)->Count = 0;

		for (i = 0; i < capacity; i++)
		{
			((struct ByteValues*)pointer)->Variables[i] = NULL;
		}
		return result;
		break;
	
	case IEC104_INTEGER:
		result = OS_Allocate_Memory(GetMemPool(), &pointer, sizeof(struct IntegerValues) + sizeof(void*) * (capacity), OS_NO_SUSPEND);
		if (result != OS_SUCCESS) { return -51;; }
		switch (Type)
		{
		case M_ME_NA_1:
		case M_ME_TD_1:
		case M_ME_TA_1:
			database->M_ME_TD_data = (struct IntegerValues*)pointer;
			database->M_ME_TD_data->Type = Type;
			break;
		case M_ME_NB_1:
		case M_ME_TB_1:
		case M_ME_TE_1:
			database->M_ME_TE_data = (struct IntegerValues*)pointer;
			database->M_ME_TE_data->Type = Type;
			break;
		case M_ME_ND_1:
			database->M_ME_ND_data = (struct IntegerValues*)pointer;
			database->M_ME_ND_data->Type = Type;
			break;
		case C_SE_NA_1:
		case C_SE_TA_1:
			database->C_SE_TA_data = (struct IntegerValues*)pointer;
			database->C_SE_TA_data->Type = Type;
			break;
		case C_SE_NB_1:
		case C_SE_TB_1:
			database->C_SE_TB_data = (struct IntegerValues*)pointer;
			database->C_SE_TB_data->Type = Type;
			break;
		
		}

		((struct IntegerValues*)pointer)->Capacity = capacity;

		// initialize all values in database
		((struct IntegerValues*)pointer)->Count = 0;

		for (i = 0; i < capacity; i++)
		{
			((struct IntegerValues*)pointer)->Variables[i] = NULL;
		}
		return result;
		break;
	case IEC104_FLOAT:
		result = OS_Allocate_Memory(GetMemPool(), &pointer, sizeof(struct FloatValues) + sizeof(void*) * (capacity), OS_NO_SUSPEND);
		if (result != OS_SUCCESS) { return -51; }
		switch (Type)
		{
		case M_BO_NA_1:
		case M_BO_TB_1:
		case M_BO_TA_1:
			database->M_BO_TB_data = (struct FloatValues*)pointer;
			database->M_BO_TB_data->Type = Type;
			break;
		case M_ME_NC_1:
		case M_ME_TC_1:
		case M_ME_TF_1:
			database->M_ME_TF_data = (struct FloatValues*)pointer;
			database->M_ME_TF_data->Type = Type;
			break;
		case M_IT_NA_1:
		case M_IT_TA_1:
		case M_IT_TB_1:
			database->M_IT_TB_data = (struct FloatValues*)pointer;
			database->M_IT_TB_data->Type = Type;
			break;
		case M_PS_NA_1:
			database->M_PS_NA_data = (struct FloatValues*)pointer;
			database->M_PS_NA_data->Type = Type;
			break;
		case C_SE_NC_1:
		case C_SE_TC_1:
			database->C_SE_TC_data = (struct FloatValues*)pointer;
			database->C_SE_TC_data->Type = Type;
			break;
		case C_BO_NA_1:
		case C_BO_TA_1:
			database->C_BO_TA_data = (struct FloatValues*)pointer;
			database->C_BO_TA_data->Type = Type;
			break;
		}
	

		((struct FloatValues*)pointer)->Capacity = capacity;

		// initialize all values in database
		((struct FloatValues*)pointer)->Count = 0;
		int i;
		for (i = 0; i < capacity; i++)
		{
			((struct FloatValues*)pointer)->Variables[i] = NULL;
		}
		return result;
		break;

	default:
		return -51;
	}
	
}

S32 IEC104Database_GetVariableType(U8 type)
{
	switch (type)
	{
	case M_SP_NA_1:
	case M_SP_TA_1:
	case M_SP_TB_1:
	case M_EP_TA_1:
	case M_EP_TD_1:
	case C_SC_NA_1:
	case C_SC_TA_1:
		return IEC104_BOOL;
	case M_DP_NA_1:
	case M_DP_TA_1:
	case M_DP_TB_1:		
	case M_ST_NA_1:
	case M_ST_TA_1:
	case M_ST_TB_1:		
	case M_EP_TB_1:
	case M_EP_TE_1:		
	case M_EP_TC_1:
	case M_EP_TF_1:		
	case C_DC_NA_1:
	case C_DC_TA_1:		
	case C_RC_NA_1:
	case C_RC_TA_1:
		return IEC104_BYTE;
	case M_ME_NA_1:
	case M_ME_TD_1:
	case M_ME_TA_1:
	case M_ME_NB_1:
	case M_ME_TB_1:
	case M_ME_TE_1:
	case M_ME_ND_1:
	case C_SE_NA_1:
	case C_SE_TA_1:
	case C_SE_NB_1:
	case C_SE_TB_1:
		return IEC104_INTEGER;
	case M_BO_NA_1:
	case M_BO_TB_1:
	case M_BO_TA_1:
	case M_ME_NC_1:
	case M_ME_TC_1:
	case M_ME_TF_1:
	case M_IT_NA_1:
	case M_IT_TA_1:
	case M_IT_TB_1:
	case M_PS_NA_1:
	case C_SE_NC_1:
	case C_SE_TC_1:
	case C_BO_NA_1:
	case C_BO_TA_1:
		return IEC104_FLOAT;
	default:
		return -1;
	}
	return -1;
}

S32 IEC104Database_GetDatabaseObject(IEC104Database database, void** databaseObject,U8 type) {

	switch (type)
	{
	case M_SP_NA_1:
	case M_SP_TA_1:
	case M_SP_TB_1:
		if (database->M_SP_TB_data == NULL) { return -1; }
		*databaseObject = database->M_SP_TB_data;
		break;
	case M_EP_TA_1:
	case M_EP_TD_1:
		if (database->M_EP_TD_data == NULL) { return -1; }
		*databaseObject = database->M_EP_TD_data;
		break;
	case M_DP_NA_1:
	case M_DP_TA_1:
	case M_DP_TB_1:
		if (database->M_DP_TB_data == NULL) { return -1; }
		*databaseObject = database->M_DP_TB_data;
		break;
	case M_ST_NA_1:
	case M_ST_TA_1:
	case M_ST_TB_1:
		if (database->M_ST_TB_data == NULL) { return -1; }
		*databaseObject = database->M_ST_TB_data;
		break;
	case M_EP_TB_1:
	case M_EP_TE_1:
		if (database->M_EP_TE_data == NULL) { return -1; }
		*databaseObject = database->M_EP_TE_data;
		break;
	case M_EP_TC_1:
	case M_EP_TF_1:
		if (database->M_EP_TF_data == NULL) { return -1; }
		*databaseObject = database->M_EP_TF_data;
		break;
	case M_ME_NA_1:
	case M_ME_TD_1:
	case M_ME_TA_1:
		if (database->M_ME_TD_data == NULL) { return -1; }
		*databaseObject = database->M_ME_TD_data;
		break;
	case M_ME_NB_1:
	case M_ME_TB_1:
	case M_ME_TE_1:
		if (database->M_ME_TE_data == NULL) { return -1; }
		*databaseObject = database->M_ME_TE_data;
		break;
	case M_ME_ND_1:
		if (database->M_ME_ND_data == NULL) { return -1; }
		*databaseObject = database->M_ME_ND_data;
		break;
	case M_BO_NA_1:
	case M_BO_TB_1:
	case M_BO_TA_1:
		if (database->M_BO_TB_data == NULL) { return -1; }
		*databaseObject = database->M_BO_TB_data;
		break;
	case M_ME_NC_1:
	case M_ME_TC_1:
	case M_ME_TF_1:
		if (database->M_ME_TF_data == NULL) { return -1; }
		*databaseObject = database->M_ME_TF_data;
		break;
	case M_IT_NA_1:
	case M_IT_TA_1:
	case M_IT_TB_1:
		if (database->M_IT_TB_data == NULL) { return -1; }
		*databaseObject = database->M_IT_TB_data;
		break;
	case M_PS_NA_1:
		if (database->M_PS_NA_data == NULL) { return -1; }
		*databaseObject = database->M_PS_NA_data;
		break;

	case C_SC_NA_1:
	case C_SC_TA_1:
		if (database->C_SC_TA_data == NULL ) { return -1; }
		*databaseObject = database->C_SC_TA_data;
		break;
	case C_DC_NA_1:
	case C_DC_TA_1:
		if (database->C_DC_TA_data == NULL ) { return -1; }
		*databaseObject = database->C_DC_TA_data;
		break;
	case C_RC_NA_1:
	case C_RC_TA_1:
		if (database->C_RC_TA_data == NULL ) { return -1; }
		*databaseObject = database->C_RC_TA_data;
		break;
	case C_SE_NA_1:
	case C_SE_TA_1:
		if (database->C_SE_TA_data == NULL ) { return -1; }
		*databaseObject = database->C_SE_TA_data;
		break;
	case C_SE_NB_1:
	case C_SE_TB_1:
		if (database->C_SE_TB_data == NULL ) { return -1; }
		*databaseObject = database->C_SE_TB_data;
		break;
	case C_SE_NC_1:
	case C_SE_TC_1:
		if (database->C_SE_TC_data == NULL ) { return -1; }
		*databaseObject = database->C_SE_TC_data;
		break;
	case C_BO_NA_1:
	case C_BO_TA_1:
		if (database->C_BO_TA_data == NULL ) { return -1; }
		*databaseObject = database->C_BO_TA_data;
		break;
	default:
		return -1;
	}
	return 0;

}

S32 IEC104Database_Add(IEC104Database database, U32 IOA, void *Value, size_t  Length, U8 Type)
{
#ifdef IDB_TYPE_CHECK
	if (!IEC104Database_ValidateObject(database)) { return -1; }         // pointer to invalid object structure
#endif
	int result;
	//Check if IOA value already exists in database
	result = IEC104Database_GetType(database, IOA);
	if (result >= 0) { return -2; }

	//get correct object 
	IEC104Values * databaseObject;
	result = IEC104Database_GetDatabaseObject(database, (void **)(&databaseObject), Type);
	if (result < 0) { return -3; }

	
    result = IEC104Database_GetVariableType(Type);
	size_t sizeoftype;
	switch (result)
	{
	case IEC104_BOOL:
		sizeoftype = sizeof(BOOL);
		break;
	case IEC104_BYTE:
		sizeoftype = sizeof(U8);
		break;
	case IEC104_INTEGER:
		sizeoftype = sizeof(S16);
		break;
	case IEC104_FLOAT:
		sizeoftype = sizeof(F32);
		break;
	default:
		return -4;
	}

	if (sizeoftype != Length) { return -5; }

	if (databaseObject->Count < databaseObject->Capacity)
	{
		int i;
		for (i = 0; i < databaseObject->Count; i++)
		{
			if (databaseObject->Variables[i]->IOA == IOA)
			{
				return -6;
			}

		}
		// allocate memory for and create new variable struct
		void* pointer;
		int result = OS_Allocate_Memory(GetMemPool(), &pointer, sizeof(struct IEC104Var), OS_NO_SUSPEND);
		if (result != OS_SUCCESS) { return -7; }

		// add pointer to the new variable struct to database table
		databaseObject->Variables[databaseObject->Count] = (struct IEC104Var*)pointer;
		// add pointer to the actual variable into variable struct in database
		databaseObject->Variables[databaseObject->Count]->Value = Value;
		databaseObject->Variables[databaseObject->Count]->IOA = IOA;
		IEC104Database_Get_CP56Time2a(&(databaseObject->Variables[databaseObject->Count]->TimeTag));
		databaseObject->Count++;
	}
	else { return -8; }
	return 0;

}

S32 IEC104Database_GetCount(IEC104Database database, U8 Type)
{
#ifdef IDB_TYPE_CHECK
	if (!IEC104Database_ValidateObject(database)) { return -1; }         // pointer to invalid object structure
#endif
	
	void * pointer;
	int result = IEC104Database_GetDatabaseObject(database, &pointer, Type);
	if (result < 0) { return -1; }

	return ((IEC104Values *)pointer)->Count;
}



S32 IEC104Database_GetIOA(IEC104Database database, U32 *IOA, U8 Type, U8 index)
{
#ifdef IDB_TYPE_CHECK
	if (!IEC104Database_ValidateObject(database)) { return -1; }         // pointer to invalid object structure
#endif

	void * pointer;
	int result = IEC104Database_GetDatabaseObject(database, &pointer, Type);
	if (result < 0) { return -1; }

	if (index >= ((IEC104Values *)pointer)->Count) { return -1; }
	*IOA = ((IEC104Values *)pointer)->Variables[index]->IOA;

	return 0;

}


//returns 0 if value has been updated 
S32 IEC104Database_GetValueUpdated(IEC104Database database, void *Value, U8 Type, size_t Length, U8 index)
{

#ifdef IDB_TYPE_CHECK
	if (!IEC104Database_ValidateObject(database)) { return -1; }         // pointer to invalid object structure
#endif

	void * pointer;
	int result = IEC104Database_GetDatabaseObject(database, &pointer, Type);
	if (result < 0) { return -1; }

	if (index >= ((IEC104Values *)pointer)->Count) { return -1; }
	if (!(((IEC104Values *)pointer)->Variables[index]->Updated)) {
		return -1;
	}

	return IEC104Database_GetValue( database,  Value, Type, Length, index);
	
}

S32 IEC104Database_GetValue(IEC104Database database, void *Value, U8 Type, size_t Length, U8 index)
{
#ifdef IDB_TYPE_CHECK
	if (!IEC104Database_ValidateObject(database)) { return -1; }         // pointer to invalid object structure
#endif
	
	void * pointer;
	int result= IEC104Database_GetDatabaseObject(database,&pointer,Type);
	if (result < 0) { return -1; }

	if(index >= ((IEC104Values *)pointer)->Count) { return -1; }

	pointer = ((IEC104Values *)pointer)->Variables[index]->Value;
	

	 result = IEC104Database_GetVariableType(Type);
	switch (result)
	{
	case IEC104_BOOL:
		if (sizeof(BOOL) != Length) { return -1; }
		*(BOOL *)Value = *(BOOL *)pointer;
		break;
	case IEC104_BYTE:
		if (sizeof(U8) != Length) { return -1; }
		*(U8 *)Value = *(U8 *)pointer;
		break;
	case IEC104_INTEGER:
		if (sizeof(S16) != Length) { return -1; }
		*(S16 *)Value = *(S16 *)pointer;
		break;
	case IEC104_FLOAT:
		if (sizeof(F32) != Length) { return -1; }
		*(F32 *)Value = *(F32 *)pointer;
		break;
	default:
		return -1;
	}


	return 0;
}

S32 IEC104Database_SetValue(IEC104Database database, void *Value, U8 Type, size_t Length, U8 index)
{
#ifdef IDB_TYPE_CHECK
	if (!IEC104Database_ValidateObject(database)) { return -1; }         // pointer to invalid object structure
#endif
	void * pointer;
	int result = IEC104Database_GetDatabaseObject(database, &pointer, Type);
	if (result < 0) { return -1; }

	if (index >= ((IEC104Values *)pointer)->Count) { return -1; }

    result = IEC104Database_GetVariableType(Type);
	switch (result)
	{
	case IEC104_BOOL:
		if (sizeof(BOOL) != Length) { return -1; }
		*(BOOL *)(((IEC104Values *)pointer)->Variables[index]->Value) = (*(BOOL *)Value) & 0x01;
		break;
	case IEC104_BYTE:
		if (sizeof(U8) != Length) { return -1; }
		*(U8 *)(((IEC104Values *)pointer)->Variables[index]->Value) = (*(U8 *)Value)& 0x03;
		break;
	case IEC104_INTEGER:
		if (sizeof(S16) != Length) { return -1; }
		*(S16 *)(((IEC104Values *)pointer)->Variables[index]->Value) = *(S16 *)Value;
		break;
	case IEC104_FLOAT:
		if (sizeof(F32) != Length) { return -1; }
		*(F32 *)(((IEC104Values *)pointer)->Variables[index]->Value) = *(F32 *)Value;
		break;
	default:
		return -1;
	}
	IEC104Database_Get_CP56Time2a(&(((IEC104Values *)pointer)->Variables[index]->TimeTag));


	
	return 0;
}

S32 IEC104Database_Get_CP56Time2a(IEC104_CP56Time2A *timetag )
{
	time_t RawTime;
	struct tm *info;

	RawTime = OS_GetTimeInMs();			// get the current time

	info = localtime(&RawTime);
	(*timetag).Milliseconds = (U16)(info->tm_sec * 1000);
	
	(*timetag).IVResMinute = 0;
	(*timetag).IVResMinute += (U8)info->tm_min;
	
	(*timetag).SURes2Hour = 0;
	if (info->tm_isdst > 0) {
		(*timetag).SURes2Hour = (U8)128;
	}
		
	(*timetag).SURes2Hour += (U8)info->tm_hour;

	if (info->tm_wday == 0) {
		(*timetag).DOWDay = (((U8)7) << 5);
	}
	else {
		(*timetag).DOWDay = (((U8)(info->tm_wday))<<5)+ (U8)(info->tm_mday);
	}
	(*timetag).Res3Month = (U8)(info->tm_mon+1);
	(*timetag).Res4Year = ((U8)info->tm_year%100)& 127;
	return 0;
}

S32 IEC104Database_Get_CP24Time2a(IEC104_CP24Time2A *timetag)
{
	time_t RawTime;
	struct tm *info;

	RawTime = OS_GetTimeInMs();			// get the current time

	info = localtime(&RawTime);
	(*timetag).Milliseconds = (U16)(info->tm_sec * 1000);

	(*timetag).IVResMinute = 0;
	(*timetag).IVResMinute += (U8)info->tm_min;

	return 0;
}

S32 UpdateDatabaseObjectValues(IEC104Database database , U8 Type) {

	void * pointer;
	int result = IEC104Database_GetDatabaseObject(database, &pointer, Type);
	if (result < 0) { return -1; }
	
	U8 i;
	U8 count = ((IEC104Values *)pointer)->Count;

	result = IEC104Database_GetVariableType(Type);
	switch (result)
	{
	case IEC104_BOOL:
		for (i = 0; i < count; i++) {
			if (*(BOOL *)((IEC104BoolVar *)((IEC104Values *)pointer)->Variables[i])->Value != ((IEC104BoolVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev) {
				((IEC104BoolVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev = *(BOOL *)((IEC104BoolVar *)((IEC104Values *)pointer)->Variables[i])->Value;
				((IEC104BoolVar *)((IEC104Values *)pointer)->Variables[i])->Updated = true;
				IEC104Database_Get_CP56Time2a(&(((IEC104Values *)pointer)->Variables[i]->TimeTag));

			}
			else {
				((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->Updated = false;

			}
		}
		break;
	case IEC104_BYTE:
		for (i = 0; i < count; i++) {
			if (*(U8 *)((IEC104ByteVar *)((IEC104Values *)pointer)->Variables[i])->Value != ((IEC104ByteVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev) {
				((IEC104ByteVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev = *(U8 *)((IEC104ByteVar *)((IEC104Values *)pointer)->Variables[i])->Value;
				((IEC104ByteVar *)((IEC104Values *)pointer)->Variables[i])->Updated = true;

				IEC104Database_Get_CP56Time2a(&(((IEC104Values *)pointer)->Variables[i]->TimeTag));
			}
			else {

			((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->Updated = false;
			}
		}
		break;
	case IEC104_INTEGER:
		for (i = 0; i < count; i++) {
			if (*(S16 *)((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->Value != ((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev) {
				((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev = *(S16 *)((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->Value;
				((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->Updated = true;
				IEC104Database_Get_CP56Time2a(&(((IEC104Values *)pointer)->Variables[i]->TimeTag));
			}
			else {

			((IEC104IntVar *)((IEC104Values *)pointer)->Variables[i])->Updated = false;
			}
		}
		break;
	case IEC104_FLOAT:
		for (i = 0; i < count; i++) {
			if (*(F32 *)((IEC104FloatVar *)((IEC104Values *)pointer)->Variables[i])->Value != ((IEC104FloatVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev) {
				((IEC104FloatVar *)((IEC104Values *)pointer)->Variables[i])->ValuePrev = *(F32 *)((IEC104FloatVar *)((IEC104Values *)pointer)->Variables[i])->Value;
				((IEC104FloatVar *)((IEC104Values *)pointer)->Variables[i])->Updated = true;
				IEC104Database_Get_CP56Time2a(&(((IEC104Values *)pointer)->Variables[i]->TimeTag));
			}
			else
			{
			((IEC104FloatVar *)((IEC104Values *)pointer)->Variables[i])->Updated = false;

			}
		}
		break;
	default:
		return -1;
	}
	return 0;
}

S32 IEC104Database_UpdateDatabaseValues(IEC104Database database)
{


#ifdef IDB_TYPE_CHECK
	if (!IEC104Database_ValidateObject(database)) { return -1; }         // pointer to invalid object structure
#endif



	UpdateDatabaseObjectValues(database, M_SP_TB_1);

	UpdateDatabaseObjectValues(database, M_DP_TB_1);

	UpdateDatabaseObjectValues(database, M_ST_TB_1);

	UpdateDatabaseObjectValues(database, M_BO_TB_1);

	UpdateDatabaseObjectValues(database, M_ME_TD_1);

	UpdateDatabaseObjectValues(database, M_ME_TE_1);

	UpdateDatabaseObjectValues(database, M_ME_TF_1);

	UpdateDatabaseObjectValues(database, M_IT_TB_1);

	UpdateDatabaseObjectValues(database, M_EP_TD_1);

	UpdateDatabaseObjectValues(database, M_EP_TE_1);

	UpdateDatabaseObjectValues(database, M_EP_TF_1);

	UpdateDatabaseObjectValues(database, M_PS_NA_1);

	UpdateDatabaseObjectValues(database, M_ME_ND_1);

	return 0;

}

S32 IEC104Database_Get(IEC104Database database, void *Value, size_t Length, U8 Type, U32 ioa)
{
	S32 i;
	S32 count;
	int result;
	count = IEC104Database_GetCount(database, Type);
	if (count < 0) {
		return -1;
	}
	U32 _ioa;
	for (i = 0; i < count; i++) {
		result = IEC104Database_GetIOA(database, &_ioa, Type, i);
		if (result < 0) { return -1; }
		if (_ioa == ioa) {
			result = IEC104Database_GetValue(database, Value, Type,Length, i);
			
			return result;
		}
	}
	return -1;
}

S32 IEC104Database_Set(IEC104Database database, void *Value, size_t Length, U8 Type, U32 ioa) {

	S32 i;
	S32 count;
	int result;
	count = IEC104Database_GetCount(database, Type);
	if (count < 0) {
		return -1;
	}
	U32 _ioa;
	for (i = 0; i < count; i++) {
		result = IEC104Database_GetIOA(database, &_ioa, Type, i);
		if (result < 0) { return -1; }
		if (_ioa == ioa) {
			result = IEC104Database_SetValue(database, Value, Type, Length, i);
			return result;
		}
	}
	return -1;

}

//returns the type of variable with given ioa, -1 if not found
S32 IEC104Database_GetType(IEC104Database database, U32 ioa) 
{
	F32 Value;
	int result;


	result = IEC104Database_Get(database, &Value, sizeof(BOOL), M_SP_TB_1, ioa);
	if (result >= 0) { return database->M_SP_TB_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(U8), M_DP_TB_1, ioa);
	if (result >= 0) { return database->M_DP_TB_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(U8), M_ST_TB_1, ioa);
	if (result >= 0) { return database->M_ST_TB_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(F32), M_BO_TB_1, ioa);
	if (result >= 0) { return database->M_BO_TB_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(S16), M_ME_TD_1, ioa);
	if (result >= 0) { return database->M_ME_TD_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(S16), M_ME_TE_1, ioa);
	if (result >= 0) { return database->M_ME_TE_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(F32), M_ME_TF_1, ioa);
	if (result >= 0) { return database->M_ME_TF_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(F32), M_IT_TB_1, ioa);
	if (result >= 0) { return database->M_IT_TB_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(BOOL), M_EP_TD_1, ioa);
	if (result >= 0) { return database->M_EP_TD_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(U8), M_EP_TE_1, ioa);
	if (result >= 0) { return database->M_EP_TE_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(U8), M_EP_TF_1, ioa);
	if (result >= 0) { return database->M_EP_TF_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(F32), M_PS_NA_1, ioa);
	if (result >= 0) { return database->M_PS_NA_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(S16), M_ME_ND_1, ioa);
	if (result >= 0) { return database->M_ME_ND_data->Type; }


	result = IEC104Database_Get(database, &Value, sizeof(BOOL), C_SC_TA_1, ioa);
	if (result >= 0) { return database->C_SC_TA_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(U8), C_DC_TA_1, ioa);
	if (result >= 0) { return database->C_DC_TA_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(U8), C_RC_TA_1, ioa);
	if (result >= 0) { return database->C_RC_TA_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(S16), C_SE_TA_1, ioa);
	if (result >= 0) { return database->C_SE_TA_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(S16), C_SE_TB_1, ioa);
	if (result >= 0) { return database->C_SE_TB_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(F32), C_SE_TC_1, ioa);
	if (result >= 0) { return database->C_SE_TC_data->Type; }
	result = IEC104Database_Get(database, &Value, sizeof(F32), C_BO_TA_1, ioa);
	if (result >= 0) { return database->C_BO_TA_data->Type; }

	return -1;
}
