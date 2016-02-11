/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

/* The pins that you will use for the lcd control will be
 *                     
 * LCD_RS      RC4     
 * LCD_E       RC2     
 * LCD_D4      RE7     
 * LCD_D5      RE5      
 * LCD_D6      RE3      
 * LCD_D7      RE1      
 * Use these so that we will be able to test your code for grading and to
 * help you debug your implementation!
 */

#define TRIS_D7 TRISEbits.TRISE1
#define TRIS_D6 TRISEbits.TRISE3
#define TRIS_D5 TRISEbits.TRISE5
#define TRIS_D4 TRISEbits.TRISE7
#define TRIS_RS TRISCbits.TRISC4
#define TRIS_E  TRISCbits.TRISC2


#define LCD_D7_3  LATEbits.LATE1
#define LCD_D6_2  LATEbits.LATE3
#define LCD_D5_1  LATEbits.LATE5
#define LCD_D4_0  LATEbits.LATE7
#define LCD_RS  LATCbits.LATC4
#define LCD_E   LATCbits.LATC2
#define LCD_RW  LATCbits.LATC12

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATE. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    // set the commandType (RS value)
    LCD_RS=commandType;
    LCD_RW=0;
    
    if (lower==1)
    {
    LCD_D4_0 = word&0x01;
    LCD_D5_1 = (word&0x02)>>1;
    LCD_D6_2 = (word&0x04)>>2;
    LCD_D7_3 = (word&0x08)>>3;
    }
    else if (lower==0)
    {
    LCD_D4_0 = (word&0x10)>>4;     //16
    LCD_D5_1 = (word&0x20)>>5;     //32
    LCD_D6_2 = (word&0x40)>>6;     //64
    LCD_D7_3 = (word&0x80)>>7;     //128
    }
    //enable
    LCD_E=1;
    //delay
    delayUs(delayAfter);          
    //disable
    LCD_E=0;
    
    //delayUs(50);
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
    writeFourBits(word,commandType,delayAfter,0);
    writeFourBits(word,commandType,delayAfter,1);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c,1,100);      
    
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    
    TRIS_D7 =0;
    TRIS_D6 =0;
    TRIS_D5 =0;
    TRIS_D4 =0;
    TRIS_RS =0;
    TRIS_E  =0;

    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    
    // Enable 4-bit interface
    delayUs(15000);     //delay 15ms

    writeFourBits(0b00110000, 0, 4100, 0);
    

    writeFourBits(0b00110000, 0, 100, 0);
   
    writeFourBits(0b00110000, 0, 0, 0);
    
    writeFourBits(0b00100000, 0, 0, 0);
    // Function Set (specifies data width, lines, and font.

    writeFourBits(0b00101011, 0, 0,0);
    writeFourBits(0b00101011, 0, 0,1);
    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.

    // TODO: Display On/Off Control
        // Turn Display (D) Off

    writeFourBits(0b00001000, 0, 0,0);
    writeFourBits(0b00001000, 0, 0,1);
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.

     writeFourBits(0b00000001, 0, 0,0);
     writeFourBits(0b00000001, 0, 0,1);
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)

    writeFourBits(0b00000111, 0, 0,0);
    writeFourBits(0b00000111, 0, 0,1);
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
    while(&s!=void)
    {
    printCharLCD(&s);   //need to write this function
    s=s+1;
    }
}

/*
 * Clear the display.
 */
void clearLCD()
{
    writeFourBits(0b00000001,0, 100, 0);
    writeFourBits(0b00000001,0, 100, 1);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y)
{
    char c="";

    if(y==1)
    {
        if(x==1) c=0b10000000;
        else if(x==2)c=0b10000001;
        else if(x==3)c=0b10000010;
        else if(x==4)c=0b10000011;
        else if(x==5)c=0b10000100;
        else if(x==6)c=0b10000101;
        else if(x==7)c=0b10000110;
        else if(x==8)c=0b10000111;
    }
    else if(y==2)
    {
        if(x==1) c=0b10001000;
        else if(x==2)c=0b10001001;
        else if(x==3)c=0b10001010;
        else if(x==4)c=0b10001011;
        else if(x==5)c=0b10001100;
        else if(x==6)c=0b10001101;
        else if(x==7)c=0b10001110;
        else if(x==8)c=0b10001111;
    }
    
    writeFourBits(c, 1, 0,0);
    writeFourBits(c, 1, 0,1);
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}