#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <vector>
#include <set>
#include <sstream>

/** 
 * @brief Класс описывающий узел дерева поиска.
 */
class Node {
public:
	Node();
	// Конструктор копирования необходим для работы с vector.
	Node(const Node& node);
	~Node();
	// Суммарная длина провода при расположении элементов указанных в order.
	int sum;
	// Расположение элементов.
	int* order;
	// Дети текущего узла.
	std::vector< Node > children;
	// Статические поля 
	static int mSize;
	static int** cMatrix;
	static int** dMatrix;
};

/**
 * @brief Основная функция решающая задачу.
 * @param cMatrix Указатель на матрицу C
 * @param mSize Размер матрицы C
 * @param dMatrix Указатель на матрицу D
 * @param mSize Размер матрицы D
 * @return Строка, представляющая найденное решение.
 */
std::string solve (int** cMatrix, int** dMatrix, int mSize);

/**
 * @brief Функция обработки одного узла дерева поиска.
 * @param node Указатель на обрабатываемый узел.
 * @param minNode Ссылка на указатель на узел с текущим минимумом суммы.
 * @param freeCellsCount Количество свободных ячеек в массиве node.order.
 */
void processNode (Node* node, Node*& minNode, int freeCellsCount);

/**
 * @brief Функция вычисляет суммарную длину провода, исходя из переданного
 * ей порядка элементов.
 * @return Суммарная длина провода.
 */
int calculateSum (int* order);

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

#endif /* _UTILS_H */