/*  FILE     Vector.hh
**  PACKAGE  Vector
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Definitions for the "Vector" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef REACTION_VECTOR_HH
#define REACTION_VECTOR_HH


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _msdos_stl
#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;
#pragma warning(disable:4786)
#endif

#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"

extern int Zero(int& x);
extern float Zero(float& x);
extern double Zero(double& x);

extern int Unit(int& x);
extern float Unit(float& x);
extern double Unit(double& x);

#include "VectorType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

//template <class T>
//bool Encode(CommBuffer& buffer, Vector<T>& vec);
//template <class T>
//bool Decode(CommBuffer& buffer, Vector<T>& vec);
//template <class T>
//bool TopDecode(CommBuffer& buffer, Vector<T>*& vec);





/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "Vector.icc"

#endif


