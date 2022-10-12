#include <iostream>
#include <string.h>
#include <string>
#include <limits>

#include "../lib/words.h"
#include "../lib/input.h"

using std::cin;
using std::cout;
using std::endl;

void print(Words &w) {
	w.print(cout);
	/*
	cout << "Новый коэффицент: ";
	double n;
	int good = 0;
	while (!good){
		try {
			n = get_double();
			good = 1;
		}
		catch (const char *s){
			good = 0;
			cout << s << endl;
	 		if (cin.eof())
	 			return;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	a.set_coef(n);*/
}

void scan(Words &w) {
	w.scan(cin);
}

void add_word(Words &w) {
	std::string s;
	cin >> s;
	w.add(s.c_str());
}

void find_word(Words &w) {
	std::string s;
	cin >> s;
	cout << w.find(s.c_str()) << endl;
}

void index(Words &w) {
	int i;
	i = get_int();
	std::string s = w.index(i);
	cout << s << endl;
}

void first_letter(Words &w) {
	char c;
	cin >> c;
	w.first_letter(c).print(cout);
}

void sort(Words &w) {
	w.sort();
}

void menu(Words &w) {
	void (*entries_func[])(Words&) = {scan, print, add_word, find_word, index, first_letter, sort};
	// auto entries_func = {set_n, get_n, sq_side, dist, r_vertex, r_point, square, max_len, dist_to_max};
	auto entries_text = {"1.Ввод из входного потока",
	"2. Вывод во входной поток",
	"3. Добавление слова",
	 "4. Поиск слова",
	 "5. Выделение слова по номеру",
	 "6. Массив слов, на заданный символ",
	 "7. Сортировка по алфавиту",
	 "0. Выход"};
	 int c;

	 do {
	 	for (auto i: entries_text)
	 	cout << i << endl;
	 	try {
	 		c = get_int(0, 7);
	 		if (c != 0)
	 			entries_func[c - 1](w);
	 	}
	 	catch (input_end_of_file &e) {
	 		c = 0;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 		cout << "End of file" << endl;
	 	}
	 	catch (input_bad_input &e) {
			c = -1;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Bad input in menu" << endl;
		}
	 	catch (input_out_of_range &e) {
			c = -1;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Input out of range" << endl;
		}
	 	catch (Words::input_error &e) {
			c = -1;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Bad input in words" << endl;
		}
	 	catch (std::overflow_error &e) {
			cout << e.what() << endl;
		}
	 	catch (std::out_of_range &e) {
			cout << "Index out of range" << endl;
		}
	 } while (c != 0);
}


int main() {
	Words w;
	menu(w);
}
