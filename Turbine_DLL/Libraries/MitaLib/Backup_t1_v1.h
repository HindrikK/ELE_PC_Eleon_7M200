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
#ifndef FILE_BACKUP_H
#define FILE_BACKUP_H

#include <os_lib.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------


// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------
extern char *AppExportParameterPosition(void);
extern char *AppLocalParameterPosition(void);
extern char *AppBackupPosition(void);
STATUS SetupParameterBackupFileNames(varid_t StateId);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------

#endif

