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
