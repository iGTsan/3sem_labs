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
		Wall() {};
		Wall(int x, int y) :
			Unit(x, y, GC::wall_symb), health(max_health) {};
		void get_damage(int damage);
		void repair(Game &);
		bool is_alive() const override {return (health > 0);}
	};
	/**
	 *  \brief Класс защитная башня
	 */
	class Tower : Unit {
	private:
		const int id = 0;
		const static int max_id = 0;
		const static tower_chars *chars_table;
		void fire(Game&) const;
	protected:
		const static int max_level;
		int level;
	public:
		Tower() {};
		Tower(int x, int y, int _level=0);
		virtual void level_up(Game&);
		virtual void Action(Game& game) override {fire(game);}
	};

	/**
	 *  \brief Класс замок
	 */
	class Castle : Wall, Tower {
	private:
		std::string name;
		const static castle_chars *chars_table;
	public:
		Castle() {};
		Castle(int x, int y, std::string _name, int _level) {};
		void Action(Game&) override;
		bool is_alive() const override {return (health > 0);}
		Castle& operator=(Castle& other);
	};
}



#endif
