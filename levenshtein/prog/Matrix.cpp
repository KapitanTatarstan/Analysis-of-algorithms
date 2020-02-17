#include "Matrix.h"



Matrix::Matrix(const int n, const int k) {
	row = n;
	col = k;
	try {
		m = new int*[row+1];
		for (int i = 0; i < row+1; ++i) {
			m[i] = new int[col+1];
		}
	}
	catch (...) {
		Matrix::~Matrix();
	}

	return;
}


Matrix::~Matrix() {
	for (int i = 0; i < row; ++i)
		delete[] m[i];
	delete[] m;

	return;
}


void Matrix::PrintInText(Matrix &matrix, const char* txtName) {
	std::ofstream f(txtName);
	for (int i = 0; i < matrix.row; ++i) {
		for (int j = 0; j < matrix.col; ++j)
			f << matrix.m[i][j] << "   ";
		f << "\n";
	}
	f.close();
}