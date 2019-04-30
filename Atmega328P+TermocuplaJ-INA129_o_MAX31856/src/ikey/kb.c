#include "../system.h"
#include "ikey.h"
#include "kb.h"


//////// KEYPAD 4X4 //////////////////////
//////////////////////////////////////KEY1
#define PORTWxKBFIL_KEY1 	PORTWxKBFIL_1
#define PORTRxKBFIL_KEY1 	PORTRxKBFIL_1
#define CONFIGIOxKBFIL_KEY1 	CONFIGIOxKBFIL_1
#define PINxKBFIL_KEY1 		PINxKBFIL_1
//
#define PORTWxKBCOL_KEY1 	PORTWxKBCOL_1
#define PORTRxKBCOL_KEY1 	PORTRxKBCOL_1
#define CONFIGIOxKBCOL_KEY1 	CONFIGIOxKBCOL_1
#define PINxKBCOL_KEY1 		PINxKBCOL_1
//////////////////////////////////////KEY2
#define PORTWxKBFIL_KEY2 	PORTWxKBFIL_1
#define PORTRxKBFIL_KEY2 	PORTRxKBFIL_1
#define CONFIGIOxKBFIL_KEY2 	CONFIGIOxKBFIL_1
#define PINxKBFIL_KEY2 		PINxKBFIL_1
//
#define PORTWxKBCOL_KEY2 	PORTWxKBCOL_2
#define PORTRxKBCOL_KEY2 	PORTRxKBCOL_2
#define CONFIGIOxKBCOL_KEY2 	CONFIGIOxKBCOL_2
#define PINxKBCOL_KEY2 		PINxKBCOL_2
//////////////////////////////////////
#define PORTWxKBFIL_KEY3 	PORTWxKBFIL_1
#define PORTRxKBFIL_KEY3 	PORTRxKBFIL_1
#define CONFIGIOxKBFIL_KEY3 	CONFIGIOxKBFIL_1
#define PINxKBFIL_KEY3 		PINxKBFIL_1
//
#define PORTWxKBCOL_KEY3 	PORTWxKBCOL_3
#define PORTRxKBCOL_KEY3 	PORTRxKBCOL_3
#define CONFIGIOxKBCOL_KEY3 	CONFIGIOxKBCOL_3
#define PINxKBCOL_KEY3 		PINxKBCOL_3
//////////////////////////////////////
#define PORTWxKBFIL_KEY4 	PORTWxKBFIL_1
#define PORTRxKBFIL_KEY4 	PORTRxKBFIL_1
#define CONFIGIOxKBFIL_KEY4 	CONFIGIOxKBFIL_1
#define PINxKBFIL_KEY4 		PINxKBFIL_1
//
#define PORTWxKBCOL_KEY4 	PORTWxKBCOL_4
#define PORTRxKBCOL_KEY4 	PORTRxKBCOL_4
#define CONFIGIOxKBCOL_KEY4 	CONFIGIOxKBCOL_4
#define PINxKBCOL_KEY4 		PINxKBCOL_4
//////////////////////////////////////
#define PORTWxKBFIL_KEY5 	PORTWxKBFIL_2
#define PORTRxKBFIL_KEY5 	PORTRxKBFIL_2
#define CONFIGIOxKBFIL_KEY5 	CONFIGIOxKBFIL_2
#define PINxKBFIL_KEY5 		PINxKBFIL_2
//
#define PORTWxKBCOL_KEY5 	PORTWxKBCOL_1
#define PORTRxKBCOL_KEY5 	PORTRxKBCOL_1
#define CONFIGIOxKBCOL_KEY5 	CONFIGIOxKBCOL_1
#define PINxKBCOL_KEY5 		PINxKBCOL_1
//////////////////////////////////////
#define PORTWxKBFIL_KEY6 	PORTWxKBFIL_2
#define PORTRxKBFIL_KEY6 	PORTRxKBFIL_2
#define CONFIGIOxKBFIL_KEY6 	CONFIGIOxKBFIL_2
#define PINxKBFIL_KEY6 		PINxKBFIL_2
//
#define PORTWxKBCOL_KEY6 	PORTWxKBCOL_2
#define PORTRxKBCOL_KEY6 	PORTRxKBCOL_2
#define CONFIGIOxKBCOL_KEY6 	CONFIGIOxKBCOL_2
#define PINxKBCOL_KEY6 		PINxKBCOL_2
//////////////////////////////////////
#define PORTWxKBFIL_KEY7 	PORTWxKBFIL_2
#define PORTRxKBFIL_KEY7 	PORTRxKBFIL_2
#define CONFIGIOxKBFIL_KEY7 	CONFIGIOxKBFIL_2
#define PINxKBFIL_KEY7 		PINxKBFIL_2
//
#define PORTWxKBCOL_KEY7 	PORTWxKBCOL_3
#define PORTRxKBCOL_KEY7 	PORTRxKBCOL_3
#define CONFIGIOxKBCOL_KEY7 	CONFIGIOxKBCOL_3
#define PINxKBCOL_KEY7 		PINxKBCOL_3
//////////////////////////////////////
#define PORTWxKBFIL_KEY8 	PORTWxKBFIL_2
#define PORTRxKBFIL_KEY8 	PORTRxKBFIL_2
#define CONFIGIOxKBFIL_KEY8 	CONFIGIOxKBFIL_2
#define PINxKBFIL_KEY8 		PINxKBFIL_2
//
#define PORTWxKBCOL_KEY8 	PORTWxKBCOL_4
#define PORTRxKBCOL_KEY8 	PORTRxKBCOL_4
#define CONFIGIOxKBCOL_KEY8 	CONFIGIOxKBCOL_4
#define PINxKBCOL_KEY8 		PINxKBCOL_4
//////////////////////////////////////
#define PORTWxKBFIL_KEY9 	PORTWxKBFIL_3
#define PORTRxKBFIL_KEY9 	PORTRxKBFIL_3
#define CONFIGIOxKBFIL_KEY9 	CONFIGIOxKBFIL_3
#define PINxKBFIL_KEY9 		PINxKBFIL_3
//
#define PORTWxKBCOL_KEY9 	PORTWxKBCOL_1
#define PORTRxKBCOL_KEY9 	PORTRxKBCOL_1
#define CONFIGIOxKBCOL_KEY9 	CONFIGIOxKBCOL_1
#define PINxKBCOL_KEY9 		PINxKBCOL_1
//////////////////////////////////////
#define PORTWxKBFIL_KEY10	PORTWxKBFIL_3
#define PORTRxKBFIL_KEY10	PORTRxKBFIL_3
#define CONFIGIOxKBFIL_KEY10	CONFIGIOxKBFIL_3
#define PINxKBFIL_KEY10		PINxKBFIL_3
//
#define PORTWxKBCOL_KEY10	PORTWxKBCOL_2
#define PORTRxKBCOL_KEY10	PORTRxKBCOL_2
#define CONFIGIOxKBCOL_KEY10	CONFIGIOxKBCOL_2
#define PINxKBCOL_KEY10		PINxKBCOL_2
//////////////////////////////////////
#define PORTWxKBFIL_KEY11	PORTWxKBFIL_3
#define PORTRxKBFIL_KEY11	PORTRxKBFIL_3
#define CONFIGIOxKBFIL_KEY11	CONFIGIOxKBFIL_3
#define PINxKBFIL_KEY11		PINxKBFIL_3
//
#define PORTWxKBCOL_KEY11	PORTWxKBCOL_3
#define PORTRxKBCOL_KEY11	PORTRxKBCOL_3
#define CONFIGIOxKBCOL_KEY11	CONFIGIOxKBCOL_3
#define PINxKBCOL_KEY11		PINxKBCOL_3
//////////////////////////////////////
#define PORTWxKBFIL_KEY12	PORTWxKBFIL_3
#define PORTRxKBFIL_KEY12	PORTRxKBFIL_3
#define CONFIGIOxKBFIL_KEY12	CONFIGIOxKBFIL_3
#define PINxKBFIL_KEY12		PINxKBFIL_3
//
#define PORTWxKBCOL_KEY12	PORTWxKBCOL_4
#define PORTRxKBCOL_KEY12	PORTRxKBCOL_4
#define CONFIGIOxKBCOL_KEY12	CONFIGIOxKBCOL_4
#define PINxKBCOL_KEY12		PINxKBCOL_4
//////////////////////////////////////
#define PORTWxKBFIL_KEY13	PORTWxKBFIL_4
#define PORTRxKBFIL_KEY13	PORTRxKBFIL_4
#define CONFIGIOxKBFIL_KEY13	CONFIGIOxKBFIL_4
#define PINxKBFIL_KEY13		PINxKBFIL_4
//
#define PORTWxKBCOL_KEY13	PORTWxKBCOL_1
#define PORTRxKBCOL_KEY13	PORTRxKBCOL_1
#define CONFIGIOxKBCOL_KEY13	CONFIGIOxKBCOL_1
#define PINxKBCOL_KEY13		PINxKBCOL_1
//////////////////////////////////////
#define PORTWxKBFIL_KEY14 	PORTWxKBFIL_4
#define PORTRxKBFIL_KEY14	PORTRxKBFIL_4
#define CONFIGIOxKBFIL_KEY14	CONFIGIOxKBFIL_4
#define PINxKBFIL_KEY14		PINxKBFIL_4
//
#define PORTWxKBCOL_KEY14	PORTWxKBCOL_2
#define PORTRxKBCOL_KEY14	PORTRxKBCOL_2
#define CONFIGIOxKBCOL_KEY14	CONFIGIOxKBCOL_2
#define PINxKBCOL_KEY14		PINxKBCOL_2
//////////////////////////////////////
#define PORTWxKBFIL_KEY15	PORTWxKBFIL_4
#define PORTRxKBFIL_KEY15	PORTRxKBFIL_4
#define CONFIGIOxKBFIL_KEY15	CONFIGIOxKBFIL_4
#define PINxKBFIL_KEY15		PINxKBFIL_4
//
#define PORTWxKBCOL_KEY15 	PORTWxKBCOL_3
#define PORTRxKBCOL_KEY15	PORTRxKBCOL_3
#define CONFIGIOxKBCOL_KEY15	CONFIGIOxKBCOL_3
#define PINxKBCOL_KEY15		PINxKBCOL_3
//////////////////////////////////////
#define PORTWxKBFIL_KEY16	PORTWxKBFIL_4
#define PORTRxKBFIL_KEY16	PORTRxKBFIL_4
#define CONFIGIOxKBFIL_KEY16	CONFIGIOxKBFIL_4
#define PINxKBFIL_KEY16		PINxKBFIL_4
//
#define PORTWxKBCOL_KEY16	PORTWxKBCOL_4
#define PORTRxKBCOL_KEY16	PORTRxKBCOL_4
#define CONFIGIOxKBCOL_KEY16	CONFIGIOxKBCOL_4
#define PINxKBCOL_KEY16		PINxKBCOL_4

#define readkey_setup_time() _delay_us(2)//NEED TO STABILIZE THE SIGNAL, WITHOUT THIS, KB CAN READ OTHER KEY IN POS 13
static inline uint8_t keyRead_pin_key1(void)
{
	PinTo0(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY1, PINxKBCOL_KEY1);
}
static inline uint8_t keyRead_pin_key2(void)
{
	PinTo0(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY2, PINxKBCOL_KEY2);
}
static inline uint8_t keyRead_pin_key3(void)
{
	PinTo0(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY3, PINxKBCOL_KEY3);
}
static inline uint8_t keyRead_pin_key4(void)
{
	PinTo0(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY4, PINxKBCOL_KEY4);
}
//
static inline uint8_t keyRead_pin_key5(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo0(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
    readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY5, PINxKBCOL_KEY5);
}
static inline uint8_t keyRead_pin_key6(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo0(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY6, PINxKBCOL_KEY6);
}
static inline uint8_t keyRead_pin_key7(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo0(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY7, PINxKBCOL_KEY7);
}
static inline uint8_t keyRead_pin_key8(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo0(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY8, PINxKBCOL_KEY8);
}
//
static inline uint8_t keyRead_pin_key9(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo0(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY9, PINxKBCOL_KEY9);
}
static inline uint8_t keyRead_pin_key10(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo0(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY10, PINxKBCOL_KEY10);
}
static inline uint8_t keyRead_pin_key11(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo0(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY11, PINxKBCOL_KEY11);
}
static inline uint8_t keyRead_pin_key12(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo0(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo1(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY12, PINxKBCOL_KEY12);
}
static inline uint8_t keyRead_pin_key13(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo0(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY13, PINxKBCOL_KEY13);
}
static inline uint8_t keyRead_pin_key14(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo0(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY14, PINxKBCOL_KEY14);
}
static inline uint8_t keyRead_pin_key15(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo0(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY15, PINxKBCOL_KEY15);
}
static inline uint8_t keyRead_pin_key16(void)
{
	PinTo1(PORTWxKBFIL_1, PINxKBFIL_1);
	PinTo1(PORTWxKBFIL_2, PINxKBFIL_2);
	PinTo1(PORTWxKBFIL_3, PINxKBFIL_3);
	PinTo0(PORTWxKBFIL_4, PINxKBFIL_4);
	readkey_setup_time();
	return ReadPin(PORTRxKBCOL_KEY16, PINxKBCOL_KEY16);
}

volatile struct _key key[KB_NUM_KEYS];

void key_initialization(void)
{
    int8_t i;
	ConfigOutputPin(CONFIGIOxKBFIL_1, PINxKBFIL_1);
	ConfigOutputPin(CONFIGIOxKBFIL_2, PINxKBFIL_2);
	ConfigOutputPin(CONFIGIOxKBFIL_3, PINxKBFIL_3);
	ConfigOutputPin(CONFIGIOxKBFIL_4, PINxKBFIL_4);

	ConfigInputPin(CONFIGIOxKBCOL_1, PINxKBCOL_1);
	ConfigInputPin(CONFIGIOxKBCOL_2, PINxKBCOL_2);
	ConfigInputPin(CONFIGIOxKBCOL_3, PINxKBCOL_3);
	ConfigInputPin(CONFIGIOxKBCOL_4, PINxKBCOL_4);

    key[0].keyRead = keyRead_pin_key1;
    key[1].keyRead = keyRead_pin_key2;
    key[2].keyRead = keyRead_pin_key3;
    key[3].keyRead = keyRead_pin_key4;
    key[4].keyRead = keyRead_pin_key5;
    key[5].keyRead = keyRead_pin_key6;
    key[6].keyRead = keyRead_pin_key7;
    key[7].keyRead = keyRead_pin_key8;
    key[8].keyRead = keyRead_pin_key9;
    key[9].keyRead = keyRead_pin_key10;
    key[10].keyRead = keyRead_pin_key11;
    key[11].keyRead = keyRead_pin_key12;
    key[12].keyRead = keyRead_pin_key13;
    key[13].keyRead = keyRead_pin_key14;
    key[14].keyRead = keyRead_pin_key15;
    key[15].keyRead = keyRead_pin_key16;

    for (i=0; i<KB_NUM_KEYS; i++)
    {
        key[i].bf.OnKeyPressed = 1;
        key[i].bf.OnKeyPressedAndKeyRelease = 0;
        key[i].bf.AtTimeExpired = 0;
        key[i].bf.Reptt = 0;
        key[i].num_group_x = 0;
        key[i].repp.to_start= 500.0/5;
        key[i].repp.after_start = 200.0/5;
    }
/*
    key[0].bf.OnKeyPressed = 1;
    key[0].bf.OnKeyPressedAndKeyRelease = 0;
    key[0].bf.AtTimeExpired = 0;
    key[0].bf.Reptt = 0;
    key[0].num_group_x = 0;
    key[0].repp.to_start= 500.0/5;
    key[0].repp.after_start = 200.0/5;

    key[1].bf.OnKeyPressed = 1;
    key[1].bf.OnKeyPressedAndKeyRelease = 0;
    key[1].bf.AtTimeExpired = 0;
    key[1].bf.Reptt = 0;
    key[1].num_group_x = 0;
    key[1].repp.to_start= 500.0/5;
    key[1].repp.after_start = 200.0/5;

    key[2].bf.OnKeyPressed = 1;
    key[2].bf.OnKeyPressedAndKeyRelease = 0;
    key[2].bf.AtTimeExpired = 0;
    key[2].bf.Reptt = 0;
    key[2].num_group_x = 0;
    key[2].repp.to_start= 500.0/5;
    key[2].repp.after_start = 200.0/5;

    key[3].bf.OnKeyPressed = 1;
    key[3].bf.OnKeyPressedAndKeyRelease = 0;
    key[3].bf.AtTimeExpired = 0;
    key[3].bf.Reptt = 0;
    key[3].num_group_x = 0;
    key[3].repp.to_start= 500.0/5;
    key[3].repp.after_start = 200.0/5;

    key[4].bf.OnKeyPressed = 1;
    key[4].bf.OnKeyPressedAndKeyRelease = 0;
    key[4].bf.AtTimeExpired = 0;
    key[4].bf.Reptt = 0;
    key[4].num_group_x = 0;
    key[4].repp.to_start= 500.0/5;
    key[4].repp.after_start = 200.0/5;

    key[5].bf.OnKeyPressed = 1;
    key[5].bf.OnKeyPressedAndKeyRelease = 0;
    key[5].bf.AtTimeExpired = 0;
    key[5].bf.Reptt = 0;
    key[5].num_group_x = 0;
    key[5].repp.to_start= 500.0/5;
    key[5].repp.after_start = 200.0/5;

    key[6].bf.OnKeyPressed = 1;
    key[6].bf.OnKeyPressedAndKeyRelease = 0;
    key[6].bf.AtTimeExpired = 0;
    key[6].bf.Reptt = 0;
    key[6].num_group_x = 0;
    key[6].repp.to_start= 500.0/5;
    key[6].repp.after_start = 200.0/5;

    key[7].bf.OnKeyPressed = 1;
    key[7].bf.OnKeyPressedAndKeyRelease = 0;
    key[7].bf.AtTimeExpired = 0;
    key[7].bf.Reptt = 0;
    key[7].num_group_x = 0;
    key[7].repp.to_start= 500.0/5;
    key[7].repp.after_start = 200.0/5;

    key[8].bf.OnKeyPressed = 1;
    key[8].bf.OnKeyPressedAndKeyRelease = 0;
    key[8].bf.AtTimeExpired = 0;
    key[8].bf.Reptt = 0;
    key[8].num_group_x = 0;
    key[8].repp.to_start= 500.0/5;
    key[8].repp.after_start = 200.0/5;

    key[9].bf.OnKeyPressed = 1;
    key[9].bf.OnKeyPressedAndKeyRelease = 0;
    key[9].bf.AtTimeExpired = 0;
    key[9].bf.Reptt = 0;
    key[9].num_group_x = 0;
    key[9].repp.to_start= 500.0/5;
    key[9].repp.after_start = 200.0/5;

    key[10].bf.OnKeyPressed = 1;
    key[10].bf.OnKeyPressedAndKeyRelease = 0;
    key[10].bf.AtTimeExpired = 0;
    key[10].bf.Reptt = 0;
    key[10].num_group_x = 0;
    key[10].repp.to_start= 500.0/5;
    key[10].repp.after_start = 200.0/5;

    key[11].bf.OnKeyPressed = 1;
    key[11].bf.OnKeyPressedAndKeyRelease = 0;
    key[11].bf.AtTimeExpired = 0;
    key[11].bf.Reptt = 0;
    key[11].num_group_x = 0;
    key[11].repp.to_start= 500.0/5;
    key[11].repp.after_start = 200.0/5;

    key[12].bf.OnKeyPressed = 1;
    key[12].bf.OnKeyPressedAndKeyRelease = 0;
    key[12].bf.AtTimeExpired = 0;
    key[12].bf.Reptt = 0;
    key[12].num_group_x = 0;
    key[12].repp.to_start= 500.0/5;
    key[12].repp.after_start = 200.0/5;

    key[13].bf.OnKeyPressed = 1;
    key[13].bf.OnKeyPressedAndKeyRelease = 0;
    key[13].bf.AtTimeExpired = 0;
    key[13].bf.Reptt = 0;
    key[13].num_group_x = 0;
    key[13].repp.to_start= 500.0/5;
    key[13].repp.after_start = 200.0/5;

    key[14].bf.OnKeyPressed = 1;
    key[14].bf.OnKeyPressedAndKeyRelease = 0;
    key[14].bf.AtTimeExpired = 0;
    key[14].bf.Reptt = 0;
    key[14].num_group_x = 0;
    key[14].repp.to_start= 500.0/5;
    key[14].repp.after_start = 200.0/5;

    key[15].bf.OnKeyPressed = 1;
    key[15].bf.OnKeyPressedAndKeyRelease = 0;
    key[15].bf.AtTimeExpired = 0;
    key[15].bf.Reptt = 0;
    key[15].num_group_x = 0;
    key[15].repp.to_start= 500.0/5;
    key[15].repp.after_start = 200.0/5;
*/
}
/*
void kb_processKeyRead_D(void)
{
    if (kb_get_ready2read(0))
    {
        kb_clear_ready2read(0);
        //kb_execfunct(0);
    }
    if (kb_get_ready2read(1))
    {
        kb_clear_ready2read(1);
        //kb_execfunct(1);
    }
    if (kb_get_ready2read(2))
    {
        kb_clear_ready2read(2);
        //kb_execfunct(2);
    }
    if (kb_get_ready2read(3))
    {
        kb_clear_ready2read(3);
        //kb_execfunct(3);
    }
    if (kb_get_ready2read(4))
    {
        kb_clear_ready2read(4);
        //kb_execfunct(4);
    }
    if (kb_get_ready2read(5))
    {
        kb_clear_ready2read(5);
        //kb_execfunct(5);
    }
    if (kb_get_ready2read(6))
    {
        kb_clear_ready2read(6);
        //kb_execfunct(6);
    }
    if (kb_get_ready2read(7))
    {
        kb_clear_ready2read(7);
        //kb_execfunct(7);
    }
    if (kb_get_ready2read(8))
    {
        kb_clear_ready2read(8);
        //kb_execfunct(8);
    }
    if (kb_get_ready2read(9))
    {
        kb_clear_ready2read(9);
        //kb_execfunct(9);
    }
    if (kb_get_ready2read(10))
    {
        kb_clear_ready2read(10);
        //kb_execfunct(10);
    }
    if (kb_get_ready2read(11))
    {
        kb_clear_ready2read(11);
        //kb_execfunct(11);
    }

    if (kb_get_ready2read(12))
    {
        kb_clear_ready2read(12);
        //kb_execfunct(12);
    }
    if (kb_get_ready2read(13))
    {
        kb_clear_ready2read(13);
        //kb_execfunct(13);
    }
    if (kb_get_ready2read(14))
    {
        kb_clear_ready2read(14);
        //kb_execfunct(14);
    }
    if (kb_get_ready2read(15))
    {
        kb_clear_ready2read(15);
        //kb_execfunct(15);
    }

}
*/
void kb_job(void)
{
    ikey_scan();
    ikey_parsing();
}
void kb_flush(void)
{
    ikey_all_clear_flag();
}
/*
void kb_change_keyDo_pgm(PTRFX_retVOID const *  keyDo)
{
    uint8_t i;
    for (i=0; i<KB_NUM_KEYS; i++)
        key[i].keyDo = (PTRFX_retVOID)pgm_read_word(&keyDo[i]);
}
 */
/*
void kb_change_keyDo(PTRFX_retVOID *keyDo)
{
    uint8_t i;
    for (i=0; i<KB_NUM_KEYS; i++)
        key[i].keyDo = keyDo[i];
}
*/
/*
void kb_change_keyDo(const PTRFX_retVOID *keyDo)
{
    uint8_t i;
    for (i=0; i<KB_NUM_KEYS; i++)
        key[i].keyDo = keyDo[i];
}
*/
