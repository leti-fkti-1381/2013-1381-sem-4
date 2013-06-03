#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>


using namespace std;
const int MAXN = 100;
vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN],iter,timex;
int tab[100][100];

int rand (int tab[100][100], vector<int>g[MAXN])
{
	int n;
	cout << "Введите количество элементов в графе: ";
	cin >> n;
	
	srand(time(0));
	for (int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			tab[i][j]=rand()%2;
	for (int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			tab[j][i]=tab[i][j];
			if(i==j) tab[i][j]=0;
			if(tab[i][j]==1)
			{
			g[i].push_back(j);
			g[j].push_back(i);
			}
		}
		return n;
}
 
void IS_BRIDGE(int a, int b)
{
	std::cout << "Ребро " << a << " - " << b << " является мостом!" << endl;
}


int dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i=0; i<g[v].size(); ++i)
	{   iter++;
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > tin[v])
				IS_BRIDGE(v,to);
			return iter;
		}
	}

}
 
void find_bridges(int n) {
	timer = 0;
	for (int i=0; i<n; ++i)
		used[i] = false;
	for (int i=0; i<n; ++i)
		if (!used[i])
			iter=iter + dfs (i);
}




int main()
{
setlocale(0,"rus");
int menu,n,i,j;
fstream fi;
cout << "1.Заполнение графа случайными числами.\n2.Заполнение графа из файла\n";
cin >> menu;
switch (menu){
			case 1: n = rand(tab,g);
					break;
			case 2:


fi.open("Графы.txt", ios::in);

fi >> n;
int j,i;
if (!fi)
{ cerr << "ошибка!\n"; 
	exit(1);
	std::system("pause");
}

for(i=0;i<n;i++){
for(j=0;j<n;j++)
{
fi>>tab[i][j];
if(tab[i][j]==1){
	 g[i].push_back(j);
	  g[j].push_back(i);
}
if (tab[i][j] !=1 && tab[i][j] !=0 )
{
std::cout << " Матрица введена некорректно\n";

fi.close();
system ("pause");
return 0;
} 
}
}
break;}
for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
cout << tab[i][j] << " ";
cout<<endl;
}
timex = clock();
find_bridges(n);
timex = clock() - timex;
cout << "Время выполнения " << (double)timex/CLOCKS_PER_SEC << " секунд " << endl;
cout << "Количество итераций " << iter << endl;
fi.close();
cout << endl;
system ("pause");
return 0;


}