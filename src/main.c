#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "../lib/pwm.h"
#include "../lib/ES.h"
#include "../lib/positioning.h"

int main(){
	
		ES_setSystemClk(16); //set clock 16MHz
	
		PWM_block_setup(1);
		PWM_block_setup(2);
		PWM_block_setup(3);
		PWM_block_setup(4);
		
		int i = 625;
		int axis = 1, direction = 1;
		int lastaxis = 0;

    while(1){
		ES_msDelay(20);
			
			switch(axis){
			case 1:
				PWM1_pulse_width(i);
				break;
			case 2:
				PWM2_pulse_width(i);
				break;
			case 3:
				PWM3_pulse_width(i);
				break;
			case 4:
				PWM4_pulse_width(i);
				break;
			case 5:
				PWM5_pulse_width(i);
			break;
			case 6:
				PWM6_pulse_width(i);
				break;
			}
			
		if(i >= 2000){
			direction = 0;
			lastaxis = axis;
		} else if(i <= 600){
			direction = 1;
		}
		
		if(axis == lastaxis){
			i = 625;
			if(axis == 6){
				axis = 1;
				continue;
			} else{
			axis++;
			}
		}
		
		if(direction){
		i += 10;
		} else{
			i -= 10;
		}
			
		}

    return 0;
}