#include "stdafx.h"
#include <iostream>
#include "stdlib.h"
#include <fstream>

using namespace std;

// ����� � ���������
bool see_all(bool see[], int n)	//������� ����������� ��� �� ���� �������������� � ������������
{		//���� �������������� ��� ���������������� true, ����� false
	for (int i = 0; i < n; i++)
	{
		if (see[i] != true)
			return false;
	}
	return true;
}
//backtrack
int backtrack(int &comA, int &comB, int chislo, int massiv[], bool k, bool see[], int a, int b, int count)
{		
	int p = 0;	//�������� ������������ ����� ������� ������������� �� ������ ���� ��������
	for (int i = 0; i < chislo; i++)	//���� �� ������ ����������������� ���������
	{
		if (see[i] != true)	//���� �������� �� �����������, ��
		{		//������� ��� � ����� �� ������(������������� ���������� k)
			if (k == true)
			{
				count++;
				a += massiv[i];
			}
			else
			{
				count--;
				b += massiv[i];
			}
			see[i] = true;	//������� ��, ��� i �������� ������������� 
			p = i;
			break;
		}
	}

	if (see_all(see,chislo))		//���� ������������ ��� ���������
	{
		if ((abs(a-b) < abs(comA - comB)) && ((count >=-1) && (count <=1)))	
		{	                 //��������� �� ��, ��� �������� ����� � �������� ������ ������������ � ��, ��� ������� ����� � ������� �� ������ ������ 
			comA = a;		 //���� �� �� ��������� �������
			comB = b;
			if (comA - comB == 0)		//���� ������� ����� 0, �� ������� ���������� � �������
				return 1;
		}
	}
	else	//���� �� ������������ ��� ���������, �� ��������� ������� ������
	{
		int ret = backtrack(comA, comB, chislo, massiv, true, see, a, b, count);	//��������� ������� ���������� (��������� � ������ �������)
		see[++p] = false;	//�������� ���������������� � ��������� �������� ������������� ������, � ��� ��� �� �����������
		if (ret == 1)		//���� ������� ����� ������ ������ 0, �� �����
			return 1;
		ret = backtrack(comA, comB, chislo, massiv, false, see, a, b, count);		//��������� ������� ���������� (��������� �� ������ �������)
		see[p] = false;		//�������� ���������������� � ��������� �������� ������������� ������, � ��� ��� �� ������������
		if (ret == 1)		//���� ������� ����� ������ ������ 0, �� �����
			return 1;
	}
	return 0;
}
// ���������� �����
void postroenie_bloka(int **massiv,int blok,int *A)
{
int i,j;
cout<<"������� ���� ���������� � ������ �����.\n"<<endl;
 for(i = 0; i < blok; i++)
  {
   cout<<"���� ����� "<<i+1<<" -��� �����\n"<<endl;
    for(j = 0; j < A[i]; j ++)
      {
        cout<<"��� "<<j+1<<"- ��� ���������:";
        cin>>massiv[i][j];
		do
		{
		if(massiv[i][j] > 450 || massiv[i][j] <= 0)
		  {
		   cout<<"������� ��� ��������� �� 1 �� 450!"<<endl;
		   cout<<"����:";
		   cin>>massiv[i][j];
		  }
		}while(massiv[i][j] > 450 || massiv[i][j] <= 0);
		cout<<"\n";
       }
    }
}
// ����� �� ����� ���-�� ��������� ������ � ����� ����������
void bloks_and_weight(int **massiv,int blok,int *A)
{
int i,j;
for(i = 0; i < blok; i++)
  {
   cout<<"\n���� "<<i+1<<"-��� �����.\n"<<endl;
   for(j = 0; j < A[i]; j ++)
    {
     cout<<"��� "<<j+1<<"-��� ��������� �������:";
     cout<<massiv[i][j];
     cout<<"\n";
    }
  }
}
void MENU()
{
cout<<"              ��������� ������ ��������� ������ 1381 �������� ����\n"
		"+++++++++++++++++++++++++++++ Backtracking +++++++++++++++++++++++++++++++++\n\n\n"
		"1. ���� ������.\n"
		"2. ����� ����� ������� �����.\n"
		"3. Backtracking.\n"
		"0. �����.\n"<<endl;
}
int main()
{
setlocale(0,"Russian");
char str[256];
int blok = 0,i;
int **massiv,*A=NULL;
int menu = 0;
int *comA = NULL;		
int *comB = NULL;
do
   {
     system("cls");
     MENU();
     cout<<"����: ";
     cin >> menu;
     switch(menu)
                {
                 case 1:
                         cout<<"������� ���������� �������(����� ������������� �����): ";
                         cin >> str;
                         blok = atoi(str);
                         do
						 {
                          if(blok < 0)
                            {
                              cout<<"������� ���������� ����� ������!\n"<<endl;
							  cout<<"������� ���������� �������� �������(����� ������������� �����): ";
							  cin >> str;
							  blok = atoi(str);
							}
						 }while(blok < 0);
						  cout<<"���������� �������� ������ ����� "<<blok<<endl;
						  A = new int[blok];
						  massiv = new int*[blok];
					      for (i = 0; i < blok; i++)
							{
							cout<<"\n������� ���������� ���������� ��� "<<i+1<<"-��� �����\n"<<endl;
							cin>>A[i];
							massiv[i] = new int[A[i]];
								do
								{
								  if(A[i] > 100 || A[i] <= 0 || A[i] == 1)
								   {
									cout<<"\n������� ���������� �� 2 �� 100 ���������� ��� "<<i+1<<"-��� �����!"<<endl;
									cout<<"����: ";
									cin>>A[i];
								   }
								}while(A[i] > 100 || A[i] <= 0 || A[i]== 1);
                             }
							cout<<"\n";
							cout<<"���������� ���������� � ������ �����.\n"<<endl;
							for(i = 0; i < blok; i++)
							{
							    cout<<"���� �"<<i+1<<endl;
							    cout<<A[i]<<endl;
							}
							cout<<"\n";
							postroenie_bloka(massiv,blok,A);
							system("pause");
							break;
				 case 2:
							system("cls");
							bloks_and_weight(massiv,blok,A);
							system("pause");
							break;
				 case 3:
				            system("cls");
							//������� ������
							    comA = new int[blok];
							    comB = new int[blok];		

							   for (int i = 0; i < blok; i++)		
								{										
									comA[i] = INT_MAX;				//������� ��� ��� �� �������� ����� ���������
									comB[i] = 0;					//� ������ ���� ������������
									int count = 0;
									bool *see = new bool[A[i]];	
									for (int k = 0; k < A[i]; k++)	
									{
										see[k] = false;
									}
									backtrack(comA[i], comB[i], A[i], massiv[i], true, see, 0, 0, 0);	
									cout<<"����� ���������� ����� �"<<i+1<<endl;
									cout<<comA[i]<<" "<<comB[i]<<endl;		
									cout<<"\n";
								}
							system("pause");
							break;
				 case 0:
				            break;
				 default:
			          	cout<<"������� ����������� ����� ����!\n"<<endl;
				        system("pause");
               };
  }while(menu != 0);
  system("pause");
return 0;
}


