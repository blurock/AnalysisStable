/*  FILE     Iterator.cc
**  PACKAGE  Iterator
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "Iterator" package.
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

#include "Iterator.hh"

/*S BaseDataObjectIterator
 */ 
/*F BaseDataObjectIterator()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObjectIterator::BaseDataObjectIterator()
{
  Identification = ITERATOR_OBJECT_ID;
  NameTag = ITERATOR_OBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataObjectIterator(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataObjectIterator::BaseDataObjectIterator(const BaseDataObjectIterator& data)
  : BaseDataSetOfObjects(data),
    ObjectNames(data.ObjectNames)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataObjectIterator
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataObjectIterator::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataObjectIterator
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataObjectIterator::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataObjectIteratorClass *setclass = (DataObjectIteratorClass *) objc;
  // bool result = ReadSetOfObjects(in,this,setclass,name,setclass->ParameterKeys);
  String endstring("END");
  DataSetOfObjectsClass *classes = setclass->PointerToAllowedClasses();
  StreamObjectInput str(in,' ');
  String classtype = str.ReadNext();
  while(!(classtype == endstring) && result) {
    if(classes->IsInList(classtype)) {
      DataObjectClass *cls = classes->GetObjectClass(classtype);
      BaseDataObject *obj = cls->BaseDataObjectExample();
      obj->SetType(cls->Identification);
      obj->Read(in,cls);
      result = result && AddObject(obj);
    } else {
      cerr << "Class Not found: '" << classtype << "'" << endl;
      result = false;
    }
    classtype = str.ReadNext();
  }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataObjectIterator::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  out << "Elements Left" << endl;
  ObjectNames.print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataObjectIterator
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataObjectIterator::Clone()
{
  BaseDataObjectIterator *obj = new BaseDataObjectIterator(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataObjectIterator
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataObjectIterator::CopyClone(Identify * obj)
{
  BaseDataObjectIterator *objfull = (BaseDataObjectIterator *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataObjectIterator::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && ObjectNames.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataObjectIterator::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && ObjectNames.DecodeThis(buffer);
  return result;
}
/*F ans = initializeIterator()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**    Initializes the iterator sequence
**
**    ans: true if objects in sequence
**
**  REMARKS
**
*/
bool BaseDataObjectIterator::initializeIterator(DataIteratorObjectClass *cls) {
  bool result = true;
  ObjectList<String> olist = ListOfObjectNames();
  ObjectListString list(olist);
  ObjectNames = list;
  
  return result;
}
/*F obj = nextIterator()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**     Get the next in the sequence
**       obj: The next element
**       
**  REMARKS
**
*/
BaseDataObject *BaseDataObjectIterator::nextIterator() {
  BaseDataObject *object = NULL;
  String name = ObjectNames.NextKey();
  if(IsInList(name)) {
    object = (BaseDataObject *) GetObject(name)->Clone();
  } 
  return object;
} 
/*F ans = numberRemaining()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**
**  REMARKS
**
*/
unsigned int BaseDataObjectIterator::numberRemaining() {
  return ObjectNames.SizeOf();
}
/*F obj = random()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**     Get the next in the sequence
**       obj: The next element
**
**  REMARKS
**
*/
BaseDataObject *BaseDataObjectIterator::randomObject(DataIteratorObjectClass *cls) {
  unsigned int numI = numberRemaining();
  double numD = (double) numI;
  double rndm = ((double) random()) / ((double) RAND_MAX);

  double numR = floor(numD * rndm + 0.5);
  unsigned int numRI = (unsigned int) numR;
  ObjectListString names = ObjectNames.GetKeyWords();
  ObjectListString::iterator name = names.begin();
  for(unsigned int i=0; i<numRI;i++) name++;
  BaseDataObject *object = NULL;
  if(IsInList(*name)) {
    object = GetObject(*name);
  }
  return object;
}
 
/*S DataObjectIteratorClass
 */
/*F DataObjectIteratorClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataObjectIteratorClass::DataObjectIteratorClass() {
  Identification = ITERATOR_OBJECT_ID;
  NameTag = ITERATOR_OBJECT_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataObjectIteratorClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataObjectIteratorClass::DataObjectIteratorClass(const DataObjectIteratorClass& data)
  : DataSetOfObjectsClass(data),
    ParameterKeys(data.ParameterKeys)
{
} 
 
/*F DataObjectIteratorClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataObjectIteratorClass::DataObjectIteratorClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  cout << "ID:          " << id << endl;
  cout << "Name:        " << name << endl;
  cout << "Description: " << descr << endl;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = "ObjectIterator";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataObjectIteratorClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataObjectIteratorClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  out << "Parameter Keys:" << endl;
  ParameterKeys.print(out);
  out << endl;
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataObjectIteratorClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataObjectIteratorClass, there is no further information.
**
**  REMARKS
**
*/
bool DataObjectIteratorClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  DataKeyWordsClass keywordsclass;

  bool result = ParameterKeys.Read(in,&keywordsclass);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataObjectIteratorClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataObjectIteratorClass::CopyClone(Identify *  objc)
{
  DataObjectIteratorClass *objcfull = (DataObjectIteratorClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataObjectIteratorClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataObjectIteratorClass::Clone()
    {
      DataObjectIteratorClass* id = new DataObjectIteratorClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataObjectIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataObjectIteratorClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && ParameterKeys.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataObjectIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataObjectIteratorClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && ParameterKeys.DecodeThis(buffer);
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
BaseDataObject * DataObjectIteratorClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataObjectIterator();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataObjectIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataObjectIteratorClass*& obj)
     {
     obj = new DataObjectIteratorClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataObjectIterator
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataObjectIterator*& obj)
     {
     obj = new BaseDataObjectIterator;
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
DataSetOfObjectsClass *DataObjectIteratorClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}

/*S BaseDataNumericIterator
 */ 
/*F BaseDataNumericIterator()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumericIterator::BaseDataNumericIterator()
  : Begin(NULL),
    End(NULL),
    Increment(NULL),
    Current(NULL)
{
  Identification = ITERATOR_NUMERIC_ID;
  NameTag = ITERATOR_NUMERIC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNumericIterator(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumericIterator::BaseDataNumericIterator(const BaseDataNumericIterator& data)
  : BaseDataObjectIterator(data) {
  Begin     = (BaseDataNumeric *) PointerClone((BaseDataObject *) data.Begin);
  End       = (BaseDataNumeric *) PointerClone((BaseDataObject *) data.End);
  Increment = (BaseDataNumeric *) PointerClone((BaseDataObject *) data.Increment);
  Current   = (BaseDataNumeric *) PointerClone((BaseDataObject *) data.Current);
  
}
/*F BaseDataNumericIterator(B,E,I)  . . . . . . . . . . . . . . . . .  constructor
**
**  DESCRIPTION
**    B: The beginning value
**    E: The end value
**    I: The increment
**
**  REMARKS
**
*/
BaseDataNumericIterator::BaseDataNumericIterator(BaseDataNumeric *B,
						 BaseDataNumeric *E,
						 BaseDataNumeric *I) {
  Begin     = (BaseDataNumeric *) B->Clone();
  End       = (BaseDataNumeric *) E->Clone();
  Increment = (BaseDataNumeric *) I->Clone();
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataNumericIterator
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumericIterator::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataNumericIterator
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumericIterator::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObjectIterator::Read(in,objc,name);
  String iter(NUMERIC_ITERATOR_KEYWORD);
  String error("Error in reading Numeric Iterator");

  DataNumericIteratorClass *iterc = (DataNumericIteratorClass *) objc;
  if( CheckReadKeyWord(in,iter) ) {
    result = result && 
      PointerObjectRead(in, (BaseDataObject *&) Begin, iterc->NumericClass,error);
    result = result && 
      PointerObjectRead(in, (BaseDataObject *&) End  , iterc->NumericClass,error);
    result = result && 
      PointerObjectRead(in, (BaseDataObject *&) Increment, iterc->NumericClass,error);
  } else {
    result = false;
    cerr << "Error in reading numeric iterator." << endl;
    cerr << "Expecting: '" << iter << "'" << endl;
  }
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataNumericIterator
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumericIterator::print(ostream& out) const
{
  out << "Numeric Iterator" << endl;
  BaseDataObjectIterator::print(out);
  PointerPrint(out,"\nBegin: ","No Begin Defined",Begin);
  PointerPrint(out,"\nEnd: ","No End Defined",End);
  PointerPrint(out,"\nIncrement: ","No Increment defined",Increment);
  PointerPrint(out,"\nCurrent: ","Not initialized",Current);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataNumericIterator
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumericIterator::Clone()
{
  BaseDataNumericIterator *obj = new BaseDataNumericIterator(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataNumericIterator
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumericIterator::CopyClone(Identify * obj)
{
  BaseDataNumericIterator *objfull = (BaseDataNumericIterator *) obj;
  *this = *objfull;
  Begin     = (BaseDataNumeric *) PointerClone((BaseDataObject *) objfull->Begin);
  End       = (BaseDataNumeric *) PointerClone((BaseDataObject *) objfull->End);
  Increment = (BaseDataNumeric *) PointerClone((BaseDataObject *) objfull->Increment);
  Current   = (BaseDataNumeric *) PointerClone((BaseDataObject *) objfull->Current);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNumericIterator
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericIterator::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObjectIterator::EncodeThis(buffer);
  result = result && PointerEncode(buffer,Begin);
  result = result && PointerEncode(buffer,End);
  result = result && PointerEncode(buffer,Increment);
  result = result && PointerEncode(buffer,Current);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNumericIterator
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericIterator::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObjectIterator::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Begin);
  result = result && PointerDecode(buffer,(BaseDataObject *&) End);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Increment);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Current);
  return result;
}
/*F ans = initializeIterator(cls)  . . . . . . . . . . . . . . . .  BaseDataNumericIterator
**
**  DESCRIPTION
**    cls: The class of the iterator
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumericIterator::initializeIterator(DataObjectIteratorClass *cls)
{
  bool result = true;
  if(Current != NULL) {
    delete Current;
  }
  Current = (BaseDataNumeric *) Begin->Clone();

  return result;
}
/*F ans = nextIterator()  . . . . . . . . . . . . . . . .  BaseDataNumericIterator
**
**  DESCRIPTION
**    ans: True if successful
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericIterator::nextIterator()
{
  if(Current != NULL) {
    if(Current > End) {
      delete Current;
      Current = NULL;
    } else {
      BaseDataNumeric *curr = (BaseDataNumeric *) Current->operator+(Increment);
      delete Current;
      Current = curr;
    }
  }
  return Current;
}
/*F ans = numberRemaining()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**
**  REMARKS
**
*/
unsigned int BaseDataNumericIterator::numberRemaining() {
  //double bD = Begin->Distance();
  double eD = End->Distance();
  double iD = Increment->Distance();
  double cD = Current->Distance();

  double remainD = floor((eD - cD)/iD);
  unsigned int remainI = (unsigned int) remainD;

  return remainI;
}
/*F obj = random()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**     Get the next in the sequence
**       obj: The next element
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNumericIterator::randomObject(DataObjectIteratorClass *cls) {
  unsigned int numI = numberRemaining();
  double numD = (double) numI;
  double rndm = ((double) random()) / ((double) RAND_MAX);

  double numR = floor(numD * rndm + 0.5);
  unsigned int numRI = (unsigned int) numR;
  
  BaseDataObject *object = NULL;
  for(unsigned int i=0; i<numRI;i++) {
    object = nextIterator();
  }
  initializeIterator(cls);
  return object;
}

/*S DataNumericIteratorClass
 */
/*F DataNumericIteratorClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumericIteratorClass::DataNumericIteratorClass()
  : NumericClass(NULL)
{
  Identification = ITERATOR_NUMERIC_ID;
  NameTag = ITERATOR_NUMERIC_NAME;
  SubClass = "ObjectIterator";
  EncodeDecodeClass = NameTag;
} 
/*F DataNumericIteratorClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumericIteratorClass::DataNumericIteratorClass(const DataNumericIteratorClass& data)
  : DataObjectIteratorClass(data)
{
  NumericClass   = (DataNumericClass *) 
    PointerClone((BaseDataObject *) data.NumericClass);
} 
 
/*F DataNumericIteratorClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataNumericIteratorClass::DataNumericIteratorClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectIteratorClass(id,name,descr),
    NumericClass(NULL)
{
  SubClass = "ObjectIterator";
  EncodeDecodeClass = "NumericIterator";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataNumericIteratorClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumericIteratorClass::print(ostream& out) const
{
  DataObjectIteratorClass::print(out);
  PointerPrint(out,"  The Numeric Class: "," No Numeric Class Defined ",NumericClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataNumericIteratorClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumericIteratorClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNumericIteratorClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectIteratorClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) NumericClass,
				      NUMERIC_BASE_NAME,
				      set," No Numeric Class ");
  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataNumericIteratorClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumericIteratorClass::CopyClone(Identify *  objc)
{
  DataNumericIteratorClass *objcfull = (DataNumericIteratorClass *) objc;
  *this = *objcfull;
  NumericClass = (DataNumericClass *) PointerClone(objcfull->NumericClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataNumericIteratorClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumericIteratorClass::Clone() {
  DataNumericIteratorClass* id = new DataNumericIteratorClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataNumericIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericIteratorClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectIteratorClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,NumericClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataNumericIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericIteratorClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectIteratorClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) NumericClass);
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
BaseDataObject * DataNumericIteratorClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataNumericIterator();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataNumericIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumericIteratorClass*& obj)
     {
     obj = new DataNumericIteratorClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNumericIterator
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumericIterator*& obj)
     {
     obj = new BaseDataNumericIterator;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataRealIterator
 */ 
/*F BaseDataRealIterator()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataRealIterator::BaseDataRealIterator()
  : BeginD(0.0),
    EndD(0.0),
    IncrementD(0.0)
{
  Identification = ITERATOR_REAL_ID;
  NameTag = ITERATOR_REAL_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataRealIterator(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataRealIterator::BaseDataRealIterator(const BaseDataRealIterator& data)
  : BaseDataNumericIterator(data),
    BeginD(data.BeginD),
    EndD(data.EndD),
    IncrementD(data.IncrementD) {
}
/*F BaseDataNumericIterator(B,E,I)  . . . . . . . . . . . . . . . . .  constructor
**
**  DESCRIPTION
**    B: The beginning value
**    E: The end value
**    I: The increment
**
**  REMARKS
**
*/
BaseDataRealIterator::BaseDataRealIterator(double B,
					   double E,
					   double I) {
  BeginD     = B;
  EndD       = E;
  IncrementD = I;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataRealIterator
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataRealIterator::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataRealIterator
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataRealIterator::Read(istream& in, DataObjectClass* objc, const String& name)
{
  String iter(REAL_ITERATOR_KEYWORD);
  bool result = CheckReadKeyWord(in,iter);

  DataRealIteratorClass *rcls = (DataRealIteratorClass *) objc;
  if( result ) {
    BaseDataReal *e;
    StreamObjectInput str(in,' ');
    String val = str.ReadNext();
    Begin = (BaseDataReal *) rcls->BaseDataObjectExample();
    e = (BaseDataReal *) Begin;
    e->SetValue(val.ToFloat());

    val = str.ReadNext();
    End = (BaseDataReal *) rcls->BaseDataObjectExample();
    e = (BaseDataReal *) End;
    e->SetValue(val.ToFloat());

    val = str.ReadNext();
    Increment = (BaseDataReal *) rcls->BaseDataObjectExample();
    e = (BaseDataReal *) Increment;
    e->SetValue(val.ToFloat());
  }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataRealIterator
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataRealIterator::print(ostream& out) const
{
  out << "Real Iterator: From ";
  out << BeginD << " to " << EndD << " with increment " << IncrementD << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataRealIterator
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataRealIterator::Clone()
{
  BaseDataRealIterator *obj = new BaseDataRealIterator(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataRealIterator
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataRealIterator::CopyClone(Identify * obj)
{
  BaseDataRealIterator *objfull = (BaseDataRealIterator *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealIterator
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealIterator::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumericIterator::EncodeThis(buffer);
  result = result && Encode(buffer,BeginD);
  result = result && Encode(buffer,EndD);
  result = result && Encode(buffer,IncrementD);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealIterator
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealIterator::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumericIterator::DecodeThis(buffer);
  result = result && Decode(buffer,BeginD);
  result = result && Decode(buffer,EndD);
  result = result && Decode(buffer,IncrementD);
  return result;
}
/*F ans = initializeIterator(cls)  . . . . . . . . . . . . . . . .  BaseDataNumericIterator
**
**  DESCRIPTION
**    cls: The class of the iterator
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealIterator::initializeIterator(DataObjectIteratorClass *cls)
{
  bool result = true;
  DataRealIteratorClass *realcls = (DataRealIteratorClass *) cls;
  BaseDataReal *r;

  if(Current != NULL) delete Current;
  Current = (BaseDataNumeric *)  realcls->NumericClass->BaseDataObjectExample();
  r = (BaseDataReal *) Current;
  r->SetValue(BeginD);
  if(Begin == NULL) {
    Begin = (BaseDataNumeric *)    realcls->NumericClass->BaseDataObjectExample();
    r = (BaseDataReal *) Begin;
    r->SetValue(BeginD);
    End = (BaseDataNumeric *)      realcls->NumericClass->BaseDataObjectExample();
    r = (BaseDataReal *) End;
    r->SetValue(EndD);
    Increment = (BaseDataNumeric *) realcls->NumericClass->BaseDataObjectExample();
    r = (BaseDataReal *) Increment;
    r->SetValue(IncrementD);
  }
  return result;
}
/*F ans = nextIterator()  . . . . . . . . . . . . . . . .  BaseDataNumericIterator
**
**  DESCRIPTION
**    ans: True if successful
**
**  REMARKS
**
*/
BaseDataObject *BaseDataRealIterator::nextIterator()
{
  if(Current != NULL) {
    if(Current > End) {
      delete Current;
      Current = NULL;
    } else {
      BaseDataNumeric *curr = (BaseDataNumeric *) Current->operator+(Increment);
      delete Current;
      Current = curr;
    }
  }
  return Current;
}
/*F ans = numberRemaining()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**
**  REMARKS
**
*/
unsigned int BaseDataRealIterator::numberRemaining() {
  //double bD = Begin->Distance();
  double eD = End->Distance();
  double iD = Increment->Distance();
  double cD = Current->Distance();

  double remainD = floor((eD - cD)/iD);
  unsigned int remainI = (unsigned int) remainD;

  return remainI;
}
/*F obj = random()  . . . . . . . . . . . . . . . .  BaseDataObjectIterator
**
**  DESCRIPTION
**     Get the next in the sequence
**       obj: The next element
**
**  REMARKS
**
*/
BaseDataObject *BaseDataRealIterator::randomObject(DataObjectIteratorClass *cls) {
  double rndm = ((double) random()) / ((double) RAND_MAX);
  double num = BeginD + rndm*(EndD - BeginD);

  DataRealClass *rcls = (DataRealClass *) cls;

  if(Current == NULL) 
    Current = (BaseDataNumeric *) rcls->BaseDataObjectExample();
  BaseDataReal *curr = (BaseDataReal *) Current;
  curr->SetValue(num);

  return Current;
}

/*S DataRealIteratorClass
 */
/*F DataRealIteratorClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRealIteratorClass::DataRealIteratorClass()
{
  Identification = ITERATOR_REAL_ID;
  NameTag = ITERATOR_REAL_NAME;
  SubClass = "NumericIterator";
  EncodeDecodeClass = NameTag;
} 
/*F DataRealIteratorClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRealIteratorClass::DataRealIteratorClass(const DataRealIteratorClass& data)
  : DataNumericIteratorClass(data)
{
} 
 
/*F DataRealIteratorClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataRealIteratorClass::DataRealIteratorClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataNumericIteratorClass(id,name,descr)
{
  SubClass = "NumericIterator";
  EncodeDecodeClass = "RealIterator";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataRealIteratorClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRealIteratorClass::print(ostream& out) const
{
  DataNumericIteratorClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataRealIteratorClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRealIteratorClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRealIteratorClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataNumericIteratorClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataRealIteratorClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRealIteratorClass::CopyClone(Identify *  objc)
{
  DataRealIteratorClass *objcfull = (DataRealIteratorClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataRealIteratorClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRealIteratorClass::Clone()
    {
      DataRealIteratorClass* id = new DataRealIteratorClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealIteratorClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataNumericIteratorClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealIteratorClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataNumericIteratorClass::DecodeThis(buffer);
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
BaseDataObject * DataRealIteratorClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataRealIterator();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataRealIteratorClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRealIteratorClass*& obj)
     {
     obj = new DataRealIteratorClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataRealIterator
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataRealIterator*& obj)
     {
     obj = new BaseDataRealIterator;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataIterationSet
 */ 
/*F BaseDataIterationSet()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataIterationSet::BaseDataIterationSet()
  : Current(NULL)
{
  Identification = ITERATOR_SET_ID;
  NameTag = ITERATOR_SET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataIterationSet(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataIterationSet::BaseDataIterationSet(const BaseDataIterationSet& data)
  : BaseDataSetOfObjects(data)
{
  Current = (BaseDataSetOfObjects *) PointerClone(data.Current);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataIterationSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataIterationSet::Read(istream& in, DataObjectClass* objc) {
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataIterationSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS

    IterationSet:
       Iterator:
         RealIterator 0.0 10.0 1.0 
       Iterator:
         ObjectIterator 
            String Red
            String Blue
            String Yellow
            END
         END
       END

**
*/
bool BaseDataIterationSet::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataIterationSetClass *setclass = (DataIterationSetClass *) objc;
  String endstring("END");
  DataSetOfObjectsClass *classes = setclass->PointerToAllowedClasses();
  StreamObjectInput str(in,' ');
  String topiterkey(TOP_ITERATOR_KEYWORD);
  String iterobj(ITERATOR_KEYWORD);
  
  if( CheckReadKeyWord(in,topiterkey) ) {
    String iterkey = str.ReadNext();
    while(!(iterkey == endstring) && result) {
      if(iterkey == iterobj) {
	String classtype = str.ReadNext();
	cout << "Reading Type: '" << classtype << "'" << endl;
	if(classes->IsInList(classtype)) {
	  DataObjectClass *cls = classes->GetObjectClass(classtype);
	  BaseDataObject *obj = cls->BaseDataObjectExample();
	  obj->SetType(cls->Identification);
	  obj->Read(in,cls);
	  result = result && AddObject(obj);
	} else {
	  cerr << "Class Not found: '" << classtype << "'" << endl;
	  result = false;
	}
	iterkey = str.ReadNext();
      } else {
	cerr << "Expected: '" << iterobj << "' got '" << iterkey << "'" << endl;
	result = false;
      }
    }
  } else {
    cerr << "Expected: '" << topiterkey << "' " << endl;
    result = false;
  }
  cout << "Done" << endl;
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataIterationSet
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataIterationSet::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataIterationSet
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataIterationSet::Clone()
{
  BaseDataIterationSet *obj = new BaseDataIterationSet(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataIterationSet
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataIterationSet::CopyClone(Identify * obj)
{
  BaseDataIterationSet *objfull = (BaseDataIterationSet *) obj;
  *this = *objfull;
  Current = (BaseDataSetOfObjects *) PointerClone(objfull->Current);

}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataIterationSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataIterationSet::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && PointerEncode(buffer,Current);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataIterationSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataIterationSet::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && PointerDecode(buffer, (BaseDataObject *&) Current);
  return result;
}
/*F ans = initialize(cls)  . . . . . . . . . . . . . . . .  BaseDataIterationSet
**
**  DESCRIPTION
**    cls: The class of the set of objects
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataIterationSet::initialize(DataIterationSetClass *cls) {
  DataSetOfObjectsClass *classes = cls->PointerToAllowedClasses();
  bool result = true;
  ObjectList<String> olist = ListOfObjectNames();
  OrderedNames = new VectorSimple<String>(olist.size());
  CurrentNames = new VectorSimple<String>(olist.size());
  if(Current != NULL)
    delete Current;
  Current = (BaseDataSetOfObjects *) cls->CurrentClass->BaseDataObjectExample();
  int count = 0;
  String setname("Set");
  for(ObjectList<String>::iterator name = olist.begin();
      name != olist.end();
      name++) {
    (*OrderedNames)[count] = *name;

    BaseDataObjectIterator *iter = (BaseDataObjectIterator *) GetObject(*name);
    DataIteratorObjectClass *cls = (DataIteratorObjectClass *) classes->GetObjectClass(iter->GetType());
    iter->initializeIterator(cls);

    BaseDataObject *obj = iter->nextIterator();
    (*CurrentNames)[count] = obj->NameTag;
    setname.AppendToEnd("-");
    setname.AppendToEnd((*CurrentNames)[count]);

    obj->NameTag = *name;
    Current->AddObject(obj);
    delete obj;
    
    count++;
  }
  Current->NameTag = setname;
  return result;
}
/*F ans = nextIterator(cls)  . . . . . . . . . . . . . . . .  BaseDataIterationSet
**
**  DESCRIPTION
**    cls: The class of the set of objects
**    ans: True if successful
**
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataIterationSet::nextIterator(DataIterationSetClass *itercls) {
  DataSetOfObjectsClass *classes = itercls->PointerToAllowedClasses();
  int i = 0;
  bool notdone = true;
  int dimension = (*OrderedNames).size();
  while(notdone && i < dimension) {
    BaseDataObjectIterator *iter = (BaseDataObjectIterator *) GetObject((*OrderedNames)[i]);
    BaseDataObject *obj = iter->nextIterator();
    if(obj == NULL) {
      DataIteratorObjectClass *cls = (DataIteratorObjectClass *) classes->GetObjectClass(iter->GetType());
      iter->initializeIterator(cls);
      obj = iter->nextIterator();
    } else {
      notdone = false;
    }
    (*CurrentNames)[i] = obj->NameTag;
    obj->NameTag = (*OrderedNames)[i];
    Current->AddObject(obj);
    //delete obj;

    i++;
  }
  if(notdone) {
    delete Current;
    Current = NULL;
  } else {
    String setname("Set");
    for(int i=0;i<dimension;i++) {
      setname.AppendToEnd("-");
      setname.AppendToEnd((*CurrentNames)[i]);
    }
    Current->NameTag = setname;
  }
  return Current;
}
/*S DataIterationSetClass
 */
/*F DataIterationSetClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataIterationSetClass::DataIterationSetClass()
  : CurrentClass(NULL)
{
  Identification = ITERATOR_SET_ID;
  NameTag = ITERATOR_SET_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataIterationSetClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataIterationSetClass::DataIterationSetClass(const DataIterationSetClass& data)
  : DataSetOfObjectsClass(data)
{
  CurrentClass = (DataSetOfObjectsClass *) PointerClone(data.CurrentClass);
} 
 
/*F DataIterationSetClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataIterationSetClass::DataIterationSetClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr),
  CurrentClass(NULL)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = "IterationSet";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataIterationSetClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataIterationSetClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  PointerPrint(out,"  The Class of the set of objects: "," No Class Defined ",CurrentClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataIterationSetClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataIterationSetClass, there is no further information.
**
**  REMARKS
**
*/
bool DataIterationSetClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = PointerClassRead(in,(DataObjectClass *&) CurrentClass,
				      COREOBJECTS_SET_NAME,
				      set," No Class for set of objects");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataIterationSetClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataIterationSetClass::CopyClone(Identify *  objc)
{
  DataIterationSetClass *objcfull = (DataIterationSetClass *) objc;
  *this = *objcfull;
  CurrentClass = (DataSetOfObjectsClass *) PointerClone(objcfull->CurrentClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataIterationSetClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataIterationSetClass::Clone() {
  DataIterationSetClass* id = new DataIterationSetClass(*this);
  return (Identify *) id;
 }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataIterationSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataIterationSetClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,CurrentClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataIterationSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataIterationSetClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) CurrentClass);
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
BaseDataObject * DataIterationSetClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataIterationSet();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataIterationSetClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataIterationSetClass*& obj)
     {
     obj = new DataIterationSetClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataIterationSet
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataIterationSet*& obj)
     {
     obj = new BaseDataIterationSet;
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
DataSetOfObjectsClass *DataIterationSetClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}



/*S Utilities
 */

extern void InitialIteratorEncodeDecodeRoutines() {
  EncodeDecodeRegisterClass(DataObjectIteratorClass,BaseDataObjectIterator,ITERATOR_OBJECT_NAME);
  EncodeDecodeRegisterClass(DataNumericIteratorClass,BaseDataNumericIterator,ITERATOR_NUMERIC_NAME);
  EncodeDecodeRegisterClass(DataRealIteratorClass,BaseDataRealIterator,ITERATOR_REAL_NAME);
  EncodeDecodeRegisterClass(DataIterationSetClass,BaseDataIterationSet,ITERATOR_SET_NAME);
}
void AddIteratorClasses(DataSetOfObjectsClass& set) {
  String objdescr("Object Iterator Class");
  String numdescr("Numeric Iterator Class");
  String realdescr("Real Number Iterator Class");
  String setdescr("Set of Iterators");
  DataObjectIteratorClass objclass(ITERATOR_OBJECT_ID,ITERATOR_OBJECT_NAME,objdescr);
  DataNumericIteratorClass numclass(ITERATOR_NUMERIC_ID,ITERATOR_NUMERIC_NAME,numdescr);
  DataRealIteratorClass realclass(ITERATOR_REAL_ID,ITERATOR_REAL_NAME,realdescr);
  DataIterationSetClass setclass(ITERATOR_SET_ID,ITERATOR_SET_NAME,setdescr);
  set.AddObjectClass(objclass);
  set.AddObjectClass(numclass);
  set.AddObjectClass(realclass);
  set.AddObjectClass(setclass);
}

/*
String PlaceHoldersKeyWord("PlaceHolders");
String NoClassNamePairsKeyWord("NoClassNamePairsKeyWord");
String NoReadKeyWord("NoRead");
String ReadAsTripletKeyWord("ReadAsTriplet");
*/
bool ReadSetOfObjects(istream& in,
		      BaseDataSetOfObjects * set,
		      DataSetOfObjectsClass* setclass, 
		      const String& name,
		      BaseDataKeyWords keys)
{
  bool result;
  if(keys.SizeOf() == 0) {
    setclass->ReadClassPairs = true;
    setclass->ReadAllowedClasses = false;
    result = setclass->ReadInClassNamePairs(in);
    result = result && set->BaseDataSetOfObjects::Read(in,setclass->PointerToAllowedClasses(),name);
  } else if(keys.KeyWordInList(NoReadKeyWord)){
    result = true;
  } else if(keys.KeyWordInList(PlaceHoldersKeyWord)){
    if(!keys.KeyWordInList(NoClassNamePairsKeyWord)) 
      result = setclass->ReadInClassNamePairs(in);
    else
      result = setclass->ReadInClassNamePairsWithoutKeyWord(in);
  } else {
    if(keys.KeyWordInList(ReadAsTripletKeyWord)) {
      set->ReadAsTriplet(in,setclass);
    } else {
      if(!keys.KeyWordInList(NoClassNamePairsKeyWord)) 
	result = setclass->ReadInClassNamePairs(in);
      else
	result = setclass->ReadInClassNamePairsWithoutKeyWord(in);
      result = result && set->BaseDataSetOfObjects::Read(in,setclass,name);
    }
  }    
  return result;
}
