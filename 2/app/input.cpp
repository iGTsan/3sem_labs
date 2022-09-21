#include <iostream>


 using namespace std;

double get_double(double l, double r) {
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

int get_int(int l, int r) {
	int n;
	cin >> n;
	if (cin.eof()) 
		throw "End of file";
	if (cin.fail())
		throw "Bad input";
	if (n < l || n > r)
		throw "Out of range";
	
	return n;
}