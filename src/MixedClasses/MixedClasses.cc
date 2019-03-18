/*  FILE     MixedClasses
**  PACKAGE     REACTION    
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  REACTION Project / Edward S. Blurock 
**
**  Version: March 16,1998
*/
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include <iostream>
using namespace std;

#define TEMPLATE_INSTANTIATION
#include "defines.hh"
#include "CommBuffer.hh"
#include "String.hh"
class SingleDecodeRoutine;
ostream& operator<<(ostream& out,const SingleDecodeRoutine& decode);

#include "Objects.hh"
#include "MixedClasses.hh"

template bool TopDecode(CommBuffer& buffer, PropertyType<int>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyType<double>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyType<String>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyTypeByName<int>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyTypeByName<double>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyTypeByName<String>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyTypeByID<int>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyTypeByID<double>*& id);
template bool TopDecode(CommBuffer& buffer, PropertyTypeByID<String>*& id);

#ifdef _unix
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
 */
template class PropertyTypeByID<int>;
template class PropertyTypeByID<double>;
template class PropertyTypeByID<String>;
//template class PntrMixed<int,Identify>;
template class SearchableObjectList<int, PntrMixed<int, Identify> >;

template class PntrMixed<Identify,Identify>;
template class SearchableObjectListFull<Identify, PntrMixed<Identify, Identify> >;
#endif

/*S Initialize
 */

/*F MixedClassesInit()  . . . . . . . . . . . . . . . .  Class Initialization
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
// whchange
extern void MixedClassesInit()
{
  InitialSetOfMixedEncodeDecodeRoutines(SetOfEncodeDecodeRoutines);
}
/*F InitialSetOfMixedEncodeDecodeRoutines(SetOfEncodeDecodeRoutines) . . . .  init
**
**  DESCRIPTION
**    SetOfEncodeDecodeRoutines: The routines
**
**  REMARKS
**
*/
extern void 
InitialSetOfMixedEncodeDecodeRoutines(SearchableObjectList<String,SingleDecodeRoutine> 
                                      *SetOfEncodeDecodeRoutines)
{
  bool (*toproutine)(CommBuffer&,Identify*&);

  bool (*rout1)(CommBuffer&,PropertyType<int>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
  SingleDecodeRoutine p1("ByIdentify-Integer", toproutine);
  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
     
  bool (*rout2)(CommBuffer&,PropertyType<double>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
  SingleDecodeRoutine p2("ByIdentify-Float",toproutine);
  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
     
  bool (*rout3)(CommBuffer&,PropertyType<String>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
  SingleDecodeRoutine p3("ByIdentify-String",toproutine);
  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
     
  bool (*rout4)(CommBuffer&,PropertyTypeByName<int>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout4;
  SingleDecodeRoutine p4("ByName-Integer",toproutine);
  (*SetOfEncodeDecodeRoutines)[p4.StructureName] = p4;
     
  bool (*rout5)(CommBuffer&,PropertyTypeByName<double>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout5;
  SingleDecodeRoutine p5("ByName-Float",toproutine);
  (*SetOfEncodeDecodeRoutines)[p5.StructureName] = p5;
     
  bool (*rout6)(CommBuffer&,PropertyTypeByName<String>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout6;
  SingleDecodeRoutine p6("ByName-String",toproutine);
  (*SetOfEncodeDecodeRoutines)[p6.StructureName] = p6;

  bool (*rout7)(CommBuffer&,PropertyTypeByID<int>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout7;
  SingleDecodeRoutine p7("ByID-Integer",toproutine);
  (*SetOfEncodeDecodeRoutines)[p7.StructureName] = p7;
   
  bool (*rout8)(CommBuffer&,PropertyTypeByID<double>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout8;
  SingleDecodeRoutine p8("ByID-Float",toproutine);
  (*SetOfEncodeDecodeRoutines)[p8.StructureName] = p8;
     
  bool (*rout9)(CommBuffer&,PropertyTypeByID<String>*&) = TopDecode;
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout9;
  SingleDecodeRoutine p9("ByID-String",toproutine);
  (*SetOfEncodeDecodeRoutines)[p9.StructureName] = p9;
}


/*S IO
 */
/*F out = operator<<(out,p) . . . . . . . . . . . . . Pntr<Identify,Identify>
**
**  DESCRIPTION
**    out: The output stream
**    p: The object
**
**  REMARKS
**
ostream& operator<<(ostream& out,
                    const PntrMixed<int,Identify>& p)
{
  return p.print(out);
}
*/
/*F out = operator<<(out,decode)  . . . . . . . . . dummy SingleDecodeRoutine
**
**  DESCRIPTION
**    decode: The decode routine structure
**    out: The stream
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out,const SingleDecodeRoutine& decode)
{
  cout << "Structure Name:" << decode.StructureName << "\n";
  return out;
}
/* EncodeDecode
 */
/*F ans = Decode(buffer,decode) . . . . . . . . . . dummy SingleDecodeRoutine
**
**  DESCRIPTION
**    buffer: The buffer
**    decode: The structure
**    ans: always true
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer,SingleDecodeRoutine& decode)
{
  Decode(buffer,decode.StructureName);
  return true;
}
/*F ans = Encode(buffer,decode) . . . . . . . . . . dummy SingleDecodeRoutine
**
**  DESCRIPTION
**    buffer: The buffer
**    decode: The structure
**    ans: always true
**    
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer,SingleDecodeRoutine& decode)
{
  Encode(buffer,decode.StructureName);
  return true;
}


/*F ans = Decode(buffer,prop) . . . . . . . . . .  dummy PropertyListByName
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The property list
**    ans: always true
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer,PropertyListByName& prop)
{
  return prop.DecodeThis(buffer);
}
/*F ans = Encode(buffer,prop) . . . . . . . . . .  dummy PropertyListByName
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The property list
**    ans: always true
**    
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer,PropertyListByName& prop)
{
  return prop.EncodeThis(buffer);
}

/*F ans = Decode(buffer,prop) . . . . . . . . . .  dummy PropertyListByIdentify
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The property list
**    ans: always true
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer,PropertyListByIdentify& prop)
{
  return prop.DecodeThis(buffer);
}
/*F ans = Encode(buffer,prop) . . . . . . . . . .  dummy PropertyListByIdentify
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The property list
**    ans: always true
**    
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer,PropertyListByIdentify& prop)
{
  return prop.EncodeThis(buffer);
}

/*F ans = Decode(buffer,prop) . . . . . . . . . .  dummy PropertyListByID
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The property list
**    ans: always true
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer,PropertyListByID& prop)
{
  return prop.DecodeThis(buffer);
}
/*F ans = Encode(buffer,prop) . . . . . . . . . .  dummy PropertyListByID
**
**  DESCRIPTION
**    buffer: The buffer
**    prop: The property list
**    ans: always true
**    
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer,PropertyListByID& prop)
{
  return prop.EncodeThis(buffer);
}
