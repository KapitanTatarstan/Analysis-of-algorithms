#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

#include "rand_num.h"



class Matrix {

public:
	int col;				// ���������� ��������� � �������
	int line;				// ���������� ��������� � ������

	double **matr;			// ��������� �� �������
	double *rowFactor;		// ������������ �������� ��������� � ������ �������  (������)
	double *columnFactor;	// ������������ �������� ��������� �� ������ ������� (�������)

public:
	// �����������
	Matrix(const int x, const int y);

	// ����������
	~Matrix();

	// ���������� ������� ���������� �������
	void Filling(Matrix &m, const int firstValue, const int lastValue);
	
	// ����� ������� � ��������� ����
	void PrintInText(Matrix &m, const char* txtName);


	// ������� ��������� ������
	void ClassicMultiplication(Matrix &, Matrix &, Matrix &);

	// ��������� ������ ���������� ���������
	void VinogradMultiplication(Matrix &m1, Matrix &m2, Matrix &result);

	// ��������� ������ ���������� ���������� ���������
	void VinogradImprovedMultiplication(Matrix &m1, Matrix &m2, Matrix &result);

};
