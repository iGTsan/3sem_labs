#include <iostream>


 using namespace std;

double get_int(double l, double r) {
	double n;
	cin >> n;
	if (cin.eof()) 
		throw "End of file";
	if (cin.fail())
		throw "Bad input";
	if (n < l || n > r)
		throw "Out of range";
	
	return n;
}