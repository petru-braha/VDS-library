#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "array.h"
#include <cstring>

class array_evaluation_p : public testing::Test
{
protected:
    array<float> numbers;

    ~array_evaluation_p() = default;
    array_evaluation_p();
};

//------------------------------------------------
// constructors:

array_evaluation_p::array_evaluation_p() : numbers(list_numbers, maximum_size)
{
    numbers = array<float>(array<float>(block_numbers, classic_size, maximum_size));
};

//------------------------------------------------
// tests:

TEST_F(array_evaluation_p, clear_method)
{
    numbers.clear();
}

TEST_F(array_evaluation_p, sort_method)
{
    numbers.setf([](const float& x, const float& y)->bool { return x < y; });
    for (bit algorithm = bubble_sort;; algorithm++)
    {
        EXPECT_NO_THROW(numbers.sort(algorithm));
        FOR(numbers.getl())
            EXPECT_GE(numbers[i], numbers[i + 1]) << "for the " << algorithm << '\n';

        // last one
        if (algorithm == quick_sort)
            break;
    }
}

TEST_F(array_evaluation_p, insert_method)
{
    float values[] = { 10.5f, 10.6f, 10.4f, 10.8f, 10.7f };
    numbers.insert(values[0], 0);
    numbers.insert(values[1], 1);
    numbers.insert(values[2], 0);
    numbers.insert(values[3], numbers.getl() + 1);
    numbers.insert(values[4], 3);

    // array has fixed size
    EXPECT_EXIT(numbers.insert(100.0f, 0), testing::ExitedWithCode(ERROR_CODE), "no more memory");

    EXPECT_EQ(numbers[0], values[2]);
    EXPECT_EQ(numbers[1], values[0]);
    EXPECT_EQ(numbers[2], values[1]);
    EXPECT_EQ(numbers[3], values[4]);
    EXPECT_EQ(numbers[numbers.getl()], values[3]);
}

TEST_F(array_evaluation_p, remove_method)
{
    numbers.remove(0);
    EXPECT_EQ(numbers.getl(), 8);
    EXPECT_EQ(numbers[0], block_numbers[1]);

    numbers.remove(2);
    EXPECT_EQ(numbers[1], block_numbers[2]);
    EXPECT_EQ(numbers[2], block_numbers[4]);
    EXPECT_NO_THROW(numbers.remove(numbers.getl() - 1));

    numbers.remove(1.01f, true);
    for (auto i : numbers)
        EXPECT_NE(i, 1.01f);
}

TEST_F(array_evaluation_p, query_operations)
{
    // all the numbers bellow are indexes
    size_t index = ULLONG_MAX;
    EXPECT_EQ(index = numbers.search(-1), 0);
    EXPECT_EQ(index = numbers.minimum(), 5);
    EXPECT_EQ(index = numbers.maximum(), 4);
    EXPECT_EQ(index = numbers.predcessr(1), 8);
    EXPECT_EQ(index = numbers.successor(1), 1);
}

TEST(array_p, friend_functions)
{
    array<> first = { 1, 2, 3, 4, 5 };
    array<> secnd = { 5, 6, 7, 8, 9 };

    array<> temp;
    temp = linking(first, secnd);
    EXPECT_EQ(temp.getn(), 200);
    EXPECT_EQ(temp.getl(), 9);
    EXPECT_EQ(temp[4], temp[5]);

    temp = ejectin(first, secnd);
    EXPECT_EQ(temp.getl(), 3); 
    
    temp = crossng(first, secnd);
    EXPECT_EQ(temp.getn(), 200);
    EXPECT_EQ(temp.getl(), 0);
}

//------------------------------------------------
// next class:

class array_evaluation_c : public testing::Test
{
protected:
    array<convoluted> objects;

    void TearDown();
    array_evaluation_c();
};

//------------------------------------------------
// constructors:

void array_evaluation_c::TearDown()
{
}

array_evaluation_c::array_evaluation_c() : objects() {}

//------------------------------------------------
// tests:

TEST_F(array_evaluation_c, sort_method)
{

}


TEST_F(array_evaluation_c, query_operations)
{

}
