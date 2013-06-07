#include <string>
#include <iostream>
#include "windows.h"
using namespace std;

int min_step = INT_MAX;
int y=2;
HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
void GetString( string s1, int i, string s2, int j, int count, int x );//получить строку и редакционное растояние
void GotoXY( HANDLE StdOut, short x, short y );
//---------------------------------------------------------
int main(){
	string str1,str2;
	int t1,t2;
	cout << "Please, enter the first string:" << endl;
	cin >> str1;
	cout << "Please, enter the second string:" << endl;
	cin >> str2;
	system( "cls" );
	cout << "Convert string '" << str2 << "' to '" << str1 << "':" << endl;	
	
	t1 = GetTickCount();
	GetString( str1, 0, str2, 0, 0, 0 );
	t2 = GetTickCount();
	cout << "\n\nMinimum number of operations: " << min_step << "\nTime: " << t2-t1 << endl;

	
	system( "pause" );
}
//--------------------------------------------------------------
void GotoXY( HANDLE StdOut, short x, short y ){//установить позицию курсора
    COORD Cord;
    Cord.X = x;
    Cord.Y = y;
    SetConsoleCursorPosition( StdOut, Cord );
}
//---------------------------------------------------------
void GetString( string s1, int i, string s2, int j, int count, int x ){
	while ( ( s1[i] == s2[j] ) && (i < s1.size() ) && ( j < s2.size() ) ){
		i++;   //пропускаем одинаковые символы
		j++;
	}

	if ( ( i == s1.size() ) || ( j == s2.size() ) ){  //если достигнут конец
		if ( s1 == s2 )                               //и строки равны
			min_step = min( min_step, count );        //сравниваем с ранее полученной стоимостью
		else
			if ( count < min_step )                   //если строки не равны
				if ( i == s1.size() ){                //и закончилась эталонная строка, остальные операции - удаление элементов,
					count = count + s2.size() - j;    //считаем их количество, увеличиваем стоимость
					min_step = min( min_step, count );//сравниваем с ранее полученной стоимостью
				}
				else{                                 //если закончилась вторая строка, остальные операции - вставка элементов,
					count = count + s1.size() - j;    //считаем их количество, увеличиваем стоимость
					min_step = min( min_step, count );//сравниваем с ранее полученной стоимостью
				}	
	}
	else{
		count++;
		
		if ( count < min_step ){
			//------замена
			string tmp = s2;
			tmp[j] = s1[i];
			GotoXY( hStdout, x, y );
			cout << tmp;
			GotoXY( hStdout, 20, y );
			cout << " replace '" << s2[j] << "' with '" << s1[i] << "'";
			y++;
			GetString( s1, i + 1, tmp, j + 1, count, x + 2 );

			//------удаление
			tmp.erase( j, 1 );
			GotoXY( hStdout, x, y );
			cout << tmp;
			GotoXY( hStdout, 20, y );
			cout << " delete '" << s2[j] << "'";
			y++;
			GetString( s1, i, tmp, j, count, x + 2 );

			//------вставка
			tmp = s2;
			tmp.insert( j, &s1[i], 1 );
			GotoXY( hStdout, x, y );
			cout << tmp;
			GotoXY( hStdout, 20, y );
			cout << " insert '" << s1[i] << "' before '" << s2[j] << "'";
			y++;
			GetString( s1, i + 1, tmp, j + 1, count, x + 2 );
		}
	}
}
