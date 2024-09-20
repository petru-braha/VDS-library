#include <stdlib.h>
#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int create_program(const char* vertex_shader, const char* fragment_shader);
void ESC_close(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    GLFWwindow* window;

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

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, ESC_close);

    float positions[6]
    {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer_id = 0;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    
    unsigned int shader_program = 0;
    try
    {
        char vs_path[] = "shader/vs0.cpp";
        char fs_path[] = "shader/fs0.cpp";
        shader_program = create_program(vs_path, fs_path);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        exit(EXIT_FAILURE);
    }
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);  
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    if(shader_program) 
        glDeleteProgram(shader_program);
    glfwTerminate();

    return 0;
    // launch into execution the visual process, the third cpp 
}

// read files names
// read files content
// create shader
// compile shader
// create program
// delete program

