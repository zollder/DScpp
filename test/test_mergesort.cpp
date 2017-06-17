/*
 * test_bubblesort.cpp
 *
 *  Created on: May 26, 2017
 *      Author: zollder
 */

# include "../include/NodeSequence.h"
# include "../src/MergeSort.cpp"

# include "stdio.h"
# include "gtest/gtest.h"

	using namespace std;
	typedef NodeSequence<int> Sequence;
	typedef Sequence::Position Position;

	TEST(MergeSortTest, regularSort_ok) {
		Sequence seq;
		MergeSort<Sequence> mSort;
		seq.addAll({4,1,2,5,3,8});
		seq.print();
		mSort.sort(seq);
		seq.print();
		EXPECT_EQ(1, seq.getPositionByRank(0).getValue());
		EXPECT_EQ(3, seq.getPositionByRank(2).getValue());
		EXPECT_EQ(5, seq.getPositionByRank(4).getValue());
	}

	TEST(MergeSortTest, emptySequenceSort_ok) {
		Sequence seq;
		MergeSort<Sequence> mSort;
		mSort.sort(seq);
		EXPECT_TRUE(seq.isEmpty());
	}
