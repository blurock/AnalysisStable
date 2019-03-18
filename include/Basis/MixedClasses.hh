/*  FILE     MixedClasses.hh
**  PACKAGE  MixedClasses
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Definitions for the "MixedClasses" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/
using namespace std;
 
#ifndef REACTION_MIXEDCLASSES_HH
#define REACTION_MIXEDCLASSES_HH

#ifdef _msdos_stl
#include <iostream>
#include <fstream>
#pragma warning(disable:4786)
#endif


#ifdef _unix
#include "STL.h"
#endif
#include "MixedClassesType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
extern void 
InitialSetOfMixedEncodeDecodeRoutines(SearchableObjectList<String,SingleDecodeRoutine> 
				      *SetOfEncodeDecodeRoutines);
extern SearchableObjectListSimple<String, SingleDecodeRoutine> *SetOfEncodeDecodeRoutines;
SingleDecodeRoutine& GetDecodeRoutineFromSet(const String& name);
void PutDecodeRoutineInSet(const String& name, void *decode);
bool Decode(CommBuffer& buffer,SingleDecodeRoutine& decode);
bool Encode(CommBuffer& buffer,SingleDecodeRoutine& decode);
ostream& operator<<(ostream& out,const SingleDecodeRoutine& decode);

bool Decode(CommBuffer& buffer,SingleDecodeRoutine& decode);
bool Encode(CommBuffer& buffer,SingleDecodeRoutine& decode);

bool Decode(CommBuffer& buffer,PropertyListByName& prop);
bool Encode(CommBuffer& buffer,PropertyListByName& prop);

bool Decode(CommBuffer& buffer,PropertyListByIdentify& prop);
bool Encode(CommBuffer& buffer,PropertyListByIdentify& prop);

bool Decode(CommBuffer& buffer,PropertyListByID& prop);
bool Encode(CommBuffer& buffer,PropertyListByID& prop);

template <class ObjectID, class BaseClass>
bool operator<(const PntrMixed<ObjectID,BaseClass>& x,
	       const PntrMixed<ObjectID,BaseClass>& y);
template <class ObjectID, class BaseClass>
bool operator==(const PntrMixed<ObjectID,BaseClass>& x, 
		const PntrMixed<ObjectID,BaseClass>& y);

template <class T>
bool Encode(CommBuffer& buffer, PropertyType<T>& id);
template <class T>
bool Decode(CommBuffer& buffer, PropertyType<T>& id);
template <class T>
bool Encode(CommBuffer& buffer, PropertyTypeByID<T>& byid);
template <class T>
bool Decode(CommBuffer& buffer, PropertyTypeByID<T>& byid);
template <class T>
bool Encode(CommBuffer& buffer, PropertyTypeByName<T>& byname);
template <class T>
bool Decode(CommBuffer& buffer, PropertyTypeByName<T>& byname);
template <class T>
bool TopDecode(CommBuffer& buffer, PropertyType<T>*& id);
template <class T>
bool TopDecode(CommBuffer& buffer, PropertyTypeByID<T>*& byid);
template <class T>
bool TopDecode(CommBuffer& buffer, PropertyTypeByName<T>*& byname);
ostream& operator<<(ostream& out,const SingleDecodeRoutine& decode);
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "MixedClasses.icc"
#ifdef TEMPLATE_INSTANTIATION
#include "MixedClasses.itc"
#include "MixedEncodeDecode.itc"
#endif
#endif
