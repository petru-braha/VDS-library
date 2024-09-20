#ifndef SHADER_EXCEPTION
#define SHADER_EXCEPTION

#include <exception>

class shader_exception : public std::exception
{
public:
	virtual const char* what() const override
	{
		return "error: invalid shader.\n";
	}
};

class shader_initialization_exception final : public shader_exception
{
public:
	const char* what() const override
	{
		return "error - shader: initialization failed.\n";
	}
};

class shader_compilation_exception final : public shader_exception
{
public:
	const char* what() const override
	{
		return "error - shader: compilation failed.\n";
	}
};

#endif // !SHADER_EXCEPTION
