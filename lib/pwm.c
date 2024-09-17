#include <stdlib.h>
#include <TM4C129.h>

void PWM0_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 5)
    while(!(SYSCTL->PRGPIO & (1 << 5)));

    int PF0 = 1 << 0;
    GPIOF_AHB->AFSEL |= PF0;
    GPIOF_AHB->PCTL |= 6; // Use PF0 as M0PWM0
    GPIOF_AHB->DEN |= PF0;

    PWM0->CC |= (1 << 8); // use PWM scaled clock as unit clock
    PWM0->CC |= 0x103; // divide system clock by 16, for 1MHz reference clock

    PWM0->_0_CTL = 0;
    PWM->_0_GENA-> |= 0x1; //invert signal when counter = 0 - easy for now

    PWM0->_ENABLE |= (1 << 0);

}

void PWM0_freq(int freq){

    //1MHz clock
    PWM->CTL &= ~ (1 << 0); //disable pwm
    PWM0->_0_LOAD = freq * 1000000; // load value
    PWM->CTL |= (1 << 0);

}