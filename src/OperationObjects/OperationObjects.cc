/*  FILE     OperationObjects.cc
**  PACKAGE  OperationObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "OperationObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
** Version 1.5
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"


/*S BaseDataOperation
 */ 
/*F BaseDataOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOperation::BaseDataOperation()
{
  Identification = OPERATION_BASE_ID;
  NameTag = OPERATION_BASE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

} 
/*F BaseDataOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataOperation::BaseDataOperation(const BaseDataOperation& data)
  : BaseDataObject(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataOperation::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataObject::Read(in,objc);
  // The rest of the read objects
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  // The rest of the read objects
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataOperation::print(ostream& out) const
{
  BaseDataObject::print(out);
  // The rest of the print objects

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataOperation::Clone()
{
  BaseDataOperation *obj = new BaseDataOperation;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataOperation::CopyClone(Identify * obj)
{
  BaseDataOperation *objfull = (BaseDataOperation *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);

  return result;
}
/*F obj = operator()(x,set,xclass,classset) . . . . .  From name do operation
**
**  DESCRIPTION
**    x1: The name of the variable (from set of Objects)
**    set: The set of objects
**    xclass: The name of the class of the variable
**    classset: The set of classes
**    obj: The output object
**
**    The names are used to get the values.  The routine is then called with these values
**
**  REMARKS
**
*/
BaseDataObject* BaseDataOperation::operator()(const String& x,
                                              BaseDataSetOfObjects& set,
                                              const String& xclass,
                                              DataSetOfObjectsClass& classset)
{
  BaseDataObject* x1 = set.GetObject(x);
  DataObjectClass *xclass1 = classset.PointerToAllowedClasses()->GetObjectClass(xclass);
  
  return operator()(x1,xclass1);
}
/*F obj = operator()(x,y,set,xclass,yclass,classset)   From name do operation
**
**  DESCRIPTION
**    x1,x2: The names of the variables (from set of Objects)
**    set: The set of objects
**    xclass,yclass: The set of classes
**    obj: The output object
**
**    The names are used to get the values.  The routine is then called with these values
**
**  REMARKS
**
*/
BaseDataObject* BaseDataOperation::operator()(const String& x, const String& y,
                                              BaseDataSetOfObjects& set,
                                              const String& xclass, const String& yclass,
                                              DataSetOfObjectsClass& classset)
{
  BaseDataObject* x1 = set.GetObject(x);
  BaseDataObject* x2 = set.GetObject(y);
  DataObjectClass *xclass1 = classset.PointerToAllowedClasses()->GetObjectClass(xclass);
  DataObjectClass *yclass1 = classset.PointerToAllowedClasses()->GetObjectClass(yclass);
  return operator()(x1,x2,xclass1,yclass1);
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
BaseDataObject *BaseDataOperation::operator()(BaseDataObject*, BaseDataObject*,
                                              DataObjectClass*, DataObjectClass*)
                                              
{
  return new BaseDataObject;
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
BaseDataObject *BaseDataOperation::operator()(BaseDataObject*,
                                              DataObjectClass*)
{
  return new BaseDataObject;
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
BaseDataObject *BaseDataOperation::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataOperation::operator()(DataObjectClass *cls,
					      BaseDataObject *x,
                                              DataObjectClass *xclass)
{
  return operator()(x,xclass);
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
bool BaseDataOperation::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag << " = ";  
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
bool BaseDataOperation::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  return BaseDataObject::WriteAsASCII(out,objc);
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
bool BaseDataOperation::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  out << endl;
  return true;
}

/*S DataOperationClass
 */
/*F DataOperationClass()  . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataOperationClass::DataOperationClass()
{
} 
/*F DataOperationClass(data)  . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataOperationClass::DataOperationClass(const DataOperationClass& data)
  : DataObjectClass(data)
  // the rest
{
} 
 
/*F DataOperationClass(id,name,descr) . . . . . . . . . . . . . . constructor
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
DataOperationClass::DataOperationClass(const int id, 
                                       const String& name,
                                       const String& descr)
  : DataObjectClass(id,name,descr)

{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = OPERATION_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . .  DataOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataOperationClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . .  DataOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataOperationClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);
  // the rest

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . .  DataOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataOperationClass::CopyClone(Identify * objc)
{
  DataOperationClass *objcfull = (DataOperationClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . .  DataOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataOperationClass::Clone()
{
  DataOperationClass* id = new DataOperationClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  DataOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  DataOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataOperationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);

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
BaseDataObject * DataOperationClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataOperation();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  DataOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataOperationClass*& obj)
{
  obj = new DataOperationClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataOperation*& obj)
{
  obj = new BaseDataOperation;
  return obj->DecodeThis(buffer);
}
/*F ans = WriteAsLine(out)  . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool DataOperationClass::WriteAsLine(ostream& out)
{
  out << NameTag << ": " << Description << endl;
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
bool DataOperationClass::WriteAsASCII(ostream& out)
{
  return DataObjectClass::WriteAsASCII(out);
}
/*F ans = WriteAsLatex(out) . . . . . . . . . . . . . . . . . DataObjectClass
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
bool DataOperationClass::WriteAsLatex(ostream& out)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}
/*S Utility
 */
 
/*F AddOperationClasses(set)  . . . . . . . . . standard operation data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddOperationClasses(DataSetOfObjectsClass& set)
{
  String opdescr("Base Operation Class");
  DataOperationClass opclass(OPERATION_BASE_ID,OPERATION_BASE_NAME,opdescr);
  set.AddObjectClass(opclass);
}
 
/*F InitialSetOfOperationEncodeDecodeRoutines() . . . . . . . . . . TopDecode
**
**  DESCRIPTION
**    Initialise 'TopDecode' functions in SetOfEncodeDecodeRoutines
**
**  REMARKS
**
*/
extern void InitialSetOfOperationEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataOperationClass,BaseDataOperation,OPERATION_BASE_NAME);
}
