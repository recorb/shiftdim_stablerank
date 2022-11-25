/************************************************************************************
Header file for degrees class.
By "degrees", we understand a vector of tuples of doubles.
These degrees will model generators and relations of a two-parameter interval module
*************************************************************************************/

#ifndef DEGREES_H
#define DEGREES_H

#include <vector>
#include <string>
#include <math.h> 

typedef std::pair<double, double> Degree; 
typedef std::vector<Degree> Degrees;

Degree shift(Degree gen, Degree shiftvalue); // shift degree by a vector
Degree negshift(Degree gen, Degree shiftvalue); // shift degree by a negative of a vector

void printdegrees(Degrees const& input);
int numberofdegrees(Degrees const& input);

#endif // DEGREES_H
