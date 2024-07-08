#pragma once
#include "pch.h"
#include "linked_list.h"
#include "bureaucracy.h"

//void insert_front();
//void insert_mddle();
//void insert_end();

template <class T>
linked_list<T>::~linked_list()
{
	node_list<T>* it = frst;
	while (it)
	{
		it = it->next;
		delete frst;
		frst = it;
	}
}

template <class T>
linked_list<T>list()
{
	this->frst = new node_list<T>;
	this->last = new node_list<T>;
	this->n = 0;
}

template <class T>
linked_list<T>::linked_list(const std::initializer_list<T>& val)
{
	this->frst = new node_list<T>(*(val.begin()));

	node_list<T>* it = frst;
	for (auto i = (*(val.begin() + 1)); i < (*(val.end())); i++)
	{
		it->next = new node_list<T>(i);
		it = it->next;
	}

	this->last = it;
	this->n = val.size();
}

template <class T>
linked_list<T>::linked_list(T* val)
{
	this->frst = new node_list<T>(*val);
	val++;
	node_list<T>* it = first;
	
	size_t i = 1;
	while (val)
	{
		it->next = new node_list<T>(*val);
		val++;
		it = it->next;
		i++;
	}

	this->last = it;
	this->n = i;
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>& l)
{
	this->frst = new node_list<T>(*l.begin());

	node_list<T>* it = first;
	for (auto i = (*(l.begin() + 1)); i < (*(l.end())); i++)
	{
		it->next = new node_list<T>(i);
		it = it->next;
	}

	this->last = it;
	this->n = l.getn();
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>&& l)
{

	this->frst = new node_list<T>(*l.begin());

	node_list<T>* it = first;
	for (auto i = (*(l.begin() + 1)); i < (*(l.end())); i++)
	{
		it->next = new node_list<T>(i);
		it = it->next;
	}

	this->last = it;
	this->n = l.getn();
	delete l;
}

//------------------------------------------------
// iterator methods:


//------------------------------------------------
// specific methods:

template <class T>
void linked_list<T>::insert(const T& value, const size_t& index)
{
	if (index == n - 1)
	{
		last->next = new node_list<T>(value);
		last = last->next;
		n++;
		return;
	}

	node_list<T>* it = frst;
	for (size_t i = 0; i + 1 < index; i++)
		it = it->next;
	if (it == nullptr)
		hard_error("bad index");
	node_list<T>* nxt = it->next;
	it->next = new node_list<T>(value);
	it = it->next;
	it->next = nxt;
}

template <class T>
void linked_list<T>::remove(const T& value, const bool& all)
{

}

template <class T>
bool search(const T& value)
{
	for (auto i : *this)
		if (i == value)
			return true;
	return false;
}

//------------------------------------------------
// constant methods:

template <class T>
T& linked_list<T>::operator [] (const size_t& index) const
{
	node_list<T>* it = this->frst;
	for (size_t i = 0; i < index; i++)
		it = it->next;
	return it->get();
}

template <class T>
size_t linked_list<T>::getn() const
{
	return n;
}

template <class T>
void   linked_list<T>::prnt() const
{
	for (auto i : *this)
		std::cout << i << ' ';
}

