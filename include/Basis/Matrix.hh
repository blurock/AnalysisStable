/*  FILE     Matrix.hh
**  PACKAGE  Matrix
**  AUTHOR   Yuri Tsybukh, extensively modified by Edward S. Blurock
**
**  CONTENT
**    Definitions for the "Matrix" package.
**
**  OVERVIEW
**    Class Matrix<T> is designed to perform
**    some typical operations with matrices
**    Each matrix is represented as a set
**    (namely vector) of  vectors (rows), 
**    which in turn, contain the elements
**    of type T
**    Class uses data type vector<T>, which
**    is available by STL 
**    "Pure" vectors can, thus, be represented 
**    as objects of type vector<T>, or, 
**    alternatively as a 1xn Matrix<T>
**    For the first case, the  basic vector 
**    operations are provided
**
**  IMPLEMENTATION
**    implementation remarks
**    
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/
 
#ifndef REACTION_MATRIX_HH
#define REACTION_MATRIX_HH

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
#include <iomanip.h>
#endif

#include <math.h>

extern int Zero(int& x);
extern float Zero(float& x);
extern double Zero(double& x);

extern int Unit(int& x);
extern float Unit(float& x);
extern double Unit(double& x);
// whchange
//typedef vector<int> myvector_int;
#include "MatrixType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
// Some prototypes Class Matrix - vector operators
template<class T> 
vector<T> operator+(vector<T>, vector<T>);
template<class T>
vector<T> operator-(vector<T>, vector<T>);
template<class T>
vector<T> operator/(vector<T>, int);
template<class T>
istream& operator>>(istream&, vector<T>&);
template<class T>
ostream& operator<<(ostream&, const vector<T>&);
// Class Matrix - matrix operators prototypes.
template<class T>               
Matrix<T> operator+(Matrix<T>, Matrix<T>);
template<class T>              
Matrix<T> operator-(Matrix<T>, Matrix<T>);
template<class T>
Matrix<T> operator*(Matrix<T>, Matrix<T>);
template<class T>
istream& operator>>(istream&, Matrix<T>&);
template<class T>
ostream& operator<<(ostream&, Matrix<T>);
 
template<class T>
bool Encode(CommBuffer& buffer, Matrix<T>&);
template<class T>
bool Decode(CommBuffer& buffer, Matrix<T>&);
//template<class T>
//bool Encode(CommBuffer& buffer, vector<T>&);
//template<class T>
//bool Decode(CommBuffer& buffer, vector<T>&);
ostream& operator<<(ostream& out, const EigenVectors& mat);
bool Encode(CommBuffer& buffer, EigenVectors& mat);
bool Decode(CommBuffer& buffer, EigenVectors& mat);
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
// Inlines 
#include "Matrix.icc"
#ifdef TEMPLATE_INSTANTIATION
// Exported
#include "Matrix.itc"
#endif	  
	  
#endif
