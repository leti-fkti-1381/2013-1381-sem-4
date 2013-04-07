#include <gtest\gtest.h>
#include <conio.h>
#include "main.cpp"

class Testing : public ::testing::Test {
};


TEST_F(Testing, BackTracking) 
{
	int result[3];
	result[0] = 120;
	result[1] = 60;
	result[2] = 60;
	int CommandA = INT_MAX, CommandB = 0;
	bool see[3];
	for (int i = 0; i < 3; i++)
		see[i] = false;
	BackTracking(CommandA, CommandB, 3, result, true, see, 0, 0, 0, 0);
	ASSERT_EQ(CommandA, CommandB);
	
	
	result[1] = 70;
	for (int i = 0; i < 3; i++)
		see[i] = false;
	CommandA = INT_MAX; CommandB = 0;
	BackTracking(CommandA, CommandB, 3, result, true, see, 0, 0, 0, 0);
	ASSERT_EQ(abs(CommandA - CommandB), 10);
	delete result;
	}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
   	RUN_ALL_TESTS();
   _getch();
   return 1;
}