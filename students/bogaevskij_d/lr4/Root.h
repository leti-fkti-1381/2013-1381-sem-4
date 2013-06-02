#ifndef _Root
#define _Root
//вершина графа
class Root {  
	private:
		int number; //имя
		int branches;  //кол-во сынов
		int cost[500]; //цена перехода к вершине, соответствующей указателю ниже или матрица смежности
		Root *sons[500]; //указатели на вершины
	public:
		Root();
		void set(int num);
		void add_son(Root *s, int c);
		int get_number(void);
		int get_branches(void);
		int get_cost(int n);
		Root *get_son(int n);
	};
Root::Root()
{
	branches=0;
}
void Root::set(int num)
{
	number=num;
}
void Root::add_son(Root *s, int c)
{
	sons[branches]=s;
	cost[branches]=c;
	branches++;
}
int Root::get_number(void)
{
	return number;
}
int Root::get_branches(void)
{
	return branches;
}
Root *Root::get_son(int n)
{
	return sons[n];
}
int Root::get_cost(int n)
{
	return cost[n];
}
#endif