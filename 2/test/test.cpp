#include <gtest/gtest.h>
#include "../lib/cartesian.h"

/*
Cartesian ();
Cartesian (double);
Cartesian (const Cartesian&);
double get ();
void set (double);
double chord ();
double dist (double);
double r_vertex();
double r_point();
double square();
double max_len();
double dist_to_max();
*/

TEST(Constructor, DefConstructor) {
	Cartesian a;
	ASSERT_NEAR(1, a.get(), 1e-6);
}

TEST(Constructor, InitConstructor) {
	Cartesian a(2), a2(7), a3(-4), a4(-1000000);
	ASSERT_NEAR(2, a.get(), 1e-6);
	ASSERT_NEAR(7, a2.get(), 1e-6);
	ASSERT_NEAR(-4, a3.get(), 1e-6);
	ASSERT_NEAR(-1000000, a4.get(), 1e-6);
}

TEST(Constructor, CopyConstructor) {
	Cartesian a(2), a2(7);
	Cartesian  a3(a), a4(a2);
	ASSERT_NEAR(2, a.get(), 1e-6);
	ASSERT_NEAR(7, a2.get(), 1e-6);
	ASSERT_NEAR(2, a3.get(), 1e-6);
	ASSERT_NEAR(7, a4.get(), 1e-6);
}

TEST(Methods, SetGetMethods) {
	Cartesian a, b, c, d;
	a.set(-1);
	b.set(100);
	c.set(-1000);
	d.set(8);
	ASSERT_NEAR(-1, a.get(), 1e-6);
	ASSERT_NEAR(100, b.get(), 1e-6);
	ASSERT_NEAR(-1000, c.get(), 1e-6);
	ASSERT_NEAR(8, d.get(), 1e-6);
}

TEST(Methods, MathMethods) {
	Cartesian a(7), b(-10);
	 ASSERT_NEAR(14.8492, a.chord(), 1e-3);
	 ASSERT_NEAR(11.4882, a.dist(9), 1e-3);
	 ASSERT_NEAR(1.85616, a.r_vertex(), 1e-3);
	 ASSERT_NEAR(10.5, a.r_point(), 1e-3);
	 ASSERT_NEAR(73.5, a.square(), 1e-3);
	 ASSERT_NEAR(6.74403, a.max_len(), 1e-3);
	 ASSERT_NEAR(8.57321, a.dist_to_max(), 1e-3);
	 ASSERT_NEAR(21.2132 , b.chord(), 1e-3);
	 ASSERT_NEAR(96.2477 , b.dist(-4), 1e-3);
	 ASSERT_NEAR(2.65165 , b.r_vertex(), 1e-3);
	 ASSERT_NEAR(15 , b.r_point(), 1e-3);
	 ASSERT_NEAR(150 , b.square(), 1e-3);
	 ASSERT_NEAR(9.63433 , b.max_len(), 1e-3);
	 ASSERT_NEAR(12.2474 , b.dist_to_max(), 1e-3);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}