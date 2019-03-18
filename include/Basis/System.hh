/*  FILE     System.hh
**  PACKAGE  System
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Definitions for the "System" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/
#ifndef REACTION_SYSTEM_HH
#define REACTION_SYSTEM_HH
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
using namespace std;

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

#include "SystemType.hh"
 
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
template <class Object>
bool Encode(CommBuffer& buffer, vector<Object>& vec);
template <class Object>
bool Decode(CommBuffer& buffer, vector<Object>& vec);


ostream& operator<<(ostream& out, const StringPropertyFunction& sys);
ostream& operator<<(ostream& out, const SystemCommands&);


template <class CommandType>
ostream& operator<<(ostream& out, 
		    const ListOfCommandsBase<CommandType>& commands);


bool Encode(CommBuffer& buffer, SingleCommandBase& command);     
bool Decode(CommBuffer& buffer, SingleCommandBase& command);
String& ReadHomeDirectory();
String& ReadDataDirectory();
String& GetEnvironmentVariable(const String& name);


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef TEMPLATE_INSTANTIATION
#include "System.itc"
#endif

#endif

