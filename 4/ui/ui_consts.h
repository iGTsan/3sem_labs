/** \file
 * \brief Файл со всеми графическими константами
 */

#ifndef UI_UI_CONSTS_H_
#define UI_UI_CONSTS_H_

#include <SFML/Graphics.hpp>

namespace ui_consts {
	constexpr int cell_size = 32;
	constexpr int menu_size = 200;
	constexpr int stat_size = 30;
	constexpr int fields_max_len = 100;

	constexpr int start_menu_width = 640;
	constexpr int start_menu_height = 480;

	constexpr int button_place_tower = 1;
	constexpr int button_place_wall = 2;
	constexpr int button_level_up_tower = 3;
	constexpr int button_level_up_castle = 4;
	constexpr int button_repair_wall = 5;

	constexpr int button_start_game = 1;
	constexpr int button_level_editor = 2;
	constexpr int button_exit = 3;

	constexpr int button_speed1 = 1;
	constexpr int button_speed2 = 2;
	constexpr int button_speed3 = 3;
	constexpr int speed1 = 7;
	constexpr int speed2 = 3;
	constexpr int speed3 = 1;

	constexpr int frametime = 60;

	const std::string way_to_recourses = "/home/ya/infa/3 sem/lab/4/recourses/";
	const std::string default_font = way_to_recourses + "OpenSans-Regular.ttf";
	const std::string beauty_font = way_to_recourses + "ZakwanOebit.ttf";
	const std::string tower_png = way_to_recourses + "tower.png";
	const std::string plain_png = way_to_recourses + "plain.png";
	const std::string mountain_png = way_to_recourses + "mountain.png";
	const std::string river_png = way_to_recourses + "river.png";
	const std::string grass_png = way_to_recourses + "grass.png";
	const std::string castle_png = way_to_recourses + "castle.png";
	const std::string lair_png = way_to_recourses + "lair.png";
	const std::string tank_png = way_to_recourses + "tank.png";
	const std::string light_png = way_to_recourses + "light.png";
	const std::string aviation_png = way_to_recourses + "aviation.png";
	const std::string hero_tank_png = way_to_recourses + "hero_tank.png";
	const std::string hero_light_png = way_to_recourses + "hero_light.png";
	const std::string hero_aviation_png = way_to_recourses + "hero_aviation.png";
	const std::string wall_png = way_to_recourses + "wall.png";

	const std::string way_to_levels = "/home/ya/infa/3 sem/lab/4/levels/";

	const std::string castle_health = "Castle health: ";
	const std::string balance = "Balance: ";

	const sf::Color background_color = sf::Color(58, 114, 120);
	const sf::Color button_color = sf::Color(0, 225, 255);
	const sf::Color font_color = sf::Color(67, 95, 99);
	const sf::Color bourder_color = sf::Color(29, 42, 43);
	const sf::Color health_back_color = sf::Color(128, 128, 128);

}



#endif
