//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2011 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:5.2.2$                                                       
// $PEPTOOL file version:101$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date$                                                  
// $Author$                                                           
// $RCSfile$                                                          
// $Revision$                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
/*********************************************************************/
/*                                                                   */
/*            Copyright (c) 2002 Mita-Teknik a/s                     */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/* FILE NAME         OSDB.h                              VERSION 2   */
/*                                                                   */
/* COMPONENT                                                         */
/*                                                                   */
/*                                                                   */
/* DESCRIPTION       Variable database header file                   */
/*                                                                   */
/* AUTHOR            Mita-teknik A/S                                 */
/*                                                                   */
/* DATA STRUCTURES                                                   */
/*                                                                   */
/* FUNCTIONS                                                         */
/*                                                                   */
/* DEPENDENCIES                                                      */
/*                                                                   */
/* HISTORY                                                           */
/* NAME DATE       REMARKS                                           */
/* ------------------------------------------------------------------*/
/* FKL  2002-10-03 Definition of database structures                 */
/* FKL  2002-10-14 Inserted defines for initiation values            */
/* FKL  2002-10-15 Inserted field for total log id in common part.   */
/*                 Inserted new field for parameters DefaultValue    */
/*                 in order to save the default value.               */
/*                 Inserted new field in output parameters. ObjectID */
/*                 used to limit update access after locking.        */
/* FKL  2002-11-04 Changed spelling for subscription                 */
/* FKL  2002-11-11 Inserted new structure os_db_alias in order to    */
/*                 assign more than one name to a variable. Inserted */
/*                 new field to first alias in os_db_common_fields.  */
/* FKL  2002-11-19 Removed VarID field from alias struct.            */
/* FKL  2002-12-10 Inserted ChangeFlag field in backed up variables. */
/*                                                                   */
/*********************************************************************/
#ifndef __OSDB_H__
#define __OSDB_H__

#include "types.h"
#include "unit.h"

/* The length of automatic generated parameter names */
#define PARAMETER_NAME_LENGTH 48

/* Define flags for log */
#define NOLOG_ENABLE                    0x00000000
#define TOTLOG_ENABLE                   0x00000001
#define FIVEMINLOG_ENABLE               0x00000002

/* Define types of the init
   arguments for variable creation
*/
#define ARG0 char*
#define ARG1 time_t
#define ARG2 scaletype_t
#define ARG3 scalevalue_t
#define ARG4 unit_t

/* For version 2 of the variable database */
enum update {
   LOCAL,                /* For normal local variables */
   PARAMETER,            /* For parameters */
   OUTPUT_PARAMETER,     /* For output data to wpline modules */
   BIT_INPUT,            /* For bit oriented input data from wpline modules */
   COUNTABLE_INPUT,      /* For countable oriented input data from wpline modules */
   NON_COUNTABLE_INPUT,  /* For non countable oriented input data from wpline modules */
   BIT_OUTPUT,           /* For bit oriented output data for wpline modules */
   COUNTABLE_OUTPUT,     /* For countable oriented output data for wpline modules */
   NON_COUNTABLE_OUTPUT, /* For non countable oriented output data for wpline modules */
   SYSTEM_RO,            /* For parameters from the protected part of the
                            EEPROM or from the bootloader in RAM. These cannot be
                            changed. */
   SYSTEM,               /* For system parameters stored in EEPROM. */
   TIMER,                /* For local variables incremented regularly by
                            timers. They cannot be updated */
   SUMMATION,            /* For summation variables */
   BACKUP,               /* For backup variables */
   AVAILABILITY          /* For availability variables */
};


struct subscription_struct;  /* forward declarations */

/* Fields stored in the variable database for all variables. All fields
   except the Value are constants which cannot be changed once a variable
   is created, but some of the fields are pointers to parameters whose
   Value also may be changed. */
typedef struct os_db_common_fields
{
   /* The following fields must be initialised by a caller who wants to
      create a new variable. */

   U32 MagicNumber;        /* A magic number to be checked before every operation
                              to a variable in order to detect validity of data */
   U32 HashValue;          /* A hash value calculated from the name */
   varid_t NextName;       /* A pointer to the next variable with the same hash table
                              index, or NULL if it the last. */
   const char *Name;       /* Name of the variable as a NULL-terminated UTF-8 string. */

   type_t Type;            /* Type of the variable. */
   access_t AccessRead;    /* Minimum access level to read the value and
                              other information about the variable. */

   access_t AccessWrite;   /* Minimum access level to update the value. */

   scaletype_t ScaleType;  /* How the scale the value before showing it in a display. The
                              possibities are:
                              - SCALE_NONE: Don't scale,
                              - SCALE_DIV: Divide by the scale value,
                              - SCALE_MUL: Multiply by the scale value,
                              - SCALE_EXPMUL: Multiply by 10 raised to the power of the
                              scale value,
                              - SCALE_EXPDIV: Divide by 10 raised to the power of the
                              scale value. */

   scalevalue_t ScaleValue; /* The display scale value. For strings the maximal string
                             * length. */

   unit_t Unit;             /* Code for the unit of the value sent to displays. */

   precision_t Precision;  /* Number of decimals in display after scaling. If the
                              precision is negative, the integer part of the value will
                              be rounded so the indicated number of least significant
                              digits will be zero. For strings the minimal string
                              length. */

   value_t Value;           /* (Initial) value. */

   /* The following fields may not be initialised by a caller who wants
      to create a new a variable. They will be overwritten */

   time_t TimeStamp;        /* The time of the latest update of the value. This field must
                               placed be immediately after the Value field, because the
                               value and the time stamp are updated together in one atomic
                               STM (STore Multiple) instruction on the ARM processor. */

   scaletype_t DisplayScaleType;
   scalevalue_t DisplayScaleValue;
   unit_t DisplayUnit;
   precision_t DisplayPrecision;


   enum update Update;                           /* The update type of this variable. */

   struct subscription_struct* FirstSubscriber;  /* A pointer to the subscription control block of the first
                                                    subscriber to this variable, or NULL if nobody subscribs
                                                    it. */

   struct os_db_variable* PreviousVariable;      /* A pointer to the previous variable, or NULL if it the first. */

   struct os_db_variable* NextVariable;          /* A pointer to the next variable, or NULL if it the last. */


   S32 ActiveReaders;                            /* The numbers of readers reading the value at any time. This
                                                  * field is only used if the TYP_LNG bit is set in Type. */

   S32 OldValueBeingRead;                        /* A Boolean variable. FALSE if we are sure that no readers
                                                  * are still reading an old value which have been replaced by
                                                  * a new value, and otherwise TRUE. This field is only used if
                                                  * the TYP_LNG bit is set in Type. */

   U16 TotalLogID;                               /* An ID used when the this variable is registered to the
                                                    total log.
                                                 */

   U16 FiveMinLogID;                             /* An ID used when the this variable is registered to the
                                                    five minutes log.
                                                 */
}os_db_common;


struct os_db_sublocal
{
   struct os_db_parameter* LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */
   value_t Minimum;
   value_t Maximum;
   /* Minimum and Maximum indicates the range of valid value for
    * the parameter. They may, however, be overwritten by setting
    * the NoLimits variable. */
   struct value_lists *Lists;
   /* Lists can point to a table with all allowed values. */

};

struct os_db_subparameter
{
   char* FileID;
   /* A pointer to a file identification for
      the file this parameter should be saved in.
   */
   value_t Minimum;
   value_t Maximum;
   /* Minimum and Maximum indicates the range of valid value for
    * the parameter. They may, however, be overwritten by setting
    * the NoLimits variable. */
   struct value_lists *Lists;
   /* Lists can point to a table with all allowed values. */
   value_t DefaultValue;
   /* Save of the default value */
   U8 ChangeFlag;
   /* Flag to indicate if value has been changed */
};
struct os_db_wpline
{
   /* A hash value calulated from the ModuleAddress
      and DataIdent of the variable */
   U32 HashValue;
   /* A pointer to the next variable with the same hash table
      index, or NULL if it the last. */
   struct osdb_iovariable* NextAddress;

   U32 ModuleAddress;
   /*
     An IP like address for the module on the bus
   */
   U32 DataIdent;
   /*
     A full id of the data in the module (CAN ID)
     DataID 16 LSB, SubID bit 16 - 20
   */
};

struct os_db_suboutputparameter
{
   char* FileID;
   /* A pointer to a file identification for
      the file this parameter should be saved in.
   */
   value_t Minimum;
   value_t Maximum;
   /* Minimum and Maximum indicates the range of valid value for
    * the parameter. They may, however, be overwritten by setting
    * the NoLimits variable. */
   struct value_lists *Lists;
   /* Lists can point to a table with all allowed values. */
   value_t DefaultValue;
   /* Save of the default value */
   S32 Locked;
   /* Lockflag for the menu. If this flag is true,
      the menu is not able to changed the value
      any longer and changes is not saved to file!
   */
   U32 ObjectID;
   /* An object ID. The owner of this ID may update
      this variable after it has been locked.
   */
   U8 ChangeFlag;
   /* Flag to indicate if value has been changed */

};

struct os_db_subbitinput
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */

   struct os_db_output_parameter* Enable;
   /*
     A pointer to an enable output parameter
   */
   struct os_db_output_parameter* Subscription;
   /*
     A pointer to a subsribtion output parameter
   */
   struct os_db_output_parameter* ChangeMask;
   /*
     A pointer to a change mask output parameter
   */
   struct os_db_output_parameter* Holdtime;
   /*
     A pointer to a holdtime output parameter
   */
   struct os_db_output_parameter* Invert;
   /*
     A pointer to an invert output parameter
   */
};

struct os_db_subcountableinput
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */
   struct os_db_output_parameter* Enable;
   /*
     A pointer to an enable output parameter
   */
   struct os_db_output_parameter* Subscription;
   /*
     A pointer to a subsribtion output parameter
   */
   struct os_db_output_parameter* Threshold;
   /*
     A pointer to a change mask output parameter
   */
   struct os_db_output_parameter* Holdtime;
   /*
     A pointer to a threshold output parameter
   */
   struct os_db_output_parameter* Offset;
   /*
     A pointer to an offset output parameter
   */
   struct os_db_output_parameter* Scale;
   /*
     A pointer to an scale output parameter
   */
};

struct os_db_subnoncountableinput
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */
   struct os_db_output_parameter* Enable;
   /*
     A pointer to an enable output parameter
   */
   struct os_db_output_parameter* Subscription;
   /*
     A pointer to a subsribtion output parameter
   */
};

struct os_db_subbitoutput
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */

   struct os_db_output_parameter* Enable;
   /*
     A pointer to an enable output parameter
   */
};

struct os_db_subcountableoutput
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */
   struct os_db_output_parameter* Enable;
   /*
     A pointer to an enable output parameter
   */
   struct os_db_output_parameter* Offset;
   /*
     A pointer to an offset output parameter
   */
   struct os_db_output_parameter* Scale;
   /*
     A pointer to an scale output parameter
   */
};

struct os_db_subnoncountableoutput
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */
   struct os_db_output_parameter* Enable;
   /*
     A pointer to an enable output parameter
   */
};

struct os_db_subsystemro
{
   U32 PROMReference;
   /*
     An address for this variable in the EEPROM.
   */
};

struct os_db_subsystem
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */
   U32 PROMReference;
   /*
     An address for this variable in the EEPROM.
   */
   value_t Minimum;
   value_t Maximum;
   /* Minimum and Maximum indicates the range of valid value for
    * the parameter. They may, however, be overwritten by setting
    * the NoLimits variable. */
   struct value_lists *Lists;
   /* Lists can point to a table with all allowed values. */
   value_t DefaultValue;
   /* Save of the default value */

};

struct os_db_subsummation
{
   char* FileID;
   /* A pointer to a file identification for
      the file this parameter should be saved in.
   */
   U8 ChangeFlag;
   /* Flag to indicate if value has been changed */

   char* FirstVariable;
   /* A pointer to a variable name.*/
   char* SecondVariable;
   /* A pointer to a variable name.*/
   char* ThirdVariable;
   /* A pointer to a variable name.*/
   char* FourthVariable;
   /* A pointer to a variable name.*/

};

struct os_db_subavailability
{
   char* FileID;
   /* A pointer to a file identification for
      the file this parameter should be saved in.
   */
   U8 ChangeFlag;
   /* Flag to indicate if value has been changed */
};

struct os_db_subbackup
{
   struct os_db_parameter *LogFlags;
   /* A pointer to a logflag parameter.
      The flag is used to decide in which
      logs updates to this variable should
      be logged.
   */
   char* FileID;
   /* A pointer to a file identification for
      the file this parameter should be saved in.
   */
   U8 ChangeFlag;
   /* Flag to indicate if value has been changed */
   value_t Minimum;
   value_t Maximum;
   /* Minimum and Maximum indicates the range of valid value for
    * the parameter. They may, however, be overwritten by setting
    * the NoLimits variable. */
   struct value_lists *Lists;
   /* Lists can point to a table with all allowed values. */
   value_t DefaultValue;
   /* Save of the default value */

};




/**************************************************/
/* The update types used in the variable database */
/**************************************************/

struct os_db_variable
{
   /* Just a help type */
   struct os_db_common_fields c;
};

struct os_db_iovariable
{
   /* Just a help type */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
};

struct os_db_logflag
{
   /* Size of the logflag */
   struct os_db_common_fields c;
   struct os_db_subparameter l;
};

struct os_db_local
{
   /* Used for local variables (UpdateType == LOCAL) */
   struct os_db_common_fields c;
   struct os_db_sublocal l;

   /* Reserve space for parameters*/
   U32 LogFlagName[PARAMETER_NAME_LENGTH /4 ];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];
};

struct os_db_parameter
{
   /* Used for local variables (UpdateType == PARAMETER) */
   struct os_db_common_fields c;
   struct os_db_subparameter l;

};


struct os_db_output_parameter
{
   /* Used for local variables (UpdateType == OUTPUT_PARAMETER) */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
   struct os_db_suboutputparameter l;


};

struct os_db_bit_input
{
   /* Used for local variables (UpdateType == BIT_INPUT) */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
   struct os_db_subbitinput l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];

   /* Reserve space for parameters*/
   U32 EnableName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Enable[sizeof (struct os_db_output_parameter) /4];

   U32 SubscriptionName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Subscription[sizeof (struct os_db_output_parameter) /4];

   U32 ChangeMaskName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 ChangeMask[sizeof (struct os_db_output_parameter) /4];

   U32 HoldtimeName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Holdtime[sizeof (struct os_db_output_parameter) /4];

   U32 InvertName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Invert[sizeof (struct os_db_output_parameter) /4];

};


struct os_db_countable_input
{
   /* Used for local variables (UpdateType == COUNTABLE_INPUT) */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
   struct os_db_subcountableinput l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];

   /* Reserve space for parameters*/
   U32 EnableName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Enable[sizeof (struct os_db_output_parameter) /4];

   U32 SubscriptionName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Subscription[sizeof (struct os_db_output_parameter) /4];

   U32 ThresholdName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Threshold[sizeof (struct os_db_output_parameter) /4];

   U32 HoldtimeName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Holdtime[sizeof (struct os_db_output_parameter) /4];

   U32 OffsetName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Offset[sizeof (struct os_db_output_parameter) /4];

   U32 ScaleName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Scale[sizeof (struct os_db_output_parameter) /4];

};

struct os_db_non_countable_input
{
   /* Used for local variables (UpdateType == NON_COUNTABLE_INPUT) */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
   struct os_db_subnoncountableinput l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];

   /* Reserve space for parameters*/
   U32 EnableName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Enable[sizeof (struct os_db_output_parameter) /4];

   U32 SubscriptionName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Subscription[sizeof (struct os_db_output_parameter) /4];

   U32 HoldtimeName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Holdtime[sizeof (struct os_db_output_parameter) /4];

};


struct os_db_bit_output
{
   /* Used for local variables (UpdateType == BIT_OUTPUT) */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
   struct os_db_subbitoutput l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];

   /* Reserve space for parameters*/
   U32 EnableName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Enable[sizeof (struct os_db_output_parameter) /4];

   U32 InvertName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Invert[sizeof (struct os_db_output_parameter) /4];

};

struct os_db_countable_output
{
   /* Used for local variables (UpdateType == COUNTABLE_OUTPUT) */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
   struct os_db_subcountableoutput l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];

   /* Reserve space for parameters*/
   U32 EnableName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Enable[sizeof (struct os_db_output_parameter) /4];

   U32 OffsetName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Offset[sizeof (struct os_db_output_parameter) /4];

   U32 ScaleName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Scale[sizeof (struct os_db_output_parameter) /4];

};

struct os_db_non_countable_output
{
   /* Used for local variables (UpdateType == NON_COUNTABLE_OUTPUT) */
   struct os_db_common_fields c;
   struct os_db_wpline wp;
   struct os_db_subnoncountableoutput l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];

   /* Reserve space for parameters*/
   U32 EnableName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 Enable[sizeof (struct os_db_output_parameter) /4];

};

struct os_db_system_ro
{
   /* Used for local variables (UpdateType == SYSTEM_RO) */
   struct os_db_common_fields c;
   struct os_db_subsystemro l;
};

struct os_db_system
{
   /* Used for local variables (UpdateType == SYSTEM) */
   struct os_db_common_fields c;
   struct os_db_subsystem l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];
};

struct os_db_timer
{
   /* Used for timer variables (Update == TIMER) */
   struct os_db_common_fields c;
};

struct os_db_backup
{
   /* Used for local variables (UpdateType == BACKUP) */
   struct os_db_common_fields c;
   struct os_db_subbackup l;

   /* Reserve space for logflag parameter*/
   U32 LogFlagName[(PARAMETER_NAME_LENGTH /4) +1];
   U32 LogFlag[(sizeof (struct os_db_logflag) /4) + 1];
};


struct os_db_summation
{
   /* Used for local variables (UpdateType == SUMMATION) */
   struct os_db_common_fields c;
   struct os_db_subsummation l;

};

struct os_db_availability
{
   /* Used for local variables (UpdateType == AVAILABILITY) */
   struct os_db_common_fields c;
   struct os_db_subavailability l;
};

struct os_db_alias
{
   /* A magic number to be checked before every operation
      to a variable in order to detect validity of data */
   U32 MagicNumber;
   /* A hash value calculated from the name */
   U32 HashValue;
   /* A pointer to the next variable with the same hash table
      index, or NULL if it the last. */
   varid_t NextName;

   /* Alias of the variable as a NULL-terminated UTF-8 string. */
   const char *Alias;

   /* Name of the variable as a NULL-terminated UTF-8 string. */
   const char *Name;

   /* Pointer to the parent variable */
   struct os_db_variable* Parent;

};

#endif
