/*  FILE     MatrixNumeric.hh
**  PACKAGE  MatrixNumeric
**  AUTHOR   Yuri Tsybukh, extensively modified by Edward S. Blurock
**			 splitted and modified by Harald Wahl
**
**  CONTENT
**    Definitions for the "Matrix" package.
**
**  OVERVIEW
**		Class MatrixNumeric is designed to perform
**		some typical operations with matrices.
**		(==, <, <<, >>, Encode, Decode, TopDecode,
**		+, -, *, transpose, getMatrixColumn,
**		getMatrixrow, setSize)
**
**  IMPLEMENTATION
**    
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/
 
#ifndef REACTION_MATRIXNUMERIC_HH
#define REACTION_MATRIXNUMERIC_HH

#ifdef _msdos_stl
#include <algorithm>
#include <deque>
#include <functional>
#include <map>
#include <ostream>
#include <iostream>
#include <iterator>
#include <fstream>
#include <list>
#include <numeric>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
#pragma warning(disable:4786)
#endif

#ifdef _unix
#include "STL.h"
#include <iomanip>
#endif
#include <math.h>


#include "defines.hh"
#include "MatrixNumericType.hh"
VectorNumeric SolveLinearSystemOfEquations(MatrixNumeric& mat, 
					   VectorNumeric& vec);

#define ROTATE(a,i,j,k,l) g = a[i][j]; h = a[k][l];\
a[i][j] = g-s*(h+g*tau); a[k][l] = h+s*(g-h*tau);
 
//extern int Zero(int& x);
//extern float Zero(float& x);
//extern double Zero(double& x);

//extern int Unit(int& x);
//extern float Unit(float& x);
//extern double Unit(double& x);



/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
