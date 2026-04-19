#ifndef __m_def_h
#define __m_def_h

//redefine null in mita source codes
#ifdef NULL
#undef NULL
#endif

#ifndef WIN32_LEAN_AND_MEAN  //for winsock2 to work
#define WIN32_LEAN_AND_MEAN
#endif

//put all windows includes here...
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <float.h>
//for task

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

//redefine null in mita source codes
#ifdef NULL
#undef NULL
#define NULL 0
#endif
#define BOOL boolredefined  //changes names of BOOL to later define to U8



#define OS_NO_SUSPEND 0
#define OS_SUCCESS 0
//#define NULL 0

//#define true 1
//#define false 0

typedef int STATUS;
//typedef unsigned char BOOL;

typedef short S16;
typedef int S32;
//typedef long S64;

//typedef unsigned long U64;

//original...

typedef unsigned char      U8;
typedef U8 BOOL; 

typedef unsigned short     U16;
typedef unsigned int       U32;
typedef unsigned long long U64;

typedef signed char        S8;
//typedef signed short       S16;
//typedef signed int         S32;
typedef signed long long   S64;

typedef float              F32;
typedef double             F64;


// Max/min definitions

#define U8_MIN             0
#define U8_MAX             0xFF

#define U16_MIN            0
#define U16_MAX            0xFFFF

#define U32_MIN            0UL
#define U32_MAX            0xFFFFFFFFUL

#define U64_MIN            0ULL
#define U64_MAX            0xFFFFFFFFFFFFFFFFULL

#define S8_MIN             0x80
#define S8_MAX             0x7F

#define S16_MIN            0x8000
#define S16_MAX            0x7FFF

#define S32_MIN            0x80000000UL
#define S32_MAX            0x7FFFFFFFUL

#define S64_MIN            0x8000000000000000ULL
#define S64_MAX            0x7FFFFFFFFFFFFFFFULL

#define F32_MAX FLT_MAX
#define F32_MIN -(FLT_MAX)
//#define F32_MIN            -(3.40282347E+38)
//#define F32_MAX            3.40282347E+38

#define F64_MAX DBL_MAX
#define F64_MIN (-DBL_MIN)

//#define F64_MIN            -(1.79769313486231571E+308)
//#define F64_MAX            1.79769313486231571E+308


#define ON                 1
#define OFF                0


/*
#define TRUE               1
#define FALSE              0
*/

#endif
