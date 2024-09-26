#ifndef POSITION
#define POSITION

#pragma warning (disable : 6386)
#include "error management/empty exception.h"

class position
{
	float* data;
	unsigned int count;

public:
	// constructors:
	~position();
	position(const std::initializer_list<float>&);

	[[deprecated("copies all the data")]]
	position(const float* _data, unsigned int _count);
	
	// constant methods:
	const float* get_pointer() const;
	unsigned int get_count() const;
};


//------------------------------------------------
// constructors:

position::~position()
{
	delete[]data;
}

position::position(const std::initializer_list<float>& l) :
	data(nullptr), count(0)
{
	if (l.size() == 0)
		throw empty_buffer();

	data = new float[l.size()] {};

	for (const auto& value : l)
	{
		data[count] = value;
		count++;
	}
}

position::position(const float* _data, unsigned int _count) :
	data(new float[_count] {} ), count(_count)
{
	for (unsigned int i = 0; i < _count; i++)
		this->data[i] = _data[i];
}

//------------------------------------------------
// constant methods:

const float* position::get_pointer() const
{
	return data;
}

unsigned int position::get_count() const
{
	return count;
}

#endif // !POSITION
