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
}

int findField( std::vector< FieldDescription >& fields, FieldDescription& fd )
{
	std::vector<FieldDescription>::iterator it = fields.begin();
	bool found = false;
	int ind;
	for (ind = 0; it != fields.end(); ++it, ++ind)
	{
		// Проверяем очередное поле
		if (fd.cameFrom != (*it).cameFrom)
			continue;
		else if (fd.field[0][0] != (*it).field[0][0]) continue;
		else if (fd.field[0][1] != (*it).field[0][1]) continue;
		else if (fd.field[0][2] != (*it).field[0][2]) continue;
		else if (fd.field[0][3] != (*it).field[0][3]) continue;
		else if (fd.field[1][0] != (*it).field[1][0]) continue;
		else if (fd.field[1][1] != (*it).field[1][1]) continue;
		else if (fd.field[1][2] != (*it).field[1][2]) continue;
		else if (fd.field[1][3] != (*it).field[1][3]) continue;
		else if (fd.field[2][0] != (*it).field[2][0]) continue;
		else if (fd.field[2][1] != (*it).field[2][1]) continue;
		else if (fd.field[2][2] != (*it).field[2][2]) continue;
		else if (fd.field[2][3] != (*it).field[2][3]) continue;
		else if (fd.field[3][0] != (*it).field[3][0]) continue;
		else if (fd.field[3][1] != (*it).field[3][1]) continue;
		else if (fd.field[3][2] != (*it).field[3][2]) continue;
		else if (fd.field[3][3] != (*it).field[3][3]) continue;
		
		// Если нашли совпадающую структуру, то отмечаем это и завершаем цикл
		found = true;
		break;
	}
	return found ? ind : -1;
}

bool addField( std::vector< FieldDescription >& fields, int** field, char cameFrom )
{
	// Сохраним текущее состояние поле в векторе.
	// первым элементом вектора будет направление прихода.
	FieldDescription fd;
	fd.cameFrom = cameFrom;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			fd.field[i][j] = field[i][j];
	// Попробуем добавить его в хранилище
	int ind = findField( fields, fd );
	bool added = false;
	if (ind < 0)
	{
		fields.push_back( fd );
		added = true;
	}
	
	// Раскомментировав следующие две строки, можно увидеть что механизм
	// отсечения повторных ветвей работает.
	//if (!added)
	//	std::cout << "< FIELD ALREADY EXIST >\n";
	
	return added;
}

void removeField( std::vector< FieldDescription >& fields, int** field, char cameFrom )
{
	// Сохраним текущее состояние поле в векторе.
	// первым элементом вектора будет направление прихода.
	FieldDescription fd;
	fd.cameFrom = cameFrom;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			fd.field[i][j] = field[i][j];
	// Попробуем удалить его из хранилища
	// Функция erase возвращает size_type, который равен количеству удаленных
	// элементов. Мы его не проверяем, так как можем быть уверены, что удаляем
	// только то, что добавили.
	int ind = findField( fields, fd );
	if (ind >= 0)
		fields.erase( fields.begin() + ind );
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

#define COUT_TRY_ADD_FIELD std::cout << "--- Try add field, depth = " << depth << " ---------------------------------\n"; printField( field );
#define COUT_FIELD_WAS_ADDED std::cout << "--- Field was added, size = " << fields.size() << ", depth = " << depth << std::endl;
#define COUT_TRY_REMOVE_FIELD std::cout << "--- Try remove field, depth = " << depth << " ---------------------------------\n"; printField( field );
#define COUT_FIELD_ALREADY_EXIST std::cout << "--- Field already exist in list, size = " << fields.size() << ", depth = " << depth << std::endl;
#define COUT_UP std::cout << "< UP >" << std::endl;
#define COUT_DOWN std::cout << "< DOWN >" << std::endl;
#define COUT_LEFT std::cout << "< LEFT >" << std::endl;
#define COUT_RIGHT std::cout << "< RIGHT >" << std::endl;
#define COUT_CURRENT_STATE std::cout << "--- Current state ---" << std::endl; printField( field );
#define COUT_CANT_GO_DOWN std::cout << "< CAN'T GO DOWN >\n";
#define COUT_CANT_GO_RIGHT std::cout << "< CAN'T GO RIGHT >\n";
#define COUT_CANT_GO_UP std::cout << "< CAN'T GO UP >\n";
#define COUT_CANT_GO_LEFT std::cout << "< CAN'T GO LEFT >\n";

void solve (int** field, int cx, int cy, char cameFrom, int& depth,
	std::stack<char>& way, bool& solved, std::vector< FieldDescription >& fields)
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
		// мы пришли, и выход за границы поля. Кроме этого 
		if (cameFrom != DOWN && cy < SIZE - 1)
		{
			// Увеличим глубину рекурсии
			++depth;
			// А теперь меняем местами фишки
			swap( field, cx, cy, cx, cy + 1 );
			
			//COUT_DOWN
			//COUT_TRY_ADD_FIELD
			
			// Здесь нужно проверить не попадали ли мы уже в такую позицию.
			// если попадали, то исследовать эту ветку уже нет смысла
			// и мы ее пропустим.
			if (addField( fields, field, UP ))
			{
				//COUT_DOWN
				//COUT_FIELD_WAS_ADDED
				
				// Запоминаем, что мы пошли вниз
				way.push( DOWN );
				// Рекурсия, такая рекурсия
				solve( field, cx, cy + 1, UP, depth, way, solved, fields );
				
				//COUT_DOWN
				//COUT_TRY_REMOVE_FIELD
				
				// После выхода из рекурсии меняем фишки обратно, и удаляем
				// позицию из хранилища.
				removeField( fields, field, UP );
				swap( field, cx, cy, cx, cy + 1 );
				//COUT_CURRENT_STATE
				
				// Теперь самое время проверить, найдено ли решение
				if (solved)
				{
					return;
				}
				// Если же решение не найдено, то возвращаем все как было
				else
				{
					--depth;
					way.pop();
				}
			}
			// Вот здесь, собственно, пропускаем ветку.
			else
			{
				--depth;
				//COUT_DOWN
				//COUT_FIELD_ALREADY_EXIST
				swap( field, cx, cy, cx, cy + 1 );
			}
		}
		//else
		//	COUT_CANT_GO_DOWN
		// То же самое пробуем с правым направлением
		if (cameFrom != RIGHT && cx < SIZE - 1)
		{
			++depth;
			swap( field, cx, cy, cx + 1, cy );
			
			//COUT_RIGHT
			//COUT_TRY_ADD_FIELD
			
			if (addField( fields, field, LEFT ))
			{
				//COUT_RIGHT
				//COUT_FIELD_WAS_ADDED
				
				way.push( RIGHT );
				solve( field, cx + 1, cy, LEFT, depth, way, solved, fields );
				
				//COUT_RIGHT
				//COUT_TRY_REMOVE_FIELD
				
				removeField( fields, field, LEFT );
				swap( field, cx, cy, cx + 1, cy );
				//COUT_CURRENT_STATE
				
				if (solved)
				{
					return;
				}
				else
				{
					--depth;
					way.pop();
				}
			}
			else
			{
				--depth;
				//COUT_RIGHT
				//COUT_FIELD_ALREADY_EXIST
				swap( field, cx, cy, cx + 1, cy );
			}
		}
		//else
		//	COUT_CANT_GO_RIGHT
		// То же самое пробуем с верхним направлением
		if (cameFrom != UP && cy > 0)
		{
			++depth;
			swap( field, cx, cy, cx, cy - 1 );
			
			//COUT_UP
			//COUT_TRY_ADD_FIELD
			
			if (addField( fields, field, DOWN ))
			{
				//COUT_UP
				//COUT_FIELD_WAS_ADDED
				
				way.push( UP );
				solve( field, cx, cy - 1, DOWN, depth, way, solved, fields );
				
				//COUT_UP
				//COUT_TRY_REMOVE_FIELD
				
				removeField( fields, field, DOWN );
				swap( field, cx, cy, cx, cy - 1 );
				//COUT_CURRENT_STATE
				
				if (solved)
				{
					return;
				}
				else
				{
					--depth;
					way.pop();
				}
			}
			else
			{
				--depth;
				//COUT_UP
				//COUT_FIELD_ALREADY_EXIST
				swap( field, cx, cy, cx, cy - 1 );
			}
		}
		//else
		//	COUT_CANT_GO_UP
		// То же самое пробуем с левым направлением
		if (cameFrom != LEFT && cx > 0)
		{
			++depth;
			swap( field, cx, cy, cx - 1, cy );
			
			//COUT_LEFT
			//COUT_TRY_ADD_FIELD
			
			if (addField( fields, field, RIGHT ))
			{
				//COUT_LEFT
				//COUT_FIELD_WAS_ADDED
				
				way.push( LEFT );
				solve( field, cx - 1, cy, RIGHT, depth, way, solved, fields );
				
				//COUT_LEFT
				//COUT_TRY_REMOVE_FIELD
				
				removeField( fields, field, RIGHT );
				swap( field, cx, cy, cx - 1, cy );
				//COUT_CURRENT_STATE
				
				if (solved)
				{
					return;
				}
				else
				{
					--depth;
					way.pop();
				}
			}
			else
			{
				--depth;
				//COUT_LEFT
				//COUT_FIELD_ALREADY_EXIST
				swap( field, cx, cy, cx - 1, cy );
			}
		}
		//else
		//	COUT_CANT_GO_LEFT
	}
	//else
	//{
	//	std::cout << "<<< MAXIMUM DEPTH REACHED >>>\n";
	//}
}
