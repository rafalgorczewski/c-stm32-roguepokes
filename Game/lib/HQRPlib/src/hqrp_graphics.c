#include "hqrp_constants.h"
#include "hqrp_graphics.h"

#include <stm32f3xx.h>

#define GPIO_SetPinValue(GPIOx, GPIO_Pin, val) \
	if (val) {                                 \
		GPIOx->ODR |= GPIO_Pin;                \
	} else {                                   \
		GPIOx->ODR &= ~GPIO_Pin;               \
	}

const HQRP_TextPixel HQRP_font[HQRP_FONT_CHAR_COUNT][HQRP_FONT_CHAR_SIZE] = {
	{ 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },  // 0
	{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },  // 1
	{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },  // 2
	{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },  // 3
	{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1 },  // 4
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 },  // 5
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },  // 6
	{ 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },  // 7
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },  // 8
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },  // 9

	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1 },  // a
	{ 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },  // b
	{ 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1 },  // c
	{ 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0 },  // d
	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1 },  // e
	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0 },  // f
	{ 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1 },  // g
	{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1 },  // h
	{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 },  // i
	{ 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0 },  // j
	{ 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1 },  // k
	{ 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1 },  // l
	{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },  // m
	{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },  // n
	{ 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0 },  // o
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0 },  // p
	{ 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1 },  // q
	{ 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1 },  // r
	{ 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0 },  // s
	{ 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 },  // t
	{ 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },  // u
	{ 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0 },  // v
	{ 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },  // w
	{ 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 },  // x
	{ 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0 },  // y
	{ 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1 },  // z

	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },  //:
	{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 },  //!
	{ 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0 },  //?
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // WHITESPACE
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }   // UNDEFINED
};

void HQRP_select_registry(uint16_t id);
void HQRP_write_data(uint32_t data);
void HQRP_write_to_registry(uint16_t id, uint32_t data);
void HQRP_draw_sign_scaled(HQRP_Vec2 start_point,
						   uint8_t sign_index,
						   HQRP_Colour colour,
						   uint16_t scale);

void HQRP_init_screen(void) {
	HAL_GPIO_WritePin(PORT_LCD_CS, PIN_LCD_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_RD, PIN_RD, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_WR, PIN_WR, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_BL_CTRL, PIN_BL_CTRL, GPIO_PIN_SET);

	HAL_GPIO_WritePin(PORT_RST, PIN_RST, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(PORT_RST, PIN_RST, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(PORT_RST, PIN_RST, GPIO_PIN_SET);

	HAL_Delay(500);
	HAL_GPIO_WritePin(PORT_LCD_CS, PIN_LCD_CS, GPIO_PIN_RESET);

	HQRP_write_to_registry(0x0001, 0x0000);
	HQRP_write_to_registry(0x0002, 0x0700);
	HQRP_write_to_registry(0x0003, 0x1117);

	HQRP_write_to_registry(0x0004, 0x0000);
	HQRP_write_to_registry(0x0008, 0x0207);
	HQRP_write_to_registry(0x0009, 0x0000);
	HQRP_write_to_registry(0x000A, 0x0000);
	HQRP_write_to_registry(0x000C, 0x0001);
	HQRP_write_to_registry(0x000D, 0x0000);
	HQRP_write_to_registry(0x000F, 0x0000);

	HQRP_write_to_registry(0x0010, 0x0000);
	HQRP_write_to_registry(0x0011, 0x0007);
	HQRP_write_to_registry(0x0012, 0x0000);
	HQRP_write_to_registry(0x0013, 0x0000);

	HQRP_write_to_registry(0x0010, 0x1290);
	HQRP_write_to_registry(0x0011, 0x0227);

	HQRP_write_to_registry(0x0012, 0x001b);

	HQRP_write_to_registry(0x0013, 0x1500);

	HQRP_write_to_registry(0x0029, 0x0018);
	HQRP_write_to_registry(0x002B, 0x000D);

	HQRP_write_to_registry(0x0030, 0x0004);
	HQRP_write_to_registry(0x0031, 0x0307);
	HQRP_write_to_registry(0x0032, 0x0002);
	HQRP_write_to_registry(0x0035, 0x0206);
	HQRP_write_to_registry(0x0036, 0x0408);
	HQRP_write_to_registry(0x0037, 0x0507);
	HQRP_write_to_registry(0x0038, 0x0204);
	HQRP_write_to_registry(0x0039, 0x0707);
	HQRP_write_to_registry(0x003C, 0x0504);
	HQRP_write_to_registry(0x003D, 0x0F02);

	HQRP_write_to_registry(0x0050, 0x0000);
	HQRP_write_to_registry(0x0051, 0x00EF);
	HQRP_write_to_registry(0x0052, 0x0000);
	HQRP_write_to_registry(0x0053, 0x013F);
	HQRP_write_to_registry(0x0060, 0xA700);
	HQRP_write_to_registry(0x0061, 0x0001);
	HQRP_write_to_registry(0x006A, 0x0000);

	HQRP_write_to_registry(0x0080, 0x0000);
	HQRP_write_to_registry(0x0081, 0x0000);
	HQRP_write_to_registry(0x0082, 0x0000);
	HQRP_write_to_registry(0x0083, 0x0000);
	HQRP_write_to_registry(0x0084, 0x0000);
	HQRP_write_to_registry(0x0085, 0x0000);

	HQRP_write_to_registry(0x0090, 0x0010);
	HQRP_write_to_registry(0x0092, 0x0600);
	HQRP_write_to_registry(0x0093, 0x0003);
	HQRP_write_to_registry(0x0095, 0x0110);
	HQRP_write_to_registry(0x0097, 0x0000);
	HQRP_write_to_registry(0x0098, 0x0000);

	HQRP_write_to_registry(0x0007, 0x0133);
}

void HQRP_select_registry(uint16_t id) {
	GPIO_SetPinValue(PORT_LCD_CS, PIN_LCD_CS, GPIO_PIN_RESET);
	GPIO_SetPinValue(PORT_RD, PIN_RD, GPIO_PIN_SET);
	GPIO_SetPinValue(PORT_WR, PIN_WR, GPIO_PIN_SET);

	GPIO_SetPinValue(PORT_RS, PIN_RS, GPIO_PIN_RESET);

	GPIO_SetPinValue(PORT_DATA, PIN_DATA_0, id & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_1, (id >> 1) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_2, (id >> 2) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_3, (id >> 3) & 1);

	GPIO_SetPinValue(PORT_DATA, PIN_DATA_4, (id >> 4) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_5, (id >> 5) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_6, (id >> 6) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_7, (id >> 7) & 1);

	GPIO_SetPinValue(PORT_WR, PIN_WR, GPIO_PIN_RESET);

	GPIO_SetPinValue(PORT_WR, PIN_WR, GPIO_PIN_SET);

	GPIO_SetPinValue(PORT_RS, PIN_RS, GPIO_PIN_SET);
}
void HQRP_write_data(uint32_t data) {
	GPIO_SetPinValue(PORT_LCD_CS, PIN_LCD_CS, GPIO_PIN_RESET);

	GPIO_SetPinValue(PORT_RS, PIN_RS, GPIO_PIN_SET);
	GPIO_SetPinValue(PORT_RD, PIN_RD, GPIO_PIN_SET);

	GPIO_SetPinValue(PORT_DATA, PIN_DATA_0, data & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_1, (data >> 1) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_2, (data >> 2) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_3, (data >> 3) & 1);

	GPIO_SetPinValue(PORT_DATA, PIN_DATA_4, (data >> 4) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_5, (data >> 5) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_6, (data >> 6) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_7, (data >> 7) & 1);

	GPIO_SetPinValue(PORT_DATA, PIN_DATA_8, (data >> 8) & 1);
	GPIO_SetPinValue(PORT_DATA, PIN_DATA_9, (data >> 9) & 1);
	GPIO_SetPinValue(PORT_DATA_10, PIN_DATA_10, (data >> 10) & 1);
	GPIO_SetPinValue(PORT_DATA_11, PIN_DATA_11, (data >> 11) & 1);

	GPIO_SetPinValue(PORT_DATA_12, PIN_DATA_12, (data >> 12) & 1);
	GPIO_SetPinValue(PORT_DATA_13, PIN_DATA_13, (data >> 13) & 1);
	GPIO_SetPinValue(PORT_DATA_14, PIN_DATA_14, (data >> 14) & 1);
	GPIO_SetPinValue(PORT_DATA_15, PIN_DATA_15, (data >> 15) & 1);

	GPIO_SetPinValue(PORT_WR, PIN_WR, GPIO_PIN_RESET);

	GPIO_SetPinValue(PORT_WR, PIN_WR, GPIO_PIN_SET);
}
void HQRP_write_to_registry(uint16_t id, uint32_t data) {
	HQRP_select_registry(id);
	HQRP_write_data(data);
}

void HQRP_clear_screen(HQRP_Colour colour) {
	if (colour != HQRP_COLOUR_TRANSPARENT) {
		HQRP_write_to_registry(0x0020, 0);
		HQRP_write_to_registry(0x0021, 0);
		HQRP_select_registry(0x22);
		for (int i = 0; i < HQRP_SCREEN_WIDTH * HQRP_SCREEN_HEIGHT; ++i) {
			HQRP_write_data(colour);
		}
	}
}
void HQRP_draw_pixel(HQRP_Vec2 point, HQRP_Colour colour) {
	if (colour != HQRP_COLOUR_TRANSPARENT) {
		HQRP_write_to_registry(0x0020, HQRP_SCREEN_HEIGHT - point.y - 1);
		HQRP_write_to_registry(0x0021, HQRP_SCREEN_WIDTH - point.x - 1);
		HQRP_write_to_registry(0x0022, colour);
	}
}
void HQRP_draw_rectangle(HQRP_Vec2 start_point,
						 HQRP_Vec2 end_point,
						 HQRP_Colour colour) {
	HQRP_write_to_registry(0x0050, HQRP_SCREEN_HEIGHT - end_point.y - 1);
	HQRP_write_to_registry(0x0051, HQRP_SCREEN_HEIGHT - start_point.y - 1);
	HQRP_write_to_registry(0x0052, HQRP_SCREEN_WIDTH - end_point.x - 1);
	HQRP_write_to_registry(0x0053, HQRP_SCREEN_WIDTH - start_point.x - 1);
	HQRP_write_to_registry(0x0020, HQRP_SCREEN_HEIGHT - start_point.y - 1);
	HQRP_write_to_registry(0x0021, HQRP_SCREEN_WIDTH - start_point.x - 1);
	for (uint16_t x = start_point.x; x < end_point.x; ++x) {
		for (uint16_t y = start_point.y; y < end_point.y; ++y) {
			HQRP_write_to_registry(0x0022, colour);
		}
	}
	HQRP_write_to_registry(0x0050, 0);
	HQRP_write_to_registry(0x0051, HQRP_SCREEN_HEIGHT - 1);
	HQRP_write_to_registry(0x0052, 0);
	HQRP_write_to_registry(0x0053, HQRP_SCREEN_WIDTH - 1);
}
void HQRP_draw_image(HQRP_Vec2 start_point,
					 const HQRP_Colour * image,
					 HQRP_Vec2 image_size) {
	HQRP_draw_image_scaled(start_point, image, image_size, 1);
}
void HQRP_draw_image_scaled(HQRP_Vec2 start_point,
							const HQRP_Colour * image,
							HQRP_Vec2 image_size,
							uint16_t scale) {
	for (uint16_t x = 0; x < image_size.x; ++x) {
		for (uint16_t y = 0; y < image_size.y; ++y) {
			for (uint16_t xx = x * scale; xx < (x + 1) * scale; ++xx) {
				for (uint16_t yy = y * scale; yy < (y + 1) * scale; ++yy) {
					HQRP_draw_pixel(
						(HQRP_Vec2){ start_point.x + xx, start_point.y + yy },
						image[(y * image_size.x) + x]);
				}
			}
		}
	}
}

void HQRP_draw_text(HQRP_Vec2 start_point,
					const char * text,
					HQRP_Colour colour) {
	HQRP_draw_text_scaled(start_point, text, colour, 1);
}
void HQRP_draw_text_scaled(HQRP_Vec2 start_point,
						   const char * text,
						   HQRP_Colour colour,
						   uint16_t scale) {
	HQRP_Vec2 cursor_pos = start_point;
	size_t i = 0;

	while (text[i] != '\0') {
		if (text[i] == '\n') {
			cursor_pos.x = start_point.x;
			cursor_pos.y += (HQRP_FONT_CHAR_HEIGHT + 1) * scale;
		} else {
			if ((uint8_t)text[i] >= 48 && (uint8_t)text[i] <= 57) {
				HQRP_draw_sign_scaled(cursor_pos, text[i] - 48, colour, scale);
			} else if ((uint8_t)text[i] >= 65 && (uint8_t)text[i] <= 90) {
				HQRP_draw_sign_scaled(
					cursor_pos, text[i] - 65 + 10, colour, scale);
			} else if ((uint8_t)text[i] >= 97 && (uint8_t)text[i] <= 122) {
				HQRP_draw_sign_scaled(
					cursor_pos, (uint8_t)text[i] - 97 + 10, colour, scale);
			} else if ((uint8_t)text[i] == ':') {
				HQRP_draw_sign_scaled(cursor_pos, 36, colour, scale);
			} else if ((uint8_t)text[i] == '!') {
				HQRP_draw_sign_scaled(cursor_pos, 37, colour, scale);
			} else if ((uint8_t)text[i] == '?') {
				HQRP_draw_sign_scaled(cursor_pos, 38, colour, scale);
			} else if ((uint8_t)text[i] == ' ') {
				HQRP_draw_sign_scaled(cursor_pos, 39, colour, scale);
			} else {
				HQRP_draw_sign_scaled(cursor_pos, 40, colour, scale);
			}
			cursor_pos.x += (HQRP_FONT_CHAR_WIDTH + 1) * scale;
		}
		++i;
	}
}

void HQRP_draw_sign_scaled(HQRP_Vec2 start_point,
						   uint8_t sign_index,
						   HQRP_Colour colour,
						   uint16_t scale) {
	for (size_t x = 0; x < HQRP_FONT_CHAR_WIDTH; ++x) {
		for (size_t y = 0; y < HQRP_FONT_CHAR_HEIGHT; ++y) {
			for (size_t xx = x * scale; xx < (x + 1) * scale; ++xx) {
				for (size_t yy = y * scale; yy < (y + 1) * scale; ++yy) {
					HQRP_draw_pixel(
						(HQRP_Vec2){ start_point.x + xx, start_point.y + yy },
						HQRP_font[sign_index][(y * HQRP_FONT_CHAR_WIDTH) + x] *
							colour);
				}
			}
		}
	}
}