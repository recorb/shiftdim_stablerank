# Description

This is an implementation of the computation of the shift-dimension and stable rank of a finitely presented 2-parameter interval module, following Algorithm 2.24 in "The Shift-Dimension of Multipersistence Modules" by Wojciech Chachólski, René Corbet, and Anna-Laura Sattelberger.

Given a finitely presented 2-parameter interval module, the code provides the following options:
* Check if the input is suitable as interval module
* Compute the shift-dimension of the input, with respect to a vector of choice
* Compute a v-basis of the input where v is a vector of choice
* Compute stable rank of the input, with respect to a vector of choice and a choice of scalings of the vector
* Compute the L_p distance between two stable rank functions, with respect to a number p of choice

# Input format

The input consists of two vectors of pairs of doubles. It can be defined by hand or can be given as a text file. In the latter case, the file should start with a line "Generators", followed by the minimal elements of the interval, line by line. Then a line "Relations" is expected, followed by the minimal values in which the interval is not present any more, again line by line. Double values are allowed. For some examples, see the folder "example_data".

# Usage

You can clone the code via
```
git clone git@github.com:recorb/shiftdim_stablerank.git
```
Currently the code is a header-only C++ library. We aim for producing executables in the future.

# Comments

The code requires standard C++ support but has no other dependencies.

While the shift-dimension is in general not additive, we look forward to conducting experiments with real-world data summand-wise: both in the cases that a persistence module is interval decomposable, and if there is an approximation by (signed) direct sums of interval modules.

The implementation of stable rank is relatively naive and could be speeded up in the future.

Feedback for the code is welcome and can be sent to maths (at) rene (minus) corbet (dot) de.

# References

Here is a reference to the paper:
```
@article{chacholski2021shift,
   title={The Shift-Dimension of Multipersistence Modules},
   author={Chach{\'o}lski, Wojciech and Corbet, Ren{\'e} and Sattelberger, Anna-Laura},
   journal={arXiv preprint arXiv:2112.06509},
   year={2021}
   }
```
