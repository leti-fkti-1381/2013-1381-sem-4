// Lab_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

struct type
{
	int x;
	double y;
	type(){y=0;}
};
int x,N,replay,sortirovka,kol_vo,raz;
type A,B;

template<typename T>
T generate( T a,T b )
{
	if( x == 2 )
		return (T)rand()/(T)RAND_MAX*(b - a) + a;
	else	
		return rand()%(int)(b-a+1)+a;
}

void print( type ARR[] )
{
	char q;
	ofstream out( "out.txt" );
		for( int i = 0; i < N; i++ )
		{
			if( x == 1 )
			{
				out << ARR[i].x << " ";
			}
			else if( x == 2 )
			{
				out << ARR[i].y << " ";
			}
			else 
			{
				q = (char)ARR[i].x;
				out << q << " ";
			}
		}	
}
void sort( type ARR[])
	{

	{ 
		for( int pass = 0; pass < N-1; pass++ )
		{
			for(int i=0; i<N-1;i++)
			{
				if( x == 2 )
				{
					if ( sortirovka==1 && ARR[i].y > ARR[i+1].y||sortirovka==2 && ARR[i].y < ARR[i+1].y  )
					{   
						double reserve = ARR[i].y;
						ARR[i].y = ARR[i+1].y;
						ARR[i+1].y=reserve;
					}
				}
				else
				{
					if( ( sortirovka==1 && ARR[i].x > ARR[i+1].x ) || ( sortirovka==2 && ARR[i].x < ARR[i+1].x ) )					
					{   
						int reserve= ARR[i].x;
						ARR[i].x=ARR[i+1].x;
						ARR[i+1].x=reserve;
					}
				}
			}	
		}
		print( ARR );
		
	}
	}

void copy (type ARR[])
	{
	{
		int i=0;
		type *ARR_2 = new type[N];
		if(x==2)
		{
			for (int pass=0;pass<N;pass++)
			{
				ARR_2[pass].y = ARR[i].y;
				i++;
				if(i == (N/kol_vo))
					i=0;
			}
		}
		else 
		{
			for (int pass=0;pass<N;pass++)
			{
				ARR_2[pass].x=ARR[i].x;
				i++;
				if(i==N/kol_vo)
					i=0;
			}
		}
		print( ARR_2 );
		
	}
	}
void mix( type ARR[])
	{
	{
		type *ARR_2=new type[N];
		if(x==2)
		{
	      int i=0;
		  x = 1;
	      int k=generate( 0,kol_vo-1 );
		
           for (int pass=0;pass<N;pass++)
	       {
			   ARR_2[pass].y=ARR[i+k*N/kol_vo].y;
	           i++; 
              if(i==N/kol_vo)
		      {
			   i=0;
               k=generate( 0,kol_vo-1 );
		      }
	       }
		   x = 2;
	    }
		else
		{
			int i = 0;
			int k=generate( 0,kol_vo-1 );
		
            for (int pass=0;pass<N;pass++)
	        {
			    ARR_2[pass].x=ARR[i+k*N/kol_vo].x;
	            i++; 
                if(i==N/kol_vo)
		        {
					i=0;
					k=generate( 0,kol_vo-1 );
				}
	        }
		}
		print( ARR_2 );
		
	}
	}

int main()
{
	SetConsoleOutputCP(1251);
	A.x = 65;
	B.x = 90;
	
	cout << "Тип элементов:\n 1 - int\n 2 - double\n 3 - char\n";
	cin >> x;
	if( x < 1 || x > 3 )
	{
		cout << "Указано неверное значение типа элемента.";
		_getch();
		return 0;
	}
	cout << "Количество элементов: ";
	cin >> N;
	if( N < 1 )
	{
		cout << "Количеcтво элементов не может быть отрицательным!Попробуйте еще раз.";
		_getch();
		return 0;
	}
	if( x != 3 )
	{
		cout << "Промежуток (a,b): ";
		if( x == 2 )
		{
			cin >> A.y >> B.y;
		}
		else
		{
			cin >> A.x >> B.x;
		}
		if( B.x < A.x || B.y < A.y )
		{
			cout << "Правая граница не может быть меньше левой!Попробуйте еще раз.";
			_getch();
			return 0;
		}
	}
	cout << "Разрешить повтрения( 1 - да, 2 - нет): ";
	cin >> replay;
	if( replay < 1 || replay > 2 )
	{
		cout << "Указано неверное значение.";
		_getch();
		return 0;
	}
	if( B.x - A.x < N && replay == 2)
	{
		cout << "Некорректные параметры!";
		_getch();
		return 0;
	}
	cout << "Сортировать:\n 1 - по возрастанию\n 2 - по убыванию\n 3 - участками\n 4 - смешенными участками\n 5 - не сортировать\n";
	cin >> sortirovka;
	if( sortirovka < 1 || sortirovka > 5 )
	{
		cout << "Указано неверное значение сортировки.";
		_getch();
		return 0;
	}
	if( sortirovka == 3 ||  sortirovka == 4 )
	{
		cout << "Количество участков: ";
		cin >> kol_vo;
		if( kol_vo > N )
		{
			cout << "Недопустимый параметр.";
			_getch();
			return 0;
		}
	}
	
	type*ARR = new type[N];
	int a,j;
	double b;

	for( int i = 0; i < N; i++ )
	{
		if( x == 2 )
		{
			b = generate( A.y,B.y );
			if( replay == 2 )
				while( true )
				{
					for( j = 0; j < i; j++ )
						if( ARR[j].y == b )
							break;
					if( j == i ) 
						break;					
					b = generate( A.y,B.y );
				}
			ARR[i].y  = b;
		}
		else
		{
			a = generate( A.x,B.x );
			if( replay == 2 )
				while( true )
				{
					for( j = 0; j < i; j++ )
						if( ARR[j].x == a )
							break;
					if( j == i ) 
						break;
					a = generate( A.x,B.x );
				}
			ARR[i].x = a;
			
		}
	}

	if( sortirovka == 5 )
	{
		print( ARR );
		_getch();
		return 0;
	}

	if ( sortirovka == 1 || sortirovka == 2 )
	{
		sort(ARR);
	    return 0;
	}
	
	// повторение элементов
	if(  sortirovka==3 )
	{
		copy( ARR);
		return 0;
	}
//смесь
	if( sortirovka==4){
		mix (ARR);
	    return 0;
	}

	_getch();
	return 0;
}
