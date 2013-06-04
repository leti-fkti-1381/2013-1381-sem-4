#include <gtest\gtest.h>
#include <conio.h>
#include "Shellsort.h"

class Testing : public ::testing::Test {
};


void TrueSort(int *a, int n)
{
	for(int i=0;i<n-1;i++)
		ASSERT_LE(a[i], a[i+1]);
}

TEST_F(Testing, shellSort) 
{
	int *result = new int[10];
	for(int i=0;i<10;i++)
		result[i] = 10-i;
	int i = 0;
	shellSort(result, 10, i);
	TrueSort(result,10);
	delete result;
	}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
   	RUN_ALL_TESTS();
   _getch();
   return 1;
}