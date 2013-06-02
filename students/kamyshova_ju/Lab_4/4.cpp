// ---------------------------------------------
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;
// -------------------------------------------
typedef int* tint; // указатель на int
void main ()
{ // int max=100; // Максимальный вес ребра
int n,j; // количество вершин
tint* G; // исходный граф
tint* H; // матрица списка ребер с весом
tint* K; /*матрица, отмечающая принадлежность
вершины компоненте*/
tint* T; // матрица остовного дерева
tint* L; // список ребер с ценами минимального дерева
// -----ввод графа
int max,i;
cout<<" Maximalno dopustimoe zna4enie vesa rebra = ";
cin>> max;
cout<<"\n Vvedite 4ilo vershin: \n ";
cin>> n;
G=new tint [n];
for (i=0; i<n; i++)
G [i] =new int [n];
cout<<" Vvedite nignij treugolnik matrici stoimosti: \n ";
for (i=1; i<n; i++)
for (j=0; j<i; j++) {
cin>> G [i] [j];
}
for (i=1; i<n; i++)
for (j=0; j<i; j++)
G [j] [i] =G [i] [j];
// ---выделение памяти для списка ребер---
int kolreb=0;
for (i=1; i<n; i++)
for (j=0; j<i; j++)
if (G [i] [j] <max && G [i] [j]!=0)
kolreb++;
H=new tint [kolreb];
for (i=0; i<kolreb; i++)
H [i] =new int [3];
// -------------------------------------------
int a=0;
for (i=1; i<n; i++)
for (j=0; j<i; j++)
if (G [i] [j] <max && G [i] [j]!=0) {
H [a] [0] =i+1;
H [a] [1] =j+1;
H [a] [2] =G [i] [j];
a++;
}
cout<<endl;
// ----сортировка ребер по возрастанию веса
int f,d,s;
for (i=0; i<kolreb-1; i++)
for (j=0; j<kolreb-1; j++)
if (H [j] [2] <H [j+1] [2]) {
f=H [j] [2];
H [j] [2] =H [j+1] [2];
H [j+1] [2] =f;
d=H [j] [0];
H [j] [0] =H [j+1] [0];
H [j+1] [0] =d;
s=H [j] [1];
H [j] [1] =H [j+1] [1];
H [j+1] [1] =s;
}
// вывод ребер отсортированных по возрастанию веса
cout<<"Matrica dostigimosni otsortirovannoe po ubivaniuy: \n ";
for (i=0; i<kolreb; i++) {
cout<<H [i] [0] <<"-->";
cout<<H [i] [1] <<" = ";
cout<<H [i] [2] <<endl;
cout<<" ";
}
for (i=0; i<kolreb; i++) {
H [i] [0] --;
H [i] [1] --;
}
// матрица для определения компоненты
K=new tint [n];
for (i=0; i<n; i++)
K [i] =new int [2];
for (i=0; i<n; i++) {
K [i] [0] =i;
K [i] [1] =0;
}
// ----матрица остовного дерева
T=new tint [n];
for (i=0; i<n; i++)
T [i] =new int [n];
for (i=0; i<n; i++)
for (j=0; j<n; j++)
T [i] [j] =0;
// -присоединение первого ребра
T [H [0] [0]] [H [0] [1]] =H [0] [2];
T [H [0] [1]] [H [0] [0]] =H [0] [2];
K [H [0] [0]] [1] =1;
K [H [0] [1]] [1] =1;
// алгорит соединения ребер без создания цикла:
int m=2; // номер компоненты
for (i=1; i<kolreb; i++) // пройти по всем ребрам
if (K [H [i] [0]] [1]!=K [H [i] [1]] [1])
// если 2 вершины не из одной компоненты
{
if (K [H [i] [0]] [1] >0 && K [H [i] [1]] [1] >0)
// если обе вершины принадлежат разной компоненте
{
for (j=0; j<n; j++)
if (K [H [i] [1]] [1] ==K [j] [1])
K [j] [1] =K [H [i] [0]] [1];
K [H [i] [1]] [1] =K [H [i] [0]] [1];
T [H [i] [0]] [H [i] [1]] =H [i] [2];
T [H [i] [1]] [H [i] [0]] =H [i] [2];
}
if ( (K [H [i] [0]] [1] >0 && K [H [i] [1]] [1] ==0)
|| (K [H [i] [0]] [1] ==0 && K [H [i] [1]] [1] >0))
// если одна вершина имеет компоненту а др. нет
{
if (K [H [i] [0]] [1]!=0)
K [H [i] [1]] [1] =K [H [i] [0]] [1];
if (K [H [i] [1]] [1]!=0)
K [H [i] [0]] [1] =K [H [i] [1]] [1];
T [H [i] [0]] [H [i] [1]] =H [i] [2];
T [H [i] [1]] [H [i] [0]] =H [i] [2];
}
if (K [H [i] [0]] [1] ==0 && K [H [i] [1]] [1] ==0)
// если обе вершины не имели компоненты
{
K [H [i] [0]] [1] =m;
K [H [i] [1]] [1] =m;
T [H [i] [0]] [H [i] [1]] =H [i] [2];
T [H [i] [1]] [H [i] [0]] =H [i] [2];
m++;
}
} // конец проверки всех ребер
// ---выделение памяти для списка ребер
kolreb=0;
for (int i=1; i<n; i++)
for (int j=0; j<i; j++)
if (T[i][j] <max && T[i][j]!=0)
kolreb++;
L=new tint [kolreb];
for (int i=0; i<kolreb; i++)
L [i] =new int [3];
// ------------------------------------------
// ---вывод ребер
cout<<endl<<" Vivod reber maximalnogo vesa: \n ";
a=0;
for (int i=1; i<n; i++)
for (int j=0; j<i; j++)
if (T [i] [j] <max && T [i] [j]!=0) {
L [a] [0] =i+1;
L [a] [1] =j+1;
L [a] [2] =T [i] [j];
a++;
}
for (int i=0; i<kolreb; i++) {
cout<<L [i] [0] <<"-->";
cout<<L [i] [1] <<" = ";
cout<<L [i] [2] <<"\n ";
}
int b=0;
for (int i=0; i<kolreb; i++)
b+=L [i] [2];
cout<<endl <<" Stoimost dereva = "<<b; // вывод стоимости
getch ();
// return 0;
}
// --------------------------------------------------------------
