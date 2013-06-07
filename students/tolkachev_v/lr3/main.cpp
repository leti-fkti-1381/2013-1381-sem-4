#include <string>
#include <iostream>
#include "windows.h"
using namespace std;

int min_step = INT_MAX;
int y=2;
HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
void GetString( string s1, int i, string s2, int j, int count, int x );//�������� ������ � ������������ ���������
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
void GotoXY( HANDLE StdOut, short x, short y ){//���������� ������� �������
    COORD Cord;
    Cord.X = x;
    Cord.Y = y;
    SetConsoleCursorPosition( StdOut, Cord );
}
//---------------------------------------------------------
void GetString( string s1, int i, string s2, int j, int count, int x ){
	while ( ( s1[i] == s2[j] ) && (i < s1.size() ) && ( j < s2.size() ) ){
		i++;   //���������� ���������� �������
		j++;
	}

	if ( ( i == s1.size() ) || ( j == s2.size() ) ){  //���� ��������� �����
		if ( s1 == s2 )                               //� ������ �����
			min_step = min( min_step, count );        //���������� � ����� ���������� ����������
		else
			if ( count < min_step )                   //���� ������ �� �����
				if ( i == s1.size() ){                //� ����������� ��������� ������, ��������� �������� - �������� ���������,
					count = count + s2.size() - j;    //������� �� ����������, ����������� ���������
					min_step = min( min_step, count );//���������� � ����� ���������� ����������
				}
				else{                                 //���� ����������� ������ ������, ��������� �������� - ������� ���������,
					count = count + s1.size() - j;    //������� �� ����������, ����������� ���������
					min_step = min( min_step, count );//���������� � ����� ���������� ����������
				}	
	}
	else{
		count++;
		
		if ( count < min_step ){
			//------������
			string tmp = s2;
			tmp[j] = s1[i];
			GotoXY( hStdout, x, y );
			cout << tmp;
			GotoXY( hStdout, 20, y );
			cout << " replace '" << s2[j] << "' with '" << s1[i] << "'";
			y++;
			GetString( s1, i + 1, tmp, j + 1, count, x + 2 );

			//------��������
			tmp.erase( j, 1 );
			GotoXY( hStdout, x, y );
			cout << tmp;
			GotoXY( hStdout, 20, y );
			cout << " delete '" << s2[j] << "'";
			y++;
			GetString( s1, i, tmp, j, count, x + 2 );

			//------�������
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
