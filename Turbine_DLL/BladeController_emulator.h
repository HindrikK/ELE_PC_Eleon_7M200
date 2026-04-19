//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2014 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:8.0$                                                         
// $PEPTOOL file version:103$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2014/09/18 20:44:41 $                                                  
// $Author: Hindrik $                                                            
// $RCSfile: BladeController_emulator.h,v $                                      
// $Revision: 1.0 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

#ifndef FILE_BLADECONTROLLER_EMULATOR_H
#define FILE_BLADECONTROLLER_EMULATOR_H

#include <lib_main.h>


#define MAX_NUMBER_OF_MDS_UNITS  3
#define MAX_LEGAL_MODES          MODE_BATTERYTEST3
#define MAX_NUMBER_OF_LREGS      6  // Max registers to read/write at one command
#define LREG_COLLECTION_SIZE     256   // Number of elements in the Logic register

#define NODE_ALL     (0)
#define NODE_MDS1    (1)
#define NODE_MDS2    (2)
#define NODE_MDS3    (3)
#define REG_MDS1     (0)
#define REG_MDS2     (1)
#define REG_MDS3     (2)

#define ITEM_UPDATE_FREE   0
#define ITEM_UPDATE_WAIT   1
#define ITEM_UPDATE_OK     2
#define ITEM_UPDATE_FAILED 3

#define ITEM_LREG_WRITE  1
#define ITEM_LREG_READ   2

#define MDS_LREG_QUEUE_NAME      "MDS_LREG_Q"                                                   // Name of CmdQueue
#define MDS_LREG_QUEUE_ELEMENTS  50                                                             // Number of elements in LregQueue
#define MDS_LREG_QUEUE_DATASIZE  ((sizeof(LregQueueData_t) + 3) / 4)                            // Size of one element in LregQueue
#define MDS_LREG_QUEUE_TOTALSIZE (MDS_LREG_QUEUE_DATASIZE*MDS_LREG_QUEUE_ELEMENTS)              // Total size of LregQueue

//MDS Logical register addresses
#define MDS_LREG_TEST                     0     // 1 reg  // RW // ??
#define MDS_LREG_CONTROL                  1     // 1 reg  // RW // U16
#define MDS_LREG_CONTROL_EX               2     // 1 reg  // RW // U16
#define MDS_LREG_CONTROL_EX_2             3     // 1 reg  // RW // U16
#define MDS_LREG_INDIV_ANGLE              4     // 1 reg  // RW // S16
#define MDS_LREG_STATUS_1                 5     // 2 regs // R  // U16
#define MDS_LREG_STATUS_2                 6     // 2 regs // R  // U16
#define MDS_LREG_MASTER_TIME_LOW          8     // 1 regs // RW // U16
#define MDS_LREG_MASTER_TIME_HIGH         9     // 1 regs // RW // U16
#define MDS_LREG_MAX_PID_SPEED            30    // 1 reg  // RW // U16
#define MDS_LREG_PID_TOLERANCE            40    // 1 reg  // RW // U16
#define MDS_LREG_BATT_MIN_VOLTAGE         64 // 1 reg  // R  // U16
#define MDS_LREG_MODULE_SW_REVISION       79    // 2 regs // R  // U16
#define MDS_LREG_MODULE_SW_REVISION_2     80    // 1 reg  // R  // U16
#define MDS_LREG_BOX_CONFIGURATION        89 // 1 reg  // R  // U16
#define MDS_LREG_EXTERNAL_TEMPERATURE_1   231
#define MDS_LREG_EXTERNAL_TEMPERATURE_2   240
#define MDS_LREG_EXTERNAL_TEMPERATURE_3   244
#define MDS_LREG_BACKUP_SUPPLY_MEASURED   156   // 1 reg  // R  // U16
#define MDS_LREG_BACKUP_SUPPLY_LIMIT      157   // 1 reg  // R  // U16
#define MDS_LREG_BACKUP_SUPPLY_TIME       158   // 1 reg  // R  // U16
#define MDS_LREG_EVENT_HISTORY_ID         160
#define MDS_LREG_EVENT_HISTORY_TICK_LOW   161
#define MDS_LREG_EVENT_HISTORY_TICK_HIGH  162
#define MDS_LREG_FAULT_HISTORY_ID         163
#define MDS_LREG_FAULT_HISTORY_TICK_LOW   164
#define MDS_LREG_FAULT_HISTORY_TICK_HIGH  165
#define MDS_LREG_FAULT_OR_WARNING_1       166   // 7 regs // RW // U16
#define MDS_LREG_FAULT_OR_WARNING_2       167   // 6 regs // RW // U16
#define MDS_LREG_FAULT_OR_WARNING_3       168   // 5 regs // RW // U16
#define MDS_LREG_FAULT_OR_WARNING_4       169   // 4 regs // RW // U16
#define MDS_LREG_FAULT_OR_WARNING_5       170   // 3 regs // RW // U16
#define MDS_LREG_FAULT_OR_WARNING_6       171   // 2 regs // RW // U16
#define MDS_LREG_FAULT_OR_WARNING_7       172   // 1 regs // RW // U16
#define MDS_LREG_FAULT_STATUS_1           173   // 7 regs // R  // U16
#define MDS_LREG_FAULT_STATUS_2           174   // 6 regs // R  // U16
#define MDS_LREG_FAULT_STATUS_3           175   // 5 regs // R  // U16
#define MDS_LREG_FAULT_STATUS_4           176   // 4 regs // R  // U16
#define MDS_LREG_FAULT_STATUS_5           177   // 3 regs // R  // U16
#define MDS_LREG_FAULT_STATUS_6           178   // 2 regs // R  // U16
#define MDS_LREG_FAULT_STATUS_7           179   // 1 reg  // R  // U16
#define MDS_LREG_WARNING_STATUS_1         180   // 7 regs // R  // U16
#define MDS_LREG_WARNING_STATUS_2         181   // 6 regs // R  // U16
#define MDS_LREG_WARNING_STATUS_3         182   // 5 regs // R  // U16
#define MDS_LREG_WARNING_STATUS_4         183   // 4 regs // R  // U16
#define MDS_LREG_WARNING_STATUS_5         184   // 3 regs // R  // U16
#define MDS_LREG_WARNING_STATUS_6         185   // 2 regs // R  // U16
#define MDS_LREG_WARNING_STATUS_7         186   // 1 reg  // R  // U16
#define MDS_LREG_SAFETYTEST_TIME          203   // 1 reg  // R  // S16
#define MDS_LREG_LIVE_DATA_SIG_SEL_0      209   //        // RW // U16
#define MDS_LREG_LIVE_DATA_SIG_SEL_1      210   //        // RW // U16
#define MDS_LREG_LIVE_DATA_SIG_SEL_2      211   //        // RW // U16
#define MDS_LREG_LIVE_DATA_SIG_SEL_3      212   //        // RW // U16
#define MDS_LREG_LIVE_DATA_SIG_SEL_4      213   //        // RW // U16
#define MDS_LREG_LIVE_DATA_SIG_SEL_5      214   //        // RW // U16
#define MDS_LREG_TIME_TICK_LOW            220   // 1 reg  // R  // U16
#define MDS_LREG_TIME_TICK_HIGH           221   // 1 reg  // R  // U16

// MDS Logical register bit patters
#define MDS_USE_BROADCAST_ANGLE                 0x0002 // Bit  1 // Ctrl
#define MDS_USE_INDIVIDUAL_ANGLE                0x0004 // Bit  2 // Ctrl
#define MDS_LOAD_LAST_SAVED                     0x0010 // Bit  4 // Ctrl
#define MDS_LOAD_DEFAULT                        0x0020 // Bit  5 // Ctrl
#define MDS_CLEAR_EVENT_HIST                    0x0080 // Bit  7 // Ctrl
#define MDS_CLEAR_FAULT_HIST                    0x0100 // Bit  8 // Ctrl
#define MDS_FAULT_WARN_RESET                    0x0200 // Bit  9 // Ctrl
#define MDS_SAVE_PERMANENTLY                    0x0400 // Bit 10 // Ctrl
#define MDS_OPEN_SAFETYCHAIN                    0x2000 // Bit 13 // Ctrl
#define MDS_BATTERY_TEST_ENABLED                0x0080 // Bit  7 // Ctrl Ex.
#define MDS_ANGLE_TOL_BRAKE_ENABLE              0x0020 // Bit  5 // Ctrl Ex.
#define MDS_PERMANENTLY_SAVED                   0x2000 // Bit 13 // Ctrl Ex.
#define MDS_STATUS_SC_OUT                       0x0008 // Bit  4 // Status 1 
#define MDS_BATTERY_WARN                        0x0020 // Bit  5 // Reg 182
#define MDS_BATTERY_STOP                        0x0020 // Bit  5 // Reg 175
#define MDS_AUTO_TEST_BATTERY_STOP              0x0080 // Bit  7
#define MDS_BATTERT_TEST_NOT_COMPLETED          0x0100 // Bit  8 //
#define MDS_MASTER_TIME_NOT_RECEIVED            0x0200 // Bit  9
#define MDS_TEMPERATURE_ERROR                   0x0002 // Bit  1

#define MDS_CMD_REG_NODE_SELECT_MASK            0x0038 // Bit 3-5
#define MDS_CMD_REG_NODE_SELECT_R_R_R           0x0000
#define MDS_CMD_REG_NODE_SELECT_WR_R_R          0x0008 // Node 1
#define MDS_CMD_REG_NODE_SELECT_R_WR_R          0x0010 // Node 2
#define MDS_CMD_REG_NODE_SELECT_R_R_WR          0x0020 // Node 3
#define MDS_CMD_REG_NODE_SELECT_WR_WR_R         0x0018 // Node 1 + 2
#define MDS_CMD_REG_NODE_SELECT_R_WR_WR         0x0030 // Node 2 + 3
#define MDS_CMD_REG_NODE_SELECT_WR_R_WR         0x0028 // Node 1 + 3
#define MDS_CMD_REG_NODE_SELECT_WR_WR_WR        0x0038 // Node 1 + 2 + 3

#define MDS_CMD_REG_COUNT_MASK                  0x00C0  // Bit 6-7
#define MDS_CMD_REG_COUNT_1                     0x0000
#define MDS_CMD_REG_COUNT_2                     0x0040  // Bit 6
#define MDS_CMD_REG_COUNT_4                     0x0080  // Bit 7
#define MDS_CMD_REG_COUNT_6                     0x00C0  // Bit 6 + 7


// Queue for Lreg handling
typedef struct
{
   U8  LregActionType;
   U16 LregNodeSelect;
   U16 LregStartAddr;
   U16 LregNoOfRegs;
   U16 LregData[MAX_NUMBER_OF_LREGS];
   U8  *LregUpdated;
   void (*CallbackFunc)(U32 Ref, U8 ItemUpdated);
   U32 CallbackRef;
} LregQueueData_t;


// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

STATUS BladeController_emulator( U8 ModuleState, U8 *DoneState , U32 Interval );

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

extern U16 LregCollection[MAX_NUMBER_OF_MDS_UNITS][LREG_COLLECTION_SIZE];
extern OS_QUEUE LregQueue;

extern STATUS MDS_UpdateRegister(U16 CustomRegister, U16 MDSUnit, U16 Value);
extern void MDS_SetMode_Operate(void);
extern void MDS_SetMode_Safety(void);
extern U32 MDS_GetMDSConnectStatus(U16 MDSUnit);
extern U8 CommunicationError(void);
// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
extern char *AppBackupPosition(void);
#endif

