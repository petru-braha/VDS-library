#pragma once

template <typename argument>
class constant_methods 
{
public:
	virtual bool operator == (const argument& structure) const = 0;
	virtual size_t get_n() const = 0;
	virtual void*  get_f() const = 0;
	virtual bool   empty() const = 0;
	virtual void   print() const = 0;
};
