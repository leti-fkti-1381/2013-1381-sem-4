#include "ShellSort.h"

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