#pragma once
#include "linked_list.h"

//------------------------------------------------
// primitives:

TEST(linked_list_p, initialisation)
{
	linked_list<> a;
	linked_list<int> b{ 100, 200, 300, 400, 500 };
	char text[6] = "hello";
	linked_list<char> c(text, 6);
	linked_list<char> d(c);
	linked_list<char> e(linked_list<char>(d));
}

TEST(linked_list_p, insert)
{
	linked_list<> numbers{ 100, 200, 300, 400, 500 };
	
	numbers.insert(50, 0);
	EXPECT_EQ(numbers[0], 50);
	numbers.insert(60, 1);
	EXPECT_EQ(numbers[1], 60);
	
	numbers.insert(350, 4);
	EXPECT_EQ(numbers[4], 350);

	numbers.insert(600, 7);
	EXPECT_EQ(numbers[7], 600);
}

TEST(linked_list_p, remove)
{
	linked_list<> numbers{ 100, 200, 300, 400, 500 };
	EXPECT_THROW(numbers[5], int);
	numbers.insert(50, 0);
	EXPECT_EQ(numbers[0], 50);
	numbers.insert(60, 1);
	EXPECT_EQ(numbers[1], 60);

	numbers.insert(350, 4);
	EXPECT_EQ(numbers[4], 350);

	numbers.insert(600, 7);
	EXPECT_EQ(numbers[7], 600);
}

TEST(linked_list_p, constant_methods)
{
	linked_list<int> b{ 100, 200, 300, 400, 500 };
	EXPECT_NO_THROW(b[4], int);
	EXPECT_EQ(b[4], 500);
	b[4] = 600;
	EXPECT_EQ(b[4], 600);
}

TEST(linked_list_p, error)
{
	



}
