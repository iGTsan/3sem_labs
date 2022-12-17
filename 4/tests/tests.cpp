#include "tests.h"
#include "../classes/vector.h"
#include "../classes/basic.h"
#include "../engine/game_engine.h"
#include <gtest/gtest.h>

namespace GE = game_engine;
namespace GC = game_consts;
namespace GO = game_objects;

const std::string pwd = "/home/ya/infa/3 sem/lab/4/tests/";
const std::string testfield = "testfield";
const std::string name = name;

constexpr int castle_x = 7;
constexpr int castle_y = 5;
constexpr int lair_x = 0;
constexpr int lair_y = 0;
constexpr int mountain_x = 4;
constexpr int mountain_y = 4;
constexpr int river_x = 7;
constexpr int river_y = 4;
constexpr int plain_x = 1;
constexpr int plain_y = 1;


TEST (Game, InitConstructor) {
	ASSERT_NO_THROW(GE::Game game(name));
}

TEST (Game, LoadLandscape) {
	GE::Game game(name);
	ASSERT_NO_THROW(game.load_landscape(pwd + testfield));
	ASSERT_EQ(game.get_castle().get_name(), name);
	ASSERT_EQ(game.get_landscape().get_cell(castle_x, castle_y), GC::castle_symb);
	ASSERT_EQ(game.get_castle().get_x_cord(), castle_x);
	ASSERT_EQ(game.get_castle().get_y_cord(), castle_y);
}

TEST (Game, SaveLandscape) {
	GE::Game game(name);
	ASSERT_NO_THROW(game.load_landscape(pwd + testfield));
	ASSERT_NO_THROW(game.save_landscape(pwd + testfield + "2"));
	ASSERT_NO_THROW(game.load_landscape(pwd + testfield + "2"));
}

TEST (Game, BuildWall) {
	GO::Unit *wall;
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	ASSERT_THROW(game.add_wall(plain_x, plain_y), std::runtime_error);
	game.balance = GC::wall_cost;
	ASSERT_NO_THROW(wall = game.add_wall(plain_x, plain_y));
	ASSERT_EQ(game.get_landscape().get_cell(plain_x, plain_y), GC::wall_symb);
	ASSERT_EQ(game.get_landscape().get_main_cell(plain_x, plain_y), GC::plain_symb);
	ASSERT_EQ(wall->get_x_cord(), plain_x);
	ASSERT_EQ(wall->get_y_cord(), plain_y);
	game.balance = GC::wall_cost;
	ASSERT_THROW(game.add_wall(plain_x, plain_y), std::runtime_error);
	ASSERT_THROW(game.add_wall(castle_x, castle_y), std::runtime_error);
	ASSERT_THROW(game.add_wall(lair_x, lair_y), std::runtime_error);
	ASSERT_THROW(game.add_wall(mountain_x, mountain_y), std::runtime_error);
	ASSERT_THROW(game.add_wall(river_x, river_y), std::runtime_error);
}

TEST (Game, BuildTower) {
	GO::Unit* tower;
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	ASSERT_THROW(game.add_tower(plain_x, plain_y), std::runtime_error);
	game.balance = GC::tower_chars_table[0].cost;
	ASSERT_NO_THROW(tower = game.add_tower(plain_x, plain_y));
	ASSERT_EQ(game.get_landscape().get_cell(plain_x, plain_y), GC::plain_symb);
	ASSERT_EQ(game.get_landscape().get_main_cell(plain_x, plain_y), GC::plain_symb);
	ASSERT_EQ(tower->get_x_cord(), plain_x);
	ASSERT_EQ(tower->get_y_cord(), plain_y);
	game.balance = GC::tower_chars_table[0].cost;
	ASSERT_THROW(game.add_tower(plain_x, plain_y), std::runtime_error);
	ASSERT_THROW(game.add_tower(castle_x, castle_y), std::runtime_error);
	ASSERT_THROW(game.add_tower(lair_x, lair_y), std::runtime_error);
	ASSERT_THROW(game.add_tower(mountain_x, mountain_y), std::runtime_error);
	ASSERT_THROW(game.add_tower(river_x, river_y), std::runtime_error);
}

TEST (Game, PlaceEnemy) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	auto enemy = game.add_to_queue(GC::light_type);
	ASSERT_EQ(enemy->get_x_cord(), lair_x);
	ASSERT_EQ(enemy->get_y_cord(), lair_y);
	ASSERT_EQ(game.units_field[lair_x][lair_y][0], enemy);

	auto hero = game.add_to_queue(GC::tank_type, {1, 1, 1});
	ASSERT_EQ(hero->get_x_cord(), lair_x);
	ASSERT_EQ(hero->get_y_cord(), lair_y);
	ASSERT_EQ(game.units_field[lair_x][lair_y][1], hero);
}

TEST (Game, GetDamage) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	auto enemy = game.add_to_queue(GC::light_type);
	game.balance = GC::wall_cost;
	auto wall = game.add_wall(plain_x, plain_y);
	int damage = 10;
	ASSERT_NO_THROW(game.get_damage(enemy->get_x_cord(), enemy->get_y_cord(), damage));
	ASSERT_NO_THROW(game.get_damage(wall->get_x_cord(), wall->get_y_cord(), damage));
	ASSERT_EQ(enemy->get_percent_health(),
			(double)(GC::light_max_health - damage) / GC::light_max_health);
	ASSERT_EQ(wall->get_percent_health(),
			(double)(GC::wall_max_health - damage) / GC::wall_max_health);
	damage = GC::wall_max_health;
	ASSERT_NO_THROW(game.get_damage(wall->get_x_cord(), wall->get_y_cord(), damage));
	ASSERT_EQ(wall->is_alive(), false);
	damage = GC::light_max_health;
	ASSERT_NO_THROW(game.get_damage(enemy->get_x_cord(), enemy->get_y_cord(), damage));
	ASSERT_EQ(enemy->is_alive(), false);
}

TEST (Castle, InitConstructor) {
	int x = 1;
	int y = 2;
	ASSERT_NO_THROW(GO::Castle castle(x, y, name));
	GO::Castle castle(x, y, name);
	ASSERT_EQ(castle.get_name(), name);
	ASSERT_EQ(x, castle.get_x_cord());
	ASSERT_EQ(y, castle.get_y_cord());

	int bad_level = GC::castle_max_level + 1;
	ASSERT_THROW(GO::Castle castle(x, y, name, bad_level), std::runtime_error);
}

TEST (Castle, Funcs) {
	int x = 1;
	int y = 2;
	int level = 3;
	int damage = GC::castle_chars_table[level].max_health / 2;
	int crit_damage =  GC::castle_chars_table[level].max_health;
	GO::Castle castle(x, y, name, level);
	ASSERT_EQ(castle.get_health(), GC::castle_chars_table[level].max_health);
	ASSERT_NO_THROW(castle.get_damage(damage));
	ASSERT_EQ(castle.get_health(), GC::castle_chars_table[level].max_health - damage);
	ASSERT_EQ(castle.get_percent_health(), (double)castle.get_health() / GC::castle_chars_table[level].max_health);
	ASSERT_EQ(castle.is_alive(), true);
	ASSERT_EQ(x, castle.get_x_cord());
	ASSERT_EQ(y, castle.get_y_cord());
	castle.get_damage(crit_damage);
	ASSERT_EQ(castle.is_alive(), false);
}

TEST (Castle, LevelUp) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	ASSERT_THROW(game.castle_level_up(), std::runtime_error);
	game.balance = GC::castle_chars_table[1].cost;
	ASSERT_NO_THROW(game.castle_level_up());
	ASSERT_LT(game.get_castle().get_percent_health(), 1);
}

TEST (Tower, InitConstructor) {
	int x1 = 1;
	int y1 = 2;
	ASSERT_NO_THROW(GO::Tower tower(x1, y1));
	GO::Tower tower(x1, y1);
	ASSERT_EQ(tower.get_x_cord(), x1);
	ASSERT_EQ(tower.get_y_cord(), y1);

	int x2 = 3;
	int y2 = 4;
	int level = 3;
	ASSERT_NO_THROW(GO::Tower tower2(x2, y2, level));
	GO::Tower tower2(x2, y2, level);
	ASSERT_EQ(tower2.get_x_cord(), x2);
	ASSERT_EQ(tower2.get_y_cord(), y2);

	int bad_level = GC::tower_max_level + 1;
	ASSERT_THROW(GO::Tower tower3(x2, y2, bad_level), std::runtime_error);
}


TEST (Tower, Fire) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	game.balance = GC::tower_chars_table[0].cost;
	game.add_tower(lair_x, lair_y + 1);
	auto enemy = game.add_to_queue(GC::light_type);
	double health = enemy->get_percent_health();
	while (game.counter % GC::tower_chars_table[0].recoil)
		game.tic();
	game.tic();
	ASSERT_LT(enemy->get_percent_health(), health);
}

TEST (Tower, LevelUp) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	game.balance = GC::tower_chars_table[0].cost;
	game.add_tower(lair_x, lair_y + 1);
	ASSERT_THROW(game.tower_level_up(lair_x, lair_y + 1), std::runtime_error);
	for (int i = 1; i < GC::tower_max_level; i++) {
		game.balance = GC::tower_chars_table[i].cost;
		ASSERT_NO_THROW(game.tower_level_up(lair_x, lair_y + 1));
	}
	ASSERT_THROW(game.tower_level_up(lair_x, lair_y + 1), std::runtime_error);
}

TEST (Wall, InitConstructor) {
	int x1 = 1;
	int y1 = 2;
	ASSERT_NO_THROW(GO::Wall wall(x1, y1));
	GO::Wall wall(x1, y1);
	ASSERT_EQ(wall.get_x_cord(), x1);
	ASSERT_EQ(wall.get_y_cord(), y1);
	ASSERT_EQ(wall.get_symb(), GC::wall_symb);
}

TEST (Wall, Funcs) {
	int x = 1;
	int y = 2;
	int damage = GC::wall_max_health / 2;
	int crit_damage = GC::wall_max_health;
	GO::Wall wall(x, y);
	ASSERT_NO_THROW(wall.get_damage(damage));
	ASSERT_EQ(wall.is_alive(), true);
	ASSERT_EQ(wall.get_percent_health(),
			(double)(GC::wall_max_health - damage) / GC::wall_max_health);
	wall.get_damage(crit_damage);
	ASSERT_EQ(wall.is_alive(), false);
}

TEST (Wall, Repair) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	game.balance = GC::wall_cost;
	auto wall = game.add_wall(lair_x, lair_y + 1);
	game.add_to_queue(GC::tank_type);
	game.tic();
	double health = wall->get_percent_health();
	game.balance = GC::wall_cost;
	ASSERT_THROW(game.repair_wall(lair_x, lair_y), std::runtime_error);
	game.repair_wall(lair_x, lair_y + 1);
	ASSERT_LT(health, wall->get_percent_health());

}

TEST (Lair, InitConstructor) {
	int x1 = 1;
	int y1 = 2;
	ASSERT_NO_THROW(GO::Lair lair(x1, y1));
	GO::Lair lair(x1, y1);
	ASSERT_EQ(lair.get_x_cord(), x1);
	ASSERT_EQ(lair.get_y_cord(), y1);
	ASSERT_EQ(lair.get_symb(), GC::lair_symb);
}

TEST (Lair, Funcs) {
	int x = 1;
	int y = 2;
	int time = 10;
	int type = GC::light_type;
	GO::Lair lair(x, y);
	GO::enemy_out enemy(time, type);
	ASSERT_NO_THROW(lair.add(enemy));
	ASSERT_EQ(lair.time_last_enemy(), time);
}

TEST (Landscape, InitConstuctor) {
	int size_x = 2;
	int size_y = 3;
	ASSERT_NO_THROW(GO::Landscape land(size_x, size_y));
	GO::Landscape land(size_x, size_y);
	ASSERT_EQ(land.get_x_size(), size_x);
	ASSERT_EQ(land.get_y_size(), size_y);

	int bad_size_x = -1;
	int bad_size_y = -2;
	ASSERT_THROW(GO::Landscape land(bad_size_x, size_y), std::runtime_error);
	ASSERT_THROW(GO::Landscape land(size_x, bad_size_y), std::runtime_error);
}

TEST (Landscape, Funcs) {
	GO::Landscape land;
	ASSERT_NO_THROW(land.load(pwd + testfield));
	ASSERT_EQ(land.get_x_size(), 8);
	ASSERT_EQ(land.get_y_size(), 8);
	ASSERT_EQ(land.get_main_cell(lair_x, lair_y), GC::lair_symb);
	ASSERT_EQ(land.get_main_cell(castle_x, castle_y), GC::castle_symb);
	ASSERT_EQ(land.get_main_cell(mountain_x, mountain_y), GC::mountain_symb);
	ASSERT_EQ(land.get_main_cell(river_x, river_y), GC::river_symb);
	ASSERT_EQ(land.get_main_cell(plain_x, plain_y), GC::plain_symb);
	ASSERT_EQ(land.get_cell(1, 1), land.get_main_cell(1, 1));
	land.set_cell(1, 1, GC::enemy_symb);
	ASSERT_EQ(land.get_cell(1, 1), GC::enemy_symb);
	ASSERT_NE(land.get_cell(1, 1), land.get_main_cell(1, 1));
	land.set_main_cell(1, 1, GC::enemy_symb);
	ASSERT_EQ(land.get_cell(1, 1), land.get_main_cell(1, 1));
	ASSERT_NO_THROW(land.save(pwd + testfield + "2"));
	ASSERT_NO_THROW(land.load(pwd + testfield + "2"));
}

TEST (Enemy, InitConstructor) {
	int x1 = 1;
	int y1 = 2;
	ASSERT_NO_THROW(GO::Enemy enemy(x1, y1, GC::light_type, 0));
	GO::Enemy enemy(x1, y1, GC::light_type, 0);
	ASSERT_EQ(enemy.get_symb(), GC::light_symb);
	ASSERT_EQ(enemy.get_x_cord(), x1);
	ASSERT_EQ(enemy.get_y_cord(), y1);

	int x2 = 4;
	int y2 = 5;
	ASSERT_NO_THROW(GO::Enemy enemy1(x2, y2, GC::tank_type, 1));
	GO::Enemy enemy1(x2, y2, GC::tank_type, 1);
	ASSERT_EQ(enemy1.get_symb(), GC::tank_symb);
	ASSERT_EQ(enemy1.get_x_cord(), x2);
	ASSERT_EQ(enemy1.get_y_cord(), y2);

	int x3 = 6;
	int y3 = 8;
	ASSERT_NO_THROW(GO::Enemy enemy2(x3, y3, GC::aviation_type, 2));
	GO::Enemy enemy2(x3, y3, GC::aviation_type, 2);
	ASSERT_EQ(enemy2.get_symb(), GC::aviation_symb);
	ASSERT_EQ(enemy2.get_x_cord(), x3);
	ASSERT_EQ(enemy2.get_y_cord(), y3);

	int bad_enemy_type = -2;
	ASSERT_THROW(GO::Enemy enemy3(x3, y3, bad_enemy_type, 2), std::runtime_error);
}

TEST (Enemy, Move) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	auto enemy = game.add_to_queue(GC::light_type);
	int x = enemy->get_x_cord();
	int y = enemy->get_y_cord();
	game.tic();
	ASSERT_TRUE(x != enemy->get_x_cord() || y != enemy->get_y_cord());
	x = enemy->get_x_cord();
	y = enemy->get_y_cord();
	for (int i = 0; i < GC::light_speed - 1; i++) {
		game.tic();
		ASSERT_EQ(enemy->get_x_cord(), x);
		ASSERT_EQ(enemy->get_y_cord(), y);
	}
	game.tic();
	ASSERT_TRUE(x != enemy->get_x_cord() || y != enemy->get_y_cord());
	auto light = game.add_to_queue(GC::light_type);
	auto tank = game.add_to_queue(GC::tank_type);
	auto aviation = game.add_to_queue(GC::aviation_type);
	for (int i = 0; i < 10000; i++) {
		game.tic();
		char light_cell = game.get_landscape().get_main_cell(
				light->get_x_cord(), light->get_y_cord());
		char tank_cell = game.get_landscape().get_main_cell(
				tank->get_x_cord(), tank->get_y_cord());
		char aviation_cell = game.get_landscape().get_main_cell(
				aviation->get_x_cord(), aviation->get_y_cord());
		ASSERT_TRUE(light_cell == GC::lair_symb || light_cell == GC::plain_symb);
		ASSERT_TRUE(tank_cell == GC::lair_symb || tank_cell == GC::plain_symb);
		ASSERT_TRUE(aviation_cell == GC::lair_symb || aviation_cell == GC::plain_symb
				|| aviation_cell == GC::river_symb);
	}
}

TEST (Enemy, LightAndAviationFire) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	game.balance = GC::wall_cost;
	auto wall = game.add_wall(lair_x, lair_y + 1);
	game.add_to_queue(GC::light_type);
	game.add_to_queue(GC::aviation_type);
	for (int i = 0;
			i < std::max(GC::light_speed, GC::aviation_speed) *
					game.get_landscape().get_x_size() *
					game.get_landscape().get_y_size(); i++)
		game.tic();
	int health = game.get_castle().get_health();
	for (int i = 0;
				i < std::max(GC::light_recoil, GC::aviation_recoil); i++)
			game.tic();
	ASSERT_LT(game.get_castle().get_health(), health);
	ASSERT_EQ(wall->get_percent_health(), 1);
}

TEST (Enemy, TankFire) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	game.balance = GC::wall_cost;
	auto wall = game.add_wall(lair_x, lair_y + 1);
	game.add_to_queue(GC::tank_type);
	game.tic();
	ASSERT_LT(wall->get_percent_health(), 1);
	for (int i = 0; i < GC::tank_speed *
					game.get_landscape().get_x_size() *
					game.get_landscape().get_y_size(); i++)
		game.tic();
	int health = game.get_castle().get_health();
	for (int i = 0; i < GC::tank_recoil; i++)
			game.tic();
	ASSERT_LT(game.get_castle().get_health(), health);
}

TEST (HeroEnemy, InitConstructor) {
	int x1 = 1;
	int y1 = 2;
	ASSERT_NO_THROW(GO::HeroEnemy enemy(x1, y1, GC::light_type, 0, {1, 1, 1}));
	GO::HeroEnemy enemy(x1, y1, GC::light_type, 0, {1, 1, 1});
	ASSERT_EQ(enemy.get_symb(), GC::hero_light_symb);
	ASSERT_EQ(enemy.get_x_cord(), x1);
	ASSERT_EQ(enemy.get_y_cord(), y1);

	int x2 = 4;
	int y2 = 5;
	ASSERT_NO_THROW(GO::HeroEnemy enemy1(x2, y2, GC::tank_type, 1, {1, 1, 1}));
	GO::HeroEnemy enemy1(x2, y2, GC::tank_type, 1, {1, 1, 1});
	ASSERT_EQ(enemy1.get_symb(), GC::hero_tank_symb);
	ASSERT_EQ(enemy1.get_x_cord(), x2);
	ASSERT_EQ(enemy1.get_y_cord(), y2);

	int x3 = 8;
	int y3 = 7;
	ASSERT_NO_THROW(GO::HeroEnemy enemy2(x3, y3, GC::aviation_type, 2, {1, 1, 1}));
	GO::HeroEnemy enemy2(x3, y3, GC::aviation_type, 2, {1, 1, 1});
	ASSERT_EQ(enemy2.get_symb(), GC::hero_aviation_symb);
	ASSERT_EQ(enemy2.get_x_cord(), x3);
	ASSERT_EQ(enemy2.get_y_cord(), y3);

	int bad_enemy_type = -2;
	ASSERT_THROW(GO::HeroEnemy enemy3(x3, y3, bad_enemy_type, 2, {1, 1, 1}), std::runtime_error);
}

TEST (Hero, Aura) {
	GE::Game game(name);
	game.load_landscape(pwd + testfield);
	auto enemy = game.add_to_queue(GC::light_type);
	game.tic();
	ASSERT_EQ(enemy->get_percent_health(), 1);
	game.add_to_queue(GC::light_type, {40, 40 ,40});
	game.tic();
	ASSERT_LT(enemy->get_percent_health(), 1);
}

TEST (Vector, Constructors) {
	ASSERT_NO_THROW(std::MyVector<int> vector);
	std::MyVector<int> vector;
	ASSERT_EQ(vector.size(), 0);

	int len = 3;
	ASSERT_NO_THROW(std::MyVector<int> vector2(len));
	std::MyVector<int> vector2(len);
	ASSERT_EQ(vector2.size(), len);

	int value = 1;
	ASSERT_NO_THROW(std::MyVector<int> vector3(len, value));
	std::MyVector<int> vector3(len, value);
	ASSERT_EQ(vector3.size(), len);
	for (int i = 0; i < len; i++)
		ASSERT_EQ(vector3[i], value);

	ASSERT_NO_THROW(std::MyVector<int> vector4(vector3));
	std::MyVector<int> vector4(vector3);
	ASSERT_EQ(vector4.size(), vector3.size());
	for (int i = 0; i < len; i++)
		ASSERT_EQ(vector4[i], vector3[i]);

	ASSERT_NO_THROW(std::MyVector<int> vector5(std::move(vector3)));
	vector3 = vector4;
	std::MyVector<int> vector5(std::move(vector3));
	ASSERT_EQ(vector5.size(), len);
	for (int i = 0; i < len; i++)
		ASSERT_EQ(vector5[i], value);
	ASSERT_EQ(vector3.size(), 0);
}

int tests::run_tests(int *argc, char **argv) {
	::testing::InitGoogleTest(argc, argv);

	return (RUN_ALL_TESTS());
}
