#ifndef KB_H_
#define KB_H_

    #include "../types.h"

    void key_initialization(void);
    void kb_job(void);
    void kb_flush(void);

    //void kb_change_keyDo(const PTRFX_retVOID const *keyDo);
    //void kb_change_keyDo(PTRFX_retVOID *keyDo);
    //void kb_change_keyDo_pgm(PTRFX_retVOID const *  keyDo);

    void kb_processKeyRead_D(void);


    /*
        PORTWxKBCOL_1 PORTWxKBCOL_2 PORTWxKBCOL_3 PORTWxKBCOL_4
    PORTWxKBFIL_1 	1  2  3  4
    PORTWxKBFIL_2 	5  6  7  8
    PORTWxKBFIL_3 	9  10 11 12
    PORTWxKBFIL_4 	13 14 15 16
     */

    #define PORTWxKBFIL_1 		PORTD
    #define PORTRxKBFIL_1 		PIND
    #define CONFIGIOxKBFIL_1 	DDRD
    #define PINxKBFIL_1 		2

    #define PORTWxKBFIL_2 		PORTD
    #define PORTRxKBFIL_2 		PIND
    #define CONFIGIOxKBFIL_2 	DDRD
    #define PINxKBFIL_2 		3

    #define PORTWxKBFIL_3 		PORTD
    #define PORTRxKBFIL_3 		PIND
    #define CONFIGIOxKBFIL_3 	DDRD
    #define PINxKBFIL_3 		4

    #define PORTWxKBFIL_4 		PORTD
    #define PORTRxKBFIL_4 		PIND
    #define CONFIGIOxKBFIL_4 	DDRD
    #define PINxKBFIL_4 		5

    #define PORTWxKBCOL_1 		PORTD
    #define PORTRxKBCOL_1 		PIND
    #define CONFIGIOxKBCOL_1 	DDRD
    #define PINxKBCOL_1 		6

    #define PORTWxKBCOL_2 		PORTD
    #define PORTRxKBCOL_2 		PIND
    #define CONFIGIOxKBCOL_2 	DDRD
    #define PINxKBCOL_2		    7

    #define PORTWxKBCOL_3 		PORTB
    #define PORTRxKBCOL_3 		PINB
    #define CONFIGIOxKBCOL_3 	DDRB
    #define PINxKBCOL_3 		0

    #define PORTWxKBCOL_4 		PORTB
    #define PORTRxKBCOL_4 		PINB
    #define CONFIGIOxKBCOL_4 	DDRB
    #define PINxKBCOL_4 		1

    //////////////////////////////////////
    //kb layout
    #include "ikey.h"

    #define KB_LYOUT_KEY_1      IKEY_POS1
    #define KB_LYOUT_KEY_2      IKEY_POS2
    #define KB_LYOUT_KEY_3      IKEY_POS3
    #define KB_LYOUT_KEY_UP     IKEY_POS4

    #define KB_LYOUT_KEY_4      IKEY_POS5
    #define KB_LYOUT_KEY_5      IKEY_POS6
    #define KB_LYOUT_KEY_6      IKEY_POS7
    #define KB_LYOUT_KEY_DOWN   IKEY_POS8

    #define KB_LYOUT_KEY_7      IKEY_POS9
    #define KB_LYOUT_KEY_8      IKEY_POS10
    #define KB_LYOUT_KEY_9      IKEY_POS11
    #define KB_LYOUT_KEY_2ND    IKEY_POS12

    #define KB_LYOUT_KEY_CLEAR  IKEY_POS13
    #define KB_LYOUT_KEY_0      IKEY_POS14
    #define KB_LYOUT_KEY_MENU   IKEY_POS15
    #define KB_LYOUT_KEY_ENTER  IKEY_POS16
#endif
