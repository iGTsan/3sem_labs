#include "basic.h"
#include "enemies.h"
#include "player_things.h"
#include <stdexcept>
#include <fstream>
#include <tuple>

using std::get;

game_objects::Landscape::Landscape(int _x_size, int _y_size,
		const std::MyVector<std::string> *_field) : x_size(0), y_size(0) {
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
	field_w_units.resize(_x_size);
		for (std::string &c: field_w_units)
			c.resize(_y_size, GC::def_symb);
	x_size = _x_size;
	y_size = _y_size;
}

char game_objects::Landscape::get_main_cell(int x, int y) const {
	return (field[x][y]);
}

char game_objects::Landscape::get_cell(int x, int y) const {
	return (field_w_units[x][y]);
}

void game_objects::Landscape::set_cell(int x, int y, char symb) {
	field_w_units[x][y] = symb;
}

void game_objects::Landscape::set_main_cell(int x, int y, char symb) {
	field[x][y] = symb;
}

bool game_objects::Landscape::check() const {
	int x;
	int y;
	if (!game_objects::bfs(*this, 0, 0, 1, GC::just_way_type, GC::castle_symb, x, y, -1))
		return (0);
	if (!game_objects::bfs(*this, x, y, 1, GC::light_type, GC::lair_symb, x, y, -1))
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
			set_main_cell(i, j, c);
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

std::ostream& operator <<(std::ostream& c, const game_objects::Landscape& land) {
	return (land.show(c));
}

std::ostream& game_objects::Landscape::show(std::ostream &c) const {
	system("clear");
	for (auto s: field_w_units) {
		for (auto c: s) {
			std::string out;
			switch (c) {
			case (GC::enemy_symb):
				printf( "\033[91;47m\033[1mE\033[0m" );
				break;
			case (GC::river_symb):
				printf( "\033[96;47m\033[1mR\033[0m" );
				break;
			case (GC::mountain_symb):
				printf( "\033[90;47m\033[1mM\033[0m" );
				break;
			case (GC::plain_symb):
				printf( "\033[93;47m\033[1mP\033[0m" );
				break;
			case (GC::castle_symb):
				printf( "\033[35;47m\033[1mC\033[0m" );
				break;
			case (GC::lair_symb):
				printf( "\033[35;47m\033[1mL\033[0m" );
				break;
			case (GC::tower_symb):
				printf( "\033[92;47m\033[1mT\033[0m" );
				break;
			case (GC::wall_symb):
				printf( "\033[31;47m\033[1mW\033[0m" );
				break;

			}
		}
		c << std::endl;
	}
	return (c);
}

bool check_cell(int way_type, char symb) {
	if (way_type == GC::light_type)
		if (symb == GC::mountain_symb ||
				symb == GC::river_symb ||
				symb == GC::wall_symb )
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

bool is_enemy(char symb) {
	return (symb == GC::tank_symb || symb == GC::hero_tank_symb ||
			symb == GC::light_symb || symb == GC::hero_light_symb ||
			symb == GC::aviation_symb || symb == GC::hero_aviation_symb);
}

bool game_objects::bfs(const Landscape &land, int x_from, int y_from, int type,
		int way_type, char to_find, int &x, int &y, int radius) {
	std::deque<std::pair<int, int>> q;
	std::MyVector<std::MyVector<std::tuple<int, int, int>>> way(land.x_size);
	for (auto &i: way)
		i.resize(land.y_size, std::make_tuple(-1, -1, -1));
	q.push_back(std::make_pair(x_from, y_from));
	way[x_from][y_from] = {-1, -1, 0};
	while (!q.empty()) {
		int x_now = get<0>(q.front());
		int y_now = get<1>(q.front());
		if (radius != -1 && radius < get<2>(way[x_now][y_now]))
			break;
		q.pop_front();

		if (land.field_w_units[x_now][y_now] == to_find ||
				(to_find == GC::enemy_symb && is_enemy(land.field_w_units[x_now][y_now]))) {
			if (type == 1) {
				x = x_now;
				y = y_now;
				return (1);
			}
			else if (type == 2) {
				if (get<2>(way[x_now][y_now]) == 1) {
					x = get<0>(way[x_now][y_now]);
					y = get<1>(way[x_now][y_now]);
				}
				else
					while (x_now != x_from || y_now != y_from) {
						x = x_now;
						y = y_now;
						x_now = get<0>(way[x][y]);
						y_now = get<1>(way[x][y]);
					}
				return (1);
			}
		}
		if (x_now > 0 && check_cell(way_type, land.field_w_units[x_now - 1][y_now]) &&
				way[x_now - 1][y_now] == std::make_tuple(-1, -1, -1)) {
			q.push_back(std::make_pair(x_now - 1, y_now));
			way[x_now - 1][y_now] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
		if (y_now > 0 && check_cell(way_type, land.field_w_units[x_now][y_now - 1]) &&
				way[x_now][y_now - 1] == std::make_tuple(-1, -1, -1)) {
			q.push_back(std::make_pair(x_now, y_now - 1));
			way[x_now][y_now - 1] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
		if (x_now < land.x_size - 1 && check_cell(way_type, land.field_w_units[x_now + 1][y_now]) &&
				way[x_now + 1][y_now] == std::make_tuple(-1, -1, -1)) {
			q.push_back(std::make_pair(x_now + 1, y_now));
			way[x_now + 1][y_now] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
		if (y_now < land.y_size - 1 && check_cell(way_type, land.field_w_units[x_now][y_now + 1]) &&
				way[x_now][y_now + 1] == std::make_tuple(-1, -1, -1)) {
			q.push_back(std::make_pair(x_now, y_now + 1));
			way[x_now][y_now + 1] = {x_now, y_now, get<2>(way[x_now][y_now]) + 1};
		}
	}
	return (0);
}


