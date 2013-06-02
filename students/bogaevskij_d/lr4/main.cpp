#include <iostream>

#include "Tree.h"

using namespace std;

int main(void)
{
	setlocale(0,"Rus");
	Tree tst;
	int n,m;

	cout << "В данной лабораторной работе будет исследован\nалгоритм ближайшего соседа на графах\n";
	cout << "Введите количество вершин графа\n";
	cin >> n;
	tst.set_size(n);
	cout << "Введите насыщенность графа первого(от 0 до 50)\n50 - не насыщенный, 0 - насыщенный\n";
	cin >> m;
	if(m<0 || m>50) return 1;
	tst.generate_matr(m);  //генерация графа 
	tst.create_tree();
	cout << "\nКоличество сравнений:" << tst.T.get_number() << endl;
#ifdef debug
	tst.print(tst.get_head());
#endif
	tst.free_mem(tst.get_head());
	cout << endl;
		
	cout << "\nВведите насыщенность графа второго(от 0 до 50)\n50 - не насыщенный, 0 - насыщенный\n";
	cin >> m;
	if(m<0 || m>50) return 1;
	tst.generate_matr(m);  //генерация графа 
	tst.create_tree();
	cout << "\nКоличество сравнений:" << tst.T.get_number() << endl;
#ifdef debug
	tst.print(tst.get_head());
#endif
	tst.free_mem(tst.get_head());
	cout << endl;
	
	system("pause");
	return 1;
}
