#include <iostream>
#include <math.h>

using namespace std;
bool see_all(bool see[], int n)	//Функция проверяющая все ли люди использовались в соревновании
{		//Если использовались все участникивернуть true, иначе false
	for (int i = 0; i < n; i++)
	{
		if (see[i] != true)
			return false;
	}
	return true;
}

int BackTracking(int &CommandA, int &CommandB, int Quant, int PartMass[], bool k, bool see[], int a, int b, int count, int &monte_carlo)
{				//окончательный вес первой команды, второй команды, количество учавствующих людей, веса этих людей, параметр показывающий в какую команду нужно добавить людей
				//массив, определяющий использовался ли человек в соревновании или нет, вес одной команды, второй команды, разница между количеством людей в командах
	int p = 0;	//параметр определяющий какой человек используеться на данном шаге перебора
	++monte_carlo;
	for (int i = 0; i < Quant; i++)	//Пока не найдем неиспользованного участника
	{
		if (see[i] != true)	//Если участник не использован, то
		{		//запишем его к одной из команд(определяеться параметром k)
			if (k == true)
			{
				count++;
				a += PartMass[i];
			}
			else
			{
				count--;
				b += PartMass[i];
			}
			see[i] = true;	//отметим то, что i участник использовался 
			p = i;
			break;
		}
	}

	if (see_all(see, Quant))		//Если использованы все участники
	{
		if ((abs(a-b) < abs(CommandA - CommandB)) && ((count >=-1) && (count <=1)))	
		{	//Проверяем на то, что разность весов в командах меньше существующей и то, что разница людей в команде не больше одного 
			CommandA = a;		//Если да то фиксируем решение
			CommandB = b;
			if (CommandA - CommandB == 0)		//Если разница весов 0, то решение оптимально и выходим
				return 1;
		}
	}
	else	//Если не использованы все участники, то запускаем перебор заново
	{
		int ret = BackTracking(CommandA, CommandB, Quant, PartMass, true, see, a, b, count, monte_carlo);	//запускаем перебор рекурсивно (добавляем в первую команду)
		see[++p] = false;	//участник использовавшийся в последнем переборе используеться заново, а его вес не учитываться
		if (ret == 1)		//Если разница между весами команд 0, то выход
			return 1;
		ret = BackTracking(CommandA, CommandB, Quant, PartMass, false, see, a, b, count, monte_carlo);		//запускаем перебор рекурсивно (добавляем во вторую команду)
		see[p] = false;		//участник использовавшийся в последнем переборе используеться заново, а его вес не учитываться
		if (ret == 1)		//Если разница между весами команд 0, то выход
			return 1;
	}
	return 0;
}

int Monte_Carlo(int n)
{
	int quant = 0;
	int k = n;
	while (n)
	{
		int add = 1;
		for (int i = k; i >= n; i--)
		{
			add *=i;
		}
		quant += add;
		--n;
	}
	return quant;
}

int main()
{
	//Ввод данных
	int TestQuan = 0;
	cin>>TestQuan;	//Количество тестовых задач

	int *PartQuan = new int[TestQuan];		//Количество учасников в тестовой задаче
	int **PartMass = new int*[TestQuan];	//Массы участников в тестовой задаче
	for (int i = 0; i < TestQuan; i++)
	{
		cin>>PartQuan[i];					//Ввод количества участников в i задаче
		PartMass[i] = new int[PartQuan[i]];
		for (int k = 0; k < PartQuan[i]; k++)	//Ввод масс участников в i задаче
		{
			cin>>PartMass[i][k];
			if ((PartMass[i][k] > 400) || (PartMass[i][k] < 1))	//Если вес больше 400 или меньше 1, 
			{														//то вес вводиться заново
				cout<<"Input weight again\n";
				--k;
			}
		}
	}

	//Решение задачи
	int *CommandA = new int[TestQuan];		//Вес первой стороны в каждой тестовой задаче
	int *CommandB = new int[TestQuan];		//Вес второй стороны в каждой тестовой задаче

	for (int i = 0; i < TestQuan; i++)		//Применим backtracking столько раз,
	{										//сколько у нас тестоых задач
		CommandA[i] = INT_MAX;				//Сделаем так что бы разность между командами
		CommandB[i] = 0;					//в начале была максимальной
		int count = 0;
		bool *see = new bool[PartQuan[i]];	//Отображает использовался ли человек в соревновании или нет
		for (int k = 0; k < PartQuan[i]; k++)	//Вначале никто из людей не используеться в соревновании
		{
			see[k] = false;
		}
		BackTracking(CommandA[i], CommandB[i], PartQuan[i], PartMass[i], true, see, 0, 0, 0, count);	//Запустим перебор
		cout<<CommandA[i]<<" "<<CommandB[i]<<endl;		//Выведем результат веса с одной стороны и со второй.
		cout<<count<<endl; //Сложность выполнения. Количество исследуемых узлов.
		cout<<Monte_Carlo(PartQuan[i])<<endl;		//Всего узлов.
	}

	return 0;
}