#include <iostream>
#include <time.h>

using namespace std;

//�������� ��������� ������������������
int SedgewickAlg(int size, int *d)
// d ������, � ������� ��������� ����������
// size ����������� ����� �������
{
  int p1, p2, p3, i;

  p1 = p2 = p3 = 1;
  i = -1;
  do {// ��������� ������ ��������� �� ������� ������� ��������
    if (++i % 2)
      d[i] = 8*p1 - 6*p2 + 1;
	else
	{
      d[i] = 9*p1 - 9*p3 + 1;
      p2 *= 2;
      p3 *= 2;
	}
	p1 *= 2;
	// ��������� ������, ���� ������� ���������� ���� ��
	// � 3 ���� ������ ���������� ��������� � �������
  } while(3*d[i] < size);  

  // ���������� ���������� ��������� � �������
  return (i > 0) ? (--i) : (0);
  
}

template<class AnyClass>					//������ ��� ������������� ������ ���� ������ � �������
double shellSort(AnyClass *a, int size, int &k) {	//���������� ����� ����������
	clock_t time = clock();
// inc ���������, ���������� ����� ���������� ���������
// i � j ����������� ���������� �����
// d[40] ������, � ������� �������� ����������
	int inc = 0, d[40];
	int i = 0, j = 0;
	int s = 0;//���������� ��������� � ������� d[40]

	// ���������� ������������������ ����������
	s = SedgewickAlg(size, d);
	while (s >= 0) 
	{
		//��������� �� ������� ��������� ����������
		inc = d[s--];
		
		// ���������� ��������� � ������������ inc
		for (i = inc; i < size; i++) 
		{
			AnyClass temp = a[i];
			// �������� �������� �� ��� ���, ���� �� ������
			// �� ����� ��� �� ���������� � ������ �������
			for (j = i-inc; (j >= 0) && (a[j] > temp); j -= inc)
			{
				a[j+inc] = a[j];
				++k;
			}
		// ����� ���� ������� ������ �� ����� j+inc �������, 
		// ������� ��������� �� i �����
			a[j+inc] = temp;
		}
	}
	return (double(clock() - time));
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int n = 0, d;
	int k = 0;//���������� ������� �������� (��������� � �����������)
	cout<<"������� ������ �������.\n";
	cin>>n;

	int *a = new int[n];
	int *b = new int[n];
	srand((signed int)time(0));
    cout<<"\n----------����-----------\n";
    cout<<" 1)��������� ���������� �������\n";
    cout<<" 2)���� ������� �������������";
    do
       {
          cout<<"\n ������� d (1 ��� 2)\n";
          cin>>d;
          if(d<1||d>2)
              cout<<"\n ������! ��������� �������! \n";
        }
     while(d<1||d>2);
     switch(d)
	 {
	   case 1:
		   {
	        for (int i = 0; i < n; i++)
			{
				a[i] = rand()%10000000; // ��������� ����� � ��������� �� 0 �� 10000000
				cout<<a[i]<<" ";
				b[i] = a[i];
			}
		   }break;
	   case 2:
		   {
	        cout<<"������� ������ �����.\n";
			for (int i = 0; i < n; i++)
			{
		       cin>>a[i];
			   b[i] = a[i];
			}
		   }
	 }
	
	cout<<"\n����� ����������:"<<shellSort(a, n, k)<<endl;
	cout<<"���������� ������� ��������:"<<k<<endl;
    cout<<"��������������� ������:"<<endl;
	for (int i = 0; i < n; i++)
		cout<<a[i]<<" ";

	clock_t time = clock();
	qsort(b, n, sizeof(int), compare);
	cout<<endl<<"����� ���������� �������� qsort: "<<double(clock() - time)<<endl;
	cout<<"��������������� ������ qsort:"<<endl;
	for (int i = 0; i < n; i++)
		cout<<b[i]<<" ";
	cout<<endl;
	system("pause");
	return 0;
}