/*
   Author: Juan Carlos Aguero Flores, ][af.
   telf. 929 498 433
   email: firwar21@gmail.com
   www.firwar.com

   no floatpoint
    usbasp
    read fuses:
    http://www.engbedded.com/fusecalc/

    lock bits:
    http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p

    -booloader size al minimo
    -boot reset disable
    -boden= on, con 2.7V
    -crystal con el max. tiempo de power-on-reset
    -clock ouput= disable
    -divide clock by8 internally = disable
    -resetiopin== no programado.. sigue sirviendo como reset
    -debug wire = disable

    1) DESPROTEGER LA PROTECCION DE BORRADO DE LA EEPROM
    EESAVE DISABLE
    EEPROM memory is preserved through chip erase
    [root@JCAFPC Release]# avrdude -c usbasp -B10 -p m328p -U lfuse:w:0xff:m -U hfuse:w:0xdf:m
    [root@JCAFPC Release]# avrdude -c usbasp -B10 -p m328p -U efuse:w:0xfd:m

    2) GRABAR EL CODIGO FUENTE CON EL COMANDO ACOSTUMBRADO
    [root@JCAFPC Release]# avrdude -c usbasp -B5 -p m328p -U flash:w:atmega328p.hex
    [root@JCAFPC Release]# avrdude -c usbasp -B5 -p m328p -V -U flash:w:atmega328p.hex (SIN VERIFICAR)
    [jcaf@JCAFPC Release]$ avrdude -c usbasp -B5 -p m328p (ONLY A RESET)

    NUEVO
    [root@JCAFPC Release]# avrdude -c usbasp -B0.3 -p m328p -V -U flash:w:atmega328p.hex (MAS RAPIDO!)
    Tambien puede ser sin -BX.. cuando ya esta bien configurado los fuses:
    [root@JCAFPC Release]# avrdude -c usbasp -p m328p -U flash:w:atmega328p.hex

    3) GRABAR LA EEPROM
    [root@JCAFPC Release]# avrdude -c usbasp -B5 -p m328p -U eeprom:w:atmega328p.eep

    4) REESTABLER LA PROTECCION DE LA EEPROM
    EESAVE ENABLE
    [jcaf@JCAFPC Release]$ avrdude -c usbasp -B10 -p m328p -U lfuse:w:0xff:m -U hfuse:w:0xd7:m
    EJECUTE PROGRAMA (1)
    EDITE PROGRAMA (1)
    avr-size -C --mcu=atmega328p atmega328p.elf
    AVRDRAGON!!!

    [root@JCAFPC Release]# avrdude -c dragon_isp -B 0.3 -P usb -p atmega328p -V -U flash:w:atmega328p.hex
    AVRDUDE: En post-instalation... Release, add:
    sudo visudo
    Then edit that file to add to the very end:
    username ALL = NOPASSWD: /fullpath/to/command, /fullpath/to/othercommand
    eg
    jcaf ALL = NOPASSWD: /usr/bin/avrdude
    sudo avrdude -c usbasp -B0.25 -p m328p -V -U flash:w:$(TARGET_OUTPUT_FILE) $(TARGET_OUTPUT_DIR)$(TARGET_OUTPUT_BASENAME).hex

    Read flash (hex format)
    avrdude -c usbasp -B10 -p m328p -U flash:r:leeme.hex:i

    proteger flash (modo 3): lectura y escritura
    avrdude -c usbasp -B10 -p m328p -U lock:w:0xFC:m
    (ignorar el error de 0x3C... pues los 2 bits de mayor peso no estan implentados)
*/

#include "src/system.h"
#include "src/types.h"
#include "src/main.h"
#include "src/lcdan/lcdan.h"
#include "src/lcdan/lcdan_aux.h"
#include "src/ikey/ikey.h"
#include "src/ikey/kb.h"
#include "src/num/num_textedit.h"
#include "src/num/num_textedit_hwspecific.h"
#include "src/PID/PID.h"
#include "src/usart/usart.h"
#include "src/adc/adc.h"
#include "src/SPI/SPI.h"
#include "src/MAX31856/MAX31856.h"

//Ktes calibracion de Termocupla Tipo J
//INA129
const float thermoJ_seedback = 52e-6;
const float gain_amp = 99.998;  //500 ohm medidos (2 resis de 100k en paralelo)
const int TMAX = TEMPER_MAX;//250;         //C
const int T25 = 25;           //C
const float diff_v = thermoJ_seedback * gain_amp * (TMAX - T25); //Volts
const float m = (TMAX - T25) / diff_v; //C/Volts
const float x_at_25C = 2.556; //volts @25 C
//const float x_at_25C = 2.463; //volts @25 C
const float b = T25 - (m * x_at_25C);// b=-466.548292504312
const float x_at_250C = x_at_25C + diff_v;

volatile struct _isr_flag
{
    unsigned f20ms: 1;
    unsigned newpiece: 1;
    unsigned reset: 1;
    unsigned __a: 5;

} isr_flag = {0};
volatile uint8_t PID_out_as_dutycycle = 0; //using in ISR

volatile struct _main_flag main_flag = {0};

struct _eep_param
{
    int Temp_sp;
    int Tminutes_max;

};
struct _eep_param sram_param;
struct _eep_param EEMEM eep_param;


int16_t  temper_actual_get_new(void);
void temper_display(float temper_actual);
void reset_all(void);

// uint16_t min_ticks;
// uint16_t min_counter;
int8_t timer_counter_enable = 0;
int8_t newpiece_counter;
void timer_display(void);
float temper_actual;//temp actual

int8_t timer_1min(void);
void timer_1min_reset(void);

void pulse_reset(void);
void pulse_newpice(void);

int8_t set_temper_sp_num_textedit(void);
void set_temper_sp(void);
int8_t set_param(void);
void set_min(void);

void process_set_texts(void);
uint16_t PID_access_delay;

struct _timer
{
    int8_t sec;
    int16_t min;
    int16_t ticks;
} timer;

#define TEMP_SENSOR_INA129 0
#define TEMP_SENSOR_MAX31856 1

#define TEMP_SENSOR TEMP_SENSOR_INA129
//#define TEMP_SENSOR TEMP_SENSOR_MAX31856

//#define DEBUG_PROCESS //hasta habilitar 2 pines rx/tx -> a main.h
void setup(void)
{
    #ifdef DEBUG_PROCESS
    USART_Init ( MYUBRR );//@9600
    #endif // DEBUG_PROCESS
    lcdan_init();

    #if TEMP_SENSOR == TEMP_SENSOR_INA129
    ADC_init(ADC_MODE_SINGLE_END);//only for INA129
    #else
    SPI_master_init();
    MAX31856_init();
    #endif // TEMP_SENSOR
    //
    key_initialization();
    PinTo1(PORTWxKBCOL_1, PINxKBCOL_1);
    PinTo1(PORTWxKBCOL_2, PINxKBCOL_2);
    PinTo1(PORTWxKBCOL_3, PINxKBCOL_3);
    PinTo1(PORTWxKBCOL_4, PINxKBCOL_4);
    //
//    PinTo0(PORTWxTIMER_ACTV, PINxTIMER_ACTV);
//    ConfigOutputPin(CONFIGIOxTIMER_ACTV, PINxTIMER_ACTV);

    RELAY1_OFF();
    RELAY2_OFF();
    ConfigOutputPin(CONFIGIOxRELAY1, PINxRELAY1);
    ConfigOutputPin(CONFIGIOxRELAY2, PINxRELAY2);
    //
    main_flag.process_disp_enable = 1;
    eeprom_read_block(&sram_param, &eep_param, sizeof(struct _eep_param));
    //
#define CTC_SET_OCRnA(CTC_FREQ, CTC_PRESCALER) ( (uint8_t)( (F_CPU/ (2.0*CTC_PRESCALER*CTC_FREQ)) -1) )//q la division sea entre decimals
    TCNT1 = 0x0000;//if no zero, -> t= 1/(16e6/1024) -> t*(65535-77) = 4.18s
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10); //CTC PRES=256
    OCR1A = 1249;//CTC_SET_OCRnA( 25, 64);// 25Hz-> cada 20ms , prees=256 --> 1249
    TIMSK1 |= (1 << OCIE1A); //TIMSK1 = (1<<OCIE1A);
    sei();
    //
    reset_all();

    //
    #if TEMP_SENSOR == TEMP_SENSOR_INA129
    #else
    PinTo0(PORTWxSPI_SS, PINxSPI_SS);
    __delay_ms(10);
    PinTo1(PORTWxSPI_SS, PINxSPI_SS);
    //__delay_ms(500);//min. tiempo x 16 samples averaged
    #endif // TEMP_SENSOR
//    while (!temper_actual_get_new())
//    {;}
//    temper_display(temper_actual);
//    //
    PID_init();
    PID_set_setpoint(sram_param.Temp_sp);
}

void temper_format_print(int16_t temper, char *str_out);

void tempe(int16_t temper)
{
    char str[10];
    temper_format_print( (int16_t)temper, str);
    lcdan_set_cursor_in_row1(0x03);
    lcdan_print_string(str);
}

int8_t MAX3156_read_coldj(void);
void coldj(int8_t temper)
{
    char str[10];
    temper_format_print( (int8_t)temper, str);
    lcdan_set_cursor_in_row0(0x03);
    lcdan_print_string(str);
}

void tch_minus_tcj(int16_t temper)//    int16_t tcj, tch, diff;
{
    char str[10];
    temper_format_print( (int8_t)temper, str);
    lcdan_set_cursor_in_row0(0x0A);
    lcdan_print_string(str);
}
int main(void)
{
    static int8_t sm0, sm1;
    setup();

//    int16_t tcj, tch, diff;
//    lcdan_clear();
//    while (1)
//    {
//        tcj = MAX3156_read_coldj();
//        coldj(tcj);
//
//        tch = MAX3156_read_temp();
//        tempe(tch);
//
//        diff = tcj - 25;
//        tch_minus_tcj(tch-diff);
//
//        __delay_ms(450);
//    }

//    while (1)
//    {
//
//        RELAY2_ON();
//        RELAY1_ON();
//        __delay_ms(5000);
//        RELAY2_OFF();
//        RELAY1_OFF();
//        __delay_ms(5000);
//    }

    while(1)
    {
        if (isr_flag.f20ms)//sync para toda la pasada
        {
            isr_flag.f20ms = 0;
            //
            main_flag.f20ms = 1;
        }
        // if (isr_flag.newpiece)
        // {
        //     isr_flag.newpiece  = 0;
        //     main_flag.newpiece = 1;
        // }
        // if (isr_flag.reset)
        // {
        //     isr_flag.reset  = 0;
        //     main_flag.reset = 1;
        // }
        //----------------------------
        if (main_flag.f20ms)
        {
            if (temper_actual_get_new())
            {
                if (main_flag.process_disp_enable)
                {
                    //temper_display(temper_actual);
                    process_set_texts();//reescribo todo el tema del arco producido por el relay
                }
            }
            //
            pulse_newpice();
            pulse_reset();
            kb_job();
        }
        //----------------------------
        if ( sm1 == 0)
        {
            if (kb_key_is_ready2read(KB_LYOUT_KEY_MENU))
            {
                //kb_key_was_read(KB_LYOUT_KEY_MENU);
                main_flag.process_disp_enable = 0;
                lcdan_clear();
                set_min();
                set_temper_sp();
                sm1++;
            }
        }
        else if ( sm1 == 1)
        {
            if (set_param())
            {
                sm1 = 0;
                main_flag.process_disp_enable = 1;
                process_set_texts();
            }
        }

        //----------------------------
        if (main_flag.reset)
        {
            main_flag.reset = 0;
            reset_all();
            sm0 = 0;

            #ifdef DEBUG_PROCESS
            usart_print_PSTRstring(PSTR("reset\n"));
            #endif
            main_flag.newpiece = 1; //Se induce una nueva cuenta
        }
        if (sm0 == 0)
        {

            if (main_flag.newpiece)
            {
                main_flag.newpiece = 0;

                #ifdef DEBUG_PROCESS
                usart_print_PSTRstring(PSTR("newpiece\n"));
                #endif

                timer_counter_enable = 1;
                timer_1min_reset();
                if (main_flag.process_disp_enable)
                {
                    timer_display();
                }
            }

            if (timer_counter_enable)//counter begin...
            {
                if (timer_1min() & 0x0F)//cada segundo
                {
                    if (main_flag.process_disp_enable)
                    {
                        timer_display();
                    }
                    //PinToggle(PORTWxTIMER_ACTV, PINxTIMER_ACTV);

                }
                if (timer.min >= sram_param.Tminutes_max)
                {
                    RELAY2_ON();
                    //__delay_ms(1);
                    //estabiliza el arco del relay,,no afecta el LCD
                    timer_1min_reset();
                    if (main_flag.process_disp_enable)
                    {
                        timer_display();
                        lcdan_set_cursor_in_row0(0x0D);
                        lcdan_print_PSTRstring(PSTR("ON "));
                        //
                    }
                    //
                    #ifdef DEBUG_PROCESS
                    usart_print_PSTRstring(PSTR("Temp.Control\n"));
                    #endif
                    //PinTo0(PORTWxTIMER_ACTV, PINxTIMER_ACTV);

                    main_flag.temp_control = 1;
                    //
                    PID_out_as_dutycycle = (uint8_t) PID_control(temper_actual);
                    //
                    sm0++;
                }
            }
        }
        else
        {
            if (main_flag.f20ms )
            {
                //if (++PID_access_delay >= 100)  //2s
                if (++PID_access_delay >= 500)  //10000ms = 10s
                {
                    PID_access_delay = 0;
                    PID_out_as_dutycycle = (uint8_t) PID_control(temper_actual);
                    //PID_out_as_dutycycle = 95;
                    //
                }
            }
        }

        //-------------------
        main_flag.f20ms = 0;
        kb_flush(); //no debe llamarse 2 veces seguidas a un handler de keyboard
        //sino,, la tecla q todavia no se ha limpiado, puede "ingresar"al sgte. codigo
    }
    return 0;
}

ISR(TIMER1_COMPA_vect)//cada 20ms
{
    isr_flag.f20ms = 1;
    if (main_flag.temp_control)
    {
        PID_control_output(PID_out_as_dutycycle);
        //__delay_us(50);//added for Relay arc
        //__delay_ms(1);
    }
}

int16_t  temper_actual_get_new(void)
{
    int8_t cod_ret = 0;
    static uint16_t analog_samples;
    int16_t tcj, tch, diff;

    #if TEMP_SENSOR == TEMP_SENSOR_INA129
    float temper;
    static uint32_t analog_acc;
    float analog_mean;
    float volt;
    //
    analog_acc += ADC_read(ADC_CH_6);
    #else // TEMP_SENSOR
        int16_t temper;
    #endif
    #define ANALOG_SAMPLES 50   //c 20ms*50 = 1000ms = 1s

    if (++analog_samples >= ANALOG_SAMPLES)
    {
        analog_samples = 0x00;
        #if TEMP_SENSOR == TEMP_SENSOR_INA129
        analog_mean =  (analog_acc / ANALOG_SAMPLES);
        analog_acc = 0x00;
        //
        volt = (analog_mean * 5.05) / 1023;
        temper = (m * volt) + b;
        //temper_actual = (m * volt) + b;

        #else

        tcj = MAX3156_read_coldj();
        __delay_us(1);
        tch = MAX3156_read_temp();
        diff = tcj - 25;

        temper = tch-diff;//(float) MAX3156_read_temp();
        //__delay_ms(350);//min. tiempo x 16 samples averaged
        #endif // TEMP_SENSOR

        //limits
        if (temper<0)
        {
            temper_actual = 0;
        }
        else if (temper>999)
        {
            temper_actual = 999;
        }
        else
        {
            temper_actual = temper;
        }

        //
        cod_ret = 1;
    }
    return cod_ret;
}

void temper_format_print(int16_t temper, char *str_out)
{
    char buff[10];

    itoa(temper, buff, 10); // convierte
    // 3 positions to display: 999
    strcpy(str_out, "   ");
    if (temper < 10)
    {
        strncpy(&str_out[2], buff, 1);
    }
    else if (temper < 100)
    {
        strncpy(&str_out[1], buff, 2);
    }
    else
    {
        strncpy(&str_out[0], buff, 3);
    }
}
void temper_display(float temper)
{
    char str[10];
    temper_format_print( (int16_t)temper, str);
    lcdan_set_cursor_in_row1(0x03);
    lcdan_print_string(str);
}

//t=999:12s Tc=OFF
void process_set_texts(void)
{
    if (main_flag.process_disp_enable)
    {
        //lcdan_clear();
        lcdan_set_cursor_in_row0(0x00);
        //lcdan_print_PSTRstring(PSTR("t=   m Tctrl=OFF"));
        lcdan_print_PSTRstring(PSTR("t=   :  s TC=   "));

        timer_display();//muestra la cuenta actual... no lo resetea

        //
        lcdan_set_cursor_in_row0(0x0D);
        if (main_flag.temp_control)
            lcdan_print_PSTRstring(PSTR("ON "));
        else
            lcdan_print_PSTRstring(PSTR("OFF"));
        //
        //timer_1min_reset();   //cada procesa resetea el timer a su conveniencia
        timer_display();
        lcdan_set_cursor_in_row1(0x00);
        lcdan_print_PSTRstring(PSTR("Tp=   C Tsp=   C"));


        temper_display(temper_actual);

        char str[10];
        temper_format_print(sram_param.Temp_sp, str);
        lcdan_set_cursor_in_row1(0x0C);
        lcdan_print_string(str);
    }

}
void reset_all(void)
{
    newpiece_counter = 0;
    timer_counter_enable = 0;
    main_flag.temp_control = 0;
    //
    PID_out_as_dutycycle = 0;
    PID_access_delay = 0;
    //
    timer_1min_reset();//
    process_set_texts();

    RELAY1_OFF();
    RELAY2_OFF();
//    PinTo0(PORTWxTIMER_ACTV, PINxTIMER_ACTV);
}

int8_t timer_1min(void)
{
    int8_t cod_ret=0;
    if (main_flag.f20ms )
    {
        if (++timer.ticks >= (50) ) //1s
        {
            timer.ticks = 0x00;

            cod_ret=0x1;
            if (++timer.sec > 59)
            {
                timer.sec  =  0x00;

                cod_ret|=(0x1<<4);
                //
                if (++timer.min > TMINUTES_MAX)
                {
                    timer.min = 0x0000;
                }
            }
        }
    }
    return cod_ret;
}

void timer_1min_reset(void)
{
    // min_ticks = 0x0000;
    // min_counter = 0x0000;

    timer.ticks = 0;
    timer.sec = 0;
    timer.min = 0;
}

void minutes_format_print(int16_t min, int16_t sec, char *str_out)
{
    char buff[10];
    itoa(min, buff, 10); // convierte

    strcpy(str_out, "   :0 ");
    if (min < 10)
    {
        strncpy(&str_out[2], buff, 1);
    }
    else if (min < 100)
    {
        strncpy(&str_out[1], buff, 2);
    }
    else
    {
        strncpy(&str_out[0], buff, 3);
    }
    //
    itoa(sec, buff, 10); // convierte
    if (sec < 10)
    {
        strncpy(&str_out[5], buff, 1);
    }
    else if (min < 100)
    {
        strncpy(&str_out[4], buff, 2);
    }
}

void timer_display(void)
{
    char str[10];
    minutes_format_print(timer.min, timer.sec, str);
    lcdan_set_cursor_in_row0(0x02);
    lcdan_print_string(str);
}
///////////


void pulse_newpice(void)
{
    static int8_t sm0;
    int8_t p = ReadPin(PORTRxNEWPIECE, PINxNEWPIECE);

    if (sm0 == 0)
    {
        if (p == 1)
            sm0++;
    }
    else if (sm0 == 1)
    {
        if (p != 1)
            sm0--;
        else
        {
            main_flag.newpiece = 1;
            sm0++;
        }
    }
    else if (sm0 == 2)
    {
        if (p == 0)
            sm0++;
    }
    else if (sm0 == 3)
    {
        if (p != 0)
            sm0--;
        else
            sm0 = 0x00;
    }
}
void pulse_reset(void)
{
    static int8_t sm0;
    int8_t p = ReadPin(PORTRxRESET, PINxRESET);

    if (sm0 == 0)
    {
        if (p == 1)
            sm0++;
    }
    else if (sm0 == 1)
    {
        if (p != 1)
            sm0--;
        else
        {
            main_flag.reset = 1;
            sm0++;
        }
    }
    else if (sm0 == 2)
    {
        if (p == 0)
            sm0++;
    }
    else if (sm0 == 3)
    {
        if (p != 0)
            sm0--;
        else
            sm0 = 0x00;
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void set_temper_sp(void)
{
    int8_t idx_ascursor;

    lcdan_set_cursor_in_row0(0x00);
    lcdan_print_PSTRstring(PSTR("Temp[sp]=    C  "));
    //

    num_textedit_disp_set_x(0x09);
    num_textedit_disp_set_y(0);
    num_textedit_valuelimits_set_max(TEMPER_MAX);
    num_textedit_valuelimits_set_min(TEMPER_MIN);//por ahora num_textedit manejo enteros positivos
    num_textedit_set_num_digits(3);
    //
    idx_ascursor = num_textedit_set_value_as_char(sram_param.Temp_sp);
    num_textedit_hwspecific_print_disp(idx_ascursor);
}

void set_min(void)
{
    int8_t idx_ascursor;

    lcdan_set_cursor_in_row1(0x00);
    lcdan_print_PSTRstring(PSTR("Tiempo=    min  "));
    //

    num_textedit_disp_set_x(0x07);
    num_textedit_disp_set_y(1);
    num_textedit_valuelimits_set_max(TMINUTES_MAX);
    num_textedit_valuelimits_set_min(TMINUTES_MIN);//por ahora num_textedit manejo enteros positivos
    num_textedit_set_num_digits(3);
    //
    idx_ascursor = num_textedit_set_value_as_char(sram_param.Tminutes_max);
    num_textedit_hwspecific_print_disp(idx_ascursor);
}

int8_t set_param(void)
{
    //static int8_t sm0;
    static int8_t c;
    int8_t idx_ascursor;
    int8_t cod_ret = 0;

    struct _kb_num_textedit_actionhandler actionhandler;
    kb_num_textedit_actionhandler(&actionhandler);//recoge la accion especifica

    if (actionhandler.char_dig == 'E')//Enter
    {

        if (c == 0)
        {
            //graba directamente el valor de temperatura
            sram_param.Temp_sp = num_textedit_get_value_as_int();

            //cambia de layout
            num_textedit_disp_set_x(0x07);
            num_textedit_disp_set_y(1);
            num_textedit_valuelimits_set_max(TMINUTES_MAX);
            num_textedit_valuelimits_set_min(TMINUTES_MIN);//por ahora num_textedit manejo enteros positivos
            num_textedit_set_num_digits(3);
            //
            idx_ascursor = num_textedit_set_value_as_char(sram_param.Tminutes_max);
            num_textedit_hwspecific_print_disp(idx_ascursor);
        }
        else
        {
            //graba directamente el valor de minutos
            sram_param.Tminutes_max = num_textedit_get_value_as_int();
            //cambia de layout
            num_textedit_disp_set_x(0x09);
            num_textedit_disp_set_y(0);
            num_textedit_valuelimits_set_max(TEMPER_MAX);
            num_textedit_valuelimits_set_min(TEMPER_MIN);//por ahora num_textedit manejo enteros positivos
            num_textedit_set_num_digits(3);
            //
            idx_ascursor = num_textedit_set_value_as_char(sram_param.Temp_sp);
            num_textedit_hwspecific_print_disp(idx_ascursor);
        }

        if (++c > 1)
        {
            c = 0;
        }
        //cod_ret = 1;
    }
    if (kb_key_is_ready2read(KB_LYOUT_KEY_2ND))//cancela la edicion
    {
        //kb_key_was_read(KB_LYOUT_KEY_2ND);
        //
        lcdan_write_cmd(LCDAN_DISP_ON_CURSOR_OFF_BLINK_OFF);

        if (c == 0)
            sram_param.Temp_sp = num_textedit_get_value_as_int();
        else
            sram_param.Tminutes_max = num_textedit_get_value_as_int();

        c = 0x00;//bug fix!

        eeprom_update_block(&sram_param, &eep_param, sizeof(struct _eep_param));

        PID_set_setpoint(sram_param.Temp_sp);

        cod_ret = 1;
    }
    return cod_ret;
}





