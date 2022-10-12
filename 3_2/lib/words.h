#ifndef WORDS_H_
#define WORDS_H_

#include <iostream>
#include <string>
#include <string.h>
#include <stdexcept>



class Words {
private:
	typedef struct word {
		int len = 0;
		static const int max_len = 10;
		char letters[max_len + 1];
	} word;

	static const int max_count = 10;
	int count;
	word data[max_count + 1];
public:
	Words() : count(0) {};
	Words(const int, const std::string[]);
	Words(const char *);

	void add(const char *);
	int find(const char *) const;
	char * operator [](const int);
	Words first_letter(const char) const;
	void sort();

	class input_error : std::exception {};
	friend std::ostream& operator<<(std::ostream &, const Words &);
	friend std::istream& operator>>(std::istream &, Words &);
	friend int cmp(const void*, const void*);
};

#endif
