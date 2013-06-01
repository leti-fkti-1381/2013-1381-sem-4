#include "include/utils.h"
#include <iostream>

Edge::Edge(int v1, int v2, int w) {
	vertex_1 = v1;
	vertex_2 = v2;
	weight = w;
}

Edge::Edge(const Edge& edge) {
	vertex_1 = edge.vertex_1;
	vertex_2 = edge.vertex_2;
	weight = edge.weight;
}

std::string Edge::toString() const {
	std::stringstream ss;
	ss << numToChar(vertex_1) << " -- " << numToStr(weight) << " -- "
		<< numToChar(vertex_2);
	return ss.str();
}

bool Edge::operator< (const Edge& edge) const {
	return weight < edge.weight;
}

void createEdgesVector(int** matrix, int mSize, std::vector<Edge>& v) {
	// Проходимся по матрице
	for (int i = 0; i < mSize; ++i) {
		for (int j = i + 1; j < mSize; ++j) {
			// Если вес ребра больше либо равен нулю, сохраняем это ребро.
			if (matrix[i][j] >= 0) {
				// Создаем ребро
				Edge e (i, j, matrix[i][j]);
				// Сохраняем его в векторе
				v.push_back( e );
			}
		}
	}
	// Сортируем вектор
	std::sort(v.begin(), v.end());
}

bool checkPathExisting(int** matrix, int mSize, int v1, int v2, int from = -1) {
	// Первым делом смотрим прямой путь между вершинами
	if (matrix[v1][v2])
		return true;
	// Если прямого пути нет, ищем обходной путь. Для этого последовательно
	// перебираем вершины, с которыми имеет соединение v1.
	bool pathExist = false;
	for (int i = 0; i < mSize; ++i) {
		// Пропускаем вершину откуда мы пришли
		if (i == from)
			continue;
		// Иначе, если есть соединение вершины i с вершиной v1, рекурсивно исследуем
		// этот путь.
		if (matrix[v1][i]) {
			pathExist = checkPathExisting( matrix, mSize, i, v2, v1 );
			// Если этот путь оказался искомым, то возвращаем true, иначе продолжаем
			// поиск.
			if (pathExist)
				return true;
		}
	}
	return false;
}

void initRandomGraph(int**& matrix, size_t mSize, size_t nEdges, int maxWeight) {
	// Выделяем память
	matrix = new int* [mSize];
	for (size_t i = 0; i < mSize; ++i)
		matrix[i] = new int [mSize];
	// Заполняем ее -1
	for (size_t i = 0; i < mSize; ++i)
		for (size_t j = 0; j < mSize; ++j)
			matrix[i][j] = -1;
	// Создаем вектор из всех возможных ребер.
	std::vector<Edge> allEdges;
	for (size_t i = 0; i < mSize; ++i) {
		for (size_t j = i + 1; j < mSize; ++j) {
			Edge e (i, j, 0);
			allEdges.push_back( e );
		}
	}
	// Выбираем из вектора nEdges случайных ребер.
	for (size_t i = 0; i < nEdges; ++i) {
		int index = rand() % allEdges.size();
		Edge e = allEdges[index];
		matrix[e.vertex_1][e.vertex_2] = rand() % maxWeight;
		matrix[e.vertex_2][e.vertex_1] = matrix[e.vertex_1][e.vertex_2];
		allEdges.erase(allEdges.begin() + index);
	}
}

void printMatrix(int** matrix, size_t mSize) {
	std::cout << "=== Matrix ===\n";
	for (size_t i = 0; i < mSize; ++i) std::cout << "\t" << numToChar(i); std::cout << "\n";
	for (size_t i = 0; i < mSize; ++i) std::cout << "\t---"; std::cout << "\n";
	for (size_t i = 0; i < mSize; ++i) {
		std::cout << numToChar(i) << "|\t";
		for (size_t j = 0; j < mSize; ++j) {
			if (matrix[i][j] < 0) std::cout << "X\t";
			else std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::string solve (int** matrix, size_t mSize) {
	// Создаем вектор граней.
	std::vector<Edge> v;
	createEdgesVector( matrix, mSize, v );
	// Используем matrix для дальнейшей работы. Для этого забьем ее нулями.
	for (size_t i = 0; i < mSize; ++i)
		for (size_t j = 0; j < mSize; ++j)
			matrix[i][j] = 0;
	// Создадим вектор, куда будем складывать ребра остовного дерева.
	// Как известно в остовном дереве имеется N - 1 ребер, где N - количество
	// вершин графа. Это знание поможет нам определить момент остановки перебора
	// ребер.
	std::vector<Edge> spanningTree;
	// Перебираем ребра
	for (size_t i = 0; i < v.size() && spanningTree.size() < mSize - 1; ++i) {
		// Берем очередное ребро.
		Edge e = v[i];
		// Проверяем, существует ли путь между вершинами ребра.
		bool pathExist = checkPathExisting(matrix, mSize, e.vertex_1, e.vertex_2);
		// Если пути нет, а значит добавления этого ребра в остовное дерево
		// не повлечет за собой создание цикла, добавляем данное ребро
		// в остовное дерево.
		if (!pathExist) {
			spanningTree.push_back( e );
			matrix[e.vertex_1][e.vertex_2] = 1;
			matrix[e.vertex_2][e.vertex_1] = 1;
		}
	}
	// Создадим строку, перечисляющую ребра вошедшие в остовное дерево.
	std::stringstream ss;
	for (size_t i = 0; i < spanningTree.size(); ++i)
		ss << spanningTree[i].toString() << std::endl;
	return ss.str();
}

std::string numToStr (int n) {
	std::stringstream ss;
	ss << n;
	return ss.str();
}

std::string numToChar (int n) {
	char c = 'a';
	c += n;
	return std::string (1, c);
}