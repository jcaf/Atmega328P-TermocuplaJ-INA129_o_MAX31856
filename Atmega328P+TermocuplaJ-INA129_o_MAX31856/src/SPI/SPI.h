#ifndef _SPI_H_
#define _SPI_H_

    /*************************************************************************************
    Seria ideal seguir haciendo esta asignación pin a pin, lo malo es que el compilador
    lo traduce a aprox 5 instrucciones de carga indirecta... :P
    *************************************************************************************/

    #define PORTWxSPI_SS PORTB
    #define PORTRxSPI_SS PINB
    #define CONFIGIOxSPI_SS DDRB
    #define PINxSPI_SS 2

    /****************************************************************************************
                                Definir el orden LSB / MSB
	****************************************************************************************/
	//Data Order SPI
	#define MSB_FIRST (0)
	#define LSB_FIRST (1)
    //
	#define MSB_LSB_FIRST (MSB_FIRST)
	//#define MSB_LSB_FIRST (LSB_FIRST)

    /****************************************************************************************
        Relationship Between SCK and the Oscillator Frequency SPI2X SPR1SPR0_SCK Frequency

	****************************************************************************************/
	//#define DOUBLE_SPI_SPEED_BIT 1
	#define DOUBLE_SPI_SPEED_BIT 0

	#if DOUBLE_SPI_SPEED_BIT == 0
		//000 fosc/4
		//001 fosc/16
		//010 fosc/64
		//011 fosc/128
		#define SPR1SPR0_SCK_FOSC_4	    (0x00)
		#define SPR1SPR0_SCK_FOSC_16	(0x01)
		#define SPR1SPR0_SCK_FOSC_64	(0x02)
		#define SPR1SPR0_SCK_FOSC_128	(0x03)

	#else
		//100 fosc/2
		//101 fosc/8
		//110 fosc/32
		//111 fosc/64
		#define SPR1SPR0_SCK_FOSC_2	    (0x04)
		#define SPR1SPR0_SCK_FOSC_8 	(0x05)
		#define SPR1SPR0_SCK_FOSC_32	(0x06)
		#define SPR1SPR0_SCK_FOSC_64	(0x07)

	#endif

    /************************************************************************************************
                            Dummy Byte by exchange data
    ************************************************************************************************/

    #define    SPI_DUMMY 0x00//(0xFF)

    /************************************************************************************************

    ************************************************************************************************/
    void SPI_master_init(void);
    uint8_t SPI_MSTR_ExchangeData(uint8_t DATASPI);

#endif
