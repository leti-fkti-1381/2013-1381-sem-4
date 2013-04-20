#ifndef _lr_2
#define _lr_2

//---------------------------------------------------------------
const int max_side = 8; // ������������ ������� ��������
const int max_bishop = 64; // ������������ ���������� ������

//---------------------------------------------------------------
double amount_position (int [max_side][max_side], int, int); // ������� �������� ���������� �������, �� ������� ����� ��������� ������, ����� ��� �� ���� ���� �����
double bust (int [max_side][max_side], int, int); // ����������� ������� �������� ���������� �������

//---------------------------------------------------------------
// ������� �������� ���������� �������, �� ������� ����� ��������� ������, ����� ��� �� ���� ���� �����
double amount_position (int field[max_side][max_side], int side, int bishop)
{
	// �������� �� ���������� ��������� ������
	if (side < 1 && side > 8 && bishop < 1 && bishop > side*side)
		return 0;
	// ������� ���������� �������
	double amount = bust (field, side, bishop);
	// ������� ���������� ������� ��� ����� ������� ������
	for (int i = 1; i <= bishop; i ++)
		amount = amount / i;
	return amount;
}

//---------------------------------------------------------------
// ����������� ������� �������� ���������� �������
double bust (int field[max_side][max_side], int side, int bishop)
{
	double amount = 0; 
	// ���� �� ���� ������� ����
	for (int i = 0; i < side; i ++)
		for (int j = 0; j < side; j ++)
		{
			if (field[i][j] == 0)
			{
				// ���������� ���������� �������
				int x = i, y = j;
				// ��������� ������ ����� ��������� ����� �������
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x ++;
					y ++;
				}
				// ��������� ������� ����� ��������� ����� �������
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x --;
					y --;
				}
				// ��������� ������ ����� ��������� ������ ������
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x ++;
					y --;
				}
				// ��������� ������� ����� ��������� ������ ������
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == 0) field[x][y] = bishop;
					x --;
					y ++;
				}
				// �������� �� ���������� �����
				if (bishop != 1)
					amount += bust (field, side, bishop-1);
				// ������� ���������� �������, �� ������� ����� ��������� ���������� �����
				if (bishop == 1)
					amount ++;
				// ���������� ���������� ������
				x = i, y = j;
				// ��������� ������ ����� ��������� ����� �������
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x ++;
					y ++;
				}
				// ��������� ������� ����� ��������� ����� �������
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x --;
					y --;
				}
				// ��������� ������ ����� ��������� ������ ������
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x ++;
					y --;
				}
				// ��������� ������� ����� ��������� ������ ������
				x = i; y = j;
				while (x >= 0 && x < side && y >= 0 && y < side)
				{
					if (field[x][y] == bishop) field[x][y] = 0;
					x --;
					y ++;
				}
			}
		}
	return amount;
}

#endif