/*
This is not original Mita library.
This is replacing Mita Avet_t1_v3 function, coded by Eleon.
*/


#ifndef FILE_AVER_T1_V3_H
#define FILE_AVER_T1_V3_H

#include <os_lib.h>

#define BufLen20ms    5
#define BufLen100ms  10
#define BufLen1s     30
#define BufLen3s     30
#define BufLen30s    20


// ---------------------------------------------------------------------
// Other modules may use these variables and functions.
// ---------------------------------------------------------------------

struct S16Buffer
{
    S16       _20ms[BufLen20ms], _100ms[BufLen100ms],
        _1s[BufLen1s], _3s[BufLen3s],
        _30s[BufLen30s];
    U32  time;
};

struct U16Buffer
{
    U16     _20ms[BufLen20ms], _100ms[BufLen100ms],
        _1s[BufLen1s], _3s[BufLen3s],
        _30s[BufLen30s];
    U32  time;
};

struct S32Buffer
{
    S32      _20ms[BufLen20ms], _100ms[BufLen100ms],
        _1s[BufLen1s], _3s[BufLen3s],
        _30s[BufLen30s];
    U32  time;
};

struct U32Buffer
{
    U32    _20ms[BufLen20ms], _100ms[BufLen100ms],
        _1s[BufLen1s], _3s[BufLen3s],
        _30s[BufLen30s];
    U32  time;
};



S16     GetS16_100msAverage(const struct S16Buffer*const);
S16     GetS16_1sAverage(const struct S16Buffer*const);
S16     GetS16_3sAverage(const struct S16Buffer*const);
S16     GetS16_30sAverage(const struct S16Buffer*const);
S16     GetS16_10mAverage(const struct S16Buffer*const);
void    ClearS16Buffer(struct S16Buffer*);
U8      UpdateS16Buffer(struct S16Buffer*, S16);

U16     GetU16_100msAverage(const struct U16Buffer*const);
U16     GetU16_1sAverage(const struct U16Buffer*const);
U16     GetU16_3sAverage(const struct U16Buffer*const);
U16     GetU16_30sAverage(const struct U16Buffer*const);
U16     GetU16_10mAverage(const struct U16Buffer*const);
void    ClearU16Buffer(struct U16Buffer*);
U8      UpdateU16Buffer(struct U16Buffer*, U16);

S32     GetS32_100msAverage(const struct S32Buffer* const);
S32     GetS32_1sAverage(const struct S32Buffer* const);
S32     GetS32_3sAverage(const struct S32Buffer* const);
S32     GetS32_30sAverage(const struct S32Buffer* const);
S32     GetS32_10mAverage(const struct S32Buffer* const);
void    ClearS32Buffer(struct S32Buffer*);
U8  	UpdateS32Buffer(struct S32Buffer*, S32);

U32     GetU32_100msAverage(const struct U32Buffer*const);
U32     GetU32_1sAverage(const struct U32Buffer*const);
U32     GetU32_3sAverage(const struct U32Buffer*const);
U32     GetU32_30sAverage(const struct U32Buffer*const);
U32     GetU32_10mAverage(const struct U32Buffer*const);
void    ClearU32Buffer(struct U32Buffer*);
U8      UpdateU32Buffer(struct U32Buffer*, U32);


#endif

