#ifndef LAYOUT
#define LAYOUT

#include <glad/glad.h>
#include <vector>
#include "attribute.h"
#include "global header.h"

class layout
{
	std::vector<attribute> attributes;
	unsigned int stride;

public:
	// constructors:
	~layout() = default;
	layout();

	// specific methods:
	layout& insert_attribute(unsigned int type, unsigned int count);

	// constant methods:
	unsigned int get_count() const;
	unsigned int get_stride() const;
	attribute get_attribute(const unsigned int& index) const;
};

//------------------------------------------------
// constructors:

layout::layout() : stride(0) {}

//------------------------------------------------
// specific methods:

// e. g. of a type: GL_FLOAT 
layout& layout::insert_attribute(unsigned int type, unsigned int count)  
{
	unsigned char normalized = 0;
	normalized = type == GL_FLOAT ? GL_FALSE : GL_TRUE;
	attributes.push_back({ type, count, normalized });
	
	if (sizeof_GLenum(type))
		throw GLenum_exception();
	stride += sizeof_GLenum(type);

	return *this;
}

//------------------------------------------------
// constant methods:

unsigned int layout::get_count() const
{
	return (unsigned int)attributes.size();
}

unsigned int layout::get_stride() const
{
	return stride;
}

attribute layout::get_attribute(const unsigned int& index) const
{
	if (index >= attributes.size())
		throw index_exception();
	return attributes.at(index);
}

#endif // !LAYOUT
