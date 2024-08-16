#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>

#include "array_tests.h"
#include "linked_list_tests.h"
#include "avl_tests.h"

int main(int argc, char** argv)
{
	//if (argc != 2)
		//fatal_error("the driver takes one argument");
	::testing::InitGoogleTest(&argc, argv);
	//::testing::GTEST_FLAG(filter) = strcat(argv[1], "*");
	::testing::GTEST_FLAG(filter) = "linked_list*";

	int exit_status = RUN_ALL_TESTS();

	// don't forget about visual!!!!
	// maybe lauch into execution another compiler visual cpp
	
	return exit_status;
}
