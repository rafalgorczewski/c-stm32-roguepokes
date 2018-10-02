#include "hqrp_touch.h"
#include "hqrp_constants.h"

#include <stm32f3xx.h>

#define HQRP_TP_CLK_TICK                                      \
	HAL_GPIO_WritePin(PORT_TP_SCK, PIN_TP_SCK, GPIO_PIN_SET); \
	HAL_GPIO_WritePin(PORT_TP_SCK, PIN_TP_SCK, GPIO_PIN_RESET);

#define HQRP_TP_X_OFFSET 340
#define HQRP_TP_Y_OFFSET 15
#define HQRP_TP_X_RATIO 22
#define HQRP_TP_Y_RATIO 30

uint16_t HQRP_get_touch_x(void);
uint16_t HQRP_get_touch_y(void);
uint16_t HQRP_get_touch_z(void);

uint16_t HQRP_tp_transmit_receive(uint8_t control_byte);

HQRP_TouchPoint HQRP_get_touch_point(void) {
	uint16_t pressure = HQRP_get_touch_z();
	return (HQRP_TouchPoint){
		(HQRP_Vec2){
			HQRP_TP_X_OFFSET - (HQRP_get_touch_x() / HQRP_TP_X_RATIO),
			(HQRP_get_touch_y() / HQRP_TP_Y_RATIO) - HQRP_TP_Y_OFFSET },
		pressure,
		((pressure > 10) ? true : false)
	};
}

uint16_t HQRP_get_touch_x(void) {
	return HQRP_tp_transmit_receive(0x90);
}
uint16_t HQRP_get_touch_y(void) {
	return HQRP_tp_transmit_receive(0xD0);
}
uint16_t HQRP_get_touch_z(void) {
	int z = HQRP_tp_transmit_receive(0xB0) + 4095;
	z -= HQRP_tp_transmit_receive(0xC0);
	return (z < 0) ? 0 : z;
}

uint16_t HQRP_tp_transmit_receive(uint8_t control_byte) {
	uint16_t data = 0;
	HAL_GPIO_WritePin(PORT_TP_CS, PIN_TP_CS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, (control_byte >> 7) & 1);
	HQRP_TP_CLK_TICK
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, (control_byte >> 6) & 1);
	HQRP_TP_CLK_TICK
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, (control_byte >> 5) & 1);
	HQRP_TP_CLK_TICK
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, (control_byte >> 4) & 1);
	HQRP_TP_CLK_TICK
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, (control_byte >> 3) & 1);
	HQRP_TP_CLK_TICK
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, (control_byte >> 2) & 1);
	HQRP_TP_CLK_TICK
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, (control_byte >> 1) & 1);
	HQRP_TP_CLK_TICK
	HAL_GPIO_WritePin(PORT_TP_SDI, PIN_TP_SDI, control_byte & 1);
	HQRP_TP_CLK_TICK

	HQRP_TP_CLK_TICK

	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK
	data |= HAL_GPIO_ReadPin(PORT_TP_SDO, PIN_TP_SDO);
	data <<= 1;
	HQRP_TP_CLK_TICK

	HQRP_TP_CLK_TICK
	HQRP_TP_CLK_TICK
	HQRP_TP_CLK_TICK

	HAL_GPIO_WritePin(PORT_TP_CS, PIN_TP_CS, GPIO_PIN_SET);

	return data;
}
