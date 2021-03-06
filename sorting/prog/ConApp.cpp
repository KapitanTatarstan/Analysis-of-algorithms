#include "Array.h"
#include "Tick.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <locale.h>



/*
double swap(const (void*) &a, const (void*) &b) {
	return (*(double*) a - *(double*) b);
}
*/
int cmp_double(const void *i, const void *j)
{
	const double *a = (double *)i;
	const double *b = (double *)j;

	if ((*a - *b) > 0)
		return 1;
	if ((*a - *b) < 0)
		return -1;
	return 0;
}


// *.exe countSort sizeArray min max
int main(int argc, char **argv) {
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	if (argc != 5) {
		std::cout << "Недостаточно аргументов командной строки\n";
		return -2;
	}

	int countSort;
	int sizeArray;
	int min;
	int max;

	try {
		countSort = std::strtol(argv[1], NULL, 10);
		sizeArray = std::strtol(argv[2], NULL, 10);
		min = std::strtol(argv[3], NULL, 10);
		max = std::strtol(argv[4], NULL, 10);
	}
	catch (...) {
		return -4;
	}
	/*

	int min = -5; 
	int max = 5;
	int sizeArray = 15000;
	int countSort = 10;
	*/
	if (min > max) {
		return -1;
	}

	Array obj0(sizeArray);
	Array obj1(sizeArray);
	Array obj2(sizeArray);
	Array obj3(sizeArray);

	obj0.Filling(obj0, min, max);

	
	//obj1.PrintInText(obj1, "До.txt");
	
	__int64 time1 = 0, time2 = 0, time3 = 0, startTime = 0, endTime = 0;
	for (int i = 0; i < countSort; ++i) {
		obj1.Copy(obj0, obj1, obj0.size);
		obj2.Copy(obj0, obj2, obj1.size);
		obj3.Copy(obj0, obj3, obj1.size);

		startTime = tick();
		qsort(obj1.mas, obj1.size, sizeof(double), cmp_double); 
		endTime = tick();
		time1 += endTime - startTime;


		startTime = tick();
		obj2.GnomeSort(obj2.mas, obj2.size);
		endTime = tick();
		time2 += endTime - startTime;


		startTime = tick();
		obj3.BubbleSort(obj3.mas, obj3.size);
		endTime = tick();
		time3 += endTime - startTime;
	}
	//obj1.PrintInText(obj1, "После.txt");
	//obj2.PrintInText(obj2, "После2.txt");

	std::cout << "size array:        " << sizeArray << "\n\n";
	std::cout << "qsort time:        " << time1 / countSort << "\n\n";
	std::cout << "gnome sort time:   " << time2 / countSort << "\n\n";
	std::cout << "Bubble sort time:  " << time3 / countSort << "\n\n";
	std::cout << "----------------------------\n\n\n\n";

	//system("pause");

    return 0;
}

