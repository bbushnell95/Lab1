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
#include "switch.h"

#define LEDRUN LATGbits.LATG12  
#define LEDSTOP LATGbits.LATG14
#define EXTERNAL LATAbits.LATA7
#define ON 1
#define OFF 0
#define PRESSED 0

typedef enum stateTypeEnum{
    ledrun,ledstop, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

volatile int switchFlag=0;
volatile int reset=0;
volatile int countflag=0;
volatile int hundred=0;
volatile int ten=0;
volatile int onesec=0;
volatile int tensec=0;
volatile int onemin=0;
volatile int tenmin=0;
volatile const char* running = "Running";
volatile const char* stopped="Stopped";
// ******************************************************************************************* //
int PrevState=1; 
int state=ledrun;

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    initSwitch1();
    initSW2();
    initLCD();
    initTimer2();
    initLEDs();
    
    while(1)
    {
        switch(state){                          //LED 1 is on
              case  ledrun:
                    LEDRUN=ON;
                    LEDSTOP=OFF;
                    T2CONbits.ON=1;
                    PrevState=1;
                    reset=0;
                    moveCursorLCD(1,1);
                    printStringLCD(running);
                    if(switchFlag==1)              //if switch is pressed
                  {
                      switchFlag=0;
                      state=debouncePress;
                  }
                    if(countflag==1)
                    {
                        incrimentcount();
                    }
                    break;
               case ledstop:                       //LED 2 is on
                    LEDRUN=OFF;
                    LEDSTOP=ON;
                    T2CONbits.ON=0;
                    PrevState=2;
                    moveCursorLCD(1,1);
                    printStringLCD(stopped);
                     if(switchFlag==1)              //if switch is pressed
                        {
                            switchFlag=0;
                            state=debouncePress;
                        }
                     if(reset==1)
                    {
                      TMR2=0;
                      reset=0;
                      hundred=0;
                      ten=0;
                      onesec=0;
                      tensec=0;
                      onemin=0;
                      tenmin=0;
                      
                    }
                    break;    
              case debouncePress:               //calls delay and moves to wait state
                  delayMs(50);
                  state=wait;
                  break;
    
              case debounceRelease:             //calls delay and moves to wait 2 aka logic state
                  delayMs(50);
                  state=wait2;
                  break;
   
                case wait:                      //waits until switch is released
                    if(switchFlag==0)
                    {
                        state=wait;
                    }
                    else
                    {
                        switchFlag=0;
                        state=debounceRelease;
                    }
                    break;
                case wait2:                     //uses flag that is triggerd if switch is held for longer than
                   if(PrevState==1)
                   {
                       state=ledstop;
                   }
                   else if(PrevState==2)
                   {
                       state=ledrun;
                   }
                   break;
                }
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


void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    PORTA;
    IFS1bits.CNAIF=0;
    switchFlag=1;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CN2Interrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    PORTD;
    IFS1bits.CNDIF=0;
    reset=1;
}

void __ISR(_TIMER_2_VECTOR, IPL7SRS) __T2Interupt()
{
    IFS0bits.T2IF=0;
    countflag=1;
}

void incrimentcount()
{
    
    
    hundred++;
    
    if(hundred==10)
    {
        hundred=0;
        ten++;
    }
    if(ten==10)
    {
        ten=0;
        onesec++;
    }
    if(onesec==10)
    {
        onesec=0;
        tensec++;
    }
    if(tensec==6)
    {
        tensec=0;
        onemin++;
    }
    if(onemin==10)
    {
        onemin=0;
        tenmin++;
    }
    if(tenmin==10)
    {
    int hundred=0;
    int ten=0;
    int onesec=0;
    int tensec=0;
    int onemin=0;
    int tenmin=0;
    }
    
    moveCursorLCD(1,2);
    writeLCD(tenmin);
    writeLCD(onemin);
    writeLCD(00111010);
    writeLCD(tensec);
    writeLCD(onesec);
    writeLCD(00111010);
    writeLCD(ten);
    writeLCD(hundred);
}
