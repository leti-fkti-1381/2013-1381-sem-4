#include <iostream>

#include "Tree.h"

using namespace std;

int main(void)
{
	setlocale(0,"Rus");
	Tree tst;
	int n,m;

	cout << "� ������ ������������ ������ ����� ����������\n�������� ���������� ������ �� ������\n";
	cout << "������� ���������� ������ �����\n";
	cin >> n;
	tst.set_size(n);
	cout << "������� ������������ ����� �������(�� 0 �� 50)\n50 - �� ����������, 0 - ����������\n";
	cin >> m;
	if(m<0 || m>50) return 1;
	tst.generate_matr(m);  //��������� ����� 
	tst.create_tree();
	cout << "\n���������� ���������:" << tst.T.get_number() << endl;
#ifdef debug
	tst.print(tst.get_head());
#endif
	tst.free_mem(tst.get_head());
	cout << endl;
		
	cout << "\n������� ������������ ����� �������(�� 0 �� 50)\n50 - �� ����������, 0 - ����������\n";
	cin >> m;
	if(m<0 || m>50) return 1;
	tst.generate_matr(m);  //��������� ����� 
	tst.create_tree();
	cout << "\n���������� ���������:" << tst.T.get_number() << endl;
#ifdef debug
	tst.print(tst.get_head());
#endif
	tst.free_mem(tst.get_head());
	cout << endl;
	
	system("pause");
	return 1;
}
