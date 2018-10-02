#include "hqrpge_entity.h"
#include "hqrpge_sprites.h"

HQRPGE_Entity HQRPGE_create_enemy(HQRP_Vec2 position,
								  HQRPGE_Poke * poke,
								  uint8_t level) {
	HQRPGE_Entity enemy = { position, *poke, &(HQRPGE_sprite_enemy[0]) };
	switch (level) {
		default:
			/* fall through */
		case 0:
			break;
		case 1:
			enemy.poke.weapon.damage += 10;
			enemy.poke.armour.sturdiness += 5;
			enemy.poke.statpack.health += 25;
			enemy.poke.statpack.armour += 5;
			break;
		case 2:
			enemy.poke.weapon.damage += 25;
			enemy.poke.armour.sturdiness += 10;
			enemy.poke.statpack.health += 75;
			enemy.poke.statpack.armour += 10;
			break;
	}
	return enemy;
}
