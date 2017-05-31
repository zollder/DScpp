/*
 * test_btree.cpp
 */

# include "stdio.h"
# include "gtest/gtest.h"
# include "../include/BTree.h"

	typedef BTree<int> tree;
	typedef tree::Position Position;

	TEST(BTreeTest, newTree) {
		tree newTree;
		EXPECT_EQ(0, newTree.size());
		EXPECT_TRUE(newTree.isEmpty());
	}

	TEST(BTreeTest, insertRoot) {
		tree newTree;
		newTree.insert(10);
		EXPECT_EQ(1, newTree.size());
		EXPECT_FALSE(newTree.isEmpty());
		EXPECT_EQ(10, newTree.getRootPosition().getValue());
	}

	TEST(BTreeTest, addAll) {
		tree newTree;
		newTree.addAll({10,7,15,5,9,20,12,17});
		EXPECT_EQ(8, newTree.size());
		EXPECT_FALSE(newTree.isEmpty());
		EXPECT_EQ(10, newTree.getRootPosition().getValue());
	}

/*	TEST(NodeListTest, first_last) {
		nList list;
		list.insertFirst(5);
		list.insertFirst(10);
		EXPECT_EQ(10, list.first().getValue());
		EXPECT_EQ(5, list.last().getValue());
	}

	TEST(NodeListTest, position_nullNode_isNull) {
		Position pos;
		EXPECT_TRUE(pos.isNull());
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
	}*/

/*	TEST(NodeListTest, insertBefore) {
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
	}*/
