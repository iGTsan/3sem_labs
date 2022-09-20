#include <iostream>
#include "../lib/cartesian.h"
#include "input.h"

using namespace std;

/*
Cartesian ();
Cartesian (double);
Cartesian (const Cartesian&);
double get ();
double set (double _n);
double chord ();
double dist (double);
double r_vertex();
double r_point(double, double);
double square();
double max_len();
double dist_to_max();
*/



int main() {
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
	return 0;
}