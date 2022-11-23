#ifndef UI_GAME_ENGINE_UI_H_
#define UI_GAME_ENGINE_UI_H_

#include <SFML/Graphics.hpp>
#include "ui_consts.h"
#include "ui.h"
#include "../engine/game_engine.h"
#include "textures.h"

namespace UC = ui_consts;

namespace engine_ui {
	class FieldMenu : public sf_my::MenuPart {
	public:
		FieldMenu(int x_shift=0, int x_pos=0, int y_pos=0, int size=0);
	};

	class GameWindow {
	private:
		sf::RenderWindow window;
		sf::Text castle_health;
		sf::Text balance;
		sf::Text info;
		sf_my::RadioButtons speed;
		sf_my::MenuPart *menu = nullptr;
		FieldMenu field_menu;
		textures::Sprites sprites;
		textures::Fonts fonts;
		std::vector<std::vector<sf_my::Button>> button_field;
		int counter;
		int size_x;
		int size_y;
		int old_size_x;
		int old_size_y;
		int max_counter;
		void mouse_pressed(GE::Game& game, sf::Event& event);
		void mouse_moved(GE::Game& game, sf::Event& event);
		void resized(sf::Event& event);
		void show_stats(GE::Game& game);
		void show_field(GE::Game &game);
		void show_units(GE::Game &game);
		void show_menu(GE::Game &game);
	public:
		GameWindow(GE::Game& game);
		void show(GE::Game &game) { window.clear(UC::background_color);
			show_field(game), show_menu(game), show_units(game), show_stats(game), window.display();}
		sf::RenderWindow& get_window() {return (window);}
		void do_event(GE::Game& game, sf::Event& event);
		bool is_ready();
	};
}



#endif
