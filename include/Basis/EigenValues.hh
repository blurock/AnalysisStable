/*  FILE     EigenValues.hh
**  PACKAGE  EigenValues
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Definitions for the "EigenValues" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef REACTION_EIGENVALUES_HH
#define REACTION_EIGENVALUES_HH


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _msdos_stl
#include <iostream>
#include <list>
#include <map>
using namespace std;
#pragma warning(disable:4786)
#include "relation.hh"
#endif

#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"
#include "EigenValuesType.hh"


/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
ostream& operator<<(ostream& out, const EigenVectors& mat);
ostream& operator<<(ostream& out, const SingleEigenVector& vec);

bool Encode(CommBuffer& buffer, EigenVectors& mat);
bool Decode(CommBuffer& buffer, EigenVectors& mat);

bool Encode(CommBuffer& buffer, SingleEigenVector& vec);
bool Decode(CommBuffer& buffer, SingleEigenVector& vec);

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
