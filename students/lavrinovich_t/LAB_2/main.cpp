#include <iostream>
#include <math.h>

using namespace std;
bool see_all(bool see[], int n)	//������� ����������� ��� �� ���� �������������� � ������������
{		//���� �������������� ��� ���������������� true, ����� false
	for (int i = 0; i < n; i++)
	{
		if (see[i] != true)
			return false;
	}
	return true;
}

int BackTracking(int &CommandA, int &CommandB, int Quant, int PartMass[], bool k, bool see[], int a, int b, int count, int &monte_carlo)
{				//������������� ��� ������ �������, ������ �������, ���������� ������������ �����, ���� ���� �����, �������� ������������ � ����� ������� ����� �������� �����
				//������, ������������ ������������� �� ������� � ������������ ��� ���, ��� ����� �������, ������ �������, ������� ����� ����������� ����� � ��������
	int p = 0;	//�������� ������������ ����� ������� ������������� �� ������ ���� ��������
	++monte_carlo;
	for (int i = 0; i < Quant; i++)	//���� �� ������ ����������������� ���������
	{
		if (see[i] != true)	//���� �������� �� �����������, ��
		{		//������� ��� � ����� �� ������(������������� ���������� k)
			if (k == true)
			{
				count++;
				a += PartMass[i];
			}
			else
			{
				count--;
				b += PartMass[i];
			}
			see[i] = true;	//������� ��, ��� i �������� ������������� 
			p = i;
			break;
		}
	}

	if (see_all(see, Quant))		//���� ������������ ��� ���������
	{
		if ((abs(a-b) < abs(CommandA - CommandB)) && ((count >=-1) && (count <=1)))	
		{	//��������� �� ��, ��� �������� ����� � �������� ������ ������������ � ��, ��� ������� ����� � ������� �� ������ ������ 
			CommandA = a;		//���� �� �� ��������� �������
			CommandB = b;
			if (CommandA - CommandB == 0)		//���� ������� ����� 0, �� ������� ���������� � �������
				return 1;
		}
	}
	else	//���� �� ������������ ��� ���������, �� ��������� ������� ������
	{
		int ret = BackTracking(CommandA, CommandB, Quant, PartMass, true, see, a, b, count, monte_carlo);	//��������� ������� ���������� (��������� � ������ �������)
		see[++p] = false;	//�������� ���������������� � ��������� �������� ������������� ������, � ��� ��� �� �����������
		if (ret == 1)		//���� ������� ����� ������ ������ 0, �� �����
			return 1;
		ret = BackTracking(CommandA, CommandB, Quant, PartMass, false, see, a, b, count, monte_carlo);		//��������� ������� ���������� (��������� �� ������ �������)
		see[p] = false;		//�������� ���������������� � ��������� �������� ������������� ������, � ��� ��� �� �����������
		if (ret == 1)		//���� ������� ����� ������ ������ 0, �� �����
			return 1;
	}
	return 0;
}

int Monte_Carlo(int n)
{
	int quant = 0;
	int k = n;
	while (n)
	{
		int add = 1;
		for (int i = k; i >= n; i--)
		{
			add *=i;
		}
		quant += add;
		--n;
	}
	return quant;
}

int main()
{
	//���� ������
	int TestQuan = 0;
	cin>>TestQuan;	//���������� �������� �����

	int *PartQuan = new int[TestQuan];		//���������� ��������� � �������� ������
	int **PartMass = new int*[TestQuan];	//����� ���������� � �������� ������
	for (int i = 0; i < TestQuan; i++)
	{
		cin>>PartQuan[i];					//���� ���������� ���������� � i ������
		PartMass[i] = new int[PartQuan[i]];
		for (int k = 0; k < PartQuan[i]; k++)	//���� ���� ���������� � i ������
		{
			cin>>PartMass[i][k];
			if ((PartMass[i][k] > 400) || (PartMass[i][k] < 1))	//���� ��� ������ 400 ��� ������ 1, 
			{														//�� ��� ��������� ������
				cout<<"Input weight again\n";
				--k;
			}
		}
	}

	//������� ������
	int *CommandA = new int[TestQuan];		//��� ������ ������� � ������ �������� ������
	int *CommandB = new int[TestQuan];		//��� ������ ������� � ������ �������� ������

	for (int i = 0; i < TestQuan; i++)		//�������� backtracking ������� ���,
	{										//������� � ��� ������� �����
		CommandA[i] = INT_MAX;				//������� ��� ��� �� �������� ����� ���������
		CommandB[i] = 0;					//� ������ ���� ������������
		int count = 0;
		bool *see = new bool[PartQuan[i]];	//���������� ������������� �� ������� � ������������ ��� ���
		for (int k = 0; k < PartQuan[i]; k++)	//������� ����� �� ����� �� ������������� � ������������
		{
			see[k] = false;
		}
		BackTracking(CommandA[i], CommandB[i], PartQuan[i], PartMass[i], true, see, 0, 0, 0, count);	//�������� �������
		cout<<CommandA[i]<<" "<<CommandB[i]<<endl;		//������� ��������� ���� � ����� ������� � �� ������.
		cout<<count<<endl; //��������� ����������. ���������� ����������� �����.
		cout<<Monte_Carlo(PartQuan[i])<<endl;		//����� �����.
	}

	return 0;
}