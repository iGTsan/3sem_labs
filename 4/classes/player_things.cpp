#include "player_things.h"
#include "../engine/game_engine.h"

using namespace game_engine;

void game_objects::Wall::repair(Game& game) {
	int add_health = std::min(max_health - health,
			game.balance * GC::wall_repair_cost / max_health);
	health += add_health;
	game.balance -= add_health * GC::wall_repair_cost / max_health;
}

void game_objects::Tower::fire(Game& game) const {
	if (game.counter % chars_table[level].recoil)
		return;
	int x, y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::enemy_symb, x, y, chars_table[level].radius))
		game.get_damage(x, y, chars_table[level].damage);
}

game_objects::Tower::Tower(int x, int y, int _level) :
		Unit(x, y, GC::tower_symb), level(_level) {
	if (level < 0 || level > GC::tower_max_level)
		throw std::runtime_error("Bad level");
}

void game_objects::Tower::level_up(Game& game) {
	if (level == max_level - 1)
		throw std::runtime_error("Max level reached");
	if (game.balance < chars_table[level + 1].cost)
		throw std::runtime_error("Low money");
	level++;
	game.balance -= chars_table[level].cost;
}

game_objects::Castle::Castle(int x, int y, const std::string& _name, int _level) :
		Wall(x, y), Tower(x, y, _level), name(_name) {
	health = chars_table[level].max_health;
	if (level < 0 || level > GC::castle_max_level)
		throw std::runtime_error("Bad level");
}

void game_objects::Castle::Action(Game& game) {
	if (game.counter % chars_table[level].repair_speed == 0)
		health = std::min(chars_table[level].max_health, health + 1);
	if (game.counter % GC::castle_profit_speed == 0)
		game.balance += chars_table[level].profit * health / chars_table[level].max_health;
}

void game_objects::Castle::level_up(GE::Game& game) {
	if (level == max_level - 1)
		throw std::runtime_error("Max level reached");
	if (game.balance < chars_table[level + 1].cost)
		throw std::runtime_error("Low money");
	level++;
	game.balance -= chars_table[level].cost;
}

double game_objects::Wall::get_percent_health() const {
	return (static_cast<double>(health) / max_health);
}

double game_objects::Castle::get_percent_health() const {
	return (static_cast<double>(health) / chars_table[level].max_health);
}
