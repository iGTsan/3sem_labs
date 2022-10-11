#ifndef WORDS_H_
#define WORDS_H_

#include <iostream>
#include <string>



class Words {
private:
	typedef struct word {
		int len = 0;
		static const int max_len = 64;
		char letters[max_len + 1];
	} word;
//	static int cmp(word *, word *);
	static const int max_count = 64;
	int count;
	word data[max_count + 1];
	friend int cmp(const void*, const void*);
public:
	Words() : count(0) {};
	Words(const int, std::string[]);
	Words(const char *);
	std::ostream & print(std::ostream &);
	std::istream & scan(std::istream &);
	void add(const char *);
	int find(const char *);
	char * index(int);
	Words first_letter(char);
	void sort();
};

#endif
