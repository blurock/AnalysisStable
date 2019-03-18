/*  FILE     BasicLaTeXTable.hh
**  PACKAGE  BasicLaTeXTable
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Definitions for the "BasicLaTeXTable" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef REACTION_BASICLATEXTABLE_HH
#define REACTION_BASICLATEXTABLE_HH


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _msdos_stl
#include <iostream>
#include <list>
#include <map>
using namespace std;
#pragma warning(disable:4786)
#endif

#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"
#include "BasicLaTeXTableType.hh"


#define RIGHT_TABLE_JUSTIFICATION    1
#define LEFT_TABLE_JUSTIFICATION     2
#define CENTER_TABLE_JUSTIFICATION   3

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/


#endif
