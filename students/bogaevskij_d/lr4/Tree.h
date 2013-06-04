#ifndef _Tree
#define _Tree
#include <iostream>
#include <ctime>
#include "paa_lr4.h"
#include "Root.h"
#include "Counter.h"
class Tree {
	private:
		int matr[500][500]; //матрица цен
		int n; //размер матрицы
		Root *head; //голова дерева
		Root *cur; //указатель на элемент
		int head_num; //начальна€ вершина
	public:
		Counter T; //счетчик
		Tree(){};
		Root *get_head(){return head;}
		void input_matr(void);   //ввод матрицы цен
		void print_matr(void);
		void input_head_num(void); //ввод начальной вершины
		void set_size(int n){this->n=n;}
		void find(Root *hd, int numb); //находит элемент с заданным номером
		void print(Root *hd);  //вывод дерева на экран
		void create_tree(void);
		void print_cost(Root *hd);
		void free_mem(Root *hd);
		void generate_matr(int mode);
	};
void Tree::input_matr(void) //откорректировать ввод
{
	std::cout << "¬ведите количество вершин графа.\n";
	std::cin >> n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j) 
			{
				matr[i][j]=-1;
			}
			if(i!=j)
			{
				if(i<j)
				{
					std::cout << "¬ведите цену дл€ перехода из " << i << " в " << j << "     "; //+1 дл€ нумерации с 1
					std::cin >> matr[i][j];
				}
				else
				{
					matr[i][j]=matr[j][i];
				}
			}
		}
	}
}
void Tree::print_matr(void)
{
	printf(" ");
	for(int i=0; i<n; i++)
		printf("%6d",i);
	printf("\n\n");
	for(int i=0;i<n;i++)
	{
		printf("%d",i);
		for(int j=0;j<n;j++)
		{
			printf("%6d",matr[i][j]);
		}
		std::cout << std::endl;
	}
}
void Tree::input_head_num(void)
{
	std::cout << "\n¬ведите начальную вершину дл€ заданной матрицы\n";
	std::cin >> head_num;
}
void Tree::find(Root *hd, int numb)
{
	if(hd->get_number()==numb) cur=hd;
	for(int i=0;i<hd->get_branches();i++)
	{
		find(hd->get_son(i), numb);
	}
}
void Tree::print(Root *hd)
{
	std::cout << "(";
	std::cout << hd->get_number();
	for(int i=0; i<hd->get_branches();i++)
		print(hd->get_son(i));
	std::cout << ")";
}
void Tree::create_tree(void)
{
	int was_here[500]; was_here[0]=-1;
	Root *added;
	head=new Root;     //строим вершину
	head->set(head_num);   //называем ее
	int *slv;
	add_in_mass(was_here,head_num);  //добавл€ем ее в массив посещенных
	T.on();
	for(int i=0;i<n-1;i++)      //строим n-1 ребро
	{
		slv=f_min(matr,was_here,n,&T);    //находим минимальное ребро, не образующее циклов и исход€щее из узла дерева
		add_in_mass(was_here,slv[1]);    //добавл€ем новую вершину в массив посещенных
		find(head,slv[0]); //cur указывает на искомого сына
		added=new Root;  //строим вершину
		added->set(slv[1]); //называем сына
		cur->add_son(added,matr[slv[0]][slv[1]]); //добавл€ем сына
		delete [] slv;
	}
	T.off();
}
void Tree::print_cost(Root *hd)
{
	for(int i=0;i<hd->get_branches();i++)
	{
		std::cout << hd->get_number() << " -> " << (hd->get_son(i))->get_number() << " :   " << hd->get_cost(i) << std::endl;
		print_cost(hd->get_son(i));
	}
}
void Tree::free_mem(Root *hd)
{
	for(int i=0; i<hd->get_branches();i++)
		free_mem(hd->get_son(i));
	delete hd;
}
void Tree::generate_matr(int mode)
{
	if(mode>50) return;
	srand(time(NULL));
	//n=rand()%10+3;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j) 
			{
				matr[i][j]=-1;
			}
			if(i!=j)
			{
				matr[i][j]=rand()%100+1;
				if(matr[i][j]+mode>100)
				{
					matr[i][j]=-1;
				}
			}
		}
	}
	head_num=rand()%n;
}
#endif