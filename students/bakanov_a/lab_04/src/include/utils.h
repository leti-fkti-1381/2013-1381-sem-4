#ifndef _UTILS_H
#define _UTILS_H

#include <string>		// std::string
#include <vector>		// std::vector
#include <algorithm>	// std::sort
#include <sstream>		// std::stringstream
#include <cstdlib>		// std::rand
#include <ctime>		// std::time

/** 
 * @brief Класс описывающий ребро графа.
 */
class Edge {
public:
	/**
	 * Конструктор.
	 * @param v1 Индекс (идентификатор) первой вершины.
	 * @param v2 Индекс (идентификатор) второй вершины.
	 * @param w Вес ребра.
	 */
	Edge(int v1, int v2, int w);
	/**
	 * Конструктор копирования.
	 */
	Edge(const Edge& edge);
	/**
	 * Оператор сравнения необходим для сортировки в векторе
	 * функцией std::sort.
	 */
	bool operator< (const Edge& edge) const;
	/**
	 * Строковое представление ребра. Пример: a -- 2 -- b
	 */
	std::string toString() const;
	
	int vertex_1;
	int vertex_2;
	int weight;
};

/**
 * Функция по заданной матрице составляет список ребер графа
 * и сортирует их в порядке возрастания весов.
 * Предусловие: если элемент матрицы меньше нуля, такое ребро считается
 * отсутствующим.
 */
void createEdgesVector(int** matrix, int mSize, std::vector<Edge>& v);

/**
 * Функция проверки существоватия пути между двумя вершинами графа.
 * Матрица matrix содержит 1 на позиции [i][j] и [j][i] если ребро i-j
 * существует, 0 - в противном случае.
 */
bool checkPathExisting(int** matrix, int mSize, int v1, int v2, int from);

/**
 * @brief Основная функция решающая задачу.
 * @param matrix Указатель на матрицу смежности
 * @param mSize Размер матрицы
 * @return Строка, представляющая найденное решение.
 */
std::string solve (int** matrix, size_t mSize);

/**
 * @brief Функция - аналог itoa.
 * @param n Число для перевода в строковое представление
 * @return Строковое представление числа.
 */
std::string numToStr (int n);

/**
 * @brief Перевод 0 в 'a', 1 в 'b', 2 в 'c' и т.д.
 */
std::string numToChar (int n);

/**
 * Функция инициализирует матрицу графа. Функция не заботится об освобождении
 * памяти. Следует также помнить, что количество ребер полного графа, состящего
 * из N вершин равно N*(N-1)/2.
 * @param matrix Указатель на матрицу
 * @param mSize Размер матрицы (количество вершин графа)
 * @param edgeCount Количество ребер графа.
 * @param maxWeight Максимальный вес ребра.
 */
void initRandomGraph(int**& matrix, size_t mSize, size_t nEdges, int maxWeight);

/**
 * Печать матрицы.
 */
void printMatrix(int** matrix, size_t mSize);

#endif /* _UTILS_H */