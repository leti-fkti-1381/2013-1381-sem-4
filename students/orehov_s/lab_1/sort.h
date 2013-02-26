#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;
typedef char T;


class Sortirovka {

	public:
		int enter(vector <T> &b) {
			clock_t start=clock();
			int i=0; T x;
			ifstream in("file.txt");
			while(true)
			{
				in>>x;
				if (!in.eof()) {
					b.push_back(x);
				}
				else break;
			};
			cout<<"Время считывания: "<<(long double)(clock()-start)<<" ms"<<endl;
			return b.size();
	};

		void selectSort(vector <T> a, int size) 
	{
		clock_t start=clock();
		T tmp;
		for(int i = 0; i < size; ++i) // i - номер текущего шага
		{ 
			int pos = i; 
			tmp = a[i];
			for(int j = i + 1; j < size; ++j) // цикл выбора наименьшего элемента
			{
				if (a[j] < tmp) 
			   {
				   pos = j; 
				   tmp = a[j]; 
			   }
			}
			a[pos] = a[i]; 
			a[i] = tmp; // меняем местами наименьший с a[i]
		}
		cout<<"Время сортировки выбором "<<size<<" элементов: "<<(long double)(clock()-start)<<" ms"<<endl;
	};

		void qSortI(vector <T> &a, int size) {
 
		unsigned const int MAXSTACK=64;
		clock_t start=clock();
		int i, j; // указатели, участвующие в разделении
		int lb, rb; // границы сортируемого в цикле фрагмента
 
		int lbstack[MAXSTACK], rbstack[MAXSTACK]; // стек запросов
		// каждый запрос задается парой значений,
		// а именно: левой(lbstack) и правой(rbstack)
		// границами промежутка
		int stackpos = 1; // текущая позиция стека
		int ppos; // середина массива
		T pivot; // опорный элемент
		T temp;
 
		lbstack[1] = 0;
		rbstack[1] = size-1;
 
		do {
			// Взять границы lb и rb текущего массива из стека.
			lb = lbstack[ stackpos ];
			rb = rbstack[ stackpos ];
			stackpos--;
 
			do {
				// Шаг 1. Разделение по элементу pivot
				ppos = ( lb + rb ) >> 1;
				i = lb; j = rb; pivot = a[ppos];
				do {
					while ( a[i] < pivot ) i++;//поиск элемента для переноса в старшую часть
					while ( pivot < a[j] ) j--;//поиск элемента для переноса в младшую часть
					if ( i <= j ) {
						temp = a[i]; a[i] = a[j]; a[j] = temp;
						i++; j--;
					}
				} while ( i <= j );
 
				// Сейчас указатель i указывает на начало правого подмассива,
				// j - на конец левого
				// Возможен случай, когда указатель i или j выходит за границу массива
 
				// Шаги 2, 3. Отправляем большую часть в стек и двигаем lb,rb
				if ( i < ppos ) { // правая часть больше
					if ( i < rb ) { // если в ней больше 1 элемента - нужно
						stackpos++; // сортировать, запрос в стек
						lbstack[ stackpos ] = i;
						rbstack[ stackpos ] = rb;
					}
						rb = j; // следующая итерация разделения
						// будет работать с левой частью
				} else { // левая часть больше
					if ( j > lb ) {
						stackpos++;
						lbstack[ stackpos ] = lb;
						rbstack[ stackpos ] = j;
					}
					lb = i;
					}
			} while ( lb < rb ); // пока в меньшей части более 1 элемента
		} while ( stackpos != 0 ); // пока есть запросы в стеке
		cout<<"Время быстрой сортировки "<<size<<" элементов: "<<(long double)(clock()-start)<<" ms"<<endl;
	};

		void write(vector <T> a)
	{
		clock_t start=clock();
		ofstream out("ofile.txt");
		for (int i=0; i<a.size(); i++)
			out<<a[i]<<endl;
		cout<<"Время записи: "<<(long double)(clock()-start)<<" ms"<<endl;
	};

};