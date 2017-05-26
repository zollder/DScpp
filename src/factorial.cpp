/*
 * factorial.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

int factorial(int n) {
        int result = 1;
        for (int i = 1; i <= n; i++) {
                result *= i;
         }
        return result;
}


