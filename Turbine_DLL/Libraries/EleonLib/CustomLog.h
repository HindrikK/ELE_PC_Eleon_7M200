//*****************************PEPTOOL Header Start******************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_CUSTOMLOG_H
#define FILE_CUSTOMLOG_H

#include <lib_main.h>


typedef struct _customLog* CustomLog;


//*******************************************************************************************
// 
//*******************************************************************************************

CustomLog CustomLog_New(const char* /*logVarName*/, int/*capacity*/, int/*stringSize(max 128)*/);

int CustomLog_ClearAll(CustomLog);

int CustomLog_MakeEntry(CustomLog, const char* /*text*/);

int CustomLog_Capacity(CustomLog);

int CustomLog_StringSize(CustomLog);


#endif
