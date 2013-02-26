#include "sort.h"
#include "gtest/gtest.h"
#include<stdlib.h>
#include<time.h>
const int N=100000;

bool proverka( vector <T> a)
{
	for (unsigned int i=0;i<N-1;i++)
		if (a[i]>a[i+1]) return false;
	return true;
}

TEST(qsort,first)
{
	unsigned int i;
	Sortirovka ob;
	srand(time(0));
	int m;
	vector <T> mass;
	for (i=0; i<N; i++)
	{
		m=rand()%256;
		mass.push_back((char)m);
	}
	ob.qSortI(mass,N);
	EXPECT_TRUE(proverka(mass));
}