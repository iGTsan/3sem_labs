#include "words.h"
#include <string>
#include <string.h>
#include <stdexcept>

Words::Words(const int _count, std::string from[]) {
//	count = 0;
//	std::cout << *from << std::endl;
	if (_count > max_count)
		throw std::overflow_error("Words overflow");
	for (int i = 0; i < _count; i++) {
		if (from[i].size() > word::max_len)
			throw std::overflow_error("Letters overflow");
		strcpy(data[i].letters, from[i].c_str());
//		for (int j = 0; j < (int) from[i].size(); j++)
//			data[i].letters[j] = from[i][j];
	}
	count = _count;
}

int cmp(const void *a, const void *b) {
	return (strcmp(((Words::word *)a)->letters, ((Words::word *)b)->letters));
}

Words::Words(const char *from) {
	int len = strlen(from);
	if (len > word::max_len)
		throw std::overflow_error("Letters overflow");
	strcpy(data[0].letters, from);
	count = 1;
}

std::ostream & Words::print(std::ostream & c) {
	for (int i = 0; i < count; i++)
		c << data[i].letters << ' ';
	c << std::endl;
	return (c);
}
std::istream & Words::scan(std::istream & c) { //throw
	int _count;
	c >> _count;
	char buf[word::max_len];
	for (int i = 0; i < _count; i++) {
		c >> buf;
		this->add(buf);
	}
	return (c);
}
void Words::add(const char * from) {
	if (count < max_count){
		strncpy(data[count].letters, from, word::max_len);
		count++;
	}
	else
		throw std::overflow_error("Overflow");
}
int Words::find(const char * s) {
	for (int i = 0; i < count; i++)
		if (strcmp(data[i].letters, s))
			return (i);
	return (-1);
}
char * Words::index(int i) {
	if (i >= 0 && i < count)
		return (data[i].letters);
	else
		throw std::range_error("Incorrect index");
}
Words Words::first_letter(char c) {
	Words res;
	int diff = 'a' - 'A';
	if (c > 'Z')
		diff = -diff;
	for (int i = 0; i < c; i++)
		if (data[i].letters[0] == c || data[i].letters[0] == c + diff)
			res.add(data[i].letters);
	return (res);
}
void Words::sort() {
	std::qsort(data, count, sizeof(word), cmp);
}
