#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <ctime>
using namespace std;

#define mSize 5

//��������� ��� �������� ���� � ��� ���������
//���� ����
typedef struct Position
{
    int PointX;
    int PointY;
    int StepsAmount;
    char Steps[6];

    struct Position* next;
}Pos;

//��������� ��� �������� ������������ ����
typedef struct MinWay
{
    int MinStepsAmount;
    string Way;
}MW;

Pos* Push (Pos* top);
Pos* Pop (Pos* top);
void FindWay (int m[mSize][mSize], int x, int y, Pos* top, MW* topMin);

int main ()
{
    setlocale(LC_CTYPE, "Russian");

    //0 - ��������� ����
    //6 - ������
    //5 - ��������� �����
    //1 - ����
    //9 - �������� �����
    int m[mSize][mSize];
    int x5, y5, x9, y9;
    int i, j;
    Pos* top = NULL;
    MW* topMin = NULL;

    srand(time(NULL)); //������������� ���. �������� ����������
    for (i=0; i<mSize; i++)
        for (j=0; j<mSize; j++)
            //if (rand()%5 == 1) //���������� ������ � ������������ 20%
            if (rand()%(13-mSize) == 1) //���������� ������ � ������������ (13-mSize);
                                        //��� ������ �����������, ��� ������ ����������� ���������� �������
                m[i][j] = 6;
            else
                m[i][j] = 0;

    cout << "\t��������:" << endl;
    for (int i=0; i<mSize; i++)
    {
        for (int j=0; j<mSize; j++)
                cout << m[i][j];
        cout << endl;
    }

    do
    {
        cout << endl << "\t������� ���������� ��������� �����:" << endl;
        cout << "������ = "; cin >> x5;
        cout << "������� = "; cin >> y5;

        cout << endl <<"\t������� ���������� �������� �����:" << endl;
        cout << "������ = "; cin >> x9;
        cout << "������� = "; cin >> y9;
    }
    while ((x5<0 || x5>=mSize || y5<0 || y5>=mSize || x9<0 || x9>=mSize || y9<0 || y9>=mSize || m[x5][y5]==6 || m[x9][y9]==6 || (x5==x9 && x5==y9)));
    m[x5][y5] = 5;
    m[x9][y9] = 9;

    ofstream OutFile ("Ways.txt");
    OutFile << "��� ���������� ���� �� [" << x5 << "][" << y5 << "] � [" << x9 << "][" << y9 << "]" << endl;
    OutFile << "�������� ��������:" << endl;
    for (int i=0; i<mSize; i++)
    {
        for (int j=0; j<mSize; j++)
                OutFile << m[i][j];
        OutFile << endl;
    }
    OutFile.close();

    topMin = new MinWay;
    topMin->MinStepsAmount = 0;

    FindWay(m, x5, y5, top, topMin);

    cout << "������ �� ������� ����������� ����! :)"; system("pause");
    cout << endl << "���������� �����: " << topMin->MinStepsAmount << endl << "����: " << topMin->Way;

    delete topMin;
}

//����������� ������� ������ ����
void FindWay (int m[mSize][mSize], int x, int y, Pos* top, MW* topMin)
{
    //cout << "������� ���������:  [" << x << "][" << y << "]" << endl;
    //if (top!=NULL) cout << "way = " << top->Steps << endl; system ("pause");

    //"����������" ������� ������ ��� ������, ����� �� ��������� � ��������� �����
    bool firstStep = false;
    if (top == NULL)
        firstStep = true;

    if (m[x][y] != 9)
    {//���������� �����
        top = Push (top);
        top->PointX = x;
        top->PointY = y;
        if (top->next != NULL)
            top->StepsAmount = top->next->StepsAmount+1;
        else //���� ��� ������ �������
            top->StepsAmount = 0;

        //�������: ����� �� �������� �� ������� && ����� �� ���� �������� && ����� �� ���� ��� ���������� ���� && ����� �� ���� ��������� ������
        if ((firstStep == true) || (x>=0 && x<mSize && y>=0 && y<mSize && m[x][y]!=6 && m[x][y]!=1 && m[x][y]!=5))
        {//���� �� �����
            //cout << "������ ������!\n"; system ("pause");
            if (m[x][y] != 5)
                m[x][y] = 1; //��������� ���!

            strcpy (top->Steps, "right");
            FindWay (m, x, y+1, top, topMin);
            strcpy (top->Steps, "down");
            FindWay (m, x+1, y, top, topMin);
            strcpy (top->Steps, "left");
            FindWay (m, x, y-1, top, topMin);
            strcpy (top->Steps, "up");
            FindWay (m, x-1, y, top, topMin);

            if (m[x][y] == 5)
            {//����� ����������� ��� ���� �� ��������� �����
                ofstream OutFile ("Ways.txt", ios::app);
                OutFile << endl << "����������� ����!" << endl;
                OutFile << "���������� �����: " << topMin->MinStepsAmount << endl;
                OutFile << "����: " << topMin->Way;
            }

            top = Pop (top);
            if (top != NULL)
            {
                strcpy (top->Steps, "none");
                m[x][y] = 0;
            }
        }
        else
            {//���� �����, �� ����������������� � ������� ���������
                //"�����" �����
                top = Pop(top);
                strcpy (top->Steps, "none");
                //����� ���������
                x = top->PointX;
                y = top->PointY;
            }
    }
    else
    {//�������� �����
        top->StepsAmount++;

        //����������� ������������ ����
        if (topMin->MinStepsAmount == 0)
            topMin->MinStepsAmount = top->StepsAmount;
        else
            if (top->StepsAmount < topMin->MinStepsAmount)
                topMin->MinStepsAmount = top->StepsAmount;

        //���������� �����������
        Pos* vs=NULL;
        string CurrWay = "";

        vs = top;
        bool ThisIsMin = false; //������ ���� ����������� �� ��� ���������?

        if (top->StepsAmount == topMin->MinStepsAmount) //���� ������� ������� ���������
        {
            ThisIsMin = true;
            topMin->Way = "";
        }

        ofstream OutFile ("Ways.txt", ios::app);
        OutFile << endl;
        OutFile << "���������� �����: " << top->StepsAmount << endl;
        OutFile << "����: ";
        while (top != NULL)
        {
            CurrWay = top->Steps + CurrWay;
            if (top->next != NULL)
                CurrWay = "->" + CurrWay;
            else
                CurrWay += ".";

            top = top->next;
        }
        OutFile << CurrWay << endl;
        if (ThisIsMin == true)
            topMin->Way = CurrWay;

        top = vs;

        //���������� �������
        OutFile << "����: ";
        for (int i=0; i<mSize; i++)
        {
            for (int j=0; j<mSize; j++)
                OutFile << m[i][j];
            OutFile << "\n      ";
        }
        OutFile.close();

        top->StepsAmount--;
    }
}

//������� ���������� � ����
Pos* Push (Pos* top)
{
    Pos* vs;

    if (top == NULL)
	{ //������ �������
		vs = new Position;
		top = vs;
		top->next = NULL;
	}
	else
	{ //�� ������ �������
		vs = new Position;
		vs->next = top;
		top = vs;
	}
}

//������ ���������� �� �����
Pos* Pop (Pos* top)
{
    if (top->next != NULL)
	{
		Pos* vs;

		vs = top;
		top = top->next; //������� ������� �����
		delete vs; //������� "������" �������
		return (top);
	}
	else
	{
		//cout << "���� ����!";
		return (NULL);
	}
}
