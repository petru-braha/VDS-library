#pragma once
#define MAX 300

template <class T>
class tree
{
	struct node {
		T info;
		node* children[MAX];
		node();
		node(T value);
		bool operator < (const node*& first) const;
	};

public:
	static node* root;
	bool compare(const node*& first, const node*& second) const { return first < second; } //uses the operator

	tree() { this->root = new node; }
	tree(T value) { this->root = new node(value); }
	void   add_node(node* parent, T value);
	void   insert(node* parent, size_t index, T value);
	
	node*  get_node(node*& parent, size_t index_child) const
	{
		if (parent == nullptr)
			return this->root;

		return parent->children[index_child];
	}

	node*  find(node* parent, const T& value, bool (*function)(const T&, const T&))
	{
		if (parent == nullptr)
			return nullptr;
		else
		{
			if (function(parent->info, value))
				return parent;

			node* found_node = nullptr;
			size_t index_child = 0;

			while (found_node == nullptr && parent->children[index_child])
			{
				found_node = this->find(parent->children[index_child], value, function);
				index_child++;
			}

			return found_node;
		}
	}
	
	void   sort(node* parent, bool (*function)(const node*&, const node*&));
	size_t cunt(node*& parent) const;

	void  delete_node(node* parent);
	~tree();
};

template <class T>
bool is_equal(const T& first_value, const T& second_value);