#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int bubbleSort(unsigned int *arr,unsigned int size)
{ 
	int t=0; //количество шагов
	int buffer; //переменная отвечающая за замену между соседними элементами
    for(unsigned int i = 0; i < size-1; i++) // i - номер прохода
    {            
        for(unsigned int j = 0; j < size-1; j++) // внутренний цикл прохода
        {     
            if (arr[j + 1] < arr[j]) 
            {
                buffer = arr[j + 1]; 
                arr[j + 1] = arr[j]; 
                arr[j] = buffer;
				t++;
				for (unsigned int k=0; k < size; k++){
					cout << arr[k] << " ";
				}
				cout << t << endl;
            }
        }
    }
	return t;
}

int main(){
	setlocale (0, "Rus");
	unsigned int size; //размер данной последовательности 
	unsigned int *sequence; //данная последовательность 
	int t; //количество шагов
	srand(time(0));

	int v1, v2=1;

	cout << "Ввод размера массива\n";
	cout << "1. Ввести в ручную\n";
	cout << "2. Ввести случайным образом\n";
	cout << "Ввыбор: ";
	cin >> v1;
	switch ( v1 )
    {
		case 1:
			cout << "Размер массива = ";
			cin >> size;
			sequence = new unsigned int [size];
			system ("pause");
            break;
        case 2:
			size = rand();
			sequence = new unsigned int [size];
            cout << "Размер массива =" << size << "\n";
			system ("pause");
            break;
        default:
			cout << "Неправильно выбрана опция.\n";
            system ("pause");
			return 1;
    }
	system("cls");

	cout << "Ввод элементов массива\n";
	cout << "1. Ввести в ручную\n";
	cout << "2. Ввести случайным образом\n";
	cout << "Ввыбор: ";
	cin >> v2;

	switch ( v2 )
    {
		case 1:
			for (unsigned int i=0; i < size; i++){
				cout << "Введите " << i+1 << " элемент ";
				cin >> sequence[i];
			}
			system ("pause");
            break;
        case 2:
			for (unsigned int i=0; i < size; i++){
				sequence[i]= rand();
			}

			for (unsigned int i=0; i < size; i++){
				cout << sequence[i] << " ";
			}
			cout << endl;
			system ("pause");
            break;
        default:
            cout << "Неправильно выбрана опция.\n";
            system ("pause");
			return 2;
    }
	system("cls");

	cout << endl;
	cout << "Сортировка: \n";	
	const clock_t start = clock();
	t = bubbleSort(sequence, size);
	const double time = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	system ("pause");
	system("cls");

	cout << "Результат: \n";
	for (unsigned int i=0; i < size; i++){
		cout << sequence[i] << " ";
	}
	cout << endl << "За " << t << " шага(ов)";
	cout << endl << "За " << time << " милисекунд";

	cout << endl;
	system ("pause");
	return 0;
}