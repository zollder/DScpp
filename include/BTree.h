/*
 * BTree.h
 */

#ifndef INCLUDE_BTREE_H_
#define INCLUDE_BTREE_H_

#include "exceptions/InvalidPositionException.h"

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
//			clear();
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

		int size() const {
			return sz;
		}

		bool isEmpty() const {
			return sz == 0;
		}

		bool isRoot(const Position& pos) const {
			return getNodePtr(pos)->isRoot();
		}

		Position getRootPosition() const {
			return Position(getRoot());
		}

		Position find(const T& key) {
			return Position(find(key));
		}

		Position insert(const T& key) {
			return Position(insertKey(key));
		}

		Position remove(const Position& pos) {
			return remove(getNodePtr(pos)->value);
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

		void print();

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

		NodePtr find(const T& key) const {
			return search(getRoot(), key);
		}

		NodePtr search(const NodePtr node, const T& key) const {
			if (node->isExternal() || node->value == key) {
				return node;
			} else if (node->value < key) {
				return search(getLeft(node), key);
			} else {
				return search(getRight(node), key);
			}
		}

		NodePtr insertKey(const T& key) {
			if (isEmpty()) {
				root = new Node(key, new Node, new Node, nullptr);
				sz++;
			}
			NodePtr node = search(getRoot(), key);
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

		void swap(NodePtr node1, NodePtr node2) {
			T value = node1->value;
			node1->value = node2->value;
			node2->value = value;
		}

		// TODO: complete
		NodePtr remove(T& key) {
			if (isEmpty()) {
				return nullptr;	// throw an exception instead
			}

			NodePtr node = find(key);
			// not found
			if (node->isExternal()) {
				return nullptr;	// throw an exception instead
			}

			if (node->isRoot() && size() == 1) {	// only root
				delete node->left;
				delete node->right;
				delete node;
				sz--;
				return nullptr;
			}

			// internal node found
			if (node->left.isExternal()) {
				removeAboveExternal(node->left);
			} else if (node->right.isExternal()) {
				removeAboveExternal(node->right);
			} else {
				NodePtr replacement = node->right;
				while (!replacement->left->isExternal()) {
					replacement = replacement->left;
				}
				swap(node, replacement);
				removeAboveExternal(replacement);
			}
			return node;
		}

		NodePtr removeAboveExternal(NodePtr node) {
			NodePtr parent = node->parent;
			if (!parent->isRoot()) {
				NodePtr gp = parent->parent;
				if (gp->left == parent) {
					gp->left = node->getSibling();
				} else {
					gp->right = node->getSibling();
				}
			}
			delete node;
			delete parent;
			sz--;
			return parent;
		}

		void clear(NodePtr node) {
			if (node->isExternal()) {
				removeAboveExternal(node);
			} else {
				clear(node->left);
				clear(node->right);
			}

		}
};

#endif /* INCLUDE_BTREE_H_ */
