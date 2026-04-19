/********************************************************************/
/*                                                                  */
/*            Copyright (c) 2005 Mita-Teknik a/s                    */
/*                                                                  */
/********************************************************************/
/*  $Date$
 *  $Author$
 *  $RCSfile$
 *  $Revision$ */
/********************************************************************/
/*                                                                  */
/* DESCRIPTION                                                      */
/*                                                                  */
/*     Macros to initialize Menus                                   */
/*                                                                  */
/* FUNCTIONS                                                        */
/*                                                                  */
/*     NA                                                           */
/*                                                                  */
/********************************************************************/

#ifndef __MENU_MACROS_H__
#define __MENU_MACROS_H__

#define MENU_ELEMENT_MENU_TEXT(Name, Password)                                   \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Menu name */                                 \
   "",                           /* Display text */                              \
   Password,                     /* View password level */                       \
   MENUTYPE_TEXT,                /* Menu type */                                 \
}

#ifdef __GNUC__
#define MENU_ELEMENT_MENU_DYNAMIC(Name, Password, MenuFunc)                      \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Menu name */                                 \
   "",                           /* Display text */                              \
   Password,                     /* View password level */                       \
   MENUTYPE_DYNAMIC,             /* Menu type */                                 \
   {.Dynamic={MenuFunc,          /* Menu function */                             \
   0}},                                                                          \
}
#else
#define MENU_ELEMENT_MENU_DYNAMIC(Name, Password, MenuFunc)                      \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Menu name */                                 \
   "",                           /* Display text */                              \
   Password,                     /* View password level */                       \
   MENUTYPE_DYNAMIC,             /* Menu type */                                 \
   (char *)MenuFunc,                     /* Menu function */                             \
}
#endif

#define MENU_ELEMENT_MENU_DYNAMIC_PAR(Name, Password, MenuFunc, Parameter)       \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Menu name */                                 \
   "",                           /* Display text */                              \
   Password,                     /* View password level */                       \
   MENUTYPE_DYNAMIC_PAR,         /* Menu type */                                 \
   MenuFunc,                     /* Menu function */                             \
   Parameter,                    /* Parameter to menu function */                \
}

#define MENU_ELEMENT_LINE_LINK(DisplayText, Password, LinkMenu, LinkGroup)       \
{                                                                                \
   0,                            /* MagicNumber */                               \
   DisplayText,                  /* Display text */                              \
   Password,                     /* View Password level */                       \
   PACKTYPE_LINK,                /* Type: Empty, Links, Var RO, Var RW */        \
   LinkMenu,                     /* Menuname in links  */                        \
   LinkGroup,                    /* Group name in links */                       \
}

#define MENU_ELEMENT_LINE_VARRO(DisplayText, Password, Varname, Format)          \
{                                                                                \
   0,                            /* MagicNumber */                               \
   DisplayText,                  /* Display text */                              \
   Password,                     /* View Password level */                       \
   PACKTYPE_VAR_RO,              /* Type: Empty, Links, Var RO, Var RW */        \
   0,                                                                            \
   0,                                                                            \
   Varname,                      /* Variabel name in Variable Database */        \
   Format,                       /* Special display view */                      \
}

#define MENU_ELEMENT_LINE_VARRW(DisplayText, Password, Varname, Format)          \
{                                                                                \
   0,                            /* MagicNumber */                               \
   DisplayText,                  /* Display text */                              \
   Password,                     /* View Password level */                       \
   PACKTYPE_VAR_RW,              /* Type: Empty, Links, Var RO, Var RW */        \
   0,                                                                            \
   0,                                                                            \
   Varname,                      /* Variabel name in Variable Database */        \
   Format,                       /* Special display view */                      \
}

#define MENU_ELEMENT_LINE_LINK_VARRO(DisplayText, Password, LinkMenu, LinkGroup, Varname, Format) \
{                                                                                \
   0,                            /* MagicNumber */                               \
   DisplayText,                  /* Display text */                              \
   Password,                     /* View Password level */                       \
   PACKTYPE_LINK_VAR_RO,         /* Type: Empty, Links, Var RO, Var RW */        \
   LinkMenu,                     /* Menuname in links  */                        \
   LinkGroup,                    /* Group name in links */                       \
   Varname,                      /* Variabel name in Variable Database */        \
   Format,                       /* Special display view */                      \
}

#define MENU_ELEMENT_LINE_LINK_VARRW(DisplayText, Password, LinkMenu, LinkGroup, Varname, Format) \
{                                                                                \
   0,                            /* MagicNumber */                               \
   DisplayText,                  /* Display text */                              \
   Password,                     /* View Password level */                       \
   PACKTYPE_LINK_VAR_RW,         /* Type: Empty, Links, Var RO, Var RW */        \
   LinkMenu,                     /* Menuname in links  */                        \
   LinkGroup,                    /* Group name in links */                       \
   Varname,                      /* Variabel name in Variable Database */        \
   Format,                       /* Special display view */                      \
}

#define MENU_ELEMENT_LINE_TEXT(DisplayText, Password)                            \
{                                                                                \
   0,                            /* MagicNumber */                               \
   DisplayText,                  /* Display text */                              \
   Password,                     /* View Password level */                       \
   PACKTYPE_TEXT,                /* Type: Empty, Links, Var RO, Var RW */        \
}

#define MENU_ELEMENT_LINE_EMPTY(Password)                                        \
{                                                                                \
   0,                            /* MagicNumber */                               \
   "",                           /* Display text */                              \
   Password,                     /* View Password level */                       \
   PACKTYPE_NULL,                /* Type: Empty, Links, Var RO, Var RW */        \
}

#define MENU_ELEMENT_BUTTON_VAR(Name, DisplayText, VarName, SetVal)              \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Button name */                               \
   DisplayText,                  /* Display text */                              \
   BUTTON_VISIBLE,               /* Display state */                             \
   BUTTON_VAR_UPDATE,            /* Select button type */                        \
   VarName,                      /* Variabel name to set */                      \
   SetVal,                       /* Set value when button is pressed */          \
   0,                            /* Unique button ID */                          \
}

#define MENU_ELEMENT_BUTTON_FUNCXX(Name, DisplayText, VarName, SetVal, ButtonId) \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Button name */                               \
   DisplayText,                  /* Display text */                              \
   BUTTON_VISIBLE,               /* Display state */                             \
   BUTTON_VAR_UPDATE,            /* Select button type */                        \
   VarName,                      /* Variabel name to set */                      \
   SetVal,                       /* Set value when button is pressed */          \
   ButtonId,                     /* Unique button ID */                          \
}

#define MENU_ELEMENT_BUTTON_FUNCCALL(Name, DisplayText, CallFunc)                \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Button name */                               \
   DisplayText,                  /* Display text */                              \
   BUTTON_VISIBLE,               /* Display state */                             \
   BUTTON_FUNC_CALL,             /* Select button type */                        \
   "",                           /* Variabel name to set */                      \
   0,                            /* Set value when button is pressed */          \
   0,                            /* Unique button ID */                          \
   CallFunc,                     /* Function to call, when button is pressed */  \
}

#define MENU_ELEMENT_BUTTON_SYSTEM(Name, DisplayText, ButtonId)                  \
{                                                                                \
   0,                            /* MagicNumber */                               \
   Name,                         /* Button name */                               \
   DisplayText,                  /* Display text */                              \
   BUTTON_VISIBLE,               /* Display state */                             \
   BUTTON_SYSTEM,                /* Select button type */                        \
   "",                           /* Variabel name to set */                      \
   0,                            /* Set value when button is pressed */          \
   ButtonId,                     /* Unique button ID */                          \
}


#endif
