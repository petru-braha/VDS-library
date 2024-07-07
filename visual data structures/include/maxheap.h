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

template <class T>
class maxheap
{
	typedef iterator_maxheap it;
	typedef const T& type;
protected:
	size_t n;
	size_t last;
	T* values;

	void heapify(const size_t& n, const size_t& index); // we need f here
public:
	bool (*f)(type, type);
	// constructors 
	maxheap(const size_t& n = default_heap_size);
	maxheap(const std::initializer_list<T>& val, const size_t& n = default_heap_size, bool (*f)(type, type) = nullptr);
	maxheap(T* val, const size_t& n = default_heap_size, bool (*f)(type, type) = nullptr);
	maxheap(const maxheap<T>& h);
	maxheap(const maxheap<T>&& h);
	~maxheap();

	// iterator methods
	it begin() const;
	it end() const;

	// specific methods
	void insert(const T& value);
	void extrct();

	// constant methods
	size_t getn() const;
	size_t getl() const;
	void   prnt() const;
	bool  empty() const;

	// friend functions
	friend maxheap<T> linking(const maxheap<T>& one, const maxheap<T>& two);
	friend maxheap<T> ejectin(const maxheap<T>& one, const maxheap<T>& two);
	friend maxheap<T> crossng(const maxheap<T>& one, const maxheap<T>& two);
};

// other methods that can be designed: parent(index), height(), search(), replace(), property(), 