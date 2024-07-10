#pragma once
#define default_heap_size 100

template <class T = int>
class maxheap
{
	typedef const T& type;

	size_t n;
	size_t last;
	T* values;

	class iterator
	{
		T* value;
	public:
		iterator(T* val);

		T		operator * () const;
		void	operator ++();
		bool	operator !=(const iterator& two) const;
	};

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
	iterator begin() const;
	iterator end() const;

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