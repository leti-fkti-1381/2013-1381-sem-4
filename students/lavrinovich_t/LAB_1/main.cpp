#include "ShellSort.h"

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