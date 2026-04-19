//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
/*
FUNCTION:

Routines for calculating average values.

The calling program must allocate the buffers it intends to use like so:

struct FloatBuffer the_name_of_the_buffer;
______^^^^^____________________
/                               \
Change the data-type as necessary.


Rev. 	 Date	Prog.	Comment
------------------------------------------------------------------------------


------------------------------------------------------------------------------
PUBLIC FUNCTIONS:

!! Only routines working on floating-point values, are documented.
!! All the following routines have four counterparts, who each are based on
!! a different data-type.
!! To convert a description of a routine from floating-point to another
!! data-type, change all occurences of 'Float' (also where it appears inside
!! another word as in 'ClearFloatBuffer') to 'SignedInt', 'UnsignedInt',
!! 'SignedLong' or 'UnsignedLong'.
!! Also change all occurences of 'float' to 'signed int', unsigned int',
!! 'signed long' or 'unsigned long'.

Call:         ClearFloatBuffer(&Buffer)
Desc:         This routine initialises a buffer, and sets all average-values
to 0.
Arg1:         (struct FloatBuffer *const) A pointer to the buffer that
is to be cleared.
Return:       N/A.

Call:         UpdateFloatBuffer(&Buf, NewData)
Desc:         This routine should be called once every 20ms, with a new
data-value. This data will be included in the buffer, whose
average-values are then updated.
Arg1:         (struct FloatBuffer *const) A pointer to the buffer.
Arg2:         (const float) The new data-value.
Return:       N/A.

Call:         Return=GetFloat100msAverage(&Buf)
Desc:         This routine returns the average value calculated over the last
100ms.
Arg1:         (const struct FloatBuffer *const) A pointer to the buffer.
Return:       (float)

Call:         Return=GetFloat1sAverage(&Buf)
Desc:         This routine returns the average value calculated over the last
second.
Arg1:         (const struct FloatBuffer *const) A pointer to the buffer.
Return:       (float)

Call:         Return=GetFloat30sAverage(&Buf)
Desc:         This routine returns the average value calculated over the last
30 sec.
Arg1:         (const struct FloatBuffer *const) A pointer to the buffer.
Return:       (float)

Call:         Return=GetFloat10mAverage(&Buf)
Desc:         This routine returns the average value calculated over the last
10 min.
Arg1:         (const struct FloatBuffer *const) A pointer to the buffer.
Return:       (float)

Call:         Return=GetFloat1hAverage(&Buf)
Desc:         This routine returns the average value calculated over the last
hour.
Arg1:         (const struct FloatBuffer *const) A pointer to the buffer.
Return:       (float)

Call:         Return=GetFloat24hAverage(&Buf)
Desc:         This routine returns the average value calculated over the last
24 hours.
Arg1:         (const struct FloatBuffer *const) A pointer to the buffer.
Return:       (float)


------------------------------------------------------------------------------
EXTERNAL IDENTIFIERS REQUIRED:

All the buffers need to be allocated beforehand.
(see top of this header-file for details)

------------------------------------------------------------------------------
*/
#ifndef FILE_AVER_T2_V1_H
#define FILE_AVER_T2_V1_H

#include <lib_main.h>

#define Avg_BufLen20ms    5
#define Avg_BufLen100ms  10
#define Avg_BufLen1s     30
#define Avg_BufLen3s     30
#define Avg_BufLen30s    20


// ---------------------------------------------------------------------
// Other modules may use these variables and functions.
// ---------------------------------------------------------------------

struct Avg_S16Buffer
{
	S16 _20ms[Avg_BufLen20ms];
	S16 _100ms[Avg_BufLen100ms];
	S16 _1s[Avg_BufLen1s];
	S16 _3s[Avg_BufLen3s];
	S16 _30s[Avg_BufLen30s];
	U32  time;
};

struct Avg_U16Buffer
{
	U16 _20ms[Avg_BufLen20ms];
	U16 _100ms[Avg_BufLen100ms];
	U16 _1s[Avg_BufLen1s];
	U16 _3s[Avg_BufLen3s];
	U16 _30s[Avg_BufLen30s];
	U32  time;
};

struct Avg_S32Buffer
{
	S32 _20ms[Avg_BufLen20ms];
	S32 _100ms[Avg_BufLen100ms];
	S32 _1s[Avg_BufLen1s];
	S32 _3s[Avg_BufLen3s];
	S32 _30s[Avg_BufLen30s];
	U32  time;
};

struct Avg_U32Buffer
{
	U32 _20ms[Avg_BufLen20ms];
	U32 _100ms[Avg_BufLen100ms];
	U32 _1s[Avg_BufLen1s];
	U32 _3s[Avg_BufLen3s];
	U32 _30s[Avg_BufLen30s];
	U32  time;
};


/*
S16     Avg_GetS16_100msAverage(const struct Avg_S16Buffer*const);
S16     Avg_GetS16_1sAverage(const struct Avg_S16Buffer*const);
S16     Avg_GetS16_3sAverage(const struct Avg_S16Buffer*const);
S16     Avg_GetS16_30sAverage(const struct Avg_S16Buffer*const);
S16     Avg_GetS16_10mAverage(const struct Avg_S16Buffer*const);
void    Avg_ClearS16Buffer(struct Avg_S16Buffer*);
void    Avg_UpdateS16Buffer(*Avg_S16Buffer, S16);

U16     Avg_GetU16_100msAverage(const struct Avg_U16Buffer*const);
U16     Avg_GetU16_1sAverage(const struct Avg_U16Buffer*const);
U16     Avg_GetU16_3sAverage(const struct Avg_U16Buffer*const);
U16     Avg_GetU16_30sAverage(const struct Avg_U16Buffer*const);
U16     Avg_GetU16_10mAverage(const struct Avg_U16Buffer*const);
void    Avg_ClearU16Buffer(struct Avg_U16Buffer*);
void    Avg_UpdateU16Buffer(struct Avg_U16Buffer*, U16);
*/
S32     Avg_GetS32_100msAverage(const struct Avg_S32Buffer*const);
S32     Avg_GetS32_1sAverage(const struct Avg_S32Buffer*const);
S32     Avg_GetS32_3sAverage(const struct Avg_S32Buffer*const);
S32     Avg_GetS32_30sAverage(const struct Avg_S32Buffer*const);
S32     Avg_GetS32_10mAverage(const struct Avg_S32Buffer*const);
void    Avg_ClearS32Buffer(struct Avg_S32Buffer*);
void	Avg_UpdateS32Buffer(struct Avg_S32Buffer*, S32);
/*
U32     Avg_GetU32_100msAverage(const struct Avg_U32Buffer*const);
U32     Avg_GetU32_1sAverage(const struct Avg_U32Buffer*const);
U32     Avg_GetU32_3sAverage(const struct Avg_U32Buffer*const);
U32     Avg_GetU32_30sAverage(const struct Avg_U32Buffer*const);
U32     Avg_GetU32_10mAverage(const struct Avg_U32Buffer*const);
void    Avg_ClearU32Buffer(struct Avg_U32Buffer*);
void    Avg_UpdateU32Buffer(struct Avg_U32Buffer*, U32);
*/

#endif

