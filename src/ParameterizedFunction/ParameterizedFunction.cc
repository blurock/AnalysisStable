/*  FILE     ParameterizedFunction.cc
**  PACKAGE  ParameterizedFunction
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "ParameterizedFunction" package.
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
#include "DataObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "InstanceObjects.hh"

#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "EvaluationTree.hh"
#include "ExpressionTree.hh"
#include "ParameterizedFunction.hh"
#include "FunctionReal1DObjects.hh"

//#define DEBUG_LEVEL1
 
/*S BaseDataParameterSet
 */ 
/*F BaseDataParameterSet()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParameterSet::BaseDataParameterSet()
{
  Identification = PARAMETERIZED_SET_ID;
  NameTag = PARAMETERIZED_SET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  ParameterList.ChangeTitle("Parameter List -> ");
  ParameterList.ChangeDelimitor(" ");
  String title("----------- Set of Parameters ----------------\n");
  String delimitor("\n");
  setTitle(title);
  setDelimitor(delimitor);
} 
/*F BaseDataParameterSet(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataParameterSet::BaseDataParameterSet(const BaseDataParameterSet& data)
  : BaseDataSetOfObjects(data),
    ParameterList(data.ParameterList)
{
}

/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataParameterSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataParameterSet::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataParameterSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool  BaseDataParameterSet::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result;
  DataParameterSetClass *setclass = (DataParameterSetClass *) objc;
#ifdef DEBUG_LEVEL1
  cout << "------------------------- Read in ParameterSet ------------------------" << endl;
  setclass->ParameterSetKeys.print(cout);
  cout << endl << "----------------------------------------------------------------------------" << endl;
#endif
  if(setclass->ParameterSetKeys.SizeOf() == 0) {
#ifdef DEBUG_LEVEL1
    cout << "No Keys" << endl;
#endif
    setclass->ReadClassPairs = true;
    setclass->ReadAllowedClasses = false;
    result = setclass->ReadInClassNamePairs(in);
    //result = setclass->Read(in, *setclass);
    result = result && BaseDataSetOfObjects::Read(in,setclass,name);
    ObjectNameClassPairs pairs =  setclass->getNameClassPairs();
    ParameterList = pairs.ObjectNames;
  } else if(setclass->ParameterSetKeys.KeyWordInList(NoReadKeyWord)){
#ifdef DEBUG_LEVEL1
    cout << "No Read" << endl;
#endif
    result = true;
  } else if(setclass->ParameterSetKeys.KeyWordInList(PlaceHoldersKeyWord)){
#ifdef DEBUG_LEVEL1
    cout << "PlaceHolders" << endl;
#endif
    if(!setclass->ParameterSetKeys.KeyWordInList(NoClassNamePairsKeyWord)) 
      result = setclass->ReadInClassNamePairs(in);
    else
      result = setclass->ReadInClassNamePairsWithoutKeyWord(in);

    ObjectNameClassPairs pairs =  setclass->getNameClassPairs();
    ParameterList = pairs.ObjectNames;
  } else {
    if(setclass->ParameterSetKeys.KeyWordInList(ReadAsTripletKeyWord)) {
      ReadAsTriplet(in,setclass);
      ParameterList = ListOfObjectNames();
    } else {
      if(!setclass->ParameterSetKeys.KeyWordInList(NoClassNamePairsKeyWord)) 
	result = setclass->ReadInClassNamePairs(in);
      else
	result = setclass->ReadInClassNamePairsWithoutKeyWord(in);
      result = result && BaseDataSetOfObjects::Read(in,setclass,name);
      ObjectNameClassPairs pairs =  setclass->getNameClassPairs();
      ParameterList = pairs.ObjectNames;
    }
  }    
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataParameterSet
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataParameterSet::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  ParameterList.print(out);
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterSet
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataParameterSet::Clone()
{
  BaseDataParameterSet *obj = new BaseDataParameterSet(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterSet
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataParameterSet::CopyClone(Identify * obj)
{
  BaseDataParameterSet *objfull = (BaseDataParameterSet *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterSet::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && ParameterList.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterSet::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && ParameterList.DecodeThis(buffer);
  return result;
}
 
/*F ans = Add(obj)  . . . . . . . . . . . . . . . . . . add ordered parameter
**
**  DESCRIPTION
**    obj: The object to add to parameter set
**    ans: True if successful
**
**    This add parameter to 'SetOfObjects', the parameter list of names and to the
**    name class pairs of the class
**
**  REMARKS
**
*/
bool BaseDataParameterSet::AddObject(BaseDataObject *obj)
{
  if(obj->NameTag.size() == 0) {
    cerr << "Fatal Error with add object" << endl;
    obj->print(cerr);
    exit(1);
  }
  bool result = BaseDataSetOfObjects::AddObject(obj);
  ParameterList.AddObjectIfNotThere(obj->NameTag);
  return result;
}
 
/*F OrderedListOfParameterNames() . . . . . . . . . . . . . .  parameter list
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ObjectList<String>& BaseDataParameterSet::OrderedListOfParameterNames()
{
  return ParameterList;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . .  BaseDataParameterSet
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
bool BaseDataParameterSet::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "ParameterSet: ";
  ParameterList.print(out);
  out << " ";
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
bool BaseDataParameterSet::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = true;
  DataObjectClass *cls;
  DataParameterSetClass *objclass = (DataParameterSetClass *) objc;
  DataSetOfObjectsClass *set = objclass->PointerToAllowedClasses();
  ObjectList<String> names = ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = names.begin();name != names.end() && result;name++)
    {
      out << "Parameter: " << *name << endl;
      if(IsInList(*name))
	{
	  BaseDataObject *obj = BaseDataSetOfObjects::GetObject(*name);
	  unsigned int otype = obj->GetType();
	  cls = set->GetObjectClass(otype);
	  result = result && obj->WriteAsASCII(out,cls);
	  out << endl;
	}
      else
	{
	  out << "Parameter: " << *name << "not set up yet" << endl;
	  result = false;
	}
    }
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . .  BaseDataSetOfObjects
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
bool BaseDataParameterSet::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  return BaseDataSetOfObjects::WriteAsLatex(out,objc);
}
/*S DataParameterSetClass
 */
/*F DataParameterSetClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataParameterSetClass::DataParameterSetClass()
{
  Identification = PARAMETERIZED_SET_ID;
  NameTag = PARAMETERIZED_SET_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataParameterSetClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataParameterSetClass::DataParameterSetClass(const DataParameterSetClass& data)
  : DataSetOfObjectsClass(data),
    ParameterSetKeys(data.ParameterSetKeys)
{
} 
 
/*F DataParameterSetClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataParameterSetClass::DataParameterSetClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = PARAMETERIZED_SET_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataParameterSetClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataParameterSetClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  out << "Parameter Set Keys: ";
  ParameterSetKeys.print(out);
  out << endl;
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataParameterSetClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataParameterSetClass, there is no further information.
**
**  REMARKS
**
*/
bool DataParameterSetClass::Read(istream& in, DataSetOfObjectsClass &set)
{
#ifdef DEBUG_LEVEL1
  cout << "------------------------- Read in ParameterSet Class ------------------------" << endl;
#endif
  //ReadClassPairs = false;
  //ReadAllowedClasses = false;
  //bool result = DataSetOfObjectsClass::Read(in,set);
  DataKeyWordsClass keyclass;
  bool result = ParameterSetKeys.Read(in,&keyclass,keyclass.NameTag);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataParameterSetClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataParameterSetClass::CopyClone(Identify *  objc)
{
  DataParameterSetClass *objcfull = (DataParameterSetClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataParameterSetClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataParameterSetClass::Clone()
    {
      DataParameterSetClass* id = new DataParameterSetClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterSetClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  ParameterSetKeys.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterSetClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  ParameterSetKeys.DecodeThis(buffer);
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
BaseDataObject * DataParameterSetClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataParameterSet();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataParameterSetClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataParameterSetClass*& obj)
     {
     obj = new DataParameterSetClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataParameterSet
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataParameterSet*& obj)
     {
     obj = new BaseDataParameterSet;
     return obj->DecodeThis(buffer);
     }
/*F classes = PointerToAllowedClasses() . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    classes: The set of classes
**
**    This in the default case points to itself (this).  
**    It is meant for the case where the set of standard objects
**    is some external (possibly global) object.
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataParameterSetClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*S BaseDataParameterizedFunction
 */ 
/*F BaseDataParameterizedFunction()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParameterizedFunction::BaseDataParameterizedFunction()
  : ParameterSet(NULL),
    Operation(NULL),
    ParametersWithOperation(true)
{
  Identification = PARAMETERIZED_FUNCTION_ID;
  NameTag = PARAMETERIZED_FUNCTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataParameterizedFunction(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataParameterizedFunction::BaseDataParameterizedFunction(const BaseDataParameterizedFunction& data)
  : BaseDataOperation(data),
    ParametersWithOperation(data.ParametersWithOperation)
{
  ParameterSet = (BaseDataParameterSet *) PointerClone(data.ParameterSet);
  Operation    = (BaseDataOperation *) PointerClone(data.Operation);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataParameterizedFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F BaseDataParameterizedFunction()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParameterizedFunction::~BaseDataParameterizedFunction()
{
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataParameterizedFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  DataParameterizedFunctionClass *objcfull = (DataParameterizedFunctionClass *) objc;
  String pnotdefined("Parameter Class not defined");
  String opnotdefined("Operation Class not defined");
  String ParameterSetKeyWord("ParameterSet:");
  String OperationKeyWord("Operation:");
  String ParamFunctionNoKeyWordsKeyWord("NoKeyWords");
  if(!objcfull->FunctionKeys.KeyWordInList(ParamFunctionNoKeyWordsKeyWord))
    result = result && CheckReadKeyWord(in,ParameterSetKeyWord);

  DataParameterSetClass *setclass = objcfull->getParameterClass();
#ifdef DEBUG_LEVEL1 
  cout << endl << "-----------Parameter Class in BaseDataParameterizedFunction::Read" << endl;
  setclass->print(cout);
  cout << endl << "-----------------------------------------------------------------" << endl;
#endif
  result = result && PointerObjectRead(in,(BaseDataObject *&) ParameterSet,
				       setclass,pnotdefined);
  if(!objcfull->FunctionKeys.KeyWordInList(ParamFunctionNoKeyWordsKeyWord))
    result = result && CheckReadKeyWord(in,OperationKeyWord);
  result = result && PointerObjectRead(in,(BaseDataObject *&) Operation,
				       objcfull->getOperationClass(),
				       opnotdefined);
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataParameterizedFunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataParameterizedFunction::print(ostream& out) const
{
  BaseDataOperation::print(out);
  PointerPrint(out,"ParameterSet: ","Parameter set not defined",ParameterSet);
  PointerPrint(out,"Operation: ","Operation not defined",Operation);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterizedFunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataParameterizedFunction::Clone()
{
  BaseDataParameterizedFunction *obj = new BaseDataParameterizedFunction(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterizedFunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataParameterizedFunction::CopyClone(Identify * obj)
{
  BaseDataParameterizedFunction *objfull = (BaseDataParameterizedFunction *) obj;
  *this = *objfull;
  BaseDataOperation::CopyClone(obj);
  ParameterSet = (BaseDataParameterSet *) PointerClone(objfull->ParameterSet);
  Operation    = (BaseDataOperation *) PointerClone(objfull->Operation);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterizedFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  PointerEncode(buffer,ParameterSet);
  PointerEncode(buffer,Operation);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterizedFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  PointerDecode(buffer,(BaseDataObject *&) ParameterSet);
  PointerDecode(buffer,(BaseDataObject *&) Operation);
  return result;
}
 
/*F ans = InsertParameterSet(objects) . . . .  set up parameters for function
**
**  DESCRIPTION
**    objects: The set of parameters
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::InsertParameterSet(BaseDataParameterSet *objects)
{
  return InsertParameterSet(objects,false);
}
/*F ans = InsertParameterSet(objects) . . . .  set up parameters for function
**
**  DESCRIPTION
**    objects: The set of parameters
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::InsertParameterSet(BaseDataParameterSet *objects,
						       bool addobject) {
  bool result = true;
  if(ParametersWithOperation) {
      ObjectList<String> names = ParameterSet->ListOfObjectNames();
      ObjectList<String>::iterator name;
      for(name = names.begin();name != names.end();name++) {
	if(objects->IsInList(*name)) {
	     BaseDataObject *obj = objects->GetObject(*name);
	     result = result && InsertParameter(obj);
	     if(addobject)
	       result = result && ParameterSet->AddObject(obj);
	   }
	}
    }
  return result;
}
/*F ans = InsertParameterSet(objects) . . . .  set up parameters for function
**
**  DESCRIPTION
**    objects: The set of parameters
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::InsertParameterSet()
{
  bool result = true;
  ObjectList<String> names = ParameterSet->ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = names.begin();name != names.end();name++)
    {
      BaseDataObject *obj = ParameterSet->GetObject(*name);
      result = result && InsertParameter(obj);
    }
  return result;
}
/*F ans = InsertParameter(obj)
**
**  DESCRIPTION
**    obj: The parameter to insert in the list of parameters
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedFunction::InsertParameter(BaseDataObject *obj) {
  return true;
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
BaseDataObject *BaseDataParameterizedFunction::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataParameterizedFunction::operator()(DataObjectClass *cls,
							  BaseDataObject *x,
							  BaseDataObject *y,
							  DataObjectClass *xc,
							  DataObjectClass *yc)
{
  DataParameterizedFunctionClass *funcclass = (DataParameterizedFunctionClass *) cls;
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  InsertParameterSet(objects,true);
  BaseDataObject *obj = Operation->operator()(ParameterSet,y,funcclass->getParameterClass(),yc);
  return obj;
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
BaseDataObject *BaseDataParameterizedFunction::operator()(BaseDataObject *x,
							  DataObjectClass *xc)
{
  //BaseDataObject *obj = Operation->operator()(x,xc);
  //return obj;
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
BaseDataObject *BaseDataParameterizedFunction::operator()(BaseDataObject *x,
							  BaseDataObject *y,
							  DataObjectClass *xc,
							  DataObjectClass *yc)
{
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  InsertParameterSet(objects,true);
  BaseDataObject *obj = Operation->operator()(ParameterSet,y,xc,yc);
  return obj;
}
/*F op = getOperation() . . . . . . . . . . . . . .  get pointer to operation
**
**  DESCRIPTION
**    op: The Parameterized operation
**
**  REMARKS
**
*/
BaseDataOperation *BaseDataParameterizedFunction::getOperation()
{
  return Operation;
}
/*F op = getParameterSet() . . . . . . . . . . . . . .  get pointer to operation
**
**  DESCRIPTION
**    op: The Parameterized operation
**
**  REMARKS
**
*/
BaseDataParameterSet *BaseDataParameterizedFunction::getParameterSet()
{
  return ParameterSet;
}
 
/*F setParameterSet(params) . . . . . . . . . . BaseDataParameterizedFunction
**
**  DESCRIPTION
**    params: The parameters to set
**
**  REMARKS
**
*/
void BaseDataParameterizedFunction::setParameterSet(BaseDataParameterSet *params)
{
  if(ParameterSet != NULL)
    delete ParameterSet;
  ParameterSet = (BaseDataParameterSet *) params->Clone();
}
 
/*F setOperation(op)  . . . . . . . . . . . . . BaseDataParameterizedFunction
**
**  DESCRIPTION
**    op: The operation to insert
**
**  REMARKS
**
*/
void BaseDataParameterizedFunction::setOperation(BaseDataOperation *op)
{
  if(Operation != NULL)
    delete Operation;
  Operation = (BaseDataOperation *) op->Clone();
}
/*F InsertParametersWithOperation()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataParameterizedFunction::InsertParametersWithOperation()
{
  ParametersWithOperation = true;
}
 
/*F DontInsertParametersWithOperation()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataParameterizedFunction::DontInsertParametersWithOperation()
{
  ParametersWithOperation = false;
}
/*S DataParameterizedFunctionClass
 */
/*F DataParameterizedFunctionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataParameterizedFunctionClass::DataParameterizedFunctionClass()
  : ParameterClass(NULL),
    OperationClass(NULL),
    OutputClass(NULL)
{
  Identification = PARAMETERIZED_FUNCTION_ID;
  NameTag = PARAMETERIZED_FUNCTION_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataParameterizedFunctionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataParameterizedFunctionClass::DataParameterizedFunctionClass(const DataParameterizedFunctionClass& data)
  : DataOperationClass(data),
    FunctionKeys(data.FunctionKeys)
{
  ParameterClass = (DataParameterSetClass *) PointerClone(data.ParameterClass);
  OperationClass = (DataOperationClass *) PointerClone(data.OperationClass);
  OutputClass = (DataObjectClass *) PointerClone(data.OutputClass);
} 
 
/*F DataParameterizedFunctionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataParameterizedFunctionClass::DataParameterizedFunctionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr),
    ParameterClass(NULL),
    OperationClass(NULL),
    OutputClass(NULL)
{
  SubClass = "Operation";
  EncodeDecodeClass = PARAMETERIZED_FUNCTION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataParameterizedFunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataParameterizedFunctionClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  PointerPrint(out,"Parameter Class:","No Parameter Class defined",ParameterClass);       
  PointerPrint(out,"Operation Class:","No Operation Class defined",OperationClass);       
  PointerPrint(out,"Output Class:","No Output Class defined",OutputClass);
  FunctionKeys.print(out);
  return out;
}
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataParameterizedFunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataParameterizedFunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataParameterizedFunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
#ifdef DEBUG_LEVEL1
  cout << "Begin: Parameterized Function Read" << endl;
#endif
  String par("SetOfObjects");
  String op("Operation");
  result = result && PointerClassRead(in,(DataObjectClass *&) ParameterClass,par,set,par);
#ifdef DEBUG_LEVEL1
  cout << "Parameter Class:" << ParameterClass->NameTag << endl;
#endif
  result = result && PointerClassRead(in,(DataObjectClass *&) OperationClass,op,set,op);
#ifdef DEBUG_LEVEL1
  cout << "Operation Class:" << OperationClass->NameTag << endl;
#endif
  result = result && PointerClassRead(in,(DataObjectClass *&) OutputClass,
				      "Object",set,"Output Class");
#ifdef DEBUG_LEVEL1
  cout << "Output Class:" << OutputClass->NameTag << endl;
#endif
  DataKeyWordsClass keyclass;
  result = result && FunctionKeys.Read(in,&keyclass,keyclass.NameTag);
#ifdef DEBUG_LEVEL1
  cout << "FunctionKeys:" << endl;
  FunctionKeys.print(cout); 
  cout << endl;
  cout << "End: Parameterized Function Read" << endl;
#endif

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataParameterizedFunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataParameterizedFunctionClass::CopyClone(Identify *  objc)
{
  DataParameterizedFunctionClass *objcfull = (DataParameterizedFunctionClass *) objc;
  *this = *objcfull;
  DataOperationClass::CopyClone(objc);
  ParameterClass = (DataParameterSetClass *) PointerClone(objcfull->ParameterClass);
  OperationClass = (DataOperationClass *) PointerClone(objcfull->OperationClass);
  OutputClass = (DataObjectClass *) PointerClone(objcfull->OutputClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataParameterizedFunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataParameterizedFunctionClass::Clone()
    {
      DataParameterizedFunctionClass* id = new DataParameterizedFunctionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterizedFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterizedFunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ParameterClass);
  result = result && PointerEncode(buffer,(BaseDataObject *&) OperationClass);
  result = result && PointerEncode(buffer,(BaseDataObject *&) OutputClass);
  result = result && FunctionKeys.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterizedFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterizedFunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ParameterClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) OperationClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) OutputClass);
  result = result && FunctionKeys.DecodeThis(buffer);
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
BaseDataObject * DataParameterizedFunctionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataParameterizedFunction();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataParameterizedFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataParameterizedFunctionClass*& obj)
     {
     obj = new DataParameterizedFunctionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataParameterizedFunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataParameterizedFunction*& obj)
     {
     obj = new BaseDataParameterizedFunction;
     return obj->DecodeThis(buffer);
     }
 
/*F parclass = getParameterClass() parameter class
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataParameterSetClass *DataParameterizedFunctionClass::getParameterClass()
{
  return ParameterClass;
}
/*F opclass = getOperationClass() . . . . . . . . . . . . . . parameter class
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataOperationClass *DataParameterizedFunctionClass::getOperationClass()
{
  return OperationClass;
}
/*S BaseDataRealFunctionParameterized
 */ 
/*F BaseDataRealFunctionParameterized()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataRealFunctionParameterized::BaseDataRealFunctionParameterized()
  : Operation(NULL)
{
  Identification = PARAMETERIZED_REALFUNC_ID;
  NameTag = PARAMETERIZED_REALFUNC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataRealFunctionParameterized(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataRealFunctionParameterized::BaseDataRealFunctionParameterized(const BaseDataRealFunctionParameterized& data)
  : BaseDataOperation(data)
{
  Operation = (BaseDataFuncReal1D *) PointerClone(data.Operation);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataRealFunctionParameterized::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataRealFunctionParameterized::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  DataRealFunctionParameterizedClass *funcclass = (DataRealFunctionParameterizedClass *) objc;
  String errorm("Real Function not Defined");
  result = result && PointerObjectRead(in,(BaseDataObject *&) Operation,funcclass->getOperationClass(),errorm);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataRealFunctionParameterized::print(ostream& out) const
{
  BaseDataOperation::print(out);
  PointerPrint(out,"Operation: "," No Operation Defined",Operation);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataRealFunctionParameterized::Clone()
{
  BaseDataRealFunctionParameterized *obj = new BaseDataRealFunctionParameterized(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataRealFunctionParameterized::CopyClone(Identify * obj)
{
  BaseDataRealFunctionParameterized *objfull = (BaseDataRealFunctionParameterized *) obj;  
  *this = *objfull;
  BaseDataOperation::CopyClone(obj);
  Operation = (BaseDataFuncReal1D *) PointerClone(objfull->Operation);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealFunctionParameterized::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  PointerEncode(buffer,(BaseDataObject *&) Operation);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealFunctionParameterized::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  PointerDecode(buffer,(BaseDataObject *&) Operation);
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
BaseDataObject *BaseDataRealFunctionParameterized::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataRealFunctionParameterized::operator()(DataObjectClass *cls,
							  BaseDataObject *x,
							  BaseDataObject *y,
							  DataObjectClass *xc,
							  DataObjectClass *yc)
{
  /*
  BaseDataReal *outnum = new BaseDataReal();
  if(Operation != NULL)
    {
      BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
      DataParameterSetClass *setclass = (DataParameterSetClass *) xc;
      BaseDataNumeric *innum = (BaseDataNumeric *) y;
      double v = (double) innum->Distance();
      double result = Operation->operator()(v,objects,setclass);
      outnum->SetValue(result);
    }
  else
    {
      cerr << "Operation not defined yet" << endl;    
    }
  */
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
BaseDataObject *BaseDataRealFunctionParameterized::operator()(BaseDataObject *x,
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
BaseDataObject *BaseDataRealFunctionParameterized::operator()(BaseDataObject *x,
							      BaseDataObject *y,
							      DataObjectClass *xc,
							      DataObjectClass *yc)
{
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  DataParameterSetClass *setclass = (DataParameterSetClass *) xc;
  BaseDataReal *innum = (BaseDataReal *) y;
  BaseDataReal *outnum = new BaseDataReal();
  double v = (double) innum->Distance();
  double result = Operation->operator()(v,objects,setclass);
  outnum->SetValue(result);
  return (BaseDataObject *) outnum;
}
/*S DataRealFunctionParameterizedClass
 */
/*F DataRealFunctionParameterizedClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRealFunctionParameterizedClass::DataRealFunctionParameterizedClass()
  : OperationClass(NULL)
{
  Identification = PARAMETERIZED_REALFUNC_ID;
  NameTag = PARAMETERIZED_REALFUNC_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataRealFunctionParameterizedClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRealFunctionParameterizedClass::DataRealFunctionParameterizedClass(const DataRealFunctionParameterizedClass& data)
  : DataOperationClass(data)
{
  OperationClass = (DataFuncReal1DClass *) PointerClone(data.OperationClass);
} 
/*F DataRealFunctionParameterizedClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataRealFunctionParameterizedClass::DataRealFunctionParameterizedClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr),
    OperationClass(NULL)
{
  SubClass = "Operation";
  EncodeDecodeClass = PARAMETERIZED_REALFUNC_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataRealFunctionParameterizedClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRealFunctionParameterizedClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataRealFunctionParameterizedClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRealFunctionParameterizedClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRealFunctionParameterizedClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  PointerClassRead(in,(DataObjectClass *&) OperationClass,ODREALFUNC_BASE_NAME,set,"Class type not defined");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataRealFunctionParameterizedClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRealFunctionParameterizedClass::CopyClone(Identify *  objc)
{
  DataRealFunctionParameterizedClass *objcfull = (DataRealFunctionParameterizedClass *) objc;
  *this = *objcfull;
  DataOperationClass::CopyClone(objc);
  OperationClass = (DataFuncReal1DClass *) PointerClone(objcfull->OperationClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataRealFunctionParameterizedClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRealFunctionParameterizedClass::Clone()
    {
      DataRealFunctionParameterizedClass* id = new DataRealFunctionParameterizedClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealFunctionParameterizedClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealFunctionParameterizedClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  PointerEncode(buffer,(BaseDataObject *&) OperationClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealFunctionParameterizedClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealFunctionParameterizedClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  PointerDecode(buffer,(BaseDataObject *&) OperationClass);
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
BaseDataObject * DataRealFunctionParameterizedClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataRealFunctionParameterized();
  obj->SetType(Identification);
  return obj;
  
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataRealFunctionParameterizedClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRealFunctionParameterizedClass*& obj)
     {
     obj = new DataRealFunctionParameterizedClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataRealFunctionParameterized
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataRealFunctionParameterized*& obj)
     {
     obj = new BaseDataRealFunctionParameterized;
     return obj->DecodeThis(buffer);
     }
 
/*F opclass = getOperationClass() . . . . . . . . . . . . . . . . the pointer
**
**  DESCRIPTION
**    opclass: The class of the function
**
**  REMARKS
**
*/
DataFuncReal1DClass *DataRealFunctionParameterizedClass::getOperationClass()
{
  return OperationClass;
}
/*S BaseDataParameterSetOperation
 */ 
/*F BaseDataParameterSetOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParameterSetOperation::BaseDataParameterSetOperation()
  : ParameterCount(0)
{
  Identification = PARAMETERIZED_SETOP_ID;
  NameTag = PARAMETERIZED_SETOP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataParameterSetOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataParameterSetOperation::BaseDataParameterSetOperation(const BaseDataParameterSetOperation& data)
  : BaseDataOperation(data),
    ParameterCount(0)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataParameterSetOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataParameterSetOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataParameterSetOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataParameterSetOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataParameterSetOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataParameterSetOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterSetOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataParameterSetOperation::Clone()
{
  BaseDataParameterSetOperation *obj = new BaseDataParameterSetOperation;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterSetOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataParameterSetOperation::CopyClone(Identify * obj)
{
  BaseDataParameterSetOperation *objfull = (BaseDataParameterSetOperation *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterSetOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterSetOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterSetOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterSetOperation::DecodeThis(CommBuffer& buffer)
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
BaseDataObject *BaseDataParameterSetOperation::operator()(BaseDataObject *x, BaseDataObject *y,
							  DataObjectClass *xclass, DataObjectClass *yclass)
                                              
{
  BaseDataParameterSet *set = (BaseDataParameterSet *) x;
  ParameterCount++;
  String par("_P");
  String name(y->NameTag);
  String count = Int2String(ParameterCount);
  name.AppendToEnd(par);
  name.AppendToEnd(count);
  String oldname(y->NameTag);
  y->NameTag = name;
  set->AddObject(y);
  y->NameTag = oldname;
  return (BaseDataObject *) set;
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
BaseDataObject *BaseDataParameterSetOperation::operator()(BaseDataObject *x,
							  DataObjectClass *xclass)
{
  BaseDataParameterSet *set = new BaseDataParameterSet();
  ParameterCount = 0;
  String par("_P");
  String name(x->NameTag);
  String count = Int2String(ParameterCount);
  name.AppendToEnd(par);
  name.AppendToEnd(count);
  String oldname(x->NameTag);
  x->NameTag = name;
  set->AddObject(x);
  x->NameTag = oldname;
  return set;
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
BaseDataObject *BaseDataParameterSetOperation::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataParameterSetOperation::operator()(DataObjectClass *cls,
							  BaseDataObject *x,
							  DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataParameterSetOperationClass
 */
/*F DataParameterSetOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataParameterSetOperationClass::DataParameterSetOperationClass()
{
  Identification = PARAMETERIZED_SETOP_ID;
  NameTag = PARAMETERIZED_SETOP_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataParameterSetOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataParameterSetOperationClass::DataParameterSetOperationClass(const DataParameterSetOperationClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataParameterSetOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataParameterSetOperationClass::DataParameterSetOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = PARAMETERIZED_SETOP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataParameterSetOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataParameterSetOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataParameterSetOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataParameterSetOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataParameterSetOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataParameterSetOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataParameterSetOperationClass::CopyClone(Identify *  objc)
{
  DataParameterSetOperationClass *objcfull = (DataParameterSetOperationClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataParameterSetOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataParameterSetOperationClass::Clone()
    {
      DataParameterSetOperationClass* id = new DataParameterSetOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterSetOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterSetOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterSetOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterSetOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataParameterSetOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataParameterSetOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataParameterSetOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataParameterSetOperationClass*& obj)
     {
     obj = new DataParameterSetOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataParameterSetOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataParameterSetOperation*& obj)
     {
     obj = new BaseDataParameterSetOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataParameterExtract
 */ 
/*F BaseDataParameterExtract()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParameterExtract::BaseDataParameterExtract()
{
  Identification = PARAMETERIZED_EXTRACT_ID;
  NameTag = PARAMETERIZED_EXTRACT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataParameterExtract(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataParameterExtract::BaseDataParameterExtract(const BaseDataParameterExtract& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataParameterExtract
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataParameterExtract::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataParameterExtract
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataParameterExtract::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataParameterExtract
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataParameterExtract::print(ostream& out) const
{
  BaseDataOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterExtract
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataParameterExtract::Clone()
{
  BaseDataParameterExtract *obj = new BaseDataParameterExtract(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterExtract
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataParameterExtract::CopyClone(Identify * obj)
{
  BaseDataParameterExtract *objfull = (BaseDataParameterExtract *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterExtract
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterExtract::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterExtract
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterExtract::DecodeThis(CommBuffer& buffer)
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
BaseDataObject *BaseDataParameterExtract::operator()(BaseDataObject *x, BaseDataObject *y,
						     DataObjectClass *xc, DataObjectClass *yc)
{
  BaseDataParameterSet *set = (BaseDataParameterSet *) y;
  BaseDataObject *object;

  if(set->IsInList(x->NameTag))
    {
      object = set->GetObject(x->NameTag);
    }
  else
    {
      cerr << "Parameter '" << x->NameTag << "' in parameter set:" << endl;
      set->OrderedListOfParameterNames().print(cerr);
      cerr << endl;
      object = x;
    }
  return (BaseDataObject *) object->Clone();
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
BaseDataObject *BaseDataParameterExtract::operator()(BaseDataObject *x,
						     DataObjectClass *xc)
{
  return (BaseDataObject *) x->Clone();
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
BaseDataObject *BaseDataParameterExtract::operator()(DataObjectClass *cls,
						  BaseDataObject *x, BaseDataObject *y,
						  DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  return operator()(x,y,xc,yc);
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
BaseDataObject *BaseDataParameterExtract::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
 
 
/*S DataParameterExtractClass
 */
/*F DataParameterExtractClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataParameterExtractClass::DataParameterExtractClass()
{
  Identification = PARAMETERIZED_EXTRACT_ID;
  NameTag = PARAMETERIZED_EXTRACT_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataParameterExtractClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataParameterExtractClass::DataParameterExtractClass(const DataParameterExtractClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataParameterExtractClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataParameterExtractClass::DataParameterExtractClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = PARAMETERIZED_EXTRACT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataParameterExtractClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataParameterExtractClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataParameterExtractClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataParameterExtractClass, there is no further information.
**
**  REMARKS
**
*/
bool DataParameterExtractClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataParameterExtractClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataParameterExtractClass::CopyClone(Identify *  objc)
{
  DataParameterExtractClass *objcfull = (DataParameterExtractClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataParameterExtractClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataParameterExtractClass::Clone()
    {
      DataParameterExtractClass* id = new DataParameterExtractClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterExtractClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterExtractClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterExtractClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterExtractClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataParameterExtractClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataParameterExtract();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataParameterExtractClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataParameterExtractClass*& obj)
     {
     obj = new DataParameterExtractClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataParameterExtract
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataParameterExtract*& obj)
     {
     obj = new BaseDataParameterExtract;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataDescriptionExpressions
 */ 
/*F BaseDataDescriptionExpressions()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDescriptionExpressions::BaseDataDescriptionExpressions()
  : Expressions(NULL),
    PostOperation(false)
{
  Identification = PARAMETERIZED_EXPDESCR_ID;
  NameTag = PARAMETERIZED_EXPDESCR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDescriptionExpressions(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDescriptionExpressions::BaseDataDescriptionExpressions(const BaseDataDescriptionExpressions& data)
  : BaseDataParameterizedFunction(data),
    PostOperation(data.PostOperation)
{
  Expressions = (BaseDataParameterSet *) PointerClone(data.Expressions);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDescriptionExpressions::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDescriptionExpressions::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataDescriptionExpressionsClass *funcclass = (DataDescriptionExpressionsClass *) objc;
  String op0("DescriptionExpressions:");
  result = result && CheckReadKeyWord(in,op0);
  result = result && BaseDataParameterizedFunction::Read(in,objc,name);  

  String op1("Post:");
  result = result && CheckReadKeyWord(in,op1);

  StreamObjectInput str(in,' ');
  String postS = str.ReadNext();
  if(postS == "PostOperation")
    PostOperation = true;
  else if(postS == "NoPostOperation")
    PostOperation = false;
  else
    {
      cerr << "Expected 'PostExpression' or 'PostExpression'" << endl;
      cerr << "Assuming no post expression evaluation" << endl;
      PostOperation = false;
    }
    
  String op2("BeginDescription:");
  result = result && CheckReadKeyWord(in,op2);
  String errorm("Set of Expressions Class not Defined");
  result = result && PointerObjectRead(in,(BaseDataObject *&) Expressions,funcclass->getExpressionsClass(),errorm);
  String op3("EndDescription:");
  result = result && CheckReadKeyWord(in,op3);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDescriptionExpressions::print(ostream& out) const
{
  BaseDataParameterizedFunction::print(out);
  if(PostOperation)
    out << "  Post Expression will be executed" << endl;
  else
    out << "  Post Expression will not be executed" << endl;

  PointerPrint(out,"The Description Expressions: ", "No Description Expressions",Expressions);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDescriptionExpressions::Clone()
{
  BaseDataDescriptionExpressions *obj = new BaseDataDescriptionExpressions(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDescriptionExpressions::CopyClone(Identify * obj)
{
  BaseDataDescriptionExpressions *objfull = (BaseDataDescriptionExpressions *) obj;
  *this = *objfull;
  BaseDataParameterizedFunction::CopyClone(obj);
  Expressions = (BaseDataParameterSet *) PointerClone(objfull->Expressions);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescriptionExpressions::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::EncodeThis(buffer);
  result = result && BoolEncode(buffer,PostOperation);
  result = result && PointerEncode(buffer,Expressions);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescriptionExpressions::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::DecodeThis(buffer);
  result = result && BoolDecode(buffer,PostOperation);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Expressions);
  return result;
}
/*F ldescr = ComputeDescription(descrclass,instance,instclass) . . . . logic results
**
**  DESCRIPTION
**    descrclass: The corresponding description class
**    instance: The instance parameters
**    instclass: The paramater classes
**    
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataDescriptionExpressions::ComputeDescription(DataDescriptionExpressionsClass *descrclass,
									 BaseDataSetOfObjects * instance,
									 DataSetOfObjectsClass * instclass)
{ 
  DataSetOfObjectsClass *ldclass = descrclass->getResultSetClass();
  DataObjectClass *baseclass = descrclass->getBaseClass();
  DataParameterSetClass *paramclass = descrclass->getExpressionsClass();
  DataSetOfObjectsClass *listofclasses = instclass->PointerToAllowedClasses();

  BaseDataSetOfObjects *descrresult = (BaseDataSetOfObjects *) ldclass->BaseDataObjectExample();
  descrresult->NameTag = instance->NameTag;

  bool result = true;
  ObjectList<String> descrnames = Expressions->OrderedListOfParameterNames();
  ObjectList<String>::iterator name;
  for(name = descrnames.begin();
      name != descrnames.end() && result;
      name++)
    {
      BaseDataParameterizedFunction *func = (BaseDataParameterizedFunction *) Expressions->GetObject(*name);
      if(listofclasses->IsOfClass(*func,PARAMETERIZED_FUNCTION_NAME))
	{
	  BaseDataObject *obj = func->operator()(getParameterSet(),instance,paramclass,instclass);
	  if(listofclasses->IsOfClass(*obj,baseclass->NameTag))
	    {
	      obj->NameTag = *name;
	      result = result && descrresult->AddObject(obj);
	      if(!result)
		cerr << "Didn't Add Value from description\n" << endl;
	    }
	  else
	    {
	      cerr << "Description Result object not of type '" << baseclass->NameTag << "'" << endl;
	      result = false;
	    }
	}
      else
	{
	  cerr << "Function not of class '" << PARAMETERIZED_FUNCTION_NAME << "'" << endl;
	  result = false;
	}
    }
  return descrresult;
}
/*F ldescr = ComputeDescription(descrclass,instance,instclass) . . . . logic results
**
**  DESCRIPTION
**    descrclass: The corresponding description class
**    instance: The instance parameters
**    instclass: The paramater classes
**    
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataDescriptionExpressions::ComputeDescription(BaseDataSetOfObjects * instance,
									 DataSetOfObjectsClass * instclass)
{ 
  DataSetOfObjectsClass *listofclasses = instclass->PointerToAllowedClasses();
  DataParameterSetClass *paramclass = (DataParameterSetClass *) listofclasses->GetObjectClass(PARAMETERIZED_SET_NAME);

  BaseDataSetOfObjects *descrresult = new BaseDataSetOfObjects();
  descrresult->NameTag = instance->NameTag;

  bool result = true;
  ObjectList<String> descrnames = Expressions->OrderedListOfParameterNames();
  ObjectList<String>::iterator name;
  for(name = descrnames.begin();
      name != descrnames.end() && result;
      name++)
    {
      BaseDataParameterizedFunction *func = (BaseDataParameterizedFunction *) Expressions->GetObject(*name);
      BaseDataObject *obj = func->operator()(getParameterSet(),instance,paramclass,instclass);
      obj->NameTag = *name;
      result = result && descrresult->AddObject(obj);
      if(!result)
	cerr << "Didn't Add Value from description\n" << endl;
    }
  return descrresult;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataDescriptionExpressions::InsertParameter(BaseDataObject *object)
{
  bool result = true;
  ObjectList<String> names = Expressions->OrderedListOfParameterNames();
  ObjectList<String>::iterator name;
  for(name = names.begin();name != names.end() && result ;name++)
    {
      BaseDataParameterizedFunction *func = (BaseDataParameterizedFunction *) Expressions->GetObject(*name);
      result = result && func->InsertParameter(object);
      func->DontInsertParametersWithOperation();
    }
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
BaseDataObject *BaseDataDescriptionExpressions::operator()(DataObjectClass *cls,
							   BaseDataObject *x,
							   DataObjectClass *xc)
{
  BaseDataObject *result;
  DataDescriptionExpressionsClass *dclass = (DataDescriptionExpressionsClass *) cls;
  BaseDataSetOfObjects *set = (BaseDataSetOfObjects *) x;
  DataSetOfObjectsClass *setclass = (DataSetOfObjectsClass *) xc;
  result = ComputeDescription(dclass,set,setclass);
  if(PostOperation)
    result = getOperation()->operator()(result,dclass->getExpressionsClass());  
  return (BaseDataObject *) result;
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
BaseDataObject *BaseDataDescriptionExpressions::operator()(DataObjectClass *cls,
							  BaseDataObject *x,
							  BaseDataObject *y,
							  DataObjectClass *xc,
							  DataObjectClass *yc)
{
  BaseDataObject *result;
  DataDescriptionExpressionsClass *dclass = (DataDescriptionExpressionsClass *) cls;
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  BaseDataSetOfObjects *set = (BaseDataSetOfObjects *) y;
  DataSetOfObjectsClass *setclass = (DataSetOfObjectsClass *) yc;
  InsertParameterSet(objects);
  result = ComputeDescription(dclass,set,setclass);
  if(PostOperation)
    result = getOperation()->operator()(result,dclass->getExpressionsClass());  
  return (BaseDataObject *) result;
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
BaseDataObject *BaseDataDescriptionExpressions::operator()(BaseDataObject *x,
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
BaseDataObject *BaseDataDescriptionExpressions::operator()(BaseDataObject *x,
							  BaseDataObject *y,
							  DataObjectClass *xc,
							  DataObjectClass *yc)
{
  BaseDataObject *result;
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  BaseDataSetOfObjects *set = (BaseDataSetOfObjects *) y;
  DataSetOfObjectsClass *setclass = (DataSetOfObjectsClass *) yc;
  InsertParameterSet(objects);
  result = ComputeDescription(set,setclass);
  if(PostOperation)
    result = getOperation()->operator()(result,setclass);  
  return (BaseDataObject *) result;
}
/*S DataDescriptionExpressionsClass
 */
/*F DataDescriptionExpressionsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDescriptionExpressionsClass::DataDescriptionExpressionsClass()
  : ExpressionsClass(NULL),
    ResultSetClass(NULL),
    BaseClass(NULL)
{
  Identification = PARAMETERIZED_EXPDESCR_ID;
  NameTag = PARAMETERIZED_EXPDESCR_NAME;
  SubClass = "ParameterizedFunction";
  EncodeDecodeClass = NameTag;
} 
/*F DataDescriptionExpressionsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDescriptionExpressionsClass::DataDescriptionExpressionsClass(const DataDescriptionExpressionsClass& data)
  : DataParameterizedFunctionClass(data)
{
  ExpressionsClass = (DataParameterSetClass *) PointerClone(data.ExpressionsClass);
  ResultSetClass = (DataSetOfObjectsClass *) PointerClone(data.ResultSetClass);
  BaseClass = (DataObjectClass *) PointerClone(data.BaseClass);
} 
 
/*F DataDescriptionExpressionsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDescriptionExpressionsClass::DataDescriptionExpressionsClass(const int id, 
								 const String& name,
								 const String& descr)
  : DataParameterizedFunctionClass(id,name,descr),
    ExpressionsClass(NULL),
    ResultSetClass(NULL),
    BaseClass(NULL)
{
  SubClass = "ParameterizedFunction";
  EncodeDecodeClass = PARAMETERIZED_EXPDESCR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDescriptionExpressionsClass::print(ostream& out) const
{
  DataParameterizedFunctionClass::print(out);
  PointerPrint(out,"\n  The Expression Set Class: "," No Class Defined ",ExpressionsClass);
  PointerPrint(out,"\n  The Result Set Class: "," No Class Defined ",ResultSetClass);
  PointerPrint(out,"\n  The Base Object Class: "," No Class Defined ",BaseClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDescriptionExpressionsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDescriptionExpressionsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
#ifdef DEBUG_LEVEL1
  cout << "Begin:  DataDescriptionExpressionsClass::Read" << endl;
#endif
  bool result = DataParameterizedFunctionClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) ExpressionsClass,
				      PARAMETERIZED_SET_NAME,
				      set," No Expression Set Class ");
#ifdef DEBUG_LEVEL1
  cout << "Expressions Class: " << ExpressionsClass->NameTag << endl;
#endif
  result = result && PointerClassRead(in,(DataObjectClass *&) ResultSetClass,
				      COREOBJECTS_SET_NAME,
				      set," No Result Set Class ");
#ifdef DEBUG_LEVEL1
  cout << "Results Set Class: " << ResultSetClass->NameTag << endl;
#endif
  result = result && PointerClassRead(in,(DataObjectClass *&) BaseClass,
				      COREOBJECTS_BASE_NAME,
				      set," No Base Class ");
#ifdef DEBUG_LEVEL1
  cout << "Base Class: " << BaseClass->NameTag << endl;
  cout << "Begin:  DataDescriptionExpressionsClass::Read" << endl;
#endif
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDescriptionExpressionsClass::CopyClone(Identify *  objc)
{
  DataDescriptionExpressionsClass *objcfull = (DataDescriptionExpressionsClass *) objc;
  *this = *objcfull;
  ExpressionsClass = (DataParameterSetClass *) PointerClone(objcfull->ExpressionsClass);
  ResultSetClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ResultSetClass);
  BaseClass = (DataObjectClass *) PointerClone(objcfull->BaseClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDescriptionExpressionsClass::Clone()
{
  DataDescriptionExpressionsClass* id = new DataDescriptionExpressionsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionExpressionsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,ExpressionsClass);
  result = result && PointerEncode(buffer,ResultSetClass);
  result = result && PointerEncode(buffer,BaseClass);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionExpressionsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ExpressionsClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ResultSetClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) BaseClass);
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
BaseDataObject * DataDescriptionExpressionsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataDescriptionExpressions();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDescriptionExpressionsClass*& obj)
     {
     obj = new DataDescriptionExpressionsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDescriptionExpressions
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDescriptionExpressions*& obj)
     {
     obj = new BaseDataDescriptionExpressions;
     return obj->DecodeThis(buffer);
     }
 
/*F cls = getExpressionsClass() . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    cls: The class of the expression set
**
**  REMARKS
**
*/
DataParameterSetClass *DataDescriptionExpressionsClass::getExpressionsClass()
{
  return ExpressionsClass;
}
/*F cls = getResultSetClass() . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    cls: The class of the description operation result set
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataDescriptionExpressionsClass::getResultSetClass()
{
  return ResultSetClass;
}
/*F cls = getBaseClass()  . . . . . . . . . . DataDescriptionExpressionsClass
**
**  DESCRIPTION
**    cls: The class of the base class of the result set
**
**  REMARKS
**
*/
DataObjectClass *DataDescriptionExpressionsClass::getBaseClass()
{
  return BaseClass;
}

/*S BaseDataDoOperation
 */ 
/*F BaseDataDoOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDoOperation::BaseDataDoOperation()
{
  Identification = PARAMETERIZED_DESCROP_ID;
  NameTag = PARAMETERIZED_DESCROP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDoOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDoOperation::BaseDataDoOperation(const BaseDataDoOperation& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDoOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDoOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDoOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDoOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDoOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDoOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDoOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDoOperation::Clone()
{
  BaseDataDoOperation *obj = new BaseDataDoOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDoOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDoOperation::CopyClone(Identify * obj)
{
  BaseDataDoOperation *objfull = (BaseDataDoOperation *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDoOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDoOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDoOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDoOperation::DecodeThis(CommBuffer& buffer)
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
BaseDataObject *BaseDataDoOperation::operator()(BaseDataObject *x, BaseDataObject *y,
						DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  BaseDataDescriptionExpressions *description = (BaseDataDescriptionExpressions *) x;
  DataDescriptionExpressionsClass *descrclass = (DataDescriptionExpressionsClass *) xc;
  BaseDataSetOfObjects *set = (BaseDataSetOfObjects *) y;
  DataSetOfObjectsClass *setclass = (DataSetOfObjectsClass *) yc;
  
  BaseDataObject *result = description->operator()(descrclass,set,setclass);
  return result;
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
BaseDataObject *BaseDataDoOperation::operator()(BaseDataObject *x,
						DataObjectClass *xc)
{
  return (BaseDataObject *) x->Clone();
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
BaseDataObject *BaseDataDoOperation::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataDoOperation::operator()(DataObjectClass *cls,
						BaseDataObject *x,
						DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataDoOperationClass
 */
/*F DataDoOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDoOperationClass::DataDoOperationClass()
{
  Identification = PARAMETERIZED_DESCROP_ID;
  NameTag = PARAMETERIZED_DESCROP_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataDoOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDoOperationClass::DataDoOperationClass(const DataDoOperationClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataDoOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDoOperationClass::DataDoOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = PARAMETERIZED_DESCROP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDoOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDoOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDoOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDoOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDoOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDoOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDoOperationClass::CopyClone(Identify *  objc)
{
  DataDoOperationClass *objcfull = (DataDoOperationClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDoOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDoOperationClass::Clone()
    {
      DataDoOperationClass* id = new DataDoOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDoOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDoOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDoOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDoOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataDoOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataDoOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDoOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDoOperationClass*& obj)
     {
     obj = new DataDoOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDoOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDoOperation*& obj)
{
  obj = new BaseDataDoOperation;
  return obj->DecodeThis(buffer);
}
/*S BaseDataParametersInFunction
 */ 
/*F BaseDataParametersInFunction()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParametersInFunction::BaseDataParametersInFunction()
{
  Identification = PARAMETERIZED_PINFUNC_ID;
  NameTag = PARAMETERIZED_PINFUNC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataParametersInFunction(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataParametersInFunction::BaseDataParametersInFunction(const BaseDataParametersInFunction& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataParametersInFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataParametersInFunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataParametersInFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataParametersInFunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataParametersInFunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataParametersInFunction::print(ostream& out) const
{
  BaseDataOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataParametersInFunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataParametersInFunction::Clone()
{
  BaseDataParametersInFunction *obj = new BaseDataParametersInFunction(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataParametersInFunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataParametersInFunction::CopyClone(Identify * obj)
{
  BaseDataParametersInFunction *objfull = (BaseDataParametersInFunction *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParametersInFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParametersInFunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParametersInFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParametersInFunction::DecodeThis(CommBuffer& buffer)
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
BaseDataObject *BaseDataParametersInFunction::operator()(DataObjectClass *cls,
							  BaseDataObject *x,
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
BaseDataObject *BaseDataParametersInFunction::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataParametersInFunction::operator()(BaseDataObject *x,
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
BaseDataObject *BaseDataParametersInFunction::operator()(BaseDataObject *x,
							 BaseDataObject *y,
							 DataObjectClass *xc,
							 DataObjectClass *yc)
{
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  BaseDataParameterizedFunction *func = (BaseDataParameterizedFunction *) y;
  BaseDataParameterSet *parameters = func->getParameterSet();

  ObjectList<String>::iterator orig,tochangeto;
  ObjectList<String> origs = parameters->OrderedListOfParameterNames();
  ObjectList<String> changes = objects->OrderedListOfParameterNames();
  if(origs.size() == changes.size())
    {
      orig = origs.begin();
      for(tochangeto = changes.begin();
	  tochangeto != changes.end();
	  tochangeto++)
	{
	  BaseDataObject *change = objects->GetObject(*tochangeto);
	  change->NameTag = *orig;
	  parameters->AddObject(change);
	  orig++;
	}
    }
  else
    {
      cerr << "Parameter Mismatch in 'ParametersInFunction' insert" <<endl;
      cerr << "No changes made" << endl;
    }
  func->InsertParameterSet(parameters,true);
  return (BaseDataObject *) func->Clone();
}
/*S DataParametersInFunctionClass
 */
/*F DataParametersInFunctionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataParametersInFunctionClass::DataParametersInFunctionClass()
{
  Identification = PARAMETERIZED_PINFUNC_ID;
  NameTag = PARAMETERIZED_PINFUNC_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataParametersInFunctionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataParametersInFunctionClass::DataParametersInFunctionClass(const DataParametersInFunctionClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataParametersInFunctionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataParametersInFunctionClass::DataParametersInFunctionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = PARAMETERIZED_PINFUNC_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataParametersInFunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataParametersInFunctionClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataParametersInFunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataParametersInFunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataParametersInFunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataParametersInFunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataParametersInFunctionClass::CopyClone(Identify *  objc)
{
  DataParametersInFunctionClass *objcfull = (DataParametersInFunctionClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataParametersInFunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataParametersInFunctionClass::Clone()
    {
      DataParametersInFunctionClass* id = new DataParametersInFunctionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataParametersInFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParametersInFunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataParametersInFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParametersInFunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataParametersInFunctionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataParametersInFunction();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataParametersInFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataParametersInFunctionClass*& obj)
     {
     obj = new DataParametersInFunctionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataParametersInFunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataParametersInFunction*& obj)
     {
     obj = new BaseDataParametersInFunction;
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
extern void InitialParameterizedEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataParameterSetClass,BaseDataParameterSet,PARAMETERIZED_SET_NAME);
  EncodeDecodeRegisterClass(DataParameterizedFunctionClass,BaseDataParameterizedFunction,PARAMETERIZED_FUNCTION_NAME);
  EncodeDecodeRegisterClass(DataParameterSetOperationClass,BaseDataParameterSetOperation,PARAMETERIZED_SETOP_NAME);
  EncodeDecodeRegisterClass(DataRealFunctionParameterizedClass,BaseDataRealFunctionParameterized,PARAMETERIZED_REALFUNC_NAME);
  EncodeDecodeRegisterClass(DataParameterExtractClass,BaseDataParameterExtract,PARAMETERIZED_EXTRACT_NAME);
  EncodeDecodeRegisterClass(DataDescriptionExpressionsClass,BaseDataDescriptionExpressions,PARAMETERIZED_EXPDESCR_NAME);
  EncodeDecodeRegisterClass(DataDoOperationClass,BaseDataDoOperation,PARAMETERIZED_DESCROP_NAME);
  EncodeDecodeRegisterClass(DataParametersInFunctionClass,BaseDataParametersInFunction,PARAMETERIZED_PINFUNC_NAME);
}
 
/*F AddParameterizedClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddParameterizedClasses(DataSetOfObjectsClass& set)
{
  String psetdescr("Parameter Set Class");
  String basedescr("Base Parameterized Function Class");
  String setdescr("Parameter Set Operation Class");
  String realdescr("Real Function Operation Class");
  String extractdescr("Extract Parameter from Set Class");
  String expdescrdescr("The Expression Predicate Description");
  String dopdescr("Operation for Logical Description");
  String pifdescr("Insert Parameters in Parameterized Function");
  
  DataParameterSetClass    psetclass(PARAMETERIZED_SET_ID,PARAMETERIZED_SET_NAME,psetdescr);
  DataParameterizedFunctionClass    baseclass(PARAMETERIZED_FUNCTION_ID,PARAMETERIZED_FUNCTION_NAME,basedescr);
  DataParameterSetOperationClass  setclass(PARAMETERIZED_SETOP_ID,PARAMETERIZED_SETOP_NAME,setdescr);
  DataRealFunctionParameterizedClass  realclass(PARAMETERIZED_REALFUNC_ID,PARAMETERIZED_REALFUNC_NAME,realdescr);
  DataParameterExtractClass       extractclass(PARAMETERIZED_EXTRACT_ID,PARAMETERIZED_EXTRACT_NAME,extractdescr);
  DataDescriptionExpressionsClass expdescrclass(PARAMETERIZED_EXPDESCR_ID,PARAMETERIZED_EXPDESCR_NAME,expdescrdescr);
  DataDoOperationClass dopclass(PARAMETERIZED_DESCROP_ID,PARAMETERIZED_DESCROP_NAME,dopdescr);
  DataParametersInFunctionClass pifclass(PARAMETERIZED_PINFUNC_ID,PARAMETERIZED_PINFUNC_NAME,pifdescr);
 
  set.AddObjectClass(psetclass);
  set.AddObjectClass(baseclass);
  set.AddObjectClass(setclass);
  set.AddObjectClass(realclass);
  set.AddObjectClass(extractclass);
  set.AddObjectClass(expdescrclass);
  set.AddObjectClass(dopclass); 
  set.AddObjectClass(pifclass);
}
