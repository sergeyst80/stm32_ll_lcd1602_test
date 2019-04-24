#include "hd44780.h"
#include "Delays.h"

//***************************************************************************
//Definitions
//***************************************************************************

//Constants
#define CMD_FCLR								0x01
#define CMD_CLR									0x02
#define CMD_SHIFT_CFG						0x04
#define CMD_DISPLAY_CURSOR			0x08
#define CMD_SCREEN_CURSOR_SHIFT	0x10
#define CMD_BUS_FONT						0x20
#define CMD_CGRAM_ADDR					0x40
#define CMD_DDRAM_ADDR					0x80

#define SHIFT_CFG_ID						0x02
#define SHIFT_CFG_S							0x01
#define DISPLAY_CURSOR_D				0x04
#define DISPLAY_CURSOR_C				0x02
#define DISPLAY_CURSOR_B				0x01
#define SCREEN_CURSOR_SHIFT_SC	0x08
#define SCREEN_CURSOR_SHIFT_RL	0x04
#define	CMD_BUS_FONT_DL					0x10
#define	CMD_BUS_FONT_N					0x80
#define	CMD_BUS_FONT_F					0x40

//Macroses
#define LCD_RS_H()	LL_GPIO_SetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin); Delay_us_ms(USEC, 1)
#define LCD_RS_L()	LL_GPIO_ResetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin); Delay_us_ms(USEC, 1)
#define LCD_E_H()		LL_GPIO_SetOutputPin(LCD_E_GPIO_Port, LCD_E_Pin); Delay_us_ms(USEC, 1)
#define LCD_E_L()		LL_GPIO_ResetOutputPin(LCD_E_GPIO_Port, LCD_E_Pin); Delay_us_ms(USEC, 1)
#define LCD_RW_H()	LL_GPIO_SetOutputPin(LCD_RW_GPIO_Port, LCD_RW_Pin); Delay_us_ms(USEC, 1)
#define LCD_RW_L()	LL_GPIO_ResetOutputPin(LCD_RW_GPIO_Port, LCD_RW_Pin); Delay_us_ms(USEC, 1)

//Variables
LcdPinsTypedef LcdPins[8];

//Functions
void LCD_write_IR(uint8_t);
void LCD_write_DR(uint8_t);
void LCD_write(enum enumIrDr, uint8_t);
void LCD_write_8bit(uint8_t);
void LCD_write_4bit(uint8_t);

//***************************************************************************
//Functions realizations
//***************************************************************************

//LCD initialization func
void LCD_Init(void)
{
	LCD_E_L();
	LCD_RS_L();
	LCD_RW_L();
	Delay_us_ms(MSEC, 100);
	LcdPins[4].GPIOx = LCD_D4_GPIO_Port;
	LcdPins[4].PinMask = LCD_D4_Pin;
	LcdPins[5].GPIOx = LCD_D5_GPIO_Port;
	LcdPins[5].PinMask = LCD_D5_Pin;
	LcdPins[6].GPIOx = LCD_D6_GPIO_Port;
	LcdPins[6].PinMask = LCD_D6_Pin;
	LcdPins[7].GPIOx = LCD_D7_GPIO_Port;
	LcdPins[7].PinMask = LCD_D7_Pin;
	
	#ifdef LCD_DATA_4_BIT_MODE
		LCD_write_4bit(0x30);
		Delay_us_ms(MSEC, 10);
		LCD_write_4bit(0x30);
		Delay_us_ms(USEC, 200);
		LCD_write_4bit(0x30);
		LCD_write_4bit(0x20);
		LCD_write(IR, 0x28);
	#else
		LcdPins[0].GPIOx = LCD_D0_GPIO_Port;
		LcdPins[0].PinMask = LCD_D0_Pin;
		LcdPins[1].GPIOx = LCD_D1_GPIO_Port;
		LcdPins[1].PinMask = LCD_D1_Pin;
		LcdPins[2].GPIOx = LCD_D2_GPIO_Port;
		LcdPins[2].PinMask = LCD_D2_Pin;
		LcdPins[3].GPIOx = LCD_D3_GPIO_Port;
		LcdPins[3].PinMask = LCD_D3_Pin;
		LCD_write(IR, 0x30);
		Delay_us_ms(MSEC, 10);
		LCD_write(IR, 0x30);
		Delay_us_ms(USEC, 200);
		LCD_write(IR, 0x30);
		LCD_write(IR, 0x38);
	#endif

	LCD_write(IR, 0x0D);
	LCD_write(IR, 0x01);
	LCD_write(DR, 'H');
	LCD_write(DR, 'e');
	LCD_write(DR, 'l');
	LCD_write(DR, 'l');
	LCD_write(DR, 'o');
	LCD_write(DR, '!');
}

//LCD write function
//dir - write direction (IR - instruction register IR, DR - data register DR)
//data - writing data
void LCD_write(enum enumIrDr dir, uint8_t data){
	switch(dir){
		case IR: LCD_RS_L();
			break;
		case DR: LCD_RS_H();
			break;
		default:
			break;
	}
	#ifdef LCD_DATA_4_BIT_MODE
		LCD_write_4bit(data);
		LCD_write_4bit(data << 4);
	#else
		LCD_write_8bit(data);
	#endif
}

//LCD write function for 8-bit databus mode
void LCD_write_8bit(uint8_t byte){
	
	Delay_us_ms(USEC, 1);
	
	for (int count = 8; count > 0; --count){
		int index = count - 1;

		if ((byte & 0x80) != 0){
			LL_GPIO_SetOutputPin(LcdPins[index].GPIOx, LcdPins[index].PinMask);
		}
		else{
			LL_GPIO_ResetOutputPin(LcdPins[index].GPIOx, LcdPins[index].PinMask);
		}

		byte <<= 1;
	}
	
	LCD_E_H();
	Delay_us_ms(USEC, 1);
	LCD_E_L();
	Delay_us_ms(USEC, 1);
}

//LCD write function for 4-bit databus mode
void LCD_write_4bit(uint8_t byte){
	LCD_RW_L();
	
	for (int count = 8; count > 4; --count){
		int index = count - 1;
		if ((byte & 0x80) != 0){
			LL_GPIO_SetOutputPin(LcdPins[index].GPIOx, LcdPins[index].PinMask);
		}
		else{
			LL_GPIO_ResetOutputPin(LcdPins[index].GPIOx, LcdPins[index].PinMask);
		}

		byte <<= 1;
	}
	
	LCD_E_H();
	LCD_E_L();
}
