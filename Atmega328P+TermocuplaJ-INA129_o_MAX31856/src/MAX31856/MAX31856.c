#include "../system.h"
#include "MAX31856.h"
#include "../SPI/SPI.h"
/*
SPCR = (1<<SPE) | (MSB_LSB_FIRST << DORD) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (SPR1SPR0_SCK_FOSC_128);   //OK: ADS1240 Comunicación integral /64
CPOL necesita ser 1
*/

uint8_t MAX31856_write_1byte(uint8_t addr, uint8_t data)
{
    uint8_t SPI_read;
    //
    PinTo0(PORTWxSPI_SS, PINxSPI_SS);
    __delay_us(1);
        SPI_MSTR_ExchangeData(addr);
        SPI_read = SPI_MSTR_ExchangeData(data);
    __delay_us(1);
    PinTo1(PORTWxSPI_SS, PINxSPI_SS);
    //
    return SPI_read;
}
void MAX31856_write_nbytes(uint8_t addr, uint8_t *data, int8_t n)
{
    int i;
    PinTo0(PORTWxSPI_SS, PINxSPI_SS);
    __delay_us(1);
        SPI_MSTR_ExchangeData(addr);
        for (i=0; i<n; i++)
        {
            SPI_MSTR_ExchangeData(data[i]);
        }
    __delay_us(1);
    PinTo1(PORTWxSPI_SS, PINxSPI_SS);
}

uint8_t MAX31856_read_1byte(uint8_t addr)
{
    return MAX31856_write_1byte(addr, SPI_DUMMY);
}

void MAX31856_read_nbytes(uint8_t addr, uint8_t *data, int8_t n)
{
    int i;
    PinTo0(PORTWxSPI_SS, PINxSPI_SS);
    __delay_us(1);

        SPI_MSTR_ExchangeData(addr);
        for (i=0; i<n; i++)
        {
            data[i]=SPI_MSTR_ExchangeData(SPI_DUMMY);
        }
    __delay_us(1);
    PinTo1(PORTWxSPI_SS, PINxSPI_SS);
}

//

/*
SPCR = (1<<SPE) | (MSB_LSB_FIRST << DORD) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (SPR1SPR0_SCK_FOSC_128);   //OK: ADS1240 Comunicación integral /64
CPOL necesita ser 1
*/
void MAX31856_init(void)
{
    //config0 : open circuit enabled
    //1001 0000

    MAX31856_write_1byte(CR0_WRITE_ADDR, 0x90);//continuous 100 ms

    //MAX31856_write_1byte(CR0_WRITE_ADDR, 0x40);//continuous 100 ms

    __delay_us(10);
    //config1




    //(60Hz rejection)
    //octave:22> tconv
    //tconv =  0.090000
    //octave:23> samples
    //samples =  16
    //octave:24> tconv + (samples-1)*16.67e-3
    //ans =  0.34005
    //
    //0b00000010 //j-thermo type
    //
    //MAX31856_write_1byte(CR1_WRITE_ADDR, 0x02);//ok 1 sample (default)
    MAX31856_write_1byte(CR1_WRITE_ADDR, 0x42);//16 samples averaged
    __delay_us(10);

    /*
    The MSB of the offset register
    is 4°C and the LSB is 0.0625°C. The resulting range of
    the offset value applied to the measured CJ temperature
    is -8°C to +7.9375°C. The default offset value is 0°C
    (00h).
    */
    //MAX31856_write_1byte(CJTO_WRITE_ADDR, 0x80);
    __delay_us(10);


    //0xFF masked nada q hacer

    /*
    ±0.7°C (max, -20°C to +85°C) Cold-Junction
    Accuracy
    The maximum cold-junction temperature is
    clamped at 128°C and the minimum is clamped at -64°C.
    See Table 2 for the Reference Junction (Cold Junction)
    Temperature Data Format.
    */
    //Cold junction high, podria ser ajustado al max. y min
    //CJHF 128.00 ES UN SOLO REGISTRO DE 8-BITS, NO USA DECIMALES BINARIOS
    //CJHL -64.00 ES UN SOLO REGISTRO DE 8-BITS, NO USA DECIMALES BINARIOS

    /*
    Linearized Temperature High Fault Threshold Register, MSB (LTHFTH): (LTHFTL) TEMPERATURA HIGH THRESHOLD
    */

    /*
    Register 07h/87h: Linearized Temperature Low Fault Threshold Register, MSB (LTLFTH) : (LTLFTL) TEMP. LOW THRESHOLD
    */

    /*
    Register 09h/89h: Cold-Junction Temperature Offset Register (CJTO) OFFSET REGISTER
    */

    /*
    Register 0Ah/8Ah: Cold-Junction Temperature Register, MSB (CJTH) : (CJTL)
    */
}
/*
int16_t ptemp(uint16_t ltc)
{
    uint16_t ltcint;
    ltcint = ltc>>4;
    int16_t temp_int;

    if (ltcint & 0x0800)//negativo
    {
        ltcint |= 0xF000;
    }
    temp_int = ltcint;

    //printf("%i \n", temp_int );
    return ltcint;
}
*/
//float
int16_t MAX3156_read_temp(void)
{
    uint8_t LTC[3];

    //LTC contain the read
    //LTC[2]: LTC[1]: LTC[0]
    /*
    __delay_ms(10);
    MAX31856_write_1byte(CR0_WRITE_ADDR, 0x40);
    __delay_ms(300);
*/
    MAX31856_read_nbytes(LTCBH_READ_ADDR, LTC, 3);
//    0x0C-> LTC[0] = BYTE 2
//    0x0D-> LTC[1] = BYTE 1
//    0x0E-> LTC[2] = BYTE 0

    uint16_t t = (((uint16_t)LTC[0])<<8) + (LTC[1] & 0xF0);
    t= t>>4;
    return (int16_t)t;
}

int8_t MAX3156_read_coldj(void)
{
    uint8_t LTC[2];
    MAX31856_read_nbytes(CJTH_READ_ADDR, LTC, 2);
    return (int8_t)LTC[0];
}
