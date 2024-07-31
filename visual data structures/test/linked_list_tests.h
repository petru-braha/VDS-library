#pragma once
#include "convoluted.h"
#include "linked_list.h"
#include "trial_test_values.h"
#include <cstring>

class linked_list_evaluation_p : public testing::Test
{
protected:
    linked_list<float> linked_numbers;

    ~linked_list_evaluation_p() = default;
    linked_list_evaluation_p();
};

//------------------------------------------------
// constructors:

linked_list_evaluation_p::linked_list_evaluation_p() : linked_numbers(list_numbers)
{
    linked_numbers = linked_list<float>(linked_list<float>(block_numbers, classic_size));
};

//------------------------------------------------
// tests: