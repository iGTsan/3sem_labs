#ifndef CLASSES_CONSTS_H_
#define CLASSES_CONSTS_H_

namespace game_consts {

//	constexpr int aura_health = 1;
//	constexpr int aura_speed = 2;
//	constexpr int aura_regeneration = 4;
//	constexpr int aura_health_speed = 3;
//	constexpr int aura_health_regeneration = 5;
//	constexpr int aura_speed_regeneration = 6;
//	constexpr int aura_health_speed_regeneration = 7;

	constexpr int tank_max_health = 100;
	constexpr int light_max_health = 100;
	constexpr int aviation_max_health = 100;
	constexpr int wall_max_health = 100;

	constexpr int tank_regeneration_speed = 1;
	constexpr int light_regeneration_speed = 1;
	constexpr int aviation_regeneration_speed = 1;

	constexpr int tank_speed = 1;
	constexpr int light_speed = 2;
	constexpr int aviation_speed = 3;

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



//	constexpr tower_chars tower_chars_table[tower_max_level] = {{1, 1, 1, 1},
//																{1, 1, 1, 1},
//																{1, 1, 1, 1},
//																{1, 1, 1, 1},
//																{1, 1, 1, 1},};




}





#endif /* CLASSES_CONSTS_H_ */
