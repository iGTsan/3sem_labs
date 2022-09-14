#include <iostream>
 
 using namespace std;

int get_int() {
	int n;
	cin >> n;
	if (cin.eof()) 
		throw "End of file";
	if (cin.fail())
		throw "Bad input";
	
	return n;
}