
typedef struct
{
    unsigned char netadd[4];
    unsigned char nodeadd[6];
    unsigned short socket;
} IPXADDRESS;

typedef struct
{
    unsigned short checksum;
    unsigned short length;
    unsigned char tc;
    unsigned char type;
    IPXADDRESS dest;
    IPXADDRESS source;
} IPXHEADER;

typedef struct
{
    void far *linkaddress;
    void (far *esraddress)();
    unsigned char inuse;
    unsigned char cc;
    unsigned short socket;
    unsigned char workspace[16];
    unsigned char immedaddr[6];
    unsigned short fragcount;
    void far *fragaddr1;
    unsigned short fragsize1;
    void far *fragaddr2;
    unsigned short fragsize2;
} IPXECB;

extern unsigned short reverseword ( unsigned short );
extern unsigned long ipxinit ( void );
// returns:
//      ipxentry, if zero, ipx is not installed
extern unsigned long ipxentry;
extern void ipxgetaddress ( void * );
// ipx far call entry point
extern unsigned short ipxgetmaxpacketsize ( void );
extern unsigned char ipxopensocket ( unsigned char, unsigned short * );
// first argument:
//      socket longevity flag
//          00h the socket will remain open until a Close Socket call or the
//              application terminates
//          01h the socket will remain open until a Close Socket call
// second argument:
//      address to the socket value (little-endian word)
// returns:
//      00h Success
//          the socket value will reflect the open socket (little-endian word)
//      FFh Socket Already Open
//      FEh Socket Table Is Full

extern void ipxclosesocket ( unsigned short );
// argument:
//      socket number (little-endian word)

extern unsigned char ipxlistenforpacket ( IPXECB * );
// argument:
//      receive ECB
// returns:
//      00h Success
//      FFh Listening socket does not exist

extern void ipxsendpacket ( IPXECB * );
// argument:
//      send ECB;
extern void ipxrelenquishcontrol ( void );

