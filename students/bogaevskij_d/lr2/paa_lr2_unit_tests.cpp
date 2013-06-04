// paa_lr2_unit_tests.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include "paa_lr2_0.h"
#include "gtest/gtest.h"

class Posledovat : public ::testing::Test {
};

void auto_in(Mark **a,int n, int m, int *in)
{
	Mark *base;
	n++;
	base=new Mark [n];
	//ƒобавл€ем пустую марку
	base[0].cost=0;
	base[0].number=0;
	for(int i=1;i<n;i++)
	{
		base[i].number=i;
		base[i].cost=in[i-1];
	}
	
	int p=pow((double)n,m);
	Mark res[20];
	Mark **result;
	int stat=0;
	Solve1(a,res,base,0,m,n,&stat);
}

TEST_F(Posledovat, Posledovatelnost) 
{
    int n,m,*in,p,res;
	Mark **a;
	a=new Mark* [20000];
	for(int i=0;i<20000;i++)
		*(a+i)=new Mark [20];

	n=3;
	m=4;
	in=new int [n];
	in[0]=1; in[1]=2; in[2]=3;
	auto_in(a,n,m,in);
	n++;
	p=pow((double)n,m);
	ASSERT_EQ(12,Posl1(a,m,p));
	delete [] in;
	
	n=4; 
	m=5;
	in=new int [n];
	in[0]=1; in[1]=4; in[2]=12; in[3]=21;
	auto_in(a,n,m,in);
	n++;
	p=pow((double)n,m);
	ASSERT_EQ(71,Posl1(a,m,p));
	delete [] in;
	
	n=4; 
	m=5;
	in=new int [n];
	in[0]=1; in[1]=5; in[2]=12; in[3]=28;
	auto_in(a,n,m,in);
	n++;
	p=pow((double)n,m);
	ASSERT_EQ(71,Posl1(a,m,p));
	delete [] in;
}

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

