#include "stdafx.h"
#include "villages.h"
#include <fstream>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <cmath>

using namespace std;

int compare (const void * a, const void * b){  
   return ( *(int*)a - *(int*)b );
}


bool consist_mass(int *massiv, int size, int element)
{
	for(int i = 0; i < size; i ++)
	{
		if(massiv[i] == element)
			return true;
	}
	return false;
}

bool Villages::from_file()
{
	char filename[100];
	int i;

	cout << "Введите название файла и путь к нему ";
	cin >> filename;
	ifstream in(filename);
	in >> this->count_vil;
	in >> this->count_post;
	this->coordinates = new int [this->count_vil];
	for(i = 0; !in.eof() ; i ++)
	{
		in >> this->coordinates[i];
		if(i == this->count_vil - 1)
		{
			i ++;
			break;
		}
	}
	if(i < this->count_vil)
		return false;
	if(this->count_vil > 0&&this->count_post > 0&&this->count_vil >= this->count_post)
	{
		qsort(this->coordinates, this->count_vil, sizeof(int), compare); 
		for(i = 1; i < this->count_vil; i ++)
			if(this->coordinates[i] == this->coordinates[i - 1])
			    return false;
	    return true;
	}
	return false;
}

bool Villages::from_keyboard()
{
	int i;
	cout << "Введите количество деревень ";
	cin >> this->count_vil;
	cout << "Введите количество почтовых отделений ";
	cin >> this->count_post;
	cout << "Введите координаты деревень " << endl;
	this->coordinates = new int [this->count_vil];
	for(i = 0; i <  this->count_vil; i ++)
		cin >> this->coordinates[i];
	if(this->count_vil > 0&&this->count_post > 0&&this->count_vil >= this->count_post)
	{
		qsort(this->coordinates, this->count_vil, sizeof(int), compare); 
		for(i = 1; i < this->count_vil; i ++)
			if(this->coordinates[i] == this->coordinates[i - 1])
			    return false;
	    return true;
	}
	return false;

}

void Villages::main_function()
{
	int i, j, k, l, min, line;
	int *resulting_index = new int[this->count_post];
	int *mass1 = new int[this->count_vil];
	int *mass2 = new int[this->count_post];
	this->result_coordinats = new int[this->count_post];

	for(k = 0; k < this->count_post; k ++)
	{
		min = INT_MAX;

		for(i = 0; i < this->count_vil; i ++)
		{
			if(!consist_mass(resulting_index, k+1, i))
			{
				mass1[i] = 0;
				for(j = 0; j < this->count_vil; j ++)
				{
					for(l = 0; l < k; l ++)
					    mass2[l] = abs(this->coordinates[j] - this->coordinates[resulting_index[l]]);
					if(k > 0)
				        qsort(mass2, k, sizeof(int), compare);
					else
						mass2[0] = INT_MAX;
					if(mass2[0] > abs(this->coordinates[i] - this->coordinates[j]))
					    mass1[i] += abs(this->coordinates[i] - this->coordinates[j]);
				    else
					    mass1[i] += mass2[0];
				}

				if(mass1[i] < min)
				{
					min = mass1[i];
					resulting_index[k] = i;
				}
			}
		}
		cout << "\n\n\n\n======================================Шаг" << k + 1 << "=====================================" << endl;
		cout << "\=========================Строим " << k + 1 << "-ое почтовое отделение=========================" << endl;
		for(j = 0; j < this->count_vil; j ++)
		{
			if(resulting_index[k] == j) 
                cout << ">>" <<mass1[j] << "<<" << " ";
			else
			    cout <<  mass1[j] << " ";
		}
		cout << endl << "Почтовое отделение <строим> в деревне с координатой "<< this->coordinates[resulting_index[k]];
	}
	cout << "\n\nНаимеьшая сумма расстояний от каждой деревни до её ближайшего почтового отделения выделена >> <<" << endl << endl << endl;
	for(i = 0; i < this->count_post; i ++)
		this->result_coordinats[i] = this->coordinates[resulting_index[i]];
	cout << endl;
	this->calculation();
	system("Pause");
}

void Villages::calculation() 
{
	int i, j, min;
	this->result_size = 0;
	for(i = 0; i < this->count_vil; i ++)
	{
		min = INT_MAX;
		for(j = 0; j < this->count_post; j ++)
		{
			if(abs(this->coordinates[i] - this->result_coordinats[j]) < min)
				min = abs(this->coordinates[i] - this->result_coordinats[j]);
		}
		this->result_size += min;
	}
}

void Villages::save_to_file()
{
	char filename[100];
	cout << "Введите название файла и путь к нему для сохранения результатов ";
	cin >> filename;
	ofstream out(filename);
	out << this->result_size;
	for(int i = 0; i < this->count_post; i ++)
		out << this->result_coordinats[i] << " ";
}

void Villages::print_on_screen()
{
	cout << "Сумма расстояний от каждой деревни до её ближайшего почтового отделения ";
	cout << this->result_size << endl;
	cout << "Координаты почтовых отделений " << endl;
	for(int i = 0; i < this->count_post; i ++)
		cout << this->result_coordinats[i] << " ";
	cout << endl;
}





