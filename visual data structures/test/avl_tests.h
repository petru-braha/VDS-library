#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "avl.h"

/*								1
		-1.01									255

	-2			-0.99					1.01			65535
			-1		  0.99
*/

class avl__p : public Test
{
protected:
	typedef node_avlt<float> n;
	typedef node_avlt<float>* p;
	avl<float> numbers;
	
	~avl__p() = default;
	avl__p();
};

//------------------------------------------------
// constructors:

avl__p::avl__p() : numbers(list_numbers) {}

//------------------------------------------------
// tests:

TEST_F(avl__p, constructors)
{
	EXPECT_FALSE(numbers.empty());
	EXPECT_EQ(numbers.get_n(), 9);

	auto it = numbers.get_r();
	EXPECT_EQ(it->get(), 1); 

	it = it->successor[left_child];
	it = it->successor[rght_child];
	it = it->successor[left_child];
	EXPECT_EQ(it->get(), -1);

	avl<float> extra(block_numbers, classic_size);
	numbers = extra;
	it = numbers.get_r();
	it = numbers.search(it, -0.99f);
	it = it->successor[left_child];
	
	EXPECT_EQ(it->get(), -1);
	EXPECT_EQ(numbers.get_n(), 9);
	EXPECT_EQ(numbers, extra);

	extra = avl<float>(avl<float>(avl<float>(list_numbers)));
	ASSERT_EQ(numbers, extra);
}

TEST_F(avl__p, clear)
{
	numbers.clear();

	EXPECT_TRUE(numbers.empty());
	EXPECT_EQ(nullptr, numbers.get_r());
	ASSERT_EQ(0, numbers.get_n());
}

TEST_F(avl__p, insert1)
{
	n node0(insertions[0]);
	n node1(insertions[1]);
	n node2(insertions[2]);
	n node3(insertions[3]);
	n node4(insertions[4]);

	numbers.insert(&node0);
	numbers.insert(&node1); // left rotation
	
	auto it = numbers.get_r()->successor[rght_child];
	it = it->successor[left_child];
	EXPECT_EQ(it->get(), node0.get());
	EXPECT_EQ(it->successor[rght_child]->get(), node1.get());

	numbers.insert(&node2); // right rotation 
	numbers.insert(&node3);
	numbers.insert(&node4); // left right rotation

	it = numbers.get_r()->successor[rght_child]
		->successor[rght_child];
	it = it->successor[left_child]->successor[left_child];
	EXPECT_EQ(it->get(), 10.6f);
}

/*										1

		-1.01													10.5

	-2			-0.99						1.01									255
			-1		  0.99						10.4						10.7			65535
																		10.6	10.8
*/

TEST_F(avl__p, insert2)
{
	// insert the same value which should not work
	size_t past_n = numbers.get_n();
	
	auto it = numbers.get_r();
	numbers.insert(it);

	EXPECT_EQ(numbers.get_n(), past_n) << "inserting the same values should not work.\n";

	// insert without rebalance
	it = new n(999999.0f);
	numbers.insert(it);
	it = numbers.get_r();
	it = it->successor[rght_child]->successor[rght_child]->successor[rght_child];

	EXPECT_NE(it, nullptr) << "\"it\" represents -5.0f.\n";
	EXPECT_EQ(it->get(), 999999.0f);
	EXPECT_EQ(numbers.get_n(), 10);

	// insert and rebalance
	it = new n(0.999f);
	numbers.insert(it);
	it = numbers.get_r()->successor[left_child];

	EXPECT_EQ(numbers.get_n(), 11);
	EXPECT_EQ(it->successor[left_child]->get(), -1.01f);
	EXPECT_EQ(it->successor[rght_child]->get(), 0.99f);

	it = it->successor[rght_child];
	EXPECT_EQ(it->successor[left_child], nullptr);
	EXPECT_EQ(it->successor[rght_child]->get(), 0.999f);
}

/* to visualize */

TEST_F(avl__p, remove1)
{
	n node0(-1);
	n node1(1);
	n node2(1.01f);
	n node3(9999); // non existent value

	numbers.remove(&node0);
	numbers.remove(&node1); // root
	numbers.remove(&node2); // root and right left rotation

	auto it = numbers.get_r();
	EXPECT_EQ(it->get(), -0.99f);
	EXPECT_EQ(it->get(), -0.99f);
	EXPECT_EQ(it->successor[rght_child]
		->successor[left_child]->get(), 0.99f);
	EXPECT_EQ(it->successor[left_child]->get(), -1.01f);
	ASSERT_EQ(numbers.get_n(), 6);
}

/*							-0.99
				-1.01					255
			-2						0.99	65535
*/

TEST_F(avl__p, remove2)
{
	// remove root
	auto temp = numbers.successor(numbers.get_r())->get();
	
	auto it = numbers.get_r();
	numbers.remove(it);
	it = numbers.get_r();

	EXPECT_EQ(it->get(), temp);
	EXPECT_EQ(numbers.get_n(), 8);
	
	// remove leaf and rebalance
	it = it->successor[rght_child]->successor[rght_child];
	numbers.remove(it);
	it = numbers.get_r();

	EXPECT_EQ(it->get(), -0.99f);
	EXPECT_EQ(numbers.get_n(), 7);

	// remove middle node and rebalance
	it = it->successor[left_child];
	numbers.remove(it->successor[left_child]);
	numbers.remove(it->successor[rght_child]);
	numbers.remove(it);
	it = numbers.get_r();
	
	EXPECT_EQ(numbers.height(it), 3);
	EXPECT_EQ(it->get(), 1.01f);
	EXPECT_EQ(numbers.get_n(), 4);

	EXPECT_EQ(it->successor[left_child]->get(), -0.99f);
	EXPECT_EQ(it->successor[rght_child]->get(), UCHAR_MAX);
}

/* to visualize */

TEST_F(avl__p, queries)
{
	auto it = numbers.search(numbers.get_r(), -1);
	EXPECT_NE(nullptr, it);
	EXPECT_EQ(it->get(), -1);
	
	it = numbers.get_r();
	it = it->successor[left_child]->successor[left_child];
	EXPECT_EQ(it, numbers.minimum());

	it = numbers.get_r();
	it = it->successor[rght_child]->successor[rght_child];
	EXPECT_EQ(it, numbers.maximum());

	it = numbers.get_r()->successor[left_child]
		->successor[rght_child]->successor[rght_child];
	EXPECT_EQ(it, numbers.predcessr(numbers.get_r()));
	
	it = numbers.get_r()->successor[rght_child]
		->successor[left_child];
	EXPECT_EQ(it, numbers.successor(numbers.get_r()));
}

TEST(avl_p, instances)
{
	avl<> first = friend_values1;
	avl<> secnd = friend_values2;
	avl<> temp;

	temp = first;
	temp.integrates(secnd);
	EXPECT_EQ(temp.get_n(), 9);
	int integer = 1;
	for (auto value : temp)
		EXPECT_EQ(value, integer++);

	temp = first;
	temp.eliminates(secnd);
	EXPECT_EQ(temp.get_n(), 4);

	temp = first;
	temp.intersects(secnd);
	EXPECT_EQ(temp.get_n(), 1);
}

TEST_F(avl__p, functions)
{
	float* data = convert(numbers);

	for(auto value : numbers)
	{
		EXPECT_EQ(value, *data);
		data++;
	}

	void* ptr = collection_ptr(numbers);
	EXPECT_EQ(((p)ptr)->get(), numbers.get_r()->get());
}

//------------------------------------------------
// next class:

class avl__c : public Test
{
protected:
    avl<convoluted> objects;

    void TearDown();
	avl__c();
};

//------------------------------------------------
// constructors:

void avl__c::TearDown() {}

avl__c::avl__c() : objects(list_objects, 10) {}

//------------------------------------------------
// tests:

TEST_F(avl__c, queries)
{
    objects.set_f(compare_numbr);
    //EXPECT_EQ(objects.minimum(), 6);
    //EXPECT_EQ(objects.maximum(), 0);

    objects.set_f(compare_addss);
    //EXPECT_EQ(objects.predcessr(8), 5);
    //EXPECT_EQ(objects.successor(9), 1);
}
