#include "words.h"

Words::Words(const int _count, const std::string from[]) {
	if (_count > max_count)
		throw std::overflow_error("Words overflow");
	count = 0;
	for (int i = 0; i < _count; i++)
		add(from[i].c_str());
}

int cmp(const void *a, const void *b) {
	return (strcmp(((Words::word *)a)->letters, ((Words::word *)b)->letters));
}

Words::Words(const char *from) {
	count = 0;
	add(from);
}

std::ostream& operator<<(std::ostream &c, const Words &w) {
//std::ostream & Words::print(std::ostream & c) const{
	for (int i = 0; i < w.count; i++)
		if (i < w.count - 1)
			c << w.data[i].letters << ' ';
		else
			c << w.data[i].letters;
//	c << std::endl;
	return (c);
}

std::istream& operator>>(std::istream &c, Words &w) {
//std::istream & Words::scan(std::istream & c) {
	int _count;
	c >> _count;
	if (c.fail())
		throw Words::input_error();
	char buf[Words::word::max_len];
//	char buf[20];
	for (int i = 0; i < _count; i++) {
		if (c.eof())
			throw Words::input_error();
		c >> buf;
		w.add(buf);
	}
	return (c);
}

void Words::add(const char * from) {
	if (strlen(from) > word::max_len)
		throw std::overflow_error("Letters overflow");
	if (count < max_count) {
		strcpy(data[count].letters, from);
		count++;
	}
	else {
		throw std::overflow_error("Words overflow");
	}
}

int Words::find(const char * s) const {
	for (int i = 0; i < count; i++)
		if (strcmp(data[i].letters, s) == 0)
			return (i);
	return (-1);
}

char * Words::operator [](const int i) {
	if (i >= 0 && i < count)
		return (data[i].letters);
	else
		throw std::out_of_range("");
}

Words Words::first_letter(const char c) const {
	Words res;
	int diff = 'a' - 'A';
	if (c > 'Z')
		diff = -diff;
	for (int i = 0; i < count; i++)
		if (data[i].letters[0] == c || data[i].letters[0] == c + diff)
			res.add(data[i].letters);
	return (res);
}

void Words::sort() {
	std::qsort(data, count, sizeof(word), cmp);
}
