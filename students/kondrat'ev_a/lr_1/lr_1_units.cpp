#include "stdafx.h"
#include "gtest/gtest.h"
#include <string>
#include <conio.h>
#include "../lr_1/lr_1.h"
using namespace std;

//-------------------------------------------------------------
class Test : public ::testing::Test 
{};

//-------------------------------------------------------------
TEST_F(Test, Sort)
{
    string str;

	//Test #1
	str = "21";
	sort (str, 0, str.size() - 1);
	ASSERT_TRUE (str == "12");

	//Test #2
	str = "73247";
	sort (str, 0, str.size() - 1);
	ASSERT_TRUE (str == "23477");
	
	//Test #3
	str = "asdfghjkl";
	sort (str, 0, str.size() - 1);
	ASSERT_TRUE (str == "adfghjkls");
	
	//Test #4
	str = "528ard";
	sort (str, 0, str.size() - 1);
	ASSERT_TRUE (str == "258adr");
	
	//Test #5
	str = "";
	sort (str, 0, str.size() - 1);
	ASSERT_TRUE (str == "");
	
	//Test #6
	str = "123456";
	sort (str, 0, str.size() - 1);
	ASSERT_TRUE (str == "123456");
	
	//Test #7
	str = "987654321";
	sort (str, 0, str.size() - 1);
	ASSERT_TRUE (str == "123456789");
}

//-------------------------------------------------------------
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	_getch();
	return 1;
}
