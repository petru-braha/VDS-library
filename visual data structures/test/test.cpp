#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>

int testing_glfw(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//#include "../include/array.h"
#include "../src/array.cpp"

TEST(array, primtive_initialisation) {
    size_t n = 10;
    std::initializer_list<int> sane = { 10, 20, 30, 40, 50 };
    array<int> people = (sane, n);
    EXPECT_EQ(people.getn(), n);
    for (int i = 0; i < people.getl(); i++)
        EXPECT_EQ(people[i], *(sane.begin() + 1));

    //ASSERT_EXIT(a[n], ::testing::ExitedWithCode(EXIT_FAILURE), "fail");
    //testing_glfw();
}

TEST(array, specific_initialisation) {

}

TEST(array, primtive_sorting_bubbl) {
    array<> numbers = { 5111, 4, 3, 2, 1 };
    numbers.sort(bubble_sort);
    FOR(numbers.getn() - 1)
        ASSERT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array, primtive_sorting_quick) {
    array<> numbers = { 5111, 4, 3, 2, 1 };
    numbers.sort();
    FOR(numbers.getl())
        ASSERT_TRUE(numbers[i] <= numbers[i + 1]);
}
