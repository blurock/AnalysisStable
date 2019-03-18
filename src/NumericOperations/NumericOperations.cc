/*  FILE     NumericOperations.cc
**  PACKAGE  NumericOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "NumericOperations" package.
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
#include "NumericOperations.hh"
#include "ParameterizedFunction.hh"

/*S BaseDataNumericOperation
 */ 
/*F BaseDataNumericOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumericOperation::BaseDataNumericOperation()
{
  Identification = OPERATION_NUMERIC_ID;
  NameTag = OPERATION_NUMERIC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNumericOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumericOperation::BaseDataNumericOperation(const BaseDataNumericOperation& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataNumericOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumericOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataNumericOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumericOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataNumericOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumericOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataNumericOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumericOperation::Clone()
{
  BaseDataNumericOperation *obj = new BaseDataNumericOperation;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataNumericOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumericOperation::CopyClone(Identify * obj)
{
  BaseDataNumericOperation *objfull = (BaseDataNumericOperation *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNumericOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNumericOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  // The rest

  return result;
}
/*F obj = operator()(x,y) . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    obj: The result
**
**    This is the plus operator.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericOperation::operator()(BaseDataObject* x,
                                              BaseDataObject* y,
                                              DataObjectClass* xclass,
                                              DataObjectClass* yclass)
{
  return (BaseDataObject *) x->Clone();
}
/*F obj = operator()(x) . . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**    This is one-argument call to plus.  It is equivalent to
**    adding zero to the argument.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericOperation::operator()(BaseDataObject* x, DataObjectClass*)
{
  return (BaseDataObject *) x->Clone();
}

 
/*S DataNumericOperationClass
 */
/*F DataNumericOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumericOperationClass::DataNumericOperationClass()
{
  Identification = OPERATION_NUMERIC_ID;
  NameTag = OPERATION_NUMERIC_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataNumericOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumericOperationClass::DataNumericOperationClass(const DataNumericOperationClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataNumericOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataNumericOperationClass::DataNumericOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = OPERATION_NUMERIC_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataNumericOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumericOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataNumericOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumericOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumericOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataNumericOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumericOperationClass::CopyClone(Identify *  objc)
{
  DataNumericOperationClass *objcfull = (DataNumericOperationClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataNumericOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumericOperationClass::Clone()
    {
      DataNumericOperationClass* id = new DataNumericOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataNumericOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataNumericOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataNumericOperationClass::BaseDataObjectExample()
{ 
  //cout << "Make NumericOperation Example\n";
  return (BaseDataObject *) new BaseDataNumericOperation();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataNumericOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumericOperationClass*& obj)
     {
     obj = new DataNumericOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNumericOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumericOperation*& obj)
     {
     obj = new BaseDataNumericOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataNumOpPlus
 */ 
/*F BaseDataNumOpPlus() . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumOpPlus::BaseDataNumOpPlus()
{
  Identification = OPERATION_NUMPLUS_ID;
  NameTag = OPERATION_NUMPLUS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

} 
/*F BaseDataNumOpPlus(data) . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumOpPlus::BaseDataNumOpPlus(const BaseDataNumOpPlus& data)
  : BaseDataOperation(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . Read in BaseDataNumOpPlus
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumOpPlus::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataOperation::Read(in,objc);
  // The rest of the read objects
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . Read in BaseDataNumOpPlus
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumOpPlus::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  // The rest of the read objects
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . BaseDataNumOpPlus
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumOpPlus::print(ostream& out) const
{
  BaseDataOperation::print(out);
  // The rest of the print objects

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . BaseDataNumOpPlus
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumOpPlus::Clone()
{
  BaseDataNumOpPlus *obj = new BaseDataNumOpPlus;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . BaseDataNumOpPlus
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumOpPlus::CopyClone(Identify * obj)
{
  BaseDataNumOpPlus *objfull = (BaseDataNumOpPlus *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . BaseDataNumOpPlus
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpPlus::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . BaseDataNumOpPlus
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpPlus::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);

  return result;
}
/*F obj = operator()(x,y) . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    obj: The result
**
**    This is the plus operator.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpPlus::operator()(BaseDataObject* x,
                                              BaseDataObject* y,
                                              DataObjectClass* xclass,
                                              DataObjectClass* yclass)
{
  if(xclass){}
  if(yclass){}
  
  BaseDataNumeric* x1 = (BaseDataNumeric *) x;
  BaseDataNumeric* y1 = (BaseDataNumeric *) y;
  
  return (BaseDataObject *) x1->operator+(y1);
}
/*F obj = operator()(x) . . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**    This is one-argument call to plus.  It is equivalent to
**    adding zero to the argument.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpPlus::operator()(BaseDataObject* x, DataObjectClass*)
{
  return (BaseDataObject *) x->Clone();
}

/*S DataNumOpPlusClass
 */
/*F DataNumOpPlusClass()  . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumOpPlusClass::DataNumOpPlusClass()
{
} 
/*F DataNumOpPlusClass(data)  . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumOpPlusClass::DataNumOpPlusClass(const DataNumOpPlusClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataNumOpPlusClass(id,name,descr) . . . . . . . . . . . . . . constructor
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
DataNumOpPlusClass::DataNumOpPlusClass(const int id, 
                                       const String& name,
                                       const String& descr)
  : DataOperationClass(id,name,descr)

{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = OPERATION_NUMPLUS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . Dat aNumOpPlusClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumOpPlusClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . .  DataNumOpPlusClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumOpPlusClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumOpPlusClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataOperationClass::Read(in,set);
  // the rest

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . .  DataNumOpPlusClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumOpPlusClass::CopyClone(Identify * objc)
{
  DataNumOpPlusClass *objcfull = (DataNumOpPlusClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . .  DataNumOpPlusClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumOpPlusClass::Clone()
{
  DataNumOpPlusClass* id = new DataNumOpPlusClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  DataNumOpPlusClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpPlusClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  DataNumOpPlusClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpPlusClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataNumOpPlusClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataNumOpPlus();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  DataNumOpPlusClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumOpPlusClass*& obj)
{
  obj = new DataNumOpPlusClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . BaseDataNumOpPlus
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumOpPlus*& obj)
{
  obj = new BaseDataNumOpPlus;
  return obj->DecodeThis(buffer);
}

/*S BaseDataNumOpMinus
 */ 
/*F BaseDataNumOpMinus()  . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumOpMinus::BaseDataNumOpMinus()
{
  Identification = OPERATION_NUMMINUS_ID;
  NameTag = OPERATION_NUMMINUS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNumOpMinus(data)  . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumOpMinus::BaseDataNumOpMinus(const BaseDataNumOpMinus& data)
  : BaseDataOperation(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . .  Read in BaseDataNumOpMinus
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumOpMinus::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataOperation::Read(in,objc);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . .  Read in BaseDataNumOpMinus
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumOpMinus::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . .  BaseDataNumOpMinus
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumOpMinus::print(ostream& out) const
{
  BaseDataOperation::print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . .  BaseDataNumOpMinus
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumOpMinus::Clone()
{
  BaseDataNumOpMinus *obj = new BaseDataNumOpMinus;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . .  BaseDataNumOpMinus
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumOpMinus::CopyClone(Identify * obj)
{
  BaseDataNumOpMinus *objfull = (BaseDataNumOpMinus *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataNumOpMinus
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpMinus::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataNumOpMinus
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpMinus::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  return result;
}
/*F obj = operator()(x,y) . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    obj: The result
**
**    This is the plus operator.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpMinus::operator()(BaseDataObject* x,
                                               BaseDataObject* y,
                                               DataObjectClass*,
                                               DataObjectClass*)
{
  BaseDataNumeric* x1 = (BaseDataNumeric *) x;
  BaseDataNumeric* y1 = (BaseDataNumeric *) y;
  
  return (BaseDataObject *) x1->operator-(y1);
}
/*F obj = operator()(x) . . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**    This is one-argument call to plus.  It is equivalent to
**    adding zero to the argument.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpMinus::operator()(BaseDataObject* x, DataObjectClass*)
{
  return (BaseDataObject *) x->Clone();
}

/*S DataNumOpMinusClass
 */
/*F DataNumOpMinusClass() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumOpMinusClass::DataNumOpMinusClass()
{
} 
/*F DataNumOpMinusClass(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumOpMinusClass::DataNumOpMinusClass(const DataNumOpMinusClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataNumOpMinusClass(id,name,descr)  . . . . . . . . . . . . . constructor
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
DataNumOpMinusClass::DataNumOpMinusClass(const int id, 
                                         const String& name,
                                         const String& descr)
  : DataOperationClass(id,name,descr)

{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = OPERATION_NUMMINUS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . DataNumOpMinusClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumOpMinusClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . DataNumOpMinusClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumOpMinusClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumOpMinusClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataOperationClass::Read(in,set);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . DataNumOpMinusClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumOpMinusClass::CopyClone(Identify * objc)
{
  DataNumOpMinusClass *objcfull = (DataNumOpMinusClass*) objc;
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . DataNumOpMinusClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumOpMinusClass::Clone()
{
  DataNumOpMinusClass* id = new DataNumOpMinusClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . DataNumOpMinusClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpMinusClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . DataNumOpMinusClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpMinusClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataNumOpMinusClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataNumOpMinus();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . DataNumOpMinusClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumOpMinusClass*& obj)
{
  obj = new DataNumOpMinusClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  BaseDataNumOpMinus
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumOpMinus*& obj)
{
  obj = new BaseDataNumOpMinus;
  return obj->DecodeThis(buffer);
}

/*S BaseDataNumOpMultiply
 */ 
/*F BaseDataNumOpMultiply() . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumOpMultiply::BaseDataNumOpMultiply()
{
  Identification = OPERATION_NUMMULT_ID;
  NameTag = OPERATION_NUMMULT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

} 
/*F BaseDataNumOpMultiply(data) . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumOpMultiply::BaseDataNumOpMultiply(const BaseDataNumOpMultiply& data)
  : BaseDataOperation(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . Read in BaseDataNumOpMultiply
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumOpMultiply::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataOperation::Read(in,objc);
  // The rest of the read objects
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . Read in BaseDataNumOpMultiply
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumOpMultiply::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  // The rest of the read objects
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . BaseDataNumOpMultiply
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumOpMultiply::print(ostream& out) const
{
  BaseDataOperation::print(out);
  // The rest of the print objects

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . BaseDataNumOpMultiply
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumOpMultiply::Clone()
{
  BaseDataNumOpMultiply *obj = new BaseDataNumOpMultiply;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . BaseDataNumOpMultiply
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumOpMultiply::CopyClone(Identify * obj)
{
  BaseDataNumOpMultiply *objfull = (BaseDataNumOpMultiply *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . BaseDataNumOpMultiply
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpMultiply::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . BaseDataNumOpMultiply
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpMultiply::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);

  return result;
}
/*F obj = operator()(x,y) . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    obj: The result
**
**    This is the plus operator.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpMultiply::operator()(BaseDataObject* x,
                                                  BaseDataObject* y,
                                                  DataObjectClass* xclass,
                                                  DataObjectClass* yclass)
{
  if(xclass){}
  if(yclass){}
  
  BaseDataNumeric* x1 = (BaseDataNumeric *) x;
  BaseDataNumeric* y1 = (BaseDataNumeric *) y;
  
  return (BaseDataObject *) x1->operator*(y1);
}
/*F obj = operator()(x) . . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**    This is one-argument call to plus.  It is equivalent to
**    adding zero to the argument.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpMultiply::operator()(BaseDataObject* x, DataObjectClass*)
{
  return (BaseDataObject *) x->Clone();
}

/*S DataNumOpMultiplyClass
 */
/*F DataNumOpMultiplyClass()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumOpMultiplyClass::DataNumOpMultiplyClass()
{
} 
/*F DataNumOpMultiplyClass(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumOpMultiplyClass::DataNumOpMultiplyClass(const DataNumOpMultiplyClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataNumOpMultiplyClass(id,name,descr) . . . . . . . . . . . . constructor
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
DataNumOpMultiplyClass::DataNumOpMultiplyClass(const int id, 
                                               const String& name,
                                               const String& descr)
  : DataOperationClass(id,name,descr)

{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = OPERATION_NUMMULT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  DataNumOpMultiplyClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumOpMultiplyClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . .  DataNumOpMultiplyClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumOpMultiplyClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumOpMultiplyClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataOperationClass::Read(in,set);
  // the rest

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . .  DataNumOpMultiplyClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumOpMultiplyClass::CopyClone(Identify * objc)
{
  DataNumOpMultiplyClass *objcfull = (DataNumOpMultiplyClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . .  DataNumOpMultiplyClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumOpMultiplyClass::Clone()
{
  DataNumOpMultiplyClass* id = new DataNumOpMultiplyClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  DataNumOpMultiplyClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpMultiplyClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  DataNumOpMultiplyClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpMultiplyClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataNumOpMultiplyClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataNumOpMultiply();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  DataNumOpMultiplyClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumOpMultiplyClass*& obj)
{
  obj = new DataNumOpMultiplyClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . BaseDataNumOpMultiply
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumOpMultiply*& obj)
{
  obj = new BaseDataNumOpMultiply;
  return obj->DecodeThis(buffer);
}

/*S BaseDataNumOpDivide
 */ 
/*F BaseDataNumOpDivide() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumOpDivide::BaseDataNumOpDivide()
{
  Identification = OPERATION_NUMDIVIDE_ID;
  NameTag = OPERATION_NUMDIVIDE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

} 
/*F BaseDataNumOpDivide(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumOpDivide::BaseDataNumOpDivide(const BaseDataNumOpDivide& data)
  : BaseDataOperation(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . Read in BaseDataNumOpDivide
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumOpDivide::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataOperation::Read(in,objc);
  // The rest of the read objects
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . Read in BaseDataNumOpDivide
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumOpDivide::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  // The rest of the read objects
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . BaseDataNumOpDivide
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumOpDivide::print(ostream& out) const
{
  BaseDataOperation::print(out);
  // The rest of the print objects

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . BaseDataNumOpDivide
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumOpDivide::Clone()
{
  BaseDataNumOpDivide *obj = new BaseDataNumOpDivide;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . BaseDataNumOpDivide
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumOpDivide::CopyClone(Identify * obj)
{
  BaseDataNumOpDivide *objfull = (BaseDataNumOpDivide *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . BaseDataNumOpDivide
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpDivide::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . BaseDataNumOpDivide
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumOpDivide::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);

  return result;
}
/*F obj = operator()(x,y) . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    obj: The result
**
**    This is the plus operator.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpDivide::operator()(BaseDataObject* x,
                                                BaseDataObject* y,
                                                DataObjectClass* xclass,
                                                DataObjectClass* yclass)
{
  if(xclass){}
  if(yclass){}
  
  BaseDataNumeric* x1 = (BaseDataNumeric *) x;
  BaseDataNumeric* y1 = (BaseDataNumeric *) y;
  
  return (BaseDataObject *) x1->operator/(y1);
}
/*F obj = operator()(x) . . . . . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**    This is one-argument call to plus.  It is equivalent to
**    adding zero to the argument.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumOpDivide::operator()(BaseDataObject* x, DataObjectClass*)
{
  return (BaseDataObject *) x->Clone();
}

/*S DataNumOpDivideClass
 */
/*F DataNumOpDivideClass()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumOpDivideClass::DataNumOpDivideClass()
{
} 
/*F DataNumOpDivideClass(data)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumOpDivideClass::DataNumOpDivideClass(const DataNumOpDivideClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataNumOpDivideClass(id,name,descr) . . . . . . . . . . . . . constructor
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
DataNumOpDivideClass::DataNumOpDivideClass(const int id, 
                                           const String& name,
                                           const String& descr)
  : DataOperationClass(id,name,descr)

{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = OPERATION_NUMDIVIDE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  DataNumOpDivideClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumOpDivideClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . .  DataNumOpDivideClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumOpDivideClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumOpDivideClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataOperationClass::Read(in,set);
  // the rest

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . .  DataNumOpDivideClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumOpDivideClass::CopyClone(Identify * objc)
{
  DataNumOpDivideClass *objcfull = (DataNumOpDivideClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . .  DataNumOpDivideClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumOpDivideClass::Clone()
{
  DataNumOpDivideClass* id = new DataNumOpDivideClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  DataNumOpDivideClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpDivideClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  DataNumOpDivideClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumOpDivideClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataNumOpDivideClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataNumOpDivide();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  DataNumOpDivideClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumOpDivideClass*& obj)
{
  obj = new DataNumOpDivideClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . BaseDataNumOpDivide
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumOpDivide*& obj)
{
  obj = new BaseDataNumOpDivide;
  return obj->DecodeThis(buffer);
}
/*S BaseDataNumericLineSegmentFunction
 */ 
/*F BaseDataNumericLineSegmentFunction()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumericLineSegmentFunction::BaseDataNumericLineSegmentFunction()
{
  Identification = OPERATION_LINESEGMENTS_ID;
  NameTag = OPERATION_LINESEGMENTS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNumericLineSegmentFunction(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumericLineSegmentFunction::BaseDataNumericLineSegmentFunction(const BaseDataNumericLineSegmentFunction& data)
  : BaseDataNumericOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumericLineSegmentFunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumericLineSegmentFunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataNumericOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumericLineSegmentFunction::print(ostream& out) const
{
  BaseDataNumericOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumericLineSegmentFunction::Clone()
{
  BaseDataNumericLineSegmentFunction *obj = new BaseDataNumericLineSegmentFunction;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumericLineSegmentFunction::CopyClone(Identify * obj)
{
  BaseDataNumericLineSegmentFunction *objfull = (BaseDataNumericLineSegmentFunction *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericLineSegmentFunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumericOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericLineSegmentFunction::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumericOperation::DecodeThis(buffer);
  // The rest

  return result;
}
/*F obj = operator()(x,y,xclass,yclass) . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a dummy two-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericLineSegmentFunction::operator()(BaseDataObject*, BaseDataObject*,
							       DataObjectClass*, DataObjectClass*)
                                              
{
  return NULL;
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a dummy one-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericLineSegmentFunction::operator()(BaseDataObject *obj,
							       DataObjectClass *objclass)
{
  bool result = true;
  BaseDataParameterSet *set = (BaseDataParameterSet *) obj;
  BaseDataReal *answer = new BaseDataReal();

  BaseDataReal *xstartobj,*x,*ystartobj,*y;
  double xstart,ystart,xdiff,ydiff;
  ObjectList<String> names = set->OrderedListOfParameterNames();
  ObjectList<String>::iterator name = names.begin();
  
  BaseDataReal *xvalueobj = (BaseDataReal *) set->GetObject(*name);
  double xvalue = xvalueobj->GetValue();
  cout << "BaseDataNumericLineSegmentFunction: The Input Parameter" << endl;
  xvalueobj->print(cout);
  cout << endl;

  name++;
  if(name != names.end())
    {
      xstartobj = (BaseDataReal *) set->GetObject(*name);
      xstart = xstartobj->GetValue();
      name++;
      if(name != names.end())
	{
	  ystartobj = (BaseDataReal *) set->GetObject(*name);
	  ystart = ystartobj->GetValue();
	  name++;
	}
      else result = false;
    }
  else result = false;

  
  bool notdone = true;

  if(result && xvalue < xstart)
    {
      notdone = false;
      answer->SetValue(ystart);
    }

  while(result && notdone && name != names.end())
    {
      x = (BaseDataReal *) set->GetObject(*name);
      xdiff = x->GetValue();
      name++;
      if(name != names.end())
	{
	  y = (BaseDataReal *) set->GetObject(*name);
	  ydiff = y->GetValue();
	  name++;
	  if(xvalue < xstart + xdiff)
	    {
	      double yvalue = ystart + (xvalue - xstart)*ydiff/xdiff;
	      cout << NameTag << ":   F(" << xvalue << ") = " << yvalue << endl;
	      answer->SetValue(yvalue);
	      notdone = false;
	    }
	}
      else result = false;
    }
  if(!result)
    {
      cerr << "Error in LineSegmentFunction evaluation" << endl;
    }
  return (BaseDataObject *) answer;
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a dummy two-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericLineSegmentFunction::operator()(DataObjectClass *cls,
							       BaseDataObject *x, BaseDataObject *y,
							       DataObjectClass *xclass, DataObjectClass *yclass)
                                              
{
  return operator()(x,y,xclass,yclass);
}
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    cls: The class of the operation
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a dummy one-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericLineSegmentFunction::operator()(DataObjectClass *cls,
							       BaseDataObject *x,
							       DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataNumericLineSegmentFunctionClass
 */
/*F DataNumericLineSegmentFunctionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumericLineSegmentFunctionClass::DataNumericLineSegmentFunctionClass()
{
  Identification = OPERATION_LINESEGMENTS_ID;
  NameTag = OPERATION_LINESEGMENTS_NAME;
  SubClass = "NumericOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataNumericLineSegmentFunctionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumericLineSegmentFunctionClass::DataNumericLineSegmentFunctionClass(const DataNumericLineSegmentFunctionClass& data)
  : DataNumericOperationClass(data)
{
} 
 
/*F DataNumericLineSegmentFunctionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataNumericLineSegmentFunctionClass::DataNumericLineSegmentFunctionClass(const int id, 
									 const String& name,
									 const String& descr)
  : DataNumericOperationClass(id,name,descr)
{
  SubClass = "NumericOperation";
  EncodeDecodeClass = OPERATION_LINESEGMENTS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataNumericLineSegmentFunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumericLineSegmentFunctionClass::print(ostream& out) const
{
  DataNumericOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataNumericLineSegmentFunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumericLineSegmentFunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumericLineSegmentFunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataNumericOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataNumericLineSegmentFunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumericLineSegmentFunctionClass::CopyClone(Identify *  objc)
{
  DataNumericLineSegmentFunctionClass *objcfull = (DataNumericLineSegmentFunctionClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataNumericLineSegmentFunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumericLineSegmentFunctionClass::Clone()
    {
      DataNumericLineSegmentFunctionClass* id = new DataNumericLineSegmentFunctionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataNumericLineSegmentFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericLineSegmentFunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataNumericOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataNumericLineSegmentFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericLineSegmentFunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataNumericOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataNumericLineSegmentFunctionClass::BaseDataObjectExample()
{ 
  //cout << "Make NumericLineSegmentFunction Example\n";
  return (BaseDataObject *) new BaseDataNumericLineSegmentFunction();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataNumericLineSegmentFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumericLineSegmentFunctionClass*& obj)
     {
     obj = new DataNumericLineSegmentFunctionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNumericLineSegmentFunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumericLineSegmentFunction*& obj)
     {
     obj = new BaseDataNumericLineSegmentFunction;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataLogicToReal
 */ 
/*F BaseDataLogicToReal()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogicToReal::BaseDataLogicToReal()
{
  Identification = OPERATION_LOGTOREAL_ID;
  NameTag = OPERATION_LOGTOREAL_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogicToReal(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogicToReal::BaseDataLogicToReal(const BaseDataLogicToReal& data)
  : BaseDataNumericOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataLogicToReal
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataLogicToReal::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataLogicToReal
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogicToReal::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataNumericOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataLogicToReal
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLogicToReal::print(ostream& out) const
{
  BaseDataNumericOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicToReal
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogicToReal::Clone()
{
  BaseDataLogicToReal *obj = new BaseDataLogicToReal(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicToReal
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogicToReal::CopyClone(Identify * obj)
{
  BaseDataLogicToReal *objfull = (BaseDataLogicToReal *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicToReal
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicToReal::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumericOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicToReal
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicToReal::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumericOperation::DecodeThis(buffer);
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
BaseDataObject *BaseDataLogicToReal::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataLogicToReal::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataLogicToReal::operator()(BaseDataObject *x,
					       DataObjectClass *xc)
{
  BaseDataLogical *logic = (BaseDataLogical *) x;
  BaseDataReal *num = new BaseDataReal();
  num->SetValue(logic->GetValue());
  return (BaseDataObject *) num;
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
BaseDataObject *BaseDataLogicToReal::operator()(BaseDataObject *x,
								BaseDataObject *y,
								DataObjectClass *xc,
								DataObjectClass *yc)
{
  cerr << "Error: Logic to Real Conversion takes only one argument" << endl;
  return (BaseDataObject *) x->Clone();
}

 
 
/*S DataLogicToRealClass
 */
/*F DataLogicToRealClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicToRealClass::DataLogicToRealClass()
{
  Identification = OPERATION_LOGTOREAL_ID;
  NameTag = OPERATION_LOGTOREAL_NAME;
  SubClass = "NumericOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicToRealClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicToRealClass::DataLogicToRealClass(const DataLogicToRealClass& data)
  : DataNumericOperationClass(data)
{
} 
 
/*F DataLogicToRealClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataLogicToRealClass::DataLogicToRealClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataNumericOperationClass(id,name,descr)
{
  SubClass = "NumericOperation";
  EncodeDecodeClass = OPERATION_LOGTOREAL_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataLogicToRealClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicToRealClass::print(ostream& out) const
{
  DataNumericOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataLogicToRealClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicToRealClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicToRealClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataNumericOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataLogicToRealClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicToRealClass::CopyClone(Identify *  objc)
{
  DataLogicToRealClass *objcfull = (DataLogicToRealClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataLogicToRealClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicToRealClass::Clone()
    {
      DataLogicToRealClass* id = new DataLogicToRealClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicToRealClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicToRealClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataNumericOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicToRealClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicToRealClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataNumericOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataLogicToRealClass::BaseDataObjectExample()
{ 
  //cout << "Make LogicToReal Example\n";
  return (BaseDataObject *) new BaseDataLogicToReal();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataLogicToRealClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicToRealClass*& obj)
     {
     obj = new DataLogicToRealClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogicToReal
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogicToReal*& obj)
     {
     obj = new BaseDataLogicToReal;
     return obj->DecodeThis(buffer);
     }

/*S Utilities
 */
/*F AddOperationClasses(set)  . . . . . . . . . standard operation data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddNumericOperationClasses(DataSetOfObjectsClass& set)
{
  String numopdescr("Numeric Operation Class");
  String plusdescr("Numeric Plus Operation Class");
  String minusdescr("Numeric Minus Operation Class");
  String multdescr("Numeric Multiply Operation Class");
  String dividedescr("Numeric Divide Operation Class");
  String segdescr("Line Segment Function Class");
  String logdescr("Convert a Logical Value to a Real Value");
  
  DataNumOpPlusClass numopclass(OPERATION_NUMERIC_ID,OPERATION_NUMERIC_NAME,numopdescr);
  DataNumOpPlusClass plusclass(OPERATION_NUMPLUS_ID,OPERATION_NUMPLUS_NAME,plusdescr);
  DataNumOpMinusClass minusclass(OPERATION_NUMMINUS_ID,OPERATION_NUMMINUS_NAME,minusdescr);
  DataNumOpMultiplyClass multclass(OPERATION_NUMMULT_ID,OPERATION_NUMMULT_NAME,multdescr);
  DataNumOpDivideClass divideclass(OPERATION_NUMDIVIDE_ID,OPERATION_NUMDIVIDE_NAME,dividedescr);
  DataNumericLineSegmentFunctionClass  segclass(OPERATION_LINESEGMENTS_ID,OPERATION_LINESEGMENTS_NAME,segdescr);
  DataLogicToRealClass logclass(OPERATION_LOGTOREAL_ID,OPERATION_LOGTOREAL_NAME,logdescr);

  set.AddObjectClass(numopclass);
  set.AddObjectClass(plusclass);
  set.AddObjectClass(minusclass);
  set.AddObjectClass(multclass);
  set.AddObjectClass(divideclass);
  set.AddObjectClass(segclass);
  set.AddObjectClass(logclass);
}
 
/*F InitialSetOfNumericOperationEncodeDecodeRoutines() . . . . . . . . . . TopDecode
**
**  DESCRIPTION
**    Initialise 'TopDecode' functions in SetOfEncodeDecodeRoutines
**
**  REMARKS
**
*/
extern void InitialSetOfNumericOperationEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataNumericOperationClass,BaseDataNumericOperation,OPERATION_NUMERIC_NAME);
  EncodeDecodeRegisterClass(DataNumOpPlusClass,BaseDataNumOpPlus,OPERATION_NUMPLUS_NAME);
  EncodeDecodeRegisterClass(DataNumOpMinusClass,BaseDataNumOpMinus,OPERATION_NUMMINUS_NAME);
  EncodeDecodeRegisterClass(DataNumOpMultiplyClass,BaseDataNumOpMultiply,OPERATION_NUMMULT_NAME);
  EncodeDecodeRegisterClass(DataNumOpDivideClass,BaseDataNumOpDivide,OPERATION_NUMDIVIDE_NAME);
  EncodeDecodeRegisterClass(DataNumericLineSegmentFunctionClass,BaseDataNumericLineSegmentFunction,OPERATION_LINESEGMENTS_NAME);
  EncodeDecodeRegisterClass(DataLogicToRealClass,BaseDataLogicToReal,OPERATION_LOGTOREAL_NAME);
}
