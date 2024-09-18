#include <stdlib.h>
#include <TM4C129.h>

void PWM1_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 5);
    while(!(SYSCTL->PRGPIO & (1 << 5)));

    int PF1 = 1 << 1;
    GPIOF_AHB->AFSEL |= PF1;
    GPIOF_AHB->PCTL |= 6 << 4; // Use PF1 as M0PWM1
    GPIOF_AHB->DEN |= PF1;

    //PWM0->CC |= (1 << 8); // use PWM scaled clock as unit clock
    PWM0->CC = (1 << 8) | (0x5); // divide system clock by 64, for 250KHz reference clock

    PWM0->_0_CTL = 0;
    PWM0->_0_GENB |= (0x1) | (1 << 6); //invert signal when counter = 0 or when counter = comp

		PWM0->ENABLE |= (1 << 1);
    
}

void PWM1_setup(int freq, int duty_percent){

		uint32_t load_value = 250000 / freq;
	
		float duty_cycle = duty_percent/100.0 ;
		
		uint32_t comparator_value = load_value * (duty_cycle);
		
		//check for integer overflow - LOAD and COMP registers are only 16 bit!
		if(load_value > 65536){
			load_value = 65536;
		}
		
		if(comparator_value > 65536){
			comparator_value = 65536;
		}
	
    //250KHz clock
    PWM0->_0_CTL &= ~ (1 << 0); //disable pwm
    PWM0->_0_LOAD = load_value;
		PWM0->_0_CMPA = comparator_value;
    PWM0->_0_CTL |= (1 << 0);
		
}

void PWM1_pulse_width(int micro_sec){
	//assumes an operating freqency of 50Hz - as required by the servos
	
	//20ms period
	 
	int comparator_load = 25 * micro_sec;
	
	PWM0->_0_CTL &= ~ (1 << 0); //disable pwm
	PWM0->_0_CMPA = comparator_load;
	PWM0->_0_CTL |= (1 << 0);
	
}