#include <iostream>
#include <fstream>
#include "include/utils.h"
#include "include/time_meter.h"

int main (int argc, char** argv) {
	// Если программе не было передано имени файла с данными,
	// запускается автотестирование.
	if (argc < 2) {
		std::cout << "Usage: main <datafile>\n";
		std::cout << "Start autotesting...\n";
		
		srand( time(NULL) );
		std::ofstream out ("out.txt");
		
		// Будем увеличивать количество ребер на один, до тех пор пока
		// не дойдем до полного графа. После этого увеличим количество вершин
		// на 5 и вновь начнем с одного ребра.
		// Определим также на каком количестве вершин остановимся.
		size_t maxVertexes = 500;
		size_t vertexIncrementStep = 50;
		size_t edgesIncrementStep = 5000;
		int maxWeight = 100;

		for (size_t mSize = vertexIncrementStep; mSize <= maxVertexes;
			mSize += vertexIncrementStep) {
			for (size_t nEdges = edgesIncrementStep; nEdges <= mSize * (mSize - 1) / 2;
				nEdges += edgesIncrementStep) {
				int** matrix = NULL;
				initRandomGraph(matrix, mSize, nEdges, maxWeight);
				
				// Находим МОД.
				TimeMeter::init();
				solve (matrix, mSize);
				float pastTime = TimeMeter::getPastTime();
				// Выводим время работы.
				std::cout << "mSize = " << mSize << "\tnEdges = " << nEdges
					<< "\ttime = " << pastTime << std::endl;
				out << "mSize = " << mSize << "\tnEdges = " << nEdges
					<< "\ttime = " << pastTime << std::endl;
				
				// Освобождаем память
				for (size_t i = 0; i < mSize; ++i)
					delete [] matrix[i];
				delete [] matrix;
			}
		}
		
		out.close();
		return 0;
	}
	
	std::ifstream data;
	data.open(argv[1]);
	if (data.fail()) {
		std::cout << "Could not open" << argv[1] << "\n";
		return 1;
	}
	
	size_t mSize;
	// Размер матрицы
	data >> mSize;
	// Создаем матрицу смежности взвешенного графа
	int** matrix = new int* [mSize];
	for (size_t i = 0; i < mSize; ++i)
		matrix[i] = new int [mSize];
	// Заполняем ее входными данными
	for (size_t i = 0; i < mSize; ++i)
		for (size_t j = 0; j < mSize; ++j)
			data >> matrix[i][j];

	// Вывод
	printMatrix(matrix, mSize);
	
	// Решение
	std::string solution = solve (matrix, mSize);
	std::cout << "\n=== Solution ===\n" << solution;
	
	for (size_t i = 0; i < mSize; ++i)
		delete [] matrix[i];
	delete [] matrix;
	
	return 0;
}