#include <iostream>
#include <stdlib.h>
#include <locale>
#include "time_meter.hpp"
#include "lr_2.h"
using namespace std;

//---------------------------------------------------------------
int main ()
{
	system ("cls");
	setlocale (LC_ALL, "Russian");
	
	cout << "���������, ����������� ���������� ������� �� ������� ����� ��������� ������, ����� ��� �� ���� ���� �����" << endl << endl;
	
	int field[max_side][max_side]; // ���������� ����
	// ��������� ����
	for (int i = 0; i < max_side; i ++)
		for (int j = 0; j < max_side; j ++)
			field[i][j] = 0;
	
	int side = 0, // ������ ����(���������� ������ �� ��������� ��� �����������)
		bishop = 0; // ���������� ������
	
	cout << "������� ������ ���� (�� 1 �� 8): ";
	cin >> side;
	cout << "������� ���������� ������ (�� 1 �� '������ ����'*'������ ����'): ";
	cin >> bishop;
	cout << endl;
	
	
	if (side < 1 || side > 8 || bishop < 1 || bishop > side*side)
		cout << "������� ������� ������!!!" << endl;
	else
	{
		TimeMeter::init();
		double amount = amount_position (field, side, bishop);
		cout << "���������� �������: " << amount << endl;
		cout << "����� ����������� �� ����������: " << TimeMeter::getPastTime() << " ������" << endl;
	}
	
	cout << endl;
	system ("pause");
	system ("cls");
	return 0;
}

