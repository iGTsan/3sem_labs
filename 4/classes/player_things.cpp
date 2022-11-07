#include "player_things.h"

namespace GC = game_consts;

void game_objects::Wall::repair(Game&) {
}

void game_objects::Tower::fire(Game& game) const {
	int x, y;
	if (bfs(game.get_landscape(), get_x_cord(), get_y_cord(),
			1, GC::aviation_type, GC::enemy_symb, x, y, chars_table[level].radius))
		game.get_damage(x, y, chars_table[level].damage);
}

game_objects::Tower::Tower(int x, int y, int _level) :
		Unit(x, y, GC::tower_symb), level(_level) {

}

void game_objects::Tower::level_up(Game&) {
}

game_objects::Castle::Castle(int x, int y, const std::string& _name, int _level) :
		Wall(x, y), Tower(x, y, _level) {
//	chars_table = GC::castle_chars_table;
}

void game_objects::Castle::set(int x, int y, const std::string &_name,
		int _level) {
}

void game_objects::Castle::Action(Game& game) {
	health = std::min(chars_table[level].max_health, health + chars_table[level].repair_speed);
	game.balance += chars_table[level].profit * health / chars_table[level].max_health;
}

void game_objects::Tower::Action(Game &game) {
	if (game.counter % chars_table[level].recoil)
		return;
	fire(game);
}
