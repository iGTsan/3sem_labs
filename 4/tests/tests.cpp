#include "tests.h"
#include "../classes/vector.h"
#include "../classes/basic.h"
#include "../engine/game_engine.h"
#include <gtest/gtest.h>

namespace GE = game_engine;
namespace GC = game_consts;
namespace GO = game_objects;

TEST (Game, InitConstructor) {
	ASSERT_NO_THROW(GE::Game game("Ya"));
}

TEST (Castle, InitConstructor) {
	ASSERT_NO_THROW(GO::Castle castle(0, 0, "Ya"));
	GO::Castle castle(0, 0, "Ya");
	ASSERT_EQ(castle.get_name(), "Ya");
	ASSERT_EQ(0, castle.get_x_cord());
	ASSERT_EQ(0, castle.get_y_cord());

	ASSERT_NO_THROW(GO::Castle castle(1, 2, "NeYa"));
	GO::Castle castle2(1, 2, "NeYa", 3);
	ASSERT_EQ(castle2.get_name(), "NeYa");
	ASSERT_EQ(1, castle2.get_x_cord());
	ASSERT_EQ(2, castle2.get_y_cord());
}

TEST (Castle, CastleFuncs) {
	GO::Castle castle(1, 2, "Ya", 2);
	ASSERT_EQ(castle.get_health(), GC::castle_chars_table[2].max_health);
	ASSERT_NO_THROW(castle.get_damage(30));
	ASSERT_EQ(castle.get_health(), GC::castle_chars_table[2].max_health - 30);
	ASSERT_EQ(castle.get_percent_health(), (double)castle.get_health() / GC::castle_chars_table[2].max_health);
	ASSERT_EQ(castle.is_alive(), 1);
	ASSERT_EQ(1, castle.get_x_cord());
	ASSERT_EQ(2, castle.get_y_cord());
}

TEST (Tower, InitConstructor) {
	ASSERT_NO_THROW(GO::Tower tower(1, 2));
	GO::Tower tower(1, 2);
	ASSERT_EQ(tower.get_x_cord(), 1);
	ASSERT_EQ(tower.get_y_cord(), 2);
	ASSERT_NO_THROW(GO::Tower tower2(2, 1, 3));
	GO::Tower tower2(2, 1, 3);
	ASSERT_EQ(tower2.get_x_cord(), 2);
	ASSERT_EQ(tower2.get_y_cord(), 1);
}

TEST (Wall, InitConstructor) {
	ASSERT_NO_THROW(GO::Wall wall(1, 2));
	GO::Wall wall(1, 2);
	ASSERT_EQ(wall.get_x_cord(), 1);
	ASSERT_EQ(wall.get_y_cord(), 2);
	ASSERT_EQ(wall.get_symb(), GC::wall_symb);
}

TEST (Lair, InitConstructor) {
	ASSERT_NO_THROW(GO::Lair lair(1, 2));
	GO::Lair lair(1, 2);
	ASSERT_EQ(lair.get_x_cord(), 1);
	ASSERT_EQ(lair.get_y_cord(), 2);
	ASSERT_EQ(lair.get_symb(), GC::lair_symb);
}

TEST (Landscape, InitConstuctor) {
	ASSERT_NO_THROW(GO::Landscape land(2, 3));
	GO::Landscape land(2, 3);
	ASSERT_EQ(land.get_x_size(), 2);
	ASSERT_EQ(land.get_y_size(), 3);
}

TEST (Enemy, InitConstructor) {
	ASSERT_NO_THROW(GO::Enemy enemy(1, 2, GC::light_type, 0));
	GO::Enemy enemy(1, 2, GC::light_type, 0);
	ASSERT_EQ(enemy.get_symb(), GC::light_symb);
	ASSERT_EQ(enemy.get_x_cord(), 1);
	ASSERT_EQ(enemy.get_y_cord(), 2);
	ASSERT_NO_THROW(GO::Enemy enemy1(3, 4, GC::tank_type, 1));
	GO::Enemy enemy1(3, 4, GC::tank_type, 1);
	ASSERT_EQ(enemy1.get_symb(), GC::tank_symb);
	ASSERT_EQ(enemy1.get_x_cord(), 3);
	ASSERT_EQ(enemy1.get_y_cord(), 4);
	ASSERT_NO_THROW(GO::Enemy enemy2(5, 6, GC::aviation_type, 2));
	GO::Enemy enemy2(5, 6, GC::aviation_type, 2);
	ASSERT_EQ(enemy2.get_symb(), GC::aviation_symb);
	ASSERT_EQ(enemy2.get_x_cord(), 5);
	ASSERT_EQ(enemy2.get_y_cord(), 6);
}

TEST (HeroEnemy, InitConstructor) {
	ASSERT_NO_THROW(GO::HeroEnemy enemy(1, 2, GC::light_type, 0, {1, 1, 1}));
	GO::HeroEnemy enemy(1, 2, GC::light_type, 0, {1, 1, 1});
	ASSERT_EQ(enemy.get_symb(), GC::hero_light_symb);
	ASSERT_EQ(enemy.get_x_cord(), 1);
	ASSERT_EQ(enemy.get_y_cord(), 2);
	ASSERT_NO_THROW(GO::HeroEnemy enemy1(3, 4, GC::tank_type, 1, {1, 1, 1}));
	GO::HeroEnemy enemy1(3, 4, GC::tank_type, 1, {1, 1, 1});
	ASSERT_EQ(enemy1.get_symb(), GC::hero_tank_symb);
	ASSERT_EQ(enemy1.get_x_cord(), 3);
	ASSERT_EQ(enemy1.get_y_cord(), 4);
	ASSERT_NO_THROW(GO::HeroEnemy enemy2(5, 6, GC::aviation_type, 2, {1, 1, 1}));
	GO::HeroEnemy enemy2(5, 6, GC::aviation_type, 2, {1, 1, 1});
	ASSERT_EQ(enemy2.get_symb(), GC::hero_aviation_symb);
	ASSERT_EQ(enemy2.get_x_cord(), 5);
	ASSERT_EQ(enemy2.get_y_cord(), 6);
}



int tests::run_tests(int *argc, char **argv) {
	::testing::InitGoogleTest(argc, argv);

	return (RUN_ALL_TESTS());
}
