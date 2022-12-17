/** \file
 * \brief Файл с самой игрой
 */

#ifndef ENGINE_GAME_ENGINE_H_
#define ENGINE_GAME_ENGINE_H_

#include "../classes/consts.h"
#include "../classes/basic.h"
#include "../classes/enemies.h"
#include "../classes/player_things.h"
#include <deque>
#include <ctime>
#include <limits.h>

namespace GC = game_consts;
namespace GO = game_objects;

namespace game_engine {
	/// Класс описывающий игру и позволяющий с ней взаимодействовать
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
		std::MyVector<std::MyVector<std::MyVector<GO::Unit*>>> units_field;
		std::MyVector<std::MyVector<GO::Tower*>> towers_field;
		std::MyVector<std::MyVector<GO::aura>> aura_field; ///< Поле с суммарными аурами героев
		int counter = 0;
		int balance = 0;
		Game(const std::string& _player_name) : player_name(_player_name) {std::srand(std::clock());}
		void load_landscape(const std::string& filename);
		void save_landscape(const std::string& filename) const;
		void move_unit(int x_from, int y_from, int x_to, int y_to, GO::Unit* unit);
		void add_enemy(int type, int time); ///< Добавить обычного врага в очередь логова
		void add_enemy(int type, const GO::aura &a, int time); ///< Добавить героя в очередь логова
		void add_random_enemy(); ///< Добавить случайного врага в очередь логова
		GO::Unit* add_tower(int x, int y); ///< Попробовать добавить башню на поле
		GO::Unit* add_wall(int x, int y); ///< Поробовать добавить стену на поле
		GO::Unit* add_to_queue(int type); ///< Выпустить нового обычного врага из логова
		GO::Unit* add_to_queue(int type, const GO::aura &a); ///< Выпустить нового героя из логова
		void tower_level_up(int x, int y);
		void castle_level_up();
		void repair_wall(int x, int y);
		void get_damage(int x, int y, int damage); ///< Нанести урон Unit в клетке с координатами x, y
		GO::Landscape& get_landscape() {return (field);}
		GO::Castle& get_castle() {return (*castle);}
		void show_field() const; ///< Консольная реализация вывода игрового поля
		int is_end() const; ///< Проверка на то, что игра закончена
		void tic(); ///< Один шаг игры
		~Game();
	};
}

#endif /* ENGINE_GAME_ENGINE_H_ */
