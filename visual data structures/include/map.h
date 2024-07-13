#pragma once
typedef unsigned int nat;

template <class K, class V>
class Map
{
	
protected:
	struct entry
	{
		struct value
		{
			V value_name;
			value* next_val;

			value(const V& next_value):value_name(next_value), next_val(nullptr) {}
			value(const V& next_value, value* nxt):value_name(next_value), next_val(nxt) {}
		};

		K key_name;
		entry* next_key;
		value* first_value;

		entry(const K& key, const V& value_name);

		void add_value(const V& next_value); // checks if the value already exists
		bool exists_value(const V& value);

		void delete_value(const V& value);
		void delete_values_recursive(value*& pointer_head);
		~entry();
	};
	typedef entry* pointer_entry;

	static entry* first_key;
	static entry* pointer_IT; // helps iteration
	
	pointer_entry add_key(const K& key, const V& value);

public:
	struct iterator
	{
		K iterator_key;
		V iterator_value;
		nat iterator_index;
		iterator(const K& key, const V& value, const nat& index);
		iterator operator*() { return { iterator_key, iterator_value, iterator_index }; }
		void operator++();
		bool operator!=(const iterator& second_itr);
	};
	
	Map();
	void Set(const K& key, const V& value) { this->add_key(key, value); }
	bool Get(const K& key, V& value);
	bool Includes(const Map<K, V>& map);
	
	V& operator[](const K& key);
	iterator begin();
	iterator end()const;

	void print(const K& key);
	int  Count()const;
	bool Delete(const K& key);
	void Clear(); // everything
	~Map() { this->Clear(); }
};

// map = multiple keys // key = multiple values
// key == entry

// adding an entry + add a second one null