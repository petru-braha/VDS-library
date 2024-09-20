#include <stdlib.h>
#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int create_program(const char* vertex_shader, const char* fragment_shader);
void ESC_close(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    // initialization of library
    GLFWwindow* window;

    if (!glfwInit())
        return EXIT_FAILURE;

    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, ESC_close);

    // triangle 
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
    
    // shader program
    unsigned int shader_program = 0;
    try
    {
        char vs_path[] = "shader/vs0.shader";
        char fs_path[] = "shader/fs0.shader";
        shader_program = create_program(vs_path, fs_path);
        glUseProgram(shader_program);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        exit(EXIT_FAILURE);
    }
    
    // main loop
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
}

// read files names
// read files content
// create shader
// compile shader
// create program
// delete program

