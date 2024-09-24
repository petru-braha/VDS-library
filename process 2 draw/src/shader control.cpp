#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "error management/file exception.h"
#include "error management/shader exception.h"

//------------------------------------------------
// shader work:

static void initialize_shader(unsigned int& program_id, unsigned int& vs_id, unsigned int& fs_id)
{
	program_id = glCreateProgram();
	if (0 == program_id)
		throw shader_initialization_exception();

	vs_id = glCreateShader(GL_VERTEX_SHADER);
	if (0 == vs_id)
		throw shader_initialization_exception();

	fs_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (0 == fs_id)
		throw shader_initialization_exception();
}

// one shader per file
static void compile_shader(unsigned int shader_id, const char* file_path)
{
	std::ifstream stream(file_path);
	if (!stream.is_open())
		throw file_exception();

	std::string code, temp;
	while (std::getline(stream, temp))
		if (temp.find("#shader"))
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

// two shaders per file
static void compile_shader(unsigned int shader_id1, unsigned int shader_id2, const char* file_path) // check for errors
{
	std::ifstream stream(file_path);
	if (!stream.is_open())
		throw file_exception();

	// compile the first shader
	std::string code, temp;
	std::getline(stream, temp);
	while (std::getline(stream, temp) && temp.find("#shader") != 0)
		code += temp += '\n';

	const char* ptr = code.c_str();
	glShaderSource(shader_id1, 1, &ptr, nullptr);
	glCompileShader(shader_id1);

	// compile the second shader
	code.clear();
	while (std::getline(stream, temp))
		code += temp += '\n';
	
	ptr = code.c_str();
	glShaderSource(shader_id2, 1, &ptr, nullptr);
	glCompileShader(shader_id2);

	// error check
	int result = 1;
	glGetShaderiv(shader_id1, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
		throw shader_compilation_exception();
	
	glGetShaderiv(shader_id2, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
		throw shader_compilation_exception();

	code.clear();
	temp.clear();
	stream.close();
}

static void connect_shader(unsigned int& program_id, unsigned int& vs_id, unsigned int& fs_id)
{
	glAttachShader(program_id, vs_id);
	glAttachShader(program_id, fs_id);
	glLinkProgram(program_id);
	glValidateProgram(program_id);

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);
}

//------------------------------------------------
// actual calls:

unsigned int create_program(const char* shader_path)
{
	// shader initialization
	unsigned int program_id = 0, vs_id = 0, fs_id = 0;
	initialize_shader(program_id, vs_id, fs_id);

	// parse code and compile
	compile_shader(vs_id, fs_id, shader_path);

	connect_shader(program_id, vs_id, fs_id);
	return program_id;
}

unsigned int create_program(const char* vertex_shader_path,const char* fragment_shader_path)
{
	// shader initialization
	unsigned int program_id = 0, vs_id = 0, fs_id = 0;
	initialize_shader(program_id, vs_id, fs_id);

	// no checks required for gl APIs, 
	// the shaders are valid
	compile_shader(vs_id, vertex_shader_path);
	compile_shader(fs_id, fragment_shader_path);

	// shape program
	connect_shader(program_id, vs_id, fs_id);
	return program_id;
}

