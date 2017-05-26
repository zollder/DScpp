/*
 * test_factorial.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

# include "gtest/gtest.h"
# include "factorial.h"

TEST(FactorialTest, Negative) {
	  EXPECT_EQ(1, factorial(-5));
	  EXPECT_EQ(1, factorial(-1));
	  EXPECT_GT(factorial(-10), 0);
}
