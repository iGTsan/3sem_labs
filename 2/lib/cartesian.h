#ifndef CARTESIAN_H
#define CARTESIAN_H

class Cartesian  {
	/* 
	x^3 + y^3 = -3nxy
	S = 1.5n^2
	*/
public:
	Cartesian ();
	Cartesian (const double);
	Cartesian (const Cartesian&);
	const double get_coef ();
	void set_coef (const double);
	const double get_chord ();
	const double get_dist (const double);
	const double get_r_vertex();
	const double get_r_point();
	const double get_square();
	const double get_max_len();
	const double get_dist_to_max();

private:
	double coef;
};

#endif