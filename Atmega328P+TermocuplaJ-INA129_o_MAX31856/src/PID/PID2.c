#include "../system.h"
#include "../main.h"
#include "../usart/usart.h"
//#include "../temper.h"
#include "PID.h"

struct _PID
{
    int16_t setpoint;

    float K_proportional;
    float K_integral;
    float K_derivative;
    //
    int16_t error_integral;
    int16_t previous_error;
    int16_t error_derivative;
};

struct _PID PID;

/*****************************************************
*****************************************************/
void PID_set_setpoint(int16_t sp)
{
    PID.setpoint = sp;
}
int16_t PID_get_setpoint(void)
{
    return PID.setpoint;
}
void PID_reset_errors(void)
{
    //PID.initial_error = PID.setpoint - temper_measured;
    PID.error_integral = 0;
    PID.previous_error = 0;
}

void PID_init(void)//cambiar de nombre
{
    PID_reset_errors();

    //for solid relay...OK
    // PID.K_proportional = 1.6;
    // PID.K_integral = 1.1;
    // PID.K_derivative = 0;

     //for mechanical relay...OK
    PID.K_proportional = 5;
    PID.K_integral = 5;
    PID.K_derivative = 3;
}
/*****************************************************
*****************************************************/
#ifdef DEBUG_PROCESS
#define PID_CONTROL_DEBUG
#endif // DEBUG_PROCCES
int16_t PID_control(int16_t pv)
{
    int16_t error;
    int16_t PID_output;
    int8_t _pid_integral_windup;
    error = PID.setpoint - pv;

    #ifdef PID_CONTROL_DEBUG
    char str[10];
    itoa(error, str, 10);
    usart_print_PSTRstring(PSTR("\nE:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG
    //
    PID.error_integral = PID.error_integral + error;

    #ifdef PID_CONTROL_DEBUG
    itoa(PID.error_integral, str, 10);
    usart_print_PSTRstring(PSTR("EIb:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG

    //_pid_integral_windup =  10;//10;//10 era el valor optimizado??

    if (error > 25)
    {
        _pid_integral_windup =  50;//70;//ok con etas ktes...
    }
    else if (error > 10)
    {
        if (pv > 80)
        {
            _pid_integral_windup =  10;
        }
        else if (pv > 60)
        {__delay_us(50);//added for Relay arc
            _pid_integral_windup =  5;
        }
        else if (pv > 40)
        {
            _pid_integral_windup =  3;
        }
        else if (pv > 20 )
        {
            _pid_integral_windup =  2;
        }
        else
        {
            _pid_integral_windup =  2;
        }
    }
    else
    {
	if (pv > 80)
        {
            _pid_integral_windup =  1;
        }
        else if (pv > 60)
        {
            _pid_integral_windup =  1;
        }
        else if (pv > 40)
        {
            _pid_integral_windup =  1;
        }
        else if (pv > 20 )
        {
            _pid_integral_windup =  1;
        }
        else
        {
            _pid_integral_windup =  1;
        }

    }


    // if (error > 25)
    // {
    //     _pid_integral_windup =  90;//70;//ok con etas ktes...
    // }

    if (PID.error_integral > _pid_integral_windup)//integral windup
        {PID.error_integral = _pid_integral_windup;}
    else if(PID.error_integral < 0)//-_pid_integral_windup)
        {PID.error_integral = 0;}//-_pid_integral_windup;}//-10;

    #ifdef PID_CONTROL_DEBUG
    itoa(PID.error_integral, str, 10);
    usart_print_PSTRstring(PSTR("EIa:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG
    //
    //
    #ifdef PID_CONTROL_DEBUG
    itoa(PID.previous_error, str, 10);
    usart_print_PSTRstring(PSTR("pEDb:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG

    PID.error_derivative = error - PID.previous_error;

    #ifdef PID_CONTROL_DEBUG
    itoa(PID.error_derivative , str, 10);
    usart_print_PSTRstring(PSTR("ED:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG

    PID.previous_error = error;

    #ifdef PID_CONTROL_DEBUG
    itoa(PID.previous_error, str, 10);
    usart_print_PSTRstring(PSTR("pEDa:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG
    //
    PID_output = (PID.K_proportional*error) + (PID.K_integral*PID.error_integral) + (PID.K_derivative*PID.error_derivative);

    #ifdef PID_CONTROL_DEBUG
    itoa(PID_output, str, 10);
    usart_print_PSTRstring(PSTR("Ob:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG

    if(PID_output > PID_CONTROL_OUTPUT_MAX)
        {PID_output = PID_CONTROL_OUTPUT_MAX;}
    else if(PID_output < 0)
        {PID_output = 0;}

    #ifdef PID_CONTROL_DEBUG
    itoa(PID_output, str, 10);
    usart_print_PSTRstring(PSTR("Oa:"));usart_println_string(str);
    #endif // PID_CONTROL_DEBUG
    //
    return PID_output;
}

/*****************************************************
PID_control_output call from ISR (MECHANICAL STATE RELAY: CYCLE TIME 10s)
*****************************************************/
#define PWM_BASETIME_COUNTER_MAX 5//20ms * 5 100ms
#define PWM_PERIOD_COUNTER_MAX PID_CONTROL_OUTPUT_MAX //

void PID_control_output(uint8_t pwm_dutycycle)
{
    static uint8_t pwm_basetime_counter;
    static uint8_t pwm_dutycycle_counter;
    static uint8_t pwm_period_counter;
    static uint8_t pwm_onoff=1;

    if (++pwm_basetime_counter >= PWM_BASETIME_COUNTER_MAX)
    {
        pwm_basetime_counter= 0x00;
        //Cada 100ms
        if (pwm_onoff==1)
        {
            if (pwm_dutycycle>0)
            {

                RELAY1_ON();//PinTo1(PORTWxRELAY1 PINxRELAY1;


                if (++pwm_dutycycle_counter >= pwm_dutycycle)//0--100
                {
                    pwm_dutycycle_counter = 0;
                    //
                    if (pwm_dutycycle < PWM_PERIOD_COUNTER_MAX)
                        {
                            RELAY1_OFF();//PinTo0(PORTWxRELAY1 PINxRELAY1;
                        } //only if less than

                    pwm_onoff = 0;
                }
            }
            else
                {
                    RELAY1_OFF();//PinTo0(PORTWxRELAY1 PINxRELAY1;
                }
        }
        if (++pwm_period_counter >= PWM_PERIOD_COUNTER_MAX)//PID_CONTROL_OUTPUT_MAX
        {
            pwm_period_counter = 0x00;
            pwm_onoff = 1;//begin new period
        }
    }
}
