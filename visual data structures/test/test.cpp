#include "pch.h"
#include <GLFW/glfw3.h>
#include <iostream>

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

TEST(array, primitive_initialisation) {
    size_t n = 10;
    std::initializer_list<int> sane = { 10, 20, 30, 40, 50 };
    array<> people = (sane, n);
    EXPECT_EQ(people.getn(), n);
    for (int i = 0; i < people.getl(); i++)
        EXPECT_EQ(people[i], *(sane.begin() + 1));
    //ASSERT_EXIT(a[n], ::testing::ExitedWithCode(EXIT_FAILURE), "fail");
    //testing_glfw();
}

TEST(array, specific_initialisation) {

}