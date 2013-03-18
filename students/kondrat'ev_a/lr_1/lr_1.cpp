//Факультет:	КТИ
//Группа:		1381
//Выполнил:		Кондратьев Александр
//Лабораторная работа №1 - сортировка слиянием (4 семестр)

//-------------------------------------------------------------
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include "lr_1.h"
using namespace std;

//---------------------------------------------------------------
int main ()
{
	SetConsoleCP (1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP (1251); // Вывод на консоль в кодировке 1251
	string str; // Строка
	cout << "Факультет	КТИ \nГруппа:		1381 \nВыполнил:	Кондратьев Александр  \n\n";
	cout << "Лабораторная работа №1 - сортировка слиянием (4 семестр)\n" << endl << endl;
	cout << "Введите строку: ";
	getline (cin, str);
	
	if (str.size() == 0)
		cout << "Введена пустая строка!!!" << endl << endl;
	else
	{
		if (debug) cout << endl << "Отладочная информация:" << endl;
		sort (str, 0, str.size() - 1); // Функция сортировки
		if (debug) cout << "Результат:" << endl;
		cout << "Отсортированная строка: " << str << endl << endl;
	}
	system ("pause");
	return 0;
}
