#include "Array.h"





Array::Array(int size) {
	this->size = size;
	this->mas = nullptr;
	try {
		this->mas = new double[size];
	}
	catch (...) {
		Array::~Array();
	}
}


Array::~Array() {
	if (this->mas == nullptr) 
		delete[] mas;
}


void Array::Copy(Array &obj1, Array &obj2, const int size) {
	for (int i = 0; i < size; ++i)
		obj2.mas[i] = obj1.mas[i];
}


void Array::Filling(Array &obj, const int min, const int max) {
	for (int i = 0; i < obj.size; ++i)
		obj.mas[i] = RandDouble(min, max);
	return;
}


void Array::PrintInText(Array &obj, const char *txtName) {
	std::ofstream f(txtName);
	for (int i = 0; i < obj.size; ++i)
		f << obj.mas[i] << "  ";

	f.close();
	return;
}





void Array::GnomeSort(double *A, int N) {
	int i = 0;
	while (i < N) {
		if (i == 0 || A[i - 1] <= A[i])
			++i;
		else {
			double Temp = A[i];
			A[i] = A[i - 1];
			A[i - 1] = Temp;
			--i;
		}
	}
}


void Array::BubbleSort(double *A, const int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			double buf = A[j];
			A[j] = A[j + 1];
			A[j + 1] = buf;
		}
	}
}