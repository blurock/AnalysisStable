/*  FILE     Identify.cc
**  PACKAGE     REACTION    
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  REACTION Project / Edward S. Blurock 
*/
#include <iostream>
using namespace std;
#include "platform.hh"
#include "CommBuffer.hh"

#include "String.hh"
#define TEMPLATE_INSTANTIATION
#include "Objects.hh"

#ifdef _unix
template class list<String>;
template class list<double>;
template class SearchableObjectList<String, int>;
template class SearchableObjectList<String, double>;
template class list<Identify>;

template class SearchableObjectListSimple<String, int>;
template bool Encode(CommBuffer &, ObjectList<Identify> &);
template bool Decode(CommBuffer &, ObjectList<Identify> &);
#endif

/*S EncodeDecode
*/
/*F ans = Encode(buffer,id) . . . . . . . . . . . . . . . . . . . .  Identify
**
**  DESCRIPTION
**    buffer: the buffer (to be written)
**    id: The class to be written
**    ans: true if successful 
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, Identify& id)
{
  return id.EncodeThis(buffer);
}
/*F ans = Decode(buffer,id) . . . . . . . . . . . . . . . . . . . .  Identify
**
**  DESCRIPTION
**    buffer: the buffer (to be read)
**    id: The class to be built
**    ans: true if successful 
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, Identify& id)
{
  return id.DecodeThis(buffer);
}
 
/*F ans = TopDecode(buffer,iden)  . . . . . . . . . . . . . . . . .  Identify
**
**  DESCRIPTION
**    buffer: the buffer (to be read)
**    iden: The class to be built from scratch
**    ans: true if successful 
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, Identify*& iden)
{
  return iden->DecodeThis(buffer);
}
/*S IO
*/ 
/*F out1 = operator<<(out,id)  . . . . . . . . . . . . . . . . . . .  Identify
**
**  DESCRIPTION
**    out,out1: The output stream
**    id: The class to be outputted
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const Identify& id)
{
  return id.print(out);
}
/*S Boolean
*/ 
/*F ans = operator==(x,y) . . . . . . . . . . . . . . . . . . . . .  Identify
**
**  DESCRIPTION
**    x,y: to be compared
**    ans: true if equal
**
**    Equality if both the name and the Identification are equal
**
**  REMARKS
**
*/
bool 
operator==(const Identify& x, const Identify& y)
{
  return (x.Identification == y.Identification) &&
    !strcmp(x.NameTag.c_str(),y.NameTag.c_str());
}
/*F ans = operator<(x,y)  . . . . . . . . . . . . . . . . . . . . .  Identify
**
**  DESCRIPTION
**    x,y: to be compared
**    ans: true if x less than y
**
**    The Identifications are compared, if equal then the NameTag is compared
**
**  REMARKS
**
*/
bool operator<(const Identify& x, const Identify& y)
{
  if(x.Identification != y.Identification)
    return x.Identification < y.Identification;
  else
    return x.NameTag < y.NameTag;
}


