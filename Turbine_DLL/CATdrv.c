//********************************************************************
//
//            Copyright (c) 2006 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date: 2014/03/25 15:37:19 $
// $Author: MITA\ihn $
// $RCSfile: CATdrv.c,v $
// $Revision: 1.7 $
//
//*******************************************************************
#include "CATdrv.h"
#include "CATsetup.h"
#include "CATlib.h"
#include "turbdef.h"
// AppLib header files
#include <Various_t1_v3.h>

// Other defines.
#define SOCKET_CLOSED           -1
#define TRUE                     1
#define FALSE                    0
#define TEST_RECV_TIME           0                       // If set, we suspend until data recevived on OS_Select (without timeout), and write the time suspend if suspended more than <TEST_SELECT_THRESHOLD> ms
#define TEST_RECV_THRESHOLD      100                     // See TEST_SELECT_TIME
#define CBUF_SZ                  UDP_MAX_MSG_SIZE        // Read-buffer size.
#define WRBUF_SZ                 200                     // Write-buffer size.
#define LINELEN                  16                      // In dump of buffer.
#define DUMP_RECV_MSG            0                       // If set, a received messages are dumped on debugport
#define DUMP_BYTES_A_ROW         16                      // Number of bytes in a row (when dumping received messages) must be > 1

// CATDrv.c is also included by EtherCanEmu.c, handle differencies below here
#ifdef EMULATOR
   #undef RECV_TIMEOUT
   #define RECV_TIMEOUT ( (atol(UsrOpts.RecvTimeout) * 1000) / sysconf(_SC_CLK_TCK) )
   #undef TEST_RECV_TIME
   #define TEST_RECV_TIME 0           // Make sure TEST_RECV_TIME is off when compiling to emulator
#endif

typedef int SOCKET_T;

// Abstract: CAT Driver internal data definition.
typedef struct
{
   // Containing info used to connect to Ethernet
   struct addr_struct SendAddr;
   struct addr_struct RecvAddr;

   // Socket connection descriptor towards the EtherCAT module.
   SOCKET_T RecvSocket;                 // Socket for reception
   SOCKET_T SendSocket;                 // Socket for sending
#ifdef __CYGWIN__
   FD_SET SockFdBitMask;
#endif
   // Linear read-buffer.
   U8 RdBuf[UDP_MAX_MSG_SIZE];

   // Linear write-buffer.
   U8 WrBuf[WRBUF_SZ];

   // Stats
   U32 MsgSentSuccessfull;
   U32 MsgSentFailed;
   U32 MsgReceivedSuccessfull;
   U32 MsgReceivedFailed;
   U32 NoSocket;
   U32 IllegalMsgType;
   U32 IllegalMsgUnitId;
   U32 UdpRxBufferOverflow;
   U32 IllegalMsgLength;
} DATA_T;

#ifdef EMULATOR
// Abstract: Hex-dump the contents of the specified, contiguous buffer.
//
static void DumpBuffer(/*In*/ U8 Level, /*In*/ const U8 * buf, /*In*/ int sz)
{
   int i = 0;
   S16 Lvl = Level;

   if ((NULL == buf) || (0 == sz))
   {
      LDEBUG_RAW(Lvl, ("\r\n"));
      return;
   }
   LDEBUG_RAW(Lvl, ("      "));
   for (i = 0; i < sz; i++)
   {
      LDEBUG_RAW(Lvl, ("%3x%s",(0X0FF&buf[i]),((i+1)%LINELEN?",":"\r\n      ")));
   }
   LDEBUG_RAW(Lvl, ("\r\n"));
}
#endif

static STATUS AreIpEqual(struct addr_struct *as1, struct addr_struct *as2)
{
   // Check every U8 in IP address, return false if they dont match
   if (as1->id.is_ip_addrs[0] != as2->id.is_ip_addrs[0]) return FALSE;
   if (as1->id.is_ip_addrs[1] != as2->id.is_ip_addrs[1]) return FALSE;
   if (as1->id.is_ip_addrs[2] != as2->id.is_ip_addrs[2]) return FALSE;
   if (as1->id.is_ip_addrs[3] != as2->id.is_ip_addrs[3]) return FALSE;

   // Ip addresses are equal. return true
   return TRUE;
}

// Waits (forever) for new data to receive on socket.
static STATUS WaitForAndGetNewDatagram(/*In,Out*/ CAT_DRV_T * This, S32 * Rcved, U8 TaskType)
{
   DATA_T * Data = NULL;

#if TEST_RECV_TIME
   time_t StartTime, EndTime;
   StartTime = OS_GetTimeInMs();
#endif
   Data = (DATA_T*)(*This).PrivData;

   // We receive until we get a datagram from the correct EtherCAT
   do
   {
#ifdef __CYGWIN__
      {
         Status = OS_Select(Data->RecvSocket+1, &Data->SockFdBitMask, &(*Data).SockFdBitMask, &(*Data).SockFdBitMask, 10000);
         if (Status != OS_SUCCESS)
         {
            LDEBUG(0, ("select error, retval = %d\r\n", Status));
         }
      }
#endif

		// Disable watchdog while waiting for datagram
      OS_Watchdog_Change_Item (Receive_WD,
                              (UNSIGNED)(WD_MAX_TIME/Wd_Counttime_Receive),  /* MyTime/Duration = count */
		                        1,
		                        (UNSIGNED)WD_DISABLED);

      // Wait (forever) for new datagram to arrive..
      *Rcved = OS_Recv_From (Data->RecvSocket, (char*)Data->RdBuf, /*Unused*/ 0, /*Unused*/ 0, &Data->RecvAddr, /*Unused*/ 0);

		// Enable watchdog again
      OS_Watchdog_Change_Item (Receive_WD,
                              (UNSIGNED)(WD_MAX_TIME/Wd_Counttime_Receive),  /* MyTime/Duration = count */
		                        1,
		                        (UNSIGNED)WD_ENABLED);

#if TEST_RECV_TIME
      EndTime = OS_GetTimeInMs();
      if (EndTime > StartTime+TEST_RECV_THRESHOLD)
      {
         LDEBUG_RAW(0, ("*** Recv waited for %llums from %lu.%lu.%lu.%lu, %d ***\r\n", EndTime-StartTime, (*Data).RecvAddr.id.is_ip_addrs[0], (*Data).RecvAddr.id.is_ip_addrs[1],
                    (*Data).RecvAddr.id.is_ip_addrs[2], (*Data).RecvAddr.id.is_ip_addrs[3], (*Data).RecvAddr.port));
      }
#endif

      // Check for errors
      if (0 == *Rcved)
      {
            AppSystemLog(1, "ERROR: Zero length data on socket");
            AppSystemLog(2, "after successfull recv?!");
            (*Data).MsgReceivedFailed++;
            return ERR_ETHCAT_GENERAL_ERROR;
      }
      else if (0 > *Rcved)
      {

         AppSystemLog(1, "Socket reception failed");
         AppSystemLog(2, "with error code %d", *Rcved);
         (*Data).MsgReceivedFailed++;
         return *Rcved;
      }
      else if (UDP_MAX_MSG_SIZE < *Rcved)
      {
         // Received message bigger than buffer, THIS SHOULD _NOT_ HAPPEN as buffer must be big enough for the
         // biggest UDP message possible. If this happens anyway, data may be overwritten!!!!
         AppSystemLog(1, "CatReceiver: UDP rx-bufferoverflow");
         AppSystemLog(2, "IP: %lu.%lu.%lu.%lu",
                       (*Data).RecvAddr.id.is_ip_addrs[0], (*Data).RecvAddr.id.is_ip_addrs[1],
                       (*Data).RecvAddr.id.is_ip_addrs[2],(*Data).RecvAddr.id.is_ip_addrs[3]);
			AppSystemLog(3, "Only room for %d bytes, read %d bytes", *Rcved, UDP_MAX_MSG_SIZE);
         (*Data).UdpRxBufferOverflow++;
         return ERR_ETHCAT_UDP_RXBUFFEROVERFLOW;
      }

   // If the datagram wasn't from the correct EtherCAT, we wait for the next datagram..
   } while ( !AreIpEqual(&Data->RecvAddr, &Data->SendAddr) );

   // Data arrived successfully
   (*Data).MsgReceivedSuccessfull++;

   return OS_SUCCESS;
}


// Abstract: Interface function.
//
// Notice:
//
//
static STATUS Receive( CAT_DRV_T * This,        /*In,Out*/
                       U8 * MsgSt,              /*Out,Unchanged*/
                       U8 * MsgSM1,             /*Out,Unchanged*/
                       U8 * MsgSM5,             /*Out,Unchanged*/
                       MSG_TYPE_t * MsgType,    /*In,Out*/
                       U8 TaskType )
{
    STATUS  Status;
    DATA_T  *Data       = NULL;
    S32     RcvedBytes  = 0;
    U16     BufSize;

    // Access the private data of "This" object.
    Data = (DATA_T*)(*This).PrivData;

    // If connection isn't ready at the moment, return error
    // Connection is managed by CATReceiver
    if( Data->RecvSocket < 0 )
    {
        (*Data).MsgReceivedFailed++;
        (*Data).NoSocket++;
        LDEBUG(1, ("Attempt to recv but not initialized\r\n"));
        return ERR_ETHCAT_NO_SOCKET;
    }

    // Wait for new data to arrive on the socket.

    Status = WaitForAndGetNewDatagram( This, &RcvedBytes, TaskType );
    if( Status != OS_SUCCESS )
    {
        return Status;
    }

    // Dump received message if DUMP_RECV_MSG  is set

#if DUMP_RECV_MSG
    {
        S32 cnt;
        U16 Msg;

        CopyU16(NETWORK_TO_HOST, (U16*)&Data->RdBuf[0], &Msg);

        LDEBUG_RAW(0, ("Content of type 0x%04x msg, %d bytes:", Msg, RcvedBytes));

        for (cnt=0; cnt<RcvedBytes; cnt++)
        {
            if (cnt%DUMP_BYTES_A_ROW == 0)
            {
                LDEBUG_RAW(0, ("\r\n%02x-%02x:  ", cnt, cnt+(DUMP_BYTES_A_ROW-1)));
            }
            LDEBUG_RAW(0, ("%02x ", Data->RdBuf[cnt]));
        }
        LDEBUG_RAW(0, ("\r\n\n"));
    }
#endif

    // Identify message type and copy received data to ...
    CopyU16( NETWORK_TO_HOST, (U16*)&Data->RdBuf[ 0 ], (U16*)MsgType );

    switch( *MsgType )
    {
        case MSG_SYNC_MANAGER1:
        {
            U8 *Buffer;
            U16 i;
            U8 step = sizeof(U16);

            Buffer = MsgSM1;
            BufSize = MSG_SZ_SYNC_MANAGER1;

            for( i = 0; BufSize > i; i = i + step )
            {
                CopyU16( NETWORK_TO_HOST, (U16*)&Data->RdBuf[ MSG_TYPE_SZ + i ], (U16*)&Buffer[ i ] );
            }
            break;
        }
        case MSG_STATUS:
        {
            U8 *Buffer;
            U8 i;
            U8 step = sizeof(U16);

            Buffer = MsgSt;
            BufSize = MSG_SZ_CNV_ST;

            for( i = 0; BufSize > i; i = i + step )
            {
                CopyU16( NETWORK_TO_HOST, (U16*)&Data->RdBuf[ MSG_TYPE_SZ + i ], (U16*)&Buffer[ i ] );
            }
            break;
        }
        case MSG_SYNC_MANAGER5:
        {
            U8 *Buffer;
            U16 i;
            U8 step = sizeof(U16);

            Buffer = MsgSM5;
            BufSize = MSG_SZ_SYNC_MANAGER5;

            for( i = 0; BufSize > i; i = i + step )
            {
                CopyU16( NETWORK_TO_HOST, (U16*)&Data->RdBuf[ MSG_TYPE_SZ + i ], (U16*)&Buffer[ i ] );
            }
            break;
        }
        default:
        {
            LDEBUG(0, ("Unknown message type: %d\r\n", MsgType));
            (*Data).IllegalMsgType++; // Update stats
            STATUS_LINE_VAR_RETURN_VALUE(ERR_ETHCAT_ILLEGAL_MSG_TYPE);
            break;
        }
    }

    // Check length of received datagram
    if( RcvedBytes != (BufSize + MSG_TYPE_SZ) )
    {
        (*Data).IllegalMsgLength++; // Update stats
        LDEBUG(0, ("IllegalMsgLength: \r\n Type=%d,\r\n Length=%d \r\n", *MsgType, RcvedBytes));

        return (ERR_ETHCAT_ILLEGAL_MSG_LENGTH);
    }

    return OS_SUCCESS;
}

// Abstract: Interface function.
//
static STATUS Send(/*In,Out*/ CAT_DRV_T * This, /*In*/ const MESSAGE_T * MsgData)
{
   STATUS   Status = OS_SUCCESS;
   U16      SendSize;
   DATA_T * Data;

   Data = (DATA_T*)(*This).PrivData;

   // If connection isn't ready at the moment, return error
   // Connection is managed by CATReceiver
   if (Data->SendSocket < 0)
   {
      (*Data).MsgSentFailed++;
      (*Data).NoSocket++;
      LDEBUG(0, ("Attempt to send %d, but not initialized\r\n", MsgData->MsgType));
      return ERR_ETHCAT_NO_SOCKET;
   }

   // Copy data to datagram
   switch (MsgData->MsgType)
   {
      case MSG_SYNC_MANAGER0:
      {
          U16 i     = 0;
          U8  step  = sizeof(U16);

         SendSize = MSG_SZ_SYNC_MANAGER0 + MSG_TYPE_SZ;
         CopyU16(HOST_TO_NETWORK, (U16*)&MsgData->MsgType,           (U16*)&Data->WrBuf[0]);    i += step;

         //Cnv 1
         //Grid-side
		 //U16 test = 0x1234;
		 //CopyU16(HOST_TO_NETWORK, &test, (U16*)&Data->WrBuf[i]);     i += step;
		 //CopyU16(HOST_TO_NETWORK, test, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_ControlWord);

		 CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_ControlWord,                (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_SystemRunning,              (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_ReactiveCurrentCmd,         (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_cosPhiCMD,                  (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_ReactivePowerCmd,           (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_BrakechopperPowerCmd,       (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_TR_PointerPosition,         (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_TR_Control,                 (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_TriggerPosition,            (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_GS_Bitsum_Sync_Manager_0,      (U16*)&Data->WrBuf[i]);     i += step;
         //Machine-side
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_ControlWord,                (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_SystemRunning,              (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Encoder_Offset,				(U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Power_Setpoint,             (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Torque_Setpoint,            (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Cos_Phi,                    (U16*)&Data->WrBuf[i]);     i += step;
         CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Exciter_Current_Setpoint,   (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_TR_PointerPosition,         (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_TR_Control,                 (U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_TriggerPosition,            (U16*)&Data->WrBuf[i]);     i += step;
		 CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Motor_Current_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		 CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Motor_Speed_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		 CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Regulator_Kp,				(U16*)&Data->WrBuf[i]);     i += step;
		 CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Regulator_Ki,				(U16*)&Data->WrBuf[i]);     i += step;
         CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv1_MS_Bitsum_Sync_Manager_0,      (U16*)&Data->WrBuf[i]);     i += step;
         //Cnv 2
        //Grid-side
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_ControlWord,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_SystemRunning,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_ReactiveCurrentCmd,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_cosPhiCMD,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_ReactivePowerCmd,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_BrakechopperPowerCmd,		(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_TR_PointerPosition,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_TR_Control,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_TriggerPosition,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_GS_Bitsum_Sync_Manager_0,		(U16*)&Data->WrBuf[i]);     i += step;
        //Machine-side
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_ControlWord,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_SystemRunning,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Encoder_Offset,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Power_Setpoint,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Torque_Setpoint,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Cos_Phi,						(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Exciter_Current_Setpoint,	(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_TR_PointerPosition,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_TR_Control,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_TriggerPosition,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Motor_Current_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Motor_Speed_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Regulator_Kp,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Regulator_Ki,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv2_MS_Bitsum_Sync_Manager_0,		(U16*)&Data->WrBuf[i]);     i += step;
        //Cnv 3
        //Grid-side
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_ControlWord,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_SystemRunning,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_ReactiveCurrentCmd,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_cosPhiCMD,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_ReactivePowerCmd,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_BrakechopperPowerCmd,		(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_TR_PointerPosition,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_TR_Control,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_TriggerPosition,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_GS_Bitsum_Sync_Manager_0,		(U16*)&Data->WrBuf[i]);     i += step;
        //Machine-side
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_ControlWord,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_SystemRunning,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Encoder_Offset,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Power_Setpoint,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Torque_Setpoint,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Cos_Phi,						(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Exciter_Current_Setpoint,	(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_TR_PointerPosition,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_TR_Control,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_TriggerPosition,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Motor_Current_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Motor_Speed_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Regulator_Kp,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Regulator_Ki,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv3_MS_Bitsum_Sync_Manager_0,		(U16*)&Data->WrBuf[i]);     i += step;
        //Cnv 4
        //Grid-side
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_ControlWord,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_SystemRunning,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_ReactiveCurrentCmd,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_cosPhiCMD,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_ReactivePowerCmd,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_BrakechopperPowerCmd,		(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_TR_PointerPosition,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_TR_Control,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_TriggerPosition,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_GS_Bitsum_Sync_Manager_0,		(U16*)&Data->WrBuf[i]);     i += step;
        //Machine-side
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_ControlWord,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_SystemRunning,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Encoder_Offset,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Power_Setpoint,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Torque_Setpoint,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Cos_Phi,						(U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Exciter_Current_Setpoint,	(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_TR_PointerPosition,			(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_TR_Control,					(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_TriggerPosition,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Motor_Current_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Motor_Speed_Setpoint,		(U16*)&Data->WrBuf[i]);     i += step;
		CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Regulator_Kp,				(U16*)&Data->WrBuf[i]);     i += step;
		CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Regulator_Ki,				(U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager0.Cnv4_MS_Bitsum_Sync_Manager_0,		(U16*)&Data->WrBuf[i]);     i += step;

         break;
      }
      case MSG_SYNC_MANAGER4:
      {
        U16 i     = 0;
        U8  step  = sizeof(U16);

        SendSize = MSG_SZ_SYNC_MANAGER4 + MSG_TYPE_SZ;
        CopyU16(HOST_TO_NETWORK, (U16*)&MsgData->MsgType,           (U16*)&Data->WrBuf[0]);    i += step;

        // Grid-side
        // Sync-Manager 4 � Configuration Write
        // FRT-Parameter
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_LVRT_K_Factor,                    (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_HVRT_K_Factor,                    (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_LVRT_DeadBandVoltage,             (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_HVRT_DeadBandVoltage,             (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_LVRT_UpperLimit,                  (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_HVRT_LowerLimit,                  (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_NominalGridVoltage,               (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_NominalGridFrequency,             (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Time_0,                           (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Time_1,                           (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Time_2,                           (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Time_3,                           (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Time_4,                           (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Time_5,                           (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Amplitude_0,                      (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Amplitude_1,                      (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Amplitude_2,                      (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Amplitude_3,                      (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Amplitude_4,                      (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Amplitude_5,                      (U16*)&Data->WrBuf[i]);     i += step;
        // Parameters for Grid Protecting
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderVoltageLevel_1,              (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderVoltageLevel_2,              (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderVoltageDurationLevel_1,      (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderVoltageDurationLevel_2,      (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverVoltageLevel_1,               (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverVoltageLevel_2,               (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverVoltageDurationLevel_1,       (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverVoltageDurationLevel_2,       (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderFrequencyLevel_1,            (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderFrequencyLevel_2,            (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderFrequencyDurationLevel_1,    (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_UnderFrequencyDurationLevel_2,    (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverFrequencyLevel_1,             (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverFrequencyLevel_2,             (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverFrequencyDurationLevel_1,     (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_OverFrequencyDurationLevel_2,     (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_VectorJump,                       (U16*)&Data->WrBuf[i]);     i += step;
        // Checksum
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.GS_Bitsum_Sync_Manager_4,            (U16*)&Data->WrBuf[i]);     i += step;
        // Machine-side
        // Sync-Manager 4 � Configuration Write
        // Machine Parameters
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Nominal_Power,                    (U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Nominal_Rotation_Speed,           (U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Nominal_Voltage,                  (U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Nominal_Current,                  (U16*)&Data->WrBuf[i]);     i += step;
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Number_of_Pole_Pairs,             (U16*)&Data->WrBuf[i]);     i += step;
        CopyS16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Maximum_Exciter_Current,          (U16*)&Data->WrBuf[i]);     i += step;
        // Encoder Parameters
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Rotary_Encoder_Div,               (U16*)&Data->WrBuf[i]);     i += step;
        // Checksum
        CopyU16(HOST_TO_NETWORK, &MsgData->Msg.MSG_GS_SyncManager4.MS_Bitsum_Sync_Manager_4,            (U16*)&Data->WrBuf[i]);     i += step;

        break;
      }
      default:
      {
         LDEBUG(0, ("Failed to setup TX-frame (type=%i)\n", MsgData->MsgType));
         Data->IllegalMsgType++;                        // Update stats
         return ERR_ETHCAT_ILLEGAL_MSG_TYPE;            // Illegal TX-message, bail out..
         break;
      }
   }

   // Send data
   Status = OS_Send_To(Data->SendSocket, (char*)Data->WrBuf, SendSize, /*Unused*/ 0, &(*Data).SendAddr, /*Unused*/ 0);

   if (Status == SendSize)
   {
      LDEBUG(2, ("Message sent: %u bytes to %lu.%lu.%lu.%lu, %u\n",
                 Status,
                 (*Data).SendAddr.id.is_ip_addrs[0],
                 (*Data).SendAddr.id.is_ip_addrs[1],
                 (*Data).SendAddr.id.is_ip_addrs[2],
                 (*Data).SendAddr.id.is_ip_addrs[3],
                 (*Data).SendAddr.port));
      (*Data).MsgSentSuccessfull++;
   }
   else
   {
      LDEBUG(0, ("Error sending %d bytes to %lu.%lu.%lu.%lu, Status=%i\n",
                 SendSize,
                 (*Data).SendAddr.id.is_ip_addrs[0],
                 (*Data).SendAddr.id.is_ip_addrs[1],
                 (*Data).SendAddr.id.is_ip_addrs[2],
                 (*Data).SendAddr.id.is_ip_addrs[3],
                 Status));
      (*Data).MsgSentFailed++;
   }

   return Status;
}


// Abstract: Interface function.
//
STATUS InitializeConnection(/*In,Out*/ CAT_DRV_T * This, /*In*/ const char * RemoteIpAddr, /*In*/ U16 RemotePortNo, /*In*/ U16 LocalPortNo)
{
   DATA_T             * Data;
   STATUS               Status = OS_SUCCESS;
   U32                  IpValues[4];
   U32                  LocalIp;
   U8                   cnt = 0;
   varid_t              varid;
   struct addr_struct   LocalAddr;

   Data = (DATA_T*)(*This).PrivData;

   // Setup remote server struct for sending
   (*Data).SendAddr.family = OS_FAMILY_IP;         // Internet Protocol
   (*Data).SendAddr.name   = "ETHCATTX";           // Used to show that SendAddr is initialized
   CopyU16(HOST_TO_NETWORK, &RemotePortNo, &(*Data).SendAddr.port);
   if ((Status = sscanf(RemoteIpAddr, "%lu.%lu.%lu.%lu", &IpValues[0], &IpValues[1], &IpValues[2], &IpValues[3])) != 4)
   {  // Illegal IP address
      LDEBUG(0, ("sscanf didn't return 4\r\n"));
      return ERR_ETHCAT_IPADDR_INVALID;
   }
   (*Data).SendAddr.id.is_ip_addrs[0] = IpValues[0];
   (*Data).SendAddr.id.is_ip_addrs[1] = IpValues[1];
   (*Data).SendAddr.id.is_ip_addrs[2] = IpValues[2];
   (*Data).SendAddr.id.is_ip_addrs[3] = IpValues[3];

   // Setup remote server struct for receiving
   (*Data).RecvAddr.family = OS_FAMILY_IP;         // Internet Protocol
   (*Data).RecvAddr.name   = "ETHCATRX";           // Used to show that RecvAddr is initialized
   CopyU16(HOST_TO_NETWORK, &RemotePortNo, &(*Data).RecvAddr.port);
   if ((Status = sscanf(RemoteIpAddr, "%lu.%lu.%lu.%lu", &IpValues[0], &IpValues[1], &IpValues[2], &IpValues[3])) != 4)
   {  // Illegal IP address
      LDEBUG(0, ("sscanf didn't return 4\r\n"));
      return ERR_ETHCAT_IPADDR_INVALID;
   }
   (*Data).RecvAddr.id.is_ip_addrs[0] = IpValues[0];
   (*Data).RecvAddr.id.is_ip_addrs[1] = IpValues[1];
   (*Data).RecvAddr.id.is_ip_addrs[2] = IpValues[2];
   (*Data).RecvAddr.id.is_ip_addrs[3] = IpValues[3];

   // Create a new socket is created for sending UDP
   if ( ((*Data).SendSocket = OS_Socket(OS_FAMILY_IP, OS_TYPE_DGRAM, OS_NONE)) < 0 )
   {
      LDEBUG(0, ("Can't create send socket\r\n"));
      return (*Data).SendSocket;
   }

   // Create a new socket is created for receiving UDP
   if ( ((*Data).RecvSocket = OS_Socket(OS_FAMILY_IP, OS_TYPE_DGRAM, OS_NONE)) < 0 )
   {
      LDEBUG(0, ("Can't create recv socket\r\n"));
      return (*Data).RecvSocket;
   }

   // Set bitmask according to RecvSocket (not neccesary for send socket)
#ifdef __CYGWIN__
   OS_FD_Set((*Data).RecvSocket, &(*Data).SockFdBitMask);
#endif

   // Setup local client struct
   LocalAddr.family = OS_FAMILY_IP;         // Internet Protocol
   LocalAddr.name   = "initialized";        // Used to show that RemoteAddr is initialized
   CopyU16(HOST_TO_NETWORK, &LocalPortNo, &LocalAddr.port);

   Status = OS_VarDB_GetVariableID("WP4000_ETH1_IP_Addr", &varid);
   if (Status != OS_SUCCESS)
   {
      LDEBUG(0, ("Error getting varid for %s from VARDB\r\n", "WP4000_ETH1_IP_Addr"));
      return Status;
   }

   Status = OS_VarDB_ReadVariable(varid, &LocalIp, sizeof(LocalIp), NULL);
   if (Status != OS_SUCCESS)
   {
      LDEBUG(0, ("Error reading %s from VARDB\r\n", "WP4000_ETH1_IP_Addr"));
      return Status;
   }
   LDEBUG(2, ("IP as U32=%d\r\n", LocalIp));

   // Extract IP as 4x1byte from 4byte variable
   for (cnt = 0; cnt < 4; cnt++)
   {
      LocalAddr.id.is_ip_addrs[cnt] = LocalIp % 256;
      LocalIp -= LocalAddr.id.is_ip_addrs[cnt];
      LocalIp /= 256;
   }
   LDEBUG(2, ("IP as 4xU8=%lu.%lu.%lu.%lu\r\n",
              LocalAddr.id.is_ip_addrs[0],
              LocalAddr.id.is_ip_addrs[1],
              LocalAddr.id.is_ip_addrs[2],
              LocalAddr.id.is_ip_addrs[3]));

   // Bind local IP and Port to socket
   Status = OS_Bind(Data->RecvSocket, &LocalAddr, /* unused */ 0);
   if (Status < OS_SUCCESS)
   {
      LDEBUG(0, ("Error binding  %lu.%lu.%lu.%lu, %d to socket %d, status = %d\r\n",
                 LocalAddr.id.is_ip_addrs[0],
                 LocalAddr.id.is_ip_addrs[1],
                 LocalAddr.id.is_ip_addrs[2],
                 LocalAddr.id.is_ip_addrs[3],
                 LocalAddr.port,
                 (*Data).RecvSocket,
                 Status));

      return Status;
   }
   else
   {
      LDEBUG(1, ("Success binding to  %lu.%lu.%lu.%lu, %d to socket %d, status = %d\r\n",
                 LocalAddr.id.is_ip_addrs[0],
                 LocalAddr.id.is_ip_addrs[1],
                 LocalAddr.id.is_ip_addrs[2],
                 LocalAddr.id.is_ip_addrs[3],
                 LocalAddr.port,
                 (*Data).RecvSocket,
                 Status));
   }

   // If requested, print initialization info
#if ETHCAT_EXTRA_DEBUG
   LDEBUG(0, ("\r\nReceive connection:"));
   LDEBUG_RAW(0, ("Socket              %d\r\n", (*Data).RecvSocket));
   LDEBUG_RAW(0, ("addr_struct.family  %d\r\n", (*Data).RecvAddr.family));
   LDEBUG_RAW(0, ("addr_struct.name    %s\r\n", (*Data).RecvAddr.name));
   LDEBUG_RAW(0, ("addr_struct.port    %d\r\n", (*Data).RecvAddr.port));
   LDEBUG_RAW(0, ("addr_struct.ip      %lu.%lu.%lu.%lu\r\n", (*Data).RecvAddr.id.is_ip_addrs[0], (*Data).RecvAddr.id.is_ip_addrs[1], (*Data).RecvAddr.id.is_ip_addrs[2], (*Data).RecvAddr.id.is_ip_addrs[3]));
   LDEBUG_RAW(0, ("Success binding to  %lu.%lu.%lu.%lu, %d, socket %d\r\n", LocalAddr.id.is_ip_addrs[0], LocalAddr.id.is_ip_addrs[1], LocalAddr.id.is_ip_addrs[2], LocalAddr.id.is_ip_addrs[3], LocalAddr.port, (*Data).RecvSocket));

   LDEBUG(0, ("\r\nSend connection:\r\n"));
   LDEBUG_RAW(0, ("Socket              %d\r\n", (*Data).SendSocket));
   LDEBUG_RAW(0, ("addr_struct.family  %d\r\n", (*Data).SendAddr.family));
   LDEBUG_RAW(0, ("addr_struct.name    %s\r\n", (*Data).SendAddr.name));
   LDEBUG_RAW(0, ("addr_struct.port    %d\r\n", (*Data).SendAddr.port));
   LDEBUG_RAW(0, ("addr_struct.ip      %lu.%lu.%lu.%lu\r\n", (*Data).SendAddr.id.is_ip_addrs[0], (*Data).SendAddr.id.is_ip_addrs[1], (*Data).SendAddr.id.is_ip_addrs[2], (*Data).SendAddr.id.is_ip_addrs[3]));
#endif

   return OS_SUCCESS;
}


// Abstract: Interface function.
//
CAT_DRV_T * CatDrvDestruct(/*In,Out*/ CAT_DRV_T * This)
{
   if (This != NULL)
   {
      DATA_T * pData;

      pData = (DATA_T*)(*This).PrivData;
      if (pData != NULL)
      {
         OS_Close_Socket((*pData).SendSocket);
         OS_Close_Socket((*pData).RecvSocket);
         OS_Deallocate_Memory(pData);
      }
      OS_Deallocate_Memory(This);
      This = NULL;
   }
   return This;
}


// Abstract: Interface function.
//
static STATUS ResetStats(/*In,Out*/ CAT_DRV_T * This)
{
   DATA_T * Data;

   Data = (DATA_T*)(*This).PrivData;
   (*Data).MsgSentSuccessfull       = 0;
   (*Data).MsgSentFailed            = 0;
   (*Data).MsgReceivedSuccessfull   = 0;
   (*Data).MsgReceivedFailed        = 0;
   (*Data).NoSocket                 = 0;
   (*Data).IllegalMsgType           = 0;
   (*Data).UdpRxBufferOverflow      = 0;
   (*Data).IllegalMsgLength         = 0;

   return OS_SUCCESS;
}

// Abstract: Interface function.
//
static STATUS GetStats(/*In,Out*/ CAT_DRV_T * This, /*In,Out*/ CAT_DRV_STATS_T * Stats)
{
   DATA_T * Data;

   Data = (DATA_T*)(*This).PrivData;
   Stats->MsgSentSuccessfull     = (*Data).MsgSentSuccessfull;
   Stats->MsgSentFailed          = (*Data).MsgSentFailed;
   Stats->MsgReceivedSuccessfull = (*Data).MsgReceivedSuccessfull;
   Stats->MsgReceivedFailed      = (*Data).MsgReceivedFailed;
   Stats->NoSocket               = (*Data).NoSocket;
   Stats->IllegalMsgType         = (*Data).IllegalMsgType;
   Stats->UdpRxBufferOverflow    = (*Data).UdpRxBufferOverflow;
   Stats->IllegalMsgLength       = (*Data).IllegalMsgLength;

   return OS_SUCCESS;
}

// Abstract: Interface function.
//
static STATUS GetIpAddr(/*In,Out*/ CAT_DRV_T * This, U8 Ip[])
{
   U32      cnt;
   DATA_T * Data;

   Data = (DATA_T*)(*This).PrivData;

   // Checking if InitializeConnection(..) has been executed
   if ((*Data).SendAddr.name == OS_NULL)
   {
      return ERR_ETHCAT_CONNECTION_NOT_INITIALIZED; // Can't return IP, if InitializeConnection(..) has not been executed
   }

   for (cnt = 0; cnt <= 3; cnt++)
   {
      Ip[cnt] = (*Data).SendAddr.id.is_ip_addrs[cnt];
   }

   return OS_SUCCESS;
}


// Abstract: Interface function.
//
CAT_DRV_T * CatDrvConstruct(OS_MEMORY_POOL * MemoryPool)
{
   STATUS      Status;
   CAT_DRV_T * pNew;
   // Allocate the main structure.
   Status = OS_Allocate_Memory(MemoryPool, (void**)&pNew, sizeof(CAT_DRV_T), OS_SUSPEND);
   if (Status == OS_SUCCESS)
   {
      DATA_T * pData;

      // Allocate the private data area.
      Status = OS_Allocate_Memory(MemoryPool, (void**)&pData, sizeof(DATA_T), OS_SUSPEND);
      if (Status == OS_SUCCESS)
      {
         (*pNew).PrivData                 = pData;
         (*pData).RecvSocket              = SOCKET_CLOSED;
         (*pData).SendSocket              = SOCKET_CLOSED;
         (*pData).RecvAddr.name           = OS_NULL;
         (*pData).SendAddr.name           = OS_NULL;
         (*pData).MsgSentSuccessfull      = 0;
         (*pData).MsgSentFailed           = 0;
         (*pData).MsgReceivedSuccessfull  = 0;
         (*pData).MsgReceivedFailed       = 0;
         (*pData).NoSocket                = 0;
         (*pData).IllegalMsgType          = 0;
         (*pData).UdpRxBufferOverflow     = 0;

#ifdef __CYGWIN__
         OS_FD_Init(&(*pData).SockFdBitMask);      // Reset bitmask
#endif

         // Setup function pointers.
         (*pNew).Receive                  = Receive;
         (*pNew).Send                     = Send;
         (*pNew).InitializeConnection     = InitializeConnection;
         (*pNew).GetStats                 = GetStats;
         (*pNew).ResetStats               = ResetStats;
         (*pNew).GetIpAddr                = GetIpAddr;
      }
      else
      {
         // Failed to allocate memory for private data, so we have to deallocate main structure again.
         (STATUS)OS_Deallocate_Memory(pNew);
         pNew = NULL;
      }
   }
   else
   {
       pNew = NULL;
   }
   return pNew;
}
