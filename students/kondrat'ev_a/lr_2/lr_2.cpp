#include <iostream>
#include <stdlib.h>
#include <locale>
#include "time_meter.hpp"
#include "lr_2.h"
using namespace std;

//---------------------------------------------------------------
int main ()
{
	system ("cls");
	setlocale (LC_ALL, "Russian");
	
	cout << "Программа, вычисляющая количество позиций на которые можно поставить слонов, чтобы они не были друг друга" << endl << endl;
	
	int field[max_side][max_side]; // Объявление поля
	// Обнуление поля
	for (int i = 0; i < max_side; i ++)
		for (int j = 0; j < max_side; j ++)
			field[i][j] = 0;
	
	int side = 0, // Размер поля(количество клеток по вертикали или горизонтали)
		bishop = 0; // Количество слонов
	
	cout << "Введите размер поля (от 1 до 8): ";
	cin >> side;
	cout << "Введите количество слонов (от 1 до 'размер поля'*'размер поля'): ";
	cin >> bishop;
	cout << endl;
	
	
	if (side < 1 || side > 8 || bishop < 1 || bishop > side*side)
		cout << "Неверно введены данные!!!" << endl;
	else
	{
		TimeMeter::init();
		double amount = amount_position (field, side, bishop);
		cout << "Количество позиций: " << amount << endl;
		cout << "Время затраченное на вычисления: " << TimeMeter::getPastTime() << " секунд" << endl;
	}
	
	cout << endl;
	system ("pause");
	system ("cls");
	return 0;
}

