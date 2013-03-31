#include "stdafx.h"
#include <fstream>
#include "func.h"
#include <stdio.h>
#include <ctime>    
#pragma once
using namespace std;
int *Generation(int h1,int a,int b)
{
  int i;
	int *d = new int[h1];
	int bebebe = b - a;
	 for (i = 0; i < h1; i++)
		 d[i]= rand()%bebebe + a;
 return d;
};
// функция чтения из файла
int * aaa(char *filename, int *h1)
{
	int i;
	int *mass = NULL;
	ifstream in (filename);
	for(i = 0; !in.eof(); i ++)
	{
		mass = (int *)realloc(mass, (i+1)*sizeof(int));
		in >> mass[i];
	}
	*h1 = i;
	return mass;
}
void sort(int *d, int from, int to) 
{
	
    int i, j;
    int x, temp;
    if (from >= to){
       return;
    }
    i = from;
    j = to;
    x = d[(from+to)/2];
    temp = d[i];
	while (i <= j) 
	{
		while (d[i] < x) 
		{
		i++;
		}
		while (d[j] > x) {
		j--;
		};
		if (i <= j) 
		{
		temp = d[i]; 
		d[i] = d[j];
		d[j] = temp;
		i++;
		j--;
		}
	}
	sort(d, from, j);
	sort(d, i, to);
};
int cmp(const void *a, const void *b) {
     return *(int*)a - *(int*)b;
 }
