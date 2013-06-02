#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;


int n;
 vector < vector<int> > a;      // Матрица эффективности a[разраб][работа]
 vector<int> xy, yx;             // Паросочетания: xy[разраб], yx[работа]
 vector<char> vx, vy;            // Альтернирующее дерево vx[разраб], vy[работа]
 vector<int> minrow, mincol;     // Стоимость назначения, выполненность

bool dotry (int i) {				//Функция нахождения свободных задач по оптимальным ребрам
     if (vx[i]) return false;
     vx[i] = true;
     for (int j=0; j<n; ++j)
         if (a[i][j]-minrow[i]-mincol[j] == 0)
             vy[j] = true;
     for (int j=0; j<n; ++j)
         if (a[i][j]-minrow[i]-mincol[j] == 0 && yx[j] == -1) {
             xy[i] = j;
             yx[j] = i;
             return true;
         }
     for (int j=0; j<n; ++j)
         if (a[i][j]-minrow[i]-mincol[j] == 0 && dotry (yx[j])) {
             xy[i] = j;
             yx[j] = i;
             return true;
         }
     return false;
 }
 
int main() {
//------------Вводим размер и саму матрицу разработчиков и работ
	cin>>n;						
	a.resize(n);
	for (int i=0; i < n; i++)
	{
		a[i].resize(n);
		for(int j = 0; j < n; j++)
			cin>>a[i][j];
	}
//------------Изначально примем, что работы еще не изучена
	mincol.assign (n, 0);
	minrow.assign (n, 0);
	for (int i=0; i<n; ++i)		//и находим минимальную стоимость назначения по разработчику
		for (int j=0; j<n; ++j)
			minrow[i] = min (minrow[i], a[i][j]);

	xy.assign (n, -1);
	yx.assign (n, -1);
	for (int c=0; c<n; ) {
		vx.assign (n, 0);
		vy.assign (n, 0);
		int k = 0;
		for (int i=0; i<n; ++i)			//Пока не всем разработчикам нашли задачи.
			if (xy[i] == -1 && dotry (i))	//Пока удается находить свободные задачи по оптимальным ребрам
				++k;						//«Переназначаем» задачи, увеличивая паросочетания
		c += k;
		if (k == 0) {				//Не достигли свободной задачи. Венгерское дерево.
		int z = INT_MAX;			//Понижаем способности разработчиков на min величину
		for (int i=0; i<n; ++i)											//Далее в цикле мы пробежим по «границе» дерева: по тем ребрам,
			if (vx[i])													//которые соединяют незадействованных разработчиков или разработчиков,
				for (int j=0; j<n; ++j)									//достижимых из них со смежными задачами(по неоптимальным ребрам).
					if (!vy[j])											
						z = min (z,a[i][j] - minrow[i] - mincol[j]);	//и вычисляем минимальное на текущий момент «несоответствие» способностей разработчика
			 for (int i=0; i<n; ++i) {		//Понизим способности разработчиков на z, чтобы присоеденить хотя бы одно ребро к альтернирующему дереву,
				if (vx[i]) minrow[i] -= z;	//по которому будем продолжать поиск оптимальной задачи
				if (vy[i]) mincol[i] += z;	//Повысим изученночть работ на z, чтобы альтернирнирующее дерево оставалось оптимальным
			}
		}
	}

	int ans = 0;
	for (int i=0; i<n; ++i)
		ans += a[i][xy[i]];
	printf ("%d\n", ans);
	for (int i=0; i<n; ++i)
	{
		cout<<i+1<<" - ";
		printf ("%d ", xy[i]+1);
		cout<<"\n";
	}
	_getch();
 }