#include <iostream>
#include <time.h>
#include "lr1.h"

using namespace std;

//#define deb

int main()
{
	setlocale(0,"Rus");
	int *mass,n,*res;
	cout << "Введите кол-во элементов\n";
	cin >> n;				
	mass=Get_Numbers(n);		//генерация массива псевдослучайных чисел
	
#ifdef deb
	cout << "\nВы ввели:\n";
	for(int i=0;i<n;i++)
		cout << mass[i] << "  ";
#endif

	int sravn=0;
	clock_t t;
	cout << "\nВремя выполнения сортировки слияний:   ";
	t=clock();
	res=Merge(mass,n,&sravn);    //сортировка естественным слиянием
	t=clock()-t;
	cout << (double)t/CLOCKS_PER_SEC << endl <<"Кол-во сравнений:  " << sravn << endl;
#ifdef deb
	cout << "\nОтсортированные(слиянием):\n";
	for(int i=0;i<n;i++)
		cout << res[i] << "  ";
#endif	
	
	sravn=0;
	cout << "\nВремя выполнения пузырьковой сортировки:   ";
	t=clock();
	res=Bubble(mass,n,&sravn);    //сортировка естественным слиянием
	t=clock()-t;
	cout << (double)t/CLOCKS_PER_SEC << endl <<"Кол-во сравнений:  " << sravn << endl;
		
#ifdef deb
	cout << "\nОтсортированные(пузырьковой):\n";
	for(int i=0;i<n;i++)
		cout << res[i] << "  ";
#endif	
	system("pause");
	return 1;
}
