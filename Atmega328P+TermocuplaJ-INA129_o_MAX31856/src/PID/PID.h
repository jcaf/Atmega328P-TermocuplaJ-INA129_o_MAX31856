#ifndef PID_H_
#define PID_H_

#define PID_CONTROL_OUTPUT_MAX 100//ahora 100*20ms = 2s

void 	PID_init(void);
void 	PID_reset_errors(void);
int16_t PID_control(int16_t pv);
void 	PID_set_setpoint(int16_t sp);
int16_t PID_get_setpoint(void);
void 	PID_control_output(uint8_t pwm_dutycycle);

#endif // PID_H_
