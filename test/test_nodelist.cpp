/*
 * test_factorial.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

# include "stdio.h"
# include "gtest/gtest.h"
# include "exceptions/InvalidPositionException.h"
# include "../include/NodeList.h"

	typedef NodeList<int> nList;
	typedef nList::Position Position;

	TEST(NodeListTest, emptyList) {
		nList emptyList;
		EXPECT_EQ(0, emptyList.size());
		EXPECT_TRUE(emptyList.isEmpty());
	}

	TEST(NodeListTest, first_emptyList) {
		nList emptyList;
		try {
			emptyList.first();
			FAIL() << "Test failed";
		} catch (const EmptyContainerException& ex) {
			EXPECT_EQ("Empty list", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeListTest, last_emptyList) {
		nList emptyList;
		try {
			emptyList.last();
			FAIL() << "Test failed";
		} catch (const EmptyContainerException& ex) {
			EXPECT_EQ("Empty list", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeListTest, first_last) {
		nList list;
		list.insertFirst(5);
		list.insertFirst(10);
		EXPECT_EQ(10, list.first().getValue());
		EXPECT_EQ(5, list.last().getValue());
	}

	TEST(NodeListTest, position_nullNode_getValue) {
		Position pos = Position();
		try {
			pos.getValue();
			FAIL() << "Test failed";
		} catch (const InvalidPositionException& ex) {
			EXPECT_EQ("Null node", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeListTest, position_nullNode_isNull) {
		Position pos;
		EXPECT_TRUE(pos.isNull());
	}

	TEST(NodeListTest, getBefore_nullNodePosition) {
		nList list;
		try {
			list.before(Position());
			FAIL() << "Test failed";
		} catch (const InvalidPositionException& ex) {
			EXPECT_EQ("Null node", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeListTest, getAfter_nullNodePosition) {
		nList list;
		try {
			list.after(Position());
			FAIL() << "Test failed";
		} catch (const InvalidPositionException& ex) {
			EXPECT_EQ("Null node", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeListTest, insertFirst) {
		nList list;
		Position pos = list.insertFirst(5);
		EXPECT_EQ(5, pos.getValue());
		EXPECT_EQ(1, list.size());
		EXPECT_TRUE(list.isFirst(pos));
		EXPECT_TRUE(list.isLast(pos));
	}

	TEST(NodeListTest, insertAfter) {
		nList list;
		Position pos = list.insertFirst(5);
		Position posAfter = list.insertAfter(pos, 7);
		EXPECT_EQ(7, list.after(pos).getValue());
		EXPECT_EQ(2, list.size());
		EXPECT_FALSE(list.isLast(pos));
		EXPECT_TRUE(list.isLast(posAfter));
	}

	TEST(NodeListTest, insertBefore) {
		nList list;
		Position pos = list.insertFirst(5);
		Position posAfter = list.insertAfter(pos, 7);
		Position posBefore = list.insertBefore(pos, 11);
		EXPECT_EQ(11, list.before(pos).getValue());
		EXPECT_EQ(3, list.size());
		EXPECT_FALSE(list.isFirst(pos));
		EXPECT_TRUE(list.isFirst(posBefore));
	}

	TEST(NodeListTest, replace) {
		nList list;
		list.insertFirst(5);
		Position pos = list.insertFirst(7);
		list.insertFirst(9);
		list.replace(pos, 3);
		EXPECT_EQ(3, pos.getValue());
	}

	TEST(NodeListTest, swap) {
		nList list;
		Position pos1 = list.insertFirst(5);
		Position pos2 = list.insertAfter(pos1, 7);
		list.swap(pos1, pos2);
		EXPECT_EQ(7, pos1.getValue());
		EXPECT_EQ(5, pos2.getValue());
	}

	TEST(NodeListTest, remove) {
		nList list;
		Position pos1 = list.insertFirst(5);
		Position pos2 = list.insertAfter(pos1, 7);
		EXPECT_EQ(2, list.size());
		EXPECT_EQ(5, list.first().getValue());
		list.remove(pos1);
		EXPECT_EQ(1, list.size());
		EXPECT_EQ(7, list.first().getValue());
	}
	TEST(NodeListTest, removeNullNode) {
		nList list;
		try {
			list.remove(Position());
			FAIL() << "Test failed";
		} catch (const InvalidPositionException& ex) {
			EXPECT_EQ("Null node", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(NodeListTest, clear) {
		nList list;
		Position pos = list.insertFirst(5);
		list.insertFirst(7);
		EXPECT_EQ(2, list.size());
		list.clear();
		EXPECT_EQ(0, list.size());
		try {
			list.after(pos);
			FAIL() << "Test failed";
		} catch (const BoundaryViolationException& ex) {
			EXPECT_EQ("Boundary violation: rear", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}
