#include <time.h>
#include <omp.h>
#include <iostream>

using namespace std;

class Massiv {
    private:
		int *mass;
		int size_mass;
		int max_mass;


		//�������
    public:
		Massiv(int *m, int s, int max);
		int *sort();
		int vizual_sort();
};

//�����������
Massiv::Massiv(int *m, int s, int max)
{
	size_mass = s;
	max_mass = max;
	mass = new int[size_mass];
	for(int i = 0; i < size_mass; i ++)
		mass[i] = m[i];
}

//������� ����������
int *Massiv::sort()
{
    int l = 0,r = size_mass - 1; //����� � ������ ������� ��������������
    int i, min, max; 
	int *M = new int[size_mass];
	for(i = 0; i < size_mass; i ++)
		M[i] = mass[i];
    while(l < r) 
        {
         min = max = l;
         for(i = l + 1; i <= r; i ++)
             {
               if(M[min] > M[i])
			       min = i;
               else 
			       {
				     if(M[max] < M[i])
					     max = i;
				   }
             }
         swap(M[l], M[min]);
         if(max == l)
	         max = min;
         swap(M[r], M[max]);
         ++ l;
         -- r;
		}
	return M;
}

//������� ����������
int Massiv::vizual_sort()
{
    int l = 0,r = size_mass - 1; //����� � ������ ������� ��������������
    int i, min, max, j = 1;
	long long int iterations = 0;
	int *M = new int[size_mass];
    while(l < r) 
        {
		 iterations ++;
         min = max = l;
		 iterations ++;
		 iterations ++;
         for(i = l + 1; i <= r; i ++)
             {
			   iterations ++;
			   iterations ++;
               if(M[min] > M[i])
			       {
			         min = i;
					 iterations ++;
			       }
               else 
			       {
					 iterations ++;
				     if(M[max] < M[i])
					     {
					       max = i;
						   iterations ++;
					     }
				   }
			   iterations ++;
             }
         swap(M[l], M[min]);
		 iterations ++;
		 iterations ++;
         if(max == l)
		     {
	           max = min;
			   iterations ++;
		     }
         swap(M[r], M[max]);
		 iterations ++;
		 iterations ++;
         ++ l;
         -- r;
		 iterations ++;
		}
	return iterations;
}

