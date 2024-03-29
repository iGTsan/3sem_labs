#include "players.h"
#include <string>
#include <iostream>

using namespace players;
using namespace DiceSpace;
using std::cout;
using std::endl;

void game_state::next_player() {
	player += 1;
	player %= players;
}

Player::Player(const string &s, const int n) : dices(n) {
	set_name(s);
	set_count_of_dices(n);
}

void Player::set_name(const string &s) {
	name = s;
}

string& Player::get_name(){
	return (name);
}

void Player::set_count_of_dices(const int n) {
	while (dices.get_amount() > n)
		lose_dice();
	while (dices.get_amount() < n)
		dices.insert_dice();
	count_dices = n;
}

void Player::lose_dice() {
	dices.remove_dice(1);
	count_dices--;
}

int Player::get_count_of_dices() const{
	return (count_dices);
}

int Player::get_count_of_dices(const int n){
	int res = 0;
	for (int i = 0; i < count_dices; i++)
		if (dices[i + 1] == n || dices[i + 1] == 1)
			res++;
	return (res);
}

void Player::throw_dices() {
	dices.throw_dice();
}
void Player::show_dices() const{
	cout << dices << endl;
}

void Players::add_player(const string &s, const int n) {
	data.push_back(Player(s, n));
}

Player& Players::operator[] (const int i){
	return (data[i]);
}

int Players::size() const{
	return (data.size());
}

int Players::get_count_of_dices(const int n){
	int res = 0;
	for (int i = 0; i < size(); i++)
		res += data[i].get_count_of_dices(n);
	return (res);
}

void Players::throw_dices() {
	for (int i = 0; i < size(); i++)
		data[i].throw_dices();
}
