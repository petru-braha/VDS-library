#include "pch.h"
#include "convoluted.h"

//------------------------------------------------
// constructors:

bool letter(const char& character)
{
	if (character < 'A' || character > 'z')
		return false;
	if (character > 'Z' && character < 'a')
		return false;
	return true;
}

convoluted::convoluted(int number, bool& one, char* two) : number(number), address1(one)
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

convoluted::~convoluted()
{
	if (address2)
		delete[]address2;
}

//------------------------------------------------
// specific methods: 

bool convoluted::operator <  (const convoluted& c)
{
	return address2[0] < c.address2[0];
}

bool convoluted::operator <= (const convoluted& c)
{
	return (*this < c || *this == c);
}

bool convoluted::operator >  (const convoluted& c)
{
	return address2[0] < c.address2[0];
}

bool convoluted::operator >= (const convoluted& c)
{
	return (*this > c || *this == c);
}

bool convoluted::operator == (const convoluted& c)
{
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
	return number + 5;
}

//------------------------------------------------
// friend functions:

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
	return one.number > two.number;
}

bool compare_addss(const convoluted& one, const convoluted& two)
{
	return one.address1 > two.address1;
}

bool compare_strng(const convoluted& one, const convoluted& two)
{
	int minimum = one.number < two.number ? one.number : two.number;
	for (int i = 0; i < minimum; i++)
		if (one.address2[i] > two.address2[i])
			return true;
	return false;
}
