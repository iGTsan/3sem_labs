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
	ASSERT_NEAR(1, a.get_coef(), 1e-6);
}

TEST(Constructor, InitConstructor) {
	Cartesian a(2), a2(7), a3(-4), a4(-1000000);
	ASSERT_NEAR(2, a.get_coef(), 1e-6);
	ASSERT_NEAR(7, a2.get_coef(), 1e-6);
	ASSERT_NEAR(-4, a3.get_coef(), 1e-6);
	ASSERT_NEAR(-1000000, a4.get_coef(), 1e-6);
}

TEST(Constructor, CopyConstructor) {
	Cartesian a(2), a2(7);
	Cartesian  a3(a), a4(a2);
	ASSERT_NEAR(2, a.get_coef(), 1e-6);
	ASSERT_NEAR(7, a2.get_coef(), 1e-6);
	ASSERT_NEAR(2, a3.get_coef(), 1e-6);
	ASSERT_NEAR(7, a4.get_coef(), 1e-6);
}

TEST(Methods, SetGetMethods) {
	Cartesian a, b, c, d;
	a.set_coef(-1);
	b.set_coef(100);
	c.set_coef(-1000);
	d.set_coef(8);
	ASSERT_NEAR(-1, a.get_coef(), 1e-6);
	ASSERT_NEAR(100, b.get_coef(), 1e-6);
	ASSERT_NEAR(-1000, c.get_coef(), 1e-6);
	ASSERT_NEAR(8, d.get_coef(), 1e-6);
}

TEST(Methods, MathMethods) {
	Cartesian a(7), b(-10);
	 ASSERT_NEAR(14.8492, a.get_chord(), 1e-3);
	 ASSERT_NEAR(11.4882, a.get_dist(9), 1e-3);
	 ASSERT_NEAR(1.85616, a.get_r_vertex(), 1e-3);
	 ASSERT_NEAR(10.5, a.get_r_point(), 1e-3);
	 ASSERT_NEAR(73.5, a.get_square(), 1e-3);
	 ASSERT_NEAR(6.74403, a.get_max_len(), 1e-3);
	 ASSERT_NEAR(8.57321, a.get_dist_to_max(), 1e-3);
	 ASSERT_NEAR(21.2132 , b.get_chord(), 1e-3);
	 ASSERT_NEAR(96.2477 , b.get_dist(-4), 1e-3);
	 ASSERT_NEAR(2.65165 , b.get_r_vertex(), 1e-3);
	 ASSERT_NEAR(15 , b.get_r_point(), 1e-3);
	 ASSERT_NEAR(150 , b.get_square(), 1e-3);
	 ASSERT_NEAR(9.63433 , b.get_max_len(), 1e-3);
	 ASSERT_NEAR(12.2474 , b.get_dist_to_max(), 1e-3);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}