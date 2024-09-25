#ifndef GLENUM_EXCEPTION
#define GLENUM_EXCEPTION

#include <exception>

class GLenum_exception : public std::exception
{
public:
	virtual const char* what() const override
	{
		return "error: invalid GLenum.\n";
	}
};

#endif // !GLENUM_EXCEPTION
