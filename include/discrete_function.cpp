/************************************************************************************
Header file for a function class.
By "discrete_function", we understand a vector of degrees,
however, understood as function values at certain values.
Such functions will model an approximation of the stable rank function.
*************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath> 
#include <math.h>
#include "degrees.h"
#include "discrete_function.h"

double Lpdist(Discrete_Function fun1, Discrete_Function fun2, double p) {
	double result = 0;
	double anotherportion = 0;
	double bad_p = 1 / p;
	double rectangle1;
	double rectangle2;
	// note: we assume here that the two discrete functions have are sorted and have the same indices, i.e., the same first values of their degrees.
	// just as quick check:
	if (fun1.size() != fun2.size()) {
		std::cout << "Something went wrong! The two functions don't follow the same approximation pattern. We give back 0 distance." << std::endl;
		return result;
	}
	else {
		for (int i = 0; i < fun1.size()-1; i++) { // we add all differences of rectangles to the power of p
			rectangle1 = (fun1[i+1].first - fun1[i].first) * (fun1[i + 1].second);
			rectangle2 = (fun2[i + 1].first - fun2[i].first) * (fun2[i + 1].second);
			if (rectangle2 > rectangle1) {
				anotherportion = rectangle2 - rectangle1;
			}
			else {
				anotherportion = rectangle1 - rectangle2;
			}
			anotherportion = pow(anotherportion, p);
			result = result + anotherportion;
		}
		result = pow(result, bad_p);
		return result;
	}
}


void Print_Discrete_Function(Discrete_Function fun) {
	std::cout << std::endl;
	std::cout << "We computed the following values as discrete function:" << std::endl;
	printdegrees(fun);
	std::cout << std::endl;
}