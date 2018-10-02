#include "hqrpge_map.h"
#include "hqrpge_constants.h"

#include <hqrp_math.h>
#include <hqrp_graphics.h>
#include <hqrp_math.h>

#include <stdlib.h>

#define HQRPGE_ROOM_SIZE_X rand() % 10 + 5;
#define HQRPGE_ROOM_SIZE_Y rand() % 10 + 5;

#define HQRPGE_MAX_TRIES 50

void HQRPGE_build_map(HQRPGE_Map * map, uint8_t max_rooms, uint16_t seed) {
	for (size_t x = 0; x < map->size.x; ++x) {
		for (size_t y = 0; y < map->size.y; ++y) {
			map->tiles[(y * map->size.x) + x] = HQRPGE_WALL_ID;
		}
	}
	srand(seed);
	uint16_t prev_room_x = 0;
	uint16_t prev_room_y = 0;
	uint16_t next_room_x = 0;
	uint16_t next_room_y = 0;
	uint8_t is_spawn_set = 0;
	for (size_t rooms_count = 0; rooms_count < max_rooms; ++rooms_count) {
		int tries = 0;
		while (rooms_count < max_rooms && tries++ <= HQRPGE_MAX_TRIES) {
			uint16_t beg_x = rand() % map->size.x;
			uint16_t beg_y = rand() % map->size.y;
			if (map->tiles[(beg_x * map->size.x) + beg_y] == HQRPGE_WALL_ID) {
				uint8_t room_size_x = HQRPGE_ROOM_SIZE_X;
				uint8_t room_size_y = HQRPGE_ROOM_SIZE_Y;
				int appropriate_size = 1;
				for (int x = 0; x < room_size_x; ++x) {
					for (int y = 0; y < room_size_y; ++y) {
						if (beg_y + y >= map->size.y ||
							beg_x + x >= map->size.x ||
							map->tiles[((beg_x + x) * map->size.x) + beg_y +
									   y] != HQRPGE_WALL_ID) {
							appropriate_size = 0;
							goto nested_for_end;
						}
					}
				}
			nested_for_end:;
				if (appropriate_size) {
					for (int x_offset = 0; x_offset < room_size_x; ++x_offset) {
						for (int y_offset = 0; y_offset < room_size_y;
							 ++y_offset) {
							map->tiles[((beg_x + x_offset) * map->size.x) +
									   beg_y + y_offset] = HQRPGE_ROOM_ID;
						}
					}
					next_room_x = beg_x + (room_size_x / 2);
					next_room_y = beg_y + (room_size_y / 2);
					if (is_spawn_set) {
						int corridor_len_x = prev_room_x - next_room_x;
						int corridor_len_y = prev_room_y - next_room_y;
						if (corridor_len_x < 0) {
							for (size_t i = 0; i < abs(corridor_len_x) &&
											   prev_room_x + i < map->size.x;
								 ++i) {
								map->tiles[((prev_room_x + i) * map->size.x) +
										   prev_room_y] = HQRPGE_FLOOR_ID;
							}
						} else if (corridor_len_x > 0) {
							for (size_t i = 0;
								 i < corridor_len_x && prev_room_x - i >= 0;
								 ++i) {
								map->tiles[((prev_room_x - i) * map->size.x) +
										   prev_room_y] = HQRPGE_FLOOR_ID;
							}
						}
						if (corridor_len_y < 0) {
							for (size_t i = 0; i < abs(corridor_len_y) &&
											   prev_room_y + i < map->size.y;
								 ++i) {
								map->tiles[((next_room_x)*map->size.x) +
										   prev_room_y + i] = HQRPGE_FLOOR_ID;
							}
						} else if (corridor_len_y > 0) {
							for (size_t i = 0;
								 i < corridor_len_y && prev_room_y - i >= 0;
								 ++i) {
								map->tiles[((next_room_x)*map->size.x) +
										   prev_room_y - i] = HQRPGE_FLOOR_ID;
							}
						}
					}
					if (!is_spawn_set) {
						for (int x = 0; x < map->size.x; ++x) {
							for (int y = 0; y < map->size.y; ++y) {
								if (map->tiles[(y * map->size.x) + x]) {
									map->spawn_point.x = x;
									map->spawn_point.y = y;
									is_spawn_set = 1;
									goto spawn_fors_end;
								}
							}
						}
						map->spawn_point.x = beg_x;
						map->spawn_point.y = beg_y;
						is_spawn_set = 1;
					}
				spawn_fors_end:
					prev_room_x = beg_x + (room_size_x / 2);
					prev_room_y = beg_y + (room_size_y / 2);
					goto while_end;
				}
			}
		}
	while_end:;
	}
}
