//���������:	���
//������:		1381
//��������:		���������� ���������
//������������ ������ �1 - ���������� �������� (4 �������)

//-------------------------------------------------------------
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include "lr_1.h"
using namespace std;

//---------------------------------------------------------------
int main ()
{
	SetConsoleCP (1251); // ���� � ������� � ��������� 1251
	SetConsoleOutputCP (1251); // ����� �� ������� � ��������� 1251
	string str; // ������
	cout << "���������	��� \n������:		1381 \n��������:	���������� ���������  \n\n";
	cout << "������������ ������ �1 - ���������� �������� (4 �������)\n" << endl << endl;
	cout << "������� ������: ";
	getline (cin, str);
	
	if (str.size() == 0)
		cout << "������� ������ ������!!!" << endl << endl;
	else
	{
		if (debug) cout << endl << "���������� ����������:" << endl;
		sort (str, 0, str.size() - 1); // ������� ����������
		if (debug) cout << "���������:" << endl;
		cout << "��������������� ������: " << str << endl << endl;
	}
	system ("pause");
	return 0;
}
