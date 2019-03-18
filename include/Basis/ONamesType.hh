/*  FILE     ONamesType.hh
**  PACKAGE  ONames
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "ONames" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef BASIS_ONAMESTYPE_HH
#define BASIS_ONAMESTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C NameIDCorrespondences . . . . . . . . . . . . . . . . . . . id given name
**
**  DESCRIPTION
**      This associates a name with an ID.  This is used for lists
**      in which the reference is by an integer ID, but it is
**      more 'natural' to access it by name.
**
**  REMARKS
**
*/
class NameIDCorrespondences : public SearchableObjectListSimple<String,int>
{
  
public:
  int IDfromName(const String& name);
  bool IsInList(const String& name);
};
/*C AlternativeNames  . . . . . . . . . . . . . . .  set of alternative names
**
**  DESCRIPTION
**    This lists a set of alternative names given by category.  Each 
**    alternative has a category associated with it (i.e. a class of 
**    names) and is references so.
**
**  REMARKS
**
*/
class AlternativeNames : public SearchableObjectListSimple<String,String>
{
public:
  AlternativeNames();
  AlternativeNames(const AlternativeNames& alt);
  String GetAlternativeName(const String& category);
  bool IsInList(const String& name)
    {
      SearchableObjectListSimple<String,String>::iterator ele = find(name);
      if(ele == end())
        return false;
      else 
        return true;
    }
};

 
/*C ObjectStringClasses . . . . . . . . . . . . . . . . . . . . . class names
**
**  DESCRIPTION
**     A particular object can belong to several classes.  Here the
**     classes are represented by string names.
**
**  REMARKS
**
*/
class ObjectStringClasses : public ObjectList<String>
{
public:
     
  ObjectStringClasses();
  ObjectStringClasses(const ObjectStringClasses& sclass);
  bool IsMemberOfClass(const String& classname);
};

#endif
