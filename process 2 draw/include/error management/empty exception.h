#ifndef EMPTY_EXCEPTION
#define EMPTY_EXCEPTION

#include <exception>

class empty_buffer : public std::exception
{
public:
	const char* what() const override
	{
		return "error: the object has no memory.\n";
	}
};

#endif // !EMPTY_EXCEPTION
