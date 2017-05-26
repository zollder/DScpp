/*
 * EmptyContainerException.h
 *
 *  Created on: May 11, 2017
 *      Author: zollder
 */

#ifndef EXCEPTIONS_EMPTYCONTAINEREXCEPTION_H_
#define EXCEPTIONS_EMPTYCONTAINEREXCEPTION_H_

#include "RuntimeException.h"
#include <string>
using std::string;

class EmptyContainerException : public RuntimeException {
public:
	EmptyContainerException( const string& error) : RuntimeException(error) {}
};



#endif /* EXCEPTIONS_EMPTYCONTAINEREXCEPTION_H_ */
