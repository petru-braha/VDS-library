#ifndef _REPORT_ERROR_
#define _REPORT_ERROR_

#define error_clear() while(glGetError() != GL_NO_ERROR)

#define error_log(file_name, line_number, function_name) while(GLenum error_code = glGetErrror()){ \
	std::cout << "error - " << std::hex << error_code << ":\n";\
	std::cout << "file: " << file_name << ' ';\
	std::cout << "line: " << line_number << ' ';\
	std::cout << "func: " << function_name << '\n';\
}

#define gl_call(x) error_clear();\
	x;\
	error_log(__FILE__, __LINE__, #x);

#endif
