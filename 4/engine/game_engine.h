#ifndef ENGINE_GAME_ENGINE_H_
#define ENGINE_GAME_ENGINE_H_

#include "../classes/consts.h"
#include "../classes/basic.h"
#include "../classes/enemies.h"
#include "../classes/player_things.h"
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <limits.h>

namespace GC = game_consts;
namespace GO = game_objects;

namespace game_engine {

	class Game {
	private:
		GO::Landscape field;
		GO::Castle *castle = nullptr;
		GO::Lair *lair = nullptr;
		std::deque<GO::Unit*> units_queue;
		std::string player_name;
		int max_counter = INT_MAX;
		void set_cords();
		int enemy_cnt = 0;
	public:
		std::vector<std::vector<std::vector<GO::Unit*>>> units_field;
		std::vector<std::vector<GO::Tower*>> towers_field;
		std::vector<std::vector<GO::aura>> aura_field;
		int counter = 0;
		int balance = 0;
		Game(const std::string& _player_name) : player_name(_player_name) {std::srand(std::clock());}
		void change_landscape(int land_x_size, int land_y_size,
				const std::vector<std::string>* _field = nullptr);
		void load_landscape(const std::string& filename);
		void save_landscape(const std::string& filename);
		void move_unit(int x_from, int y_from, int x_to, int y_to, GO::Unit* unit);
		void add_enemy(int type, int time);
		void add_enemy(int type, const GO::aura &a, int time);
		void add_random_enemy();
		void add_tower(int x, int y);
		void add_wall(int x, int y);
		void add_to_queue(int type);
		void add_to_queue(int type, const GO::aura &a);
		void tower_level_up(int x, int y);
		void castle_level_up();
		void repair_wall(int x, int y);
		void get_damage(int x, int y, int damage);
		GO::Landscape& get_landscape() {return (field);}
		GO::Castle& get_castle() {return (*castle);}
		void show_field();
		int is_end();
		void tic();
	};
}





#endif /* ENGINE_GAME_ENGINE_H_ */
