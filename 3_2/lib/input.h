#ifndef INPUT_H
#define INPUT_H
#define MAX_INT 2e9

class input_out_of_range : std::exception {};
class input_end_of_file : std::exception {};
class input_bad_input : std::exception {};

double get_double(double l = -MAX_INT, double r = MAX_INT);

int get_int(int l = -MAX_INT, int r = MAX_INT);

#endif
