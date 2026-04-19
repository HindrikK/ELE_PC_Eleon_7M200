//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2015 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:101$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2014/03/25 15:37:52 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: turbdef.h,v $                                                       
// $Revision: 1.21 $                                                             
//                                                                               
//******************************PEPTOOL Header End*******************************

#ifndef FILE_TURBDEF_H
#define FILE_TURBDEF_H

#include "os_lib.h"

//_____________________________________________________________________
//                               General

#ifndef NOLOG_ENABLE
#define NOLOG_ENABLE         ((U8)0)
#endif

#define N_(string) string // Macro for marking strings only

#define ENABLE   ((U8)1)
#define DISABLE  ((U8)0)

#define TEXT_ON             "On"
#define TEXT_OFF            "Off"

#define TEXT_ENABLE         "Enable"
#define TEXT_DISABLE        "Disable"
#define TEXT_WARNING        "Warning"
#define TEXT_NOT_AVAILABLE  "N/A"
//---------------------------------------------------------------------
#ifndef ERR_1_TO_7
#define ERR_1_TO_7
#define ERR_1    ((U8)1)
#define ERR_2    ((U8)2)
#define ERR_3    ((U8)3)
#define ERR_4    ((U8)4)
#define ERR_5    ((U8)5)
#define ERR_6    ((U8)6)
#define ERR_7    ((U8)7)
#endif
//---------------------------------------------------------------------
#define STEP0    ((U8)0)
#define STEP1    ((U8)10)
#define STEP2    ((U8)20)
#define STEP3    ((U8)30)
#define STEP4    ((U8)40)
#define STEP5    ((U8)50)
#define STEP6    ((U8)60)
#define STEP7    ((U8)70)
#define STEP8    ((U8)80)
#define STEP9    ((U8)90)
#define STEP10   ((U8)100)
#define STEP11   ((U8)110)
#define STEP12   ((U8)120)
#define STEP13   ((U8)130)
#define STEP14   ((U8)140)
#define STEP15   ((U8)150)

#define PASSWORD_LEVEL_99 ((U8)99)

//_____________________________________________________________________
//                           Managers
#define MANAGER_MODE_DISABLE                    ((U8)0)
#define MANAGER_MODE_ENABLE                     ((U8)1)
#define MANAGER_MODE_FORCED_DISABLE             ((U8)2)
#define MANAGER_MODE_FORCED_ENABLE              ((U8)3)

#define MANAGER_MODE_FORCED_DISABLE_TEXT        "Forced Disable"
#define MANAGER_MODE_FORCED_ENABLE_TEXT         "Forced Enable"

//_____________________________________________________________________
//                          Mode/State/Status
#define MODE_AUTO                          ((U8)0)
#define MODE_SERVICE_OFF                   ((U8)1)
#define MODE_SERVICE_ON                    ((U8)2)
#define MODE_SERVICE_LOW_ON                ((U8)2)
#define MODE_SERVICE_HIGH_ON               ((U8)3)

//---------------------------------------------------------------------
#define STATE_AUTO_ON                      ((U8)0)
#define STATE_AUTO_OFF                     ((U8)1)
#define STATE_AUTO_LOW_ON                  ((U8)2)
#define STATE_AUTO_HIGH_ON                 ((U8)3)
#define STATE_AUTO_INTERVAL                ((U8)4)
#define STATE_BLOCKED                      ((U8)5)
#define STATE_STOPPED                      ((U8)6)
#define STATE_SUSPENDED                    ((U8)11)

#define STATE_SERVICE_ON                   ((U8)7)
#define STATE_SERVICE_OFF                  ((U8)8)
#define STATE_SERVICE_LOW_ON               ((U8)9)
#define STATE_SERVICE_HIGH_ON              ((U8)10)

#define STATE_REGISTERED                   ((U32)0x7FFFFFFE)    // Object is registered in its manager object
#define STATE_UNREGISTERED                 ((U32)0x7FFFFFFF)    // Object is not registered in its manager object

//---------------------------------------------------------------------
#define STATE_TEXT_AUTO_ON             "Auto On"
#define STATE_TEXT_AUTO_OFF            "Auto Off"
#define STATE_TEXT_AUTO_LOW_ON         "Auto Low On"
#define STATE_TEXT_AUTO_HIGH_ON        "Auto High On"

#define STATE_TEXT_SERVICE_ON          "Service On"
#define STATE_TEXT_SERVICE_OFF         "Service Off"
#define STATE_TEXT_SERVICE_LOW_ON      "Service Low On"
#define STATE_TEXT_SERVICE_HIGH_ON     "Service High On"

#define STATE_TEXT_AUTO_OPEN           "Auto Open"
#define STATE_TEXT_AUTO_CLOSE          "Auto Close"

#define STATE_TEXT_SERVICE_OPEN        "Service Open"
#define STATE_TEXT_SERVICE_CLOSE       "Service Close"



#define STATE_TEXT_BLOCKED             "Blocked"
#define STATE_TEXT_STOPPED             "Stopped"
#define STATE_TEXT_SUSPENDED           "Suspended"
#define STATE_TEXT_UNDEFINED           "Undefined"

//---------------------------------------------------------------------
#define STATE_ACTUATOR_SERVICE_BLOCKED      ((U8)21)
#define STATE_ACTUATOR_SERVICE_OFF          ((U8)22)
#define STATE_ACTUATOR_SERVICE_ON           ((U8)23)
#define STATE_ACTUATOR_SERVICE_MOVE_TO_OFF  ((U8)24)
#define STATE_ACTUATOR_SERVICE_MOVE_TO_ON   ((U8)25)
#define STATE_ACTUATOR_AUTO_MOVE_TO_ON      ((U8)26)
#define STATE_ACTUATOR_AUTO_MOVE_TO_OFF     ((U8)27)

#define MODE_EXEC_MECH_SERVICE_BLOCK        ((U8)1)
#define MODE_EXEC_MECH_SERVICE_OFF          ((U8)2)
#define MODE_EXEC_MECH_SERVICE_ON           ((U8)3)
#define MODE_EXEC_MECH_SERVICE_MOVE_TO_OFF  ((U8)4)
#define MODE_EXEC_MECH_SERVICE_MOVE_TO_ON   ((U8)5)

typedef enum _EXEC_MECH_STATE_t
{
    STATE_EXEC_MECH_UNDEFINED = 0,
    STATE_EXEC_MECH_ON,
    STATE_EXEC_MECH_OFF,
    STATE_EXEC_MECH_TO_ON,
    STATE_EXEC_MECH_TO_OFF,
    STATE_EXEC_MECH_ERROR
} EXEC_MECH_STATE_t;

typedef enum _EXEC_MECH_ERR_t
{
    ERROR_EXEC_MECH_NONE = 0,
    ERROR_EXEC_MECH_TO_ON,
    ERROR_EXEC_MECH_TO_OFF,
    ERROR_EXEC_MECH_ON_OFF
} EXEC_MECH_ERR_t;

#define STATE_TEXT_EXEC_MECH_OFF            "Actuator OFF"
#define STATE_TEXT_EXEC_MECH_ON             "Actuator ON"
#define STATE_TEXT_EXEC_MECH_ERROR          "Error"
#define STATE_TEXT_EXEC_MECH_UNDEFINED      "Undefined"

#define STATE_TEXT_SERVICE_MOVE_TO_OFF      "Service move to OFF position"
#define STATE_TEXT_SERVICE_MOVE_TO_ON       "Service move to ON position"
#define STATE_TEXT_SERVICE_BLOCKED          "Service Blocked"
#define STATE_TEXT_AUTO_MOVE_TO_ON          "Auto move to ON position"
#define STATE_TEXT_AUTO_MOVE_TO_OFF         "Auto move to OFF position"

//---------------------------------------------------------------------
#define STATUS_OK              ((U8)0)

#define STATUS_SC_OPEN         ((U8)1)
#define STATUS_GRID_ERRROR     ((U8)2)
#define STATUS_LVRT            ((U8)3)

#define STATUS_NOT_READY       ((U8)0)
#define STATUS_READY           ((U8)1)
//---------------------------------------------------------------------
#define STATUS_OK_TEXT            "Ok"
#define STATUS_SC_OPEN_TEXT       "Safety open"
#define STATUS_GRID_ERRROR_TEXT   "Grid error"
#define STATUS_LVRT_TEXT          "LVRT"

#define STATUS_TEXT_NOT_READY     "Not ready"
#define STATUS_TEXT_READY         "Ready"
#define STATUS_TEXT_UNDEFINED     "Undefined"

//---------------------------------------------------------------------
//Gray-code mode define
#define Z_Mode             ((U8)0x01)
#define FRQ_DIV_2          ((U8)0x02)
#define FRQ_DIV_4          ((U8)0x04)
#define FRQ_DIV_8          ((U8)0x06)

#define GRAY_CODE_MODE     FRQ_DIV_4 | Z_Mode

//---------------------------------------------------------------------
#define RESET_BUTTON_PRESSED     ((U8)1)
#define RESET_BUTTON_RELEASED    ((U8)0)

//_____________________________________________________________________
//                            Yaw programs
#define YAW_PROG_MIN ((U8)0)
#define YAW_PROG_MAX ((U8)250)

#define YAW_PROG_0   ((U8)0)
#define YAW_PROG_30  ((U8)30)
#define YAW_PROG_50  ((U8)50)
#define YAW_PROG_60  ((U8)60)
#define YAW_PROG_70  ((U8)70)
#define YAW_PROG_80  ((U8)80)
#define YAW_PROG_100 ((U8)100)
#define YAW_PROG_230 ((U8)230)
#define YAW_PROG_240 ((U8)240)
#define YAW_PROG_250 ((U8)250)
//---------------------------------------------------------------------
#define B_YAWCCW     ((U32)62721)
#define B_YAWCW      ((U32)62722)
#define B_YAWBLOCK   ((U32)62723)
#define B_YAWAUTO    ((U32)62724)

//#define YAW_NORMAL_MODE 0
//#define YAW_SOFT_MODE   1
//#define YAW_HARD_MODE 2		//MOD_150114_2
//--------yaw brakes----------------------------------------------------
//enum _YAWBRAKE_State
//{
//    YB_CLOSE = 0x00,
//    YB_GRP1_CLOSE,
//    YB_GRP2_CLOSE,

//    YB_RELEASE = 0xF0,
//    YB_GRP1_RELEASE,
//    YB_GRP2_RELEASE
//};

#define YB_RELEASE_MASK ((U8)0xF0)
#define YB_GRP_MASK ((U8)0x0F)

//_____________________________________________________________________
//                           Brake programs
#define BRAKE_PROG_0   ((U8)0)
#define BRAKE_PROG_10  ((U8)10)
#define BRAKE_PROG_50  ((U8)50)
#define BRAKE_PROG_70  ((U8)70)
#define BRAKE_PROG_75  ((U8)75)
#define BRAKE_PROG_99  ((U8)99)
#define BRAKE_PROG_199 ((U8)199)
#define BRAKE_PROG_200 ((U8)200)
#define BRAKE_PROG_210 ((U8)210)
#define BRAKE_PROG_MAX ((U8)211)

//_____________________________________________________________________
//                             CANopen
// State
typedef enum _NODE_STATE_t
{
    CO_UNKNOWN,
    CO_INITIALISING,
    CO_STOPPED         =4,
    CO_OPERATIONAL     =5,
    CO_PRE_OPERATIONAL =127,
    CO_RESET_APPLICATION,
    CO_RESET_COMM
} NODE_STATE_t, NODE_STATE_T;
//---------------------------------------------------------------------
// CAN bus status
#define CAN_BUS_INIT          ((U8)0x01)
#define CAN_BUS_ACTIVE        ((U8)0x02)
#define CAN_BUS_BUSOFF        ((U8)0x04)
#define CAN_BUS_PASSIVE       ((U8)0x08)
#define CAN_BUS_OVERRUN       ((U8)0x10)
#define CAN_BUS_STATE_MASK    ((U8)0x0F)

#define CAN_BUS_FLAGS         ((U8)0xFF)
//---------------------------------------------------------------------
// Master and Network status
#define MASTER_READY4START          ((U32)0x00010000)
#define MASTER_STARTED              ((U32)0x00020000)
#define NET_ALL_SLAVES_BOOTED       ((U32)0x00040000)
#define NET_ALL_SLAVES_STARTED      ((U32)0x00080000)
#define NET_BOOT_TIMEOUT            ((U32)0x00100000)
#define NET_STARTUP_STOPPED         ((U32)0x00200000)
#define MASTER_NET_FLAGS            ((U32)0xFFFF0000)
//---------------------------------------------------------------------
// Slave status
#define SLAVE_BOOT_STARTED          ((U32)0x00010000)
#define SLAVE_CONFIG_FINISHED       ((U32)0x00020000)
#define SLAVE_BOOT_FINISHED         ((U32)0x00040000)
#define SLAVE_STARTED               ((U32)0x00080000)
#define SLAVE_NO_DEVICE_TYPE        ((U32)0x00100000)
#define SLAVE_WRONG_DEVICE_TYPE     ((U32)0x00200000)
#define SLAVE_WRONG_VENDOR_ID       ((U32)0x00400000)
#define SLAVE_CONFIG_DNL_FAILED     ((U32)0x00800000)
#define SLAVE_NO_NMT_DURING_BOOTUP  ((U32)0x01000000)
#define SLAVE_WRONG_PRODUCT_CODE    ((U32)0x02000000)
#define SLAVE_WRONG_REVISION        ((U32)0x04000000)
#define SLAVE_WRONG_SERIAL_NUMBER   ((U32)0x08000000)
#define SLAVE_MANDATORY_ERROR       ((U32)0x10000000)
#define SLAVE_CONFIG_ERROR          ((U32)0x20000000)
#define SLAVE_FLAGS                 ((U32)0xFFFF0000)

#define SLAVE_NMT_STARTUP_ERROR    (SLAVE_NO_DEVICE_TYPE     | SLAVE_WRONG_DEVICE_TYPE    | SLAVE_WRONG_VENDOR_ID    | \
                                    SLAVE_CONFIG_DNL_FAILED  | SLAVE_NO_NMT_DURING_BOOTUP | SLAVE_WRONG_PRODUCT_CODE | \
                                    SLAVE_WRONG_REVISION     | SLAVE_WRONG_SERIAL_NUMBER  | SLAVE_MANDATORY_ERROR)
//---------------------------------------------------------------------
#define SDO_ACTION_COMMON_READ     ((U8)0)
#define SDO_ACTION_COMMON_WRITE    ((U8)1)

//_____________________________________________________________________
//                             Old CANopen
#define ERR_ETHCAT_NO_SOCKET                  (10) // Socket not open and initialized
#define ERR_ETHCAT_ILLEGAL_MSG_TYPE           (11) // Received message type not recognized
#define ERR_ETHCAT_ILLEGAL_MSG_LENGTH         (12) // Received length didn't match expected length (according to msg type)
#define ERR_ETHCAT_RXBUFFER_OVERFLOW          (16) // Waiting for more data to receive, than will fit in RxBuffer
#define ERR_ETHCAT_IPADDR_INVALID             (17) // IP address didn't match x.y.z.q pattern
#define ERR_ETHCAT_GENERAL_ERROR              (18) // Non specified error, should not happen..
#define ERR_ETHCAT_GENERAL_ERROR2             (19) // Non specified error, should not happen..
#define ERR_ETHCAT_CONNECTION_NOT_INITIALIZED (20) // Connection must be initialized before attempting to connect
#define ERR_ETHCAT_UPDATE_VARDB               (21) // Error occured updating VARDB
#define ERR_ETHCAT_READ_VARDB                 (22) // Error occured reading VARDB
#define ERR_ETHCAT_GET_VARID                  (23) // Error occured getting VARID
#define ERR_ETHCAT_TX_CONN_WAS_DOWN_NOW_OK    (24) // Transmit connection has been down but is now working again
#define ERR_ETHCAT_ILLEGAL_CONVERSION_TYPE    (25) // Conversion type unknown
#define ERR_ETHCAT_CATDRV_CONSTRUCT           (26) // Error occured when constructing CanDrv (can't allocate mem)
#define ERR_ETHCAT_WRONG_TASK_TYPE            (27) // Task type must be either PLU or INV (enum TASK_TYPE_T in canlib.h)
#define ERR_ETHCAT_UDP_RXBUFFEROVERFLOW       (28) // New data ready, but not room in rx buffer for the biggest possible UDP message
#define ERR_ETHCAT_CANMANAGER_INIT_FAIL       (29) // Initialization of CANmanager failed, see syslog for details


//_____________________________________________________________________
//                             TCP Errors
#define ERR_TCP_NO_SOCKET                  (30) // Socket not open and initialized
#define ERR_TCP_ILLEGAL_MSG_TYPE           (31) // Received message type not recognized
#define ERR_TCP_ILLEGAL_MSG_LENGTH         (32) // Received length didn't match expected length (according to msg type)
#define ERR_TCP_RXBUFFER_OVERFLOW          (36) // Waiting for more data to receive, than will fit in RxBuffer
#define ERR_TCP_IPADDR_INVALID             (37) // IP address didn't match x.y.z.q pattern
#define ERR_TCP_GENERAL_ERROR              (38) // Non specified error, should not happen..
#define ERR_TCP_GENERAL_ERROR2             (39) // Non specified error, should not happen..
#define ERR_TCP_CONNECTION_NOT_INITIALIZED (40) // Connection must be initialized before attempting to connect
#define ERR_TCP_CANT_UPDATE_VARDB          (41) // Error occured updating VARDB
#define ERR_TCP_CANT_READ_VARDB            (42) // Error occured reading VARDB
#define ERR_TCP_CANT_GET_VARID             (43) // Error occured getting VARID
#define ERR_TCP_TX_CONN_WAS_DOWN_NOW_OK    (44) // Transmit connection has been down but is now working again
#define ERR_TCP_ILLEGAL_CONVERSION_TYPE    (45) // Conversion type unknown
#define ERR_TCP_CANDRV_CANT_CONSTRUCT      (46) // Error occured when constructing CanDrv (can't allocate mem)
#define ERR_TCP_WRONG_TASK_TYPE            (47) // Task type must be either PLU or INV (enum TASK_TYPE_T in canlib.h)
#define ERR_TCP_CANMANAGER_INIT_FAIL       (48) // Initialization of CANmanager failed, see syslog for details

//_____________________________________________________________________
//                             Operate
typedef enum _OPERATE_MODE_t
{
    OPERATE_MODE_RUN_AUTO,
    OPERATE_MODE_RUN_SERVICE = 10,
    OPERATE_MODE_SERVICE = 20
} OPERATE_MODE_t;

//  Operate State:
//  - These defines uses for S32 type variable
//  - 32 digits are divided into groups to determine operational state, step, conditions
//  in general, negative values are used to describe active Brake Program (50 or more)
//  =================================================================================================================
//  |          0 - 7        |     8 - 15      |           16 - 23           |    24 - 30    |       31              |
//  |-----------------------|-----------------|-----------------------------|---------------|-----------------------|
//  | step in each operate  |  operate state  | describe status of the      |   reserved    | Is Braking procedure  |
//  |          state        |                 | turbine: BP active, Stopped,|               | active (1 - active)   |
//  |                       |                 | Freewheeling, Producing     |               |                       |
//  =================================================================================================================
//
//  STEPS
#define OPERATE_STATE_STEP_MASK       ((S32)0xFF)

#define OPERATE_STATE_STEP_NA         ((S32)0x00)

#define OPERATE_STATE_STEP1           ((S32)0x01)
#define OPERATE_STATE_STEP2           ((S32)0x02)
#define OPERATE_STATE_STEP3           ((S32)0x03)
#define OPERATE_STATE_STEP4           ((S32)0x04)
#define OPERATE_STATE_STEP5           ((S32)0x05)
#define OPERATE_STATE_STEP6           ((S32)0x06)
#define OPERATE_STATE_STEP7           ((S32)0x07)
#define OPERATE_STATE_STEP8           ((S32)0x08)
#define OPERATE_STATE_STEP9           ((S32)0x09)
#define OPERATE_STATE_STEP10          ((S32)0x0A)
#define OPERATE_STATE_STEP11          ((S32)0x0B)
#define OPERATE_STATE_STEP12          ((S32)0x0C)
#define OPERATE_STATE_STEP13          ((S32)0x0D)
#define OPERATE_STATE_STEP14          ((S32)0x0E)
#define OPERATE_STATE_STEP15          ((S32)0x0F)
#define OPERATE_STATE_STEP16          ((S32)0x10)
#define OPERATE_STATE_STEP17          ((S32)0x11)
#define OPERATE_STATE_STEP18          ((S32)0x12)
#define OPERATE_STATE_STEP19          ((S32)0x13)
#define OPERATE_STATE_STEP20          ((S32)0x14)

//---------------------------------------------------------------------
//  OPERATE STATES
#define OPERATE_STATE_NAME_MASK             ((S32)0xFF00)

#define OPERATE_STATE_BP_MIN                ((S32)0x0000)     // 0
#define OPERATE_STATE_BP_50                 ((S32)0x0E00)
#define OPERATE_STATE_BP_70                 ((S32)0x0F00)
#define OPERATE_STATE_BP_99                 ((S32)0x1500)
#define OPERATE_STATE_BP_199                ((S32)0x1C00)
#define OPERATE_STATE_BP_200                ((S32)0x2300)
#define OPERATE_STATE_BP_201                ((S32)0x2A00)
#define OPERATE_STATE_BP_210                ((S32)0x3100)
#define OPERATE_STATE_BP_MAX                ((S32)0x3200)     // 50

#define OPERATE_STATE_STOPPED_MIN           ((S32)0x3300)     // 51
#define OPERATE_STATE_STARTING              ((S32)0x3F00)
#define OPERATE_STATE_SERVICE               ((S32)0x4B00)
#define OPERATE_STATE_YAW_INTO_WIND         ((S32)0x5700)
#define OPERATE_STATE_STOPPED_MAX           ((S32)0x6400)     // 100

#define OPERATE_STATE_TEST_MIN              ((S32)0x6500)     // 101
#define OPERATE_STATE_SELFTEST_RUN_CHECK    ((S32)0x6A00)
#define OPERATE_STATE_SELFTEST_1            ((S32)0x6F00)
#define OPERATE_STATE_SELFTEST_2            ((S32)0x7000)
#define OPERATE_STATE_SELFTEST_3            ((S32)0x7100)
#define OPERATE_STATE_SELFTEST_4            ((S32)0x7200)
#define OPERATE_STATE_SELFTEST_5            ((S32)0x7300)
#define OPERATE_STATE_SELFTEST_6            ((S32)0x7400)
#define OPERATE_STATE_SELFTEST_SKIP         ((S32)0x8D00)
#define OPERATE_STATE_TEST_MAX              ((S32)0x9600)     // 150

#define OPERATE_STATE_RUN_MIN               ((S32)0x9700)     // 151
#define OPERATE_STATE_FREEWHEEL_INIT        ((S32)0x9C00)
#define OPERATE_STATE_FREEWHEEL_G1          ((S32)0xA100)
#define OPERATE_STATE_GRIDCONNECT_G1        ((S32)0xA600)
#define OPERATE_STATE_OPERATION_G1          ((S32)0xAB00)
#define OPERATE_STATE_LVRT                  ((S32)0xAE00)
#define OPERATE_STATE_FREEWHEEL_G1G1        ((S32)0xB000)
#define OPERATE_STATE_TORQUE_TABLE_CHANGE   ((S32)0xB500)
#define OPERATE_STATE_PITCH_LUB             ((S32)0xBA00)
#define OPERATE_STATE_PITCH_BATT_TEST       ((S32)0xBF00)
#define OPERATE_STATE_PITCH_SERV_TEST       ((S32)0xC400)
#define OPERATE_STATE_RUN_MAX               ((S32)0xC800)     // 200

//---------------------------------------------------------------------
//  TURBINE STATUS
#define TURBINE_STATUS_MASK                 ((S32)0xFF0000)

#define TURBINE_STATUS_STOPPED              ((S32)0x010000)
#define TURBINE_STATUS_FREEWHEELING         ((S32)0x020000)
#define TURBINE_STATUS_PRODUCING            ((S32)0x030000)

//---------------------------------------------------------------------
//  SYSTEM STATUS
#define SYSTEM_STATUS_OK                    ((S32)0)
#define SYSTEM_STATUS_WARNING               ((S32)1)
#define SYSTEM_STATUS_STOP                  ((S32)2)

//---------------------------------------------------------------------
//  OPERATE BRAKING STATUS
#define OPERATE_STATE_BRAKE_PROG_MASK       ((S32)0x80000000)
#define OPERATE_STATE_BRAKE_PROG_ACTIVE     ((S32)0x80000000)
#define OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE ((S32)0x0)

//---------------------------------------------------------------------
#define OPERATE_STATE_UNION_SERVICE              ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SERVICE       | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_STARTING             ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_STARTING      | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_YAW_INTO_WIND        ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_YAW_INTO_WIND | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_SELFTEST_CHECK       ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_RUN_CHECK | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_SKIP        ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_SKIP      | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_SELFTEST_1_NA        ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_1 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_1_STEP_1    ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_SELFTEST_1 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_1_STEP_2    ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_SELFTEST_1 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_1_STEP_3    ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_SELFTEST_1 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_1_STEP_4    ((S32)(OPERATE_STATE_STEP4   | OPERATE_STATE_SELFTEST_1 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_SELFTEST_2_NA        ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_2 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_2_STEP_1    ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_SELFTEST_2 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_2_STEP_2    ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_SELFTEST_2 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_2_STEP_3    ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_SELFTEST_2 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_SELFTEST_3_NA        ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_3 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_3_STEP_1    ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_SELFTEST_3 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_3_STEP_2    ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_SELFTEST_3 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_3_STEP_3    ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_SELFTEST_3 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_3_STEP_4    ((S32)(OPERATE_STATE_STEP4   | OPERATE_STATE_SELFTEST_3 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_SELFTEST_4_NA        ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_4 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_4_STEP_1    ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_SELFTEST_4 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_4_STEP_2    ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_SELFTEST_4 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_4_STEP_3    ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_SELFTEST_4 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_SELFTEST_5_NA        ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_5 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_5_STEP_1    ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_SELFTEST_5 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_5_STEP_2    ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_SELFTEST_5 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_SELFTEST_5_STEP_3    ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_SELFTEST_5 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_SELFTEST_6           ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_SELFTEST_6 | TURBINE_STATUS_STOPPED | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_FREEWHEEL_INIT_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_FREEWHEEL_INIT | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_INIT_STEP_1 ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_FREEWHEEL_INIT | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_INIT_STEP_2 ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_FREEWHEEL_INIT | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_INIT_STEP_3 ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_FREEWHEEL_INIT | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_INIT_STEP_4 ((S32)(OPERATE_STATE_STEP4   | OPERATE_STATE_FREEWHEEL_INIT | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_INIT_STEP_5 ((S32)(OPERATE_STATE_STEP5   | OPERATE_STATE_FREEWHEEL_INIT | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_FREEWHEEL_G1_NA      ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_FREEWHEEL_G1 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_G1_STEP_1  ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_FREEWHEEL_G1 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_G1_STEP_2  ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_FREEWHEEL_G1 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_FREEWHEEL_G1_STEP_3  ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_FREEWHEEL_G1 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_PJM_PRODUCING_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PJM_FREEWHEEL_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PJM_PRODUCING_STEP_1 ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PJM_FREEWHEEL_STEP_1 ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PJM_PRODUCING_STEP_2 ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PJM_FREEWHEEL_STEP_2 ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PJM_PRODUCING_STEP_3 ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PJM_FREEWHEEL_STEP_3 ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_PITCH_LUB | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_PBT_PRODUCING_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_FREEWHEEL_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_PRODUCING_STEP_1 ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_FREEWHEEL_STEP_1 ((S32)(OPERATE_STATE_STEP1   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_PRODUCING_STEP_2 ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_FREEWHEEL_STEP_2 ((S32)(OPERATE_STATE_STEP2   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_PRODUCING_STEP_3 ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_FREEWHEEL_STEP_3 ((S32)(OPERATE_STATE_STEP3   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_PRODUCING_STEP_4 ((S32)(OPERATE_STATE_STEP4   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_PBT_FREEWHEEL_STEP_4 ((S32)(OPERATE_STATE_STEP4   | OPERATE_STATE_PITCH_BATT_TEST | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_PITCH_SERV_TEST      ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_PITCH_SERV_TEST | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_GRID_CONNECT_G1      ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_GRIDCONNECT_G1 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_OPERATION_G1         ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_OPERATION_G1   | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_LVRT_NA              ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_LVRT | TURBINE_STATUS_PRODUCING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_FREEWHEEL_G1G1       ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_FREEWHEEL_G1G1 | TURBINE_STATUS_PRODUCING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))
#define OPERATE_STATE_UNION_TORQUE_TABLE         ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_TORQUE_TABLE_CHANGE | TURBINE_STATUS_PRODUCING | OPERATE_STATE_BRAKE_PROG_NOT_ACTIVE))

#define OPERATE_STATE_UNION_BP_50_PRODUCING_NA   ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_50 | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_50_STOPPED_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_50 | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_50_FREEWHEEL_NA   ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_50 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_ACTIVE))

#define OPERATE_STATE_UNION_BP_70_PRODUCING_NA   ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_70 | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_70_STOPPED_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_70 | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_70_FREEWHEEL_NA   ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_70 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_ACTIVE))

#define OPERATE_STATE_UNION_BP_99_STOPPED_NA     ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_99 | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_99_FREEWHEEL_NA   ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_99 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_ACTIVE))

#define OPERATE_STATE_UNION_BP_199_PRODUCING_NA  ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_199 | TURBINE_STATUS_PRODUCING    | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_199_STOPPED_NA    ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_199 | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_199_FREEWHEEL_NA  ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_199 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_ACTIVE))

#define OPERATE_STATE_UNION_BP_200_STOPPED_NA    ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_200 | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_200_FREEWHEEL_NA  ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_200 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_ACTIVE))

#define OPERATE_STATE_UNION_BP_210_STOPPED_NA    ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_210 | TURBINE_STATUS_STOPPED      | OPERATE_STATE_BRAKE_PROG_ACTIVE))
#define OPERATE_STATE_UNION_BP_210_FREEWHEEL_NA  ((S32)(OPERATE_STATE_STEP_NA | OPERATE_STATE_BP_210 | TURBINE_STATUS_FREEWHEELING | OPERATE_STATE_BRAKE_PROG_ACTIVE))

//---------------------------------------------------------------------

#define GET_OPERATE_STATE(STATE_UNION)  ((STATE_UNION) & OPERATE_STATE_NAME_MASK)
#define GET_OPERATE_STEP(STATE_UNION)   ((STATE_UNION) & OPERATE_STATE_STEP_MASK)
#define GET_OPERATE_STATUS(STATE_UNION) ((STATE_UNION) & TURBINE_STATUS_MASK)

//_____________________________________________________________________
//                              Brake
typedef enum _BRAKE_SERVICE_MODE_t
{
    BRAKE_SERVICE_MODE_AUTO    = 0,
    BRAKE_SERVICE_MODE_MANUAL
} BRAKE_SERVICE_MODE_t;

// Mechanical braking control
typedef enum _BRAKE_CONTROL_MODE_t
{
    BRAKE_CONTROL_RELEASE = 0,              // No braking
    BRAKE_CONTROL_APPLY = 1,                    // Apply brakes according to algorithm (Low/High Torque)
    BRAKE_CONTROL_APPLY_LOW_TORQUE,         // Apply brakes with low torque
    BRAKE_CONTROL_APPLY_HIGH_TORQUE,        // Apply brakes with high torque
    BRAKE_CONTROL_ERROR
} BRAKE_CONTROL_MODE_t;

// Mechanical braking states
typedef enum _BRAKE_STATE_t
{
    BRAKE_STATE_RELEASED = 0,
    BRAKE_STATE_APPLIED,
    BRAKE_STATE_APPLIED_ERR
} BRAKE_STATE_t;

#define BRAKE_STATUS_TEXT_APPLIED        "Applied"
#define BRAKE_STATUS_TEXT_RELEASED       "Released"

//_____________________________________________________________________
//                               MDS
/*
 * State machine description.
 *
 * The MDS statemachine consists of states and modes. Mode are superior to state.
 * Mode defines how the MDS are running. State defines wether MDS are entering, leaving, or
 * running the actual mode.
 *
 * States:
 * - Ready:         Ready to switch to next mode. Switches mode if another more are either requested or previous stored.
 * - Enter:         Entering the mode, not running yet. Will switch to state running when finished entering.
 * - Running:       Running the mode. Staying in this mode until another mode are requested.
 * - Leave:         Leaving mode, not running anymore. Will switch to state ready when finished leaving.
 *
 * Modes:
 * - Safety:        Pitching at full speed to safety position.
 * - Operate:       Normal operate mode for MDS. MDS are pitching to setpoint, monitors and handles errors.
 * - Service:       Manual setpoint, or manual pitch the blades.
 * - Batterytest1:  Testing the batteries.
 * - Batterytest2:  Testing the batteries.
 * - Batterytest3:  Testing the batteries.
 * - Test:          Internal testmode.
 * - Simulate:      Loops setpoints back as actual pitch angle. MDS hw not needed.
 *
 */
typedef enum _MDS_STATE_t
{
    STATE_READY = 0,
    STATE_ENTER,
    STATE_RUNNING,
    STATE_LEAVE,
    NUMBER_STATES
} MDS_STATE_t, MDS_State_t;

typedef enum _MDS_MODE_t
{
    MODE_SAFETY = 0,
    MODE_OPERATE,
    MODE_SERVICE,
    MODE_BATTERYTEST1,
    MODE_BATTERYTEST2,
    MODE_BATTERYTEST3,
    MODE_TEST,
    MODE_SIMULATE,
    NUMBER_MODES,
    MODE_NONE
} MDS_MODE_t, MDS_Mode_t;
//_____________________________________________________________________
//                               Converter
#define CNV_UNIT_CNT 4 //sizeof(CNV_UNITS_t)

#define CNV_TYPE_FULLPOWER      ((S32)0)
#define CNV_TYPE_DFIG           ((S32)1)

// Inverter Service/Auto
typedef enum _CNV_MODE_SERVICE_t
{
    CNV_MODE_AUTO       = 0,
    CNV_MODE_SERVICE_1, //service control word
    CNV_MODE_SERVICE_2, //service run
    CNV_MODE_SERVICE_3  //config converter
} CNV_MODE_SERVICE_t;

//// Inverter Control
//typedef enum _CNV_CONTROL_t
//{
//    CNV_CTRL_EMERGENCY_STOP = 0,
//    CNV_CTRL_STOP           = 1,
//
//    CNV_CTRL_CONFIG,
//
//    CNV_CTRL_CHECK_INSULATION,
//    CNV_CTRL_CONNECT_GS,
//    CNV_CTRL_START_GS,
//    CNV_CTRL_CONNECT_MS,
//	CNV_CTRL_START_MS,
//
//    CNV_CTRL_RUN,
//
//    CNV_CTRL_STOP_MS
//} CNV_CONTROL_t;

//// Inverter Status
//// used only for FeCon Converter object compatibility
//typedef enum _INVERTER_STATUS_t
//{
//    INVERTER_STATUS_COMMERROR = 0,
//    INVERTER_STATUS_TRIPPED,
//    INVERTER_STATUS_CANOPENEMCY,
//    INVERTER_STATUS_ERROR,
//    INVERTER_STATUS_NOTREADY,
//    INVERTER_STATUS_LVRT,
//    INVERTER_STATUS_WARNING,
//    INVERTER_STATUS_HEATINGREQUEST,
//    INVERTER_STATUS_REMOTE,
//    INVERTER_STATUS_REPEATEDERROR,
//    INVERTER_STATUS_EMERGENCYSTOP,
//
//    INVERTER_STATUS_STARTCHECK_COOLHEATSYS = 100,
//    INVERTER_STATUS_STARTCHECK_TEMPCONDITIONS,
//    INVERTER_STATUS_STARTCHECK_NOTREADY,
//
//    INVERTER_STATUS_RDYON,
//
//    INVERTER_STATUS_CHARGING = 200,
//    INVERTER_STATUS_CHARGING_TIMEOUT,
//
//    INVERTER_STATUS_GRIDCONNECT = 250,
//    INVERTER_STATUS_GRIDCONNECTED,
//
//    INVERTER_STATUS_GRIDSIDE_STOP = 300,
//    INVERTER_STATUS_GRIDSIDE_START,
//    INVERTER_STATUS_GRIDSIDE_OFF,
//    INVERTER_STATUS_GRIDSIDE_ON,
//    INVERTER_STATUS_GRIDSIDE_TIMEOUT,
//
//    INVERTER_STATUS_ROTORSIDE_STOP = 400,
//    INVERTER_STATUS_ROTORSIDE_START,
//    INVERTER_STATUS_ROTORSIDE_OFF,
//    INVERTER_STATUS_ROTORSIDE_ON,
//    INVERTER_STATUS_ROTORSIDE_TIMEOUT,
//
//    INVERTER_STATUS_PRODUCTION = 500,
//	INVERTER_STATUS_OK,
//	INVERTER_STATUS_DISABLE
//} INVERTER_STATUS_t;

//typedef enum _CNV_STATE_t
//{
//    CNV_DISABLED                = 0,
//    CNV_CONFIGURATION           = 1,
//    CNV_INACTIVE                = 2,
//    CNV_CHECK_INSULATION        = 3,
//	CNV_DISCONNECT_GRID         = 4,
//	CNV_STOP_GRID               = 5,
//    CNV_CONNECT_GRID            = 6,
//    CNV_START_GRID              = 7,
//	CNV_DISCONNECT_GENERATOR	= 8,
//	CNV_STOP_GENERATOR          = 9,
//    CNV_CONNECT_GENERATOR       = 10,
//    CNV_START_GENERATOR         = 11,
//    CNV_PRODUCTION              = 12,
//	CNV_MOTOR_RUNNING			= 13
//} CNV_STATE_t;

typedef enum _CNV_STATE_t
{
    CNV_DISABLED               = 0,
    CNV_READYTOSTART           = 1,
    CNV_FAULT                  = 2,
    CNV_EM_STOP                = 3,
    //CNV_FAST_STOP              = 4,
    CNV_NOT_READY              = 5,
    CNV_STOP                   = 6,

    CNV_GRID_DISCONNECTING     = 10,
    CNV_GRID_CONNECTING        = 11,
    CNV_GRID_CONNECTED         = 12,

    CNV_GRID_STOPPING          = 20,
    CNV_GRID_STARTING          = 21,
    CNV_GRID_RUNNING           = 22,

    CNV_GEN_DISCONNECTING      = 30,
    CNV_GEN_CONNECTING         = 31,
    CNV_GEN_CONNECTED          = 32,

    CNV_GEN_STOPPING           = 40,
    CNV_GEN_STARTING           = 41,
    CNV_GEN_RUNNING            = 42,

    CNV_PRODUCTION             = 100,
    CNV_FRT                    = 101,

    CNV_MOTOR_RUNNING			= 110
} CNV_STATE_t;

typedef enum _Cnv_ErrorType_t
{
    CNV_OK,
    CNV_UNDERVOLT_ERR,
    CNV_ERR,
} Cnv_ErrorType_t;
//_____________________________________________________________________
//                    Heating/Cooling for Inverter
typedef enum _INVERTER_ENVIRONMENT_STATUS_t
{
    INVERTER_ENV_STATUS_ERROR = 0,
    INVERTER_ENV_STATUS_OK,
} INVERTER_ENVIRONMENT_STATUS_t;

//_____________________________________________________________________
//                           Rotor Control
// Rotor Lock states
typedef enum _ROTOR_LOCK_STATE_t
{
    ROTOR_LOCK_STATE_RELEASED = 0,
    ROTOR_LOCK_STATE_LOCKED,
    ROTOR_LOCK_STATE_ERROR
} ROTOR_LOCK_STATE_t;

#define BRAKE_STATE_TEXT_APPLIED        "Locked"
#define BRAKE_STATE_TEXT_RELEASED       "Released"

//_____________________________________________________________________
//                           Blade Control

// Blade Control Mode
typedef enum _BLADE_CONTROL_MODE_t
{
    BLADE_CONTROL_MODE_STOP1 = 0,
    BLADE_CONTROL_MODE_STOP2,
    BLADE_CONTROL_MODE_STOP3,

    BLADE_CONTROL_MODE_INIT1 = 10,
    BLADE_CONTROL_MODE_INIT2,
    BLADE_CONTROL_MODE_INIT3,

    BLADE_CONTROL_MODE_SELFTEST      = 20,
    BLADE_CONTROL_MODE_SELFTEST_SKIP = 25,

    BLADE_CONTROL_MODE_RUNMODE1 = 30,
    BLADE_CONTROL_MODE_RUNMODE2,
    BLADE_CONTROL_MODE_RUNMODE3,
    BLADE_CONTROL_MODE_RUNMODE4,
    BLADE_CONTROL_MODE_RUNMODE5,

    BLADE_CONTROL_MODE_RESET = 70

} BLADE_CONTROL_MODE_t;

// Blade Control State
typedef enum _BLADE_CONTROL_STATE_t
{
    BLADE_CONTROL_STATE_UNDEFINED = 0,
    BLADE_CONTROL_STATE_RESET,
    BLADE_CONTROL_STATE_DISABLE,
    BLADE_CONTROL_STATE_SHUTDOWN,
    BLADE_CONTROL_STATE_SWITCH_ON,
    BLADE_CONTROL_STATE_OPER_ENABLE
} BLADE_CONTROL_STATE_t;

// Blade Control Status
typedef enum _BLADE_CONTROL_STATUS_t
{
    BLADE_CONTROL_STATUS_STOPPING1 = 0,
    BLADE_CONTROL_STATUS_STOPPING2,

    BLADE_CONTROL_STATUS_STOPPED1 = 20,
    BLADE_CONTROL_STATUS_STOPPED2,

    BLADE_CONTROL_STATUS_INIT_RUN = 30,
    BLADE_CONTROL_STATUS_INIT_DONE,

    BLADE_CONTROL_STATUS_SELFTEST_RUN  = 40,
    BLADE_CONTROL_STATUS_SELFTEST_DONE = 45,
    BLADE_CONTROL_STATUS_SELFTEST_STEP_ERR,

    BLADE_CONTROL_STATUS_LVRT_ACTIVE  = 50,
    BLADE_CONTROL_STATUS_PITCHJOGMOVE = 60,

    BLADE_CONTROL_STATUS_RESET_RUN  = 70,
    BLADE_CONTROL_STATUS_RESET_DONE = 75,

    BLADE_CONTROL_STATUS_READY = 90,
    BLADE_CONTROL_STATUS_NOT_READY,

    BLADE_CONTROL_STATUS_ERROR_BC = 100,

    BLADE_CONTROL_STATUS_OPERATION1 = 120,
    BLADE_CONTROL_STATUS_OPERATION2,
    BLADE_CONTROL_STATUS_OPERATION3,
    BLADE_CONTROL_STATUS_OPERATION4,

    BLADE_CONTROL_STATUS_REQUEST_ERROR = 200

} BLADE_CONTROL_STATUS_t;

// Blade Control Selftest Status
typedef enum _BLADE_CONTROL_STATUS_SELFTEST_t
{
    BLADE_CONTROL_STATUS_ST_1 = 1,
    BLADE_CONTROL_STATUS_ST_2,
    BLADE_CONTROL_STATUS_ST_3,
    BLADE_CONTROL_STATUS_ST_DONE,
    BLADE_CONTROL_STATUS_ST_1_FAILED,
    BLADE_CONTROL_STATUS_ST_2_FAILED,
    BLADE_CONTROL_STATUS_ST_3_FAILED
} BLADE_CONTROL_STATUS_SELFTEST_t;
//_____________________________________________________________________
// Pitch modes
#define PITCH_MODE_AUTO           ((U8)0)
#define PITCH_MODE_MANUAL         ((U8)1)
#define PITCH_MODE_ESTOP          ((U8)2)

#define PITCH_IF_STOP             ((U8)1)
#define PITCH_IF_SERVICE          ((U8)2)
#define PITCH_IF_EMERGENCY        ((U8)3)
#define PITCH_IF_OPERATION        ((U8)4)

#define PITCH_PID_POWER_ENABLE    ((U8)0)
#define PITCH_PID_POWER_DISABLE   ((U8)1)

//_____________________________________________________________________
// Rotation Speed Control

#define RSC_ROTATION_PRESENT      ((U8)0)
#define RSC_ROTATION_ABSENT       ((U8)1)

//_____________________________________________________________________
// WTG type defines
/*#define WTG_STALL_REGULATED       ((U8)0)
#define WTG_ACTIVE_POWER_CONTROL  ((U8)1)
#define WTG_WRONG_TYPE            ((U8)2)*/

//_____________________________________________________________________
//                             Library

#define ALIBRARY_NAME_LENGTH       ((U8)12)

#define ALIBRARY_INVERT_ENABLE     ((U8)1)
#define ALIBRARY_INVERT_DISABLE    ((U8)0)

#endif

// Pitch and Torque Controller states
#define PAT_STATE_STOPNORMAL     0
#define PAT_STATE_STOPTORQUE     1
#define PAT_STATE_STOPFAST       2
#define PAT_STATE_STOPIMMEDIATE  3
#define PAT_STATE_STOPPED        4
#define PAT_STATE_LOWWIND        5
#define PAT_STATE_STARTUP        6
#define PAT_STATE_RAMPUP         7
#define PAT_STATE_BELOWRATED     8
#define PAT_STATE_RATEDSPEED     9
#define PAT_STATE_RATEDPOWER    10
#define PAT_STATE_LIMITED       11
#define PAT_STATE_PITCHMOVE     12
#define PAT_STATE_OVERSPEED     13
#define PAT_STATE_NACACCEL      14
#define PAT_STATE_FREEWHEEL     15

//______________________________________________________________________

#define INVERTER_STOP_MODULATION  20
#define INVERTER_STOP_G_INV_SIDE  30

//Operate Modes
#define OPERMODE_RUN_AUTO      0
#define OPERMODE_RUN_SERVICE   1
#define OPERMODE_SERVICE       2
