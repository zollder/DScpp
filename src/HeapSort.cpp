/*
 * HeapSort.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

# include <vector>

using namespace::std;

/*------------------------------------------------------------------------
  Declaration
 -------------------------------------------------------------------------*/
template <class T>
class HeapSort {

	protected:
		/** Converts a collection of elements into a heap. */
		void buildHeap(vector<T>& subtree, int pos, int nSize);

	public:
		void sort(vector<T>& elements);
};

/*------------------------------------------------------------------------
  Implementation
 -------------------------------------------------------------------------*/

	/**
	 * Recursively constructs the heap from the given collection of elements.
	 * Parent-child relationships:
	 *   left child index: (2*index + 1)
	 *   right child index: (2*index + 2)
	 */
	template <typename T>
	void HeapSort<T>::buildHeap(vector<T>& subtree, int pos, int sz) {
		// initialize subtree root and calculate its children
		int largestPos = pos;
		int leftPos = 2*pos + 1;
		int rightPos = leftPos + 1;

		// find an element to be swapped, if any
		if (leftPos < sz && subtree[largestPos] < subtree[leftPos]) {
			largestPos = leftPos;
		}
		if (rightPos < sz && subtree[largestPos] < subtree[rightPos]) {
			largestPos = rightPos;
		}
		// tree has changed, fix it
		if (largestPos != pos) {
			swap(subtree[largestPos], subtree[pos]);
			buildHeap(subtree, largestPos, sz);
		}
	};

	/**
	 * Sorts a given collection of elements.
	 */
	template <class T>
	void HeapSort<T>::sort(vector<T>& elements) {
		int sz = elements.size();
		// build the heap in-place
		for (int pos = sz/2 - 1; pos >= 0; pos--) {
			buildHeap(elements, pos, sz);
		}
		for (int pos = sz - 1; pos >= 0; pos--) {
			swap(elements[0], elements[pos]);
			buildHeap(elements, 0, pos);
		}
	};
