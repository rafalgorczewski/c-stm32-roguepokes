#include <math.h>
#include <stdio.h>

#include <hqrp_board.h>
#include <hqrp_graphics.h>
#include <hqrp_math.h>
#include <hqrp_constants.h>

#include <hqrpge_map.h>
#include <hqrpge_engine.h>
#include <hqrpge_pokes.h>

void HQRP_welcome_screen(void);

int main(void) {
	HQRP_init_board();
	HQRP_init_screen();

	HQRPGE_Map map = { .size = (HQRP_Vec2){ HQRPGE_MAP_SIZE, HQRPGE_MAP_SIZE },
					   .tiles = {},
					   .spawn_point = (HQRP_Vec2){ 0, 0 } };

	HQRPGE_Game game = {
		HQRPGE_GAMESTATE_MENU,
		&map,
		{ &HQRPGE_poke_psyduck,
		  &HQRPGE_poke_charmander,
		  &HQRPGE_poke_squirtle },
		{ &HQRPGE_poke_psyduck, &HQRPGE_poke_charmander, &HQRPGE_poke_squirtle }
	};
	HQRP_welcome_screen();

	while (1) {
		HQRPGE_draw_game(&game);
		HQRPGE_handle_input(&game);
	}
}

void HQRP_welcome_screen(void) {
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	for (size_t x = 0; x < (HQRP_SCREEN_WIDTH / 2) + 1; ++x) {
		for (size_t y = 0; y < HQRP_SCREEN_HEIGHT; ++y) {
			HQRP_draw_pixel((HQRP_Vec2){ x, y }, (y * y) - (x * x));
			HQRP_draw_pixel((HQRP_Vec2){ HQRP_SCREEN_WIDTH - x - 1, y },
							(y * y) - (x * x));
		}
	}
	HQRP_draw_text_scaled((HQRP_Vec2){ 85, 50 }, "HQRP", HQRP_COLOUR_BLACK, 10);
	HQRP_draw_text_scaled(
		(HQRP_Vec2){ 65, 110 }, "STATION", HQRP_COLOUR_BLACK, 7);
	HAL_Delay(1000);
	HQRP_draw_text_scaled(
		(HQRP_Vec2){ 15, 190 }, "Loading", HQRP_COLOUR_YELLOW, 5);
	HAL_Delay(5000);
}
