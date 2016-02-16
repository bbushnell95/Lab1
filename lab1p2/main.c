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
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"


// ******************************************************************************************* //

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    
    initLCD();
    initTimer2();
    
    while(1)
    {
        
        //testLCD();
    }
    
    return 0;
}


void tesDelayUs(){
    while (1)
    {
        LATDbits.LATD0=0;
        delayUs(5);
        LATDbits.LATD0=1;
        delayUs(5);
    }
}

void testWriteLCD()
{
    while(1)
    {
        delayUs(500);
        writeLCD('c',1,100);
        delayUs(500);
        clearLCD();
    }
}