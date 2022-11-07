#ifndef CLASSES_CONSTS_H_
#define CLASSES_CONSTS_H_

#include "additional_classes.h"

namespace GO = game_objects;

namespace game_consts {

	constexpr int tank_max_health = 30;
	constexpr int light_max_health = 15;
	constexpr int aviation_max_health = 20;
	constexpr int wall_max_health = 100;

	constexpr int tank_regeneration_speed = 1;
	constexpr int light_regeneration_speed = 1;
	constexpr int aviation_regeneration_speed = 1;

	constexpr int tank_speed = 3;
	constexpr int light_speed = 2;
	constexpr int aviation_speed = 1;

	constexpr int tank_recoil = 3;
	constexpr int light_recoil = 2;
	constexpr int aviation_recoil = 3;

	constexpr int tank_radius = 2;
	constexpr int light_radius = 2;
	constexpr int aviation_radius = 3;

	constexpr int tank_damage = 3;
	constexpr int light_damage = 2;
	constexpr int aviation_damage = 1;

	constexpr char def_symb = 'P';
	constexpr char plain_symb = 'P';
	constexpr char mountain_symb = 'M';
	constexpr char river_symb = 'R';
	constexpr char wall_symb = 'W';
	constexpr char castle_symb = 'C';
	constexpr char lair_symb = 'L';
	constexpr char enemy_symb = 'E';
	constexpr char tower_symb = 'T';

	constexpr int light_type = 1;
	constexpr int tank_type = 2;
	constexpr int aviation_type = 3;
	constexpr int just_way_type = 4;

	constexpr int tower_max_level = 5;
	constexpr int castle_max_level = 5;

	constexpr GO::tower_chars tower_chars_table[tower_max_level] = {{3, 10, 2, 3},
																{3, 25, 4, 5},
																{2, 50, 7, 7},
																{2, 80, 10, 9},
																{1, 130, 12, 20}};

	constexpr GO::castle_chars castle_chars_table[castle_max_level] = {{10, 0, 50, 1},
																		{15, 150, 100, 3},
																		{25, 250, 150, 5},
																		{50, 500, 500, 10},
																		{100, 1000, 1000, 15}};

	constexpr int wall_cost = 30;
}





#endif /* CLASSES_CONSTS_H_ */
