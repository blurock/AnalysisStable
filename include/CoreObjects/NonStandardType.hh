/*  FILE     NonStandardType.hh
**  PACKAGE  NonStandard
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "NonStandard" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_NONSTANDARDTYPE_HH
#define CoreObjects_NONSTANDARDTYPE_HH

/*C ObjectNameClassPairs 
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class ObjectNameClassPairs : public SymmetricPairList<String>
{
  String ClassEndDelimitor;
  
public:
  ObjectList<String> ClassNames;
  ObjectList<String> ObjectNames;
  
  ObjectNameClassPairs();
  ObjectNameClassPairs(const ObjectNameClassPairs& set);
  bool AddObject(const String& objname, const String& objclass);
  bool Read(istream& in);
  ostream& print(ostream& out) const;
  bool EncodeThis(CommBuffer& buffer);
  bool DecodeThis(CommBuffer& buffer);
  void WriteAsASCII(ostream& out);
  bool XMLWrite(ostream& out);
  bool XMLRead(istream& in);
};

class SearchableListOfMixedObjectsIdentify : public SearchableListOfMixedObjects<Identify,Identify> 
{
};
class SearchableObjectListSimpleStringdouble : public SearchableObjectListSimple<String,double>
{
};

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
