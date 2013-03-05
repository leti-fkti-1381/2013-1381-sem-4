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
			cout<<"����� ����������: "<<(long double)(clock()-start)<<" ms"<<endl;
			return b.size();
	};

		void selectSort(vector <T> a, int size) 
	{
		clock_t start=clock();
		T tmp;
		for(int i = 0; i < size; ++i) // i - ����� �������� ����
		{ 
			int pos = i; 
			tmp = a[i];
			for(int j = i + 1; j < size; ++j) // ���� ������ ����������� ��������
			{
				if (a[j] < tmp) 
			   {
				   pos = j; 
				   tmp = a[j]; 
			   }
			}
			a[pos] = a[i]; 
			a[i] = tmp; // ������ ������� ���������� � a[i]
		}
		cout<<"����� ���������� ������� "<<size<<" ���������: "<<(long double)(clock()-start)<<" ms"<<endl;
	};

		void qSortI(vector <T> &a, int size) {
 
		unsigned const int MAXSTACK=64;
		clock_t start=clock();
		int i, j; // ���������, ����������� � ����������
		int lb, rb; // ������� ������������ � ����� ���������
 
		int lbstack[MAXSTACK], rbstack[MAXSTACK]; // ���� ��������
		// ������ ������ �������� ����� ��������,
		// � ������: �����(lbstack) � ������(rbstack)
		// ��������� ����������
		int stackpos = 1; // ������� ������� �����
		int ppos; // �������� �������
		T pivot; // ������� �������
		T temp;
 
		lbstack[1] = 0;
		rbstack[1] = size-1;
 
		do {
			// ����� ������� lb � rb �������� ������� �� �����.
			lb = lbstack[ stackpos ];
			rb = rbstack[ stackpos ];
			stackpos--;
 
			do {
				// ��� 1. ���������� �� �������� pivot
				ppos = ( lb + rb ) >> 1;
				i = lb; j = rb; pivot = a[ppos];
				do {
					while ( a[i] < pivot ) i++;//����� �������� ��� �������� � ������� �����
					while ( pivot < a[j] ) j--;//����� �������� ��� �������� � ������� �����
					if ( i <= j ) {
						temp = a[i]; a[i] = a[j]; a[j] = temp;
						i++; j--;
					}
				} while ( i <= j );
 
				// ������ ��������� i ��������� �� ������ ������� ����������,
				// j - �� ����� ������
				// �������� ������, ����� ��������� i ��� j ������� �� ������� �������
 
				// ���� 2, 3. ���������� ������� ����� � ���� � ������� lb,rb
				if ( i < ppos ) { // ������ ����� ������
					if ( i < rb ) { // ���� � ��� ������ 1 �������� - �����
						stackpos++; // �����������, ������ � ����
						lbstack[ stackpos ] = i;
						rbstack[ stackpos ] = rb;
					}
						rb = j; // ��������� �������� ����������
						// ����� �������� � ����� ������
				} else { // ����� ����� ������
					if ( j > lb ) {
						stackpos++;
						lbstack[ stackpos ] = lb;
						rbstack[ stackpos ] = j;
					}
					lb = i;
					}
			} while ( lb < rb ); // ���� � ������� ����� ����� 1 ��������
		} while ( stackpos != 0 ); // ���� ���� ������� � �����
		cout<<"����� ������� ���������� "<<size<<" ���������: "<<(long double)(clock()-start)<<" ms"<<endl;
	};

		void write(vector <T> a)
	{
		clock_t start=clock();
		ofstream out("ofile.txt");
		for (int i=0; i<a.size(); i++)
			out<<a[i]<<endl;
		cout<<"����� ������: "<<(long double)(clock()-start)<<" ms"<<endl;
	};

};