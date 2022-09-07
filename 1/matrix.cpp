#include "matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define width 5

matrix:: matrix() {
	cnt_cols = 0;
}

void matrix:: add_empty(int row) {
	while (rows.size() < row)
		rows.push(cols.size());
}

void matrix:: add_elem(int row, int col, int n) {
	add_empty(row);
	int i = rows[-1];
	while (i < cols.size() && col - 1 > cols[i])
		i++;
	if (i < cols.size() && col - 1 == cols[i]) {
		cout << "Point already exist " << endl;
		return;
	}
	cols.push(col - 1, i);
	val.push(n, i);
	if (col > cnt_cols)
		cnt_cols = col;
	// cols.print();
	// val.print();
	// rows.print();
	// cin >> col;
}

void matrix:: print() {
	cout << endl;
	for (int row = 0; row < rows.size(); row++) {
		int col = 0;
		int k = 0;
		while ((row < rows.size() - 1 && rows[row] + k < rows[row + 1]) ||
		 (row == rows.size() - 1 && rows[row] + k < val.size())) {
			while (col != cols[rows[row] + k]) {
				cout << setw(width) << '-';
				col++;
			}
			cout << setw(width) << val[rows[row] + k];
			k++;
			col++;
		}
		
		for (; col < cnt_cols; col++)
			cout << setw(width) << '-';
		cout << endl;
	}
}