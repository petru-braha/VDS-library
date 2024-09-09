#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "avl.h"

class avl_evaluation_p : public ::testing::Test
{
protected:
	//avl<float> numbers;

	~avl_evaluation_p() = default;
	avl_evaluation_p();
};

//------------------------------------------------
// constructors:

avl_evaluation_p::avl_evaluation_p() {}//: numbers() {}

//------------------------------------------------
// tests:

TEST(avl, a)
{
	
	

	avl<> tree{ 1, 2, 3 };
	//a.insert(node1);
	//a.insert(node2);

	//auto nodeee = a.get_r();
	//std::cout << nodeee->get_height();
}