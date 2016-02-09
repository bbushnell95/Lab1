/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>

#define PRESCALAR_256 3

void initTimer1(){
    TMR1=0;
    IFS0bits.T1IF=0;        //interrupt flag is down
}

void delayMs(unsigned int delay){
    TMR1=0;
    T1CONbits.TCKPS=PRESCALAR_256;      //prescaler of 256
    PR1=((delay*10^-3*10000000/256)-1);
    T1CONbits.ON=1;
    IFS0bits.T1IF=0;
    while(IFS0bits.T1IF==0)
    {
        
    }
    T1CONbits.ON=0;
    IFS0bits.T1IF=0;
}

//Uses timer 2

initTimer2(){
    TMR2=0;
    IFS0bits.T2IF=0;        //flag
}
void delayUs(unsigned int delay){
    TMR2=0;
    T2CONbits.TCKPS=7;      //prescale of 256
    PR2=((delay*10^-6*10000000/256)-1);
    T2CONbits.ON=1;
    IFS0bits.T2IF=0;
    while(IFS0bits.T2IF==0)
    {
        
    }
    T2CONbits.ON=0;
    IFS0bits.T2IF=0;
}