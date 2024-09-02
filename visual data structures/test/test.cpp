#include "pch.h"
#include "bureaucracy.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "array_tests.h"
#include "linked_list_tests.h"
#include "adaptor_tests.h"
#include "avl_tests.h"

int main(int argc, char** argv)
{
    //if (argc != 2)
        //fatal_error("the driver takes one argument");
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = strcat(argv[1], "*");
    ::testing::GTEST_FLAG(filter) = "adapt*queue*";

    int exit_status = RUN_ALL_TESTS();

    log_file.clear();
    log_file.close();
    return EXIT_SUCCESS;
}
