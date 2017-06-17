/*
 * test_bubblesort.cpp
 *
 *  Created on: May 26, 2017
 *      Author: zollder
 */

# include "../src/HeapSort.cpp"
# include "../src/Utilities.cpp"

# include "stdio.h"
# include "gtest/gtest.h"

	using namespace std;

	TEST(HeapSortTest, heapsort_int) {
		HeapSort<int> mSort;
		Utilities<int> Utils;
		vector<int> initData = {12,11,15,10,9,1,2,3,13,14,4,5,6,7,8};
		vector<int> expectedResult = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

		mSort.sort(initData);
		Utils.print(initData);
		EXPECT_TRUE(Utils.equal(initData, expectedResult));
	}

	TEST(HeapSortTest, heapsort_double) {
		HeapSort<double> mSort;
		Utilities<double> Utils;
		vector<double> initData = {12.1, 11.5, 15.7, 10.2, 9.0, 1.3, 2.5, 3.7,
				13.9, 14.01, 4.03, 5.05, 6.07, 7.09, 8.2};
		vector<double> expectedResult = {1.3, 2.5, 3.7, 4.03, 5.05, 6.07, 7.09,
				8.2, 9, 10.2, 11.5, 12.1, 13.9, 14.01, 15.7};

		mSort.sort(initData);
		Utils.print(initData);
		EXPECT_TRUE(Utils.equal(initData, expectedResult));
	}
