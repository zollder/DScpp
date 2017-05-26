/*
 * test_factorial.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

# include "stdio.h"
# include "gtest/gtest.h"
# include "../src/NodeSequence.cpp"
#include <vector>

	using namespace std;
	typedef NodeSequence<int> nSequence;
	typedef nSequence::Position Position;

	TEST(NodeSequenceTest, emptySequence) {
		nSequence emptySeq;
		EXPECT_EQ(0, emptySeq.size());
		EXPECT_TRUE(emptySeq.isEmpty());
	}

	TEST(NodeSequenceTest, getPosition_negativeRank) {
		nSequence sequence;
		sequence.insertFirst(5);
		try {
			sequence.getPosition(-1);
			FAIL() << "Test failed";
		} catch (const BoundaryViolationException& ex) {
			EXPECT_EQ("Invalid rank", ex.getMessage());
		} catch (...) {	FAIL() << "Wrong exception"; }
	}

	TEST(NodeSequenceTest, getPosition_overflowedRank) {
		nSequence sequence;
		sequence.insertFirst(5);
		try {
			sequence.getPosition(2);
			FAIL() << "Test failed";
		} catch (const BoundaryViolationException& ex) {
			EXPECT_EQ("Invalid rank", ex.getMessage());
		} catch (...) {	FAIL() << "Wrong exception"; }
	}

	TEST(NodeSequenceTest, getPosition_ok) {
		nSequence sequence;
		sequence.addAll({1,2,3});
		EXPECT_EQ(2, sequence.getPosition(1).getValue());
		EXPECT_EQ(3, sequence.getPosition(2).getValue());
	}

	TEST(NodeSequenceTest, getRank_ok) {
		nSequence sequence;
		Position pos1 = sequence.insertFirst(1);
		Position pos2 = sequence.insertLast(2);
		Position pos3 = sequence.insertLast(3);
		EXPECT_EQ(1, sequence.getRank(pos2));
		EXPECT_EQ(2, sequence.getRank(pos3));
	}

	TEST(NodeSequenceTest, getValueAtRank_ok) {
		nSequence sequence;
		sequence.addAll({1,2,3});
		EXPECT_EQ(1, sequence.getValueAtRank(0));
		EXPECT_EQ(3, sequence.getValueAtRank(2));
	}

	TEST(NodeSequenceTest, insertAtRank_negative) {
		nSequence sequence;
		try {
			int value = 5;
			sequence.insertAtRank(-1, value);
			FAIL() << "Test failed";
		} catch (const BoundaryViolationException& ex) {
			EXPECT_EQ("Invalid rank", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeSequenceTest, insertAtRank_overflow) {
		nSequence sequence;
		try {
			int value = 5;
			sequence.insertAtRank(1, value);
			FAIL() << "Test failed";
		} catch (const BoundaryViolationException& ex) {
			EXPECT_EQ("Invalid rank", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeSequenceTest, insertAtRank_ok) {
		nSequence sequence;
		int value = 5;
		sequence.insertFirst(1);
		sequence.insertAtRank(1, value);
		EXPECT_EQ(2, sequence.size());
		EXPECT_EQ(value, sequence.getValueAtRank(1));

		sequence.insertAtRank(0, value);
		EXPECT_EQ(3, sequence.size());
		EXPECT_EQ(value, sequence.getValueAtRank(0));
		EXPECT_EQ(value, sequence.getValueAtRank(2));
	}

	TEST(NodeSequenceTest, removeAtRank_ok) {
		nSequence sequence;
		sequence.addAll({1,2,3});
		EXPECT_EQ(3, sequence.size());
		EXPECT_EQ(2, sequence.getValueAtRank(1));

		sequence.removeAtRank(1);
		EXPECT_EQ(2, sequence.size());
		EXPECT_EQ(3, sequence.getValueAtRank(1));
	}

	TEST(NodeSequenceTest, replaceAtRank_ok) {
		nSequence sequence;
		sequence.addAll({1,2,3});
		EXPECT_EQ(2, sequence.getValueAtRank(1));

		int value = 5;
		sequence.replaceAtRank(1, value);
		EXPECT_EQ(value, sequence.getValueAtRank(1));
	}
