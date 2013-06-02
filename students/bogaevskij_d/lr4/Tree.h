#ifndef _Tree
#define _Tree
#include <iostream>
#include <ctime>
#include "paa_lr4.h"
#include "Root.h"
#include "Counter.h"
class Tree {
	private:
		int matr[500][500]; //������� ���
		int n; //������ �������
		Root *head; //������ ������
		Root *cur; //��������� �� �������
		int head_num; //��������� �������
	public:
		Counter T; //�������
		Tree(){};
		Root *get_head(){return head;}
		void input_matr(void);   //���� ������� ���
		void print_matr(void);
		void input_head_num(void); //���� ��������� �������
		void set_size(int n){this->n=n;}
		void find(Root *hd, int numb); //������� ������� � �������� �������
		void print(Root *hd);  //����� ������ �� �����
		void create_tree(void);
		void print_cost(Root *hd);
		void free_mem(Root *hd);
		void generate_matr(int mode);
	};
void Tree::input_matr(void) //���������������� ����
{
	std::cout << "������� ���������� ������ �����.\n";
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
					std::cout << "������� ���� ��� �������� �� " << i << " � " << j << "     "; //+1 ��� ��������� � 1
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
	std::cout << "\n������� ��������� ������� ��� �������� �������\n";
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
	head=new Root;     //������ �������
	head->set(head_num);   //�������� ��
	int *slv;
	add_in_mass(was_here,head_num);  //��������� �� � ������ ����������
	T.on();
	for(int i=0;i<n-1;i++)      //������ n-1 �����
	{
		slv=f_min(matr,was_here,n,&T);    //������� ����������� �����, �� ���������� ������ � ��������� �� ���� ������
		add_in_mass(was_here,slv[1]);    //��������� ����� ������� � ������ ����������
		find(head,slv[0]); //cur ��������� �� �������� ����
		added=new Root;  //������ �������
		added->set(slv[1]); //�������� ����
		cur->add_son(added,matr[slv[0]][slv[1]]); //��������� ����
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