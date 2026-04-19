#ifndef OS_LIB_H
#define OS_LIB_H

#include "types.h"
#include "vardb_macros.h"
#include "SOCKDEFS.H"

#include <math.h>
#include "os_sts.h"
#include "menudefs.h"
#include "stscode_macros.h"
#include "menu_macros.h"
//#include "action_server_api.h"
//#include "emaildefs.h"


/*********************************************************************/
/*                                                                   */
/*      Define standard data types defined in ISO C 99: 7.18         */
/*                                                                   */
/*********************************************************************/

/* Exact integral types - signed */
typedef signed char             int8_t;
typedef signed short int        int16_t;
typedef signed long int         int32_t;
typedef signed long long int    int64_t;

/* Exact integral types - unsigned */
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned long int       uint32_t;
typedef unsigned long long int  uint64_t;

/* Small types - signed */
typedef signed char             int_least8_t;
typedef signed short int        int_least16_t;
typedef signed long int         int_least32_t;
typedef signed long long int    int_least64_t;

/* Small types - unsigned */
typedef unsigned char           uint_least8_t;
typedef unsigned short int      uint_least16_t;
typedef unsigned long int       uint_least32_t;
typedef unsigned long long int  uint_least64_t;

/* Fast types - signed */
typedef int                     int_fast8_t;
typedef int                     int_fast16_t;
typedef int                     int_fast32_t;
typedef signed long long int    int_fast64_t;

/* Fast types - unsigned */
typedef unsigned char           uint_fast8_t;
typedef unsigned short int      uint_fast16_t;
typedef unsigned long int       uint_fast32_t;
typedef unsigned long long      uint_fast64_t;


/*************************************************************************/
/*                                                                       */
/*      Application related defines                                      */
/*                                                                       */
/*************************************************************************/



/*************************************************************************/
/*                                                                       */
/*      OS related defines                                               */
/*                                                                       */
/*************************************************************************/
/* Define standard data types. */
//#ifndef VOID
#define VOID    void
typedef char                    CHAR;
typedef int                     INT;
typedef long                    SIGNED;
typedef unsigned char           UNSIGNED_CHAR;
typedef unsigned long           UNSIGNED;
typedef int                     STATUS;
typedef unsigned char           DATA_ELEMENT;
typedef DATA_ELEMENT            OPTION;
typedef unsigned long *         UNSIGNED_PTR;
typedef unsigned char *         BYTE_PTR;
// Nucleus types
typedef U8  UINT8;
typedef S8  INT8;
typedef U16 UINT16;
typedef S16 INT16;
typedef U32 UINT32;
typedef S32 INT32;
//#endif

/* Define constants for use in service parameters.  */
#define         OS_OR                           0
#define         OS_OR_CONSUME                   1
#define         OS_AND                          2
#define         OS_AND_CONSUME                  3
#define         OS_PREEMPT                      10
#define         OS_NO_PREEMPT                   8
#define         OS_SUSPEND                      0xFFFFFFFFUL
#define         OS_NO_SUSPEND                   0
#define         OS_START                        12
#define         OS_NO_START                     9
#define         OS_DISABLE_TIMER                4
#define         OS_ENABLE_TIMER                 5
#define         OS_NULL                         0
#define         OS_FALSE                        0
#define         OS_TRUE                         1
#define         OS_FIFO                         6
#define         OS_FIXED_SIZE                   7
#define         OS_PRIORITY                     11
#define         OS_VARIABLE_SIZE                13

/* Define constants that are target dependent or internal used. */
#define         OS_MIN_STACK_SIZE               240
#define         OS_MAX_NAME                     8
#define         OS_MAX_VECTORS                  8
#define         OS_MAX_LISRS                    8

/* Define interrupt lockout and enable constants.  */
#define         OS_DISABLE_INTERRUPTS           0xC0
#define         OS_ENABLE_INTERRUPTS            0x00

/* Define task suspension constants.  */
#define         OS_READY                        0
#define         OS_DRIVER_SUSPEND               10
#define         OS_EVENT_SUSPEND                7
#define         OS_FINISHED                     11
#define         OS_MAILBOX_SUSPEND              3
#define         OS_MEMORY_SUSPEND               9
#define         OS_PARTITION_SUSPEND            8
#define         OS_PIPE_SUSPEND                 5
#define         OS_PURE_SUSPEND                 1
#define         OS_QUEUE_SUSPEND                4
#define         OS_SEMAPHORE_SUSPEND            6
#define         OS_SLEEP_SUSPEND                2
#define         OS_TERMINATED                   12

/* Define service completion status constants.  */
#define         OS_SUCCESS                      0
#define         OS_END_OF_LOG                   -1
#define         OS_GROUP_DELETED                -2
#define         OS_INVALID_DELETE               -3
#define         OS_INVALID_DRIVER               -4
#define         OS_INVALID_ENABLE               -5
#define         OS_INVALID_ENTRY                -6
#define         OS_INVALID_FUNCTION             -7
#define         OS_INVALID_GROUP                -8
#define         OS_INVALID_HISR                 -9
#define         OS_INVALID_MAILBOX              -10
#define         OS_INVALID_MEMORY               -11
#define         OS_INVALID_MESSAGE              -12
#define         OS_INVALID_OPERATION            -13
#define         OS_INVALID_PIPE                 -14
#define         OS_INVALID_POINTER              -15
#define         OS_INVALID_POOL                 -16
#define         OS_INVALID_PREEMPT              -17
#define         OS_INVALID_PRIORITY             -18
#define         OS_INVALID_QUEUE                -19
#define         OS_INVALID_RESUME               -20
#define         OS_INVALID_SEMAPHORE            -21
#define         OS_INVALID_SIZE                 -22
#define         OS_INVALID_START                -23
#define         OS_INVALID_SUSPEND              -24
#define         OS_INVALID_TASK                 -25
#define         OS_INVALID_TIMER                -26
#define         OS_INVALID_VECTOR               -27
#define         OS_MAILBOX_DELETED              -28
#define         OS_MAILBOX_EMPTY                -29
#define         OS_MAILBOX_FULL                 -30
#define         OS_MAILBOX_RESET                -31
#define         OS_NO_MEMORY                    -32
#define         OS_NO_MORE_LISRS                -33
#define         OS_NO_PARTITION                 -34
#define         OS_NOT_DISABLED                 -35
#define         OS_NOT_PRESENT                  -36
#define         OS_NOT_REGISTERED               -37
#define         OS_NOT_TERMINATED               -38
#define         OS_PIPE_DELETED                 -39
#define         OS_PIPE_EMPTY                   -40
#define         OS_PIPE_FULL                    -41
#define         OS_PIPE_RESET                   -42
#define         OS_POOL_DELETED                 -43
#define         OS_QUEUE_DELETED                -44
#define         OS_QUEUE_EMPTY                  -45
#define         OS_QUEUE_FULL                   -46
#define         OS_QUEUE_RESET                  -47
#define         OS_SEMAPHORE_DELETED            -48
#define         OS_SEMAPHORE_RESET              -49
#define         OS_TIMEOUT                      -50
#define         OS_UNAVAILABLE                  -51

/* Define system errors.  */
#define         OS_ERROR_CREATING_TIMER_HISR    1
#define         OS_ERROR_CREATING_TIMER_TASK    2
#define         OS_STACK_OVERFLOW               3
#define         OS_UNHANDLED_INTERRUPT          4


/* Define constants for the number of UNSIGNED words in each of the basic
   system data structures.  */

   //#define         OS_TASK_SIZE                    42
#define         OS_TASK_SIZE                    45
// #define         OS_HISR_SIZE                    22
#define         OS_HISR_SIZE                    26
#define         OS_MAILBOX_SIZE                 13
#define         OS_QUEUE_SIZE                   18
#define         OS_PIPE_SIZE                    18
//#define         OS_SEMAPHORE_SIZE               10
#define         OS_SEMAPHORE_SIZE               12
#define         OS_EVENT_GROUP_SIZE             9
#define         OS_PARTITION_POOL_SIZE          15
#define         OS_MEMORY_POOL_SIZE             17
#define         OS_TIMER_SIZE                   17
#define         OS_PROTECT_SIZE                 2
#define         OS_DRIVER_SIZE                  3


/* Define OS data structure with all internal information hidden.  */
typedef struct OS_TASK_STRUCT
{
	UNSIGNED      words[OS_TASK_SIZE];
} OS_TASK;

typedef struct OS_HISR_STRUCT
{
	UNSIGNED      words[OS_HISR_SIZE];
} OS_HISR;

typedef struct OS_MAILBOX_STRUCT
{
	UNSIGNED      words[OS_MAILBOX_SIZE];
} OS_MAILBOX;

typedef struct OS_QUEUE_STRUCT
{
	UNSIGNED      words[OS_QUEUE_SIZE];
} OS_QUEUE;

typedef struct OS_PIPE_STRUCT
{
	UNSIGNED      words[OS_PIPE_SIZE];
} OS_PIPE;

typedef struct OS_SEMAPHORE_STRUCT
{
	UNSIGNED       words[OS_SEMAPHORE_SIZE];
} OS_SEMAPHORE;

typedef struct OS_EVENT_GROUP_STRUCT
{
	UNSIGNED       words[OS_EVENT_GROUP_SIZE];
} OS_EVENT_GROUP;

typedef struct OS_PARTITION_POOL_STRUCT
{
	UNSIGNED       words[OS_PARTITION_POOL_SIZE];
} OS_PARTITION_POOL;

typedef struct OS_MEMORY_POOL_STRUCT
{
	UNSIGNED       words[OS_MEMORY_POOL_SIZE];
} OS_MEMORY_POOL;

typedef struct OS_TIMER_STRUCT
{
	UNSIGNED       words[OS_TIMER_SIZE];
} OS_TIMER;

typedef struct OS_PROTECT_STRUCT
{
	UNSIGNED       words[OS_PROTECT_SIZE];
} OS_PROTECT;

/* Define I/O driver request structures.  */
struct OS_INITIALIZE_STRUCT
{
	VOID       *os_io_address;              /* Base IO address          */
	UNSIGNED    os_logical_units;           /* Number of logical units  */
	VOID       *os_memory;                  /* Generic memory pointer   */
	INT         os_vector;                  /* Interrupt vector number  */
};

struct OS_ASSIGN_STRUCT
{
	UNSIGNED    os_logical_unit;            /* Logical unit number      */
	INT         os_assign_info;             /* Additional assign info   */
};

struct OS_RELEASE_STRUCT
{
	UNSIGNED    os_logical_unit;            /* Logical unit number      */
	INT         os_release_info;            /* Additional release info  */
};

struct OS_INPUT_STRUCT
{
	UNSIGNED    os_logical_unit;            /* Logical unit number      */
	UNSIGNED    os_offset;                  /* Offset of input          */
	UNSIGNED    os_request_size;            /* Requested input size     */
	UNSIGNED    os_actual_size;             /* Actual input size        */
	VOID       *os_buffer_ptr;              /* Input buffer pointer     */
};

struct OS_OUTPUT_STRUCT
{
	UNSIGNED    os_logical_unit;            /* Logical unit number      */
	UNSIGNED    os_offset;                  /* Offset of output         */
	UNSIGNED    os_request_size;            /* Requested output size    */
	UNSIGNED    os_actual_size;             /* Actual output size       */
	VOID       *os_buffer_ptr;              /* Output buffer pointer    */
};

struct OS_STATUS_STRUCT
{
	UNSIGNED    os_logical_unit;            /* Logical unit number      */
	VOID       *os_extra_status;            /* Additional status ptr    */
};

struct OS_TERMINATE_STRUCT
{
	UNSIGNED    os_logical_unit;            /* Logical unit number      */
};


typedef struct OS_DRIVER_REQUEST_STRUCT
{
	INT         os_function;                /* I/O request function     */
	UNSIGNED    os_timeout;                 /* Timeout on request       */
	STATUS      os_status;                  /* Status of request        */
	UNSIGNED    os_supplemental;            /* Supplemental information */
	VOID       *os_supplemental_ptr;        /* Supplemental info pointer*/

  /* Define a union of all the different types of request structures. */
	union OS_REQUEST_INFO_UNION
	{
		struct OS_INITIALIZE_STRUCT     os_initialize;
		struct OS_ASSIGN_STRUCT         os_assign;
		struct OS_RELEASE_STRUCT        os_release;
		struct OS_INPUT_STRUCT          os_input;
		struct OS_OUTPUT_STRUCT         os_output;
		struct OS_STATUS_STRUCT         os_status;
		struct OS_TERMINATE_STRUCT      os_terminate;
	} os_request_info;

} OS_DRIVER_REQUEST;

typedef struct OS_DRIVER_STRUCT
{
	UNSIGNED       words[OS_DRIVER_SIZE];
	CHAR           os_driver_name[OS_MAX_NAME];
	VOID     *os_info_ptr;
	UNSIGNED os_driver_id;
	VOID(*os_driver_entry)(struct OS_DRIVER_STRUCT *, OS_DRIVER_REQUEST *);
} OS_DRIVER;

#define OS_IP_SIZE              4               /* bytes in an IP address */
#define OS_NUM_SEED             2
#define OS_CRYPT_LEN            8               /* encryption system works in units of this size */
#define OS_AUTH_MAX_USERS       4                   /* maximum authenticated users allowed at a time */
#define OS_URL_LEN              100             /* length of a URL 100 */
#define OS_URI_LEN              (OS_URL_LEN/2)
#define OS_RECEIVE_SIZE         2048                /* size of the recieve buffer */
#define OS_OUT_BUFSZ            2048                /* size of output buffer */
#define OS_SSI_LINE             256                 /* maximum size of a SSI tag */

typedef struct OS_WS_SERVER
{
	INT                  ws_flags;
	struct OS_WS_SERVER  *ws_next;
	INT                  ws_bytes_in;
	INT                  ws_bytes_out;
	UINT8                ws_ip[OS_IP_SIZE];
	UINT16               ws_port;
	struct OS_WS_MASTER_AUTH
	{
		UINT32   ws_timeoutval;
		UINT32   ws_last_time;
		INT      ws_flags;
		struct OS_WS_AUTH
		{
			INT               ws_state;                           /* authentication state of this connection */
			UINT32            ws_countdown;                       /* countdown untill this structure is re-claimed */
			UINT8             ws_ip[OS_IP_SIZE];                  /* ip address of the client */
			CHAR              ws_salt[OS_NUM_SEED][OS_CRYPT_LEN]; /* sent to user to combine with user plaintext */
			struct OS_WS_AUTH *ws_next;                           /* linked list of structures */
		} ws_user_auth[OS_AUTH_MAX_USERS];
		CHAR  ws_key[OS_CRYPT_LEN + 1];
		INT   ws_auth_state;
		CHAR  ws_auth_uri[OS_URI_LEN];
		CHAR  ws_auth_public[OS_URI_LEN];
		INT   ws_auth_method;
	} ws_master;
} OS_WServer;

typedef struct _OS_WS_REQ_DATA
{
	CHAR ws_lbuf[OS_RECEIVE_SIZE + 2];     /* raw HTTP request from client is stored here */
	CHAR ws_out_head[OS_OUT_BUFSZ / 2];    /* space to store the response header for this request */
	CHAR ws_ssi_buf[OS_SSI_LINE];
	CHAR ws_obuf[OS_OUT_BUFSZ];            /* output buffer for WS_Write_To_Net() */
} OS_WS_REQ_DATA;

typedef struct OS_WS_REQUEST
{
	struct OS_WS_TOKEN_INFO
	{
		INT16 *ws_token_array;
		CHAR  *ws_token_string;
	} ws_pg_args;
	OS_WServer        *ws_server;          /* pointer to infor for this server */
	CHAR              *ws_headers;         /* Any header info the client may have sent */
	CHAR              *ws_fname;           /* URI (filename) of the requested entity GET,POST */
	CHAR              *ws_response;        /* the HTTP response to the current request */
	struct OS_WS_STAT *ws_stat;            /* internal stat structure */
	OS_WS_REQ_DATA    *ws_rdata;           /* per request allocated data */
	UINT8             ws_ip[OS_IP_SIZE];   /* ip address of client */
	INT               ws_nbytes;           /* number of bytes in input buffer */
	INT               ws_sd;               /* socket descripter for this connection */
	INT16             ws_method;           /* HTTP method of this request GET, POST, HEAD etc */
	UINT16            ws_obufcnt;
	INT               *ws_http_ver;
	INT               ws_first;
	CHAR              ws_user[33];         /* Name of authenticated user */
	CHAR              *ws_line;
	struct OS_HTTP_PLUGIN
	{
		CHAR            *ws_header;
		CHAR            *ws_data;
		INT32           ws_tsize;
		INT32           ws_free_buf_sz;
		INT             ws_header_size;
		INT             ws_header_set;
		INT             ws_no_pluginhead;
	} ws_hp;
}OS_REQUEST;

typedef struct _OS_WS_STAT
{
	CHAR  *ws_address;               /* address if incore file */
	INT(*plugin)(OS_REQUEST *);    /* triggers a call to this function */
	INT32           ws_size;
	INT             ws_flags;
} OS_WS_STAT;

/* Defines for objects creation */

#define TASK_INFO        1
#define QUEUE_INFO       2
#define SEMAPHORE_INFO   3
#define EVENT_GROUP_INFO 4
#define HISR_INFO        5
#define MAILBOX_INFO     6
#define TIMER_INFO       7

/* Structs for objects creation */

struct task_info
{
	U8 object_type;
	OS_TASK *task;
	CHAR *name;
	VOID(*task_entry) (UNSIGNED, VOID *);
	UNSIGNED argc;
	VOID *argv;
	UNSIGNED stack_size;
	OPTION priority;
	UNSIGNED time_slice;
	OPTION preempt;
};
struct queue_info
{
	U8 object_type;
	OS_QUEUE *queue;
	char *name;
	UNSIGNED queue_size;
	OPTION message_type;
	UNSIGNED message_size;
	OPTION suspend_type;
};
struct semaphore_info
{
	U8 object_type;
	OS_SEMAPHORE *semaphore;
	CHAR *name;
	UNSIGNED initial_count;
	OPTION suspend_type;
};
struct event_group_info
{
	U8 object_type;
	OS_EVENT_GROUP *event_group;
	CHAR *name;
};
struct HISR_info
{
	U8 object_type;
	OS_HISR *hisr;
	CHAR *name;
	VOID(*hisr_entry) (VOID);
	OPTION priority;
	UNSIGNED stack_size;
};
struct mailbox_info
{
	U8 object_type;
	OS_MAILBOX *mailbox;
	CHAR *name;
	OPTION suspend_type;
};
struct timer_info
{
	U8 object_type;
	OS_TIMER *timer;
	CHAR *name;
	VOID(*expiration_routine) (UNSIGNED);
	UNSIGNED id;
	UNSIGNED initial_time;
	UNSIGNED rescedule_time;
	OPTION enable;
};

/* TCP Networking */

/* host structure */
typedef struct OS_Host_Ent
{
	CHAR   *h_name;
	CHAR   **h_alias;        /* unused */
	S16    h_addrtype;
	S16    h_length;
	CHAR   **h_addr_list;        /* address, for backward compatibility */

#define   h_addr  h_addr_list[0]   /* address, for backward compatibility */

} OS_HOSTENT;

struct id_struct
{
	U8 is_ip_addrs[4];        /* IP address number */
};

struct addr_struct
{
	S16     family;            /* family = INTERNET */
	U16     port;              /* machine's port number */
	struct  id_struct id;      /* contains the 4-digit ip number for the host machine */
	char    *name;             /* points to machine's name */
};

struct sockaddr_struct
{
	struct  id_struct ip_num;     /* the address = the ip num */
	UINT16  port_num;             /* the process = the port num */
	INT16   pad;
};

/* Total number of socket descriptors. This should be
   TCP_MAX_PORTS + UDP_MAX_PORTS + IPR_MAX_PORTS
   Define NSOCKETS must match the definition in Net\target.h */
#define NSOCKETS                    100

   /* Defines added for the OS_Select service call.
	  Defines must match the definitions in Net\Inc\socketd.h */
#define FD_BITS                     32
#define FD_ELEMENTS                 (NSOCKETS/FD_BITS)+1

#define SCK_EVENT_Q_ELEMENT_SIZE    3       /* event queue element size
											   do not change the size */
#define SCK_EVENT_Q_NUM_ELEMENTS    100    /* number of elements in the
											  event queue */


//typedef struct os_fd_set  redefinition
//{
//	U32 words[FD_ELEMENTS];
//} FD_SET;

/* Definitions for subscriptions */
enum subscriber_type {
	NO_SUBSCRIPTION,
	SIGNAL,
	EVENT,
	MAILBOX,
	QUEUE,
	UPDATE,
	FUNCTION,
	FUNCTION_WITH_REF
};




union subscriber
{
	struct
	{
		OS_TASK *task;
		UNSIGNED signals;
	} signal;

	struct
	{
		OS_EVENT_GROUP *group;
		UNSIGNED events;
	} event;

	struct
	{
		OS_MAILBOX *mailbox;
		UNSIGNED reference;
	} mailbox;

	struct
	{
		OS_QUEUE *queue;
		UNSIGNED reference;
		UNSIGNED message_size;
	} queue;

	struct
	{
		void *pointer;
	} update;

	struct
	{
		STATUS(*Update)(varid_t VariableId,
			void* Message,
			U16 Length);
	} function;

	struct
	{
		UNSIGNED Ref1;
		UNSIGNED Ref2;
		STATUS(*Update)(varid_t VariableId,
			void* Message,
			U16 Length,
			UNSIGNED Ref1,
			UNSIGNED Ref2);
	} function_with_ref;
};


#define MESSAGETYPE_SUBSCRIBED_VARIABLE_IS_UPDATED 10

typedef
struct subscription_struct
{
	varid_t varid;
	enum subscriber_type type;
	union subscriber subscriber;
	struct subscription_struct *next;
} SUBSCRIPTION;

/*********************************************************************/
/*                                                                   */
/*  struct ModulInOut contains information about a variable in       */
/*  variable database used for input or outpur by application        */
/*  programs.                                                        */
/*                                                                   */
/*********************************************************************/
struct ModulInOut
{
	const char *Name;        /* Name of the variable. */
	void *DataAdr;           /* Points to a buffer with a local copy of
								the variable's value */
	const U8 DataAdrSize;    /* The size of the buffer which DataAdr
								points to. */
	varid_t Id;              /* Variable ID in the variable
								database. The value is set by the
								DoesVariablesExist() call */
};
/* All applications are started with a pointer to this struct
   application_arguments */
struct application_arguments
{
	OS_MEMORY_POOL Pool;
	varid_t RequestId;
	varid_t StateId;
};
#ifndef NUCL_OS //GSOAP
typedef char *__va_list[1];
#else
#include <stdio.h>
#endif
#include "OSDB.h"
/* include SW Watchdog structures */
#include "OS_WD.h"

// /* include defines for Nucleus FILE */
 #include <PCDISK.H>
/****************************************************************************
 *
 * definitions which file system is used
 *
 ***************************************************************************/

#define FW_FAT_USED 1
#define FW_SAFE_USED 1

#define INT_DRIVE_INCLUDED 1
#define EXT_DRIVE_INCLUDED 1
#define EXT_DRIVE_INDEX 1 /* Index for the external drive */
#define NUM_USERS               100    // Number of file users is set according to "MAXFILE" definition from HCC file system.
#define EMAXPATH                255     /* Maximum path length Change if you like */

#if (INT_DRIVE_INCLUDED==1)
#define INT_DRIVE_INDEX 0 /* Index for the internal drive */
#endif
#if (EXT_DRIVE_INCLUDED==1)&&(INT_DRIVE_INCLUDED==1)
#define EXT_DRIVE_INDEX 1 /* Index for the external drive */
#define MAX_DRIVE_INDEX 1 /* Maximum Index, ALWAYS 1 below number of drives */
#elif (EXT_DRIVE_INCLUDED==1)
#define EXT_DRIVE_INDEX 0 /* Index for the external drive */
#define MAX_DRIVE_INDEX 0 /* Maximum Index, ALWAYS 1 below number of drives */
#else
#define MAX_DRIVE_INDEX 0
#endif

#define ILL_DRIVE_INDEX MAX_DRIVE_INDEX+1 /* Illegal, for error checking */

 /* These #defines are used for initialization */
#define         RAM_DRIVE_NO        17
#define         RAM_DISK           "R:"
#if (INT_DRIVE_INCLUDED==1)
#define         INTERNAL_DRIVE_NO    8
#define         INTERNAL_DISK      "I:"
#endif/*INT_DRIVE*/
#if (EXT_DRIVE_INCLUDED==1)
#define         EXTERNAL_DRIVE_NO   23
#define         EXTERNAL_DISK      "X:"
#endif/*EXT_DRIVE*/

#define F_MAXPATH 256
#define FS_MAXPATH F_MAXPATH
#define FN_MAXPATH  F_MAXPATH


#ifndef HCC_UNICODE
#define F_LONGFILENAME 1 /*  0 - 8+3 names   1 - long file names   */
#define W_CHAR char
#else
#define F_LONGFILENAME 1 /* don't change it, because unicode version alvays uses longfile */
#define W_CHAR wchar
#endif

/* F_NAME structure definition */
#if (!F_LONGFILENAME)
typedef struct
{
	int drivenum; 				/*  drive number 0-A 1-B 2-C  */
	char path[FN_MAXPATH];		/*  pathnam  /directory1/dir2/   */
	char filename[F_MAXNAME];	/*  filename  */
	char fileext[F_MAXEXT];  	/*  extension  */
} F_NAME;
#else
#define F_MAXLNAME	256			/* maximum length of long filename */
typedef struct
{
	int drivenum; 				/*  drive number 0-A 1-B 2-C  */
	W_CHAR path[FN_MAXPATH];	/*  pathname /directory1/dir2/   */
	W_CHAR lname[F_MAXLNAME];	/*  long file name   */
} F_NAME;
#endif /*  F_LONGFILENAME   */

typedef struct
{
	unsigned long cluster;		/* which cluster is used */
	unsigned long prevcluster;	/* previous cluster for bad block handling */
	unsigned long sectorbegin;	/* calculated sector start */
	unsigned long sector;		/* current sector */
	unsigned long sectorend;	/* last saector position of the cluster */
	unsigned long pos;			/* current position */
} F_POS;

typedef struct {
	int drivenum;				/*  0-A 1-B 2-C  */
	W_CHAR path[FS_MAXPATH];		/*   /directory1/dir2/   */
	W_CHAR lname[FS_MAXPATH];		/*  filename  */
	unsigned short dirnum;		/*  0xffff-root other case in subdir n  */
} FS_NAME;

typedef struct {
	char filename[F_MAXPATH];	/* file name+ext */
	unsigned char attr;			/* attribute of the file/entry */

	unsigned short ctime;		/* creation time */
	unsigned short cdate;		/* creation date */

	unsigned long filesize;		/* length of file */

#if FW_SAFE_USED || FW_FAT_USED
	union {
#if FW_FAT_USED
		struct {
			F_NAME findfsname;		   	/* find properties */
			F_POS pos;
		} fat;
#endif
#if FW_SAFE_USED
		struct {
			FS_NAME findfsname;		   	/* find properties */
			unsigned short findpos;		/* find position */
		} safe;
#endif
	} common;
#endif
	int type;
} F_FIND;

/* File search structure */
//typedef struct
//{
	//CHAR       sfname[9];          /* Null terminated file and extension */
	//CHAR       fext[4];
	//CHAR       lfname[EMAXPATH + 1]; /* Null terminated long file name */
	//UINT8       fattribute;         /* File attributes */
	//UINT8       fcrcmsec;           /* File create centesimal mili second */
	//UINT16      fcrtime;            /* File create time */
	//UINT16      fcrdate;            /* File create date */
	//UINT16      faccdate;           /* Access date */
	//UINT16      fclusterhigh;       /* High cluster for data file */
	//UINT16      fuptime;            /* File update time */
	//UINT16      fupdate;            /* File update */
	//UINT16      fclusterlow;        /* Low cluster for data file */
	//UINT32      fsize;              /* File size */

	/* INTERNAL */
	//UINT8       pname[EMAXPATH + 1];  /* Pattern. */
	//UINT8       pext[4];
	//INT8        path[EMAXPATH + 1];
	//void       *pobj;              /* not used */
	//void       *pmom;              /* not used */

	/*HCC FILE SYSTEM*/
	//F_FIND      *find;

//} DSTAT;

/* User supplied parameter block for formatting */
//typedef struct fmtparms
//{
	//UINT8       partdisk;           /* 1 : Partitioned disk, 0 : Not paritioned disk */
	//UINT16      bytepsec;           /* Bytes per sectors */
	//UINT8       secpalloc;          /* Sectors per cluster */
	//UINT16      secreserved;        /* Reserved sectors before the FAT */
	//UINT8       numfats;            /* Number of FATS on the disk */
	//UINT16      numroot;            /* Maximum # of root dir entries. FAT32 always 0 */
	//UINT8       mediadesc;          /* Media descriptor byte */
	//UINT16      secptrk;            /* Sectors per track */
	//UINT16      numhead;            /* Number of heads */
	//UINT16      numcyl;             /* Number of cylinders */
	//UINT32      totalsec;           /* Total sectors */

	//INT8        oemname[9];             /* Only first 8 bytes are used */
	//UINT8       physical_drive_no;      /* Boot Drive Information */
										/* 80h BootDrive  00h NotBootDrive */
	//UINT32      binary_volume_label;    /* Volume ID or Serial Number */
	//INT8        text_volume_label[12];  /* Volume Label */

//} FMTPARMS;


#define ARDONLY     0x01        /* Read only fil attributes */
#define AHIDDEN     0x02        /* Hidden fil attributes */
#define ASYSTEM     0x04        /* System fil attributes */
#define AVOLUME     0x08        /* Volume Lable fil attributes */
#define ADIRENT     0x10        /* Dirrectory fil attributes */
#define ARCHIVE     0x20        /* Archives fil attributes */
#define ANORMAL     0x00        /* Normal fil attributes */

/* File creation permissions for open */
/* Note: OCTAL */
#define PS_IWRITE       0000400         /* Write permitted      */
#define PS_IREAD        0000200         /* Read permitted. (Always true anyway)*/

/* File access flags */
#define PO_RDONLY       0x0000          /* Open for read only*/
#define PO_WRONLY       0x0001          /* Open for write only*/
#define PO_RDWR         0x0002          /* Read/write access allowed.*/
#define PO_APPEND       0x0008          /* Seek to eof on each write*/
#define PO_CREAT        0x0100          /* Create the file if it does not exist.*/
#define PO_TRUNC        0x0200          /* Truncate the file if it already exists*/
#define PO_EXCL         0x0400          /* Fail if creating and already exists*/
#define PO_TEXT         0x4000          /* Ignored*/
#define PO_BINARY       0x8000          /* Ignored. All file access is binary*/
#define PO_NOSHAREANY   0x0004          /* Wants this open to fail if already
										   open.  Other opens will fail while
										   this open is active */
#define PO_NOSHAREWRITE 0x0800          /* Wants this opens to fail if already
										   open for write. Other open for
										   write calls will fail while this
										   open is active. */

										   /* Errno values */
#define PEBADF          9               /* Invalid file descriptor*/
#define PENOENT         2               /* File not found or path to file not found*/
#define PEMFILE         24              /* No file descriptors available (too many
										   files open)*/
#define PEEXIST         17              /* Exclusive access requested but file
										   already exists.*/
#define PEACCES         13              /* Attempt to open a read only file or a
										   special (directory)*/
#define PEINVAL         22              /* Seek to negative file pointer attempted.*/
#define PENOSPC         28              /* Write failed. Presumably because of no space */
#define PESHARE         30              /* Open failed do to sharing */

										   /* Arguments to SEEK */
#define PSEEK_SET       0               /* offset from begining of file*/
#define PSEEK_CUR       1               /* offset from current file pointer*/
#define PSEEK_END       2               /* offset from end of file*/



/* Arguments to po_extend_file */
#define PC_FIRST_FIT    1
#define PC_BEST_FIT     2
#define PC_WORST_FIT    3


/* Define service completion status constants.  */
/* Nucleus FILE status value */
#define     NUF_BAD_USER        -3000       /* Not a file user.                         */
#define     NUF_BADDRIVE        -3001       /* Bad drive number.                        */
#define     NUF_BADPARM         -3002       /* Invalid parametor given */
/* Disk */
#define     NUF_NOT_OPENED      -3003       /* The disk is not opened yet.               */
#define     NUF_NO_DISK         -3004       /* Disk is removed.                         */
#define     NUF_DISK_CHANGED    -3005       /* Disk is changed.                         */
#define     NUF_INVALID_CSIZE   -3006       /* The Disk has invalid clluster size.      */
#define     NUF_FATCORE         -3007       /* Fat cache table too small. */
#define     NUF_DEFECTIVEC      -3008       /* Defective cluster detected. */
#define     NUF_BADDISK         -3009       /* Bad Disk */
#define     NUF_NO_PARTITION    -3010       /* No partition in disk. */
#define     NUF_ROOT_FULL       -3011       /* Root directry full */
	/* Format */
#define     NUF_NOFAT           -3012       /* No FAT type in this partition. Can't Format */
#define     NUF_FMTCSIZE        -3013       /* Too many clusters for this partition. Can't Format */
#define     NUF_FMTFSIZE        -3014       /* File allocation table too small. Can't Format. */
#define     NUF_FMTRSIZE        -3015       /* Numroot must be an even multiple of 16  */
#define     NUF_FORMAT          -3016       /* Not formatted this disk. */
	/* Path */
#define     NUF_LONGPATH        -3017       /* Path or filename too long */
#define     NUF_INVNAME         -3018       /* Path or filename is invalid.  */
	/* File */
#define     NUF_PEMFILE         -3019       /* No file descriptors available (too many files open). */
#define     NUF_BADFILE         -3020       /* Invalid file descriptor */
#define     NUF_ACCES           -3021       /* Attempt to open a read only file or a special (directory). */
#define     NUF_NOSPC           -3022       /* Write failed. Presumably because of no space. */
#define     NUF_SHARE           -3023       /* The access conflict from multiple task to a specific file. */
#define     NUF_NOFILE          -3024       /* File not found or path to file not found. */
#define     NUF_EXIST           -3025       /* Exclusive access requested but file already exists. */
#define     NUF_NVALFP          -3026       /* Seek to negative file pointer attempted. */
#define     NUF_MAXFILE_SIZE    -3027       /* Over the maximum file size. */
#define     NUF_NOEMPTY         -3028       /* Directory is not empty.     */
#define     NUF_INVPARM         -3029       /* Invalid parameter is specified.  */
#define     NUF_INVPARCMB       -3030       /* Invalid parameter combination is specified.  */
	/* Memory  */
#define     NUF_NO_MEMORY       -3031       /* Can't allocate internal buffer. */
#define     NUF_NO_BLOCK        -3032       /* No block buffer available */
#define     NUF_NO_FINODE       -3033       /* No FINODE buffer available */
#define     NUF_NO_DROBJ        -3034       /* No DROBJ buffer available */
#define     NUF_IO_ERROR        -3035       /* Driver IO function routine returned error */

#define     NUF_INTERNAL        -3036       /* Nucleus FILE internal error */


/* IDE Driver Error code */
#define     NUF_IDE_ASSIGN              -3100      /* Logical drive assign error. */
#define     NUF_IDE_NUM_LOGICAL         -3101      /* NUM_LOGICAL_DRIVES set error. */
#define     NUF_IDE_NUM_PHYSICAL        -3102      /* NUM_PHYSICAL_DRIVES set error. */
#define     NUF_IDE_LOG_TABLE           -3103      /* LOG_DISK_TABLE setup error. */
#define     NUF_IDE_PHYS_TALBE          -3104      /* PHYS_DISK_TABLE setup error. */
#define     NUF_IDE_INITIALIZE          -3105      /* Initialize error. See c_s[].err_code */
#define     NUF_IDE_NOT_SETCOUNT        -3106      /* Read/Write sector count is zero. */
#define     NUF_IDE_NOT_LOG_OPENED      -3107      /* Logical drive is not opened. */
#define     NUF_IDE_NOT_PHYS_OPENED     -3108      /* Physical drive is not opened. */
#define     NUF_IDE_DISK_SIZE           -3109      /* illegal partition size. */
#define     NUF_IDE_FAT_TYPE            -3110      /* illegal FAT type. */
#define     NUF_IDE_NO_DOSPART          -3111      /* NO DOS partition in disk. */
#define     NUF_IDE_NO_EXTPART          -3112      /* NO Extension partition in disk. */
#define     NUF_IDE_NOT_CAPACITY        -3113      /* Partition capacity error. */
#define     NUF_IDE_OVER_PART           -3114      /* Over the partition end sectors. */
#define     NUF_IDE_MAX_BLOCKS          -3115      /* More than max blocks access. */
#define     NUF_IDE_RESET               -3116      /* Controller reset failed in initialize. */
#define     NUF_IDE_DIAG_FAILED         -3117      /* Drive diagnostic failed in initialize. */
#define     NUF_IDE_SETMULTIPLE         -3118      /* Set multiple mode command failed. */
#define     NUF_IDE_INITPARMS           -3119      /* initialize parmaters failed in initialize */
#define     NUF_IDE_NOT_READY           -3120      /* Drive not ready. */
#define     NUF_IDE_CMDERROR            -3121      /* IDE command error. See error register. */
#define     NUF_IDE_BUSERROR            -3122      /* DRQ should be asserted but it isn't. */
#define     NUF_IDE_EVENT_TIMEOUT       -3123      /* Event timeout. */




/* include comm. manager structures */
#include "com_mgr_defs.h"

#define API_VERSION_MAJOR 4
#define API_VERSION_MINOR 22

#define vector_version(version) U16 APIVersionMajor, APIVersionMinor;

typedef struct OS_Services
{
	vector_version(API_VERSION_MAJOR + API_VERSION_MINOR)
} OS_Services_T;

extern OS_Services_T *OS_SERVICES;

/* Re-map structure to function names */
/* Include OS functions from vector.dff */
//#include "vector.dff"

#include "OS4x00.h"

#endif