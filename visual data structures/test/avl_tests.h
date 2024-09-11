#pragma once
#include "convoluted.h"
#include "trial_test_values.h"
#include "avl.h"

class avl_evaluation_p : public ::testing::Test
{
protected:
	typedef node_avlt<float> n;
	typedef node_avlt<float>* p;
	avl<float> numbers;
	
	~avl_evaluation_p() = default;
	avl_evaluation_p();
};

//------------------------------------------------
// constructors:

avl_evaluation_p::avl_evaluation_p() : numbers(list_numbers) {}

//------------------------------------------------
// tests:

/*TEST_F(avl_evaluation_p, constructors)
{
	
}*/

TEST_F(avl_evaluation_p, clear_method)
{
	numbers.clear();

	EXPECT_TRUE(numbers.empty());
	EXPECT_EQ(nullptr, numbers.get_r());
	EXPECT_EQ(0, numbers.get_n());
}
/*
TEST_F(avl_evaluation_p, insert_method)
{

}*/

TEST_F(avl_evaluation_p, remove_method)
{
	p node1 = new n(1);
	numbers.remove(node1);
	
	EXPECT_EQ(numbers.get_n(), 8);
	
	
	
	delete node1;
}
/*
// query operations:
	// instance synergy:
	// iterator methods:
	// friend functions:


//------------------------------------------------
// next class:

class avl_evaluation_c : public testing::Test
{
protected:
    avl<convoluted> objects;

    void TearDown();
    avl_evaluation_c();
};

//------------------------------------------------
// constructors:

void avl_evaluation_c::TearDown() {}

avl_evaluation_c::avl_evaluation_c() : objects(list_objects) {}

//------------------------------------------------
// tests:

TEST_F(avl_evaluation_c, query_operations)
{
    objects.set_f(compare_numbr);
    EXPECT_EQ(objects.minimum(), 6);
    EXPECT_EQ(objects.maximum(), 0);

    objects.set_f(compare_addss);
    //EXPECT_EQ(objects.predcessr(8), 5);
    //EXPECT_EQ(objects.successor(9), 1);
}
*/
