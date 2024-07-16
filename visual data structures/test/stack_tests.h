#pragma once
#include "adaptor/stack.h"

TEST(stack_p, initialisation)
{

}

TEST(stack_p, specific_methods)
{
	stack<> numbers;
	numbers.push(1);
	numbers.push(2);
	EXPECT_EQ(numbers.top(), 2);
	numbers.pop();
	numbers.push(3);
	EXPECT_EQ(numbers.top(), 3);
	numbers.pop();
	EXPECT_EQ(numbers.top(), 1);
	numbers.pop();
	EXPECT_EQ(numbers.top(), 0);
	numbers.pop();
	EXPECT_THROW(numbers.top(), int);
}