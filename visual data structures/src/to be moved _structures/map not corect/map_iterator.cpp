#include "H9_map.h"
//--------------------------------------------------------------------
//ENTRY

template <class K, class V>
Map<K, V>::entry::entry(const K& key, const V& value_name)
{
	this->key_name = key;
	this->first_value = new value(value_name, nullptr);
	this->next_key = nullptr;
}

template <class K, class V>
void Map<K, V>::entry::add_value(const V& next_value)
{
	entry::value* val = this->first_value;
	if (val == nullptr)
	{
		this->first_value = new value(next_value, nullptr);
		return;
	}
	
	entry::value* nxt = val->next_val;
	if (nxt == nullptr)
	{
		nxt = new value(next_value, nullptr);
		return;
	}
	if (val->value_name == next_value) return;

	while (nxt)
	{
		if (nxt->value_name == next_value)
			return;
		val = nxt;
		nxt = nxt->next_val;
	}

	nxt = new value(next_value, nullptr);
}

template <class K, class V>
bool Map<K, V>::entry::exists_value(const V& value)
{
	entry::value* val = this->first_value;
	if (val == nullptr)
		return false;
	if (val->value_name == value)
		return true;

	entry::value* nxt = val->next_val;
	while (nxt)
	{
		if (nxt->value_name == value)
			return true;

		val = nxt;
		nxt = nxt->next_val;
	}

	return false;
}

template <class K, class V>
void Map<K, V>::entry::delete_value(const V& value)
{
	entry::value* val = this->first_value;
	if (val == nullptr)
		return;

	if (val->value_name == value)
	{
		if (val->next_val == nullptr)
		{
			delete val;
			this->first_value = nullptr;
			return;
		}
		this->first_value = this->first_value->next_val;
		delete val;
		return;
	}

	entry::value* nxt = val->next_val;
	while (nxt)
	{
		if (nxt->value_name == value)
		{
			entry::value* temp = nxt;
			nxt = nxt->next_val;
			val->next_val = nxt;
			delete temp;
			return;
		}

		val = nxt;
		nxt = nxt->next_val;
	}
}

template <class K, class V>
void Map<K, V>::entry::delete_values_recursive(value*& pointer_head)
{
	if (pointer_head == nullptr)
		return;

	this->delete_values_recursive(pointer_head->next_val);
	delete pointer_head; pointer_head = nullptr;
}

template <class K, class V>
Map<K, V>::entry::~entry()
{
	delete_values_recursive(this->first_value);
}

//--------------------------------------------------------------------
//ITERATOR

template <class K, class V>
Map<K, V>::iterator::iterator(const K& key, const V& value, const nat& index)
{
	this->iterator_key = key;
	this->iterator_value = value;
	this->iterator_index = index;
}

template <class K, class V>
void Map<K, V>::iterator::operator++()
{
	if (pointer_IT->next_key == nullptr)
		return;
	pointer_IT = pointer_IT->next_key;
	this->iterator_key = pointer_IT->key_name;
	this->iterator_value = pointer_IT->first_value->value_name;
	this->iterator_index++;
}

template <class K, class V>
bool Map<K, V>::iterator::operator!=(const iterator& second_itr)
{
	if (this->iterator_index != second_itr.iterator_index)
		return true;
	pointer_IT = first_key;
	return false;
}