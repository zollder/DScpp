/*
 * test_bubblesort.cpp
 *
 *  Created on: May 26, 2017
 *      Author: zollder
 */

# include "../include/NodeSequence.h"
# include "../include/BubbleSort.cpp"

# include "stdio.h"
# include "gtest/gtest.h"

	using namespace std;
	typedef NodeSequence<int> Sequence;
	typedef Sequence::Position Position;

	TEST(BubbleSortTest, rankBasedSort_ok) {
		Sequence seq;
		BubbleSort<Sequence> bubble;
		seq.addAll({4,1,2,5,3,8});
		seq.print();
		bubble.bubbleSort1(seq);
		seq.print();
		EXPECT_EQ(1, seq.getPositionByRank(0).getValue());
		EXPECT_EQ(3, seq.getPositionByRank(2).getValue());
		EXPECT_EQ(5, seq.getPositionByRank(4).getValue());
	}

	TEST(BubbleSortTest, positionBasedSort_ok) {
		Sequence seq;
		BubbleSort<Sequence> bubble;
		seq.addAll({4,1,2,5,3});
		bubble.bubbleSort2(seq);
		EXPECT_EQ(1, seq.getPositionByRank(0).getValue());
		EXPECT_EQ(3, seq.getPositionByRank(2).getValue());
		EXPECT_EQ(5, seq.getPositionByRank(4).getValue());
	}
