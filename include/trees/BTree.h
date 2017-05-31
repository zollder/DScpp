/*
 * BTree.h
 *
 *  Created on: May 26, 2017
 *      Author: zollder
 */

#ifndef INCLUDE_BTREE_H_
#define INCLUDE_BTREE_H_

#include <vector>

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
			root = setRoot(new Node);
			sz = 1;
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

		int size() const {
			return sz;
		}

		bool isEmpty() const {
			return sz == 0;
		}

		bool isRoot(const Position& pos) const {
			return getNodePtr(pos)->parent == nullptr;
		}

		Position find(const T& value) {
			return Position(find(value));
		}

		Position insert(T& value) {
			return Position(insert(T& value));
		}

		Position remove(const Position& pos) {
			return nullptr;
		}

		void clear() {
			if (!isEmpty()) {

			}
		}

		bool isInternal(const Position& pos) const {
			return isInternal(getNodePtr(pos));
		}
		bool isExternal(const Position& pos) const {
			return !isInternal(pos);
		}

		void expandExternal(const Position& pos) {
			expandExternal(getNodePtr(pos));
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

		bool isInternal(NodePtr node) {
			return node->left != nullptr || node->right != nullptr;
		}

		bool isExternal(NodePtr node) {
			return !isInternal(node);
		}

		NodePtr find(const T& key) {
			NodePtr node = search(getRoot(), key);
			if (isInternal(node)) {
				return node;
			} else {
				return nullptr;
			}
		}

		NodePtr search(NodePtr node, const T& key) const {
			if (isExternal(node)) {
				return node;
			} else if (node->value == key) {
				return node;
			} else if (node->value < key) {
				return search(getLeft(node), key);
			} else {
				return search(getRight(node), key);
			}
		}

		NodePtr insert(const T& key) {
			NodePtr node = search(getRoot(), key);
			if (isInternal(node)) {
				// key found, do nothing, to be implemented
			} else {
				expandExternal(node);
				sz++;
			}
			return node;
		}

		void expandExternal(NodePtr node) {
			node->left = new Node;
			node->left->parent = node;
			node->right = new Node;
			node->right->parent = node;
			sz += 2;
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
		NodePtr remove(NodePtr node) {
			NodePtr target = find(node->value);
			if (target != nullptr) {
			}
			return target;
		}



		void clear();
};



#endif /* INCLUDE_BTREE_H_ */
