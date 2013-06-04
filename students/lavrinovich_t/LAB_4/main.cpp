#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <omp.h>
#include <iostream>
#include <Windows.h>
using namespace std;

typedef vector<int> VInt;
typedef vector<VInt> VVInt;
typedef VInt::iterator VIter;
typedef pair<int, int> PInt;
typedef vector<PInt> VPInt;
typedef vector<VPInt> VVPInt;
typedef VPInt::iterator VPIter;


class Grath {
private:
	VVInt graph;
	VInt vrem, parents, enter, low, bcc;
	int myTime;
	int newIndex;
	int Cout_iter;
public:
	Grath(){myTime=0;newIndex=0;Cout_iter=0;}
	void visitLow(int u);
	void visitBCC(int u);
	int getBCC(int u, int v);
	void job();
};




/*
 * Поиск в глубину, выполняющий вычисление enter и low
 */
void Grath::visitLow(int u) {
   vrem[u] = 1;
   low[u] = enter[u] = ++myTime;
   Cout_iter++;
   for(VIter it = graph[u].begin(); it != graph[u].end(); it++)
      if(vrem[*it] == 0) 
	  {
         parents[*it] = u;
         visitLow(*it);
         low[u] = min(low[u], low[*it]);
		 Cout_iter++;
      } 
	  else 
	  {
		  if(vrem[*it] == 1 && *it != parents[u]) 
		  {
			low[u] = min(low[u], enter[*it]);
			Cout_iter++;
		  }
	  }
}

/*
 * Второй поиск в глубину, присвающий идентификаторы bcc
 */
void Grath::visitBCC(int u) {
   for(VIter it = graph[u].begin(); it != graph[u].end(); it++)
      if(parents[*it] == u) 
	  {
	   Cout_iter++;
			 if (low[*it] < enter[u])
				 bcc[*it] =  bcc[u]  ;       
			 else
                   if (low[*it] > enter[u])
					  bcc[*it] =  -1 ;
				   else
					  bcc[*it] = (newIndex++);                            
         visitBCC(*it);
      }
}

/*
  Получение номера BCC, которому принадлежит ребро.
 */
 int Grath::getBCC(int u, int v) {
	 Cout_iter++;
	 if (enter[u] > enter[v])
		 return bcc[u];
	 else
		 return bcc[v];
 }



void Grath::job() {
   int n, m, i;
   cout << "Введите количество вершин и количество рёбер:"<<endl;
   // Прочитаем граф
   scanf("%d%d", &n, &m);
   graph.resize(n);
   cout<< "Вводите рёбра:"<<endl;
   while(m--) {
      int from, to;
      scanf("%d%d", &from, &to);
      graph[from - 1].push_back(to - 1);
      graph[to - 1].push_back(from - 1);
   }

   // Запустим первый поиск (вычислим enter и low)
   vrem.assign(n, 0);
   parents.assign(n, -1);
   enter.resize(n);
   low.resize(n);

   double t1 = omp_get_wtime(); // системное время до выполнения функции

   for(i = 0; i < n; i++)
      if(vrem[i] == 0)
	  { Cout_iter++;
         visitLow(i);
	  }

   // Запустим второй поиск (определение идентификаторов bcc)
   // Второй поиск запускается "по следам" первого,
   // то есть проходит по уже найденному дереву
   bcc.assign(n, -1);
   for(i = 0; i < n; i++)
      if(parents[i] == -1)
	  {
		  Cout_iter++;
         visitBCC(i);
	  }
   // Выведем результат
   VVPInt comps(newIndex);
   for(i = 0; i < n; i++)
      for(VIter it = graph[i].begin(); it != graph[i].end(); it++)
         if(i < *it) 
		 {
		   Cout_iter++;
           int id = getBCC(i, *it);
           if (id != -1)
			    comps[id].push_back(PInt(i, *it));
         }
	double t2 = omp_get_wtime(); // время после выполнения функции
	bool z=false;
   for(i = 0; i < newIndex; i++) {
      printf("Компонент %d: ", i+1);
      for(VPIter edge = comps[i].begin(); edge != comps[i].end(); edge++)
	  {
         printf("(%d, %d) ", edge->first + 1, edge->second + 1);
		 z=true;
	  }
      printf("\n");
   }
   if (z==false)
	   cout<<"Нет компонентов!"<<endl;
  double time = t2 - t1;
  cout<<"Время выполнения: "<<time<<endl;
  cout<<"Количество базовых операций: "<<Cout_iter<<endl;
}



int main()
{
	   setlocale(LC_ALL,"Russian");
	   Grath g;
	   g.job();
	   system("PAUSE");
return 0;
}