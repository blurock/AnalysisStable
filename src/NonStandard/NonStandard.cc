/*  FILE     NonStandard.cc
**  PACKAGE  NonStandard
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "NonStandard" package.
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
#include "CommBuffer.hh"
#include "String.hh"
#include "MixedClasses.hh"
#include "Objects.hh"
#include "Pairs.hh"
#include "NonStandard.hh"

String DefaultEndDelimitor("END");
String NoStructure("NoStructure");


/*S ObjectNameClassPairs
 */ 
/*F ObjectNameClassPairs()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ObjectNameClassPairs::ObjectNameClassPairs()
  : ClassEndDelimitor(DefaultEndDelimitor)
{
  ObjectNames.ChangeTitle("Set Of Object Names\n");
  ClassNames.ChangeTitle("Set Of Object Classes\n");
}
 
/*F ObjectNameClassPairs(set) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    set: The set of pairs
**
**  REMARKS
**
*/
ObjectNameClassPairs::ObjectNameClassPairs(const ObjectNameClassPairs& set)
  : SymmetricPairList<String>(set),
    ClassEndDelimitor(set.ClassEndDelimitor),
    ClassNames(set.ClassNames),
    ObjectNames(set.ObjectNames)
{
  ChangeTitle("Set of Name and Class Pairs\n");
}
 
/*F ans = AddObject(objname,objclass) Add to set
**
**  DESCRIPTION
**    objname: The object name
**    objclass: The corresponding class
**    ans: true if successful (for example, the name is unique)
**
**  REMARKS
**
*/
bool ObjectNameClassPairs::AddObject(const String& objname, const String& objclass)
{
  bool result = true;
  
  ObjectNames.AddObjectIfNotThere(objname);

  ClassNames.AddObjectIfNotThere(objclass);
  SymmetricPair<String> p(objname,objclass);
  SymmetricPairList<String>::AddObject(p);

  return result;
}
 
/*F ans = Read(in)  . . . . . . . . . . . . . read in set of name class pairs
**
**  DESCRIPTION
**    in: The input buffer
**    ans: True if successful
**
**    The pairs are read, one pair to a line, until the 
**    end delimitor is reached.
**
**  REMARKS
**
*/
bool ObjectNameClassPairs::Read(istream& in)
{
  bool result = true;
  String line;
  StreamObjectInput file(in,' ');
  String name = file.ReadNext();
  while(name != ClassEndDelimitor && result)
    {
      String objc = file.ReadNext();
      result = result && AddObject(name,objc);
      if(!result)
        {
          cerr << "Failure in Reading and adding class pairs\n";
          cerr << name << "," << objc << "\n";
	  print(cerr);
	  cerr << endl;
        }
      name = file.ReadNext();
    }
  return result;
} 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  ObjectNameClassPairs
**
**  DESCRIPTION
**    out: The output stream
**    out1: The output stream
**
**  REMARKS
**
*/
ostream& ObjectNameClassPairs::print(ostream& out) const
{
  SymmetricPairList<String>::const_iterator p;
  for(p=begin();p!=end();p++)
    {
      out << (*p).I << "     " << (*p).J << endl;
    }
  
  return out;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  ObjectNameClassPairs
**
**  DESCRIPTION
**    buffer: The encode buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool ObjectNameClassPairs::EncodeThis(CommBuffer& buffer)
{
  bool result = SymmetricPairList<String>::EncodeThis(buffer);
  result = result && Encode(buffer,ClassEndDelimitor);
  result = result && ClassNames.EncodeThis(buffer);
  result = result && ObjectNames.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  ObjectNameClassPairs
**
**  DESCRIPTION
**    buffer: The decode buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool ObjectNameClassPairs::DecodeThis(CommBuffer& buffer)
{
  bool result = SymmetricPairList<String>::DecodeThis(buffer);
  result = result && Decode(buffer,ClassEndDelimitor);
  result = result && ClassNames.DecodeThis(buffer);
  result = result && ObjectNames.DecodeThis(buffer);
  return result;
}
/*F WriteAsASCII(out) . . . . . . . . . . . . . . . . .  NameClassPairs
**
**  DESCRIPTION
**    out: The output stream
**
**  REMARKS
**
*/
void ObjectNameClassPairs::WriteAsASCII(ostream& out)
{
  out << "ClassNamePairs:" << endl;
  SymmetricPairList<String>::iterator p;
  for(p=begin();p!=end();p++)
    {
      out << (*p).I << "     " << (*p).J << endl;
    }
  out << "END" << endl;
}
/*S XML
 */
/*F ans = XMLRead(in)  . . . . . . . . . . . . . read in set of name class pairs
**
**  DESCRIPTION
**    in: The input buffer
**    ans: True if successful
**
**    The pairs are read, one pair to a line, until the 
**    end delimitor is reached.
**
**  REMARKS
**
*/
bool ObjectNameClassPairs::XMLRead(istream& in)
{
  bool result = XMLReadBegin(in,(char *) "ObjectNameClassPairs");
  String line;
  StreamObjectInput file(in,' ');
  String nameA,nameB;
  result = result && nameA.XMLRead(in);
  while(result)
    {
      result = result && nameB.XMLRead(in);
      result = result && AddObject(nameA,nameB);
      if(!result)
        {
          cerr << "Failure in Reading and adding class pairs\n";
          cerr << nameA << "," << nameB << "\n";
	  print(cerr);
	  cerr << endl;
        }
      result = result && nameA.XMLRead(in);
    }
  if(!(nameA == "ObjectNameClassPairs"))
    result = false;
  //result = result && XMLReadEnd(in);
  return result;
} 

/*F XMLWrite(out) . . . . . . . . . . . . . . . . .  NameClassPairs
**
**  DESCRIPTION
**    out: The output stream
**
**  REMARKS
**
*/
bool ObjectNameClassPairs::XMLWrite(ostream& out)
{
  out << endl;
  bool result = XMLWriteBegin(out,"ObjectNameClassPairs");
  SymmetricPairList<String>::iterator p;
  for(p=begin();p!=end();p++)
    {
      (*p).I.XMLWrite(out);
      (*p).J.XMLWrite(out);
      out << endl;
    }
  result = result && XMLWriteBegin(out,"ObjectNameClassPairs");
  out << endl;
  return result;
}
