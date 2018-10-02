#ifndef HQRPGE_GUI_H
#define HQRPGE_GUI_H

#include <stdbool.h>

#include <hqrp_math.h>
#include <hqrp_graphics.h>

#include "hqrpge_constants.h"
struct HQRPGE_Game;

typedef enum { HQRPGE_GUI_NOT_CLICKED, HQRPGE_GUI_CLICKED } HQRPGE_GuiIsClicked;

typedef struct {
	HQRP_Vec2 position;
	HQRP_Vec2 size;
	char text[HQRPGE_GUI_BUTTON_TEXT_LENGTH_MAX];
	uint8_t text_line_length_for_margin;
	uint8_t text_top_margin;
	uint8_t text_scale;
	HQRP_Colour text_colour;
	HQRP_Colour outline_colour;
	HQRP_Colour fill_colour;
	uint8_t outline_width;
	void (*action)(struct HQRPGE_Game *);
} HQRPGE_Button;

typedef struct {
	HQRP_Vec2 position;
	HQRP_Vec2 image_size;
	const HQRP_Colour * image;
	uint8_t image_scale;
	void (*action)(struct HQRPGE_Game *);
} HQRPGE_ImageButton;

typedef struct {
	HQRP_Vec2 position;
	HQRP_Vec2 size;
	const char text[HQRPGE_GUI_DIALOGBOX_TEXT_LENGTH_MAX];
	uint8_t text_line_length_for_margin;
	uint8_t text_top_margin;
	uint8_t text_scale;
	HQRP_Colour text_colour;
	HQRP_Colour outline_colour;
	HQRP_Colour fill_colour;
	uint8_t outline_width;
	uint8_t buttons_count;
	const HQRPGE_Button * buttons[HQRPGE_GUI_DIALOGBOX_BUTTONS_MAX];
} HQRPGE_DialogBox;

void HQRPGE_draw_dialog_box(const HQRPGE_DialogBox * dialog_box);

void HQRPGE_draw_button(const HQRPGE_Button * button);
void HQRPGE_draw_image_button(const HQRPGE_ImageButton * button);
bool HQRPGE_is_button_clicked(const HQRPGE_Button * button);
bool HQRPGE_is_image_button_clicked(const HQRPGE_ImageButton * button);

HQRPGE_GuiIsClicked HQRPGE_dialog_box_update(
	const HQRPGE_DialogBox * dialog_box, struct HQRPGE_Game * game);
HQRPGE_GuiIsClicked HQRPGE_button_update(const HQRPGE_Button * button,
										 struct HQRPGE_Game * game);
HQRPGE_GuiIsClicked HQRPGE_image_button_update(
	const HQRPGE_ImageButton * button, struct HQRPGE_Game * game);

#endif
