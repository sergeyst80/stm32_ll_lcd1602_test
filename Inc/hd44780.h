#ifndef __HD44780_H
#define __HD44780_H

#ifdef __cplusplus
 extern "C" {
#endif
/*****************************************************************************/

#include "main.h"	 

#define LCD_DATA_4_BIT_MODE

/*
uint8_t cols;
	uint8_t rows;
	uint8_t symb_size_x;
	uint8_t symb_size_y;
*/

typedef struct{
	uint8_t;
	uint32_t PinMask;
} LcdInitTypedef;	 
	 
enum enumIrDr {IR, DR};

typedef struct{
	GPIO_TypeDef *GPIOx;
	uint32_t PinMask;
} LcdPinsTypedef;

//Definitions of MCU pins for 4-bit LCD mode
//LCD control pins
#define LCD_RS_Pin LL_GPIO_PIN_13
#define LCD_RS_GPIO_Port GPIOC

#define LCD_RW_Pin LL_GPIO_PIN_14
#define LCD_RW_GPIO_Port GPIOC

#define LCD_E_Pin LL_GPIO_PIN_15
#define LCD_E_GPIO_Port GPIOC

//LCD data pins
#define LCD_D4_Pin LL_GPIO_PIN_0
#define LCD_D4_GPIO_Port GPIOA

#define LCD_D5_Pin LL_GPIO_PIN_1
#define LCD_D5_GPIO_Port GPIOA

#define LCD_D6_Pin LL_GPIO_PIN_2
#define LCD_D6_GPIO_Port GPIOA

#define LCD_D7_Pin LL_GPIO_PIN_3
#define LCD_D7_GPIO_Port GPIOA	 

//Definitions of MCU pins for 8-bit LCD mode
#ifndef LCD_DATA_4_BIT_MODE

	#define LCD_D0_Pin LL_GPIO_PIN_x
	#define LCD_D0_GPIO_Port GPIOx

	#define LCD_D1_Pin LL_GPIO_PIN_x
	#define LCD_D1_GPIO_Port GPIOx
	
	#define LCD_D2_Pin LL_GPIO_PIN_x
	#define LCD_D2_GPIO_Port GPIOx
	
	#define LCD_D3_Pin LL_GPIO_PIN_x
	#define LCD_D3_GPIO_Port GPIOx

#endif
	 
void LCD_Init(void);	 
/*****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* __HD44780_H */
