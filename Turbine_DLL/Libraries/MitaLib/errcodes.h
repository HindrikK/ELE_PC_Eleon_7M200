/********************************************************************/
/*                                                                  */
/*            Copyright (c) 2003 Mita-Teknik a/s                    */
/*                                                                  */
/********************************************************************/
/*  $Date$
 *  $Author$
 *  $RCSfile$
 *  $Revision$ */
/********************************************************************/
/*                                                                  */
/* DESCRIPTION                                                      */
/*       Error codes which various functions can return.            */
/*                                                                  */
/* FUNCTIONS                                                        */
/*                                                                  */
/*     None                                                         */
/*                                                                  */
/********************************************************************/

#ifndef __errcodes_h
#define __errcodes_h

/* Error codes used by functions in link.c */
#define ERR_LINK_NO_FREE                        (-128)
#define ERR_LINK_NO_SEMAPHORE                   (-129)
#define ERR_LINK_NOT_FOUND                      (-130)

/* Error codes used by functions in lmodule.c */
#define ERR_LMODULE_NO_FREE                     (-144)
#define ERR_LMODULE_NO_SEMAPHORE                (-145)
#define ERR_LMODULE_NOT_FOUND                   (-146)

/* Error codes used by functions in backbone module */
#define ERR_BACKBONE_PUT                        (-150)
#define ERR_BACKBONE_MESSAGE                    (-151)

/* Error codes used by functions in vardb.c */
#define ERR_VARDB_BAD_VARIABLEID                (-160)
#define ERR_VARDB_VARIABLE_EXISTS               (-161)
#define ERR_VARDB_NO_SEMAPHORE                  (-162)
#define ERR_VARDB_WRONG_LENGTH                  (-163)
#define ERR_VARDB_WRONG_VALUE                   (-164)
#define ERR_VARDB_WRONG_UPDATE                  (-165)
#define ERR_VARDB_WRONG_TYPE                    (-166)
#define ERR_VARDB_NOT_FOUND                     (-167)
#define ERR_VARDB_NOT_READY                     (-168)
#define ERR_VARDB_NOT_IMPLEMENTED_YET           (-169)
#define ERR_VARDB_NO_NAME                       (-170)
#define ERR_VARDB_VARIABLE_LOCKED               (-171)
#define ERR_VARDB_NULL_POINTER                  (-172)
#define ERR_VARDB_VALUE_OUTSIDE_LIMITS          (-173)
#define ERR_VARDB_MENU_UPDATE_NOT_ALLOWED       (-174)
#define ERR_VARDB_WRONG_LIMITS                  (-175)
#define ERR_VARDB_WRONG_RESTORE                 (-176)
#define ERR_VARDB_BAD_VARIABLE                  (-177)
#define ERR_VARDB_ILLEGAL_UPDATE                (-178)
#define ERR_VARDB_BAD_BACKUP_FILE               (-179)
#define ERR_VARDB_WRONG_SCALE_VALUE             (-180)
#define ERR_VARDB_RW_ACCESS_NOT_GRANTED         (-181)

/* Error codes used by functions in io.c */
#define ERR_IO_NO_ROUTE_TO_ADDR                 (-200)
#define ERR_IO_CANNOT_ROUTE_TO_NET_ADDR         (-201)
#define ERR_IO_ROUTE_NOT_IMPLEMENTED            (-202)

/* Error codes used by functions in loadappl.c */
#define ERR_LOADAPPL_WRONG_CRC                  (-230)
#define ERR_LOADAPPL_ILL_FLASHOFFSET            (-231)
#define ERR_LOADAPPL_WRONG_APPL                 (-232)
#define ERR_LOADAPPL_NO_APPL                    (-233)
#define ERR_LOADAPPL_WRONG_LENGTH               (-234)
#define ERR_LOADAPPL_FLASH_ERR                  (-235)

/* Error codes used by function in flash.c */
#define FLASH_ADDRESS_OUT_OF_RANGE              (-250)

/* Error codes used by functions in backup.c */
#define ERR_BACKUP_ENTRY_NOT_FOUND              (-260)
#define ERR_BACKUP_TYPE_MISMATCH                (-261)
#define ERR_BACKUP_INVALID_FILENAME             (-262)
#define ERR_BACKUP_PARAMETER_CHECK              (-263)
#define ERR_INIT_CRC_ERROR                      (-264)
#define ERR_BACKUP_TIMEOUT                      (-265)
#define ERR_BACKUP_FILE_SIZE                    (-266)
#define ERR_BACKUP_BAD_RECORD_DATA              (-267)

/* Error codes used by functions in totlog.c */
#define ERR_TOTLOG_TOO_MANY_VARS                (-270)
#define ERR_TOTLOG_INVALID_PARAMETER            (-271)
#define ERR_TOTLOG_FILE_USER_ERROR              (-272)
#define ERR_TOTLOG_ARGUMENT                     (-273)
#define ERR_TOTLOG_LOOP_GUARD                   (-274)

/* Error codes used by functions in subhandl.c */
#define ERR_SUBHANDL_BAD_VARIABLEID             (-280)
#define ERR_SUBHANDL_BAD_TYPE                   (-281)

/* Error codes used by functions in lists.c */
#define ERR_LISTS_NO_SEMAPHORE                  (-290)
#define ERR_LISTS_NO_ELEMENT                    (-291)
#define ERR_LISTS_NOT_FOUND                     (-292)

/* Error codes used by functions in summa.c */
#define ERR_SUM_NOT_IMPLEMENTED                 (-300)
#define ERR_SUM_TYPE                            (-301)
#define ERR_SUM_VAR_NOT_FOUND                   (-302)
#define ERR_SUM_NO_SEMAPHORE                    (-303)
#define ERR_SUM_BAD_VARIABLEID                  (-304)
#define ERR_SUM_NO_NAME                         (-305)
#define ERR_SUM_VARIABLE_EXISTS                 (-306)
#define ERR_SUM_OUTSIDE_LIMITS                  (-307)
#define ERR_SUM_WRONG_TYPE_FOR_UPDATE           (-308)
#define ERR_SUM_WRONG_TYPE                      (-309)

/* Error codes used by eeprom.c */
#define ERR_EEPROM_PARAMETER_ERROR              (-320)
#define ERR_EEPROM_NOT_FOUND                    (-321)
#define ERR_EEPROM_NO_I2C                       (-322)
#define ERR_EEPROM_NO_SPI                       (-323)
#define ERR_EEPROM_DATA_NOT_VALID               (-324)
#define ERR_EEPROM_OUT_OF_RO_MEM                (-325)
#define ERR_EEPROM_OUT_OF_RW_MEM                (-326)
#define ERR_EEPROM_VAR_NOT_FOUND                (-327)
#define ERR_EEPROM_CRC_ERROR                    (-328)
#define ERR_EEPROM_WRONG_VERSION                (-329)
#define ERR_EEPROM_ADDRESS_WRITE_PROTECTED      (-330)
#define ERR_EEPROM_VERIFY_ERROR					(-331)

/* Error codes used by temp.c */
#define ERR_TEMP_INIT                           (-335)

/* Error codes for statuscode functions */
#define ERR_STATUSCODE_WRONG_VERSION            (-340)
#define ERR_STATUSCODE_DUPLICATE                (-341)
#define ERR_STATUSCODE_BAD_INDEX                (-342)
#define ERR_STATUSCODE_BAD_UPDATE_TYPE          (-343)
#define ERR_STATUSCODE_BAD_CONTROL_BLOCK        (-344)
#define ERR_STATUSCODE_BAD_INIT_STRUCTURE       (-345)
#define ERR_STATUSCODE_BAD_INIT_SIZE            (-346)
#define ERR_STATUSCODE_TOO_MANY_STATUS_CODES    (-347)
#define ERR_STATUSCODE_CHANGE_NOT_ALLOWED       (-348)

/* Error codes used by autoexec.c */
#define ERR_AUTOEXEC_NO_VALID_PATH              (-350)
#define ERR_AUTOEXEC_NO_VALID_FILE              (-351)
#define ERR_AUTOEXEC_FILE_TOO_SHORT             (-352)
#define ERR_AUTOEXEC_FILE_TOO_LONG              (-353)
#define ERR_AUTOEXEC_BAD_IMAGE_IDENT            (-354)
#define ERR_AUTOEXEC_BAD_IMAGE_TYPE             (-355)
#define ERR_AUTOEXEC_BAD_IMAGE_DATA             (-356)
#define ERR_AUTOEXEC_BAD_CRC                    (-357)
#define ERR_AUTOEXEC_BAD_BACKUP_CRC             (-358)
#define ERR_AUTOEXEC_OVERFLOW_APP_SLOTS         (-359)

/* Error relating to memory handling (memory.h) */
#define ERR_MEMORY_IN_USE                       (-360)
#define ERR_MEMORY_OUT_OF_RANGE                 (-361)
#define ERR_MEMORY_REG_ERROR                    (-362)
#define ERR_MEMORY_NOT_FOUND                    (-363)
#define ERR_MEMORY_BAD_USAGE                    (-364)

/* Error relating to task handling (task.h) */
#define  ERR_TASK_WRONG_TASK_OBJECT             (-370)  /* Not af defined task object type */

#define ERR_OS_VERSION_OS_WRONG_VERSION         (-380)
#define ERR_OS_VERSION_APP_NULL_POINTER         (-381)
#define ERR_OS_VERSION_OS_NULL_POINTER          (-382)

#define ERR_OS_MENU_CREATE_GROUP_NULL_POINTER   (-400)
#define ERR_OS_MENU_CREATE_MENU_NULL_POINTER    (-401)
#define ERR_OS_MENU_CREATE_MENU_NO_GROUP        (-402)
#define ERR_OS_MENU_CREATE_LINES_NULL_POINTER   (-403)
#define ERR_OS_MENU_CREATE_LINES_NO_GROUP       (-404)
#define ERR_OS_MENU_CREATE_LINES_NO_MENU        (-405)
#define ERR_OS_MENU_CREATE_LINES_NO_VAR         (-406)
#define ERR_OS_MENU_CREATE_BUTTON_NULL_POINTER  (-407)
#define ERR_OS_MENU_FIND_NO_GROUP               (-408)
#define ERR_OS_MENU_FIND_NO_MENU                (-409)
#define ERR_OS_MENU_CREATE_ALREADY_EXISTS       (-410)
#define ERR_OS_MENU_CREATE_NO_LINE              (-411)
#define ERR_OS_MENU_MAGIC_NUMBER_MISMATCH       (-412)

/* Error codes used by functions in avail.c */
#define ERR_AVAIL_NO_SEMAPHORE                  (-420)
#define ERR_AVAIL_BAD_VARIABLEID                (-421)
#define ERR_AVAIL_NO_NAME                       (-422)
#define ERR_AVAIL_VARIABLE_EXISTS               (-423)
#define ERR_AVAIL_UNKNOWN_TOTAL                 (-424)
#define ERR_AVAIL_INVALID_GROUP_NUMBER          (-425)
#define ERR_AVAIL_INVALID_GROUP_DATA            (-426)
#define ERR_AVAIL_INVALID_PARAMETER             (-427)
#define ERR_AVAIL_NO_TIMESTAMP                  (-428)

/* Error codes used by functions in stscode.c */
#define ERR_STS_INI_FILE_BAD_CRC                (-440)
#define ERR_STS_INI_FILE_CRC_MISSING            (-441)
#define ERR_STS_INI_FILE_MISSING                (-442)
#define ERR_STS_INI_FILE_STS_CODE_MISSING       (-443)
#define ERR_STS_INI_FILE_FIELD_MISSING          (-444)
#define ERR_STS_INI_FILE_BAD_FIELD_NAME         (-445)
#define ERR_STS_INI_FILE_BAD_FILE               (-446)
#define ERR_STS_INI_FILE_ILLEGAL_FIELD          (-447)
#define ERR_STS_BAD_FILENAMES                   (-448)


/* Error codes used by RTL8019.c */
#define  ERR_RTL8019_ID_NOT_FOUND               (-460)
#define  ERR_NET_BUFFER_ALLOC_ERROR             (-461)
#define  RTL8019_OPEN_ERROR                     (-462)
#define  ETH_OPEN_ERROR                         RTL8019_OPEN_ERROR                     
#define  RTL8019_INVALID_RECEIVE_PKT_SIZE       (-463)

/* Error codes used by simple logs */
#define  ERR_SIMPLE_LOG_LOOP_GUARD              (-470)

/* Error codes used by 5 min log */
#define  ERR_5MINLOG_LOOP_GUARD                 (-480)
#define  ERR_5MINLOG_TOO_MANY_VARS              (-481)
#define  ERR_5MINLOG_WRONG_TYPE                 (-482)
#define  ERR_5MINLOG_WRONG_TIME                 (-483)

/* Error codes used for log in general */
#define  ERR_LOG_MEMORY_ACCESS                  (-485)

/* Error codes used by functions in debug.c */
#define  ERR_DBG_ILLEGAL_OUTPUT                 (-490)

/* Error codes used by functions in com_mgr.c and directly related files */
#define ERR_COMM_LOGIN_FAILED                   (-503) /* Don't change this!!! */
#define ERR_COMM_NO_CONNECT                     (-506) /* Don't change this!!! */
#define ERR_COMM_NO_CARRIER                     (-507) /* Don't change this!!! */
#define ERR_COMM_BUSY                           (-508) /* Don't change this!!! */
#define ERR_COMM_NO_MODEM                       (-510) /* Don't change this!!! */
#define ERR_COMM_BAD_ARGS                       (-520)
#define ERR_COMM_DENIED                         (-521)
#define ERR_COMM_QUEUED                         (-522)
#define ERR_COMM_NOT_INITED                     (-523)
#define ERR_COMM_NO_DEVICE                      (-524)
#define ERR_COMM_BAD_NAME                       (-525)
#define ERR_COMM_NOT_READY                      (-526)
#define ERR_COMM_WRONG_BAUD                     (-527)
#define ERR_COMM_INTERNAL_ERROR                 (-528)

#define ERR_PPP_CONECTION_ERROR                 (-530)

#define ERR_ACCOUNT_PASSWORD_NOT_VALID          (-540)
#define ERR_ACCOUNT_TOO_MANY_USERS              (-541)
#define ERR_ACCOUNT_UNKNOWN                     (-542)
#define ERR_ACCOUNT_ACCESS_DENIED               (-543)
#define ERR_ACCOUNT_NOT_INITIALIZED             (-544)
#define ERR_ACCOUNT_DUPLICATE_SOCKET            (-545)

/* Error codes used by the watchdog */
#define ERR_WD_NO_ITEM                          (-550)
#define ERR_WD_NO_MORE_ITEMS                    (-551)
#define ERR_WD_UNKNOWN_OPTION                   (-552)

#define ERR_CUSTLANG_NO_MEM                     (-560)  // Can't allocate mem for linked list
#define ERR_CUSTLANG_ILLEGAL_LANGCODE           (-561)  // Wrong lenght, must be 2 characters (plus '\0')
#define ERR_CUSTLANG_LANGCODE_NOT_FOUND         (-562)  // Couldn't find this LanfCode in language ini file
#define ERR_CUSTLANG_CAN_NOT_READ_MO_FILE       (-563)  // Couldn't read mo file
#define ERR_CUSTLANG_CAN_NOT_WRITE_MO_FILE      (-564)  // Couldn't write mo file (when mo file shoud be swaped)
#define ERR_CUSTLANG_CAN_NOT_CLOSE_MO_FILE      (-565)  // Couldn't close mo file
#define ERR_CUSTLANG_TOO_MANY_USERS             (-566)  // Too many language users
#define ERR_CUSTLANG_REMOVE                     (-567)  // Language user can not be removed
#define ERR_CUSTLANG_UNKNOWN                    (-568)  // Error custom language unknown

/* Error codes used by filesystem */
#define ERR_FORMATTING_CANCELLED                (-570)

/* Error codes used by WP-Line */
#define ERR_WPL_GROUP_NOT_FOUND                 (-580)
#define ERR_WPL_MODULE_NOT_FOUND                (-581)
#define ERR_WPL_ILLEGAL_STATE                   (-582)

#endif
