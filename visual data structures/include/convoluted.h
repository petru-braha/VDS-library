#pragma once
#include "bureaucracy.h"
#include <cstring>

class convoluted
{
	// data members:
	int number;
	bool& address1;
	char* address2;
public:
	// constructors:
	~convoluted();
	convoluted(int number, bool one, const char* two);
	bool constructor_ = false; // patch
	convoluted(int null = NULL);
	
	// modifier methods:
	convoluted& operator = (const convoluted& c);

	// specific methods: 
	void set_number(const int& value);
	bool operator <  (const convoluted& c); // they only compare the first letter
	bool operator <= (const convoluted& c);
	bool operator >  (const convoluted& c);
	bool operator >= (const convoluted& c);
	bool operator == (const convoluted& c);
	bool operator != (const convoluted& c);
	
	// constant methods:
	int    get_numbr() const;
	bool   get_addr1() const;
	char*  get_addr2() const;
	size_t get_bytes() const;

	// friend functions:
	friend bool operator >  (const convoluted& c1, const convoluted& c2);
	friend std::ostream& operator << (std::ostream& out, const convoluted& c); // they assume: one > two
	friend bool compare_numbr(const convoluted& one, const convoluted& two);
	friend bool compare_addss(const convoluted& one, const convoluted& two);
	friend bool compare_strng(const convoluted& one, const convoluted& two);
};

// comments:
// convoluted::number doesn't depend on the char array, but helps at initializing it in constructors
// this class should look arbitrarly built, the structures have to work as expected even if this header doesn't make sense

//------------------------------------------------
// constructors:

convoluted::~convoluted()
{
	if (address2)
		delete[]address2;
}

bool letter(const char& character)
{
	if (character < 'A' || character > 'z')
		return false;
	if (character > 'Z' && character < 'a')
		return false;
	return true;
}

convoluted::convoluted(int number, bool one, const char* two) : number(number), address1(one)
{
	this->number = number;
	address2 = new char[number];
	for (int i = 0; i < number - 1; i++)
	{
		if (letter(two[i]))
			address2[i] = two[i];
		else
			address2[i] = 'A';
	}

	address2[number - 1] = 0;
}

convoluted::convoluted(int null) : number(0), address1(constructor_), address2(nullptr) {}

//------------------------------------------------
// modifier methods: 

convoluted& convoluted::operator = (const convoluted& c)
{
	this->number = c.number;
	if (address2)
		delete[]address2;
	address2 = nullptr;
	if (c.address2)
	{
		address2 = new char[c.number];
		strcpy(this->address2, c.address2);
	}

	bool temp = c.address1;
	this->address1 = temp;
	return *this;
}

//------------------------------------------------
// specific methods: 

void convoluted::set_number(const int& value)
{
	this->number = value;
}

bool convoluted::operator <  (const convoluted& c)
{
	if (address2 == nullptr)
		return false;
	if (c.address2 == nullptr)
		return true;
	return address2[0] < c.address2[0];
}

bool convoluted::operator <= (const convoluted& c)
{
	return (*this < c || *this == c);
}

bool convoluted::operator >  (const convoluted& c)
{
	if (address2 == nullptr)
		return false;
	if (c.address2 == nullptr)
		return true;
	return address2[0] > c.address2[0];
}

bool convoluted::operator >= (const convoluted& c)
{
	return (*this > c || *this == c);
}

bool convoluted::operator == (const convoluted& c)
{
	if (address2 == nullptr)
		return false;
	if (c.address2 == nullptr)
		return true;
	return address2[0] == c.address2[0];
}

bool convoluted::operator != (const convoluted& c)
{
	return !(*this == c);
}

//------------------------------------------------
// constant methods:

int convoluted::get_numbr() const
{
	return number;
}

bool convoluted::get_addr1() const
{
	return address1;
}

char* convoluted::get_addr2() const
{
	return address2;
}

size_t convoluted::get_bytes() const
{
	return size_t(number + 5);
}

//------------------------------------------------
// friend functions:

bool operator > (const convoluted& c1, const convoluted& c2)
{
	if (c1.address2 == nullptr)
		return false;
	if (c2.address2 == nullptr)
		return true;
	return c1.address2[0] > c2.address2[0];
}

std::ostream& operator << (std::ostream& out, const convoluted& c)
{
	out << "\n";
	out << "|" << "----------" << "----------" << "----------" << "|\n";
	out << "|" << " number: " << c.number << "\n";
	out << "|" << " abstract: " << c.address1 << "\n";
	out << "|" << " text: ";
	
	if (c.address2) out << c.address2;
	else out << "nullptr";
	out << "\n";
	out << "|" << "----------" << "----------" << "----------" << "|\n" << "\n";
	return out;
}

bool compare_numbr(const convoluted& one, const convoluted& two)
{
	if (one.number == two.number)
		return compare_addss(one, two);
	return one.number > two.number;
}

bool compare_addss(const convoluted& one, const convoluted& two)
{
	if ((bool)one.address1 == (bool)two.address1)
		return compare_strng(one, two);
	return (bool)one.address1 > (bool)two.address1;
}

bool compare_strng(const convoluted& one, const convoluted& two)
{
	// patch
	if (one.address2 == nullptr)
		return false;
	if (one.address2 && two.address2 == nullptr)
		return true;
	
	for (size_t i = 0;; i++)
	{
		if (one.address2[i] == 0 || two.address2[i] == 0)
			return false;
		if (one.address2[i] > two.address2[i])
			return true;
	}
	return false;
}
