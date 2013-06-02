#include <iostream>
#include <fstream>
#include "include/utils.h"

int main (int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage: main <datafile>\n";
		return 1;
	}
	
	std::ifstream data;
	data.open(argv[1]);
	if (data.fail()) {
		std::cout << "Could not open" << argv[1] << "\n";
		return 2;
	}
	
	int mSize;
	// Размер матриц
	data >> mSize;
	// Создаем матрицу C
	int** cMatrix = new int* [mSize];
	for (int i = 0; i < mSize; ++i)
		cMatrix[i] = new int [mSize];

	for (int i = 0; i < mSize; ++i)
		for (int j = 0; j < mSize; ++j)
			data >> cMatrix[i][j];
	
	// Создаем матрицу D
	int** dMatrix = new int* [mSize];
	for (int i = 0; i < mSize; ++i)
		dMatrix[i] = new int [mSize];

	for (int i = 0; i < mSize; ++i)
		for (int j = 0; j < mSize; ++j)
			data >> dMatrix[i][j];

	// Вывод
	std::cout << "=== C matrix ===\n";
	for (int i = 0; i < mSize; ++i) std::cout << "\t" << i; std::cout << "\n";
	for (int i = 0; i < mSize; ++i) std::cout << "\t---"; std::cout << "\n";
	for (int i = 0; i < mSize; ++i) {
		std::cout << i << "|\t";
		for (int j = 0; j < mSize; ++j) {
			if (cMatrix[i][j] < 0) std::cout << "X\t";
			else std::cout << cMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "=== D matrix ===\n";
	for (int i = 0; i < mSize; ++i) std::cout << "\t" << numToChar(i); std::cout << "\n";
	for (int i = 0; i < mSize; ++i) std::cout << "\t---"; std::cout << "\n";
	for (int i = 0; i < mSize; ++i) {
		std::cout << numToChar(i) << "|\t";
		for (int j = 0; j < mSize; ++j) {
			if (dMatrix[i][j] < 0) std::cout << "X\t";
			else std::cout << dMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	
	// Решение
	std::string solution = solve (cMatrix, dMatrix, mSize);
	std::cout << "\n=== Solution ===\n" << solution;
	
	for (int i = 0; i < mSize; ++i)
		delete [] cMatrix[i];
	delete [] cMatrix;
	for (int i = 0; i < mSize; ++i)
		delete [] dMatrix[i];
	delete [] dMatrix;
	
	return 0;
}