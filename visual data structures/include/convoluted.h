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
	bool&  get_addr1() const;
	void*  get_addr2() const;
	size_t get_bytes() const;

	// friend functions:
	friend bool operator >  (const convoluted& c1, const convoluted& c2);
	friend std::ostream& operator << (std::ostream& out, const convoluted& c); // they assume: one > two
	friend bool compare_numbr(const convoluted& one, const convoluted& two);
	friend bool compare_addss(const convoluted& one, const convoluted& two);
	friend bool compare_strng(const convoluted& one, const convoluted& two);
};

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
	char* temp = new char[number];
	for (int i = 0; i < number; i++)
	{
		if (letter(two[i]))
			temp[i] = two[i];
		else
			temp[i] = 'A';
	}
	temp[number - 1] = 0;

	address2 = temp;
}

convoluted::convoluted(int null) : number(0), address1(reinterpret_cast<bool&>(null)), address2(nullptr) {}

//------------------------------------------------
// modifier methods: 

convoluted& convoluted::operator = (const convoluted& c)
{
	if (address2)
		delete[]address2;
	address2 = nullptr;
	if (c.address2)
	{
		address2 = new char[c.number];
		strcpy(this->address2, c.address2);
	}

	this->address1 = c.address1;
	this->number = c.number;
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

bool& convoluted::get_addr1() const
{
	return address1;
}

void* convoluted::get_addr2() const
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
	out << "|" << " strlen: " << c.number << "\n";
	out << "|" << " address: " << c.address1 << "\n";
	out << "|" << " text: " << c.address2 << "\n";
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
	if (one.address1 == two.address1)
		return compare_strng(one, two);
	return one.address1 > two.address1;
}

bool compare_strng(const convoluted& one, const convoluted& two)
{
	// patch
	if (one.address2 == nullptr)
		return false;
	if (one.address2 && two.address2 == nullptr)
		return true;
	
	int minimum = one.number < two.number ? one.number : two.number;
	int nr1 = 0, nr2 = 0;
	for (int i = 0; i < minimum; i++)
	{
		nr1 += (i + 1) * one.address2[i];
		nr2 += (i + 1) * two.address2[i];
	}

	return nr1 > nr2;
}
