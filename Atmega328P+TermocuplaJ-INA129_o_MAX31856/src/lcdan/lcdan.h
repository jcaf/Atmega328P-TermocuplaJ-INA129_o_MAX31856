/*
 * File:   lcdan.h
 * Author: ][af.
 *
 * Created on 8 de febrero de 2015, 05:18 PM
 */
#ifndef LCDAN_H
#define	LCDAN_H

#define LCD_ROW 2//4
#define LCD_COL 16//20

//
#define	LCDAN_DISP_ON_CURSOR_ON_BLINK_ON		0x0F
#define	LCDAN_DISP_ON_CURSOR_OFF_BLINK_ON		0x0D
#define	LCDAN_DISP_ON_CURSOR_OFF_BLINK_OFF		0x0C
#define	LCDAN_DISP_ON_CURSOR_ON_BLINK_OFF		0x0E
#define LCDAN_DISP_CLEAR                        0x01
#define LCDAN_DISP_OFF				            0x08
#define LCDAN_DISP_CURSOR_DISPLAY_SHIFT         0x10
#define LCDAN_DISP_DISPLAY_SHIFT                0x08
#define LCDAN_DISP_CURSOR_MOVE                  0x00

//Base Address for DDRAM
#define LCDAN_BASEADDR_ROW_0 0x80
#define LCDAN_BASEADDR_ROW_1 0xC0
#define LCDAN_BASEADDR_ROW_2 0x94
#define LCDAN_BASEADDR_ROW_3 0xD4

void lcdan_write_cmd(uint8_t cmd);
void lcdan_write_data(uint8_t data);
void lcdan_init(void);

//#define BKLIGHT_CONTRL
#ifdef BKLIGHT_CONTRL
    #define PORTWxLCD_BKLIGHT PORTB
    #define PORTRxLCD_BKLIGHT PINB
    #define CONFIGIOxLCD_BKLIGHT DDRB
    #define PINxLCD_BKLIGHT 3//MOSI

    #define lcdan_bklight_enable() do{ConfigInputPin(CONFIGIOxLCD_BKLIGHT, PINxLCD_BKLIGHT);}while(0)
    #define lcdan_bklight_disable() do{PinTo0(PORTWxLCD_BKLIGHT, PINxLCD_BKLIGHT);ConfigOutputPin(CONFIGIOxLCD_BKLIGHT, PINxLCD_BKLIGHT);}while(0)
#endif // BKLIGHT_CONTRL


#endif	/* LCDAN_H */

