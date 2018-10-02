#ifndef HQRP_TOUCH_H
#define HQRP_TOUCH_H

#include "hqrp_math.h"
#include <stdbool.h>

typedef struct {
	HQRP_Vec2 position;
	uint16_t pressure;
	bool is_touched;
} HQRP_TouchPoint;

HQRP_TouchPoint HQRP_get_touch_point(void);

#endif
