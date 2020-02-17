#pragma once


#include "Matrix.h"

#include <string>
#include <iostream>
#include <fstream>

void LevenshteinMatrix(std::string s1, std::string s2, Matrix &);


void LevenshteinModifMatrix(std::string s1, std::string s2, Matrix &);

int LevenshteinRec(std::string s1, int m, std::string s2, int n, int& count);