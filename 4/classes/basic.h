/**
* \file
* \brief Файл с объявлением основных классов
*/

#ifndef CLASSES_BASIC_H_
#define CLASSES_BASIC_H_

#include "consts.h"
#include "additional_classes.h"
#include "../engine/game_engine_prot.h"
#include <iostream>
#include <deque>
#include "vector.h"

namespace GC = game_consts;
namespace GE = game_engine;

/// Пространство имен с классами игровых объектов
namespace game_objects {
	/// Класс "Ячейка игрового поля"
	/**
	 * Имеет координаты и символ соответсвующий типу ячейки.
	 */
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
	/// Класс "Действующее лицо"
	/**
	 * Потомок Cell.
	 * Интерфейс для всех действующих лиц игры.
	 */
	class Unit : public Cell {
	public:
		Unit(int x, int y, char symb) :
			Cell(x, y, symb) {};
		virtual void Action(GE::Game&) = 0;
		virtual bool is_alive() const = 0;
		virtual void get_damage(int damage) = 0;
		virtual double get_percent_health() const = 0;
	};
	/// Класс "Ландшафт"
	/**
	 *	Описывает игровое поле(расположение врагов, башен, замка и т. д.).
	 */
	class Landscape {
	private:
		std::MyVector<std::string> field; ///< Основное поле \details Только равнины, горы, реки, замок и логово.
		std::MyVector<std::string> field_w_units; ///< Поле со всеми действующими лицами
		int x_size;
		int y_size;
	public:
		Landscape(int _x_size=0, int _y_size=0,
				const std::MyVector<std::string>* _field = nullptr);
		int get_x_size() const {return (x_size);};
		int get_y_size() const {return (y_size);};
		void set_size(int _x_size, int _y_size);
		char get_main_cell(int x, int y) const;
		char get_cell(int x, int y) const;
		void set_cell(int x, int y, char symb);
		void set_main_cell(int x, int y, char symb);
		bool check() const; ///< Проверка текущего поля на корректность \details Проверка на существование замка, логова и пути между ними
		void load(const std::string& filename);
		std::ostream& show(std::ostream&) const;
		void save(const std::string& filename) const;

		friend bool bfs(const Landscape& land, int x_from, int y_from,
				int type, int way_type, char to_find, int &x, int &y, int radius);
	};

	/** \brief Поиск кратчайшего пути между чем угодно
	 * \param [in] land поле, на котором ищется путь
	 * \param [in] x_from начальная координата x
	 * \param [in] y_from начальная координата y
	 * \param [in] type тип возвращаемого значения (1 - найденная клетка, 2 - соседняя клетка на пути к найденной)
	 * \param [in] way_type тип пути (легкая пехота, танк или авиация)
	 * \param [in] to_find клетка, которую нужно найти
	 * \param [out] x возвращаемая координата x
	 * \param [out] y возвращаемая координата y
	 * \param [in] radius радиус поиска
	 */
	bool bfs(const Landscape& land, int x_from, int y_from,
			int type, int way_type, char to_find, int &x, int &y, int radius = -1);
}

#endif
