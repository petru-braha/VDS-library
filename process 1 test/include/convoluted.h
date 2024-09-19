#pragma once
#include "dev/bureaucracy.h"
#include <cstring>

class convoluted
{
	// data members:
	int number;
	bool* address1;
	char* address2;
public:
	// constructors:
	~convoluted();
	convoluted(int number, const bool& one, const char* two);
	convoluted(int null = NULL);
	convoluted(const convoluted& c);
	convoluted(const convoluted&& c);
	
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
	
	friend bit  swap(convoluted& c1, convoluted& c2);
	friend bool absolute_equality(const convoluted& c1, const convoluted& c2);
};

// comments:
// convoluted::number doesn't depend on the char array, but helps at initializing it in constructors
// this class should look arbitrarly built, the structures have to work as expected even if this header doesn't make sense
// address2 can be nullptr

//------------------------------------------------
// auxiliary utility:

bool letter(const char& character)
{
	if (character < 'A' || character > 'z')
		return false;
	if (character > 'Z' && character < 'a')
		return false;
	return true;
}

//------------------------------------------------
// constructors:

convoluted::~convoluted()
{
	delete address1;
	if (address2)
		delete[]address2;
}

convoluted::convoluted(int number, const bool& one, const char* two) : number(number)
{
	address1 = new bool {one};
	address2 = new char[number];
	
	size_t sz = strlen(two) + 1;
	sz = sz < number ? sz : number;
	for (size_t i = 0; i < sz - 1; i++)
	{
		if (0 == two[i])
		{
			this->address2[i] = 0;
			break;
		}

		address2[i] = letter(two[i]) ? two[i] : 'A';
	}

	address2[sz - 1] = 0;
}

convoluted::convoluted(int null) : number(0), address1(new bool{ false }), address2(nullptr) {}

convoluted::convoluted(const convoluted& c)
{
	this->number = c.number;
	this->address1 = new bool{ *c.address1 };
	
	if (nullptr == c.address2)
	{
		this->address2 = nullptr;
		return;
	}

	size_t sz = strlen(c.address2) + 1;
	this->address2 = new char[sz];
	for (size_t i = 0; i < sz; i++)
		this->address2[i] = c.address2[i];
}

//------------------------------------------------
// modifier methods: 

convoluted& convoluted::operator = (const convoluted& c)
{
	this->number = c.number;
	
	delete address1;
	if(address2)
		delete[]address2;
	address1 = nullptr;
	address2 = nullptr;

	address1 = new bool{ *c.address1 };
	
	if (c.address2 == nullptr)
		return *this;
	size_t sz = strlen(c.address2) + 1;
	address2 = new char[sz];
	for (size_t i = 0; i < sz; i++)
		this->address2[i] = c.address2[i];

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
	return *address1;
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
	out << "|" << " abstract: " << *c.address1 << "\n";
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
	if (*one.address1 == *two.address1)
		return compare_strng(one, two);
	return *one.address1 > *two.address1;
}

bool compare_strng(const convoluted& one, const convoluted& two)
{
	// patch
	if (one.address2 == nullptr)
		return false;
	if (one.address2 && two.address2 == nullptr)
		return true;
	
	if (strcmp(one.address2, two.address2) > 0)
		return true;
	return false;
}

bit swap(convoluted& c1, convoluted& c2)
{
	// number
	int nr = c1.number;
	c1.number = c2.number;
	c2.number = nr;
	
	// address1
	bool ad = *c1.address1;
	*c1.address1 = false == *c2.address1 ? false : true;
	*c2.address1 = false == ad ? false: true;
	
	// address2
	char* ptr = c1.address2;
	c1.address2 = c2.address2;
	c2.address2 = ptr;
	
	return 0;
}

bool absolute_equality(const convoluted& c1, const convoluted& c2)
{
	if (c1.number != c2.number)
		return false;
	if (*c1.address1 != *c2.address1)
		return false;
	
	if (c1.address2 == nullptr && c2.address2 == nullptr)
		return true;
	if ((c1.address2 == nullptr && c2.address2) || c1.address2 && c2.address2 == nullptr)
		return false;
	if (strcmp(c1.address2, c2.address2) != 0)
		return false;
	return true;
}
