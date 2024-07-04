#include "H7_tree.h"
#include <stdio.h>

//-------------------------------------------------------------------------------------

template <class T>
tree<T>::node::node()
{
	this->info = NULL;
	for (size_t i = 0; i < MAX; i++)
		this->children[i] = nullptr;
}

template <class T>
tree<T>::node::node(T value)
{
	this->info = value;
	for (size_t i = 0; i < MAX; i++)
		this->children[i] = nullptr;
}

template <class T>
bool tree<T>::node::operator < (const node*& first) const
{
	if (this->info && first->info)
		return this->info < first->info;
	return false;
}

//-------------------------------------------------------------------------------------

template <class T>
void tree<T>::add_node(node* parent, T value)
{
	if (parent == nullptr)
	{
		this->root = new node(value);
		return;
	}

	size_t index_nullptr = 0;
	while (parent->children[index_nullptr])
		index_nullptr++;

	parent->children[index_nullptr] = new node(value);
}

template <class T>
void tree<T>::insert(node* parent, size_t index, T value) 
{
	if (parent == nullptr)
	{
		this->root = new node(value);
		return;
	}

	delete parent->children[index]; 
	parent->children[index] = new node(value);
}

// get_node

template <class T> 
bool is_equal(const T& first_value, const T& second_value) // for find !!!!!!!!!!!!!!!!!!!!!!!
{
	return (first_value == second_value);
}

// find

template <class T>
void tree<T>::sort(node* parent, bool (*function)(const node*&, const node*&))
{
	//if (function == nullptr)
		//function = this->compare; // operator < !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	bool swapped = false;
	do
	{
		swapped = false;
		for (size_t i = 0; parent->children[i]; i++)
		{
			T* current = &parent->children[i]->info;
			T* next = &parent->children[i + 1]->info;

			if (*next < *current)
			{
				swapped = true;
				T temp = *next;
				*next = *current;
				*current = temp;
			}
		}
	}
	while (swapped);
}

template <class T>
size_t tree<T>::cunt(node*& parent) const
{
	size_t index = 0;
	while (parent->children[index])
		index++;
	return index - 1;
}

template <class T>
void  tree<T>::delete_node(node* parent)
{
	if (parent == nullptr)
		return;
	else
	{
		size_t index = 0;
		while (parent->children[index])
		{
			delete_node(parent->children[index]);
			index++;
		}
	}
}

template <class T>
tree<T>::~tree()
{
	delete this->root;
}