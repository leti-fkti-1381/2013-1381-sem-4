#include "stdafx.h"
#include "Лаба 1.h"
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
	cout << "Введите количество элементов в генерируемом массиве"<<endl;
	do
	    {
	      cin >> size_mas;
		  if((size_mas < 1)||(size_mas == 1))
			  cout << "Ошибка! Введите количество большее 1" <<endl;
		}
	while((size_mas < 1)||(size_mas == 1));
	cout << "Введите минимальное значение в генерируемом массиве"<<endl;
	cin >> min_mas;
	cout << "Введите максимальное значение в генерируемом массиве"<<endl;
	do
	    {
	      cin >> max_mas;
		  if((max_mas < min_mas)||(max_mas == min_mas))
			  cout << "Ошибка! Введите максимальное значение превосходящее минимальное" <<endl;
		}
	while((max_mas < min_mas)||(max_mas == min_mas));

	mass = new int[size_mas];
	int n = max_mas - min_mas;
	for(i = 0; i < size_mas; i ++)
	    mass[i] = rand() % n + min_mas;
	cout << "Вывод сгенерированного массива" << endl;
	for(i = 0; i < size_mas; i ++)
	    cout << mass[i] << ";";

	Massiv massiv(mass, size_mas, max_mas);
	if(sort_mass != NULL)
	    delete sort_mass;
	double t1 = omp_get_wtime(); // системное время до выполнения функции
    sort_mass = massiv.sort();
    double t2 = omp_get_wtime(); // время после выполнения функции
	double time = t2 - t1;

	cout << "\nВывод отсортированного массива" << endl;
	for(i = 0; i < size_mas; i ++)
	    cout << sort_mass[i] << ";";
	
	t1 = omp_get_wtime(); // системное время до выполнения функции
	qsort(mass, size_mas, sizeof(int), compare);
	t2 = omp_get_wtime(); // время после выполнения функции
	double qtime = t2 - t1;

	cout << "\nЗатраченное время на сортировку " << time << " секунд" << endl;
	cout << "\nЗатраченное время на сортировку стандартной функцией qsort " << qtime << " секунд" << endl;
	int iterations = massiv.vizual_sort();
	cout << "\nКоличество операций " << iterations << endl;
	system("Pause");
	return 0;
}

