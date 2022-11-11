#ifndef UI_TEXTURES_H_
#define UI_TEXTURES_H_

#include <SFML/Graphics.hpp>
#include "ui_consts.h"
#include "ui.h"

namespace UC = ui_consts;

namespace textures {
	sf::Font default_font;
	sf::Font beauty_font;

	sf_my::Sprite tower_sprite(UC::tower_png);
	sf_my::Sprite plain_sprite(UC::plain_png);
	sf_my::Sprite mountain_sprite(UC::mountain_png);
	sf_my::Sprite river_sprite(UC::river_png);
	sf_my::Sprite grass_sprite(UC::grass_png);
	sf_my::Sprite castle_sprite(UC::castle_png);
	sf_my::Sprite lair_sprite(UC::lair_png);
	sf_my::Sprite tank_sprite(UC::tank_png);
	sf_my::Sprite light_sprite(UC::light_png);
	sf_my::Sprite aviation_sprite(UC::aviation_png);
	sf_my::Sprite hero_tank_sprite(UC::hero_tank_png);
	sf_my::Sprite hero_light_sprite(UC::hero_light_png);
	sf_my::Sprite hero_aviation_sprite(UC::hero_aviation_png);
	sf_my::Sprite wall_sprite(UC::wall_png);

	void init() {
		beauty_font.loadFromFile(UC::beauty_font);
		default_font.loadFromFile(UC::default_font);
	}
}

#endif
