/************************************************************************
*
*       Copyright (c) 2000 by Accelerated Technology, Inc.
*
*  PROPRIETARY RIGHTS of Accelerated Technology are  involved in
*  the subject matter of this material.  All manufacturing,
*  reproduction, use, and sales rights pertaining to this subject
*  matter are  governed by the license agreement.  The recipient of
*     this software implicitly accepts the terms of the license.
*
*
*************************************************************************
*************************************************************************
* FILE NAME                                     VERSION
*
*       PCDISK.H                            FILE/SA1110/ADS  2.1.1
*
* COMPONENT
*
*       Nucleus File
*
* DESCRIPTION
*
*       This file contains Nucleus File2 constants common to both the
*       application and the actual Nucleus File components.  This file
*       also contains data structure definitions that hide internal
*       information from the application.
*
* DATA STRUCTURES
*
*       FATSWAP                             Fat blocks structure.
*       DDRIVE                              Block 0 image.
*       DOSINODE                            Dos Directory Entry.
*       BLKBUFF                             Block buffer.
*       LNAMINFO                            Long file name information.
*       LNAMENT                             Long file name Directory
*                                            Entry.
*       FINODE                              DOS entry.
*       DIRBLK                              Directory information.
*       DROBJ                               Object used to find a dirent
*                                            on a disk and its parent's.
*       DATESTR                             Date stamping buffer.
*       PC_FILE                             Internal file representation.
*       DSTAT                               File search structure.
*       FMTPARMS                            Format parameter blcok.
*       pcblk0                              Block 0. Not use.
*       FILE_SYSTEM_USER                    File system user structure.
*       _PC_BDEVSW                          Device driver dispatch table.
*       _NUF_FSTBL                          File system dispatch table.
*       PTABLE_ENTRY                        Partition table descriptions.
*       PTABLE                              Boot Record structure.
*
* FUNCTIONS
*
*       None.
*
* DEPENDENCIES
*
*       nucleus.h                           System definitions
*
*************************************************************************/

#ifndef __PCDISK__
#define __PCDISK__ 1

#define DBG_LINE_MARK

#define INT_DRIVE_INCLUDED 1

#define         RAM_DRIVE_NO        17
#define         RAM_DISK           "R:"
#if (INT_DRIVE_INCLUDED==1)
#define         INTERNAL_DRIVE_NO    8
#define         INTERNAL_DISK      "I:"
#endif /*INT_DRIVE*/

#define EXT_DRIVE_INCLUDED 1
#if (EXT_DRIVE_INCLUDED==1)
#define         EXTERNAL_DRIVE_NO   23
#define         EXTERNAL_DISK      "X:"
#endif /*EXT_DRIVE*/

//#define FAR
//#define NEAR

#define NDRIVES                 26
#define NUM_USERS               100    // Number of file users is set according to "MAXFILE" definition from HCC file system.
#define LOCK_METHOD             2
#define EMAXPATH                255

typedef int WAIT_HANDLE_TYPE;

typedef struct lockobj
{
   WAIT_HANDLE_TYPE  wait_handle;
   INT16             opencount;
   INT               exclusive;
} LOCKOBJ;


#define ARDONLY     0x01        /* Read only fil attributes */
#define AHIDDEN     0x02        /* Hidden fil attributes */
#define ASYSTEM     0x04        /* System fil attributes */
#define AVOLUME     0x08        /* Volume Lable fil attributes */
#define ADIRENT     0x10        /* Dirrectory fil attributes */
#define ARCHIVE     0x20        /* Archives fil attributes */
#define ANORMAL     0x00        /* Normal fil attributes */


/* Structure used to track cached fat blocks */
typedef struct fatswap
{
   UINT32      n_to_swap;           /* Next to swap. For implementing round robin */
   UINT32      base_block;          /* base_block of FAT sector index in data_map */
   /* These two counters track cache usage as we fill it. Eventually the
      FAT fills and we go into swapping mode at steady state */
   UINT16      n_blocks_used;       /* How many blocks in the cache have we used */
   UINT16      n_blocks_total;      /* How many blocks are available in the cache */

   UINT8       *pdirty;             /* BIT-map of blocks needing flushing */
   INT         block_0_is_valid;    /* If YES then data_map[0] contains the offset
                                       of the first block of the FAT */
   INT         data_map_size;       /* data_map table size */
   UINT16      *data_map;           /* Table that maps block numbers in the fat to
                                       block offsets in our data array. zero means
                                       the block is not mapped. Except.. data_map[0]
                                       contains block zero of the FAT which
                                       is at location 0 in the data array */
   UINT8 FAR   *data_array;         /* Block buffer area on Intel systems always FAR */
} FATSWAP;


/* Structure to contain block 0 image from the disk */
typedef struct ddrive
{
    UINT32      fs_type;            /* FAT_FILE_SYSTEM */
    INT16       opencount;          /* Drive open count */
    UINT16      bytespcluster;      /* Bytes per cluster */
    UINT32      byte_into_cl_mask;  /* And this with file pointer to get the
                                       byte offset into the cluster */
    UINT16      fasize;             /* Nibbles per fat entry. (2 or 4) */
    UINT32      rootblock;          /* First block of root dir */
    UINT32      firstclblock;       /* First block of cluster area */
    UINT16      driveno;            /* Driveno. Set when open succeeds */
    UINT32      maxfindex;          /* Last element in the fat */
    UINT16      secproot;           /* blocks in root dir */
    INT         fat_is_dirty;       /* FAT update flag */
    INT         use_fatbuf;         /* Use FAT buffer flag */
    FATSWAP     fat_swap_structure; /* Fat swap structure if swapping */
    UINT16      log2_secpalloc;     /* Log of sectors per cluster */
    UINT32      maxfsize_cluster;   /* Maximum file cluster size */
    UINT16      valid_fsinfo;       /* fsinfo valid  flag */
          /******** BPB  ***********/
    INT8        oemname[8];         /* 0x03 OEM name */
    UINT16      bytspsector;        /* 0x0b Must be 512 for this implementation */
    UINT8       secpalloc;          /* 0x0d Sectors per cluster */
    UINT16      fatblock;           /* 0x0e Reserved sectors before the FAT */
    UINT8       numfats;            /* 0x10 Number of FATS on the disk */
    UINT16      numroot;            /* 0x11 Maximum # of root dir entries */
    UINT32      numsecs;            /* 0x13 Total # sectors on the disk */
    UINT8       mediadesc;          /* 0x15 Media descriptor byte */
    UINT32      secpfat;            /* 0x16 Size of each fat */
    UINT16      secptrk;            /* 0x18 sectors per track */
    UINT16      numhead;            /* 0x1a number of heads */
    UINT32      numhide;            /* 0x1c # hidden sectors */
    UINT32      bignumsecs;         /* 0x20 Sectors per FAT32 */
 /* FAT16/12 */
    UINT8       phys_num;           /* 0x24 physical drive number */
    UINT8       xtbootsig;          /* 0x26 extend boot recored signature */
    UINT32      volid;              /* 0x27 or 0x43 (FAT32) volume serial number */
    UINT8       vollabel[11];       /* 0x2b or 0x47 (FAT32) volueme_label */
 /* FAT32 */
    UINT32      bigsecpfat;         /* 0x24 Size of each FAT on the FAT32 */
    UINT16      fat_flag;           /* 0x28 FAT flag */
    UINT16      file_version;       /* 0x2a file system version */
    UINT32      rootdirstartcl;     /* 0x2c root cluster */
    UINT16      fsinfo;             /* 0x30 fsinfo block */
    UINT16      bpb_backup;         /* 0x32 BPB backup */
 /* FAT32 FSINFO */
    UINT32      free_clusters_count; /* If non-zero pc_free may use this value */
    UINT32      free_contig_pointer; /* Efficiently stored */

} DDRIVE;


/* Block buffer */
typedef struct blkbuff
{
    struct      blkbuff *pnext;     /* Next block buffer pointer */
    UINT32      lru;                /* Last recently used stuff */
    INT16       locked;             /* Reserve */
    DDRIVE      *pdrive;            /* Drive block 0 image */
    UINT32      blockno;            /* I/O block number */
    INT16       use_count;          /* use count */
    INT         io_pending;         /* I/O pending flag */
    UINT8       data[512];          /* I/O data buffer */

} BLKBUFF;


/* Long file name information */
typedef struct lnaminfo
{
    BLKBUFF     *lnamblk1;          /* Long file name block buffer 1    */
    BLKBUFF     *lnamblk2;          /* Long file name block buffer 2    */
    BLKBUFF     *lnamblk3;          /* Long file name block buffer 3    */
    INT16       lnam_index;         /* Long file name start index       */
    INT16       lnament;            /* Number of long file name entries */
    UINT8       lnamchk;            /* Check value of short file name   */

} LNAMINFO;


/* Internal representation of DOS entry */
typedef struct finode
{
    UINT8       fname[8];           /* File name */
    UINT8       fext[3];            /* File extension */
    UINT8       fattribute;         /* File attributes */
    UINT8       reserve;            /* Reserved */
    UINT8       fcrcmsec;           /* File create centesimal mili second */
    UINT16      fcrtime;            /* File create time */
    UINT16      fcrdate;            /* File create date */
    UINT16      faccdate;           /* Access date */
    UINT16      fuptime;            /* File update time */
    UINT16      fupdate;            /* File update */
    UINT32      fcluster;           /* Cluster for data file */
    UINT32      fsize;              /* File size */
    UINT32      alloced_size;       /* Size rounded up to the hearest cluster
                       (only maintained for files */
    INT16   opencount;

/* If the finode is an open file the following flags control the sharing.
   they are maintained by NU_Open                                      */
#ifdef OF_WRITE
#undef OF_WRITE
#endif
#define OF_WRITE            0x01    /* File is open for write by someone */
#define OF_WRITEEXCLUSIVE   0x02    /* File is open for write by someone
                                       they wish exclusive write access */
#define OF_EXCLUSIVE        0x04    /* File is open with exclusive access not
                                       sharing write or read */
    INT16       openflags;          /* For Files. Track how files have it open */
    DDRIVE      *my_drive;          /* Block 0 image from this disk */
    UINT32      my_block;           /* Number of this file directory entry block */
    INT16       my_index;           /* Directory entry index */
#if (LOCK_METHOD == 2)
    LOCKOBJ     lock_object;        /* for locking during critical sections */
#endif
    struct finode *pnext;           /* Next DOS entry pointer */
    struct finode *pprev;           /* Prevenience DOS entry pointer */
    UINT16      abs_length;         /* Absolute path length */

} FINODE;


/* contain location information for a directory */
typedef struct dirblk
{
    UINT32      my_frstblock;       /* First block in this directory */
    UINT32      my_block;           /* Current block number */
    UINT16      my_index;           /* dirent number in my cluster   */
    /* fname[0] == "\0" entry blocks and index */
    UINT32      end_block;          /* End block number in this directory entry */
    UINT16      end_index;          /* End directory entry number in my cluster */

} DIRBLK;


typedef struct drobj
{
    DDRIVE      *pdrive;            /* Block 0 image from the disk */
    FINODE      *finode;            /* Dos entry */
    DIRBLK      blkinfo;            /* Directory information */
    INT         isroot;             /* True if this is the root */
    BLKBUFF     *pblkbuff;          /* Block buffer pointer */
    LNAMINFO    linfo;              /* for long file name */

} DROBJ;


/* File search structure */
typedef struct dstat
{
    CHAR       sfname[9];          /* Null terminated file and extension */
    CHAR       fext[4];
    CHAR       lfname[EMAXPATH+1]; /* Null terminated long file name */
    UINT8       fattribute;         /* File attributes */
    UINT8       fcrcmsec;           /* File create centesimal mili second */
    UINT16      fcrtime;            /* File create time */
    UINT16      fcrdate;            /* File create date */
    UINT16      faccdate;           /* Access date */
    UINT16      fclusterhigh;       /* High cluster for data file */
    UINT16      fuptime;            /* File update time */
    UINT16      fupdate;            /* File update */
    UINT16      fclusterlow;        /* Low cluster for data file */
    UINT32      fsize;              /* File size */

    /* INTERNAL */
    UINT8       pname[EMAXPATH+1];  /* Pattern. */
    UINT8       pext[4];
    INT8        path[EMAXPATH+1];
    DROBJ       *pobj;              /* Info for getting at the inode */
    DROBJ       *pmom;              /* Info for getting at parent inode */

} DSTAT;


/* User supplied parameter block for formatting */
typedef struct fmtparms
{
   UINT8    partdisk;               /* 1 : Partitioned disk, 0 : Not paritioned disk */
   UINT16   bytepsec;               /* Bytes per sectors */
   UINT8    secpalloc;              /* Sectors per cluster */
   UINT16   secreserved;            /* Reserved sectors before the FAT */
   UINT8    numfats;                /* Number of FATS on the disk */
   UINT16   numroot;                /* Maximum # of root dir entries. FAT32 always 0 */
   UINT8    mediadesc;              /* Media descriptor byte */
   UINT16   secptrk;                /* Sectors per track */
   UINT16   numhead;                /* Number of heads */
   UINT16   numcyl;                 /* Number of cylinders */
   UINT32   totalsec;               /* Total sectors */
   INT8     oemname[9];             /* Only first 8 bytes are used */
   UINT8    physical_drive_no;      /* Boot Drive Information */
   UINT32   binary_volume_label;    /* Volume ID or Serial Number */
   INT8     text_volume_label[12];  /* Volume Label */
} FMTPARMS;

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

/* Define service completion status constants.  */
/* Nucleus FILE status value */
#define     OS_FILE_BAD_USER        -3000       /* Not a file user.                         */
#define     OS_FILE_BADDRIVE        -3001       /* Bad drive number.                        */
#define     OS_FILE_BADPARM         -3002       /* Invalid parametor given */
/* Disk */
#define     OS_FILE_NOT_OPENED      -3003       /* The disk is not opened yet.               */
#define     OS_FILE_NO_DISK         -3004       /* Disk is removed.                         */
#define     OS_FILE_DISK_CHANGED    -3005       /* Disk is changed.                         */
#define     OS_FILE_INVALID_CSIZE   -3006       /* The Disk has invalid clluster size.      */
#define     OS_FILE_FATCORE         -3007       /* Fat cache table too small. */
#define     OS_FILE_DEFECTIVEC      -3008       /* Defective cluster detected. */
#define     OS_FILE_BADDISK         -3009       /* Bad Disk */
#define     OS_FILE_NO_PARTITION    -3010       /* No partition in disk. */
#define     OS_FILE_ROOT_FULL       -3011       /* Root directry full */
    /* Format */
#define     OS_FILE_NOFAT           -3012       /* No FAT type in this partition. Can't Format */
#define     OS_FILE_FMTCSIZE        -3013       /* Too many clusters for this partition. Can't Format */
#define     OS_FILE_FMTFSIZE        -3014       /* File allocation table too small. Can't Format. */
#define     OS_FILE_FMTRSIZE        -3015       /* Numroot must be an even multiple of 16  */
#define     OS_FILE_FORMAT          -3016       /* Not formatted this disk. */
    /* Path */
#define     OS_FILE_LONGPATH        -3017       /* Path or filename too long */
#define     OS_FILE_INVNAME         -3018       /* Path or filename is invalid.  */
    /* File */
#define     OS_FILE_PEMFILE         -3019       /* No file descriptors available (too many files open). */
#define     OS_FILE_BADFILE         -3020       /* Invalid file descriptor */
#define     OS_FILE_ACCESS          -3021       /* Attempt to open a read only file or a special (directory). */
#define     OS_FILE_NOSPC           -3022       /* Write failed. Presumably because of no space. */
#define     OS_FILE_SHARE           -3023       /* The access conflict from multiple task to a specific file. */
#define     OS_FILE_NOFILE          -3024       /* File not found or path to file not found. */
#define     OS_FILE_EXIST           -3025       /* Exclusive access requested but file already exists. */
#define     OS_FILE_NVALFP          -3026       /* Seek to negative file pointer attempted. */
#define     OS_FILE_MAXFILE_SIZE    -3027       /* Over the maximum file size. */
#define     OS_FILE_NOEMPTY         -3028       /* Directory is not empty.     */
#define     OS_FILE_INVPARM         -3029       /* Invalid parameter is specified.  */
#define     OS_FILE_INVPARCMB       -3030       /* Invalid parameter combination is specified.  */
    /* Memory  */
#define     OS_FILE_NO_MEMORY       -3031       /* Can't allocate internal buffer. */
#define     OS_FILE_NO_BLOCK        -3032       /* No block buffer available */
#define     OS_FILE_NO_FINODE       -3033       /* No FINODE buffer available */
#define     OS_FILE_NO_DROBJ        -3034       /* No DROBJ buffer available */
#define     OS_FILE_IO_ERROR        -3035       /* Driver IO function routine returned error */

#define     OS_FILE_INTERNAL        -3036       /* Nucleus FILE internal error */


/* IDE Driver Error code */
#define     OS_FILE_IDE_ASSIGN              -3100      /* Logical drive assign error. */
#define     OS_FILE_IDE_NUM_LOGICAL         -3101      /* NUM_LOGICAL_DRIVES set error. */
#define     OS_FILE_IDE_NUM_PHYSICAL        -3102      /* NUM_PHYSICAL_DRIVES set error. */
#define     OS_FILE_IDE_LOG_TABLE           -3103      /* LOG_DISK_TABLE setup error. */
#define     OS_FILE_IDE_PHYS_TALBE          -3104      /* PHYS_DISK_TABLE setup error. */
#define     OS_FILE_IDE_INITIALIZE          -3105      /* Initialize error. See c_s[].err_code */
#define     OS_FILE_IDE_NOT_SETCOUNT        -3106      /* Read/Write sector count is zero. */
#define     OS_FILE_IDE_NOT_LOG_OPENED      -3107      /* Logical drive is not opened. */
#define     OS_FILE_IDE_NOT_PHYS_OPENED     -3108      /* Physical drive is not opened. */
#define     OS_FILE_IDE_DISK_SIZE           -3109      /* illegal partition size. */
#define     OS_FILE_IDE_FAT_TYPE            -3110      /* illegal FAT type. */
#define     OS_FILE_IDE_NO_DOSPART          -3111      /* NO DOS partition in disk. */
#define     OS_FILE_IDE_NO_EXTPART          -3112      /* NO Extension partition in disk. */
#define     OS_FILE_IDE_NOT_CAPACITY        -3113      /* Partition capacity error. */
#define     OS_FILE_IDE_OVER_PART           -3114      /* Over the partition end sectors. */
#define     OS_FILE_IDE_MAX_BLOCKS          -3115      /* More than max blocks access. */
#define     OS_FILE_IDE_RESET               -3116      /* Controller reset failed in initialize. */
#define     OS_FILE_IDE_DIAG_FAILED         -3117      /* Drive diagnostic failed in initialize. */
#define     OS_FILE_IDE_SETMULTIPLE         -3118      /* Set multiple mode command failed. */
#define     OS_FILE_IDE_INITPARMS           -3119      /* initialize parmaters failed in initialize */
#define     OS_FILE_IDE_NOT_READY           -3120      /* Drive not ready. */
#define     OS_FILE_IDE_CMDERROR            -3121      /* IDE command error. See error register. */
#define     OS_FILE_IDE_BUSERROR            -3122      /* DRQ should be asserted but it isn't. */
#define     OS_FILE_IDE_EVENT_TIMEOUT       -3123      /* Event timeout. */


#endif   /* __PCDISK__ */
