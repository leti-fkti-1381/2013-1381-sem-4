// paa_lr1_utest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "lr1.h"
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

TEST_F(Numbers, Sortirovka) 
{
	int *result,sravn=-3200;
	//test 1
	int mass1[7]={4,-8,21,11,7,-20,-45};
	result=Merge(mass1,7,&sravn);
	ChSort(result,7);
	delete result;
	//test1 end

	//test 2
	int mass2[8]={-37,-92,52,-58,32,-85,-86,-45};
	result=Merge(mass2,8,&sravn);
	ChSort(result,8);
	delete result;
	//test2 end

	//test 3
	int mass3[7]={-77,-37,49,-59,28,70,-43};
	result=Merge(mass3,7,&sravn);
	ChSort(result,7);
	delete result;
	//test3 end

	//test 4
	int mass4[11]={-74,-88,-55,4,-57,-3,69,91,41,65,13};
	result=Merge(mass4,11,&sravn);
	ChSort(result,11);
	delete result;
	//test4 end

	//test 5
	int mass5[13]={-70,60,9,99,57,-44,-18,-37,-15,-83,65,55,12};
	result=Merge(mass5,13,&sravn);
	ChSort(result,13);
	delete result;
	//test5 end

	//test 6
	int mass6[14]={-64,-11,-30,58,-82,9,39,-91,40,-11,-30,-57,-78,33};
	result=Merge(mass6,14,&sravn);
	ChSort(result,14);
	delete result;
	//test6 end

	//test 7
	int mass7[16]={-61,-63,66,-47,33,-64,-49,-18,-49,41,22,-13,93,11,-84,-34};
	result=Merge(mass7,16,&sravn);
	ChSort(result,16);
	delete result;
	//test7 end

	//test 8
	int mass8[19]={-51,15,-78,7,9,-84,88,0,-50,-3,-22,-81,-27,82,-44,44,-66,-93,-73};
	result=Merge(mass8,19,&sravn);
	ChSort(result,19);
	delete result;
	//test8 end

	//test 9
	int mass9[23]={-44,-57,83,-2,70,2,-87,-87,5,69,82,7,83,7,-27,-47,2,-11,-11,11,-52,-34,-34};
	result=Merge(mass9,23,&sravn);
	ChSort(result,23);
	delete result;
	//test9 end
}

int _tmain(int argc, _TCHAR* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
   	RUN_ALL_TESTS();
   _getch();
   return 1;
}

