#include <gtest/gtest.h>
#include "../words.h"
#include <string>


TEST(Words, InitConstructor) {
	ASSERT_NO_THROW(Words a);
	Words b("abc");
	ASSERT_EQ(strcmp(b.index(0), "abc"), 0);
	std::string s[] = {"First", "second", "Third", "fourth", "Fifth"};
	Words c(5, s);
	ASSERT_EQ(strcmp(c.index(2), s[2].c_str()), 0);
//	std::string output = testing::internal::GetCapturedStdout();
}

TEST(Words, Input) {
	std::string input_string_1 = "3 abc cda ghf";
	std::stringstream input_stream_1(input_string_1);
	std::string input_string_2 = "0";
	std::stringstream input_stream_2(input_string_2);
	std::string input_string_3 = "3 abc cda";
	std::stringstream input_stream_3(input_string_3);
	Words a;
	a.scan(input_stream_1);
	ASSERT_EQ(strcmp(a.index(2), "ghf"), 0);
	a.scan(input_stream_2);

}

TEST(Methods, SetGetMethods) {

}

TEST(Methods, MathMethods) {

}
/*
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
*/



