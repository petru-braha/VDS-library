#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "avl.h"

class avl_evaluation_p : public ::testing::Test
{
protected:
	avl<float> numbers;

	~avl_evaluation_p() = default;
	avl_evaluation_p();
};

//------------------------------------------------
// constructors:

avl_evaluation_p::avl_evaluation_p() : numbers(list_numbers) {}

//------------------------------------------------
// tests:

TEST_F(avl_evaluation_p, constructors)
{
	auto it = numbers.get_r();
	it = it->successor[left_child];
	it = it->successor[rght_child];
	//it = it->successor[left_child];
	std::cout << it->get();
	//std::cout << numbers.get_r()->get();
	//std::cout << numbers.get_r()->successor[left_child]->get();

	//node_avlt<float>* node1 = new node_avlt<float>(2);
	//numbers.insert(node1);
	//delete node1;

	/*
	
								1
	    
		-1.01									256
	

	-2			-0.99					1.01			65535
			
			-1			0.99
	*/
}
