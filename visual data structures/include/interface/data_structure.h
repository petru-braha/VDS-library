#pragma once

template <class T>
class data_structure
{
	// typedefs:
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef const data_structure<T>& ds;

	// data members
	// iterator concept
	// auxiliar utility

public:
	// constructors:
	virtual ~data_structure() = default;
	// default, list, block, copy, move

	// modifier methods:
	data_structure<T>& operator = (const data_structure& structure) = 0;
	data_structure<T>& operator = (const data_structure&& structure) = 0;
	virtual data_structure<T>& clear() = 0;
	virtual data_structure<T>& setf(fct f) = 0;

	// specific methods:
	//data_structure<T>& insert();
	//data_structure<T>& remove();

	// constant methods:
	virtual bool operator == (ds structure) = 0;
	virtual size_t get_n() const = 0;
	virtual void*  get_f() const = 0;
	virtual bool   empty() const = 0;
	virtual void   print() const = 0;
	
	// query operations:
	/*void search();
	void minimum();
	void maximum();
	void predecessor();
	void successor();*/

	// instance synergy:
	virtual data_structure<T>& integrates(ds structure) = 0;
	virtual data_structure<T>& eliminates(ds structure) = 0;
	virtual data_structure<T>& intersects(ds structure) = 0;

	// friend functions:
	template <class T> friend T* convert() const = 0;
	template <class T> friend std::ostream& operator << (std::ostream& out, const array<T>& arr) = 0;
};

// comments:
// typedefs are used except for constructors
// important
// no all data structure are
