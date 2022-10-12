#include <iostream>
#include <stdexcept>
#include "input.h"

using std::cin;

double get_double(double l, double r) {
	double n;
	cin >> n;
	if (cin.eof())
		throw input_end_of_file();
	if (cin.fail())
		throw input_bad_input();
	if (n < l || n > r)
		throw input_out_of_range();

	return n;
}

int get_int(int l, int r) {
	int n;
	cin >> n;
	if (cin.eof())
		throw input_end_of_file();
	if (cin.fail())
		throw input_bad_input();
	if (n < l || n > r)
		throw input_out_of_range();

	return n;
}
