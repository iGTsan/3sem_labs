#include "basic.h"
#include "enemies.h"
#include "player_things.h"
#include <stdexcept>
#include <fstream>
#include <tuple>

using std::get;

class game_objects::Game {
	private:
		Landscape field;
		Castle castle;
		Lair lair;
		std::queue<Unit*> units_queue;
		std::vector<std::vector<Unit*>> units_field;
		std::vector<std::vector<aura>> aura_field;
		int balance = 0;
		unsigned long long counter = 0;
	public:
		Game();
		Game(int land_x_size, int land_y_size,
				const std::vector<std::string>* _field = nullptr);
		void change_landscape(int land_x_size, int land_y_size,
				const std::vector<std::string>* _field = nullptr);
		void add_enemy(int type, int time);
		void tic();
	};

game_objects::Landscape::Landscape(int _x_size, int _y_size,
		const std::vector<std::string> *_field) : x_size(0), y_size(0) {
	if (_field == nullptr)
		return;
	if (static_cast<int>(_field->size()) != _x_size)
		throw std::length_error("Несовпадение размеров по Х");
	for (auto s: *_field) {
		if (static_cast<int>(s.size()) != _y_size)
			throw std::length_error("Несовпадение размеров по Y");
	}
	x_size = _x_size;
	y_size = _y_size;
	field = *_field;
}

void game_objects::Landscape::set_size(int _x_size, int _y_size) {
	field.resize(_x_size);
	for (std::string &c: field)
		c.resize(_y_size, GC::def_symb);
	x_size = _x_size;
	y_size = _y_size;
}

char game_objects::Landscape::get_cell(int x, int y) const {
	return (field[x][y]);
}

void game_objects::Landscape::set_cell(int x, int y, char symb) {
	field[x][y] = symb;
}

bool game_objects::Landscape::check() const {
	int x;
	int y;
	if (!game_objects::bfs(*this, 0, 0, 1, GC::just_way_type, GC::castle_symb, x, y, -1))
		return (0);
	if (!game_objects::bfs(*this, 0, 0, 1, GC::just_way_type, GC::lair_symb, x, y, -1))
		return (0);
	return (1);
}

void game_objects::Landscape::load(const std::string &filename) {
	std::ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
		throw std::runtime_error("Нет такого файла");
	fin >> x_size >> y_size;
	set_size(x_size, y_size);
	if (x_size * y_size != 0 && fin.eof())
		throw std::runtime_error("Плохой файл");
	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++) {
			char c;
			fin >> c;
			if (i != x_size && j != y_size && fin.eof())
				throw std::runtime_error("Плохой файл");
			set_cell(i, j, c);
		}
}

void game_objects::Landscape::save(const std::string &filename) const {
	std::ofstream fout;
	fout.open(filename, std::ios_base::out | std::ios_base::trunc);
	if (!fout.is_open())
		throw std::runtime_error("Невозможно открыть файл");
	fout << x_size << ' ' << y_size << std::endl;
	for (int i = 0; i < x_size; i++) {
		for (int j = 0; j < y_size; j++)
			fout << field[i][j] << ' ';
		fout << std::endl;
	}
}

game_objects::Game::Game() {
	field.load("../recourses/field1");
	int x;
	int y;
	game_objects::bfs(field, 0, 0, 1, GC::just_way_type, GC::castle_symb, x, y, -1);
//	castle.set(x, y, "my castle", 0);
//	game_objects::Castle new_castle(x, y, "my castle", 0);
//	castle = new_castle;
	game_objects::bfs(field, 0, 0, 1, GC::just_way_type, GC::lair_symb, x, y, -1);
//	lair = game_objects::Lair(x, y);
//	enemy_out e1(1, 1), e2(2, 2), e3(3, 3); // @suppress("Multiple variable declaration")
//	lair.add(e1);
}

void game_objects::Game::change_landscape(int land_x_size, int land_y_size,
		const std::vector<std::string> *_field) {
}

void game_objects::Game::add_enemy(int type, int time) {

}

game_objects::Game::Game(int land_x_size, int land_y_size,
		const std::vector<std::string> *_field) {
	int x = 0, y = 0;
//	game_objects::Castle new_castle(x, y, "my castle", 0);
//	castle = new_castle;
//	lair = game_objects::Lair(x, y);
}

void game_objects::Game::tic() {
}

bool check_cell(int way_type, char symb) {
	if (way_type == GC::light_type)
		if (symb == GC::mountain_symb ||
				symb == GC::river_symb ||
				symb == GC::wall_symb)
			return (0);
		else
			return (1);
	else if (way_type == GC::tank_type)
		if (symb == GC::mountain_symb ||
				symb == GC::river_symb)
			return (0);
		else
			return (1);
	else if (way_type == GC::aviation_type)
		if (symb == GC::mountain_symb)
			return (0);
		else
			return (1);
	else if (way_type == GC::just_way_type)
		return (1);
	return (1);
}

bool game_objects::bfs(const Landscape &land, int x_from, int y_from, int type,
		int way_type, char to_find, int &x, int &y, int radius) {
	std::queue<std::pair<int, int>> q;
	std::vector<std::vector<std::tuple<int, int, int>>> way(land.x_size);
	for (auto &i: way)
		i.resize(land.y_size, std::make_tuple(-1, -1, 0));
	q.push(std::make_pair(x_from, y_from));
	while (!q.empty()) {
		int x_now = get<0>(q.front());
		int y_now = get<1>(q.front());
		if (radius != -1 && radius < get<2>(way[x_now][y_now]))
			break;
		q.pop();

		if (land.field[x_now][y_now] == to_find) {
			if (type == 1) {
				x = x_now;
				y = y_now;
				return (1);
			}
			else if (type == 2) {
				while (x_now != -1 && y_now != -1) {
					x = x_now;
					y = y_now;
					x_now = get<0>(way[x][y]);
					y_now = get<1>(way[x][y]);
					return (1);
				}
			}
		}
		if (x_now > 0 && check_cell(way_type, land.field[x_now - 1][y_now]) &&
				way[x_now - 1][y_now] == std::make_tuple(-1, -1, 0)) {
			q.push(std::make_pair(x_now - 1, y_now));
			way[x_now - 1][y_now] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
		else if (y_now > 0 && check_cell(way_type, land.field[x_now][y_now - 1]) &&
				way[x_now][y_now - 1] == std::make_tuple(-1, -1, 0)) {
			q.push(std::make_pair(x_now, y_now - 1));
			way[x_now][y_now - 1] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
		else if (x_now < land.x_size - 1 && check_cell(way_type, land.field[x_now + 1][y_now]) &&
				way[x_now + 1][y_now] == std::make_tuple(-1, -1, 0)) {
			q.push(std::make_pair(x_now + 1, y_now));
			way[x_now + 1][y_now] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
		else if (y_now < land.y_size - 1 && check_cell(way_type, land.field[x_now][y_now + 1]) &&
				way[x_now][y_now + 1] == std::make_tuple(-1, -1, 0)) {
			q.push(std::make_pair(x_now, y_now + 1));
			way[x_now][y_now + 1] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
	}
	return (0);
}
