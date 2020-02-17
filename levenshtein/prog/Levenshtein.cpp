#include "Levenshtein.h"

int CustomMin(int c1, int c2, int c3) {
	int min;
	if (c1 < c2)
		min = c1;
	else
		min = c2;

	if (min > c3)
		min = c3;

	return min;
}

void PrintInText(int **matrix, const int n, const int m, const char* txtName) {
	std::ofstream f(txtName);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			f << matrix[i][j] << "   ";
		f << "\n";
	}
	f.close();
}

void LevenshteinMatrix(std::string str1, std::string str2, Matrix &matrix) {
	int n = str1.size();
	int m = str2.size();

	int cost = 0;

	for (int i = 0; i < n + 1; ++i)
		matrix.m[i][0] = i;
	for (int i = 0; i < m + 1; ++i)
		matrix.m[0][i] = i;

	for (int i = 1; i < n + 1; ++i) {
		for (int j = 1; j < m + 1; ++j) {
			cost = (str1[i - 1] == str2[j - 1] ? 0 : 1);
			matrix.m[i][j] = CustomMin(matrix.m[i - 1][j] + 1, 
									   matrix.m[i][j-1] + 1, 
									   matrix.m[i-1][j-1] + cost);
		}
	}

	/*
	PrintInText(matrix, n + 1, m + 1, "resultMatrix.txt");
	for (int i = 0; i < n + 1; ++i)
		delete[] matrix[i];
	delete[] matrix;
	
	return;
}


void LevenshteinModifMatrix(std::string str1, std::string str2, Matrix &matrix) {
	int n = str1.size();  						// 1
	int m = str2.size();					
	
	for (int i = 0; i < n + 1; ++i)					// 2
		matrix.m[i][0] = i;					// 3
	for (int i = 0; i < m + 1; ++i)					// 4
		matrix.m[0][i] = i;					// 5


	for (int i = 1; i < n + 1; ++i) {									// 6
		for (int j = 1; j < m + 1; ++j) {								// 7
			int insert = matrix.m[i - 1][j] + 1;							// 8
			int del = matrix.m[i][j - 1] + 1;							
			int repl = matrix.m[i - 1][j - 1] + (str1[i - 1] == str2[j - 1] ? 0 : 1);	

			int min = CustomMin(insert, del, repl);							

			if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1]) { 	// 9
				int swap = matrix.m[i - 2][j - 2] + 1;						// 10
				min = (swap < min ? swap : min);						
			}
			matrix.m[i][j] = min;									// 11
		}
	}

	return;	// 12
}



int LevenshteinRec(std::string s1, int n, std::string s2, int m, int& count) {
	if (n == 0 && m == 0)
		return 0;
	if (n == 0)
		return m;
	if (m == 0)
		return n;

	int insert = LevenshteinRec(s1, n, s2, m - 1, ++count) + 1;
	int del = LevenshteinRec(s1, n - 1, s2, m, ++count) + 1;
	int repl = LevenshteinRec(s1, n - 1, s2, m - 1, ++count) + (s1[n - 1] == s2[m - 1] ? 0 : 1);
	
	

	return CustomMin(repl, del, insert);
}

