// ******************************************************************************************* //
//
// File:         main.c
// Date:         2-22-2016
// Software Designer: Ryan Trumpinski
// Hardware Designer: Brett Bushnell
// Quality Assurance: Sydney Clark
// Systems Integrator: Matt Dzurick
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
void getTimeString();
void testgetTimeString();

typedef enum stateTypeEnum{
    ledrun,ledstop, wait, wait2, debouncePress, debounceRelease, debounceRelease2, debounceReset
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

char timeString[9] = "MM:SS:FF\0";
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
    int j = 0;
    
    while(1)
    {
        switch(state){                          //LED 1 is on
              case  ledrun:
                  reset = 0;
                  if(PrevState==2)
                  {
                      switchFlag = 0;
                    LEDRUN=ON;
                    LEDSTOP=OFF;
                    T3CONbits.TON=1;
                    PrevState=1;
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
                       switchFlag = 0;
                   LEDRUN=OFF;
                    LEDSTOP=ON;
                    T3CONbits.TON=0;
                    PrevState=2;
                    moveCursorLCD(1,1);
                    printStringLCD(stopped);
                    j = 0;
                   }
                     if(switchFlag==1)              //if switch is pressed
                        {
                            switchFlag=0;
                            state=debouncePress;
                        }
                     if(reset==1)
                    {
                         reset = 0;
                         state = debounceReset;
                    }
                    break;    
              case debouncePress:               //calls delay and moves to wait state
                  delayMs(15);
                  state=wait;
                  break;
                  
            case debounceReset:
                /* Debounce the press. */
                delayMs(15);
                
                /* Reset timer 3 to 0. It is already turned off in ledstop. */
                TMR3=0;
                reset=0;
                
                /* Resets volatile variables for the counting function. */
                hundred=0;
                ten=0;
                onesec=0;
                tensec=0;
                onemin=0;
                tenmin=0;
                
                /* Set the time on the display back to zero. */
                moveCursorLCD(1,2);
                getTimeString();
                printStringLCD(timeString);
                
                /* Wait until the switch is released. */
                while (reset != 1) {  }
        
                /* Turn reset back to zero for future logic. */
                reset = 0;
                
                /* Debounce the release. */
                delayMs(15);
                
                /* Go back to ledstop. */
                state = ledstop;
                break;
    
              case debounceRelease:             //calls delay and moves to wait 2 aka logic state
                  delayMs(15);
                  state=wait2;
                  break;
   
                case wait:                      //waits until switch is released
                   
                    while ( switchFlag != 1 );
                    
                    switchFlag = 0;
                    state = debounceRelease;
                        
                        
                   
//                    if(switchFlag==1)
//                    {
//                        switchFlag=0;
//                        state=debounceRelease;
//                    }
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
//    if (LATAbits.LATA0 == 0) LATAbits.LATA0 = 1;
//    else if (LATAbits.LATA0 == 1) LATAbits.LATA0 = 0;
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
//    printCharLCD(tenmin+'0');
//    printCharLCD(onemin+'0');
//    printCharLCD(':');
//    printCharLCD(tensec+'0');
//    printCharLCD(onesec+'0');
//    printCharLCD(':');
//    printCharLCD(ten+'0');
//    printCharLCD(hundred+'0');
    
    getTimeString();
    printStringLCD(timeString);
}

void getTimeString(){
    
    timeString[0] = tenmin + '0';
    timeString[1] = onemin + '0';
    timeString[3] = tensec + '0';
    timeString[4] = onesec + '0';
    timeString[6] = ten + '0';
    timeString[7] = hundred + '0';
    
}

void testgetTimeString(){
// testing MM:SS:FF 
// expect string to be at least dd:dd:dd
    
    tenmin = 7;
    onemin = 2;
    tensec = 3;
    onesec = 4;
    ten = 5;
    hundred = 7;
    
    getTimeString();
    
    const char* testing = "72:34:57";
    int i = 0;
    int noError = 0;
    while(testing[i] != '\0'){
        if(testing[i] != timeString[i]){
            //ERROR (printing to stdout????) fix???
            printf("ERROR: timeString incorrect\n");
            printf("Expected: %s\n Actual: %s", testing, timeString);
            noError = 1;
            break;
        }
        i++;
    }
    if(noError == 0){
        printf("No errors, getTimeString functions");
    }
}