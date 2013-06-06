// ������_������.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <time.h>

vector<Lisp<int> > list;
int *nv,*fn,*sn,*tn;
int N;

//������� �� ����� ������ ���������
bool readFile( ifstream &infile )
{
	if( !infile )		return false;
	char t;
	int q;
	string t1;
	while( infile >> t )
	{
		Lisp<int> a;
		infile >> q >> t1;
		stringstream ss;

		while( t1[t1.length()-1] != ')' )
		{
			ss << t1;
			ss >> q;
			ss.clear();
			a.insert( q-1 );
			infile >> t1;
		}
		if( t1.length() > 1 )
		{
		ss << t1;
		ss >> q;
		a.insert( q-1 );
		}
		//������� �������� �� ����� ������� � ������ ������ ������
		vector<Lisp<int> >::iterator en = list.end();
		list.insert( en, a );
	}
	return true;
}

int k = 0,h = 0,STEP;

//����� � �������, �� ���� ������� �������
void searchDepth( int curr )
{
	//������ � ������ ������ � ������� curr
	list[curr].moveHead( );
	//���� �� ������� ��� ����
	if( list[curr].getSize() == 0 )
	{
		STEP++;
		if( nv[curr] == 0 )
			nv[curr] = ++k;
		cout << "��������� � ������� " << curr+1 << endl;
	}
	//���������� ������������ ����
	for( int i = 0; i < list[curr].getSize(); i++ )
	{
		if( nv[curr] == 0 )
			nv[curr] = ++k;
		cout << "���� �� ������� " << curr+1 << " � ������� " << list[curr].getCurr()+1 << endl;
		STEP++;
		
		//������������� ������� � ������� �����
		searchDepth( list[curr].getCurr() );

		cout << "������������ �� ������� " << list[curr].getCurr()+1 << " � ������� " << curr+1 << endl;
		list[curr].moveR();
	}
	if( fn[curr] == 0 )
		fn[curr] = ++h;
}

//������ ��� �������� �� �����
vector<int> check;

//�������� �� ������� ������
bool checkWhile( int curr )
{
	//������� �������� �� ����� � ������ ������� �������
	vector<int>::iterator en = check.end();
	check.insert( en,curr );
	list[curr].moveHead();
	//���������� ��� ����
	for( int i = 0; i < list[curr].getSize(); i++ )
	{
		//���� ���������� � �������
		for( unsigned int i = 0; i < check.size(); i++ )
			if( check[i] == list[curr].getCurr() )
			{
				cout << curr+1 << " " << list[curr].getCurr() << endl;
				return false;
			}
		//���� � ��������� �������
		if( !checkWhile( list[curr].getCurr() ) )
			return false;
		//������� �� ������� �������
		vector<int>::iterator it = check.begin(), en2 = check.end();
		for( ; it != en2; ++it )
		{
			if( (*it) == list[curr].getCurr() )
			{
				check.erase( it );
				break;
			}
		}
		list[curr].moveR();
	}
	return true;
}

int main()
{
	srand((int)time(0));
	SetConsoleOutputCP( 1251 );
	cout << "		�������� ������\n\n";
	
	char file[256];

	cout << "������� ��� ����� � ������: ";
	cin >> file;
	ifstream infile( file );

	if( !readFile( infile ) )
	{
		cout << "���� �� ������.";
		_getch();
		return 0;
	}

	int startPosition;

	cout << "������� ����� ������� � ������� ���������� ������: ";
	cin >> startPosition;


	



	N  = list.size();
	nv = new int[N];
	fn = new int[N];
	sn = new int[N];
	tn = new int[N];



	for( int i = 0; i < N; i++ )
	{
		nv[i] = fn[i] = sn[i] = tn[i] = 0;
	}

	if( ! checkWhile( startPosition - 1 ) )
	{
		cout << "� ����� ������ ����!";
		_getch();
		return 0;
	}

	cout << "\n������ ���������: \n------------------------------------\n";
	long c = clock();
	searchDepth( startPosition - 1 );
	for( int i = 0; i < N; i++ )
	{
		if( nv[i] == 0 )
			searchDepth( i );
	}
	cout << "------------------------------------\n\n����������:\n------------------------------------\n";
	float end = (float)(clock()-c)/1000;

	cout << " v ";
	for( int i = 0; i < N; i++ )
		cout << i+1 << " ";
	cout << endl << "nv ";

	for( int i = 0; i < N; i++ )
	{
		cout << nv[i] << " ";
	}
	cout << endl << "fn ";
	for( int i = 0; i < N; i++ )
	{
		cout << fn[i] << " ";		
		sn[i] = N - fn[i] + 1;
	}
	cout << endl << "sn ";
	for( int i = 0; i < N; i++ )
	{
		cout << sn[i] << " ";
		tn[sn[i]-1] = i+1;
	}
	cout << endl << "tn ";
	for( int i = 0; i < N; i++ )
	{
		cout << tn[i] << " ";
	}

	cout << "\n\n����� ���������: " << end << " ������.\n";
	cout << "���������� �����: " << STEP << endl;


	_getch();
	return 0;
}

