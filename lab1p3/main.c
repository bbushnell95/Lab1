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
#define ON 1
#define OFF 0
#define PRESSED 0

void incrimentcount();

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
const char* running = "Running:";
const char* stopped="Stopped:";
// ******************************************************************************************* //
int PrevState=2; 
int state=ledrun;

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initSwitch1();
    initSW2();
    initTimer1();
    initTimer2();
    initTimer3();
    initLEDs();
    initLCD();
    
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 1;
    
    while(1)
    {
        switch(state){                          //LED 1 is on
              case  ledrun:
                  if(PrevState==2)
                  {
                    LEDRUN=ON;
                    LEDSTOP=OFF;
                    T3CONbits.TON=1;
                    PrevState=1;
                    reset=0;
                    moveCursorLCD(1,1);
                    printStringLCD(running);
                  }
                    if(switchFlag==1)              //if switch is pressed
                  {
                      switchFlag=0;
                      state=debouncePress;
                  }
                    if(countflag==1)
                    {
                        countflag = 0;
                        incrimentcount();
                    }
                    break;
               case ledstop:                       //LED 2 is on
                   if(PrevState==1)
                   {
                   LEDRUN=OFF;
                    LEDSTOP=ON;
                    T3CONbits.TON=0;
                    PrevState=2;
                    moveCursorLCD(1,1);
                    printStringLCD(stopped);
                   }
                     if(switchFlag==1)              //if switch is pressed
                        {
                            switchFlag=0;
                            state=debouncePress;
                        }
                     if(reset==1)
                    {
                         //delayMs(50);
                      TMR3=0;
                      reset=0;
                      hundred=0;
                      ten=0;
                      onesec=0;
                      tensec=0;
                      onemin=0;
                      tenmin=0;
                      
                      moveCursorLCD(1,2);
                      printCharLCD(tenmin+'0');
                      printCharLCD(onemin+'0');
                      printCharLCD(':');
                      printCharLCD(tensec+'0');
                      printCharLCD(onesec+'0');
                      printCharLCD(':');
                      printCharLCD(ten+'0');
                      printCharLCD(hundred+'0');
                      
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
                    if(switchFlag==1)
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

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    if(IFS1bits.CNAIF==1)
    {
    PORTA;
    IFS1bits.CNAIF=0;
    switchFlag=1;
    }
    else if(IFS1bits.CNDIF==1)
    {
    PORTD;
    IFS1bits.CNDIF=0;
    reset=1;
    }
}


void __ISR(_TIMER_3_VECTOR, IPL7SRS) __T3Interupt()
{
    IFS0bits.T3IF=0;
    countflag=1;
    if (LATDbits.LATD0 == 0) LATDbits.LATD0 = 1;
    else if (LATDbits.LATD0 == 1) LATDbits.LATD0 = 0;
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
    hundred=0;
    ten=0;
    onesec=0;
    tensec=0;
    onemin=0;
    tenmin=0;
    }
    moveCursorLCD(1,2);
    printCharLCD(tenmin+'0');
    printCharLCD(onemin+'0');
    printCharLCD(':');
    printCharLCD(tensec+'0');
    printCharLCD(onesec+'0');
    printCharLCD(':');
    printCharLCD(ten+'0');
    printCharLCD(hundred+'0');
}
