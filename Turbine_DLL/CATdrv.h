//********************************************************************
//
//            Copyright (c) 2006 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date: 2014/03/25 15:37:21 $
// $Author: MITA\ihn $
// $RCSfile: CATdrv.h,v $
// $Revision: 1.6 $
//
//*******************************************************************
#ifndef FILE_CATDRV_H
#define FILE_CATDRV_H

#include <os_lib.h>


//-----------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------

#define MSG_TYPE_SZ             2     // Size of message type in bytes

#define MSG_SZ_CNV_ST           22
#define MSG_SZ_SYNC_MANAGER0    200
#define MSG_SZ_SYNC_MANAGER1    514
#define MSG_SZ_SYNC_MANAGER2    1       //not used, not defined yet //ihn
#define MSG_SZ_SYNC_MANAGER3    1       //not used, not defined yet //ihn
#define MSG_SZ_SYNC_MANAGER4    92
#define MSG_SZ_SYNC_MANAGER5    176
#define MSG_SZ_SYNC_MANAGER6    1       //not used, not defined yet //ihn
#define MSG_SZ_SYNC_MANAGER7    1       //not used, not defined yet //ihn
#define UDP_MAX_MSG_SIZE        1472    // The biggest possible UDP message on Ethernet

//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------
// Abstract: Message types.
//
typedef enum _MSG_TYPE_t
{
    MSG_SYNC_MANAGER0       = 0x00,
    MSG_SYNC_MANAGER1       = 0x01,
    MSG_SYNC_MANAGER2       = 0x02,
    MSG_SYNC_MANAGER3       = 0x03,
    MSG_SYNC_MANAGER4       = 0x04,
    MSG_SYNC_MANAGER5       = 0x05,
    MSG_SYNC_MANAGER6       = 0x06,
    MSG_SYNC_MANAGER7       = 0x07,
    MSG_STATUS              = 0xFF
}MSG_TYPE_t;

typedef enum _MSG_UNIT_ID_t
{
    MSG_UNIT_1  = 0x1,
    MSG_UNIT_2  = 0x2,
    MSG_UNIT_3  = 0x4,
    MSG_UNIT_4  = 0x8
} MSG_UNIT_ID_t;

// Abstract: Message type MSG_ID_GS_SM0.
//
typedef struct _MSG_GS_SYNC_MANAGER0_t
{
   //Cnv 1
   //Grid-side
   U16 Cnv1_GS_ControlWord;
   U16 Cnv1_GS_SystemRunning;
   S16 Cnv1_GS_ReactiveCurrentCmd;
   S16 Cnv1_GS_cosPhiCMD;
   S16 Cnv1_GS_ReactivePowerCmd;
   S16 Cnv1_GS_BrakechopperPowerCmd;
   U16 Cnv1_GS_TR_PointerPosition;
   U16 Cnv1_GS_TR_Control;
   U16 Cnv1_GS_TriggerPosition;
   U16 Cnv1_GS_Bitsum_Sync_Manager_0;
   //Machine-side
   U16 Cnv1_MS_ControlWord;
   U16 Cnv1_MS_SystemRunning;
   S16 Cnv1_MS_Encoder_Offset;
   S16 Cnv1_MS_Power_Setpoint;
   S16 Cnv1_MS_Torque_Setpoint;
   S16 Cnv1_MS_Cos_Phi;
   S16 Cnv1_MS_Exciter_Current_Setpoint;
   U16 Cnv1_MS_TR_PointerPosition;
   U16 Cnv1_MS_TR_Control;
   U16 Cnv1_MS_TriggerPosition;
   S16 Cnv1_MS_Motor_Current_Setpoint;
   S16 Cnv1_MS_Motor_Speed_Setpoint;
   U16 Cnv1_MS_Regulator_Kp;
   U16 Cnv1_MS_Regulator_Ki;
   U16 Cnv1_MS_Bitsum_Sync_Manager_0;
   //Cnv 2
    U16 Cnv2_GS_ControlWord;
    U16 Cnv2_GS_SystemRunning;
    S16 Cnv2_GS_ReactiveCurrentCmd;
    S16 Cnv2_GS_cosPhiCMD;
    S16 Cnv2_GS_ReactivePowerCmd;
    S16 Cnv2_GS_BrakechopperPowerCmd;
    U16 Cnv2_GS_TR_PointerPosition;
    U16 Cnv2_GS_TR_Control;
    U16 Cnv2_GS_TriggerPosition;
    U16 Cnv2_GS_Bitsum_Sync_Manager_0;
    U16 Cnv2_MS_ControlWord;
    U16 Cnv2_MS_SystemRunning;
    S16 Cnv2_MS_Encoder_Offset;
    S16 Cnv2_MS_Power_Setpoint;
    S16 Cnv2_MS_Torque_Setpoint;
    S16 Cnv2_MS_Cos_Phi;
    S16 Cnv2_MS_Exciter_Current_Setpoint;
    U16 Cnv2_MS_TR_PointerPosition;
    U16 Cnv2_MS_TR_Control;
    U16 Cnv2_MS_TriggerPosition;
	S16 Cnv2_MS_Motor_Current_Setpoint;
	S16 Cnv2_MS_Motor_Speed_Setpoint;
	U16 Cnv2_MS_Regulator_Kp;
	U16 Cnv2_MS_Regulator_Ki;
    U16 Cnv2_MS_Bitsum_Sync_Manager_0;
    //Cnv 3
    U16 Cnv3_GS_ControlWord;
    U16 Cnv3_GS_SystemRunning;
    S16 Cnv3_GS_ReactiveCurrentCmd;
    S16 Cnv3_GS_cosPhiCMD;
    S16 Cnv3_GS_ReactivePowerCmd;
    S16 Cnv3_GS_BrakechopperPowerCmd;
    U16 Cnv3_GS_TR_PointerPosition;
    U16 Cnv3_GS_TR_Control;
    U16 Cnv3_GS_TriggerPosition;
    U16 Cnv3_GS_Bitsum_Sync_Manager_0;
    U16 Cnv3_MS_ControlWord;
    U16 Cnv3_MS_SystemRunning;
    S16 Cnv3_MS_Encoder_Offset;
    S16 Cnv3_MS_Power_Setpoint;
    S16 Cnv3_MS_Torque_Setpoint;
    S16 Cnv3_MS_Cos_Phi;
    S16 Cnv3_MS_Exciter_Current_Setpoint;
    U16 Cnv3_MS_TR_PointerPosition;
    U16 Cnv3_MS_TR_Control;
    U16 Cnv3_MS_TriggerPosition;
	S16 Cnv3_MS_Motor_Current_Setpoint;
	S16 Cnv3_MS_Motor_Speed_Setpoint;
	U16 Cnv3_MS_Regulator_Kp;
	U16 Cnv3_MS_Regulator_Ki;
    U16 Cnv3_MS_Bitsum_Sync_Manager_0;
    //Cnv 4
    U16 Cnv4_GS_ControlWord;
    U16 Cnv4_GS_SystemRunning;
    S16 Cnv4_GS_ReactiveCurrentCmd;
    S16 Cnv4_GS_cosPhiCMD;
    S16 Cnv4_GS_ReactivePowerCmd;
    S16 Cnv4_GS_BrakechopperPowerCmd;
    U16 Cnv4_GS_TR_PointerPosition;
    U16 Cnv4_GS_TR_Control;
    U16 Cnv4_GS_TriggerPosition;
    U16 Cnv4_GS_Bitsum_Sync_Manager_0;
    U16 Cnv4_MS_ControlWord;
    U16 Cnv4_MS_SystemRunning;
    S16 Cnv4_MS_Encoder_Offset;
    S16 Cnv4_MS_Power_Setpoint;
    S16 Cnv4_MS_Torque_Setpoint;
    S16 Cnv4_MS_Cos_Phi;
    S16 Cnv4_MS_Exciter_Current_Setpoint;
    U16 Cnv4_MS_TR_PointerPosition;
    U16 Cnv4_MS_TR_Control;
    U16 Cnv4_MS_TriggerPosition;
	S16 Cnv4_MS_Motor_Current_Setpoint;
	S16 Cnv4_MS_Motor_Speed_Setpoint;
	U16 Cnv4_MS_Regulator_Kp;
	U16 Cnv4_MS_Regulator_Ki;
    U16 Cnv4_MS_Bitsum_Sync_Manager_0;
} MSG_GS_SYNC_MANAGER0_t;           //Grid Side Sync-Manager 0

// Abstract: Message type MSG_ID_GS_SM1.
//
typedef struct _MSG_GS_SYNC_MANAGER1_t
{
    //Cnv 1
    U16 Cnv1_GS_StatusWord;
    U16 Cnv1_GS_Heartbeat;
    U8  Cnv1_GS_ErrorByte[8];
    S16 Cnv1_GS_ActivePower_LCU;
    S16 Cnv1_GS_ReactivePower_LCU;
    S16 Cnv1_GS_ApparentPower_LCU;
    S16 Cnv1_GS_BrakeChopperCapacity;
    S16 Cnv1_GS_GridVoltage[3];
    S16 Cnv1_GS_DC_LinkVoltage;
    S16 Cnv1_GS_ConverterCurrent[3];
    S16 Cnv1_GS_PhaseShift[3];
    S16 Cnv1_GS_GridFrequency;
    S16 Cnv1_GS_Heatsink_IGBT[3];
    S16 Cnv1_GS_ControlCard;
    S16 Cnv1_GS_Cabinet;
    S16 Cnv1_GS_Inductor;
    U16 Cnv1_GS_Inputs;
    U16 Cnv1_GS_OutputSettings;
    U16 Cnv1_GS_FRT_Detection;
    U16 Cnv1_GS_FRT_Mode;
    U16 Cnv1_GS_ErrorcounterFRT;
    U16 Cnv1_GS_Bitsum_Sync_Manager_1;
    U16 Cnv1_MS_Statusword;
    U16 Cnv1_MS_Heartbeat;
    U8  Cnv1_MS_ErrorByte[8];
    S16 Cnv1_MS_ActivePower_MCU;
    S16 Cnv1_MS_ReactivePower_MCU;
    S16 Cnv1_MS_ApparentPower_MCU;
    S16 Cnv1_MS_MachineVoltage[3];
    S16 Cnv1_MS_DC_LinkVoltage;
    S16 Cnv1_MS_InverterCurrent[3];
    S16 Cnv1_MS_ExciterCurrent;
    S16 Cnv1_MS_GeneratorFrequency;
    S16 Cnv1_MS_GeneratorRotationSpeed;
    S16 Cnv1_MS_GeneratorRotorPosition;
    S16 Cnv1_MS_Torque;
    S16 Cnv1_MS_InsulationTestvoltage;
    S16 Cnv1_MS_InsulationSignalvoltage;
    S16 Cnv1_MS_Heatsink_IGBT[3];
    S16 Cnv1_MS_ControlCard;
    S16 Cnv1_MS_Inductor;
    U16 Cnv1_MS_Inputs;
    U16 Cnv1_MS_OutputSettings;
    U16 Cnv1_MS_Checksum;
    //Cnv 2
    U16 Cnv2_GS_StatusWord;
    U16 Cnv2_GS_Heartbeat;
    U8  Cnv2_GS_ErrorByte[8];
    S16 Cnv2_GS_ActivePower_LCU;
    S16 Cnv2_GS_ReactivePower_LCU;
    S16 Cnv2_GS_ApparentPower_LCU;
    S16 Cnv2_GS_BrakeChopperCapacity;
    S16 Cnv2_GS_GridVoltage[3];
    S16 Cnv2_GS_DC_LinkVoltage;
    S16 Cnv2_GS_ConverterCurrent[3];
    S16 Cnv2_GS_PhaseShift[3];
    S16 Cnv2_GS_GridFrequency;
    S16 Cnv2_GS_Heatsink_IGBT[3];
    S16 Cnv2_GS_ControlCard;
    S16 Cnv2_GS_Cabinet;
    S16 Cnv2_GS_Inductor;
    U16 Cnv2_GS_Inputs;
    U16 Cnv2_GS_OutputSettings;
    U16 Cnv2_GS_FRT_Detection;
    U16 Cnv2_GS_FRT_Mode;
    U16 Cnv2_GS_ErrorcounterFRT;
    U16 Cnv2_GS_Bitsum_Sync_Manager_1;
    U16 Cnv2_MS_Statusword;
    U16 Cnv2_MS_Heartbeat;
    U8  Cnv2_MS_ErrorByte[8];
    S16 Cnv2_MS_ActivePower_MCU;
    S16 Cnv2_MS_ReactivePower_MCU;
    S16 Cnv2_MS_ApparentPower_MCU;
    S16 Cnv2_MS_MachineVoltage[3];
    S16 Cnv2_MS_DC_LinkVoltage;
    S16 Cnv2_MS_InverterCurrent[3];
    S16 Cnv2_MS_ExciterCurrent;
    S16 Cnv2_MS_GeneratorFrequency;
    S16 Cnv2_MS_GeneratorRotationSpeed;
    S16 Cnv2_MS_GeneratorRotorPosition;
    S16 Cnv2_MS_Torque;
    S16 Cnv2_MS_InsulationTestvoltage;
    S16 Cnv2_MS_InsulationSignalvoltage;
    S16 Cnv2_MS_Heatsink_IGBT[3];
    S16 Cnv2_MS_ControlCard;
    S16 Cnv2_MS_Inductor;
    U16 Cnv2_MS_Inputs;
    U16 Cnv2_MS_OutputSettings;
    U16 Cnv2_MS_Checksum;
    //Cnv 3
    U16 Cnv3_GS_StatusWord;
    U16 Cnv3_GS_Heartbeat;
    U8  Cnv3_GS_ErrorByte[8];
    S16 Cnv3_GS_ActivePower_LCU;
    S16 Cnv3_GS_ReactivePower_LCU;
    S16 Cnv3_GS_ApparentPower_LCU;
    S16 Cnv3_GS_BrakeChopperCapacity;
    S16 Cnv3_GS_GridVoltage[3];
    S16 Cnv3_GS_DC_LinkVoltage;
    S16 Cnv3_GS_ConverterCurrent[3];
    S16 Cnv3_GS_PhaseShift[3];
    S16 Cnv3_GS_GridFrequency;
    S16 Cnv3_GS_Heatsink_IGBT[3];
    S16 Cnv3_GS_ControlCard;
    S16 Cnv3_GS_Cabinet;
    S16 Cnv3_GS_Inductor;
    U16 Cnv3_GS_Inputs;
    U16 Cnv3_GS_OutputSettings;
    U16 Cnv3_GS_FRT_Detection;
    U16 Cnv3_GS_FRT_Mode;
    U16 Cnv3_GS_ErrorcounterFRT;
    U16 Cnv3_GS_Bitsum_Sync_Manager_1;
    U16 Cnv3_MS_Statusword;
    U16 Cnv3_MS_Heartbeat;
    U8  Cnv3_MS_ErrorByte[8];
    S16 Cnv3_MS_ActivePower_MCU;
    S16 Cnv3_MS_ReactivePower_MCU;
    S16 Cnv3_MS_ApparentPower_MCU;
    S16 Cnv3_MS_MachineVoltage[3];
    S16 Cnv3_MS_DC_LinkVoltage;
    S16 Cnv3_MS_InverterCurrent[3];
    S16 Cnv3_MS_ExciterCurrent;
    S16 Cnv3_MS_GeneratorFrequency;
    S16 Cnv3_MS_GeneratorRotationSpeed;
    S16 Cnv3_MS_GeneratorRotorPosition;
    S16 Cnv3_MS_Torque;
    S16 Cnv3_MS_InsulationTestvoltage;
    S16 Cnv3_MS_InsulationSignalvoltage;
    S16 Cnv3_MS_Heatsink_IGBT[3];
    S16 Cnv3_MS_ControlCard;
    S16 Cnv3_MS_Inductor;
    U16 Cnv3_MS_Inputs;
    U16 Cnv3_MS_OutputSettings;
    U16 Cnv3_MS_Checksum;
    //Cnv 4
    U16 Cnv4_GS_StatusWord;
    U16 Cnv4_GS_Heartbeat;
    U8  Cnv4_GS_ErrorByte[8];
    S16 Cnv4_GS_ActivePower_LCU;
    S16 Cnv4_GS_ReactivePower_LCU;
    S16 Cnv4_GS_ApparentPower_LCU;
    S16 Cnv4_GS_BrakeChopperCapacity;
    S16 Cnv4_GS_GridVoltage[3];
    S16 Cnv4_GS_DC_LinkVoltage;
    S16 Cnv4_GS_ConverterCurrent[3];
    S16 Cnv4_GS_PhaseShift[3];
    S16 Cnv4_GS_GridFrequency;
    S16 Cnv4_GS_Heatsink_IGBT[3];
    S16 Cnv4_GS_ControlCard;
    S16 Cnv4_GS_Cabinet;
    S16 Cnv4_GS_Inductor;
    U16 Cnv4_GS_Inputs;
    U16 Cnv4_GS_OutputSettings;
    U16 Cnv4_GS_FRT_Detection;
    U16 Cnv4_GS_FRT_Mode;
    U16 Cnv4_GS_ErrorcounterFRT;
    U16 Cnv4_GS_Bitsum_Sync_Manager_1;
    U16 Cnv4_MS_Statusword;
    U16 Cnv4_MS_Heartbeat;
    U8  Cnv4_MS_ErrorByte[8];
    S16 Cnv4_MS_ActivePower_MCU;
    S16 Cnv4_MS_ReactivePower_MCU;
    S16 Cnv4_MS_ApparentPower_MCU;
    S16 Cnv4_MS_MachineVoltage[3];
    S16 Cnv4_MS_DC_LinkVoltage;
    S16 Cnv4_MS_InverterCurrent[3];
    S16 Cnv4_MS_ExciterCurrent;
    S16 Cnv4_MS_GeneratorFrequency;
    S16 Cnv4_MS_GeneratorRotationSpeed;
    S16 Cnv4_MS_GeneratorRotorPosition;
    S16 Cnv4_MS_Torque;
    S16 Cnv4_MS_InsulationTestvoltage;
    S16 Cnv4_MS_InsulationSignalvoltage;
    S16 Cnv4_MS_Heatsink_IGBT[3];
    S16 Cnv4_MS_ControlCard;
    S16 Cnv4_MS_Inductor;
    U16 Cnv4_MS_Inputs;
    U16 Cnv4_MS_OutputSettings;
    U16 Cnv4_MS_Checksum;
} MSG_GS_SYNC_MANAGER1_t;           //Sync-Manager 1: Status Data

typedef struct _MSG_GS_SYNC_MANAGER4_t
{
    // Grid-side
    // Sync-Manager 4 � Configuration Write
    // FRT-Parameter
    S16 GS_LVRT_K_Factor;
    S16 GS_HVRT_K_Factor;
    S16 GS_LVRT_DeadBandVoltage;
    S16 GS_HVRT_DeadBandVoltage;
    S16 GS_LVRT_UpperLimit;
    S16 GS_HVRT_LowerLimit;
    S16 GS_NominalGridVoltage;
    S16 GS_NominalGridFrequency;
    S16 GS_Time_0;
    S16 GS_Time_1;
    S16 GS_Time_2;
    S16 GS_Time_3;
    S16 GS_Time_4;
    S16 GS_Time_5;
    S16 GS_Amplitude_0;
    S16 GS_Amplitude_1;
    S16 GS_Amplitude_2;
    S16 GS_Amplitude_3;
    S16 GS_Amplitude_4;
    S16 GS_Amplitude_5;
    // Parameters for Grid Protecting
    S16 GS_UnderVoltageLevel_1;
    S16 GS_UnderVoltageLevel_2;
    S16 GS_UnderVoltageDurationLevel_1;
    S16 GS_UnderVoltageDurationLevel_2;
    S16 GS_OverVoltageLevel_1;
    S16 GS_OverVoltageLevel_2;
    S16 GS_OverVoltageDurationLevel_1;
    S16 GS_OverVoltageDurationLevel_2;
    S16 GS_UnderFrequencyLevel_1;
    S16 GS_UnderFrequencyLevel_2;
    S16 GS_UnderFrequencyDurationLevel_1;
    S16 GS_UnderFrequencyDurationLevel_2;
    S16 GS_OverFrequencyLevel_1;
    S16 GS_OverFrequencyLevel_2;
    S16 GS_OverFrequencyDurationLevel_1;
    S16 GS_OverFrequencyDurationLevel_2;
    S16 GS_VectorJump;
    // Checksum
    U16 GS_Bitsum_Sync_Manager_4;
// Machine-side
// Sync-Manager 4 � Configuration Write
    // Machine Parameters
    U16 MS_Nominal_Power;
    U16 MS_Nominal_Rotation_Speed;
    U16 MS_Nominal_Voltage;
    U16 MS_Nominal_Current;
    U16 MS_Number_of_Pole_Pairs;
    S16 MS_Maximum_Exciter_Current;
    // Encoder Parameters
    U16 MS_Rotary_Encoder_Div;
    // Checksum
    U16 MS_Bitsum_Sync_Manager_4;
}MSG_GS_SYNC_MANAGER4_t;

typedef struct _MSG_GS_SYNC_MANAGER5_t
{
    //Cnv 1
    U16 Cnv1_GS_SoftwareVersion;
    U16 Cnv1_GS_ControlCard_ID[4];
    U16 Cnv1_GS_InterfaceCard_ID[4];
    U16 Cnv1_GS_BootloaderVersion;
    U16 Cnv1_GS_Bitsum_Sync_Manager_5;
    U16 Cnv1_MS_SoftwareVersion;
    U16 Cnv1_MS_ControlCard_ID[4];
    U16 Cnv1_MS_InterfaceCard_ID[4];
    U16 Cnv1_MS_BootloaderVersion;
    U16 Cnv1_MS_Bitsum_Sync_Manager_5;
    //Cnv 2
    U16 Cnv2_GS_SoftwareVersion;
    U16 Cnv2_GS_ControlCard_ID[4];
    U16 Cnv2_GS_InterfaceCard_ID[4];
    U16 Cnv2_GS_BootloaderVersion;
    U16 Cnv2_GS_Bitsum_Sync_Manager_5;
    U16 Cnv2_MS_SoftwareVersion;
    U16 Cnv2_MS_ControlCard_ID[4];
    U16 Cnv2_MS_InterfaceCard_ID[4];
    U16 Cnv2_MS_BootloaderVersion;
    U16 Cnv2_MS_Bitsum_Sync_Manager_5;
    //Cnv 3
    U16 Cnv3_GS_SoftwareVersion;
    U16 Cnv3_GS_ControlCard_ID[4];
    U16 Cnv3_GS_InterfaceCard_ID[4];
    U16 Cnv3_GS_BootloaderVersion;
    U16 Cnv3_GS_Bitsum_Sync_Manager_5;
    U16 Cnv3_MS_SoftwareVersion;
    U16 Cnv3_MS_ControlCard_ID[4];
    U16 Cnv3_MS_InterfaceCard_ID[4];
    U16 Cnv3_MS_BootloaderVersion;
    U16 Cnv3_MS_Bitsum_Sync_Manager_5;
    //Cnv 4
    U16 Cnv4_GS_SoftwareVersion;
    U16 Cnv4_GS_ControlCard_ID[4];
    U16 Cnv4_GS_InterfaceCard_ID[4];
    U16 Cnv4_GS_BootloaderVersion;
    U16 Cnv4_GS_Bitsum_Sync_Manager_5;
    U16 Cnv4_MS_SoftwareVersion;
    U16 Cnv4_MS_ControlCard_ID[4];
    U16 Cnv4_MS_InterfaceCard_ID[4];
    U16 Cnv4_MS_BootloaderVersion;
    U16 Cnv4_MS_Bitsum_Sync_Manager_5;
}MSG_GS_SYNC_MANAGER5_t;
typedef struct
{
    U16 Main_DevState;
    U16 Cnv1_2_EK1122_DevState;
    U16 Cnv3_4_EK1122_DevState;
    U16 Cnv1_GS_DevState;
    U16 Cnv1_MS_DevState;
    U16 Cnv2_GS_DevState;
    U16 Cnv2_MS_DevState;
    U16 Cnv3_GS_DevState;
    U16 Cnv3_MS_DevState;
    U16 Cnv4_GS_DevState;
    U16 Cnv4_MS_DevState;
} MSG_CNV_ST_T;


typedef struct
{
    MSG_TYPE_t MsgType;
    union
    {
        MSG_CNV_ST_T                  MSG_CnvSt;
        MSG_GS_SYNC_MANAGER0_t        MSG_GS_SyncManager0;
        MSG_GS_SYNC_MANAGER1_t        MSG_GS_SyncManager1;
        MSG_GS_SYNC_MANAGER4_t        MSG_GS_SyncManager4;
    } Msg;
} MESSAGE_T;


typedef struct
{
   U32 MsgSentSuccessfull;
   U32 MsgSentFailed;
   U32 MsgReceivedSuccessfull;
   U32 MsgReceivedFailed;
   U32 NoSocket;
   U32 IllegalMsgType;
   U32 UdpRxBufferOverflow;
   U32 IllegalMsgLength;
} CAT_DRV_STATS_T;

// CAT Driver interface description.
typedef struct CAT_DRV CAT_DRV_T;
struct CAT_DRV
{
   // Abstract: Initializes data used by Send() and Receive()
   //
   // Notice:
   //   Returns 0 on success.
   //
   STATUS (*InitializeConnection)(CAT_DRV_T * This,            /*In,Out*/
                                  const char * RemoteIpAddr,   /*In*/
                                  U16 RemotePortNo,            /*In*/
                                  U16 LocalPortNo              /*In*/ );


   // Abstract: Read message data transmitted from the server.
   //
   // Notice:
   //   The caller must initialize the "MsgType" argument to one of the four message
   //   types that can be returned by this function.
   //   If "MsgType" is pre-initialized to one of the "MSG_ID_INV_" types, then this
   //   function will return either an Converter Status message or an Converter IO message - or an error.
   //   On return, the "MsgType" field will specify the type of message actually read.
   //
   //   The message data will be located in its designated buffer. The other buffer will
   //   be left unchanged.
   //
   //   Returns OS_SUCCESS (0) on success.
   //
   STATUS (*Receive)(CAT_DRV_T * This,              /*In,Out*/
                     U8 * MsgSt,                    /*Out,Unchanged*/
                     U8 * MsgSM1,                   /*Out,Unchanged*/
                     U8 * MsgSM5,                   /*Out,Unchanged*/
                     MSG_TYPE_t * MsgType,          /*In,Out*/
                     U8 TaskType);


   // Abstract: Send data on already open socket.
   //
   // Notice:
   //   Returns number of bytes sendt,
   //   or error number (<0)
   //   Returns ERR_SOCKET_CLOSED if socket isn't open
   //
   STATUS (*Send)(/*In/Out*/ CAT_DRV_T *This, /*In*/const MESSAGE_T *MsgData);

   // Abstract: Returns message stats
   //
   // Notice:
   //   Returns 0 on success.
   //
   STATUS (*GetStats)(/*In/Out*/ CAT_DRV_T *This, /*In/Out*/ CAT_DRV_STATS_T *Stats);

   // Abstract: Resets message stats to zeroes
   //
   // Notice:
   //   Returns 0 on success.
   //
   STATUS (*ResetStats)(/*In/Out*/ CAT_DRV_T *This);

   // Abstract: Returns current IP-address as U8[4]
   //
   // Notice:
   //    Returns <0 if IP-address is unknown
   STATUS (*GetIpAddr)(/*In/Out*/ CAT_DRV_T *This, U8 Ip[]);

   // Private data.
   void* PrivData;
};



//-----------------------------------------------------------------------
// Public function prototypes
//-----------------------------------------------------------------------

// Abstract: Construct an instance of the EtherCAT driver.
//
CAT_DRV_T * CatDrvConstruct(OS_MEMORY_POOL *MemoryPool);

// Abstract: Destruct the specified instance of the EtherCAT driver.
//
CAT_DRV_T * CatDrvDestruct(/*In/Out*/ CAT_DRV_T* This);


#endif // FILE_CATDRV_H
