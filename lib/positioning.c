#include <stdlib.h>
#include <TM4C129.h>

/*

Axis numbering system:

*/

void raw_set_axis(int axis, degree){

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