#include <stdlib.h>
#include <TM4C129.h>
#include "../lib/pwm.h"
#include "../lib/ES.h"

/*

Axis numbering system:

*/

void movement_test(){
	int i = 650;
	int direction = 1;
	
	while(1){
		ES_msDelay(20);
		PWM1_pulse_width(i);
		if(i < 1500){
				i += direction * 25;
			} else if(i <= 600){
				break;
			}	else {
				direction *= -1;
				i+= direction * 25;
			}
	}
	
	while(1){
		ES_msDelay(20);
		PWM2_pulse_width(i);
		if(i < 1500){
				i += direction * 25;
			} else if(i <= 600){
				break;
			}	else {
				direction *= -1;
				i+= direction * 25;
			}
	}
	
	while(1){
		ES_msDelay(20);
		PWM3_pulse_width(i);
		if(i < 1500){
				i += direction * 25;
			} else if(i <= 600){
				break;
			}	else {
				direction *= -1;
				i+= direction * 25;
			}
	}
	
	while(1){
		ES_msDelay(20);
		PWM4_pulse_width(i);
		if(i < 1500){
				i += direction * 25;
			} else if(i <= 600){
				break;
			}	else {
				direction *= -1;
				i+= direction * 25;
			}
	}
	
	while(1){
		ES_msDelay(20);
		PWM5_pulse_width(i);
		if(i < 1500){
				i += direction * 25;
			} else if(i <= 600){
				break;
			}	else {
				direction *= -1;
				i+= direction * 25;
			}
	}
	
	while(1){
		ES_msDelay(20);
		PWM6_pulse_width(i);
		if(i < 1500){
				i += direction * 25;
			} else if(i <= 600){
				break;
			}	else {
				direction *= -1;
				i+= direction * 25;
			}
	}
}

void raw_set_axis(int axis, int degree){

    if(degree < 0 || degree > 180){
        return;
    }

    switch(axis){
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
    }

}

void raw_increment_axis(int axis){}

void raw_decrement_axis(int axis){}