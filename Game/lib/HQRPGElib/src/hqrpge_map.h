#ifndef HQRPGE_MAP_H
#define HQRPGE_MAP_H

#include <hqrp_graphics.h>
#include <hqrp_math.h>

#include "hqrpge_constants.h"

typedef struct {
	HQRP_Vec2 size;
	uint8_t tiles[HQRPGE_MAP_SIZE * HQRPGE_MAP_SIZE];
	HQRP_Vec2 spawn_point;
} HQRPGE_Map;

void HQRPGE_build_map(HQRPGE_Map * map, uint8_t max_rooms, uint16_t seed);

#endif