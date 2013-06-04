// tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "main.cpp"

class MySolve : public ::testing::Test {
};

TEST_F(MySolve, uTest) 
{
    char alph[34];
	int m;
	

	//TEST 1
	char A1[]="asdfg",B1[]="aasdff";
	strcpy(alph,AnalyseB(B1));
	m=strlen(B1)-strlen(A1); 
	m=abs(m);
	m+=strlen(B1);		
	Solve(A1,B1,alph,0,&m);
	ASSERT_TRUE(m == 2);

	//TEST 2
	char A2[]="bzwerth",B2[]="bzurt";
	strcpy(alph,AnalyseB(B2));
	m=strlen(B2)-strlen(A2); 
	m=abs(m);
	m+=strlen(B2);		
	Solve(A2,B2,alph,0,&m);
	ASSERT_TRUE(m == 3);
}

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

