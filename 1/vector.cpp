#include "vector.h"
#include "stdlib.h"
#include <iostream>
#include "string.h"

using namespace std;

vector:: vector() {
	data = NULL;
	len = 0;
	mlen = 0;
}

void vector:: push(int n, int pos) {
	if (len == mlen) {
		data = (int *)realloc(data, (mlen * 2 + 1) * sizeof(int));
		mlen = mlen * 2 + 1;
	}
	if (pos == -1)
		pos = len;
	else
		memmove(data + pos + 1, data + pos, (len - pos) * sizeof(int));
	data[pos] = n;
	len++;
}

void vector:: print() {
	for (int i = 0; i < len; i++)
		cout << data[i] << ' ';
	cout << endl;
}
int& vector:: operator [](int i) {
	if (i < 0) 
		return data[len + i];
	return data[i];
}

int vector:: size() {
	return len;
}

vector:: ~vector() {
	free(data);
}