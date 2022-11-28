#include "editor_engine_ui.h"
#include "ui_consts.h"
#include "../classes/consts.h"
#include <stdexcept>

using namespace ui_consts;
namespace GC = game_consts;

engine_ui::EditorMenu::EditorMenu(int x_shift, int x_pos, int y_pos, int size) :
	MenuPart(x_shift, x_pos, y_pos, size){
	buttons.push_back(new sf_my::Button(x_shift, 1, size, stat_size - 1, button_plain));
	buttons[0]->set_text("Plain");
	buttons.push_back(new sf_my::Button(x_shift, stat_size, size, stat_size - 1, button_mountain));
	buttons[1]->set_text("Mountain");
	buttons.push_back(new sf_my::Button(x_shift, stat_size * 2, size, stat_size - 1, button_river));
	buttons[2]->set_text("River");
	buttons.push_back(new sf_my::Button(x_shift, stat_size * 3, size, stat_size - 1, button_castle));
	buttons[3]->set_text("Castle");
	buttons.push_back(new sf_my::Button(x_shift, stat_size * 4, size, stat_size - 1, button_lair));
	buttons[4]->set_text("Lair");
}

void engine_ui::EditorWindow::show() {
	window.clear(background_color);
	show_field();
	if (menuptr)
		menuptr->show(window);
	buttons_field.show(window);
	expand_x_btn.show(window);
	expand_y_btn.show(window);
	save_btn.show(window);
	window.display();
}

void engine_ui::EditorWindow::do_event(sf::Event &event) {
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

void engine_ui::EditorWindow::mouse_moved(sf::Event &event) {
	int x = event.mouseMove.x * old_size_x / size_x;
	int y = event.mouseMove.y * old_size_y / size_y;
	buttons_field.is_active(x, y);
	expand_x_btn.is_active(x, y);
	expand_y_btn.is_active(x, y);
	menu.is_active(x, y);
	save_btn.is_active(x, y);
}

void engine_ui::EditorWindow::mouse_pressed(sf::Event &event) {
	int x = event.mouseButton.x * old_size_x / size_x;
	int y = event.mouseButton.y * old_size_y / size_y;
	int i;
	int j;
	if (buttons_field.is_clicked(x, y, i, j)) {
		menuptr = &menu;
		menuptr->set_pos(i, j);
	}
	if (menuptr)
		switch (menuptr->is_clicked(x, y)) {
		case button_castle:
			set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::castle_symb);
			break;
		case button_lair:
			set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::lair_symb);
			break;
		case button_plain:
			set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::plain_symb);
			break;
		case button_mountain:
			set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::mountain_symb);
			break;
		case button_river:
			set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::river_symb);
			break;
		}
	if (expand_x_btn.is_clicked(x, y))
		expand(1, 0);
	if (expand_y_btn.is_clicked(x, y))
		expand(0, 1);
	if (save_btn.is_clicked(x, y)) {
		try {
			save(way_to_levels + filename);
			window.close();
		} catch (std::runtime_error& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void engine_ui::EditorWindow::expand(int x, int y) {
	if (x) {
		set_size(get_x_size() + 1, get_y_size());
		if (get_x_size() * cell_size + 2 * cell_size + menu_size > size_x) {
			old_size_x += cell_size;
			window.create(sf::VideoMode(old_size_x, old_size_y), "Editor");
			size_x = old_size_x;
			size_y = old_size_y;
		}
	}
	if (y) {
		set_size(get_x_size(), get_y_size() + 1);
		if (get_y_size() * cell_size + cell_size * 3 / 2 > size_y) {
			old_size_y += cell_size;
			window.create(sf::VideoMode(old_size_x, old_size_y), "Editor");
			size_x = old_size_x;
			size_y = old_size_y;
		}
	}
	expand_x_btn.set_pos(get_x_size() * cell_size + cell_size / 2
			, (get_y_size() - 1) * cell_size / 2);
	expand_y_btn.set_pos((get_x_size() - 1) * cell_size / 2
			, get_y_size() * cell_size + cell_size / 2);
	buttons_field.set_size(get_x_size(), get_y_size());
	save_btn.set_pos(get_x_size() * cell_size + 2 * cell_size,
			std::max(stat_size * 5 + 6, get_y_size() * cell_size + cell_size / 2));
	menu.set_shift(get_x_size() * cell_size + 2 * cell_size);
}

engine_ui::EditorWindow::EditorWindow(const std::string &filename) :
		filename(filename) {
	try {
		load(way_to_levels + filename);
	}
	catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}

	size_x = std::max(start_menu_width, get_x_size() * cell_size + 2 * cell_size + menu_size);
	size_y = std::max(start_menu_height, get_y_size() * cell_size + cell_size * 3 / 2 );
	old_size_x = size_x;
	old_size_y = size_y;
	window.create(sf::VideoMode(size_x, size_y), "Editor");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(frametime);
	size_x = old_size_x;
	size_y = old_size_y;

	menu.set_size(menu_size);
	expand_x_btn.set_text("+");
	expand_y_btn.set_text("+");
	expand_x_btn.set_size(cell_size, cell_size);
	expand_y_btn.set_size(cell_size, cell_size);
	save_btn.set_size(menu_size, stat_size - 1);
	save_btn.set_text("Save field");

	expand(0, 0);
}

void engine_ui::EditorWindow::show_field() {
	for (int i = 0; i < get_x_size(); i++)
		for (int j = 0; j < get_y_size(); j++) {
			switch (get_cell(i, j)) {
			case GC::plain_symb:
				sprites.grass_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.grass_sprite.get_sprite());
				break;
			case GC::river_symb:
				sprites.river_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.river_sprite.get_sprite());
				break;
			case GC::mountain_symb:
				sprites.mountain_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.mountain_sprite.get_sprite());
				break;
			case GC::castle_symb:
				sprites.grass_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.grass_sprite.get_sprite());
				sprites.castle_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.castle_sprite.get_sprite());
				break;
			case GC::lair_symb:
				sprites.lair_sprite.get_sprite().setPosition(i * cell_size, j * cell_size);
				window.draw(sprites.lair_sprite.get_sprite());
				break;
			}
		}
}

void engine_ui::EditorWindow::resized(sf::Event &event) {
	size_x = event.size.width;
	size_y = event.size.height;
}

void engine_ui::EditorWindow::key_pressed(sf::Event &event) {
	switch (event.key.code) {
	case sf::Keyboard::Key::P:
		set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::plain_symb);
		break;
	case sf::Keyboard::Key::C:
		set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::castle_symb);
		break;
	case sf::Keyboard::Key::L:
		set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::lair_symb);
		break;
	case sf::Keyboard::Key::M:
		set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::mountain_symb);
		break;
	case sf::Keyboard::Key::R:
		set_cell(menuptr->get_x_pos(), menuptr->get_y_pos(), GC::river_symb);
		break;
	case sf::Keyboard::Key::Y:
		expand(0, 1);
		break;
	case sf::Keyboard::Key::X:
		expand(1, 0);
		break;
	default:
		break;
	}
}

void engine_ui::EditorWindow::loop() {
	while (window.isOpen()) {
		sf::Event event;
			while (window.pollEvent(event))
			{
				do_event(event);
			}
		show();
	}
}
