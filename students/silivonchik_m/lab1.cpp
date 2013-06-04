#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

//обобщённая функция для любого типа (YourType) данных
//генерирует входной массив для сортировки
template <class YourType> YourType* RandomGeneration (unsigned int *mSize)
{
    unsigned int i, j, only; //"переменная цикла"
    int percent; //количество совпадающих элементов
    double percentTemp; //вспомогательная переменная для верного формирования percent
    char sw; //переменная выбора
    bool control;
    YourType elTemp; //переменная для временнного хранения элемента массива
    YourType *mTemp; //создаваемый массив
    YourType min, max; //границы диапазона

    ofstream OutFile ("Generation.txt", ios::app);

    //размер
    cout << "\n\tВыберите размер массива: ";
    cin >> (*mSize);
    mTemp = new YourType [*mSize];
    OutFile << "\nРазмер массива: " << (*mSize);

    //диапазон значений
    cout << "\n\tЗадайте диапазон:\n";
    cout << "Нижняя граница: "; cin >> min;
    cout << "Верхняя граница: "; cin >> max;
    OutFile << "\nДиапазон значений: от " << min << " до " << max;

    //совпадающие элементы
    do
    {
        cout << "\n\tДолжен ли массив иметь совпадающие элементы? Да(Y)/Нет(N) ";
        cin >> sw;
        if (isupper(sw)==1)
            sw=_tolower(sw);
        switch (sw)
        {
            case ('y'): cout << "Выберите долю совпадающих элементов: (в процентах) ";
                        //cin >> percent;
                        cin >> percentTemp;
                        OutFile << "\nСовпадающие значения элементов: наличие";
                        OutFile << "\nПроцент совпадающих элементов: " << percentTemp;

                        percentTemp = (*mSize)*percentTemp/100;
                        percentTemp = ceil (percentTemp); //округляем "вверх"
                        //если задан хоть один процент, то по алгоритму совпадение будет
                        percent = percentTemp;
                        if (percent == 1)
                            percent++;

                        //cout << "\nВ массиве будет " << percent << " одинаковых элементов.";
                        OutFile << "\nКоличество совпадающих элементов: " << percent;
                        break;

            case ('n'): percent = 0;
                        OutFile << "\nСовпадающие значения элементов: отсутствие";
                        break;

            default:    cout << "\nНет такого ответа! Попробуйте снова!\n\n";
                        break;
        }
    }
    while (sw!='y' && sw!='n');

    //генерация
    srand(time(NULL)); //устанавливаем нач. значение генератора
    for (i=0; i < *mSize; i++)
    {
        do
        {
            control = true;

            mTemp[i] = min + (YourType)rand()/((YourType)RAND_MAX/(max-min+1));
            //cout << "\nm[" << i << "] = " << mTemp[i] << " "; system ("pause");

            if (percent == 0) //не должно быть совпадений!
            {
                for (j=0; j<i; j++)
                    if (mTemp[j] == mTemp[i])
                        control = false; //генерируем новый!
            }
            else //совпадение?
            {
                for (j=0; j<i; j++)
                    if (mTemp[j] == mTemp[i])
                    {//нужно проверить, который раз совпадает?
                        control = true;
                        //true - то это первое совпадение и надо получить percent=percent-2
                        //false - то это не первое совпадение и надо получить percent=percent-1
                        for (j++; j<i; j++)
                            if (mTemp[j] == mTemp[i]) //непервое совпадение?
                            {
                                percent = percent - 1;
                                j=i;
                                control = false;
                            }
                        if (control == true) //первое совпадение?
                        {
                            if (percent-2 >= 0) //условие нам позволяет ввести этот элемент?
                                percent = percent - 2;
                            else //если нет, то генерируем новый!
                                control = false;
                        }
                        else //непервое совпадение. устанавливаем control = true для выхода из цикла
                            control = true;
                    }
                    //else //новый уникальный элемент
            }
        }
        while (control != true);
    }

    if (percent>0) //недостаточная доля совпадений?
    {
        if (percent == 1) //выбираем уже имеющийся
        {
            for (i=0, control = false; control == false; i++)//определяем элемент для копирования (дожен быть повторяющимся)
            {
                for (j=i+1; j<(*mSize) && control == false; j++)
                    if (mTemp[j] == mTemp[i]) //i совпадает?
                        control = true;
            }
            only = i-1;
            for (i=only+1, control = true; percent>0; i++, control = true)
            {
            //вставляем элемент m[only] только вместо единственных элементов!
                for (j=i+1; j<(*mSize) && control == true; j++)
                    if (mTemp[j] == mTemp[i] && mTemp[j] == mTemp[only])
                        control = false; //элемент не единственный

                if (control == true) //если элемент единственный
                {
                    mTemp[i] = mTemp[only];
                    percent--;
                }
            }
        }
        else //выбираем уникальный элемент и копируем его вместо других уникальны элементов необходимое количество раз
        {
            for (i=0, control = true; control == false; i++, control = true)//определяем элемент для копирования (дожен быть единственным)
            {
                for (j=i+1; j<(*mSize) && control == true; j++)
                    if (mTemp[j] == mTemp[i])
                        control = false; //i не единственный
            }//на выходе из цикла знаем, что (i-1)-ый элемент единственный в массиве
            only = i;
            percent--; //так как при первой вставке необходимо percent=percent-2;
            for (i=only+1, control = true; percent>0; i++, control = true) //вставляем, пока надо вставлять))
            {
            //вставляем элемент m[only] только вместо единственных элементов!
                for (j=i+1; j<(*mSize) && control == true; j++)
                    if (mTemp[j] == mTemp[i])
                        control = false; //элемент не единственный

                if (control == true)
                {
                    mTemp[i] = mTemp[only];
                    percent--;
                }
            }
        }
    }

    //упорядоченность
    do
    {
        cout << "\n\tУпорядочить массив? Да(Y)/Нет(N)";
        cin >> sw;
        if (isupper(sw)==1)
            sw=_tolower(sw);
        switch (sw)
        {
            case ('y'): OutFile << "\nУпорядоченность: да";
                        cout << "\nУпорядочить по убыванию (D) или возврастанию (U)? ";
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
                                            OutFile << ", прямая";
                                            break;

                                case ('d'): for (i=0; i<(*mSize-1); i++)
                                                for (j=0; j<(*mSize-1); j++)
                                                    if (mTemp[j+1] > mTemp[j])
                                                    {
                                                        elTemp = mTemp[j+1];
                                                        mTemp[j+1] = mTemp[j];
                                                        mTemp[j] = elTemp;
                                                    }
                                            OutFile << ", обратная";
                                            break;

                                default:    cout << "\nНет такого ответа! Попробуйте снова!\n\n";
                                            system ("pause");
                                            break;
                            }
                        }
                        while (sw!='u' && sw!='d');

                        sw='y';
                        break;

            case ('n'): OutFile << "\nУпорядоченность: нет";
                        system ("pause");
                        break;

            default:    cout << "\nНет такого ответа! Попробуйте снова!\n\n";
                        system ("pause");
                        break;

        }
    }
    while (sw!='y' && sw!='n');

    OutFile.close();
    return (mTemp);
}

//функция вывода на экран
template <class YourType> void Print (YourType *m, unsigned int mSize)
{
    ofstream OutFile ("Generation.txt", ios::app);

    //system ("cls");
    cout << "\n";
    OutFile << "\n\tСгенерированный массив:";
    cout << "Сгенерированный массив: ";
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

    unsigned int mSize; //размер массива m
    char typeSelect; //переменная выбора типа
    ofstream OutFile ("Generation.txt"); //сохраним выбранные настройки генерации и полученный массив
    OutFile << "\tУсловия генерации:";

    do
    {
        cout << "\tВыберите тип элементов массива:";
        cout << "\nInteger (i)";
        cout << "\nFloat (f)";
        cout << "\nDouble (d)\n";
        //more types??
        cin >> typeSelect;
        if (isupper(typeSelect)==1)
            typeSelect=_tolower(typeSelect);
        switch(typeSelect)
        {
            case ('i'): {int *m; //определяем целочисленный массив
                        OutFile << "\nТип элементов массива: integer";
                        OutFile.close();
                        m = RandomGeneration <int> (&mSize);
                        Print <int> (m, mSize);
                        delete [] m;
                        break;}

            case ('f'): {float *m; //определяем массив элементов с плавающей точкой
                        OutFile << "\nТип элементов массива: float";
                        OutFile.close();
                        m = RandomGeneration <float> (&mSize);
                        Print <float> (m, mSize);
                        delete [] m;
                        break;}

            case ('d'): {double *m; //определяем массив элементов с плавающей точкой
                        OutFile << "\nТип элементов массива: double";
                        OutFile.close();
                        m = RandomGeneration <double> (&mSize);
                        Print <double> (m, mSize);
                        delete [] m;
                        break;}

            default:    cout << "\nНет такого типа! Попробуйте снова!\n\n";
                        system ("pause");
                        break;
        }

    }
    while (typeSelect!='i' && typeSelect!='f' && typeSelect!='d');
}
