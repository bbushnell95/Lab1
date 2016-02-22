/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>

#define LEDRUN LATGbits.LATG12  
#define LEDSTOP LATGbits.LATG14
#define ON 1
#define OFF 0
#define OUTPUT 0

void initLEDs(){
    ODCGbits.ODCG12=1;          //enables ODC for leds
    ODCGbits.ODCG14=1;
    TRISGbits.TRISG12=OUTPUT;      //configure LEDS as outputs
    TRISGbits.TRISG14=OUTPUT;
    
    LATGbits.LATG12=1;              //Turn latches on
    LATGbits.LATG14=1;
    
    LEDRUN=ON;                      //initialize leds
    LEDSTOP=OFF;
    
}