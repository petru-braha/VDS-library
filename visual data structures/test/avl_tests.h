#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "avl.h"

class avl_evaluation_p : public ::testing::Test
{
protected:
	array<float> numbers;

	~avl_evaluation_p() = default;
	avl_evaluation_p();
};

//------------------------------------------------
// constructors:

avl_evaluation_p::avl_evaluation_p() : numbers() {}

//------------------------------------------------
// tests:

TEST_F(avl_evaluation_p, clear_method)
{

}