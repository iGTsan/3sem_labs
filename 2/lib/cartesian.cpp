#include "cartesian.h"
#include <cmath>

Cartesian::Cartesian () {
	coef = 1;
}

Cartesian::Cartesian (const double _coef) {
	coef = _coef;
}

Cartesian::Cartesian (const Cartesian& cart) {
	coef = cart.coef;
}

const double Cartesian::get_coef () {
	return coef;
}

void Cartesian::set_coef (const double _coef) {
	coef = _coef;
}

const double Cartesian::get_chord () {
	return std::abs(3 * coef / sqrt(2));
}

const double Cartesian::get_dist (const double y) {
	return std::abs(3 * coef * cos(y) * sin(y) / 
	(pow(cos(y), 3) + pow(sin(y), 3)));
}

const double Cartesian::get_r_vertex() {
	return std::abs(3 * coef / (8 * sqrt(2)));

}

const double Cartesian::get_r_point() {
	return std::abs(3 * coef / 2);
}

const double Cartesian::get_square() {
	return 1.5 * coef * coef;
}

const double Cartesian::get_max_len() {
	double l = get_chord();
	return 2 * l / 3 * sqrt(2 * sqrt(3) - 3);
}

const double Cartesian::get_dist_to_max() { 
	double l = get_chord();
	return l / 3 * sqrt(3);
}
