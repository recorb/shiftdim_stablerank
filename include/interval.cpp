/************************************************************************************
Cpp file for interval class.
By "interval", we understand a pair of degrees.
Between these degrees, the interval module is nonzero.
*************************************************************************************/

#include <stdio.h>  
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath> 
#include <math.h>
#include "degrees.h"
#include "interval.h"


// constructor
Interval::Interval(std::vector<std::pair<double, double>> input_degs1, std::vector<std::pair<double, double>> input_degs2) {
	SetInterval(input_degs1, input_degs2);
}

// initialize the degrees
void Interval::SetInterval(std::vector<std::pair<double, double>> input_degs1, std::vector<std::pair<double, double>> input_degs2) {
	gens = input_degs1;
	rels = input_degs2;
	numgens = numberofdegrees(gens);
	numrels = numberofdegrees(rels);
	order();
	//welldefined();
}


// -------------------- read from file

// read the interval from a text file 
// we allow integer values and doubles, written for example as 1.5
// Format: first line should be "Generators"
// Then degrees of generators line by line as "number emptyspace number"
// Then a line should say "Relations"
// Then degrees of relations in the same format
void Interval::read_from_file(std::ifstream& intervalfile) {
	Degrees gen_degrees;
	Degrees rel_degrees;
	Degree addthis;
	std::string templine;
	std::string tempstring1;
	std::string tempstring2;
	bool counter;
	// first line is "generators"
	while (intervalfile) {
		std::getline(intervalfile, templine);
		// go to start of first number
		if (!isdigit(templine[0])) { // should read "Generators"
			//std::cout << "found line: " << templine << '\n';
		}
		if (isdigit(templine[0])) { // should not be true.
			std::cout << "Reading error! We found int value: " << templine << ". It shouldn't be there!" << '\n';
		}
		else break;
	}
	// Now we get the generators, line by line until there is non-digit line
	while (intervalfile) {
		std::getline(intervalfile, templine);
		if (isdigit(templine[0])) {
			//std::cout << "here's a read line: " << templine << '\n';
			counter = 0;
			tempstring1.clear();
			tempstring2.clear();
			for (unsigned int i = 0; i < templine.length(); i++) { // go through all the characters of the line
				if (isspace(templine[i])) {
					counter = 1;
					//std::cout << templine[i];
				}
				else { // write the characters in string
					//std::cout << templine[i];
					if (counter == 0) {
						tempstring1.insert(tempstring1.end(), templine[i]);
						//tempstring1.insert(i,templine);
						//std::cout << tempstring1 << '\n';
						//std::cout <<  1 << '\n';
					}
					else {
						tempstring2.insert(tempstring2.end(), templine[i]);
						//std::cout << tempstring2 << '\n';
					}
				}
			}
			//std::cout << tempstring1 << '\n';
			//std::cout << tempstring2 << '\n';
			addthis = std::make_pair(stod(tempstring1), stod(tempstring2)); // get a degree from the strings
			gen_degrees.push_back(addthis); // add this degree
		}
		else break;
	}
	// Now, a line should be called "relations"
	//std::cout << "found line: " << templine << '\n';
	// Now we get the relations, line by line
	while (intervalfile) {
		templine.clear();
		std::getline(intervalfile, templine);
		if (isdigit(templine[0])) {
			//std::cout << "here's a read line: " << templine << '\n';
			counter = 0;
			tempstring1.clear();
			tempstring2.clear();
			for (unsigned int i = 0; i < templine.length(); i++) { // go through all the characters of the line
				if (isspace(templine[i])) {
					counter = 1;
					//std::cout << templine[i];
				}
				else { // write the characters in string
					//std::cout << templine[i];
					if (counter == 0) {
						tempstring1.insert(tempstring1.end(), templine[i]);
					}
					else {
						tempstring2.insert(tempstring2.end(), templine[i]);
					}
				}
			}
			//std::cout << tempstring1 << '\n';
			//std::cout << tempstring2 << '\n';
			addthis = std::make_pair(stod(tempstring1), stod(tempstring2)); // get a degree from the strings
			rel_degrees.push_back(addthis); //add this degree
		}
		else break;
	}
	// Define the interval
	SetInterval(gen_degrees, rel_degrees);
}

// -------------------- debug, test & co

void Interval::print_interval() {
	std::cout << "We have generators in the following degrees: " << std::endl;
	printdegrees(gens);
	std::cout << "We have relations in the following degrees: " << std::endl;
	printdegrees(rels);
}

// -------------------- basic functions

// add a generator at the right index
void Interval::add_gen(Degree add_degree) {
	gens.push_back(add_degree);
	numgens = numgens + 1;
	// order(); // Should be commented to reduce time complexity. The user should call order() and welldefined() themselves at the end!
}

// add a relation at the right index
void Interval::add_rel(Degree add_degree) {
	rels.push_back(add_degree);
	numrels = numrels + 1;
	// order(); // Should be commented to reduce time complexity. The user should call order() and welldefined() themselves at the end!
}

// delete a generator from the list
void Interval::delete_gen(int delete_degree) {
	if (delete_degree < numgens) {
		gens.erase(gens.begin() + delete_degree);
		numgens = numgens - 1;
	}
	else {
		std::cout << " The generator could NOT be removed since it is out of range! " << std::endl;
	}
}

// delete a relation from the list
void Interval::delete_rel(int delete_degree) {
	if (delete_degree < numrels) {
		rels.erase(rels.begin() + delete_degree);
		numrels = numrels - 1;
	}
	else {
		std::cout << " The relation could NOT be removed since it is out of range! " << std::endl;
	}
}

// -------------------- check if the input defines an interval module


// Compares first elements of each pair
static bool compare_first(Degree degree1, Degree degree2) {
	return degree1.first < degree2.first;
}

// order the generators and relations
void Interval::order() {
	std::sort(gens.begin(), gens.end(), compare_first);
	std::sort(rels.begin(), rels.end(), compare_first);
}

// check if the second coordinates are reversely ordered
bool Interval::are_total() {
	bool totalanswer = 1;
	for (int i = 0; i < numgens - 1; i++) {
		if (gens[i].second <= gens[i + 1].second)
		{
			std::cout << " THE DEGREES ARE NOT SUITABLE AS MINIMAL GENERATORS FOR AN INTERVAL MODULE! " << std::endl;
			totalanswer = 0;
			break;
		}
	}
	for (int i = 0; i < numrels - 1; i++) {
		if (rels[i].second <= rels[i + 1].second)
		{
			std::cout << " THE DEGREES ARE NOT SUITABLE AS MINIMAL RELATIONS FOR AN INTERVAL MODULE! " << std::endl;
			totalanswer = 0;
			break;
		}
	}
	return totalanswer;
}

// check if a degree is above the interval
bool Interval::is_above(Degree shiftedgen) {
	bool above = 0;
	for (int i = 0; i < numrels; i++) {
		if (shiftedgen.first >= rels[i].first) {
			if (shiftedgen.second >= rels[i].second) {
				above = 1;
				break;
			}
		}
		else break;
		if (above == 1) break;
	}
	return above;
}

// check if the interval is welldefined
bool Interval::welldefined() {
	bool answer = 1;
	bool above = 0;
	// first check minimality
	answer = are_total();
	// now check that all relations are above some generator
	for (int i = 0; i < numrels; i++) {
		for (int j = 0; j < numgens; j++) {
			if (rels[i].first >= gens[j].first && rels[i].second >= gens[j].second) { // relation is above the current generator
				if (rels[i].first == gens[j].first && rels[i].second == gens[j].second) {
					answer = 0; // relation = generator is not desired!
					std::cout << "A relation is equal to a generator!" << std::endl;
					return answer;
				}
				else above = 1;
			}
			if (above == 1) {
				above = 0;
				j = numgens + 1; // found a generator below; so end the for loop
			}
			if (j == numgens - 1) { // could not find a generator below
				std::cout << "Found a relation that is not above any of the generators!" << std::endl;
				answer = 0;
				return answer;
			}
		}
	}
	return answer;
}

// -------------------- operations

// compute the shift-dimension of an interval module
int Interval::shift_dim(Degree shiftvalue) {
	int shiftdim = 0;
	Degree tempdegree;
	for (int i = 0; i < numgens; i++) { // walk through the array of generators
		tempdegree = shift(gens[i], shiftvalue); // shift current generator
		if (is_above(tempdegree)) { // we can go to the next one if its shift is 0 in the module
		}
		else { // the shift is not 0 in the module.
			shiftdim = shiftdim + 1;
			while (tempdegree.first >= gens[i].first) { // find the last generator that is left from the shift
				i++; //note: might be out of range of gens now! in that case, we are done.
				if (i == numgens) return shiftdim;
			} // current generator is the first one that is right from the shift
			tempdegree = std::make_pair(tempdegree.first, gens[i - 1].second); // projection to the generating line of the interval module
			tempdegree = negshift(tempdegree, shiftvalue);
			while (tempdegree.second <= gens[i].second) { // find the last generator that is above from the negshift of the projection
				i++; //note: might be out of range of gens now! in that case, we are done.
				if (i == numgens) return shiftdim;
			} // current generator is the first one that is below the negshift
			tempdegree = std::make_pair(gens[i - 1].first, tempdegree.second); // projection to the generating line of the interval module. not necessary, actually
			i--; // we do i++ anyway in the for-loop
		}
	}
	return shiftdim;
}

// get a shiftvalue-basis
// is nearly the same as the computation of the shift-dim!
Degrees Interval::get_basis(Degree shiftvalue) {
	Degrees basis;
	Degree tempdegree;
	for (int i = 0; i < numgens; i++) { // walk through the array of generators
		tempdegree = shift(gens[i], shiftvalue); // shift current generator
		if (is_above(tempdegree)) { // we can go to the next one if its shift is 0 in the module
		}
		else { // the shift is not 0 in the module.
			//shiftdim = shiftdim + 1;
			while (tempdegree.first >= gens[i].first) { // find the last generator that is left from the shift
				i++; //note: might be out of range of gens now! in that case, we are done.
				if (i == numgens) {
					basis.push_back(tempdegree);
					return basis;
				}
			} // current generator is the first one that is right from the shift
			tempdegree = std::make_pair(tempdegree.first, gens[i - 1].second); // projection to the generating line of the interval module
			basis.push_back(tempdegree);
			tempdegree = negshift(tempdegree, shiftvalue);
			while (tempdegree.second <= gens[i].second) { // find the last generator that is above from the negshift of the projection
				i++; //note: might be out of range of gens now! in that case, we are done.
				if (i == numgens) return basis;
			} // current generator is the first one that is below the negshift
			tempdegree = std::make_pair(gens[i - 1].first, tempdegree.second); // projection to the generating line of the interval module. not necessary, actually
			i--; // we do i++ anyway in the for-loop
		}
	}
	return basis;
}

Discrete_Function Interval::stable_rank(Degree shiftvalue, double length, double coarsity) {
	Discrete_Function fun;
	Degree tempvalue;
	Degree stretched_shift;
	int shiftdim=0;
	int quantity = int(length / coarsity);
	for (int n = 0; n < quantity; n++) {
		stretched_shift = std::make_pair(n * coarsity * shiftvalue.first, n * coarsity * shiftvalue.second);
		shiftdim = shift_dim(stretched_shift);
		tempvalue = std::make_pair(n * coarsity, shiftdim);
		fun.push_back(tempvalue);
	}
	return fun;
}