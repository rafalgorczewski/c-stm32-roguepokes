#ifndef HQRPGE_ENGINE_H
#define HQRPGE_ENGINE_H

#include "hqrpge_map.h"
#include "hqrpge_entity.h"
#include "hqrpge_gui.h"

typedef enum {
	HQRPGE_GAMESTATE_MENU,
	HQRPGE_GAMESTATE_GENERATE_SEED,
	HQRPGE_GAMESTATE_STARTER_SELECTION,
	HQRPGE_GAMESTATE_MAP,
	HQRPGE_GAMESTATE_MAP_MOVEMENT_UPDATE,
	HQRPGE_GAMESTATE_INVENTORY,
	HQRPGE_GAMESTATE_BATTLE
} HQRPGE_GameState;

typedef struct {
	HQRPGE_GameState game_state;
	HQRPGE_Map * map;
	HQRPGE_Poke * starter_pokes[HQRPGE_STARTER_POKES_COUNT];
	HQRPGE_Poke * available_pokes[HQRPGE_AVAILABLE_POKES];
	HQRPGE_Entity player;
	HQRPGE_Entity entities[HQRPGE_MAX_ENTITES];
	uint16_t seed;
} HQRPGE_Game;

void HQRPGE_draw_game(HQRPGE_Game * game);
void HQRPGE_draw_hourglass(HQRPGE_Game * game);
void HQRPGE_draw_empty_on_hourglass(HQRPGE_Game * game);
void HQRPGE_draw_exit(HQRPGE_Game * game);
void HQRPGE_draw_menu(HQRPGE_Game * game);
void HQRPGE_draw_generate_seed(HQRPGE_Game * game);
void HQRPGE_draw_starter_selection(HQRPGE_Game * game);
void HQRPGE_draw_map(HQRPGE_Game * game);
void HQRPGE_draw_entities(HQRPGE_Game * game);
void HQRPGE_draw_player(HQRPGE_Game * game);
void HQRPGE_draw_minimap(HQRPGE_Game * game);
void HQRPGE_draw_movement_keys(HQRPGE_Game * game);
void HQRPGE_draw_battle(HQRPGE_Game * game);
void HQRPGE_draw_battle_gui(HQRPGE_Game * game);

void HQRPGE_handle_input(HQRPGE_Game * game);
void HQRPGE_handle_input_menu(HQRPGE_Game * game);
void HQRPGE_handle_input_starter_selection(HQRPGE_Game * game);
void HQRPGE_handle_input_generate_seed(HQRPGE_Game * game);
void HQRPGE_handle_input_map(HQRPGE_Game * game);
void HQRPGE_handle_input_battle(HQRPGE_Game * game);

void HQRPGE_main_menu(HQRPGE_Game * game);
void HQRPGE_generate_seed(HQRPGE_Game * game);
void HQRPGE_create_player_with_first_poke(HQRPGE_Game * game);
void HQRPGE_create_player_with_second_poke(HQRPGE_Game * game);
void HQRPGE_create_player_with_third_poke(HQRPGE_Game * game);
void HQRPGE_new_game(HQRPGE_Game * game);
void HQRPGE_spawn_enemies(HQRPGE_Game * game);
void HQRPGE_move_player_up(HQRPGE_Game * game);
void HQRPGE_move_player_right(HQRPGE_Game * game);
void HQRPGE_move_player_down(HQRPGE_Game * game);
void HQRPGE_move_player_left(HQRPGE_Game * game);
void HQRPGE_battle(HQRPGE_Game * game);

#endif
