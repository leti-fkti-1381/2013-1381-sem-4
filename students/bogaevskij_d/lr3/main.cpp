#include <iostream>
#include <math.h>

using namespace std;

#define debug

void add(char *s, int n, int c);/*Добавить символ "с" с "n" позиции в строку "s"    61h=97=a    7Ah=122=z*/
void del(char *s, int n);
void change(char *s,int n, int c);
void Solve(char *A, char *B, char *alph, int n, int *m);
char *AnalyseB(char *B);
bool inMass(char *MASS, char c);

char DEB[100][100];
char DEB2[100][100];



int main()
{
	setlocale(0,"Rus");
	char A[50],B[50],alph[34];
	cout << "Введите строку A" << endl;
	cin >> A;
	cout << "Введите строку B" << endl;
	cin >> B;
	strcpy(alph,AnalyseB(B)); //Для более быстрой работы необходимо проанализировать строку B на то, какие символы в нее входят
	int m=strlen(B)-strlen(A); 
	m=abs(m);
	m+=strlen(B);		//наибольший порог операций
	Solve(A,B,alph,0,&m);	
	cout << endl << m;
#ifdef debug
	cout << endl << endl << "Решение: \n";
	for(int i=0;i<=m;i++)
		cout << DEB2[i] << endl;
#endif


	system("pause");
	return 1;
}

void Solve(char *A, char *B, char *alph,int n, int *m)
{
	//"n" - текущее кол-во операций
	//"m" - минимальное кол-во операций
	//1) Сначала нужно уровнять кол-во символов в строках
	//2) Потом нужно заменить несходящиеся
	if(n>=m[0]) return;   //если текущие операции превышают найденное решение
	if(strlen(A)<strlen(B)) //если длина А меньше длины В, то надо добавлять символы.
	{
		char A2[50];
		for(int i=0;i<strlen(A);i++) //добавляем в каждое место символ
		{
			for(int j=0;j<strlen(alph);j++) //подставляем все символы из алфавита
			{
#ifdef debug
				strcpy(DEB[n],A);
#endif
				strcpy(A2,A);
				add(A2,i,alph[j]);	//добавляем j-ий символ в i-е место
				Solve(A2,B,alph,n+1,m);	//решаем новую задачу
			}
		}
	}
	if(strlen(A)>strlen(B)) //удаляем буквы
	{
		char A2[50];
		for(int i=0;i<strlen(A);i++)  //удаляем каждую букву из А
		{
#ifdef debug
			strcpy(DEB[n],A);
#endif
			strcpy(A2,A);	//копируем строку
			del(A2,i);		//удаляем букву
			Solve(A2,B,alph,n+1,m); //решаем новую задачу
		}
	}
	if(strlen(A)==strlen(B))
	{
		//заменяем несовпадающие буквы
		for(int i=0;i<strlen(A);i++)
		{
			if(A[i]!=B[i])
			{
#ifdef debug
				strcpy(DEB[n],A);
				A[i]=B[i];
#endif
				n++; //увеличиваем кол-во операций
			}
		}
		if(n<m[0]) //если длина найденного решения меньше длины оптимального
		{
#ifdef debug
			for(int i=0;i<n;i++)
				strcpy(DEB2[i],DEB[i]);
#endif
			m[0]=n;
#ifdef debug
			strcpy(DEB2[n],B);
#endif
		}
	}
}

char *AnalyseB(char *A)  //анализируем строку на используемые в ней символы и составляет алфавит
{
	char res[34];
	res[0]='\0';
	int i=0,j=0;
	while(A[i]!='\0') //пока не конец строки
	{
		if(!inMass(res,A[i]))//если символ не содержится в массиве, то добавляем
		{
			res[j]=A[i];
			j++;
		}
		i++;
	}
	res[j]='\0';
	return res;
}

bool inMass(char *MASS, char c) //содержится ли символ с в строке MASS
{
	int i=0;
	while(MASS[i]!='\0') //пока не конец строки
	{
		if(MASS[i]==c) return true; //если найден символ
		i++;
	}
	return false;
}


void add(char *s, int n, int c) //добавляем символ с в массив s на n место
{
	if(n>strlen(s)) return; //если некуда добавить
	int i;
	for(i=strlen(s)+1;i>n;i--) //сдвиг символов
	{
		s[i]=s[i-1];
	}
	s[i]=c; //добавляем символ
}

void del(char *s, int n) //удаляем символ из строки s с n места
{
	if(n>strlen(s)) return; //если нечего удалять
	for(int i=n;i<strlen(s)+1;i++) //сдвигаем все на 1 c n поздиции.
	{
		s[i]=s[i+1];
	}
}

void change(char *s,int n, int c) //заменяем n-ый символ на c в строке s
{
	if(n>strlen(s)) return;
	s[n]=c;
}