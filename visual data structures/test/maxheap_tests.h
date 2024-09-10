/*#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "maxheap.h"

class maxheap_evaluation_p : public testing::Test
{
protected:
    maxheap<float> numbers;

    ~maxheap_evaluation_p() = default;
    maxheap_evaluation_p();
};

//------------------------------------------------
// constructors:

maxheap_evaluation_p::maxheap_evaluation_p() : numbers(list_numbers, maximum_size) {}

//------------------------------------------------
// tests:

TEST_F(maxheap_evaluation_p, constructors)
{
    auto extra = numbers;
    EXPECT_EQ(numbers, extra);
    extra = decltype(numbers)(list_numbers, maximum_size);
    EXPECT_EQ(numbers, extra);
    extra = array<float>(array<float>(array<float>(block_numbers, classic_size, maximum_size)));

    size_t extra_index = 0;
    for (auto value : numbers)
    {
        EXPECT_EQ(value, extra.get(extra_index));
        extra_index++;
    }
}

TEST_F(maxheap_evaluation_p, clear_method)
{
    numbers.clear();
    EXPECT_TRUE(numbers.empty());
    EXPECT_THROW(numbers.get_l(), int);
}

TEST_F(maxheap_evaluation_p, extract_method)
{
    numbers.remove(0);
    EXPECT_EQ(numbers.get_l(), 8);
    EXPECT_EQ(numbers[0], block_numbers[1]);

    numbers.remove(2);
    EXPECT_EQ(numbers[1], block_numbers[2]);
    EXPECT_EQ(numbers[2], block_numbers[4]);
    EXPECT_NO_THROW(numbers.remove(numbers.get_l() - 1));
}

TEST_F(maxheap_evaluation_p, query_operations)
{
    // all the numbers bellow are indexes
    size_t index = 0;
    EXPECT_EQ(index = numbers.search(-1), 0) << "searching failed.\n";
    EXPECT_EQ(index = numbers.minimum(), 5) << "minimum failed.\n";
    EXPECT_EQ(index = numbers.maximum(), 4) << "maximum failed.\n";
    EXPECT_EQ(index = numbers.predcessr(2), 8) << "predecessor failed.\n";
    EXPECT_EQ(index = numbers.successor(2), 1) << "successor failed.\n";
}

TEST(maxheap_p, friend_functions)
{
    array<> first = { 1, 2, 3, 4, 5 };
    array<> secnd = { 5, 6, 7, 8, 9 };
    array<> temp;

    temp = first;
    temp.integrates(secnd);
    EXPECT_EQ(temp.get_n(), 200) << "n\n";
    EXPECT_EQ(temp.get_l(), 9) << "l\n";
    EXPECT_EQ(temp[4], temp[5]);

    temp = first;
    temp.eliminates(secnd);
    EXPECT_EQ(temp.get_l(), 3);

    temp = first;
    temp.intersects(secnd);
    EXPECT_EQ(temp.get_l(), 0);
}

//------------------------------------------------
// next class:

class maxheap_evaluation_c : public testing::Test
{
protected:
    maxheap<convoluted> objects;

    void TearDown();
    maxheap_evaluation_c();
};

//------------------------------------------------
// constructors:

void maxheap_evaluation_c::TearDown() {}

maxheap_evaluation_c::maxheap_evaluation_c() : objects(list_objects, classic_size, maximum_size) {}

//------------------------------------------------
// tests:

TEST_F(maxheap_evaluation_c, query_operations)
{
    objects.set_f(compare_numbr);
    EXPECT_EQ(objects.minimum(), 6);
    EXPECT_EQ(objects.maximum(), 0);

    objects.set_f(compare_addss);
    EXPECT_EQ(objects.predcessr(8), 5);
    EXPECT_EQ(objects.successor(9), 1);
}
*/
