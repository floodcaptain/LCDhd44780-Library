/******************************************************************************

_____________________________________________________________________________
Header File     		: To Implement functionality on LCD.
Author's Name   		: Pranav Sanwal
Date of creation		: 16-012-2017
File Name           : LCDhd44780.h
Version		   		: 1.1
NOTE: KEEP R/W PIN TIED TO GROUND
NOTE: IF using 4 bit mode, connect d7,d6,d5,d4
_____________________________________________________________________________

******************************************************************************/

//! \Define to prevent recursive inclusion
#ifndef	__ISLCD__
#define __ISLCD__

#include "stdint.h"
//#define __FRAMES__


#ifdef __FRAMES__
  #include "lcdFrameVariables.h"  //!\@LCDhd44780
#endif

#define __LCD_BIT_MODE__ 8   //!|@LCDhd44780 set either to 8 or 4
#define __COLUMNS__ 20		//!\ @LCDhd44780  SET NUMBER OF COLUMNS TO USE
#define __ROWS__ 4			//!\ @LCDhd44780  SET NUMBER OF ROWS TO USE


#define LCD_GPIO_PIN_INIT(x,y)            STM32F0xx_Pin_Init(x,y);     //!\ @MCUspecific GPIO function
#define LCD_SETBIT(x)                     GPIO_SetBits(x)              //!\ @MCUspecific GPIO function
#define LCD_RESETBIT(x)                   GPIO_ResetBits(x)            //!\ @MCUspecific GPIO function

#define _RW_LCD                         GPIOB,GPIO_Pin_1               //!\ @MCUspecific
#define _RS_LCD                         GPIOB,GPIO_Pin_2               //!\ @MCUspecific
#define _EN_LCD                         GPIOB,GPIO_Pin_3               //!\ @MCUspecific
#define	_D7_LCD   		                  GPIOB,GPIO_Pin_4               //!\ @MCUspecific
#define	_D6_LCD   	                    GPIOB,GPIO_Pin_5               //!\ @MCUspecific
#define	_D5_LCD   	                    GPIOB,GPIO_Pin_6               //!\ @MCUspecific
#define	_D4_LCD   	                    GPIOB,GPIO_Pin_7               //!\ @MCUspecific
#define _D3_LCD                         GPIOB,GPIO_Pin_8               //!\ @MCUspecific
#define _D2_LCD                         GPIOB,GPIO_Pin_9               //!\ @MCUspecific
#define _D1_LCD                         GPIOB,GPIO_Pin_10              //!\ @MCUspecific
#define _D0_LCD                         GPIOB,GPIO_Pin_11              //!\ @MCUspecific
#define CONFIG_OUTPUT_LCD               GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_Level_3   //!\ @MCUspecific
#define CONFIG_INPUT_LCD                GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_Level_3    //!\ @MCUspecific

#define LCDDELAY  			800


#define __CUSTOM_CHAR_1__               {0x07,0x0F,0x09,0x09,0x09,0x09,0x1B,0x1B}       //music character
#define __CUSTOM_CHAR_2__               {0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B}       //pause character
#define __CUSTOM_CHAR_3__               {0x0C,0x0A,0x1B,0x0A,0x0C,0x1A,0x0B,0x0C}       //bluetooh character      
#define __CUSTOM_CHAR_4__               {0x00,0x08,0x0C,0x0E,0x0F,0x0E,0x0C,0x08}       //play character
#define __CUSTOM_CHAR_5__               {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
#define __CUSTOM_CHAR_6__               {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
#define __CUSTOM_CHAR_7__               {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
#define __CUSTOM_CHAR_8__               {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}


#define _CLR_DISP_ 					0x01	//! \@LCDhd44780 clear Display, bring cursor home
#define _HOME_CURS_ 				0x02	//! \ @LCDhd44780 bring cursor to home, DRAM unchanged
#define _CRSR_LEFT_	 				0x04	//! \ @LCDhd44780 shift cursor left 
#define _CRSR_RIGHT_				0x06	//! \ @LCDhd44780 Increment cursor (shift cursor to right)
#define _SHIFT_DISP_RIGHT_			0x05	//! \@LCDhd44780 Shift display right
#define _SHIFT_DISP_LEFT_			0x07	//! \@LCDhd44780 Shift display left
#define _DISP_OFF_					0x08    //! \@LCDhd44780 Display off, cursor off
#define _CRSR_OFF_					0x0c    //! \@LCDhd44780 Display on, cursor off
#define _CRSR_BLINK_				0x0e    //! \@LCDhd44780 Display on, cursor blinking

#define _CRSR_HOME_0				0x80    //! \@LCDhd44780 Force cursor to beginning to 1st line
#define _CRSR_HOME_1				0xc0    //! \@LCDhd44780 Force cursor to beginning to 2nd line
#if (__ROWS__ == 4)
  #define _CRSR_HOME_2				0x94    //! \@LCDhd44780 Force cursor to beginning to 3rd line
  #define _CRSR_HOME_3				0xd4    //! \@LCDhd44780 Force cursor to beginning to 4th line
#endif

#define _4BIT_LCD 				0x28    //! \


typedef enum {
  _customChar1=0,
  _customChar2,
  _customChar3,
  _customChar4,
  _customChar5,
  _customChar6,
  _customChar7,
  _customChar8,
}customChar;

typedef union{ 
  uint8_t Data;
  struct _BITS__
  {
    uint8_t _0:1;
    uint8_t _1:1;
    uint8_t _2:1;
    uint8_t _3:1;
    uint8_t _4:1;
    uint8_t _5:1;
    uint8_t _6:1;
    uint8_t _7:1;		
  }BITS;
}BYTE_STRUCT;


extern customChar scustomChar;

//! \Function Declarations
void LCD_Initialization(void);
void LCD_Command(uint8_t com);
void LCD_PrintNum( uint8_t value, uint8_t x, uint8_t y );
void LCD_PrintChar(uint8_t data,uint8_t x, uint8_t y);
void LCD_PrintString( uint8_t *str, uint8_t col, uint8_t row);
void LCD_GotoXY(uint8_t row, uint8_t column);
void LCD_Clear(void);
void LCD_PrintCustom(customChar yo ,uint8_t x, uint8_t y);

void LCD_Data(uint8_t data);
void Lcd_Send_Nibble(uint8_t *Value);
void Lcd_Send_Byte(uint8_t value);
void LCD_Delay(uint16_t var);

void Delay_With_LCD_Enable(uint8_t Delay_Var);
void Load_Custom_Fonts(uint8_t Location,uint8_t *Font);
#endif	//! \DEFINE __ISLCD__














