# hd44780 Based LCD API

- Simple to use LCD API library based on **hd44780 Chipset**. 
- This library has options for **16x2** and **20x4** library (Rows and Columns can be configured).

 # Usage
 

 - First initialize the LCD by calling `LCD_Initialization();`
 - To print a string at `0th` row and `1st` column, call
  `LCD_PrintString( "test",1,0);`
 - To print a custom character saved as defined in macro `__CUSTOM_CHAR_1__` at `0th` row and `1st` column call, `LCD_PrintCustom(_customChar1 ,1,0);`
- To clear the LCD display, call `LCD_Clear();`
- Sample code flow: 
	

	    void main(){
	    LCD_Initialization();	//initialises LCD
	    LCD_PrintString( "test",1,0);	//print string "test" at 1,0
	    LCD_PrintCustom(_customChar1 ,1,0); //prints custom character
	    LCD_Clear(); 			//clears LCD screen
	    }
	    while(1);

# How to configure?

This library can be used with any MCU .
**NOTES:** 
 - all decorators with *@LCDhd44780* are library specific .
 - all decorators with *@MCUspecific* are MCU specific .
 - Copy these files in project directory
	 - LCDhd44780.h
	 - LCDhd44780.c
	 
***CONFIGURATIONS IN LCDhd44780.h FILE :*** 

 -  Edit `#define __LCD_BIT_MODE__` to bit mode you want to use.  use either **4** OR **5**

 - Add MCU specific API to `#define` macro:

		#define LCD_GPIO_PIN_INIT(x,y)      //to eg.  STM32F0xx_Pin_Init(x,y);
		#define LCD_SETBIT(x)				//to eg.  GPIO_SetBits(x);
		#define LCD_RESETBIT(x)				//to eg.  GPIO_ResetBits(x)
		#define _RW_LCD					    //to eg.  GPIOB,GPIO_Pin_1
		#define _RW_LCD
		#define _EN_LCD
		#define	_D7_LCD
		#define	_D6_LCD
		#define _D5_LCD
		#define	_D5_LCD
		#define	_D4_LCD 
		#define	_D3_LCD
		#define	_D2_LCD 
		#define	_D1_LCD
		#define	_D0_LCD
		#define CONFIG_OUTPUT_LCD    		//to eg.  GPIOO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_Level_3 
		#define CONFIG_INPUT_LCD  			//to eg. GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_Level_3


 -  If you want to edit custom characters, edit:

	     #define __CUSTOM_CHAR_1__ 
	     #define __CUSTOM_CHAR_2__ 
	     #define __CUSTOM_CHAR_3__
	     #define __CUSTOM_CHAR_4__
	     #define __CUSTOM_CHAR_5__
	     #define __CUSTOM_CHAR_6__
	     #define __CUSTOM_CHAR_7__
	     #define __CUSTOM_CHAR_8__  
	     
 ***CONFIGURATIONS IN LCDhd44780.c FILE :*** 
 - Include MCU specific library that contains GPIO definitions for eg. `#include "STM32F0xx_Config.h"`
	
# OPTIONAL:

 - This library also supports Framed mode, via an external library  `"framedLcd.h"`
 

 - to enable framing, enable the macro `#define __FRAMES__`
