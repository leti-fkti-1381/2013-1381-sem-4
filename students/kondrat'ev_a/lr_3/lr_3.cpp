#include <iostream>
#include <stdlib.h>
#include <locale>
#include <vector>
#include "lr_3.h"
using namespace std;

//---------------------------------------------------------------
int main ()
{
	system ("cls");
	setlocale (LC_ALL, "Russian");
	
	cout << "�������:\n���� ������������������ ����� ������������� ����� a1, a2, ..., an. �� ���� �������� ����������� ������� ����� (����� �������) �����. ���������  �������� ����� ������������ ����� ����� �� ����� �������� �����. ��������� ������� ��� �����, ����� �������, ���, ����� ��������� ��������� ���� �����������. ����������� n<=100, ai<=100. " << endl << endl;
	
	vector <int> arr; // ������ �����
	int amount_arr = 0; // ������ �������
	int item; // ������� �������
	
	cout << "������� ���������� ��������� �������: ";
	cin >> amount_arr;
	for (int i = 0; i < amount_arr; i++)
	{
		cout << "������� " << i+1 << " �������: ";
		cin >> item;
		arr.push_back(item);
	}
	
	int solution = Solution (arr, amount_arr); // �������
	if (solution == -1)
		cout << endl << "������� �������� ������!!!" << endl << endl;
	else
		cout << endl << "���������� �������: " << solution << endl << endl;
	
	system ("pause");
	system ("cls");
	return 0;
}

