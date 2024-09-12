#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "avl.h"

class avl_evaluation_p : public Test
{
protected:
	typedef node_avlt<float> n;
	typedef node_avlt<float>* p;
	avl<float> numbers;
	
	~avl_evaluation_p() = default;
	avl_evaluation_p();
};

//------------------------------------------------
// constructors:

avl_evaluation_p::avl_evaluation_p() : numbers(list_numbers) {}

//------------------------------------------------
// tests:

TEST_F(avl_evaluation_p, constructors)
{
	EXPECT_FALSE(numbers.empty());
	EXPECT_EQ(numbers.get_n(), 9);

	auto it = numbers.get_r();
	EXPECT_EQ(it->get(), 1); 

	it = it->successor[left_child];
	it = it->successor[rght_child];
	it = it->successor[left_child];
	EXPECT_EQ(it->get(), -1);

	avl<float> temp(block_numbers, classic_size);
	//numbers = temp;
	it = numbers.get_r();
	it = numbers.search(it, -0.99f);
	it = it->successor[left_child];
	
	EXPECT_EQ(it->get(), -1);
	EXPECT_EQ(numbers.get_n(), 9);
	ASSERT_TRUE(numbers == temp);
}

TEST_F(avl_evaluation_p, clear_method)
{
	numbers.clear();

	EXPECT_TRUE(numbers.empty());
	EXPECT_EQ(nullptr, numbers.get_r());
	ASSERT_EQ(0, numbers.get_n());
}

TEST_F(avl_evaluation_p, insert_method)
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

TEST_F(avl_evaluation_p, remove_method)
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

TEST_F(avl_evaluation_p, iterator)
{
	numbers.print();
}

/*
// query operations:
// instance synergy:
// iterator methods:
// friend functions:


//------------------------------------------------
// next class:

class avl_evaluation_c : public Test
{
protected:
    avl<convoluted> objects;

    void TearDown();
    avl_evaluation_c();
};

//------------------------------------------------
// constructors:

void avl_evaluation_c::TearDown() {}

avl_evaluation_c::avl_evaluation_c() : objects(list_objects) {}

//------------------------------------------------
// tests:

TEST_F(avl_evaluation_c, query_operations)
{
    objects.set_f(compare_numbr);
    EXPECT_EQ(objects.minimum(), 6);
    EXPECT_EQ(objects.maximum(), 0);

    objects.set_f(compare_addss);
    //EXPECT_EQ(objects.predcessr(8), 5);
    //EXPECT_EQ(objects.successor(9), 1);
}
*/


/*

								1

		-1.01									255


	-2			-0.99					1.01			65535

			-1			0.99
	*/