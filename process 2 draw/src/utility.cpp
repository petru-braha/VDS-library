#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "error management/file exception.h"
#include "error management/shader exception.h"

static void compile_shader(unsigned int shader_id, const char* file_path)
{
	std::ifstream stream(file_path);
	if (!stream.is_open())
		throw file_exception();

	std::string code, temp;
	while (std::getline(stream, temp))
		code += temp += '\n';

	const char* ptr = code.c_str();
	glShaderSource(shader_id, 1, &ptr, nullptr);
	glCompileShader(shader_id);

	int result = 1;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
		throw shader_compilation_exception();

	code.clear();
	temp.clear();
	stream.close();
}

unsigned int create_program(const char* shader_path)
{
	return 0;
}

unsigned int create_program(const char* vertex_shader_path,const char* fragment_shader_path)
{
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

	// no checks required for gl APIs, 
	// the shaders are valid
	compile_shader(vs_id, vertex_shader_path);
	compile_shader(fs_id, fragment_shader_path);

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
