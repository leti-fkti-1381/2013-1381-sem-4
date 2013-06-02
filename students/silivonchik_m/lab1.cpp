#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

//���������� ������� ��� ������ ���� (YourType) ������
//���������� ������� ������ ��� ����������
template <class YourType> YourType* RandomGeneration (unsigned int *mSize)
{
    unsigned int i, j, only; //"���������� �����"
    int percent; //���������� ����������� ���������
    double percentTemp; //��������������� ���������� ��� ������� ������������ percent
    char sw; //���������� ������
    bool control;
    YourType elTemp; //���������� ��� ����������� �������� �������� �������
    YourType *mTemp; //����������� ������
    YourType min, max; //������� ���������

    ofstream OutFile ("Generation.txt", ios::app);

    //������
    cout << "\n\t�������� ������ �������: ";
    cin >> (*mSize);
    mTemp = new YourType [*mSize];
    OutFile << "\n������ �������: " << (*mSize);

    //�������� ��������
    cout << "\n\t������� ��������:\n";
    cout << "������ �������: "; cin >> min;
    cout << "������� �������: "; cin >> max;
    OutFile << "\n�������� ��������: �� " << min << " �� " << max;

    //����������� ��������
    do
    {
        cout << "\n\t������ �� ������ ����� ����������� ��������? ��(Y)/���(N) ";
        cin >> sw;
        if (isupper(sw)==1)
            sw=_tolower(sw);
        switch (sw)
        {
            case ('y'): cout << "�������� ���� ����������� ���������: (� ���������) ";
                        //cin >> percent;
                        cin >> percentTemp;
                        OutFile << "\n����������� �������� ���������: �������";
                        OutFile << "\n������� ����������� ���������: " << percentTemp;

                        percentTemp = (*mSize)*percentTemp/100;
                        percentTemp = ceil (percentTemp); //��������� "�����"
                        //���� ����� ���� ���� �������, �� �� ��������� ���������� �����
                        percent = percentTemp;
                        if (percent == 1)
                            percent++;

                        //cout << "\n� ������� ����� " << percent << " ���������� ���������.";
                        OutFile << "\n���������� ����������� ���������: " << percent;
                        break;

            case ('n'): percent = 0;
                        OutFile << "\n����������� �������� ���������: ����������";
                        break;

            default:    cout << "\n��� ������ ������! ���������� �����!\n\n";
                        break;
        }
    }
    while (sw!='y' && sw!='n');

    //���������
    srand(time(NULL)); //������������� ���. �������� ����������
    for (i=0; i < *mSize; i++)
    {
        do
        {
            control = true;

            mTemp[i] = min + (YourType)rand()/((YourType)RAND_MAX/(max-min+1));
            //cout << "\nm[" << i << "] = " << mTemp[i] << " "; system ("pause");

            if (percent == 0) //�� ������ ���� ����������!
            {
                for (j=0; j<i; j++)
                    if (mTemp[j] == mTemp[i])
                        control = false; //���������� �����!
            }
            else //����������?
            {
                for (j=0; j<i; j++)
                    if (mTemp[j] == mTemp[i])
                    {//����� ���������, ������� ��� ���������?
                        control = true;
                        //true - �� ��� ������ ���������� � ���� �������� percent=percent-2
                        //false - �� ��� �� ������ ���������� � ���� �������� percent=percent-1
                        for (j++; j<i; j++)
                            if (mTemp[j] == mTemp[i]) //�������� ����������?
                            {
                                percent = percent - 1;
                                j=i;
                                control = false;
                            }
                        if (control == true) //������ ����������?
                        {
                            if (percent-2 >= 0) //������� ��� ��������� ������ ���� �������?
                                percent = percent - 2;
                            else //���� ���, �� ���������� �����!
                                control = false;
                        }
                        else //�������� ����������. ������������� control = true ��� ������ �� �����
                            control = true;
                    }
                    //else //����� ���������� �������
            }
        }
        while (control != true);
    }

    if (percent>0) //������������� ���� ����������?
    {
        if (percent == 1) //�������� ��� ���������
        {
            for (i=0, control = false; control == false; i++)//���������� ������� ��� ����������� (����� ���� �������������)
            {
                for (j=i+1; j<(*mSize) && control == false; j++)
                    if (mTemp[j] == mTemp[i]) //i ���������?
                        control = true;
            }
            only = i-1;
            for (i=only+1, control = true; percent>0; i++, control = true)
            {
            //��������� ������� m[only] ������ ������ ������������ ���������!
                for (j=i+1; j<(*mSize) && control == true; j++)
                    if (mTemp[j] == mTemp[i] && mTemp[j] == mTemp[only])
                        control = false; //������� �� ������������

                if (control == true) //���� ������� ������������
                {
                    mTemp[i] = mTemp[only];
                    percent--;
                }
            }
        }
        else //�������� ���������� ������� � �������� ��� ������ ������ ��������� ��������� ����������� ���������� ���
        {
            for (i=0, control = true; control == false; i++, control = true)//���������� ������� ��� ����������� (����� ���� ������������)
            {
                for (j=i+1; j<(*mSize) && control == true; j++)
                    if (mTemp[j] == mTemp[i])
                        control = false; //i �� ������������
            }//�� ������ �� ����� �����, ��� (i-1)-�� ������� ������������ � �������
            only = i;
            percent--; //��� ��� ��� ������ ������� ���������� percent=percent-2;
            for (i=only+1, control = true; percent>0; i++, control = true) //���������, ���� ���� ���������))
            {
            //��������� ������� m[only] ������ ������ ������������ ���������!
                for (j=i+1; j<(*mSize) && control == true; j++)
                    if (mTemp[j] == mTemp[i])
                        control = false; //������� �� ������������

                if (control == true)
                {
                    mTemp[i] = mTemp[only];
                    percent--;
                }
            }
        }
    }

    //���������������
    do
    {
        cout << "\n\t����������� ������? ��(Y)/���(N)";
        cin >> sw;
        if (isupper(sw)==1)
            sw=_tolower(sw);
        switch (sw)
        {
            case ('y'): OutFile << "\n���������������: ��";
                        cout << "\n����������� �� �������� (D) ��� ������������ (U)? ";
                        cin >> sw;
                        do
                        {
                            switch (sw)
                            {
                                case ('u'): for (i=0; i<(*mSize-1); i++)
                                                for (j=0; j<(*mSize-1); j++)
                                                    if (mTemp[j+1] < mTemp[j])
                                                    {
                                                        elTemp = mTemp[j+1];
                                                        mTemp[j+1] = mTemp[j];
                                                        mTemp[j] = elTemp;
                                                    }
                                            OutFile << ", ������";
                                            break;

                                case ('d'): for (i=0; i<(*mSize-1); i++)
                                                for (j=0; j<(*mSize-1); j++)
                                                    if (mTemp[j+1] > mTemp[j])
                                                    {
                                                        elTemp = mTemp[j+1];
                                                        mTemp[j+1] = mTemp[j];
                                                        mTemp[j] = elTemp;
                                                    }
                                            OutFile << ", ��������";
                                            break;

                                default:    cout << "\n��� ������ ������! ���������� �����!\n\n";
                                            system ("pause");
                                            break;
                            }
                        }
                        while (sw!='u' && sw!='d');

                        sw='y';
                        break;

            case ('n'): OutFile << "\n���������������: ���";
                        system ("pause");
                        break;

            default:    cout << "\n��� ������ ������! ���������� �����!\n\n";
                        system ("pause");
                        break;

        }
    }
    while (sw!='y' && sw!='n');

    OutFile.close();
    return (mTemp);
}

//������� ������ �� �����
template <class YourType> void Print (YourType *m, unsigned int mSize)
{
    ofstream OutFile ("Generation.txt", ios::app);

    //system ("cls");
    cout << "\n";
    OutFile << "\n\t��������������� ������:";
    cout << "��������������� ������: ";
    for (unsigned int i=0; i<mSize; i++)
    {
        cout << "\nm[" << i << "] = " << m[i];
        OutFile << "\nm[" << i << "] = " << m[i];
    }
    cout << "\n";
    OutFile.close();
    system ("pause");
}

int main ()
{
    setlocale(LC_CTYPE, "Russian");

    unsigned int mSize; //������ ������� m
    char typeSelect; //���������� ������ ����
    ofstream OutFile ("Generation.txt"); //�������� ��������� ��������� ��������� � ���������� ������
    OutFile << "\t������� ���������:";

    do
    {
        cout << "\t�������� ��� ��������� �������:";
        cout << "\nInteger (i)";
        cout << "\nFloat (f)";
        cout << "\nDouble (d)\n";
        //more types??
        cin >> typeSelect;
        if (isupper(typeSelect)==1)
            typeSelect=_tolower(typeSelect);
        switch(typeSelect)
        {
            case ('i'): {int *m; //���������� ������������� ������
                        OutFile << "\n��� ��������� �������: integer";
                        OutFile.close();
                        m = RandomGeneration <int> (&mSize);
                        Print <int> (m, mSize);
                        delete [] m;
                        break;}

            case ('f'): {float *m; //���������� ������ ��������� � ��������� ������
                        OutFile << "\n��� ��������� �������: float";
                        OutFile.close();
                        m = RandomGeneration <float> (&mSize);
                        Print <float> (m, mSize);
                        delete [] m;
                        break;}

            case ('d'): {double *m; //���������� ������ ��������� � ��������� ������
                        OutFile << "\n��� ��������� �������: double";
                        OutFile.close();
                        m = RandomGeneration <double> (&mSize);
                        Print <double> (m, mSize);
                        delete [] m;
                        break;}

            default:    cout << "\n��� ������ ����! ���������� �����!\n\n";
                        system ("pause");
                        break;
        }

    }
    while (typeSelect!='i' && typeSelect!='f' && typeSelect!='d');
}
