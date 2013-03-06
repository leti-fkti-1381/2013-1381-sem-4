#ifndef _lr_1
#define _lr_1

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

//---------------------------------------------------------------
const bool debug = false; // ��������� ��� ������ �������

//---------------------------------------------------------------
void sort (string&, int, int); // ������� ���������� (������, ������ ������, ����� ������)
void merge (string&, int, int, int); // ������� ������� (������, ������ ������, �������� ������, ����� ������)

//---------------------------------------------------------------
// ������� ���������� (������, ������ ������, ����� ������)
void sort (string& str, int left, int right)
{
	// � ������ ������ ���� ����� ������ �������
	if (left < right)
	{
		int middle = (left + right)/2; // �������� ������
		sort (str, left, middle); // ���������� ����� ��������
		sort (str, middle+1, right); // ���������� ������ ��������
		merge (str, left, middle, right); // ������� ���� �������
	}
}

//---------------------------------------------------------------
// ������� ������� (������, ������ ������, �������� ������, ����� ������)
void merge (string& str, int left, int middle, int right)
{
	string temp; // ������ ��� �������
	int i = left; // ������ ������� ������ ������
	int j = middle+1; // ������ ������� ������ ������
	
	// ������� ��������� ���� � ������ ������ ���� ���� �� �� ������ �������
	while (i <= middle && j <= right)
	{
		// ��������� ���� ������� ��������� � ������ � �������������� ������
		if (str[i] < str[j])
		{
			temp += str[i];
			i ++;
		}
		else
		{
			temp += str[j];
			j ++;
		}
	}
	// ����������� ������� ������ ������ � ����� ��������������
	while (i <= middle)
	{
		temp += str[i];
		i ++;
	}
	// ����������� ������� ������ ������ � ����� ��������������
	while (j <= right)
	{
		temp += str[j];
		j ++;
	}
	// ����� ���������� ����������
	if (debug)
	{
		cout << endl << "����� �������� ������: ";
		for (int i = left; i <= middle; i ++)
		{
			cout << str[i];
		}
		cout << endl;
		cout << "������ �������� ������: ";
		for (int i = middle+1; i <= right; i ++)
		{
			cout << str[i];
		}
		cout << endl;
		cout << "��������� �������: " << temp << endl << endl;
	}
	// ����������� ��������� ������ � ��������
	for (i = 0; left <= right; left ++, i ++)
		str[left] = temp[i];
}
#endif