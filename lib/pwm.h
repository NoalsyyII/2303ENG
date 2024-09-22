#ifndef PWM_H
#define PWM_H

extern void PWM1_init();
extern void PWM1_setup(int freq, int duty_percent);
extern void PWM1_pulse_width(int micro_sec);

extern void PWM2_init();
extern void PWM2_setup(int freq, int duty_percent);
extern void PWM2_pulse_width(int micro_sec);

extern void PWM3_init();
extern void PWM3_setup(int freq, int duty_percent);
extern void PWM3_pulse_width(int micro_sec);

extern void PWM4_init();
extern void PWM4_setup(int freq, int duty_percent);
extern void PWM4_pulse_width(int micro_sec);

extern void PWM5_init();
extern void PWM5_setup(int freq, int duty_percent);
extern void PWM5_pulse_width(int micro_sec);

extern void PWM6_init();
extern void PWM6_setup(int freq, int duty_percent);
extern void PWM6_pulse_width(int micro_sec);

#endif