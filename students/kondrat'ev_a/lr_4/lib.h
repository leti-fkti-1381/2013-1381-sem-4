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
	// �����������
	Edge (int NewX, int NewY)
	{
		x = NewX;
		y = NewY;
	};
	// ����������� �� ���������
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
	// ���������� ������
	in >> Vertex;
	// ������� ���������
	for (int i = 0; i < Vertex; i++)
		for (int j = 0; j < Vertex; j++)
			in >> arr_graph[i][j];
	// ���������� ��������� �����
	static double pi = atan2(0.0,-1.0);

	double x = 650 / 2; //����� ����������� �������������� � ����� ������
	double y = 600 / 2;
	double r = 250; //������ ��������� ����������
	double angle = 0; //���� ������� ����������� ��������������
	double i = 0; //������� �����

	// ���������� ������ �����
	point_x[0] = x + r * cos(angle * pi / 180);
	point_y[0] = y + r * sin(angle * pi / 180);
	for (int i = 0; i < Vertex; i++)
	{
		point_x[i] = x + r * cos(angle * pi / 180); //���������� ������ ��������� ���������� x
		point_y[i] = y + r * sin(angle * pi / 180); //���������� ������ ��������� ���������� y
		angle = angle + 360 / Vertex; //����������� ���� �� �������� ���� ����������� ��������������
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
	// ������� ������ ������
	for (int i = 0; i < Vertex; i++)
		for (int j = 0; j < Vertex; j++)
			temp_arr[i][j] = 0;

	// ������ ��������� ���������
	vector<set<int>> arr_Comp;
	// ������ ���� ����������� �����
	vector<int> min;
	// ������ ���������� �����
	vector<Edge> shortest;

	// ��������
	while (arr_Comp.size() != 1)
	{
		int Num = -1; // ����� ����������
		// ���������
		for (int i = 0; i < max_vertex; i++)
			NumComp[i] = -1;
		// ������� ���������� ���������
		for (int i = 0; i < Vertex; i++)
		{
			if (NumComp[i] == -1)
			{
				Num++;
				Comp (Num, i);
			}
		}

		// ���������� ���������� ���������
		arr_Comp.clear();
		min.clear();
		shortest.clear();
		// ������� ����������� ���������� ��������� ���������
		set<int> s;
		for (int i = 0; i <= Num; i++)
			arr_Comp.push_back (s);

		for (int i = 0; i < Vertex; i++)
			arr_Comp[NumComp[i]].insert (i);

		// ��������� ������ ���� ����������� �����
		// ��������� ������ ���������� �����
		for (int i = 0; i < arr_Comp.size(); i++)
		{
			min.push_back (numeric_limits<int>::max());
			Edge ed;
			shortest.push_back (ed);
		}
		// ������� ������ ���������� �����
		for (int i = 0; i < Vertex; i++)
		{
			for (int j = i; j < Vertex; j++)
			{
				// ���� ���������� ����� i - j
				if (arr_graph[i][j] != 0)
				{
					// ������� � ����� ���������� ��������� ����������� i
					int have_i;
					for (int k = 0; k < arr_Comp.size(); k++)
						if (arr_Comp[k].find(i) != arr_Comp[k].end())
							have_i = k;
					// ������� � ����� ���������� ��������� ����������� j
					int have_j;
					for (int k = 0; k < arr_Comp.size(); k++)
						if (arr_Comp[k].find(j) != arr_Comp[k].end())
							have_j = k;
					if (have_i != have_j)
					{
						// ���������� ����� ����������� �����
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
		// ��������� � ����������� ���������� �����
		for (int i = 0; i < arr_Comp.size(); i++)
		{
			if (arr_graph[shortest[i].x][shortest[i].y] != 0)
			{
				temp_arr[shortest[i].x][shortest[i].y] = arr_graph[shortest[i].x][shortest[i].y];
				temp_arr[shortest[i].y][shortest[i].x] = arr_graph[shortest[i].y][shortest[i].x];
			}
		}
	}

	// ����� ������ � ����
	ofstream out ("output.txt");
	for (int i = 0; i < Vertex; i++)
	{
		for (int j = 0; j < Vertex; j++)
			out << temp_arr[i][j];
		out << endl;
	}

}


#endif