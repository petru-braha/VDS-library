#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class vertex_buffer
{
	unsigned int id;

public:
	// constructors:
	~vertex_buffer();
	vertex_buffer(const float* data, unsigned int count, unsigned int usage = GL_STATIC_DRAW);

	// specific methods:
	void bind() const;
	void unbind() const;

	// constant methods:
	unsigned int get_id() const;
};

//------------------------------------------------
// constructors:

vertex_buffer::~vertex_buffer()
{
	glDeleteBuffers(1, &id);
}

vertex_buffer::vertex_buffer(const float* data, unsigned int count, unsigned int usage) : id(0)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, usage);
}

//------------------------------------------------
// specific methods:

void vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void vertex_buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//------------------------------------------------
// constant methods:

unsigned int vertex_buffer::get_id() const
{
	return id;
}

#endif
