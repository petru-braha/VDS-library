#ifndef FILE_EXCEPTION
#define FILE_EXCEPTION

#include <exception>

class file_exception : public std::exception
{
public:
	virtual const char* what() const override
	{
		return "error: invalid file.\n";
	}
};

class file_name_exception final : public file_exception
{
public:
	const char* what() const override
	{
		return "error: file not found.\n";
	}
};

#endif // !FILE_EXCEPTION
