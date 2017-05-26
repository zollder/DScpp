/*
 * Sequence.h
 *
 *  Created on: May 17, 2017
 *      Author: zollder
 */

#ifndef INCLUDE_SEQUENCE_H_
#define INCLUDE_SEQUENCE_H_

template <typename Object>
class Sequence : public List<Object> {
public:
	Position atRank(int rank) const throw (BoundaryViolationException);
	int rankOf(Position& position) const throw (InvalidPositionException);
};

#endif /* INCLUDE_SEQUENCE_H_ */
