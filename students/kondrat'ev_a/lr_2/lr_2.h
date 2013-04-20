#ifndef _lr_2
#define _lr_2

//---------------------------------------------------------------
const int max_side = 8; // Максимальная сторона квадрата
const int max_bishop = 64; // Максимальное количество слонов

//---------------------------------------------------------------
double amount_position (int [max_side][max_side], int, int); // Функция подсчета количества позиций, на которые можно поставить слонов, чтобы они не били друг друга
double bust (int [max_side][max_side], int, int); // Рекурсивная Функция подсчета количества позиций

//---------------------------------------------------------------
// Функция подсчета количества позиций, на которые можно поставить слонов, чтобы они не били друг друга
double amount_position (int field[max_side][max_side], int side, int bishop)
{
	// Проверка на правильные начальные данные
	if (side < 1 && side > 8 && bishop < 1 && bishop > side*side)
		return 0;
	// Подсчет количества позиций
	double amount = bust (field, side, bishop);
	// Подсчет количества позиций без учета порядка слонов
	for (int i = 1; i <= bishop; i ++)
		amount = amount / i;
	return amount;
}

//---------------------------------------------------------------
// Рекурсивная Функция подсчета количества позиций
double bust (int field[max_side][max_side], int side, int bishop)
{
	double amount = 0; 
	// Цикл по всем клеткам поля
	for (int i = 0; i < side; i ++)
		for (int j = 0; j < side; j ++)
		{
			if (field[i][j] == 0)
			{
				// Заполнение диагоналей цифрами
				int x = i, y = j;
				// Заполнить нижнюю часть диагонали слева направо
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x ++;
					y ++;
				}
				// Заполнить верхнюю часть диагонали слева направо
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x --;
					y --;
				}
				// Заполнить нижнюю часть диагонали справа налево
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x ++;
					y --;
				}
				// Заполнить верхнюю часть диагонали справа налево
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x --;
					y ++;
				}
				// Проверка на последнего слона
				if (bishop != 1)
					amount += bust (field, side, bishop-1);
				// Подсчет количества позиций, на которые можно поставить последнего слона
				if (bishop == 1)
					amount ++;
				// Заполнение диагоналей нулями
				x = i, y = j;
				// Заполнить нижнюю часть диагонали слева направо
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x ++;
					y ++;
				}
				// Заполнить верхнюю часть диагонали слева направо
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x --;
					y --;
				}
				// Заполнить нижнюю часть диагонали справа налево
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x ++;
					y --;
				}
				// Заполнить верхнюю часть диагонали справа налево
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x --;
					y ++;
				}
			}
		}
	return amount;
}

#endif