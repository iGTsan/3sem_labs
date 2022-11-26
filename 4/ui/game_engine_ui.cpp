#include "game_engine_ui.h"

using namespace ui_consts;
namespace GC = game_consts;

void engine_ui::GameWindow::show_field(GE::Game &game) {
	for (int i = 0; i < game.get_landscape().get_x_size(); i++)
		for (int j = 0; j < game.get_landscape().get_y_size(); j++) {
			switch (game.get_landscape().get_main_cell(i, j)) {
			case (GC::plain_symb):
				sprites.grass_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.grass_sprite.get_sprite());
				break;
			case (GC::mountain_symb):
				sprites.mountain_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.mountain_sprite.get_sprite());
				break;
			case (GC::river_symb):
				sprites.river_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.river_sprite.get_sprite());
				break;
			case (GC::castle_symb):
				sprites.plain_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.plain_sprite.get_sprite());
				sprites.castle_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.castle_sprite.get_sprite());
				break;
			case (GC::lair_symb):
				sprites.lair_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.lair_sprite.get_sprite());
				break;
			}
			button_field[i][j].show(window);
		}
}

void engine_ui::GameWindow::show_units(GE::Game &game) {
	sf::RectangleShape health_back;
	sf::RectangleShape health_front;
	health_back.setFillColor(health_back_color);
	health_back.setSize(sf::Vector2f(cell_size - 2, 4));
	health_front.setFillColor(sf::Color::Green);
	for (int i = 0; i < game.get_landscape().get_x_size(); i++)
		for (int j = 0; j < game.get_landscape().get_y_size(); j++) {
			auto unit_cell = game.units_field[i][j];
			auto tower_cell = game.towers_field[i][j];
			for (auto unit: unit_cell) {
				switch (unit->get_symb()) {
				case (GC::tank_symb):
					sprites.tank_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
					window.draw(sprites.tank_sprite.get_sprite());
					break;
				case (GC::light_symb):
					sprites.light_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
					window.draw(sprites.light_sprite.get_sprite());
					break;
				case (GC::aviation_symb):
					sprites.aviation_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
					window.draw(sprites.aviation_sprite.get_sprite());
					break;
				case (GC::hero_tank_symb):
					sprites.hero_tank_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
					window.draw(sprites.hero_tank_sprite.get_sprite());
					break;
				case (GC::hero_light_symb):
					sprites.hero_light_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
					window.draw(sprites.hero_light_sprite.get_sprite());
					break;
				case (GC::hero_aviation_symb):
					sprites.hero_aviation_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
					window.draw(sprites.hero_aviation_sprite.get_sprite());
					break;
				case (GC::wall_symb):
					sprites.wall_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
					window.draw(sprites.wall_sprite.get_sprite());
					break;
				}
				if (unit->get_percent_health() != 1) {
					health_front.setSize(sf::Vector2f((cell_size - 2) * unit->get_percent_health(), 4));
					health_front.setPosition(i * cell_size + 1, (j + 1) * cell_size - 1);
					health_back.setPosition(health_front.getPosition());
					window.draw(health_back);
					window.draw(health_front);
				}
			}
			if (tower_cell != nullptr) {
				sprites.tower_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.tower_sprite.get_sprite());
			}
		}
	sf::Text end;
	end.setFont(fonts.beauty_font);
	end.setPosition(10, old_size_y / 2);
	end.setFillColor(sf::Color::Red);
	end.setCharacterSize(cell_size * 3);
	if (game.is_end() == 1)
		end.setString("You win");
	if (game.is_end() == -1)
		end.setString("You lose");
	window.draw(end);
}

engine_ui::GameWindow::GameWindow(GE::Game &game) :
		counter(0), max_counter(speed2) {
	size_x = game.get_landscape().get_x_size() * cell_size + menu_size + 4;
	size_y = game.get_landscape().get_y_size() * cell_size + stat_size * 3 + 2;
	old_size_x = size_x;
	old_size_y = size_y;
	window.create(sf::VideoMode(size_x, size_y), "Game");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(frametime);
	size_x = old_size_x;
	size_y = old_size_y;

	castle_health.setCharacterSize(stat_size);
	castle_health.setPosition(sf::Vector2f(10, game.get_landscape().get_y_size() * cell_size ));
	castle_health.setFont(fonts.beauty_font);
	balance.setCharacterSize(stat_size);
	balance.setPosition(sf::Vector2f(10, game.get_landscape().get_y_size() * cell_size + stat_size));
	balance.setFont(fonts.beauty_font);
	info.setCharacterSize(stat_size);
	info.setPosition(sf::Vector2f(10, game.get_landscape().get_y_size() * cell_size + stat_size * 2));
	info.setFont(fonts.beauty_font);
	info.setFillColor(sf::Color::Red);

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

void engine_ui::GameWindow::show_stats(GE::Game &game) {
	castle_health.setString(UC::castle_health + std::to_string(game.get_castle().get_health()));
	balance.setString(UC::balance + std::to_string(game.balance));
	window.draw(castle_health);
	window.draw(balance);
	window.draw(info);
}

void engine_ui::GameWindow::show_menu(GE::Game &game) {
	if (menu)
		menu->show(window);
	speed.show(window);
}

void engine_ui::GameWindow::do_event(GE::Game &game, sf::Event &event) {
	if (event.type == sf::Event::Closed)
		window.close();
	if (event.type == sf::Event::MouseButtonPressed)
		mouse_pressed(game, event);
	if (event.type == sf::Event::MouseMoved)
		mouse_moved(game, event);
	if (event.type == sf::Event::Resized)
		resized(event);

}

void engine_ui::GameWindow::mouse_pressed(GE::Game &game, sf::Event& event) {
	int x = event.mouseButton.x * old_size_x / size_x;
	int y = event.mouseButton.y * old_size_y / size_y;
	for (int i = 0; i < static_cast<int>(button_field.size()); i++)
		for (int j = 0; j < static_cast<int>(button_field[i].size()); j++)
			if (button_field[i][j].is_clicked(x, y)) {
				menu = &field_menu;
				menu->set_pos(i, j);
			}
	if (menu)
		try {
		switch (menu->is_clicked(x, y)) {
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
			game.repair_wall(menu->get_x_pos(), menu->get_y_pos());
			break;
		}} catch (std::runtime_error& e) {
			info.setString(e.what());
			}
	switch (speed.is_clicked(x, y)) {
	case (button_speed1):
		max_counter = speed1;
		break;
	case (button_speed2):
		max_counter = speed2;
		break;
	case (button_speed3):
		max_counter = speed3;
		break;
	}
}

void engine_ui::GameWindow::mouse_moved(GE::Game &game, sf::Event &event) {
	int x = event.mouseMove.x * old_size_x / size_x;
	int y = event.mouseMove.y * old_size_y / size_y;
	for (int i = 0; i < static_cast<int>(button_field.size()); i++)
		for (int j = 0; j < static_cast<int>(button_field[i].size()); j++)
			button_field[i][j].is_active(x, y);
	if (menu)
		menu->is_active(x, y);
	speed.is_active(x, y);
}

engine_ui::FieldMenu::FieldMenu(int x_shift, int x_pos, int y_pos, int size) :
	MenuPart(x_shift, x_pos, y_pos, size) {

	buttons.push_back(new sf_my::Button(x_shift, 1, size, stat_size - 1, button_place_tower));
	buttons[0]->set_text("Buy tower");
	buttons.push_back(new sf_my::Button(x_shift, stat_size, size, stat_size - 1, button_level_up_tower));
	buttons[1]->set_text("Tower level up");
	buttons.push_back(new sf_my::Button(x_shift, stat_size * 2, size, stat_size - 1, button_place_wall));
	buttons[2]->set_text("Buy wall");
	buttons.push_back(new sf_my::Button(x_shift, stat_size * 3, size, stat_size - 1, button_repair_wall));
	buttons[3]->set_text("Repair wall");
	buttons.push_back(new sf_my::Button(x_shift, stat_size * 4, size, stat_size - 1, button_level_up_castle));
	buttons[4]->set_text("Castle level up");
}

void engine_ui::GameWindow::resized(sf::Event& event) {
	size_x = event.size.width;
	size_y = event.size.height;
}

bool engine_ui::GameWindow::is_ready() {
	if (counter >= max_counter) {
		counter = 0;
		return (1);
	}
	counter++;
	return (0);
}
