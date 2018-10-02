#ifndef HQRPGE_ENTITY_H
#define HQRPGE_ENTITY_H

#include <stdint.h>

#include <hqrp_math.h>
#include <hqrp_graphics.h>

#include "hqrpge_constants.h"

typedef struct {
	char name[HQRPGE_WEAPON_NAME_LENGTH];
	char type;  // P = psychic, W - water, F - fire, N - nature, A - air, G -
				// ground, E - electric
	uint16_t damage;
} HQRPGE_Weapon;

typedef struct {
	char type;
	uint16_t sturdiness;
} HQRPGE_Armour;

typedef struct {
	uint16_t health;
	uint16_t armour;
} HQRPGE_Statpack;

typedef struct {
	char name[HQRPGE_POKE_NAME_LENGTH];
	HQRPGE_Weapon weapon;
	HQRPGE_Armour armour;
	HQRPGE_Statpack statpack;
	HQRP_Colour * sprite;
} HQRPGE_Poke;

typedef struct {
	HQRP_Vec2 position;
	HQRPGE_Poke poke;
	HQRP_Colour * sprite;
} HQRPGE_Entity;

HQRPGE_Entity HQRPGE_create_enemy(HQRP_Vec2 position,
								  HQRPGE_Poke * poke,
								  uint8_t level);

#endif
