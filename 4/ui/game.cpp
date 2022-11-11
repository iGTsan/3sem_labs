#include "engine_ui.h"
#include <clocale>

using namespace engine_ui;


int main()
{
    GE::Game game("ya");
    game.load_landscape("/home/ya/infa/3 sem/lab/4/levels/field2");
//    game.add_enemy(1, 1);
//	game.add_enemy(2, 2);
//	game.add_enemy(3, 3);
//	game.add_enemy(4, 2);
//	game.add_enemy(5, 3);
//	game.add_enemy(6, GO::aura{1, 40, 1}, 3);
    for (int i = 0; i < 10; i++) {
    	game.add_random_enemy();
    }

	MainWindow window(game);

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

    return 0;
}
