#ifndef PWM_H
#define PWM_H

extern void PWM1_init();

extern void PWM1_setup(int freq, int duty_percent);

extern void PWM1_pulse_width(int micro_sec);


#endif