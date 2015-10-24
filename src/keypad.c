#include "keypad.h"
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include <stdio.h>

const char BUTTON_MAP[12] = "147*2580369#";

int keypad_gpio_reset() {
	GPIO_InitTypeDef gpio_init_rows;
	GPIO_InitTypeDef gpio_init_cols;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//set rows pins as output
	gpio_init_rows.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_rows.GPIO_OType = GPIO_OType_PP;
	gpio_init_rows.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4;
	gpio_init_rows.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_init_rows.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio_init_rows);
	
	//set cols pins as input
	gpio_init_cols.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_cols.GPIO_OType = GPIO_OType_PP;
	gpio_init_cols.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
	gpio_init_cols.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_cols.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio_init_cols);
	
		return 0;
	
}
int keypad_NVIC_config(){
		NVIC_InitTypeDef nvic_init_s;
	
		nvic_init_s.NVIC_IRQChannel = EXTI9_5_IRQn;
		nvic_init_s.NVIC_IRQChannelPreemptionPriority = 0x00;
		nvic_init_s.NVIC_IRQChannelSubPriority = 0x0F;
		nvic_init_s.NVIC_IRQChannelCmd = ENABLE;
	
		NVIC_Init(&nvic_init_s);
	
		return 0;
}	
int keypad_EXTI_config(){
	
	EXTI_InitTypeDef exti_init_col0;	//C5
	EXTI_InitTypeDef exti_init_col1;	//C6
	EXTI_InitTypeDef exti_init_col2;	//C8
	EXTI_InitTypeDef exti_init_col3;	//C9
	
	//let the system know that C5,C6, C8, C9 are being used
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource9);
	
	//set the line connections
	exti_init_col0.EXTI_Line = EXTI_Line5;
	exti_init_col1.EXTI_Line = EXTI_Line6;
	exti_init_col2.EXTI_Line = EXTI_Line8;
	exti_init_col3.EXTI_Line = EXTI_Line9;

	//enable interrupts
	exti_init_col0.EXTI_LineCmd = ENABLE;
	exti_init_col1.EXTI_LineCmd = ENABLE;
	exti_init_col2.EXTI_LineCmd = ENABLE;
	exti_init_col3.EXTI_LineCmd = ENABLE;
	
	//interrupt mode
	exti_init_col0.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_col1.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_col2.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_col3.EXTI_Mode = EXTI_Mode_Interrupt;
	
	//Triggers on Rising and Falling Edge
	exti_init_col0.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init_col1.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init_col2.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init_col3.EXTI_Trigger = EXTI_Trigger_Falling;
	
	//Add to EXTI
	EXTI_Init(&exti_init_col0);
	EXTI_Init(&exti_init_col1);
	EXTI_Init(&exti_init_col2);
	EXTI_Init(&exti_init_col3);
	
		return 0;

}
int keypad_switch(){
	GPIO_InitTypeDef gpio_init_rows;
	GPIO_InitTypeDef gpio_init_cols;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//set rows pins as input
	gpio_init_rows.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_rows.GPIO_OType = GPIO_OType_PP;
	gpio_init_rows.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4;
	gpio_init_rows.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_rows.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio_init_rows);
	
	//set cols pins as input
	gpio_init_cols.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_cols.GPIO_OType = GPIO_OType_PP;
	gpio_init_cols.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
	gpio_init_cols.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_init_cols.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio_init_cols);
	
		return 0;
}
/*!
	Makes system calls for setting up GPIO for keypad
	
	@return 0 on success, else negative
 */
 //C1,C2,C4, C5,C6,C8,C9
 //Row0,Row1,Row2, Col0,Col1,Col2,Col3
int keypad_setup() {
	//set variables
	GPIO_InitTypeDef gpio_init_rows;
	GPIO_InitTypeDef gpio_init_cols;
	
	//enable clock for GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//enable clock for SYSCFG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//set row pins as output
	gpio_init_rows.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_rows.GPIO_OType = GPIO_OType_PP;
	gpio_init_rows.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4;
	gpio_init_rows.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_init_rows.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio_init_rows);
	
	//set cols pins as input
	gpio_init_cols.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_cols.GPIO_OType = GPIO_OType_PP;
	gpio_init_cols.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
	gpio_init_cols.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_cols.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio_init_cols);

	keypad_EXTI_config();
	keypad_NVIC_config();
	
	
	return 0;
}
void EXTI9_5_IRQHandler(void){
	int col_select;
	int  row_select;
	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET) {
		col_select = 3;
		EXTI_ClearITPendingBit(EXTI_Line9);
	}else if(EXTI_GetITStatus(EXTI_Line8) != RESET) {
		col_select = 2;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}else if(EXTI_GetITStatus(EXTI_Line6) != RESET) {
		col_select = 1;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}else if(EXTI_GetITStatus(EXTI_Line5) != RESET) {
		col_select = 0;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}else
		return;
	
	keypad_switch();
	
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
		row_select = 0;
	else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == 0)
		row_select = 4;
	else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0)
		row_select = 8;
	else
		return;
	
	
	unsigned int selection = col_select + row_select;
	
	printf("button selected: %c\n", BUTTON_MAP[selection]);

	
	
	keypad_gpio_reset();

}
/*!
	Get's a guess from user
	@param *guess what the user guessed
	@return 0 on success, else negative
 */
int get_input(int* guess) {
	return 0;
}
