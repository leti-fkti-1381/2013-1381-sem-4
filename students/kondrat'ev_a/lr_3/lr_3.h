#ifndef _lr_3_
#define _lr_3_

#include <vector>
#include <limits>
using namespace std;

//---------------------------------------------------------------
const int max_amount = 100; // Максимальное количество элементов
const int max_value = 100; // Максимальное значение элемента

//---------------------------------------------------------------
int Solution (vector <int>, int); // Функция нахождения решения
void MinSolution (vector <int>, int, int, int&); // Рекурсивная Функция нахождения минимального решения

//---------------------------------------------------------------
// Функция нахождения решения
int Solution (vector <int> arr , int amount_arr)
{
	// Проверка введенных данных
	if (!(amount_arr > 1 && amount_arr <= max_amount))
		return -1;
	for (int i = 0; i < arr.size(); i++)
		if (arr[i] > max_value)
			return -1;
	int solution = numeric_limits<int>::max(); // Максимальное значение типа int;
	MinSolution (arr, amount_arr, 0, solution); // Нахождение решения
	return solution;
}

//---------------------------------------------------------------
// Рекурсивная Функция нахождения минимального решения
void MinSolution (vector <int> arr, int amount_arr, int curr, int& solution)
{
	int step = 0; // Цена шага
	for (int i = 1; i < amount_arr-1; i++)
	{
		// Вычисление стоимости шага
		step = (arr[i-1]+arr[i+1])*arr[i];
		// Проверка на продолжение выполнения
		if (curr+step <= solution)
		{
			int erase_elem = arr[i]; // Удаляемый элемент
			arr.erase(arr.begin()+i); // Удаление
			MinSolution (arr, amount_arr-1, curr+step, solution);
			arr.insert(arr.begin()+i, erase_elem); // Востановление удаленного элемента
		}
	}
	// Сравнение полученного результата с текущим решением
	if (amount_arr == 2 && curr < solution)
	{
		solution = curr;
	}
}

#endif