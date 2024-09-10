#include "pch.h"
#include <GLFW/glfw3.h>

GLFWwindow* window;

void draw_line()
{
    if (!window)
        throw - 1;

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(1);
    glLineWidth(10);
    glColor3f(1.0, 0.0, 0.0);

    int frame_size[2]{};
    
    glfwGetFramebufferSize(window, &frame_size[0], &frame_size[1]);
    glViewport(0, 0, frame_size[0], frame_size[1]);
    
    glBegin(GL_LINES);

    //glVertex3f(frame_size[0] / 2, 0.0, 0.0);
    //glVertex3f(frame_size[0] / 2, frame_size[1], 0.0);

    glEnd();
}

void ESC_close(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int new_main(int argc, char** argv)
{
    if (!glfwInit())
        return EXIT_FAILURE;

    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    const GLFWvidmode* monitor_details = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int width = monitor_details->width / 2, height = monitor_details->height / 2;

    window = glfwCreateWindow(width, height, "representation", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwSetWindowPos(window, 0, 20);
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, 0.0, 1.0); // this creates a canvas you can do 2D drawing on
    
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, ESC_close);

    while (!glfwWindowShouldClose(window))
    {
        draw_line();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
    // launch into execution the visual process, the third cpp 
}

void start_visual()
{
    new_main(0, nullptr);
}
