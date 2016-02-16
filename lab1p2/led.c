#include <proc/p32mx470f512l.h>

#include "led.h"


void initLEDs(){
    TRISDbits.TRISD0 = 0;
    
    
    LATDbits.LATD0 = 1;
}
