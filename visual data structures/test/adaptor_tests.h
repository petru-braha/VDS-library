#pragma once
#include "stack.h"
#include "queue.h"

TEST(adaptor_stack, dada)
{
	stack<> euro_temperatures;
	EXPECT_TRUE(euro_temperatures.empty());
	
	euro_temperatures.push(1);
	euro_temperatures.push(2);
	euro_temperatures.push(3);
	EXPECT_EQ(3, euro_temperatures.top());
	EXPECT_EQ(3, euro_temperatures.get_n());

	euro_temperatures.pop();
	euro_temperatures.pop();
	euro_temperatures.push(4);
	EXPECT_EQ(4, euro_temperatures.top());
	
	euro_temperatures.pop();
	EXPECT_EQ(1, euro_temperatures.top());
	EXPECT_EQ(1, euro_temperatures.get_n());
	
	euro_temperatures.pop();
	EXPECT_TRUE(euro_temperatures.empty());

	EXPECT_THROW(euro_temperatures.pop(), int);
}

TEST(adaptor_queue, dada)
{
	std::initializer_list<int> aaa = { 100, 60, 42, 25, 23, 21, 20 };
	queue<> rabbit_log(aaa);

	EXPECT_EQ(100, rabbit_log.front());
	EXPECT_EQ(20, rabbit_log.back());
}
