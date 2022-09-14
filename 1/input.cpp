#include <iostream>


 using namespace std;

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