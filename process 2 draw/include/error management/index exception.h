#ifndef INDEX_EXCEPTION
#define INDEX_EXCEPTION

#include <exception>

class index_exception : public std::exception
{
public:
	virtual const char* what() const override
	{
		return "error: bad index.\n";
	}
};

#endif // !INDEX_EXCEPTION
