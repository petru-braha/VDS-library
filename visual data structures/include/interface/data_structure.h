#pragma once

template <class T>
class data_structure 
{
	// typedefs:
	typedef const T& type;
	typedef bool (*fct)(type, type);

	// data members:
	// iterator concept:
	// auxiliar utility:

public:
	// constructors:
	virtual ~data_structure() = default;
	// default, list, block, copy, move

	// modifier methods:
	virtual data_structure<T>& operator = (const data_structure<T>& structure) = 0;
	virtual data_structure<T>& operator = (const data_structure<T>&& structure) = 0;
	virtual data_structure<T>& clear() = 0;
	virtual data_structure<T>& set_f(fct f) = 0;

	// specific methods:
	// constant methods:
	virtual bool   operator == (const data_structure<T>& structure) const = 0;
	virtual size_t get_n() const = 0;
	virtual void*  get_f() const = 0;
	virtual bool   empty() const = 0;
	virtual void   print() const = 0;
	//virtual void   paint() const = 0;

	// query operations:
	// instance synergy:
	virtual data_structure<T>& integrates(const data_structure<T>& structure) = 0;
	virtual data_structure<T>& eliminates(const data_structure<T>& structure) = 0;
	virtual data_structure<T>& intersects(const data_structure<T>& structure) = 0;

	// friend functions:
};

// comments:
// no all data structure have iterators
// the developer is responsable for: constructors, specific methods, queries and friend functions
// typedefs can not be inherited
// whenever is used a ds type parameter, int the method body will be used a static_assert; 