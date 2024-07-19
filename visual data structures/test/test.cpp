#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>

//#include "array_tests.h"
// #include "maxheap_tests.h"
// #include "linked_list_tests.h"
// #include "tree_tests.h"
// #include "avl_tests.h"
// #include "stack_tests.h"

TEST(aaad, ddd)
{
	EXPECT_EQ(0, 0);
}

TEST(aaad, dddds)
{
	EXPECT_EQ(0, 0);
}

TEST(aaaddd, ddd) {}

int main(int argc, char** argv)
{
	// execution direct from the terminal
	// data structure // 10 values + display construction


	// tests
	// after testing 
	// give the oportunity to insert delete and stop // 
	::testing::InitGoogleTest(&argc, argv);
	::testing::GTEST_FLAG(filter) = "aaadd*.ddd*";
	return RUN_ALL_TESTS();
}	