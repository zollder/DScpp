/*
 * InvalidPositionException.h
 *
 *  Created on: May 10, 2017
 *      Author: zollder
 */

#ifndef EXCEPTIONS_INVALIDPOSITIONEXCEPTION_H_
#define EXCEPTIONS_INVALIDPOSITIONEXCEPTION_H_

#include "RuntimeException.h"
#include <string>
using std::string;

class InvalidPositionException : public RuntimeException {
public:
	InvalidPositionException(const string& error) : RuntimeException(error) {}
};

#endif /* EXCEPTIONS_INVALIDPOSITIONEXCEPTION_H_ */
