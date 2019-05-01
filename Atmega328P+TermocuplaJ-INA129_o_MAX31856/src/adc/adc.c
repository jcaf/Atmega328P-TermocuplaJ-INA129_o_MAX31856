#include "../system.h"
#include "adc.h"

/*
- 13 - 260μs Conversion Time
- Up to 76.9kSPS (Up to 15kSPS at Maximum Resolution)
- The ADC has a separate analog supply voltage pin, AV CC . AV CC must not differ more than ±0.3V from
V CC . See section ADC Noise Canceler on how to connect this pin.
- The ADC converts an analog input voltage to a 10-bit digital value through successive approximation. The
minimum value represents GND and the maximum value represents the voltage on the AREF pin minus 1
LSB.
*/

void ADC_set_channel(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
}
/*
ADC Voltage Reference Selection

The reference voltage for the ADC (V REF ) indicates the conversion range for the ADC. Single ended
channels that exceed V REF will result in codes close to 0x3FF.

V REF can be selected as either AV CC ,
internal 1.1V reference, or external AREF pin.

The ADC has a separate analog supply voltage pin, AV CC . AV CC must not differ more than ±0.3V from
V CC . See section ADC Noise Canceler on how to connect this pin.
*/
void ADC_set_reference(uint8_t ref)
{
	ADMUX = (ADMUX & 0x3F) | ((ref&0x03)<<6);
}

/*
50Khz = 20us
200Khz = 5us

By default, the successive approximation circuitry requires an input clock frequency between 50kHz and
200kHz to get maximum resolution. If a lower resolution than 10 bits is needed, the input clock frequency
to the ADC can be higher than 200kHz to get a higher sample rate.
*/
void ADC_set_prescaler(uint8_t prescaler)
{
	ADCSRA = (ADCSRA & 0xF8) | prescaler;
}

void ADC_enable(void)
{
	BitTo1(ADCSRA, ADEN);
}

void ADC_disable(void)
{
	BitTo0(ADCSRA, ADEN);
}


void ADC_set_adjust(uint8_t adj)
{
	if (adj == ADC_ADJUST_RIGHT)
	{
		BitTo0(ADMUX, ADLAR);
	}
	else
	{
		BitTo1(ADMUX, ADLAR);
	}
}
uint8_t ADC_get_resultH(void)
{
	return ADCH;
}

uint8_t ADC_get_resultL(void)
{
	return ADCL;
}


void ADC_init(int8_t mode)
{
	//ADC_set_reference(ADC_REF_AREF);//Aref tied +VDD
	ADC_set_reference(ADC_REF_AVCC);//

	ADC_set_prescaler(ADC_PRESCALER_128);

	//
	if (mode != ADC_MODE_SINGLE_END)
	{
		BitTo1(ADCSRA, ADATE);
		ADCSRB =  (ADCSRB & 0xF8) | mode;
	}
	else
	{
		BitTo0(ADCSRA, ADATE);
	}
	//
	//ADC_set_adjust(ADC_ADJUST_RIGHT);//by default
	ADC_enable();
}
/*
In Single Conversion mode, write this bit to one to start each conversion. In Free Running mode, write this bit to
one to start the first conversion.
*/
void ADC_start_conv(uint8_t channel)
{
	BitTo0(MCUCR, PRADC);//Writing a logic one to this bit shuts down the ADC

	ADC_set_channel(channel);
	BitTo1(ADCSRA, ADSC);
}

void ADC_start_and_wait_conv(uint8_t channel)
{
	ADC_start_conv(channel);
	while (ADCSRA & (1<<ADSC))
		{;}
}

/*
The ADC generates a 10-bit result which is presented in the ADC Data Registers, ADCH and ADCL. By
default, the result is presented right adjusted, but can optionally be presented left adjusted by setting the
If the result is left adjusted and no more than 8-bit precision is required, it is sufficient to read ADCH.
Otherwise, ADCL must be read first, then ADCH, to ensure that the content of the Data Registers belongs
to the same conversion: Once ADCL is read, ADC access to Data Registers is blocked. This means that if
has been read, and a second conversion completes before ADCH is read, neither register is
updated and the result from the second conversion is lost. When ADCH is read, ADC access to the
ADCH and ADCL Registers is re-enabled.
The ADC has its own interrupt which can be triggered when a conversion completes. When ADC access
to the Data Registers is prohibited between reading of ADCH and ADCL, the interrupt will trigger even if
the result is lost.
*/

/*
If a different data channel is selected while a
conversion is in progress, the ADC will finish the current conversion before performing the channel
change
*/
//uint16_t ADC_get_new_fullresult_block(uint8_t channel)
uint16_t ADC_read(uint8_t channel)
{
	uint8_t resultL;

	if (!(ADCSRA & (1<<ADATE)))
	{
		ADC_start_and_wait_conv(channel);//blocking
	}
	else
	{
		/*
		When this bit is written to one, Auto Triggering of the ADC is enabled. The ADC will start a conversion on
		a positive edge of the selected trigger signal. The trigger source is selected by setting the ADC Trigger
		Select bits, ADTS in ADCSRB.
		*/

		/*
		Beware that if doing a Read-Modify-Write on ADCSRA, a pending interrupt can be disabled. This also
		applies if the SBI and CBI instructions are used.
		*/
		BitTo1(ADCSRA ,ADIF); //Clear flag for new conversion
		//internally, wait for new positive-edge


		while (!(ADCSRA & (1<<ADIF)))
			{;}
		BitTo1(ADCSRA ,ADIF);
		//es mejor trabajarlo por interrupciones
	}

	resultL = ADC_get_resultL();

	if (ADMUX & (1<<ADLAR))//left?
	{
		return (((uint16_t)ADC_get_resultH())<<2) + (resultL>>6);

	}
	else //right by default
	{
		return (((uint16_t)ADC_get_resultH())<<8) + resultL;
	}
}

