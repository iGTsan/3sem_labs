#include "words.h"
#include <algorithm>

Words::Words(const int _count, const std::string from[]) : Words::Words() {
	for (int i = 0; i < _count; i++)
		*this += from[i];
}

Words::Words(const string &from) : Words::Words() {
	*this += from;
}

Words::Words(const Words &w) : Words::Words() {
	*this += w;
}

std::ostream& operator<<(std::ostream &c, const Words &w) {
	for (int i = 0; i < w.count; i++)
		if (i < w.count - 1)
			c << w.data[i] << ' ';
		else
			c << w.data[i];
	return (c);
}

std::istream& operator>>(std::istream &c, Words &w) {
	int _count;
	c >> _count;
	if (c.fail())
		throw Words::input_error();
	std::string buf;
	for (int i = 0; i < _count; i++) {
		if (c.eof())
			throw Words::input_error();
		c >> buf;
		w += buf;
	}
	return (c);
}

void Words::operator +=(const Words &w) {
	for (int i = 0; i < w.count; i++)
		*this += w.data[i];
}

void Words::operator +=(const string &from) {
	if (count >= max_count) {
		string *prev = data;
		max_count = 2 * max_count + 1;
		data = new string[max_count];
		std::move(prev, prev + count, data);
		delete[] prev;
	}
	data[count] = from;
	count++;
}

Words Words::operator +(const Words &w) const {
	Words res;
	res += *this;
	res += w;
	return (res);
}

Words& Words::operator =(const Words &w) {
	count = 0;
	max_count = 0;
	delete[] data;
	data = nullptr;
	*this += w;
	return (*this);
}

int Words::operator [](const string &s) const {
	for (int i = 0; i < count; i++)
		if (data[i] == s)
			return (i);
	return (-1);
}

string& Words::operator [](const int i) const {
	if (i >= 0 && i < count)
		return (data[i]);
	else
		throw std::out_of_range("");
}

Words Words::first_letter(const char c) const {
	Words res;
	int diff = 'a' - 'A';
	if (c > 'Z')
		diff = -diff;
	for (int i = 0; i < count; i++)
		if (data[i][0] == c || data[i][0] == c + diff)
			res += data[i];
	return (res);
}
void Words::operator ~() {
	std::sort(data, data + count);
}

Words::~Words() {
	delete[] data;
}

