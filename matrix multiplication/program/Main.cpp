#include "matrix.h"

#include <iostream>
#include <ctime>
#include <chrono>
#include <omp.h>
#include <intrin.h>  

unsigned __int64 tick(void) {
	return (__rdtsc());
}

// int n, int countMult, int min, int max 
int main(int argc, char **argv) {
	setlocale(LC_ALL, "Russian");
	
	if (argc != 5) {
		std::cout << "Недостаточно аргументов командной строки\n";
		return -2;
	}
	
	int col, line;
	int min, max;
	int countMultiplication;

	try {
		col = line = std::strtol(argv[1], NULL, 10);
		countMultiplication = std::strtol(argv[2], NULL, 10);
		min = std::strtol(argv[3], NULL, 10);
		max = std::strtol(argv[4], NULL, 10);
	}
	catch (...) {
		return -4;
	}
	
	/*
	int min = -5; 
	int max = 5;
	int countMultiplication = 10;
	int col = 100, line = 100;
	*/

	srand(time(0));

	Matrix m1(col, line);
	Matrix m2(col, line);

	Matrix m3(col, line);
	Matrix m4(col, line);
	Matrix m5(col, line);

	char error[] = "Неправильная размерность матриц для умножения\n";
	try {
		if (m1.col != m2.line)
			throw error;
	}
	catch (...) {
		std::cout << error;
		system("pause");
		return -1;
	}


	m1.Filling(m1, min, max);
	m2.Filling(m2, min, max);

	__int64 time1 = 0, time2 = 0, time3 = 0, bufTime, bufTime2;

	for (int i = 0; i < countMultiplication; ++i) {	
		bufTime = tick();
		m3.ClassicMultiplication(m1, m2, m3);
		bufTime2 = tick();
		time1 += bufTime2 - bufTime;
		
		bufTime = tick();
		m4.VinogradMultiplication(m1, m2, m4);
		bufTime2 = tick();
		time2 += bufTime2 - bufTime;

		bufTime = tick();
		m5.VinogradImprovedMultiplication(m1, m2, m5);
		bufTime2 = tick();
		time3 += bufTime2 - bufTime;
	}

	std::cout << "\n" << "Размер: " << col << "x" << line << "\n\n";
	std::cout << "Стандартное умножение :  " << time1/countMultiplication << "\n";
	std::cout << "Виноградов:              " << time2/countMultiplication << "\n";
	std::cout << "Улуч. Виноградов:        " << time3/countMultiplication << "\n";

	std::cout << "------------------------------------------------\n\n\n\n";
	
	
	m1.PrintInText(m1, "1.txt");
	m2.PrintInText(m2, "2.txt");
	m3.PrintInText(m3, "ClassicMul.txt");
	m4.PrintInText(m4, "WinogradMul.txt");
	m5.PrintInText(m5, "WinogradImpMul.txt");
	
	//system("pause");

    return 0;
}

