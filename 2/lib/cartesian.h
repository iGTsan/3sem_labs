#ifndef CARTESIAN_H
#define CARTESIAN_H

class Cartesian  {
	/* 
	x^3 + y^3 = -3nxy
	S = 1.5n^2
	*/
public:
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

private:
	double n;
};

#endif