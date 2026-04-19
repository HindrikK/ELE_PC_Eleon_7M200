//********************************************************************
//
//            Copyright (c) 2006 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date: 2013/03/06 07:45:09 $
// $Author: MITA\ihn $
// $RCSfile: CATsetup.h,v $
// $Revision: 1.2 $
//
//*******************************************************************
#ifndef FILE_CATSETUP_H
#define FILE_CATSETUP_H


// ---------------------------------------------------------------------
// This file is used to setup the WP4000 EtherCAT driver's _global_ behaviour
// ---------------------------------------------------------------------

// C O M M U N I C A T I O N   E R R O R H A N D L I N G :
//
// <XX_MAX_RETRIES> represents the number of reception/sending errors (timeouts not included) which must occur in a row before
// the reception/sending error is handled as an error. Hence if <MAX_RETRIES = 1> every reception/sending error is handled as an error,
// a values above 1 means that isolated reception/sending errors are handled as warnings, a value of zero is not allowed.
//
// <RECV_TIMEOUT> is the max time allowed between two receptions, if mores than this time elapses without receiving
// a datagram, we handle this as an error. The timeout is handled as an error _everytime_ a timeout occurs regardless
// the value of <XX_MAX_RETRIES>.
//
// If an error is treated as a warning, a warning message is written in syslog.
//
// If an error is treated as an error, appropriate statuscode is set, an error message is written in syslog and
// we stop sending messages (only recv errors). Thereafter we enter a failstate in which we wait until <FLAWLESS_XX_MSG_DEMAND> have been sent/received successfully, when
// that is done the status code is cleared, a message is written in syslog and we start sending again. The messages received in the fail state
// are not processed.

#define CATDISPATCHER_MAX_RETRIES             3  // If CATDrv::Send() returns error more than MAX_RETRIES times, a statuscode is set and CATDispatcher awaits that CATReceiver fixes the connection
#define CATRECEIVER_MAX_RETRIES               3  // If CATDrv::Receive() returns error more than MAX_RETRIES times, the connection gets disconnected and thereafter reconnected
#define CATRECEIVER_MAX_RETRIES_ERRORMODE     3  // Same as MAX_RETRIES but is used when in errormode (waiting for FLAWLESS_RECEIVE_MSG_DEMAND messages)
#define FLAWLESS_RECEIVE_MSG_DEMAND          10  // If failed to receive in MAX_RETRIES, this amount of messages must be received OK before the statuscode for received OK is set
#define FLAWLESS_SENT_MSG_DEMAND             10  // If failed to send in MAX_RETRIES, this amount of messages must be sent OK before the statuscode for sending OK is set
#define DEFAULT_ETHERCAT_IP_PORT           7236  // IP Port number to be used on EtherCAT
#define DEFAULT_LOCAL_IP_PORT              7236  // IP Port number to be used on EtherCAT
#define RECV_TIMEOUT                        500  // Max ticks to wait for incoming bytes before timeout
#define RECV_TIMEOUT_INITIAL              20000  // Same usage as <RECV_TIMEOUT>, but used only when waiting on the first message from EtherCAT
#define ETHCAT_EXTRA_DEBUG                    0  // Turns on extra debug on debugport
#define RECV_WARNING_TIME                   250  // If more than this ms between reception of two messages, the recv. warning is updated

#endif // FILE_CATSETUP_H
