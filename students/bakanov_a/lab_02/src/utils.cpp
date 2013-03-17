#include "include/utils.hpp"

void swap (int** field, int ax, int ay, int bx, int by)
{
	int temp = field[ay][ax];
	field[ay][ax] = field[by][bx];
	field[by][bx] = temp;
}

bool checkSolution (int** field)
{
	// Правильней сначала убедиться в верном расположении пустышки, а уже потом
	// просматривать остальные ячейки.
	if (field[3][3] == 0 && field[3][2] == 15 && field[3][1] == 14 && field[3][0] == 13 &&
		field[0][0] == 1 && field[0][1] ==  2 && field[0][2] ==  3 && field[0][3] ==  4 &&
		field[1][0] == 5 && field[1][1] ==  6 && field[1][2] ==  7 && field[1][3] ==  8 &&
		field[2][0] == 9 && field[2][1] == 10 && field[2][2] == 11 && field[2][3] == 12)
	{
		return true;
	}
	else
	{
		return false;
	}

	/**
	 * Далее следует старый вариант проверки. Он вроде как был расчитан
	 * на отвязку от конкретного размера поля 4x4. Но я пришел к выводу,
	 * что проверка в лоб в учебных целях будет целесообразней.
	 *
	// Проще сначала проверять последний элемент на соответствие нулю
	if (field[SIZE - 1][SIZE - 1] != 0)
		return false;
	// Если же чуда не случилось, будем проверять подряд.
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
		{
			// Проверка последнего элемента. Он должен быть равен нулю.
			if (i == SIZE - 1 && j == SIZE - 1)
				return field[i][j] == 0;
			// Проверка прочих элементов. То есть если все хорошо, то данное
			// условие всегда будет не выполняться, и в конце концов выполнится
			// предыдущее условие, которое вернет результат сравнения последнего
			// элемента с нулем (а не с 16).
			if ( field[i][j] != i * SIZE + j + 1 )
				return false;
		}
	*/
}

void printField (int** field)
{
	std::cout << "|--|--|--|--|\n";
	for (int i = 0; i < SIZE; ++i)
	{
		std::cout << "|";
		for (int j = 0; j < SIZE; ++j)
		{
			if (field[i][j] / 10)
				std::cout << field[i][j] << "|";
			else if (field[i][j] == 0)
				std::cout << "  |";
			else
				std::cout << " " << field[i][j] << "|";
		}
		std::cout << std::endl;
		std::cout << "|--|--|--|--|\n";
	}
}

void printWay (std::stack<char> way)
{
	std::vector<char> v;
	while (way.size())
	{
		v.push_back(way.top());
		way.pop();
	}
	for (int i = v.size() - 1; i >= 0; --i)
		std::cout << v[i] << " ";
	std::cout << "size=" << v.size() << std::endl;
}

void printSequence (int** field, int cx, int cy, std::stack<char> way)
{
	std::vector<char> v;
	while (way.size())
	{
		v.push_back(way.top());
		way.pop();
	}
	for (int i = v.size() - 1; i >= 0; --i)
	{
		std::cout << std::endl;
		if (v[i] == UP)
		{
			swap( field, cx, cy, cx, cy - 1 );
			printField( field );
			--cy;
		}
		else if (v[i] == DOWN)
		{
			swap( field, cx, cy, cx, cy + 1 );
			printField( field );
			++cy;
		}
		else if (v[i] == LEFT)
		{
			swap( field, cx, cy, cx - 1, cy );
			printField( field );
			--cx;
		}
		else if (v[i] == RIGHT)
		{
			swap( field, cx, cy, cx + 1, cy );
			printField( field );
			++cx;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void solve (int** field, int cx, int cy, char cameFrom, int& depth, std::stack<char>& way, bool& solved)
{
	// Проверяем состояние поля. Если задача решена, устанавливаем solved в true
	// и выходим.
	if (checkSolution( field ))
	{
		solved = true;
		return;
	}
	
	// Иначе же пробуем сместить фишки.
	// Сначала проверим, не превысим ли мы следующим вызовом RECURSIVE_DEPTH
	// Если это уже последний уровень вызовов, то ничего не делаем кроме проверки
	// состояния поля.
	if (depth < RECURSIVE_DEPTH)
	{
		// Смещаем вниз, если это возможно. Проверять следует направление, откуда
		// мы пришли, и выход за границы поля.
		if (cameFrom != DOWN && cy < SIZE - 1)
		{
			// Говорим такие: "Увеличим-ка глубину рекурсии"
			++depth;
			// А теперь меняем местами фишки
			swap( field, cx, cy, cx, cy + 1 );
			// Запоминаем, что мы пошли вниз
			way.push( DOWN );
			// Рекурсия, такая рекурсия
			solve( field, cx, cy + 1, UP, depth, way, solved );
			// Теперь самое время проверить, найдено ли решение
			if (solved)
			{
				// Этот swap вызывается исключительно в эстетических целях.
				// То есть затем, чтобы после нахождения решения его можно было
				// изобразить графически, а не только как последовательность
				// букв 'U', 'D', 'L', 'R'.
				swap( field, cx, cy, cx, cy + 1 );
				return;
			}
			// Если же решение не найдено, то возвращаем все как было
			else
			{
				--depth;
				swap( field, cx, cy, cx, cy + 1 );
				way.pop();
			}
		}
		// То же самое пробуем с правым направлением
		if (cameFrom != RIGHT && cx < SIZE - 1)
		{
			++depth;
			swap( field, cx, cy, cx + 1, cy );
			way.push( RIGHT );
			solve( field, cx + 1, cy, LEFT, depth, way, solved );
			if (solved)
			{
				swap( field, cx, cy, cx + 1, cy );
				return;
			}
			else
			{
				--depth;
				swap( field, cx, cy, cx + 1, cy );
				way.pop();
			}
		}
		// То же самое пробуем с верхним направлением
		if (cameFrom != UP && cy > 0)
		{
			++depth;
			swap( field, cx, cy, cx, cy - 1 );
			way.push( UP );
			solve( field, cx, cy - 1, DOWN, depth, way, solved );
			if (solved)
			{
				swap( field, cx, cy, cx, cy - 1 );
				return;
			}
			else
			{
				--depth;
				swap( field, cx, cy, cx, cy - 1 );
				way.pop();
			}
		}
		// То же самое пробуем с левым направлением
		if (cameFrom != LEFT && cx > 0)
		{
			++depth;
			swap( field, cx, cy, cx - 1, cy );
			way.push( LEFT );
			solve( field, cx - 1, cy, RIGHT, depth, way, solved );
			if (solved)
			{
				swap( field, cx, cy, cx - 1, cy );
				return;
			}
			else
			{
				--depth;
				swap( field, cx, cy, cx - 1, cy );
				way.pop();
			}
		}
	}
}
