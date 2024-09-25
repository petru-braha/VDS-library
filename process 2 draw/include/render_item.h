#ifndef REDNDER_ITEM
#define REDNDER_ITEM

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

class render_item
{
	vertex_buffer vb;
	index_buffer ib;
	vertex_array va;

public:
	// constructors:
	~render_item() = default;
	render_item(const vertex_buffer&, const index_buffer&, const vertex_array&);

	// specific methods:
	void bind() const;
	void unbind() const;
	
	unsigned int draw() const;
};

//------------------------------------------------
// constructors:

render_item::render_item(const vertex_buffer& v0, const index_buffer& v1, const vertex_array& v2)
	: vb(v0), ib(v1), va(v2) {}

void render_item::bind() const
{
	vb.bind();
	ib.bind();
	va.bind();
}

void render_item::unbind() const
{
	vb.unbind();
	ib.unbind();
	va.unbind();
}

// wrapper method
unsigned int draw() const
{
	return 0;
}

#endif // !REDNDER_ITEM
