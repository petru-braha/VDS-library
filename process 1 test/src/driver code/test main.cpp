#pragma warning (disable: 26495)
#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <process.h>

using testing::InitGoogleTest;
using testing::Test;

/*#include "../../test/array_tests.h"
#include "../../test/linked_list_tests.h"
#include "../../test/adaptor_tests.h"
#include "../../test/avl_tests.h"
#include "../../test/maxheap_tests.h"
*/
int main(int argc, char* argv[])
{
    //if (argc != 2)
        //fatal_error("the driver takes one argument.\n");
    system("cls");
    
    testing::GTEST_FLAG(filter) = "zzzz";

    InitGoogleTest(&argc, argv);
    int tests_status = RUN_ALL_TESTS();
    
    //log_file.clear();
    //log_file.close();
    
    using namespace std::this_thread;
    sleep_for(std::chrono::seconds(2));

    if (tests_status)
    {
        std::cout << "error - tests execution failed.\n";
        return EXIT_FAILURE;
    }

    //_execl("x64/Debug/visual data structures.exe", "head_argument", argument, NULL);
    printf("lauching the GUI failed.\n");
    return EXIT_FAILURE;
}
