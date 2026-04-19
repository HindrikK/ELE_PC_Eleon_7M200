//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2017 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:105$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: DESKTOP-3H3JCEK\jaakl $                                                           
// $RCSfile: VarArrayMenus.c,v $                                                 
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <os_lib.h>

#include "VarArrayMenus.h"

struct menu_group_struct* GetMenuGroupStruct(OS_MEMORY_POOL* pPool)
{
   struct menu_group_struct* menuGroupStruct = (struct menu_group_struct*)SysAllocDataMemory(pPool, sizeof(struct menu_group_struct));
   if (menuGroupStruct)
   {
      memset(menuGroupStruct, 0, sizeof(struct menu_group_struct));
   }
   return menuGroupStruct;
}

struct menu_struct* GetMenuStruct(OS_MEMORY_POOL* pPool)
{
   struct menu_struct* menuStruct = (struct menu_struct*)SysAllocDataMemory(pPool, sizeof(struct menu_struct));
   if (menuStruct)
   {
      memset(menuStruct, 0, sizeof(struct menu_struct));
   }
   return menuStruct;
}

struct line_struct* GetLineStruct(OS_MEMORY_POOL* pPool)
{
   struct line_struct* lineStruct = (struct line_struct*)SysAllocDataMemory(pPool, sizeof(struct line_struct));
   if (lineStruct)
   {
      memset(lineStruct, 0, sizeof(struct line_struct));
   }
   return lineStruct;
}

char* FormatMenuNames(char* Name, const char* NameBasis, U16 Index)
{
   if (!Name || !NameBasis)
   {
      return 0;
   }

   sprintf(Name, "%s %d", NameBasis, Index);
   return Name;
}

STATUS CreateMenuArrayGroups(OS_MEMORY_POOL* pPool, U16 Length, const char* GroupNameBasis)
{
   STATUS Status = OS_SUCCESS;

   char GroupName[30];

   U16 i;
   for (i = 0; i < Length; i++)
   {
      FormatArrayNames(GroupName, GroupNameBasis, i+1);

      struct menu_group_struct* menuGroupStruct = GetMenuGroupStruct(pPool);
      if (!menuGroupStruct)
      {
         AppDebugLog(7777, "Cant find free memory!");
         Status = ERR_OS_MENU_CREATE_GROUP_NULL_POINTER;
         STATUS_LINE_VAR_RETURN_VALUE(Status);
      }
      else
      {
         Status = OS_CreateMenuGroup(menuGroupStruct, myStrDup(pPool, GroupName));
         if (Status)
         {
            SysFreeDataMemory(menuGroupStruct, sizeof(struct menu_group_struct));
            AppDebugLog(7777, "Cant create menu Group %s", GroupName);
            STATUS_LINE_VAR_RETURN_VALUE(Status);
         }
      }
   }

   return Status;
}

STATUS CreateMenusArray(OS_MEMORY_POOL* pPool,
                        U16 Length,
                        const char* GroupNameBasis,
                        const char* MenuNameBasis,
                        access_t AccessLevel
                       )
{
   STATUS Status = OS_SUCCESS;

   char GroupName[30];
   char  MenuName[30];

   U16 i;
   for (i = 0; i < Length; i++)
   {
      FormatArrayNames(GroupName, GroupNameBasis, i+1);
      //sprintf(GroupName,     "%s", GroupNameBasis);

      FormatArrayNames(MenuName, MenuNameBasis, i+1);

      struct menu_struct* menuStruct = GetMenuStruct(pPool);
      if (!menuStruct)
      {
         AppDebugLog(7777, "Cant find free memory!");
         Status = ERR_OS_MENU_CREATE_MENU_NULL_POINTER;
         STATUS_LINE_VAR_RETURN_VALUE(Status);
      }
      else
      {
         menuStruct->MagicNumber = 0;
         menuStruct->DisplayText = 0;
         menuStruct->Name = myStrDup(pPool, MenuName);
         menuStruct->ViewPasswordLevel = AccessLevel;
         menuStruct->MenuType = MENUTYPE_TEXT;
         menuStruct->Type.Text.NoOfLines = 0;
         menuStruct->Type.Text.first_line = 0;
         menuStruct->Type.Text.last_line = 0;
         menuStruct->Type.DynamicParameter.FunctionWorks = 0;
         menuStruct->Type.DynamicParameter.Parameter = 0;
         menuStruct->Type.Dynamic.FunctionWorks = 0;
         menuStruct->Type.dummy.dummy1 = 0;
         menuStruct->Type.dummy.dummy2 = 0;
         menuStruct->Type.dummy.dummy3 = 0;
         menuStruct->Type.Graphic.Filename = 0;
         menuStruct->next = 0;

         Status = OS_CreateMenus(myStrDup(pPool, GroupName), menuStruct, 1);
         if (Status)
         {
            SysFreeDataMemory(menuStruct, sizeof(struct menu_struct));
            AppDebugLog(7777, "Cant create Menu %s", MenuName);
            STATUS_LINE_VAR_RETURN_VALUE(Status);
         }
      }
   }

   return Status;
}

STATUS CreateMenuLinksArray(OS_MEMORY_POOL* pPool,
                            U8 LineType,
                            const char* VarNameBasis,
                            U16 Length,
                            U8 HomeReplicationFlag,
                            const char* HomeGroupNameBasis,
                            const char* HomeMenuNameBasis,
                            U8 LinkReplicationFlag,
                            const char* LinkGroupNameBasis,
                            const char* LinkMenuNameBasis,
                            U8 LineReplicationFlag,
                            const char* LinkNameBasis,
                            access_t AccessLevel
                           )
{
   STATUS Status = OS_SUCCESS;

   char HomeGroupName[30];
   char  HomeMenuName[30];
   char LinkGroupName[30];
   char  LinkMenuName[30];
   char      LinkName[50];
   char       VarName[50];

   struct line_struct* lineStruct;

   U16 i;
   for (i = 0; i < Length; i++)
   {
      if (HomeReplicationFlag)
      {
         FormatArrayNames(HomeGroupName, HomeGroupNameBasis, i+1);
         FormatArrayNames(HomeMenuName,  HomeMenuNameBasis, i+1);
      }
      else
      {
         sprintf(HomeGroupName, "%s", HomeGroupNameBasis);
         sprintf(HomeMenuName, "%s", HomeMenuNameBasis);
      }
      //sprintf(HomeGroupName, "%s", HomeGroupNameBasis);

      if (LinkReplicationFlag)
      {
         FormatArrayNames(LinkGroupName, LinkGroupNameBasis, i+1);
         FormatArrayNames(LinkMenuName,  LinkMenuNameBasis, i+1);
      }
      else
      {
         sprintf(LinkGroupName, "%s", LinkGroupNameBasis);
         sprintf(LinkMenuName, "%s", LinkMenuNameBasis);
      }

      //sprintf(LinkMenuName, "%s", LinkMenuNameBasis);

      if (LineReplicationFlag)
      {
         FormatMenuNames(LinkName, LinkNameBasis, i+1);
      }
      else
      {
         sprintf(LinkName, "%s", LinkNameBasis);
      }

      if (VarNameBasis)
      {
         FormatArrayNames(VarName, VarNameBasis, i);    //TODO: Need to investigate
      }

      lineStruct = GetLineStruct(pPool);

      if (!lineStruct)
      {
         AppDebugLog(7777, "Cant find free memory!");
         Status = ERR_OS_MENU_CREATE_LINES_NULL_POINTER;
         STATUS_LINE_VAR_RETURN_VALUE(Status);

         return Status;
      }

      lineStruct->MagicNumber = 0;
      lineStruct->DisplayText = myStrDup(pPool, LinkName);
      lineStruct->ViewPasswordLevel = AccessLevel;
      lineStruct->Linetype = LineType;
      lineStruct->LinkName = myStrDup(pPool, LinkMenuName);
      lineStruct->LinkGroup = myStrDup(pPool, LinkGroupName);
      if (VarNameBasis)
      {
         lineStruct->VarName = myStrDup(pPool, VarName);
         lineStruct->Format = LINE_FORMAT_NONE;
      }

      Status = OS_AddLines(myStrDup(pPool, HomeGroupName), myStrDup(pPool, HomeMenuName), lineStruct, 1);

      if (Status)
      {
         SysFreeDataMemory(lineStruct, sizeof(struct line_struct));
         AppDebugLog(7777, "Cant create menu line %s", LinkName);
         STATUS_LINE_VAR_RETURN_VALUE(Status);
      }
   }

   return Status;
}

static STATUS CreateArrayGroupedMenu(OS_MEMORY_POOL* pPool,
                                     char* GroupCaption,
                                     char* GroupName,
                                     char* MenuName,
                                     access_t AccessLevel,
                                     const char* GroupNameBasis,
                                     const char* MenuNameBasis)
{
   STATUS Status = OS_SUCCESS;
   struct line_struct* lineStruct;
   struct menu_struct* groupMenuStruct;
   struct menu_group_struct* menuGroupStruct;

   menuGroupStruct = GetMenuGroupStruct(pPool);
   if (!menuGroupStruct)
   {
      AppDebugLog(7777, "Cant find free memory!");
      Status = ERR_OS_MENU_CREATE_LINES_NULL_POINTER;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
      return Status;
   }

   Status = OS_CreateMenuGroup(menuGroupStruct, myStrDup(pPool, GroupName));
   if (Status != OS_SUCCESS)
   {
      SysFreeDataMemory(menuGroupStruct, sizeof(struct menu_group_struct));
      if (Status != ERR_OS_MENU_CREATE_ALREADY_EXISTS)
      {
         AppDebugLog(7777, "Cant Create Menu Group!");
         STATUS_LINE_VAR_RETURN_VALUE(Status);
         return Status;
      }
      Status = OS_SUCCESS;
   }

   groupMenuStruct = GetMenuStruct(pPool);
   if (!groupMenuStruct)
   {
      AppDebugLog(7777, "Cant find free memory!");
      Status = ERR_OS_MENU_CREATE_LINES_NULL_POINTER;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
      return Status;
   }

   groupMenuStruct->MagicNumber = 0;
   groupMenuStruct->DisplayText = 0;
   groupMenuStruct->Name = myStrDup(pPool, MenuName);
   groupMenuStruct->ViewPasswordLevel = AccessLevel;
   groupMenuStruct->MenuType = MENUTYPE_TEXT;
   groupMenuStruct->Type.Text.NoOfLines = 0;
   groupMenuStruct->Type.Text.first_line = 0;
   groupMenuStruct->Type.Text.last_line = 0;
   groupMenuStruct->Type.DynamicParameter.FunctionWorks = 0;
   groupMenuStruct->Type.DynamicParameter.Parameter = 0;
   groupMenuStruct->Type.Dynamic.FunctionWorks = 0;
   groupMenuStruct->Type.dummy.dummy1 = 0;
   groupMenuStruct->Type.dummy.dummy2 = 0;
   groupMenuStruct->Type.dummy.dummy3 = 0;
   groupMenuStruct->Type.Graphic.Filename = 0;
   groupMenuStruct->next = 0;

   Status = OS_CreateMenus(myStrDup(pPool, GroupName), groupMenuStruct, 1);
   if (Status != 0)
   {
      AppDebugLog(7777, "Cant Create Menus!");
      STATUS_LINE_VAR_RETURN_VALUE(Status);
      return Status;
   }

   lineStruct = GetLineStruct(pPool);
   if (!lineStruct)
   {
      AppDebugLog(7777, "Cant find free memory!");
      Status = ERR_OS_MENU_CREATE_LINES_NULL_POINTER;
      STATUS_LINE_VAR_RETURN_VALUE(Status);
      return Status;
   }

   lineStruct->MagicNumber = 0;
   lineStruct->DisplayText = myStrDup(pPool, GroupCaption);
   lineStruct->ViewPasswordLevel = AccessLevel;
   lineStruct->Linetype = PACKTYPE_LINK;
   lineStruct->LinkName = myStrDup(pPool, MenuNameBasis);
   lineStruct->LinkGroup = myStrDup(pPool, GroupNameBasis);

   Status = OS_AddLines(myStrDup(pPool, GroupName), myStrDup(pPool, MenuName), lineStruct, 1);
   if (Status)
   {
      SysFreeDataMemory(lineStruct, sizeof(struct line_struct));
      AppDebugLog(7777, "Cant create menu links %s", GroupCaption);
      STATUS_LINE_VAR_RETURN_VALUE(Status);
      return Status;
   }

   return OS_SUCCESS;
}

STATUS CreateMenuLinesArray(OS_MEMORY_POOL* pPool,
                            U8 LineType,
                            const char* VarNameBasis,
                            U16 Length,
                            U8 LinkReplicationFlag,
                            const char* GroupNameBasis,
                            const char* MenuNameBasis,
                            const char* LineNameBasis,
                            access_t AccessLevel,
                            U16 GroupSize,
                            const char* GroupCaptionBasis,
                            const char* GroupGroupNameBasis,
                            const char* GroupMenuNameBasis
                           )
{
   STATUS Status = OS_SUCCESS;

   char    GroupName[30];
   char     MenuName[30];
   char     LineName[50];
   char      VarName[50];
   char GroupCaption[60];
   struct line_struct* lineStruct;

   U16 groupIndex = 0;
   U16 i;
   for (i = 0; i < Length; i++)
   {
      if (LinkReplicationFlag)
      {
         FormatArrayNames(GroupName, GroupNameBasis, i+1);
         FormatArrayNames(MenuName, MenuNameBasis, i+1);
         sprintf(LineName, "%s", LineNameBasis);
      }
      else if (GroupSize != 0)
      {
         groupIndex = i / GroupSize;

         FormatArrayNames(GroupName, GroupGroupNameBasis, groupIndex+1);
         FormatArrayNames(MenuName, GroupMenuNameBasis, groupIndex+1);
         FormatMenuNames(LineName, LineNameBasis, i+1);

         if (i % GroupSize == 0)
         {
            sprintf(GroupCaption, "%s %d-%d", GroupCaptionBasis, i+1, (i+GroupSize) < Length ? i+GroupSize : Length);
            Status = CreateArrayGroupedMenu(pPool, GroupCaption, GroupName, MenuName, AccessLevel, GroupNameBasis, MenuNameBasis);
            STATUS_LINE_VAR_RETURN_VALUE(Status);

            lineStruct = GetLineStruct(pPool);

            if (!lineStruct)
            {
               AppDebugLog(7777, "Cant find free memory!");
               Status = ERR_OS_MENU_CREATE_LINES_NULL_POINTER;
               STATUS_LINE_VAR_RETURN_VALUE(Status);
               return Status;
            }
            sprintf(GroupCaption, "%s %d-%d", LineNameBasis, i+1, (i+GroupSize) < Length ? i+GroupSize : Length);

            lineStruct->MagicNumber = 0;
            lineStruct->DisplayText = myStrDup(pPool, GroupCaption);
            lineStruct->ViewPasswordLevel = AccessLevel;
            lineStruct->Linetype = PACKTYPE_LINK;
            lineStruct->LinkName = myStrDup(pPool, MenuName);
            lineStruct->LinkGroup = myStrDup(pPool, GroupName);

            Status = OS_AddLines(myStrDup(pPool, GroupNameBasis), myStrDup(pPool, MenuNameBasis), lineStruct, 1);
            if (Status)
            {
               SysFreeDataMemory(lineStruct, sizeof(struct line_struct));
               AppDebugLog(7777, "Cant create menu links %s", GroupCaption);
               STATUS_LINE_VAR_RETURN_VALUE(Status);
            }
         }
      }
      else
      {
         sprintf(GroupName,      "%s", GroupNameBasis);
         sprintf(MenuName,       "%s", MenuNameBasis);
         FormatMenuNames(LineName, LineNameBasis, i+1);
      }

      if (VarNameBasis)
      {
         FormatArrayNames(VarName, VarNameBasis, i);
      }

      lineStruct = GetLineStruct(pPool);

      if (!lineStruct)
      {
         AppDebugLog(7777, "Cant find free memory!");
         Status = ERR_OS_MENU_CREATE_LINES_NULL_POINTER;
         STATUS_LINE_VAR_RETURN_VALUE(Status);

         return Status;
      }

      lineStruct->MagicNumber = 0;
      lineStruct->DisplayText = myStrDup(pPool, LineName);
      lineStruct->ViewPasswordLevel = AccessLevel;
      lineStruct->Linetype = LineType;
      if (VarNameBasis)
      {
         lineStruct->VarName = myStrDup(pPool, VarName);
         lineStruct->Format = LINE_FORMAT_NONE;
      }

      Status = OS_AddLines(myStrDup(pPool, GroupName), myStrDup(pPool, MenuName), lineStruct, 1);

      if (Status)
      {
         SysFreeDataMemory(lineStruct, sizeof(struct line_struct));
         AppDebugLog(7777, "Cant create menu line %s", LineName);
         STATUS_LINE_VAR_RETURN_VALUE(Status);
      }
   }

   return Status;
}
