#include "handle.h"
#include <iostream>

using namespace std;

int read_int(const char *name) {
    int number;
    std::cout << "Enter " << name << ": ";
    cin >> number;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Enter correct number: " << endl;
        cin >> number;
    }
    return number;
}


int read_menu_int(const char *name) {
    int number;
    std::cout << "Enter " << name << ": ";
    cin >> number;
    while (cin.fail() || (number < 0 || number > 13)) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Enter correct number: " << endl;
        cin >> number;
    }
    return number;
}