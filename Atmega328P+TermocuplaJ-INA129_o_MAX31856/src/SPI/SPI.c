    #include "../system.h"
    #include "SPI.h"
	void SPI_master_init(void)
	{
	    //Configurando SPI Módulo, Usando el mismo pin ~SS(OUTPUT siempre) para direccionar
        //MOSI - SCK - nSS -> User Defined

        PinTo1(PORTWxSPI_SS, PINxSPI_SS);
        DDRB |= (1<<5) | (1<<3) | (1<<2);

        //MASTER SPI
        SPCR = (1<<SPE) | (MSB_LSB_FIRST << DORD) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (SPR1SPR0_SCK_FOSC_128);   //OK: ADS1240 Comunicación integral /64
        //SPSR = DOUBLE_SPI_SPEED_BIT << SPI2X;

//       PinTo0(PORTB, 2); //SS high
//       __delay_ms(2);
//       PinTo1(PORTB, 2); //SS high

	}//End fx()

    /////////////////////////////////////////////////
    uint8_t SPI_MSTR_ExchangeData(uint8_t DATASPI)
    {
        SPDR = DATASPI;

        //Esperar por data transmitida
        while ( !(SPSR & (1<<SPIF) ) )   //1º Read Status register
        {;}

        return  SPDR;               //2º leer SPDR -> Clear flag
    }

