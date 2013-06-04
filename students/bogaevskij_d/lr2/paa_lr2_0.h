#ifndef _paa_lr2_0
#define _paa_lr2_0
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class Mark
{
public:
	int number; //�����������(�����) �����
	int cost;   //���� �����
	void Init(int k);	
};

void Mark::Init(int k)
{
	number=k;
	cout << "\n������� ���� ��� ����� � ������� " << number << "     ";
	cin >> cost;
}

void Solve1(Mark **a, Mark *res, Mark *base, int n, int m, int num, int stat); //���������� ������� ��� ���������� � ������� ��� ��� ����
void CostSort(Mark **a, int m, int p);	//���������� ����� �� ����, p - ���-�� ���������
int Posl1(Mark **a, int m, int p);  //������� ������������������ � ����������������� �������
int Posl(Mark **a, int m, int p);   //������� ������������������ � ��������������� �������
void MarkSort(Mark **a, int m, int p); //��������� ����� �� ������� � ������
bool MasCmp(Mark *a, Mark *b, int m);	//���������� ������ m ��������� ������� � � b(���� ��� ����� �� 1, ����� 0)
Mark **ChoseAns(Mark **, int m, int n);	//�������� ��������������� ����������
int C(int N, int k);  //N~n, k~m  ������� �(k,N+k-1)
int Monte_Carlo(int *res, int n, int m, int cur); //������ ��������� ������� �����-�����

void Solve1(Mark **a, Mark *res, Mark *base, int n, int m, int num, int *stat)
{
	if(n<m) //���� ����� �� �������� ������ ����������� ���-��
	{
		
		for(int i=0;i<num;i++)  //���������� ��������� ������������ ����������
		{
			res[n]=base[i];		 //���������� � �������������� ������ ������� �����
			Solve1(a,res,base,n+1,m,num,stat); 
		}
	}
	else	//���� ��������� ������ �����
	{
		//static int stat=0;		//����������� ���������� ��� ������ ��������� � ��������� ������
		int sum=0;				
		for(int i=0;i<m;i++)
		{
			a[stat[0]][i]=res[i];	//��������� ���������
			sum+=res[i].cost;	//������� ����� ����
		}
		a[stat[0]][m].cost=sum;  //���������� ����� ���� � m �������
		stat[0]++;
	}
}

void CostSort(Mark **a, int m, int p)
{
	for(int i=0;i<p-1;i++)  //��������� m �������, � ������� �������� ����� ����
	{
		for(int j=i+1;j<p;j++)	
		{
			if(a[i][m].cost>a[j][m].cost)
			{
				Mark *b=a[i];
				a[i]=a[j];
				a[j]=b;
			}
		}
	}
}

int Posl1(Mark **a, int m, int p)
{
	int i=0, next=1;
	while(i<p)
	{
		if(a[i][m].cost==next)
		{
			i=0;
			next++;
		}
		i++;
	}
	next--;
	return next;
}


int Posl(Mark **a, int m, int p) 
{
	int min, max,s;
	min=a[0][m].cost; //����������� ����(�� ��������� 0(������ ���������� �����))
	max=min;
	s=min;
	for(int i=1;i<p;i++)
		if(a[i-1][m].cost<a[i][m].cost)  //���� ������� ������� ������ �����������
		{
			s++;				// - ��������� �� ����� �����
			max=a[i][m].cost;	// - ���� �������� ��������
			if(max!=s)			//���� �� �����, �� ������� ������������������
			{
				max=s-1;
				cout << "\n���������: �� " << min << " �� " << max << endl;
				return max;
			}
		}
}

void MarkSort(Mark **a, int m, int p)
{
	for(int k=0;k<p;k++)	//��� ������ ������
		for(int i=0;i<m-1;i++)	//��������� ������� ������
			for(int j=i+1;j<m;j++)
				if(a[k][i].number>a[k][j].number)
				{
					Mark b=a[k][i];
					a[k][i]=a[k][j];
					a[k][j]=b;
				}
}

bool MasCmp(Mark *a, Mark *b, int m)
{
	for(int i=0;i<m;i++)
	{
		if(a[i].number!=b[i].number) return false; //���� ������� �������� �������� ���������� 0
	}
	return true;
}

int C(int N, int k) //N~n, k~m    �(k,N+k-1)=(N+k-1)!/(k!*(N-1)!) - ���������� ���������� ����� ����������� ����������
{
	int ch=1;
	int zn1=1;
	int zn2=1;
	for(int i=1; i<N+k;i++)
		ch*=i;
	for(int i=1; i<k+1;i++)
		zn1*=i;
	for(int i=1; i<N;i++)
		zn1*=i;
	int res=ch/(zn1*zn2);
	return res;
}

Mark **ChoseAns(Mark **a, int m, int n) 
{
	Mark **res;
	int p=pow((double)n,m);  //���-�� ���� ����������
	res=new Mark* [C(n,m)];		//���-�� ������ ����������
	*res=new Mark [m];
	res[0]=a[0];		//���������� ��������� ����������
	int q=1;
	for(int i=1;i<p;i++)  //��� ������ ����������
	{
		bool p=0;
		for(int j=0;j<q;j++)  //��������� ���� �� ��� � ������������� ������� ����������
		{
			if(MasCmp(a[i],res[j],m)) p=1;  
		}
		if(p==0)		//���� ���� ���������� ��
		{
			res[q]=a[i];
			q++;
		}
	}
	return res;
}

int Monte_Carlo(int *res,int n, int m, int cur)
{
	int pr=n;
	if(cur<m) //���� ���������� �� ������ �� ��������� �����
	{
		for(int j=0;j<cur;j++)
				pr*=n;
		pr*=n;    //�.�. � ������ ������ ��� ����� ����������, �� �������� �� �� ���-��
		res[0]+=pr; //������� �����
		Monte_Carlo(&res[0],n,m,cur+1);
	}
	return res[0]/pow((double)n,m-1);
}

#endif