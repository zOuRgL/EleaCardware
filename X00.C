
 /* *********************************************************************
	  Fonctions de gestion de ports series … travers X00.SYS
    ********************************************************************* */


 #include <alloc.h>
 #include <conio.h>
 #include <string.h>
 #include <stdio.h>
 #include <fcntl.h>
 #include <dos.h>
 #include <string.h>
 #include <process.h>

 #include "x00.h"




 /* **********************************************************************
     SerialSetPort: Configuration d'un port serie (FNCT X00 : 0 )
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
		  (int)   : Parametres de configuration (voir doc X00)
       Retourne : Rien.
    ********************************************************************** */

 void SerialSetPort( byte port, int parametre )
{
 union REGS reg;

 reg.h.ah = 0;
 reg.x.dx = port;
 reg.h.al = parametre;

 int86( 0x14, &reg, &reg );
}







 /* **********************************************************************
     SerialOpenPort: Ouverture d'un port multiserie a travers X00
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : FALSE si OK sinon TRUE
    ********************************************************************** */

 int SerialOpenPort( byte port )
{
 union REGS reg;

 reg.h.ah = 0x1c;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );

 if ( reg.x.ax == 0x1954 )
    return 0;
 else
    return 1;
}







 /* **********************************************************************
     SerialClosePort: Fermeture d'un port multiserie a travers X00
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Rien
    ********************************************************************** */

 void SerialClosePort( byte port )
{
 union REGS reg;

 reg.h.ah = 0x1d;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );
}







 /* **********************************************************************
     SerialSendChr: Envoi d'un caractŠre dans un port serie
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
		  (int)   : Caractere … envoyer
       Retourne : Rien.
    ********************************************************************** */

 void SerialSendChr( byte port , int chr )
{
 char i;
 union REGS reg;

 reg.h.ah = 1;
 reg.x.dx = port;
 reg.h.al = chr;

 int86( 0x14, &reg, &reg );
}








 /* **********************************************************************
     SerialSendStr: Envoi d'une chaine de caractere dans un port serie
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
		  (char *): Chaine … envoyer
       Retourne : REG.X.AX
    ********************************************************************** */

 int SerialSendStr( byte port , char *str )
{
 char i;
 union REGS reg;
 struct SREGS sreg;

 reg.h.ah = 0x19;
 reg.x.dx = port;
 reg.x.cx = strlen( str );

 sreg.es = FP_SEG( str );
 reg.x.di = FP_OFF( str );

 int86x( 0x14, &reg, &reg, &sreg );

 return reg.x.ax;
}








 /* **********************************************************************
     SerialStatus: Status d'un port multiserie
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Status dans REG.H.AL
    ********************************************************************** */

 int SerialStatus( byte port )
{
 union REGS reg;

 reg.h.ah = 3;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );

 return reg.h.ah;
}







 /* **********************************************************************
     SerialModemStatus: Status d'un modem sur un port multiserie
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Status dans REG.H.AL
    ********************************************************************** */

 int SerialModemStatus( byte port )
{
 union REGS reg;

 reg.h.ah = 3;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );

 return reg.h.al;
}




 /* **********************************************************************
     SerialFlush: Fait un flush des chr restant dans le buffer d'un port
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Rien
    ********************************************************************** */

 void SerialFlush( byte port )
{
 union REGS reg;

 reg.h.ah = 8;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );
}







 /* **********************************************************************
     SerialPurgeOutput: Vide le buffer de sortie d'un port
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Rien
    ********************************************************************** */

 void SerialPurgeOutput( byte port )
{
 union REGS reg;

 reg.h.ah = 0x09;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );
}








 /* **********************************************************************
     SerialPurgeInput: Vide le buffer d'entr‚e d'un port
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Rien
    ********************************************************************** */

 void SerialPurgeInput( byte port )
{
 union REGS reg;

 reg.h.ah = 0x0a;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );
}








 /* **********************************************************************
     SerialInputWait: Saisie d'un caractere sur un port avec attente si VIDE
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Caractere dans REG.H.AL ou -1 si TIMOUT
    ********************************************************************** */

 int SerialInputWait( byte port )
{
 union REGS reg;

 reg.h.ah = 2;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );

 if ( (reg.h.ah & 128) != 128 )
    return reg.h.al;
 else
    return -1;
}







 /* **********************************************************************
     SerialInput: Regarde si un caractere est disponible sur un port
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Caractere dans REG.H.AL ou -1 si VIDE
    ********************************************************************** */

 int SerialInput( byte port )
{
 union REGS reg;

 reg.h.ah = 0x20;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );

 if ( reg.x.ax != 0x0ffff )
    return reg.h.al;
 else
    return -1;
}






 /* **********************************************************************
     ResetComputer: Red‚marrage … froid
    ----------------------------------------------------------------------
     ParamŠtres : Aucun
       Retourne : Rien
    ********************************************************************** */

 void ResetComputer( void )
{
 union REGS reg;

 reg.h.ah = 0x17;
 reg.h.al = 0x0;    // Cold Boot

 int86( 0x14, &reg, &reg );
}






 /* **********************************************************************
     SerialWriteMCR: Reprogramme le MCR d'un port ( registre ‚tat modem )
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
		  (byte)  : Nouveau MCR
       Retourne : Rien.
    ********************************************************************** */

 void SerialWriteMCR( byte port , byte mcr )
{
 union REGS reg;

 reg.h.ah = 0x1F;
 reg.h.al = 0x01;
 reg.x.dx = port;
 reg.h.bl = mcr;

 int86( 0x14, &reg, &reg );

 //return reg.x.ax;
}






 /* **********************************************************************
     SerialReadMCR: lecture du MCR d'un port ( registre ‚tat modem )
    ----------------------------------------------------------------------
     ParamŠtres : (int)   : Num‚ro de port X00 ( 0 … 7 )
       Retourne : Rien.
    ********************************************************************** */

 byte SerialReadMCR( byte port )
{
 union REGS reg;

 reg.h.ah = 0x1F;
 reg.h.al = 0x0;
 reg.x.dx = port;

 int86( 0x14, &reg, &reg );

 return reg.h.bl;
}

