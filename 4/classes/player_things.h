#ifndef CLASSES_PLAYER_THINGS_H_
#define CLASSES_PLAYER_THINGS_H_

#include "basic.h"
#include "consts.h"
#include "additional_classes.h"

namespace GC = game_consts;


namespace game_objects {
	/**
	 *  \brief Класс защитная стена
	 */
	class Wall : Unit {
	private:
		static const int max_health = GC::wall_max_health;
	protected:
		int health;
	public:
		Wall(int x, int y) :
			Unit(x, y, GC::wall_symb), health(max_health) {};
		void get_damage(int damage) override {health -= damage;};
		void repair(Game &);
		bool is_alive() const override {return (health > 0);}
	};
	/**
	 *  \brief Класс защитная башня
	 */
	class Tower : public Unit {
	private:
		const int id = 0;
		const static int max_id = 0;
		constexpr static const tower_chars *chars_table = GC::tower_chars_table;
		void fire(Game&) const;
	protected:
		const static int max_level;
		int level;
	public:
		void get_damage(int damage) override {};
		Tower(int x, int y, int _level=0);
		void level_up(Game&);
		virtual void Action(Game& game) override;
		bool is_alive() const override {return (1);}
	};

	/**
	 *  \brief Класс замок
	 */
	class Castle : public Wall, Tower {
	private:
		std::string name;
		constexpr static const castle_chars *chars_table = GC::castle_chars_table;
	public:
		Castle() : Wall(0, 0), Tower(0, 0) {};
		Castle(int x, int y, const std::string& _name, int _level=0);
		void set(int x, int y, const std::string& _name, int _level=0);
		int get_health() {return (health);}
		void Action(Game&) override;
		void get_damage(int damage) {Wall::get_damage(damage);};
		bool is_alive() const {return (Wall::is_alive());}
//		Castle& operator=(Castle& other);
	};
}



#endif
