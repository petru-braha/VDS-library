#include "pch.h"
#include "bureaucracy.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "array_tests.h"
#include "linked_list_tests.h"
#include "adaptor_tests.h"
#include "avl_tests.h"

void start_visual();

int main(int argc, char** argv)
{
    //if (argc != 2)
        //fatal_error("the driver takes one argument");
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = strcat(argv[1], "*");
    ::testing::GTEST_FLAG(filter) = "avl*";
    
    start_visual();
        
    int exit_status = 0;//RUN_ALL_TESTS();

    log_file.clear();
    log_file.close();
    return exit_status;
}
