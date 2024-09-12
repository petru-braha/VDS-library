#pragma once
#include "../abstract class methods.h/query_operations.h"

template <class T>
class array_queries : public query_operations
{
	typedef const T& t;
	typedef const size_t& szt;

public:
	virtual size_t search(t value) const = 0;
	virtual size_t minimum() const = 0;
	virtual size_t maximum() const = 0;
	virtual size_t predcessr(szt index) const = 0;
	virtual size_t successor(szt index) const = 0;
	virtual T& operator [] (szt index) = 0;
};
