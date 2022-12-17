#include "game_engine.h"

using namespace game_objects;
using namespace game_engine;

void Game::add_enemy(int type, int time) {
	lair->add(enemy_out(time, type));
}

void Game::load_landscape(const std::string &filename) {
	field.load(filename);
	set_cords();
	units_field.resize(field.get_x_size());
	for (auto &v: units_field)
		v.resize(field.get_y_size());
	towers_field.resize(field.get_x_size());
	for (auto &v: towers_field)
		v.resize(field.get_y_size(), nullptr);
	aura_field.resize(field.get_x_size());
	for (auto &v: aura_field)
		v.resize(field.get_y_size(), {0,0,0});
}

void Game::save_landscape(const std::string &filename) const {
	field.save(filename);
}

void Game::set_cords() {
	int x;
	int y;
	bfs(field, 0, 0, 1, GC::just_way_type, GC::castle_symb, x, y, -1);
	delete castle;
	castle = new Castle(x, y, player_name);
	bfs(field, 0, 0, 1, GC::just_way_type, GC::lair_symb, x, y, -1);
	delete lair;
	lair = new Lair(x, y);
	units_queue.clear();
	units_queue.push_back(nullptr);
}

void Game::show_field() const {
	field.show(std::cout);
	std::cout << "Здоровье замка: " << castle->get_health() <<
			" Деньги: "  << balance << " Время: " << counter << std::endl;
}

int Game::is_end() const {
	if (!castle->is_alive())
		return (-1);
	if (lair->time_last_enemy() == 0) {
		for (auto row: units_field)
			for (auto cell: row)
				for (auto unit: cell)
					if (unit->get_symb() != GC::wall_symb)
						return (0);
		return (1);
	}
	return (0);
}

GO::Unit* Game::add_to_queue(int type) {
	int x = lair->get_x_cord();
	int y = lair->get_y_cord();
	Unit * new_unit = new Enemy(x, y, type, counter);
	units_queue.push_front(new_unit);
	units_field[x][y].push_back(new_unit);
	return (new_unit);
}

void Game::add_enemy(int type, const aura &a, int time) {
	lair->add(enemy_out(time, type, a));
}

GO::Unit* Game::add_to_queue(int type, const aura &a) {
	int x = lair->get_x_cord();
	int y = lair->get_y_cord();
	Unit * new_unit = new HeroEnemy(x, y, type, counter, a);
	units_queue.push_front(new_unit);
	units_field[x][y].push_back(new_unit);
	return (new_unit);
}

void Game::get_damage(int x, int y, int damage) {
	auto it = units_field[x][y].begin();
	if (it == units_field[x][y].end())
		return;
	(static_cast<Unit*>(*it))->get_damage(damage);
	if (!(static_cast<Unit*>(*it))->is_alive()) {
		units_field[x][y].erase(it);
		if (units_field[x][y].empty())
			field.set_cell(x, y, field.get_main_cell(x, y));
	}
}

GO::Unit* Game::add_tower(int x, int y) {
	if (balance < GC::tower_chars_table[0].cost)
		throw std::runtime_error("Low money");
	if (x < 0 || x >= field.get_x_size() ||
			y < 0 || y >= field.get_y_size())
		throw std::runtime_error("Wrong cords");
	if (towers_field[x][y] != nullptr)
		throw std::runtime_error("Place isn't empty");
	if (field.get_cell(x, y) != GC::plain_symb &&
			field.get_cell(x, y) != GC::wall_symb)
		throw std::runtime_error("Bad place");
	balance -= GC::tower_chars_table[0].cost;
	Tower* new_tower = new Tower(x, y);
	units_queue.push_front(new_tower);
	towers_field[x][y] = (new_tower);
	return (new_tower);
}

GO::Unit* Game::add_wall(int x, int y) {
	if (balance < GC::wall_cost)
		throw std::runtime_error("Low money");
	if (x < 0 || x >= field.get_x_size() ||
			y < 0 || y >= field.get_y_size())
		throw std::runtime_error("Wrong cords");
	if (field.get_cell(x, y) != GC::plain_symb &&
			field.get_cell(x, y) != GC::tower_symb)
		throw std::runtime_error("Bad place");
	auto it = units_field[x][y].begin();
	while (it != units_field[x][y].end()) {
		if ((static_cast<GO::Unit*>((*it)))->get_symb() == GC::wall_symb)
			throw std::runtime_error("Place isn't empty");
		it++;
	}
	balance -= GC::wall_cost;
	Unit* new_wall = new Wall(x, y);
	units_field[x][y].push_back(new_wall);
	field.set_cell(x, y, GC::wall_symb);
	return (new_wall);
}

void Game::tower_level_up(int x, int y) {
	if (towers_field[x][y])
		towers_field[x][y]->level_up(*this);
	else
		throw std::runtime_error("There is no tower");
}

void Game::castle_level_up() {
	castle->level_up(*this);
}

void game_engine::Game::repair_wall(int x, int y) {
	auto it = units_field[x][y].begin();
	while (it != units_field[x][y].end()) {
		if ((static_cast<GO::Unit*>((*it)))->get_symb() == GC::wall_symb) {
			(static_cast<GO::Wall*>((*it)))->repair(*this);
			return;
		}
		it++;
	}
	if (it == units_field[x][y].end())
		throw std::runtime_error("There is no wall");
}

void game_engine::Game::add_random_enemy() {
	int type = std::rand() % 3 + 1;
	int is_hero = std::rand() % 10;
	GO::aura aur;
	int time = std::rand() % 300;
	time = std::max(counter, lair->time_last_enemy()) + time;
	if (!is_hero) {
		aur.health = std::rand() % 100;
		aur.health = (aur.health * aur.health * aur.health) / 10000;
		aur.regeneration = std::rand() % 100;
		aur.regeneration = (aur.regeneration * aur.regeneration * aur.regeneration) / 10000;
		aur.speed = std::rand() % 100;
		aur.speed = (aur.speed * aur.speed * aur.speed) / 10000;
		lair->add(enemy_out(time, type, aur));
	}
	else
		lair->add(enemy_out(time, type));
}

void Game::tic() {
	lair->Action(*this);
	castle->Action(*this);
	while (units_queue.front()) {
		if (units_queue.front()->is_alive()) {
			units_queue.front()->Action(*this);
			units_queue.push_back(units_queue.front());
			units_queue.pop_front();
		}
		else {
			auto unit = units_queue.front();
			units_queue.pop_front();
			if (units_field[unit->get_x_cord()][unit->get_y_cord()].empty())
				field.set_cell(unit->get_x_cord(), unit->get_y_cord(),
						field.get_main_cell(unit->get_x_cord(), unit->get_y_cord()));
			delete unit;
		}
	}
	units_queue.pop_front();
	units_queue.push_back(nullptr);
	counter++;
}

void Game::move_unit(int x_from, int y_from, int x_to, int y_to, Unit* unit) {
	auto it = units_field[x_from][y_from].begin();
	while (*it != unit)
		it++;
	units_field[x_from][y_from].erase(it);
	if (units_field[x_from][y_from].empty())
		field.set_cell(x_from, y_from, field.get_main_cell(x_from, y_from));

	if (units_field[x_to][y_to].empty())
		field.set_cell(x_to, y_to, unit->get_symb());
	units_field[x_to][y_to].push_back(unit);

}

game_engine::Game::~Game() {
	delete castle;
	delete lair;
	for (auto row: units_field)
		for (auto cell: row)
			for (auto unit: cell)
				delete unit;

	for (auto row: towers_field)
		for (auto unit: row)
			if (unit)
				delete unit;
}
