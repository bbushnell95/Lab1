/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

/*#include <xc.h>
#include "timer.h"

initTimer2(){
    TMR2=0;
    IEC0bits.T2IE = 0;
    IFS0bits.T2IF=0;        //flag
}
void delayUs(unsigned int delay){
    TMR2=0;
    T2CONbits.TCKPS=0;      //prescaler of 1
    PR2=(((delay*10))-1);
    IFS0bits.T2IF=0;
    T2CONbits.ON=1;
    while(IFS0bits.T2IF==0);
    T2CONbits.ON=0;
    IFS0bits.T2IF=0;
}*/
#include <xc.h>
#include "timer.h"


//void initTimer1()
//{
//    TMR1 = 0;
//    T1CONbits.ON = 0;
//    T1CONbits.TCKPS = 3;
//    T1CONbits.TCS = 0;
//    T1CONbits.TON = 0;
//    PR1 = 65535;
//}

void delayUs(unsigned int delay)
{
    IFS0bits.T2IF = 0; //reset the flag
    TMR2 = 0x0000; //clear the timer 2
    T2CONbits.ON = 1;
    PR2 = 4095; 
    int i;
    for(i=0; i < delay/(256*2); i++)
    {
        while(!IFS0bits.T2IF);
        IFS0bits.T2IF = 0; 
    }
    PR2 =(delay % (256*2))*8 - 1;
    while(!IFS0bits.T2IF); 
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 0;
}

