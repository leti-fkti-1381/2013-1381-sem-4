#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <math.h>
enum Color
{
	Black       = 0,
	Grey        = FOREGROUND_INTENSITY,
	LightGrey   = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
	White       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Blue        = FOREGROUND_BLUE,
	Green       = FOREGROUND_GREEN,
	Cyan        = FOREGROUND_GREEN | FOREGROUND_BLUE,
	Red         = FOREGROUND_RED,
	Purple      = FOREGROUND_RED   | FOREGROUND_BLUE,
	LightBlue   = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
	LightGreen  = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	LightCyan   = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
	LightRed    = FOREGROUND_RED   | FOREGROUND_INTENSITY,
	LightPurple = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
	Orange      = FOREGROUND_RED   | FOREGROUND_GREEN,
	Yellow      = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
};
using namespace std;
class Polindrome{
public: 
	Polindrome(): Width(0), solution(-1), m(NULL) {}

public: 
	bool AddString (string _str) {
		if (_str.length() < 3 || _str.length() > 5000){
			cout << endl << "Ошибка." << endl << "Количество символов " 
				<< "в строке не соответствует условию (3 - 5000).";
			return FALSE;
		}
		
		str = _str;
		CreateNewMassive(_str.length());
		return TRUE;
	}

private: 
	void CreateNewMassive(int n){
			Width = n;
			m = new int*[n];
			for(int i = 0; i < n; i++){
				m[i] = new int[n];
				for(int j = 0; j < n; j++)
					m[i][j] = 0;
			}
		}

private: 
	int Width;
	int **m;
	int solution;
	string str;

public:
	bool CheckOnCreated(){
		if (m) return TRUE;
		return FALSE;
	}

public:
	void Print( int x = 0, int y = 0, int flag = 0) {
		if(Width < 19){
			for(int i = 0; i < Width; i++) {
				cout << endl <<  "   +";
				for(int k = 0; k < Width; k++)
					cout << "--+";
				cout << endl <<  "   |";
				for(int j = 0; j < Width; j++){
					if((x || y) && i == x + 1 && j == y - 1 && flag == 1) 
						SetColor(LightGreen);
					if((x || y) && ((i == x + 1 && j == y) 
						|| (i == x && j == y - 1)) && flag == 2) 
						SetColor(LightGreen);
					if((x || y) && i == x && j == y) SetColor(LightRed);
					printf("%2d", m[i][j]);
					if((x || y) && i == x && j == y || flag) SetColor(LightGrey);
					cout << "|";
				}
			}
			cout << endl <<  "   +";
			for(int k = 0; k < Width; k++)
				cout << "--+";
			cout << endl;
		}
		else{
			cout << endl << endl << "Слишком большая матрица для вывода." << endl;
		}
	}

private:
	int PrintString(int x = 0, int y = 0){
		cout << endl << "Исходная строка: ";
		if(!x && !y){
			cout << str;
			return 1;
		}
		for(int i = 0; i<Width; i++){
			if(i == x || i == y) SetColor(LightRed);
			cout << str[i];
			if(i == x || i == y) SetColor(LightGrey);
		}
		return 1;
	}

private:
	void SetColor(Color color){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	}

public:
	int Size(){
		return Width;
	}

public:
	void FindSolution (bool detailed_mode) {
		int x, y, difference;
		
		for(difference = 1; difference < str.length() ; difference++){
			for(x = 0, y = difference; y < str.length(); x++, y++){
				if(str[x] == str[y]){
					m[x][y] = m[x+1][y-1];
					if(detailed_mode){
						system("cls"); 
						PrintString(x,y);
						cout << endl << endl << "Выделенные символы в строке ";
							SetColor(LightGreen); cout << "равны"; SetColor(LightGrey);
						cout << "." << endl 
							<< endl << "Значение выделенного красным элемента матрицы равно зеленому."
							<< endl << endl;
						Print(x,y,1);
						cout << endl << endl;
						system("pause");
					}
				}
				else{
					if(m[x+1][y] < m[x][y-1])
						m[x][y] = m[x+1][y] + 1;
					else
						m[x][y] = m[x][y-1] + 1;

					if(detailed_mode){
						system("cls"); 
						PrintString(x,y);
						cout << endl << endl << "Выделенные символы в строке ";
						SetColor(LightRed); cout << "не равны"; SetColor(LightGrey);
						cout << "." << endl 
							<< endl << "Значение выделенного красным элемента матрицы равно" 
							<< " минимальному " << endl << "из зеленых и увеличено на единицу."
							<< endl;
						Print(x,y,2);
						cout << endl << endl;
						system("pause");
					}
				}
			}
		}

		system("cls");
		PrintString();
		SetColor(LightGreen); 
		cout << endl << endl << endl << "Решение для исходной задачи с палиндромом найдено. ";
		SetColor(LightGrey);
		cout << endl << endl << "Минимальное количество символов для вставки в строку: ";
		SetColor(LightGreen); 
		cout << m[0][Width-1] << endl;
		SetColor(LightGrey);
		Print(0,Width-1);
	}
	int FindSolution_2 (string str,int n) {
		int x, y, difference;
		int **m2;
		Width = n;
		m2 = new int*[n];
			for(int i = 0; i < n; i++){
				m2[i] = new int[n];
				for(int j = 0; j < n; j++)
					m2[i][j] = 0;
			}
		for(difference = 1; difference < n ; difference++){
			for(x = 0, y = difference; y < n; x++, y++){
				if(str[x] == str[y]){
					m2[x][y] = m2[x+1][y-1];
					}
				else
				{
					if(m2[x+1][y] < m2[x][y-1])
						m2[x][y] = m2[x+1][y] + 1;
					else
						m2[x][y] = m2[x][y-1] + 1;

				}		
		}
	}
		int h=m2[0][Width-1];
		return h;
	}
};