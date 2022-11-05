/*
 * enemies.h
 *
 *  Created on: 5 нояб. 2022 г.
 *      Author: ya
 */

#ifndef CLASSES_ENEMIES_H_
#define CLASSES_ENEMIES_H_

#include "basic.h"
#include "consts.h"
#include <queue>

namespace GC = game_consts;

namespace game_objects {
	/**
	 *  \brief Класс враг
	 */
	class EnemySpecialization : Cell {
	protected:
		std::string name;
		const int max_health;
		int health;
		const int regeneration_speed;
		const int speed;
		const int damage;
		const int radius;
		virtual void move(Game&) = 0;
		virtual void fire(Game&) const = 0;

	public:
		EnemySpecialization(int x, int y, int _max_health,
				int _regeneration_speed, int _speed,
				int _damage, int _radius) : Cell(x, y, GC::enemy_symb),
					max_health(_max_health), health(max_health), regeneration_speed(_regeneration_speed),
					speed(_speed), damage(_damage), radius(_radius) {};
		bool is_alive() const {return (health > 0);}
		virtual ~EnemySpecialization();
		friend class Enemy;
	};

	class Enemy : Unit {
	private:
		EnemySpecialization *specialization;
	protected:
		void regeneration();
		void move(Game& game) {specialization->move(game);}
		void fire(Game& game) const {specialization->fire(game);}
	public:
		Enemy(int x, int y, int type);
		virtual void Action(Game& game) override
			{regeneration(), move(game), fire(game);}
		bool is_alive() const override {return (specialization->is_alive());}
	};

	class HeroEnemy : Enemy {
	private:
		aura hero_aura;
		int aura_placed = 0;
		void place_aura(Game& game) const;
		void displace_aura(Game& game) const;
	public:
		HeroEnemy(int x, int y, int type, aura _hero_aura) :
			Enemy(x, y, type), hero_aura(_hero_aura) {};
		void Action(Game& game) override
			{regeneration(), displace_aura(game),
			move(game), place_aura(game), fire(game);}

	};

	class Tank : EnemySpecialization {
	private:
		void move(Game&) override;
		void fire(Game&) const override;
	public:
		Tank(int x, int y);
	};

	class Light : EnemySpecialization {
	private:
		void move(Game&) override;
		void fire(Game&) const override;
	public:
		Light(int x, int y);
	};

	class Aviation : EnemySpecialization {
	private:
		void move(Game&) override;
		void fire(Game&) const override;
	public:
		Aviation(int x, int y);
	};

	/**
	 *  \brief Класс логово
	 */

	class Lair : Unit {
		private:
			std::queue<enemy_out> enemies;
		public:
			Lair(int x=0, int y=0) : Unit(x, y, 'a') {};
			void Action(Game&) override {};
			void add(enemy_out &enemy);
			bool is_alive() const {return (1);}
		};
}




#endif /* CLASSES_ENEMIES_H_ */
