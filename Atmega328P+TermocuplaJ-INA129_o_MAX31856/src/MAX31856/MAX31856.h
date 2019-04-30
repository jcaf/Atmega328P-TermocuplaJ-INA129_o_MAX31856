#ifndef MAX31856_H_INCLUDED
#define MAX31856_H_INCLUDED

    /*
    The registers are accessed using the 0Xh addresses for reads and the 8Xh addresses for writes. Data is read from or
    written to the registers MSB first. Attempts to write to a read-only register results in no change in the data.
    */
    #define CR0_READ_ADDR 0x00 //config. 0 reg
    #define CR0_WRITE_ADDR 0x80

    #define CR1_READ_ADDR 0x01 //config 1 reg
    #define CR1_WRITE_ADDR 0x81

    #define MASK_READ_ADDR 0x02    //fault mask register
    #define MASK_WRITE_ADDR 0x82

    #define CJHF_READ_ADDR 0x03    //cold-junction high fault thres.
    #define CJHF_WRITE_ADDR 0x83

    #define CJLF_READ_ADDR 0x04 //cold-junction low fault thres.
    #define CJLF_WRITE_ADDR 0x84

    #define LTHFTH_READ_ADDR 0x05  //linearized temp. high fault thr MSB
    #define LTHFTH_WRITE_ADDR 0x85

    #define LTHFTL_READ_ADDR 0x06 //linearized temp. high fault thr LSB
    #define LTHFTL_WRITE_ADDR 0x86

    #define LTLFTH_READ_ADDR 0x07 //linearized temp. low fault thr MSB
    #define LTLFTH_WRITE_ADDR 0x87

    #define LTLFTL_READ_ADDR 0x08  //linearized temp. low fault thr LSB
    #define LTLFTL_WRITE_ADDR 0x88

    #define CJTO_READ_ADDR 0x09    //cold-junct. temperature offset reg
    #define CJTO_WRITE_ADDR 0x89

    #define CJTH_READ_ADDR 0x0A    //cold-junct. temperature reg MSB
    #define CJTH_WRITE_ADDR 0x8A

    #define CJTL_READ_ADDR 0x0B    //cold-junct. temperature reg LSB
    #define CJTL_WRITE_ADDR 0x8B
    //
    #define LTCBH_READ_ADDR 0x0C    //Linearized TC temperature Byte 2
    #define LTCBM_READ_ADDR 0x0D    //Linearized TC temperature Byte 1
    #define LTCBL_READ_ADDR 0x0E    //Linearized TC temperature Byte 0
    #define SR_READ_ADDR    0x0F    //Fault Status reg.

    uint8_t MAX31856_write_1byte(uint8_t addr, uint8_t data);
    void MAX31856_write_nbytes(uint8_t addr, uint8_t *data, int8_t n);
    uint8_t MAX31856_read_1byte(uint8_t addr);
    void MAX31856_read_nbytes(uint8_t addr, uint8_t *data, int8_t n);

    void MAX31856_init(void);
    int16_t MAX3156_read_temp(void);

#endif // MAX31856_H_INCLUDED
