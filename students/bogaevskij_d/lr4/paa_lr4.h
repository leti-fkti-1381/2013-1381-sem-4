#ifndef _paa_lr4
#define _paa_lr4
#include "Counter.h"
bool inMass(int *mass, int a) //массив должен заканчиватся -1
{
	int i=0;
	while(mass[i]!=-1)
	{
		if(mass[i]==a) return true;
		i++;
	}
	return false;
}

void add_in_mass(int *mass, int a) //добавить в массив
{
	int i=0;
	while(mass[i]!=-1) i++;
	mass[i]=a;
	mass[i+1]=-1;
}

int *f_min(int a[500][500], int *was_here, int n, Counter *ct) //находит минимальный элемент из заданных строк(was_here) в матрице
{
	int i_min=9999;
	int j_min=9999;
	int min=99999;
	int *solve=new int [2];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(a[i][j]!=-1) ct[0].inc();
			if(inMass(was_here,i) && !inMass(was_here,j) && a[i][j]<min && a[i][j]>=0)
			{
				i_min=i;
				j_min=j;
				min=a[i][j];
			}
		}
	}
	solve[0]=i_min;
	solve[1]=j_min;
	return solve;
}
#endif