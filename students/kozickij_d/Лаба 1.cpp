#include "stdafx.h"
#include "���� 1.h"
#include <iostream>

using namespace std;

int compare (const void * a, const void * b)
{  
   return ( *(int*)a - *(int*)b );
}

int main()
{
	int size_mas, min_mas, max_mas;
	int i;
	int *mass = NULL, *sort_mass = NULL;

	setlocale(0, "Rus");
	cout << "������� ���������� ��������� � ������������ �������"<<endl;
	do
	    {
	      cin >> size_mas;
		  if((size_mas < 1)||(size_mas == 1))
			  cout << "������! ������� ���������� ������� 1" <<endl;
		}
	while((size_mas < 1)||(size_mas == 1));
	cout << "������� ����������� �������� � ������������ �������"<<endl;
	cin >> min_mas;
	cout << "������� ������������ �������� � ������������ �������"<<endl;
	do
	    {
	      cin >> max_mas;
		  if((max_mas < min_mas)||(max_mas == min_mas))
			  cout << "������! ������� ������������ �������� ������������� �����������" <<endl;
		}
	while((max_mas < min_mas)||(max_mas == min_mas));

	mass = new int[size_mas];
	int n = max_mas - min_mas;
	for(i = 0; i < size_mas; i ++)
	    mass[i] = rand() % n + min_mas;
	cout << "����� ���������������� �������" << endl;
	for(i = 0; i < size_mas; i ++)
	    cout << mass[i] << ";";

	Massiv massiv(mass, size_mas, max_mas);
	if(sort_mass != NULL)
	    delete sort_mass;
	double t1 = omp_get_wtime(); // ��������� ����� �� ���������� �������
    sort_mass = massiv.sort();
    double t2 = omp_get_wtime(); // ����� ����� ���������� �������
	double time = t2 - t1;

	cout << "\n����� ���������������� �������" << endl;
	for(i = 0; i < size_mas; i ++)
	    cout << sort_mass[i] << ";";
	
	t1 = omp_get_wtime(); // ��������� ����� �� ���������� �������
	qsort(mass, size_mas, sizeof(int), compare);
	t2 = omp_get_wtime(); // ����� ����� ���������� �������
	double qtime = t2 - t1;

	cout << "\n����������� ����� �� ���������� " << time << " ������" << endl;
	cout << "\n����������� ����� �� ���������� ����������� �������� qsort " << qtime << " ������" << endl;
	int iterations = massiv.vizual_sort();
	cout << "\n���������� �������� " << iterations << endl;
	system("Pause");
	return 0;
}

