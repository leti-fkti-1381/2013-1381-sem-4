#include <iostream>
#include <time.h>
#include "lr1.h"

using namespace std;

//#define deb

int main()
{
	setlocale(0,"Rus");
	int *mass,n,*res;
	cout << "������� ���-�� ���������\n";
	cin >> n;				
	mass=Get_Numbers(n);		//��������� ������� ��������������� �����
	
#ifdef deb
	cout << "\n�� �����:\n";
	for(int i=0;i<n;i++)
		cout << mass[i] << "  ";
#endif

	int sravn=0;
	clock_t t;
	cout << "\n����� ���������� ���������� �������:   ";
	t=clock();
	res=Merge(mass,n,&sravn);    //���������� ������������ ��������
	t=clock()-t;
	cout << (double)t/CLOCKS_PER_SEC << endl <<"���-�� ���������:  " << sravn << endl;
#ifdef deb
	cout << "\n���������������(��������):\n";
	for(int i=0;i<n;i++)
		cout << res[i] << "  ";
#endif	
	
	sravn=0;
	cout << "\n����� ���������� ����������� ����������:   ";
	t=clock();
	res=Bubble(mass,n,&sravn);    //���������� ������������ ��������
	t=clock()-t;
	cout << (double)t/CLOCKS_PER_SEC << endl <<"���-�� ���������:  " << sravn << endl;
		
#ifdef deb
	cout << "\n���������������(�����������):\n";
	for(int i=0;i<n;i++)
		cout << res[i] << "  ";
#endif	
	system("pause");
	return 1;
}
