#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "polindrome.h"
using namespace std;
#define endl "\n\t"
int main ()
{
	system("chcp 1251");
	char sw;
	bool menu_view = TRUE;
	bool string_generation;
	bool detailed_mode;
	Polindrome polindrome;
	do{
		system("cls");
		cout << endl  << endl << "�������� ������ ����� ���� �������� ��������������� �������:";
		cout << endl << endl << endl << "1. ��������� ������.";
		cout << endl << endl << "2. ���� ������ ��������.";
		cout << endl << endl << "3. ����� �� ���������.";

		fflush(stdin);
		sw=_getch();

		switch (sw) {
			case '1': string_generation = TRUE; menu_view = FALSE; break;
			case '2': string_generation = FALSE; menu_view = FALSE; break;
			case '3': return 1;
			default : menu_view = TRUE;
		}
	}while(menu_view);

	if( !string_generation ) {
		system("cls");
		while( !polindrome.CheckOnCreated() ){
			cout << endl << endl << "������� �������� ������:";
			cout << endl;
			string _str;
			getline(cin, _str);
			cout << endl << _str;
			if ( !polindrome.AddString(_str) ) {
				cout << endl;
				system("pause");
			}
			system("cls");
		}
	}
	else{
		char count_symbols[20] = "";
		while( atoi(count_symbols) < 3 || atoi(count_symbols) > 5000 ){
			system("cls");
			cout << endl << endl << "������� ���������� �������� � ������������ ������:";
			cout << endl;
			cin >> count_symbols;
			if ( atoi(count_symbols) < 3 || atoi(count_symbols) > 5000 ) {
				cout << endl << "������." << endl << "���������� �������� " 
					<< "� ������ �� ������������� ������� (3 - 5000)." << endl;
				system("pause");
			}
		}

		string _str;
		int temp;
		srand(time(0));
		for(int _count_symbols = atoi(count_symbols); _str.length() < _count_symbols;){
			// �-�: -64,-33; �-�: -32,-1; �: -72 ; �: -88; A-Z: 65,90; a-z: 97,122; 0-9: 48,57
			temp = fmod(rand(),127.0);
			if(temp >= 0 && temp < 64)
				_str += temp - 64;
			if(temp >= 64 && temp < 89)
				_str += temp + 1;
			if(temp >= 89 && temp < 115)
				_str += temp + 8;
			if(temp > 116)
				_str += temp -69;
			if(temp == 115)
				_str += -72;
			if(temp == 116)
				_str += -88;
		}
		polindrome.AddString(_str);
		cout << endl << "������������� ������:" 
			<< endl << _str << endl << endl;
		system("pause");
	}

	system("cls");

	if(polindrome.Size() < 19){
		do{
			system("cls");
			cout << endl << endl << "�������� ������ ����� ���� �������� ��������������� �������:";
			cout << endl << endl << endl << "1. ����� �������"
				<< " � �������������� ������" << endl
				<< "   � ������� ��������� �������� �� �����.";
			cout << endl << endl << "2. ����� �������"
				<< " � ������ ������"<<endl
				<< "   � ������� ��������� �������� �� �����.";

			fflush(stdin);
			sw=_getch();

			switch (sw) {
			case '1': detailed_mode = FALSE; menu_view = FALSE; break;
			case '2': detailed_mode = TRUE; menu_view = FALSE; break;
			default : menu_view = TRUE;
			}
		}while(menu_view);
	}
	else
		detailed_mode = FALSE;
	polindrome.FindSolution(detailed_mode);
	cout << endl << "��������� ������� ���������. ";
	system("pause");

	return 0;
}
