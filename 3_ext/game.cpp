#include <iostream>
#include "dice.h"
#include "dialog.h"
#include "players.h"
#include <string>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace DiceSpace;
using namespace players;
using namespace dialog;

void print_menu(string s[], int n) {
	for (int i = 0; i < n; i++)
		cout << s[i] << endl;
	cout << endl;
}

void game() {
	Players p;
	game_state g;
	string s[] = {"0. Выход",
			"1. Показать кости",
			"2. Показать игроков",
			"3. Новая ставка",
			"4. Проверяем",
			"5. Добавить игрока"
	};
//	void (*func[])(Players &, game_state &) = {show_dices, show_players, new_bet, check, add_player};
	print_menu(s, 6);
	int c;
	while ((c = int_input("", 0, 6))) {
		switch (c) {
		case 1:
			show_dices(p);
			break;
		case 2:
			show_players(p);
			break;
		case 3:
			new_bet(p, g);
			break;
		case 4:
			check(p, g);
			break;
		case 5:
			add_player(p, g);
			break;
		}
		print_menu(s, 6);
	}
}

int main() {
	cout << "Hi" << endl;
	game();
}
//перудо
