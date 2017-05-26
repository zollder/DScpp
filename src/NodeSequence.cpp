/*
 * NodeSequence.cpp
 *
 *  Created on: May 17, 2017
 *      Author: zollder
 */

# include "NodeList.cpp"

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
	Position getPosition(int rank) const throw (BoundaryViolationException)	{
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
			for (int i = size(); i > 0; i--) {
				node = this->trailer->prev;
			}
		}
		return Position(node);
	}

	/**
	 * Returns rank for specified position.
	 */
	int getRank(Position& position) const throw (InvalidPositionException) {
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
		return getPosition(rank).getValue();
	}

	void insertAtRank(int rank, T& value) throw (BoundaryViolationException) {
		if (rank == size()) {
			this->insertLast(value);
		} else {
			validateRank(rank);
			this->insertBefore(getPosition(rank), value);
		}
	}

	void removeAtRank(int rank) throw (BoundaryViolationException) {
		validateRank(rank);
		this->remove(getPosition(rank));
	}

	void replaceAtRank(int rank, T& value) throw (BoundaryViolationException) {
		validateRank(rank);
		this->replace(getPosition(rank), value);
	}
};
