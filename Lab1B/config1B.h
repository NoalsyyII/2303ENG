#ifndef CONFIG1B_H
#define CONFIG1B_H
#include <stdio.h>
#include <stdint.h>

void enablePKOutput(){

    SYSCTL->RCGCGPIO |= 1 << 9;

    while(!(SYSCTL->PRGPIO & 1 << 9)){}

    uint32_t ports = 0b111;

    GPIOK->DIR |= ports;
    GPIOK->AFSEL &= ~(ports);
    GPIOK->AMSEL &= ~(ports);
    GPIOK->DEN |= ports;
    GPIOK->DR2R |= ports;
    
}

void enablePEInput(){
    
    SYSCTL->RCGCGPIO |= 1 << 4;

    while(!(SYSCTL->PRGPIO & 1 << 4)){}

    uint32_t ports = 0b1111;

    GPIOE->DIR &= ~(ports);
    GPIOE->AFSEL &= ~(ports);
    GPIOE->AMSEL &= ~(ports);
    GPIOE->DEN |= ports;
    GPIOE->PDR |= ports;

}

#endif