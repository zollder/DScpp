/*
 * BoundaryViolationException.h
 *
 *  Created on: May 11, 2017
 *      Author: zollder
 */

#ifndef EXCEPTIONS_BOUNDARYVIOLATIONEXCEPTION_H_
#define EXCEPTIONS_BOUNDARYVIOLATIONEXCEPTION_H_

#include "RuntimeException.h"
#include <string>
using std::string;

class BoundaryViolationException : public RuntimeException {
public:
	BoundaryViolationException( const string& error) : RuntimeException(error) {}
};

#endif /* EXCEPTIONS_BOUNDARYVIOLATIONEXCEPTION_H_ */
