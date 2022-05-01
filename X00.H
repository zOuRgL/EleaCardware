
 // Header X00

 #ifndef byte
    typedef unsigned char byte;
 #endif


 // Prototype de fonction

 void SerialSetPort( byte port, int parametre );
 int SerialOpenPort( byte port );
 void SerialClosePort( byte port );
 void SerialSendChr( byte port , int chr );
 int SerialSendStr( byte port , char *str );
 int SerialStatus( byte port );
 int SerialModemStatus( byte port );
 void SerialFlush( byte port );
 void SerialPurgeOutput( byte port );
 void SerialPurgeInput( byte port );
 int SerialInputWait( byte port );
 int SerialInput( byte port );
 void ResetComputer( void );
 void SerialWriteMCR( byte port , byte mcr );
 byte SerialReadMCR( byte port );
