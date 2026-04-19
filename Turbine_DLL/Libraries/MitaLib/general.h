//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2017 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:109$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: DESKTOP-3H3JCEK\jaakl $                                                           
// $RCSfile: general.h,v $                                                       
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef __COMMON_POB_H__
#define __COMMON_POB_H__

#include <os_main.h>

/*************************************************** Defines *******************************************************/
#ifndef ERR_1_TO_7
#define ERR_1_TO_7
#define ERR_1 1
#define ERR_2 2
#define ERR_3 3
#define ERR_4 4
#define ERR_5 5
#define ERR_6 6
#define ERR_7 7

#endif

#define N_(string) string // Macro for marking strings only

/*********************************************** MemPool Management ************************************************/

void SetMemPool(OS_MEMORY_POOL* pPool);

OS_MEMORY_POOL* GetMemPool();

char* myStrDup(OS_MEMORY_POOL* pPool, const char* strIn);
char* FormatArrayNames(char* Name, const char* NameBasis, U16 Index);

char* StrToUpper(OS_MEMORY_POOL* pPool, const char* strIn);


/***************************** Mempry managemet wrappers maybe in future they removed ******************************/
void* SysAllocDataMemory(OS_MEMORY_POOL* pPool, unsigned long ulSize);
char SysFreeDataMemory(void* pMem, unsigned long ulSize);


/********************************************* Multiplexed menu items **********************************************/
#define MULTIPLEXED_CAT          207
#define MULTIPLEXED_LINE         208
#define MULTIPLEXED_CAT_EXT      209
#define MULTIPLEXED_LINE_GROUPED 210

struct multiplexed_info_struct
{
   char* ArrName;               // CAT_EXT, LINE
   char* Length;                // CAT, CAT_EXT, LINE
   int  LineType;               // CAT_EXT, LINE
   int  HomeReplicationFlag;    // CAT, CAT_EXT
   union
   {
      char* HomeGroupNameBasis;  // CAT, CAT_EXT
      char* GroupNameBasis;      // LINE
   };
   union
   {
      char* HomeMenuNameBasis;   // CAT, CAT_EXT
      char* MenuNameBasis;       // LINE
   };
   int LinkReplicationFlag;     // CAT, CAT_EXT, LINE
   char* LinkGroupNameBasis;    // CAT, CAT_EXT
   char* LinkMenuNameBasis;     // CAT, CAT_EXT
   int LineReplicationFlag;     // CAT, CAT_EXT
   union
   {
      char* LinkNameBasis;       // CAT, CAT_EXT
      char* LineNameBasis;       // LINE
   };
   int AccessLevel;             // CAT, CAT_EXT, LINE
};

#ifdef OPTION_MENU
STATUS CreateAndInitializeMenu(U8 ModuleState,
                               char* UpperGroup,
                               char* UpperMenu,
                               struct line_struct_old* newline,
                               size_t elements,

                               char* groupname,
                               struct menu_struct* newmenu,
                               size_t MenuElements,
                               char* MenuName,
                               struct line_struct_old* LocalLine,
                               size_t LocalElements,
                               OS_MEMORY_POOL* pPool,
                               struct multiplexed_info_struct M_MultiplexedInfoMenu[]);

STATUS CreateAndInitializeMenuOpt(U8 ModuleState,
                                  char* UpperGroup,
                                  char* UpperMenu,
                                  struct line_struct* newline,
                                  size_t elements,

                                  char* groupname,
                                  struct menu_struct* newmenu,
                                  size_t MenuElements,
                                  char* MenuName,
                                  struct line_struct* LocalLine,
                                  size_t LocalElements,
                                  OS_MEMORY_POOL* pPool,
                                  struct multiplexed_info_struct M_MultiplexedInfoMenu[]);
#else
STATUS CreateAndInitializeMenu(U8 ModuleState,
                               char* UpperGroup,
                               char* UpperMenu,
                               struct line_struct* newline,
                               size_t elements,

                               char* groupname,
                               struct menu_struct* newmenu,
                               size_t MenuElements,
                               char* MenuName,
                               struct line_struct* LocalLine,
                               size_t LocalElements,
                               OS_MEMORY_POOL* pPool,
                               struct multiplexed_info_struct M_MultiplexedInfoMenu[]);
#endif

#define MULTIPLEXED_INFO_CAT(Length, HomeReplicationFlag, HomeGroupNameBasis, HomeMenuNameBasis, \
                             LinkReplicationFlag, LinkGroupNameBasis, LinkMenuNameBasis, LineReplicationFlag, LinkNameBasis, AccessLevel) \
{ \
   0, \
   Length, \
   0, \
   HomeReplicationFlag, \
   {HomeGroupNameBasis}, \
   {HomeMenuNameBasis}, \
   LinkReplicationFlag, \
   LinkGroupNameBasis, \
   LinkMenuNameBasis, \
   LineReplicationFlag, \
   {LinkNameBasis}, \
   AccessLevel, \
}

#define MULTIPLEXED_INFO_CAT_EXT(ArrName, Length, LineType, HomeReplicationFlag, HomeGroupNameBasis, HomeMenuNameBasis, \
                                 LinkReplicationFlag, LinkGroupNameBasis, LinkMenuNameBasis, LineReplicationFlag, LinkNameBasis, AccessLevel) \
{ \
   ArrName, \
   Length, \
   LineType, \
   HomeReplicationFlag, \
   {HomeGroupNameBasis}, \
   {HomeMenuNameBasis}, \
   LinkReplicationFlag, \
   LinkGroupNameBasis, \
   LinkMenuNameBasis, \
   LineReplicationFlag, \
   {LinkNameBasis}, \
   AccessLevel, \
}

#define MULTIPLEXED_INFO_LINE(ArrName, Length, LineType, GroupNameBasis, MenuNameBasis, \
                              LinkReplicationFlag, LineNameBasis, AccessLevel) \
{ \
   ArrName, \
   Length, \
   LineType, \
   0, \
   {GroupNameBasis}, \
   {MenuNameBasis}, \
   LinkReplicationFlag, \
   0, \
   0, \
   0, \
   {LineNameBasis}, \
   AccessLevel, \
}

#define MENU_ELEMENT_LINE_MULTIPLEXED(MultiplexedType, MultiplexedIndex) \
   { \
      MultiplexedIndex, \
      0, \
      0, \
      MultiplexedType, \
   }

#define MENU_ELEMENT_LINE_MULTIPLEXED_GROUPED(MultiplexedIndex, GroupSize, GroupCaptionBasis, LinkGroupNameBasis, LinkMenuNameBasis) \
   { \
      MultiplexedIndex, \
      GroupCaptionBasis, \
      0, \
      MULTIPLEXED_LINE_GROUPED, \
      LinkMenuNameBasis, \
      LinkGroupNameBasis, \
      0, \
      GroupSize, \
   }

/********************************************* Fileapi Data **********************************************/
#ifndef TRG_WIN

#define CREATE_DIR 1
#define NO 0
#define YES 1

//STATUS CopyFile(char* destfilename, char* srcfilename, U32 overwrite);   redefinition
STATUS CheckDir(const char* filename, char* parentdir, int create);
STATUS CheckFileExist(char* srcfilename);
STATUS FILEAPI_External_Init_File_User_Control(void);
STATUS FILEAPI_External_Become_File_User(void);
void FILEAPI_External_Release_File_User(void);

#endif

extern void AppDebugLog(U16 code, const char* text_format, ...);

#endif


#ifndef FILE_BACKUP_H
#define FILE_BACKUP_H
#define FILE_BACKUP_H_LOCAL
/*****************************Backup Data ***********************************/
extern char* AppExportParameterPosition(void);
extern char* AppLocalParameterPosition(void);
extern char* AppBackupPosition(void);
STATUS SetupParameterBackupFileNames(varid_t StateId);
#endif

#ifndef FILE_VARIOUS_T1_V3_H
#define FILE_VARIOUS_T1_V3_H

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------
#define APP_INIT2        (U8)2  /* App. may initialise own variables */
#define APP_INIT2_DONE   (U8)2  /* App. have initialised all own variables */

#define APP_INIT3        (U8)3  /* App. may subscribe to foreign variables */
#define APP_INIT3_DONE   (U8)3  /* App. have subscribed to all needed variables */

#define APP_INIT4        (U8)4  /* App. may subscribe to foreign variables */
#define APP_INIT4_DONE   (U8)4  /* App. have subscribed to all needed variables */

#define APP_INIT5        (U8)5  /* App. may subscribe to foreign variables */
#define APP_INIT5_DONE   (U8)89  /* App. have subscribed to all needed variables */

#define APP_RUN AS_RUN

#define SETDELAY_MIN       U32_MIN
#define SETDELAY_MAX       U32_MAX

#define RESETDELAY_MIN     U32_MIN
#define RESETDELAY_MAX     U32_MAX

#define REPEATTIMES_MIN    U32_MIN
#define REPEATTIMES_MAX    U32_MAX

#define REPEATPERIOD_MIN   U16_MIN
#define REPEATPERIOD_MAX   U16_MAX

#define REPEATCODE_MIN     U16_MIN
#define REPEATCODE_MAX     U16_MAX

#define TIMEOUTPERIOD_MIN  U32_MIN
#define TIMEOUTPERIOD_MAX  U32_MAX

#define TIMEOUTCODE_MIN    U16_MIN
#define TIMEOUTCODE_MAX    U16_MAX

void Set_App_RequestId_StateId(varid_t RequestId, varid_t StateId);
extern varid_t Get_RequestId(void);
extern varid_t Get_StateId(void);


void AppDebugLog(U16 code, const char* text_format, ...);
void AppSystemLog(U16 code, const char* text_format, ...);
void AppSystemError(U16 code, const char* text_format, ...);
U8 ActivateAppSystemError(void);

#define ELEMENT(array) array,(sizeof(array)/sizeof(array[0]))
#define STATUS_LINE_NUMBER(Status) AppSystemLog(1, "Status "#Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);
#define STATUS_LINE_VAR(Status) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);}
#define STATUS_LINE_VAR_RETURN(Status) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__); return;}
#define STATUS_LINE_VAR_RETURN_VALUE(Status) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__); return(Status);}
#define STATUS_LINE_VAR_RETURN_CONST(Status, ReturnValue) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__); return(ReturnValue);}

void SetAppState(U8 NewState);
U8 AppState(void);

#endif

