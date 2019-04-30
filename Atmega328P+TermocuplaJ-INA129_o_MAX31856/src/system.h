#ifndef SYSTEM_H_
#define SYSTEM_H

#define F_CPU 16000000UL		//AVR-GCC
#define _XTAL_FREQ F_CPU	//C PIC


#define OR_BITWISE(REG, KTE)  	do{REG |= KTE;}while(0)
#define AND_BITWISE(REG, KTE)	do{REG &= KTE;}while(0)
#define XOR_BITWISE(REG, KTE) 	do{REG ^= KTE;}while(0)

//Write to generic register
#define BitTo1(REG, BIT) OR_BITWISE(REG, 1<<BIT)
#define BitTo0(REG, BIT) AND_BITWISE(REG, ~(1<<BIT))
#define BitToggle(REG,BIT) XOR_BITWISE(REG, 1<<BIT)

//Write physical port
#define PinTo1(PORTX,PIN) BitTo1(PORTX, PIN)
#define PinTo0(PORTX,PIN) BitTo0(PORTX, PIN)
#define PinToggle(PORTX,PIN) BitToggle(PORTX,PIN)
//Lectura de Pin
#define PinRead(PINX,PIN) ((PINX & (1<<PIN))>>PIN)
#define ReadPin(PINX,PIN) ((PINX & (1<<PIN))>>PIN)//To deprecate
//

#if defined(__XC) || defined(HI_TECH_C) || defined(_MPC_)

	#define INPUT_PIN  1
	#define OUTPUT_PIN  0

	#define ConfigInputPin(IOREG,PIN)  BitTo1(IOREG, PIN)
	#define ConfigOutputPin(IOREG,PIN) BitTo0(IOREG, PIN)

	#define ConfigInputPort(IOREG,  BITS_INPUT) OR_BITWISE(IOREG, BITS_INPUT)
	#define ConfigOutputPort(IOREG, BITS_INPUT) AND_BITWISE(IOREG, ~(BITS_INPUT))

	//#define __delay_ms(x) //the same name as intrinsic functions for microchip
	//#define __delay_us(x)

	//Timer CPU INSTRUCCTION CYCLE = N Q_CYCLES
	#define Q_CYCLE 4   //PIC ARCH.

#elif defined(__GNUC__) && defined(__AVR__)

	#define INPUT_PIN  0
	#define OUTPUT_PIN  1

	#define ConfigInputPin(IOREG,PIN) do{IOREG &= (~(0x01<<PIN));}while(0)
	#define ConfigOutputPin(IOREG,PIN) do{IOREG |= (0x01<<PIN);}while(0)

	#define ConfigInputPort(IOREG,  BITS_INPUT) AND_BITWISE(IOREG, ~(BITS_INPUT))
	#define ConfigOutputPort(IOREG, BITS_INPUT) OR_BITWISE(IOREG, BITS_INPUT)

	#define FLASH_DECLARE(x) x __attribute__((__progmem__))
	#define NOP() do{asm volatile ("nop");}while(0)

	#include <avr/io.h>
	#include <avr/interrupt.h>
    #include <avr/pgmspace.h>
    #include <avr/eeprom.h>
    #include <util/delay.h>
	#define __delay_ms(x) _delay_ms(x)
	#define __delay_us(x) _delay_us(x)

	//Timer CPU INSTRUCCTION CYCLE = N Q_CYCLES
	#define Q_CYCLE 1   //AVR ARCH.
    #define TMR8B_OVF(T_DESIRED, PREESCALER)  (256 - (T_DESIRED*F_CPU/(PREESCALER*Q_CYCLE)) )

/*
#elif defined(__ICCAVR__) && defined(AVR)

	#define ConfigInputPin(IOREG,PIN) do{IOREG &= (~(0x01<<PIN));}while(0)
	#define ConfigOutputPin(IOREG,PIN) do{IOREG |= (0x01<<PIN);}while(0)

	#define ConfigInputPort(IOREG,  BITS_INPUT) AND_BITWISE(IOREG, ~(BITS_INPUT))
	#define ConfigOutputPort(IOREG, BITS_INPUT) OR_BITWISE(IOREG, BITS_INPUT)

	#define PSTR(s) (s)
	#define sei() do{ __enable_interrupt();}while(0)
	#define cli() do{ __disable_interrupt();}while(0)

	#define PRAGMA(text) _Pragma( #text )
	#define ISR(VECT) PRAGMA(vector=VECT) __interrupt void VECT##_fxInt(void)

	#define FLASH_DECLARE(x) __flash x
	#define NOP() do{__no_operation();}while(0)
*/
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MHz 1000000
#define KHz 1000
#define ms 0.001
#define us 0.000001

#endif


