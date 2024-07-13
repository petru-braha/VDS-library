#pragma once
#include "array.cpp"
#include "convoluted.h"

//------------------------------------------------
// primitives:

TEST(array_p, initialisation) 
{
    size_t n = 10;
    std::initializer_list<int> sane = { 10, 20, 30, 40, 50 };
    array<int> people = (sane, n);
    EXPECT_EQ(people.getn(), n);
    for (int i = 0; i < people.getl() + 1; i++)
        EXPECT_EQ(people[i], *(sane.begin() + i));

    //ASSERT_EXIT(a[n], ::testing::ExitedWithCode(EXIT_FAILURE), "fail");
}

// specific methods:

TEST(array_p, sorting_bubbl) {
    array<> numbers = { 5111, 4, 3, 2, 1 };
    numbers.sort(bubble_sort);
    FOR(numbers.getl())
        ASSERT_TRUE(numbers[i] <= numbers[i + 1]);
}

TEST(array_p, sorting_quick) {
    array<> numbers = { 5111, 4, 3, 2, 1 };
    numbers.sort();
    FOR(numbers.getl())
        ASSERT_TRUE(numbers[i] <= numbers[i + 1]);
}

// specific methods end;


/*array<T>& operator = (const array<T>&arr);
    void sort(const int& algorithm = quick_sort, bool (*f)(const T&, const T&) = nullptr);
    void insert(const T & value, const size_t & index = last + 1);
    void remove(const size_t & index);
    void remove(const T & value, const bool& all = false);
    bool search(const T & value) const; // used for crossng
*/

TEST(array_p, constant_methods)
{
    /*bool operator == (const array<T>&arr) const;
    T& operator [] (const size_t& index) const; // get / replace method, shift to the left until there is no more empty space
    size_t getn() const;
    size_t getl() const;
    void   prnt() const;
    bool  empty() const;*/

}

TEST(array_p, friend_functions)
{
    /*T* convert(const array<T>&arr);
    array<T> linking(const array<T>&one, const array<T>&two);
    void		ejectin(const array<T>&one, const array<T>&two);
    array<T> crossng(const array<T>&one, const array<T>&two);
    std::ostream& operator << (std::ostream & out, const array<T>&arr);*/
}

TEST(array_p, defined_errors)
{
    array<> numbers = { 5111, 4, 3, 2, 1 };
    for (auto i : numbers)
        std::cout << i << ' ';

}

//------------------------------------------------
// convoluted types:

TEST(array_c, initialisation)
{

}
