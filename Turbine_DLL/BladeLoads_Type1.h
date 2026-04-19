//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2017 Mita-Teknik.                         
// This software may only be used with the Controllers delivered by Mita-Teknik  
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:8.1$                                                         
// $PEPTOOL file version:103$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: 2015/03/13 16:05:14 $                                                  
// $Author: MITA\ihn $                                                           
// $RCSfile: BladeStrainGaugeSystem_MT_Type1.h,v $                               
// $Revision: 1.7 $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_BLADELOADS_TYPE1_H
#define FILE_BLADELOADS_TYPE1_H

#include <lib_main.h>


// ----------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ----------------------------------------------------------------------
#define PR_P_NUM 12608
#define BSGS_SCANTIME   100
#define BSGS_IN_PROCESS (1)
#define BSGS_ERROR (-1)
#define BSGS_MAX_SENSORS 8
#define BSGS_MAX_SENSOR_SW 4 /*define max sensor which software can support, must be equal to array size of the multiplexed var.*/
#define defValue (-998)
typedef enum
{
    TEST,
    STAT,
    IDEN,
    REST,
    TIME,
    TIME_CONF,
    DATE,
    DATE_CONF,
    IPAD,
    ACQU_STAR,
    ACQU_STOP,
    GAIN_CONF_CH1,
    GAIN_CONF_CH2,
    GAIN_CONF_CH3,
    GAIN_CH1,
    GAIN_CH2,
    GAIN_CH3,
    THRE_CONF_CH1,
    THRE_CONF_CH2,
    THRE_CONF_CH3,
    THRE_CH1,
    THRE_CH2,
    THRE_CH3,
//    BAND_STAR,
//    BAND_STOP,
//    BAND_WAVE_CONF,
//    BAND_WAVE,
    WAVE_CHAN,
    POWE_CHAN,
//    OSAT_CHAN,
//    OSAT_CONT_STAR,
    WAVE_CONT_STAR,
	CAN_ADDR,
	CAN_ADDR_CONF,
	CAN_BAUD,
	CAN_BAUD_CONF,
	CAN_HRTB,
	CAN_HRTB_CONF
}BSGS_CMD_t;

typedef enum
{
    WM_ERROR = 0,
    WM_READY = 1,
    WM_FREE_ACQ = 2,
    WM_CONT_ACQU = 3,
    WM_WARM_UP = 5,
    WM_UNSUPPORTED_STATE
}WM_State_t;

typedef enum
{
    BSGS_READY = 0,
    BSGS_SERVICE = 1,
    BSGS_REQ_RESP = 2,
    BSGS_CONTINUOUS = 3,
    BSGS_STARTUP = 4,
    BSGS_ERRORSTATE = 5,
    BSGS_UNSUPPORTED_STATE = 6
}BSGS_State_t;

#define CMD_ACKN ":ACK\r\n"

STATUS Send_CMD_TEST(void);
STATUS Parse_ANS_TEST(char* msg, U16 msg_size);

#define BSGS_CMD_STAT ":STAT?\r\n"
#define BSGS_ANS_STAT ":ACK:%hu\r\n"
STATUS Send_CMD_STAT(void);
STATUS Parse_ANS_STAT(char* msg, U16 msg_size);

#define BSGS_CMD_IDEN ":IDEN?\r\n"
//BSGS_ANS_IDEN ":ACK:<manufacturer>:<Type> <Revision>:<channels>:<model number>:<date stamp>"
#define BSGS_ANS_IDEN ":ACK:%3s %12s:%6s %4s:%2s:%3s %3s %3s %3s:%8s"
//ex.: ":ACK:HBM FiberSensing:FS22WM v0.5:03:046 840 200 432:20150602"
#define BSGS_ANS_IDEN_ARGUMENTS 10
STATUS Send_CMD_IDEN(void);
STATUS Parse_ANS_IDEN(char* msg, U16 msg_size);

#define BSGS_CMD_REST ":REST\r\n"
#define BSGS_ANS_REST ":ACK\r\n"
STATUS Send_CMD_REST(void);
STATUS Parse_ANS_REST(char* msg, U16 msg_size);

#define BSGS_CMD_TIME ":SYST:TIME?\r\n"
#define BSGS_ANS_TIME ":ACK:%s\r\n"
STATUS Send_CMD_TIME(void);
STATUS Parse_ANS_TIME(char* msg, U16 msg_size);

#define BSGS_CMD_TIME_CONF ":SYST:TIME:%H:%M:%S\r\n"
#define BSGS_ANS_TIME_CONF ":ACK\r\n"
STATUS Send_CMD_TIME_CONF(void);
STATUS Parse_ANS_TIME_CONF(char* msg, U16 msg_size);

#define BSGS_CMD_DATE ":SYST:DATE?\r\n"
#define BSGS_ANS_DATE ":ACK:%s\r\n"
STATUS Send_CMD_DATE(void);
STATUS Parse_ANS_DATE(char* msg, U16 msg_size);

#define BSGS_CMD_DATE_CONF ":SYST:DATE:%Y:%m:%d\r\n"
#define BSGS_ANS_DATE_CONF ":ACK\r\n"
STATUS Send_CMD_DATE_CONF(void);
STATUS Parse_ANS_DATE_CONF(char* msg, U16 msg_size);

#define BSGS_CMD_IPAD ":SYST:IPAD:%s:%s\r\n"
#define BSGS_ANS_IPAD ":ACK\r\n"
STATUS Send_CMD_IPAD(void);
STATUS Parse_ANS_IPAD(char* msg, U16 msg_size);

#define BSGS_CMD_ACQU_STAR ":ACQU:STAR\r\n"
#define BSGS_ANS_ACQU_STAR ":ACK\r\n"
STATUS Send_CMD_ACQU_STAR(void);
STATUS Parse_ANS_ACQU_STAR(char* msg, U16 msg_size);


#define BSGS_CMD_ACQU_STOP ":ACQU:STOP\r\n"
#define BSGS_ANS_ACQU_STOP ":ACK\r\n"
STATUS Send_CMD_ACQU_STOP(void);
STATUS Parse_ANS_ACQU_STOP(char* msg, U16 msg_size);

#define BSGS_CMD_GAIN_CONF_CH1 ":ACQU:CONF:GAIN:CHAN:1:%d\r\n"
#define BSGS_ANS_GAIN_CONF_CH1 ":ACK\r\n"
STATUS Send_CMD_GAIN_CONF_CH1(void);
STATUS Parse_ANS_GAIN_CONF_CH1(char* msg, U16 msg_size);

#define BSGS_CMD_GAIN_CONF_CH2 ":ACQU:CONF:GAIN:CHAN:2:%d\r\n"
#define BSGS_ANS_GAIN_CONF_CH2 ":ACK\r\n"
STATUS Send_CMD_GAIN_CONF_CH2(void);
STATUS Parse_ANS_GAIN_CONF_CH2(char* msg, U16 msg_size);

#define BSGS_CMD_GAIN_CONF_CH3 ":ACQU:CONF:GAIN:CHAN:3:%d\r\n"
#define BSGS_ANS_GAIN_CONF_CH3 ":ACK\r\n"
STATUS Send_CMD_GAIN_CONF_CH3(void);
STATUS Parse_ANS_GAIN_CONF_CH3(char* msg, U16 msg_size);

#define BSGS_CMD_GAIN_CH1 ":ACQU:CONF:GAIN:CHAN:1?\r\n"
#define BSGS_ANS_GAIN_CH1 ":ACK:%hu\r\n"
STATUS Send_CMD_GAIN_CH1(void);
STATUS Parse_ANS_GAIN_CH1(char* msg, U16 msg_size);


#define BSGS_CMD_GAIN_CH2 ":ACQU:CONF:GAIN:CHAN:2?\r\n"
#define BSGS_ANS_GAIN_CH2 ":ACK:%hu\r\n"
STATUS Send_CMD_GAIN_CH2(void);
STATUS Parse_ANS_GAIN_CH2(char* msg, U16 msg_size);

#define BSGS_CMD_GAIN_CH3 ":ACQU:CONF:GAIN:CHAN:3?\r\n"
#define BSGS_ANS_GAIN_CH3 ":ACK:%hu\r\n"
STATUS Send_CMD_GAIN_CH3(void);
STATUS Parse_ANS_GAIN_CH3(char* msg, U16 msg_size);

#define BSGS_CMD_THRE_CONF_CH1 ":ACQU:CONF:THRE:CHAN:1:%d\r\n"
#define BSGS_ANS_THRE_CONF_CH1 ":ACK\r\n"
STATUS Send_CMD_THRE_CONF_CH1(void);
STATUS Parse_ANS_THRE_CONF_CH1(char* msg, U16 msg_size);

#define BSGS_CMD_THRE_CONF_CH2 ":ACQU:CONF:THRE:CHAN:2:%d\r\n"
#define BSGS_ANS_THRE_CONF_CH2 ":ACK\r\n"
STATUS Send_CMD_THRE_CONF_CH2(void);
STATUS Parse_ANS_THRE_CONF_CH2(char* msg, U16 msg_size);

#define BSGS_CMD_THRE_CONF_CH3 ":ACQU:CONF:THRE:CHAN:3:%d\r\n"
#define BSGS_ANS_THRE_CONF_CH3 ":ACK\r\n"
STATUS Send_CMD_THRE_CONF_CH3(void);
STATUS Parse_ANS_THRE_CONF_CH3(char* msg, U16 msg_size);

#define BSGS_CMD_THRE_CH1 ":ACQU:CONF:THRE:CHAN:1?\r\n"
#define BSGS_ANS_THRE_CH1 ":ACK:%hu\r\n"
STATUS Send_CMD_THRE_CH1(void);
STATUS Parse_ANS_THRE_CH1(char* msg, U16 msg_size);

#define BSGS_CMD_THRE_CH2 ":ACQU:CONF:THRE:CHAN:2?\r\n"
#define BSGS_ANS_THRE_CH2 ":ACK:%hu\r\n"
STATUS Send_CMD_THRE_CH2(void);
STATUS Parse_ANS_THRE_CH2(char* msg, U16 msg_size);

#define BSGS_CMD_THRE_CH3 ":ACQU:CONF:THRE:CHAN:3?\r\n"
#define BSGS_ANS_THRE_CH3 ":ACK:%hu\r\n"
STATUS Send_CMD_THRE_CH3(void);
STATUS Parse_ANS_THRE_CH3(char* msg, U16 msg_size);

// not supported by wind meter
//#define BSGS_CMD_BAND_STAR ":ACQU:CONF:BAND:STAR:A\r\n"
//#define BSGS_ANS_BAND_STAR ":ACK\r\n"
//STATUS Send_CMD_BAND_STAR(void);
//STATUS Parse_ANS_BAND_STAR(char* msg, U16 msg_size);
//
//#define BSGS_CMD_BAND_STOP ":ACQU:CONF:BAND:STOP:A\r\n"
//#define BSGS_ANS_BAND_STOP ":ACK\r\n"
//STATUS Send_CMD_BAND_STOP(void);
//STATUS Parse_ANS_BAND_STOP(char* msg, U16 msg_size);
//
//#define BSGS_CMD_BAND_WAVE_CONF_CH1 ":ACQU:CONF:BAND:WAVE:1:02:%f,%f,%f,%f,%f,%f,%f,%f\r\n"
//#define BSGS_ANS_BAND_WAVE_CONF_CH1 ":ACK\r\n"
//STATUS Send_CMD_BAND_WAVE_CONF_CH1(void);
//STATUS Parse_ANS_BAND_WAVE_CONF_CH1(char* msg, U16 msg_size);
//
//#define BSGS_CMD_BAND_WAVE_CONF_CH2 ":ACQU:CONF:BAND:WAVE:2:02:%f,%f,%f,%f,%f,%f,%f,%f\r\n"
//#define BSGS_ANS_BAND_WAVE_CONF_CH2 ":ACK\r\n"
//STATUS Send_CMD_BAND_WAVE_CONF_CH2(void);
//STATUS Parse_ANS_BAND_WAVE_CONF_CH2(char* msg, U16 msg_size);
//
//#define BSGS_CMD_BAND_WAVE_CONF_CH3 ":ACQU:CONF:BAND:WAVE:3:02:%f,%f,%f,%f,%f,%f,%f,%f\r\n"
//#define BSGS_ANS_BAND_WAVE_CONF_CH3 ":ACK\r\n"
//STATUS Send_CMD_BAND_WAVE_CONF_CH3(void);
//STATUS Parse_ANS_BAND_WAVE_CONF_CH3(char* msg, U16 msg_size);
//
//#define BSGS_CMD_BAND_WAVE ":ACQU:CONF:BAND:WAVE:A?\r\n"
//#define BSGS_ANS_BAND_WAVE ":ACK:%f,%f\r\n"                             /*TODO: template is not finished*/
//STATUS Send_CMD_BAND_WAVE(void);
//STATUS Parse_ANS_BAND_WAVE(char* msg, U16 msg_size);

#define BSGS_CMD_WAVE_CHAN ":ACQU:WAVE:CHAN:A?\r\n"
//#define BSGS_ANS_WAVE_CHAN ":ACK:...."                             /*depends from system configuration*/
STATUS Send_CMD_WAVE_CHAN(void);
STATUS Parse_ANS_WAVE_CHAN(char* msg, U16 msg_size);

#define BSGS_CMD_POWE_CHAN ":ACQU:POWE:CHAN:A?\r\n"
//#define BSGS_ANS_POWE_CHAN ":ACK:....."                             /*depends from system configuration*/
STATUS Send_CMD_POWE_CHAN(void);
STATUS Parse_ANS_POWE_CHAN(char* msg, U16 msg_size);

// not supported by wind meter
//#define BSGS_CMD_OSAT_CHAN ":ACQU:OSAT:CHAN:A?\r\n"
//#define BSGS_ANS_OSAT_CHAN ":ACK:......."                             /*depends from system configuration*/
//STATUS Send_CMD_OSAT_CHAN(void);
//STATUS Parse_ANS_OSAT_CHAN(char* msg, U16 msg_size);


//TODO: not supported
//#define BSGS_CMD_OSAT_CONT_STAR ":ACQU:OSAT:CONT:STAR\r\n"
//#define BSGS_ANS_OSAT_CONT_STAR ":....."                        /*depends from system configuration*/d
//STATUS Send_CMD_OSAT_CONT_STAR(void);
//STATUS Parse_ANS_OSAT_CONT_STAR(char* msg, U16 msg_size);

#define BSGS_CMD_WAVE_CONT_STAR ":ACQU:WAVE:CONT:STAR\r\n"
//#define BSGS_ANS_WAVE_CONT_STAR ":......\r\n"                        /*depends from system configuration*/
STATUS Send_CMD_WAVE_CONT_STAR(void);
STATUS Parse_ANS_WAVE_CONT_STAR(char* msg, U16 msg_size);

//CANOpen cmd
#define BSGS_CMD_CAN_ADDR ":CANO:ADDR?\r\n"
#define BSGS_ANS_CAN_ADDR ":ACK:%hu\r\n"
STATUS Send_CMD_CAN_ADDR(void);
STATUS Parse_ANS_CAN_ADDR(char* msg, U16 msg_size);

#define BSGS_CMD_CAN_ADDR_CONF ":CANO:ADDR:%d\r\n"
#define BSGS_ANS_CAN_ADDR_CONF ":ACK\r\n"
STATUS Send_CMD_CAN_ADDR_CONF(void);
STATUS Parse_ANS_CAN_ADDR_CONF(char* msg, U16 msg_size);

#define BSGS_CMD_CAN_BAUD ":CANO:BAUD?\r\n"
#define BSGS_ANS_CAN_BAUD ":ACK:%hu\r\n"
STATUS Send_CMD_CAN_BAUD(void);
STATUS Parse_ANS_CAN_BAUD(char* msg, U16 msg_size);

#define BSGS_CMD_CAN_BAUD_CONF ":CANO:BAUD:00%d\r\n"
#define BSGS_ANS_CAN_BAUD_CONF ":ACK\r\n"
STATUS Send_CMD_CAN_BAUD_CONF(void);
STATUS Parse_ANS_CAN_BAUD_CONF(char* msg, U16 msg_size);

#define BSGS_CMD_CAN_HRTB ":CANO:HRTB?\r\n"
#define BSGS_ANS_CAN_HRTB ":ACK:%hu\r\n"
STATUS Send_CMD_CAN_HRTB(void);
STATUS Parse_ANS_CAN_HRTB(char* msg, U16 msg_size);

#define BSGS_CMD_CAN_HRTB_CONF ":CANO:HRTB:%d\r\n"
#define BSGS_ANS_CAN_HRTB_CONF ":ACK\r\n"
STATUS Send_CMD_CAN_HRTB_CONF(void);
STATUS Parse_ANS_CAN_HRTB_CONF(char* msg, U16 msg_size);

STATUS BladeLoads_Type1( U8 ModuleState, U8 *DoneState , U32 Interval );


// ----------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ----------------------------------------------------------------------
#define COMM_STS_Disconnected   "Disconnected"
#define COMM_STS_Connecting     "Connecting, please wait..."
#define COMM_STS_Connected      "Connected"
#define COMM_STS_Disconnect     "Disconnect, please wait..."

#define OPER_STATE_Disconnected "Disconnected"
#define OPER_STATE_Start_up     "Start-up"
#define OPER_STATE_Ready        "Ready"
#define OPER_STATE_Service      "Service"
#define OPER_STATE_RequestRespond "Request/Respond"
#define OPER_STATE_WAVE         "WAVE"
#define OPER_STATE_Error        "Error"
#define OPER_STATE_SwitchedOFF  "Switched OFF"
#define OPER_STATE_SwitchedON   "Switched ON"

// ----------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ----------------------------------------------------------------------
extern void InfoMessage(char*, U8);

#endif
