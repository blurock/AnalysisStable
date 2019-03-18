/*  FILE     MatrixUtilities.hh
**  PACKAGE  MatrixUtilities
**  AUTHOR   Yuri Tsybukh, extensively modified by Edward S. Blurock
**			  splitted and modified by Harald Wahl
**
**  CONTENT
**
**  OVERVIEW
**
**  IMPLEMENTATION
**    
**  REFERENCES
**
*/
 
#ifndef REACTION_MATRIXUTILITIES_HH
#define REACTION_MATRIXUTILITIES_HH

#ifdef _msdos_stl
#include <algorithm>
#include <deque>
#include <functional>
#include <map>
//#include <ostream>
#include <iostream>
#include <iterator>
#include <fstream>
#include <list>
//#include <numeric>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
#pragma warning(disable:4786)
#endif

#ifdef _unix
#include "Basis/STL.h"
#include <iomanip>
#endif
#include <math.h>


#include "defines.hh"
//#include "Basis/Vector.hh"


// whchange
//typedef vector<int> myvector_int;
#include "MatrixUtilitiesType.hh"


/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define ROTATE(a,i,j,k,l) g = a[i][j]; h = a[k][l];\
a[i][j] = g-s*(h+g*tau); a[k][l] = h+s*(g-h*tau);

void jacobi(MatrixNumeric& A, VectorNumeric& d, MatrixNumeric& V, int& nrot);
VectorNumeric SolveLinearSystemOfEquations(MatrixNumeric& mat, 
					   VectorNumeric& vec);
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
// Inlines 
//#ifdef _sniff
//#include "MatrixUtilities.icc"
//#else
//#include "BasisSrc/MatrixUtilities/MatrixUtilities.icc"
//#endif

	  
#endif
