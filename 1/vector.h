#ifndef VECTOR_H
#define VECTOR_H


class vector {
public:
	vector();
	void push(int n, int pos=-1);
	~vector();
	void print();
	int operator [](int i);
	int size();

private:
	int* data;
	int len;
	int mlen;
};

#endif