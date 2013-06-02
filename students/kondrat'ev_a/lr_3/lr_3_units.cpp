#include "stdafx.h"
#include "gtest/gtest.h"
#include <vector>
#include <conio.h>
#include "lr_3.h"
using namespace std;

//-------------------------------------------------------------
class Test : public ::testing::Test {};

//-------------------------------------------------------------
TEST_F(Test, Sort)
{
    vector <int> arr;

	//Test #1
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);
	arr.push_back(5);
	ASSERT_TRUE (Solution (arr, 5) == 47);

	//Test #2
	arr.push_back(10);
	arr.push_back(23);
	arr.push_back(9);
	arr.push_back(4);
	arr.push_back(8);
	arr.push_back(17);
	arr.push_back(2);
	arr.push_back(13);
	arr.push_back(8);
	arr.push_back(5);
	ASSERT_TRUE (Solution (arr, 10) == 979);
	
	//Test #3
	arr.push_back(3);
	arr.push_back(9);
	arr.push_back(6);
	arr.push_back(2);
	arr.push_back(5);
	arr.push_back(1);
	ASSERT_TRUE (Solution (arr, 5) == 125);
	
	//Test #4
	arr.push_back(5);
	ASSERT_TRUE (Solution (arr, 1) == -1);
	
	//Test #5
	arr.push_back(120);
	arr.push_back(5);
	arr.push_back(3);
	ASSERT_TRUE (Solution (arr, 3) == -1);
}

//-------------------------------------------------------------
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	_getch();
	return 1;
}
