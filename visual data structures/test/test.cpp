#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>

#include "array_tests.h"


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	//::testing::GTEST_FLAG(filter) = "aaadd*.ddd*";
	return RUN_ALL_TESTS();
}	