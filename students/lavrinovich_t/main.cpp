#include <iostream>
#include <time.h>

using namespace std;

//Алгоритм получения последовательности
int SedgewickAlg(int size, int *d)
// d массив, в который заносятся инкременты
// size размерность этого массива
{
  int p1, p2, p3, i;

  p1 = p2 = p3 = 1;
  i = -1;
  do {// заполняем массив элементов по формуле Роберта Седжвика
    if (++i % 2)
      d[i] = 8*p1 - 6*p2 + 1;
	else
	{
      d[i] = 9*p1 - 9*p3 + 1;
      p2 *= 2;
      p3 *= 2;
	}
	p1 *= 2;
	// заполняем массив, пока текущая инкремента хотя бы
	// в 3 раза меньше количества элементов в массиве
  } while(3*d[i] < size);  

  // возвращаем количество элементов в массиве
  return (i > 0) ? (--i) : (0);
  
}

template<class AnyClass>					//Шаблон для использования любого типа данных в массиве
double shellSort(AnyClass *a, int size, int &k) {	//Возвращает время выполнения
	clock_t time = clock();
// inc инкремент, расстояние между элементами сравнения
// i и j стандартные переменные цикла
// d[40] массив, в котором хранятся инкременты
	int inc = 0, d[40];
	int i = 0, j = 0;
	int s = 0;//количество элементов в массиве d[40]

	// вычисление последовательности приращений
	s = SedgewickAlg(size, d);
	while (s >= 0) 
	{
		//извлекаем из массива очередную инкременту
		inc = d[s--];
		
		// сортировка вставками с инкрементами inc
		for (i = inc; i < size; i++) 
		{
			AnyClass temp = a[i];
			// сдвигаем элементы до тех пор, пока не дойдем
			// до конца или не упорядочим в нужном порядке
			for (j = i-inc; (j >= 0) && (a[j] > temp); j -= inc)
			{
				a[j+inc] = a[j];
				++k;
			}
		// после всех сдвигов ставим на место j+inc элемент, 
		// который находился на i месте
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
	int k = 0;//Количество базовых опереций (сравнение и перемещение)
	cout<<"Введите размер массива.\n";
	cin>>n;

	int *a = new int[n];
	int *b = new int[n];
	srand((signed int)time(0));
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
	        for (int i = 0; i < n; i++)
			{
				a[i] = rand()%10000000; // Генерация чисел в диапазоне от 0 до 10000000
				cout<<a[i]<<" ";
				b[i] = a[i];
			}
		   }break;
	   case 2:
		   {
	        cout<<"Введите массив чисел.\n";
			for (int i = 0; i < n; i++)
			{
		       cin>>a[i];
			   b[i] = a[i];
			}
		   }
	 }
	
	cout<<"\nВремя выполнения:"<<shellSort(a, n, k)<<endl;
	cout<<"Количество базовых операций:"<<k<<endl;
    cout<<"отсортированный массив:"<<endl;
	for (int i = 0; i < n; i++)
		cout<<a[i]<<" ";

	clock_t time = clock();
	qsort(b, n, sizeof(int), compare);
	cout<<endl<<"Время сортировки функцией qsort: "<<double(clock() - time)<<endl;
	cout<<"отсортированный массив qsort:"<<endl;
	for (int i = 0; i < n; i++)
		cout<<b[i]<<" ";
	cout<<endl;
	system("pause");
	return 0;
}