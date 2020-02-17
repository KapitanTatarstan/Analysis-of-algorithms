#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

#include "rand_num.h"



class Matrix {

public:
	int col;				// Количество элементов в столбце
	int line;				// Количество элементов в строке

	double **matr;			// Указатель на матрицу
	double *rowFactor;		// Произведение соседних элементов в первом векторе  (строке)
	double *columnFactor;	// Произведение соседних элементов во втором векторе (столбце)

public:
	// Конструктор
	Matrix(const int x, const int y);

	// Деструктор
	~Matrix();

	// Заполнение матрицы случайными числами
	void Filling(Matrix &m, const int firstValue, const int lastValue);
	
	// Вывод матрицы в текстовый файл
	void PrintInText(Matrix &m, const char* txtName);


	// Базовое умножение матриц
	void ClassicMultiplication(Matrix &, Matrix &, Matrix &);

	// Умножение матриц алгоритмом Винограда
	void VinogradMultiplication(Matrix &m1, Matrix &m2, Matrix &result);

	// Умножение матриц улучшенным алгоритмом Винограда
	void VinogradImprovedMultiplication(Matrix &m1, Matrix &m2, Matrix &result);

};
