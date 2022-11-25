/************************************************************************************
Cpp file for degrees class.
By "degrees", we understand a vector of tuples of doubles.
These degrees will model generators and relations of a two-parameter interval module
*************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath> 
#include <math.h>
#include "degrees.h"

Degree shift(Degree gen, Degree shiftvalue) {
	Degree result;
	result.first = gen.first + shiftvalue.first;
	result.second = gen.second + shiftvalue.second;
	return result;
}

Degree negshift(Degree gen, Degree shiftvalue) {
	Degree result;
	result.first = gen.first - shiftvalue.first;
	result.second = gen.second - shiftvalue.second;
	return result;
}

void printdegrees(Degrees const& input) {
	//std::cout << "We have the following degrees: " << std::endl;
	for (int i = 0; i < input.size(); i++) {
		if (i == 0) {
			std::cout << "(" << input[i].first << "," << input[i].second << ")";
		}
		else
		{
			std::cout << ", (" << input[i].first << "," << input[i].second << ")";
		}
	}
	std::cout << std::endl;
}

int numberofdegrees(Degrees const& input) {
	int num = input.size();
	return num;
}

