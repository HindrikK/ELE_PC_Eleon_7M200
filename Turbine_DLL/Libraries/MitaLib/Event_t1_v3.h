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
#ifndef FILE_EVENT_T1_V3_H
#define FILE_EVENT_T1_V3_H

#include <os_lib.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

//BN struct EventTextStruct
//BN {
//BN    const U16 EventNo;
//BN    char EventText[30];
//BN };
struct EventTextStruct
{
   U16 EventNo;
   char *EventText;
};

//BN void UserEvent(struct EventTextStruct Event);
STATUS UserEvent(struct EventTextStruct Event);

STATUS GetEventNumber(struct EventTextStruct *Event, char *EventText);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------

#endif

