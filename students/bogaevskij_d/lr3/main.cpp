#include <iostream>
#include <math.h>

using namespace std;

#define debug

void add(char *s, int n, int c);/*�������� ������ "�" � "n" ������� � ������ "s"    61h=97=a    7Ah=122=z*/
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
	cout << "������� ������ A" << endl;
	cin >> A;
	cout << "������� ������ B" << endl;
	cin >> B;
	strcpy(alph,AnalyseB(B)); //��� ����� ������� ������ ���������� ���������������� ������ B �� ��, ����� ������� � ��� ������
	int m=strlen(B)-strlen(A); 
	m=abs(m);
	m+=strlen(B);		//���������� ����� ��������
	Solve(A,B,alph,0,&m);	
	cout << endl << m;
#ifdef debug
	cout << endl << endl << "�������: \n";
	for(int i=0;i<=m;i++)
		cout << DEB2[i] << endl;
#endif


	system("pause");
	return 1;
}

void Solve(char *A, char *B, char *alph,int n, int *m)
{
	//"n" - ������� ���-�� ��������
	//"m" - ����������� ���-�� ��������
	//1) ������� ����� �������� ���-�� �������� � �������
	//2) ����� ����� �������� ������������
	if(n>=m[0]) return;   //���� ������� �������� ��������� ��������� �������
	if(strlen(A)<strlen(B)) //���� ����� � ������ ����� �, �� ���� ��������� �������.
	{
		char A2[50];
		for(int i=0;i<strlen(A);i++) //��������� � ������ ����� ������
		{
			for(int j=0;j<strlen(alph);j++) //����������� ��� ������� �� ��������
			{
#ifdef debug
				strcpy(DEB[n],A);
#endif
				strcpy(A2,A);
				add(A2,i,alph[j]);	//��������� j-�� ������ � i-� �����
				Solve(A2,B,alph,n+1,m);	//������ ����� ������
			}
		}
	}
	if(strlen(A)>strlen(B)) //������� �����
	{
		char A2[50];
		for(int i=0;i<strlen(A);i++)  //������� ������ ����� �� �
		{
#ifdef debug
			strcpy(DEB[n],A);
#endif
			strcpy(A2,A);	//�������� ������
			del(A2,i);		//������� �����
			Solve(A2,B,alph,n+1,m); //������ ����� ������
		}
	}
	if(strlen(A)==strlen(B))
	{
		//�������� ������������� �����
		for(int i=0;i<strlen(A);i++)
		{
			if(A[i]!=B[i])
			{
#ifdef debug
				strcpy(DEB[n],A);
				A[i]=B[i];
#endif
				n++; //����������� ���-�� ��������
			}
		}
		if(n<m[0]) //���� ����� ���������� ������� ������ ����� ������������
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

char *AnalyseB(char *A)  //����������� ������ �� ������������ � ��� ������� � ���������� �������
{
	char res[34];
	res[0]='\0';
	int i=0,j=0;
	while(A[i]!='\0') //���� �� ����� ������
	{
		if(!inMass(res,A[i]))//���� ������ �� ���������� � �������, �� ���������
		{
			res[j]=A[i];
			j++;
		}
		i++;
	}
	res[j]='\0';
	return res;
}

bool inMass(char *MASS, char c) //���������� �� ������ � � ������ MASS
{
	int i=0;
	while(MASS[i]!='\0') //���� �� ����� ������
	{
		if(MASS[i]==c) return true; //���� ������ ������
		i++;
	}
	return false;
}


void add(char *s, int n, int c) //��������� ������ � � ������ s �� n �����
{
	if(n>strlen(s)) return; //���� ������ ��������
	int i;
	for(i=strlen(s)+1;i>n;i--) //����� ��������
	{
		s[i]=s[i-1];
	}
	s[i]=c; //��������� ������
}

void del(char *s, int n) //������� ������ �� ������ s � n �����
{
	if(n>strlen(s)) return; //���� ������ �������
	for(int i=n;i<strlen(s)+1;i++) //�������� ��� �� 1 c n ��������.
	{
		s[i]=s[i+1];
	}
}

void change(char *s,int n, int c) //�������� n-�� ������ �� c � ������ s
{
	if(n>strlen(s)) return;
	s[n]=c;
}