#pragma once
#include "stack.h"
#include "queue.h"

TEST(adaptor, stack)
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

TEST(adaptor, queue)
{
	queue<> rabbit_log{ 100, 60, 42, 25, 23, 21, 20 };
	EXPECT_EQ(100, rabbit_log.front());
	EXPECT_EQ(20, rabbit_log.back());

	rabbit_log.pop();
	rabbit_log.pop();
	rabbit_log.pop();
	EXPECT_EQ(25, rabbit_log.front());
	EXPECT_EQ(4, rabbit_log.get_n());

	rabbit_log.push(15);
	rabbit_log.push(10);
	rabbit_log.pop();
	EXPECT_EQ(23, rabbit_log.front());
	EXPECT_EQ(10, rabbit_log.back());

	FOR(4)
		rabbit_log.pop();
	EXPECT_EQ(rabbit_log.front(), rabbit_log.back());
	EXPECT_FALSE(rabbit_log.empty());

	rabbit_log.pop();
	EXPECT_TRUE(rabbit_log.empty());
	EXPECT_THROW(rabbit_log.pop(), int);
	EXPECT_THROW(rabbit_log.front(), int);
	EXPECT_THROW(rabbit_log.back(), int);
}
