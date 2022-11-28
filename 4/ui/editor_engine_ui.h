#ifndef UI_EDITOR_ENGINE_UI_H_
#define UI_EDITOR_ENGINE_UI_H_

#include "../engine/editor_engine.h"
#include <SFML/Graphics.hpp>
#include "ui_consts.h"
#include "ui.h"
#include "textures.h"

namespace engine_ui {
	class EditorMenu : public sf_my::MenuPart {
	public:
		EditorMenu(int x_shift=0, int x_pos=0, int y_pos=0, int size=0);
	};

	class EditorWindow : public editor_engine::Editor {
	private:
		sf::RenderWindow window;
		sf_my::ButtonMatrix buttons_field;
		sf_my::Button expand_y_btn;
		sf_my::Button expand_x_btn;
		sf_my::Button save_btn;
		EditorMenu menu;
		sf_my::MenuPart *menuptr = nullptr;
		std::string filename;
		textures::Sprites sprites;

		int size_x;
		int size_y;
		int old_size_x;
		int old_size_y;

		void show_field();
		void show();
		void do_event(sf::Event& event);
		void mouse_moved(sf::Event& event);
		void mouse_pressed(sf::Event& event);
		void key_pressed(sf::Event& event);
		void resized(sf::Event& event);
		void expand(int x, int y);
	public:
		EditorWindow(const std::string& filename);
		void loop();
	};
}

#endif
