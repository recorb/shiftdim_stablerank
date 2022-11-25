/************************************************************************************
Header file for a function class.
By "discrete_function", we understand a vector of degrees, (same as "Degrees"),
however, understood as a collection of function values.
Such functions will model an approximation of the stable rank function.
*************************************************************************************/

#ifndef DISCRETE_FUNCTION_H
#define DISCRETE_FUNCTION

#include <vector>
#include <string>
#include <math.h> 
#include "degrees.h"

typedef std::vector<Degree> Discrete_Function;

double Lpdist(Discrete_Function fun1, Discrete_Function fun2, double p);
void Print_Discrete_Function(Discrete_Function fun);

#endif // DISCRETE_FUNCTION
