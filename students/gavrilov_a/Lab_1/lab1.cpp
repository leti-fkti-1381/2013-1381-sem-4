#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int bubbleSort(unsigned int *arr,unsigned int size)
{ 
	int t=0; //���������� �����
	int buffer; //���������� ���������� �� ������ ����� ��������� ����������
    for(unsigned int i = 0; i < size-1; i++) // i - ����� �������
    {            
        for(unsigned int j = 0; j < size-1; j++) // ���������� ���� �������
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
	unsigned int size; //������ ������ ������������������ 
	unsigned int *sequence; //������ ������������������ 
	int t; //���������� �����
	srand(time(0));

	int v1, v2=1;

	cout << "���� ������� �������\n";
	cout << "1. ������ � ������\n";
	cout << "2. ������ ��������� �������\n";
	cout << "������: ";
	cin >> v1;
	switch ( v1 )
    {
		case 1:
			cout << "������ ������� = ";
			cin >> size;
			sequence = new unsigned int [size];
			system ("pause");
            break;
        case 2:
			size = rand();
			sequence = new unsigned int [size];
            cout << "������ ������� =" << size << "\n";
			system ("pause");
            break;
        default:
			cout << "����������� ������� �����.\n";
            system ("pause");
			return 1;
    }
	system("cls");

	cout << "���� ��������� �������\n";
	cout << "1. ������ � ������\n";
	cout << "2. ������ ��������� �������\n";
	cout << "������: ";
	cin >> v2;

	switch ( v2 )
    {
		case 1:
			for (unsigned int i=0; i < size; i++){
				cout << "������� " << i+1 << " ������� ";
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
            cout << "����������� ������� �����.\n";
            system ("pause");
			return 2;
    }
	system("cls");

	cout << endl;
	cout << "����������: \n";	
	const clock_t start = clock();
	t = bubbleSort(sequence, size);
	const double time = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	system ("pause");
	system("cls");

	cout << "���������: \n";
	for (unsigned int i=0; i < size; i++){
		cout << sequence[i] << " ";
	}
	cout << endl << "�� " << t << " ����(��)";
	cout << endl << "�� " << time << " ����������";

	cout << endl;
	system ("pause");
	return 0;
}