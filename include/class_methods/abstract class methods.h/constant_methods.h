#pragma once

class constant_methods 
{
public:
	typedef const size_t& szt;
	typedef const constant_methods& c_type;

	virtual bool operator == (c_type structure) = 0;
	virtual size_t get_n() const = 0;
	virtual void*  get_f() const = 0;
	virtual bool   empty() const = 0;
	virtual void   print() const = 0;
};
