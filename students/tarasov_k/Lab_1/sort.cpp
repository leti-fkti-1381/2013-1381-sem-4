# include <iostream>
# include <conio.h>
# include <time.h>


using namespace std;
 
int *get (int num, int *arr)
{
	for (int i=0; i<num; i++)
	{arr[i] = rand ()%200-100;}
	return arr;
}
void print (int num,  int arr[])
{
	for(int i=0; i < num; i++)
		cout << arr[i] << ' ';
}

int *insert (int num, int *arr)
{
	int* sort = new int [num];
	for (int i=0; i< num; i++)
	{sort[i]=arr[i];}

	for (int i=1; i< num; i++)
  {
    // ������ j ��������� ���� �� ������ �� A[i] � ��������
    // ������ ���������� ������� ������������ ��������
    int j = i;
    int temp = sort[i];
    // ���������� ���������� ������� ��� �������, �������� ���������,
    // ���� temp < A[j-1] ��� ���� �� ���������� ������ ������
    while (j > 0 && temp < sort[j-1])
    {
      // �������� �������� ������, ����� ���������� ����� ��� �������
      sort[j] = sort[j-1];
      j--;
    }
    // ����� ������� �������; �������� temp
    sort[j] = temp;
	cout << i << "-�� ���" << endl;
	print(num,sort);
	cout<<endl;
  }
	return sort;
}
int *binary_insert(int num, int *arr)
// num - ����� ����������,
// array - ��������� �� ������ �������� �������.
{
	int* sort = new int [num];
	for (int i=0; i< num; i++)
	{sort[i]=arr[i];}
    long i, b, e, c, k;
    float temp;

    i = 1;
    do
    {
        b = 0;
        e = i - 1;
        c= (b + e)/2;

        while (b != c)
        {
            if (sort[c] > sort[i]) e=c; else b=c;
            c = (b + e)/2;
        }

        if (sort[b] < sort[i])
            if (sort[i] > sort[e]) b = e + 1; else b = e;
        k=i;
        temp = sort[i];

        while (k > b)
        {
            sort[k] = sort[k-1];
            k--;
        }

        sort[b] = temp;
        i++;
		cout << i-1 << "-�� ���" << endl;
		print(num,sort);
		cout<<endl;
    } while (i < num);
return sort;
}
int main ()
{
	setlocale (0,"");
	int size,d;
	cout <<"������� ������ ������� \n";
    cin>>size;
	int* mass = new int [size];
	int* res = new int [size];
	
	
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
	        res = get(size,mass);
		   }break;
	   case 2:
		   {
	        cout<<"������� ������ �����.\n";
			for (int i = 0; i < size; i++)
			{
		       cin>>mass[i];
			}
		   }
	 }
	cout <<"�������� ������" << endl;
	print(size,mass);
	int low = mass[0];
	int high = mass[size];
	cout << low << high <<endl;
	cout<<endl;
	clock_t t;
	t = clock ();
	res = insert(size,mass);
	t = clock() - t;
	cout<<"����� ����������� ���������"<<endl;
	cout << (double)t/CLOCKS_PER_SEC << endl;
	cout<<endl;
	cout <<"��������������� ������ �������� ���������" << endl;
	print(size,res);
	cout<<endl;
	cout<<"-------------------------------------------"<< endl;

	clock_t t1;
	t1 = clock ();
	res = binary_insert(size,mass);
	t1 = clock() - t1;
	cout<<"����� ����������� ���������"<<endl;
	cout << (double)t1/CLOCKS_PER_SEC << endl;
	cout<<endl;
	cout <<"��������������� ������ ��������� ���������" << endl;
	print(size,res);
	delete [] mass;
	delete []res;
	getch();
}
