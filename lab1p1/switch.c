/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#include <xc.h>

void initSwitch1(){         //initialize switch and pull up resistor
    TRISDbits.TRISD6=1;
    CNPUDbits.CNPUD6=1;
    CNCONDbits.ON=0;        //turn on CN for port D
}


void initSW2(){
    TRISAbits.TRISA7=1;     //configure as input
    CNPUAbits.CNPUA7=1;
    CNCONAbits.ON=1;        
    CNENAbits.CNIEA7=1;        //enable change notification
    IFS1bits.CNAIF=0;
    IEC1bits.CNAIE=1;
    IPC8bits.CNIP=7;        //set priority
}
