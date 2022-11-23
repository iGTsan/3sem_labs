#ifndef UI_TEXTURES_H_
#define UI_TEXTURES_H_

#include <SFML/Graphics.hpp>
#include "ui_consts.h"
#include "ui.h"

namespace UC = ui_consts;

namespace textures {
	class Fonts {
	public:
		Fonts() {
			beauty_font.loadFromFile(UC::beauty_font);
			default_font.loadFromFile(UC::default_font);
		}
		sf::Font default_font;
		sf::Font beauty_font;
	};

	class Sprites {
	public:
		Sprites() :
			tower_sprite(UC::tower_png),
			plain_sprite(UC::plain_png),
			mountain_sprite(UC::mountain_png),
			river_sprite(UC::river_png),
			grass_sprite(UC::grass_png),
			castle_sprite(UC::castle_png),
			lair_sprite(UC::lair_png),
			tank_sprite(UC::tank_png),
			light_sprite(UC::light_png),
			aviation_sprite(UC::aviation_png),
			hero_tank_sprite(UC::hero_tank_png),
			hero_light_sprite(UC::hero_light_png),
			hero_aviation_sprite(UC::hero_aviation_png),
			wall_sprite(UC::wall_png) {};
		sf_my::Sprite tower_sprite;
		sf_my::Sprite plain_sprite;
		sf_my::Sprite mountain_sprite;
		sf_my::Sprite river_sprite;
		sf_my::Sprite grass_sprite;
		sf_my::Sprite castle_sprite;
		sf_my::Sprite lair_sprite;
		sf_my::Sprite tank_sprite;
		sf_my::Sprite light_sprite;
		sf_my::Sprite aviation_sprite;
		sf_my::Sprite hero_tank_sprite;
		sf_my::Sprite hero_light_sprite;
		sf_my::Sprite hero_aviation_sprite;
		sf_my::Sprite wall_sprite;
	};
}

#endif
