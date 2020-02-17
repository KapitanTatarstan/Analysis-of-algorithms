#include "rand_num.h"

double RandDouble(const double min, const double max) {
	//a + (b - a) * (double)rand() / (double)RAND_MAX
	return min + (max - min) * (double)rand() / (double)RAND_MAX;
}



