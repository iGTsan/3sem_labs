#include "enemies.h"
#include "player_things.h"
#include "../engine/game_engine.h"

game_objects::Lair::Lair(int x, int y) : Unit(x, y, GC::lair_symb) {}

void game_objects::Lair::add(const enemy_out &enemy) {
	if (!enemies.empty() && enemies.back().time > enemy.time)
		throw std::runtime_error("Нарушение порядка выхода врагов");
	enemies.push_back(enemy);
}

void game_objects::Enemy::regeneration(GE::Game& game) {
	new_speed = std::max(1, specialization->speed - specialization->speed *
			game.aura_field[get_x_cord()][get_y_cord()].speed / 100);
	if (game.counter % std::max(specialization->regeneration_speed *
			(100 - game.aura_field[get_x_cord()][get_y_cord()].regeneration) / 100, 1))
		return;
	new_max_health = specialization->max_health + specialization->max_health *
			game.aura_field[get_x_cord()][get_y_cord()].health / 100;
	specialization->health = std::min(specialization->health + 1, new_max_health);
}

game_objects::Enemy::Enemy(int x, int y, int type, int shift) :
		Unit(x, y, GC::enemy_symb) {
	switch(type) {
	case (GC::tank_type):
		specialization = new Tank(x, y, shift);
		set_symb(GC::tank_symb);
		break;
	case (GC::light_type):
		specialization = new Light(x, y, shift);
		set_symb(GC::light_symb);
		break;
	case (GC::aviation_type):
		specialization = new Aviation(x, y, shift);
		set_symb(GC::aviation_symb);
		break;
	default:
		throw std::runtime_error("Нет такого типа");
	}
	new_max_health = specialization->max_health;
	new_speed = specialization->speed;
	new_regeneration = specialization->regeneration_speed;
}

void game_objects::Tank::move(GE::Game& game) {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			2, GC::light_type, GC::castle_symb,x, y, -1))
		set_cords(x, y);
	else if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			2, GC::tank_type, GC::castle_symb,x, y, -1) &&
			game.get_landscape().get_cell(x, y) != GC::wall_symb)
		set_cords(x, y);
}

void game_objects::Tank::fire(GE::Game& game) const {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::castle_symb, x, y, radius))
		game.get_castle().get_damage(damage * health / max_health);
	else if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::wall_symb, x, y, radius))
		game.get_damage(x, y, damage * health / max_health);
}

game_objects::Tank::Tank(int x, int y, int shift) :
		EnemySpecialization(x, y, GC::tank_max_health, GC::tank_regeneration_speed,
				GC::tank_speed, GC::tank_damage, GC::tank_radius, GC::tank_recoil, shift) {}

void game_objects::Light::move(GE::Game& game) {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			2, GC::light_type, GC::castle_symb, x, y, -1))
		set_cords(x, y);
}

void game_objects::Light::fire(GE::Game& game) const {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::castle_symb, x, y, radius))
		game.get_castle().get_damage(damage * health / max_health);
}

game_objects::Light::Light(int x, int y, int shift) :
		EnemySpecialization(x, y, GC::light_max_health, GC::light_regeneration_speed,
				GC::light_speed, GC::light_damage, GC::light_radius, GC::light_recoil, shift) {
}

void game_objects::Aviation::move(GE::Game& game) {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			2, GC::aviation_type, GC::castle_symb, x, y, -1))
		set_cords(x, y);
}

void game_objects::Aviation::fire(GE::Game& game) const {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::castle_symb, x, y, radius))
		game.get_castle().get_damage(damage * health / max_health);
}

game_objects::Aviation::Aviation(int x, int y, int shift) :
		EnemySpecialization(x, y, GC::aviation_max_health, GC::aviation_regeneration_speed,
				GC::aviation_speed, GC::aviation_damage, GC::aviation_radius, GC::aviation_recoil, shift) {
}

void game_objects::Lair::Action(GE::Game& game) {
	if (!enemies.empty()
			&& enemies.front().time	<= game.counter) {
		if (enemies.front().aur == aura{0,0,0})
			game.add_to_queue(enemies.front().type);
		else
			game.add_to_queue(enemies.front().type, enemies.front().aur);
		enemies.pop_front();
	}
}

void game_objects::HeroEnemy::place_aura(GE::Game &game) {
	if (!aura_placed)
		aura_bfs(game, 1);
	aura_placed = 1;
}

void game_objects::HeroEnemy::displace_aura(GE::Game &game) {
	if (aura_placed)
		aura_bfs(game, 0);
	aura_placed = 0;
}

void game_objects::Enemy::move(GE::Game &game) {
	if ((game.counter - specialization->shift) % new_speed)
		return;
	int x_old = specialization->get_x_cord();
	int y_old = specialization->get_y_cord();
	specialization->move(game);
	game.move_unit(x_old, y_old,
			specialization->get_x_cord(), specialization->get_y_cord(), this);
	set_cords(specialization->get_x_cord(), specialization->get_y_cord());
}

void game_objects::Enemy::fire(GE::Game &game) const {
	if ((game.counter - specialization->shift) % specialization->recoil)
		return;
	specialization->fire(game);
}

void game_objects::HeroEnemy::aura_bfs(GE::Game &game, int type) {
	std::deque<std::pair<int, int>> q;
	std::MyVector<std::MyVector<int>> way(game.get_landscape().get_x_size());
	for (auto &i: way)
		i.resize(game.get_landscape().get_y_size(), -1);
	q.push_back(std::make_pair(get_x_cord(), get_y_cord()));
	way[get_x_cord()][get_y_cord()] = 0;
	while (!q.empty()) {
		int x_now = std::get<0>(q.front());
		int y_now = std::get<1>(q.front());
		if (specialization->radius < way[x_now][y_now])
			break;
		q.pop_front();
		if (type == 1)
			game.aura_field[x_now][y_now] += hero_aura;
		else
			game.aura_field[x_now][y_now] -= hero_aura;
		if (x_now > 0 && way[x_now - 1][y_now] == -1) {
			q.push_back(std::make_pair(x_now - 1, y_now));
			way[x_now - 1][y_now] = way[x_now][y_now] + 1;
		}
		if (y_now > 0 && way[x_now][y_now - 1] == -1) {
			q.push_back(std::make_pair(x_now, y_now - 1));
			way[x_now][y_now - 1] = way[x_now][y_now] + 1;
		}
		if (x_now < game.get_landscape().get_x_size() - 1 && way[x_now + 1][y_now] == -1) {
			q.push_back(std::make_pair(x_now + 1, y_now));
			way[x_now + 1][y_now] = way[x_now][y_now] + 1;
		}
		if (y_now < game.get_landscape().get_y_size() - 1 && way[x_now][y_now + 1] == -1) {
			q.push_back(std::make_pair(x_now, y_now + 1));
			way[x_now][y_now + 1] = way[x_now][y_now] + 1;
		}
	}
}

int game_objects::Lair::time_last_enemy() {
	if (enemies.empty())
		return (0);
	return (enemies.back().time);
}

game_objects::HeroEnemy::HeroEnemy(int x, int y, int type, int shift,
		aura _hero_aura) :
		Enemy(x, y, type, shift), hero_aura(_hero_aura) {
	switch(type) {
		case (GC::tank_type):
			set_symb(GC::hero_tank_symb);
			break;
		case (GC::light_type):
			set_symb(GC::hero_light_symb);
			break;
		case (GC::aviation_type):
			set_symb(GC::hero_aviation_symb);
			break;
		default:
			throw std::runtime_error("Нет такого типа");
		}
}

double game_objects::Enemy::get_percent_health() const {
		return (static_cast<double>(specialization->health) / new_max_health);
}

game_objects::Enemy::~Enemy() {
	delete specialization;
}
/*
 * enemies.cpp
 *
 *  Created on: 5 нояб. 2022 г.
 *      Author: ya
 */




