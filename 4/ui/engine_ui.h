#ifndef UI_ENGINE_UI_H_
#define UI_ENGINE_UI_H_

#include <SFML/Graphics.hpp>
#include "ui_consts.h"
#include "textures.h"
#include "ui.h"

namespace engine_ui {
	class StartMenu {
	private:
		sf::RenderWindow window;
		sf_my::TextField name;
		sf_my::TextField level;
		sf::Text name_text;
		sf::Text level_text;
		sf_my::Button next;
		textures::Fonts fonts;
		int size_x;
		int size_y;
		int old_size_x;
		int old_size_y;
		int state = 0;
		void play(const std::string& player_name, const std::string& level);
		void show();
		void do_event(sf::Event& event);
		void mouse_moved(sf::Event& event);
		void mouse_pressed(sf::Event& event);
		void resized(sf::Event& event);
		void key_pressed(sf::Event& event);
		std::vector<sf_my::Button *> buttons;
	public:
		StartMenu();
		void loop();
		~StartMenu();
	};
}



#endif
