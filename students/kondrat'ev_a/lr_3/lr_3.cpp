#include <iostream>
#include <stdlib.h>
#include <locale>
#include <vector>
#include "lr_3.h"
using namespace std;

//---------------------------------------------------------------
int main ()
{
	system ("cls");
	setlocale (LC_ALL, "Russian");
	
	cout << "Задание:\nДана последовательность целых положительных чисел a1, a2, ..., an. За одну операцию разрешается удалить любое (кроме крайних) число. Стоимость  операции равна произведению этого числа на сумму соседних чисел. Требуется удалить все числа, кроме крайних, так, чтобы суммарная стоимость была минимальной. Ограничения n<=100, ai<=100. " << endl << endl;
	
	vector <int> arr; // Массив чисел
	int amount_arr = 0; // Размер массива
	int item; // Элемент массива
	
	cout << "Введите количество элементов массива: ";
	cin >> amount_arr;
	for (int i = 0; i < amount_arr; i++)
	{
		cout << "Введите " << i+1 << " элемент: ";
		cin >> item;
		arr.push_back(item);
	}
	
	int solution = Solution (arr, amount_arr); // Решение
	if (solution == -1)
		cout << endl << "Введены неверные данные!!!" << endl << endl;
	else
		cout << endl << "Полученное решение: " << solution << endl << endl;
	
	system ("pause");
	system ("cls");
	return 0;
}

