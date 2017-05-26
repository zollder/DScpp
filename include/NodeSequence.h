/*
 * NodeSequence.cpp
 *
 *  Created on: May 17, 2017
 *      Author: zollder
 */

#include "NodeList.h"

template <class T> class NodeSequence : public NodeList<T> {

// declare unqualified members of a base class
public:
	NodeSequence() : NodeList<T>() {}	// constructor
	// TODO: add copy constructor and assignment operator

	using typename NodeList<T>::Position;
	using typename NodeList<T>::NodePtr;
	using NodeList<T>::size;
	using NodeList<T>::first;
	using NodeList<T>::getNodePtr;

protected:
	void validateRank(int rank) const throw (BoundaryViolationException) {
		if (rank < 0 || rank >= size()) {
			throw BoundaryViolationException("Invalid rank");
		}
	}

public:

	/**
	 * Returns position for specified rank.
	 */
	Position getPositionByRank(int rank) const throw (BoundaryViolationException)	{
		validateRank(rank);
		NodePtr node;
		if (rank <= size()/2) {
			// search from header
			node = this->header->next;
			for (int i = 0; i < rank; i++) {
				node = node->next;
			}
		} else {
			// search from trailer
			node = this->trailer->prev;
			for (int i = 1; i < size()-rank; i++) {
				node = node->prev;
			}
		}
		return Position(node);
	}

	/**
	 * Returns rank for specified position.
	 */
	int getRankByPosition(Position& position) const throw (InvalidPositionException) {
		NodePtr current = getNodePtr(first());
		NodePtr required = getNodePtr(position);
		int rank = 0;
		while (current != this->trailer) {
			if (current == required) {
				return rank;
			}
			rank++;
			current = current->next;
		}
		throw InvalidPositionException("Position not found");
	}

	T getValueAtRank(int rank) const throw (BoundaryViolationException) {
		validateRank(rank);
		return getPositionByRank(rank).getValue();
	}

	void insertAtRank(int rank, T& value) throw (BoundaryViolationException) {
		if (rank == size()) {
			this->insertLast(value);
		} else {
			validateRank(rank);
			this->insertBefore(getPositionByRank(rank), value);
		}
	}

	void removeAtRank(int rank) throw (BoundaryViolationException) {
		validateRank(rank);
		this->remove(getPositionByRank(rank));
	}

	void replaceAtRank(int rank, T& value) throw (BoundaryViolationException) {
		validateRank(rank);
		this->replace(getPositionByRank(rank), value);
	}
};
