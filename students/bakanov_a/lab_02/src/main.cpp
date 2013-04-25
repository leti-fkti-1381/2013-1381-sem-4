#include "include/utils.hpp"
#include "include/time_meter.hpp"

#include <fstream>

int main()
{
	int constField [SIZE][SIZE];
	// Создаем поле, с которым будем работать
	int** field = new int*[SIZE];
	for (int i = 0; i < SIZE; ++i)
		field[i] = new int[SIZE];

	std::ifstream in;
	in.open ("data.txt", std::ifstream::in);

	int count;
	in >> count;
	
	TimeMeter::init();
	
	for (int i = 0; i < count; ++i)
	{
		// Переменные для запоминания начального положения пустой ячейки
		int cx, cy;
		// Считываем данные
		for (int j = 0; j < SIZE; ++j)
		{
			for (int k = 0; k < SIZE; ++k)
			{
				in >> field[j][k];
				constField[j][k] = field[j][k];
				if (field[j][k] == 0)
				{
					cy = j;
					cx = k;
				}
			}
		}
		
		int testTimes = 1;
		float passedTime = 0.0;
		for (int n = 0; n < testTimes; ++n)
		{
			// Обновляем поле.
			for (int j = 0; j < SIZE; ++j)
			{
				for (int k = 0; k < SIZE; ++k)
				{
					field[j][k] = constField[j][k];
					if (field[j][k] == 0)
					{
						cy = j;
						cx = k;
					}
				}
			}
			// Хранилище состояний поля
			std::vector<FieldDescription> fields;
			// Создаем стек для хранения пути
			std::stack<char> way;
			// Флаг решения
			bool solved = false;
			// Глубина рекурсии
			int depth = 0;
			// Ищем решение
			solve( field, cx, cy, NOWHERE, depth, way, solved, fields );
			if (solved)
			{
				std::cout << "Solved: ";
				printWay( way );
				std::cout << std::endl;
			}
			else
				std::cout << "This puzzle is not solvable." << std::endl;
			passedTime += TimeMeter::getPastTime();
		}
		std::cout << "Time passed: " << (passedTime / float(testTimes)) << " seconds\n";
	}
	
	in.close();
	
	return 0;
}
