#ifndef HQRP_GRAPHICS_H
#define HQRP_GRAPHICS_H

#include <stdint.h>

#include "hqrp_math.h"

typedef uint16_t HQRP_Colour;
typedef uint8_t HQRP_TextPixel;

void HQRP_init_screen(void);
void HQRP_clear_screen(HQRP_Colour colour);

void HQRP_draw_pixel(HQRP_Vec2 point, HQRP_Colour colour);
void HQRP_draw_rectangle(HQRP_Vec2 start_point,
						 HQRP_Vec2 end_point,
						 HQRP_Colour colour);
void HQRP_draw_image(HQRP_Vec2 start_point,
					 const HQRP_Colour * image,
					 HQRP_Vec2 image_size);
void HQRP_draw_image_scaled(HQRP_Vec2 start_point,
							const HQRP_Colour * image,
							HQRP_Vec2 image_size,
							uint16_t scale);
void HQRP_draw_text(HQRP_Vec2 start_point,
					const char * text,
					HQRP_Colour colour);
void HQRP_draw_text_scaled(HQRP_Vec2 start_point,
						   const char * text,
						   HQRP_Colour colour,
						   uint16_t scale);
#endif
