#pragma once
#define default_heap_size 100

template <class T = int>
class iterator_maxheap
{
	T* value;
public:
	iterator_maxheap(T*& val) : value(val) {};

	T		operator * () { return *value; }
	void	operator ++() { value++; }
	bool	operator !=(const iterator_maxheap& two) { return value != two.value; }
};

template <class T = int>
class maxheap
{
	typedef iterator_maxheap<T> it;
	typedef const T& type;
protected:
	size_t n;
	size_t last;
	T* values;

	void heapify(const size_t& nnn, const size_t& index); // we need f here
public:
	bool (*f)(type, type);
	// constructors:
	maxheap(const size_t& n = default_heap_size);
	maxheap(const std::initializer_list<T>& val, const size_t& n = default_heap_size, bool (*f)(type, type) = nullptr);
	maxheap(T* val, const size_t& n = default_heap_size, bool (*f)(type, type) = nullptr);
	maxheap(const maxheap<T>& h);
	maxheap(const maxheap<T>&& h);
	~maxheap();

	// iterator methods:
	it begin() const;
	it end() const;

	// specific methods:
	maxheap<T>& operator = (const maxheap<T>& h);
	void replce(const size_t& index, const T& value);
	void insert(const T& value);
	void extrct();
	bool search(const T& value);

	// constant methods:
	bool operator == (const maxheap<T>& h) const;
	size_t getn() const;
	size_t getl() const;
	void   prnt() const;
	bool  empty() const;
};

// parent(index) == floor( (index - 1) / 2 )
// height()      == floor( log2(n) )
// property()    == it is never broken