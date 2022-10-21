#ifndef WORDS_H_
#define WORDS_H_

#include <iostream>
#include <string>
#include <string.h>
#include <stdexcept>
#include <stdlib.h>

using std::string;

class Words {
private:
	int count;
	int max_count;
	string *data;
public:
	Words() : count(0), max_count(0), data(nullptr) {};
	Words(const int, const string[]);
	Words(const string &);
	Words(const Words &);

	void operator +=(const string &);
	void operator +=(const Words &);
	Words operator +(const Words &) const;
	Words& operator =(const Words &);
	string& operator [](const int) const;
	int operator [](const string &) const;
	void operator ~();
	Words first_letter(const char) const;

	class input_error : std::exception {};

	friend std::ostream& operator<<(std::ostream &, const Words &);
	friend std::istream& operator>>(std::istream &, Words &);
	friend int cmp(const void*, const void*);

	~Words();
};

#endif
