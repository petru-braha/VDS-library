#pragma once
#include "array.cpp"

//------------------------------------------------
// primitives:

TEST(array_p, initialisation) {
    size_t n = 10;
    std::initializer_list<int> sane = { 10, 20, 30, 40, 50 };
    array<int> people = (sane, n);
    EXPECT_EQ(people.getn(), n);
    for (int i = 0; i < people.getl(); i++)
        EXPECT_EQ(people[i], *(sane.begin() + 1));

    //ASSERT_EXIT(a[n], ::testing::ExitedWithCode(EXIT_FAILURE), "fail");
    //testing_glfw();
}

// specific methods:

TEST(array_p, sorting_bubbl) {
    array<> numbers = { 5111, 4, 3, 2, 1 };
    numbers.sort(bubble_sort);
    FOR(numbers.getn() - 1)
        ASSERT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array_p, sorting_quick) {
    array<> numbers = { 5111, 4, 3, 2, 1 };
    numbers.sort();
    FOR(numbers.getl())
        ASSERT_TRUE(numbers[i] <= numbers[i + 1]);
}

// specific methods end;

TEST(array_p, defined_errors)
{

}

TEST(array_p, constant_methods)
{

}

TEST(array_p, friend_functions)
{

}

//------------------------------------------------
// convoluted types:

TEST(array_c, initialisation)
{

}
