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

	//modifier methods:
	virtual void clear() = 0;
	virtual void setf(fct f) = 0;

	// specific methods:
	virtual void sort() = 0;

	// 
	// constant methods:
	virtual void   prnt() const = 0;
	virtual size_t getn() const = 0;
	virtual void*  getf() const = 0;
	virtual T*    block() const = 0; // equivalent to convert
	virtual bool  empty() const = 0;

	//

	/*

	template <class T> friend array<T> linking(const array<T>& one, const array<T>& two);
	template <class T> friend array<T> ejectin(const array<T>& one, const array<T>& two);
	template <class T> friend array<T> crossng(const array<T>& one, const array<T>& two);

	template <class T> friend std::ostream& operator << (std::ostream& out, const array<T>& arr);*/
};