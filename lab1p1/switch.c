/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#include <xc.h>
#include "switch.h"



void initSW2(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISAbits.TRISA7=1;
    CNPUAbits.CNPUA7=1;
    CNCONAbits.ON=1;        //ask if we truly need cn for switch 
    CNENAbits.CNIEA7=1;        //check
    IFS1bits.CNAIF=0;
    IEC1bits.CNAIE=1;
    IPC8bits.CNIP=7;        //check
}
