#include <stdlib.h>
#include <limits>
#include "dialog.h"

using namespace dialog;
using namespace players;
using std::cout;
using std::endl;
using std::cin;

int dialog::int_input(string s, int l, int r) {
	cout << s;
	int t = 0;
	int res;
	do {
		if (t) {
			cout << "Неправильный ввод" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		cin >> res;
		t = 0;
		if (cin.eof())
			return (0);
		if (cin.fail())
			t = 1;
		if (res < l || res > r)
			t = 1;
	} while (t);
	return (res);
}

void dialog::show_dices(Players &p) {
	int i;
	if (p.size() == 0) {
		cout << "Нет ни одного игрока" << endl;
		return;
	}
	i = int_input("Номер игрока: ", 1, p.size());
	p[i - 1].show_dices();
	cout << "Enter to hide dices" << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.get();
	system("clear");
}

void dialog::show_players(Players &p) {
	for (int i = 0; i < p.size(); i++)
		cout << i + 1 << ". " << p[i].get_name() << " " << p[i].get_count_of_dices() << endl;
	cout << endl;
}


void dialog::new_bet(Players &p, game_state &g) {
	if (p.size() == 0) {
		cout << "Нет ни одного игрока" << endl;
		return;
	}
	cout << "Ход игрока " << p[g.player].get_name() << endl;
	int _cnt = int_input("Количество: ");
	int _val = int_input("Значение: ", 1, 6);
	if (g.val != 1) {
		if ((_val > g.val && _cnt >= g.cnt) ||
				(_val <= g.val && _cnt > g.cnt) ||
				(_val == 1 && _cnt > (g.cnt + 1) / 2))
			g.val = _val, g.cnt = _cnt, g.next_player();
		else
			cout << "Плохая ставка" << endl;
	}
	else
		if ((_val > g.val && _cnt >= g.cnt * 2) ||
				(_val == g.val && _cnt > g.cnt))
			g.val = _val, g.cnt = _cnt, g.next_player();
		else
			cout << "Плохая ставка" << endl;
}

int check_win(Players &p) {
	int cnt = 0;
	for (int i = 0; i < p.size(); i++)
		if (p[i].get_count_of_dices())
			cnt++;
	return (!(cnt - 1));
}

void dialog::check(Players &p, game_state g) {
	if (p.size() == 0) {
		cout << "Нет ни одного игрока" << endl;
		return;
	}
	if (g.cnt == 0 || g.val == 0) {
		cout << "Ставок еще не было" << endl;
		return;
	}
	if (p.get_count_of_dices(g.val) >= g.cnt) {
		p[g.player].lose_dice();
		cout << "Игрок " << p[g.player].get_name() << " теряет кость" << endl;
	}
	else {
		p[(g.player + p.size() - 1) % p.size()].lose_dice();
		cout << "Игрок " << p[(g.player + p.size() - 1) % p.size()].get_name() << " теряет кость" << endl;
	}
	if (check_win(p)) {
		cout << "Игра окончена" << endl;
	}
	p.throw_dices();
}

void dialog::add_player(Players &p, game_state &g) {
	string name;
	cout << "Имя: ";
	cin >> name;
	int n = int_input("Количество костей: ");
	p.add_player(name, n);
	g.players++;
	p.throw_dices();
}

void dialog::show_rules() {
	cout << "Все игроки смотрят кости, не показывая другим участникам. Первы называет число и номинал костей, которые, по его мнению, находятся на игровом столе — у всех игроков вместе взятых. Второй игрок может либо согласиться со ставкой предыдущего игрока, сделав собственную ставку, либо сказать «проверяем»." << endl;
	cout << "Если игрок согласен со ставкой предыдущего игрока, он должен сделать собственную ставку. При этом должны быть соблюдены определённые условия" << endl;
	cout << "Количество костей в ставке нельзя понижать" << endl;
	cout << "Исключение — игрок вправе уменьшить количество костей в ставке в два раза (при нечётном числе округление в большую сторону), если он называет номинал «единицы»" << endl;
	cout << "сли количество костей в ставке остаётся прежним, номинал должен быть увеличен." << endl;
	cout << "Если количество костей в ставке увеличивается, то номинал костей может быть назван любой" << endl;
	cout << "Если номинал предыдущей ставки был «единицы», игрок вправе изменить ставку только увеличив количество костей в «единицах» или сделав ход в другом номинале, но с количеством костей на одну больше, чем двойное число ставки в единицах предыдущего игрока." << endl;
	cout << "-----------------------------------" << endl;
	cout << "Если игрок не верит" << endl;
	cout << "Если костей названного проверяемым игроком номинала на столе оказывается меньше того количества, которое фигурировало в ставке, игрок, делавший данную ставку считается проигравшим и теряет кость." << endl;
	cout << "Если костей названного номинала больше или равно количеству костей в ставке, проигравшим считается игрок, сказавший «не верю»." << endl;
	cout << "После того, как кто-то из игроков проиграл кость, игроки вновь бросают кости и первым ходит проигравший игрок." << endl;
}

