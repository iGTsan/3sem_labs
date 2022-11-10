#include "engine_ui.h"
#include <clocale>

using namespace engine_ui;


int main()
{
    GE::Game game("ya");
    game.load_landscape("/home/ya/infa/3 sem/lab/4/recourses/field2");
    game.add_enemy(1, 1);
	game.add_enemy(2, 2);
	game.add_enemy(3, 3);
	game.add_enemy(4, 2);
	game.add_enemy(5, 3);
	game.add_enemy(6, GO::aura{1, 40, 1}, 3);

	MainWindow window(game);

    while (window.get_window().isOpen())
    {
        sf::Event event;
        while (window.get_window().pollEvent(event))
        {
            window.do_event(game, event);
        }
        window.show(game);
        game.tic();
        game.counter++;

    }

    return 0;
}
