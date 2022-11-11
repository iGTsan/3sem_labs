#include "../classes/player_things.h"
#include "../classes/basic.h"
#include "../engine/game_engine.h"
#include <unistd.h>

using namespace game_engine;
using namespace std;

string menu_entries[] = {"1. Поставить башню(10)",
						"2. Поставить стену(30)",
						"3. Следующий ход",
						"4. Пропустить н ходов"};

void menu(Game& game) {
	for (int i = 0; i < 4; i++)
		cout << menu_entries[i] << endl;
	int c, x, y, n;
	cin >> c;
	switch (c) {
	case 1:
		cin >> x >> y;
		game.add_tower(x, y);
		break;
	case 2:
		cin >> x >> y;
		game.add_wall(x, y);
		break;
	case 3:
		break;
	case 4:
		cin >> n;
		for (int i = 0; i < n; i++)
			game.tic();
		break;
	}
}

/*
int main() {
	Game game("ya");
	game.load_landscape("/home/ya/infa/3 sem/lab/4/recourses/field2");
	game.add_enemy(1, 1);
	game.add_enemy(2, 2);
	game.add_enemy(3, 3);
	game.add_enemy(4, 2);
	game.add_enemy(5, 3);
	game.add_enemy(6, GO::aura{1, 1, 1}, 3);
	while (!game.is_end()) {
		game.tic();
		game.show_field();
		menu(game);
	}
	// 1 6 6 1 6 7 1 6 8 1 7 6 1 7 7 1 7 8 1 7 9

//	Landscape land;
//	land.load("/home/ya/infa/3 sem/lab/4/recourses/field1");
//	land.set_size(10, 10);
//	land.save("/home/ya/infa/3 sem/lab/4/recourses/field2");
}*/
