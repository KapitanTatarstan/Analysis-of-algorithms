#include "Levenshtein.h"
#include "Matrix.h"

#include <string>
#include <locale>


// prog.exe str1 str2 
int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
	//std::string str1 = "строкааа";
	//std::string str2 = "собака";
	
	if (argc != 3) {
		std::cout << "Недостаточно аргументов командной строки\n";
		return -1;
	}

	std::string str1 = argv[1];
	std::string str2 = argv[2];
	
	/*
	std::string str1 = "si";
	std::string str2 = "arcyu";
	*/
	int len_str1 = str1.size();
	int len_str2 = str2.size();

	Matrix m1(len_str1 + 1, len_str2 + 1);
	Matrix m2(len_str1 + 1, len_str2 + 1);

	LevenshteinMatrix(str1, str2, m1);
	m1.PrintInText(m1, "resultMatrix.txt");

	LevenshteinModifMatrix(str1, str2, m2);
	m2.PrintInText(m2, "resultModMatrix.txt");

	int count = 0;

	std::cout << "LevenshteinRec Cost = " << LevenshteinRec(str1, len_str1, str2, len_str2, count) << "\n";
	//std::cout << "Количество вызовов рекурсии = " << count << "\n";

	system("pause");
    return 0;
}

