#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "../lib/pwm.h"
#include "../lib/ES.h"

int main(){
	
		ES_setSystemClk(16); //set clock 16MHz
		
		PWM1_init();
	
		PWM1_setup(50, 5);
		ES_msDelay(1000);
		PWM1_pulse_width(25);

    while(1){}

    return 0;
}