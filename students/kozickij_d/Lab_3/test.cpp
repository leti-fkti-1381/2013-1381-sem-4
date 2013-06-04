#include "stdafx.h"
#include "polindrome.h"
#include <conio.h>
#include "gtest\gtest.h"
#include <iostream>
#include <string.h>

class num : public ::testing::Test {
};
void Mas(int result, int n)
{   
		ASSERT_EQ(result, n);
}

TEST_F(num,polindrome) 
{
	//test 1
	int result;
	string str1="1221";
	Polindrome polindrome;
	result=polindrome.FindSolution_2(str1,4);
	Mas(result,0);
	//test 1 end
}

int _tmain(int argc, _TCHAR* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
   	RUN_ALL_TESTS();
   _getch();
   return 1;
}

