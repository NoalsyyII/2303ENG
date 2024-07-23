#ifndef BITSANDPIECES_H
#define BITSANDPIECES_H
#include <stdint.h>

//Sets bits in the range [start, stop] for a 32-bit value or register
void setBits(uint32_t* number, int start, int stop){
    
    if(stop < start || start < 0 || stop >= 32){
        return;
    }

    uint32_t mask = ((1 << (stop - start + 1)) - 1) << start;

    *number |= mask;
}

//Clears bits in the range [start, stop] for a 32-bit value or register
void clearBits(uint32_t* number, int start, int stop){

    if(stop < start || start < 0 || stop >= 32){
        return;
    }

    uint32_t mask = ~((1 << (stop - start + 1)) - 1) << start;

    *number &= mask;
}


#endif