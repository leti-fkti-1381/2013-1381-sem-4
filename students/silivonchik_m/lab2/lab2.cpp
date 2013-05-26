#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <ctime>
using namespace std;

#define mSize 5

//структура дл€ хранени€ пути и его координат
//типа стек
typedef struct Position
{
    int PointX;
    int PointY;
    int StepsAmount;
    char Steps[6];

    struct Position* next;
}Pos;

//структура дл€ хранени€ минимального пути
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

    //0 - свободное поле
    //6 - барьер
    //5 - начальна€ точка
    //1 - путь
    //9 - конечна€ точка
    int m[mSize][mSize];
    int x5, y5, x9, y9;
    int i, j;
    Pos* top = NULL;
    MW* topMin = NULL;

    srand(time(NULL)); //устанавливаем нач. значение генератора
    for (i=0; i<mSize; i++)
        for (j=0; j<mSize; j++)
            //if (rand()%5 == 1) //генерируем барьер с веро€тностью 20%
            if (rand()%(13-mSize) == 1) //генерируем барьер с веро€тностью (13-mSize);
                                        //чем больше размерность, тем больше веро€тность постановки барьера
                m[i][j] = 6;
            else
                m[i][j] = 0;

    cout << "\tЋабиринт:" << endl;
    for (int i=0; i<mSize; i++)
    {
        for (int j=0; j<mSize; j++)
                cout << m[i][j];
        cout << endl;
    }

    do
    {
        cout << endl << "\t¬ведите координаты начальной точки:" << endl;
        cout << "строка = "; cin >> x5;
        cout << "столбец = "; cin >> y5;

        cout << endl <<"\t¬ведите координаты конечной точки:" << endl;
        cout << "строка = "; cin >> x9;
        cout << "столбец = "; cin >> y9;
    }
    while ((x5<0 || x5>=mSize || y5<0 || y5>=mSize || x9<0 || x9>=mSize || y9<0 || y9>=mSize || m[x5][y5]==6 || m[x9][y9]==6 || (x5==x9 && x5==y9)));
    m[x5][y5] = 5;
    m[x9][y9] = 9;

    ofstream OutFile ("Ways.txt");
    OutFile << "¬се возможнные пути из [" << x5 << "][" << y5 << "] в [" << x9 << "][" << y9 << "]" << endl;
    OutFile << "«аданный лабиринт:" << endl;
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

    cout << "—ейчас вы узнаете минимальный путь! :)"; system("pause");
    cout << endl << " оличество шагов: " << topMin->MinStepsAmount << endl << "Ўаги: " << topMin->Way;

    delete topMin;
}

//рекурсивна€ функци€ поиска пути
void FindWay (int m[mSize][mSize], int x, int y, Pos* top, MW* topMin)
{
    //cout << "“екущее положение:  [" << x << "][" << y << "]" << endl;
    //if (top!=NULL) cout << "way = " << top->Steps << endl; system ("pause");

    //"пропускаем" условие тупика дл€ случа€, когда мы находимс€ в начальной точке
    bool firstStep = false;
    if (top == NULL)
        firstStep = true;

    if (m[x][y] != 9)
    {//неконечна€ точка
        top = Push (top);
        top->PointX = x;
        top->PointY = y;
        if (top->next != NULL)
            top->StepsAmount = top->next->StepsAmount+1;
        else //если это первый элемент
            top->StepsAmount = 0;

        //условие: чтобы не выходило за границы && чтобы не было барьером && чтобы не было уже пройденным путЄм && чтобы не было начальной точкой
        if ((firstStep == true) || (x>=0 && x<mSize && y>=0 && y<mSize && m[x][y]!=6 && m[x][y]!=1 && m[x][y]!=5))
        {//если не тупик
            //cout << "Ўагаем дальше!\n"; system ("pause");
            if (m[x][y] != 5)
                m[x][y] = 1; //маркируем шаг!

            strcpy (top->Steps, "right");
            FindWay (m, x, y+1, top, topMin);
            strcpy (top->Steps, "down");
            FindWay (m, x+1, y, top, topMin);
            strcpy (top->Steps, "left");
            FindWay (m, x, y-1, top, topMin);
            strcpy (top->Steps, "up");
            FindWay (m, x-1, y, top, topMin);

            if (m[x][y] == 5)
            {//когда рассмотрены все пути из начальной точки
                ofstream OutFile ("Ways.txt", ios::app);
                OutFile << endl << "ћинимальный путь!" << endl;
                OutFile << " оличество шагов: " << topMin->MinStepsAmount << endl;
                OutFile << "Ўаги: " << topMin->Way;
            }

            top = Pop (top);
            if (top != NULL)
            {
                strcpy (top->Steps, "none");
                m[x][y] = 0;
            }
        }
        else
            {//если тупик, то восстанавливаемс€ в прошлое состо€ние
                //"откат" стека
                top = Pop(top);
                strcpy (top->Steps, "none");
                //откат координат
                x = top->PointX;
                y = top->PointY;
            }
    }
    else
    {//конечна€ точка
        top->StepsAmount++;

        //определение минимального пути
        if (topMin->MinStepsAmount == 0)
            topMin->MinStepsAmount = top->StepsAmount;
        else
            if (top->StepsAmount < topMin->MinStepsAmount)
                topMin->MinStepsAmount = top->StepsAmount;

        //сохранение результатов
        Pos* vs=NULL;
        string CurrWay = "";

        vs = top;
        bool ThisIsMin = false; //данный путь минимальный из уже найденных?

        if (top->StepsAmount == topMin->MinStepsAmount) //если текущий элемент минимален
        {
            ThisIsMin = true;
            topMin->Way = "";
        }

        ofstream OutFile ("Ways.txt", ios::app);
        OutFile << endl;
        OutFile << " оличество шагов: " << top->StepsAmount << endl;
        OutFile << "Ўаги: ";
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

        //сохранение матрицы
        OutFile << "ѕуть: ";
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

//функци€ добавлени€ в стек
Pos* Push (Pos* top)
{
    Pos* vs;

    if (top == NULL)
	{ //первый элемент
		vs = new Position;
		top = vs;
		top->next = NULL;
	}
	else
	{ //не первый элемент
		vs = new Position;
		vs->next = top;
		top = vs;
	}
}

//фунци€ извлечени€ из стека
Pos* Pop (Pos* top)
{
    if (top->next != NULL)
	{
		Pos* vs;

		vs = top;
		top = top->next; //смещаем вершину стека
		delete vs; //удал€ем "старую" вершину
		return (top);
	}
	else
	{
		//cout << "—тек пуст!";
		return (NULL);
	}
}
