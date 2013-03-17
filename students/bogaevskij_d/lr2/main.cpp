#include <iostream>
#include <fstream>
#include <math.h>
#include <conio.h>
#include "paa_lr2_0.h"

using namespace std;

#define debug

int main()
{
	setlocale(0,"Rus");
	int n=5,m;
	Mark *base=NULL;
	cout << "Введите количество различных марок:   ";
	cin >> n;
	cout << "\nВведите максимальное число марок на письме:   ";
	cin >> m;  
	n++;
	base=new Mark [n];
	//Добавляем пустую марку
	base[0].cost=0;
	base[0].number=0;
	for(int i=1;i<n;i++)
		base[i].Init(i);
	
	Mark **a;
	int p=pow((double)n,m);
	a=new Mark* [p];
	for(int i=0;i<p;i++)
		*(a+i)=new Mark [m+1];
	Mark res[20];
	Mark **result;
	int stat=0;
	Solve1(a,res,base,0,m,n,&stat);  //Рассматриваем всевозможные комбинации
#ifdef debug
	CostSort(a,m,p);			//Сортируем комбинации по цене
	MarkSort(a,m,p);			//Сортируем марки по 
	Posl(a,m,p);	//Находим последовательность 0,1,2,...,N,(N - натуральное число) и выводим ее на экран
	result=ChoseAns(a,m,n);  //Убираем равные комбинации (полученные перестановкой билетов)
	cout << endl;
#endif	
	int rs=Posl1(a,m,p);			//Находим последовательность 0,1,2,...,N,(N - натуральное число) и выводим ее на экран
	cout << 0 << "..." << rs << endl;
#ifdef debug
	//Вывод результатов:
	cout << endl << "Комбинации номеров: (в скобках цена)";
	for(int i=0;i<C(n,m);i++)
	{
		cout << endl;
		for(int j=0;j<m;j++)
		{
			cout << result[i][j].number << "(" << result[i][j].cost << ") ";
		}
		cout << "    Цена: " << result[i][m].cost;
	}
	cout << endl;
#endif
	//Оценка сложности методом Монте-Карло
	int MC=0;
	MC=Monte_Carlo(&MC,n,m,0);
	cout << "Оценка сложности(метод Монте-Карло):   " << MC << endl;
	system("pause");
	return 1;
}

