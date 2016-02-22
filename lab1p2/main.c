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
int main(void)
{
    int i=0;
    SYSTEMConfigPerformance(10000000);      //initialize everything
    enableInterrupts();
    initTimer1();
    initTimer2();
    initLCD();
    
    
    while(1)
    {
	testLCD();                              //calls test function
   }
    
    return 0;
}

void testDelayUs(){
    
    while(1){
        delayMs(50); // testing delayMs() instead of delayUs() since delayMs() is the delay used in project
        LATDbits.LATD0 = 1;
        delayMs(50);
        LATDbits.LATD0 = 0;
    }
}

void testWriteLCD(){

    while(1){
        delayMs(1);
        writeLCD('p',1,100);
        delayMs(1);
        clearLCD();
    }
}
