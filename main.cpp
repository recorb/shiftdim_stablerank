// Main file for computing the shift-dimension of a 2-parameter interval module.
// 
// We have the following parameters to define:
// Input file, shift / collection of shifts in a certain direction
//
// We can compute the following functions:
// Shift-dimension, stable rank of a collection of shifts, get shift-bases, check if the interval module is well-defined and minimally defined by the degrees

#include <iostream>
#include <stdio.h>  
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include "./include/degrees.h"
#include "./include/discrete_function.h"
#include "./include/interval.h"


// Choose your parameters and options here!
// 
// Location of your input files
std::string inputpath1 = "./example_data/test1quot.txt"; 
std::string inputpath2 = "./example_data/test1.txt";
// Define a collection of shifts
Degree myshift = std::make_pair(1, 1); // plug in your shift, coarsity and maximal length of the shifts here! 
double mycoarsity = .05;
int mylength = 10;
// Value p for L_p distance
double p = 2; 
// What shall we do? 1 for yes, 0 for no.
bool print_interval = 1; // Print the degrees of the interval to the console
bool check_welldef = 1; // Check if the degrees actually gives rise to minimal generators and relations of a well-defined interval module
bool get_shiftdim = 1; // Print all shift-dimensions to the console
bool get_basis = 1; // Get all (myshift)-bases
bool get_stable_rank = 1; // Compute an approximation of stable rank of the first interval in the direction of myshift, depending on coarsity and maxlength
bool get_lpdist = 1; // compute the L_p distance between the approximations of stable rank of the two intervals 

int main()
{
	Degrees test_degrees1; // can also be defined by hand here
	Degrees test_degrees2; // can also be defined by hand here
	// define the (empty) interval
	Interval myinterval(test_degrees1, test_degrees2);
	Interval myotherinterval(test_degrees1, test_degrees2);
	// read two intervals from the predefined file
	std::ifstream intervalinputfile1(inputpath1);
	if (intervalinputfile1.fail() || !intervalinputfile1.is_open()) {
		std::cout << "\n The file does not exist! \n\n";
	}
	myinterval.read_from_file(intervalinputfile1);
	//
	std::ifstream intervalinputfile2(inputpath2);
	if (intervalinputfile2.fail() || !intervalinputfile2.is_open()) {
		std::cout << "\n The file does not exist! \n\n";
	}
	myotherinterval.read_from_file(intervalinputfile2);
	// test functions
	if (print_interval == 1) {
		myinterval.print_interval();
		std::cout << std::endl << std::endl;
	}
	if (check_welldef == 1) {
		bool welldef = myinterval.welldefined();
		std::cout << "Is the interval well-defined? " << welldef << std::endl;
		std::cout << std::endl << std::endl;
	}
	//
	// check if a certain degree is above the interval
	// Degree newdeg = std::make_pair(4, 8);
	// bool isitabove = someinterval.is_above(newdeg);
	// std::cout << "Is the desired degree (" << newdeg.first << "," << newdeg.second << ") above the interval ? - " << isitabove << std::endl;
	// std::cout << std::endl;
	//
	// Compute the shift dimension
	if (get_shiftdim == 1) {
		int myshiftdim = 0;
		myshiftdim = myinterval.shift_dim(myshift);
		std::cout << "The shift-dimension of the given interval module is " << myshiftdim << " where the shift is (" << myshift.first << "," << myshift.second << ")" << "." << std::endl;
		std::cout << std::endl << std::endl;
	}
	//
	// Compute a myshift-basis
	if (get_basis == 1) {
		Degrees basis;
		basis = myinterval.get_basis(myshift);
		if (basis.size() == 0) {
			std::cout << "We did not compute a (" << myshift.first << "," << myshift.second << ")" << "-basis since any basis is the empty set.";
			std::cout << std::endl;
		}
		else {
			std::cout << "We computed the (" << myshift.first << "," << myshift.second << ")" << "-basis: ";
			printdegrees(basis);
		}
		std::cout << std::endl << std::endl;
	}
	//
	// Compute an approximation of stable rank of the first module, given the entered parameters
	if (get_stable_rank == 1) {
		std::cout << "We compute an approximation of stable rank by evaluating the shift dimension in the direction of the given shift vector:" << std::endl;
		Discrete_Function myfun;
		myfun = myinterval.stable_rank(myshift, mylength, mycoarsity);
		Print_Discrete_Function(myfun);
		std::cout << std::endl << std::endl;
	}
	//
	// Compute an approximation of stable rank of the two given modules and compute the L_p distance, given the entered parameters
	if (get_lpdist == 1) {
		std::cout << "We compute an approximation of stable rank of two intervals by evaluating the shift dimension in the direction of the given shift vector:" << std::endl; 
		Discrete_Function myfun1;
		Discrete_Function myfun2;
		std::cout << std::endl << "First one:" << std::endl;
		myfun1 = myinterval.stable_rank(myshift, mylength, mycoarsity);
		Print_Discrete_Function(myfun1);
		std::cout << "Second one:" << std::endl;
		myfun2 = myotherinterval.stable_rank(myshift, mylength, mycoarsity);
		Print_Discrete_Function(myfun2);
		double dist;
		dist = Lpdist(myfun1, myfun2, p);
		std::cout << "The L_" << p << "-distance between the stable rank approximations of the two intervals is " << dist << std::endl;
		std::cout << std::endl << std::endl;
	}
	return 1;
}
