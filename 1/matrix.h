#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class matrix {
public:
	matrix();
	void add_elem(int row, int col, int n);
	void add_empty(int row);
	void print();
	
	vector val;
	vector rows;
	vector cols;
	int cnt_cols;
};

#endif