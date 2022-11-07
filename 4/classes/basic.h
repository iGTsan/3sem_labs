/*
 * basic.h
 *
 *  Created on: 5 нояб. 2022 г.
 *      Author: ya
 */

#ifndef CLASSES_BASIC_H_
#define CLASSES_BASIC_H_

#include "consts.h"
#include "additional_classes.h"
#include <iostream>
#include <vector>
#include <deque>
#include <memory>

namespace GC = game_consts;

namespace game_objects {
	class Game;
	class Castle;
	class Lair;

	class Cell {
	protected:
		int x;
		int y;
		char symb;
	public:
		Cell(int _x, int _y, char c=GC::def_symb) :
			x(_x), y(_y), symb(c) {};
		int get_x_cord() const {return (x);};
		int get_y_cord() const {return (y);};
		void set_cords(int _x, int _y) {x = _x, y = _y;};
		char get_symb() const {return (symb);};
		void set_symb(char c) {symb = c;};
		virtual ~Cell() {};
	};

	class Unit : public Cell {
	public:
		Unit(int x, int y, char symb) :
			Cell(x, y, symb) {};
		virtual void Action(Game&) = 0;
		virtual bool is_alive() const = 0;
		virtual void get_damage(int damage) = 0;
	};
	/**
	 *	\brief Класс ландшафт
	 *
	 *	Описывает игровое поле(расположение врагов, башен, замка и т. д.)
	 */
	class Landscape {
	private:
		std::vector<std::string> field;
		std::vector<std::string> field_w_units;
		int x_size;
		int y_size;
	public:
		Landscape(int _x_size=0, int _y_size=0,
				const std::vector<std::string>* _field = nullptr);
		int get_x_size() const {return (x_size);};
		int get_y_size() const {return (y_size);};
		void set_size(int _x_size, int _y_size);
		char get_main_cell(int x, int y) const;
		char get_cell(int x, int y) const;
		void set_cell(int x, int y, char symb);
		void set_main_cell(int x, int y, char symb);
		bool check() const;
		void load(const std::string& filename);
		std::ostream& show(std::ostream&) const;
		void save(const std::string& filename) const;

		friend bool bfs(const Landscape& land, int x_from, int y_from,
				int type, int way_type, char to_find, int &x, int &y, int radius);
	};

	bool bfs(const Landscape& land, int x_from, int y_from,
			int type, int way_type, char to_find, int &x, int &y, int radius = 0);

	class Game {
		private:
			Landscape field;
			Castle *castle = nullptr;
			Lair *lair = nullptr;
			std::deque<Unit*> units_queue;
			std::vector<std::vector<std::vector<Unit*>>> units_field;
			std::vector<std::vector<Unit*>> towers_field;
			std::vector<std::vector<aura>> aura_field;
			std::string player_name;
			const unsigned long long max_counter = 200;
			void set_cords();
			int enemy_cnt = 0;
		public:
			unsigned long long counter = 0;
			int balance = 0;
			Game(const std::string& _player_name) : player_name(_player_name) {};
			void change_landscape(int land_x_size, int land_y_size,
					const std::vector<std::string>* _field = nullptr);
			void load_landscape(const std::string& filename);
			void save_landscape(const std::string& filename);
			void move_unit(int x_from, int y_from, int x_to, int y_to, Unit* unit);
			void add_enemy(int type, int time);
			void add_enemy(int type, aura &a, int time);
			void add_tower(int x, int y);
			void add_wall(int x, int y);
			void add_to_queue(int type);
			void add_to_queue(int type, aura &a);
			void tower_level_up(int x, int y);
			void castle_level_up();
			void get_damage(int x, int y, int damage);
			Landscape& get_landscape() {return (field);}
			Castle& get_castle() {return (*castle);}
			void show_field();
			bool is_end();
			void tic();
		};
}



#endif /* CLASSES_BASIC_H_ */
