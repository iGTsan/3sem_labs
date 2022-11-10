#ifndef UI_ENGINE_UI_H_
#define UI_ENGINE_UI_H_

#include <SFML/Graphics.hpp>
#include "ui_consts.h"
#include "ui.h"
#include "../engine/game_engine.h"

namespace GE = game_engine;
namespace UC = ui_consts;

namespace engine_ui {

	class TowerMenu : public sf_my::MenuPart {
	public:
		TowerMenu(int x_shift=0, int x_pos=0, int y_pos=0, int size=0);
	};

	class FieldMenu : public sf_my::MenuPart {
	public:
		FieldMenu(int x_shift=0, int x_pos=0, int y_pos=0, int size=0);

	};

	class CastleMenu : public sf_my::MenuPart {
	public:
		CastleMenu(int x_shift=0, int x_pos=0, int y_pos=0, int size=0);
	};

	class MainWindow {
	private:
		sf::Font font;
		sf::Font font2;
		sf::RenderWindow window;
		sf::Text castle_health;
		sf::Text balance;
		sf::Text info;
		sf_my::RadioButtons speed;
		sf_my::MenuPart *menu = nullptr;
		CastleMenu castle_menu;
		TowerMenu tower_menu;
		FieldMenu field_menu;
		std::vector<std::vector<sf_my::Button>> button_field;
	public:
		MainWindow(GE::Game& game);
		void show_stats(GE::Game& game);
		void show_field(GE::Game &game);
		void show_units(GE::Game &game);
		void show_menu(GE::Game &game);
		void show(GE::Game &game) { window.clear();
			show_field(game), show_menu(game), show_units(game), show_stats(game), window.display();}
		sf::RenderWindow& get_window() {return (window);}
		void do_event(GE::Game& game, sf::Event& event);
		void mouse_pressed(GE::Game& game, sf::Event& event);
		void mouse_moved(GE::Game& game, sf::Event& event);
	};
}



#endif /* UI_ENGINE_UI_H_ */
