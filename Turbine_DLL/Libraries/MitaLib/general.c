//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2017 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:108$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: DESKTOP-3H3JCEK\jaakl $                                                           
// $RCSfile: general.c,v $                                                       
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <os_lib.h>
#include <lib_main.h>
#include <VarMacros.h>
#include <OS4x00.h>
#include <stdio.h>

#include <general.h>
#include <string.h>

static OS_MEMORY_POOL* pGlobalMemPool;

void SetMemPool(OS_MEMORY_POOL* pPool)
{
   pGlobalMemPool = pPool;
}

OS_MEMORY_POOL* GetMemPool()
{
   return pGlobalMemPool;
}

/************************************ myStrDup ********************************/
char* myStrDup(OS_MEMORY_POOL* pPool, const char* strIn)
{
   if (!strIn)
   {
      return NULL;
   }
   int length = strlen(strIn) + 1;
   char* result = (char*)SysAllocDataMemory(pPool,length);
   memset(result, '\0', length);
   strcpy(result, strIn);
   return result;
}

char* StrToUpper(OS_MEMORY_POOL* pPool, const char* strIn)
{
   char* res = myStrDup(pPool, strIn);

   if (res == NULL)
   {
      return NULL;
   }

   U32 i;
   for (i = 0; i < strlen(res); ++i)
   {
      int upper = toupper(res[i]);
      res[i] = upper;
   }

   return res;
}

char* FormatArrayNames(char* Name, const char* NameBasis, U16 Index)
{
   if (!Name || !NameBasis)
   {
      return 0;
   }

   sprintf(Name, "%s_%d", NameBasis, Index);
   return Name;
}

void* SysAllocDataMemory(OS_MEMORY_POOL* pPool, unsigned long ulSize)
{
   void* pMem = NULL;
   STATUS iRetVal = OS_Allocate_Memory(pPool, &pMem, ulSize, OS_NO_SUSPEND);

   if (pMem == NULL || iRetVal != OS_SUCCESS)
   {
      (void)OS_DEBUGLOG_make_entry(8888, "*** SysAllocDataMemory failed %i***", iRetVal);
      (void)OS_DEBUGLOG_make_entry(8888, "-(%s, %d)", __FILE__, __LINE__);

      (void)OS_EVENTLOG_make_entry(8888, "*** SysAllocDataMemory failed %i***", iRetVal);
      (void)OS_EVENTLOG_make_entry(8888, "-(%s, %d)", __FILE__, __LINE__);

      return NULL;
   }

   return pMem;
}

/***************************** SysFreeDataMemory ******************************/
char SysFreeDataMemory(void* pMem, unsigned long ulSize)
{
   STATUS iRetVal = 0;
   iRetVal = OS_Deallocate_Memory((VOID*)pMem);
   if (iRetVal)
   {
      (void)OS_DEBUGLOG_make_entry(8888, "*** SysFreeDataMemory failed %i***", iRetVal);
      (void)OS_DEBUGLOG_make_entry(8888, "-(%s, %d)", __FILE__, __LINE__);
#ifdef DEBUG_OUTPUT
      AppDebugLog(0, "*** SysFreeDataMemory failed %i***", iRetVal);
#endif
   }
   return (char)iRetVal;
}

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
                               struct multiplexed_info_struct M_MultiplexedInfoMenu[])
{
   static STATUS Status;
   int i, multiplexed_index;

   switch (ModuleState)
   {
      case APP_INIT1 :
      {
         /* Create Application menu structure */
         Status = OS_CreateMenus(groupname, newmenu, MenuElements);
         if (Status != 0)
         {
            AppSystemLog(10, "Menu err %d", Status);
            return Status;
         }
         break;
      }
      case APP_INIT4 :
      {
         //Menu line and link to local menu
         if (newline)
         {
            Status = OS_AddLines(UpperGroup, UpperMenu, (struct line_struct*) newline, elements);
            if (Status != 0)
            {
               AppSystemLog(20, "Menu err %d", Status);
               return Status;
            }
         }
         for (i = 0; i < LocalElements; ++i)
            if (LocalLine[i].Linetype < 7)
            {
               Status = OS_AddLines(groupname, MenuName, (struct line_struct*) &LocalLine[i], 1);
               if (Status != 0)
               {
                  AppSystemLog(21, "Menu err %d", Status);
                  return Status;
               }
            }
            else
            {
               if (!pPool)
               {
                  AppSystemLog(22, "Menu err %d", Status);
                  return Status;
               }
               multiplexed_index = LocalLine[i].MagicNumber;
               if (LocalLine[i].Linetype == MULTIPLEXED_CAT)
               {
                  CREATE_MENU_LINKS_ARRAY_DOUBLE(pPool,
                                                 M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeGroupNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeMenuNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkGroupNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkMenuNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LineReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                 Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_LINE)
               {
                  CREATE_MENU_LINES_ARRAY(pPool,
                                          M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                          M_MultiplexedInfoMenu[multiplexed_index].Length,
                                          M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                          M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                          M_MultiplexedInfoMenu[multiplexed_index].GroupNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].MenuNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].LineNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                          Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_LINE_GROUPED)
               {
                  CREATE_MENU_LINES_ARRAY_GROUPED(pPool,
                                                  M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                                  M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                  M_MultiplexedInfoMenu[multiplexed_index].GroupNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].MenuNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LineNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                  LocalLine[i].Format,
                                                  LocalLine[i].DisplayText,
                                                  LocalLine[i].LinkGroup,
                                                  LocalLine[i].LinkName,
                                                  Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_CAT_EXT)
               {
                  CREATE_MENU_LINKS_ARRAY_DOUBLE_EXT(pPool,
                                                     M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                                     M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeGroupNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeMenuNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkGroupNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkMenuNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LineReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                     Status);
               }
               if (Status != 0)
               {
                  AppSystemLog(22, "Menu err %d", Status);
                  return Status;
               }
            }
         break;
      }
   }
   return OS_SUCCESS;
}

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
                                  struct multiplexed_info_struct M_MultiplexedInfoMenu[])
{
   static STATUS Status;
   int i, multiplexed_index;

   switch (ModuleState)
   {
      case APP_INIT1 :
      {
         /* Create Application menu structure */
         Status = OS_CreateMenus(groupname, newmenu, MenuElements);
         if (Status != 0)
         {
            AppSystemLog(10, "Menu err %d", Status);
            return Status;
         }
         break;
      }
      case APP_INIT4 :
      {
         //Menu line and link to local menu
         if (newline)
         {
            Status = OS_AddLines(UpperGroup, UpperMenu, newline, elements);
            if (Status != 0)
            {
               AppSystemLog(20, "Menu err %d", Status);
               return Status;
            }
         }
         for (i = 0; i < LocalElements; ++i)
            if (LocalLine[i].Linetype < 7)
            {
               Status = OS_AddLines(groupname, MenuName, &LocalLine[i], 1);
               if (Status != 0)
               {
                  AppSystemLog(21, "Menu err %d", Status);
                  return Status;
               }
            }
            else
            {
               if (!pPool)
               {
                  AppSystemLog(22, "Menu err %d", Status);
                  return Status;
               }
               multiplexed_index = LocalLine[i].MagicNumber;
               if (LocalLine[i].Linetype == MULTIPLEXED_CAT)
               {
                  CREATE_MENU_LINKS_ARRAY_DOUBLE(pPool,
                                                 M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeGroupNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeMenuNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkGroupNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkMenuNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LineReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                 Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_LINE)
               {
                  CREATE_MENU_LINES_ARRAY(pPool,
                                          M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                          M_MultiplexedInfoMenu[multiplexed_index].Length,
                                          M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                          M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                          M_MultiplexedInfoMenu[multiplexed_index].GroupNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].MenuNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].LineNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                          Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_LINE_GROUPED)
               {
                  CREATE_MENU_LINES_ARRAY_GROUPED(pPool,
                                                  M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                                  M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                  M_MultiplexedInfoMenu[multiplexed_index].GroupNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].MenuNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LineNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                  LocalLine[i].Format,
                                                  LocalLine[i].DisplayText,
                                                  LocalLine[i].LinkGroup,
                                                  LocalLine[i].LinkName,
                                                  Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_CAT_EXT)
               {
                  CREATE_MENU_LINKS_ARRAY_DOUBLE_EXT(pPool,
                                                     M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                                     M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeGroupNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeMenuNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkGroupNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkMenuNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LineReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                     Status);
               }
               if (Status != 0)
               {
                  AppSystemLog(22, "Menu err %d", Status);
                  return Status;
               }
            }
         break;
      }
   }
   return OS_SUCCESS;
}

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
                               struct multiplexed_info_struct M_MultiplexedInfoMenu[])
{
   static STATUS Status;
   int i, multiplexed_index;

   switch (ModuleState)
   {
      case APP_INIT1 :
      {
         /* Create Application menu structure */
         Status = OS_CreateMenus(groupname, newmenu, MenuElements);
         if (Status != 0)
         {
            AppSystemLog(10, "Menu err %d", Status);
            return Status;
         }
         break;
      }
      case APP_INIT4 :
      {
         //Menu line and link to local menu
         if (newline)
         {
            Status = OS_AddLines(UpperGroup, UpperMenu, newline, elements);
            if (Status != 0)
            {
               AppSystemLog(20, "Menu err %d", Status);
               return Status;
            }
         }
         for (i = 0; i < (int) LocalElements; ++i)
            if (LocalLine[i].Linetype < 7)
            {
               Status = OS_AddLines(groupname, MenuName, &LocalLine[i], 1);
               if (Status != 0)
               {
                  AppSystemLog(21, "Menu err %d", Status);
                  return Status;
               }
            }
            else
            {
               if (!pPool)
               {
                  AppSystemLog(22, "Menu err %d", Status);
                  return Status;
               }
               multiplexed_index = LocalLine[i].MagicNumber;
               if (LocalLine[i].Linetype == MULTIPLEXED_CAT)
               {
                  CREATE_MENU_LINKS_ARRAY_DOUBLE(pPool,
                                                 M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeGroupNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].HomeMenuNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkGroupNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkMenuNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LineReplicationFlag,
                                                 M_MultiplexedInfoMenu[multiplexed_index].LinkNameBasis,
                                                 M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                 Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_LINE)
               {
                  CREATE_MENU_LINES_ARRAY(pPool,
                                          M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                          M_MultiplexedInfoMenu[multiplexed_index].Length,
                                          M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                          M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                          M_MultiplexedInfoMenu[multiplexed_index].GroupNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].MenuNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].LineNameBasis,
                                          M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                          Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_LINE_GROUPED)
               {
                  CREATE_MENU_LINES_ARRAY_GROUPED(pPool,
                                                  M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                                  M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                  M_MultiplexedInfoMenu[multiplexed_index].GroupNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].MenuNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].LineNameBasis,
                                                  M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                  LocalLine[i].Format,
                                                  LocalLine[i].DisplayText,
                                                  LocalLine[i].LinkGroup,
                                                  LocalLine[i].LinkName,
                                                  Status);
               }
               else if (LocalLine[i].Linetype == MULTIPLEXED_CAT_EXT)
               {
                  CREATE_MENU_LINKS_ARRAY_DOUBLE_EXT(pPool,
                                                     M_MultiplexedInfoMenu[multiplexed_index].ArrName,
                                                     M_MultiplexedInfoMenu[multiplexed_index].Length,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LineType,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeGroupNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].HomeMenuNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkGroupNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkMenuNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LineReplicationFlag,
                                                     M_MultiplexedInfoMenu[multiplexed_index].LinkNameBasis,
                                                     M_MultiplexedInfoMenu[multiplexed_index].AccessLevel,
                                                     Status);
               }
               if (Status != 0)
               {
                  AppSystemLog(22, "Menu err %d", Status);
                  return Status;
               }
            }
         break;
      }
   }
   return OS_SUCCESS;
}

#endif

/********************************* Fileapi Data ******************************/
#ifndef TRG_WIN
extern OS_MEMORY_POOL System_Memory;

/*   redefinition
STATUS CopyFile(char* destfilename, char* srcfilename, U32 overwrite)
{
#define BUFSIZE 50000
#define MAX_LOOP_TIMES 1000000
   STATUS status;
   U32 offset;
   int fd1;
   int fd2;
   char* buf = NULL;
   int i;
   char dir[512] = {0};
   int bytes_read;
   int bytes_written;

   status = OS_Allocate_Memory(GetMemPool(), (void**)&buf, BUFSIZE, OS_NO_SUSPEND);
   if (status != OS_SUCCESS)
   {
      AppDebugLog(13570, "Param.List: Allocate_Mem %d (%s, %d)", status, __FILE__, __LINE__);
      return status;
   }

   status = CheckDir(destfilename,dir,CREATE_DIR);
   if (status != OS_SUCCESS)
   {
      AppDebugLog(13570, "Param.List: CheckDir %d (%s, %d)", status, __FILE__, __LINE__);
      OS_Deallocate_Memory(buf);
      return status;
   }

   fd1 = OS_Open(srcfilename, PO_RDONLY, PS_IREAD);
   if (fd1 < 0)
   {
      AppDebugLog(13570, "Param.List: OS_Open %d (%s, %d)", fd1, __FILE__, __LINE__);
      OS_Deallocate_Memory(buf);
      return fd1;
   }

   if (overwrite == 1)
   {
      fd2 = OS_Open(destfilename, PO_RDWR | PO_CREAT, PS_IWRITE);
      if (fd2 < 0)
      {
         AppDebugLog(13570, "Param.List: OS_Open %d (%s, %d)", fd2, __FILE__, __LINE__);
         OS_Close(fd1);
         OS_Deallocate_Memory(buf);
         return fd2;
      }
   }
   else
   {
      fd2 = OS_Open(destfilename, PO_RDWR | PO_CREAT | PO_EXCL, PS_IWRITE);
      if (fd2 < 0)
      {
         AppDebugLog(13570, "Param.List: OS_Open %d (%s, %d)", fd2, __FILE__, __LINE__);
         OS_Close(fd1);
         OS_Deallocate_Memory(buf);
         return fd2;
      }
   }

   offset = 0;
   for (i=0 ; i<MAX_LOOP_TIMES ; i++)
   {
      bytes_read = (STATUS)OS_Read(fd1, buf, BUFSIZE);
      if (bytes_read < BUFSIZE)
      {
         if (bytes_read < 0)
         {
            AppDebugLog(13570, "Param.List: OS_Read %d (%s, %d)", bytes_read, __FILE__, __LINE__);
            OS_Deallocate_Memory(buf);
            OS_Close(fd1);
            OS_Close(fd2);
            return bytes_read;
         }
         else
         {
            bytes_written = (STATUS)OS_Write(fd2, buf, bytes_read);
            if (bytes_written != bytes_read)
            {
               AppDebugLog(13570, "Param.List: OS_Write %d (%s, %d)", bytes_written, __FILE__, __LINE__);
               OS_Deallocate_Memory(buf);
               OS_Close(fd1);
               OS_Close(fd2);
               return bytes_written;
            }
            break;
         }
      }
      bytes_written = (int)OS_Write(fd2, buf, BUFSIZE);
      if (bytes_written != BUFSIZE)
      {
         AppDebugLog(13570, "Param.List: OS_Write %d (%s, %d)", bytes_written, __FILE__, __LINE__);
         OS_Deallocate_Memory(buf);
         OS_Close(fd1);
         OS_Close(fd2);
         return bytes_written;
      }
      status = (STATUS)OS_Seek(fd1, offset, PSEEK_SET);
      if (status != offset)
      {
         AppDebugLog(13570, "Param.List: OS_Seek %d (%s, %d)", status, __FILE__, __LINE__);
         OS_Deallocate_Memory(buf);
         OS_Close(fd1);
         OS_Close(fd2);
         return status;
      }
      status = (STATUS)OS_Seek(fd2, offset, PSEEK_SET);
      if (status != offset)
      {
         AppDebugLog(13570, "Param.List: OS_Seek %d (%s, %d)", status, __FILE__, __LINE__);
         OS_Deallocate_Memory(buf);
         OS_Close(fd1);
         OS_Close(fd2);
         return status;
      }
      offset += BUFSIZE;
   }

   status = OS_Close(fd1);
   if (status != OS_SUCCESS)
   {
      AppDebugLog(13570, "Param.List: OS_Close %d (%s, %d)", status, __FILE__, __LINE__);
      OS_Deallocate_Memory(buf);
      return status;
   }
   status = OS_Close(fd2);
   if (status != OS_SUCCESS)
   {
      AppDebugLog(13570, "Param.List: OS_Close %d (%s, %d)", status, __FILE__, __LINE__);
      OS_Deallocate_Memory(buf);
      return status;
   }

   OS_Deallocate_Memory(buf);
   return OS_SUCCESS;
}
*/

extern volatile int watchdog_running;
STATUS CheckDir(const char* abs, char* path, int create)
{
   char temp_path[EMAXPATH] = {0};
   char absolute[EMAXPATH] = {0};
   char* work_ptr = NULL;
   int bytes = 0;
   STATUS sts;

   if (strncmp(abs, "\\", 1) && strncmp(abs, "I:\\", 3) && strncmp(abs, "X:\\", 3) && strncmp(abs, "R:\\", 3))
   {
      AppDebugLog(13570, "Param.List: CheckDir invalid prefix: %s (%s, %d)\r\n", abs, __FILE__, __LINE__);
      return NUF_INVNAME;
   }

   if (strlen(abs) > EMAXPATH)
   {
      AppDebugLog(13570, "Param.List: CheckDir filename too long (> 256b) : %s (%s, %d)\r\n", abs, __FILE__, __LINE__);
      return NUF_INVNAME;
   }

   if (strncmp(abs, "I:\\", 3) && strncmp(abs, "X:\\", 3) && strncmp(abs, "R:\\", 3))
   {
      snprintf(absolute, sizeof(absolute), "I:");
      strcat(absolute, abs);
   }
   else
   {
      strncpy(absolute, abs, sizeof(absolute));
   }

   work_ptr = (char*) absolute;
   bytes = 3;

   while (absolute[bytes] && bytes < (EMAXPATH - 1))
   {
      if (absolute[bytes] == '\\')
      {
         memset(temp_path, 0, sizeof(temp_path));
         strncpy(temp_path, absolute, bytes);
         if (create == CREATE_DIR)
         {
            sts = OS_Make_Dir(temp_path);
            if (sts != OS_SUCCESS && sts != NUF_EXIST)
            {
               return sts;
            }
         }
      }
      bytes ++;
   }
   strcpy(path, temp_path);
   return OS_SUCCESS;
}

STATUS CheckFileExist(char* srcfilename)
{
   STATUS fd1;

   fd1 = OS_Open(srcfilename, PO_RDONLY, PS_IREAD);
   if (fd1 < 0)
   {
      AppDebugLog(13570, "Param.List: OS_Open %d (%s, %d)\r\n", fd1, __FILE__, __LINE__);
      return fd1;
   }
   else
   {
      OS_Close(fd1);
      return 0;
   }
}

OS_SEMAPHORE File_User_Control_Semaphore;

#define MAX_EXTERNAL_FILE_USERS 5

OS_TASK* external_file_users[MAX_EXTERNAL_FILE_USERS] = {0};
STATUS FILEAPI_External_Init_File_User_Control(void)
{
   STATUS sts;
   int i = 0;

   for (i=0 ; i<MAX_EXTERNAL_FILE_USERS ; i++)
   {
      external_file_users[i] = NULL;
   }

   sts = OS_Create_Semaphore(&File_User_Control_Semaphore, "FileUser", 1, OS_FIFO);
   if (sts != OS_SUCCESS)
   {
      AppDebugLog(13570, "OS_Create_Semaphore returned %d, (%s, %d)\r\n", sts, __FILE__, __LINE__);
      return sts;
   }

   return OS_SUCCESS;
}

STATUS FILEAPI_External_Become_File_User(void)
{
   STATUS sts;
   int i = 0;
   int found = 0;

   if (OS_Check_File_User() == YES)
   {
      return OS_SUCCESS;
   }

   sts = OS_Obtain_Semaphore(&File_User_Control_Semaphore, OS_SUSPEND);
   if (sts != OS_SUCCESS)
   {
      AppDebugLog(13570, "OS_Obtain_Semaphore returned %d (%s, %d)\r\n", sts, __FILE__, __LINE__);
      return sts;
   }

   found = 0;
   for (i=0 ; i<MAX_EXTERNAL_FILE_USERS ; i++)
   {
      if (external_file_users[i] == NULL)
      {
         found = 1;
         break;
      }
   }

   if (found == 1)
   {
      sts = OS_Become_File_User();
      if (sts != YES)
      {
         AppDebugLog(13570, "OS_Become_File_User failed (%s, %d)\r\n", __FILE__, __LINE__);
         OS_Release_Semaphore(&File_User_Control_Semaphore);
         return -1;
      }

      external_file_users[i] = OS_Current_Task_Pointer();
   }
   else
   {
      OS_Release_Semaphore(&File_User_Control_Semaphore);
      return -1;
   }

   sts = OS_Release_Semaphore(&File_User_Control_Semaphore);
   if (sts != OS_SUCCESS)
   {
      AppDebugLog(13570, "OS_Release_Semaphore returned %d (%s, %d)\r\n", sts, __FILE__, __LINE__);
      return sts;
   }

   return OS_SUCCESS;
}

void FILEAPI_External_Release_File_User(void)
{
   STATUS sts;
   int i = 0;
   int found = 0;

   sts = OS_Obtain_Semaphore(&File_User_Control_Semaphore, OS_SUSPEND);
   if (sts != OS_SUCCESS)
   {
      AppDebugLog(13570, "OS_Obtain_Semaphore returned %d, (%s, %d)\r\n", sts, __FILE__, __LINE__);
      return;
   }

   for (i=0 ; i<MAX_EXTERNAL_FILE_USERS ; i++)
   {
      if (external_file_users[i] == OS_Current_Task_Pointer())
      {
         found = 1;
         break;
      }
   }

   if (found == 1)
   {
      external_file_users[i] = NULL;
      OS_Release_File_User();
   }

   sts = OS_Release_Semaphore(&File_User_Control_Semaphore);
   if (sts != OS_SUCCESS)
   {
      AppDebugLog(13570, "OS_Release_Semaphore returned %d, (%s, %d)\r\n", sts, __FILE__, __LINE__);
      return;
   }

   return;
}
#endif


#ifdef FILE_BACKUP_H_LOCAL

// Parameter backup
char* ExportParameterFile = "I:\\Backup\\App\\P99999\\Parameters\\Exports.App";
char* LocalParameterFile = "I:\\Backup\\App\\P99999\\Parameters\\Locals.App";
// General backup
char* GeneralBackupFile = "I:\\Backup\\App\\P99999\\General_Backups\\Backups.tmp";

static U8 TestOrder = 0;

char* AppExportParameterPosition(void)
{
   if (!TestOrder)
   {
      AppSystemError(0, "Export Parameter file name not intialised");
   }
   return(ExportParameterFile);
}

char* AppLocalParameterPosition(void)
{
   if (!TestOrder)
   {
     // AppSystemError(0, "Local Parameter file name not intialised");
   }
   return(LocalParameterFile);
}

char* AppBackupPosition(void)
{
   if (!TestOrder)
   {
      AppSystemError(0, "Backup file name not intialised");
   }
   return(GeneralBackupFile);
}

// Sets up the filenames, that the 3 functions above returns.
// Therefore this function must be called before any of the 3 above functions!
STATUS SetupParameterBackupFileNames(varid_t StateId)
{
   TestOrder = 1;
    OS_Retrieve_Backup_File_Names(StateId, &ExportParameterFile, &LocalParameterFile, &GeneralBackupFile);
   return 0;
}

//------------------------------------------------------------------------------
#define MAX_LOG_SIZE 53
void AppComPrint(U16 code,  const char* logName, const char* msg)
{
   char    Text[MAX_LOG_SIZE];

   memset( Text, 0, sizeof( Text ) );
   (void)snprintf( Text, sizeof(Text), "%5u %s ", code, logName);
   strncat( Text, msg, sizeof( Text ) - strlen( Text ) - 3 ); /* To ensure space for "\r\n" and at least one terminating zero */
   strcat( Text, "\r\n" );
   OS_com_printf( Text );
}

void AppDebugLog(U16 code, const char* text_format, ...)
{
   char    Text[MAX_LOG_SIZE];
   va_list ap;

   va_start( ap, text_format );                             /* Variable argument begin */
#ifdef __GNUC__
   (void)vsnprintf( Text, sizeof( Text ) - 1, text_format, ap ); /* To ensure at least one terminating zero */
#else
   (void)vsnprintf(Text, sizeof(Text) - 1, text_format, ap); /* To ensure at least one terminating zero */
   //(void)_vnsprintf( Text, (int)sizeof( Text ) - 1, text_format, ap ); /* To ensure at least one terminating zero */
#endif
   va_end( ap );

   (void)OS_DEBUGLOG_make_entry( code, Text);
   (void)AppComPrint(code, "APPDBG", Text);
}

//------------------------------------------------------------------------------

void AppSystemLog(U16 code, const char* text_format, ...)
{
   char    Text[MAX_LOG_SIZE];
   va_list ap;

   va_start( ap, text_format );                             /* Variable argument begin */
#ifdef __GNUC__
   (void)vsnprintf( Text, sizeof( Text ) - 1, text_format, ap ); /* To ensure at least one terminating zero */
#else
   (void)vsnprintf(Text, sizeof(Text) - 1, text_format, ap); /* To ensure at least one terminating zero */
  // (void)_vnsprintf( Text, (int)sizeof( Text ) - 1, text_format, ap ); /* To ensure at least one terminating zero */
#endif
   va_end( ap );

   (void)OS_SYSLOG_make_entry(code, Text);
   (void)AppComPrint(code, "APPSYS", Text);
}

//------------------------------------------------------------------------------

U8 SetAppSystemError = 0;

void AppSystemError(U16 code, const char* text_format, ...)
{
   char    Text[MAX_LOG_SIZE];
   va_list ap;

   va_start( ap, text_format );                             /* Variable argument begin */
#ifdef __GNUC__
   (void)vsnprintf( Text, sizeof( Text ) - 1, text_format, ap ); /* To ensure at least one terminating zero */
#else
   (void)vsnprintf(Text, sizeof(Text) - 1, text_format, ap); /* To ensure at least one terminating zero */
   //(void)_vnsprintf( Text, (int)sizeof( Text ) - 1, text_format, ap ); /* To ensure at least one terminating zero */
#endif
   va_end( ap );

   AppSystemLog(code, Text);
   SetAppSystemError = 1;
}

U8 ActivateAppSystemError(void)
{
   return SetAppSystemError;
}

/*-------------------------------------------------------------------*/
static U8 ApplicationState = APP_INIT1;

void SetAppState(U8 NewState)
{
   ApplicationState = NewState;
}

U8 AppState(void)
{
   return (ApplicationState);
}

//**************************Functions to get/set global RequestID and StateID
static varid_t App_RequestId = 0;
static varid_t App_StateId = 0;
void Set_App_RequestId_StateId(varid_t RequestId, varid_t StateId)
{
   App_RequestId = RequestId;
   App_StateId = StateId;
}

varid_t Get_RequestId(void)
{
   return App_RequestId;
}

varid_t Get_StateId(void)
{
   return App_StateId;
}

#endif

