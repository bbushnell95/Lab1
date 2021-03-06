/*
 * File:         switch.c
 * Date:         2-22-2016
 * Software Designer: Ryan Trumpinski
 * Hardware Designer: Brett Bushnell
 * Quality Assurance: Sydney Clark
 * Systems Integrator: Matt Dzurick
 *
 * Created on September 19, 2015, 10:46 AM
 */

#include <xc.h>

void initSwitch1(){         //initialize switch and pull up resistor
    TRISDbits.TRISD6=1;
    CNPUDbits.CNPUD6=1;
    CNCONDbits.ON=1;        //turn on CN for port D
    CNENDbits.CNIED6=1;        //check
    IFS1bits.CNDIF=0;
    IEC1bits.CNDIE=1;
    IPC8bits.CNIP=7;       //check
}


void initSW2(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISAbits.TRISA7=1;
    CNPUAbits.CNPUA7=1;
    CNCONAbits.ON=1;        
    CNENAbits.CNIEA7=1;        //check
    IFS1bits.CNAIF=0;
    IEC1bits.CNAIE=1;
    IPC8bits.CNIP=7;        //check
}
