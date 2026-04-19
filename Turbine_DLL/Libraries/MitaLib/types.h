#ifndef __types_h_
#define __types_h_

#include "m_def.h"


#define __MODULE__ __FILE__


/* Definition of the types of the fields in the database */
/* The variable IDs are just pointers to the variables. */

typedef struct os_db_variable* varid_t;
typedef struct vardb_iovariable* iovarid_t;

#define NULL_VARID NULL


typedef S32 type_t;

typedef U32 scalevalue_t;


#define SCALE_NONE   (U8)0
#define SCALE_DIV    (U8)1
#define SCALE_MUL    (U8)2
#define SCALE_EXPMUL (U8)3
#define SCALE_EXPDIV (U8)4

typedef U8 scaletype_t;



typedef S8 precision_t;

typedef U8 access_t;
#define NO_ACCESS 255
#define SUM_ACCESS_ON_WRITE 250
#define ALL_ACCESS 0

typedef U8 unit_t;
typedef U8 log_t;
typedef U32 timetolive_t;
typedef U8 subhandler_t;

/* Date and time in millisecs since 1-Jan-1970 00:00:01 */
//#ifdef __time_t_defined
//#error time_t already defined.
//#error types.h in API must be included before types.h from compiler library.
//#error Try to change the order of include files.
//#endif
//#define _TIME_T_DEFINED /* used to avoid type redefinition from mingw sys/types.h */
//typedef unsigned long long time_t;

/* Definition of a  signed angle type */
typedef S32 ANGLE_SIGN;

/* Definition of an unsigned angle type */
typedef S32 ANGLE;

/* Definition of the BOOL type */
//typedef enum { false, true } BOOL;
/* JLL: 16/10-2003 enums are not OSI-types, variable size*/
//typedef U8 BOOL; //redefinition error
#define false (U8)0 /*FIXME should not use lower-case*/
#define true  (U8)1 /*FIXME should not use lowercase*/

#ifdef __GNUC__
/*@-matchfields@*/
#define _TM_DEFINED
struct tm
{
	int tm_sec;   /* seconds after the minute, 0 to 60
					 (0 - 60 allows for the occasional leap second) */
	int tm_min;   /* minutes after the hour, 0 to 59 */
	int tm_hour;  /* hours since midnight, 0 to 23 */
	int tm_mday;  /* day of the month, 1 to 31 */
	int tm_mon;   /* months since January, 0 to 11 */
	int tm_year;  /* years since 1900 */
	int tm_wday;  /* days since Sunday, 0 to 6 */
	int tm_yday;  /* days since January 1, 0 to 365 */
	int tm_isdst; /* Daylight Savings Time flag */
	int tm_msec;  /* Milliseconds, 0 to 999 [New field] */

};
#endif
/* struct tm holds the components of a calendar time, called the broken-down
 * time. The value of tm_isdst is positive if Daylight Savings Time is in
 * effect, zero if Daylight Savings Time is not in effect, and negative if
 * the information is not available.
 */


#define TYP_8    0x1
#define TYP_16   0x2
#define TYP_32   0x4
#define TYP_64   0x8

/* A type value masked with TYPE_LENGTH_MASK will give the length in
   bytes of the type. */
#define TYPE_LENGTH_MASK 0x0000FFFF

#define TYPE_TYPE_MASK   0x7FFF0000

/* TYP_LNG is used for types stored
   externally in the VarDB (64 bit
   integers, strings, and summations).
*/
#define TYP_LNG     0x00010000

#define TYP_SGN     0x00020000
#define TYP_INT     0x00040000
#define TYP_BOL     0x00080000
#define TYP_STR     0x00100000
#define TYP_ESUM    0x00200000
#define TYP_SSUM    0x00400000
#define TYP_SUM     0x00800000
#define TYP_ARR     0x01000000
#define TYP_TIME    0x02000000
#define TYP_ENUM    0x04000000
#define TYP_FLOAT   0x08000000
#define TYP_COM     0x10000000
#define TYP_ANGLE   0x20000000
#define TYP_AVAIL   0x40000000
#define TYP_STATSUM  0x80000000

/* Table of variable database data types */
/*================================================================================*/
/*                     Basic        Sign    Special     Pointed   Data            */
/*                     Data type    Bit     Data type   Data      Length          */
/*================================================================================*/
#define TYPE_NONE      (0                                                         )
#define TYPE_BOOL      (TYP_INT   | TYP_BOL                       | TYP_8         )
#define TYPE_U8        (TYP_INT                                   | TYP_8         )
#define TYPE_S8        (TYP_INT   | TYP_SGN                       | TYP_8         )
#define TYPE_U16       (TYP_INT                                   | TYP_16        )
#define TYPE_S16       (TYP_INT   | TYP_SGN                       | TYP_16        )
#define TYPE_U32       (TYP_INT                                   | TYP_32        )
#define TYPE_S32       (TYP_INT   | TYP_SGN                       | TYP_32        )
#define TYPE_U64       (TYP_INT                                   | TYP_64        )
#define TYPE_S64       (TYP_INT   | TYP_SGN                       | TYP_64        )
#define TYPE_STRING    (                      TYP_STR   | TYP_LNG                 )
#define TYPE_ESUM      (                      TYP_ESUM  | TYP_LNG | sizeof (ESUM) )
#define TYPE_SSUM      (                      TYP_SSUM  | TYP_LNG | 0x000000a4 )
#define TYPE_SUM       (                      TYP_SUM   | TYP_LNG | sizeof (SUM)  )
#define TYPE_STATSUM (                        TYP_STATSUM | TYP_LNG | sizeof (STATSUM)  )
#define TYPE_AVAIL     (                      TYP_AVAIL | TYP_LNG | sizeof (AVAIL))
#define TYPE_ARR       (                      TYP_ARR   | TYP_LNG                 )
#define TYPE_TIME      (TYP_INT             | TYP_TIME            | TYP_64        )
#define TYPE_ENUM      (TYP_INT             | TYP_ENUM            | TYP_32        )
#define TYPE_F32       (TYP_FLOAT                                 | TYP_32        )
#define TYPE_F64       (TYP_FLOAT                                 | TYP_64        )
#define TYPE_COM       (                      TYP_COM                             )
#define TYPE_ANGLE_SGN (TYP_INT   | TYP_SGN | TYP_ANGLE           | TYP_32        )
#define TYPE_ANGLE     (TYP_INT             | TYP_ANGLE           | TYP_32        )
/*================================================================================*/



/*********************************************************************/
/* The data structures of the summations                             */
/*********************************************************************/
#define  MAX_DAYS   31
#define  MAX_MONTHS 12
#define  MAX_YEARS  30

// The element of an energy summation
typedef struct energy
{
	U64 Produced;          // Produced non reactive energi
	U64 Consumed;          // Consumed non reactive energi
	U64 ProducedReactive;  // Produced reactive energi
	U64 ConsumedReactive;  // Consumed reactive energi
	time_t Start;          // The start time for this summation
}ENERGY;


typedef struct energysummation
{
	ENERGY  Total;
	ENERGY  Subtotal1;
	ENERGY  Subtotal2;
	ENERGY  Day;
	ENERGY  Month;
	ENERGY  Year;
}ENERGYSUMMATION;

// The energy summation
typedef struct
{
	// Variables for housekeeping
	time_t  LastUpdated;
	struct energysummation e;
}ESUM;

// The element of an activation and
// service summation
typedef struct service
{
	U64 Activated;        // Times activated
	U64 Sumtime;          // The time in the active state
	time_t Start;         // The start time for this summation
}SERVICE;


typedef struct servicesummation
{
	SERVICE Total;
	SERVICE Subtotal1;
	SERVICE Subtotal2;
	SERVICE Day;
	SERVICE Month;
	SERVICE Year;
}SERVICESUMMATION;

// The activation and service summation
// Delta time and old time is used to
// adjust the extrapolated time on the
// transistion from active to not active
typedef struct
{
	// Variables for housekeeping
	U8      CurrentStatus; // The current state of this variable
	time_t  LastReleased;
	time_t  LastActivated;
	struct servicesummation s;
}SSUM;

typedef struct simple
{
	U64 Sum;              // Sum
	time_t Start;         // The start time for this summation
}SIMPLE;

struct simplesummation
{
	SIMPLE Total;
	SIMPLE Subtotal1;
	SIMPLE Subtotal2;
	SIMPLE Day;
	SIMPLE Month;
	SIMPLE Year;
};

typedef struct simpelsummation
{
	// Variables for housekeeping
	time_t  LastUpdated;
	struct simplesummation s;
}SUM;

// The element of an activation and
// statistic summation
typedef struct statistic
{
	S32 Min;
	S32 Max;
	S32 Sum;
	S64 Count;
	time_t Start;
}STATISTIC;

typedef struct statisticsummation
{
	STATISTIC Total;
	STATISTIC Subtotal1;
	STATISTIC Subtotal2;
	STATISTIC Day;
	STATISTIC Month;
	STATISTIC Year;
}STATISTICSUMMATION;

// The activation and service summation
// Delta time and old time is used to
// adjust the extrapolated time on the
// transistion from active to not active
typedef struct
{
	// Variables for housekeeping
	U8      CurrentStatus; // The current state of this variable
	time_t  LastUpdated;
	U64     UpdateInterval;
	S32     LastValue;
	struct statisticsummation s;
}STATSUM;

/***************************************************************/
/*                                                             */
/* Availability structures                                     */
/*                                                             */
/***************************************************************/

// Number og group definitions
#define NUMBER_OF_AVAIL_GROUPS   32
#define AV_MAX_DAYS   31
#define AV_MAX_MONTHS 12
#define AV_MAX_YEARS  30

// The element of an active availability
typedef struct av_active
{
	U64 Activated;        // Times activated
	U64 Sumtime;          // The time in the active state
	time_t Start;         // The start time for this summation
	time_t Stop;
}AV_ACTIVE;

// The element of an availability result
typedef struct av_result
{
	time_t PeriodStart;
	time_t PeriodStop;
	time_t LastResetTime;
	U64 Activated;          // Times activated
	time_t PeriodAvTime;    // The time in the active state element
	time_t PeriodTotalTime; // The time from all groups
	U16 Percentage;         // Calculated Percentage
 //   S8 InfluenceFactor;     // Influence Factor
}AV_RESULT;

// The element to be save as history
typedef struct availability_active_type
{
	AV_ACTIVE Active[NUMBER_OF_AVAIL_GROUPS + 1];
	AV_RESULT Result;
}AV_ACTIVE_RESULT;

// counts within a range of trigger Group 1..32
struct availability_active
{
	AV_ACTIVE_RESULT Total;
	AV_ACTIVE_RESULT Subtotal1;
	AV_ACTIVE_RESULT Subtotal2;
	AV_ACTIVE_RESULT ThisDay;
	AV_ACTIVE_RESULT ThisMonth;
	AV_ACTIVE_RESULT ThisYear;
};

/*struct availability_history
{
   AV_RESULT Day[AV_MAX_DAYS][NUMBER_OF_AVAIL_GROUPS+1];
   AV_RESULT Month[AV_MAX_MONTHS][NUMBER_OF_AVAIL_GROUPS+1];
   AV_RESULT Year[AV_MAX_YEARS][NUMBER_OF_AVAIL_GROUPS+1];
}; */

typedef struct
{
	struct availability_active      Live;
	//    struct availability_history     History;
	   // Variables for housekeeping
	U8     LastActiveGroup;
	S8     InfluenceFactor[NUMBER_OF_AVAIL_GROUPS + 1];     // Influence Factor
	time_t LasttimeActivated[NUMBER_OF_AVAIL_GROUPS + 1];
	time_t LasttimeReleased[NUMBER_OF_AVAIL_GROUPS + 1];
}AVAIL;

typedef union vardbvalue
{
	char*       string;
	BOOL        bool;
	U8          u8;
	S8          s8;
	U16         u16;
	S16         s16;
	U32         u32;
	S32         s32;
	U64         u64;
	S64         s64;
	time_t      time;
	F32         f32;
	F64         f64;
	ANGLE       angle;
	ANGLE_SIGN  angle_sign;
	const char* stringconstant;
	ESUM*       esum;
	SSUM*       ssum;
	SUM*        sum;
	AVAIL*      avail;
	STATSUM*    statistic;
} value_t;

typedef struct _CFILE
{
	char **section;
	char ***arg;
	char *buf;

	int  section_num;
	int  arg_num;
	int  buf_size;
} CFILE;

typedef enum _CFGTYPE
{
	TYPE_INT,
	TYPE_CHAR_PTR
} CFGTYPE;


#endif