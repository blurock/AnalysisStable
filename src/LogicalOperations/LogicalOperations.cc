/*  FILE     LogicalOperations.cc
**  PACKAGE  LogicalOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "LogicalOperations" package.
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

/*S BaseDataLogicalOperation
 */ 
/*F BaseDataLogicalOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogicalOperation::BaseDataLogicalOperation()
{
  Identification = LOGICALOP_BASE_ID;
  NameTag = LOGICALOP_BASE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogicalOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogicalOperation::BaseDataLogicalOperation(const BaseDataLogicalOperation& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataLogicalOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataLogicalOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataLogicalOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogicalOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataLogicalOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLogicalOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogicalOperation::Clone()
{
  BaseDataLogicalOperation *obj = new BaseDataLogicalOperation;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogicalOperation::CopyClone(Identify * obj)
{
  BaseDataLogicalOperation *objfull = (BaseDataLogicalOperation *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
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
BaseDataObject *BaseDataLogicalOperation::operator()(BaseDataObject*, BaseDataObject*,
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
BaseDataObject *BaseDataLogicalOperation::operator()(BaseDataObject*,
						     DataObjectClass*)
{
  return NULL;
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
BaseDataObject *BaseDataLogicalOperation::operator()(DataObjectClass *cls,
					      BaseDataObject *x, BaseDataObject *y,
                                              DataObjectClass *xclass, DataObjectClass *yclass)
                                              
{
  return NULL;
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
BaseDataObject *BaseDataLogicalOperation::operator()(DataObjectClass *cls,
					      BaseDataObject *x,
                                              DataObjectClass *xclass)
{
  return NULL;
}
/*S DataLogicalOperationClass
 */
/*F DataLogicalOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicalOperationClass::DataLogicalOperationClass()
{
  Identification = LOGICALOP_BASE_ID;
  NameTag = LOGICALOP_BASE_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicalOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicalOperationClass::DataLogicalOperationClass(const DataLogicalOperationClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataLogicalOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataLogicalOperationClass::DataLogicalOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = LOGICALOP_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataLogicalOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicalOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataLogicalOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicalOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicalOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataLogicalOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicalOperationClass::CopyClone(Identify *  objc)
{
  DataLogicalOperationClass *objcfull = (DataLogicalOperationClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataLogicalOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicalOperationClass::Clone()
    {
      DataLogicalOperationClass* id = new DataLogicalOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataLogicalOperationClass::BaseDataObjectExample()
{ 
  //cout << "Make LogicalOperation Example\n";
  return (BaseDataObject *) new BaseDataLogicalOperation();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataLogicalOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicalOperationClass*& obj)
     {
     obj = new DataLogicalOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogicalOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogicalOperation*& obj)
     {
     obj = new BaseDataLogicalOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataLogicalAND
 */ 
/*F BaseDataLogicalAND()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogicalAND::BaseDataLogicalAND()
{
  Identification = LOGICALOP_AND_ID;
  NameTag = LOGICALOP_AND_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogicalAND(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogicalAND::BaseDataLogicalAND(const BaseDataLogicalAND& data)
  : BaseDataLogicalOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataLogicalAND
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataLogicalAND::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataLogicalAND
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogicalAND::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataLogicalOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataLogicalAND
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLogicalAND::print(ostream& out) const
{
  BaseDataLogicalOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalAND
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogicalAND::Clone()
{
  BaseDataLogicalAND *obj = new BaseDataLogicalAND;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalAND
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogicalAND::CopyClone(Identify * obj)
{
  BaseDataLogicalAND *objfull = (BaseDataLogicalAND *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalAND
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalAND::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalAND
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalAND::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::DecodeThis(buffer);
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
BaseDataObject *BaseDataLogicalAND::operator()(BaseDataObject *obj1, BaseDataObject *obj2,
                                              DataObjectClass*, DataObjectClass*)
                                              
{
  BaseDataLogical *logans = (BaseDataLogical *) obj1->Clone();
  BaseDataLogical *log2 = (BaseDataLogical *) obj2;
  logans->AND(*log2);
  return logans;
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
BaseDataObject *BaseDataLogicalAND::operator()(BaseDataObject *obj,
                                              DataObjectClass*)
{
  return (BaseDataObject *) obj->Clone();
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
BaseDataObject *BaseDataLogicalAND::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataLogicalAND::operator()(DataObjectClass *cls,
					      BaseDataObject *x,
                                              DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataLogicalANDClass
 */
/*F DataLogicalANDClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicalANDClass::DataLogicalANDClass()
{
  Identification = LOGICALOP_AND_ID;
  NameTag = LOGICALOP_AND_NAME;
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicalANDClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicalANDClass::DataLogicalANDClass(const DataLogicalANDClass& data)
  : DataLogicalOperationClass(data)
{
} 
 
/*F DataLogicalANDClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataLogicalANDClass::DataLogicalANDClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataLogicalOperationClass(id,name,descr)
{
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = LOGICALOP_AND_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataLogicalANDClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicalANDClass::print(ostream& out) const
{
  DataLogicalOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataLogicalANDClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicalANDClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicalANDClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataLogicalOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataLogicalANDClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicalANDClass::CopyClone(Identify *  objc)
{
  DataLogicalANDClass *objcfull = (DataLogicalANDClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataLogicalANDClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicalANDClass::Clone()
    {
      DataLogicalANDClass* id = new DataLogicalANDClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalANDClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalANDClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalANDClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalANDClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataLogicalANDClass::BaseDataObjectExample()
{ 
  //cout << "Make LogicalAND Example\n";
  return (BaseDataObject *) new BaseDataLogicalAND();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataLogicalANDClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicalANDClass*& obj)
     {
     obj = new DataLogicalANDClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogicalAND
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogicalAND*& obj)
     {
     obj = new BaseDataLogicalAND;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataLogicalOR
 */ 
/*F BaseDataLogicalOR()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogicalOR::BaseDataLogicalOR()
{
  Identification = LOGICALOP_OR_ID;
  NameTag = LOGICALOP_OR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogicalOR(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogicalOR::BaseDataLogicalOR(const BaseDataLogicalOR& data)
  : BaseDataLogicalOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataLogicalOR
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataLogicalOR::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataLogicalOR
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogicalOR::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataLogicalOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataLogicalOR
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLogicalOR::print(ostream& out) const
{
  BaseDataLogicalOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalOR
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogicalOR::Clone()
{
  BaseDataLogicalOR *obj = new BaseDataLogicalOR;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalOR
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogicalOR::CopyClone(Identify * obj)
{
  BaseDataLogicalOR *objfull = (BaseDataLogicalOR *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalOR
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalOR::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalOR
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalOR::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::DecodeThis(buffer);
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
BaseDataObject *BaseDataLogicalOR::operator()(BaseDataObject *obj1, BaseDataObject *obj2,
                                              DataObjectClass *obj1class, DataObjectClass *obj2class)
                                              
{
  BaseDataLogical *logans = (BaseDataLogical *) obj1->Clone();
  BaseDataLogical *log2 = (BaseDataLogical *) obj2;
  logans->OR(*log2);
  return logans;
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
BaseDataObject *BaseDataLogicalOR::operator()(BaseDataObject *obj,
                                              DataObjectClass *objclass)
{
  return (BaseDataObject *) obj->Clone();
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
BaseDataObject *BaseDataLogicalOR::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataLogicalOR::operator()(DataObjectClass *cls,
					      BaseDataObject *x,
                                              DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataLogicalORClass
 */
/*F DataLogicalORClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicalORClass::DataLogicalORClass()
{
  Identification = LOGICALOP_OR_ID;
  NameTag = LOGICALOP_OR_NAME;
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicalORClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicalORClass::DataLogicalORClass(const DataLogicalORClass& data)
  : DataLogicalOperationClass(data)
{
} 
 
/*F DataLogicalORClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataLogicalORClass::DataLogicalORClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataLogicalOperationClass(id,name,descr)
{
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = LOGICALOP_OR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataLogicalORClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicalORClass::print(ostream& out) const
{
  DataLogicalOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataLogicalORClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicalORClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicalORClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataLogicalOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataLogicalORClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicalORClass::CopyClone(Identify *  objc)
{
  DataLogicalORClass *objcfull = (DataLogicalORClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataLogicalORClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicalORClass::Clone()
    {
      DataLogicalORClass* id = new DataLogicalORClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalORClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalORClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalORClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalORClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataLogicalORClass::BaseDataObjectExample()
{ 
  //cout << "Make LogicalOR Example\n";
  return (BaseDataObject *) new BaseDataLogicalOR();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataLogicalORClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicalORClass*& obj)
     {
     obj = new DataLogicalORClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogicalOR
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogicalOR*& obj)
     {
     obj = new BaseDataLogicalOR;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataLogicalNOT
 */ 
/*F BaseDataLogicalNOT()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogicalNOT::BaseDataLogicalNOT()
{
  Identification = LOGICALOP_NOT_ID;
  NameTag = LOGICALOP_NOT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogicalNOT(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogicalNOT::BaseDataLogicalNOT(const BaseDataLogicalNOT& data)
  : BaseDataLogicalOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataLogicalNOT
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataLogicalNOT::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataLogicalNOT
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogicalNOT::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataLogicalOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataLogicalNOT
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLogicalNOT::print(ostream& out) const
{
  BaseDataLogicalOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalNOT
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogicalNOT::Clone()
{
  BaseDataLogicalNOT *obj = new BaseDataLogicalNOT;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalNOT
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogicalNOT::CopyClone(Identify * obj)
{
  BaseDataLogicalNOT *objfull = (BaseDataLogicalNOT *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalNOT
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalNOT::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalNOT
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalNOT::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::DecodeThis(buffer);
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
BaseDataObject *BaseDataLogicalNOT::operator()(BaseDataObject *obj1, BaseDataObject *obj2,
                                              DataObjectClass *obj1class, DataObjectClass *obj2class)
                                              
{
  BaseDataLogical *logans = (BaseDataLogical *) obj1->Clone();
  logans->NOT();
  return logans;
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
BaseDataObject *BaseDataLogicalNOT::operator()(BaseDataObject *obj,
                                              DataObjectClass *objclass)
{
  BaseDataLogical *logans = (BaseDataLogical *) obj->Clone();
  logans->NOT();
  return (BaseDataObject *) logans;
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
BaseDataObject *BaseDataLogicalNOT::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataLogicalNOT::operator()(DataObjectClass *cls,
					      BaseDataObject *x,
                                              DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataLogicalNOTClass
 */
/*F DataLogicalNOTClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicalNOTClass::DataLogicalNOTClass()
{
  Identification = LOGICALOP_NOT_ID;
  NameTag = LOGICALOP_NOT_NAME;
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicalNOTClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicalNOTClass::DataLogicalNOTClass(const DataLogicalNOTClass& data)
  : DataLogicalOperationClass(data)
{
} 
 
/*F DataLogicalNOTClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataLogicalNOTClass::DataLogicalNOTClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataLogicalOperationClass(id,name,descr)
{
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = LOGICALOP_NOT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataLogicalNOTClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicalNOTClass::print(ostream& out) const
{
  DataLogicalOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataLogicalNOTClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicalNOTClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicalNOTClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataLogicalOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataLogicalNOTClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicalNOTClass::CopyClone(Identify *  objc)
{
  DataLogicalNOTClass *objcfull = (DataLogicalNOTClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataLogicalNOTClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicalNOTClass::Clone()
    {
      DataLogicalNOTClass* id = new DataLogicalNOTClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalNOTClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalNOTClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalNOTClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalNOTClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataLogicalNOTClass::BaseDataObjectExample()
{ 
  //cout << "Make LogicalNOT Example\n";
  return (BaseDataObject *) new BaseDataLogicalNOT();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataLogicalNOTClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicalNOTClass*& obj)
     {
     obj = new DataLogicalNOTClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogicalNOT
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogicalNOT*& obj)
     {
     obj = new BaseDataLogicalNOT;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataNumericPredicate
 */ 
/*F BaseDataNumericPredicate()  . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumericPredicate::BaseDataNumericPredicate()
  : PredicateFunction(NULL),
    LogicClass(NULL)
{
  Identification = LOGICALOP_NUMPRED_ID;
  NameTag = LOGICALOP_NUMPRED_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNumericPredicate(data)  . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumericPredicate::BaseDataNumericPredicate(const BaseDataNumericPredicate& data)
  : BaseDataOperation(data)
{
  PredicateFunction = (BaseDataFuncReal1D *) PointerClone((BaseDataObject *) data.PredicateFunction);
  LogicClass = (DataLogicalClass *) PointerClone((BaseDataObject *) data.LogicClass);
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumericPredicate::BaseDataNumericPredicate(BaseDataFuncReal1D* func,
                                                   DataLogicalClass* log)
{
  PredicateFunction = (BaseDataFuncReal1D *) PointerClone((BaseDataObject *) func);
  LogicClass = (DataLogicalClass *) PointerClone((BaseDataObject *) log);
  Identification = LOGICALOP_NUMPRED_ID;
  NameTag = LOGICALOP_NUMPRED_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumericPredicate::~BaseDataNumericPredicate()
{
  if(PredicateFunction != NULL)
    delete PredicateFunction;
  if(LogicClass != NULL)
    delete LogicClass;
  
  PredicateFunction = NULL;
  LogicClass = NULL;
}

 
/*F Read(in,objc) . . . . . . . . . . . . .  Read in BaseDataNumericPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumericPredicate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . .  Read in BaseDataNumericPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumericPredicate::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  
  if(objc->getDebugLevel() > 2)
    {
      cout << "Read in Predicate:\n";
    }
  
  BaseDataOperation::Read(in,objc,name);
  DataNumericPredicateClass * objclass = (DataNumericPredicateClass *) objc;

  if(objc->getDebugLevel() > 2)
    {
      PointerPrint(cout,"Logic Class: ","No Logic Class",(BaseDataObject *) objclass->LogicClass);
      cout << "\n";
      PointerPrint(cout,"Predicate Function Class: ", "No Predicate Function", 
                   (BaseDataObject *) objclass->PredicateFunction);
      cout << endl;
    }
  
  LogicClass = (DataLogicalClass *) PointerClone((BaseDataObject *) objclass->LogicClass);
  if(objclass->PredicateFunction != NULL)
    {
      if(objc->getDebugLevel() > 2)
        {
          cout << "\nThe predict function class\n";
          objclass->PredicateFunction->print(cout);
          cout << endl;
        }
      PredicateFunction = (BaseDataFuncReal1D *) objclass->PredicateFunction->BaseDataObjectExample();
      if(objc->getDebugLevel() > 2)
        {
          cout << "The empty predicate function\n";
          PredicateFunction->print(cout);
          cout << endl;
        }
      
      result = result && PredicateFunction->Read(in,objclass->PredicateFunction,NameTag);
      if(objc->getDebugLevel() > 1)
        {
          cout << "The Predicate function just read in:\n";
          PredicateFunction->print(cout);
          cout << "\n";
        }
    }
  else
    {
      cout << "Predicate Function Class not defined\n";
      PredicateFunction = 0;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumericPredicate::print(ostream& out) const
{
  cout << "Numeric Predicate:\n";
  
  BaseDataOperation::print(out);

  PointerPrint(cout,"\nPredicate with Logic: ","No Logic Class",(BaseDataObject *) LogicClass);
  PointerPrint(cout,"\nPredicate Function: ", "No Predicate Function", (BaseDataObject *) PredicateFunction);
  out << "\n";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumericPredicate::Clone()
{
  BaseDataNumericPredicate *obj = new BaseDataNumericPredicate;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumericPredicate::CopyClone(Identify * obj)
{
  BaseDataNumericPredicate *objfull = (BaseDataNumericPredicate *) obj;
  
  BaseDataOperation::CopyClone(obj);
  PredicateFunction = (BaseDataFuncReal1D *) PointerClone(objfull->PredicateFunction);
  LogicClass = (DataLogicalClass *) PointerClone((BaseDataObject *) objfull->LogicClass);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericPredicate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  if(PredicateFunction != NULL)
    {
      result = result && Encode(buffer,PredicateFunction->EncodeDecodeClass);
      result = result && PredicateFunction->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  
  if(LogicClass != NULL)
    {
      result = result && Encode(buffer,LogicClass->EncodeDecodeClass);
      result = result && LogicClass->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericPredicate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    result = result && DecodeFromName(result,buffer,name,(Identify *&) PredicateFunction);
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    result = result && DecodeFromName(result,buffer,name,(Identify *&) LogicClass);

  return result;
}
 
/*F log = operator()(x) . . . . . . . . . . . . . evaluate predicate function
**
**  DESCRIPTION
**    x: The numeric value
**    log: The resulting logical value
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericPredicate::operator()(const double x)
{
  double ans = PredicateFunction->operator()(x);
  BaseDataLogical *final = (BaseDataLogical *) LogicClass->BaseDataObjectExample();
  final->SetValue(ans);
  
  return (BaseDataObject *) final;
}
/*F obj = operator()(x) . . . . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    x: The numeric object
**    obj: The logical value
**
**    This is the numeric predicate with one argument.  The Distance 
**    function is evaluated 
**    to yield a number with is then used in the predicate function
**    to yield the logical value.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericPredicate::operator()(BaseDataObject *x,
                                                     DataObjectClass*)
{
  BaseDataNumeric *x1 = (BaseDataNumeric *) x;
  double ans = x1->Distance();
  double value = PredicateFunction->operator()(ans);
  BaseDataLogical *logic = (BaseDataLogical *) LogicClass->BaseDataObjectExample();
  logic->SetValue(value);
  
  return (BaseDataObject *) logic;
}
/*F obj = operator()(x) . . . . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    x: The numeric object
**    obj: The logical value
**
**    This is the numeric predicate with one argument.  The Distance 
**    function is evaluated 
**    to yield a number with is then used in the predicate function
**    to yield the logical value.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericPredicate::operator()(BaseDataObject *log,
                                                     BaseDataObject *x,
                                                     DataObjectClass*,
                                                     DataObjectClass*)
{
  BaseDataLogical *logic = (BaseDataLogical *) log;
  
  BaseDataNumeric *x1 = (BaseDataNumeric *) x;
  double ans = x1->Distance();
  double value = PredicateFunction->operator()(ans);
  logic->SetValue(value);

  return log;
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
BaseDataObject *BaseDataNumericPredicate::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataNumericPredicate::operator()(DataObjectClass *cls,
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
bool BaseDataNumericPredicate::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  BaseDataNumericPredicate *objclass = (BaseDataNumericPredicate *) objc;

  out << "(" << objc->NameTag << ") " << NameTag << " = ";
  PredicateFunction->WriteAsLine(out,(DataObjectClass *) objclass->PredicateFunction);
  out << endl;
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
bool BaseDataNumericPredicate::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  DataNumericPredicateClass *objclass = (DataNumericPredicateClass *) objc;
  bool result = BaseDataOperation::WriteAsASCII(out,objc);
  if(PredicateFunction != NULL)
    result = result && PredicateFunction->WriteAsASCII(out,(DataObjectClass *) objclass->PredicateFunction);
  else
    {
      BaseDataFuncReal1D dummy;
      DataFuncReal1DClass dummyclass;
      result = result && dummy.WriteAsASCII(out,&dummyclass);
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
bool BaseDataNumericPredicate::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  BaseDataNumericPredicate *objclass = (BaseDataNumericPredicate *) objc;
  bool result = true;
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  if(LogicClass != NULL)
    result = result && LogicClass->WriteAsASCII(out);
  else
    {
      out << " (No Logical) ";
    }
  if(PredicateFunction != NULL)
    result = result && PredicateFunction->WriteAsASCII(out,(DataObjectClass *) objclass->PredicateFunction);
  else
    {
      out << " No Operation ";
    }
  out << endl;
  return true;
}

/*S DataNumericPredicateClass
 */
/*F DataNumericPredicateClass() . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumericPredicateClass::DataNumericPredicateClass()
  : PredicateFunction(NULL),
    LogicClass(NULL)
{
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = LOGICALOP_NUMPRED_NAME;
} 
/*F DataNumericPredicateClass(data) . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumericPredicateClass::DataNumericPredicateClass(const DataNumericPredicateClass& data)
  : DataOperationClass(data)
{
  PredicateFunction = (DataFuncReal1DClass *) PointerClone((BaseDataObject *) data.PredicateFunction);
  LogicClass = (DataLogicalClass *) PointerClone((BaseDataObject *) data.LogicClass);
} 
 
/*F DataNumericPredicateClass(id,name,descr)  . . . . . . . . . . constructor
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
DataNumericPredicateClass::DataNumericPredicateClass(const int id, 
                                                     const String& name,
                                                     const String& descr)
  : DataOperationClass(id,name,descr),
    PredicateFunction(NULL),
    LogicClass(NULL)
{
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = LOGICALOP_NUMPRED_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumericPredicateClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  out << "\n          Logical Output: ";
  if(LogicClass != NULL)
    out << LogicClass->NameTag;
  else
    out << "None Specified";

  out << "     Predicate Function: ";
  if(PredicateFunction != NULL)
    out << PredicateFunction->NameTag;
  else
    out << "None Specified";

  out << endl;
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumericPredicateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumericPredicateClass::Read(istream& in,
                                     DataSetOfObjectsClass& set)
{
  bool result = DataOperationClass::Read(in,set);
  
  StreamObjectInput str(in,' ');

  String log = str.ReadNext();
  String fun = str.ReadNext();
  LogicClass = (DataLogicalClass *) set.CloneClassFromName(log);
  PredicateFunction = (DataFuncReal1DClass *) set.CloneClassFromName(fun);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumericPredicateClass::CopyClone(Identify * objc)
{
  DataNumericPredicateClass *objcfull = (DataNumericPredicateClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumericPredicateClass::Clone()
{
  DataNumericPredicateClass* id = new DataNumericPredicateClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericPredicateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);

  if(PredicateFunction != 0)
    {
      result = result && Encode(buffer,PredicateFunction->EncodeDecodeClass);
      result = result && PredicateFunction->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  
  if(LogicClass != 0)
    {
      result = result && Encode(buffer,LogicClass->EncodeDecodeClass);
      result = result && LogicClass->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  

  return result;
}
 
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericPredicateClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);

  String name;
  
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) PredicateFunction);
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) LogicClass);

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
BaseDataObject * DataNumericPredicateClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataNumericPredicate();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumericPredicateClass*& obj)
{
  obj = new DataNumericPredicateClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumericPredicate*& obj)
{
  obj = new BaseDataNumericPredicate;
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
bool DataNumericPredicateClass::WriteAsLine(ostream& out)
{
  bool result = DataOperationClass::WriteAsLine(out);
  
  if(PredicateFunction != NULL)
    out << " " << PredicateFunction->NameTag;
  else
    out << " No Predicate Function Given " << endl;
  if(LogicClass != NULL)
    out << " " << LogicClass->NameTag << endl;
  else
    out << " No Logic Class Given " << endl;

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
bool DataNumericPredicateClass::WriteAsASCII(ostream& out)
{
  bool result = DataOperationClass::WriteAsASCII(out);
  if(PredicateFunction != NULL)
    out << " " << PredicateFunction->NameTag;
  else
    out << " NoPredicateClass " << endl;
  if(LogicClass != NULL)
    out << " " << LogicClass->NameTag << endl;
  else
    out << " NoLogicClass " << endl;
  return result;
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
bool DataNumericPredicateClass::WriteAsLatex(ostream& out)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}
 
/*F setPredicateFunction(func)  . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    func: The function class
**
**  REMARKS
**
*/
void DataNumericPredicateClass::setPredicateFunction(DataFuncReal1DClass *func)
{
  if(PredicateFunction != NULL)
    delete PredicateFunction;
  PredicateFunction = (DataFuncReal1DClass *) func->Clone();
}
 
/*F setLogicClass(logclass) . . . . . . . . . . . . DataNumericPredicateClass
**
**  DESCRIPTION
**    logclass: The logical class
**
**  REMARKS
**
*/
void DataNumericPredicateClass::setLogicClass(DataLogicalClass *logclass)
{
  if(LogicClass != NULL)
    delete LogicClass;
  LogicClass = (DataLogicalClass *) logclass->Clone();
}

/*S BaseDataExactlyEqualPredicate
 */ 
/*F BaseDataExactlyEqualPredicate() . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExactlyEqualPredicate::BaseDataExactlyEqualPredicate()
  : objectToCompare(NULL),
    logicClass(NULL)
{
  Identification = LOGICALOP_EXACTEQPRED_ID;
  NameTag = LOGICALOP_EXACTEQPRED_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataExactlyEqualPredicate(data) . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExactlyEqualPredicate::BaseDataExactlyEqualPredicate(const BaseDataExactlyEqualPredicate& data)
  : BaseDataOperation(data),
    parameterName(data.parameterName)
{
  
  logicClass = (DataLogicalClass *) PointerClone(data.logicClass);
  objectToCompare = PointerClone(data.objectToCompare);
}
/*F BaseDataExactlyEqualPredicate() . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExactlyEqualPredicate::BaseDataExactlyEqualPredicate(String name,
							     BaseDataObject *object,
							     DataLogicalClass *lclass)
  : parameterName(name)
{
  Identification = LOGICALOP_EXACTEQPRED_ID;
  NameTag = LOGICALOP_EXACTEQPRED_NAME;
  SetType(Identification);
  String name1("Object.");
  name1.AppendToEnd(NameTag);
  EncodeDecodeClass = name1;

  objectToCompare = PointerClone(object);
  logicClass      = (DataLogicalClass *) PointerClone(lclass);
} 
/*F Read(in,objc) . . . . . . . . . . . Read in BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataExactlyEqualPredicate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . Read in BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataExactlyEqualPredicate::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);

  DataExactlyEqualPredicateClass *objclass = (DataExactlyEqualPredicateClass *) objc;
  logicClass = (DataLogicalClass *) objclass->logicClass->Clone();
  
  StreamObjectInput str(in,' ');
  String key = str.ReadNext();
  if(key == "ExactlyEqualPredicate:")
    {
      parameterName = str.ReadNext();
      objectToCompare = objclass->objectClass->BaseDataObjectExample();
      objectToCompare->NameTag = objclass->objectClass->NameTag;
      result = result && objectToCompare->Read(in,objclass->objectClass,name);
    }
  else
    {
      cerr << "Expecting: 'ExactlyEqualPredicate:' got '" << key << "'" << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExactlyEqualPredicate::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << "Is " << parameterName << " exactly equal to " << objectToCompare->NameTag << endl;
  objectToCompare->print(out);
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExactlyEqualPredicate::Clone()
{
  BaseDataExactlyEqualPredicate *obj = new BaseDataExactlyEqualPredicate;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExactlyEqualPredicate::CopyClone(Identify * obj)
{
  BaseDataExactlyEqualPredicate *objfull = (BaseDataExactlyEqualPredicate *) obj;

  BaseDataOperation::CopyClone(obj);
  parameterName = objfull->parameterName;
  objectToCompare = PointerClone(objfull->objectToCompare);
  logicClass = (DataLogicalClass *) PointerClone(objfull->logicClass);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExactlyEqualPredicate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);

  result = result && Encode(buffer,parameterName);
  
  if(objectToCompare != 0)
    {
      result = result && Encode(buffer,objectToCompare->EncodeDecodeClass);
      result = result && objectToCompare->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  if(logicClass != 0)
    {
      result = result && Encode(buffer,logicClass->EncodeDecodeClass);
      result = result && logicClass->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExactlyEqualPredicate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);

  result = result && Decode(buffer,parameterName);
  
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) objectToCompare);
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) logicClass);
  
  return result;
}
 
 
/*F obj = operator()(x) . . . . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    x: The numeric object
**    obj: The logical value
**
**    This is the numeric predicate with one argument.  The Distance 
**    function is evaluated 
**    to yield a number with is then used in the predicate function
**    to yield the logical value.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExactlyEqualPredicate::operator()(BaseDataObject *x,
                                                          DataObjectClass*)
{
  BaseDataLogical *logic = (BaseDataLogical *) logicClass->BaseDataObjectExample();

  if(x->operator==(objectToCompare))
    {
      logic->SetValue(1.0);
    }
  else
    {
      logic->SetValue(0.0);
    }
  
  return (BaseDataObject *) logic;
}
/*F obj = operator()(x) . . . . . . . . . . . . . .  BaseDataNumericPredicate
**
**  DESCRIPTION
**    x: The numeric object
**    obj: The logical value
**
**    This is the numeric predicate with one argument.  The Distance 
**    function is evaluated 
**    to yield a number with is then used in the predicate function
**    to yield the logical value.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExactlyEqualPredicate::operator()(BaseDataObject *log,
                                                          BaseDataObject *x,
                                                          DataObjectClass *logclass,
                                                          DataObjectClass *xclass)
{
  BaseDataLogical *logic = (BaseDataLogical *) log;
  BaseDataSetOfObjects* instance = (BaseDataSetOfObjects *) x;
  
  if(instance->IsInList(parameterName)) {
      BaseDataObject *object = instance->GetObject(parameterName);
      if(object->operator==(objectToCompare)) {
	  logic->SetValue(1.0);
	} else {
	  logic->SetValue(0.0);
	}
    }
  else
    {
      /*
      cerr << "Parameter: '" << parameterName << "' for Predicate: '" << NameTag << "' not found ";
      cerr << "in Instance: '" << instance->NameTag << "'";
      cerr << " Returning Logical value of zero\n";
      */
      logic->SetValue(0.0);
    }
  return (BaseDataObject *) logic;
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
BaseDataObject *BaseDataExactlyEqualPredicate::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataExactlyEqualPredicate::operator()(DataObjectClass *cls,
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
bool BaseDataExactlyEqualPredicate::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = true;
  out << "(" << objc->NameTag << ") " << NameTag << " = ";
  out << "Exact Compare: " << parameterName << " and ";
  if(objectToCompare != NULL) 
    out << objectToCompare->NameTag;
  else
    out << " (no object specified) ";
  out << endl;
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
bool BaseDataExactlyEqualPredicate::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  DataExactlyEqualPredicateClass *objclass = (DataExactlyEqualPredicateClass *) objc;
  bool result = BaseDataOperation::WriteAsASCII(out,objc);
  out << "ExactlyEqualPredicate: ";
  out << parameterName << " ";
  if(objectToCompare != NULL)
    {
      result = result && objectToCompare->WriteAsASCII(out,objclass->objectClass);
    }
  else
    {
      BaseDataObject dummy;
      DataObjectClass dummyclass;
      result = result && dummy.WriteAsASCII(out,&dummyclass);
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
bool BaseDataExactlyEqualPredicate::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  DataExactlyEqualPredicateClass *objclass = (DataExactlyEqualPredicateClass *) objc;
  bool result = true;
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  out << " Compare " << parameterName << " with:" << endl;
  if(objectToCompare != NULL)
    {
      out << "object to compare not null" << endl;
      result = objectToCompare->WriteAsASCII(out,objclass->objectClass);
    }
  else
    {
      out << " (No object given) ";
    }
  return result;
}
/*S DataExactlyEqualPredicateClass
 */
/*F DataExactlyEqualPredicateClass()  . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExactlyEqualPredicateClass::DataExactlyEqualPredicateClass()
  : objectClass(NULL),
    logicClass(NULL)
{
  Identification = LOGICALOP_EXACTEQPRED_ID;
  NameTag = LOGICALOP_EXACTEQPRED_NAME;
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataExactlyEqualPredicateClass(data)  . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExactlyEqualPredicateClass::DataExactlyEqualPredicateClass(const DataExactlyEqualPredicateClass& data)
  : DataOperationClass(data),
    objectClass(NULL),
    logicClass(NULL)
{
  objectClass = (DataObjectClass *) PointerClone(data.objectClass);
  logicClass  = (DataLogicalClass *) PointerClone((BaseDataObject *) data.logicClass);
} 
 
/*F DataExactlyEqualPredicateClass(id,name,descr) . . . . . . . . constructor
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
DataExactlyEqualPredicateClass::DataExactlyEqualPredicateClass(const int id, 
                                                               const String& name,
                                                               const String& descr)
  : DataOperationClass(id,name,descr),
    objectClass(0),
    logicClass(0)
{
  SubClass = LOGICALOP_BASE_NAME;
  EncodeDecodeClass = LOGICALOP_EXACTEQPRED_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . .  DataExactlyEqualPredicateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExactlyEqualPredicateClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  out << "\n            ";
  
  if(objectClass != 0 && logicClass != 0)
    out << objectClass->NameTag << " exactly equal (giving logic: " << logicClass->NameTag << ")" << endl;
  else
    {
      out << "Logic and/or Object classes not assigned yet" << endl;
    }
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . .  DataExactlyEqualPredicateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataExactlyEqualPredicateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExactlyEqualPredicateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  StreamObjectInput str(in,' ');

  String log = str.ReadNext();
  String obj = str.ReadNext();
  
  logicClass = (DataLogicalClass *) set.CloneClassFromName(log);
  if(logicClass == NULL)
    {
      cerr << "Logic Class in ExactlyEqualPredicate Class not found: '" << log << "'" << endl;
      result = false;
      objectClass = NULL;
    }
  else
    {
      objectClass = (DataObjectClass *) set.CloneClassFromName(obj);
      if(objectClass == NULL)
	{
	  cerr << "Object Class in ExactlyEqualPredicate Class not found: '" << obj << "'" << endl;
	  result = false;
	  delete logicClass;
	  logicClass = NULL;
	}
    }
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . .  DataExactlyEqualPredicateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExactlyEqualPredicateClass::CopyClone(Identify *  objc)
{
  DataExactlyEqualPredicateClass *objcfull = (DataExactlyEqualPredicateClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . .  DataExactlyEqualPredicateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExactlyEqualPredicateClass::Clone()
{
  DataExactlyEqualPredicateClass* id = new DataExactlyEqualPredicateClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . .  DataExactlyEqualPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExactlyEqualPredicateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);

  if(logicClass != 0)
    {
      result = result && Encode(buffer,logicClass->EncodeDecodeClass);
      result = result && logicClass->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  
  if(objectClass != 0)
    {
      result = result && Encode(buffer,objectClass->EncodeDecodeClass);
      result = result && objectClass->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . .  DataExactlyEqualPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExactlyEqualPredicateClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);

  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) logicClass);

  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) objectClass);

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
BaseDataObject * DataExactlyEqualPredicateClass::BaseDataObjectExample()
{ 
  BaseDataExactlyEqualPredicate *obj = new BaseDataExactlyEqualPredicate();
  obj->NameTag = NameTag;
  obj->SetType(Identification);
  return (BaseDataObject *) obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . .  DataExactlyEqualPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExactlyEqualPredicateClass*& obj)
{
  obj = new DataExactlyEqualPredicateClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . BaseDataExactlyEqualPredicate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExactlyEqualPredicate*& obj)
{
  obj = new BaseDataExactlyEqualPredicate;
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
bool DataExactlyEqualPredicateClass::WriteAsLine(ostream& out)
{
  bool result = DataOperationClass::WriteAsLine(out);
  
  if(objectClass != NULL)
    out << " " << objectClass->NameTag;
  else
    out << " No Object Class Given " << endl;
  if(logicClass != NULL)
    out << " " << logicClass->NameTag << endl;
  else
    out << " No Logic Class Given " << endl;

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
bool DataExactlyEqualPredicateClass::WriteAsASCII(ostream& out)
{
  bool result = DataOperationClass::WriteAsASCII(out);
  if(logicClass != NULL)
    out << " " << logicClass->NameTag << endl;
  else
    out << " No Logic Class Given " << endl;
  if(objectClass != NULL)
    out << " " << objectClass->NameTag;
  else
    out << " No Object Class Given " << endl;

  return result;
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
bool DataExactlyEqualPredicateClass::WriteAsLatex(ostream& out)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}
/*S BaseDataMemberOfKeyWord
 */ 
/*F BaseDataMemberOfKeyWord()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMemberOfKeyWord::BaseDataMemberOfKeyWord()
{
  Identification = LOGICALOP_KEYWORDMEMBER_ID;
  NameTag = LOGICALOP_KEYWORDMEMBER_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataMemberOfKeyWord(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMemberOfKeyWord::BaseDataMemberOfKeyWord(const BaseDataMemberOfKeyWord& data)
  : BaseDataLogicalOperation(data),
    parameterName(data.parameterName),
    KeyWord(data.KeyWord)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMemberOfKeyWord::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMemberOfKeyWord::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataLogicalOperation::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String mem("MemberOfKeyWord:");
  CheckReadKeyWord(in,mem);
  parameterName = str.ReadNext();
  KeyWord = str.ReadNext();
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMemberOfKeyWord::print(ostream& out) const
{
  BaseDataLogicalOperation::print(out);
  out << "Is the keyword '" << KeyWord << "' in the parameter '" << parameterName << "'" << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMemberOfKeyWord::Clone()
{
  BaseDataMemberOfKeyWord *obj = new BaseDataMemberOfKeyWord(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMemberOfKeyWord::CopyClone(Identify * obj)
{
  BaseDataMemberOfKeyWord *objfull = (BaseDataMemberOfKeyWord *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMemberOfKeyWord::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::EncodeThis(buffer);
  result = result && Encode(buffer,parameterName);
  result = result && Encode(buffer,KeyWord);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMemberOfKeyWord::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::DecodeThis(buffer);
  result = result && Decode(buffer,parameterName);
  result = result && Decode(buffer,KeyWord);
  return result;
}
/*F obj = operator()(x,y,xclass,yclass) . . . . . . . . . . BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataMemberOfKeyWord::operator()(BaseDataObject *log, BaseDataObject *x,
						    DataObjectClass *logclass, DataObjectClass *xclass)
{
  BaseDataLogical *logic = (BaseDataLogical *) log;
  BaseDataSetOfObjects* instance = (BaseDataSetOfObjects *) x;
  if(instance->IsInList(parameterName)) {
      BaseDataKeyWords *object = (BaseDataKeyWords *) instance->GetObject(parameterName);
      if(object->KeyWordInList(KeyWord)) {
	  logic->SetValue(1.0);
	} else {
	  logic->SetValue(0.0);
	}
    }
  else
    {
      /*
      cerr << "Parameter: '" << parameterName << "' for Predicate: '" << NameTag << "' not found ";
      cerr << "in Instance: '" << instance->NameTag << "'";
      cerr << " Returning Logical value of zero\n";
      */
      logic->SetValue(0.0);
    }
  return (BaseDataObject *) logic;
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . . . . BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a one-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataMemberOfKeyWord::operator()(BaseDataObject *x,
						    DataObjectClass *xc)
{
  BaseDataLogical *logic = (BaseDataLogical *) new BaseDataLogical();
  BaseDataKeyWords *keys = (BaseDataKeyWords *) x;
  if(keys->KeyWordInList(KeyWord)) {
      logic->SetValue(1.0);
    } else {
      logic->SetValue(0.0);
    }
  return (BaseDataObject *) logic;
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . . . . . . BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**    The cls is used (among other things) to check the input types
**
**  REMARKS
**
*/
BaseDataObject *BaseDataMemberOfKeyWord::operator()(DataObjectClass *cls,
						  BaseDataObject *x, BaseDataObject *y,
						  DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  /*
    DataSetOfObjectsClass *set = (BaseDataSetOfObjects *) cls->PointerToAllowedClasses();
    bool result = true;
    result = result && set->IsOfClass(xc,_NAME);
    result = result && set->IsOfClass(yc,_NAME);
    result = result && (x->GetType() == xc->GetType());
    result = result && (y->GetType() == yc->GetType());
  */
  return operator()(x,y,xc,yc);
}
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . . . . . . BaseDataMemberOfKeyWord
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
BaseDataObject *BaseDataMemberOfKeyWord::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  /*
    DataSetOfObjectsClass *set = (BaseDataSetOfObjects *) cls->PointerToAllowedClasses();
    bool result = true;
    result = result && set->IsOfClass(xc,_NAME);
    result = result && (x->GetType() == xc->GetType());
  */
  return operator()(x,xclass);
}
 
 
/*S DataMemberOfKeyWordClass
 */
/*F DataMemberOfKeyWordClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMemberOfKeyWordClass::DataMemberOfKeyWordClass()
{
  Identification = LOGICALOP_KEYWORDMEMBER_ID;
  NameTag = LOGICALOP_KEYWORDMEMBER_NAME;
  SubClass = "LogicalOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataMemberOfKeyWordClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMemberOfKeyWordClass::DataMemberOfKeyWordClass(const DataMemberOfKeyWordClass& data)
  : DataLogicalOperationClass(data)
{
} 
 
/*F DataMemberOfKeyWordClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMemberOfKeyWordClass::DataMemberOfKeyWordClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataLogicalOperationClass(id,name,descr)
{
  SubClass = "LogicalOperation";
  EncodeDecodeClass = "MemberOfKeyWord";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMemberOfKeyWordClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMemberOfKeyWordClass::print(ostream& out) const
{
  DataLogicalOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMemberOfKeyWordClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMemberOfKeyWordClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMemberOfKeyWordClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataLogicalOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMemberOfKeyWordClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMemberOfKeyWordClass::CopyClone(Identify *  objc)
{
  DataMemberOfKeyWordClass *objcfull = (DataMemberOfKeyWordClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMemberOfKeyWordClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMemberOfKeyWordClass::Clone()
    {
      DataMemberOfKeyWordClass* id = new DataMemberOfKeyWordClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMemberOfKeyWordClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMemberOfKeyWordClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMemberOfKeyWordClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMemberOfKeyWordClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataMemberOfKeyWordClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataMemberOfKeyWord();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMemberOfKeyWordClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMemberOfKeyWordClass*& obj)
     {
     obj = new DataMemberOfKeyWordClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMemberOfKeyWord
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMemberOfKeyWord*& obj)
     {
     obj = new BaseDataMemberOfKeyWord;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataRealToLogic
 */ 
/*F BaseDataRealToLogic()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataRealToLogic::BaseDataRealToLogic()
{
  Identification = LOGICALOP_REALTOLOGIC_ID;
  NameTag = LOGICALOP_REALTOLOGIC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataRealToLogic(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataRealToLogic::BaseDataRealToLogic(const BaseDataRealToLogic& data)
  : BaseDataLogicalOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataRealToLogic
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataRealToLogic::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataRealToLogic
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataRealToLogic::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataLogicalOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataRealToLogic
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataRealToLogic::print(ostream& out) const
{
  BaseDataLogicalOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataRealToLogic
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataRealToLogic::Clone()
{
  BaseDataRealToLogic *obj = new BaseDataRealToLogic(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataRealToLogic
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataRealToLogic::CopyClone(Identify * obj)
{
  BaseDataRealToLogic *objfull = (BaseDataRealToLogic *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealToLogic
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealToLogic::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealToLogic
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealToLogic::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogicalOperation::DecodeThis(buffer);
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
BaseDataObject *BaseDataRealToLogic::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataRealToLogic::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataRealToLogic::operator()(BaseDataObject *x,
					       DataObjectClass *xc)
{
  BaseDataReal *num = (BaseDataReal *) x;
  BaseDataContinuous *logic = new BaseDataContinuous();
  logic->SetValue(num->GetValue());

  return (BaseDataObject *) logic;
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
BaseDataObject *BaseDataRealToLogic::operator()(BaseDataObject *x,
								BaseDataObject *y,
								DataObjectClass *xc,
								DataObjectClass *yc)
{
  cerr << "Error: Real Value to Logic Value expects only one argument" << endl;
  return (BaseDataObject *) x->Clone();
}

 
 
/*S DataRealToLogicClass
 */
/*F DataRealToLogicClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRealToLogicClass::DataRealToLogicClass()
{
  Identification = LOGICALOP_REALTOLOGIC_ID;
  NameTag = LOGICALOP_REALTOLOGIC_NAME;
  SubClass = "LogicalOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataRealToLogicClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRealToLogicClass::DataRealToLogicClass(const DataRealToLogicClass& data)
  : DataLogicalOperationClass(data)
{
} 
 
/*F DataRealToLogicClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataRealToLogicClass::DataRealToLogicClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataLogicalOperationClass(id,name,descr)
{
  SubClass = "LogicalOperation";
  EncodeDecodeClass = LOGICALOP_REALTOLOGIC_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataRealToLogicClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRealToLogicClass::print(ostream& out) const
{
  DataLogicalOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataRealToLogicClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRealToLogicClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRealToLogicClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataLogicalOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataRealToLogicClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRealToLogicClass::CopyClone(Identify *  objc)
{
  DataRealToLogicClass *objcfull = (DataRealToLogicClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataRealToLogicClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRealToLogicClass::Clone()
    {
      DataRealToLogicClass* id = new DataRealToLogicClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealToLogicClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealToLogicClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealToLogicClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealToLogicClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataRealToLogicClass::BaseDataObjectExample()
{ 
  //cout << "Make RealToLogic Example\n";
  return (BaseDataObject *) new BaseDataRealToLogic();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataRealToLogicClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRealToLogicClass*& obj)
     {
     obj = new DataRealToLogicClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataRealToLogic
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataRealToLogic*& obj)
     {
     obj = new BaseDataRealToLogic;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataRealPredicate
 */ 
/*F BaseDataRealPredicate()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataRealPredicate::BaseDataRealPredicate()
{
  Identification = LOGICALOP_REALPRED_ID;
  NameTag = LOGICALOP_REALPRED_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataRealPredicate(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataRealPredicate::BaseDataRealPredicate(const BaseDataRealPredicate& data)
  : BaseDataRealFunctionParameterized(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataRealPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataRealPredicate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataRealPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataRealPredicate::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataRealFunctionParameterized::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataRealPredicate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataRealPredicate::print(ostream& out) const
{
  BaseDataRealFunctionParameterized::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataRealPredicate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataRealPredicate::Clone()
{
  BaseDataRealPredicate *obj = new BaseDataRealPredicate(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataRealPredicate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataRealPredicate::CopyClone(Identify * obj)
{
  BaseDataRealPredicate *objfull = (BaseDataRealPredicate *) obj;
  *this = *objfull;
  BaseDataRealFunctionParameterized::CopyClone(obj);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealPredicate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataRealFunctionParameterized::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealPredicate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataRealFunctionParameterized::DecodeThis(buffer);
  return result;
}
/*S DataRealPredicateClass
 */
/*F DataRealPredicateClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRealPredicateClass::DataRealPredicateClass()
  : LogicClass(NULL)
{
  Identification = LOGICALOP_REALPRED_ID;
  NameTag = LOGICALOP_REALPRED_NAME;
  SubClass = "RealFunctionParameterized";
  EncodeDecodeClass = NameTag;
} 
/*F DataRealPredicateClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRealPredicateClass::DataRealPredicateClass(const DataRealPredicateClass& data)
  : DataRealFunctionParameterizedClass(data)
{
  LogicClass = (DataLogicalClass *) PointerClone(data.LogicClass);
} 
 
/*F DataRealPredicateClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataRealPredicateClass::DataRealPredicateClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataRealFunctionParameterizedClass(id,name,descr),
    LogicClass(NULL)
{
  SubClass = "RealFunctionParameterized";
  EncodeDecodeClass = LOGICALOP_REALPRED_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataRealPredicateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRealPredicateClass::print(ostream& out) const
{
  DataRealFunctionParameterizedClass::print(out);
  out << endl;
  PointerPrint(out,"The Logic Class ","No Logic Class",LogicClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataRealPredicateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRealPredicateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRealPredicateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataRealFunctionParameterizedClass::Read(in,set);
  String logtype(LOGICAL_BASE_NAME);
  String lognotdefined("Logic Class");
  result = result && PointerClassRead(in,(DataObjectClass *&) LogicClass,
				      logtype,set,lognotdefined);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataRealPredicateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRealPredicateClass::CopyClone(Identify *  objc)
{
  DataRealPredicateClass *objcfull = (DataRealPredicateClass *) objc;
  *this = *objcfull;
  LogicClass = (DataLogicalClass *) PointerClone(objcfull->LogicClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataRealPredicateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRealPredicateClass::Clone()
    {
      DataRealPredicateClass* id = new DataRealPredicateClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealPredicateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataRealFunctionParameterizedClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,LogicClass);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealPredicateClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataRealFunctionParameterizedClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) LogicClass);
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
BaseDataObject * DataRealPredicateClass::BaseDataObjectExample()
{ 
  //cout << "Make RealPredicate Example\n";
  return (BaseDataObject *) new BaseDataRealPredicate();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataRealPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRealPredicateClass*& obj)
     {
     obj = new DataRealPredicateClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataRealPredicate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataRealPredicate*& obj)
     {
     obj = new BaseDataRealPredicate;
     return obj->DecodeThis(buffer);
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
BaseDataObject *BaseDataRealPredicate::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataRealPredicate::operator()(DataObjectClass *cls,
					       BaseDataObject *x,
					       BaseDataObject *y,
					       DataObjectClass *xc,
					       DataObjectClass *yc)
{
  /*
  DataRealPredicateClass *predclass = (DataRealPredicateClass *) cls;
  DataLogicalClass *logclass = predclass->getLogicClass();

  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  DataParameterSetClass *setclass = (DataParameterSetClass *) xc;
  BaseDataReal *innum = (BaseDataReal *) y;
  BaseDataLogical *logic = (BaseDataLogical *) logclass->BaseDataObjectExample();
  double v = (double) innum->Distance();
  double result = Operation->operator()(v,objects,setclass);
  logic->SetValue(result);
  return (BaseDataObject *) logic;
  */
  DataRealPredicateClass *predclass = (DataRealPredicateClass *) cls;
  DataLogicalClass *logclass = predclass->getLogicClass();
  BaseDataLogical *logic = (BaseDataLogical *) logclass->BaseDataObjectExample();
  BaseDataReal *num = (BaseDataReal *) BaseDataRealFunctionParameterized::operator()(cls,x,y,xc,yc);
  logic->SetValue(num->GetValue());
  delete num;
  return logic;
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
BaseDataObject *BaseDataRealPredicate::operator()(BaseDataObject *x,
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
BaseDataObject *BaseDataRealPredicate::operator()(BaseDataObject *x,
						  BaseDataObject *y,
						  DataObjectClass *xc,
						  DataObjectClass *yc)
{
  /*
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  DataParameterSetClass *setclass = (DataParameterSetClass *) xc;
  BaseDataReal *innum = (BaseDataReal *) y;
  BaseDataContinuous *logic = new BaseDataContinuous();
  double v = (double) innum->Distance();
  double result = Operation->operator()(v,objects,setclass);
  logic->SetValue(result);
  return (BaseDataObject *) logic;
  */
  BaseDataLogical *logic = new BaseDataContinuous();
  BaseDataReal *num = (BaseDataReal *) BaseDataRealFunctionParameterized::operator()(x,y,xc,yc);
  logic->SetValue(num->GetValue());
  delete num;
  return logic;
}
/*F logclass = getLogicClass()  . . . . . . . . . . . . BaseDataRealPredicate
**
**  DESCRIPTION
**    logclass: The logical class of the answer
**
**  REMARKS
**
*/
DataLogicalClass    *DataRealPredicateClass::getLogicClass()
{
  return LogicClass;
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
void AddLogicalOperationClasses(DataSetOfObjectsClass& set)
{
  String opdescr("Base Logical Operation Class");
  String anddescr("Logical AND Operation Class");
  String ordescr("Logical OR Operation Class");
  String notdescr("Logical NOT Operation Class");
  String preddescr("Numeric Predicate Operation Class");
  String eqpreddescr("Exactly Equal Predicate Class");
  String tologdescr("Convert Real Value to Continuous Logic Value");
  String realdescr("Predicate From Real One Dimensional Function");
  String memkeydescr("The Member of KeyWord Class");

  DataLogicalOperationClass opclass(LOGICALOP_BASE_ID,LOGICALOP_BASE_NAME,opdescr);
  DataLogicalANDClass andclass(LOGICALOP_AND_ID,LOGICALOP_AND_NAME,anddescr);
  DataLogicalORClass orclass(LOGICALOP_OR_ID,LOGICALOP_OR_NAME,ordescr);
  DataLogicalNOTClass notclass(LOGICALOP_NOT_ID,LOGICALOP_NOT_NAME,notdescr);
  DataNumericPredicateClass predclass(LOGICALOP_NUMPRED_ID,LOGICALOP_NUMPRED_NAME,preddescr);
  DataExactlyEqualPredicateClass eqpredclass(LOGICALOP_EXACTEQPRED_ID,LOGICALOP_EXACTEQPRED_NAME,eqpreddescr);
  DataRealToLogicClass tologclass(LOGICALOP_REALTOLOGIC_ID,LOGICALOP_REALTOLOGIC_NAME,tologdescr);
  DataRealPredicateClass realclass(LOGICALOP_REALPRED_ID,LOGICALOP_REALPRED_NAME,realdescr);
  DataMemberOfKeyWordClass memkeyclass(LOGICALOP_KEYWORDMEMBER_ID,LOGICALOP_KEYWORDMEMBER_NAME,memkeydescr);

  set.AddObjectClass(opclass);
  set.AddObjectClass(andclass);
  set.AddObjectClass(orclass);
  set.AddObjectClass(notclass);
  set.AddObjectClass(predclass);
  set.AddObjectClass(eqpredclass);
  set.AddObjectClass(tologclass);
  set.AddObjectClass(realclass);
  set.AddObjectClass(memkeyclass);
}
 
/*F InitialSetOfOperationEncodeDecodeRoutines() . . . . . . . . . . TopDecode
**
**  DESCRIPTION
**    Initialise 'TopDecode' functions in SetOfEncodeDecodeRoutines
**
**  REMARKS
**
*/
extern void InitialSetOfLogicalOperationEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataLogicalOperationClass,BaseDataLogicalOperation,LOGICALOP_BASE_NAME);
  EncodeDecodeRegisterClass(DataLogicalANDClass,BaseDataLogicalAND,LOGICALOP_AND_NAME);
  EncodeDecodeRegisterClass(DataLogicalORClass,BaseDataLogicalOR,LOGICALOP_OR_NAME);
  EncodeDecodeRegisterClass(DataLogicalNOTClass,BaseDataLogicalNOT,LOGICALOP_NOT_NAME);
  EncodeDecodeRegisterClass(DataNumericPredicateClass,BaseDataNumericPredicate,LOGICALOP_NUMPRED_NAME);
  EncodeDecodeRegisterClass(DataExactlyEqualPredicateClass,BaseDataExactlyEqualPredicate,LOGICALOP_EXACTEQPRED_NAME);
  EncodeDecodeRegisterClass(DataRealToLogicClass,BaseDataRealToLogic,LOGICALOP_REALTOLOGIC_NAME);
  EncodeDecodeRegisterClass(DataRealPredicateClass,BaseDataRealPredicate,LOGICALOP_REALPRED_NAME);
  EncodeDecodeRegisterClass(DataMemberOfKeyWordClass,BaseDataMemberOfKeyWord,LOGICALOP_KEYWORDMEMBER_NAME);
}
