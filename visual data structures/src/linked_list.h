#pragma once
#include "bureaucracy.h"
#include "node/node_list.h"
#include <initializer_list>
#include <ostream>

#define head_node nullptr // to precisely manipulate the first node of the list

template <class T = int>
class linked_list
{
	// typedefs:
	typedef const T& type;
	typedef bool (*fct)(type, type);
	typedef const linked_list<T>& lnkl;

	typedef node_list<T>* ptr;
	typedef const node_list<T>* ptr_return;

	// data members:
	node_list<T>* head, * tail;
	size_t n;

	// iterator concept:
	class iterator
	{
		node_list<T>* value;
	public:
		iterator(node_list<T>* val);

		T    operator  * () const;
		void operator ++ ();
		bool operator != (const iterator& two) const;
	};

	// auxiliar utility:
	fct compare = [](type x, type y)->bool { return x > y; };
	auto partition(ptr& head, ptr& tail);
	ptr quick_sort(ptr& head, ptr& tail);
public:
	// constructors:
	~linked_list();
	linked_list();
	linked_list(const std::initializer_list<T>& val);
	linked_list(const T* val, const size_t& val_size);
	linked_list(const linked_list<T>& l);
	linked_list(const linked_list<T>&& l);

	// iterator methods:
	iterator begin() const;
	iterator end() const;

	// modifier methods:
	void clear();
	linked_list<T>& operator = (lnkl l);
	void setf(fct f);

	// specific methods:
	void sort();	
	void atypical_insert(type value, szt index); // WARNING: atypical, time complexity O(n)
	void atypical_remove(szt index); // WARNING: atypical, time complexity O(n)

	void insert(const ptr& value, const node_list<T>* before_inserted = head_node); // traditional, time complexity O(1)
	void remove(const node_list<T>* before_removed); // traditional, time complexity O(1)

	// query operations:
	ptr_return search(type value) const;
	ptr_return mimimum() const;
	ptr_return maximum() const;
	ptr_return predcessr(ptr& value) const;
	ptr_return successor(ptr& value) const;

	// constant methods:
	bool  operator == (lnkl l) const;
	size_t getn() const;
	void*  getf() const;
	
	void   prnt() const;
	bool  empty() const;
	ptr_return get_node(szt index) const;
	ptr_return get_head() const;
	ptr_return get_tail() const;

	// friend functions:
	template <class T> friend T* convert(const linked_list<T>& l);

	template <class T> friend linked_list<T> linking(const linked_list<T>& one, const linked_list<T>& two);
	template <class T> friend linked_list<T> ejectin(const linked_list<T>& one, const linked_list<T>& two);
	template <class T> friend linked_list<T> crossng(const linked_list<T>& one, const linked_list<T>& two);

	template <class T> friend std::ostream& operator << (std::ostream& out, const linked_list<T>& l);
	template <class T> friend void* collection_ptr(const linked_list<T>& l); // just for the collection!
};

// comments:
// BEST practice: use only the object / only the node pointers
// for insert and remove methods, the head-case actually means the second node
// PAY ATTENTION - SYNTAX: "BEFORE_INSERTED", "BEFORE_REMOVED"
// how to sort: merge_sort and quick_sort_Lomuto_scheme
// allows repeating values

//------------------------------------------------
// auxiliar utility:

template <class T>
auto linked_list<T>::partition(ptr& h, ptr& t) // divides the list into two pieces
{
	// the suffix '_s' == smaller
	ptr head_s = nullptr, tail_s = nullptr, it = h;
	ptr pivot = t, previous = nullptr;
	while (it != pivot)
	{
		if (!(compare(it->get(), pivot->get()))) // it <= pivot
		{
			if (nullptr == head_s)
				head_s = it;
			previous = it;
			it = it->successor[0];
		}
		else
		{
			if (previous)
				previous->successor[0] = it->successor[0];

			ptr temp = it->successor[0];

			it->successor[0] = nullptr;
			tail->successor[0] = it;
			tail = it;

			it = temp;
		}
	}

	if (nullptr == head_s) // everything was greater than pivot
		head_s = pivot;
	tail_s = t;

	struct result{ ptr pv, hd, tl; };
	return result{ pivot, head_s, tail_s };
}

template <class T>
node_list<T>* linked_list<T>::quick_sort(ptr& h, ptr& t) // returns new head of a list
{
	if (nullptr == h || h == t)
		return h;
	auto [pivot, head_s, tail_s] = partition(h, t);
	
	if (head_s != pivot) // pivot wasn't the smallest
	{
		ptr temp = head_s;
		while (temp->successor[0] != pivot)
			temp = temp->successor[0];
		temp->successor[0] = nullptr;

		head_s = quick_sort(head_s, temp);
		
		temp = tail_s;
		temp->successor[0] = pivot;
	}

	pivot->successor[0] = quick_sort(pivot->successor[0], tail_s); // they say it is tail_s
	return head_s;
}

//------------------------------------------------
// constructors:

template <class T>
linked_list<T>::~linked_list()
{
	clear();
}

template <class T>
linked_list<T>::linked_list() : n(0), head(nullptr), tail(nullptr) {}

template <class T>
linked_list<T>::linked_list(const std::initializer_list<T>& val) : n(0), head(nullptr), tail(nullptr)
{
	this->head = new node_list<T>(*(val.begin()));

	node_list<T>* it = head;
	for (auto i = (val.begin() + 1); i < (val.end()); i++)
	{
		it->successor[0] = new node_list<T>(*i);
		it = it->successor[0];
	}

	this->tail = it;
	this->n = val.size();
}

template <class T>
linked_list<T>::linked_list(const T* val, const size_t& val_size) : n(0), head(nullptr), tail(nullptr)
{
	this->head = new node_list<T>(*val);
	val++;
	node_list<T>* it = head;

	size_t i = 1;
	while (i < val_size)
	{
		it->successor[0] = new node_list<T>(*val);
		it = it->successor[0];
		val++;
		i++;
	}

	this->tail = it;
	this->n = i;
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>& l) : n(0), head(nullptr), tail(nullptr)
{
	this->head = new node_list<T>(*l.begin());

	node_list<T>* it = head;
	bool first_element = true;
	for (auto i : l)
	{
		if (first_element == false)
		{
			it->successor[0] = new node_list<T>(i);
			it = it->successor[0];
		}

		first_element = false;
	}

	this->tail = it;
	this->n = l.getn();
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>&& l) : n(0), head(nullptr), tail(nullptr)
{
	this->head = new node_list<T>(*l.begin());

	node_list<T>* it = head;
	bool first_element = true;
	for (auto i : l)
	{
		if (first_element == false)
		{
			it->successor[0] = new node_list<T>(i);
			it = it->successor[0];
		}

		first_element = false;
	}

	this->tail = it;
	this->n = l.getn();
}

//------------------------------------------------
// iterator methods:

template <class T>
linked_list<T>::iterator::iterator(node_list<T>* val) : value(val) {};

template <class T>
T linked_list<T>::iterator::operator * () const
{
	return value->get();
}

template <class T>
void linked_list<T>::iterator::operator ++ ()
{
	value = value->successor[0];
}

template <class T>
bool linked_list<T>::iterator::operator != (const iterator& two) const
{
	return value != two.value;
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::begin() const
{
	return iterator(head);
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::end() const
{
	return iterator(tail->successor[0]); // nullptr
}

//------------------------------------------------
// modifier methods:

template <class T>
void linked_list<T>::clear()
{
	ptr it = head;
	while (it)
	{
		it = it->successor[0];
		delete head;
		head = it;
		n--;
	}
	head = tail = nullptr;
}

template <class T>
linked_list<T>& linked_list<T>::operator = (lnkl l)
{
	clear();
	this->head = new node_list<T>(*l.begin());

	node_list<T>* it = head;
	bool first_element = true;
	for (auto i : l)
	{
		if (first_element == false)
		{
			it->successor[0] = new node_list<T>(i);
			it = it->successor[0];
		}

		first_element = false;
	}

	this->tail = it;
	this->n = l.getn();
	return *this;
}

template <class T>
void linked_list<T>::setf(fct f)
{
	this->compare = f;
}

//------------------------------------------------
// specific methods:

template <class T>
void linked_list<T>::sort()
{
	quick_sort(head, tail);
}

template <class T>
void linked_list<T>::atypical_insert(type value, szt index)
{
	// optimisation:
	if (index == n)
	{
		tail->successor[0] = new node_list<T>(value);
		tail = tail->successor[0];
		n++;
		return;
	}

	if (index == 0)
	{
		node_list<T>* it = new node_list<T>(value);
		it->successor[0] = head;
		head = it;
		n++;
		return;
	}

	node_list<T>* it = head;
	for (size_t i = 0; i + 1 < index; i++)
		it = it->successor[0];
	if (it == nullptr)
		hard_error("bad index");

	node_list<T>* nxt = it->successor[0];
	it->successor[0] = new node_list<T>(value);
	it = it->successor[0];
	it->successor[0] = nxt;
	n++;
}

template <class T>
void linked_list<T>::atypical_remove(szt index)
{
	if (index >= n || index < 0)
	{
		eazy_error("bad index");
		return;
	}

	// deleting the first element
	if (index == 0)
	{
		node_list<T>* it = head;
		head = head->successor[0];
		delete it;
		n--;
		return;
	}

	node_list<T>* it = head;
	for (size_t i = 0; i + 1 < index; i++)
		it = it->successor[0];
	node_list<T>* nxt = it->successor[0];
	it->successor[0] = nxt->successor[0];
	delete nxt;
	n--;
}

template <class T>
void linked_list<T>::insert(const ptr& value, const node_list<T>* before_inserted)
{
	n++;
	ptr actual = new node_list<float>(value->get()); // if value has successors

	// case head_node
	if (before_inserted == head_node)
	{
		if (empty())
		{
			head = tail = actual;
			return;
		}

		actual->successor[0] = head; // not empty => insert as a first node
		head = actual;
		return;
	}

	// case head
	if (before_inserted == head)
	{
		actual->successor[0] = head->successor[0];
		head->successor[0] = actual;
		return;
	}

	// case tail
	if (before_inserted == tail)
	{
		tail = tail->successor[0] = actual;
		return;
	}

	// case mid
	actual->successor[0] = before_inserted->successor[0];

	node_list<T>* bfr_insert = const_cast<node_list<T>*>(before_inserted);
	bfr_insert->successor[0] = actual;
}

template <class T>
void linked_list<T>::remove(const node_list<T>* before_removed)
{
	if (empty())
		fatal_error("no more memory");
	n--;

	// case head_node
	if (before_removed == head_node)
	{
		ptr it = head;
		head = head->successor[0];
		delete it;
		return;
	}
	
	// case tail 
	if (before_removed->successor[0] == tail)
	{
		delete tail;
		tail = const_cast<node_list<T>*>(before_removed);
		tail->successor[0] = nullptr;
		return;
	}

	// case mid
	ptr it = before_removed->successor[0];
	
	node_list<T>* bfr_remove = const_cast<node_list<T>*>(before_removed);
	bfr_remove->successor[0] = it->successor[0];
	delete it;
	return;
}

//------------------------------------------------
// query operations:

template <class T>
const node_list<T>* linked_list<T>::search(type value) const
{
	auto it = head;
	FOR(n)
	{
		if (it->get() == value)
			return it;
		it = it->successor[0];
	}
	
	return nullptr;
}

template <class T>
const node_list<T>* linked_list<T>::mimimum() const
{
	ptr minimum = head;
	for (ptr it = head; it; it = it->successor[0])
		if (compare(minimum->get(), it->get()))
			minimum = it;
	return minimum;
}

template <class T>
const node_list<T>* linked_list<T>::maximum() const
{
	ptr maximum = head;
	for (ptr it = head; it; it = it->successor[0])
		if (compare(it->get(), maximum->get()))
			maximum = it;
	return maximum;
}

template <class T>
const node_list<T>* linked_list<T>::predcessr(ptr& value) const
{
	ptr node = nullptr;
	for (ptr it = head; it; it = it->successor[0])
	{
		if (compare(value->get(), it->get())) // it < value
		{
			if (node == nullptr)
				node = it;
			if (comapre(it->get(), node->get()))
				node = it;
		}
	}

	return node;
}

template <class T>
const node_list<T>* linked_list<T>::successor(ptr& value) const
{
	ptr node = nullptr;
	for (ptr it = head; it; it = it->successor[0])
		if (compare(it->get(), value->get())) // it > value
		{
			if (node == nullptr)
				node = it;
			if (comapre(node->get(), it->get()))
				node = it;
		}

	return node;
}

//------------------------------------------------
// constant methods:

template <class T>
bool linked_list<T>::operator == (lnkl l) const
{
	if (this->n != l.n || this->head->get())
		return false;

	node_list<T>* it = head;
	for (auto i : l)
	{
		if (it->get() != i)
			return false;
		it = it->successor[0];
	}

	return true;
}

template <class T>
size_t linked_list<T>::getn() const
{
	return n;
}

template <class T>
void* linked_list<T>::getf() const
{
	return this->compare;
}

template <class T>
void linked_list<T>::prnt() const
{
	for (ptr it = head; it; it = it->successor[0])
		std::cout << it->get() << ' ';
	std::cout << '\n';
}

template <class T>
bool linked_list<T>::empty() const
{
	return n == 0;
}

template <class T>
const node_list<T>* linked_list<T>::get_node(szt index) const
{
	if (index > n)
		hard_error("bad index");
	const node_list<T>* it = this->get_head();
	FOR(index)
		it = it->successor[0];
	return it;
}

template <class T>
const node_list<T>* linked_list<T>::get_head() const
{
	return head;
}

template <class T>
const node_list<T>* linked_list<T>::get_tail() const
{
	return tail;
}

//------------------------------------------------
// friend functions:

template <class T>
T* convert(const linked_list<T>& l)
{
	T* ptr = new T[n]{};
	size_t index = 0;
	for (auto i : l)
		ptr[index++] = i;
	return ptr;
}

template <class T>
linked_list<T> linking(const linked_list<T>& one, const linked_list<T>& two)
{
	linked_list<T> new_list(one);
	new_list.tail->successor[0] = two.head;
	new_list.n += two.n;
	new_list.tail = two.tail;
	return new_list;
}

template <class T>
linked_list<T> ejectin(const linked_list<T>& one, const linked_list<T>& two)
{
	linked_list<T> new_list(one);

	for (node_list<T>* it_two = two.head; it_two; it_two = it_two->successor[0])
		for (node_list<T>* it = new_list.head; it; it = it->successor[0])
		{
			// patch
			while (new_list.head->get() == it_two->get())
			{
				new_list.remove(head_node);
				it = new_list.head;
			}

			if (it->successor[0]->get() == it_two->get())
				new_list.remove(it);
		}

	return new_list;
}

template <class T>
linked_list<T> crossng(const linked_list<T>& one, const linked_list<T>& two)
{
	linked_list<T> new_list;

	for (node_list<T>* it_two = two.head; it_two; it_two = it_two->successor[0])
		for (node_list<T>* it = one.head; it; it = it->successor[0])
		{
			if (it->get() == it_two->get())
				new_list.insert(it);
		}

	return new_list;
}

template <class T>
std::ostream& operator << (std::ostream& out, const linked_list<T>& l)
{
	node_list<T>* it = l.head;
	while (it)
	{
		out << it->get() << ' ';
		it = it->successor[0];
	}

	out << '\n';
	return out;
}

template <class T>
void* collection_ptr(const linked_list<T>& l)
{
	return (void*)head;
}
