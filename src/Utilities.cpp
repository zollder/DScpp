/*
 * HeapSort.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

# include <vector>
#include<iostream>

using namespace::std;

/*------------------------------------------------------------------------
  Declaration
 -------------------------------------------------------------------------*/
template <class T>
class Utilities {

	public:

		void print(vector<T>& elements);
		bool equal(vector<T>& v1, vector<T>& v2);
};

/*------------------------------------------------------------------------
  Implementation
 -------------------------------------------------------------------------*/

	/**
	 * Compares two vectors.
	 * Returns true if the vectors are equal.
	 */
	template <class T>
	bool Utilities<T>::equal(vector<T>& v1, vector<T>& v2) {
		if (v1.size() != v2.size()) {
			return false;
		}
		for (int i = 0; i < v1.size(); i++) {
			if (v1[i] != v2[i]) {
				return false;
			}
		}
		return true;
	};

	/**
	 * Prints vector items to the consiole.
	 */
	template <class T>
	void Utilities<T>::print(vector<T>& items) {
		// use constant reference (don't copy by value)
		for (auto const& item : items) {
			cout << item << ' ';
		}
	}


