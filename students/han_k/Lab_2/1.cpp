#include <iostream.h>
#include <conio.h>
#include <limits.h>
#include <time.h>
#include "stack.cpp"

struct MovesFromPoint
{
        int NumMoves;
        union
        {
                Point point;
                MovesFromPoint *Moves;
        }node;
};

string ru(string input);
MovesFromPoint AviableSteps(int x, int y, int mode);
void bubble(MovesFromPoint *items, int count);
void processing (int **check, int CurrX, int CurrY);
void print(int **check, int mode, int kolls, int rows);

//���������� ���������� ����������
MovesFromPoint **moves;
Stack st, st1;
int     num = 0,                        //����������� ����
        NumCells = 0,                   //���������� ������ �� ����
        StartedX = 0, StartedY = 0,     //��������� ���������� �� ������ �����
        NumStep = INT_MIN,              //���������� �������� �������
        show = 1,                       //����� �� ����� (1 - ��, 0 - ���)
        MaxSteps = 164;                  //������������ ����� ������ ���������
long double SpeedComp = 4155579;            //�������� ������ ���������� (���-�� ������� ������� � ���)
clock_t start;

int main()
{
        cout << ru("                    ������������ ������ N2. ��� ������\n");
        cout << ru("              ���������� ������������ ����� ���� �� ���������� ����\n\n");
        cout << ru("������� ����������� ����: ");
        cin >> num;
        if (num > 2)
        {
                long double CurrNumStep = 46;
                cout << ru("\n\n�����, ��������� ��� ���������� ���� � ������ ������ ����������: ");
                if(num == 2) cout << CurrNumStep/SpeedComp;
                 else
                 {
                        long double temp = MaxSteps;
                        for(int i = 0; i < num - 4; i++)
                        {
                                CurrNumStep = CurrNumStep*temp;
                                temp = temp*10+24;
                        }
                        cout << (temp*CurrNumStep)/SpeedComp;
                 }
                cout << ru("\n��� �������� ������ ���������� ") << SpeedComp << ru(" ������� ������� � �������\n\n\n");
        }
        cout << ru("�������� ������������? Y/N:\n\n\n");
        if (!kbhit())
        {
                char c = getch();
                if(c == 'n') show = 0;
        }
        start = clock();
        NumCells = num*num;

//�������� ���������� �������, ����������� ��������� ���� ��� ������ �����
        moves = new MovesFromPoint *[num];
        for (int i = 0; i < num; i++) moves[i] = new MovesFromPoint[num];
        for(int x = 0; x < num; x++)
                for (int y = 0; y < num; y++)
                        moves[x][y] = AviableSteps(x,y,0);
//��������� ������ �������� ��������
        for(int i = 0; i <= ((num%2)? num/2:num/2-1); i++)
                for (int j = 0; j <= ((num%2)? num/2:num/2-1); j++)
                {
                //������� ������ ��� �������� ��������� ������
                        int **check;
                        check = new int *[num];
                        for (int i = 0; i < num; i++) check[i] = new int [num];
                        for(int i = 0; i < num; i++)
                                for (int j = 0; j < num; j++)
                                        check[i][j] = 0;
                        StartedX = i;
                        StartedY = j;
                        processing(check,StartedX,StartedY);

                //����������� ���������� ��� ������ �������� ������
                        for (int i = 0; i < num; i++) delete[] check[i];
                        delete[] check;
                }
        cout << ru("\n��������� ���������:");
        cout << "\n\n" << ru("���������� ��������� ����� = ") << INT_MAX - abs(NumStep) + 1 << endl;
        cout << ru("���������� ������ ����!\n\n");
        long double q = ((clock() - start) / CLOCKS_PER_SEC);
        cout << ru("����� ������: ") << q << endl;
        system("pause");

return 0;
}


void processing (int **check, int CurrX, int CurrY)
{
        check[CurrX][CurrY] = 1;
        NumCells--;
        NumStep++;
        st.push(CurrX,CurrY);
        if(show)
        {
                system("cls");
                print(check,0,CurrX,CurrY);
                cout << "\n\n" << endl;
                print(check,1,CurrX,CurrY);
                cout << ru("\n������� �����: ") << CurrX << " " << CurrY << "\n\n";
                cout << ru("���� �� ������� ������:\n\n");
                st.print();
                cout << "\n";
                getch();
        }
        if (!kbhit())
        {
                char c = getch();
                if(c == 's')
                {
                        if(show) cout << ru("�������� ����� �� �����? (Y/N):  ");
                        cin >> c;
                        if((show) && ((c == 'y') || (c == 'Y')))
                        {
                                show = 0;
                                system("cls");
                                cout << ru("���� ���������..\n\n");
                        }
                }

        }
        for(int i = 0; i < moves[CurrX][CurrY].NumMoves; i++) if(!check[moves[CurrX][CurrY].node.Moves[i].node.point.x][moves[CurrX][CurrY].node.Moves[i].node.point.y]) processing(check,moves[CurrX][CurrY].node.Moves[i].node.point.x,moves[CurrX][CurrY].node.Moves[i].node.point.y);
        if((NumCells == 0)) //������� ������
                for(int i = 0; i < moves[CurrX][CurrY].NumMoves; i++)
                        if((moves[CurrX][CurrY].node.Moves[i].node.point.x == StartedX) && (moves[CurrX][CurrY].node.Moves[i].node.point.y == StartedY))
                        {
                                cout << ru("������� �������!\n\n���������� ��������� ����� = ") << INT_MAX - abs(NumStep) + 1;
                                long double q = ((clock() - start) / CLOCKS_PER_SEC);
                                while(!st.empty())
                                {
                                        Point temp = st.pop();
                                        st1.push(temp.x,temp.y);
                                }
                                cout << ru("\n����� ������: ") << q << ru("\n\n���������� ����:\n"); st1.print(); cout << "\n";
                                system("pause");
                                exit(1);
                        }
        st.pop();
        NumCells++;
        check[CurrX][CurrY] = 0;
}



void print(int **check, int mode, int kolls, int rows)
{
        char ch = 0;
        if(mode) cout << ru("������� ��������� ���� �� ����:") << endl << endl;
         else cout << ru("��������� ���������� ������:") << endl << endl; //ru("��������� ���������� ������");
	for(int i = 0; i < num*2+1;cout << "\n", i++)
                for (int j = 0; j < num*2+1; j++)
                {
                        if((i == 0) && (j == 0)){ch = 201; cout << "      " << ch; continue;}
                        if(((i == 0) && (j != 0) && (j != num*2)&&(j%2 != 0)) || ((i == num*2) && (j != 0) && (j != num*2)&&(j%2 != 0))){ch = 205; cout << ch; continue;}
                        if((i == 0) && (j != 0) && (j != num*2)&&(j%2 != 1)){ch = 209; cout << ch; continue;}
                        if((i == num*2) && (j == num*2)){ch = 188; cout << ch; continue;}
                        if((i != 0) && (j == num*2)&& (i%2 != 1)){ch = 182; cout << ch; continue;}
                        if((i == 0) && (j == num*2)){ch = 187; cout << ch; continue;}
                        if(((i != 0) && (j == 0) && (i != num*2) && (i%2 != 0))){ch = 186; cout << "      " << ch; continue;}
                        if((i != 0) && (j == num*2)&& (i%2 != 0)){ch = 186; cout << ch; continue;}
                        if((i != 0) && (j != 0) && (j != num*2) && (j%2 != 0) && (i%2 != 0))
                        {
                                if(mode)
                                {
                                        if((i/2 == kolls) && (j/2 == rows))cout << "*";
                                        else cout << " ";
                                }
                                else cout << check[i/2][j/2];
                        }
                        if((i != 0) && (j != 0) && (j != num*2) && (j%2 != 1) && (i%2 != 0)){ch = 179; cout << ch; continue;}
                        if((i != 0) && (j == 0) && (i != num*2) && (i%2 != 1)){ch = 199; cout << "      " << ch; continue;}
                        if((i != 0) && (j != 0) && (i != num*2) && (j%2 != 0) && (i%2 != 1)){ch = 196; cout << ch; continue;}
                        if((i != 0) && (j != 0) && (i != num*2) && (j%2 != 1) && (i%2 != 1)){ch = 197; cout << ch; continue;}
                        if((i == num*2) && (j == 0)){ch = 200; cout << "      " << ch; continue;}
                        if((i == num*2) && (j != 0) && (j != num*2)&&(j%2 != 1)){ch = 207; cout << ch; continue;}
                }
}

MovesFromPoint AviableSteps(int x, int y, int mode)
{
        int NumAviableSteps = 0;
        if((x-2 >= 0)  &&  (y-1 >= 0)) {if (!mode) st.push(x-2,y-1); NumAviableSteps++;}
        if((x-2 >= 0)  && (y+1 < num)) {if (!mode) st.push(x-2,y+1); NumAviableSteps++;}
        if((x-1 >= 0)  && (y+2 < num)) {if (!mode) st.push(x-1,y+2); NumAviableSteps++;}
        if((x+1 < num) && (y+2 < num)) {if (!mode) st.push(x+1,y+2); NumAviableSteps++;}
        if((x+2 < num) && (y+1 < num)) {if (!mode) st.push(x+2,y+1); NumAviableSteps++;}
        if((x+2 < num) &&  (y-1 >= 0)) {if (!mode) st.push(x+2,y-1); NumAviableSteps++;}
        if((x+1 < num) &&  (y-2 >= 0)) {if (!mode) st.push(x+1,y-2); NumAviableSteps++;}
        if((x-1 >= 0)  &&  (y-2 >= 0)) {if (!mode) st.push(x-1,y-2); NumAviableSteps++;}
        MovesFromPoint CurrPoint;
        CurrPoint.NumMoves = NumAviableSteps; //���������� ��������� ����� �� ������ �����
        if (!mode)
        {
                CurrPoint.node.Moves = new MovesFromPoint[NumAviableSteps]; //�������� ������ ��� �����, � ������� ����� ����� �� ������
                for(int i = 0; i < NumAviableSteps; i++)
                {
                        Point cash;
                        cash = st.pop();
                        CurrPoint.node.Moves[i] = AviableSteps(cash.x,cash.y,1); //��������� "���" �����
                }
                bubble(CurrPoint.node.Moves,CurrPoint.NumMoves); //��������� �����, � ������� ����� ����� �� ������ �� ����������� �����
        }
        else
        {
                Point curr;
                curr.x = x;
                curr.y = y;
                CurrPoint.node.point = curr;
        }
return CurrPoint;
}


void bubble(MovesFromPoint *items, int count)
{
        for (int i = 0; i < count; i++)
                for (int j = 0; j < count - 1; j++)
                        if (items[j].NumMoves > items[j + 1].NumMoves)
                        {
                                MovesFromPoint temp = items[j + 1];
                                items[j + 1] = items[j];
                                items[j] = temp;
                        }
}



string ru(string input)
{
   const int N = 66;
   const char DosABC[N] = "������񦧨�����������������������������������������������������";
   const char WinABC[N] = "�������������������������������������Ũ��������������������������";
   string output = "";
   bool Ok = 0;
   for(unsigned int i = 0; i<input.length(); i++)
   {
      Ok = false;
      for (int j = 0; j<N; j++)
         if (input[i] == WinABC[j])
            {
               output += DosABC[j];
               Ok = true;
            }
      if (!Ok)
         output+=input[i];
   }
return output;
}
