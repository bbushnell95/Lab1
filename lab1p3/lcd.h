/*
 * File:         lcd.h
 * Date:         2-22-2016
 * Software Designer: Ryan Trumpinski
 * Hardware Designer: Brett Bushnell
 * Quality Assurance: Sydney Clark
 * Systems Integrator: Matt Dzurick
 *
 * Created on December 31, 2014, 1:39 PM
 */

#ifndef LCD_H
#define	LCD_H

void writeLCD(unsigned char word, unsigned int commandType, unsigned int delay);
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(char c);
void printStringLCD(const char* s);
void testLCD();

#endif	/* LCD_H */