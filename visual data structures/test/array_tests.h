#pragma once
#include "convoluted.h"
#include "array.h"
#include "trial_test_values.h"

class array_evaluation_p : public testing::Test
{
protected:
    array<> a;
    array<char> b;
    array<float> c;
    array<size_t> d;

    void SetUp() {}
    void TearDown() {}
    //test sharing
};

class array_evaluation_c : public testing::Test
{
protected:
    array<convoluted> absolute;

    void SetUp() {}
    void TearDown() {}
};

//------------------------------------------------
// tests:

TEST_F(array_evaluation_p, dadad)
{

}

//------------------------------------------------
// tests:


// sort
// insert__remove

// query operations
// constant methods
// friend functions

// errors



/*
old code:

TEST(array_p, initialisation)
{
    array<> number1;
    array<> numbers = { 5111, 4, 3, 2, 1 };

    std::initializer_list<char> letters = { 'd' , 'c', 'j', '2' };
    array<char> word = (letters, 5);

    array<float> fnr = { -1, 4.05f, 22, 0 };
    array<float> fn2 = fnr;
    array<float>* fn4 = new array<float>(array<float>(fn2));
    delete fn4;

    array<> numbrs2 = { 1 };
    numbrs2 = numbers;
    EXPECT_EQ(numbrs2[0], 5111);
    EXPECT_EQ(numbrs2[4], 1);
}

//------------------------------------------------
// specific methods:

TEST(array_p, sorting_bubbs)
{
    array<> numbers = { 5111, 4, -3, 2, 1, 1, -(-5) };
    EXPECT_NO_THROW(numbers.sort(bubble_sort));
    FOR(numbers.getl())
        EXPECT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array_p, sorting_seles)
{
    array<size_t> numbers = { 0, 0, 0, ULLONG_MAX, LLONG_MAX, USHRT_MAX };
    EXPECT_NO_THROW(numbers.sort(selection_sort));
    FOR(numbers.getl())
        EXPECT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array_p, sorting_insrs)
{
    array<char> numbers = { 'a', 'b', 'a' };
    EXPECT_NO_THROW(numbers.sort(insertion_sort));
    FOR(numbers.getl())
        EXPECT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array_p, sorting_mrges)
{
    array<float> numbers = { -INT16_MAX, -5.06f , -5.04f , -5.05f , 0, 0, 12, INT16_MAX };
    EXPECT_NO_THROW(numbers.sort(merge_sort));
    FOR(numbers.getl())
        EXPECT_TRUE(numbers[i] <= numbers[i + 1]);
    //EXPECT_LE
}

TEST(array_p, sorting_heaps)
{
    array<> numbers = { -1, -1, -11, 22, LONG_MIN, LONG_MAX };
    EXPECT_NO_THROW(numbers.sort(heap_sort));
    FOR(numbers.getl())
        EXPECT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array_p, sorting_qucks)
{
    array<float> numbers = { -55, 1.02f, 1.03f, 1, 0, 1.001f };
    EXPECT_NO_THROW(numbers.sort());
    FOR(numbers.getl())
        EXPECT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array_p, insert)
{
    array<> numbers;
    numbers.insert(1, 0);
    numbers.insert(2, 0);
    numbers.insert(444, 2);
    numbers.insert(646, 2);
    numbers.insert(646, 3);
    EXPECT_EQ(numbers[0], 2);
    EXPECT_EQ(numbers[1], 1);
    EXPECT_EQ(numbers[2], 646);
    EXPECT_EQ(numbers[3], 646);
    EXPECT_EQ(numbers[4], 444);
}

TEST(array_p, remove)
{
    array<> numbers;
    numbers.insert(1, 0);
    numbers.insert(2, 0);
    EXPECT_EQ(numbers[0], 2);
    EXPECT_EQ(numbers[1], 1);
}

TEST(array_p, defined_errors)
{
    array<> numbers = { 5111, 4, 3, 2, 1 };
    for (auto i : numbers)
        std::cout << i << ' ';

}

//------------------------------------------------
//------------------------------------------------
// convoluted types:

TEST(array_c, initialisation)
{

}

*/