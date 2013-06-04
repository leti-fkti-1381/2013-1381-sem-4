#ifndef _LIB_
#define _LIB_

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <set>
using namespace std;

//-------------------------------------------------------------
const int max_vertex = 20;
int Vertex;
int arr_graph[max_vertex][max_vertex];
int temp_arr [max_vertex][max_vertex];
int point_x[max_vertex];
int point_y[max_vertex];
bool makeTree = false;

int NumComp[max_vertex];

//-------------------------------------------------------------
class Edge
{
public:
	int x;
	int y;
	// Конструктор
	Edge (int NewX, int NewY)
	{
		x = NewX;
		y = NewY;
	};
	// Конструктор по умолчанию
	Edge ()
	{
		x = 0;
		y = 0;
	};
};

//-------------------------------------------------------------
void getData ()
{
	ifstream in ("input.txt");
	// Количество вершин
	in >> Vertex;
	// Матрица смежности
	for (int i = 0; i < Vertex; i++)
		for (int j = 0; j < Vertex; j++)
			in >> arr_graph[i][j];
	// Вычисдение координат точек
	static double pi = atan2(0.0,-1.0);

	double x = 650 / 2; //Центр правильного многоугольника в центр экрана
	double y = 600 / 2;
	double r = 250; //Радиус описанной окружности
	double angle = 0; //Угол наклона правильного многоугольника
	double i = 0; //Счетчик цикла

	// Координаты вершин графа
	point_x[0] = x + r * cos(angle * pi / 180);
	point_y[0] = y + r * sin(angle * pi / 180);
	for (int i = 0; i < Vertex; i++)
	{
		point_x[i] = x + r * cos(angle * pi / 180); //Запоминаем каждую следующую координату x
		point_y[i] = y + r * sin(angle * pi / 180); //Запоминаем каждую следующую координату y
		angle = angle + 360 / Vertex; //Увеличиваем угол на величину угла правильного многоугольника
	}
}

//-------------------------------------------------------------
void Comp (/*int NumComp[20],*/ int Num, int v)
{
	NumComp[v] = Num;
	for (int i = 0; i < Vertex; i++)
		if (temp_arr[v][i] != 0 && NumComp[i] == -1)
			Comp (Num, i);
}


//-------------------------------------------------------------
void Search ()
{
	// Матрица поиска остова
	for (int i = 0; i < Vertex; i++)
		for (int j = 0; j < Vertex; j++)
			temp_arr[i][j] = 0;

	// Вектор компонент связности
	vector<set<int>> arr_Comp;
	// Вектор длин минимальных ребер
	vector<int> min;
	// Вектор кратчайших путей
	vector<Edge> shortest;

	// Алгоритм
	while (arr_Comp.size() != 1)
	{
		int Num = -1; // Номер компоненты
		// Обнуление
		for (int i = 0; i < max_vertex; i++)
			NumComp[i] = -1;
		// Находим компоненты связности
		for (int i = 0; i < Vertex; i++)
		{
			if (NumComp[i] == -1)
			{
				Num++;
				Comp (Num, i);
			}
		}

		// Записываем компоненты связности
		arr_Comp.clear();
		min.clear();
		shortest.clear();
		// Создаем необходимое количество компонент связности
		set<int> s;
		for (int i = 0; i <= Num; i++)
			arr_Comp.push_back (s);

		for (int i = 0; i < Vertex; i++)
			arr_Comp[NumComp[i]].insert (i);

		// Заполняем вектор длин минимальных ребер
		// Заполняем вектор кратчайших путей
		for (int i = 0; i < arr_Comp.size(); i++)
		{
			min.push_back (numeric_limits<int>::max());
			Edge ed;
			shortest.push_back (ed);
		}
		// Находим вектор кратчайших путей
		for (int i = 0; i < Vertex; i++)
		{
			for (int j = i; j < Vertex; j++)
			{
				// Если существует ребро i - j
				if (arr_graph[i][j] != 0)
				{
					// Находим к какой компоненте связности принадлежит i
					int have_i;
					for (int k = 0; k < arr_Comp.size(); k++)
						if (arr_Comp[k].find(i) != arr_Comp[k].end())
							have_i = k;
					// Находим к какой компоненте связности принадлежит j
					int have_j;
					for (int k = 0; k < arr_Comp.size(); k++)
						if (arr_Comp[k].find(j) != arr_Comp[k].end())
							have_j = k;
					if (have_i != have_j)
					{
						// Сравниваем длины минимальных ребер
						if (arr_graph[i][j] < min[have_i])
						{
							min[have_i] = arr_graph[i][j];
							Edge e (i, j);
							shortest[have_i] = e;
						}
						if (arr_graph[i][j] < min[have_j])
						{
							min[have_j] = arr_graph[i][j];
							Edge e (i, j);
							shortest[have_j] = e;
						}
					}
					
				}
			}
		}
		// Добавляем к компонентам кратчайшие ребра
		for (int i = 0; i < arr_Comp.size(); i++)
		{
			if (arr_graph[shortest[i].x][shortest[i].y] != 0)
			{
				temp_arr[shortest[i].x][shortest[i].y] = arr_graph[shortest[i].x][shortest[i].y];
				temp_arr[shortest[i].y][shortest[i].x] = arr_graph[shortest[i].y][shortest[i].x];
			}
		}
	}

	// Вывод остова в файл
	ofstream out ("output.txt");
	for (int i = 0; i < Vertex; i++)
	{
		for (int j = 0; j < Vertex; j++)
			out << temp_arr[i][j];
		out << endl;
	}

}


#endif