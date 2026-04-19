//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2017 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:104$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: DESKTOP-3H3JCEK\jaakl $                                                           
// $RCSfile: VarArrayMenus.h,v $                                                 
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef __VAR_ARRAY_MENUS_H__
#define __VAR_ARRAY_MENUS_H__

#include <os_main.h>
#include <errcodes.h>
#include <lib_main.h>
#include <menu_macros.h>

#include "VarArrayMacros.h"
//#include "MemoryCommon.h"
#include "general.h"



//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_ARRAY_GROUPS
//
// DESCRIPTION:
//
//    This macros creates menu groups, which will be used
//    for creating arrays of menu from  arrays of Vbd.
//    For every element of array creates own menu group
//    with basic name GroupNameBasis
//
// INPUT:
//
//    pPool : App memory pool pointer
//    Length : Length of array
//    GroupNameBasis : Menu group name template
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_ARRAY_GROUPS( pPool,           /*App memory pool pointer*/         \
                                  Length,           /*Length of array*/                \
                                  GroupNameBasis,   /*Menu group name template*/       \
                                  Status)          /*Status of creating menu groups*/ \
{                                                                                      \
   int DigitLength = 0;                                                               \
   DigitLength = GetLength(Length);                                                     \
   if (DigitLength <= 0)                                                                \
   {                                                                                  \
      Status = DigitLength;                                                              \
   }                                                                                    \
   else                                                                               \
   {                                                                                    \
      Status = CreateMenuArrayGroups(pPool, DigitLength,  GroupNameBasis);               \
   }                                                                                    \
}


//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENUS_ARRAY
//
// DESCRIPTION:
//
//    This macros creates menus, which will be used
//    for creating arrays of menu from  arrays of Vbd.
//    For every element of array creates own menu with
//    with basic name GroupNameBasis.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    Length : Length of array
//    GroupNameBasis : Menu group name template
//    MenuNameBasis : Menu name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Statrus of creating menu groups
//*************************************************************************************
#define CREATE_MENUS_ARRAY( pPool,             /*App memory pool pointer*/            \
                            Length,            /*Length of array*/                    \
                            GroupNameBasis,    /*Menu group name template*/           \
                            MenuNameBasis,     /*Menu name template*/                 \
                            AccessLevel,       /*Menu access level*/                  \
                            Status)                                                   \
{                                                                                     \
   int DigitLength = 0;                                                              \
   DigitLength = GetLength(Length);                                                  \
   if (DigitLength <= 0)                                                             \
   {                                                                                 \
      Status = DigitLength;                                                         \
   }                                                                                 \
   else                                                                              \
   {                                                                                 \
      Status = CreateMenusArray( pPool,                                             \
                                 DigitLength,                                       \
                                 GroupNameBasis,                                    \
                                 MenuNameBasis,                                     \
                                 AccessLevel                                        \
                               );                                                  \
   }                                                                                 \
}

//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_LINKS_ARRAY
//
// DESCRIPTION:
//
//    This macros creates links menu item, with Vdbs
//    from array ArrName.
//    For every element of array creates own link.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    ArrName :  Name of array
//    LineType : Type of link
//    HomeReplicationFlag :  Replicate or not home
//    HomeGroupNameBasis : Home group name template
//    HomeMenuNameBasis : Home menu name template
//    LinkReplicationFlag : Replicate or not link
//    LinkGroupNameBasis : Link group name template
//    LinkMenuNameBasis : Link menu name template
//    LineReplicationFlag : Replicate or not line caption
//    LinkNameBasis : Link name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_LINKS_ARRAY( pPool,               /*App memory pool pointer*/      \
                                 ArrName,             /*Name of array*/                \
                                 Length,               /*Length of array*/              \
                                 LineType,             /*Type of link*/                 \
                                 HomeReplicationFlag,  /*Replicate or not home*/        \
                                 HomeGroupNameBasis,   /*Home group name template*/     \
                                 HomeMenuNameBasis,    /*Home menu name template*/      \
                                 LinkReplicationFlag,  /*Replicate or not link*/        \
                                 LinkGroupNameBasis,   /*Link group name template*/     \
                                 LinkMenuNameBasis,    /*Link menu name template*/      \
                                 LineReplicationFlag,  /*Replicate or not line caption*/\
                                 LinkNameBasis,        /*Link name template*/           \
                                 AccessLevel,          /*Menu access level*/            \
                                 Status)                                                \
{                                                                                      \
   int DigitLength = 0;                                                               \
   DigitLength = GetLength(Length);                                                   \
   if (DigitLength <= 0)                                                              \
   {                                                                                  \
      Status = DigitLength;                                                          \
   }                                                                                  \
   else                                                                               \
   {                                                                                  \
      Status = CreateMenuLinksArray( pPool,                                          \
                                     LineType,                                       \
                                     ArrName,                                        \
                                     DigitLength                                     \
                                     HomeReplicationFlag,                            \
                                     HomeGroupNameBasis,                             \
                                     HomeMenuNameBasis,                              \
                                     LinkReplicationFlag,                            \
                                     LinkGroupNameBasis,                             \
                                     LinkMenuNameBasis,                              \
                                     LineReplicationFlag,                            \
                                     LinkNameBasis,                                  \
                                     AccessLevel                                     \
                                   );                                               \
   }                                                                                  \
}

//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_LINKS_ARRAY_DOUBLE
//
// DESCRIPTION:
//
//    This macros creates links menu item, with Vdbs
//    from array ArrName.
//    This macros also create dobule size links from/to home menu item
//    For every element of array creates own link.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    ArrName :  Name of array
//    LineType : Type of link
//    HomeReplicationFlag :  Replicate or not home
//    HomeGroupNameBasis : Home group name template
//    HomeMenuNameBasis : Home menu name template
//    LinkReplicationFlag : Replicate or not link
//    LinkGroupNameBasis : Link group name template
//    LinkMenuNameBasis : Link menu name template
//    LineReplicationFlag : Replicate or not line caption
//    LinkNameBasis : Link name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_LINKS_ARRAY_DOUBLE( pPool,               /*App memory pool pointer*/          \
                                        Length,               /*Length of array*/                 \
                                        HomeReplicationFlag,  /*Replicate or not home*/           \
                                        HomeGroupNameBasis,   /*Home group name template*/        \
                                        HomeMenuNameBasis,    /*Home menu name template*/         \
                                        LinkReplicationFlag,  /*Replicate or not link*/           \
                                        LinkGroupNameBasis,   /*Link group name template*/        \
                                        LinkMenuNameBasis,    /*Link menu name template*/         \
                                        LineReplicationFlag,  /*Replicate or not line caption*/   \
                                        LinkNameBasis,         /*Link name template*/             \
                                        AccessLevel,           /*Menu access level*/              \
                                        Status)                                                   \
{                                                                                                 \
   int DigitLength = 0;                                                                          \
   DigitLength = GetLength(Length);                                                              \
   if (DigitLength <= 0)                                                                         \
   {                                                                                             \
      Status = DigitLength;                                                                     \
   }                                                                                             \
   else                                                                                          \
   {                                                                                             \
      Status = CreateMenuLinksArray( pPool,                                                     \
                                     PACKTYPE_LINK,                                             \
                                     NULL,                                                      \
                                     DigitLength,                                               \
                                     HomeReplicationFlag,                                       \
                                     HomeGroupNameBasis,                                        \
                                     HomeMenuNameBasis,                                         \
                                     LinkReplicationFlag,                                       \
                                     LinkGroupNameBasis,                                        \
                                     LinkMenuNameBasis,                                         \
                                     LineReplicationFlag,                                       \
                                     LinkNameBasis,                                             \
                                     AccessLevel                                                \
                                   );                                                         \
      \
      Status += CreateMenuLinksArray( pPool,                                                    \
                                      PACKTYPE_LINK,                                            \
                                      "0",                                                      \
                                      DigitLength,                                              \
                                      LinkReplicationFlag,                                      \
                                      LinkGroupNameBasis,                                       \
                                      LinkMenuNameBasis,                                        \
                                      HomeReplicationFlag,                                      \
                                      HomeGroupNameBasis,                                       \
                                      HomeMenuNameBasis,                                        \
                                      LineReplicationFlag,                                      \
                                      StrToUpper(pPool, LinkNameBasis),                         \
                                      AccessLevel                                               \
                                    );                                                        \
   }                                                                                             \
}

//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_LINKS_ARRAY_DOUBLE
//
// DESCRIPTION:
//
//    This macros creates links menu item, with Vdbs
//    from array ArrName.
//    This macros also create dobule size links from/to home menu item
//    For every element of array creates own link.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    ArrName :  Name of array
//    LineType : Type of link
//    HomeReplicationFlag :  Replicate or not home
//    HomeGroupNameBasis : Home group name template
//    HomeMenuNameBasis : Home menu name template
//    LinkReplicationFlag : Replicate or not link
//    LinkGroupNameBasis : Link group name template
//    LinkMenuNameBasis : Link menu name template
//    LineReplicationFlag : Replicate or not line caption
//    LinkNameBasis : Link name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_LINKS_ARRAY_DOUBLE_EXT( pPool,                 /*App memory pool pointer*/       \
      ArrName,               /*Name of array*/                 \
      Length,                /*Length of array*/               \
      LineType,              /*Type of link*/                  \
      HomeReplicationFlag,   /*Replicate or not home*/         \
      HomeGroupNameBasis,    /*Home group name template*/      \
      HomeMenuNameBasis,     /*Home menu name template*/       \
      LinkReplicationFlag,   /*Replicate or not link*/         \
      LinkGroupNameBasis,    /*Link group name template*/      \
      LinkMenuNameBasis,     /*Link menu name template*/       \
      LineReplicationFlag,   /*Replicate or not line caption*/ \
      LinkNameBasis,         /*Link name template*/            \
      AccessLevel,           /*Menu access level*/             \
      Status)                                                  \
{                                                                                                    \
   \
   int DigitLength = 0;                                                                             \
   DigitLength = GetLength(Length);                                                                 \
   if (DigitLength <= 0)                                                                            \
   {                                                                                                \
      Status = DigitLength;                                                                        \
   }                                                                                                \
   else                                                                                             \
   {                                                                                                \
      Status = CreateMenuLinksArray( pPool,                                                        \
                                     LineType,                                                     \
                                     ArrName,                                                      \
                                     DigitLength,                                                  \
                                     HomeReplicationFlag,                                          \
                                     HomeGroupNameBasis,                                           \
                                     HomeMenuNameBasis,                                            \
                                     LinkReplicationFlag,                                          \
                                     LinkGroupNameBasis,                                           \
                                     LinkMenuNameBasis,                                            \
                                     LineReplicationFlag,                                          \
                                     LinkNameBasis,                                                \
                                     AccessLevel                                                   \
                                   );                                                            \
      \
      Status += CreateMenuLinksArray( pPool,                                                       \
                                      LineType,                                                    \
                                      ArrName,                                                     \
                                      DigitLength,                                                 \
                                      LinkReplicationFlag,                                         \
                                      LinkGroupNameBasis,                                          \
                                      LinkMenuNameBasis,                                           \
                                      HomeReplicationFlag,                                         \
                                      HomeGroupNameBasis,                                          \
                                      HomeMenuNameBasis,                                           \
                                      LineReplicationFlag,                                         \
                                      StrToUpper(pPool, LinkNameBasis),                            \
                                      AccessLevel                                                  \
                                    );                                                           \
   }                                                                                                \
}

//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_LINES_ARRAY
//
// DESCRIPTION:
//
//    This macros creates menu line item, with Vdbs
//    from array ArrName.
//    For every element of array creates own menu item.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    ArrName :  Name of array
//    LineType : Type of link
//    GroupNameBasis : Menu group name template
//    MenuNameBasis : Menu name template
//    LineNameBasis : Menu line name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_LINES_ARRAY( pPool,                 /*App memory pool pointer*/           \
                                 ArrName,               /*Name of array*/                     \
                                 Length,                /*Length of array*/                   \
                                 LineType,              /*Type of line*/                      \
                                 LinkReplicationFlag,   /*Replicate or not link*/             \
                                 GroupNameBasis,        /*Menu group name template*/          \
                                 MenuNameBasis,         /*Menu name template*/                \
                                 LineNameBasis,         /*Menu line name template*/           \
                                 AccessLevel,           /*Menu access level*/                 \
                                 Status)                                                      \
{                                                                                             \
   \
   int DigitLength = 0;                                                                      \
   DigitLength = GetLength(Length);                                                          \
   if (DigitLength <= 0)                                                                     \
   {                                                                                         \
      Status = DigitLength;                                                                 \
   }                                                                                         \
   else                                                                                      \
   {                                                                                         \
      Status = CreateMenuLinesArray( pPool,                                                 \
                                     LineType,                                               \
                                     ArrName,                                                \
                                     DigitLength,                                            \
                                     LinkReplicationFlag,                                    \
                                     GroupNameBasis,                                         \
                                     MenuNameBasis,                                          \
                                     LineNameBasis,                                          \
                                     AccessLevel,                                            \
                                     0,                                                      \
                                     NULL,                                                   \
                                     NULL,                                                   \
                                     NULL                                                    \
                                   );                                                      \
   }                                                                                         \
}

//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_LINES_ARRAY_GROUPED
//
// DESCRIPTION:
//
//    This macros creates menu line item, with Vdbs
//    from array ArrName.
//    For every element of array creates own menu item.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    ArrName :  Name of array
//    LineType : Type of link
//    GroupNameBasis : Menu group name template
//    MenuNameBasis : Menu name template
//    LineNameBasis : Menu line name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_LINES_ARRAY_GROUPED( pPool,                 /*App memory pool pointer*/           \
      ArrName,               /*Name of array*/                     \
      Length,                /*Length of array*/                   \
      LineType,              /*Type of line*/                      \
      LinkReplicationFlag,   /*Replicate or not link*/             \
      GroupNameBasis,        /*Menu group name template*/          \
      MenuNameBasis,         /*Menu name template*/                \
      LineNameBasis,         /*Menu line name template*/           \
      AccessLevel,           /*Menu access level*/                 \
      GroupSize,             /*Menu group size*/                   \
      GroupCaptionBasis,     /*Menu group caption for group*/      \
      GroupGroupNameBasis,   /*Menu group name for group*/         \
      GroupMenuNameBasis,    /*Menu name for group*/               \
      Status)                                                      \
{                                                                                                     \
   \
   int DigitLength = 0;                                                                              \
   DigitLength = GetLength(Length);                                                                  \
   if (DigitLength <= 0)                                                                             \
   {                                                                                                 \
      Status = DigitLength;                                                                         \
   }                                                                                                 \
   else                                                                                              \
   {                                                                                                 \
      Status = CreateMenuLinesArray( pPool,                                                         \
                                     LineType,                                                       \
                                     ArrName,                                                        \
                                     DigitLength,                                                    \
                                     LinkReplicationFlag,                                            \
                                     GroupNameBasis,                                                 \
                                     MenuNameBasis,                                                  \
                                     LineNameBasis,                                                  \
                                     AccessLevel,                                                    \
                                     GroupSize,                                                      \
                                     GroupCaptionBasis,                                              \
                                     GroupGroupNameBasis,                                            \
                                     GroupMenuNameBasis                                              \
                                   );                                                              \
   }                                                                                                 \
}

//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_TEXT_ARRAY
//
// DESCRIPTION:
//
//    This macros creates text menu line item. array
//    For every element of array creates own menu item.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    GroupNameBasis : Menu group name template
//    MenuNameBasis : Menu name template
//    LineNameBasis : Menu line name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_TEXT_ARRAY( pPool,                  /*App memory pool pointer*/        \
                                Length,                 /*Length of array*/                \
                                LinkReplicationFlag,    /*Replicate or not link*/          \
                                GroupNameBasis,         /*Menu group name template*/       \
                                MenuNameBasis,          /*Menu name template*/             \
                                LineNameBasis,          /*Menu line name template*/        \
                                AccessLevel,            /*Menu access level*/              \
                                Status)                                                    \
{                                                                                          \
   \
   int DigitLength = 0;                                                                   \
   DigitLength = GetLength(Length);                                                       \
   if (DigitLength <= 0)                                                                  \
   {                                                                                      \
      Status = DigitLength;                                                              \
   }                                                                                      \
   else                                                                                   \
   {                                                                                      \
      Status = CreateMenuLinesArray( pPool,                                              \
                                     PACKTYPE_TEXT,                                      \
                                     "0",                                                \
                                     DigitLength,                                        \
                                     LinkReplicationFlag,                                \
                                     GroupNameBasis,                                     \
                                     MenuNameBasis,                                      \
                                     LineNameBasis,                                      \
                                     AccessLevel,                                        \
                                     0,                                                  \
                                     NULL,                                               \
                                     NULL,                                               \
                                     NULL                                                \
                                   );                                                  \
   }                                                                                      \
}

//*************************************************************************************
//
// FUNCTION:
//
//    CREATE_MENU_EMPTY_LINES_ARRAY
//
// DESCRIPTION:
//
//    This macros creates empty menu line item array
//    For every element of array creates own menu item.
//
// INPUT:
//
//    pPool : App memory pool pointer
//    GroupNameBasis : Menu group name template
//    MenuNameBasis : Menu name template
//    AccessLevel : Menu access level
//
// OUTPUT:
//    Status : Status of creating menu groups
//*************************************************************************************
#define CREATE_MENU_EMPTY_LINES_ARRAY( pPool,                  /*App memory pool pointer*/           \
                                       Length,                 /*Length of array*/                   \
                                       LinkReplicationFlag,    /*Replicate or not link*/             \
                                       GroupNameBasis,         /*Menu group name template*/          \
                                       MenuNameBasis,          /*Menu name template*/                \
                                       AccessLevel,            /*Menu access level*/                 \
                                       Status)                                                       \
{                                                                                                    \
   \
   int DigitLength = 0;                                                                             \
   DigitLength = GetLength(Length);                                                                 \
   if (DigitLength <= 0)                                                                            \
   {                                                                                                \
      Status = DigitLength;                                                                        \
   }                                                                                                \
   else                                                                                             \
   {                                                                                                \
      Status = CreateMenuLinesArray( pPool,                                                        \
                                     PACKTYPE_NULL,                                                \
                                     "0",                                                          \
                                     DigitLength,                                                  \
                                     LinkReplicationFlag,                                          \
                                     GroupNameBasis,                                               \
                                     MenuNameBasis,                                                \
                                     "",                                                           \
                                     AccessLevel,                                                  \
                                     0,                                                            \
                                     NULL,                                                         \
                                     NULL,                                                         \
                                     NULL                                                          \
                                   );                                                             \
   }                                                                                                \
}





// Functions prototypes
// Most of this functions uses in macroses. Parasmaters of they are the same as in macroses
//----------------------------------------------------------------------------

/*Create clients menu groups from template*/
STATUS CreateMenuArrayGroups(OS_MEMORY_POOL* pPool,          /*App memory pool pointer*/
                             U16 Length,
                             const char* GroupNameBasis     /*Menu group name template*/
                            );

/*Create clients menu from template*/
STATUS CreateMenusArray(OS_MEMORY_POOL* pPool,                /*App memory pool pointer*/
                        U16 Length,
                        const char* GroupNameBasis,          /*Menu group name template*/
                        const char* MenuNameBasis,           /*Menu name template*/
                        access_t AccessLevel                 /*Menu access level*/
                       );

/*Create clients menu links from template*/
STATUS CreateMenuLinksArray(OS_MEMORY_POOL* pPool,            /*App memory pool pointer*/
                            U8 LineType,                     /*Type of link*/
                            const char* VarNameBasis,        /*Variable name template*/
                            U16 Length,                      /*Length*/
                            U8 HomeReplicationFlag,          /*Replicate or not home*/
                            const char* HomeGroupNameBasis,  /*Home group name template*/
                            const char* HomeMenuNameBasis,   /*Home menu name template*/
                            U8 LinkReplicationFlag,          /*Replicate or not link*/
                            const char* LinkGroupNameBasis,  /*Link group name template*/
                            const char* LinkMenuNameBasis,   /*Link menu name template*/
                            U8 LineReplicationFlag,          /*Replicate or not line caption*/
                            const char* LinkNameBasis,       /*Link name template*/
                            access_t AccessLevel             /*Menu access level*/
                           );

/*Create clients menu lines from template*/
STATUS CreateMenuLinesArray(OS_MEMORY_POOL* pPool,            /*App memory pool pointer*/
                            U8 LineType,                     /*Type of line*/
                            const char* VarNameBasis,        /*Variable name template*/
                            U16 Length,                      /*Length*/
                            U8 LinkReplicationFlag,          /*Replicate or not link*/
                            const char* GroupNameBasis,      /*Menu group name template*/
                            const char* MenuNameBasis,       /*Menu name template*/
                            const char* LineNameBasis,       /*Menu line name template*/
                            access_t AccessLevel,            /*Menu access level*/
                            U16 GroupSize,                   /*Menu group size*/
                            const char* GroupCaptionBasis,   /*Link group caption template*/
                            const char* GroupGroupNameBasis, /*Link group name template*/
                            const char* GroupMenuNameBasis   /*Link menu name template*/
                           );

#endif
