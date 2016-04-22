
//*********************************************************************
//    File Name:         LCD.h
//    Description:       LCD Interfacing declaration file, LCD can be connected to any port;
//
//						 4-bit communication:
//
//						 P0.0 for LCD RS (1)
//						 P0.1 for LCD E  (2)
//						 P2 for LCD Data (3-10)
//
//    Code Memory:		 x bytes
//	  Data Memory:		 x bytes
//*********************************************************************

#ifndef __LCD_4BIT_H__
#define __LCD_4BIT_H__


	#ifdef _SYS_DISPLAY_H_
			#define LCD_CONTROL_PORT		SYS_LCD_PORT
			#define LCD_CONTROL_DIRECTION	SYS_LCD_PORT_DIR

			#define LCD_DATA_PORT			SYS_LCD_PORT
			#define LCD_DATA_DIRECTION		SYS_LCD_PORT_DIR

			#define LCD_RS 	SYS_LCD_RS
			#define LCD_E 	SYS_LCD_E
			#define LCD_D4	SYS_LCD_D4	//LCD PIN 11
			#define LCD_D5	SYS_LCD_D5	//LCD PIN 11
			#define LCD_D6	SYS_LCD_D6	//LCD PIN 11
			#define LCD_D7	SYS_LCD_D7	//LCD PIN 11
	#else
			#define LCD_CONTROL_PORT		PORTD
			#define LCD_CONTROL_DIRECTION	DDRD

			#define LCD_DATA_PORT			PORTD
			#define LCD_DATA_DIRECTION		DDRD

			#define LCD_RS 	6
			#define LCD_RW	7
			#define LCD_E 	5
			#define LCD_D4	3	//LCD PIN 11
			#define LCD_D5	2	//LCD PIN 11
			#define LCD_D6	1	//LCD PIN 11
			#define LCD_D7	0	//LCD PIN 11
	#endif


#include <avr/io.h>		// include I/O definitions (port names, pin names, etc)
#include <util/delay.h>

#define LCD_cmd		0
#define LCD_data	1

#define LCD_ENABLE 	1
#define LCD_DISABLE 0

#define LCD_INIT        0x3 // 8-bit data length
#define LCD_MODE 		0x28 //2 line LCDD

//Entry modes, use at initialization
#define LCD_CURSOR_SHIFT_LEFT_MODE		0x04// 0000 0100
#define LCD_DISPLAY_SHIFT_LEFT_MODE		0x05// 0000 0101
#define LCD_CURSOR_SHIFT_RIGHT_MODE		0x06// 0000 0110
#define LCD_DISPLAY_SHIFT_RIGHT_MODE	0x07// 0000 0111


#define LCD_MAX_CHAR_IN_LINE 	20

#ifndef LCD_MAX_CHAR_IN_LINE
	#define LCD_MAX_CHAR_IN_LINE 20
#endif

//DDRAM Addresses
#define DDRAM_PTR  0x80      							  // Address Display Data RAM pointer
#define LINE1_ADDR 0x00    								  // Start of line 1 in the DD-Ram
#define LINE2_ADDR 0x40     							  // Start of line 2 in the DD-Ram
#define LINE3_ADDR 0x14   // Start of line 3 in the DD-Ram
#define LINE4_ADDR 0x54   // Start of line 4 in the DD-Ram


//Display modes, use at initialization
#define LCDOff()	LCDSendCmd(0x08)
#define LCDOn()		LCDSendCmd(0x0C)
#define LCDCursorOff()	LCDSendCmd(0x0C)
#define LCDCursorNoBlink()	LCDSendCmd(0x0E)
#define LCDCursorBlink()	LCDSendCmd(0x0F)
#define LCDClear()	LCDSendCmd(0x01); _delay_ms(10)
#define LCDCursorHome()	LCDSendCmd(0x02)
#define LCDCursorLeft()	LCDSendCmd(0x10)
#define LCDCursorRight()	LCDSendCmd(0x14)}
#define LCDDisplayShiftLeft()	LCDSendCmd(0x1C)
#define LCDDisplayShiftRight()	LCDSendCmd(0x18)


void LCDSendCmd4BIT(unsigned char ucCmd);

void LCDSendCmd(unsigned char ucCmd);
void LCDSendData (unsigned char ucData);

void LCDGotoXY(unsigned char x,unsigned char y);

void LCDInit(void);

void LCDPutchar(char c);

void LCDString(char *msg);

void LCDDigit(unsigned char c);

// ***** Added by Bakee  ******************
void LCDShowCursor(void);

void LCDHideCursor(void);

void LCDRefresh(void);

//............................................................................
#endif

