/************************************************************************************
Header file for interval class.
By "interval", we understand a pair of degrees.
Between these degrees, the interval module is nonzero.
*************************************************************************************/

#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdio.h>  
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h> 
#include "degrees.h"
#include "discrete_function.h"

class Interval
{
private:

public:
	Degrees gens; // degrees of generators
	Degrees rels; // degrees of relations
	int numgens; // number of generators
	int numrels; // number of relations
	// construct
	Interval(Degrees input_degs1, Degrees input_degs2);
	// initialize the variables:
	void SetInterval(Degrees input_degs1, Degrees input_degs2);
	// read from file
	void read_from_file(std::ifstream& intervalfile);
	// debug, test & co
	void print_interval();
	// basic functions
	void order(); // orders gens and relations in the corresponding arrays
	void add_gen(Degree add_degree); // add a generator (by degree)
	void add_rel(Degree add_degree); // add a relation (by degree)
	void delete_gen(int delete_degree); // delete a generator from the array
	void delete_rel(int delete_degree); // delete a relation from the array
	// check if the input defines an interval module
	bool are_total(); // check if degrees of generators and relations are incomparable
	bool is_above(Degree shiftedgen); // check if a degree is above the interval
	bool welldefined(); // check if gens and rels define an interval, i.e., run are_total() and check that the degrees of the generators are below the degrees of the relations
	// functions
	int shift_dim(Degree shiftvalue); // compute the shift dimension
	Degrees get_basis(Degree shiftvalue); // get a shiftvalue-basis
	Discrete_Function stable_rank(Degree shiftvalue, double length, double coarsity); // compute a discrete approximation of stable rank
};

#endif // INTERVAL_H
