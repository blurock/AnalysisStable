/*  FILE     BasisSystem.hh
**  PACKAGE  BasisSystem
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "BasisSystem" package in the Basis environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef Basis_BASISSYSTEM_HH
#define Basis_BASISSYSTEM_HH
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "platform.hh"
#ifdef _msdos_stl
#include <algorithm>
// #include "relation.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
using namespace std;
#pragma warning(disable:4786)
#endif


#ifdef _unix
/*
#include <defalloc.h>
#include <algo.h>
#include <function.h>
#include <iterator.h>
#include <list.h>
#include <deque.h>
#include <map.h>
#include <pair.h>
#include <set.h>
#include <stack.h>
#include <vector.h>
#include <iostream.h>
#include <strstream.h>
#include <iostream.h>
#include <fstream.h>
*/
#include "STL.h"
#endif


#include "defines.hh"
#include "CommBuffer.hh"
#include "String.hh"
class SingleDecodeRoutine;
ostream& operator<<(ostream& out,const SingleDecodeRoutine& decode);
#include "Objects.hh"
#include "MixedClasses.hh"

#define HOME_NAME     "HOME"
#define DATAHOME_NAME "DATAHOME"

#ifndef CODEBASEROOT
#define CODEBASEROOT "."
#endif

#ifndef CODEBASEROOT_DATA
#define CODEBASEROOT_DATA "."
#endif

#ifndef CODEBASEROOT_DATABASE
#define CODEBASEROOT_DATABASE "."
#endif

#include "BasisSystemType.hh"

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
template <class Object>
bool Encode(CommBuffer& buffer, vector<Object>& vec);
template <class Object>
bool Decode(CommBuffer& buffer, vector<Object>& vec);


//ostream& operator<<(ostream& out, const StringPryopertyFunction& sys);
ostream& operator<<(ostream& out, const SystemCommands&);
//ostream& operator<<(ostream& out, const SingleSystemCommand& sys);




bool Encode(CommBuffer& buffer, SingleCommandBase& command);     
bool Decode(CommBuffer& buffer, SingleCommandBase& command);
template <class CommandType>
ostream& operator<<(ostream& out, 
		    const ListOfCommandsBase<CommandType>& commands);

String& ReadHomeDirectory();
String& ReadDataDirectory();
String& GetEnvironmentVariable(const String& name);

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#ifdef TEMPLATE_INSTANTIATION
#include "BasisSystem.itc"
#endif

#endif

