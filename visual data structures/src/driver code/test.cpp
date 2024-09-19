#include "pch.h"
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>

using testing::InitGoogleTest;
using testing::Test;

#include "../../test/array_tests.h"
#include "../../test/linked_list_tests.h"
#include "../../test/adaptor_tests.h"
#include "../../test/avl_tests.h"
#include "../../test/maxheap_tests.h"

//#include <GLFW/glfw3.h>
//void start_visual();

int main(int argc, char* argv[])
{
    //if (argc != 2)
        //fatal_error("the driver takes one argument.\n");
    system("cls");
    
    //testing::GTEST_FLAG(filter) = argv[1];
    testing::GTEST_FLAG(filter) = "*avl*";

    InitGoogleTest(&argc, argv);
    int exit_status = RUN_ALL_TESTS();
    
    log_file.clear();
    log_file.close();
    
    using namespace std::this_thread;
    sleep_for(std::chrono::seconds(2));

    //start_visual();
    return exit_status;
}
