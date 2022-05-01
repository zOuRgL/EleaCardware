
 // Header MS232.C - Module de gestion du Master 232 - Elea cardware

 // Contrìle apräs l'envoi d'une trame
 #define ACK		0x06
 #define NACK		0x15

 // Statut
 #define ST_BUZZER	0x01
 #define ST_LED		0x02
 #define ST_CARD	0x04
 #define ST_CARD_ON	0x08

 #define BUZZER_ON	0x11
 #define BUZZER_OFF	0x10

 // Etat de la led verte du lecteur
 #define LED_ON		0x21
 #define LED_OFF	0x20
 #define LED_FAST1	0x23	// Clignotement rapide
 #define LED_FAST2	0x25
 #define LED_FAST3	0x27
 #define LED_NORM       0x29    // Valeur initiale
 #define LED_SLOW1	0x2B
 #define LED_SLOW2      0x2D
 #define LED_SLOW3      0x2F	// Clignotement lent


 // Structure de gestion d'un lecteur

 typedef struct {

		   byte instate;	// Etat

		   char bufferIn[ 128 ];
		   byte posBufferIn;    // Position dans le buffer RX

		}Master232;

