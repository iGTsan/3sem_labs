/** \file
 *  \brief файл с классами построек игрока
 */

#ifndef CLASSES_PLAYER_THINGS_H_
#define CLASSES_PLAYER_THINGS_H_

#include "basic.h"
#include "consts.h"
#include "additional_classes.h"

namespace GC = game_consts;

namespace game_objects {

	//// Класс защитная стена
	class Wall : public Unit {
	private:
		static const int max_health = GC::wall_max_health;
	protected:
		int health;
	public:
		Wall(int x, int y) :
			Unit(x, y, GC::wall_symb), health(max_health) {};
		void get_damage(int damage) override {health -= damage;};
		void repair(GE::Game &);
		bool is_alive() const override {return (health > 0);}
		void Action(GE::Game &) override {};
		double get_percent_health() const override;
	};

	/// Класс защитная башня
	class Tower : public Unit {
	private:
		const int id = 0;
		const static int max_id = 0;
		constexpr static const tower_chars *chars_table = GC::tower_chars_table;
		void fire(GE::Game&) const;
		const static int max_level = GC::tower_max_level;
	protected:
		int level;
	public:
		void get_damage(int damage) override {};
		Tower(int x, int y, int _level=0);
		virtual void level_up(GE::Game&);
		virtual void Action(GE::Game& game) override {fire(game);};
		bool is_alive() const override {return (1);}
		double get_percent_health() const override {return (1);}
	};

	/// Класс замок
	class Castle : public Wall, Tower {
	private:
		const static int max_level = GC::castle_max_level;
		std::string name;
		constexpr static const castle_chars *chars_table = GC::castle_chars_table;
	public:
		Castle() : Wall(0, 0), Tower(0, 0) {};
		Castle(int x, int y, const std::string& _name, int _level=0);
		int get_health() {return (health);}
		void Action(GE::Game&) override; ///< Регенерация и генерация монет
		void get_damage(int damage) override {Wall::get_damage(damage);};
		bool is_alive() const override {return (Wall::is_alive());}
		void level_up(GE::Game&) override;
		double get_percent_health() const override {return (Wall::get_percent_health());}
	};
}



#endif
