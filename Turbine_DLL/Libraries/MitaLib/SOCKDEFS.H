/*********************************************************************/
/*                                                                   */
/*            Copyright (c) 2001 Mita-Teknik a/s                     */
/*                                                                   */
/*********************************************************************/

/*********************************************************************/
/*                                                                   */
/* FILE NAME                                            VERSION      */
/*                                                                   */
/*      sockdefs.h                                                   */
/*                                                                   */
/* DESCRIPTION                                                       */
/*                                                                   */
/*       This include file will define socket type error return      */
/*       codes, socket options, and socket protocol types.           */
/*                                                                   */
/* AUTHOR     Mita-teknik a/s                                        */
/*                                                                   */
/*********************************************************************/

#ifndef SOCKDEFS_H
#define SOCKDEFS_H

#ifdef          __cplusplus
extern  "C" {                               /* C declarations in C++     */
#endif /* _cplusplus */

/* A generic catch-all for unused parameters. */
#define OS_NONE         0

/* Address family equates */
#define SK_FAM_UNSPEC   0               /* unspecified */
#define SK_FAM_LOCAL    1
#define SK_FAM_UNIX     SK_FAM_LOCAL
#define SK_FAM_IP       2               /* Internet:  UDP, TCP, etc. */
#define SK_FAM_ROUTE    17              /* Internal routing protocol */
#define SK_FAM_LINK     18              /* Link layer interface.     */

/* These equates are for backwards compatability */
#define OS_FAMILY_UNIX SK_FAM_UNIX        /* Unix */
#define OS_FAMILY_IP   SK_FAM_IP          /* Internet       - valid entry */

/* TYPE equates */
#define OS_TYPE_STREAM    0     /* stream Socket             - valid entry */
#define OS_TYPE_DGRAM     1     /* datagram Socket           - valid entry */
#define OS_TYPE_RAW       2     /* raw Socket                - valid entry */
#define OS_TYPE_SEQPACKET 3     /* sequenced packet Socket */
#define OS_TYPE_RDM       4     /* reliably delivered msg Socket */

/* PROTOCOL equates */
#define OS_PROTO_INVALID  0
#define OS_PROTO_TCP      1
#define OS_PROTO_UDP      2
#define OS_PROTO_ICMP     3

/***************************  SOCKET OPTIONS  *****************************/
/* SOCKET OPTION control flags */
#define OS_SETFLAG        1
#define OS_BLOCK          1
#define OS_NO_BLOCK       0

/* PROTOCOL LEVELS */
#define OS_SOCKET_LEVEL   0

/* Levels used in the call to OS_Setsockopt */
#define IPPROTO_IP      0
#define IPPROTO_ICMP    1
#define IPPROTO_IGMP    2
#define IPPROTO_GGP     3
#define IPPROTO_TCP     6
#define IPPROTO_EGP     8
#define IPPROTO_PUP     12
#define IPPROTO_UDP     17
//#define SOL_SOCKET      100    //redefinition

/* Protocol used int call to OS_Socket with a Raw IP socket */
#define IPPROTO_HELLO   63
//#define IPPROTO_RAW     255
#define IPPROTO_OSPF    89


/*
 * Options for use with [gs]etsockopt at the socket level.
 * First word of comment is data type; bool is stored in int.
 */
//#define SO_BROADCAST        1  /* permission to transmit broadcast messages? */ //redefinition

/*
 * Options for use with [gs]etsockopt at the IP level.
 * First word of comment is data type; bool is stored in int.
 */
#define IP_OPTIONS          1    /* buf/ip_opts; set/get IP options */
#define IP_HDRINCL          2    /* int; header is included with data */
//#define IP_TOS              3    /* int; IP type of service and preced. */	//redefinition error
//#define IP_TTL              4    /* int; IP time to live */					//redefinition error
#define IP_RECVOPTS         5    /* bool; receive all IP opts w/dgram */
#define IP_RECVRETOPTS      6    /* bool; receive IP opts for response */
#//define IP_RECVDSTADDR      7    /* bool; receive IP dst addr w/dgram */
#define IP_RETOPTS          8    /* ip_opts; set/get IP options */
//#define IP_MULTICAST_IF     9    /* u_char; set/get IP multicast i/f  */		//redefinition error
//#define IP_MULTICAST_TTL    10   /* u_char; set/get IP multicast ttl */		//redefinition error
//#define IP_MULTICAST_LOOP   11   /* u_char; set/get IP multicast loopback */ //redefinition error
//#define IP_ADD_MEMBERSHIP   12   /* ip_mreq; add an IP group membership */	//redefinition error
//#define IP_DROP_MEMBERSHIP  13   /* ip_mreq; drop an IP group membership */	//redefinition error	

/*******************  SOCKET ERROR CODES  ****************************

 The range for OS NET error codes is -251 to -500.

*/

#define OS_INVALID_PROTOCOL     -251    /*  Invalid network protocol */
#define OS_NO_DATA_TRANSFER     -252    /*  Data was not written/read
                                            during send/receive function */
#define OS_NO_PORT_NUMBER       -253    /*  No local port number was stored
                                            in the socket descriptor */
#define OS_NO_TASK_MATCH        -254    /*  No task/port number combination
                                            existed in the task table */
#define OS_NO_SOCKET_SPACE      -255    /*  The socket structure list was full
                                            when a new socket descriptor was
                                            requested */
#define OS_NO_ACTION            -256    /*  No action was processed by
                                            the function */
#define OS_NOT_CONNECTED        -257    /*  A connection has been closed
                                            by the network.  */
#define OS_INVALID_SOCKET       -258    /*  The socket ID passed in was
                                            not in a valid range.  */
#define OS_NO_SOCK_MEMORY       -259    /*  Memory allocation failed for
                                            internal sockets structure.  */
#define OS_INVALID_ADDRESS      -260    /*  An incomplete address was sent */
#define OS_NO_HOST_NAME         -261    /*  No host name specified in a  */
#define OS_RARP_INIT_FAILED     -262    /*  During initialization RARP failed. */
#define OS_BOOTP_INIT_FAILED    -263    /*  During initialization BOOTP failed. */
#define OS_INVALID_PORT         -264    /*  The port number passed in was
                                            not in a valid range. */
#define OS_NO_BUFFERS           -265    /*  There were no buffers to place */
                                        /*  the outgoing packet in. */
#define OS_NOT_ESTAB            -266    /*  A connection is open but not in
                                            an established state. */
#define OS_WINDOW_FULL          -267    /*  The foreign host's in window is
                                            full. */
#define OS_NO_SOCKETS           -268    /*  No sockets were specified. */
#define OS_NO_DATA              -269    /*  None of the specified sockets were
                                            data ready.  OS_Select. */



/* The following errors are reported by the OS_Setsockopt and OS_Getsockopt
   service calls. */
#define OS_INVALID_LEVEL        -270    /*  The specified level is invalid. */
#define OS_INVALID_OPTION       -271    /*  The specified option is invalid. */
#define OS_INVAL                -272    /*  General purpose error condition. */
#define OS_ACCESS               -273    /*  The attempted operation is not   */
                                        /*  allowed on the  socket           */
#define OS_ADDRINUSE            -274

#define OS_HOST_UNREACHABLE     -275    /*  Host unreachable */
#define OS_MSGSIZE              -276    /*  Packet is to large for interface. */
#define OS_NOBUFS               -277    /*  Could not allocate a memory buffer. */
#define OS_UNRESOLVED_ADDR      -278    /*  The MAC address was not resolved.*/
#define OS_CLOSING              -279    /*  The other side in a TCP connection*/
                                        /*  has sent a FIN */
#define OS_MEM_ALLOC            -280    /* Failed to allocate memory. */
#define OS_RESET                -281
#define OS_DEVICE_DOWN          -282    /* A device being used by the socket has
                                           gone down. Most likely because a PPP
                                           link has been disconnected or a DHCP
                                           IP address lease has expired. */
/* These error codes are returned by DNS. */
#define OS_INVALID_LABEL        -283    /* Indicates a domain name with an
                                           invalid label.                   */
#define OS_FAILED_QUERY         -284    /* No response received for a DNS
                                           Query. */
#define OS_DNS_ERROR            -285    /* A general DNS error status. */
#define OS_NOT_A_HOST           -286    /* The host name was not found. */
#define OS_INVALID_PARM         -287    /*  A parameter has an invalid value. */

#define OS_NO_DNS_SERVER        -288    /* No DNS server has been registered with
                                            the stack. */

/* Error codes for DHCP */
#define OS_DHCP_INIT_FAILED     -289    /*  During initialization DHCP failed. */
#define OS_DHCP_REQUEST_FAILED  -290

/*  Error codes for BOOTP */
#define OS_BOOTP_SEND_FAILED          -291
#define OS_BOOTP_RECV_FAILED          -292
#define OS_BOOTP_ATTACH_IP_FAILED     -293
#define OS_BOOTP_SELECT_FAILED        -294
#define OS_BOOTP_FAILED               -295

#define OS_NO_ROUTE_TO_HOST     -296    /* ICMP Destination Unreachable specific error */
#define OS_CONNECTION_REFUSED   -297    /* ICMP Destination Unreachable specific error */
#define OS_MSG_TOO_LONG         -298    /* ICMP Destination Unreachable specific error */

#define OS_BAD_SOCKETD          -299
#define OS_BAD_LEVEL            -300
#define OS_BAD_OPTION           -301

/* Error Code for NON Blocking  */
#define OS_WOULD_BLOCK          -319


#ifdef          __cplusplus
}
#endif /* _cplusplus */

#endif  /* SOCKDEFS_H */
