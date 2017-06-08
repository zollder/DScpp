/*
 * BTree.h
 */

#ifndef INCLUDE_BTREE_H_
#define INCLUDE_BTREE_H_

#include "exceptions/InvalidPositionException.h"
#include "exceptions/NotFoundException.h"

#include <vector>
#include "stdio.h"

using namespace::std;

template <class T>
class BTree {
	protected:
		struct Node {
			T value;
			Node* left;
			Node* right;
			Node* parent;

			Node(const T& v = T(),
					Node* l = nullptr,
					Node* r = nullptr,
					Node* p = nullptr)
					: value(v), left(l), right(r), parent(p) {}

			Node* getSibling() {
				return (this == parent->left ? parent->right : parent->left);
			}

			T& getValue() {
				return this->value;
			}

			bool isExternal() {
				return left == nullptr && right == nullptr;
			}

			bool isRoot() {
				return parent == nullptr;
			}
		};
		typedef Node* NodePtr;

	public:
		class Position {
			private:
				NodePtr node;

			public:
				Position(NodePtr n = nullptr) {
					node = n;
				}

				T& getValue() {
					return node->getValue();
				}

				bool isNull() {
					return node == nullptr;
				}

				friend BTree;
		};

	private:
		NodePtr root;
		int sz;

	public:
		BTree() {
			root = nullptr;
			sz = 0;
		}

		~BTree() {
			clear();
		}

		/* Converts Positions to a NodePtr
		 * Throws exception if position is null */
		NodePtr getNodePtr(const Position& position) const throw (InvalidPositionException) {
			if (position.node != nullptr) {
				return position.node;
			} else {
				throw InvalidPositionException("Null node");
			}
		}

		bool isEmpty() const {
			return sz == 0;
		}

		int size() const {
			return sz;
		}

		int depth(const Position& pos) {
			return getNodeDepth(getNodePtr(pos));
		}

		int height(const Position& pos) {
			return getNodeHeight(getNodePtr(pos));
		}

		bool isRoot(const Position& pos) const {
			return getNodePtr(pos)->isRoot();
		}

		Position getRootPosition() const {
			return Position(getRoot());
		}

		Position find(const T& key) const throw (NotFoundException) {
			NodePtr node = findKey(key);
			if (node->isExternal()) {
				throw NotFoundException("Key not found");
			} else {
				return Position(node);
			}
		}

		Position insert(const T& key) {
			return Position(insertKey(key));
		}

		bool remove(const T& key) {
			return removeKey(key);
		}

		void clear() {
			if (!isEmpty()) {
				clear(getRoot());
			}
		}

		bool isExternal(const Position& pos) const {
			return isExternal(getNodePtr(pos));
		}

		bool isInternal(const Position& pos) const {
			return !isExternal(getNodePtr(pos));
		}

		void addAll(const vector<T> &values) {
			for (int i = 0; i < values.size(); i++) {
				insert(values[i]);
			}
		}

		/** Depth-first tree traversal. */

		/** Inorder printing of tree elements. */
		void printInorder() {
			inorder(getRoot());
		}

		/** Preorder printing of tree elements. */
		void printPreorder() {
			preorder(getRoot());
		}

		/** Postorder printing of tree elements. */
		void printPostorder() {
			postorder(getRoot());
		}

	protected:

		NodePtr getRoot() const {
			return root;
		}

		void setRoot(NodePtr node) {
			this->root = node;
		}

		NodePtr getLeft(const NodePtr node) const {
			return node->left;
		}

		void setLeft(NodePtr node, NodePtr left) {
			node->left = left;
		}

		NodePtr getRight(const NodePtr node) const {
			return node->right;
		}

		void setRight(NodePtr node, NodePtr right) {
			node->right = right;
		}

		NodePtr getParent(const NodePtr node) const {
			return node->parent;
		}

		NodePtr getSibling(const NodePtr node) const {
			return node->getSibling();
		}

		bool isExternal(NodePtr node) {
			return node->isExternal();
		}

		int getNodeDepth(NodePtr node) {
			if (node->isRoot()) {
				return 0;
			} else {
				return 1 + getNodeDepth(node->parent);
			}
		}

		int getNodeHeight(NodePtr node) {
			if (node->isExternal()) {
				return 0;
			} else {
				return 1 + maxOf(getNodeHeight(node->left), getNodeHeight(node->right));
			}
		}

		NodePtr findKey(const T& key) const {
			return search(getRoot(), key);
		}

		NodePtr search(const NodePtr node, const T& key) const {
			if (node->isExternal() || node->value == key) {
				return node;
			} else if (node->value > key) {
				return search(node->left, key);
			} else {
				return search(node->right, key);
			}
		}

		NodePtr insertKey(const T& key) {
			if (isEmpty()) {
				root = new Node;
			}
			NodePtr node = search(root, key);
			if (node->isExternal()) {
				expandExternal(node);
				node->value = key;
				sz++;
			} else {
				// key found, do nothing, to be implemented
			}
			return node;
		}

		void expandExternal(NodePtr node) {
			node->left = new Node;
			node->left->parent = node;
			node->right = new Node;
			node->right->parent = node;
		}

		void replace(NodePtr node, const T& val) {
			node->value = val;
		}

		bool removeKey(const T& key) {
			if (isEmpty()) {
				return false;
			}

			NodePtr node = findKey(key);
			// not found
			if (node->isExternal()) {
				return false;
			}

			if (node->isRoot() && size() == 1) {	// only root
				delete node->left;
				delete node->right;
				delete node;
				sz--;
				return true;
			}

			// internal node found
			if (node->left->isExternal()) {
				removeAboveExternal(node->left);
			} else if (node->right->isExternal()) {
				removeAboveExternal(node->right);
			} else {
				NodePtr replacement = node->right;
				while (!replacement->left->isExternal()) {
					replacement = replacement->left;
				}
				swapElements(node, replacement);
				removeAboveExternal(replacement->left);
			}
			return true;
		}

		void removeAboveExternal(NodePtr node) {
			NodePtr parent = node->parent;
			if (!parent->isRoot()) {
				NodePtr gp = parent->parent;
				if (gp->left == parent) {
					gp->left = node->getSibling();
					gp->left->parent = gp;
				} else {
					gp->right = node->getSibling();
					gp->right->parent = gp;
				}
			}
			delete node;
			delete parent;
			sz--;
		}

		void swapElements(NodePtr node1, NodePtr node2) {
			T value = node1->value;
			node1->value = node2->value;
			node2->value = value;
		}

		void clear(NodePtr node) {
			if (!node->isExternal()) {
				NodePtr left = node->left;
				NodePtr right = node->right;
				delete node;
				sz--;
				clear(left);
				clear(right);
			} else {
				delete node;
			}
		}

		int maxOf(int num1, int num2) {
			return num1 > num2 ? num1 : num2;
		}

		void inorder(NodePtr node) {
			if (!node->isExternal()) {
				inorder(node->left);
				cout << node->getValue() << " ";
				inorder(node->right);
			}
		}

		void preorder(NodePtr node) {
			if (!node->isExternal()) {
				cout << node->getValue() << " ";
				preorder(node->left);
				preorder(node->right);
			}
		}

		void postorder(NodePtr node) {
			if (!node->isExternal()) {
				postorder(node->left);
				postorder(node->right);
				cout << node->getValue() << " ";
			}
		}
};

#endif /* INCLUDE_BTREE_H_ */
