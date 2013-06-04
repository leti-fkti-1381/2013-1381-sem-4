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
	cout << "������� ���������� ��������� �����:   ";
	cin >> n;
	cout << "\n������� ������������ ����� ����� �� ������:   ";
	cin >> m;  
	n++;
	base=new Mark [n];
	//��������� ������ �����
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
	Solve1(a,res,base,0,m,n,&stat);  //������������� ������������ ����������
#ifdef debug
	CostSort(a,m,p);			//��������� ���������� �� ����
	MarkSort(a,m,p);			//��������� ����� �� 
	Posl(a,m,p);	//������� ������������������ 0,1,2,...,N,(N - ����������� �����) � ������� �� �� �����
	result=ChoseAns(a,m,n);  //������� ������ ���������� (���������� ������������� �������)
	cout << endl;
#endif	
	int rs=Posl1(a,m,p);			//������� ������������������ 0,1,2,...,N,(N - ����������� �����) � ������� �� �� �����
	cout << 0 << "..." << rs << endl;
#ifdef debug
	//����� �����������:
	cout << endl << "���������� �������: (� ������� ����)";
	for(int i=0;i<C(n,m);i++)
	{
		cout << endl;
		for(int j=0;j<m;j++)
		{
			cout << result[i][j].number << "(" << result[i][j].cost << ") ";
		}
		cout << "    ����: " << result[i][m].cost;
	}
	cout << endl;
#endif
	//������ ��������� ������� �����-�����
	int MC=0;
	MC=Monte_Carlo(&MC,n,m,0);
	cout << "������ ���������(����� �����-�����):   " << MC << endl;
	system("pause");
	return 1;
}

