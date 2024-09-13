#pragma once
#include "convoluted.h"
#include "linked_list.h"
#include "trial_test_values.h"
#include <cstring>

class list__p : public Test
{
protected:
    typedef node_list<float> n;
    typedef node_list<float>* p;

    linked_list<float> numbers;
    node_list<float>* const head_node;

    ~list__p() = default;
    list__p();
};

//------------------------------------------------
// constructors:

list__p::list__p() : numbers(list_numbers), head_node(nullptr) {}

//------------------------------------------------
// tests:

TEST_F(list__p, constructors)
{
    linked_list<float> extra = numbers;
    EXPECT_EQ(numbers, extra);
    
    extra = decltype(numbers)(list_numbers);
    EXPECT_EQ(numbers, extra);
    
    extra = linked_list<float>(linked_list<float>(linked_list<float>(block_numbers, classic_size)));
    
    size_t extra_index = 0;
    for (auto value : numbers)
    {
        EXPECT_EQ(value, extra.get_node(extra_index)->get());
        extra_index++;
    }
}

TEST_F(list__p, clear)
{
    numbers.clear();
    EXPECT_TRUE(numbers.empty());
    EXPECT_EQ(numbers.get_n(), 0);
    EXPECT_EQ(numbers.get_head(), nullptr);
    EXPECT_EQ(numbers.get_tail(), nullptr);
}

TEST_F(list__p, sort)
{
    EXPECT_NO_THROW(numbers.sort());
    const node_list<float>* it = numbers.get_head();
    
    for (auto nxt = it->successor[0]; nxt; nxt = nxt->successor[0])
    {
        EXPECT_LE(it->get(), nxt->get());
        it = nxt;
    }
}

TEST_F(list__p, insert)
{
    n node0(insertions[0]);
    n node1(insertions[1]);
    n node2(insertions[2]);
    n node3(insertions[3]);
    n node4(insertions[4]);
    
    numbers.insert(&node0, head_node).insert(&node1, numbers.get_head());
    EXPECT_EQ(numbers.get_n(), 12);
    EXPECT_EQ(numbers.get_head()->get(), 10.5f);
    EXPECT_EQ(numbers.get_node(1)->get(), 10.6f);

    numbers.insert(&node2, head_node);
    numbers.insert(&node3, numbers.get_tail());
    numbers.insert(&node4, numbers.get_node(2));
    
    auto it = numbers.get_head();
    EXPECT_EQ(numbers.get_n(), 15);
    
    for(auto value : final_numbers)
    {
        EXPECT_EQ(value, it->get());
        it = it->successor[0];
    }
}

TEST_F(list__p, remove)
{
    numbers.remove(head_node);
    EXPECT_EQ(numbers.get_n(), 9);
    EXPECT_EQ(numbers.get_head()->get(), block_numbers[1]);

    numbers.remove(numbers.get_node(1));
    EXPECT_EQ(numbers.get_n(), 8);
    EXPECT_EQ(numbers.get_node(2)->get(), block_numbers[4]);

    numbers.remove(numbers.get_node(6));
    EXPECT_EQ(numbers.get_n(), 7);
    EXPECT_EQ(numbers.get_tail()->get(), block_numbers[8]);
}

TEST_F(list__p, queries)
{
    auto node = numbers.search(-1);
    EXPECT_TRUE(node != nullptr && node->get() == -1);
    EXPECT_TRUE((node = numbers.minimum()) != nullptr && LONG_MIN == node->get());
    EXPECT_TRUE((node = numbers.maximum()) != nullptr && USHRT_MAX == node->get());

    p other_node = new n(block_numbers[2]); // 1
    node = numbers.predcessr(other_node);
    EXPECT_EQ(node->get(), block_numbers[8]);
    
    node = numbers.successor(other_node);
    EXPECT_EQ(node->get(), block_numbers[1]);

    delete other_node;
}

TEST(list_p, instances)
{
    linked_list<> first = friend_values1;
    linked_list<> secnd = friend_values2;
    linked_list<> temp;

    temp = first;
    temp.integrates(secnd);
    EXPECT_EQ(temp.get_n(), 10);
    EXPECT_EQ(temp.get_node(4)->get(), temp.get_node(5)->get());

    temp = first;
    temp.eliminates(secnd);
    EXPECT_EQ(temp.get_n(), 4);
    EXPECT_EQ(temp.get_node(3)->get(), 4);

    temp = first;
    temp.intersects(secnd);
    EXPECT_EQ(temp.get_n(), 1);
    EXPECT_EQ(temp.get_head(), temp.get_tail());
}

TEST_F(list__p, functions)
{
    float* data = convert(numbers);

    auto it = numbers.get_head();
    FOR(numbers.get_n())
    {
        EXPECT_EQ(it->get(), *data);
        data++;
        it = it->successor[0];
    }
}

//------------------------------------------------
// next class:

class list__c : public Test
{
protected:
    linked_list<convoluted> objects;

    void TearDown();
    list__c();
};


//------------------------------------------------
// constructors:

void list__c::TearDown() {}

list__c::list__c() : objects(list_objects, classic_size) {}

//------------------------------------------------
// tests:

TEST_F(list__c, sort)
{
    /*
    linked_list<convoluted> sorted(objects);

const size_t indexes1[] = { 6, 4, 7, 5, 8, 9, 1, 2, 3, 0 };
objects.set_f(compare_numbr);
objects.sort();
    
    const size_t indexes2[] = { 6, 9, 1, 3, 5, 8, 0, 2, 4, 7 };
    objects.set_f(compare_addss);
    objects.sort();
    FOR(10)
        EXPECT_TRUE(absolute_equality(
            sorted.get_node(i)->get(),
            objects.get_node(indexes2[i])->get()))
        << "address comparison - index: " << i << '\n';

    const size_t indexes3[] = { 6, 8, 9, 0, 1, 2, 3, 4, 5, 7 };
    objects.set_f(compare_strng);
    objects.sort();
    FOR(10)
        EXPECT_TRUE(absolute_equality(
            sorted.get_node(i)->get(),
            objects.get_node(indexes3[i])->get()))
        << "string comparison - index: " << i << '\n';
        */
}

TEST_F(list__c, queries)
{
    objects.set_f(compare_strng);
    EXPECT_EQ(objects.minimum(), objects.get_node(9));
    EXPECT_EQ(objects.maximum(), objects.get_node(7));

    objects.set_f(compare_numbr);
}
