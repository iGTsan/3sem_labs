
#include <gtest/gtest.h>
#include "../lib/words.h"
#include <string>
#include <stdexcept>

using std::string;

string s1[] = {"First", "second", "Third", "fourth", "Fifth"};
string s2[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
string _s1 = "First second Third fourth Fifth";
string _s2 = "1 2 3 4 5 6 7 8 9 0";
string _s3 = "abc";

Words some_Words() {

	Words a(5, s1);
	return (a);
}

void more_Words(Words &a, int n) {
	for (int i = 0; i < n; i++)
		a += s2[i];
}

string print_Words(Words &a) {
	testing::internal::CaptureStdout();
	std::cout << a;
	string output = testing::internal::GetCapturedStdout();
	return (output);
}

TEST(Words, Output) {
	Words a = some_Words();
	string output = print_Words(a);
	ASSERT_EQ(output, _s1);
}

TEST(Words, InitConstructor) {
	ASSERT_NO_THROW(Words a);

	Words b(_s3);
	string output = print_Words(b);
	ASSERT_EQ(output, _s3);

	Words c(5, s1);
	output = print_Words(c);
	ASSERT_EQ(output, _s1);

	Words d(c);
	output = print_Words(d);
	ASSERT_EQ(output, _s1);
}

TEST(Words, Input) {
	std::stringstream input_stream;

	input_stream << "3 abc cda ghf\n";
	Words a;
	input_stream >> a;
	string output = print_Words(a);
	ASSERT_EQ(output, "abc cda ghf");

	input_stream << "0";
	input_stream >> a;
	output = print_Words(a);
	ASSERT_EQ(output, "abc cda ghf");

	input_stream << "3 abc cda";
	ASSERT_THROW(input_stream >> a, Words::input_error);

	input_stream << "abc";
	ASSERT_THROW(input_stream >> a, Words::input_error);
}


TEST(Words, Add) {
	Words a;
	a += _s3;
	string output = print_Words(a);
	ASSERT_EQ(output, _s3);
}

TEST(Words, Plus) {
	Words a = some_Words();
	Words b, c;
	more_Words(b, 10);
	c = a + b;
	string output = print_Words(c);
	ASSERT_EQ(output, _s1 + ' ' + _s2);
}

TEST(Words, Find) {
	Words a = some_Words();
	ASSERT_EQ(a["Third"], 2);
	ASSERT_EQ(a["third"], -1);
}

TEST(Words, Index) {
	Words a = some_Words();
	ASSERT_EQ(a[1], "second");
	ASSERT_THROW(a[20], std::out_of_range);
}

TEST(Words, FirstLetter) {
	Words a = some_Words();

	Words b = a.first_letter('f');
	string output = print_Words(b);
	ASSERT_EQ(output, "First fourth Fifth");

	Words c = a.first_letter('F');
	output = print_Words(c);
	ASSERT_EQ(output, "First fourth Fifth");

	Words d = a.first_letter('e');
	output = print_Words(d);
	ASSERT_EQ(output, "");
}

TEST(Words, Sort) {
	Words a = some_Words();
	~a;
	string output = print_Words(a);
	ASSERT_EQ(output, "Fifth First Third fourth second");
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

