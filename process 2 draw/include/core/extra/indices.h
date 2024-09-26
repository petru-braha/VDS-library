#ifndef INDICES
#define INDICES

#pragma warning (disable : 6386)

class indices
{
	unsigned int* data;
	unsigned int count;

public:
	// constructors:
	~indices();
	indices(const std::initializer_list<unsigned int>&);

	[[deprecated("copies all the data")]]
	indices(const unsigned int* _data, unsigned int _count);

	// constant methods:
	const unsigned int* get_pointer() const;
	unsigned int get_count() const;
};

//------------------------------------------------
// constructors:

indices::~indices()
{
	delete[]data;
}

indices::indices(const std::initializer_list<unsigned int>& l) :
	data(nullptr), count(0)
{
	if (l.size() == 0)
		return;

	data = new unsigned int[l.size()] {};

	for (const auto& value : l)
	{
		data[count] = value;
		count++;
	}
}

indices::indices(const unsigned int* _data, unsigned int _count) :
	data(new unsigned int[_count] {}), count(_count)
{
	for (unsigned int i = 0; i < _count; i++)
		data[i] = _data[i];
}

//------------------------------------------------
// constant methods:

const unsigned int* indices::get_pointer() const
{
	return data;
}

unsigned int indices::get_count() const
{
	return count;
}

#endif // !INDICES
