/*  FILE     VerifyEnvironment.cc
**  PACKAGE  VerifyEnvironment
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "VerifyEnvironment" package.
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
#include "LogicalOperations.hh"
#include "PredicateObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "VerifyEnvironment.hh"

/*S BaseDataVerifyOperation
 */ 
/*F BaseDataVerifyOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataVerifyOperation::BaseDataVerifyOperation()
  : ErrorOperation(NULL),
    CombineOperation(NULL),
    IndividualCutoff(1.0),
    TotalCutOff(0.0)
{
  Identification = VERIFY_OPERATION_ID;
  NameTag = VERIFY_OPERATION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataVerifyOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataVerifyOperation::BaseDataVerifyOperation(const BaseDataVerifyOperation& data)
  : BaseDataOperation(data),
    IndividualCutoff(data.IndividualCutoff),
    TotalCutOff(data.TotalCutOff)
{
  ErrorOperation = (BaseDataVerifyErrorOperation *) PointerClone(data.ErrorOperation);
  CombineOperation = (BaseDataLogicalOperation *) PointerClone(data.CombineOperation);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataVerifyOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataVerifyOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataVerifyOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataVerifyOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  DataVerifyOperationClass *vclass = (DataVerifyOperationClass *) objc;
  String ver("VerifyOperation:");
  CheckReadKeyWord(in,ver);

  StreamObjectInput str(in,' ');

  String ver1("IndividualCutOff:");
  CheckReadKeyWord(in,ver1);
  String icut = str.ReadNext();
  IndividualCutoff = icut.ToFloat();
  String ver2("TotalCutOff:");
  CheckReadKeyWord(in,ver2);
  String tcut = str.ReadNext();
  TotalCutOff = tcut.ToFloat();
  String errnotdefined("Error Operation Not Defined");
  PointerObjectRead(in,(BaseDataObject *&) ErrorOperation,
		    vclass->getErrorOperationClass(),errnotdefined);
  String combnotdefined("Combination Operation Not Defined");
  PointerObjectRead(in,(BaseDataObject *&) CombineOperation,
		    vclass->getCombineOperationClass(),combnotdefined);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataVerifyOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataVerifyOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  PointerPrint(out,"The ErrorOperation: ","Not Defined",ErrorOperation);
  PointerPrint(out,"The CombineOperation: ","Not Defined",CombineOperation);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataVerifyOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataVerifyOperation::Clone()
{
  BaseDataVerifyOperation *obj = new BaseDataVerifyOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataVerifyOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataVerifyOperation::CopyClone(Identify * obj)
{
  BaseDataVerifyOperation *objfull = (BaseDataVerifyOperation *) obj;
  *this = *objfull;
  BaseDataOperation::CopyClone(obj);
  ErrorOperation = (BaseDataVerifyErrorOperation *) PointerClone(objfull->ErrorOperation);
  CombineOperation = (BaseDataLogicalOperation *) PointerClone(objfull->CombineOperation);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVerifyOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVerifyOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Encode(buffer,IndividualCutoff);
  result = result && Encode(buffer,TotalCutOff);
  result = result && PointerEncode(buffer,ErrorOperation);
  result = result && PointerEncode(buffer,CombineOperation);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVerifyOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVerifyOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Decode(buffer,IndividualCutoff);
  result = result && Decode(buffer,TotalCutOff);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ErrorOperation);
  result = result && PointerDecode(buffer,(BaseDataObject *&) CombineOperation);
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
BaseDataObject *BaseDataVerifyOperation::operator()(BaseDataObject *x, BaseDataObject *y,
                                              DataObjectClass *xclass, DataObjectClass *yclass)
                                              
{
  return operator()(x,xclass);
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
BaseDataObject *BaseDataVerifyOperation::operator()(BaseDataObject *x,
						    DataObjectClass *xclass)
{
  BaseDataLogicDescription *logdescr = (BaseDataLogicDescription *) x;
  DataLogicDescriptionClass *logdescrclass = (DataLogicDescriptionClass *) xclass;
  DataLogicalClass *logclass = logdescrclass->getLogicClass();

  BaseDataLogical *log = (BaseDataLogical *) logclass->BaseDataObjectExample();
  BaseDataLogical *flagged = (BaseDataLogical *) logclass->BaseDataObjectExample();
  log->SetAbsoluteTrue();
  flagged->SetAbsoluteFalse();
  BaseDataLogical *ans;

  bool errornotfound = true;
  ObjectList<String> names = logdescr->ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end(); name++)
    {
      BaseDataLogical *next = (BaseDataLogical *) logdescr->GetObject(*name);
      if(next->GetValue() < IndividualCutoff)
	{
	  ErrorOperation->operator()(next,logclass);
	  flagged->SetAbsoluteTrue();
	  errornotfound = false;
	}
      ans = (BaseDataLogical *) CombineOperation->operator()(log,next,logclass,logclass);
      delete log;
      log = ans;
    }
  ans->NameTag = CombineOperation->NameTag;
  if(ans->GetValue() < TotalCutOff && errornotfound)
    {
      ErrorOperation->operator()(logdescr,ans,logdescrclass,logclass);
      flagged->SetAbsoluteTrue();
    }
  delete ans;
  return flagged;
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
BaseDataObject *BaseDataVerifyOperation::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataVerifyOperation::operator()(DataObjectClass *cls,
					      BaseDataObject *x,
                                              DataObjectClass *xclass)
{
  return operator()(x,xclass);
}

/*S DataVerifyOperationClass
 */
/*F DataVerifyOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataVerifyOperationClass::DataVerifyOperationClass()
  : ErrorOperationClass(NULL),
    CombineOperationClass(NULL)
{
  Identification = VERIFY_OPERATION_ID;
  NameTag = VERIFY_OPERATION_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataVerifyOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataVerifyOperationClass::DataVerifyOperationClass(const DataVerifyOperationClass& data)
  : DataOperationClass(data)
{
  ErrorOperationClass = (DataVerifyErrorOperationClass *) PointerClone(data.ErrorOperationClass);
  CombineOperationClass = (DataLogicalOperationClass *) PointerClone(data.CombineOperationClass);
} 
 
/*F DataVerifyOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataVerifyOperationClass::DataVerifyOperationClass(const int id, 
						   const String& name,
						   const String& descr)
  : DataOperationClass(id,name,descr),
    ErrorOperationClass(NULL),
    CombineOperationClass(NULL)
{
  SubClass = "Operation";
  EncodeDecodeClass = VERIFY_OPERATION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataVerifyOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataVerifyOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  PointerPrint(out,"ErrorOperationClass: ","Not Defined",ErrorOperationClass);
  PointerPrint(out,"CombineOperationClass: ","Not Defined",CombineOperationClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataVerifyOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataVerifyOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataVerifyOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) ErrorOperationClass,
				      VERIFY_ERROR_NAME,
				      set," No Class ");
  result = result && PointerClassRead(in,(DataObjectClass *&) CombineOperationClass,
				      LOGICALOP_BASE_NAME,
				      set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataVerifyOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataVerifyOperationClass::CopyClone(Identify *  objc)
{
  DataVerifyOperationClass *objcfull = (DataVerifyOperationClass *) objc;
  *this = *objcfull;
  DataOperationClass::CopyClone(objc);
  ErrorOperationClass = (DataVerifyErrorOperationClass *) PointerClone(objcfull->ErrorOperationClass);
  CombineOperationClass = (DataLogicalOperationClass *) PointerClone(objcfull->CombineOperationClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataVerifyOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataVerifyOperationClass::Clone()
{
  DataVerifyOperationClass* id = new DataVerifyOperationClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataVerifyOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVerifyOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,ErrorOperationClass);
  result = result && PointerEncode(buffer,CombineOperationClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataVerifyOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVerifyOperationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ErrorOperationClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) CombineOperationClass);
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
BaseDataObject * DataVerifyOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataVerifyOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataVerifyOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataVerifyOperationClass*& obj)
     {
     obj = new DataVerifyOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataVerifyOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataVerifyOperation*& obj)
     {
     obj = new BaseDataVerifyOperation;
     return obj->DecodeThis(buffer);
     }
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataVerifyErrorOperationClass *DataVerifyOperationClass::getErrorOperationClass()
{
  return ErrorOperationClass;
}
DataLogicalOperationClass *DataVerifyOperationClass::getCombineOperationClass()
{
  return CombineOperationClass;
}

/*S BaseDataVerifyErrorOperation
 */ 
/*F BaseDataVerifyErrorOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataVerifyErrorOperation::BaseDataVerifyErrorOperation()
{
  Identification = VERIFY_ERROR_ID;
  NameTag = VERIFY_ERROR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataVerifyErrorOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataVerifyErrorOperation::BaseDataVerifyErrorOperation(const BaseDataVerifyErrorOperation& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataVerifyErrorOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataVerifyErrorOperation::Clone()
{
  BaseDataVerifyErrorOperation *obj = new BaseDataVerifyErrorOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataVerifyErrorOperation::CopyClone(Identify * obj)
{
  BaseDataVerifyErrorOperation *objfull = (BaseDataVerifyErrorOperation *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
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
BaseDataObject *BaseDataVerifyErrorOperation::operator()(BaseDataObject *x, BaseDataObject *y,
							 DataObjectClass *xclass, DataObjectClass *yclass)
                                              
{
  BaseDataLogical *log = (BaseDataLogical *) x;
  BaseDataLogicDescription *descr = (BaseDataLogicDescription *) y;
  
  cout << "Combined Total Error using '" << descr->NameTag;
  cout << "' on description '" << log->NameTag << "'" << endl;
  log->WriteAsASCII(cout,xclass);
  cout << endl;
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
BaseDataObject *BaseDataVerifyErrorOperation::operator()(BaseDataObject *x,
							 DataObjectClass *xclass)
{
  BaseDataLogical *log = (BaseDataLogical *) x;
  cout << "Failure in Parameter: ";
  cout << log->NameTag;
  cout << "  with Logic Value: ";
  log->WriteAsASCII(cout,xclass);
  cout << endl;
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
BaseDataObject *BaseDataVerifyErrorOperation::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataVerifyErrorOperation::operator()(DataObjectClass *cls,
					      BaseDataObject *x,
                                              DataObjectClass *xclass)
{
  return operator()(x,xclass);
}

 
/*S DataVerifyErrorOperationClass
 */
/*F DataVerifyErrorOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataVerifyErrorOperationClass::DataVerifyErrorOperationClass()
{
  Identification = VERIFY_ERROR_ID;
  NameTag = VERIFY_ERROR_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataVerifyErrorOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataVerifyErrorOperationClass::DataVerifyErrorOperationClass(const DataVerifyErrorOperationClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataVerifyErrorOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataVerifyErrorOperationClass::DataVerifyErrorOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = VERIFY_ERROR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataVerifyErrorOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataVerifyErrorOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataVerifyErrorOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataVerifyErrorOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataVerifyErrorOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataVerifyErrorOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataVerifyErrorOperationClass::CopyClone(Identify *  objc)
{
  DataVerifyErrorOperationClass *objcfull = (DataVerifyErrorOperationClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataVerifyErrorOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataVerifyErrorOperationClass::Clone()
    {
      DataVerifyErrorOperationClass* id = new DataVerifyErrorOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataVerifyErrorOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVerifyErrorOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataVerifyErrorOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVerifyErrorOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataVerifyErrorOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataVerifyErrorOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataVerifyErrorOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataVerifyErrorOperationClass*& obj)
     {
     obj = new DataVerifyErrorOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataVerifyErrorOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataVerifyErrorOperation*& obj)
     {
     obj = new BaseDataVerifyErrorOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataVerifyErrorAlgorithm
 */ 
/*F BaseDataVerifyErrorAlgorithm()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataVerifyErrorAlgorithm::BaseDataVerifyErrorAlgorithm()
  : VerificationOperationS("VerificationOperation"),
    LogicalDescriptionNamesS("LogicalDescriptionNames"),
    InstanceNamesS("InstanceNames"),
    ErrorInstanceNamesS("ErrorInstanceNames")
{
  Identification = VERIFY_ALGORITHM_ID;
  NameTag = VERIFY_ALGORITHM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataVerifyErrorAlgorithm(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataVerifyErrorAlgorithm::BaseDataVerifyErrorAlgorithm(const BaseDataVerifyErrorAlgorithm& data)
  : BaseDataAlgorithmOperation(data),
    VerificationOperationS(data.VerificationOperationS),
    LogicalDescriptionNamesS(data.LogicalDescriptionNamesS),
    InstanceNamesS(data.InstanceNamesS),
    ErrorInstanceNamesS(data.ErrorInstanceNamesS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataVerifyErrorAlgorithm::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataVerifyErrorAlgorithm::Clone()
{
  BaseDataVerifyErrorAlgorithm *obj = new BaseDataVerifyErrorAlgorithm(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataVerifyErrorAlgorithm::CopyClone(Identify * obj)
{
  BaseDataVerifyErrorAlgorithm *objfull = (BaseDataVerifyErrorAlgorithm *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,VerificationOperationS);
  result = result && Encode(buffer,LogicalDescriptionNamesS);
  result = result && Encode(buffer,InstanceNamesS);
  result = result && Encode(buffer,ErrorInstanceNamesS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataVerifyErrorAlgorithm::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,VerificationOperationS);
  result = result && Decode(buffer,LogicalDescriptionNamesS);
  result = result && Decode(buffer,InstanceNamesS);
  result = result && Decode(buffer,ErrorInstanceNamesS);
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
bool BaseDataVerifyErrorAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances*,
					     DataSetOfInstancesClass*,
					     BaseDataAlgorithmRun* ,
					     DataAlgorithmRunClass*)
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
bool BaseDataVerifyErrorAlgorithm::CheckInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass *runclass)
{
  bool result = true;

  if(run->ParameterInList(InstanceNamesS))
    {
      if(run->ParameterInList(LogicalDescriptionNamesS))
	{
	  if(run->ParameterInList(VerificationOperationS))
	    {
	    }
	  else
	    {
	      cerr << "The List of Instance Names: '" << InstanceNamesS << "' was not in the list of parameters";
	      result = false;
	    }
	}
      else
	{
	  cerr << "The Logic Description Names '" << LogicalDescriptionNamesS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The Verification Operation '" << VerificationOperationS << "' was not in the list of parameters";
      result = false;
    }
  
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
bool BaseDataVerifyErrorAlgorithm::SetUpInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass* rclass)
{
  bool result = true;
  VerificationOperation = (BaseDataVerifyOperation *) run->ParameterValue(VerificationOperationS);
  LogicalDescriptionNames = (BaseDataKeyWords *) run->ParameterValue(LogicalDescriptionNamesS);
  InstanceNames = (BaseDataKeyWords *) run->ParameterValue(InstanceNamesS);
  ErrorInstanceNames = new ObjectList<String>();
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
bool BaseDataVerifyErrorAlgorithm::Calculate(BaseDataSetOfInstances *instances,
				       DataSetOfInstancesClass *instclasses,
				       BaseDataAlgorithmRun *run,
				       DataAlgorithmRunClass *runclass)
{
  bool result = true;
  ObjectList<String> descrnames = LogicalDescriptionNames->GetKeyWords();
  ObjectList<String> instnames  = InstanceNames->GetKeyWords();
  
  if(descrnames.size() > 0)
    {
      String flagname = descrnames.front();
      descrnames.pop_front();
      ObjectList<String>::iterator instname,descrname;
      for(instname = instnames.begin(); instname != instnames.end();instname++)
	{
	  cout << "  ***************   Check Instance: '" << *instname << "' ***************   "<< endl;
	  BaseDataInstance *instance = instances->GetInstance(*instname);
	  for(descrname = descrnames.begin(); descrname != descrnames.end();descrname++)
	    {
	      if(instance->IsInList(*descrname))
		{
		  BaseDataLogicDescription *logdescr = (BaseDataLogicDescription *) instance->GetObject(*descrname);
		  unsigned int dtype = logdescr->GetType();
		  DataLogicDescriptionClass *logdescrclass 
		    = (DataLogicDescriptionClass *) instclasses->GetObjectClass(dtype);
		  BaseDataLogical *ans = (BaseDataLogical *) VerificationOperation->operator()(logdescr,logdescrclass);
		  ans->NameTag = flagname;
		  instance->AddObject(ans);
		  if(ans->GetValue() == 1.0)
		    {
		      ErrorInstanceNames->AddObject(*instname);
		    }
		  delete ans;
		}
	      else
		{
		  cerr << "Description: '" << *descrname << "' not in instance '" << *instname << "'" << endl;
		}
	    }
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
bool BaseDataVerifyErrorAlgorithm::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
{
  bool result = true;
  BaseDataKeyWords *names = new BaseDataKeyWords(*ErrorInstanceNames);
  names->NameTag = ErrorInstanceNamesS;
  run->AddParameter(names);
  delete names;
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
bool BaseDataVerifyErrorAlgorithm::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  delete ErrorInstanceNames;
  return result;
}
 

/*S DataVerifyErrorAlgorithmClass
 */
/*F DataVerifyErrorAlgorithmClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataVerifyErrorAlgorithmClass::DataVerifyErrorAlgorithmClass()
{
  Identification = VERIFY_ALGORITHM_ID;
  NameTag = VERIFY_ALGORITHM_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataVerifyErrorAlgorithmClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataVerifyErrorAlgorithmClass::DataVerifyErrorAlgorithmClass(const DataVerifyErrorAlgorithmClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataVerifyErrorAlgorithmClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataVerifyErrorAlgorithmClass::DataVerifyErrorAlgorithmClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = VERIFY_ALGORITHM_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataVerifyErrorAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataVerifyErrorAlgorithmClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataVerifyErrorAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataVerifyErrorAlgorithmClass, there is no further information.
**
**  REMARKS
**
*/
bool DataVerifyErrorAlgorithmClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataVerifyErrorAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataVerifyErrorAlgorithmClass::CopyClone(Identify *  objc)
{
  DataVerifyErrorAlgorithmClass *objcfull = (DataVerifyErrorAlgorithmClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataVerifyErrorAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataVerifyErrorAlgorithmClass::Clone()
    {
      DataVerifyErrorAlgorithmClass* id = new DataVerifyErrorAlgorithmClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataVerifyErrorAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVerifyErrorAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataVerifyErrorAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataVerifyErrorAlgorithmClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataVerifyErrorAlgorithmClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataVerifyErrorAlgorithm();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataVerifyErrorAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataVerifyErrorAlgorithmClass*& obj)
     {
     obj = new DataVerifyErrorAlgorithmClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataVerifyErrorAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataVerifyErrorAlgorithm*& obj)
     {
     obj = new BaseDataVerifyErrorAlgorithm;
     return obj->DecodeThis(buffer);
     }
/*S Utility
 */
/*F AddBasicAlgorithmClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddBaseVerifyClasses(DataSetOfObjectsClass& set)
{
String opdescr("The Verification Operation Class");
String errdescr("The Error on Verification Class");
String algdescr("The Verification Algorithm Class");

DataVerifyOperationClass opclass(VERIFY_OPERATION_ID,VERIFY_OPERATION_NAME,opdescr);
DataVerifyErrorOperationClass errclass(VERIFY_ERROR_ID,VERIFY_ERROR_NAME,errdescr);
DataVerifyErrorAlgorithmClass algclass(VERIFY_ALGORITHM_ID,VERIFY_ALGORITHM_NAME,algdescr);

set.AddObjectClass(opclass);
set.AddObjectClass(errclass);
set.AddObjectClass(algclass);
}
/*F VerifyEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void VerifyEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataVerifyErrorAlgorithmClass,BaseDataVerifyErrorAlgorithm,VERIFY_ALGORITHM_NAME);
  EncodeDecodeRegisterClass(DataVerifyErrorOperationClass,BaseDataVerifyErrorOperation,VERIFY_ERROR_NAME);
  EncodeDecodeRegisterClass(DataVerifyOperationClass,BaseDataVerifyOperation,VERIFY_OPERATION_NAME);
}
