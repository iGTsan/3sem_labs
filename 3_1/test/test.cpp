#include <gtest/gtest.h>
#include "../lib/words.h"
#include <string>
#include <stdexcept>

using std::string;

Words some_Words() {
	string s[] = {"First", "second", "Third", "fourth", "Fifth"};
	Words a(5, s);
	return (a);
}

void more_Words(Words &a, int n) {
	string s[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
	for (int i = 0; i < n; i++)
		a.add(s[i].c_str());
}

string print_Words(Words &a) {
	testing::internal::CaptureStdout();
	a.print(std::cout);
	string output = testing::internal::GetCapturedStdout();
	return (output);
}

TEST(Words, Output) {
	Words a = some_Words();
	string output = print_Words(a);
	ASSERT_EQ(strcmp(output.c_str(), "First second Third fourth Fifth \n"), 0);
}

TEST(Words, InitConstructor) {
	ASSERT_NO_THROW(Words a);
	Words b("abc");
	ASSERT_THROW(Words bad("12345678901"), std::overflow_error);
	string output = print_Words(b);
	ASSERT_EQ(strcmp(output.c_str(), "abc \n"), 0);
	string s[] = {"First", "second", "Third", "fourth", "Fifth"};
	Words c(5, s);
	string bads[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "1"};
	ASSERT_THROW(Words bad(11, bads), std::overflow_error);
	output = print_Words(c);
	ASSERT_EQ(strcmp(output.c_str(), "First second Third fourth Fifth \n"), 0);
}

TEST(Words, Input) {
	std::stringstream input_stream;
	input_stream << "3 abc cda ghf\n";
	Words a;
	a.scan(input_stream);
	string output = print_Words(a);
	ASSERT_EQ(strcmp(output.c_str(), "abc cda ghf \n"), 0);
	input_stream << "0";
	a.scan(input_stream);
	output = print_Words(a);
	ASSERT_EQ(strcmp(output.c_str(), "abc cda ghf \n"), 0);
	input_stream << "3 abc cda";
	ASSERT_THROW(a.scan(input_stream), Words::input_error);
	input_stream << "abc";
	ASSERT_THROW(a.scan(input_stream), Words::input_error);
}


TEST(Words, Add) {
	Words a;
	a.add("abc");
	string output = print_Words(a);
	ASSERT_EQ(strcmp(output.c_str(), "abc \n"), 0);
	more_Words(a, 9);
	a.print(std::cout);
	ASSERT_THROW(a.add("bca"), std::overflow_error);
}

TEST(Words, Find) {
	Words a = some_Words();
	ASSERT_EQ(a.find("Third"), 2);
	ASSERT_EQ(a.find("third"), -1);
}

TEST(Words, Index) {
	Words a = some_Words();
	ASSERT_EQ(strcmp(a.index(1), "second"), 0);
	ASSERT_THROW(a.index(20), std::out_of_range);
}

TEST(Words, FirstLetter) {
	Words a = some_Words();
	Words b = a.first_letter('f');
	Words c = a.first_letter('F');
	Words d = a.first_letter('e');
	string output = print_Words(b);
	ASSERT_EQ(strcmp(output.c_str(), "First fourth Fifth \n"), 0);
	output = print_Words(c);
	ASSERT_EQ(strcmp(output.c_str(), "First fourth Fifth \n"), 0);
	output = print_Words(d);
	ASSERT_EQ(strcmp(output.c_str(), "\n"), 0);
}

TEST(Words, Sort) {
	Words a = some_Words();
	a.sort();
	string output = print_Words(a);
	ASSERT_EQ(strcmp(output.c_str(), "Fifth First Third fourth second \n"), 0);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}