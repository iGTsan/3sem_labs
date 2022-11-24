#include "engine_ui.h"
#include <iostream>
#include "../classes/vector.h"
//#include <vector>

//#define MyVector MyVector

using namespace engine_ui;


void test_vector() {
	std::MyVector<int> a;
	a.push_back(3);
	a.push_back(2);
	a.push_back(1);
//	a.resize(3, 0);
	std::cout << a[0] << ' ' << a[2] << std::endl;
	for (auto i: a)
		std::cout << i << ' ';
	std::cout << std::endl;
	for (auto i = a.begin(); i != a.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
	for (auto& i: a)
		i = 1;
	for (auto i: a)
		std::cout << i << ' ';
	std::cout << std::endl;
}

int main()
{
	test_vector();
	StartMenu menu;
	menu.loop();
}
