/** \file
 * \brief Файл со всеми игровыми константами
 */

#ifndef CLASSES_CONSTS_H_
#define CLASSES_CONSTS_H_

#include "additional_classes.h"

namespace GO = game_objects;

/// Пространство имен игровых констант
namespace game_consts {
	constexpr int tank_max_health = 30;
	constexpr int light_max_health = 15;
	constexpr int aviation_max_health = 20;
	constexpr int wall_max_health = 10;

	constexpr int tank_regeneration_speed = 100;
	constexpr int light_regeneration_speed = 100;
	constexpr int aviation_regeneration_speed = 100;

	constexpr int tank_speed = 180;
	constexpr int light_speed = 120;
	constexpr int aviation_speed = 60;

	constexpr int tank_recoil = 180;
	constexpr int light_recoil = 120;
	constexpr int aviation_recoil = 180;

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
	constexpr char tank_symb = 't';
	constexpr char light_symb = 'l';
	constexpr char aviation_symb = 'a';
	constexpr char hero_tank_symb = 'T';
	constexpr char hero_light_symb = 'L';
	constexpr char hero_aviation_symb = 'A';
	constexpr char tower_symb = 'O';

	constexpr int light_type = 1;
	constexpr int tank_type = 2;
	constexpr int aviation_type = 3;
	constexpr int just_way_type = 4;

	constexpr int tower_max_level = 5;
	constexpr int castle_max_level = 5;

	constexpr GO::tower_chars tower_chars_table[tower_max_level] = {{180, 20, 2, 3},
																{150, 25, 4, 5},
																{120, 50, 7, 7},
																{90, 80, 10, 9},
																{60, 130, 12, 20}};

	constexpr GO::castle_chars castle_chars_table[castle_max_level] = {{10, 0, 50, 120},
																		{15, 150, 100, 100},
																		{25, 250, 150, 80},
																		{50, 500, 500, 60},
																		{100, 1000, 1000, 40}};
	constexpr int castle_profit_speed = 60;

	constexpr int wall_cost = 30;
	constexpr int wall_repair_cost = 25;
}





#endif /* CLASSES_CONSTS_H_ */
