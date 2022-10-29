#ifndef DIALOG_H
#define DIALOG_H

#include "players.h"
#include <limits.h>

namespace dialog {
	void show_dices(players::Players &);
	int int_input(string s = "", int l = 0, int r = INT_MAX);
	void show_players(players::Players &);
	void new_bet(players::Players &, players::game_state &);
	void check(players::Players &, players::game_state);
	void add_player(players::Players &, players::game_state &);


}

#endif
