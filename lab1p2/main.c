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
#include "led.h" 


// ******************************************************************************************* //
void testDelayUs();
void testWriteLCD();

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    
//    initLCD();
    //initTimer2();
    initLEDs();
    int i;
    while(1)
    {
        
         LATDbits.LATD0 = 0;
//         i = 1;
//         while (i < 1000000)
//             i++;
         delayUs(5);
         LATDbits.LATD0 = 1;
//         i = 1;
//         while (i < 1000000){
//             i++;
         delayUs(5);
         //}
         // testDelayUs();
       // testLCD();
    }
    
    return 0;
}

void testDelayUs(){
    // set pin as output
    
    while(1){
       
    }
}
//
//void testWriteLCD(){
//
//    while(1){
//        delayUs(500);
//        writeLCD('c',1,100);
//        delayUs(500);
//        clearLCD();
//    }
//}