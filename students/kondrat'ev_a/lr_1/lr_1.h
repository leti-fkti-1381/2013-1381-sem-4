#ifndef _lr_1
#define _lr_1

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

//---------------------------------------------------------------
const bool debug = false; // Константа для режима отладки

//---------------------------------------------------------------
void sort (string&, int, int); // Функция сортировки (строка, начало строки, конец строки)
void merge (string&, int, int, int); // Функция слияния (строка, начало строки, середина строки, конец строки)

//---------------------------------------------------------------
// Функция сортировки (строка, начало строки, конец строки)
void sort (string& str, int left, int right)
{
	// В строке должно быть более одного символа
	if (left < right)
	{
		int middle = (left + right)/2; // Середина строки
		sort (str, left, middle); // Сортировка левой половины
		sort (str, middle+1, right); // Сортировка правой половины
		merge (str, left, middle, right); // Слияние двух половин
	}
}

//---------------------------------------------------------------
// Функция слияния (строка, начало строки, середина строки, конец строки)
void merge (string& str, int left, int middle, int right)
{
	string temp; // Строка для слияния
	int i = left; // Первый элемент первой строки
	int j = middle+1; // Первый элемент второй строки
	
	// Слияние элементов пока в каждой строке есть хотя бы по одному символу
	while (i <= middle && j <= right)
	{
		// Сравнение двух текущих элементов и запись в результирующую строку
		if (str[i] < str[j])
		{
			temp += str[i];
			i ++;
		}
		else
		{
			temp += str[j];
			j ++;
		}
	}
	// Копирование остатка первой строки в конец результирующей
	while (i <= middle)
	{
		temp += str[i];
		i ++;
	}
	// Копирование остатка второй строки в конец результирующей
	while (j <= right)
	{
		temp += str[j];
		j ++;
	}
	// Вывод отладочной информации
	if (debug)
	{
		cout << endl << "Левая половина строки: ";
		for (int i = left; i <= middle; i ++)
		{
			cout << str[i];
		}
		cout << endl;
		cout << "Правая половина строки: ";
		for (int i = middle+1; i <= right; i ++)
		{
			cout << str[i];
		}
		cout << endl;
		cout << "Результат слияния: " << temp << endl << endl;
	}
	// Копирование временной строки в исходную
	for (i = 0; left <= right; left ++, i ++)
		str[left] = temp[i];
}
#endif