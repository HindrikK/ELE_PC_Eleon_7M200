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
#ifndef FILE_IEC104_DATABASE_H
#define FILE_IEC104_DATABASE_H

#include <lib_main.h>

#define IEC104_BOOL ((U8)0)
#define IEC104_BYTE ((U8)1)
#define IEC104_INTEGER ((U8)2)
#define IEC104_FLOAT ((U8)3)

#define         M_SP_NA_1 ((U8)1)       // Single-point information
#define         M_SP_TA_1 ((U8)2)       // Single-point information with time tag
#define         M_DP_NA_1 ((U8)3)       // Double-point information
#define         M_DP_TA_1 ((U8)4)       // Double-point information with time tag
#define         M_ST_NA_1 ((U8)5)       // Step position information
#define         M_ST_TA_1 ((U8)6)       // Step position information with time tag
#define         M_BO_NA_1 ((U8)7)       // Bitstring of 32 bit
#define         M_BO_TA_1 ((U8)8)       // Bitstring of 32 bit with time tag
#define         M_ME_NA_1 ((U8)9)       // Measured value) normalised value
#define         M_ME_TA_1 ((U8)10)       // Measured value) normalized value with time tag
#define         M_ME_NB_1 ((U8)11)       // Measured value) scaled value
#define         M_ME_TB_1 ((U8)12)       // Measured value) scaled value wit time tag
#define         M_ME_NC_1 ((U8)13)       // Measured value) short floating point number
#define         M_ME_TC_1 ((U8)14)       // Measured value) short floating point number with time tag
#define         M_IT_NA_1 ((U8)15)       // Integrated totals (15)
#define         M_IT_TA_1 ((U8)16)       // Integrated totals with time tag (16)
#define         M_EP_TA_1 ((U8)17)       // Event of protection equipment with time tag (17)
#define         M_EP_TB_1 ((U8)18)       // Packed start events of protection equipment with time tag (18)
#define         M_EP_TC_1 ((U8)19)       // Packed output circuit information of protection equipment with time tag (19)
#define         M_PS_NA_1 ((U8)20)       // Packed single point information with status change detection (20)
#define         M_ME_ND_1 ((U8)21)       // Measured value) normalized value without quality descriptor (21)
#define         M_SP_TB_1 ((U8)30)       // Single-point information with time tag CP56Time2a (30)
#define         M_DP_TB_1 ((U8)31)       // Double-point information with time tag CP56Time2a (31)
#define         M_ST_TB_1 ((U8)32)       // Step position information with time tag CP56Time2a (32)
#define         M_BO_TB_1 ((U8)33)       // Bitstring of 32 bit with time tag CP56Time2a (33)
#define         M_ME_TD_1 ((U8)34)       // Measured value) normalised value with time tag CP56Time2a (34)
#define         M_ME_TE_1 ((U8)35)       // Measured value) scaled value with time tag CP56Time2a (35)
#define         M_ME_TF_1 ((U8)36)       // Measured value) short floating point number with time tag CP56Time2a (36)
#define         M_IT_TB_1 ((U8)37)       // Integrated totals with time tag CP56Time2a (37)
#define         M_EP_TD_1 ((U8)38)       // Event of protection equipment with time tag CP56Time2a (38)
#define         M_EP_TE_1 ((U8)39)       // Packed start events of protection equipment with time tag CP56Time2a (39)
#define         M_EP_TF_1 ((U8)40)       // Packed output circuit information of protection equipment with time tag CP56Time2a (40)


#define         C_SC_NA_1 ((U8)45)       // Single command (45)
#define         C_DC_NA_1 ((U8)46)       // Double command (46)
#define         C_RC_NA_1 ((U8)47)       // Regulating step command (47)
#define         C_SE_NA_1 ((U8)48)       // Set-point Command) normalised value (48)
#define         C_SE_NB_1 ((U8)49)       // Set-point Command) scaled value (49)
#define         C_SE_NC_1 ((U8)50)       // Set-point Command) short floating point number (50)
#define         C_BO_NA_1 ((U8)51)       // Bitstring 32 bit command (51)
#define         C_SC_TA_1 ((U8)58)       // Single command with time tag CP56Time2a (58)
#define         C_DC_TA_1 ((U8)59)       // Double command with time tag CP56Time2a (59)
#define         C_RC_TA_1 ((U8)60)       // Regulating step command with time tag CP56Time2a (60)
#define         C_SE_TA_1 ((U8)61)       // Measured value) normalised value command with time tag CP56Time2a (61)
#define         C_SE_TB_1 ((U8)62)       // Measured value) scaled value command with time tag CP56Time2a (62)
#define         C_SE_TC_1 ((U8)63)       // Measured value) short floating point number command with time tag CP56Time2a (63)
#define         C_BO_TA_1 ((U8)64)       // Bitstring of 32 bit command with time tag CP56Time2a (64)


typedef struct I104Database* IEC104Database;

typedef struct IEC104_CP24Time2A  // used in TA
{
	U16 Milliseconds; //0..59.999ms = 60sec = 1min
	U8 IVResMinute; // Bit 7 = IV(invalid time), Bit 6 = Res(spare bit), Bit 0..5 = Minutes(0..59min) 
}IEC104_CP24Time2A;

typedef struct IEC104_CP56Time2A // used in TB
{
	U16 Milliseconds; //0..59.999ms = 60sec = 1min 
	U8 IVResMinute; // Bit 7 = IV(invalid time), Bit 6 = Res(spare bit), Bit 0..5 = Minutes(0..59min)
	U8 SURes2Hour; //Bit 7 = SU(1 = summer time, 0 = normal time), Bits 5..6 = Res2, Bits 0..4 = Hours(0..23)
	U8 DOWDay;		//Bits 5..7 = Day of week(1..7, not used 0 !!!), Bits 0..4 = Day of month(1..31) //Day of week (DOW): 1 = Monday, 7 = Sunday, 0 = not used;
	U8 Res3Month; //Bits 4..7 = Res3(spare bits), Bits 0..3 = Month(1..12) 
	U8 Res4Year; //Bit 7 = Res4, Bits 0..6 = Year(0..99) 
}IEC104_CP56Time2A;


IEC104Database IEC104Database_New();
//Function to initialize each ASDU database object type with capacity. returns 0 on success
S32 IEC104Database_InitializeDatabaseASDUObject( U8 /*capacity*/, IEC104Database /*database*/, U8 /*Type*/);
//Function to add information objects to database object. returns 0 on success
S32 IEC104Database_Add(IEC104Database /*database*/, U32 /*IOA*/, void * /*variable*/,size_t Length, U8 /*Object type*/);
S32 IEC104Database_GetCount(IEC104Database database, U8 Type);

S32 IEC104Database_GetIOA(IEC104Database database, U32 *IOA, U8 Type, U8 index);
//Get ASDU type
S32 IEC104Database_GetType(IEC104Database database, U32 ioa);
//Get type of variable  IEC104_BOOL, IEC104_BYTE, IEC104_INTEGER, IEC104_FLOAT
S32 IEC104Database_GetVariableType(U8 type);


S32 IEC104Database_UpdateDatabaseValues(IEC104Database database);
S32 IEC104Database_GetValueUpdated(IEC104Database database, void *Value, U8 Type, size_t Length, U8 index);

S32 IEC104Database_GetValue(IEC104Database database, void *Value, U8 Type, size_t Length, U8 index);
S32 IEC104Database_Get(IEC104Database database, void *Value, size_t Length, U8 Type, U32 ioa);

S32 IEC104Database_SetValue(IEC104Database database, void *Value, U8 Type, size_t Length, U8 index);
S32 IEC104Database_Set(IEC104Database database, void *Value, size_t Length, U8 Type, U32 ioa);
S32 IEC104Database_Get_CP24Time2a(IEC104_CP24Time2A *timetag);
S32 IEC104Database_Get_CP56Time2a(IEC104_CP56Time2A *timetag);
#endif
