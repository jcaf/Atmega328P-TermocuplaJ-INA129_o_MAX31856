#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
struct _main_flag
{
    unsigned f20ms:1;
    unsigned newpiece:1;
    unsigned reset:1;
    unsigned process_disp_enable:1;
    unsigned temp_control:1;
    unsigned __a:3;
};

extern volatile struct _main_flag main_flag;

//#define DEBUG_PROCESS //hasta habilitar 2 pines rx/tx

//Output-pins
#define PORTWxRELAY1 PORTC
#define PORTRxRELAY1 PINC
#define CONFIGIOxRELAY1 DDRC
#define PINxRELAY1 2

#define PORTWxRELAY2 PORTC
#define PORTRxRELAY2 PINC
#define CONFIGIOxRELAY2 DDRC
#define PINxRELAY2 3

//Inverted logic for 2-RELAY-MODULE-ARDUINO
//#define RELAY1_ON() 	do{PinTo0(PORTWxRELAY1, PINxRELAY1);}while(0)
//#define RELAY1_OFF() 	do{PinTo1(PORTWxRELAY1, PINxRELAY1);}while(0)
//#define RELAY2_ON() 	do{PinTo0(PORTWxRELAY2, PINxRELAY2);}while(0)
//#define RELAY2_OFF() 	do{PinTo1(PORTWxRELAY2, PINxRELAY2);}while(0)

//
#define RELAY1_ON() 	do{PinTo1(PORTWxRELAY1, PINxRELAY1);}while(0)
#define RELAY1_OFF() 	do{PinTo0(PORTWxRELAY1, PINxRELAY1);}while(0)

#define RELAY2_ON() 	do{PinTo1(PORTWxRELAY2, PINxRELAY2);}while(0)
#define RELAY2_OFF() 	do{PinTo0(PORTWxRELAY2, PINxRELAY2);}while(0)

//deprecated led activity
//#define PORTWxTIMER_ACTV PORTB
//#define PORTRxTIMER_ACTV PINB
//#define CONFIGIOxTIMER_ACTV DDRB
//#define PINxTIMER_ACTV 5


//Input-pins
#define PORTWxNEWPIECE PORTC
#define PORTRxNEWPIECE PINC
#define CONFIGIOxNEWPIECE DDRC
#define PINxNEWPIECE 4

#define PORTWxRESET PORTC
#define PORTRxRESET PINC
#define CONFIGIOxRESET DDRC
#define PINxRESET 5

//
#define TEMPER_MAX 250
#define TEMPER_MIN 0

#define TMINUTES_MAX 999
#define TMINUTES_MIN 0

#endif // MAIN_H_INCLUDED
