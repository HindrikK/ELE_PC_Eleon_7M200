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
#ifndef FILE_MID2STAT_H
#define FILE_MID2STAT_H

#include <os_lib.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------
#define BufLen20ms    5
#define BufLen100ms  10
#define BufLen1s     3
#define BufLen3s     10
#define BufLen30s    20

struct Mid2StateStruct
{
    U16  Smod5;
    U16  Sdiv5;
    U16  Smod50;
    U16  Sdiv50;
    U16  Smod150;
    U16  Sdiv150;
    U16  Sdiv1500;
    U8 BufOffset20ms;
    U8 BufOffset100ms;
    U8 BufOffset1s;
    U8 BufOffset3s;
    U8 BufOffset30s;
    U8 ElementsInBuf20ms;
    U8 ElementsInBuf100ms;
    U8 ElementsInBuf1s;
    U8 ElementsInBuf3s;
    U8 ElementsInBuf30s;
    U8 Full20ms;
    U8 Full100ms;
    U8 Full1s;
    U8 Full3s;
    U8 Full30s;
};

extern struct Mid2StateStruct Mid2State;

extern U16 Mid2StateCounter;

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------
void Mid2StateUpdate(void);
void Mid2StateClear(void);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------

#endif

