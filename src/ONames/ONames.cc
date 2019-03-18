/*  FILE     ONames.cc
**  PACKAGE  ONames
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "ONames" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "BasisSystem.hh"
#include "ONames.hh"

/*S Initialization
*/ 
/*F InitONameForPropertyList(plist) . . . . . . . . . . .  init for insertion
**
**  DESCRIPTION
**    plist: The property list
**
**    Since Alternative names and String classes are expandable lists
**    (i.e new elements are added), it should be initialized in the list 
**    of properties at the creation of the list of properties.	
**
**    This routine initialises the classes 'AlternativeNames' and 'ObjectStringClasses' 
**    in the property list 'plist'.
**
**  REMARKS
**
*/
void InitONameForPropertyList(PropertyListByName* plist)
{
  AlternativeNames names;
  PropertyTypeByName<AlternativeNames> *prop1
    = new PropertyTypeByName<AlternativeNames>("AlternativeNames",names);
  plist->AddObject(prop1,"AlternativeNames");
  
  ObjectStringClasses classnames;
  PropertyTypeByName<ObjectStringClasses> *prop2
    = new PropertyTypeByName<ObjectStringClasses>("ObjectStringClasses",classnames);
  plist->AddObject(prop2,"ObjectStringClasses");
}
/*F ans = AlternativeNamesFromLine(plist,line)	. . . . read alternative name
**
**  DESCRIPTION
**    plist: The current list of molecular properties
**    line: The input line
**    ans: 0 if successful
**
**    The line has two items: 
**    - Type: The type of the name
**    - The name of this type
**    
**  REMARKS
**
*/
int AlternativeNamesFromLine(PropertyListByName* plist,
			     String line)
{
  String nametype;
  String altname;
     
  line.IsolateNextWord(nametype,' ');
  nametype.EliminateBlanks();
     
  line.IsolateNextWord(altname,' ');
  altname.EliminateBlanks();
     
  PropertyTypeByName<AlternativeNames> *orig
    = (PropertyTypeByName<AlternativeNames> *)
    plist->GetPointerToProperty("AlternativeNames");
     
  bool result;
  AlternativeNames names;
  PropertyTypeByName<AlternativeNames> nameprop("AlternativeNames",names);
  (orig->Object)[nametype] = altname;
  PropertyTypeByName<AlternativeNames> *prop
    = new PropertyTypeByName<AlternativeNames>("AlternativeNames",orig->Object);
  result = plist->AddObject(prop,"AlternativeNames");

  int ret;     
  if(result)
    ret = 0;
  else
    ret = 1;
  return ret;
}

/*F InitializeONamesPropertyFunctions(PropertyFunctions)  . .  read functions
**
**  DESCRIPTION
**    PropertyFunctions: The property functions
**
**    For the 'StringPropertyFunctions', this routine initialises the
**    the following routines:
**    - AlternativeNamesFromLines
**    - ObjectStringClassesFromLine
**
**  REMARKS
**
*/
void InitializeONamesPropertyFunctions(StringPropertyFunctions& PropertyFunctions)
{
  /*
  String al("AlternativeNames");
  String st("ObjectStringClasses");
  StringPropertyFunction alternative(al,
				     "Alternative names read from a line",
				     &AlternativeNamesFromLine);
  PropertyFunctions.AddObject(al,alternative);

  StringPropertyFunction stringclass(st,
				     "Class names are read from a line",
				     &ObjectStringClassesFromLine);
  PropertyFunctions.AddObject(st,stringclass);
  */
}
/*F InitializeONamePropertyDecodeFunctions()  . . . . String Class Properties
**
**  DESCRIPTION
**    This initialises the property decode functions in SetOfEncodeDecodeRoutines for:
**    - AlternativeNames
**    - ObjectStringClasses
** 
**  REMARKS
**
*/
void InitializeONamePropertyDecodeFunctions()
{
  bool (*toproutine)(CommBuffer&,Identify*&);

  bool (*rout1)(CommBuffer&,PropertyTypeByName<AlternativeNames>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
  SingleDecodeRoutine p1("AlternativeNames",toproutine);
  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;

  bool (*rout2)(CommBuffer&,PropertyTypeByName<ObjectStringClasses>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
  SingleDecodeRoutine p2("ObjectStringClasses",toproutine);
  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
}
 
/*S EncodeDecode
 */
/*F TopDecode(buffer,prop)  . . . . . .	 PropertyTypeByName<AlternativeNames>
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The structure
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer & buffer, PropertyTypeByName<AlternativeNames> *& prop)
{
  AlternativeNames names;
  prop = new PropertyTypeByName<AlternativeNames>("AlternativeNames",names);
  return prop->DecodeThis(buffer);
}
/*F TopDecode(buffer,prop)  . . . . . PropertyTypeByName<ObjectStringClasses>
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The structure
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer & buffer, PropertyTypeByName<ObjectStringClasses> *& prop)
{
  ObjectStringClasses names;
  prop = new PropertyTypeByName<ObjectStringClasses>("ObjectStringClasses",names);
  return prop->DecodeThis(buffer);
}

 
/*F ans = Encode(buffer,names)	. . . . . . . . . . . . .  AlternativeNames
**
**  DESCRIPTION
**    buffer: The buffer
**    names: The structure
**    ans: True if successful
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, AlternativeNames& names)
{
  return names.EncodeThis(buffer);
}
/*F ans = Decode(buffer,names)	. . . . . . . . . . . . . .  AlternativeNames
**
**  DESCRIPTION
**    buffer: The buffer
**    names: The structure
**    ans: True if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, AlternativeNames& names)
{
  return names.DecodeThis(buffer);
}
/*F ans = Encode(buffer,names)	. . . . . . . . . . . . . ObjectStringClasses
**
**  DESCRIPTION
**    buffer: The buffer
**    names: The structure
**    ans: True if successful
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, ObjectStringClasses& names)
{
  return names.EncodeThis(buffer);
}
/*F ans = Decode(buffer,names)	. . . . . . . . . . . . . ObjectStringClasses
**
**  DESCRIPTION
**    buffer: The buffer
**    names: The structure
**    ans: True if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, ObjectStringClasses& names)
{
  return names.DecodeThis(buffer);
}
/*S IO
 */
/*F nout = operator<<(out,names)  . . . . . . . . . . . . ObjectStringClasses
**
**  DESCRIPTION
**    out: The output stream
**    names: The structure
**    nout: The resulting stream
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const ObjectStringClasses& names)
{
  return names.print(out);
}
/*F nout = operator<<(out,names)  . . . . . . . . . . . . .  AlternativeNames
**
**  DESCRIPTION
**    out: The output stream
**    names: The structure
**    nout: The resulting stream
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const AlternativeNames& names)
{
  return names.print(out);
}
/*S Constructors
*/
 
/*F AlternativeNames()	. . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
AlternativeNames::AlternativeNames()
{
}
 
/*F AlternativeNames(alt) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    alt: The set of names
**
**  REMARKS
**
*/
AlternativeNames::AlternativeNames(const AlternativeNames& alt)
  : SearchableObjectListSimple<String,String>(alt)
{
}
/*S Utility
*/ 
/*F name = GetAlternativeName(category) . . . . . . . .	 get alternative name
**
**  DESCRIPTION
**    category: The catagory of the alternative name
**    name: The alternative name
**
**    The category describes the type of alternative name
**
**  REMARKS
**
*/
String AlternativeNames::GetAlternativeName(const String& category)
{
  return (*this)[category];
}
/*F name = GetAlternativeName(category,plist) . . . . .	 get alternative name
**
**  DESCRIPTION
**    category: The catagory of the alternative name
**    plist: The property list
**    name: The alternative name
**
**    The category describes the type of alternative name
**
**  REMARKS
**
*/
String GetAlternativeName(const String& category,
			  PropertyListByName& plist)
{
  PropertyTypeByName<AlternativeNames> *prop
    = (PropertyTypeByName<AlternativeNames> *)
    plist.GetPointerToProperty("AlternativeNames");
  return (prop->Object)[category];
}
 
     
/*F ans = IsMemberOfClass(classname)  . . . . . . . . . . . . .	 is of class?
**
**  DESCRIPTION
**    classname: The name of the class
**    ans: true if the object is a member
**
**  REMARKS
**
*/
bool ObjectStringClasses::IsMemberOfClass(const String& classname)
{
  return !(find(begin(),end(),classname) == end());
}
/*F ans = IsMemberOfClass(classname,plist)  . . . . . . . . . .	 is of class?
**
**  DESCRIPTION
**    classname: The name of the class
**    props: Property list
**    ans: true if the object is a member
**
**  REMARKS
**
*/
bool IsMemberOfClass(const String& classname, 
		     PropertyListByName& plist)
{
  PropertyTypeByName<ObjectStringClasses> *prop
    = (PropertyTypeByName<ObjectStringClasses> *)
    plist.GetPointerToProperty("ObjectStringClasses");
  return !(find(prop->Object.begin(),prop->Object.end(),classname) == prop->Object.end());
}
/*F ClassNamesFromLine(plist,line)  . . . . . . . . . . . . . read class name
**
**  DESCRIPTION
**    plist: The current list of molecular properties
**    line: The input line
**
**    The line has two items: 
**    - Type: The type of the name
**    - The name of this type
**    
**  REMARKS
**
*/
int ObjectStringClassesFromLine(PropertyListByName* plist,
				String line)
{
  String classname;
     
  line.IsolateNextWord(classname,' ');
  classname.EliminateBlanks();
     
  PropertyTypeByName<ObjectStringClasses> *orig
    = (PropertyTypeByName<ObjectStringClasses> *)
    plist->GetPointerToProperty("ObjectStringClasses");
     
  bool result;
  ObjectStringClasses names;
  PropertyTypeByName<ObjectStringClasses> nameprop("ObjectStringClasses",names);
  (orig->Object).AddObject(classname);
     
  PropertyTypeByName<ObjectStringClasses> *prop
    = new PropertyTypeByName<ObjectStringClasses>("ObjectStringClasses",orig->Object);
  result = plist->AddObject(prop,"ObjectStringClasses");

  int ret;     
  if(result)
    ret = 0;
  else
    ret = 1;
  return ret;
}
/*F id = IDfromName(name) . . . . . . . . . . . . . . . given name, return id
**
**  DESCRIPTION
**    name: The string name
**    id: The corresponding integer ID
**
**  REMARKS
**
*/
int NameIDCorrespondences::IDfromName(const String& name)
{
  return (*this)[name];
}
/*F ans = IsInList(name)  . . . . . . . . . . . . is there already this name?
**
**  DESCRIPTION
**    name: The string name to check
**    ans: true if in list
**
**  REMARKS
**
*/
bool NameIDCorrespondences::IsInList(const String& name)
{
  SearchableObjectListSimple<String,int>::iterator ele = find(name);
  if(ele == end())
    return false;
  else 
    return true;
}
/*S Constructors
*/
/*F ObjectStringClasses() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ObjectStringClasses::ObjectStringClasses()
{
}
/*F ObjectStringClasses(sclass) . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    sclass: The string class
**
**  REMARKS
**
*/
ObjectStringClasses::ObjectStringClasses(const ObjectStringClasses& sclass)
  : ObjectList<String>(sclass)
{
}
