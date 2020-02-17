#include "matrix.h"
#include <omp.h>

#define PARALLELS true


Matrix::Matrix(const int x, const int y) {
	col = x;
	line = y;

	try {
		matr = new double*[col];
		for (int i = 0; i < col; ++i) {
			matr[i] = new double[line];
		}

		rowFactor = new double[col];
		columnFactor = new double[line];

	}
	catch (...) {
		Matrix::~Matrix();
	}

	return;
}


Matrix::~Matrix() {
	for (int i = 0; i < col; ++i)
		delete[] matr[i];
	delete[] matr;

	delete[] rowFactor;
	delete[] columnFactor;

	return;
}


void Matrix::Filling(Matrix &m, const int minValue, const int maxValue) {
	for (int i = 0; i < m.col; ++i)
		for (int j = 0; j < m.line; ++j)
			m.matr[i][j] = (int) RandDouble(minValue, maxValue);
}


void Matrix::PrintInText(Matrix &m, const char* txtName) {
	std::ofstream f(txtName);
	for (int i = 0; i < m.col; ++i) {
		for (int j = 0; j < m.line; ++j)
			f << matr[i][j] << "   ";
		f << "\n";
	}
	f.close();
}


void Matrix::ClassicMultiplication(Matrix &m1, Matrix &m2, Matrix &result) {
	#if PARALLELS
	#pragma omp parallel for
	#endif
	for (int i = 0; i < m1.col; ++i) {
		for (int j = 0; j < m2.line; ++j) {
			result.matr[i][j] = 0;
			for (int k = 0; k < m1.line; ++k)
				result.matr[i][j] = result.matr[i][j] + m1.matr[i][k] * m2.matr[k][j];
		}
	}
	return;
}


void Matrix::VinogradMultiplication(Matrix &m1, Matrix &m2, Matrix &result) {
	int d = m1.line / 2; // 1

	// Вычисление rowFactors для m1
	#if PARALLELS
	#pragma omp parallel for
	#endif
	for (int i = 0; i < m1.col; ++i) { //2
		m1.rowFactor[i] = m1.matr[i][0] * m1.matr[i][1]; //3
		for (int j = 1; j < d; ++j) // 4
			m1.rowFactor[i] = m1.rowFactor[i] + m1.matr[i][2 * j] * m1.matr[i][2 * j + 1]; // 5
	}

	// Вычисление columnFactor для m2
	#if PARALLELS
	#pragma omp parallel for
	#endif
	for (int i = 0; i < m2.line; ++i) { // 6
		m2.columnFactor[i] = m2.matr[0][i] * m2.matr[1][i]; //7 
		for (int j = 1; j < d; ++j) // 8
			m2.columnFactor[i] = m2.columnFactor[i] + m2.matr[2 * j][i] * m2.matr[2 * j + 1][i]; //9
	}

	// Вычисление матрицы result
	#if PARALLELS
	#pragma omp parallel for 
	#endif
	for (int i = 0; i < m1.col; ++i) { //10 
		for (int j = 0; j < m2.line; ++j) { //11
			result.matr[i][j] = -m1.rowFactor[i] - m2.columnFactor[j];//12
			
			for (int k = 0; k < d; ++k) //13
				result.matr[i][j] = result.matr[i][j] + (m1.matr[i][2 * k] + m2.matr[2 * k + 1][j]) 
													   *(m1.matr[i][2 * k + 1] + m2.matr[2 * k][j]); //14
		}
	}



	if (m1.line % 2 == 1) { //15
		#if PARALLELS
		#pragma omp parallel for
		#endif
		for (int i = 0; i < m1.col; ++i) //16
			for (int j = 0; j < m2.line; ++j) //17
				result.matr[i][j] = result.matr[i][j] + m1.matr[i][m1.line - 1] * m2.matr[m2.line - 1][j]; //18
	}
	return; /19
}


void Matrix::VinogradImprovedMultiplication(Matrix &m1, Matrix &m2, Matrix &result) {
	int d = m1.line / 2;
	bool flag = m1.line % 2 == 1;
	

	// Вычисление rowFactors для m1
	#if PARALLELS
	#pragma omp parallel for
	#endif
	for (int i = 0; i < m1.col; ++i) {
		m1.rowFactor[i] = m1.matr[i][0] * m1.matr[i][1];
		for (int j = 1; j < d; ++j)
			m1.rowFactor[i] += m1.matr[i][2 * j] * m1.matr[i][2 * j + 1];
	}

	// Вычисление columnFactor для m2
	#if PARALLELS
	#pragma omp parallel for 
	#endif
	for (int i = 0; i < m2.line; ++i) {
		m2.columnFactor[i] = m2.matr[0][i] * m2.matr[1][i];
		for (int j = 1; j < d; ++j)
			m2.columnFactor[i] += m2.matr[2 * j][i] * m2.matr[2 * j + 1][i];
	}


	
	// Вычисление матрицы result
	#if PARALLELS
	#pragma omp parallel for 
	#endif
	for (int i = 0; i < m1.col; ++i) {
		double buf = 0.0;
		for (int j = 0; j < m2.line; ++j) {
			buf = (flag ? m1.matr[i][m1.line - 1] * m2.matr[m2.line - 1][j] : 0);
			buf -= m1.rowFactor[i] + m2.columnFactor[j];
			
			for (int k = 0; k < d; ++k)
				buf += (m1.matr[i][2 * k] + m2.matr[2 * k + 1][j]) * 
				       (m1.matr[i][2 * k + 1] + m2.matr[2 * k][j]);

			result.matr[i][j] = buf;
		}
	}

	
	return;
}

