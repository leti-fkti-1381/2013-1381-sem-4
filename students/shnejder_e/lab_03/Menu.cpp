#include <iostream>
#include "Menu.h"

using namespace std;

void Menu::print_in_menu()
{
    cout << "1. ���� �� �����" << endl;
	cout << "2. ���� � ����������" << endl << endl << endl << endl;
	cout << "������� ����� �������� ";
	cin >> this->var_menu;
}

void Menu::print_out_menu()
{
    cout << "1. ���������� � ����" << endl;
	cout << "2. ����� �� �����" << endl << endl << endl << endl;
	cout << "������� ����� �������� ";
	cin >> this->var_menu;
}

int Menu::getVar_menu()
{
	return this->var_menu;
}

void Menu::error_message()
{
	cout << "������ �����!" << endl;
}
