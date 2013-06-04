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
    // индекс j пробегает вниз по списку от A[i] в процессе
    // поиска правильной позиции вставляемого значения
    int j = i;
    int temp = sort[i];
    // обнаружить подходящую позицию для вставки, сканируя подсписок,
    // пока temp < A[j-1] или пока не встретится начало списка
    while (j > 0 && temp < sort[j-1])
    {
      // сдвинуть элементы вправо, чтобы освободить место для вставки
      sort[j] = sort[j-1];
      j--;
    }
    // точка вставки найдена; вставить temp
    sort[j] = temp;
	cout << i << "-ый шаг" << endl;
	print(num,sort);
	cout<<endl;
  }
	return sort;
}
int *binary_insert(int num, int *arr)
// num - число эллементов,
// array - указатель на первый эллемент массива.
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
		cout << i-1 << "-ый шаг" << endl;
		print(num,sort);
		cout<<endl;
    } while (i < num);
return sort;
}
int main ()
{
	setlocale (0,"");
	int size,d;
	cout <<"Введите размер массива \n";
    cin>>size;
	int* mass = new int [size];
	int* res = new int [size];
	
	
	cout<<"\n----------Меню-----------\n";
    cout<<" 1)Генерация случайного массива\n";
    cout<<" 2)Ввод массива пользователем";
    do
       {
          cout<<"\n Введите d (1 или 2)\n";
          cin>>d;
          if(d<1||d>2)
              cout<<"\n Ошибка! Повторите попытку! \n";
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
	        cout<<"Введите массив чисел.\n";
			for (int i = 0; i < size; i++)
			{
		       cin>>mass[i];
			}
		   }
	 }
	cout <<"Исходный массив" << endl;
	print(size,mass);
	int low = mass[0];
	int high = mass[size];
	cout << low << high <<endl;
	cout<<endl;
	clock_t t;
	t = clock ();
	res = insert(size,mass);
	t = clock() - t;
	cout<<"Время выполянения программы"<<endl;
	cout << (double)t/CLOCKS_PER_SEC << endl;
	cout<<endl;
	cout <<"Отсортированный массив обычными вставками" << endl;
	print(size,res);
	cout<<endl;
	cout<<"-------------------------------------------"<< endl;

	clock_t t1;
	t1 = clock ();
	res = binary_insert(size,mass);
	t1 = clock() - t1;
	cout<<"Время выполянения программы"<<endl;
	cout << (double)t1/CLOCKS_PER_SEC << endl;
	cout<<endl;
	cout <<"Отсортированный массив двоичными вставками" << endl;
	print(size,res);
	delete [] mass;
	delete []res;
	getch();
}
