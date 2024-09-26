#pragma warning (disable : 4098)
#include <stdlib.h>
#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

#include "draw/structure/draw_data_structure.h"

#include "draw main.h"

#include "render_item.h"

#include "color.h"

int main(int argc, char* argv[])
{
    // init
    start(argc);
    GLFWwindow* window = create_window();
    create_context(window);

    // square
    render_item square_renderer = { {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    },
    { 0, 1, 2, 2, 3, 0 }
    };

    layout default_layout;
    default_layout.insert_attribute(GL_FLOAT, 2);
    square_renderer.set_layout(default_layout);

    // line
    render_item line_renderer({ 0.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 1.0f, 0.0f
        }, {});
    line_renderer.set_layout(default_layout);

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

    draw_data_structure* data_structure = assing_ds(argv[1]);

    // uniform for gradient color
    int uniform_location = glGetUniformLocation(shader_program_id, "u_color");
    
    // main loop
    float r = 22, g = 160, b = 202, ratio = 255;
    float color = color::heavy_gray;
    float increment = 0.15f;

    while (0 == glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // draw
        square_renderer.bind();
        
        color = color::light_gray;
        glUniform4f(uniform_location, color / ratio, color / ratio, color / ratio, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        

        line_renderer.bind();
        
        color = color::gray_white;
        glUniform4f(uniform_location, color / ratio, color / ratio, color / ratio, 1.0f);
        glDrawArrays(GL_LINES, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    

    delete data_structure;
    glDeleteProgram(shader_program_id);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
