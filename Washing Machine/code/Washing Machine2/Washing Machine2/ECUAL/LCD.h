/*
 * LCD.h
 *
 * Created: 7/3/2019 6:50:24 PM
 *  Author: shaher
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "MACROSH.h"
#include "MC_Config.h"
#include "StandardTypes.h"
#include "GPIO.h"
#include <avr/io.h>
#include <stdlib.h>


/* Ports Configuration Defination */

typedef struct  
{
	GPIO *LCD_Control;
	uint8 RS;
	uint8 RW;
	uint8 E;
	GPIO *LCD_Data;
}LCD_CONFIG;

/***************************************/

/* Instruction Set */
#define Display_Clear           0x01
#define Return_Home             0x02
#define Display_OFF             0x08
#define Display_ON              0x0c |((Cursor)<<1) | ((Blink))
#define Display_Shift_Left      0x18
#define Display_shift_Right     0x1c
#define Cursor_Shift_Right	    0x14
#define Cursor_Shift_left	    0x10
#define Function_Set            0x20 | ((Eight_Bit)<<4) | ((Two_Lines)<<3) | ((_5x10Dots)<<2) /*what the meaning of two lines*/
#define DDRAM                   0x80
#define CGRAM                   0x40

#define LCD_1ST_Base            0x00 /*how to get?*/
#define LCD_2ND_Base            0x40
#define LCD_3RD_Base            0x10
#define LCD_4TH_Base            0x50

/**************************************/

/*LCD Config */
#define Cursor      0
#define Blink       0
#define Eight_Bit   0
#define Two_Lines   1
#define _5x10Dots   0

#define LCD_Left    1
#define LCD_Right   0

#define LCD_DIR(DIR)         ((DIR == LCD_Left) ? Send_Instruction(Display_Shift_Left) : Send_Instruction( Display_shift_Right ))
#define Cursor_DIR(DIR)      ((DIR == LCD_Left) ? Send_Instruction( Cursor_Shift_left) : Send_Instruction( Cursor_Shift_Right ))
    /*?*/
/**************************************/

/*When Using Upper Data Port DB4->DB7*/
#define Upper_Data_Port  1

/**************************************/

/* Function Set*/

void LCD_INIT(LCD_CONFIG * ports);
void Send_Instruction(LCD_CONFIG * ports,uint8 Instruction);
void LCD_Send_Char(LCD_CONFIG * ports,uint8 Data);
void LCD_Send_String(LCD_CONFIG * ports,uint8 * ptr);
void LCD_RowCol(LCD_CONFIG * ports,uint8 Row ,uint8 Col);
void LCD_Clear(LCD_CONFIG * ports);
void LCD_DisplayInt(LCD_CONFIG * ports,sint32 data);

/**************************************/

#endif /* LCD_H_ */