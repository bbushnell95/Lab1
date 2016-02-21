/*
 * File:         leds.c
 * Date:         2-22-2016
 * Software Designer: Ryan Trumpinski
 * Hardware Designer: Brett Bushnell
 * Quality Assurance: Sydney Clark
 * Systems Integrator: Matt Dzurick
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
    ODCGbits.ODCG12=1;
    ODCGbits.ODCG14=1;
    TRISGbits.TRISG12=OUTPUT;
    TRISGbits.TRISG14=OUTPUT;
    
    LATGbits.LATG12=1;
    LATGbits.LATG14=1;
    
    LEDRUN=ON;
    LEDSTOP=ON;
    
}