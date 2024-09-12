#pragma once
#include "bureaucracy.h"

#include "class_methods/abstract class methods.h/modifier_methods.h"
#include "class_methods/linked_list_methods/linked_list_specific.h"
#include "class_methods/linked_list_methods/linked_list_constant.h"
#include "class_methods/linked_list_methods/linked_list_queries.h"
#include "class_methods/abstract class methods.h/instance_synergy.h"
#include "class_methods/abstract class methods.h/iterator_methods.h"

#include "iterators/linked_list_iterator.h"

#include "node/node_list.h"
#include "data_structure.h"
#include <initializer_list>

/* comments:
	- BEST PRACTICE: use only the object / only the node pointers
	- CHECK NULLPTR: before inserting and deleting!
	- PAY ATTENTION: "BEFORE_INSERTED", "BEFORE_REMOVED"
	
	- used quick sort lomuto scheme (future alternative: merge sort)
	- allows repeating values
*/

template <class T = int>
class linked_list : public data_structure <modifier_methods<T, linked_list<T>>, linked_list_specific<node_list<T>>,
	linked_list_constant<T, linked_list<T>, node_list<T>>, linked_list_queries<T, node_list<T>>,
	instance_synergy<linked_list<T>>, iterator_methods<linked_list_iterator<T>>>
{
	// typedefs:
	structure_typedefs;
	typedef node_list<T>* ptr;
	typedef const node_list<T>* ptr_return;

public:
	// constructors:
	~linked_list();
	linked_list();
	linked_list(const std::initializer_list<T>& data);
	linked_list(const T* data, szt data_size);
	linked_list(const linked_list<T>& l);
	linked_list(const linked_list<T>&& l) noexcept;

	// modifier methods:
	linked_list<T>& operator = (const linked_list<T>& l);
	linked_list<T>& clear();
	linked_list<T>& set_f(fct f);

	// specific methods:
	linked_list<T>& sort();
	linked_list<T>& insert(const node_list<T>* const value, node_list<T>* const before_inserted = head_node); // traditional, time complexity O(1)
	linked_list<T>& remove(node_list<T>* before_removed); // traditional, time complexity O(1)

	linked_list<T>& atypical_insert(t value, szt index); // WARNING: atypical, time complexity O(n)
	linked_list<T>& atypical_remove(szt index); // WARNING: atypical, time complexity O(n)

	// constant methods:
	bool   operator == (const linked_list<T>& l) const;
	size_t get_n() const;
	void*  get_f() const;
	bool   empty() const;
	void   print() const;

	ptr_return get_node(szt index) const;
	ptr_return get_head() const;
	ptr_return get_tail() const;

	// query operations:
	ptr_return search(t value) const;
	ptr_return mimimum() const;
	ptr_return maximum() const;
	ptr_return predcessr(const node_list<T>*& value) const;
	ptr_return successor(const node_list<T>*& value) const;

	// instance synergy:
	linked_list<T>& integrates(const linked_list<T>& l);
	linked_list<T>& eliminates(const linked_list<T>& l);
	linked_list<T>& intersects(const linked_list<T>& l);

	// iterator methods:
	linked_list_iterator<T> begin() const;
	linked_list_iterator<T> end() const;

	// friend functions:
	template <class T> friend T* convert(const linked_list<T>& l);
	template <class T> friend std::ostream& operator << (std::ostream& out, const linked_list<T>& l);
	template <class T> friend void* collection_ptr(const linked_list<T>& l); // just for the collection!

private:
	// data members:
	node_list<T>* head;
	node_list<T>* tail;
	size_t n;

	// auxiliar utility:
	fct compare;
	auto partition(node_list<T>*& head_b, node_list<T>*& tail_b);
	node_list<T>* quick_sort(node_list<T>*& head_b, node_list<T>*& tail_b);

public:
	static node_list<T>* const head_node;
};

//------------------------------------------------
// constructors:

template <class T>
linked_list<T>::~linked_list()
{
	clear();
}

template <class T>
linked_list<T>::linked_list() : head(nullptr), tail(nullptr), 
	n(0), compare([](t x, t y)->bool { return x > y; }) {}

template <class T>
linked_list<T>::linked_list(const std::initializer_list<T>& data) : linked_list<T>()
{
	this->head = new node_list<T>(*(data.begin()));

	node_list<T>* it = head;
	for (auto i = (data.begin() + 1); i < (data.end()); i++)
	{
		it->successor[0] = new node_list<T>(*i);
		it = it->successor[0];
	}

	this->tail = it;
	this->n = data.size();
}

template <class T>
linked_list<T>::linked_list(const T* data, szt data_size) : linked_list<T>()
{
	this->head = new node_list<T>(*data);
	data++;
	node_list<T>* it = head;

	size_t i = 1;
	while (i < data_size)
	{
		it->successor[0] = new node_list<T>(*data);
		it = it->successor[0];
		data++;
		i++;
	}

	this->tail = it;
	this->n = i;
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>& l) : linked_list<T>()
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
	this->n = l.n;
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>&& l) noexcept : linked_list<T>()
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
// modifier methods:

template <class T>
linked_list<T>& linked_list<T>::operator = (const linked_list<T>& l)
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
	this->n = l.n;
	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::clear()
{
	ptr it = head;
	while (it)
	{
		head = it;
		it = it->successor[0];
		delete head;
		n--;
	}

	head = tail = nullptr;
	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::set_f(fct f)
{
	this->compare = f;
	return *this;
}

//------------------------------------------------
// specific methods:

template <class T>
linked_list<T>& linked_list<T>::sort()
{
	quick_sort(head, tail);
	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::insert(const node_list<T>* const value, node_list<T>* const before_inserted)
{
	ptr actual = new node_list<T>(value->get()); // if value has successors

	// case head_node
	if (before_inserted == head_node)
	{
		if (empty())
		{
			n++;
			head = tail = actual;
			return *this;
		}

		n++;
		actual->successor[0] = head; // not empty => insert as a first node
		head = actual;
		return *this;
	}

	// general case
	n++;
	actual->successor[0] = before_inserted->successor[0];
	before_inserted->successor[0] = actual;
	if (nullptr == actual->successor[0])
		tail = actual;

	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::remove(node_list<T>* before_removed)
{
	if (empty())
		return *this;
	
	n--;

	// case head
	if (before_removed == head_node)
	{
		ptr it = head;
		head = head->successor[0];
		delete it;
		if (nullptr == head)
			tail = head;
		return *this;
	}

	// case mid
	ptr it = before_removed->successor[0];
	before_removed->successor[0] = it->successor[0];
	delete it;

	// case tail 
	if (nullptr == before_removed->successor[0])
		tail = before_removed;

	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::atypical_insert(t value, szt index)
{
	// optimisation:
	if (index == n)
	{
		tail->successor[0] = new node_list<T>(value);
		tail = tail->successor[0];
		n++;	
		return *this;
	}

	if (index == 0)
	{
		node_list<T>* it = new node_list<T>(value);
		it->successor[0] = head;
		head = it;
		n++;
		return *this;

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
	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::atypical_remove(szt index)
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

//------------------------------------------------
// constant methods:

template <class T>
bool linked_list<T>::operator == (const linked_list<T>& l) const
{
	if (this->n != l.n)
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
size_t linked_list<T>::get_n() const
{
	return n;
}

template <class T>
void* linked_list<T>::get_f() const
{
	return this->compare;
}

template <class T>
bool linked_list<T>::empty() const
{
	return n == 0;
}

template <class T>
void linked_list<T>::print() const
{
	for (ptr it = head; it; it = it->successor[0])
		std::cout << it->get() << ' ';
	std::cout << '\n';
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
// query operations:

template <class T>
const node_list<T>* linked_list<T>::search(t value) const
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
const node_list<T>* linked_list<T>::predcessr(const node_list<T>*& value) const
{
	ptr node = nullptr;
	for (ptr it = head; it; it = it->successor[0])
	{
		if (compare(value->get(), it->get())) // it < value
		{
			if (nullptr == node)
				node = it;
			if (compare(it->get(), node->get()))
				node = it;
		}
	}

	return node;
}

template <class T>
const node_list<T>* linked_list<T>::successor(const node_list<T>*& value) const
{
	ptr node = nullptr;
	for (ptr it = head; it; it = it->successor[0])
		if (compare(it->get(), value->get())) // it > value
		{
			if (node == nullptr)
				node = it;
			if (compare(node->get(), it->get()))
				node = it;
		}

	return node;
}

//------------------------------------------------
// instance synergy:

template <class T>
linked_list<T>& linked_list<T>::integrates(const linked_list<T>& l) 
{
	for (auto value : l)
	{
		ptr it = new node_list<T>(value);
		tail = this->tail->successor[0] = it;
		this->n++;
	}

	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::eliminates(const linked_list<T>& l) 
{
	for (node_list<T>* it_two = l.head; it_two; it_two = it_two->successor[0])
		for (node_list<T>* it = this->head; it; it = it->successor[0])
		{
			while (this->head->get() == it_two->get())
			{
				this->remove(head_node);
				it = this->head;
			}

			if (it->successor[0]->get() == it_two->get())
				this->remove(it);
		}

	return *this;
}



template <class T>
linked_list<T>& linked_list<T>::intersects(const linked_list<T>& l) 
{
	ptr new_head = nullptr, new_tail = nullptr, new_it = nullptr;
	size_t new_n = 0;

	for (ptr it_two = l.head; it_two; it_two = it_two->successor[0])
		for (ptr it = this->head; it; it = it->successor[0])
		{
			if (it->get() == it_two->get())
			{
				new_it = new node_list<T>(it->get());
				new_head = 0 == new_n ? new_it : new_head;
				new_tail = new_it;
				new_n++;
			}
		}

	this->clear();
	this->head = new_head;
	this->tail = new_tail;
	this->n = new_n;
	return *this;
}

//------------------------------------------------
// iterator methods:

template <class T>
linked_list_iterator<T> linked_list<T>::begin() const
{
	return const_cast<node_list<T>*>(head);
}

template <class T>
linked_list_iterator<T> linked_list<T>::end() const
{
	return tail->successor[0]; // nullptr
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

//------------------------------------------------
// auxiliar utility:

template <class T>
auto linked_list<T>::partition(node_list<T>*& head_b, node_list<T>*& tail_b) // divides the list into two pieces
{
	// the suffix '_s' == smaller
	ptr head_s = nullptr, tail_s = nullptr, it = head_b;
	ptr pivot = tail_b, previous = nullptr;
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
	tail_s = tail_b;

	struct result { ptr pv, hd, tl; };
	return result{ pivot, head_s, tail_s };
}

template <class T>
node_list<T>* linked_list<T>::quick_sort(node_list<T>*& head_b, node_list<T>*& tail_b) // returns new head of a list
{
	if (nullptr == head_b || head_b == tail_b)
		return head_b;
	auto [pivot, head_s, tail_s] = partition(head_b, tail_b);

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

template <class T>
node_list<T>* const linked_list<T>::head_node = nullptr;
