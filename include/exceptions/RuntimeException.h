/*
 * RuntimeException.h
 *
 *  Created on: Mar 17, 2017
 *      Author: zollder
 */

#ifndef EXCEPTIONS_RUNTIMEEXCEPTION_H_
#define EXCEPTIONS_RUNTIMEEXCEPTION_H_

#include <iostream>
#include <string>

using std::string;

class RuntimeException {

private:
	string errorMessage;

public:
	RuntimeException( const string& error) {
		errorMessage = error;
	}

	string getMessage() const {
		return errorMessage;
	}

};

/**
 * Friend function to print error message.
 */
inline std::ostream& operator<<(std::ostream& out, const RuntimeException& ex) {
	return out << ex.getMessage();
}

#endif /* EXCEPTIONS_RUNTIMEEXCEPTION_H_ */
