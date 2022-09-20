#include "cartesian.h"
#include <cmath>

Cartesian::Cartesian () {
	n = 1;
}

Cartesian::Cartesian (double _n) {
	n = _n;
}

Cartesian::Cartesian (const Cartesian& cart) {
	n = cart.n;
}

double Cartesian::get () {
	return n;
}

void Cartesian::set (double _n) {
	n = _n;
}

double Cartesian::chord () {
	return std::abs(3 * n / sqrt(2));
}

double Cartesian::dist (double y) {
	return std::abs(3 * n * cos(y) * sin(y) / 
	(pow(cos(y), 3) + pow(sin(y), 3)));
}

double Cartesian::r_vertex() {
	return std::abs(3 * n / (8 * sqrt(2)));

}

double Cartesian::r_point() {
	return std::abs(3 * n / 2);
}

double Cartesian::square() {
	return 1.5 * n * n;
}

double Cartesian::max_len() {
	double l = chord();
	return 2 * l / 3 * sqrt(2 * sqrt(3) - 3);
}

double Cartesian::dist_to_max() { 
	double l = chord();
	return l / 3 * sqrt(3);
}
