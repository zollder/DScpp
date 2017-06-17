/*
 * MergeSort.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

/*------------------------------------------------------------------------
  Declaration
 -------------------------------------------------------------------------*/
template <typename NodeSequence>
class MergeSort {

	protected:
		void merge(NodeSequence& s1, NodeSequence& s2, NodeSequence& seq);
		void moveFirst(NodeSequence& src, NodeSequence& dest) {
			dest.insertLast(src.first().getValue());
			src.remove(src.first());
		}

	public:
		void sort(NodeSequence& sequence);
};

/*------------------------------------------------------------------------
  Implementation
 -------------------------------------------------------------------------*/

	/**
	 * Merges sorted sequences.
	 */
	template <typename NodeSequence>
	void MergeSort<NodeSequence>::merge(NodeSequence& s1, NodeSequence& s2, NodeSequence& seq) {
		while (!s1.isEmpty() & !s2.isEmpty()) {
			if (s1.first().getValue() < s2.first().getValue()) {
				moveFirst(s1, seq);
			} else {
				moveFirst(s2, seq);
			}
		}
		while (!s1.isEmpty()) {
			moveFirst(s1, seq);
		}
		while (!s2.isEmpty()) {
			moveFirst(s2, seq);
		}
	};

	/**
	 * Sort sequence.
	 */
	template <typename NodeSequence>
	void MergeSort<NodeSequence>::sort(NodeSequence& seq) {
		if (seq.size() <= 1) {
			return;
		}
		NodeSequence s1, s2;
		int size = seq.size();
		int i;
		for (i = size; i > size/2; i--) {
			moveFirst(seq, s1);
		}
		for (; i > 0; i--) {
			moveFirst(seq, s2);
		}
		// recursively partition the sequence
		sort(s1);
		sort(s2);
		// merge & sort
		merge(s1, s2, seq);
	};


