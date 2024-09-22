#include <stdlib.h>
#include <TM4C129.h>

/*
- PWM signals are tied together in blocks (see below)
- Output signals for each block will be the same FREQUENCY, duty cycles can be changed using comparator loads
- Any PWMX_setup() call will alter the frequency of the entire block, but only change the duty cycle of PWM X
- Calls to PWMX_pulse_width() are the preferred method for signal changes during operation

Block 1: PWM1
Block 2: PWM2, PWM3
Block 3: PWM4, PWM5
Block 4: PWM6 

*/

void PWM1_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 5);
    while(!(SYSCTL->PRGPIO & (1 << 5)));

    int PF1 = 1 << 1;
    GPIOF_AHB->AFSEL |= PF1;
    GPIOF_AHB->PCTL |= 6 << 4; // Use PF1 as M0PWM1
    GPIOF_AHB->DEN |= PF1;

    PWM0->CC = (1 << 8) | (0x5); // divide system clock by 64, for 250KHz reference clock

    PWM0->_0_CTL = 0;
    PWM0->_0_GENB |= (0x1) | (1 << 10); //invert signal when counter = 0 or when counter = compB

	PWM0->ENABLE |= (1 << 1);
    
}

void PWM2_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 5);
    while(!(SYSCTL->PRGPIO & (1 << 5)));

    int PF2 = 1 << 2;
    GPIOF_AHB->AFSEL |= PF2;
    GPIOF_AHB->PCTL |= 6 << 8; // Use PF2 as M0PWM2
    GPIOF_AHB->DEN |= PF2;

    PWM0->CC = (1 << 8) | (0x5); // divide system clock by 64, for 250KHz reference clock

    PWM0->_1_CTL = 0;
    PWM0->_1_GENA |= (0x1) | (1 << 6); //invert signal when counter = 0 or when counter = comp

	PWM0->ENABLE |= (1 << 1);
    
}

void PWM3_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 5);
    while(!(SYSCTL->PRGPIO & (1 << 5)));

    int PF3 = 1 << 3;
    GPIOF_AHB->AFSEL |= PF3;
    GPIOF_AHB->PCTL |= 6 << 12; // Use PF3 as M0PWM3
    GPIOF_AHB->DEN |= PF3;

    PWM0->CC = (1 << 8) | (0x5); // divide system clock by 64, for 250KHz reference clock

    PWM0->_1_CTL = 0;
    PWM0->_1_GENB |= (0x1) | (1 << 10); //invert signal when counter = 0 or when counter = compB

	PWM0->ENABLE |= (1 << 1);
    
}

void PWM4_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 6);
    while(!(SYSCTL->PRGPIO & (1 << 6)));

    int PG0 = 1 << 0;
    GPIOG_AHB->AFSEL |= PG0;
    GPIOG_AHB->PCTL |= 6 << 0; // Use PG0 as M0PWM4
    GPIOG_AHB->DEN |= PG0;

    PWM0->CC = (1 << 8) | (0x5); // divide system clock by 64, for 250KHz reference clock

    PWM0->_2_CTL = 0;
    PWM0->_2_GENA |= (0x1) | (1 << 6); //invert signal when counter = 0 or when counter = comp

	PWM0->ENABLE |= (1 << 1);
    
}

void PWM5_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 6);
    while(!(SYSCTL->PRGPIO & (1 << 6)));

    int PG1 = 1 << 1;
    GPIOG_AHB->AFSEL |= PG1;
    GPIOG_AHB->PCTL |= 6 << 4; // Use PG1 as M0PWM5
    GPIOG_AHB->DEN |= PG1;

    PWM0->CC = (1 << 8) | (0x5); // divide system clock by 64, for 250KHz reference clock

    PWM0->_2_CTL = 0;
    PWM0->_2_GENB |= (0x1) | (1 << 10); //invert signal when counter = 0 or when counter = compB

	PWM0->ENABLE |= (1 << 1);
    
}

void PWM6_init(){

    SYSCTL->RCGCPWM |= (1 << 0);
    while(!(SYSCTL->PRPWM & (1 << 0)));

    SYSCTL->RCGCGPIO |= (1 << 10);
    while(!(SYSCTL->PRGPIO & (1 << 10)));

    int PK4 = 1 << 4;
    GPIOK->AFSEL |= PK4;
    GPIOK->PCTL |= 6 << 4; // Use PK4 as M0PWM6
    GPIOK->DEN |= PK4;

    PWM0->CC = (1 << 8) | (0x5); // divide system clock by 64, for 250KHz reference clock

    PWM0->_3_CTL = 0;
    PWM0->_3_GENA |= (0x1) | (1 << 6); //invert signal when counter = 0 or when counter = comp

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
	PWM0->_0_CMPB = comparator_value;
    PWM0->_0_CTL |= (1 << 0);
		
}

void PWM2_setup(int freq, int duty_percent){

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
    PWM0->_1_CTL &= ~ (1 << 0); //disable pwm
    PWM0->_1_LOAD = load_value;
	PWM0->_1_CMPA = comparator_value;
    PWM0->_1_CTL |= (1 << 0);
		
}

void PWM3_setup(int freq, int duty_percent){

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
    PWM0->_1_CTL &= ~ (1 << 0); //disable pwm
    PWM0->_1_LOAD = load_value;
	PWM0->_1_CMPB = comparator_value;
    PWM0->_1_CTL |= (1 << 0);
		
}

void PWM4_setup(int freq, int duty_percent){

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
    PWM0->_2_CTL &= ~ (1 << 0); //disable pwm
    PWM0->_2_LOAD = load_value;
	PWM0->_2_CMPA = comparator_value;
    PWM0->_2_CTL |= (1 << 0);
		
}

void PWM5_setup(int freq, int duty_percent){

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
    PWM0->_2_CTL &= ~ (1 << 0); //disable pwm
    PWM0->_2_LOAD = load_value;
	PWM0->_2_CMPB = comparator_value;
    PWM0->_2_CTL |= (1 << 0);
		
}

void PWM6_setup(int freq, int duty_percent){

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
    PWM0->_3_CTL &= ~ (1 << 0); //disable pwm
    PWM0->_3_LOAD = load_value;
	PWM0->_3_CMPA = comparator_value;
    PWM0->_3_CTL |= (1 << 0);
		
}

void PWM1_pulse_width(int micro_sec){
	//assumes an operating freqency of 50Hz - as required by the servos
	
	//20ms period
	 
	int comparator_load = 25 * micro_sec;
	
	PWM0->_0_CTL &= ~ (1 << 0); //disable pwm
	PWM0->_0_CMPB = comparator_load;
	PWM0->_0_CTL |= (1 << 0);
	
}

void PWM2_pulse_width(int micro_sec){
	//assumes an operating freqency of 50Hz - as required by the servos
	
	//20ms period
	 
	int comparator_load = 25 * micro_sec;
	
	PWM0->_1_CTL &= ~ (1 << 0); //disable pwm
	PWM0->_1_CMPA = comparator_load;
	PWM0->_1_CTL |= (1 << 0);
	
}

void PWM3_pulse_width(int micro_sec){
	//assumes an operating freqency of 50Hz - as required by the servos
	
	//20ms period
	 
	int comparator_load = 25 * micro_sec;
	
	PWM0->_1_CTL &= ~ (1 << 0); //disable pwm
	PWM0->_1_CMPB = comparator_load;
	PWM0->_1_CTL |= (1 << 0);
	
}

void PWM4_pulse_width(int micro_sec){
	//assumes an operating freqency of 50Hz - as required by the servos
	
	//20ms period
	 
	int comparator_load = 25 * micro_sec;
	
	PWM0->_2_CTL &= ~ (1 << 0); //disable pwm
	PWM0->_2_CMPA = comparator_load;
	PWM0->_2_CTL |= (1 << 0);
	
}

void PWM5_pulse_width(int micro_sec){
	//assumes an operating freqency of 50Hz - as required by the servos
	
	//20ms period
	 
	int comparator_load = 25 * micro_sec;
	
	PWM0->_2_CTL &= ~ (1 << 0); //disable pwm
	PWM0->_2_CMPB = comparator_load;
	PWM0->_2_CTL |= (1 << 0);
	
}

void PWM6_pulse_width(int micro_sec){
	//assumes an operating freqency of 50Hz - as required by the servos
	
	//20ms period
	 
	int comparator_load = 25 * micro_sec;
	
	PWM0->_3_CTL &= ~ (1 << 0); //disable pwm
	PWM0->_3_CMPA = comparator_load;
	PWM0->_3_CTL |= (1 << 0);
	
}