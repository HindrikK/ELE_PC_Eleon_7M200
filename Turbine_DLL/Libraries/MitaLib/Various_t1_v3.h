//********************************************************************
//
//            Copyright (c) 2003 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date$
// $Author$
// $RCSfile$
// $Revision$
//
//*******************************************************************
#ifndef FILE_VARIOUS_T1_V3_H
#define FILE_VARIOUS_T1_V3_H

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------


#include "os_lib.h"
#define APP_INIT2        (U8)2  /* App. may initialise own variables */
#define APP_INIT2_DONE   (U8)2  /* App. have initialised all own variables */

#define APP_INIT3        (U8)3  /* App. may subscribe to foreign variables */
#define APP_INIT3_DONE   (U8)3  /* App. have subscribed to all needed variables */

#define APP_INIT4        (U8)4  /* App. may subscribe to foreign variables */
#define APP_INIT4_DONE   (U8)4  /* App. have subscribed to all needed variables */

#define APP_INIT5        (U8)5  /* App. may subscribe to foreign variables */
#define APP_INIT5_DONE   (U8)89  /* App. have subscribed to all needed variables */

#define APP_RUN AS_RUN

/**************************************************/
/* Convert from host to network order short       */
/**************************************************/
//..............U16 Htons(U16 Host);
/**************************************************/
/* Convert from host to network order long        */
/**************************************************/
//..................U32 Htonl(U32 Host);
/**************************************************/
/* Convert from network order to host order short */
/**************************************************/
//.................U16 Ntohs(U16 Net);
/**************************************************/
/* Convert from network order to host order long  */
/**************************************************/
//..................U32 Ntohl(U32 Net);

void Set_App_RequestId_StateId(varid_t RequestId, varid_t StateId);
extern varid_t Get_RequestId(void);
extern varid_t Get_StateId(void);


void AppDebugLog(U16 code, const char *text_format, ...);
void AppSystemLog(U16 code, const char *text_format, ...);
void AppSystemError(U16 code, const char *text_format, ...);
U8 ActivateAppSystemError(void);

#define SIZE_OF_ARRAY(Array) (sizeof(Array)/sizeof(Array[0]))
#define ELEMENT(array) array,(sizeof(array)/sizeof(array[0]))
#define STATUS_LINE_NUMBER(Status) AppSystemLog(1, "Status "#Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);
#define STATUS_LINE_VAR(Status) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);}
#define STATUS_LINE_VAR_RETURN(Status) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__); return;}
#define STATUS_LINE_VAR_RETURN_VALUE(Status) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__); return(Status);}
#define STATUS_LINE_VAR_RETURN_CONST(Status, ReturnValue) if(Status != 0) {AppSystemLog(1, "Status %d", Status);AppSystemLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__); return(ReturnValue);}

/********************************************************************

 FUNCTION NAME    CreateMenu
 -------------
 DESCRIPTION
 -----------
 If module state is equal to MODULE_INIT_STEP_1 one new menu is created.
 If module state is equal to MODULE_INIT_STEP_2 two lines are created.
 The first line links to the new menu.
 The second line links back to the previous menu.

  <Previous menu>
  -----------------
 |                 |         <New menu>
 |                 |         ------------------
 |Link new menu    | <----> |Link previous menu|
  -----------------         |                  |
                            |                  |
                             ------------------

 ARGUMENTS
 ---------
   ModuleState       Value: MODULE_INIT_STEP_1 / MODULE_INIT_STEP_2.
   UpperGroup        Pointer to name of the previous menu group.
   UpperMenu         Pointer to name of the previous menu.
   newline           Pointer to array of the new line (Link new Menu).
   elements          Number of new lines (Link new Menu).

   groupname         Pointer to the group name for the new menu.
   newmenu           Pointer to array of the new menu (New menu).
   MenuElements      Number of new menus (New menu).
   MenuName          Pointer to menu name.
   LocalLine         Pointer to array of the new line (Link previous Menu).
   LocalElements     Number of new lines (Link previous Menu).


 RETURN VALUES
 -------------
   STATUS            Error = none zero, no error = zero.

 HISTORY
 -------
    NAME         DATE        REMARKS
    BN/HJL       2002-03-21  New function.

*******************************************************************/
/*
STATUS CreateMenu(U8 ModuleState,
                 char *UpperGroup,
                 char *UpperMenu,
                 struct line_struct *newline,
                 size_t elements,

                 char *groupname,
                 struct menu_struct *newmenu,
                 size_t MenuElements,
                 char *MenuName,
                 struct line_struct *LocalLine,
                 size_t LocalElements);
*/



/********************************************************************

 FUNCTION NAME    StatusCodeActive
 -------------
 DESCRIPTION
 -----------
 Wraps the "OS_StatusCodeActiveErr" function (which returns an error
 status on inquiries to non-existent status codes).
 This function returns true if the specified status code exists _AND_
 is currently active. It returns false on any other condition - but, in
 addition, it writes out an error message to the log if the status code
 in question doesn't exist.
 The function has an upper limit of 3 specific error messages and a fourth
 general error message - after that no more messages are printed regardless
 of how many additional undefined status codes are encountered.

 ARGUMENTS
 ---------

 RETURN VALUES
 -------------
   STATUS            Status code active = none zero, inactive = zero.

 HISTORY
 -------
    NAME         DATE        REMARKS
    JSC       2003-04-3  New function.

*******************************************************************/

STATUS StatusCodeActive(U16 StatusCodeNo);




/********************************************************************

 FUNCTION NAME    StatusCodeActive
 -------------
 DESCRIPTION
 -----------
 Sets the current application state to be returned by "AppState".
 This function should only be called from the main application
 loop, where the application state is initially determined.


 ARGUMENTS
 ---------

 RETURN VALUES
 -------------
   STATUS            Status code active = none zero, inactive = zero.

 HISTORY
 -------
    NAME         DATE        REMARKS
    JSC       2003-04-3  New function.

*******************************************************************/

void SetAppState(U8 NewState);



/********************************************************************

 FUNCTION NAME    StatusCodeActive
 -------------
 DESCRIPTION
 -----------
 Returns the current application state (APP_INIT1, APP_INIT2,
 APP_INIT3, APP_RUN) for use by applications modules. This function
 relies on some primary application module to have called "SetAppState"
 previously.


 ARGUMENTS
 ---------

 RETURN VALUES
 -------------
   STATUS            Status code active = none zero, inactive = zero.

 HISTORY
 -------
    NAME         DATE        REMARKS
    JSC       2003-04-3  New function.

*******************************************************************/

U8 AppState(void);


// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
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

// ---------------------------------------------------------------------
// Safe cast of F32 to unsigned variables
// ---------------------------------------------------------------------
#define F32TOU64(f32_var, u64_var) S32 temporary_cast_variable;temporary_cast_variable = (S32)f32_var;if(temporary_cast_variable < 0){AppDebugLog(1, "Floting point cast error in %ld:", temporary_cast_variable);AppDebugLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);u64_var = 0};else u64_var = (U64)temporary_cast_variable;
#define F32TOU32(f32_var, u32_var) S32 temporary_cast_variable;temporary_cast_variable = (S32)f32_var;if(temporary_cast_variable < 0){AppDebugLog(1, "Floting point cast error in %ld:", temporary_cast_variable);AppDebugLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);u32_var = 0};else u32_var = (U32)temporary_cast_variable;
#define F32TOU16(f32_var, u16_var) S32 temporary_cast_variable;temporary_cast_variable = (S32)f32_var;if(temporary_cast_variable < 0 || temporary_cast_variable > U16_MAX){AppDebugLog(1, "Floting point cast error in %ld:", temporary_cast_variable);AppDebugLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);u16_var = 0;} else u16_var = (U16)temporary_cast_variable;
#define F32TOU8(f32_var, u8_var) S32 temporary_cast_variable;temporary_cast_variable = (S32)f32_var;if(temporary_cast_variable < 0 || temporary_cast_variable > U8_MAX){AppDebugLog(1, "Floting point cast error in %ld:", temporary_cast_variable);AppDebugLog(2, "Line %d", __LINE__);AppSystemLog(3, "File %s", __MODULE__);u8_var = 0;} else u8_var = (U8)temporary_cast_variable;

#endif
