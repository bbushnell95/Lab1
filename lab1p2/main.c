// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "timer.h"
#include "interrupt.h"
#include "lcd.h"


// ******************************************************************************************* //
//void testDelayUs();
//void testWriteLCD();

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initTimer1();
    initTimer2();
    //initLEDs();
    initLCD();
    

    while(1)
    {
        moveCursorLCD(1,1);  // x,y set top left corner.
        testLCD();
    }
    
    return 0;
}

//void testDelayUs(){
//    
//    while(1){
//        delayUs(50);
//        LATDbits.LATD0 = 1;
//        delayUs(50);
//        LATDbits.LATD0 = 0;
//    }
//}
////
void testWriteLCD(){

    while(1){
        delayUs(500);
        writeLCD('p',1,100);
        delayUs(500);
        clearLCD();
    }
}