#pragma once

#include <iostream>
#include <fstream>


class Matrix {
public:
	int row;
	int col;

	int **m;

	Matrix(const int row, const int col);
	~Matrix();

	void PrintInText(Matrix &m, const char* txtName);
};