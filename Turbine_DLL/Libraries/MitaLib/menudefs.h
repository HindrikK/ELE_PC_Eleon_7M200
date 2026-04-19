/*********************************************************************/
/*                                                                   */
/*            Copyright (c) 2002 Mita-Teknik a/s                     */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/* FILE NAME                                            VERSION      */
/*                                                                   */
/*      menudefs.h                                      Mita 1.0     */
/*                                                                   */
/* COMPONENT                                                         */
/*                                                                   */
/*                                                                   */
/* DESCRIPTION                                                       */
/*                                                                   */
/*      Definitions for various menu items.                          */
/*                                                                   */
/* AUTHOR                                                            */
/*    Mita-Teknik A/S                                                */
/*                                                                   */
/* HISTORY                                                           */
/*                                                                   */
/* NAME     DATE         REMARKS                                     */
/*-------------------------------------------------------------------*/
/* BJE      2001-11-07   Created                                     */
/* PBA      2002-02-11   Added Menutypes                             */
/*                       Cleanup of pack types                       */
/* PBA      2002-02-15   Added new menudefinitions                   */
/* FKL      2002-09-02   Changed to vardb version 2.                 */
/* PBA      2004-06-11   Major cleanup                               */
/*********************************************************************/

#ifndef __menudefs_h
#define __menudefs_h
//#include <stddef.h>
#include "types.h"

/*********************************************************************/
/*                                                                   */
/* BUTTON DEFINITIONS                                                */
/*                                                                   */
/*********************************************************************/

/* Buttons definitions */
/* Max number of buttons = nine */
/* Three pre button are reserved for START/STOP, EDIT and SELECT */
/* Two post buttons are reserved for scroll up and scroll down */
#define NUMBER_OF_BUTTONS 9
#define NUMBER_OF_FIXED_PRE_BUTTONS    3
#define NUMBER_OF_FIXED_POST_BUTTONS   2
/* Dont change the following definition - NUMBER_OF_NONFIXED_BUTTONS = seven */
#define NUMBER_OF_NONFIXED_BUTTONS \
    (NUMBER_OF_BUTTONS - NUMBER_OF_FIXED_PRE_BUTTONS - NUMBER_OF_FIXED_POST_BUTTONS)

typedef U32 buttonid_t;


/* Buttons definitions */
                                    /* Protected button ID´s */
#define B_AREA_START    0xE000
#define B_AREA_END      0xFFFF

                                    /* Automatic numbers - user to application buttons */
#define B_AUTO_START      0xE000
#define B_AUTO_END        0xEFFF

#define B_SYSTEM_START    0xF000
#define B_SYSTEM_END      0xFFFF
                                    /* Common buttons */
#define B_EMPTY           0xF000
#define B_LOGIN           0xF001
#define B_LOGOUT          0xF002
#define B_SHUTDOWN        0xF003
#define B_REBOOT          0xF004

                                    /* Buttons array for new menu system */
#define B_FUNC_START      0xF500
#define B_FUNC1           0xF501
#define B_FUNC2           0xF502
#define B_FUNC3           0xF503
#define B_FUNC4           0xF504
#define B_FUNC5           0xF505
#define B_FUNC6           0xF506
#define B_FUNC7           0xF507
#define B_FUNC8           0xF508
#define B_FUNC9           0xF509
#define B_FUNC10          0xF510
#define B_FUNC11          0xF511
#define B_FUNC12          0xF512
#define B_FUNC13          0xF513
#define B_FUNC14          0xF514
#define B_FUNC15          0xF515
#define B_FUNC16          0xF516
#define B_FUNC17          0xF517
#define B_FUNC18          0xF518
#define B_FUNC19          0xF519
#define B_FUNC20          0xF520
#define B_FUNC_END        0xF520

                                    /* Sliding windows control */
#define B_WINDOWS_START   0XFE00
#define B_WINDOWS_END     0XFEFF
#define B_PREV            0xFEFC
#define B_NEXT            0xFEFD
#define B_PAGEUP          0xFEFE
#define B_PAGEDOWN        0xFEFF

                                    /* System buttons */
#define B_BACK            0xFFF7
#define B_HOME            0xFFF8
#define B_RESET           0xFFF9
#define B_SELECT          0xFFFA
#define B_STOP            0xFFFB
#define B_START           0xFFFC
//#define B_   <free>       0xFFFD
#define B_EDIT            0xFFFE
#define B_RUN             0xFFFF

/*********************************************************************/
/* Button Viewtypes                                                  */
/* - Invisible:   Button is not visible in menu                      */
/* - Visible:     Button is visible in menu - can be activated       */
/* - Supressed:   Button is grayed out - can not be activated        */
/*********************************************************************/
#define BUTTON_INVISIBLE      0
#define BUTTON_VISIBLE        1
#define BUTTON_SUPRESSED      2

/*********************************************************************/
/* Button Type                                                       */
/* - Var update:  Sets a VDB variable to a specific value            */
/* - System:      Used by OS system                                  */
/* - Func call:   Calls a specific function                          */
/* - Touch:       Sets a VDB varable to a specific value             */
/*                to 1 when activated and 0 when released            */
/*********************************************************************/
#define BUTTON_VAR_UPDATE     0
#define BUTTON_SYSTEM         1
#define BUTTON_FUNC_CALL      2
#define BUTTON_TOUCH          3         // Not implemented yet

/*********************************************************************/
/* Button Structures                                                 */
/*********************************************************************/
struct button_struct
{
      U32   MagicNumber;                   /* A magic number to detect validity of data */
      char  *Name;                         /* Button name */
      char  *DisplayText;                  /* Display text on button */
      U8    ViewType;                      /* Display state */
      U8    ButtonType;                    /* Select button type */
      char  *VariableName;                 /* Variable name to set */
      U8    SetValue;                      /* Set value when button is pressed */
      buttonid_t Id;                       /* Unique button ID */
      void  (*callfunc)(buttonid_t id);    /* Function to call when button is pressed */

      /* Changed from Index to pointer for vardb vers.2 */
      varid_t  Var_ID;                     /* Unique variable ID. Changed for vardb version 2 */
      struct   button_struct *next;        /* Pointer to next button in group */
};

struct buttonlink_struct
{
   U32   MagicNumber;                   /* A magic number to detect validity of data */
   struct button_struct *This;          /* Pointer to this button array */
//   struct buttonlink_struct *prev;    /* Previus, zero if first */
   struct buttonlink_struct *next;      /* next, zero if last  */
};

/*********************************************************************/
/*                                                                   */
/* LINE DEFINITIONS                                                  */
/*                                                                   */
/*********************************************************************/

#define NUMBER_OF_LINES       11
#define MAX_DISPLAY_TEXT      23

/*********************************************************************/
/* Line Types                                                        */
/* used in Data Server protocol for Menulines identification         */
/* - Null:        Empty Line                                         */
/* - Link:        Linktext to new menu                               */
/* - Var RO:      Text and Read Only Variable                        */
/* - Var RW:      Text and Read Write Variable                       */
/* - Text:        Text only                                          */
/* - Link Var RO: Linktext and Read Only Variable                    */
/* - Link Var RW: Linktext and Read Write Variable                   */
/*********************************************************************/
#define PACKTYPE_STATIC_START  0
#define PACKTYPE_STATIC_END    6

#define PACKTYPE_NULL          0
#define PACKTYPE_LINK          1
#define PACKTYPE_VAR_RO        2
#define PACKTYPE_VAR_RW        3
#define PACKTYPE_TEXT          4
#define PACKTYPE_LINK_VAR_RO   5
#define PACKTYPE_LINK_VAR_RW   6

#define LINE_FORMAT_NONE       0

struct line_struct
{
      U32      MagicNumber;               /* A magic number to detect validity of data */
      char     *DisplayText;              /* Display text */
      access_t ViewPasswordLevel;         /* View Password level */
      U8       Linetype;                  /* Type: Empty, Links, Var RO, Var RW */

      /* Link information */
      char     *LinkName;                 /* Menuname in links */
      char     *LinkGroup;                /* Group name in links */

      /* Variable information */
      char     *VarName;                  /* Variable name */
      U16      Format;                    /* Special display view */

      struct menu_struct *menulink;       /* Pointer to links menu */
      varid_t  Var_ID;                    /* Unique variable ID */
      struct line_struct *nextline;
};

/*********************************************************************/
/*                                                                   */
/* MENU DEFINITIONS                                                  */
/*                                                                   */
/*********************************************************************/

/* Menu types used in Data Server protocol 2. */
#define MENUTYPE_TEXT         0
#define MENUTYPE_DYNAMIC      1     /* Dynamic menu with a reference to a menu function */
//#define MENUTYPE_GRAPHIC      2
//#define MENUTYPE_GRAPH        3     // Grafisk kurver linie, søjlediagram mv. til f.eks. Effektkurve
//#define MENUTYPE_LOG          4     // Grafisk 10000 liniers LOG
#define MENUTYPE_DYNAMIC_PAR  5     /* Dynamic menu including a parameter to the menu function */

//Why-parameters Call function
#define FUNC_LINK           1
#define FUNC_VAR_UPDATE     2
#define FUNC_BUTTON_CHANGE  3
#define FUNC_SUB_UPDATE     4
#define FUNC_RAW            5
#define FUNC_BACK_TO_STATIC 6
#define FUNC_REDRAW         7
#define FUNC_GET_EDIT_PARAMETERS 8

struct menu_struct
{
   U32 MagicNumber;                 /* A magic number to detect validity of data */
   char     *Name;                  /* Menu name */
   char     *DisplayText;           /* Menu display title */
   access_t ViewPasswordLevel;      /* View Password level */
   U32      MenuType;               /* text, graphicfile */
   union
   {
      struct
      {
         char *dummy1;
         char *dummy2;
         char *dummy3;
      } dummy;

      struct
      {
         size_t   NoOfLines;                       /* Number of Lines in menu */
         struct   line_struct *first_line;         /* Pointer to first line */
         struct   line_struct *last_line;          /* Pointer to last line in menu */
      } Text;

      struct
      {
         void  (*callfunc)(void *Socket);          /* Function to call and arguments */
         U8 FunctionWorks;                         /* 0 = Not tested, 1 = failed, 2 = Works */
      } Dynamic;

      struct
      {
         void  (*callfunc)(void *Socket, U32 Par); /* Function to call and arguments */
         U32 Parameter;                            /* Parameter to menu function */
         U8 FunctionWorks;                         /* 0 = Not tested, 1 = failed, 2 = Works */
      } DynamicParameter;

      struct
      {
         char     *Filename;                       /* Graphic filename */
      } Graphic;
   }Type;

   struct   menu_struct *next;         /* Pointer to next menu in group */
};

struct menu_group_struct
{
   U32 MagicNumber;                    /* A magic number to detect validity of data */
   char  *Name;                        /* Menu group name*/
   struct menu_struct *first_menu;     /* Pointer to first menu in this group, zero if none */
   struct menu_struct *last_menu;      /* Pointer to last menu in this group, zero if none */
   struct menu_group_struct *prev;     /* Pointer to previus group, zero if first */
   struct menu_group_struct *next;     /* Pointer to next group, zero if last. */
   struct button_struct *first_button; /* Pointer to first button in group */
   struct button_struct *last_button;  /* Pointer to last button in group */
};


// date format is as follows:  YYYY.MM.DD
// where: YYYY = year
//          MM = month (01-12)
//          DD = day (01-31)
// The separators between the fields are defined below. The separators SHALL be in double quotation marks:
#define YEAR_MONTH_SEPARATOR    "."
#define MONTH_DAY_SEPARATOR     "."

#endif
