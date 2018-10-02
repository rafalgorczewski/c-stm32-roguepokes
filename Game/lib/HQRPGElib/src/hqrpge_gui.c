#include <stdlib.h>

#include <hqrp_graphics.h>
#include <hqrp_constants.h>
#include <hqrp_touch.h>

#include "hqrpge_gui.h"

void HQRPGE_draw_dialog_box(const HQRPGE_DialogBox * dialog_box) {
	HQRP_draw_rectangle(
		dialog_box->position,
		(HQRP_Vec2){ dialog_box->position.x + dialog_box->size.x,
					 dialog_box->position.y + dialog_box->size.y },
		dialog_box->outline_colour);
	HQRP_draw_rectangle(
		(HQRP_Vec2){ dialog_box->position.x + dialog_box->outline_width,
					 dialog_box->position.y + dialog_box->outline_width },
		(HQRP_Vec2){ dialog_box->position.x + dialog_box->size.x -
						 dialog_box->outline_width,
					 dialog_box->position.y + dialog_box->size.y -
						 dialog_box->outline_width },
		dialog_box->fill_colour);

	uint16_t dialog_center_x =
		dialog_box->position.x + (dialog_box->size.x >> 1);
	uint16_t text_center_x =
		(dialog_box->text_line_length_for_margin * dialog_box->text_scale *
		 (HQRP_FONT_CHAR_WIDTH + 1)) >>
		1;
	uint16_t text_position_x = abs((int)dialog_center_x - (int)text_center_x);

	HQRP_draw_text_scaled(
		(HQRP_Vec2){ text_position_x,
					 dialog_box->position.y + dialog_box->text_top_margin },
		dialog_box->text,
		dialog_box->text_colour,
		dialog_box->text_scale);

	for (size_t i = 0; i < dialog_box->buttons_count; ++i) {
		HQRPGE_draw_button(dialog_box->buttons[i]);
	}
}

void HQRPGE_draw_button(const HQRPGE_Button * button) {
	HQRP_draw_rectangle(button->position,
						(HQRP_Vec2){ button->position.x + button->size.x,
									 button->position.y + button->size.y },
						button->outline_colour);
	HQRP_draw_rectangle(
		(HQRP_Vec2){ button->position.x + button->outline_width,
					 button->position.y + button->outline_width },
		(HQRP_Vec2){
			button->position.x + button->size.x - button->outline_width,
			button->position.y + button->size.y - button->outline_width },
		button->fill_colour);

	uint16_t button_center_x = button->position.x + (button->size.x >> 1);
	uint16_t text_center_x =
		(button->text_line_length_for_margin * button->text_scale *
		 (HQRP_FONT_CHAR_WIDTH + 1)) >>
		1;
	uint16_t text_position_x = abs((int)button_center_x - (int)text_center_x);

	HQRP_draw_text_scaled(
		(HQRP_Vec2){ text_position_x,
					 button->position.y + button->text_top_margin },
		button->text,
		button->text_colour,
		button->text_scale);
}

void HQRPGE_draw_image_button(const HQRPGE_ImageButton * button) {
	HQRP_draw_image_scaled(button->position,
						   button->image,
						   button->image_size,
						   button->image_scale);
}

bool HQRPGE_is_button_clicked(const HQRPGE_Button * button) {
	HQRP_TouchPoint point = HQRP_get_touch_point();
	if (point.is_touched) {
		if ((point.position.x >= button->position.x) &&
			(point.position.x <= button->position.x + button->size.x) &&
			(point.position.y >= button->position.y) &&
			(point.position.y <= button->position.y + button->size.y)) {
			return true;
		}
	}
	return false;
}
bool HQRPGE_is_image_button_clicked(const HQRPGE_ImageButton * button) {
	HQRP_TouchPoint point = HQRP_get_touch_point();
	if (point.is_touched) {
		if ((point.position.x >= button->position.x) &&
			(point.position.x <= button->position.x + (button->image_size.x *
													   button->image_scale)) &&
			(point.position.y >= button->position.y) &&
			(point.position.y <= button->position.y + (button->image_size.y *
													   button->image_scale))) {
			return true;
		}
	}
	return false;
}

HQRPGE_GuiIsClicked HQRPGE_dialog_box_update(
	const HQRPGE_DialogBox * dialog_box, struct HQRPGE_Game * game) {
	for (size_t i = 0; i < dialog_box->buttons_count; ++i) {
		if (HQRPGE_is_button_clicked(dialog_box->buttons[i])) {
			dialog_box->buttons[i]->action(game);
			return HQRPGE_GUI_CLICKED;
		}
	}
	return HQRPGE_GUI_NOT_CLICKED;
}
HQRPGE_GuiIsClicked HQRPGE_button_update(const HQRPGE_Button * button,
										 struct HQRPGE_Game * game) {
	if (HQRPGE_is_button_clicked(button)) {
		button->action(game);
		return HQRPGE_GUI_CLICKED;
	}
	return HQRPGE_GUI_NOT_CLICKED;
}
HQRPGE_GuiIsClicked HQRPGE_image_button_update(
	const HQRPGE_ImageButton * button, struct HQRPGE_Game * game) {
	if (HQRPGE_is_image_button_clicked(button)) {
		button->action(game);
		return HQRPGE_GUI_CLICKED;
	}
	return HQRPGE_GUI_NOT_CLICKED;
}
