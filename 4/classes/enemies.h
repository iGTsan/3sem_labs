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
		virtual void move(GE::Game&) = 0;
		virtual void fire(GE::Game&) const = 0;

	public:
		EnemySpecialization(int x, int y, int _max_health,
				int _regeneration_speed, int _speed,
				int _damage, int _radius, int _recoil, int _shift) : Cell(x, y, GC::enemy_symb),
					max_health(_max_health), health(max_health), regeneration_speed(_regeneration_speed),
					speed(_speed), damage(_damage), radius(_radius), recoil(_recoil), shift(_shift) {};
		bool is_alive() const {return (health > 0);}
		virtual ~EnemySpecialization() {};
		friend class Enemy;
		friend class HeroEnemy;
	};

	class Enemy : public Unit {
	protected:
		EnemySpecialization *specialization;
		void regeneration(GE::Game&);
		void move(GE::Game& game);
		void fire(GE::Game& game) const;
		int new_speed;
		int new_max_health;
		int new_regeneration;
	public:
		Enemy(int x, int y, int type, int shift);
		void get_damage(int damage) override {specialization->health -= damage, std::cout << specialization->health << " Здоровья осталось" << std::endl;};
		virtual void Action(GE::Game& game) override
			{regeneration(game), move(game), fire(game);}
		bool is_alive() const override {return (specialization->is_alive());}
		double get_percent_health() const override;
	};

	class HeroEnemy : public Enemy {
	private:
		aura hero_aura;
		int aura_placed = 0;
		void place_aura(GE::Game& game);
		void displace_aura(GE::Game& game);
		void aura_bfs(GE::Game& game, int type);
	public:
		HeroEnemy(int x, int y, int type, int shift, aura _hero_aura);
		void Action(GE::Game& game) override
			{regeneration(game), displace_aura(game),
			move(game), place_aura(game), fire(game);}

	};

	class Tank : EnemySpecialization {
		friend class Enemy;
	protected:
		void move(GE::Game&) override;
		void fire(GE::Game&) const override;
	public:
		Tank(int x, int y, int shift);
	};

	class Light : EnemySpecialization {
		friend class Enemy;
	protected:
		void move(GE::Game&) override;
		void fire(GE::Game&) const override;
	public:
		Light(int x, int y, int shift);
	};

	class Aviation : EnemySpecialization {
		friend class Enemy;
	protected:
		void move(GE::Game&) override;
		void fire(GE::Game&) const override;
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
			void Action(GE::Game&) override;
			void add(const enemy_out &enemy);
			bool is_alive() const {return (1);}
			int time_last_enemy();
			double get_percent_health() const override {return (1);}
		};
}

#endif /* CLASSES_ENEMIES_H_ */
