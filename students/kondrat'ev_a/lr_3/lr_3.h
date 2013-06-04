#ifndef _lr_3_
#define _lr_3_

#include <vector>
#include <limits>
using namespace std;

//---------------------------------------------------------------
const int max_amount = 100; // ������������ ���������� ���������
const int max_value = 100; // ������������ �������� ��������

//---------------------------------------------------------------
int Solution (vector <int>, int); // ������� ���������� �������
void MinSolution (vector <int>, int, int, int&); // ����������� ������� ���������� ������������ �������

//---------------------------------------------------------------
// ������� ���������� �������
int Solution (vector <int> arr , int amount_arr)
{
	// �������� ��������� ������
	if (!(amount_arr > 1 && amount_arr <= max_amount))
		return -1;
	for (int i = 0; i < arr.size(); i++)
		if (arr[i] > max_value)
			return -1;
	int solution = numeric_limits<int>::max(); // ������������ �������� ���� int;
	MinSolution (arr, amount_arr, 0, solution); // ���������� �������
	return solution;
}

//---------------------------------------------------------------
// ����������� ������� ���������� ������������ �������
void MinSolution (vector <int> arr, int amount_arr, int curr, int& solution)
{
	int step = 0; // ���� ����
	for (int i = 1; i < amount_arr-1; i++)
	{
		// ���������� ��������� ����
		step = (arr[i-1]+arr[i+1])*arr[i];
		// �������� �� ����������� ����������
		if (curr+step <= solution)
		{
			int erase_elem = arr[i]; // ��������� �������
			arr.erase(arr.begin()+i); // ��������
			MinSolution (arr, amount_arr-1, curr+step, solution);
			arr.insert(arr.begin()+i, erase_elem); // ������������� ���������� ��������
		}
	}
	// ��������� ����������� ���������� � ������� ��������
	if (amount_arr == 2 && curr < solution)
	{
		solution = curr;
	}
}

#endif