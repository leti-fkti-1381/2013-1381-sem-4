#include "stdafx.h"
#include <iostream>
#include "menu.h"

using namespace std;

void Menu::helloWorld()
{
	system("cls");
	cout << "=============================Лабораторная работа №3============================" << endl;
	cout << "========================Задача 2.2. Почтовые отделения=========================" << endl << endl;
	cout << "================Выполнила студентка группы №1381 Камышова Ю.А.====================" << endl << endl;
}

void Menu::print_in_menu()
{
    cout << "1. Ввод из файла" << endl;
	cout << "2. Ввод с клавиатуры" << endl << endl << endl << endl;
	cout << "Введите номер операции ";
	cin >> this->var_menu;
}

void Menu::print_out_menu()
{
    cout << "1. Сохранение в файл" << endl;
	cout << "2. Вывод на экран" << endl << endl << endl << endl;
	cout << "Введите номер операции ";
	cin >> this->var_menu;
}

int Menu::getVar_menu()
{
	return this->var_menu;
}

void Menu::error_message()
{
	cout << "ОШИБКА ВХОДНЫХ ДАННЫХ" << endl;
}