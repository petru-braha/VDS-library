#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "point.h"

void start(int argc)
{
    // init project
    if (argc != 1)
    {
        std::cout << "error - init: wrong number of parameters.\n";
        exit(EXIT_FAILURE);
    }

    if (!glfwInit())
    {
        std::cout << "error - init: glfw library failed.\n";
        exit(EXIT_FAILURE);
    }

    // compatibility hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* create_window()
{
    const GLFWvidmode* monitor_details = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int width = monitor_details->width / 2, height = monitor_details->height / 2;

    GLFWwindow* window;
    window = glfwCreateWindow(width, height, "visual data structure", nullptr, nullptr);
    if (!window)
    {
        std::cout << "error - init: window failed.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

void create_context(GLFWwindow* window, point w_position = {0, 38})
{
    if (nullptr == window)
    {
        std::cout << "error - init: window failed.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowPos(window, w_position.x, w_position.y);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (0 == gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "error - init: glad failed.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

// not ready yet
bool loop_render(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // draw calls

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
    return 0 == glfwWindowShouldClose(window) ? 0 : loop_render(window);
}
