#pragma once
#include "convoluted.h"
#include "linked_list.h"
#include "trial_test_values.h"
#include <cstring>

class linked_list_evaluation_p : public testing::Test
{
protected:
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
    numbers.prnt();
    numbers.sort();
    numbers.prnt();
}

// clear
// sort
// insert
// remove
// query: predecessor successor search minimum maximum
// friend:
// convoluted: sort query