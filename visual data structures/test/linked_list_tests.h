#pragma once
#include "convoluted.h"
#include "linked_list.h"
#include "trial_test_values.h"
#include <cstring>

class linked_list_evaluation_p : public testing::Test
{
protected:
    typedef node_list<float> n;
    linked_list<float> numbers;

    ~linked_list_evaluation_p() = default;
    linked_list_evaluation_p();
};

//------------------------------------------------
// constructors:

linked_list_evaluation_p::linked_list_evaluation_p() : numbers(list_numbers)
{
    numbers = linked_list<float>(linked_list<float>(block_numbers, classic_size));
};

//------------------------------------------------
// tests:

TEST_F(linked_list_evaluation_p, clear_method)
{
    numbers.clear();
    EXPECT_TRUE(numbers.empty());
    EXPECT_EQ(numbers.getn(), 0);
    EXPECT_EQ(numbers.get_head(), nullptr);
    EXPECT_EQ(numbers.get_tail(), nullptr);
}

TEST_F(linked_list_evaluation_p, sort_method)
{
    //numbers.sort();
    const node_list<float>* it = numbers.get_head(), * nxt = nullptr;
    for (auto nxt = it->successor[0]; nxt; nxt = nxt->successor[0])
    {
        EXPECT_LE(it->get(), nxt->get());
        it = nxt;
    }
}

TEST_F(linked_list_evaluation_p, insert_method)
{
    n node1(5);
    n node2(6);
    n node3(7);
    n node4(8);
    n node5(9);

    const n* h = numbers.get_head();
    n* it = h->successor[0];
    numbers.insert(&node1);
    EXPECT_EQ(numbers.get_head->get(), node1.get());
    
    numbers.insert(&node2, it);
    numbers.insert(&node3);
    numbers.insert(&node4, it);
    
    h = numbers.get_tail();
    it = const_cast<n*>(h);
    numbers.insert(&node5, it);
}

TEST_F(linked_list_evaluation_p, remove_method)
{}

// clear
// sort
// insert
// remove
// query: predecessor successor search minimum maximum
// friend:
// convoluted: sort query