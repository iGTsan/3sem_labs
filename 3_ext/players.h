#ifndef PLAYERS_H
#define PLAYERS_H

#include "dice.h"
#include <vector>

namespace players {

	typedef struct game_state {
		int cnt = 0;
		int val = 0;
		int player = 0;
		int players = 0;
		void next_player();
	} game_state;

	class Player {
	private:
		string name = "";
		DiceSpace::Dice_vector dices;
		int count_dices = 0;
	public:
		Player() : dices(0) {};
		Player(const string &, const int n = 0);
		void set_name(const string &);
		string& get_name();
		void set_count_of_dices(const int);
		void lose_dice();
		int get_count_of_dices() const;
		int get_count_of_dices(const int);
		void throw_dices();
		void show_dices() const;
	};

	class Players {
	private:
		std::vector<Player> data;
	public:
		void add_player(const string &, const int);
		Player& operator[] (const int);
		int size() const;
		int get_count_of_dices(const int);
		void throw_dices();
	};
}

#endif
