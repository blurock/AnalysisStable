/*  FILE     VectorOperations.cc
**  PACKAGE  VectorOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "VectorOperations" package.
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
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "NumericOperations.hh"
#include "VectorOperations.hh"

/*S BaseDataFormVector
 */ 
/*F BaseDataFormVector()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataFormVector::BaseDataFormVector()
{
  Identification = VECOPERATION_FORM_ID;
  NameTag = VECOPERATION_FORM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataFormVector(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataFormVector::BaseDataFormVector(const BaseDataFormVector& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataFormVector
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataFormVector::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataFormVector
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataFormVector::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataFormVector
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataFormVector::print(ostream& out) const
{
  BaseDataOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataFormVector
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataFormVector::Clone()
{
  BaseDataFormVector *obj = new BaseDataFormVector(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataFormVector
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataFormVector::CopyClone(Identify * obj)
{
  BaseDataFormVector *objfull = (BaseDataFormVector *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataFormVector
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFormVector::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataFormVector
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFormVector::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  // The rest

  return result;
}
/*F operator()(cls,x,xc)  . . . . . . . . . . Execute the function with input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of objects as input parameters
**    xc: The class of the set of objects
**
**    The operation at this level can be used to set up the output object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataFormVector::operator()(DataObjectClass *cls,
					       BaseDataObject *x,
					       DataObjectClass *xc)
{
  return operator()(x,xc);
}
 
/*F obj = operator()(cls,x,xc,y,yc) . . . . . . . . with parameters and input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of function parameters
**    xc: The function parameter class
**    y: The input parameters
**    yc: The input parameter class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataFormVector::operator()(DataObjectClass *cls,
					       BaseDataObject *x,
					       BaseDataObject *y,
					       DataObjectClass *xc,
					       DataObjectClass *yc)
{
  return operator()(x,y,xc,yc);
}
/*F operator()(cls,x,xc)  . . . . . . . . . . Execute the function with input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of objects as input parameters
**    xc: The class of the set of objects
**
**    The operation at this level can be used to set up the output object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataFormVector::operator()(BaseDataObject *x,
					       DataObjectClass *xc)
{
  BaseDataInteger *rx = (BaseDataInteger *) x;
  unsigned int vsize = rx->GetValue();
  VectorNumeric vec(vsize);
  String name("V");
  BaseDataKeyWords keys;
  for(unsigned int i=0;i<vsize;i++)
    {
      String par(name);
      String num = Int2String(i);
      name.AppendToEnd(num);
      keys.AddKeyWord(name);
    }
  //BaseDataInstanceDoubleVector *instvec = (BaseDataInstanceDoubleVector *) new BaseDataInstanceDoubleVector(vec,keys);
  BaseDataDoubleVector *instvec = (BaseDataDoubleVector *) new BaseDataDoubleVector(vec);
  cout << "BaseDataFormVector::operator()(1 arg)" << endl;
  instvec->print(cout);
  cout << endl;
  CurrentPosition = 0;
  
  return (BaseDataObject *) instvec;
}
 
/*F obj = operator()(cls,x,xc,y,yc) . . . . . . . . with parameters and input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of function parameters
**    xc: The function parameter class
**    y: The input parameters
**    yc: The input parameter class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataFormVector::operator()(BaseDataObject *x,
					       BaseDataObject *y,
					       DataObjectClass *xc,
					       DataObjectClass *yc)
{
  BaseDataReal *rx = (BaseDataReal *) y;
  BaseDataDoubleVector *instvec = (BaseDataDoubleVector *) x;

  if(CurrentPosition < instvec->CurrentVector().size())
    {
      (instvec->CurrentVector())[CurrentPosition] = rx->GetValue();
      CurrentPosition++;
    }
  else
    {
      cerr << "Number of Arguments for vector creation exceeded" << endl;
      cerr << "A maximum of " << instvec->CurrentVector().size() << " is allowed" << endl;
    }
  cout << "BaseDataFormVector::operator()(2 arg)" << endl;
  instvec->print(cout);
  cout << endl;
  return instvec;
}

 
/*S DataFormVectorClass
 */
/*F DataFormVectorClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataFormVectorClass::DataFormVectorClass()
{
  Identification = VECOPERATION_FORM_ID;
  NameTag = VECOPERATION_FORM_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataFormVectorClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataFormVectorClass::DataFormVectorClass(const DataFormVectorClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataFormVectorClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataFormVectorClass::DataFormVectorClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = VECOPERATION_FORM_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataFormVectorClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataFormVectorClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataFormVectorClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataFormVectorClass, there is no further information.
**
**  REMARKS
**
*/
bool DataFormVectorClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataFormVectorClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataFormVectorClass::CopyClone(Identify *  objc)
{
  DataFormVectorClass *objcfull = (DataFormVectorClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataFormVectorClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataFormVectorClass::Clone()
    {
      DataFormVectorClass* id = new DataFormVectorClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataFormVectorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFormVectorClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataFormVectorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFormVectorClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

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
BaseDataObject * DataFormVectorClass::BaseDataObjectExample()
{ 
  //cout << "Make FormVector Example\n";
  return (BaseDataObject *) new BaseDataFormVector();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataFormVectorClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataFormVectorClass*& obj)
     {
     obj = new DataFormVectorClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataFormVector
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataFormVector*& obj)
     {
     obj = new BaseDataFormVector;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataVectorParameterizedFunction
 */ 
/*F BaseDataVectorParameterizedFunction()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataVectorParameterizedFunction::BaseDataVectorParameterizedFunction()
{
  Identification = VECOPERATION_REAL_ID;
  NameTag = VECOPERATION_REAL_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataVectorParameterizedFunction(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataVectorParameterizedFunction::BaseDataVectorParameterizedFunction(const BaseDataVectorParameterizedFunction& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataVectorParameterizedFunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataVectorParameterizedFunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataVectorParameterizedFunction::print(ostream& out) const
{
  BaseDataOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataVectorParameterizedFunction::Clone()
{
  BaseDataVectorParameterizedFunction *obj = new BaseDataVectorParameterizedFunction(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataVectorParameterizedFunction::CopyClone(Identify * obj)
{
  BaseDataVectorParameterizedFunction *objfull = (BaseDataVectorParameterizedFunction *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVectorParameterizedFunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVectorParameterizedFunction::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  // The rest

  return result;
}
/*F operator()(cls,x,xc)  . . . . . . . . . . Execute the function with input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of objects as input parameters
**    xc: The class of the set of objects
**
**    The operation at this level can be used to set up the output object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataVectorParameterizedFunction::operator()(DataObjectClass *cls,
					       BaseDataObject *x,
					       DataObjectClass *xc)
{
  return operator()(x,xc);
}
 
/*F obj = operator()(cls,x,xc,y,yc) . . . . . . . . with parameters and input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of function parameters
**    xc: The function parameter class
**    y: The input parameters
**    yc: The input parameter class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataVectorParameterizedFunction::operator()(DataObjectClass *cls,
					       BaseDataObject *x,
					       BaseDataObject *y,
					       DataObjectClass *xc,
					       DataObjectClass *yc)
{
  return operator()(x,y,xc,yc);
}
/*F operator()(cls,x,xc)  . . . . . . . . . . Execute the function with input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of objects as input parameters
**    xc: The class of the set of objects
**
**    The operation at this level can be used to set up the output object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataVectorParameterizedFunction::operator()(BaseDataObject *x,
					       DataObjectClass *xc)
{
  return (BaseDataObject *) x->Clone();
}
 
/*F obj = operator()(cls,x,xc,y,yc) . . . . . . . . with parameters and input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of function parameters
**    xc: The function parameter class
**    y: The input parameters
**    yc: The input parameter class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataVectorParameterizedFunction::operator()(BaseDataObject *x,
								BaseDataObject *y,
								DataObjectClass *xc,
								DataObjectClass *yc)
{
  return (BaseDataObject *) x->Clone();
}

 
/*S DataVectorParameterizedFunctionClass
 */
/*F DataVectorParameterizedFunctionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataVectorParameterizedFunctionClass::DataVectorParameterizedFunctionClass()
{
  Identification = VECOPERATION_REAL_ID;
  NameTag = VECOPERATION_REAL_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataVectorParameterizedFunctionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataVectorParameterizedFunctionClass::DataVectorParameterizedFunctionClass(const DataVectorParameterizedFunctionClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataVectorParameterizedFunctionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataVectorParameterizedFunctionClass::DataVectorParameterizedFunctionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = VECOPERATION_REAL_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataVectorParameterizedFunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataVectorParameterizedFunctionClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataVectorParameterizedFunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataVectorParameterizedFunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataVectorParameterizedFunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataVectorParameterizedFunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataVectorParameterizedFunctionClass::CopyClone(Identify *  objc)
{
  DataVectorParameterizedFunctionClass *objcfull = (DataVectorParameterizedFunctionClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataVectorParameterizedFunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataVectorParameterizedFunctionClass::Clone()
    {
      DataVectorParameterizedFunctionClass* id = new DataVectorParameterizedFunctionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataVectorParameterizedFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVectorParameterizedFunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataVectorParameterizedFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVectorParameterizedFunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

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
BaseDataObject * DataVectorParameterizedFunctionClass::BaseDataObjectExample()
{ 
  //cout << "Make VectorParameterizedFunction Example\n";
  return (BaseDataObject *) new BaseDataVectorParameterizedFunction();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataVectorParameterizedFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataVectorParameterizedFunctionClass*& obj)
     {
     obj = new DataVectorParameterizedFunctionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataVectorParameterizedFunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataVectorParameterizedFunction*& obj)
     {
     obj = new BaseDataVectorParameterizedFunction;
     return obj->DecodeThis(buffer);
     }
/*S Utilities
 */
/*F InitialSetOfParameterizedEncodeDecodeRoutines() . . parameterized classes
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialVectorOperationsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataFormVectorClass,BaseDataFormVector,VECOPERATION_FORM_NAME);
  EncodeDecodeRegisterClass(DataVectorParameterizedFunctionClass,BaseDataVectorParameterizedFunction,VECOPERATION_REAL_NAME);
}
 
/*F AddParameterizedClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddVectorOperationClasses(DataSetOfObjectsClass& set)
{
  String formdescr("Form a Vector Operation");
  String realdescr("Function Based on Vector Input");
  
  DataFormVectorClass    formclass(VECOPERATION_FORM_ID,VECOPERATION_FORM_NAME,formdescr);
  DataVectorParameterizedFunctionClass    realclass(VECOPERATION_REAL_ID,VECOPERATION_REAL_NAME,realdescr);

  set.AddObjectClass(formclass);
  set.AddObjectClass(realclass);
}
