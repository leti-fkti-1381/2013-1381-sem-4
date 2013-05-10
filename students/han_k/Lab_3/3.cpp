#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <vector>

string ru(string input);
void Branch_Bound(vector<int *> *Result, ofstream &out);
void Embranchment(int *arr);
int Bound(int *set, ofstream &out);
int Find_Index(int *set, int elem);
int Factorial(int n);

int NUM = 0, **C = NULL, **D = NULL, Upper_Limit = INT_MAX;

int main()
{
        cout << ru("                    ������������ ������ N3. ��� ������\n");
        cout << ru("               ������� ������ � ������ ������� ������ � ������\n\n");
        cout << ru("������� �������� ����� � ��������� �������: ");
        string file;
        cin >> file;
        file += ".txt";
        char *file_name = new char[file.size()+1];
        file_name[file.size()] = '\0';
        memcpy(file_name,file.c_str(),file.size());
        fstream in(file_name);
        ofstream out("out.txt");
        vector<int *> Result;
        in >> NUM;
        cout << ru("���������� ��������� = ") << NUM << endl;
        out << ru("���������� ��������� = ") << NUM << endl;

        C = new int*[NUM]; for(int i = 0; i < NUM; i++) C[i] = new int[NUM];
        D = new int*[NUM]; for(int i = 0; i < NUM; i++) D[i] = new int[NUM];
        for(int i = 0; i < NUM; i++) for(int j = 0; j < NUM; j++) in >> C[i][j];
        for(int i = 0; i < NUM; i++) for(int j = 0; j < NUM; j++) in >> D[i][j];

        cout << ru("\n\n������� ������ ���������:\n\n");
        out << ru("\n\n������� ������ ���������:\n\n");
        for(int i = 0; i < NUM; i++,cout << endl,out << endl) for(int j = 0; j < NUM; j++, cout << C[i][j-1] << " ",out << C[i][j-1] << " ");

        cout << ru("\n\n������� ���������� ���������� ����� ��������:\n\n");
        out << ru("\n\n������� ���������� ���������� ����� ��������:\n\n");
        for(int i = 0; i < NUM; i++,cout << endl,out << endl) for(int j = 0; j < NUM; j++, cout << D[i][j-1] << " ",out << D[i][j-1] << " ");

        cout << "\n\n";
        out << "\n\n";

        Branch_Bound(&Result,out);


        cout << ru("���������� ��������� ������������ ������� �� �����: ") << Upper_Limit << endl;
        out << ru("���������� ��������� ������������ ������� �� �����: ") << Upper_Limit << endl;
        cout << ru("��� ����������� ��� ��������� �����������:\n\n");
        out << ru("��� ����������� ��� ��������� �����������:\n\n");
        for(vector<int *>::iterator it = Result.begin(); it != Result.end(); ++it,cout << endl, out << endl)
        {
                cout << "  ";
                for(int i = 0; i < NUM; i++,cout << (*it)[i-1] << " ",out << (*it)[i-1] << " ");
        }
        _getch();
}


void Branch_Bound(vector<int *> *Result, ofstream &out)
{
        int *set = new int[NUM], temp = 0, i = Factorial(NUM);
        for(int i = 0; i < NUM; i++) set[i] = i;
        do
        {
                cout << ru("������� ������������: "); for(int i = 0; i < NUM; i++) cout << set[i] << " "; cout << endl;
                out << ru("������� ������������: "); for(int i = 0; i < NUM; i++) out << set[i] << " "; out << endl;
                temp = Bound(set,out);
                if(temp)
                {
                        if(Upper_Limit != temp)
                        {
                                cout << ru("������� ����� �������, ������� ��������� = ") << temp << endl;
                                out << ru("������� ����� �������, ������� ��������� = ") << temp << endl;
                                while(!Result->empty()) Result->pop_back();
                                Upper_Limit = temp;
                        }
                        else
                        {
                                cout << ru("������� ��� ���� �������, ������� �����-�� ��������� = ") << temp << endl;
                                out << ru("������� ��� ���� �������, ������� �����-�� ��������� = ") << temp << endl;
                        }
                        int *temp = new int[NUM];
                        for(int i = 0; i < NUM; i++) temp[i] = set[i];
                        Result->push_back(temp);
                }
                Embranchment(set);
                i--;
                cout << "\n";
                out << "\n";
        }while(i);
}


int Bound(int *set, ofstream &out)
{
        int temp = 0;
        for(int index = 0; index < NUM; index++)
                for(int i = index+1; i < NUM; i++)
                        if(C[index][i])
                        {
                                temp += C[index][i]*D[Find_Index(set,index)][Find_Index(set,i)];
                                if(temp > Upper_Limit)
                                {
                                        cout << ru("��������� ������� ������� = ") << Upper_Limit << ru(" �� ") << index << ru(" ������ �� ") << temp - Upper_Limit << "\n";
                                        out << ru("��������� ������� ������� = ") << Upper_Limit << ru(" �� ") << index << ru(" ������ �� ") << temp - Upper_Limit << "\n";
                                        return 0;
                                }
                        }
return temp;
}

int Find_Index(int *set, int elem)
{
        for(int i = 0; i < NUM; i++)
                if(set[i] == elem) return i;
return -1;
}

int Factorial(int n)
{
      return (!n)? 1 : n*Factorial(n-1);
}

void Embranchment(int *arr)
{
        int n = NUM-1 , k = n-1;
        while ( (arr[k] >= arr[k+1]) && (k >= 0) ) k--;
        if (k < 0) return;
        int t = k+1, y = arr[k];
        while ( (t < n) && (arr[t+1] > arr[k]) ) t++;
        arr[k] = arr[t];
        arr[t] = y;
        t = 0;
        while (t < (int)((double)(n-k)/2.0))
        {
                y = arr[n-t];
                arr[n-t] = arr[k+1+t];
                arr[k+1+t] = y;
                t++;
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
