#ifndef ADC_H_
#define ADC_H_

    #define ADC_MODE_SINGLE_END 	-1
    #define ADC_MODE_AUTOTRIGGER_FREE_RUNNING 			0x00
    #define ADC_MODE_AUTOTRIGGER_ANALOG_COMPARATOR 		0x01
    #define ADC_MODE_AUTOTRIGGER_EXTERNAL_INT_REQ_0 		0x02
    #define ADC_MODE_AUTOTRIGGER_TIMER0_COMPARE_MATCH_A 	0x03
    #define ADC_MODE_AUTOTRIGGER_TIMER0_OVERFLOW 		0x04
    #define ADC_MODE_AUTOTRIGGER_TIMER1_COMPARE_MATCH_B 	0x05
    #define ADC_MODE_AUTOTRIGGER_TIMER1_OVERFLOW 		0x06
    #define ADC_MODE_AUTOTRIGGER_TIMER1_CAPTURE_EVENT 	0x07

    #define ADC_ADJUST_RIGHT	0
    #define ADC_ADJUST_LEFT		1


    #define ADC_CH_0 0x00
    #define ADC_CH_1 0x01
    #define ADC_CH_2 0x02
    #define ADC_CH_3 0x03
    #define ADC_CH_4 0x04
    #define ADC_CH_5 0x05
    #define ADC_CH_6 0x06
    #define ADC_CH_7 0x07
    #define ADC_CH_TEMP_SENSOR 0x08
    #define ADC_CH_RESERVED0 0x09
    #define ADC_CH_RESERVED1 0x0A
    #define ADC_CH_RESERVED2 0x0B
    #define ADC_CH_RESERVED3 0x0C
    #define ADC_CH_RESERVED4 0x0D
    #define ADC_CH_1_1V 0x0E
    #define ADC_CH_0V_GND 0x0F


    /*
    ADC Voltage Reference Selection

    The reference voltage for the ADC (V REF ) indicates the conversion range for the ADC. Single ended
    channels that exceed V REF will result in codes close to 0x3FF.

    V REF can be selected as either AV CC ,
    internal 1.1V reference, or external AREF pin.

    The ADC has a separate analog supply voltage pin, AV CC . AV CC must not differ more than ±0.3V from
    V CC . See section ADC Noise Canceler on how to connect this pin.
    */

    #define ADC_REF_AREF 00	//Internal V_ref turned off
    #define ADC_REF_AVCC 01	//with external capacitor at AREF pin
    #define ADC_REF_RESERVERD 02	//
    #define ADC_REF_INTERNAL_1_1V 03//Voltage Reference with external capacitor at AREF pin

    /*
    50Khz = 20us
    200Khz = 5us

    By default, the successive approximation circuitry requires an input clock frequency between 50kHz and
    200kHz to get maximum resolution. If a lower resolution than 10 bits is needed, the input clock frequency
    to the ADC can be higher than 200kHz to get a higher sample rate.

    */

    #define ADC_PRESCALER_2 0x0
    //#define ADC_PRESCALER_2 0x1
    #define ADC_PRESCALER_4 0x2
    #define ADC_PRESCALER_8 0x3
    #define ADC_PRESCALER_16 0x4
    #define ADC_PRESCALER_32 0x5
    #define ADC_PRESCALER_64 0x6
    #define ADC_PRESCALER_128 0x7

    void ADC_set_channel(uint8_t channel);
    void ADC_set_reference(uint8_t ref);
    void ADC_set_prescaler(uint8_t prescaler);
    void ADC_enable(void);
    void ADC_disable(void);
    void ADC_set_adjust(uint8_t adj);
    uint8_t ADC_get_resultH(void);
    uint8_t ADC_get_resultL(void);
    //
    void ADC_init(int8_t mode);
    void ADC_start_conv(uint8_t channel);
    void ADC_start_and_wait_conv(uint8_t channel);
    uint16_t ADC_read(uint8_t channel);

#endif // ADC_H_

