/*  FILE     ONames.hh
**  PACKAGE  ONames
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "ONames" package in the Basis environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef Basis_ONAMES_HH
#define Basis_ONAMES_HH
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "ONamesType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
ostream& operator<<(ostream& out, const AlternativeNames& names);
ostream& operator<<(ostream& out, const ObjectStringClasses& names);
bool Encode(CommBuffer& buffer, AlternativeNames& names);
bool Encode(CommBuffer& buffer, ObjectStringClasses& names);
bool Decode(CommBuffer& buffer, AlternativeNames& names);
bool Decode(CommBuffer& buffer, ObjectStringClasses& names);

void InitializeONamesPropertyFunctions(StringPropertyFunctions& PropertyFunctions);
void InitONameForPropertyList(PropertyListByName* plist);
int AlternativeNamesFromLine(PropertyListByName* plist,
			     String line);
int ObjectStringClassesFromLine(PropertyListByName* plist,
			     String line);
String GetAlternativeName(const String& category,
			  PropertyListByName& plist);
bool IsMemberOfClass(const String& classname, 
		     PropertyListByName& plist);

bool TopDecode(CommBuffer &, PropertyTypeByName<AlternativeNames> *&); 
bool TopDecode(CommBuffer & buffer, PropertyTypeByName<ObjectStringClasses> *& prop);

void InitializeONamePropertyDecodeFunctions();
#endif
