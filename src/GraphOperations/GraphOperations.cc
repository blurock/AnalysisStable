/*  FILE     GraphOperations.cc
**  PACKAGE  GraphOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "GraphOperations" package.
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
#include "PredicateObjects.hh"
#include "GraphOperations.hh"
#include "GeneralGraph.hh"

/*S BaseDataGraphNodePair
 */ 
/*F BaseDataGraphNodePair()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGraphNodePair::BaseDataGraphNodePair()
  : Value(NULL)
{
  Identification = GRAPHOP_PAIR_ID;
  NameTag = GRAPHOP_PAIR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGraphNodePair(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGraphNodePair::BaseDataGraphNodePair(const BaseDataGraphNodePair& data)
  : BaseDataObject(data),
    Node1S(data.Node1S),
    Node2S(data.Node2S),
    Value(NULL)
{
  Value = (BaseDataLogical *) PointerClone(data.Value);
} 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGraphNodePair
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGraphNodePair::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGraphNodePair
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGraphNodePair::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataGraphNodePairClass *objfull = (DataGraphNodePairClass *) objc;
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  Node1S = str.ReadNext();
  Node2S = str.ReadNext();
  String notdefined("Logical Value Not Defined");
  result = result && PointerObjectRead(in, (BaseDataObject *&) Value,
				       objfull->getLogicClass(),notdefined);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGraphNodePair
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGraphNodePair::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << "  ['" <<  Node1S << "', '" << Node2S << "'](";
  if(Value != NULL) 
    out << Value->GetValue();
  else
    out << " No Value ";
  out  << ")"; 
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNodePair
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGraphNodePair::Clone()
{
  BaseDataGraphNodePair *obj = new BaseDataGraphNodePair(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNodePair
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGraphNodePair::CopyClone(Identify * obj)
{
  BaseDataGraphNodePair *objfull = (BaseDataGraphNodePair *) obj;
  *this = *objfull;
  Value = (BaseDataLogical *) PointerClone(objfull->Value);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNodePair
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNodePair::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,Node1S);
  result = result && Encode(buffer,Node2S);
  result = result && PointerEncode(buffer,Value);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNodePair
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNodePair::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Decode(buffer,Node1S);
  result = result && Decode(buffer,Node2S);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Value);
  return result;
}
 
/*F name = GenerateName()  . . . . . . . . . . . . . . . . . . BaseDataGraphNodePair
**
**  DESCRIPTION
**    name: Name generated from node names
**
**  REMARKS
**
*/
void BaseDataGraphNodePair::GenerateName()
{
  NameTag = Node1S;
  String delim("#");
  NameTag.AppendToEnd(delim);
  NameTag.AppendToEnd(Node2S);
}
 
/*F ans = operator==(pair)  . . . . . . . . . . . . . . BaseDataGraphNodePair
**
**  DESCRIPTION
**    pair: The pair to compare
**    ans: True if the same
**
**    'Same' is defined by having the two node names being the same
**
**  REMARKS
**
*/
bool BaseDataGraphNodePair::operator==(BaseDataObject *obj)
{
  BaseDataGraphNodePair *pair = (BaseDataGraphNodePair *) obj;
  bool result = Node1S.operator==(pair->GetName1());
  result = result && Node2S.operator==(pair->GetName2());
  return result;
}
 
/*F name = GetName1() . . . . . . . . . . . . . . . . BaseDataGraphNodePair
**
**  DESCRIPTION
**    name: The first node name
**
**  REMARKS
**
*/
String& BaseDataGraphNodePair::GetName1()
{
  return Node1S;
}
/*F name = GetName2() . . . . . . . . . . . . . . . . BaseDataGraphNodePair
**
**  DESCRIPTION
**    name: The second node name
**
**  REMARKS
**
*/
String& BaseDataGraphNodePair::GetName2()
{
  return Node2S;
}
/*F val = getValue()  . . . . . . . . . . . . . . . . .  BaseDataGraphNodePai
**
**  DESCRIPTION
**    val: The logical value
**
**  REMARKS
**
*/
BaseDataLogical *BaseDataGraphNodePair::getValue()
{
  return Value;
}

/*S DataGraphNodePairClass
 */
/*F DataGraphNodePairClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGraphNodePairClass::DataGraphNodePairClass()
  : LogicClass(NULL)
{
  Identification = GRAPHOP_PAIR_ID;
  NameTag = GRAPHOP_PAIR_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataGraphNodePairClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGraphNodePairClass::DataGraphNodePairClass(const DataGraphNodePairClass& data)
  : DataObjectClass(data)
{
  LogicClass = (DataLogicalClass *) PointerClone(data.LogicClass);
} 
 
/*F DataGraphNodePairClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGraphNodePairClass::DataGraphNodePairClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr),
    LogicClass(NULL)
{
  SubClass = "Object";
  EncodeDecodeClass = GRAPHOP_PAIR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGraphNodePairClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGraphNodePairClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  PointerPrint(out,"Logic Class: ","None Defined",LogicClass);
  return out;
}
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGraphNodePairClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGraphNodePairClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  PointerClassRead(in,(DataObjectClass *&) LogicClass,
		   LOGICAL_BASE_NAME,set,
		   "No Logical Class");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGraphNodePairClass::CopyClone(Identify *  objc)
{
  DataGraphNodePairClass *objcfull = (DataGraphNodePairClass *) objc;
  *this = *objcfull;
  LogicClass = (DataLogicalClass *) PointerClone(objcfull->LogicClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGraphNodePairClass::Clone()
{
  DataGraphNodePairClass* id = new DataGraphNodePairClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNodePairClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNodePairClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,LogicClass);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNodePairClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNodePairClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataGraphNodePairClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataGraphNodePair();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGraphNodePairClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGraphNodePairClass*& obj)
     {
     obj = new DataGraphNodePairClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGraphNodePair
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGraphNodePair*& obj)
     {
     obj = new BaseDataGraphNodePair;
     return obj->DecodeThis(buffer);
     }
 
/*F logclass = getLogicClass()
**
**  DESCRIPTION
**    logclass: The logical class of the value of the pair
**
**  REMARKS
**
*/
DataLogicalClass *DataGraphNodePairClass::getLogicClass()
{
  return LogicClass;
}

/*S BaseDataGraphNodePairs
 */ 
/*F BaseDataGraphNodePairs()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGraphNodePairs::BaseDataGraphNodePairs()
  : Value(NULL)
{
  Identification = GRAPHOP_PAIRS_ID;
  NameTag = GRAPHOP_PAIRS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  String title("-------- Set of Graph Node Pairs ---------\n");
  String delim("\n");
  setTitle(title);
  setDelimitor(delim);
} 
/*F BaseDataGraphNodePairs(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGraphNodePairs::BaseDataGraphNodePairs(const BaseDataGraphNodePairs& data)
  : BaseDataSetOfObjects(data)
{
  Value = (BaseDataLogical *) PointerClone(data.Value);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGraphNodePairs
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairs::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGraphNodePairs
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairs::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataGraphNodePairsClass *pairsclass = (DataGraphNodePairsClass *) objc;

  DataGraphNodePairClass *nodeclass = pairsclass->getNodePairClass();
  StreamObjectInput str(in,' ');
  String next = str.ReadNext();
  while(!(next == "END") && result)
    {
      BaseDataGraphNodePair *node = (BaseDataGraphNodePair *) nodeclass->BaseDataObjectExample();
      result = result && node->Read(in,nodeclass,next);
      AddObject(node);
      delete node;
      next = str.ReadNext();
    }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGraphNodePairs
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGraphNodePairs::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  PointerPrint(out,"The Total Value: ","No Value Specified",Value);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNodePairs
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGraphNodePairs::Clone()
{
  BaseDataGraphNodePairs *obj = new BaseDataGraphNodePairs(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNodePairs
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGraphNodePairs::CopyClone(Identify * obj)
{
  BaseDataGraphNodePairs *objfull = (BaseDataGraphNodePairs *) obj;
  *this = *objfull;
  Value = (BaseDataLogical *) PointerClone(objfull->Value);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNodePairs
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairs::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && PointerEncode(buffer,Value);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNodePairs
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairs::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Value);
  return result;
}
 
/*F ans = AddObject(obj)  . . . . . . . . . . . . . .  BaseDataGraphNodePairs
**
**  DESCRIPTION
**    obj: The pair to add
**    ans: true if successful, meaning that if this pair is not already in the list
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairs::AddObject(BaseDataObject *obj)
{
  BaseDataGraphNodePair *pair = (BaseDataGraphNodePair *) obj;
  bool result = true;
  pair->GenerateName();
  if(!( IsInList(obj->NameTag) ) )
    {
      result = BaseDataSetOfObjects::AddObject(obj);
      if(Value != NULL)
	{
	  Value->AND(*(pair->getValue()));
	}
      else
	{
	  Value = (BaseDataLogical *) pair->getValue()->Clone();
	}
    }
  else
    {
      result = false;
    }
  return result;
}
 
/*F value = getTotalValue() . . . . . . . . . . . . .  BaseDataGraphNodePairs
**
**  DESCRIPTION
**    value = The value of the total set of match pairs
**
**  REMARKS
**
*/
BaseDataLogical *BaseDataGraphNodePairs::getTotalValue()
{
  return Value;
}
/*S DataGraphNodePairsClass
 */
/*F DataGraphNodePairsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGraphNodePairsClass::DataGraphNodePairsClass()
  : NodePairClass(NULL)
{
  Identification = GRAPHOP_PAIRS_ID;
  NameTag = GRAPHOP_PAIRS_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataGraphNodePairsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGraphNodePairsClass::DataGraphNodePairsClass(const DataGraphNodePairsClass& data)
  : DataSetOfObjectsClass(data)
{
  NodePairClass = (DataGraphNodePairClass *) PointerClone(data.NodePairClass);
} 
 
/*F DataGraphNodePairsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGraphNodePairsClass::DataGraphNodePairsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr),
    NodePairClass(NULL)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = GRAPHOP_PAIRS_NAME;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGraphNodePairsClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  PointerPrint(out,"The Logical Class: ","No Logical Class Specified\n",NodePairClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGraphNodePairsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGraphNodePairsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = 
    PointerClassRead(in,(DataObjectClass *&) NodePairClass,
		     GRAPHOP_PAIR_NAME,set,
		     "No Pair Class");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGraphNodePairsClass::CopyClone(Identify *  objc)
{
  DataGraphNodePairsClass *objcfull = (DataGraphNodePairsClass *) objc;
  *this = *objcfull;
  NodePairClass = (DataGraphNodePairClass *) PointerClone(objcfull->NodePairClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGraphNodePairsClass::Clone()
{
  DataGraphNodePairsClass* id = new DataGraphNodePairsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNodePairsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,NodePairClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNodePairsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) NodePairClass);
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
BaseDataObject * DataGraphNodePairsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataGraphNodePairs();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGraphNodePairsClass*& obj)
     {
     obj = new DataGraphNodePairsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGraphNodePairs
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGraphNodePairs*& obj)
{
  obj = new BaseDataGraphNodePairs;
  return obj->DecodeThis(buffer);
}
/*F logclass = getLogicClass()  . . . . . . . . . . . DataGraphNodePairsClass
**
**  DESCRIPTION
**    logclass: The logical class
**
**  REMARKS
**
*/
DataGraphNodePairClass *DataGraphNodePairsClass::getNodePairClass()
{
  return NodePairClass;
}
 
/*F PointerToAllowedClasses()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataSetOfObjectsClass *DataGraphNodePairsClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*S BaseDataNodeEdgeOperation
 */ 
/*F BaseDataNodeEdgeOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNodeEdgeOperation::BaseDataNodeEdgeOperation()
  : Operation(NULL),
    VariableS("NodeLogicalDescription"),
    NodeOperation(true)
{
  Identification = GRAPHOP_NODEEDGEOP_ID;
  NameTag = GRAPHOP_NODEEDGEOP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNodeEdgeOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNodeEdgeOperation::BaseDataNodeEdgeOperation(const BaseDataNodeEdgeOperation& data)
  : BaseDataOperation(data),
    VariableS(data.VariableS),
    NodeOperation(data.NodeOperation)
{
  Operation = (BaseDataOperation *) PointerClone(data.Operation);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNodeEdgeOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNodeEdgeOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  DataNodeEdgeOperationClass *nodeopclass = (DataNodeEdgeOperationClass *) objc;
  String key("NodeEdgeOperation:");
  CheckReadKeyWord(in,key);

  StreamObjectInput str(in,' ');
  VariableS = str.ReadNext();

  String tag = str.ReadNext();
  if(tag == "NodeOperation")
    NodeOperation = true;
  else
    NodeOperation = false;
  
  String notdefined("Operation not defined");
  result = result && PointerObjectRead(in,(BaseDataObject *&) Operation,
				       nodeopclass->getOperationClass(),
				       notdefined);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNodeEdgeOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  cout << "NodeEdgeOperation:  " << VariableS << endl;
  if(NodeOperation)
    cout << " NodeOperation " << endl;
  else
    cout << " EdgeOperation " << endl;

  PointerPrint(out,"The Node Operation: ","No Node Operation",Operation);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNodeEdgeOperation::Clone()
{
  BaseDataNodeEdgeOperation *obj = new BaseDataNodeEdgeOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNodeEdgeOperation::CopyClone(Identify * obj)
{
  BaseDataNodeEdgeOperation *objfull = (BaseDataNodeEdgeOperation *) obj;
  *this = *objfull;
  Operation = (BaseDataOperation *) PointerClone(objfull->Operation);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNodeEdgeOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Encode(buffer,VariableS);
  result = result && BoolEncode(buffer,NodeOperation);
  result = result && PointerEncode(buffer,Operation);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNodeEdgeOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Decode(buffer,VariableS);
  result = result && BoolDecode(buffer,NodeOperation);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Operation);
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
BaseDataObject *BaseDataNodeEdgeOperation::operator()(BaseDataObject *x, BaseDataObject *y,
						      DataObjectClass *xc, DataObjectClass *yc)
{
  BaseDataDescriptionExpressions  *description = (BaseDataDescriptionExpressions  *) x;
  DataDescriptionExpressionsClass *descriptionclass = (DataDescriptionExpressionsClass *) xc;
  BaseDataGraph *graph = (BaseDataGraph *) y->Clone();
  DataGraphClass *graphclass = (DataGraphClass *) yc;
  BaseDataSetOfObjects *set;
  DataObjectClass *oclass;
  if(NodeOperation)
    {
      set = graph->getNodes();
      oclass = graphclass->NodeClass;
    }
  else
    {
      set = graph->getEdges();
      oclass = graphclass->EdgeClass;
    }
  ObjectList<String> names = set->ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end(); name++)
    {
      BaseDataSetOfObjects *o = (BaseDataSetOfObjects *) set->GetObject(*name);
      BaseDataObject *object = Operation->operator()(description,o,
						     descriptionclass,oclass);
      cout << "------------------------------------------------------" << endl;
      cout << *name << endl;
      cout << "Output of Expression to variable: " << VariableS << endl;
      object->print(cout);
      cout << "------------------------------------------------------" << endl;
      object->NameTag = VariableS;
      o->AddObject(object);
      delete object;
    }
  graph->NameTag = VariableS;
  return graph;
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
BaseDataObject *BaseDataNodeEdgeOperation::operator()(BaseDataObject *x,
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
BaseDataObject *BaseDataNodeEdgeOperation::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataNodeEdgeOperation::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataNodeEdgeOperationClass
 */
/*F DataNodeEdgeOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNodeEdgeOperationClass::DataNodeEdgeOperationClass()
  : OperationClass(NULL)
{
  Identification = GRAPHOP_NODEEDGEOP_ID;
  NameTag = GRAPHOP_NODEEDGEOP_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataNodeEdgeOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNodeEdgeOperationClass::DataNodeEdgeOperationClass(const DataNodeEdgeOperationClass& data)
  : DataOperationClass(data)
{
  OperationClass = (DataOperationClass *) PointerClone(data.OperationClass);
} 
 
/*F DataNodeEdgeOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataNodeEdgeOperationClass::DataNodeEdgeOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr),
    OperationClass(NULL)
{
  SubClass = "Operation";
  EncodeDecodeClass = GRAPHOP_NODEEDGEOP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataNodeEdgeOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNodeEdgeOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  PointerPrint(out,"The Operation Class: ","No Operation Class Defined",OperationClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataNodeEdgeOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNodeEdgeOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNodeEdgeOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  PointerClassRead(in,(DataObjectClass *&) OperationClass,
		   OPERATION_BASE_NAME,set,"Operation Class");
  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataNodeEdgeOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNodeEdgeOperationClass::CopyClone(Identify *  objc)
{
  DataNodeEdgeOperationClass *objcfull = (DataNodeEdgeOperationClass *) objc;
  *this = *objcfull;
  OperationClass = (DataOperationClass *) PointerClone(objcfull->OperationClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataNodeEdgeOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNodeEdgeOperationClass::Clone()
{
  DataNodeEdgeOperationClass* id = new DataNodeEdgeOperationClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataNodeEdgeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNodeEdgeOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *) OperationClass);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataNodeEdgeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNodeEdgeOperationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) OperationClass);
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
BaseDataObject * DataNodeEdgeOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataNodeEdgeOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataNodeEdgeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNodeEdgeOperationClass*& obj)
     {
     obj = new DataNodeEdgeOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNodeEdgeOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNodeEdgeOperation*& obj)
     {
     obj = new BaseDataNodeEdgeOperation;
     return obj->DecodeThis(buffer);
     }
 
/*F getOperationClass()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataOperationClass *DataNodeEdgeOperationClass::getOperationClass()
{
  return OperationClass;
}
/*S BaseDataGraphElementMatch
 */ 
/*F BaseDataGraphElementMatch()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGraphElementMatch::BaseDataGraphElementMatch()
  : NodeMatch(true),
    MatchVariableS("LogicDescription"),
    DescriptionVariableS("Matches"),
    Operation(NULL),
    CutOff(0.0)
{
  Identification = GRAPHOP_ELEMATCH_ID;
  NameTag = GRAPHOP_ELEMATCH_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGraphElementMatch(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGraphElementMatch::BaseDataGraphElementMatch(const BaseDataGraphElementMatch& data)
  : BaseDataOperation(data),
    NodeMatch(data.NodeMatch),
    MatchVariableS(data.MatchVariableS),
    DescriptionVariableS(data.DescriptionVariableS),
    CutOff(data.CutOff)
{
  Operation = (BaseDataOperation *) PointerClone(data.Operation);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGraphElementMatch
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGraphElementMatch::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGraphElementMatch
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGraphElementMatch::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  DataGraphElementMatchClass *matchclass = (DataGraphElementMatchClass *) objc;
  String key("GraphElementMatch:");
  CheckReadKeyWord(in,key);

  StreamObjectInput str(in,' ');
  DescriptionVariableS = str.ReadNext();
  MatchVariableS = str.ReadNext();
  String numS = str.ReadNext();
  CutOff = numS.ToFloat();

  String tag = str.ReadNext();
  if(tag == "NodeMatch")
    NodeMatch = true;
  else
    NodeMatch = false;
  String notdef("No Operation Defined");
  PointerObjectRead(in,(BaseDataObject *&) Operation,
		    matchclass->getOperationClass(),
		    notdef);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGraphElementMatch
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGraphElementMatch::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << "GraphElementMatch:" << endl;
  if(NodeMatch)
    out << " NodeMatch " << endl;
  else
    out << " EdgeMatch " << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphElementMatch
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGraphElementMatch::Clone()
{
  BaseDataGraphElementMatch *obj = new BaseDataGraphElementMatch(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphElementMatch
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGraphElementMatch::CopyClone(Identify * obj)
{
  BaseDataGraphElementMatch *objfull = (BaseDataGraphElementMatch *) obj;
  *this = *objfull;
  Operation = (BaseDataOperation *) PointerClone(objfull->Operation);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphElementMatch
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphElementMatch::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Encode(buffer,MatchVariableS);
  result = result && Encode(buffer,DescriptionVariableS);
  result = result && Encode(buffer,CutOff);
  result = result && PointerEncode(buffer,Operation);
  result = result && BoolEncode(buffer,NodeMatch);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphElementMatch
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphElementMatch::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Decode(buffer,MatchVariableS);
  result = result && Decode(buffer,DescriptionVariableS);
  result = result && Decode(buffer,CutOff);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Operation);
  result = result && BoolDecode(buffer,NodeMatch);
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
BaseDataObject *BaseDataGraphElementMatch::operator()(BaseDataObject *x, BaseDataObject *y,
						      DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  BaseDataGraph *graph1 = (BaseDataGraph *) x->Clone();
  DataGraphClass *graphclass1 = (DataGraphClass *) xc;
  BaseDataGraph *graph2 = (BaseDataGraph *) y;
  DataGraphClass *graphclass2 = (DataGraphClass *) yc;

  BaseDataSetOfObjects *set1,*set2;
  DataSetOfObjectsClass *oclass1,*oclass2;
  if(NodeMatch)
    {
      set1 = graph1->getNodes();
      set2 = graph2->getNodes();
      oclass1 = graphclass1->NodeClass->PointerToAllowedClasses();
      oclass2 = graphclass2->NodeClass->PointerToAllowedClasses();
    }
  else
    {
      set1 = graph1->getEdges();
      set2 = graph2->getEdges();
      oclass1 = graphclass1->EdgeClass;
      oclass2 = graphclass2->EdgeClass;
    }
  ObjectList<String> names1 = set1->ListOfObjectNames();
  ObjectList<String> names2 = set2->ListOfObjectNames();
  ObjectList<String>::iterator name1,name2;
  for(name1 = names1.begin(); name1 != names1.end(); name1++)
    {
      BaseDataSetOfObjects *o1 = (BaseDataSetOfObjects *) set1->GetObject(*name1);
      BaseDataLogicDescription *descr1 = (BaseDataLogicDescription *) o1->GetObject(DescriptionVariableS);
      DataLogicDescriptionClass *ldclass1 = (DataLogicDescriptionClass *) oclass1->GetObjectClass(descr1->GetType());
      BaseDataSetOfObjects *matches = new BaseDataSetOfObjects();
      matches->NameTag = MatchVariableS;
      for(name2 = names2.begin(); name2 != names2.end(); name2++)
	{
	  BaseDataSetOfObjects *o2 = (BaseDataSetOfObjects *) set2->GetObject(*name2);
	  BaseDataLogicDescription *descr2 = (BaseDataLogicDescription *) o2->GetObject(DescriptionVariableS);
	  DataLogicDescriptionClass *ldclass2 = (DataLogicDescriptionClass *) oclass2->GetObjectClass(descr2->GetType());

	  BaseDataLogical *object = (BaseDataLogical *) Operation->operator()(descr1,descr2,ldclass1,ldclass2);
	  if(object->GetValue() > CutOff)
	    {
	      object->NameTag = *name2;
	      matches->AddObject(object);
	    }
	  delete object;
	}
      o1->AddObject(matches);
    }
  return graph1;
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
BaseDataObject *BaseDataGraphElementMatch::operator()(BaseDataObject *x,
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
BaseDataObject *BaseDataGraphElementMatch::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataGraphElementMatch::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*S DataGraphElementMatchClass
 */
/*F DataGraphElementMatchClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGraphElementMatchClass::DataGraphElementMatchClass()
  : OperationClass(NULL)
{
  Identification = GRAPHOP_ELEMATCH_ID;
  NameTag = GRAPHOP_ELEMATCH_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataGraphElementMatchClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGraphElementMatchClass::DataGraphElementMatchClass(const DataGraphElementMatchClass& data)
  : DataOperationClass(data)
{
  OperationClass = (DataOperationClass *) PointerClone(data.OperationClass);
} 
 
/*F DataGraphElementMatchClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGraphElementMatchClass::DataGraphElementMatchClass(const int id, 
						       const String& name,
						       const String& descr)
  : DataOperationClass(id,name,descr),
    OperationClass(NULL)
{
  SubClass = "Operation";
  EncodeDecodeClass = GRAPHOP_ELEMATCH_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGraphElementMatchClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGraphElementMatchClass::print(ostream& out) const
{
  DataOperationClass::print(out);
       
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGraphElementMatchClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGraphElementMatchClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGraphElementMatchClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) OperationClass,
				      OPERATION_BASE_NAME,set,
				      "Operation for Element Match");
				      
				      
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGraphElementMatchClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGraphElementMatchClass::CopyClone(Identify *  objc)
{
  DataGraphElementMatchClass *objcfull = (DataGraphElementMatchClass *) objc;
  *this = *objcfull;
  OperationClass = (DataOperationClass *) PointerClone(objcfull->OperationClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGraphElementMatchClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGraphElementMatchClass::Clone()
{
  DataGraphElementMatchClass* id = new DataGraphElementMatchClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphElementMatchClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphElementMatchClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,OperationClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphElementMatchClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphElementMatchClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) OperationClass);
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
BaseDataObject * DataGraphElementMatchClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataGraphElementMatch();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGraphElementMatchClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGraphElementMatchClass*& obj)
     {
     obj = new DataGraphElementMatchClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGraphElementMatch
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGraphElementMatch*& obj)
     {
     obj = new BaseDataGraphElementMatch;
     return obj->DecodeThis(buffer);
     }
 
/*F opclass = getOperationClass()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataOperationClass *DataGraphElementMatchClass::getOperationClass()
{
  return OperationClass;
}
/*S BaseDataGraphNeighbors
 */ 
/*F BaseDataGraphNeighbors()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGraphNeighbors::BaseDataGraphNeighbors()
  : PairsVariableS("Pairs"),
    MatchesVariableS("Matches")
{
  Identification = GRAPHOP_NEIGHBORS_ID;
  NameTag = GRAPHOP_NEIGHBORS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGraphNeighbors(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGraphNeighbors::BaseDataGraphNeighbors(const BaseDataGraphNeighbors& data)
  : BaseDataOperation(data),
    PairsVariableS(data.PairsVariableS),
    MatchesVariableS(data.MatchesVariableS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGraphNeighbors
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGraphNeighbors::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGraphNeighbors
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGraphNeighbors::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String key0("GraphNeighbors:");
  CheckReadKeyWord(in,key0);

  String key1("Matches:");
  CheckReadKeyWord(in,key1);
  MatchesVariableS = str.ReadNext();
  String key2("Pairs:");
  CheckReadKeyWord(in,key2);
  PairsVariableS = str.ReadNext();
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGraphNeighbors
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGraphNeighbors::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << "Matches: " << MatchesVariableS;
  out << " Pairs: " << PairsVariableS;
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNeighbors
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGraphNeighbors::Clone()
{
  BaseDataGraphNeighbors *obj = new BaseDataGraphNeighbors(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNeighbors
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGraphNeighbors::CopyClone(Identify * obj)
{
  BaseDataGraphNeighbors *objfull = (BaseDataGraphNeighbors *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNeighbors
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNeighbors::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Encode(buffer,PairsVariableS);
  result = result && Encode(buffer,MatchesVariableS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNeighbors
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNeighbors::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Decode(buffer,PairsVariableS);
  result = result && Decode(buffer,MatchesVariableS);
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
BaseDataObject *BaseDataGraphNeighbors::operator()(BaseDataObject *x, BaseDataObject *y,
						   DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  bool result = true;
  BaseDataParameterSet *graphpair = (BaseDataParameterSet *) x;
  BaseDataGraphNodePairs *pairs = (BaseDataGraphNodePairs *) y;
  
  ObjectList<String> graphs = graphpair->OrderedListOfParameterNames();
  String name1 = graphs.front();
  graphs.pop_front();
  String name2 = graphs.front();

  BaseDataGraph *g1 = (BaseDataGraph *) graphpair->GetObject(name1);
  BaseDataGraph *g2 = (BaseDataGraph *) graphpair->GetObject(name2);

  BaseDataGraph *graph1 = (BaseDataGraph *) g1->Clone();
  BaseDataGraph *graph2 = (BaseDataGraph *) g2->Clone();

  BaseDataParameterSet *matchset = new BaseDataParameterSet();
  matchset->NameTag = PairsVariableS;

  BaseDataSetOfObjects *nodes1 = graph1->getNodes();
  BaseDataSetOfObjects *nodes2 = graph2->getNodes();
  ObjectList<String> pairnames = pairs->ListOfObjectNames();

  ObjectList<String>::iterator pairname;
  for(pairname = pairnames.begin(); pairname != pairnames.end(); pairname++)
    {
      BaseDataGraphNodePair *nodepair = (BaseDataGraphNodePair *) pairs->GetObject(*pairname);
      String name1 = nodepair->GetName1();
      String name2 = nodepair->GetName2();
      
      BaseDataNode *node1 = (BaseDataNode *) nodes1->GetObject(name1);
      BaseDataNode *node2 = (BaseDataNode *) nodes2->GetObject(name2);

      
      ObjectList<String> neighbors1 = node1->getNeighboredNodes();
      ObjectList<String> neighbors2 = node2->getNeighboredNodes();
      
      ObjectList<String>::iterator neighbor1,neighbor2;
      int pcount = 0;

      for(neighbor1=neighbors1.begin();neighbor1 != neighbors1.end();neighbor1++)
	{
	  BaseDataNode *next1 = (BaseDataNode *) nodes1->GetObject(*neighbor1);
	  BaseDataSetOfObjects *matches1 = (BaseDataSetOfObjects *) next1->GetObject(MatchesVariableS);
	  for(neighbor2=neighbors2.begin();neighbor2 != neighbors2.end();neighbor2++)
	    {
	      if(matches1->IsInList(*neighbor2))
		{
		  BaseDataGraphNodePairs *newpairs = (BaseDataGraphNodePairs *) pairs->Clone();
		  String pname("NextMatch");
		  String cntS = Int2String(pcount);
		  pcount++;
		  pname.AppendToEnd(cntS);
		  newpairs->NameTag = pname;
		  BaseDataLogical *log = (BaseDataLogical *) matches1->GetObject(*neighbor2);
		  BaseDataGraphNodePair *dummy = new BaseDataGraphNodePair();
		  dummy->Node1S = *neighbor1;
		  dummy->Node2S = *neighbor2;
		  dummy->Value = (BaseDataLogical *) log->Clone();
		  result = newpairs->AddObject(dummy);
		  delete dummy;
		  if(result)
		    matchset->AddObject(newpairs);
		  delete newpairs;
		}

	    }
	}
    }
  return matchset;
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
BaseDataObject *BaseDataGraphNeighbors::operator()(BaseDataObject *x,
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
BaseDataObject *BaseDataGraphNeighbors::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataGraphNeighbors::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  return operator()(x,xclass);
}

/*S DataGraphNeighborsClass
 */
/*F DataGraphNeighborsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGraphNeighborsClass::DataGraphNeighborsClass()
{
  Identification = GRAPHOP_NEIGHBORS_ID;
  NameTag = GRAPHOP_NEIGHBORS_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataGraphNeighborsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGraphNeighborsClass::DataGraphNeighborsClass(const DataGraphNeighborsClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataGraphNeighborsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGraphNeighborsClass::DataGraphNeighborsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = GRAPHOP_NEIGHBORS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGraphNeighborsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGraphNeighborsClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGraphNeighborsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGraphNeighborsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGraphNeighborsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGraphNeighborsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGraphNeighborsClass::CopyClone(Identify *  objc)
{
  DataGraphNeighborsClass *objcfull = (DataGraphNeighborsClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGraphNeighborsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGraphNeighborsClass::Clone()
    {
      DataGraphNeighborsClass* id = new DataGraphNeighborsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNeighborsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNeighborsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNeighborsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNeighborsClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataGraphNeighborsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataGraphNeighbors();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGraphNeighborsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGraphNeighborsClass*& obj)
     {
     obj = new DataGraphNeighborsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGraphNeighbors
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGraphNeighbors*& obj)
     {
     obj = new BaseDataGraphNeighbors;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataSimpleGraphCounts
 */ 
/*F BaseDataSimpleGraphCounts()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimpleGraphCounts::BaseDataSimpleGraphCounts()
  : NodeOperationS("NodeOperation"),
    NodeOperation(true),
    NumberOfS("NumberOfNodes"),
    LogicDescriptionS("LogicDescription")
{
  Identification = GRAPHOP_GRAPHCOUNTS_ID;
  NameTag = GRAPHOP_GRAPHCOUNTS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSimpleGraphCounts(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimpleGraphCounts::BaseDataSimpleGraphCounts(const BaseDataSimpleGraphCounts& data)
  : BaseDataOperation(data),
    NodeOperationS(data.NodeOperationS),
    NodeOperation(data.NodeOperation),
    NumberOfS(data.NumberOfS),
    CountRootS(data.CountRootS),
    LogicDescriptionS(data.LogicDescriptionS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSimpleGraphCounts::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSimpleGraphCounts::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  StreamObjectInput str(in,' ');

  String key0("SimpleGraphCounts:");
  CheckReadKeyWord(in,key0);
  NodeOperationS = str.ReadNext();
  if(NodeOperationS == "NodeOperation")
    NodeOperation = true;
  else
    NodeOperation = false;
  String key1("NumberOf:");
  CheckReadKeyWord(in,key1);
  NumberOfS = str.ReadNext();
  String key2("CountRoot:");
  CheckReadKeyWord(in,key2);
  CountRootS = str.ReadNext();
  String key3("LogicDescription:");
  CheckReadKeyWord(in,key3);
  LogicDescriptionS = str.ReadNext();
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSimpleGraphCounts::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << "Operation over all ";
  if(NodeOperation)
    out << "Nodes" << endl;
  else 
    out << "Edges" << endl;
  out << "NumberOf: '" << NumberOfS;
  out << "'  CountRoot: '" << CountRootS;
  out << "'  LogicDescription: '" << LogicDescriptionS;
  out << "'" << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSimpleGraphCounts::Clone()
{
  BaseDataSimpleGraphCounts *obj = new BaseDataSimpleGraphCounts(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSimpleGraphCounts::CopyClone(Identify * obj)
{
  BaseDataSimpleGraphCounts *objfull = (BaseDataSimpleGraphCounts *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleGraphCounts::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Encode(buffer,NodeOperationS);
  result = result && BoolEncode(buffer,NodeOperation);
  result = result && Encode(buffer,NumberOfS);
  result = result && Encode(buffer,CountRootS);
  result = result && Encode(buffer,LogicDescriptionS);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleGraphCounts::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Decode(buffer,NodeOperationS);
  result = result && BoolDecode(buffer,NodeOperation);
  result = result && Decode(buffer,NumberOfS);
  result = result && Decode(buffer,CountRootS);
  result = result && Decode(buffer,LogicDescriptionS);
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
BaseDataObject *BaseDataSimpleGraphCounts::operator()(BaseDataObject *x, BaseDataObject *y,
						      DataObjectClass *xc, DataObjectClass *yc)
{
  return operator()(x,xc);
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
BaseDataObject *BaseDataSimpleGraphCounts::operator()(BaseDataObject *x,
						  DataObjectClass *xc)
{
  BaseDataGraph *graph = (BaseDataGraph *) x->Clone();
  DataGraphClass *graphclass = (DataGraphClass *) xc;
  BaseDataSetOfObjects *set;
  DataObjectClass *oclass;
  if(NodeOperation)
    {
      set = graph->getNodes();
      oclass = graphclass->NodeClass;
    }
  else
    {
      set = graph->getEdges();
      oclass = graphclass->EdgeClass;
    }
  BaseDataParameterSet *counts = new BaseDataParameterSet();
  counts->NameTag = CountRootS;

  ObjectList<String> names = set->ListOfObjectNames();

  double numnodes = (double) names.size();
  String cntname(CountRootS);
  if(NodeOperation)
    {
      String n("Nodes");
      cntname.AppendToEnd(n);
    }
  else
    {
      String e("Edges");
      cntname.AppendToEnd(e);
    }
  BaseDataReal *rcnt = new BaseDataReal();
  rcnt->NameTag = cntname;
  rcnt->SetValue(numnodes);
  counts->AddObject(rcnt);
  delete rcnt;
  
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end(); name++)
    {
      BaseDataSetOfObjects *setobject = (BaseDataSetOfObjects *) set->GetObject(*name);
      if(setobject->IsInList(LogicDescriptionS))
	{
	  BaseDataLogicDescription *ldescr = (BaseDataLogicDescription *) setobject->GetObject(LogicDescriptionS);
	  ObjectList<String> lnames = ldescr->ListOfObjectNames();
	  ObjectList<String>::iterator lname;
	  for(lname = lnames.begin(); lname != lnames.end(); lname++)
	    {
	      BaseDataLogical *l = (BaseDataLogical *) ldescr->GetObject(*lname);
	      double value = l->GetValue();
	      String name(CountRootS);
	      name.AppendToEnd(*lname);
	      if(counts->IsInList(name))
		{
		  BaseDataReal *r = (BaseDataReal*) counts->GetObject(name);
		  r->SetValue(r->GetValue() + value);
		}
	      else
		{
		  BaseDataReal *r = new BaseDataReal();
		  r->NameTag = name;
		  r->SetValue(value);
		  counts->AddObject(r);
		  delete r;
		}
	    }
	}
    }
  return counts;
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
BaseDataObject *BaseDataSimpleGraphCounts::operator()(DataObjectClass *cls,
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
BaseDataObject *BaseDataSimpleGraphCounts::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
 
 
/*S DataSimpleGraphCountsClass
 */
/*F DataSimpleGraphCountsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSimpleGraphCountsClass::DataSimpleGraphCountsClass()
{
  Identification = GRAPHOP_GRAPHCOUNTS_ID;
  NameTag = GRAPHOP_GRAPHCOUNTS_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataSimpleGraphCountsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSimpleGraphCountsClass::DataSimpleGraphCountsClass(const DataSimpleGraphCountsClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataSimpleGraphCountsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataSimpleGraphCountsClass::DataSimpleGraphCountsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = "SimpleGraphCounts";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSimpleGraphCountsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSimpleGraphCountsClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSimpleGraphCountsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSimpleGraphCountsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSimpleGraphCountsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSimpleGraphCountsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSimpleGraphCountsClass::CopyClone(Identify *  objc)
{
  DataSimpleGraphCountsClass *objcfull = (DataSimpleGraphCountsClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSimpleGraphCountsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSimpleGraphCountsClass::Clone()
    {
      DataSimpleGraphCountsClass* id = new DataSimpleGraphCountsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleGraphCountsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleGraphCountsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleGraphCountsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleGraphCountsClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataSimpleGraphCountsClass::BaseDataObjectExample()
{ 
  //cout << "Make SimpleGraphCounts Example\n";
  return (BaseDataObject *) new BaseDataSimpleGraphCounts();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSimpleGraphCountsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSimpleGraphCountsClass*& obj)
     {
     obj = new DataSimpleGraphCountsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSimpleGraphCounts
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSimpleGraphCounts*& obj)
     {
     obj = new BaseDataSimpleGraphCounts;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataGraphNodePairsOperation
 */ 
/*F BaseDataGraphNodePairsOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGraphNodePairsOperation::BaseDataGraphNodePairsOperation()
  : NumberOfMatchesS("NumberOfMatches"),
    MatchValueS("MatchValue")
{
  Identification = GRAPHOP_PAIRSOP_ID;
  NameTag = GRAPHOP_PAIRSOP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGraphNodePairsOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGraphNodePairsOperation::BaseDataGraphNodePairsOperation(const BaseDataGraphNodePairsOperation& data)
  : BaseDataOperation(data),
    NumberOfMatchesS(data.NumberOfMatchesS),
    MatchValueS(data.MatchValueS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairsOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairsOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String key("GraphNodePairsOperation:");
  CheckReadKeyWord(in,key);

  String key0("NumberOfMatches:");
  CheckReadKeyWord(in,key0);
  NumberOfMatchesS = str.ReadNext();
  
  String key1("MatchValue:");
  CheckReadKeyWord(in,key1);
  MatchValueS = str.ReadNext();
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGraphNodePairsOperation::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << endl << "NumberOfMatches: '" << NumberOfMatchesS;
  out << "'   MatchValues: '" << MatchValueS << "'" << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGraphNodePairsOperation::Clone()
{
  BaseDataGraphNodePairsOperation *obj = new BaseDataGraphNodePairsOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGraphNodePairsOperation::CopyClone(Identify * obj)
{
  BaseDataGraphNodePairsOperation *objfull = (BaseDataGraphNodePairsOperation *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairsOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Encode(buffer,NumberOfMatchesS);
  result = result && Encode(buffer,MatchValueS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraphNodePairsOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Decode(buffer,NumberOfMatchesS);
  result = result && Decode(buffer,MatchValueS);
  return result;
}
/*F obj = operator()(x,y,xclass,yclass) . . . . . . . . . . BaseDataGraphNodePairsOperation
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
BaseDataObject *BaseDataGraphNodePairsOperation::operator()(BaseDataObject *x, BaseDataObject *y,
					     DataObjectClass *xc, DataObjectClass *yc)
{
  return operator()(x,xc);
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . . . . BaseDataGraphNodePairsOperation
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
BaseDataObject *BaseDataGraphNodePairsOperation::operator()(BaseDataObject *x,
							    DataObjectClass *xc)
{
  BaseDataGraphNodePairs *pairs = (BaseDataGraphNodePairs *) x;
  BaseDataLogical *lvalue = pairs->getTotalValue();

  BaseDataParameterSet *parameters = new BaseDataParameterSet();
  if(lvalue != NULL)
    {
      BaseDataReal *value = new BaseDataReal();
      value->NameTag = MatchValueS;
      value->SetValue(lvalue->GetValue());
      parameters->AddObject(value);
      delete value;
    }
  
  ObjectList<String> names = pairs->ListOfObjectNames();
  double pairsize = (double) names.size();
  BaseDataReal *psize = new BaseDataReal();
  psize->NameTag = NumberOfMatchesS;
  psize->SetValue(pairsize);
  parameters->AddObject(psize);
  delete psize;
  
  return parameters;
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . . . . . . BaseDataGraphNodePairsOperation
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
BaseDataObject *BaseDataGraphNodePairsOperation::operator()(DataObjectClass *cls,
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
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . . . . . . BaseDataGraphNodePairsOperation
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
BaseDataObject *BaseDataGraphNodePairsOperation::operator()(DataObjectClass *cls,
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
 
 
/*S DataGraphNodePairsOperationClass
 */
/*F DataGraphNodePairsOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGraphNodePairsOperationClass::DataGraphNodePairsOperationClass()
{
  Identification = GRAPHOP_PAIRSOP_ID;
  NameTag = GRAPHOP_PAIRSOP_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataGraphNodePairsOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGraphNodePairsOperationClass::DataGraphNodePairsOperationClass(const DataGraphNodePairsOperationClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataGraphNodePairsOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGraphNodePairsOperationClass::DataGraphNodePairsOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = GRAPHOP_PAIRSOP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGraphNodePairsOperationClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGraphNodePairsOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGraphNodePairsOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGraphNodePairsOperationClass::CopyClone(Identify *  objc)
{
  DataGraphNodePairsOperationClass *objcfull = (DataGraphNodePairsOperationClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGraphNodePairsOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGraphNodePairsOperationClass::Clone()
    {
      DataGraphNodePairsOperationClass* id = new DataGraphNodePairsOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNodePairsOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNodePairsOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphNodePairsOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphNodePairsOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataGraphNodePairsOperationClass::BaseDataObjectExample()
{ 
  //cout << "Make GraphNodePairsOperation Example\n";
  return (BaseDataObject *) new BaseDataGraphNodePairsOperation();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGraphNodePairsOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGraphNodePairsOperationClass*& obj)
     {
     obj = new DataGraphNodePairsOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGraphNodePairsOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGraphNodePairsOperation*& obj)
     {
     obj = new BaseDataGraphNodePairsOperation;
     return obj->DecodeThis(buffer);
     }

/*S
 */
/*F AddGraphOperationClasses(set) . . . . . . .  add to DataSetOfObjectsClass
**
**  DESCRIPTION
**    set: The set of classes of objects to add the graph operation classes to
**
**  REMARKS
**
*/
void AddGraphOperationClasses(DataSetOfObjectsClass& set)
{
  String nodeopdescr("The Node Operation");
  String elematchdescr("The Element Match");
  String pairdescr("A Graph Node Pair");
  String pairsdescr("The set of matched graph node pairs");
  String neighbordescr("Finding the next matching pair");
  String countsdescr("Counting Node/Edge Properties");
  String pairsopdescr("Computing Generate Match Set Properties");

  DataNodeEdgeOperationClass nodeopclass(GRAPHOP_NODEEDGEOP_ID,GRAPHOP_NODEEDGEOP_NAME,nodeopdescr);
  DataGraphElementMatchClass elematchclass(GRAPHOP_ELEMATCH_ID,GRAPHOP_ELEMATCH_NAME,elematchdescr);
  DataGraphNodePairClass pairclass(GRAPHOP_PAIR_ID,GRAPHOP_PAIR_NAME,pairdescr);
  DataGraphNodePairsClass pairsclass(GRAPHOP_PAIRS_ID,GRAPHOP_PAIRS_NAME,pairsdescr);
  DataGraphNeighborsClass neighborclass(GRAPHOP_NEIGHBORS_ID,GRAPHOP_NEIGHBORS_NAME,neighbordescr);
  DataSimpleGraphCountsClass countsclass(GRAPHOP_GRAPHCOUNTS_ID,GRAPHOP_GRAPHCOUNTS_NAME,countsdescr);
  DataGraphNodePairsOperationClass pairsopclass(GRAPHOP_PAIRSOP_ID,GRAPHOP_PAIRSOP_NAME,pairsopdescr);
  
  set.AddObjectClass(nodeopclass);
  set.AddObjectClass(elematchclass);
  set.AddObjectClass(pairclass);
  set.AddObjectClass(pairsclass);
  set.AddObjectClass(neighborclass);
  set.AddObjectClass(countsclass);
  set.AddObjectClass(pairsopclass);
}
 
/*F InitialGraphOperationEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InitialGraphOperationEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataNodeEdgeOperationClass,BaseDataNodeEdgeOperation,GRAPHOP_NODEEDGEOP_NAME);
  EncodeDecodeRegisterClass(DataGraphElementMatchClass,BaseDataGraphElementMatch,GRAPHOP_ELEMATCH_NAME);
  EncodeDecodeRegisterClass(DataGraphNodePairClass,BaseDataGraphNodePair,GRAPHOP_PAIR_NAME);
  EncodeDecodeRegisterClass(DataGraphNodePairsClass,BaseDataGraphNodePairs,GRAPHOP_PAIRS_NAME);
  EncodeDecodeRegisterClass(DataGraphNeighborsClass,BaseDataGraphNeighbors,GRAPHOP_NEIGHBORS_NAME);
  EncodeDecodeRegisterClass(DataSimpleGraphCountsClass,BaseDataSimpleGraphCounts,GRAPHOP_GRAPHCOUNTS_NAME);
  EncodeDecodeRegisterClass(DataGraphNodePairsOperationClass,BaseDataGraphNodePairsOperation,GRAPHOP_PAIRSOP_NAME);
}
