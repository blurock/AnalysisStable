/*  FILE     Objects.hh
**  PACKAGE  Objects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Definitions for the "Objects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/
 
#ifndef REACTION_OBJECTS_HH
#define REACTION_OBJECTS_HH
#define SEARCHABLE_KEYWORD  1
#define SEARCHABLE_OBJECT   2
#define SEARCHABLE_BOTH     3

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
using namespace std;
#ifdef _msdos_stl
#include <iostream>
#include <list>
#include <map>
pragma warning(disable:4786)
#endif


#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"
#include "ObjectsType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
bool operator==(const Identify& x, const Identify& y);
bool operator<(const Identify& x, const Identify& y);
ostream& operator<<(ostream& out, const Identify& id);
bool Encode(CommBuffer& buffer, Identify& id);
bool Decode(CommBuffer& buffer, Identify& id);

template <class T>
ObjectList<T> operator+(ObjectList<T>& olist1,
			ObjectList<T>& olist2);
template <class T>
bool operator==(const ObjectList<T>& olist1, 
		const ObjectList<T>& olist2);
template <class T>
bool operator<(const ObjectList<T>& olist1, 
	       const ObjectList<T>& olist2);
template <class T>
ostream& operator<<(ostream& out, 
		    const ObjectList<T>& llist);
template <class T>
bool Encode(CommBuffer& buffer, ObjectList<T>& id);
template <class T>
bool Decode(CommBuffer& buffer, ObjectList<T>& id);

bool TopDecode(CommBuffer& buffer, Identify*& id);
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "Objects.icc"
#include "SearchableObjects.icc"
#include "Identify.icc"
#ifdef TEMPLATE_INSTANTIATION
#include "Objects.itc"
#endif
#endif


