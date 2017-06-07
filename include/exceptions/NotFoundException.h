/*
 * NotFoundException.h
 *
 *  Created on: Jun 6, 2017
 *      Author: zollder
 */

#ifndef INCLUDE_EXCEPTIONS_NOTFOUNDEXCEPTION_H_
#define INCLUDE_EXCEPTIONS_NOTFOUNDEXCEPTION_H_

#include "RuntimeException.h"
#include <string>
using std::string;

class NotFoundException : public RuntimeException {
public:
	NotFoundException(const string& error) : RuntimeException(error) {}
};

#endif /* INCLUDE_EXCEPTIONS_NOTFOUNDEXCEPTION_H_ */
