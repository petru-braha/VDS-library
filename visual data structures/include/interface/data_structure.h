#pragma once

template <class T>
class data_structure 
{
	// typedefs:
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef const data_structure<T>& ds;

	// data members:
	// iterator concept:
	// auxiliar utility:

public:
	// constructors:
	virtual ~data_structure() = default;
	// default, list, block, copy, move

	// modifier methods:
	virtual data_structure<T>& operator = (const data_structure& structure) = 0; // problem: for each data structure i have to assert that ds is the same
	virtual data_structure<T>& operator = (const data_structure&& structure) = 0;
	virtual data_structure<T>& clear() = 0;
	virtual data_structure<T>& set_f(fct f) = 0;

	// specific methods:
	// constant methods:
	virtual bool operator == (ds structure) = 0;
	virtual size_t get_n() const = 0;
	virtual void*  get_f() const = 0;
	virtual bool   empty() const = 0;
	virtual void   print() const = 0;
	
	// query operations:
	// instance synergy:
	virtual data_structure<T>& integrates(ds structure) = 0;
	virtual data_structure<T>& eliminates(ds structure) = 0;
	virtual data_structure<T>& intersects(ds structure) = 0;

	// friend functions:
};

// comments:
// no all data structure have iterators
// 
