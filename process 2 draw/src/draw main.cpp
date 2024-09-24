#include <stdlib.h>
#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "draw_data_structure.h"

draw_data_structure* assing_ds(const char*);
unsigned int create_program(const char*);
unsigned int create_program(const char*, const char*);
void ESC_close(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        std::cout << "error - graphics: launching failed, wrong number of parameters.\n";
        exit(EXIT_FAILURE);
    }

    draw_data_structure* data_structure = assing_ds(argv[1]);

    // initialization of library
    GLFWwindow* window;

    if (!glfwInit())
        return EXIT_FAILURE;

    // compatibility hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // window
    const GLFWvidmode* monitor_details = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int width = monitor_details->width / 2, height = monitor_details->height / 2;

    window = glfwCreateWindow(width, height, "representation", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // context
    glfwSetWindowPos(window, 0, 20);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (0 == gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    
    // vertex array
    unsigned int vao_id = 0;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    // send data to GPU
    float positions[]
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int buffer_id = 0;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
    
    // design layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // index buffer
    unsigned int indexes[]
    {
        0, 1, 2,
        2, 3, 0
    };
    
    unsigned int index_buffer = 0;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(unsigned int), indexes, GL_STATIC_DRAW);

    // shader program
    unsigned int shader_program_id = 0;
    try
    {
        char vs_path[] = "../process 2 draw/shader/vs0.shader";
        char fs_path[] = "../process 2 draw/shader/fs1.shader";
        shader_program_id = create_program(vs_path, fs_path);
        glUseProgram(shader_program_id);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        exit(EXIT_FAILURE);
    }

    // uniform for gradient color
    int uniform_location = glGetUniformLocation(shader_program_id, "u_color");
    
    // main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);  
        glUniform4f(uniform_location, 0.183f, 0.26f, 0.107f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete data_structure;
    glDeleteProgram(shader_program_id);
    glfwTerminate();

    return 0;
}

// read files names
// read files content
// create shader
// compile shader
// create program
// delete program

