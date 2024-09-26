#ifndef REDNDER_ITEM
#define REDNDER_ITEM

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

#include "extra/position.h"
#include "extra/indices.h"

void render(void)
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void render(const vertex_array& va, const vertex_buffer& vb, const index_buffer& ib, const layout& design)
{
	va.bind();
	vb.bind();
	ib.bind();

	va.insert_buffer(vb, design);
}

class render_item
{
	// typedefs:
	typedef const std::initializer_list<float>& lf_ref;
	typedef const std::initializer_list<unsigned int>& li_ref;

	// data members:
	layout design;

	vertex_array va;
	vertex_buffer vb;
	index_buffer ib;

public:
	// constructors:
	~render_item() = default;
	render_item(const vertex_array&, const vertex_buffer&, const index_buffer&);
	render_item(const position&, const indices&, unsigned int usage = GL_STATIC_DRAW);
	render_item(lf_ref, li_ref, unsigned int usage = GL_STATIC_DRAW);

	// specific methods:
	void set_layout(const layout&);
	
	void bind() const;
	void unbind() const;
	
	unsigned int draw() const;
	
	// constant methods:
	bool empty_layout() const;
	const layout& get_layout() const;
};

//------------------------------------------------
// constructors:

// assuming the objects are valid
render_item::render_item(const vertex_array& v0, const vertex_buffer& v1, const index_buffer& v2) : 
	design(), va(v0), vb(v1), ib(v2) {}

render_item::render_item(const position& p, const indices& i, unsigned int usage) : 
	design(), va(),
	vb(p.get_pointer(), p.get_count(), usage),
	ib(i.get_pointer(), i.get_count(), usage) {}

render_item::render_item(lf_ref p, li_ref i, unsigned int usage) :
	design(), va(), 
	vb(position(p).get_pointer(), (unsigned int)p.size(), usage),
	ib(indices(i).get_pointer(), (unsigned int)i.size(), usage) {}

//------------------------------------------------
// specific methods:

void render_item::set_layout(const layout& l)
{
	this->design = l;
	va.insert_buffer(vb, design);
}

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
unsigned int render_item::draw() const
{
	if (empty_layout())
		return 1;

	// draw
	return 0;
}

//------------------------------------------------
// constant methods:

bool render_item::empty_layout() const
{
	return design.get_stride() == 0;
}

const layout& render_item::get_layout() const
{
	return design;
}

#endif // !REDNDER_ITEM
