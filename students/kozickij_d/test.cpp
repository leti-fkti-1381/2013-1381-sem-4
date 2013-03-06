#include "stdafx.h"
#include "Ырср 1.h"
#include <conio.h>
#include "gtest\gtest.h"
#include <iostream>

class Numbers : public ::testing::Test {
};

void ChSort(int *a, int n)
{
	for(int i=0;i<n-1;i++)
		ASSERT_LE(a[i], a[i+1]);
}

TEST_F(Numbers, sort) 
{
	//int *result;
	//test 1
	int i,*result;
	int mass1[2]={0,2};
	Massiv massiv(mass1,2,2);
	result=massiv.sort();
	ChSort(result,2);
	delete result;
	//test1 end

	}

int _tmain(int argc, _TCHAR* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
   	RUN_ALL_TESTS();
   _getch();
   return 1;
}

