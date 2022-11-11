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
#include "../engine/game_engine_prot.h"
#include <iostream>
#include <vector>
#include <deque>
#include <memory>

namespace GC = game_consts;
namespace GE = game_engine;

namespace game_objects {
//	class Game;
//	class

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
		virtual void Action(GE::Game&) = 0;
		virtual bool is_alive() const = 0;
		virtual void get_damage(int damage) = 0;
		virtual double get_percent_health() const = 0;
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
			int type, int way_type, char to_find, int &x, int &y, int radius = -1);

}



#endif /* CLASSES_BASIC_H_ */
