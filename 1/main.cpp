#include <iostream>
// #include "vector.h"
#include "matrix.h"
#include "input.h"
#include <limits>

using namespace std;

void task(matrix &a, matrix &b) {
	for (int i = 0; i < a.rows.size(); i++) {
		b.add_empty(i + 1);
		int max = -1e9;
		int j = a.rows[i];
		int right = a.val.size();
		if (i < a.rows.size() - 1)
			right = a.rows[i + 1];
		while (j < right) {
			if (a.val[j] > max)
				max = a.val[j];
			j++;
		}
		j = a.rows[i];
		while (j < right && a.val[j] < max) {
			b.add_elem(i + 1, a.cols[j] + 1, a.val[j]);
			j++;
		}
		if (j < right && a.val[j] == max)
			b.add_elem(i + 1, a.cols[j] + 1, a.val[j]);
	}
}

int main() {
	matrix a;
	int col, row = 1, val;
	do {
		cout << row << " Row" << endl;
		do {
			cout << "Enter column (-2 for next, -1 for exit):";
			try {
				col = get_int(-2);
				if (col >= 0) {
					cout << "Enter value:";
					val = get_int();
				}
			}
			catch (const char *s) {
				cerr << s << endl;
				col = 0;
				if (cin.eof())
					col = -1;
;				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			if (col == -2) {
				a.add_empty(row + 1);
			}
			else if (col != -1) {
				a.add_elem(row, col, val);
			}
		} while (col != -1 && col != -2);
		row++;
	} while (col != -1);
	// a.add_elem(2,3,4);
	matrix b;
	task(a, b);
	a.print();
	b.print();
}