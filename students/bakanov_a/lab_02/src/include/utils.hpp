#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <vector>

// Размер игрового поля
const int SIZE = 4;
// Глубина рекурсии.
// Вот про глубину рекурсии стоит сказать, что очень большой ее делать не нужно.
// Для проверки правильности работы алгоритма достаточно значения 20-25.
// Во-первых будет большой вывод найденного решения, во-вторых, если запустить
// программу с глубиной рекурсии 50, как указано в задании, то можно смело
// пойти погулять, или там на концерт, или в оперу.
const int RECURSIVE_DEPTH = 50;
// Константы для записи ходов
const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';
const char NOWHERE = 'N';

struct FieldDescription
{
	char cameFrom;
	int field[SIZE][SIZE];
};

// Функция проверки существования / добавления состояния поля в хранилище.
bool addField( std::vector< FieldDescription >& fields, int** field, char cameFrom );
// Функция удаления из хранилища текущего состояния поля
void removeField( std::vector< FieldDescription >& fields, int** field, char cameFrom );
/**
 * @brief Функция поиска поля в списке.
 * @return Индекс искомого поля или -1, если поле не найдено.
 */
int findField( std::vector< FieldDescription >& fields, FieldDescription& fd );

/**
 * Функция меняет местами два значения на указанных координатах.
 * @param	field	Указатель на поле
 * @param	ax	x координата первой ячейки
 * @param	ay	y координата первой ячейки
 * @param	bx	x координата второй ячейки
 * @param	by	y координата второй ячейки
 */
void swap (int** field, int ax, int ay, int bx, int by);

/**
 * Функция проверки совпадения поля с выигрышным расположением фишек
 * @param	field	Указатель на поле
 * @return	True, если решение найдено.
 */
bool checkSolution (int** field);

/**
 * Печать поля.
 * @param	field	Указатель на поле
 */
void printField (int** field);

/**
 * Печать последовательности решения задачи.
 * @param	way	Стек с шагами
 */
void printWay (std::stack<char> way);

/**
 * Печать последовательных шагов решения задачи.
 * @param	field	Указатель на поле
 * @param	cx	Начальная координата x пустой ячейки
 * @param	cy	Начальная координата y пустой ячейки
 * @param	way	Стек с шагами
 */
void printSequence (int** field, int cx, int cy, std::stack<char> way);

/**
 * Рекурсивная функция поиска пути.
 * @param	field	Указатель на поле
 * @param	cx	Текущая координата x нуля (пустой ячейки)
 * @param	cy	Текущая координата y нуля (пустой ячейки)
 * @param	cameFrom	Указывает откуда пришли
 * @param	depth	Текущая глубина рекурсии
 * @param	way	Стек, содержащий решение
 * @param	solved	Флаг нахождения решения
 */
void solve (int** field, int cx, int cy, char cameFrom, int& depth,
	std::stack<char>& way, bool& solved, std::vector< FieldDescription >& fields);

#endif /* _UTILS_HPP */
