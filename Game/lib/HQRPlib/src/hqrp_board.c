#include "hqrp_board.h"
#include "hqrp_constants.h"

#include <stm32f3xx.h>

void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void HQRP_init_board(void) {
	HAL_Init();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio.Pin = PIN_DATA_0;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_1;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_2;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_3;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_4;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_5;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_6;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_7;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_8;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_9;
	HAL_GPIO_Init(PORT_DATA, &gpio);
	gpio.Pin = PIN_DATA_10;
	HAL_GPIO_Init(PORT_DATA_10, &gpio);
	gpio.Pin = PIN_DATA_11;
	HAL_GPIO_Init(PORT_DATA_11, &gpio);
	gpio.Pin = PIN_DATA_12;
	HAL_GPIO_Init(PORT_DATA_12, &gpio);
	gpio.Pin = PIN_DATA_13;
	HAL_GPIO_Init(PORT_DATA_13, &gpio);
	gpio.Pin = PIN_DATA_14;
	HAL_GPIO_Init(PORT_DATA_14, &gpio);
	gpio.Pin = PIN_DATA_15;
	HAL_GPIO_Init(PORT_DATA_15, &gpio);

	gpio.Pin = PIN_LCD_CS;
	HAL_GPIO_Init(PORT_LCD_CS, &gpio);
	gpio.Pin = PIN_WR;
	HAL_GPIO_Init(PORT_WR, &gpio);

	gpio.Pin = PIN_RST;
	HAL_GPIO_Init(PORT_RST, &gpio);
	gpio.Pin = PIN_BL_CTRL;
	HAL_GPIO_Init(PORT_BL_CTRL, &gpio);

	gpio.Pin = PIN_RS;
	HAL_GPIO_Init(PORT_RS, &gpio);
	gpio.Pin = PIN_RD;
	HAL_GPIO_Init(PORT_RD, &gpio);
	gpio.Pin = PIN_NC;
	HAL_GPIO_Init(PORT_NC, &gpio);
	gpio.Pin = PIN_TP_CS;
	HAL_GPIO_Init(PORT_TP_CS, &gpio);
	HAL_GPIO_WritePin(PORT_TP_CS, PIN_TP_CS, GPIO_PIN_SET);
	gpio.Pin = PIN_TP_SDI;
	HAL_GPIO_Init(PORT_TP_SDI, &gpio);
	gpio.Pin = PIN_TP_SCK;
	HAL_GPIO_Init(PORT_TP_SCK, &gpio);
	HAL_GPIO_WritePin(PORT_TP_SCK, PIN_TP_SCK, GPIO_PIN_RESET);

	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pin = PIN_TP_IRQ;
	HAL_GPIO_Init(PORT_TP_IRQ, &gpio);
	gpio.Pin = PIN_TP_SDO;
	HAL_GPIO_Init(PORT_TP_SDO, &gpio);
}