#include "enemies.h"
#include "player_things.h"

game_objects::Lair::Lair(int x, int y) : Unit(x, y, GC::lair_symb) {}

void game_objects::Lair::add(const enemy_out &enemy) {
	if (!enemies.empty() && enemies.back().time > enemy.time)
		throw std::runtime_error("Нарушение порядка выхода врагов");
	enemies.push_back(enemy);
}

void game_objects::Enemy::regeneration() {
	specialization->health = std::min(specialization->health + specialization->regeneration_speed, specialization->max_health);
}

game_objects::Enemy::Enemy(int x, int y, int type, int shift) :
		Unit(x, y, GC::enemy_symb) {
	switch(type) {
	case (GC::tank_type):
		specialization = new Tank(x, y, shift);
		break;
	case (GC::light_type):
		specialization = new Light(x, y, shift);
		break;
	case (GC::aviation_type):
		specialization = new Aviation(x, y, shift);
		break;
	default:
		throw std::runtime_error("Нет такого типа");
	}
}

void game_objects::Tank::move(Game& game) {
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

void game_objects::Tank::fire(Game& game) const {
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

void game_objects::Light::move(Game& game) {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			2, GC::light_type, GC::castle_symb, x, y, -1))
		set_cords(x, y);
}

void game_objects::Light::fire(Game& game) const {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::castle_symb, x, y, radius))
		game.get_castle().get_damage(damage * health / max_health);
	else if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::wall_symb, x, y, radius))
		game.get_damage(x, y, damage * health / max_health);
}

game_objects::Light::Light(int x, int y, int shift) :
		EnemySpecialization(x, y, GC::light_max_health, GC::light_regeneration_speed,
				GC::light_speed, GC::light_damage, GC::light_radius, GC::light_recoil, shift) {
}

void game_objects::Aviation::move(Game& game) {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			2, GC::aviation_type, GC::castle_symb, x, y, -1))
		set_cords(x, y);
}

void game_objects::Aviation::fire(Game& game) const {
	int x;
	int y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::castle_symb, x, y, radius))
		game.get_castle().get_damage(damage * health / max_health);
	else if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::wall_symb, x, y, radius))
		game.get_damage(x, y, damage * health / max_health);
}

game_objects::Aviation::Aviation(int x, int y, int shift) :
		EnemySpecialization(x, y, GC::aviation_max_health, GC::aviation_regeneration_speed,
				GC::aviation_speed, GC::aviation_damage, GC::aviation_radius, GC::aviation_recoil, shift) {
}

void game_objects::Lair::Action(Game& game) {
	if (!enemies.empty()
			&& static_cast<unsigned long long>(enemies.front().time)
					<= game.counter) {
		game.add_to_queue(enemies.front().type);
		enemies.pop_front();
	}
}

game_objects::EnemySpecialization::~EnemySpecialization() {
}

void game_objects::HeroEnemy::place_aura(Game &game) const {
}

void game_objects::HeroEnemy::displace_aura(Game &game) const {
}

void game_objects::Enemy::move(Game &game) {
	if ((game.counter - specialization->shift) % specialization->speed)
		return;
	int x_old = specialization->get_x_cord();
	int y_old = specialization->get_y_cord();
	specialization->move(game);
	game.move_unit(x_old, y_old,
			specialization->get_x_cord(), specialization->get_y_cord(), this);
	set_cords(specialization->get_x_cord(), specialization->get_y_cord());
}

void game_objects::Enemy::fire(Game &game) const {
	if ((game.counter - specialization->shift) % specialization->recoil)
		return;
	specialization->fire(game);
}
/*
 * enemies.cpp
 *
 *  Created on: 5 нояб. 2022 г.
 *      Author: ya
 */




