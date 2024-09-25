#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include <glad/glad.h>
#include "layout.h"
#include "vertex_buffer.h"

class vertex_array
{
	unsigned int id;

public:
	// constructors:
	~vertex_array();
	vertex_array();

	// specific methods:
	void insert_buffer(const vertex_buffer&, const layout&);
	void bind() const;
	void unbind() const;

	// constant methods:
	unsigned int get_id() const;
};

//------------------------------------------------
// constructors:

vertex_array::~vertex_array()
{
	glDeleteVertexArrays(1, &id);
}

vertex_array::vertex_array() : id(0)
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

//------------------------------------------------
// specific methods:

void vertex_array::insert_buffer(const vertex_buffer& vb, const layout& l)
{
	unsigned int offset = 0;

	this->bind();
	vb.bind();
	
	for (unsigned int i = 0; i < l.get_count(); i++)
	{
		const auto& element = l.get_attribute(i);

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, l.get_stride(), (const void*)offset);

		offset += element.count * sizeof_GLenum(element.type);
	}
}

void vertex_array::bind() const
{
	glBindVertexArray(id);
}

void vertex_array::unbind() const
{
	glBindVertexArray(0);
}

//------------------------------------------------
// constant methods:

unsigned int vertex_array::get_id() const
{
	return id;
}

#endif // !VERTEX_ARRAY
