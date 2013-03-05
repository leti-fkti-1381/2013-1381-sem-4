#ifndef _lr1
#define _lr1
#include <iostream>
#include <time.h>

int *Get_Numbers(int n);				//Генерация последовательности из n случайных элементов в пределах -100 до 99
int *Bubble(int *mass, int n, int *sravn);				//Пузырьковая сортировка
int *Merge(int *mass,int n, int *sravn);				//Сортировка слиянием
int *Step2(int *a,int m,int *b,int k, int *sravn);		//Слияние массивов
bool Check_Sort(int *a, int n);				//Проверка на неубывание

int *Bubble(int *mass, int n, int *sravn)
{
	int *result=new int [n],b;
	sravn[0]=0;
	for(int i=0;i<n;i++)
		result[i]=mass[i];
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
		{
			sravn[0]++;
			if(result[i]>result[j])
			{
				b=result[i];
				result[i]=result[j];
				result[j]=b;
			}
		}
	return result;
}
int *Merge(int *mass,int n, int *sravn)
{
	int i=0,*a=NULL,m=0,*b=NULL,k=0;
	bool p=0;							//Если p=0, то пишем в массив а, иначе в b
	if(Check_Sort(mass,n)) return mass;		//Проверка на неубывание
	while(i<n)
	{
		if(p==0)   
		{
			a=(int*)realloc(a,(m+1)*sizeof(int));
			a[m]=mass[i];
			m++;		//кол-во записанных элементов
		}
		else
		{
			b=(int*)realloc(b,(k+1)*sizeof(int));
			b[k]=mass[i];
			k++;	//кол-во записанных элементов
		}
		sravn[0]++;
		if(mass[i]>mass[i+1]) p=!p;   //Если нарушен порядок неубывания, то выбираем другой массив
		i++;
	}
	a=Merge(a,m,sravn);  //разбиваем первй массив
	b=Merge(b,k,sravn);	//разбиваем второй массив
	int *result;
	result=Step2(a,m,b,k,sravn);   //слияние полученных массивов а и b
	return result;
}
int *Step2(int *a,int m,int *b,int k,int *sravn)
{
	int i=1,m1=m,k1=k;
	int *res=new int[m+k];
	//определяем первый элемент массива
	sravn[0]++;
	if(a[0]<=b[0])     
	{
		res[0]=a[0];
		m1--;
	}
	else
	{
		res[0]=b[0];
		k1--;
	}
	while(!(m1==0 || k1==0))  //пока не кончился массив а или b
	{
		sravn[0]++;
		if(a[m-m1]<=b[k-k1])  //если элемент текущий элемент в массиве а небольше чем текущий элемент массива b
		{
			res[i]=a[m-m1];	//в результат пишем текущий элемент а
			m1--;
			i++;
		}
		else
		{
			res[i]=b[k-k1];  //в результат пишем текущий элемент b
			k1--;
			i++;
		}
	}
	if(m1==0)   //если массив а кончился
	{
		while(k1!=0)    //дописываем массив b
		{
			res[i]=b[k-k1];
			k1--;
			i++;
		}
	}
	else
	{
		while(m1!=0)	//дописываем массив а
		{
			res[i]=a[m-m1];
			m1--;
			i++;
		}
	}
	return res;
}
bool Check_Sort(int *a, int n)
{
	if(n==1) return true;
	for(int i=0;i<n-1;i++)
		if(a[i]>a[i+1]) return false;
	return true;

}
int *Get_Numbers(int n)
{
	int *a;
	a=new int[n];
	srand(time(NULL));
	for(int i=0;i<n;i++) a[i]=rand()%200-100;
	return a;
}
#endif