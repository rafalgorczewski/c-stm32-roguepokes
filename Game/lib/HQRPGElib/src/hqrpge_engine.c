#include "hqrpge_engine.h"
#include "hqrpge_map.h"
#include "hqrpge_entity.h"
#include "hqrpge_sprites.h"
#include "hqrpge_gui.h"

#include <hqrp_constants.h>
#include <hqrp_graphics.h>
#include <hqrp_touch.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static HQRPGE_Button HQRPGE_gui_menu_seed;
static HQRPGE_Button HQRPGE_gui_menu_new_game;
static HQRPGE_Button HQRPGE_gui_seed_dialog_button;
static HQRPGE_DialogBox HQRPGE_gui_seed_dialog;
static HQRPGE_Button HQRPGE_gui_starter1;
static HQRPGE_Button HQRPGE_gui_starter2;
static HQRPGE_Button HQRPGE_gui_starter3;
static HQRPGE_Button HQRPGE_gui_help_dialog_button;
static HQRPGE_DialogBox HQRPGE_gui_help_dialog;
static HQRPGE_ImageButton HQRPGE_gui_movement_arrows_background;
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_up;
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_down;
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_left;
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_right;
static HQRPGE_ImageButton HQRPGE_gui_exit;

void HQRPGE_draw_game(HQRPGE_Game * game) {
	switch (game->game_state) {
		case HQRPGE_GAMESTATE_MENU:
			HQRPGE_draw_menu(game);
			break;
		case HQRPGE_GAMESTATE_GENERATE_SEED:
			HQRPGE_draw_generate_seed(game);
			break;
		case HQRPGE_GAMESTATE_STARTER_SELECTION:
			HQRPGE_draw_starter_selection(game);
			break;
		case HQRPGE_GAMESTATE_MAP:
			HQRP_clear_screen(HQRP_COLOUR_BLACK);
			HQRPGE_draw_hourglass(game);
			HQRPGE_draw_movement_keys(game);
			/* fall through */
		case HQRPGE_GAMESTATE_MAP_MOVEMENT_UPDATE:
			HQRPGE_draw_hourglass(game);
			HQRPGE_draw_map(game);
			HQRPGE_draw_entities(game);
			HQRPGE_draw_player(game);
			HQRPGE_draw_minimap(game);
			HQRPGE_draw_empty_on_hourglass(game);
			HQRPGE_draw_exit(game);
			break;
		case HQRPGE_GAMESTATE_BATTLE:
			HQRPGE_draw_battle(game);
			break;
		default:
			break;
	}
}

void HQRPGE_draw_hourglass(HQRPGE_Game * game) {
	HQRP_draw_image_scaled(
		(HQRP_Vec2){ 0,
					 HQRP_SCREEN_HEIGHT - 1 -
						 (HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE) },
		HQRPGE_sprite_hourglass,
		HQRPGE_SPRITE_SIZE,
		HQRPGE_GFX_SCALE);
}

void HQRPGE_draw_empty_on_hourglass(HQRPGE_Game * game) {
	HQRP_draw_rectangle(
		(HQRP_Vec2){ 0,
					 HQRP_SCREEN_HEIGHT - 1 -
						 (HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE) },
		(HQRP_Vec2){ HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE,
					 HQRP_SCREEN_HEIGHT - 1 },
		HQRP_COLOUR_BLACK);
}

void HQRPGE_draw_exit(HQRPGE_Game * game) {
	HQRPGE_draw_image_button(&HQRPGE_gui_exit);
}

void HQRPGE_draw_menu(HQRPGE_Game * game) {
	char seed_str[10];
	sprintf(seed_str, "%d", game->seed);

	HQRP_clear_screen(HQRP_COLOUR_BROWN);
	HQRP_draw_text_scaled((HQRP_Vec2){ 15, 15 }, "MENU", HQRP_COLOUR_YELLOW, 7);
	HQRP_draw_text_scaled(
		(HQRP_Vec2){ 15, 60 }, "Seed:", HQRP_COLOUR_ORANGE, 4);
	HQRP_draw_text_scaled(
		(HQRP_Vec2){ 120, 60 }, seed_str, HQRP_COLOUR_ORANGE, 4);
	HQRPGE_draw_button(&HQRPGE_gui_menu_new_game);
	HQRPGE_draw_button(&HQRPGE_gui_menu_seed);
}

void HQRPGE_draw_generate_seed(HQRPGE_Game * game) {
	HQRPGE_draw_dialog_box(&HQRPGE_gui_seed_dialog);
}

void HQRPGE_draw_starter_selection(HQRPGE_Game * game) {
	strcpy(HQRPGE_gui_starter1.text, game->starter_pokes[0]->name);
	HQRPGE_gui_starter1.text_line_length_for_margin =
		strlen(HQRPGE_gui_starter1.text);
	strcpy(HQRPGE_gui_starter2.text, game->starter_pokes[1]->name);
	HQRPGE_gui_starter2.text_line_length_for_margin =
		strlen(HQRPGE_gui_starter2.text);
	strcpy(HQRPGE_gui_starter3.text, game->starter_pokes[2]->name);
	HQRPGE_gui_starter3.text_line_length_for_margin =
		strlen(HQRPGE_gui_starter3.text);
	HQRP_clear_screen(HQRP_COLOUR_PEAR);
	HQRP_draw_text_scaled(
		(HQRP_Vec2){ 20, 30 }, "CHOOSE STARTER", HQRP_COLOUR_YELLOW, 5);
	HQRPGE_draw_button(&HQRPGE_gui_starter1);
	HQRP_draw_image_scaled((HQRP_Vec2){ 26, 80 },
						   game->starter_pokes[0]->sprite,
						   HQRPGE_SPRITE_POKE_SIZE,
						   5);
	HQRPGE_draw_button(&HQRPGE_gui_starter2);
	HQRP_draw_image_scaled((HQRP_Vec2){ 117, 80 },
						   game->starter_pokes[1]->sprite,
						   HQRPGE_SPRITE_POKE_SIZE,
						   5);
	HQRPGE_draw_button(&HQRPGE_gui_starter3);
	HQRP_draw_image_scaled((HQRP_Vec2){ 212, 80 },
						   game->starter_pokes[2]->sprite,
						   HQRPGE_SPRITE_POKE_SIZE,
						   5);
}

void HQRPGE_draw_map(HQRPGE_Game * game) {
	HQRP_Vec2 cursor_pos = { 0, 0 };

	for (int x = (int)game->player.position.x - (HQRPGE_MAP_VIEW_WIDTH / 2);
		 x <= (int)game->player.position.x + (HQRPGE_MAP_VIEW_WIDTH / 2);
		 ++x) {
		for (int y =
				 (int)game->player.position.y - (HQRPGE_MAP_VIEW_HEIGHT / 2);
			 y <= (int)game->player.position.y + (HQRPGE_MAP_VIEW_HEIGHT / 2);
			 ++y) {
			if (x >= 0 && y >= 0 && x < game->map->size.x &&
				y < game->map->size.y) {
				if (game->map->tiles[(y * game->map->size.x) + x] ==
					HQRPGE_WALL_ID) {
					HQRP_draw_image_scaled(cursor_pos,
										   HQRPGE_sprite_wall,
										   HQRPGE_SPRITE_SIZE,
										   HQRPGE_GFX_SCALE);
				} else {
					HQRP_draw_image_scaled(cursor_pos,
										   HQRPGE_sprite_grass,
										   HQRPGE_SPRITE_SIZE,
										   HQRPGE_GFX_SCALE);
				}
			} else {
				HQRP_draw_image_scaled(cursor_pos,
									   HQRPGE_sprite_void,
									   HQRPGE_SPRITE_SIZE,
									   HQRPGE_GFX_SCALE);
			}
			cursor_pos.y += HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE;
		}
		cursor_pos.y = 0;
		cursor_pos.x += HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE;
	}
}

void HQRPGE_draw_entities(HQRPGE_Game * game) {
	for (size_t i = 0; i < HQRPGE_MAX_ENTITES; ++i) {
		if ((int)game->entities[i].position.x >=
				(int)game->player.position.x - (HQRPGE_MAP_VIEW_WIDTH / 2) &&
			(int)game->entities[i].position.x <=
				(int)game->player.position.x + (HQRPGE_MAP_VIEW_WIDTH / 2) &&
			(int)game->entities[i].position.y >=
				(int)game->player.position.y - (HQRPGE_MAP_VIEW_HEIGHT / 2) &&
			(int)game->entities[i].position.y <=
				(int)game->player.position.y + (HQRPGE_MAP_VIEW_HEIGHT / 2)) {
			int entity_offset_x = ((HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE) *
								   (HQRPGE_MAP_VIEW_WIDTH / 2)) -
								  (((int)game->player.position.x -
									(int)game->entities[i].position.x) *
								   HQRPGE_GFX_SCALE * HQRPGE_SPRITE_WIDTH);
			int entity_offset_y = ((HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE) *
								   (HQRPGE_MAP_VIEW_HEIGHT / 2)) -
								  (((int)game->player.position.y -
									(int)game->entities[i].position.y) *
								   HQRPGE_GFX_SCALE * HQRPGE_SPRITE_HEIGHT);
			HQRP_draw_image_scaled(
				(HQRP_Vec2){ entity_offset_x, entity_offset_y },
				HQRPGE_sprite_enemy,
				HQRPGE_SPRITE_SIZE,
				HQRPGE_GFX_SCALE);
		}
	}
}

void HQRPGE_draw_player(HQRPGE_Game * game) {
	HQRP_draw_image_scaled(
		(HQRP_Vec2){ (HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE) *
						 (HQRPGE_MAP_VIEW_WIDTH / 2),
					 (HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE) *
						 (HQRPGE_MAP_VIEW_HEIGHT / 2) },
		HQRPGE_sprite_player,
		HQRPGE_SPRITE_SIZE,
		HQRPGE_GFX_SCALE);
}

void HQRPGE_draw_minimap(HQRPGE_Game * game) {
	for (uint16_t x = 0; x < game->map->size.x; ++x) {
		for (uint16_t y = 0; y < game->map->size.y; ++y) {
			for (uint16_t xx = x * 3; xx < (x + 1) * 3; ++xx) {
				for (uint16_t yy = y * 3; yy < (y + 1) * 3; ++yy) {
					HQRP_draw_pixel(
						(HQRP_Vec2){
							xx + (HQRPGE_MAP_VIEW_WIDTH * HQRPGE_GFX_SCALE *
								  HQRPGE_SPRITE_WIDTH),
							yy },
						(game->map->tiles[(y * game->map->size.x) + x] ==
						 HQRPGE_WALL_ID)
							? HQRPGE_MINIMAP_WALL_COLOUR
							: HQRPGE_MINIMAP_FLOOR_COLOUR);
				}
			}
		}
	}
	for (uint16_t xx = game->player.position.x * 3;
		 xx < (game->player.position.x + 1) * 3;
		 ++xx) {
		for (uint16_t yy = game->player.position.y * 3;
			 yy < (game->player.position.y + 1) * 3;
			 ++yy) {
			HQRP_draw_pixel(
				(HQRP_Vec2){ xx + (HQRPGE_MAP_VIEW_WIDTH * HQRPGE_GFX_SCALE *
								   HQRPGE_SPRITE_WIDTH),
							 yy },
				HQRPGE_MINIMAP_PLAYER_COLOUR);
		}
	}
	for (size_t i = 0; i < HQRPGE_MAX_ENTITES; ++i) {
		for (uint16_t xx = game->entities[i].position.x * 3;
			 xx < (game->entities[i].position.x + 1) * 3;
			 ++xx) {
			for (uint16_t yy = game->entities[i].position.y * 3;
				 yy < (game->entities[i].position.y + 1) * 3;
				 ++yy) {
				HQRP_draw_pixel(
					(HQRP_Vec2){ xx + (HQRPGE_MAP_VIEW_WIDTH *
									   HQRPGE_GFX_SCALE * HQRPGE_SPRITE_WIDTH),
								 yy },
					HQRPGE_MINIMAP_ENEMY_COLOUR);
			}
		}
	}
}

void HQRPGE_draw_movement_keys(HQRPGE_Game * game) {
	HQRPGE_draw_image_button(&HQRPGE_gui_movement_arrows_background);
	HQRPGE_draw_image_button(&HQRPGE_gui_movement_arrow_up);
	HQRPGE_draw_image_button(&HQRPGE_gui_movement_arrow_down);
	HQRPGE_draw_image_button(&HQRPGE_gui_movement_arrow_left);
	HQRPGE_draw_image_button(&HQRPGE_gui_movement_arrow_right);
}

void HQRPGE_draw_battle(HQRPGE_Game * game) {
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	HQRPGE_draw_battle_gui(game);
}

void HQRPGE_draw_battle_gui(HQRPGE_Game * game) {
	HQRP_clear_screen(HQRP_COLOUR_WHITE);
	// HQRP
}

void HQRPGE_handle_input(HQRPGE_Game * game) {
	switch (game->game_state) {
		case HQRPGE_GAMESTATE_MENU:
			HQRPGE_handle_input_menu(game);
			break;
		case HQRPGE_GAMESTATE_GENERATE_SEED:
			HQRPGE_handle_input_generate_seed(game);
			break;
		case HQRPGE_GAMESTATE_STARTER_SELECTION:
			HQRPGE_handle_input_starter_selection(game);
			break;
		case HQRPGE_GAMESTATE_MAP:
			/* fall through */
		case HQRPGE_GAMESTATE_MAP_MOVEMENT_UPDATE:
			HQRPGE_handle_input_map(game);
			break;
		case HQRPGE_GAMESTATE_BATTLE:
			HQRPGE_handle_input_battle(game);
			break;
		default:
			break;
	}
}

void HQRPGE_handle_input_menu(HQRPGE_Game * game) {
	while (!HQRPGE_button_update(&HQRPGE_gui_menu_new_game, game) &&
		   !HQRPGE_button_update(&HQRPGE_gui_menu_seed, game)) {
	}
}

void HQRPGE_handle_input_starter_selection(HQRPGE_Game * game) {
	while (!HQRPGE_button_update(&HQRPGE_gui_starter1, game) &&
		   !HQRPGE_button_update(&HQRPGE_gui_starter2, game) &&
		   !HQRPGE_button_update(&HQRPGE_gui_starter3, game)) {
	}
}

void HQRPGE_handle_input_generate_seed(HQRPGE_Game * game) {
	HQRP_TouchPoint touch_point;

	while (!HQRPGE_button_update(&HQRPGE_gui_seed_dialog_button, game)) {
		touch_point = HQRP_get_touch_point();
		if (touch_point.is_touched) {
			HQRP_draw_pixel(touch_point.position, HQRP_COLOUR_RED);
			game->seed += touch_point.position.x + touch_point.position.y;
		}
	}
}

void HQRPGE_handle_input_map(HQRPGE_Game * game) {
	while (
		!HQRPGE_image_button_update(&HQRPGE_gui_movement_arrow_up, game) &&
		!HQRPGE_image_button_update(&HQRPGE_gui_movement_arrow_down, game) &&
		!HQRPGE_image_button_update(&HQRPGE_gui_movement_arrow_left, game) &&
		!HQRPGE_image_button_update(&HQRPGE_gui_movement_arrow_right, game) &&
		!HQRPGE_image_button_update(&HQRPGE_gui_exit, game)) {
	}
}

void HQRPGE_handle_input_battle(HQRPGE_Game * game) {
}

void HQRPGE_main_menu(HQRPGE_Game * game) {
	game->game_state = HQRPGE_GAMESTATE_MENU;
}

void HQRPGE_generate_seed(HQRPGE_Game * game) {
	game->game_state = HQRPGE_GAMESTATE_GENERATE_SEED;
}

void HQRPGE_create_player_with_first_poke(HQRPGE_Game * game) {
	game->player = (HQRPGE_Entity){ game->map->spawn_point,
									*game->starter_pokes[0],
									&(HQRPGE_sprite_player[0]) };
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	HQRP_draw_image_scaled((HQRP_Vec2){ 70, 40 },
						   game->starter_pokes[0]->sprite,
						   HQRPGE_SPRITE_POKE_SIZE,
						   12);
	HQRP_draw_text_scaled((HQRP_Vec2){ 15, 15 },
						  game->starter_pokes[0]->name,
						  HQRP_COLOUR_YELLOW,
						  7);
	HAL_Delay(1000);
	HQRP_clear_screen(HQRP_COLOUR_GRAY);
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	game->game_state = HQRPGE_GAMESTATE_MAP;
}

void HQRPGE_create_player_with_second_poke(HQRPGE_Game * game) {
	game->player = (HQRPGE_Entity){ game->map->spawn_point,
									*game->starter_pokes[1],
									&(HQRPGE_sprite_player[0]) };
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	HQRP_draw_image_scaled((HQRP_Vec2){ 70, 40 },
						   game->starter_pokes[1]->sprite,
						   HQRPGE_SPRITE_POKE_SIZE,
						   12);
	HQRP_draw_text_scaled((HQRP_Vec2){ 15, 15 },
						  game->starter_pokes[1]->name,
						  HQRP_COLOUR_YELLOW,
						  7);
	HAL_Delay(1000);
	HQRP_clear_screen(HQRP_COLOUR_GRAY);
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	game->game_state = HQRPGE_GAMESTATE_MAP;
}

void HQRPGE_create_player_with_third_poke(HQRPGE_Game * game) {
	game->player = (HQRPGE_Entity){ game->map->spawn_point,
									*game->starter_pokes[2],
									&(HQRPGE_sprite_player[0]) };
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	HQRP_draw_image_scaled((HQRP_Vec2){ 70, 40 },
						   game->starter_pokes[2]->sprite,
						   HQRPGE_SPRITE_POKE_SIZE,
						   12);
	HQRP_draw_text_scaled((HQRP_Vec2){ 15, 15 },
						  game->starter_pokes[2]->name,
						  HQRP_COLOUR_YELLOW,
						  7);
	HAL_Delay(1000);
	HQRP_clear_screen(HQRP_COLOUR_GRAY);
	HQRP_clear_screen(HQRP_COLOUR_BLACK);
	game->game_state = HQRPGE_GAMESTATE_MAP;
}

void HQRPGE_new_game(HQRPGE_Game * game) {
	HQRPGE_build_map(game->map, HQRPGE_MAP_MAX_ROOMS, game->seed);
	HQRPGE_spawn_enemies(game);
	HQRPGE_draw_dialog_box(&HQRPGE_gui_help_dialog);
	while (!HQRPGE_is_button_clicked(&HQRPGE_gui_help_dialog_button)) {
	}
	game->game_state = HQRPGE_GAMESTATE_STARTER_SELECTION;
}

void HQRPGE_spawn_enemies(HQRPGE_Game * game) {
	size_t i = 0;
while_end:
	while (i < HQRPGE_MAX_ENTITES) {
		for (size_t x = rand() % game->map->size.x; x < game->map->size.x;
			 ++x) {
			for (size_t y = rand() % game->map->size.y; y < game->map->size.y;
				 ++y) {
				if (game->map->tiles[(y * game->map->size.x) + x]) {
					if (rand() % 100 < HQRPGE_ENEMY_SPAWN_RATE) {
						game->entities[i] = HQRPGE_create_enemy(
							(HQRP_Vec2){ x, y },
							game->available_pokes[rand() %
												  HQRPGE_AVAILABLE_POKES],
							rand() % 3);
						++i;
						goto while_end;
					}
				}
			}
		}
	}
}

void HQRPGE_move_player_up(HQRPGE_Game * game) {
	game->game_state = HQRPGE_GAMESTATE_MAP_MOVEMENT_UPDATE;
	if ((int)game->player.position.y - 1 >= 0) {
		if (game->map
				->tiles[((game->player.position.y - 1) * game->map->size.x) +
						game->player.position.x]) {
			game->player.position.y -= 1;
		}
		for (size_t i = 0; i < HQRPGE_MAX_ENTITES; ++i) {
			if (game->player.position.x == game->entities[i].position.x &&
				game->player.position.y == game->entities[i].position.y) {
				HQRPGE_battle(game);
			}
		}
	}
}

void HQRPGE_move_player_right(HQRPGE_Game * game) {
	game->game_state = HQRPGE_GAMESTATE_MAP_MOVEMENT_UPDATE;
	if ((int)game->player.position.x + 1 < game->map->size.x) {
		if (game->map->tiles[(game->player.position.y * game->map->size.x) +
							 game->player.position.x + 1]) {
			game->player.position.x += 1;
		}
		for (size_t i = 0; i < HQRPGE_MAX_ENTITES; ++i) {
			if (game->player.position.x == game->entities[i].position.x &&
				game->player.position.y == game->entities[i].position.y) {
				HQRPGE_battle(game);
			}
		}
	}
}

void HQRPGE_move_player_down(HQRPGE_Game * game) {
	game->game_state = HQRPGE_GAMESTATE_MAP_MOVEMENT_UPDATE;
	if ((int)game->player.position.y + 1 < game->map->size.y) {
		if (game->map
				->tiles[((game->player.position.y + 1) * game->map->size.x) +
						game->player.position.x]) {
			game->player.position.y += 1;
		}
		for (size_t i = 0; i < HQRPGE_MAX_ENTITES; ++i) {
			if (game->player.position.x == game->entities[i].position.x &&
				game->player.position.y == game->entities[i].position.y) {
				HQRPGE_battle(game);
			}
		}
	}
}

void HQRPGE_move_player_left(HQRPGE_Game * game) {
	game->game_state = HQRPGE_GAMESTATE_MAP_MOVEMENT_UPDATE;
	if ((int)game->player.position.x - 1 >= 0) {
		if (game->map->tiles[(game->player.position.y * game->map->size.x) +
							 game->player.position.x - 1]) {
			game->player.position.x -= 1;
		}
		for (size_t i = 0; i < HQRPGE_MAX_ENTITES; ++i) {
			if (game->player.position.x == game->entities[i].position.x &&
				game->player.position.y == game->entities[i].position.y) {
				HQRPGE_battle(game);
			}
		}
	}
}

void HQRPGE_battle(HQRPGE_Game * game) {
	for (size_t x = 0; x < HQRP_SCREEN_WIDTH - 2; ++x) {
		HQRP_draw_rectangle((HQRP_Vec2){ x, 0 },
							(HQRP_Vec2){ x + 1, HQRP_SCREEN_HEIGHT - 1 },
							(x % 2) ? HQRP_COLOUR_RED : HQRP_COLOUR_BLACK);
	}
	HQRP_draw_text_scaled(
		(HQRP_Vec2){ 5, 100 }, "!BATTLE!", HQRP_COLOUR_YELLOW, 10);
	HAL_Delay(1000);
	for (size_t x = 0; x < HQRP_SCREEN_WIDTH - 2; ++x) {
		HQRP_draw_rectangle((HQRP_Vec2){ x, 0 },
							(HQRP_Vec2){ x + 1, HQRP_SCREEN_HEIGHT - 1 },
							(x % 2) ? HQRP_COLOUR_RED : HQRP_COLOUR_BLACK);
	}
	HQRP_draw_image_scaled((HQRP_Vec2){ 0, 50 },
						   game->player.poke.sprite,
						   HQRPGE_SPRITE_POKE_SIZE,
						   8);
	HQRP_draw_text_scaled((HQRP_Vec2){ 130, 80 }, "VS", HQRP_COLOUR_YELLOW, 10);
	for (size_t i = 0; i < HQRPGE_MAX_ENTITES; ++i) {
		if (game->player.position.x == game->entities[i].position.x &&
			game->player.position.y == game->entities[i].position.y) {
			HQRP_draw_image_scaled((HQRP_Vec2){ 200, 50 },
								   game->entities[i].poke.sprite,
								   HQRPGE_SPRITE_POKE_SIZE,
								   8);
		}
	}
	HAL_Delay(1000);
	game->game_state = HQRPGE_GAMESTATE_MAP;
}

static HQRPGE_Button HQRPGE_gui_menu_seed = { (HQRP_Vec2){ 150, 160 },
											  (HQRP_Vec2){ 150, 50 },
											  "CHANGE SEED",
											  11,
											  17,
											  3,
											  HQRP_COLOUR_YELLOW,
											  HQRP_COLOUR_PEAR,
											  HQRP_COLOUR_BLUE,
											  5,
											  &HQRPGE_generate_seed };
static HQRPGE_Button HQRPGE_gui_menu_new_game = { (HQRP_Vec2){ 150, 100 },
												  (HQRP_Vec2){ 150, 50 },
												  "NEW GAME",
												  8,
												  17,
												  3,
												  HQRP_COLOUR_YELLOW,
												  HQRP_COLOUR_PEAR,
												  HQRP_COLOUR_BLUE,
												  5,
												  &HQRPGE_new_game };
static HQRPGE_Button HQRPGE_gui_seed_dialog_button = { (HQRP_Vec2){ 40, 150 },
													   (HQRP_Vec2){ 100, 50 },
													   "READY",
													   5,
													   17,
													   3,
													   HQRP_COLOUR_YELLOW,
													   HQRP_COLOUR_PEAR,
													   HQRP_COLOUR_BLUE,
													   5,
													   &HQRPGE_main_menu };
static HQRPGE_DialogBox HQRPGE_gui_seed_dialog = {
	(HQRP_Vec2){ 20, 20 },
	(HQRP_Vec2){ 280, 200 },
	"CLICK SOME RANDOM\nPOINTS TO GENERATE\nA NEW SEED",
	18,
	25,
	3,
	HQRP_COLOUR_YELLOW,
	HQRP_COLOUR_PEAR,
	HQRP_COLOUR_BROWN,
	5,
	1,
	{ &HQRPGE_gui_seed_dialog_button }
};
static HQRPGE_Button HQRPGE_gui_starter1 = {
	(HQRP_Vec2){ 20, 170 },
	(HQRP_Vec2){ 90, 45 },
	"POKE1",
	5,
	17,
	2,
	HQRP_COLOUR_YELLOW,
	HQRP_COLOUR_GREEN,
	HQRP_COLOUR_NAVY,
	5,
	&HQRPGE_create_player_with_first_poke
};
static HQRPGE_Button HQRPGE_gui_starter2 = {
	(HQRP_Vec2){ 111, 170 },
	(HQRP_Vec2){ 90, 45 },
	"POKE2",
	5,
	17,
	2,
	HQRP_COLOUR_YELLOW,
	HQRP_COLOUR_GREEN,
	HQRP_COLOUR_NAVY,
	5,
	&HQRPGE_create_player_with_second_poke
};
static HQRPGE_Button HQRPGE_gui_starter3 = {
	(HQRP_Vec2){ 202, 170 },
	(HQRP_Vec2){ 90, 45 },
	"POKE3",
	5,
	17,
	2,
	HQRP_COLOUR_YELLOW,
	HQRP_COLOUR_GREEN,
	HQRP_COLOUR_NAVY,
	5,
	&HQRPGE_create_player_with_third_poke
};
static HQRPGE_Button HQRPGE_gui_help_dialog_button = { (HQRP_Vec2){ 20, 170 },
													   (HQRP_Vec2){ 100, 50 },
													   "READY",
													   5,
													   17,
													   3,
													   HQRP_COLOUR_YELLOW,
													   HQRP_COLOUR_PEAR,
													   HQRP_COLOUR_ARCTIC,
													   5,
													   NULL };
static HQRPGE_DialogBox HQRPGE_gui_help_dialog = {
	(HQRP_Vec2){ 0, 0 },
	(HQRP_Vec2){ HQRP_SCREEN_WIDTH - 1, HQRP_SCREEN_HEIGHT - 1 },
	"You embark on a new quest\nto find glory and power!\n\nUse movement keys "
	"to move\n\nHourglass icon means\nyou have to wait ",
	25,
	25,
	3,
	HQRP_COLOUR_YELLOW,
	HQRP_COLOUR_PEAR,
	HQRP_COLOUR_BROWN,
	5,
	1,
	{ &HQRPGE_gui_help_dialog_button }
};
static HQRPGE_ImageButton HQRPGE_gui_movement_arrows_background = {
	(HQRP_Vec2){ HQRPGE_MAP_VIEW_WIDTH * HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE,
				 HQRPGE_MAP_SIZE * 3 },
	HQRPGE_SPRITE_SIZE,
	HQRPGE_sprite_arrows_background,
	HQRPGE_GFX_SCALE * 3,
	NULL,
};
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_up = {
	(HQRP_Vec2){
		(HQRPGE_MAP_VIEW_WIDTH * HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE) +
			(HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE),
		HQRPGE_MAP_SIZE * 3 },
	HQRPGE_SPRITE_SIZE,
	HQRPGE_sprite_arrow_up,
	HQRPGE_GFX_SCALE,
	&HQRPGE_move_player_up,
};
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_down = {
	(HQRP_Vec2){
		(HQRPGE_MAP_VIEW_WIDTH * HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE) +
			(HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE),
		(HQRPGE_MAP_SIZE * 3) + (HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE * 2) },
	HQRPGE_SPRITE_SIZE,
	HQRPGE_sprite_arrow_down,
	HQRPGE_GFX_SCALE,
	&HQRPGE_move_player_down,
};
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_left = {
	(HQRP_Vec2){
		(HQRPGE_MAP_VIEW_WIDTH * HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE),
		(HQRPGE_MAP_SIZE * 3) + (HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE) },
	HQRPGE_SPRITE_SIZE,
	HQRPGE_sprite_arrow_left,
	HQRPGE_GFX_SCALE,
	&HQRPGE_move_player_left,
};
static HQRPGE_ImageButton HQRPGE_gui_movement_arrow_right = {
	(HQRP_Vec2){
		(HQRPGE_MAP_VIEW_WIDTH * HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE) +
			(HQRPGE_SPRITE_WIDTH * HQRPGE_GFX_SCALE * 2),
		(HQRPGE_MAP_SIZE * 3) + (HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE) },
	HQRPGE_SPRITE_SIZE,
	HQRPGE_sprite_arrow_right,
	HQRPGE_GFX_SCALE,
	&HQRPGE_move_player_right,
};
static HQRPGE_ImageButton HQRPGE_gui_exit = {
	(HQRP_Vec2){
		0, HQRP_SCREEN_HEIGHT - 1 - (HQRPGE_SPRITE_HEIGHT * HQRPGE_GFX_SCALE) },
	HQRPGE_SPRITE_SIZE,
	HQRPGE_sprite_exit,
	HQRPGE_GFX_SCALE,
	&HQRPGE_main_menu,
};
