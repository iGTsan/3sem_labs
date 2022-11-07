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
#include <deque>

namespace GC = game_consts;

namespace game_objects {
	/**
	 *  \brief Класс враг
	 */
	class EnemySpecialization : public Cell {
	protected:
		std::string name;
		const int max_health;
		int health;
		const int regeneration_speed;
		const int speed;
		const int damage;
		const int radius;
		const int recoil;
		const int shift;
		virtual void move(Game&) = 0;
		virtual void fire(Game&) const = 0;

	public:
		EnemySpecialization(int x, int y, int _max_health,
				int _regeneration_speed, int _speed,
				int _damage, int _radius, int _recoil, int _shift) : Cell(x, y, GC::enemy_symb),
					max_health(_max_health), health(max_health), regeneration_speed(_regeneration_speed),
					speed(_speed), damage(_damage), radius(_radius), recoil(_recoil), shift(_shift) {};
		bool is_alive() const {return (health > 0);}
		virtual ~EnemySpecialization();
		friend class Enemy;
	};

	class Enemy : public Unit {
	private:
		EnemySpecialization *specialization;
	protected:
		void regeneration();
		void move(Game& game);
		void fire(Game& game) const;
	public:
		Enemy(int x, int y, int type, int shift);
		void get_damage(int damage) override {specialization->health -= damage, std::cout << specialization->health << " Здоровья осталось" << std::endl;};
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
		HeroEnemy(int x, int y, int type, int shift, aura _hero_aura) :
			Enemy(x, y, type, shift), hero_aura(_hero_aura) {};
		void Action(Game& game) override
			{regeneration(), displace_aura(game),
			move(game), place_aura(game), fire(game);}

	};

	class Tank : EnemySpecialization {
		friend class Enemy;
	protected:
		void move(Game&) override;
		void fire(Game&) const override;
	public:
		Tank(int x, int y, int shift);
	};

	class Light : EnemySpecialization {
		friend class Enemy;
	protected:
		void move(Game&) override;
		void fire(Game&) const override;
	public:
		Light(int x, int y, int shift);
	};

	class Aviation : EnemySpecialization {
		friend class Enemy;
	protected:
		void move(Game&) override;
		void fire(Game&) const override;
	public:
		Aviation(int x, int y, int shift);
	};

	/**
	 *  \brief Класс логово
	 */

	class Lair : public Unit {
		private:
			std::deque<enemy_out> enemies;
		public:
			void get_damage(int damage) override {};
			Lair(int x=0, int y=0);
			void Action(Game&) override;
			void add(const enemy_out &enemy);
			bool is_alive() const {return (1);}
		};
}




#endif /* CLASSES_ENEMIES_H_ */
