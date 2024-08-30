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
    const node_list<float>* head_node;

    ~linked_list_evaluation_p() = default;
    linked_list_evaluation_p();
};

//------------------------------------------------
// constructors:

linked_list_evaluation_p::linked_list_evaluation_p() : numbers(list_numbers), head_node(nullptr)
{
    numbers = linked_list<float>(linked_list<float>(block_numbers, classic_size));
};

//------------------------------------------------
// tests:

TEST_F(linked_list_evaluation_p, clear_method)
{
    numbers.clear();
    EXPECT_TRUE(numbers.empty());
    EXPECT_EQ(numbers.get_n(), 0);
    EXPECT_EQ(numbers.get_head(), nullptr);
    EXPECT_EQ(numbers.get_tail(), nullptr);
}

TEST_F(linked_list_evaluation_p, sort_method)
{
    EXPECT_NO_THROW(numbers.sort());
    const node_list<float>* it = numbers.get_head(), * nxt = nullptr;
    for (auto nxt = it->successor[0]; nxt; nxt = nxt->successor[0])
    {
        EXPECT_LE(it->get(), nxt->get());
        it = nxt;
    }
}

TEST_F(linked_list_evaluation_p, insert_method)
{
    n node0(insertions[0]);
    n node1(insertions[1]);
    n node2(insertions[2]);
    n node3(insertions[3]);
    n node4(insertions[4]);

    /*numbers.insert(&node0, head_node);

    auto it = numbers.get_head();
    numbers.insert(&node1, it);

    numbers.insert(&node2, head_node);

    it = numbers.get_tail();
    numbers.insert(&node3, it);

    it = numbers.get_node(2);
    numbers.insert(&node4, it);

    linked_list<float> temp(final_numbers);
    FOR(15)
    {
        auto one = numbers.get_node(i)->get(), two = temp.get_node(i)->get();
        EXPECT_EQ(one, two);
    }*/
}

TEST_F(linked_list_evaluation_p, remove_method)
{
    // delete first
    numbers.remove(head_node);
    EXPECT_EQ(numbers.get_node(0)->get(), block_numbers[1]);

    // delete last
    auto it = numbers.get_head();
    while (it->successor[0] != numbers.get_tail())
        it = it->successor[0];
    numbers.remove(it);
    EXPECT_EQ(numbers.get_tail()->get(), block_numbers[8]);

    // delete somewhere in the middle
    it = numbers.get_node(3);
    numbers.remove(it);
    EXPECT_EQ(numbers.get_node(3)->get(), block_numbers[4]);
}

TEST_F(linked_list_evaluation_p, query_operations)
{
    EXPECT_EQ(numbers.search(-1), numbers.get_node(0));
    EXPECT_EQ(numbers.search(60), nullptr);

    EXPECT_EQ(numbers.mimimum(), numbers.get_node(5));
    EXPECT_EQ(numbers.maximum(), numbers.get_node(4));

    //EXPECT_EQ(numbers.predcessr(), numbers.get_node(4));
}

TEST(linked_list_p, friend_functions)
{
    linked_list<> first(frnd_values1);
    linked_list<> secnd(frnd_values2);
    linked_list<> temp;

    std::cout << secnd.get_n() << ' ' << first.get_n() << ' ' << temp.get_n() << ' ';
}

//------------------------------------------------
// next class:

class linked_list_evaluation_c : public testing::Test
{
protected:
    linked_list<convoluted> objects;

    void TearDown();
    linked_list_evaluation_c();
};


//------------------------------------------------
// constructors:

void linked_list_evaluation_c::TearDown() {}

linked_list_evaluation_c::linked_list_evaluation_c() : objects(list_objects, classic_size) {}

//------------------------------------------------
// tests:

TEST_F(linked_list_evaluation_c, sort_method)
{

}

TEST_F(linked_list_evaluation_c, query_operations)
{

}
