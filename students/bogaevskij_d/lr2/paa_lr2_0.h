#ifndef _paa_lr2_0
#define _paa_lr2_0
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class Mark
{
public:
	int number; //достоинство(номер) марки
	int cost;   //цена марки
	void Init(int k);	
};

void Mark::Init(int k)
{
	number=k;
	cout << "\nВведите цену для марки с номером " << number << "     ";
	cin >> cost;
}

void Solve1(Mark **a, Mark *res, Mark *base, int n, int m, int num, int stat); //Рекурсивно находит все комбинации и считает для них цену
void CostSort(Mark **a, int m, int p);	//Сортировка писем по цене, p - кол-во вариантов
int Posl1(Mark **a, int m, int p);  //Находит последовательность в неотсортированном массиве
int Posl(Mark **a, int m, int p);   //Находит последовательность в отсортированном массиве
void MarkSort(Mark **a, int m, int p); //сортирует марки по номерам в письме
bool MasCmp(Mark *a, Mark *b, int m);	//Сравнивает первые m элементов массива а и b(если все равны то 1, иначе 0)
Mark **ChoseAns(Mark **, int m, int n);	//Выбирает неповторяющиеся комбинации
int C(int N, int k);  //N~n, k~m  считает С(k,N+k-1)
int Monte_Carlo(int *res, int n, int m, int cur); //оценка сложности методом Монте-Крало

void Solve1(Mark **a, Mark *res, Mark *base, int n, int m, int num, int *stat)
{
	if(n<m) //если марок на конверте меньше допустимого кол-ва
	{
		
		for(int i=0;i<num;i++)  //рекурсивно подбираем всевозможные комбинации
		{
			res[n]=base[i];		 //записываем в резульитрующий массив текущую марку
			Solve1(a,res,base,n+1,m,num,stat); 
		}
	}
	else	//если достигнут предел марок
	{
		//static int stat=0;		//статическая переменная для записи резульата в двумерный массив
		int sum=0;				
		for(int i=0;i<m;i++)
		{
			a[stat[0]][i]=res[i];	//сохраняем результат
			sum+=res[i].cost;	//считаем общую цену
		}
		a[stat[0]][m].cost=sum;  //записываем общую цену в m столбик
		stat[0]++;
	}
}

void CostSort(Mark **a, int m, int p)
{
	for(int i=0;i<p-1;i++)  //сортируем m столбик, в который записана общая цена
	{
		for(int j=i+1;j<p;j++)	
		{
			if(a[i][m].cost>a[j][m].cost)
			{
				Mark *b=a[i];
				a[i]=a[j];
				a[j]=b;
			}
		}
	}
}

int Posl1(Mark **a, int m, int p)
{
	int i=0, next=1;
	while(i<p)
	{
		if(a[i][m].cost==next)
		{
			i=0;
			next++;
		}
		i++;
	}
	next--;
	return next;
}


int Posl(Mark **a, int m, int p) 
{
	int min, max,s;
	min=a[0][m].cost; //минимальная цена(по умолчанию 0(первая комбинация нулей))
	max=min;
	s=min;
	for(int i=1;i<p;i++)
		if(a[i-1][m].cost<a[i][m].cost)  //если текущий элемент больше предидущего
		{
			s++;				// - следующее по счету число
			max=a[i][m].cost;	// - цена текущего элемента
			if(max!=s)			//если не равны, то найдена последовательность
			{
				max=s-1;
				cout << "\nРезультат: от " << min << " до " << max << endl;
				return max;
			}
		}
}

void MarkSort(Mark **a, int m, int p)
{
	for(int k=0;k<p;k++)	//для каждой строки
		for(int i=0;i<m-1;i++)	//сортируем текущую строку
			for(int j=i+1;j<m;j++)
				if(a[k][i].number>a[k][j].number)
				{
					Mark b=a[k][i];
					a[k][i]=a[k][j];
					a[k][j]=b;
				}
}

bool MasCmp(Mark *a, Mark *b, int m)
{
	for(int i=0;i<m;i++)
	{
		if(a[i].number!=b[i].number) return false; //если находим неравные элементы возвращаем 0
	}
	return true;
}

int C(int N, int k) //N~n, k~m    С(k,N+k-1)=(N+k-1)!/(k!*(N-1)!) - количество комбинаций после выкидывания одинаковых
{
	int ch=1;
	int zn1=1;
	int zn2=1;
	for(int i=1; i<N+k;i++)
		ch*=i;
	for(int i=1; i<k+1;i++)
		zn1*=i;
	for(int i=1; i<N;i++)
		zn1*=i;
	int res=ch/(zn1*zn2);
	return res;
}

Mark **ChoseAns(Mark **a, int m, int n) 
{
	Mark **res;
	int p=pow((double)n,m);  //кол-во всех комбинаций
	res=new Mark* [C(n,m)];		//кол-во нужных комбинаций
	*res=new Mark [m];
	res[0]=a[0];		//записываем начальную комбинацию
	int q=1;
	for(int i=1;i<p;i++)  //для каждой комбинации
	{
		bool p=0;
		for(int j=0;j<q;j++)  //проверяем есть ли она в резульирующем массиве комбинаций
		{
			if(MasCmp(a[i],res[j],m)) p=1;  
		}
		if(p==0)		//если нету записываем ее
		{
			res[q]=a[i];
			q++;
		}
	}
	return res;
}

int Monte_Carlo(int *res,int n, int m, int cur)
{
	int pr=n;
	if(cur<m) //пока рекурсивно не дойдем до последней ветки
	{
		for(int j=0;j<cur;j++)
				pr*=n;
		pr*=n;    //т.к. в данной задаче все ветки одинаковые, то умножаем на их кол-во
		res[0]+=pr; //находим сумму
		Monte_Carlo(&res[0],n,m,cur+1);
	}
	return res[0]/pow((double)n,m-1);
}

#endif