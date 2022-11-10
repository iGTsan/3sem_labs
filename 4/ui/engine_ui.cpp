#include "engine_ui.h"
#include "../classes/consts.h"

using namespace ui_consts;
namespace GC = game_consts;

void engine_ui::MainWindow::show_field(GE::Game &game) {
	for (int i = 0; i < game.get_landscape().get_x_size(); i++)
		for (int j = 0; j < game.get_landscape().get_y_size(); j++) {
			sf::RectangleShape sprite;
			sprite.setPosition(i * cell_size, j * cell_size);
			sprite.setSize(sf::Vector2f(cell_size, cell_size));
			switch (game.get_landscape().get_main_cell(i, j)) {
			case (GC::plain_symb):
				sprite.setFillColor(sf::Color::Yellow);
				break;
			case (GC::mountain_symb):
				sprite.setFillColor(sf::Color::Black);
				break;
			case (GC::river_symb):
				sprite.setFillColor(sf::Color::Blue);
				break;
			case (GC::castle_symb):
				sprite.setFillColor(sf::Color::Magenta);
				break;
			case (GC::lair_symb):
				sprite.setFillColor(sf::Color::Magenta);
				break;
			}
			window.draw(sprite);
			button_field[i][j].show(window);
		}
}

void engine_ui::MainWindow::show_units(GE::Game &game) {
	sf::CircleShape enemy_sprite;
	enemy_sprite.setPointCount(3);
	enemy_sprite.setRadius(cell_size / 2);
	enemy_sprite.setFillColor(sf::Color::Red);
	sf::CircleShape tower_sprite;
	tower_sprite.setPointCount(4);
	tower_sprite.setRadius(cell_size / 2);
	tower_sprite.setFillColor(sf::Color::Green);
	sf::RectangleShape wall_sprite;
	wall_sprite.setSize(sf::Vector2f(cell_size - 2, cell_size - 2));
	wall_sprite.setFillColor(sf::Color::Red);
	for (int i = 0; i < game.get_landscape().get_x_size(); i++)
		for (int j = 0; j < game.get_landscape().get_y_size(); j++) {
			auto unit_cell = game.units_field[i][j];
			auto tower_cell = game.towers_field[i][j];
			for (auto unit: unit_cell)
				switch (unit->get_symb()) {
				case (GC::enemy_symb):
					enemy_sprite.setPosition(i * cell_size, j * cell_size);
					window.draw(enemy_sprite);
					break;
				case (GC::wall_symb):
					wall_sprite.setPosition(i * cell_size + 1, j * cell_size + 1);
					window.draw(wall_sprite);
					break;
				}
			if (tower_cell != nullptr) {
				tower_sprite.setPosition(i * cell_size, j * cell_size);
				window.draw(tower_sprite);
			}
		}
}

engine_ui::MainWindow::MainWindow(GE::Game &game) {
	window.create(sf::VideoMode(game.get_landscape().get_x_size() * cell_size + menu_size + 4,
				game.get_landscape().get_y_size() * cell_size + stat_size * 3 + 2), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	font.loadFromFile(UC::beauty_font);
	font2.loadFromFile(UC::default_font);
	castle_health.setCharacterSize(stat_size);
	castle_health.setPosition(sf::Vector2f(10, game.get_landscape().get_y_size() * cell_size ));
	castle_health.setFont(font);
	balance.setCharacterSize(stat_size);
	balance.setPosition(sf::Vector2f(10, game.get_landscape().get_y_size() * cell_size + stat_size));
	balance.setFont(font);
	info.setCharacterSize(stat_size);
	info.setPosition(sf::Vector2f(10, game.get_landscape().get_y_size() * cell_size + stat_size * 2));
	info.setFont(font2);
	info.setFillColor(sf::Color::Red);

	castle_menu.set_shift(game.get_landscape().get_x_size() * cell_size + 2);
	castle_menu.set_size(menu_size);
	tower_menu.set_shift(game.get_landscape().get_x_size() * cell_size + 2);
	tower_menu.set_size(menu_size);
	field_menu.set_shift(game.get_landscape().get_x_size() * cell_size + 2);
	field_menu.set_size(menu_size);

	button_field.resize(game.get_landscape().get_x_size());
	for (int i = 0; i < static_cast<int>(button_field.size()); i++) {
		button_field[i].resize(game.get_landscape().get_y_size());
		for (int j = 0; j < static_cast<int>(button_field[i].size()); j++) {
			button_field[i][j].set_size(cell_size, cell_size);
			button_field[i][j].set_pos(i * cell_size, j * cell_size);
			button_field[i][j].set_back_color(sf::Color::Transparent);
			button_field[i][j].set_outline_color(sf::Color::Transparent);
		}
	}

	speed.add_button(button_speed1, "Speed 1");
	speed.add_button(button_speed2, "Speed 2");
	speed.add_button(button_speed3, "Speed 3");
	speed.set_pos(game.get_landscape().get_x_size() * cell_size + 5,
			game.get_landscape().get_y_size() * cell_size - stat_size);
	speed.set_size(menu_size, stat_size);
}

void engine_ui::MainWindow::show_stats(GE::Game &game) {
	castle_health.setString(UC::castle_health + std::to_string(game.get_castle().get_health()));
	balance.setString(UC::balance + std::to_string(game.balance));
	window.draw(castle_health);
	window.draw(balance);
	window.draw(info);
}

void engine_ui::MainWindow::show_menu(GE::Game &game) {
	if (menu)
		menu->show(window);
	speed.show(window);
}

void engine_ui::MainWindow::do_event(GE::Game &game, sf::Event &event) {
	if (event.type == sf::Event::Closed)
		window.close();
	if (event.type == sf::Event::MouseButtonPressed)
		mouse_pressed(game, event);
	if (event.type == sf::Event::MouseMoved)
		mouse_moved(game, event);
}

void engine_ui::MainWindow::mouse_pressed(GE::Game &game, sf::Event& event) {
	for (int i = 0; i < static_cast<int>(button_field.size()); i++)
		for (int j = 0; j < static_cast<int>(button_field[i].size()); j++)
			if (button_field[i][j].is_clicked(event.mouseButton.x, event.mouseButton.y)) {
				menu = &field_menu;
				menu->set_pos(i, j);
			}
	if (menu)
		try {
		switch (menu->is_clicked(event.mouseButton.x, event.mouseButton.y)) {
		case UC::button_level_up_castle:
			game.castle_level_up();
			break;
		case UC::button_level_up_tower:
			game.tower_level_up(menu->get_x_pos(), menu->get_y_pos());
			break;
		case UC::button_place_tower:
			game.add_tower(menu->get_x_pos(), menu->get_y_pos());
			break;
		case UC::button_place_wall:
			game.add_wall(menu->get_x_pos(), menu->get_y_pos());
			break;
		case UC::button_repair_wall:
//			game.;
			break;
		}} catch (std::runtime_error& e) {
			info.setString(e.what());
			}
	switch (speed.is_clicked(event.mouseButton.x, event.mouseButton.y)) {
	case (button_speed1):
		window.setFramerateLimit(10);
		break;
	case (button_speed2):
		window.setFramerateLimit(30);
		break;
	case (button_speed3):
		window.setFramerateLimit(60);
		break;
	}
}

void engine_ui::MainWindow::mouse_moved(GE::Game &game, sf::Event &event) {
	for (int i = 0; i < static_cast<int>(button_field.size()); i++)
		for (int j = 0; j < static_cast<int>(button_field[i].size()); j++)
			button_field[i][j].is_active(event.mouseMove.x, event.mouseMove.y);
	if (menu)
		menu->is_active(event.mouseMove.x, event.mouseMove.y);
}

engine_ui::TowerMenu::TowerMenu(int x_shift, int x_pos, int y_pos, int size) :
	MenuPart(x_shift, x_pos, y_pos, size) {
	buttons.push_back(new sf_my::Button(x_shift, 1, size, stat_size, button_level_up_tower));
	buttons[0]->set_text("Level up");
}

engine_ui::FieldMenu::FieldMenu(int x_shift, int x_pos, int y_pos, int size) :
	MenuPart(x_shift, x_pos, y_pos, size) {
	;
	buttons.push_back(new sf_my::Button(x_shift, 1, size, stat_size, button_place_tower));
	buttons[0]->set_text("Buy tower");
	buttons.push_back(new sf_my::Button(x_shift, stat_size + 2, size, stat_size, button_place_wall));
	buttons[1]->set_text("Buy wall");
	buttons.push_back(new sf_my::Button(x_shift, 2 * stat_size + 2, size, stat_size, button_repair_wall));
	buttons[2]->set_text("Repair wall");
}

engine_ui::CastleMenu::CastleMenu(int x_shift, int x_pos, int y_pos, int size) :
	MenuPart(x_shift, x_pos, y_pos, size) {
	buttons.push_back(new sf_my::Button(x_shift, 1, size, stat_size, button_level_up_castle));
	buttons[0]->set_text("Level up");
}
/*
 * engine_ui.cpp
 *
 *  Created on: 8 нояб. 2022 г.
 *      Author: ya
 */




