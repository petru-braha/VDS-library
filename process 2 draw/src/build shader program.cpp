#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "error management/file exception.h"
#include "error management/shader exception.h"

unsigned int create_program(const char* vertex_shader,const char* fragment_shader)
{
	// get code
	std::ifstream vs_source(vertex_shader);
	if (!vs_source.is_open())
		throw file_exception();
	
	std::ifstream fs_source(fragment_shader);
	if (!fs_source.is_open())
		throw file_exception();

	std::string vs_data, fs_data, temp;

	while (std::getline(vs_source, temp))
		vs_data += temp += '\n'; 
	while (std::getline(fs_source, temp))
		fs_data += temp += '\n';
	temp.clear();

	// shader initialization
	unsigned int program_id = glCreateProgram();
	if (0 == program_id)
		throw shader_initialization_exception();

	unsigned int vs_id = glCreateShader(GL_VERTEX_SHADER);
	if (0 == vs_id)
		throw shader_initialization_exception();

	unsigned int fs_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (0 == fs_id)
		throw shader_initialization_exception();

	// compile programs
	const char* ptr = vs_data.c_str();
	glShaderSource(vs_id, 1, &ptr, nullptr);
	
	ptr = fs_data.c_str();
	glShaderSource(fs_id, 1, &ptr, nullptr);
	
	glCompileShader(vs_id);
	glCompileShader(fs_id);

	vs_data.clear();
	fs_data.clear();
	vs_source.close();
	fs_source.close();

	// shape program
	glAttachShader(program_id, vs_id);
	glAttachShader(program_id, fs_id);
	glLinkProgram(program_id);
	glValidateProgram(program_id);

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);
	return program_id;
}

void ESC_close(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
