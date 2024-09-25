#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class index_buffer
{
	unsigned int id;

public:
	// constructors:
	~index_buffer();
	index_buffer(const unsigned int* data, unsigned int count, unsigned int usage = GL_STATIC_DRAW);

	// specific methods:
	void bind() const;
	void unbind() const;

	// constant methods:
	unsigned int get_id() const;
};

//------------------------------------------------
// constructors:

index_buffer::~index_buffer()
{
	glDeleteBuffers(1, &id);
}

index_buffer::index_buffer(const unsigned int* data, unsigned int count, unsigned int usage) : id(0)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(float), data, usage);
}

//------------------------------------------------
// specific methods:

void index_buffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void index_buffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//------------------------------------------------
// constant methods:

unsigned int index_buffer::get_id() const
{
	return id;
}

#endif
