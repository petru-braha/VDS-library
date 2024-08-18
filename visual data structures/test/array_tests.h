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
    EXPECT_TRUE(numbers.empty());
    EXPECT_THROW(numbers.get_l(), int);
}

TEST_F(array_evaluation_p, sort_method)
{
    numbers.set_f([](const float& x, const float& y)->bool { return x < y; });
    for (bit algorithm = bubble_sort;; algorithm++)
    {
        EXPECT_NO_THROW(numbers.sort(algorithm));
        FOR(numbers.get_l())
            EXPECT_GE(numbers[i], numbers[i + 1]) << "for the " << algorithm << '\n';

        // last one
        if (algorithm == quick_sort)
            break;
    }
}

TEST_F(array_evaluation_p, insert_method)
{
    numbers.insert(insertions[0], 0);
    numbers.insert(insertions[1], 1);
    numbers.insert(insertions[2], 0);
    numbers.insert(insertions[3], numbers.get_l() + 1);
    numbers.insert(insertions[4], 3);

    // array has fixed size
    EXPECT_EXIT(numbers.insert(100.0f, 0), testing::ExitedWithCode(ERROR_CODE), "");

    EXPECT_EQ(numbers[0], insertions[2]);
    EXPECT_EQ(numbers[1], insertions[0]);
    EXPECT_EQ(numbers[2], insertions[1]);
    EXPECT_EQ(numbers[3], insertions[4]);
    EXPECT_EQ(numbers[numbers.get_l()], insertions[3]);
}

TEST_F(array_evaluation_p, remove_method)
{
    numbers.remove(0);
    EXPECT_EQ(numbers.get_l(), 8);
    EXPECT_EQ(numbers[0], block_numbers[1]);

    numbers.remove(2);
    EXPECT_EQ(numbers[1], block_numbers[2]);
    EXPECT_EQ(numbers[2], block_numbers[4]);
    EXPECT_NO_THROW(numbers.remove(numbers.get_l() - 1));
}

TEST_F(array_evaluation_p, query_operations)
{
    // all the numbers bellow are indexes
    size_t index = 0;
    EXPECT_EQ(index = numbers.search(-1), 0) << "searching failed.\n";
    EXPECT_EQ(index = numbers.minimum(), 5) << "minimum failed.\n";
    EXPECT_EQ(index = numbers.maximum(), 4) << "maximum failed.\n";
    EXPECT_EQ(index = numbers.predcessr(2), 8) << "predecessor failed.\n";
    EXPECT_EQ(index = numbers.successor(2), 1) << "successor failed.\n";
}

/*TEST(array_p, friend_functions)
{
    array<> first = { 1, 2, 3, 4, 5 };
    array<> secnd = { 5, 6, 7, 8, 9 };
    array<> temp;

    temp = linking(first, secnd);
    EXPECT_EQ(temp.get_n(), 200) << "n\n";
    EXPECT_EQ(temp.get_l(), 9) << "l\n";
    EXPECT_EQ(temp[4], temp[5]);

    temp = ejectin(first, secnd);
    EXPECT_EQ(temp.get_l(), 3);

    temp = crossng(first, secnd);
    EXPECT_EQ(temp.get_n(), 200);
    EXPECT_EQ(temp.get_l(), 0);
}*/

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

array_evaluation_c::array_evaluation_c() : objects(list_objects, classic_size, maximum_size) {}

//------------------------------------------------
// tests:

// it is imposed to use a stable algorithm
TEST_F(array_evaluation_c, sort_method)
{
    array<convoluted> sorted = objects;
    const int indexes1[] = { 6, 4, 7, 5, 8, 9, 1, 2, 3, 0 };
    sorted.set_f(compare_numbr);
    EXPECT_NO_THROW(sorted.sort());
    FOR(10)
        EXPECT_TRUE(absolute_equality(sorted[i], objects[indexes1[i]])) << "number comparison - index: " << i << '\n';
    sorted = objects;

    const int indexes2[] = { 6, 9, 1, 3, 5, 8, 0, 2, 4, 7 };
    sorted.set_f(compare_addss);
    EXPECT_NO_THROW(sorted.sort(bubble_sort));
    FOR(10)
        EXPECT_TRUE(absolute_equality(sorted[i], objects[indexes2[i]])) << "address comparison - index: " << i << '\n';
    sorted = objects;

    // this, last section, can't be stable because of the satellite data, and poor implementation of 'compare_strng'
    const int indexes3[] = { 6, 8, 9, 0, 1, 2, 3, 4, 5, 7 };
    sorted.set_f(compare_strng);
    EXPECT_NO_THROW(sorted.sort(bubble_sort));
    FOR(10)
        EXPECT_TRUE(absolute_equality(sorted[i], objects[indexes3[i]])) << "string comparison - index: " << i << '\n';
}

TEST_F(array_evaluation_c, query_operations)
{

    objects.set_f(compare_numbr);
    EXPECT_EQ(objects.minimum(), 6);
    EXPECT_EQ(objects.maximum(), 0);

    objects.set_f(compare_addss);
    EXPECT_EQ(objects.predcessr(8), 5);
    EXPECT_EQ(objects.successor(9), 1);
}