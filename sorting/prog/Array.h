#pragma once

#include <fstream>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>

#include "rand_num.h"



class Array {
public:
	int size;
	

	double *mas;


	Array(int size);
	~Array();

	void Filling(Array &, const int min, const int max);

	void Copy(Array&, Array&, const int size);

	void PrintInText(Array &, const char *txtname);


	void GnomeSort(double *A, int N);

	void BubbleSort(double *, const int);


};