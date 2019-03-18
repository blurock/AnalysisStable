/*  FILE     EquivalentClasses.cc
**  PACKAGE  EquivalentClasses
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "EquivalentClasses" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "NumericOperations.hh"
#include "MenuObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"
#include "DescriptionProbs.hh"
#include "EquivalentClasses.hh"
/*S BaseDataDegreeOfEquivalence
 */ 
/*F BaseDataDegreeOfEquivalence()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDegreeOfEquivalence::BaseDataDegreeOfEquivalence()
{
  Identification = EQUIVALENTSETS_DEGREE_ID;
  NameTag = EQUIVALENTSETS_DEGREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDegreeOfEquivalence(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDegreeOfEquivalence::BaseDataDegreeOfEquivalence(const BaseDataDegreeOfEquivalence& data)
  : BaseDataObject(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDegreeOfEquivalence::print(ostream& out) const
{
  BaseDataObject::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDegreeOfEquivalence::Clone()
{
  BaseDataDegreeOfEquivalence *obj = new BaseDataDegreeOfEquivalence(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDegreeOfEquivalence::CopyClone(Identify * obj)
{
  BaseDataDegreeOfEquivalence *objfull = (BaseDataDegreeOfEquivalence *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  // The rest

  return result;
}
/*F ans = Equivalence(degree)
**
**  DESCRIPTION
**    degree:  The value to compare with
      ans:     True if equivalent
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence:: Equivalent(BaseDataDegreeOfEquivalence *degree, BaseDataObject *obj)
{
  return true;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << NameTag << endl;
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  return true;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalence::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << " " << NameTag << " "; 
  return true;
}

/*S DataDegreeOfEquivalenceClass
 */
/*F DataDegreeOfEquivalenceClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDegreeOfEquivalenceClass::DataDegreeOfEquivalenceClass()
{
  Identification = EQUIVALENTSETS_DEGREE_ID;
  NameTag = EQUIVALENTSETS_DEGREE_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataDegreeOfEquivalenceClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDegreeOfEquivalenceClass::DataDegreeOfEquivalenceClass(const DataDegreeOfEquivalenceClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataDegreeOfEquivalenceClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataDegreeOfEquivalenceClass::DataDegreeOfEquivalenceClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = "Object";
  EncodeDecodeClass = "DegreeOfEquivalence";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDegreeOfEquivalenceClass::print(ostream& out) const
{
  DataObjectClass::print(out);
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDegreeOfEquivalenceClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDegreeOfEquivalenceClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDegreeOfEquivalenceClass::CopyClone(Identify *  objc)
{
  DataDegreeOfEquivalenceClass *objcfull = (DataDegreeOfEquivalenceClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDegreeOfEquivalenceClass::Clone()
    {
      DataDegreeOfEquivalenceClass* id = new DataDegreeOfEquivalenceClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDegreeOfEquivalenceClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDegreeOfEquivalenceClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) Class);
  //result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataDegreeOfEquivalenceClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataDegreeOfEquivalence();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDegreeOfEquivalenceClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDegreeOfEquivalenceClass*& obj)
     {
     obj = new DataDegreeOfEquivalenceClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDegreeOfEquivalence
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDegreeOfEquivalence*& obj)
     {
     obj = new BaseDataDegreeOfEquivalence;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataDegreeOfEquivalenceNumeric
 */ 
/*F BaseDataDegreeOfEquivalenceNumeric()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDegreeOfEquivalenceNumeric::BaseDataDegreeOfEquivalenceNumeric()
  : Values(NULL)
{
  Identification = EQUIVALENTSETS_NUMDEGREE_ID;
  NameTag = EQUIVALENTSETS_NUMDEGREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDegreeOfEquivalenceNumeric(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDegreeOfEquivalenceNumeric::BaseDataDegreeOfEquivalenceNumeric(const BaseDataDegreeOfEquivalenceNumeric& data)
  : BaseDataDegreeOfEquivalence(data)
{
  Values = (BaseDataInstanceDoubleVector *) PointerClone(data.Values);
}
/*F BaseDataDegreeOfEquivalenceNumeric(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDegreeOfEquivalenceNumeric::BaseDataDegreeOfEquivalenceNumeric(BaseDataInstanceDoubleVector *values)
{
  Identification = EQUIVALENTSETS_NUMDEGREE_ID;
  NameTag = EQUIVALENTSETS_NUMDEGREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  NameTag = values->NameTag;
  Values = (BaseDataInstanceDoubleVector *) PointerClone(values);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataDegreeOfEquivalence::Read(in,objc,name);
  DataDegreeOfEquivalenceNumericClass *objcfull = (DataDegreeOfEquivalenceNumericClass *) objc;
  StreamObjectInput str(in,' ');
  String dummy = str.ReadNext();
  if(dummy == "Values:") { 
    String mess1("Equivalence Values Not Defined");
    PointerObjectRead(in,(BaseDataObject *&) Values,objcfull->getValuesClass(),mess1);
  } else if(!(dummy == "NoValues")) {
    cerr << "In reading DegreeOfEquivalenceNumeric, Expected: 'Values:' or 'NoValues', but got '" << dummy << "'" << endl;
    result = false;
  }
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDegreeOfEquivalenceNumeric::print(ostream& out) const
{
  BaseDataDegreeOfEquivalence::print(out);
  PointerPrint(out,"Equivalence Values: ","No Values",Values);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDegreeOfEquivalenceNumeric::Clone()
{
  BaseDataDegreeOfEquivalenceNumeric *obj = new BaseDataDegreeOfEquivalenceNumeric(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDegreeOfEquivalenceNumeric::CopyClone(Identify * obj)
{
  BaseDataDegreeOfEquivalenceNumeric *objfull = (BaseDataDegreeOfEquivalenceNumeric *) obj;
  *this = *objfull;
  Values = (BaseDataInstanceDoubleVector *) PointerClone(objfull->Values);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDegreeOfEquivalence::EncodeThis(buffer);
  result = result && PointerEncode(buffer,Values);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDegreeOfEquivalence::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Values);
  return result;
}
/*F ans = Equivalent(degree)  . . . . . . . . . . . . . . . .  BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    degree:   The comparison object in an equivalence class
**    ans: True if equivalent
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::Equivalent(BaseDataDegreeOfEquivalence *degree, BaseDataObject *obj) {
  bool same = false;
  BaseDataNumeric *CutOff = (BaseDataNumeric *) obj;
  NameTag = degree->NameTag;
  BaseDataDegreeOfEquivalenceNumeric *numdegree = (BaseDataDegreeOfEquivalenceNumeric *) degree;
  BaseDataInstanceDoubleVector *objvec = numdegree->getValues();
  VectorNumeric vec = objvec->CurrentVector();
  VectorNumeric ref = Values->CurrentVector();
  double cutoff = CutOff->Distance();
  double sumdiff = 0.0;
  if(vec.size() == ref.size()) {
    VectorNumeric::iterator objvalue = vec.begin();
    VectorNumeric::iterator refvalue=ref.begin();
    while(refvalue != ref.end() && sumdiff <= cutoff) {
      double diff = (*objvalue)-(*refvalue);
      sumdiff += diff*diff;
      refvalue++;
      objvalue++;
    }  
  }
  if(sumdiff <= cutoff)
    same = true;
  return same;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataDegreeOfEquivalence::WriteAsLine(out,objc);
  return result;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataDegreeOfEquivalence::WriteAsASCII(out,objc);
  DataDegreeOfEquivalenceNumericClass *objcfull = (DataDegreeOfEquivalenceNumericClass *) objc;
  if(Values == NULL) {
    out << " NoValues " << endl;
  } else {
    out << " Values: ";
    Values->WriteAsASCII(out,objcfull->getValuesClass());
  }
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataDegreeOfEquivalenceNumeric::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataDegreeOfEquivalence::WriteAsLatex(out,objc);
  return result;
}

/*S DataDegreeOfEquivalenceNumericClass
 */
/*F DataDegreeOfEquivalenceNumericClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDegreeOfEquivalenceNumericClass::DataDegreeOfEquivalenceNumericClass()
  : ValuesClass(NULL)
{
  Identification = EQUIVALENTSETS_NUMDEGREE_ID;
  NameTag = EQUIVALENTSETS_NUMDEGREE_NAME;
  SubClass = "DegreeOfEquivalence";
  EncodeDecodeClass = NameTag;
} 
/*F DataDegreeOfEquivalenceNumericClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDegreeOfEquivalenceNumericClass::DataDegreeOfEquivalenceNumericClass(const DataDegreeOfEquivalenceNumericClass& data)
  : DataDegreeOfEquivalenceClass(data),
    ValuesClass(data.ValuesClass)
{
}
/*F DataDegreeOfEquivalenceNumericClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataDegreeOfEquivalenceNumericClass::DataDegreeOfEquivalenceNumericClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataDegreeOfEquivalenceClass(id,name,descr),
    ValuesClass(NULL)
{
  SubClass = "DegreeOfEquivalence";
  EncodeDecodeClass = "DegreeOfEquivalenceNumeric";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceNumericClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDegreeOfEquivalenceNumericClass::print(ostream& out) const
{
  DataDegreeOfEquivalenceClass::print(out);
  PointerPrint(out,"  The Equivalence Values Class: "," No Class Defined ",ValuesClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceNumericClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDegreeOfEquivalenceNumericClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDegreeOfEquivalenceNumericClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataDegreeOfEquivalenceClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) ValuesClass,
				      DATAOBJ_VECTOR_NAME,
				      set," No Equivalence Values Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceNumericClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDegreeOfEquivalenceNumericClass::CopyClone(Identify *  objc)
{
  DataDegreeOfEquivalenceNumericClass *objcfull = (DataDegreeOfEquivalenceNumericClass *) objc;
  *this = *objcfull;
  ValuesClass = (DataInstanceDoubleVectorClass *) PointerClone(objcfull->ValuesClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceNumericClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDegreeOfEquivalenceNumericClass::Clone()
    {
      DataDegreeOfEquivalenceNumericClass* id = new DataDegreeOfEquivalenceNumericClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceNumericClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDegreeOfEquivalenceNumericClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataDegreeOfEquivalenceClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,ValuesClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDegreeOfEquivalenceNumericClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDegreeOfEquivalenceNumericClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataDegreeOfEquivalenceClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ValuesClass);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataDegreeOfEquivalenceNumericClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataDegreeOfEquivalenceNumeric();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDegreeOfEquivalenceNumericClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDegreeOfEquivalenceNumericClass*& obj)
     {
     obj = new DataDegreeOfEquivalenceNumericClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDegreeOfEquivalenceNumeric
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDegreeOfEquivalenceNumeric*& obj)
     {
     obj = new BaseDataDegreeOfEquivalenceNumeric;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataEquivalentSet
 */ 
/*F BaseDataEquivalentSet()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataEquivalentSet::BaseDataEquivalentSet()
  : Equivalence(NULL),
    CutOffCriteria(NULL),
    SetCount(0)
{
  Identification = EQUIVALENTSETS_EQUIVALENT_ID;
  NameTag = EQUIVALENTSETS_EQUIVALENT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataEquivalentSet(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataEquivalentSet::BaseDataEquivalentSet(const BaseDataEquivalentSet& data)
  : BaseDataObject(data),
    ObjectNames(data.ObjectNames),
    SetCount(0)
{
  Equivalence = (BaseDataDegreeOfEquivalence *) PointerClone(data.Equivalence);
  CutOffCriteria = (BaseDataObject *) PointerClone(data.CutOffCriteria);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataEquivalentSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataEquivalentSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  DataEquivalentSetClass *objcfull = (DataEquivalentSetClass *) objc;
  String equiv("EquivalentSet:");
  CheckReadKeyWord(in,equiv);
  DataKeyWordsClass keyclass;
  ObjectNames.Read(in,&keyclass,name);
  SetCount = ObjectNames.SizeOf();
  String equivthere("Equivalence:");
  bool bequivthere = CheckReadKeyWord(in,equivthere);
  if(bequivthere) {
    //cout << "Read in " << SetCount << "Object names: " << endl;
    //ObjectNames.print(cout);
    //cout << endl;
    String mess("Equivalence Class Not Defined");
    PointerObjectRead(in,(BaseDataObject *&) Equivalence,objcfull->getEquivalenceClass(),mess);
    //cout << "Read in Degree of Equivalence: " << endl;
    //Equivalence->print(cout);
    //cout << endl;
  }
  String cutoffthere("CutOffCriteria:");
  bool cutoff = CheckReadKeyWord(in,cutoffthere);
  if(cutoff) {
    String mess2("Cutoff Criteria Not Defined");
    PointerObjectRead(in,(BaseDataObject *&) CutOffCriteria,objcfull->getCutOffCriteriaClass(),mess2);
  }
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataEquivalentSet
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataEquivalentSet::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << "Equivalent Set:" << endl;
  ObjectNames.print(out);
  PointerPrint(out,"Degree of Equivalence: ","No Degree of Equivalence defined",Equivalence);
  out << endl;
  PointerPrint(out,"CutOff Criteria: ","No CutOff Criteria defined",CutOffCriteria);
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataEquivalentSet
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataEquivalentSet::Clone()
{
  BaseDataEquivalentSet *obj = new BaseDataEquivalentSet(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataEquivalentSet
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataEquivalentSet::CopyClone(Identify * obj)
{
  BaseDataEquivalentSet *objfull = (BaseDataEquivalentSet *) obj;
  *this = *objfull;
  Equivalence = (BaseDataDegreeOfEquivalence *) PointerClone(objfull->Equivalence);
  CutOffCriteria = PointerClone(objfull->CutOffCriteria);
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataEquivalentSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && ObjectNames.EncodeThis(buffer);
  result = result && PointerEncode(buffer,Equivalence);
  result = result && PointerEncode(buffer,CutOffCriteria);
  result = result && Encode(buffer,SetCount);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataEquivalentSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && ObjectNames.DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Equivalence);
  result = result && PointerDecode(buffer,(BaseDataObject *&) CutOffCriteria);
  result = result && Decode(buffer,SetCount);
  return result;
}
/*F ans = BelongsInSet(degree)
**
**  DESCRIPTION
**    degree: The degree of equivalence object to compare
**    ans: True if it belongs in the set
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::BelongsInSet(BaseDataDegreeOfEquivalence *degree) {
  return Equivalence->Equivalent(degree,CutOffCriteria);
}
/*F AddToSet(degree)
**
**  DESCRIPTION
**    degree:  The object to add
**
**  REMARKS
**
*/
void BaseDataEquivalentSet::AddToSet(BaseDataDegreeOfEquivalence *degree) {
  ObjectNames.AddKeyWord(degree->NameTag);
  SetCount++;
}
/*F name = DefaultName(rootname)  . . . . . . . . . . . . . . . .  BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    root:  The root of the next name
      name:  The default name generated
**
**  REMARKS
**
*/
String *BaseDataEquivalentSet::DefaultName(String& rootname)
{
  String *name = new String(rootname);
  String cntname = Int2String(SetCount);
  name->AppendToEnd("_");
  name->AppendToEnd(cntname);
  return name;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataObject::WriteAsASCII(out,objc);
  DataEquivalentSetClass *objcfull = (DataEquivalentSetClass *) objc;
  out << " EquivalentSet:";
  DataKeyWordsClass keyclass;
  ObjectNames.WriteAsASCII(out,&keyclass);
  if(Equivalence == NULL) {
    out << " NoEquivalence ";
  } else {
    out << " Equivalence:" << endl;
    Equivalence->WriteAsASCII(out,objcfull->getEquivalenceClass());
  }
  if(CutOffCriteria == NULL) {
    out << " NoCutOff ";
  } else {
    out << " CutOffCriteria: ";
    CutOffCriteria->WriteAsASCII(out,objcfull->getCutOffCriteriaClass());
  }
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataEquivalentSet::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  return true;
}

/*S DataEquivalentSetClass
 */
/*F DataEquivalentSetClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataEquivalentSetClass::DataEquivalentSetClass()
  : EquivalenceClass(NULL),
    CutOffCriteriaClass(NULL)
{
  Identification = EQUIVALENTSETS_EQUIVALENT_ID;
  NameTag = EQUIVALENTSETS_EQUIVALENT_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataEquivalentSetClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataEquivalentSetClass::DataEquivalentSetClass(const DataEquivalentSetClass& data)
  : DataObjectClass(data)
{
  EquivalenceClass = (DataDegreeOfEquivalenceClass *) PointerClone(data.EquivalenceClass);
  CutOffCriteriaClass = (DataObjectClass *) PointerClone(data.CutOffCriteriaClass);
} 
 
/*F DataEquivalentSetClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataEquivalentSetClass::DataEquivalentSetClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr),
    EquivalenceClass(NULL),
    CutOffCriteriaClass(NULL)
{
  SubClass = "Object";
  EncodeDecodeClass = "EquivalentSet";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataEquivalentSetClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataEquivalentSetClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  PointerPrint(out,"  The EquivalenceSet Class: "," No Class Defined ",EquivalenceClass);
  PointerPrint(out,"  The CutOff Value Class: "," No Class Defined ",CutOffCriteriaClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataEquivalentSetClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataEquivalentSetClass, there is no further information.
**
**  REMARKS
**
*/
bool DataEquivalentSetClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) EquivalenceClass,
				      EQUIVALENTSETS_DEGREE_NAME,set," No Equivalence Class ");
  result = result && PointerClassRead(in,(DataObjectClass *&) CutOffCriteriaClass,
				      COREOBJECTS_BASE_NAME,
				      set," No CutOff Value Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataEquivalentSetClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataEquivalentSetClass::CopyClone(Identify *  objc)
{
  DataEquivalentSetClass *objcfull = (DataEquivalentSetClass *) objc;
  *this = *objcfull;
  EquivalenceClass = (DataDegreeOfEquivalenceClass *) PointerClone(objcfull->EquivalenceClass);
  CutOffCriteriaClass = (DataObjectClass *) PointerClone(objcfull->CutOffCriteriaClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataEquivalentSetClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataEquivalentSetClass::Clone()
    {
      DataEquivalentSetClass* id = new DataEquivalentSetClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataEquivalentSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEquivalentSetClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,EquivalenceClass);
  result = result && PointerEncode(buffer,CutOffCriteriaClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataEquivalentSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEquivalentSetClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) EquivalenceClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) CutOffCriteriaClass);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataEquivalentSetClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataEquivalentSet();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataEquivalentSetClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataEquivalentSetClass*& obj)
     {
     obj = new DataEquivalentSetClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataEquivalentSet
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataEquivalentSet*& obj)
     {
     obj = new BaseDataEquivalentSet;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataSetOfEquivalentSets
 */ 
/*F BaseDataSetOfEquivalentSets()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfEquivalentSets::BaseDataSetOfEquivalentSets()
  : SetCount(0)
{
  Identification = EQUIVALENTSETS_SET_ID;
  NameTag = EQUIVALENTSETS_SET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSetOfEquivalentSets(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSetOfEquivalentSets::BaseDataSetOfEquivalentSets(const BaseDataSetOfEquivalentSets& data)
  : BaseDataSetOfObjects(data),
    SetCount(data.SetCount)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSetOfEquivalentSets::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSetOfEquivalentSets::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataSetOfEquivalentSetsClass *objcfull = (DataSetOfEquivalentSetsClass *) objc;
  DataEquivalentSetClass *equivsetclass = objcfull->getEquivalentSetClass();
  
  SetCount = 0;
  StreamObjectInput str(in,' ');
  String ename = str.ReadNext();
  while(!(ename == "END")) {
    BaseDataEquivalentSet *set = (BaseDataEquivalentSet *) equivsetclass->BaseDataObjectExample();
    set->Read(in,equivsetclass,ename);
    set->NameTag = ename;
    AddObject(set);
    ename = str.ReadNext();
    cout << "Next Set Name: (or END) '" << ename << "'" << endl;
  }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSetOfEquivalentSets::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSetOfEquivalentSets::Clone()
{
  BaseDataSetOfEquivalentSets *obj = new BaseDataSetOfEquivalentSets(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSetOfEquivalentSets::CopyClone(Identify * obj)
{
  BaseDataSetOfEquivalentSets *objfull = (BaseDataSetOfEquivalentSets *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfEquivalentSets::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && Encode(buffer,SetCount);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfEquivalentSets::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && Decode(buffer,SetCount);
  return result;
}
/*F name = DefaultName(rootname)  . . . . . . . . . . . . . . . .  BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    root:  The root of the next name
      name:  The default name generated
**
**  REMARKS
**
*/
String *BaseDataSetOfEquivalentSets::DefaultName(String& rootname)
{
  String *name = new String(rootname);
  String cntname = Int2String(SetCount);
  name->AppendToEnd("_");
  name->AppendToEnd(cntname);
  return name;
}
 /*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataSetOfEquivalentSets::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataSetOfEquivalentSets::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  ObjectList<String> names = ListOfObjectNames();
  ObjectList<String>::iterator name;
  DataSetOfEquivalentSetsClass *esetclass = (DataSetOfEquivalentSetsClass *) objc;
  DataSetOfObjectsClass *classes = esetclass->PointerToAllowedClasses();
  for(name = names.begin(); name != names.end(); name++) {
    out << " " << *name << endl;
    BaseDataEquivalentSet *set = (BaseDataEquivalentSet *) GetObject(*name);
    DataEquivalentSetClass *setclass = (DataEquivalentSetClass *) classes->GetObjectClass(set->GetType());
    set->WriteAsASCII(out,setclass);
    out << endl;
  }
  out << "END" << endl;
  return true;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataSetOfEquivalentSets::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  return true;
}

/*S DataSetOfEquivalentSetsClass
 */
/*F DataSetOfEquivalentSetsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSetOfEquivalentSetsClass::DataSetOfEquivalentSetsClass()
  : EquivalentSetClass(NULL)
{
  Identification = EQUIVALENTSETS_SET_ID;
  NameTag = EQUIVALENTSETS_SET_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataSetOfEquivalentSetsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSetOfEquivalentSetsClass::DataSetOfEquivalentSetsClass(const DataSetOfEquivalentSetsClass& data)
  : DataSetOfObjectsClass(data)
{
  EquivalentSetClass = (DataEquivalentSetClass *) PointerClone(data.EquivalentSetClass);
} 
 
/*F DataSetOfEquivalentSetsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataSetOfEquivalentSetsClass::DataSetOfEquivalentSetsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr),
    EquivalentSetClass(NULL)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = "SetOfEquivalentSets";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSetOfEquivalentSetsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSetOfEquivalentSetsClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  PointerPrint(out,"  The Equivalent Set Class: "," No Equivalent Set Class Defined ",EquivalentSetClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSetOfEquivalentSetsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSetOfEquivalentSetsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSetOfEquivalentSetsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = PointerClassRead(in,(DataObjectClass *&) EquivalentSetClass,
				      EQUIVALENTSETS_EQUIVALENT_NAME,
				      set," No Equivalent Set Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSetOfEquivalentSetsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSetOfEquivalentSetsClass::CopyClone(Identify *  objc)
{
  DataSetOfEquivalentSetsClass *objcfull = (DataSetOfEquivalentSetsClass *) objc;
  *this = *objcfull;
  EquivalentSetClass = (DataEquivalentSetClass *) PointerClone(objcfull->EquivalentSetClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSetOfEquivalentSetsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSetOfEquivalentSetsClass::Clone()
    {
      DataSetOfEquivalentSetsClass* id = new DataSetOfEquivalentSetsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSetOfEquivalentSetsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfEquivalentSetsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,EquivalentSetClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSetOfEquivalentSetsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfEquivalentSetsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) EquivalentSetClass);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataSetOfEquivalentSetsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataSetOfEquivalentSets();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSetOfEquivalentSetsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSetOfEquivalentSetsClass*& obj)
     {
     obj = new DataSetOfEquivalentSetsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSetOfEquivalentSets
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSetOfEquivalentSets*& obj)
     {
     obj = new BaseDataSetOfEquivalentSets;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataSimpleEquivalentSetAlgorithm
 */ 
/*F BaseDataSimpleEquivalentSetAlgorithm()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimpleEquivalentSetAlgorithm::BaseDataSimpleEquivalentSetAlgorithm()
  : RealCutOffS(EQUIVALENT_NUMERICCUTOFF),
    MatrixOfProbsS(DESCRIPTION_MATRIX_NAME),
    EquivalentSetsS(EQUIVALENT_SET_NAME)
    
{
  Identification = EQUIVALENTSETS_SIMPEQUIVALG_ID;
  NameTag = EQUIVALENTSETS_SIMPEQUIVALG_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSimpleEquivalentSetAlgorithm(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimpleEquivalentSetAlgorithm::BaseDataSimpleEquivalentSetAlgorithm(const BaseDataSimpleEquivalentSetAlgorithm& data)
  : BaseDataAlgorithmOperation(data),
    RealCutOffS(data.RealCutOffS),
    MatrixOfProbsS(data.MatrixOfProbsS),
    EquivalentSetsS(data.EquivalentSetsS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSimpleEquivalentSetAlgorithm::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "Simple Setup of EquivalentSets from an existing set, '" << EquivalentSetsS << "' and Matrix of";
  out << " Probabilities, '" << MatrixOfProbsS << "' with Cutoff '" << RealCutOffS << "'" << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSimpleEquivalentSetAlgorithm::Clone()
{
  BaseDataSimpleEquivalentSetAlgorithm *obj = new BaseDataSimpleEquivalentSetAlgorithm(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSimpleEquivalentSetAlgorithm::CopyClone(Identify * obj)
{
  BaseDataSimpleEquivalentSetAlgorithm *objfull = (BaseDataSimpleEquivalentSetAlgorithm *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,RealCutOffS);
  result = result && Encode(buffer,MatrixOfProbsS);
  result = result && Encode(buffer,EquivalentSetsS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,RealCutOffS);
  result = result && Decode(buffer,MatrixOfProbsS);
  result = result && Decode(buffer,EquivalentSetsS);
  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances *instances,
				       DataSetOfInstancesClass *instancesclass,
				       BaseDataAlgorithmRun *run,
				       DataAlgorithmRunClass *runclass)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(RealCutOffS,"Matrix of Probabilities",run);
  result = result && CheckInputVariable(MatrixOfProbsS,"Matrix of Probabilities",run);
  result = result && CheckInputVariable(EquivalentSetsS,"Set of Equivalent Sets Names: Input and Output",run);
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::SetUpInput(BaseDataSetOfInstances *instances,
						      DataSetOfInstancesClass *instancesclass,
						      BaseDataAlgorithmRun *run,
						      DataAlgorithmRunClass *runclass)
{
  bool result = true;
  RealCutOff = (BaseDataReal *) run->ParameterValue(RealCutOffS);
  MatrixOfProbs = (BaseDataInstanceDoubleMatrix *) run->ParameterValue(MatrixOfProbsS);
  ProbMatrix = &(MatrixOfProbs->CurrentMatrix());

  BaseDataKeyWords *equivnames = (BaseDataKeyWords *) run->ParameterValue(EquivalentSetsS);
  if(equivnames->SizeOf() == 2) {
    BaseDataKeyWords *names = (BaseDataKeyWords *) equivnames->Clone();
    StartEquivalentSetsS = names->NextKey();
    NewEquivalentSetsS = names->NextKey();
    if(instances->IsInList(StartEquivalentSetsS)) {
      EquivalentSets = (BaseDataSetOfEquivalentSets *) instances->GetObject(StartEquivalentSetsS);
      unsigned int ctype = EquivalentSets->GetType();
      DataSetOfObjectsClass *classes = instancesclass->PointerToAllowedClasses();
      EquivalentSetsClass = (DataSetOfEquivalentSetsClass *) classes->GetObjectClass(ctype);
      NewEquivalentSets = (BaseDataSetOfEquivalentSets *) EquivalentSetsClass->BaseDataObjectExample();
      NewEquivalentSets->NameTag = NewEquivalentSetsS;
    } else {
      result = false;
      cerr << "The start equivalent set, '" << StartEquivalentSetsS << "' not found in attributes" << endl;
    }
  }
  if(run->AlgorithmSummary.KeyWordInList(EQUIVALENT_SINGLETONS))
    filterSingletons = true;
  else
    filterSingletons = false;

  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::Calculate(BaseDataSetOfInstances *instances,
						     DataSetOfInstancesClass *instancesclass,
						     BaseDataAlgorithmRun *run,
						     DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
  DataEquivalentSetClass *setclass = EquivalentSetsClass->getEquivalentSetClass();
  ObjectList<String> sets = EquivalentSets->ListOfObjectNames();
  ObjectList<String>::iterator setname;
  for(setname = sets.begin();setname != sets.end();setname++) {
    BaseDataEquivalentSet *set = (BaseDataEquivalentSet *) EquivalentSets->GetObject(*setname);
    BaseDataSetOfEquivalentSets *newsets = GroupEquivalentSet(set,setclass);
    AddNewSets(newsets);
    delete newsets;
  }
  cout << "==========================================================================" << endl;
  DataObjectClass keyclass;
  ObjectList<String> names = NewEquivalentSets->ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = names.begin();name != names.end();name++) {
    BaseDataEquivalentSet *set = (BaseDataEquivalentSet *) NewEquivalentSets->GetObject(*name);
    BaseDataKeyWords *objs = set->getNames();
    cout << endl << *name << endl;
    objs->WriteAsASCII(cout,&keyclass);
    cout << endl;
  }
  cout << "==========================================================================" << endl;
  return result;
}
String *BaseDataSimpleEquivalentSetAlgorithm::BuildEquivalenceName(BaseDataReal *cutoff, BaseDataInstanceDoubleVector *probs) {
  String *name = new String("M_");
  double cut = cutoff->GetValue();
  ObjectListString names = probs->getParameterNames().KeyWords;
  ObjectListString::iterator n = names.begin();
  VectorNumeric vec = probs->CurrentVector();
  VectorNumeric::iterator value = vec.begin();
  for(VectorNumeric::iterator value = vec.begin();
      value != vec.end();
      value++) {
    if(*value >= cut) {
      if((*n).size() > 9) {
	String buf = (*n).Isolate(10,(*n).size()-2);
	name->AppendToEnd(buf);
      } else {
	name->AppendToEnd(*n);
      }
    }
    n++;
  }
  return name;
}
/*F sets = GroupEquivalentSet(set)
**
**  DESCRIPTION
**    set:   A single set of objects in an equivalence set
**    sets:  The objects groups in subgroups
**    
**  REMARKS
**
*/
BaseDataSetOfEquivalentSets *BaseDataSimpleEquivalentSetAlgorithm::GroupEquivalentSet(BaseDataEquivalentSet *set,
										      DataEquivalentSetClass *setclass) {

  BaseDataSetOfEquivalentSets *newequivsets = (BaseDataSetOfEquivalentSets *) EquivalentSetsClass->BaseDataObjectExample();
  
  BaseDataKeyWords *names = (BaseDataKeyWords *) set->getNames()->Clone();
  while(names->SizeOf() > 0) {
    String name = names->NextKey();
    cout << "GroupEquivalentSet: " << name << endl;
    BaseDataInstanceDoubleVector *probs = MatrixOfProbs->getRow(name);
    if(probs != NULL) {
      BaseDataDegreeOfEquivalenceNumeric *newvalue = new BaseDataDegreeOfEquivalenceNumeric(probs);
      ObjectList<String> names = newequivsets->ListOfObjectNames();
      bool notfound = true;
      ObjectList<String>::iterator newname = names.begin();
      while(newname != names.end() && notfound) {
	BaseDataEquivalentSet *reference = (BaseDataEquivalentSet *) newequivsets->GetObject(*newname);
	if(reference->BelongsInSet(newvalue)) {
	  reference->AddToSet(newvalue);
	  notfound = false;
	}
	newname++;
      }
      if(notfound) {
	cout << "New set" << endl;
	BaseDataEquivalentSet *newrefset = (BaseDataEquivalentSet *) setclass->BaseDataObjectExample();
	newrefset->setCutOffCriteria((BaseDataObject *) RealCutOff->Clone());
	newrefset->setDegreeOfEquivalence(newvalue);
	//newrefset->NameTag = *(newequivsets->DefaultName(name));
	newrefset->NameTag = *(BuildEquivalenceName(RealCutOff,probs));
	newrefset->AddToSet(newvalue);
	newequivsets->AddObject(newrefset);
      }
    } else {
      cerr << "The Object, '" << name << "' has no probability values, ignored" << endl;
    }
  }
  return newequivsets;
}
/*F AddNewSets(sets)
**
**  DESCRIPTION
**    sets:  The new sets to add to the total
**    
**  REMARKS
**
*/
void BaseDataSimpleEquivalentSetAlgorithm::AddNewSets(BaseDataSetOfEquivalentSets *sets) {
  ObjectList<String> names = sets->ListOfObjectNames();
  for(ObjectList<String>::iterator name = names.begin();name != names.end();name++) {
    BaseDataEquivalentSet *set = (BaseDataEquivalentSet *) sets->GetObject(*name);
    if(filterSingletons) {
      if(!set->Singleton()) {
	NewEquivalentSets->AddObject(set);
      }
    } else {
      	NewEquivalentSets->AddObject(set);
    }
  }
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  instances->AddObject(NewEquivalentSets);
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataSimpleEquivalentSetAlgorithm::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 
 
 
/*S DataSimpleEquivalentSetAlgorithmClass
 */
/*F DataSimpleEquivalentSetAlgorithmClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSimpleEquivalentSetAlgorithmClass::DataSimpleEquivalentSetAlgorithmClass()
{
  Identification = EQUIVALENTSETS_SIMPEQUIVALG_ID;
  NameTag = EQUIVALENTSETS_SIMPEQUIVALG_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataSimpleEquivalentSetAlgorithmClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSimpleEquivalentSetAlgorithmClass::DataSimpleEquivalentSetAlgorithmClass(const DataSimpleEquivalentSetAlgorithmClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataSimpleEquivalentSetAlgorithmClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataSimpleEquivalentSetAlgorithmClass::DataSimpleEquivalentSetAlgorithmClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "SimpleEquivalentSetAlgorithm";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSimpleEquivalentSetAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSimpleEquivalentSetAlgorithmClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSimpleEquivalentSetAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSimpleEquivalentSetAlgorithmClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSimpleEquivalentSetAlgorithmClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSimpleEquivalentSetAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSimpleEquivalentSetAlgorithmClass::CopyClone(Identify *  objc)
{
  DataSimpleEquivalentSetAlgorithmClass *objcfull = (DataSimpleEquivalentSetAlgorithmClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSimpleEquivalentSetAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSimpleEquivalentSetAlgorithmClass::Clone()
    {
      DataSimpleEquivalentSetAlgorithmClass* id = new DataSimpleEquivalentSetAlgorithmClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleEquivalentSetAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleEquivalentSetAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleEquivalentSetAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleEquivalentSetAlgorithmClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) Class);
  //result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataSimpleEquivalentSetAlgorithmClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataSimpleEquivalentSetAlgorithm();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSimpleEquivalentSetAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSimpleEquivalentSetAlgorithmClass*& obj)
     {
     obj = new DataSimpleEquivalentSetAlgorithmClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSimpleEquivalentSetAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSimpleEquivalentSetAlgorithm*& obj)
     {
     obj = new BaseDataSimpleEquivalentSetAlgorithm;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataAddEquivalentNameToKeyWords
 */ 
/*F BaseDataAddEquivalentNameToKeyWords()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataAddEquivalentNameToKeyWords::BaseDataAddEquivalentNameToKeyWords()
  : InstanceNameListS("TotalInstanceNameList"),
    ParametersS("Parameters"),
    EquivalentSetsS(EQUIVALENT_SET_NAME),
    KeyWordListS("KeyWordList"),
    ReplaceKeyS(EQUIVALENT_REPLACE_KEY)
{
  Identification = EQUIVALENTSETS_ADDCLASSTOKEYS_ID;
  NameTag = EQUIVALENTSETS_ADDCLASSTOKEYS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataAddEquivalentNameToKeyWords(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataAddEquivalentNameToKeyWords::BaseDataAddEquivalentNameToKeyWords(const BaseDataAddEquivalentNameToKeyWords& data)
  : BaseDataAlgorithmOperation(data),
    InstanceNameListS(data.InstanceNameListS),
    ParametersS(data.ParametersS),
    EquivalentSetsS(data.EquivalentSetsS),
    KeyWordListS(data.KeyWordListS),
    ReplaceKeyS(data.ReplaceKeyS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataAddEquivalentNameToKeyWords::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "Add/Replace keys in '" << InstanceNameListS << "' ";
  out << "with equivalent names given by '" << EquivalentSetsS << "' ";
  out << "in parameters '" << ParametersS << "' ";
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataAddEquivalentNameToKeyWords::Clone()
{
  BaseDataAddEquivalentNameToKeyWords *obj = new BaseDataAddEquivalentNameToKeyWords(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataAddEquivalentNameToKeyWords::CopyClone(Identify * obj)
{
  BaseDataAddEquivalentNameToKeyWords *objfull = (BaseDataAddEquivalentNameToKeyWords *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,InstanceNameListS);
  result = result && Encode(buffer,ParametersS);
  result = result && Encode(buffer,EquivalentSetsS);
  result = result && Encode(buffer,KeyWordListS);
  result = result && Encode(buffer,ReplaceKeyS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,InstanceNameListS);
  result = result && Decode(buffer,ParametersS);
  result = result && Decode(buffer,EquivalentSetsS);
  result = result && Decode(buffer,KeyWordListS);
  result = result && Decode(buffer,ReplaceKeyS);
  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::SetUpAlgorithms(BaseDataSetOfInstances *instances,
				       DataSetOfInstancesClass *instancesclass,
				       BaseDataAlgorithmRun *run,
				       DataAlgorithmRunClass *runclass)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(InstanceNameListS,"List of Instance Names",run);
  result = result && CheckInputVariable(ParametersS,"List of Parameters in Instances",run);
  result = result && CheckInputVariable(EquivalentSetsS,"Set of Equivalent Sets",run);
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  InstanceNameList = (BaseDataKeyWords *) run->ParameterValue(InstanceNameListS)->Clone();
  Parameters = (BaseDataKeyWords *) run->ParameterValue(ParametersS);
  EquivalentSets = (BaseDataSetOfEquivalentSets *) run->ParameterValue(EquivalentSetsS);

  ReplaceKey = false;
  if(run->AlgorithmSummary.KeyWordInList(ReplaceKeyS)){
    ReplaceKey = true;
  }

  KeyWordList = new BaseDataKeyWords();
  KeyWordList->NameTag = KeyWordListS;

  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  BaseDataSetOfObjects *corrs = SetUpCorrespondences(EquivalentSets);
  while(InstanceNameList->SizeOf() > 0) {
    String instname = InstanceNameList->NextKey();
    if(instances->InstanceInSet(instname)) {
      BaseDataInstance *instance = instances->GetInstance(instname);
      //cout << "Instance: " << instance->NameTag << endl;
      BaseDataKeyWords *params = (BaseDataKeyWords *) Parameters->Clone();
      while(params->SizeOf() > 0) {
	String param = params->NextKey();
	if(instance->IsInList(param)) {
	  //cout << "Parameter: " << param << endl;
	  BaseDataKeyWords *keys = (BaseDataKeyWords *) instance->GetObject(param)->Clone();
	  BaseDataKeyWords *newkeys = (BaseDataKeyWords *) keys->Clone();
	  while(keys->SizeOf() > 0) {
	    String key = keys->NextKey();
	    if(corrs->IsInList(key)) {
	      if(ReplaceKey) {
		newkeys->RemoveKeyWord(key);
	      } else {
		if(!KeyWordList->KeyWordInList(key))
		  KeyWordList->AddKeyWord(key);
	      }
	      BaseDataString *str = (BaseDataString *) corrs->GetObject(key);
	      //cout << "replace " << key << " with " << str->getString() << endl;
	      newkeys->AddKeyWord(str->getString());
	      if(!KeyWordList->KeyWordInList(str->getString()))
		KeyWordList->AddKeyWord(str->getString());
	    } else {
	      if(!KeyWordList->KeyWordInList(key))
		KeyWordList->AddKeyWord(key);
	    }
	  }
	  instance->AddObject(newkeys);
	  delete newkeys;
	  delete keys;
	}
      }
    } else {
      cerr << "Instance '" << instname << "' not in Instances" << endl;
    }
  }
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
//  run->AddParameter(ctree);
  instances->AddObject(KeyWordList);
  delete KeyWordList;
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataAddEquivalentNameToKeyWords::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 

 
/*S DataAddEquivalentNameToKeyWordsClass
 */
/*F DataAddEquivalentNameToKeyWordsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataAddEquivalentNameToKeyWordsClass::DataAddEquivalentNameToKeyWordsClass()
{
  Identification = EQUIVALENTSETS_ADDCLASSTOKEYS_ID;
  NameTag = EQUIVALENTSETS_ADDCLASSTOKEYS_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataAddEquivalentNameToKeyWordsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataAddEquivalentNameToKeyWordsClass::DataAddEquivalentNameToKeyWordsClass(const DataAddEquivalentNameToKeyWordsClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataAddEquivalentNameToKeyWordsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataAddEquivalentNameToKeyWordsClass::DataAddEquivalentNameToKeyWordsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "AddEquivalentNameToKeyWords";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataAddEquivalentNameToKeyWordsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataAddEquivalentNameToKeyWordsClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataAddEquivalentNameToKeyWordsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataAddEquivalentNameToKeyWordsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataAddEquivalentNameToKeyWordsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataAddEquivalentNameToKeyWordsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataAddEquivalentNameToKeyWordsClass::CopyClone(Identify *  objc)
{
  DataAddEquivalentNameToKeyWordsClass *objcfull = (DataAddEquivalentNameToKeyWordsClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataAddEquivalentNameToKeyWordsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataAddEquivalentNameToKeyWordsClass::Clone()
    {
      DataAddEquivalentNameToKeyWordsClass* id = new DataAddEquivalentNameToKeyWordsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataAddEquivalentNameToKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAddEquivalentNameToKeyWordsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataAddEquivalentNameToKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAddEquivalentNameToKeyWordsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) Class);
  //result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataAddEquivalentNameToKeyWordsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataAddEquivalentNameToKeyWords();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataAddEquivalentNameToKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataAddEquivalentNameToKeyWordsClass*& obj)
     {
     obj = new DataAddEquivalentNameToKeyWordsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataAddEquivalentNameToKeyWords
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataAddEquivalentNameToKeyWords*& obj)
     {
     obj = new BaseDataAddEquivalentNameToKeyWords;
     return obj->DecodeThis(buffer);
     }

/*S  Utilities
 */

BaseDataSetOfObjects *SetUpCorrespondences(BaseDataSetOfEquivalentSets *sets) {
  cout << "SetUpCorrespondences  Sets" << endl;
  sets->print(cout);
  cout << endl;
  BaseDataSetOfObjects *corrs = new BaseDataSetOfObjects();
  ObjectList<String> names = sets->ListOfObjectNames();
  cout << "SetUpCorrespondences Names" << endl;
  names.print(cout);
  cout << endl;
  ObjectList<String>::iterator name;
  for(name = names.begin();name != names.end();name++) {
    cout << "SetUpCorrespondences  Name '" << *name << "'" << endl;
    BaseDataEquivalentSet *set = (BaseDataEquivalentSet *) sets->GetObject(*name);
    cout << "SetUpCorrespondences  Set from name" << endl;
    set->print(cout);
    cout << endl;
    BaseDataKeyWords *mols = (BaseDataKeyWords *) set->getNames()->Clone();
    while(mols->SizeOf() > 0) {
      BaseDataString corr;
      corr.NameTag = mols->NextKey();
      corr.setString(*name);
      corrs->AddObject(&corr);
    }
  }
  return corrs;
}
BaseDataKeyWords *TranslateKeyWords(BaseDataKeyWords *keys, BaseDataSetOfObjects *translations) {
  BaseDataKeyWords *refkeys = (BaseDataKeyWords *) keys->Clone();
  BaseDataKeyWords *newkeys = (BaseDataKeyWords *) keys->Clone();
  while(refkeys->SizeOf() > 0) {
    String name = refkeys->NextKey();
    if(translations->IsInList(name)) {
      newkeys->RemoveKeyWord(name);
      BaseDataString  *strname = (BaseDataString  *) translations->GetObject(name);
      if(!newkeys->KeyWordInList(strname->getString()))
	newkeys->AddKeyWord(strname->getString());
    } 
  }
  delete refkeys;
  return newkeys;
}
void ReplaceWithTranslatedKeyWords(BaseDataKeySet *keys, BaseDataSetOfObjects *translations) {
  BaseDataKeySet *newkeys = new BaseDataKeySet();
  while(keys->SizeOf() > 0) {
    String name = keys->NextKey();
    if(translations->IsInList(name)) {
      BaseDataString  *strname = (BaseDataString  *) translations->GetObject(name);
      newkeys->AddKeyWord(strname->getString());
    } else {
      newkeys->AddKeyWord(name);
    }
  }
  while(newkeys->SizeOf() > 0) {
    String name = newkeys->NextKey();
    keys->AddKeyWord(name);
  }
  delete newkeys;
}
/*F InitialSetOfEquivalenceClassesEncodeDecodeRoutines()
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void InitialSetOfEquivalenceClassesEncodeDecodeRoutines() {
  EncodeDecodeRegisterClass(DataDegreeOfEquivalenceClass,BaseDataDegreeOfEquivalence,EQUIVALENTSETS_DEGREE_NAME);
  EncodeDecodeRegisterClass(DataEquivalentSetClass,BaseDataEquivalentSet,EQUIVALENTSETS_EQUIVALENT_NAME);
  EncodeDecodeRegisterClass(DataSetOfEquivalentSetsClass,BaseDataSetOfEquivalentSets,EQUIVALENTSETS_SET_NAME);
  EncodeDecodeRegisterClass(DataSimpleEquivalentSetAlgorithmClass,BaseDataSimpleEquivalentSetAlgorithm,EQUIVALENTSETS_SIMPEQUIVALG_NAME);
  EncodeDecodeRegisterClass(DataDegreeOfEquivalenceNumericClass,BaseDataDegreeOfEquivalenceNumeric,EQUIVALENTSETS_NUMDEGREE_NAME);
EncodeDecodeRegisterClass(DataAddEquivalentNameToKeyWordsClass,BaseDataAddEquivalentNameToKeyWords,EQUIVALENTSETS_ADDCLASSTOKEYS_NAME);
}
/*F InitialSetOfEquivalenceClassesEncodeDecodeRoutines()
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void AddEquivalenceClassesClasses(DataSetOfObjectsClass& set) {
  String degreedescr("The Degree of Equivalence Class");
  DataDegreeOfEquivalenceClass degreeclass(EQUIVALENTSETS_DEGREE_ID,EQUIVALENTSETS_DEGREE_NAME,degreedescr);
  set.AddObjectClass(degreeclass);

  String equivdescr("The Equivalent Set Class");
  DataEquivalentSetClass equivclass(EQUIVALENTSETS_EQUIVALENT_ID,EQUIVALENTSETS_EQUIVALENT_NAME,equivdescr);
  set.AddObjectClass(equivclass);

  String setdescr("The Set of Equivalent Set Class");
  DataSetOfEquivalentSetsClass setclass(EQUIVALENTSETS_SET_ID,EQUIVALENTSETS_SET_NAME,setdescr);
  set.AddObjectClass(setclass);

  String simpalgdescr("The Simple Equivalent Sets Algorithm Class");
  DataSimpleEquivalentSetAlgorithmClass simpalgclass(EQUIVALENTSETS_SIMPEQUIVALG_ID,EQUIVALENTSETS_SIMPEQUIVALG_NAME,simpalgdescr);
  set.AddObjectClass(simpalgclass);

  String numdegdescr("The Numeric Degree of Equivalence Class");
  DataDegreeOfEquivalenceNumericClass numdegclass(EQUIVALENTSETS_NUMDEGREE_ID,EQUIVALENTSETS_NUMDEGREE_NAME,numdegdescr);
  set.AddObjectClass(numdegclass);

  String addkeydescr("The Class");
  DataAddEquivalentNameToKeyWordsClass addkeyclass(EQUIVALENTSETS_ADDCLASSTOKEYS_ID,EQUIVALENTSETS_ADDCLASSTOKEYS_NAME,addkeydescr);
  set.AddObjectClass(addkeyclass);
}



