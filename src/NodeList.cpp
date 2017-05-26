/*
 * NodeList.h
 *
 *  Created on: May 10, 2017
 *      Author: zollder
 */

//#ifndef NODELIST_H_
//#define NODELIST_H_

#include "../include/List.h.txt"
#include <vector>

using namespace::std;

template <class T>
class NodeList {

	protected:
		struct Node {
			T value;
			Node* prev;
			Node* next;
			Node(const T& val = T(), Node* prv = nullptr, Node* nxt = nullptr)
				: value(val), prev(prv), next(nxt) {}
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

				~Position() {
					// position node is deleted upon list cleanup
				}

				T& getValue() {
					if (node == nullptr) {
						throw InvalidPositionException("Null node");
					} else {
						return node->value;
					}
				}

				bool isNull() {
					return node == nullptr;
				}

				friend class NodeList<T>;
		};

	private:
		int sz;

	protected:
		NodePtr header;
		NodePtr trailer;

		/*
		 * Converts Positions to a NodePtr
		 * Throws exception if position is null
		 */
		NodePtr getNodePtr(const Position& position) const throw (InvalidPositionException) {
			if (position.node != nullptr) {
				return position.node;
			} else {
				throw InvalidPositionException("Null node");
			}
		}

	public:
		// TODO: add copy constructor and assignment operator
		NodeList() {
			sz = 0;
			header = new Node;
			trailer = new Node;
			header->next = trailer;
			header->prev = nullptr;
			trailer->prev = header;
			trailer->next = nullptr;
		}

		~NodeList() {
			clear();
			delete header;
			delete trailer;
		}

		int size() const {
			return sz;
		}

		bool isEmpty() const {
			return sz == 0;
		}

		bool isFirst(const Position& position) {
			return getNodePtr(position)->prev == header;
		}

		bool isLast(const Position& position) {
			return getNodePtr(position)->next == trailer;
		}

		Position first() const throw (EmptyContainerException) {
			if (isEmpty()) {
				throw EmptyContainerException("Empty list");
			} else {
				return Position(header->next);
			}
		}

		Position last() const throw (EmptyContainerException) {
			if (isEmpty()) {
				throw EmptyContainerException("Empty list");
			} else {
				return Position(trailer->prev);
			}
		}

		Position before(const Position& position) const throw (InvalidPositionException, BoundaryViolationException) {
			NodePtr node = getNodePtr(position)->prev;
			if (node == header) {
				throw BoundaryViolationException("Boundary violation: front");
			}
			return Position(node);
		}

		Position after(const Position& position) const throw (InvalidPositionException, BoundaryViolationException) {
			NodePtr node = getNodePtr(position)->next;
			if (node == trailer) {
				throw BoundaryViolationException("Boundary violation: rear");
			}
			return Position(node);
		}

		Position insertFirst(const T& value) {
			sz++;
			NodePtr newNode = new Node(value, header, header->next);
			header->next->prev = newNode;
			header->next = newNode;
			return Position(newNode);
		}

		Position insertLast(const T& value) {
			sz++;
			NodePtr newNode = new Node(value, trailer->prev, trailer);
			trailer->prev->next = newNode;
			trailer->prev = newNode;
			return Position(newNode);
		}

		Position insertBefore(const Position& position, const T& value) throw (InvalidPositionException) {
			NodePtr node = getNodePtr(position);
			sz++;
			NodePtr newNode = new Node(value, node->prev, node);
			node->prev->next = newNode;
			node->prev = newNode;
			return Position(newNode);
		}

		Position insertAfter(const Position& position, const T& value) throw (InvalidPositionException) {
			NodePtr node = getNodePtr(position);
			sz++;
			NodePtr newNode = new Node(value, node, node->next);
			node->next->prev = newNode;
			node->next = newNode;
			return Position(newNode);
		}

		void addAll(const vector<T> &values) {
			for (int i = 0; i < values.size(); i++) {
				insertLast(values[i]);
			}
		}

		void replace(const Position& position, const T& val) {
			if (position.node != nullptr) {
				getNodePtr(position)->value = val;
			}
		}

		void swap(const Position& position1, const Position& position2) const throw (InvalidPositionException) {
			T value = getNodePtr(position1)->value;
			getNodePtr(position1)->value = getNodePtr(position2)->value;
			getNodePtr(position2)->value = value;
		}

		void remove(const Position& position) throw (InvalidPositionException) {
			NodePtr node = getNodePtr(position);
			sz--;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;
		}

		/* Deletes all the elements of a linked list */
		void clear() {
			if (size() > 0) {
				NodePtr node = header->next;
				while (node != trailer) {
					NodePtr nextNode = node->next;
					delete node;
					node = nextNode;
				}
				sz = 0;
			}
		}

		void print() {
			NodePtr node = header->next;
			while (node != trailer) {
				printf("%d ", node->value);
				node = node->next;
			}
		}
};

//#endif /* NODELIST_H_ */
