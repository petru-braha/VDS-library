#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "array.h"

class array__p : public Test
{
protected:
    array<float> numbers;

    ~array__p() = default;
    array__p();
};

//------------------------------------------------
// constructors:

array__p::array__p() : numbers(list_numbers, maximum_size) {}

//------------------------------------------------
// tests:

TEST_F(array__p, constructors)
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

TEST_F(array__p, clear)
{
    numbers.clear();
    EXPECT_TRUE(numbers.empty());
    EXPECT_THROW(numbers.get_l(), int);
}

TEST_F(array__p, sort)
{
    numbers.set_f([](const float& x, const float& y)->bool { return x < y; });
    for (bit algorithm = bubble_sort; algorithm != 6; algorithm++)
    {
        EXPECT_NO_THROW(numbers.sort(algorithm)) << algorithm << "has an undefined exception.\n";
        FOR(numbers.get_l())
            EXPECT_GE(numbers[i], numbers[i + 1]) << "wrong order of elements sorting with " << algorithm << ".\n";
    }
}

TEST_F(array__p, insert)
{
    numbers.insert(insertions[0], 0);
    numbers.insert(insertions[1], 1);
    numbers.insert(insertions[2], 0);
    numbers.insert(insertions[3], numbers.get_l() + 1);
    numbers.insert(insertions[4], 3);

    //EXPECT_EXIT(numbers.insert(100.0f, 0), ExitedWithCode(ERROR_CODE), "");

    EXPECT_EQ(numbers[0], insertions[2]);
    EXPECT_EQ(numbers[1], insertions[0]);
    EXPECT_EQ(numbers[2], insertions[1]);
    EXPECT_EQ(numbers[3], insertions[4]);
    EXPECT_EQ(numbers[numbers.get_l()], insertions[3]);
}

TEST_F(array__p, remove)
{
    numbers.remove(0);
    EXPECT_EQ(numbers.get_l(), 8);
    EXPECT_EQ(numbers[0], block_numbers[1]);

    numbers.remove(2);
    EXPECT_EQ(numbers[1], block_numbers[2]);
    EXPECT_EQ(numbers[2], block_numbers[4]);
    EXPECT_NO_THROW(numbers.remove(numbers.get_l() - 1));

    EXPECT_THROW(numbers.remove(100), int);
}

TEST_F(array__p, queries)
{
    // all the numbers bellow are indexes
    size_t index = 0;
    EXPECT_EQ(index = numbers.search(-1), 0) << "searching failed.\n";
    EXPECT_EQ(index = numbers.minimum(), 5) << "minimum failed.\n";
    EXPECT_EQ(index = numbers.maximum(), 4) << "maximum failed.\n";
    EXPECT_EQ(index = numbers.predcessr(2), 8) << "predecessor failed.\n";
    EXPECT_EQ(index = numbers.successor(2), 1) << "successor failed.\n";
}

TEST(array_p, instances)
{
    array<> first = friend_values1;
    array<> secnd = friend_values2;
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

TEST_F(array__p, functions)
{
    float* data = convert(numbers);
    
    FOR(numbers.get_l() + 1)
    {
        EXPECT_EQ(numbers.get(i), *data);
        data++;
    }
}

//------------------------------------------------
// next class:

class array__c : public Test
{
protected:
    array<convoluted> objects;

    void TearDown();
    array__c();
};

//------------------------------------------------
// constructors:

void array__c::TearDown() {}

array__c::array__c() : objects(list_objects, classic_size, maximum_size) {}

//------------------------------------------------
// tests:

// it is imposed to use a stable algorithm
TEST_F(array__c, sort)
{
    array<convoluted> sorted = objects;
    
    const size_t indexes1[] = { 6, 4, 7, 5, 8, 9, 1, 2, 3, 0 };
    sorted.set_f(compare_numbr);
    EXPECT_NO_THROW(sorted.sort());
    FOR(10)
        EXPECT_TRUE(absolute_equality(sorted[i], objects[indexes1[i]]))
        << "number comparison - index: " << i << '\n';
    sorted = objects;

    const size_t indexes2[] = { 6, 9, 1, 3, 5, 8, 0, 2, 4, 7 };
    sorted.set_f(compare_addss);
    EXPECT_NO_THROW(sorted.sort(bubble_sort));
    FOR(10)
        EXPECT_TRUE(absolute_equality(sorted[i], objects[indexes2[i]])) << "address comparison - index: " << i << '\n';
    sorted = objects;

    // this section is unstable because of the satellite data, and poor implementation of 'compare_strng'
    const size_t indexes3[] = { 6, 8, 9, 0, 1, 2, 3, 4, 5, 7 };
    sorted.set_f(compare_strng);
    EXPECT_NO_THROW(sorted.sort(bubble_sort));
    FOR(10)
        EXPECT_TRUE(absolute_equality(sorted[i], objects[indexes3[i]])) << "string comparison - index: " << i << '\n';
}

TEST_F(array__c, queries)
{
    objects.set_f(compare_numbr);
    EXPECT_EQ(objects.minimum(), 6);
    EXPECT_EQ(objects.maximum(), 0);

    objects.set_f(compare_addss);
    EXPECT_EQ(objects.predcessr(8), 5);
    EXPECT_EQ(objects.successor(9), 1);
}
