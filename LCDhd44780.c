/******************************************************************************

_____________________________________________________________________________
Header File         : To Implement functionality on LCD.
Author's Name       : Pranav Sanwal
Date of creation    : 16-012-2017
File Name           : LCDhd44780.c
Version         : 1.1
NOTE: KEEP R/W PIN TIED TO GROUND
NOTE: IF using 4 bit mode, connect d7,d6,d5,d4
_____________________________________________________________________________

******************************************************************************/

#include <stdio.h>
#include "STM32F0xx_Config.h"  //!\ @MCU SPECIFIC DEPENDENCY
#include "LCDhd44780.h"


BYTE_STRUCT LCD_BYTE;

uint8_t Custom_Font_Location[]={64,72,80,88,96,104,112,120};
customChar scustomChar;
uint8_t Custom_Font[8][8]=
{
	__CUSTOM_CHAR_1__,
	__CUSTOM_CHAR_2__,          
	__CUSTOM_CHAR_3__,           
	__CUSTOM_CHAR_4__,             
	__CUSTOM_CHAR_5__,
	__CUSTOM_CHAR_6__,
	__CUSTOM_CHAR_7__,
	__CUSTOM_CHAR_8__,
};

//*****************************************************************************
//! \Function 		: LCD_Initialization
//! \Description	: Initializations for LCD pins.
//! \param 			: None.
//! \return			: None.
//*****************************************************************************
void LCD_Initialization(void)
{
  LCD_GPIO_PIN_INIT(_RS_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_EN_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_RW_LCD,CONFIG_OUTPUT_LCD);
  LCD_RESETBIT(_RW_LCD);
  
  LCD_GPIO_PIN_INIT(_D7_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_D6_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_D5_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_D4_LCD,CONFIG_OUTPUT_LCD);

#if (__LCD_BIT_MODE__==8)   
  LCD_GPIO_PIN_INIT(_D3_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_D2_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_D1_LCD,CONFIG_OUTPUT_LCD);
  LCD_GPIO_PIN_INIT(_D0_LCD,CONFIG_OUTPUT_LCD);
#endif  
  
  /* INITIALIZING SEQUENCE */
  
  //TODO: 15MS DELAY
  LCD_Delay(10);
   
  LCD_Command(0x03);
  Delay_With_LCD_Enable(50);

  LCD_Command(0x03);
  Delay_With_LCD_Enable(50);

  LCD_Command(0x03);
  Delay_With_LCD_Enable(50);
  
  LCD_Command(0x03);
  
  Delay_With_LCD_Enable(50);
  
  
#if (__LCD_BIT_MODE__== 4 )  
  LCD_Command(_4BIT_LCD);					//! \set LCD to 4-bit mode with 4 lines 
  Delay_With_LCD_Enable(50);
  
  LCD_Command(_4BIT_LCD);					//! \set LCD to 4-bit mode with 4 lines 
  LCD_Delay(LCDDELAY);
  
  LCD_Command(_4BIT_LCD);					//! \set LCD to 4-bit mode with 4 lines 
  LCD_Delay(LCDDELAY);
  
#else                                           
  LCD_Command(0x38);                                            //! \set LCD in 8-bit mode
  LCD_Delay(LCDDELAY);

   LCD_Command(0x38);                                            //! \set LCD in 8-bit mode
  LCD_Delay(LCDDELAY);
  
    LCD_Command(0x38);                                            //! \set LCD in 8-bit mode
  LCD_Delay(LCDDELAY);
  
    LCD_Command(0x38);                                            //! \set LCD in 8-bit mode
  LCD_Delay(LCDDELAY);
#endif 

  LCD_Command(_DISP_OFF_);
  LCD_Delay(LCDDELAY);
  
  LCD_Command(0x06);                                            //!\ disable display shift
  LCD_Delay(LCDDELAY);
  
  LCD_Command(0x14);                                            //\!\ enable cursor increment to right
  LCD_Delay(LCDDELAY);

  Load_Custom_Fonts(0,Custom_Font[0]);
  Load_Custom_Fonts(1,Custom_Font[1]);
  Load_Custom_Fonts(2,Custom_Font[2]);
  Load_Custom_Fonts(3,Custom_Font[3]);
  Load_Custom_Fonts(4,Custom_Font[4]);
  Load_Custom_Fonts(5,Custom_Font[5]);
  Load_Custom_Fonts(6,Custom_Font[6]);
  Load_Custom_Fonts(7,Custom_Font[7]);
  
  LCD_Command(_HOME_CURS_);				//! \return cursor to home
  LCD_Delay(LCDDELAY);

  LCD_Command(_CRSR_OFF_); 				//! \display on, curor off, cursor blink off
  LCD_Delay(LCDDELAY);
  
  LCD_Clear();
  
#ifdef __FRAMES__
  initialize_frame();
#endif  
}


//*****************************************************************************
//! \Function 		: LCD_PrintString
//! \Description	: Send string on LCD with x-y coordinates .
//! \param 			: "str" for string to display
//						:"x" for column select .
//							:"y" for row select .
//! \return			: None.
//*****************************************************************************
void LCD_PrintString( uint8_t *str, uint8_t col, uint8_t row)
{ uint8_t count=0;
  LCD_GotoXY(col,row);
  while(*str !='\0' && count<__COLUMNS__)
  {
    LCD_Data(*str++);
    count++;
  }
}

//*****************************************************************************
//! \Function 		: LCD_PrintNum
//! \Description	: Send number on LCD with x-y coordinates .
//! \param 			: "value" for number to display
//						:"x" for column select .
//							:"y" for row select .
//! \return			: None.
//*****************************************************************************
void LCD_PrintNum( uint8_t value, uint8_t x, uint8_t y )
{	
  uint8_t outputstring[__COLUMNS__];
  //LCD_GotoXY(x,y);
  sprintf((char*)outputstring,"%d",value);
  //itoa(value, outputstring, 10);
  LCD_PrintString(outputstring,x,y);	
}

//*****************************************************************************
//! \Function     : Load_Custom_Fonts
//! \Description  : 
//! \param        : "value" for number to display
//                :"x" for column select .
//                :"y" for row select .
//! \return       : None.
//*****************************************************************************
void Load_Custom_Fonts(uint8_t memLoc,uint8_t *Font)
{
	LCD_Command(Custom_Font_Location[memLoc]);
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
        
        Font++;
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
        
        Font++;
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
        
        Font++;
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
        
        Font++;
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
        
        Font++;
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
        
        Font++;
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
        
        Font++;
	LCD_Delay(LCDDELAY);
	LCD_Data(*Font);
	LCD_Delay(LCDDELAY);
	Delay(0xFFFF);
}

//*****************************************************************************
//! \Function 		: LCD_PrintChar
//! \Description	: send display data to LCD with coordinates.
//! \param 			: "data" to display character on LCD .
//!                             : "x" x-coordinate on LCD
//!                             : "y" y-coordinate on LCD
//! \return			: None.
//!\ NOTE:                      : DOSEN'T print if encounters NULL charcter .
//*****************************************************************************
void LCD_PrintChar(uint8_t data,uint8_t x, uint8_t y)
{
  if(data == '\0')
    return;
  LCD_GotoXY(x,y);
  LCD_SETBIT(_RS_LCD); //set RS
  Lcd_Send_Byte(data); //CALL LCD_SENDBYTE
  //LCD_Delay(LCDDELAY);
}

//*****************************************************************************
//! \Function 		: LCD_PrintCustom
//! \Description	: print custom character at given location .
//! \param 			: "cChar" of type customChar .
//!                             : "x" x-coordinate on LCD
//!                             : "y" y-coordinate on LCD
//! \return			: None.
//*****************************************************************************
void LCD_PrintCustom(customChar data ,uint8_t x, uint8_t y)
{
  LCD_GotoXY(x,y);
  LCD_Data(data);
}


//*****************************************************************************
//! \Function 		: LCD_GotoXY
//! \Description	: change cursor postion on LCD with x-y coordinates .
//! \param 			: "column" for column select .[0,1,2,...20]
//						:"y" for row select .[0,1,2,3]
//! \return			: None.
//*****************************************************************************
void LCD_GotoXY(uint8_t column, uint8_t row) //(x,y)
{
  //column++;
  if(column>20)
    column=20;
  switch(row)
  {
  case 0:
    LCD_Command(_CRSR_HOME_0 + column);
    break;
  case 1:
    LCD_Command(_CRSR_HOME_1 + column);
    break;
    
#if (__ROWS__ == 4)			
  case 2:
    LCD_Command(_CRSR_HOME_2 + column);
    break;
  case 3:
    LCD_Command(_CRSR_HOME_3 + column);
    break;
#endif
  default:
    break;
  }
  
  LCD_Delay(LCDDELAY);
  LCD_Delay(LCDDELAY);
}

//*****************************************************************************
//! \Function 		: LCD_Clear
//! \Description	: clears the lcd display .
//! \param 			: None.
//! \return			: None.
//*****************************************************************************
void LCD_Clear(void){
  LCD_Delay(LCDDELAY);
  LCD_Command(_CLR_DISP_);
  LCD_Delay(LCDDELAY);  
}

//*****************************************************************************
//! \Function 		: LCD_Command
//! \Description	: send command to LCD .
//! \param 			: "com" for LCD command in hex .
//! \return			: None.
//*****************************************************************************
void LCD_Command(uint8_t com)
{
  LCD_RESETBIT(_RS_LCD);//reset RS
  Lcd_Send_Byte(com); //send a byte to LCD
  //LCD_Delay(LCDDELAY);
}

//*****************************************************************************
//! \Function 		: LCD_Data
//! \Description	: send display data to LCD .
//! \param 			: "data" to display character on LCD .
//! \return			: None.
//*****************************************************************************
void LCD_Data(uint8_t data)
{
  LCD_SETBIT(_RS_LCD); //set RS
  Lcd_Send_Byte(data); //CALL LCD_SENDBYTE
  //LCD_Delay(LCDDELAY);
}

//*****************************************************************************
//! \Function 		: Lcd_Send_Byte
//! \Description	: send a byte to LCD .
//! \param 			: "value" for LCD command in hex .
//! \return			: None.
//*****************************************************************************
void Lcd_Send_Byte(uint8_t value)
{
  Lcd_Send_Nibble(&value); //send high value
  LCD_SETBIT(_EN_LCD);//set enable
  LCD_Delay(LCDDELAY);//delay
  LCD_RESETBIT(_EN_LCD);//reset enable
  LCD_Delay(LCDDELAY);//delay
  
#if __LCD_BIT_MODE__ == 4
  value= value<<4;//shift lower values to higher values
  
  Lcd_Send_Nibble(&value); //send low value
  LCD_SETBIT(_EN_LCD);///set enable
  LCD_Delay(LCDDELAY);//delay
  LCD_RESETBIT(_EN_LCD);//reset enable
  LCD_Delay(LCDDELAY);//delay
#endif	
  
}

//*****************************************************************************
//! \Function 		: Lcd_Send_Nibble
//! \Description	: send a nibble to lcd .
//! \param 			: *Value : pointer to data
//! \return			: None.
//*****************************************************************************
void Lcd_Send_Nibble(uint8_t *Value)
{
  LCD_BYTE.Data=*Value;
  if(LCD_BYTE.BITS._7)LCD_SETBIT(_D7_LCD);else LCD_RESETBIT(_D7_LCD);
  if(LCD_BYTE.BITS._6)LCD_SETBIT(_D6_LCD);else LCD_RESETBIT(_D6_LCD);
  if(LCD_BYTE.BITS._5)LCD_SETBIT(_D5_LCD);else LCD_RESETBIT(_D5_LCD);
  if(LCD_BYTE.BITS._4)LCD_SETBIT(_D4_LCD);else LCD_RESETBIT(_D4_LCD);
#if __LCD_BIT_MODE__ == 8
  if(LCD_BYTE.BITS._3)LCD_SETBIT(_D3_LCD);else LCD_RESETBIT(_D3_LCD);
  if(LCD_BYTE.BITS._2)LCD_SETBIT(_D2_LCD);else LCD_RESETBIT(_D2_LCD);
  if(LCD_BYTE.BITS._1)LCD_SETBIT(_D1_LCD);else LCD_RESETBIT(_D1_LCD);
  if(LCD_BYTE.BITS._0)
    LCD_SETBIT(_D0_LCD);
  else LCD_RESETBIT(_D0_LCD);
#endif	
  
}

//*****************************************************************************
//! \Function 		: delay function for lcd library
//! \Description	: wait for 'var' count.
//! \param 			: "value" for delay
//! \return			: None.
//*****************************************************************************
void LCD_Delay(uint16_t var){
  while(--var);
}

//*****************************************************************************
//! \Function     : Delay_With_LCD_Enable(
//! \Description  : blocking delay which toggles EN pin.
//! \param      : Delay_Var
//! \return     : None.
//*****************************************************************************
        
void Delay_With_LCD_Enable(uint8_t Delay_Var)
{
  while(Delay_Var)
  {
          LCD_Delay(150);
          LCD_SETBIT(_EN_LCD);
          LCD_Delay(150);
          LCD_RESETBIT(_EN_LCD);
          Delay_Var--;
  }	
}