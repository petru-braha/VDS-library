#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>

#include "array_tests.h"
#include "linked_list_tests.h"
// more directives


int main(int argc, char** argv)
{
	//if (argc != 2)
		//fatal_error("the driver takes one argument");
	::testing::InitGoogleTest(&argc, argv);
	char temp[199] = "linked_list";
	::testing::GTEST_FLAG(filter) = strcat(temp, "*");

	int exit_status = RUN_ALL_TESTS();

	// don't forget about visual!!!!
	// maybe lauch into execution another compiler visual cpp
	
	return exit_status;
}
