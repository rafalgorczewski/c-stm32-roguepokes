#include "hqrpge_pokes.h"
#include "hqrpge_entity.h"
#include "hqrpge_sprites.h"

HQRPGE_Poke HQRPGE_poke_psyduck = { "Psyduck",
									{ "Psychic Bolt", 'P', 15 },
									{ 'P', 5 },
									{ 120, 1 },
									&(HQRPGE_sprite_psyduck[0]) };
HQRPGE_Poke HQRPGE_poke_charmander = { "Charmander",
									   { "Fire Breath", 'F', 20 },
									   { 'F', 5 },
									   { 110, 2 },
									   &(HQRPGE_sprite_charmander[0]) };
HQRPGE_Poke HQRPGE_poke_squirtle = { "Squirtle",
									 { "Bubble", 'W', 15 },
									 { 'W', 5 },
									 { 100, 3 },
									 &(HQRPGE_sprite_squirtle[0]) };
