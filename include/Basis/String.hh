/*  FILE     String.hh
**  PACKAGE  String
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Definitions for the "String" package.
**
**  OVERVIEW
**    Class String is designed to provide  basic operations,
**    connected to strings I/O, their transformation and 
**    manipulation. Names of routines represent their functionality. 
**
**  IMPLEMENTATION
**    implementation remarks
**    
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/
#ifndef CLASS_STRING_H
#define CLASS_STRING_H
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
using namespace std;
#ifdef _msdos_stl
#include <vector>
#include <algorithm>
#include <iostream>
#include <strstream>
#include <fstream>
#include <string>
#pragma warning(disable:4786)
#endif

#ifdef _unix
#include "STL.h"
#endif

#include <math.h>
#include <stdlib.h>
#include "defines.hh"
//#include "mstring.hh"
#include "StringType.hh"


 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

bool Encode(CommBuffer& buffer, String& string);
bool Decode(CommBuffer& buffer, String& string);
//bool operator==(const String& s1, const String& s2);
ostream& operator<<(ostream& out, const String& str);

String Float2String(double num);
String Int2String(int num);
String PositveIntegerToString(unsigned int c, const String& prefix, unsigned int places);
String& FillStringToLength(const unsigned int length, const String& original);
ostream& RepeatOutNTimes(ostream& out, char c, int n);
ostream& OutputStringInWidth(ostream& out,const unsigned int w,const String& str);
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "String.icc"
#ifdef TEMPLATE_INSTANTIATION
// Exported
#endif
#endif




