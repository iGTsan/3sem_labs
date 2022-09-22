#include <iostream>
#include "../lib/cartesian.h"
#include "input.h"
#include <limits>

using namespace std;

void set_coef(Cartesian &a) {
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
	a.set_coef(n);
}

void get_coef(Cartesian &a) {
	cout << a.get_coef() << endl;
}

void sq_side(Cartesian &a) {
	cout << a.get_chord() << endl;
}

void dist(Cartesian &a) {
	cout << "Угол : ";
	double y;
	int good = 0;
	while (!good){
		try {
			y = get_double();
			good = 1;
		}
		catch (const char *s){
			cout << s << endl;
	 		if (cin.eof())
	 			return;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cout << a.get_dist(y) << endl;
}

void r_vertex(Cartesian &a) {
	cout << a.get_r_vertex() << endl;
}

void r_point(Cartesian &a) {
	cout << a.get_r_point() << endl;
}

void square(Cartesian &a) {
	cout << a.get_square() << endl;
}

void max_len(Cartesian &a) {
	cout << a.get_max_len() << endl;
}

void dist_to_max(Cartesian &a) {
	cout << a.get_dist_to_max() << endl;
}

void menu(Cartesian &a) {
	void (*entries_func[])(Cartesian&) = {set_coef, get_coef, sq_side, dist, r_vertex, r_point, square, max_len, dist_to_max};
	// auto entries_func = {set_n, get_n, sq_side, dist, r_vertex, r_point, square, max_len, dist_to_max};
	auto entries_text = {"1.Изменить коэффицент", 
	"2. Посмотреть коэффицент", 
	"3. Сторона квадрата, которая равна наибольшей хорде листа",
	 "4. Расстояние до центра в полярной системе координат в зависимости от угла",
	 "5. Радиус кривизны в вершине листа",
	 "6. Радиус кривизны в узловой точке",
	 "7. Площадь петли листа",
	 "8. Длина наибольшего поперечника петли",
	 "9. Расстояния от узла до наибольшего поперечника",
	 "0. Выход"};
	 int c;
	 
	 do {
	 	for (auto i: entries_text)
	 	cout << i << endl;
	 	try {
	 		c = get_int(0, 9);
	 		if (c != 0)
	 			entries_func[c - 1](a);
	 	}
	 	catch (const char *s) {
	 		c = -1;	 		
	 		if (cin.eof())
	 			c = 0;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
	 		cout << s << endl;
	 	}
	 } while (c != 0);
}


int main() {
	Cartesian a;
	menu(a);
	/*
	double n;
	cout << "коэффицент:" ;
	n = get_int();
	Cartesian a(n);
	cout << "коэффицент = " << a.get() << endl;
	cout << "сторона квадрата, которая равна наибольшей хорде листа = " << a.chord() << endl;
	double x;
	cout << "Угол:";
	x = get_int();
	cout << "Расстояние до центра в полярной системе координат в зависимости от угла = " << a.dist(x) << endl;
	cout << "Радиус кривизны в вершине листа = " << a.r_vertex() << endl;
	cout << "Радиус кривизны в узловой точке = " << a.r_point() << endl;
	cout << "Площадь петли листа = " << a.square() << endl;
	cout << "Длина наибольшего поперечника петли = " << a.max_len() << endl;
	cout << "Расстояния от узла до наибольшего поперечника = " << a.dist_to_max() << endl;
	return 0;*/
}