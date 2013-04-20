#include "stdafx.h"
#include "gtest/gtest.h"
#include <conio.h>
#include "../lr_2/lr_2.h"
using namespace std;

//-------------------------------------------------------------
class Test : public ::testing::Test 
{};

//-------------------------------------------------------------
TEST_F(Test, Sort)
{
	int field[max_side][max_side]; // Объявление поля
	// Обнуление поля
	for (int i = 0; i < max_side; i ++)
		for (int j = 0; j < max_side; j ++)
			field[i][j] = 0;
	
	//Test #1
	ASSERT_TRUE (amount_position (field, 4, 4) == 260);

	//Test #2
	ASSERT_TRUE (amount_position (field, 8, 4) == 242856);
	
	//Test #3
	ASSERT_TRUE (amount_position (field, 2, 2) == 4);
	
	//Test #4
	ASSERT_TRUE (amount_position (field, 4, 1) == 16);
	
	//Test #5
	ASSERT_TRUE (amount_position (field, 1, 1) == 1);
}

//-------------------------------------------------------------
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	_getch();
	return 1;
}
