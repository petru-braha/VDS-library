#include <stdlib.h>
#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

#include "draw/structure/draw_data_structure.h"

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
    
    // core data for drawing
    float positions[]
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indexes[]
    {
        0, 1, 2,
        2, 3, 0
    };
    
    vertex_array vao;
    vertex_buffer vbo(positions, 4 * 2, GL_STATIC_DRAW);
    index_buffer ibo(indexes, 6, GL_STATIC_DRAW);

    layout att;
    att.insert_attribute(GL_FLOAT, 2);

    vao.insert_buffer(vbo, att);

    
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
    float r = 22, g = 160, b = 202, ratio = 255;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(uniform_location, r/ratio, g/ratio, b/ratio, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete data_structure;
    glDeleteProgram(shader_program_id);
    glfwTerminate();

    return 0;
}
