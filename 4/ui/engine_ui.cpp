#include "game_engine_ui.h"
#include "engine_ui.h"

using namespace ui_consts;

void engine_ui::StartMenu::play(const std::string& player_name, const std::string& level) {
	GE::Game game(player_name);
	try {
		game.load_landscape(way_to_levels + level);
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		return;
	}
	window.close();
	game.add_enemy(GC::tank_type, {40, 40, 40}, 1);
	for (int i = 0; i < 15; i++) {
		game.add_random_enemy();
	}

	GameWindow window(game);

	while (window.get_window().isOpen())
	{
		sf::Event event;
		while (window.get_window().pollEvent(event))
		{
			window.do_event(game, event);
		}
		window.show(game);
		if (window.is_ready()) {
			game.tic();
			game.counter++;
		}

	}
}

engine_ui::StartMenu::StartMenu() {
	size_x = start_menu_width;
	size_y = start_menu_height;
	old_size_x = size_x;
	old_size_y = size_y;
	window.create(sf::VideoMode(size_x, size_y), "Menu");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(frametime);
	size_x = old_size_x;
	size_y = old_size_y;

	buttons.push_back(new sf_my::Button((size_x - menu_size) / 2,
			size_y / 2 - stat_size * 1.7, menu_size, stat_size, button_start_game));
	buttons[0]->set_text("Start game");
	buttons.push_back(new sf_my::Button((size_x - menu_size) / 2,
			(size_y - stat_size) / 2, menu_size, stat_size, button_level_editor));
	buttons[1]->set_text("Level editor");
	buttons.push_back(new sf_my::Button((size_x - menu_size) / 2,
			size_y / 2 + stat_size * 0.7, menu_size, stat_size, button_exit));
	buttons[2]->set_text("Exit");

	next.set_size(menu_size, stat_size);
	next.set_pos((size_x - menu_size) / 2 + menu_size + stat_size, (size_y - stat_size) / 2);
	next.set_text("Next");

	name.set_pos((size_x - menu_size) / 2, size_y / 2 - stat_size * 1.2);
	name.set_size(menu_size, stat_size);
	name_text.setPosition((size_x - menu_size) / 2 - menu_size, size_y / 2 - stat_size * 1.2);
	name_text.setFont(fonts.beauty_font);
	name_text.setFillColor(font_color);
	name_text.setCharacterSize(stat_size);
	name_text.setString("Your name:");
	level.set_pos((size_x - menu_size) / 2, size_y / 2 + stat_size * 0.2);
	level.set_size(menu_size, stat_size);
	level_text.setPosition((size_x - menu_size) / 2 - menu_size, size_y / 2 + stat_size * 0.2);
	level_text.setFont(fonts.beauty_font);
	level_text.setFillColor(font_color);
	level_text.setCharacterSize(stat_size);
	level_text.setString("Level:");
}

void engine_ui::StartMenu::do_event(sf::Event &event) {
	if (event.type == sf::Event::Closed)
		window.close();
	if (event.type == sf::Event::MouseButtonPressed)
		mouse_pressed(event);
	if (event.type == sf::Event::MouseMoved)
		mouse_moved(event);
	if (event.type == sf::Event::Resized)
		resized(event);
	if (event.type == sf::Event::KeyPressed)
		key_pressed(event);
}

void engine_ui::StartMenu::loop() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			do_event(event);
		}
		show();
	}
}

void engine_ui::StartMenu::show() {
	window.clear(background_color);
	switch (state) {
	case 0:
		for (auto button: buttons)
			button->show(window);
		break;
	case 1:
		name.show(window);
		level.show(window);
		next.show(window);
		window.draw(name_text);
		window.draw(level_text);
		break;
	case 2:
		level.show(window);
		next.show(window);
		window.draw(level_text);
		break;
	}
	window.display();
}

void engine_ui::StartMenu::mouse_moved(sf::Event &event) {
	int x = event.mouseMove.x * old_size_x / size_x;
	int y = event.mouseMove.y * old_size_y / size_y;
	switch (state) {
	case 0:
		for (auto button: buttons)
			button->is_active(x, y);
		break;
	case 1:
		name.is_active(x, y);
		level.is_active(x, y);
		next.is_active(x, y);
		break;
	case 2:
		level.is_active(x, y);
		next.is_active(x, y);
		break;
	}
}

void engine_ui::StartMenu::mouse_pressed(sf::Event &event) {
	int x = event.mouseButton.x * old_size_x / size_x;
	int y = event.mouseButton.y * old_size_y / size_y;
	switch (state) {
	case 0:
		for (auto button: buttons)
			switch (button->is_clicked(x, y)) {
			case button_start_game:
				state = 1;
				break;
			case button_level_editor:
				state = 2;
				break;
			case button_exit:
				window.close();
				return;
			}
		break;
	case 1:
		name.is_clicked(x, y);
		level.is_clicked(x, y);
		if (next.is_clicked(x, y))
			play(name.get_text(), level.get_text());
		break;
	case 2:
		level.is_clicked(x, y);
		break;
	}
}

void engine_ui::StartMenu::resized(sf::Event &event) {
	size_x = event.size.width;
	size_y = event.size.height;
}

void engine_ui::StartMenu::key_pressed(sf::Event &event) {
	if (state != 0) {
		name.button_pressed(event.key.code);
		level.button_pressed(event.key.code);
	}
}

engine_ui::StartMenu::~StartMenu() {
	for (auto button: buttons)
		delete button;
}
