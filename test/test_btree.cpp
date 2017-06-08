/*
 * test_btree.cpp
 */

# include "stdio.h"
# include "gtest/gtest.h"
# include "../include/BTree.h"

	typedef BTree<int> Tree;
	typedef Tree::Position Position;

	TEST(BTreeTest, newTree) {
		Tree tree;
		EXPECT_EQ(0, tree.size());
		EXPECT_TRUE(tree.isEmpty());
	}

	TEST(BTreeTest, insertRoot) {
		Tree tree;
		tree.insert(10);
		EXPECT_EQ(1, tree.size());
		EXPECT_FALSE(tree.isEmpty());
		EXPECT_EQ(10, tree.getRootPosition().getValue());
	}

	TEST(BTreeTest, insertKey) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});

		// insert existing keys
		EXPECT_EQ(15, tree.insert(15).getValue());
		EXPECT_EQ(5, tree.insert(5).getValue());
		EXPECT_EQ(8, tree.size());

		// insert non-existing keys
		EXPECT_EQ(3, tree.insert(3).getValue());
		EXPECT_EQ(11, tree.insert(11).getValue());
		EXPECT_EQ(10, tree.size());
	}

	TEST(BTreeTest, findExistingKey) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});

		EXPECT_EQ(9, tree.find(9).getValue());
		EXPECT_EQ(20, tree.find(20).getValue());
	}

	TEST(BTreeTest, findMissingKey) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		try {
			tree.find(100).getValue();
			FAIL() << "Test failed";
		} catch (const NotFoundException& ex) {
			EXPECT_EQ("Key not found", ex.getMessage());
		} catch (...) {
			FAIL() << "Wrong exception";
		}
	}

	TEST(BTreeTest, remove_emptyTree) {
		Tree tree;
		EXPECT_FALSE(tree.remove(1));
	}

	TEST(BTreeTest, remove_missingKey) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		EXPECT_FALSE(tree.remove(100));
	}

	TEST(BTreeTest, remove_existingKey) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		EXPECT_EQ(8, tree.size());

		EXPECT_TRUE(tree.remove(15));
		EXPECT_TRUE(tree.remove(17));
		EXPECT_EQ(6, tree.size());

		EXPECT_FALSE(tree.remove(15));
		EXPECT_FALSE(tree.remove(17));
		EXPECT_EQ(6, tree.size());
	}

	TEST(BTreeTest, clearTree) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		EXPECT_EQ(8, tree.size());
		tree.clear();
		EXPECT_EQ(0, tree.size());
	}

	TEST(BTreeTest, nodeDepth) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		EXPECT_EQ(1, tree.depth(tree.find(15)));
		EXPECT_EQ(3, tree.depth(tree.find(17)));
	}

	TEST(BTreeTest, nodeHeight) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		EXPECT_EQ(3, tree.height(tree.find(15)));
		EXPECT_EQ(1, tree.height(tree.find(17)));
	}

	TEST(BTreeTest, inorderPrint) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		tree.printInorder();
	}

	TEST(BTreeTest, preorderPrint) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		tree.printPreorder();
	}

	TEST(BTreeTest, postorderPrint) {
		Tree tree;
		tree.addAll({10,7,15,5,9,20,12,17});
		tree.printPostorder();
	}
