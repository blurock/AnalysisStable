/*  FILE     ExpressionTree.cc
**  PACKAGE  ExpressionTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "ExpressionTree" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

//#define  DEBUG_LEVEL3
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
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
#include "NonStandard.hh"

/*S BaseDataExpressionTreeNode
 */ 
/*F BaseDataExpressionTreeNode()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExpressionTreeNode::BaseDataExpressionTreeNode()
{
  Identification = EXPRESSIONTREE_NODE_ID;
  NameTag = EXPRESSIONTREE_NODE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataExpressionTreeNode(data)  . . . . . . . . . . . . . . . . .	 copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExpressionTreeNode::BaseDataExpressionTreeNode(const BaseDataExpressionTreeNode& data)
  : BaseDataTreeNode(data),
    Object(data.Object)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeNode::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)	. . . . . . . . . . . . . . .  Read in BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeNode::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataTreeNode::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExpressionTreeNode::print(ostream& out) const
{
  BaseDataTreeNode::print(out);
  out << "Object: " << Object << "   ";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExpressionTreeNode::Clone()
{
  BaseDataExpressionTreeNode *obj = new BaseDataExpressionTreeNode;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExpressionTreeNode::CopyClone(Identify * obj)
{
  BaseDataExpressionTreeNode *objfull = (BaseDataExpressionTreeNode *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeNode::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::EncodeThis(buffer);
  result = result && Encode(buffer,Object);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeNode::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::DecodeThis(buffer);
  result = result && Decode(buffer,Object);
  return result;
}
 
/*F obj = Evaluate(set,setclass,tree,treeclass) . . . . . . . . evaluate node
**
**  DESCRIPTION
**    set: The set of parameter objects
**    setclass: The set of classes
**    tree: The expression tree
**    ctree: The tree class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExpressionTreeNode::Evaluate(BaseDataSetOfObjects *set,
						     DataSetOfObjectsClass *,
						     BaseDataExpressionTree *tree,
						     DataExpressionTreeClass *,
						     BaseDataSetOfObjects *attrs,
						     DataSetOfObjectsClass *)
{
  BaseDataObject *ans = NULL;
  
  if(tree->ParameterInList(Object)) {
    ans = (BaseDataObject *) tree->GetParameter(Object)->Clone();
  } else if(set->IsInList(Object)) {
      ans = (BaseDataObject *) set->GetObject(Object)->Clone();
  } else if(Object == "INSTANCE_VALUES") {
    ans = (BaseDataObject *) set->Clone();
  } else if(attrs->IsInList(Object)) {
    ans = (BaseDataObject *) attrs->GetObject(Object)->Clone();
  } else {
    cerr << "Parameter not found: '" << Object << "'" << endl;
    
  }
  
  return ans;
}
 
/*F name = getAttribute() . . . . . . . .  get the attribute name of the node
**
**  DESCRIPTION
**    name: The name of the attribute
**
**  REMARKS
**
*/
String& BaseDataExpressionTreeNode::getAttribute()
{
  return Object;
}
/*F name = SetAttribute() . . . . . . . .  set the attribute name of the node
**
**  DESCRIPTION
**    name: The name of the attribute
**
**  REMARKS
**
*/
void BaseDataExpressionTreeNode::SetAttribute(String& name)
{
  Object = name;
}


 
/*S DataExpressionTreeNodeClass
 */
/*F DataExpressionTreeNodeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExpressionTreeNodeClass::DataExpressionTreeNodeClass()
{
  Identification = EXPRESSIONTREE_NODE_ID;
  NameTag = EXPRESSIONTREE_NODE_NAME;
  SubClass = DIRECTEDTREE_NODE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataExpressionTreeNodeClass(data) . . . . . . . . . . . . . . . . .	 copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExpressionTreeNodeClass::DataExpressionTreeNodeClass(const DataExpressionTreeNodeClass& data)
  : DataTreeNodeClass(data)
{
} 
 
/*F DataExpressionTreeNodeClass(id,name,descr)	. . . . . . . . . . . . . . . constructor
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
DataExpressionTreeNodeClass::DataExpressionTreeNodeClass(const int id, 
							 const String& name,
							 const String& descr)
  : DataTreeNodeClass(id,name,descr)
{
  SubClass = DIRECTEDTREE_NODE_NAME;
  EncodeDecodeClass = EXPRESSIONTREE_NODE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataExpressionTreeNodeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExpressionTreeNodeClass::print(ostream& out) const
{
  DataTreeNodeClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeNodeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataExpressionTreeNodeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExpressionTreeNodeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataTreeNodeClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeNodeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExpressionTreeNodeClass::CopyClone(Identify *	objc)
{
  DataExpressionTreeNodeClass *objcfull = (DataExpressionTreeNodeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeNodeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExpressionTreeNodeClass::Clone()
{
  DataExpressionTreeNodeClass* id = new DataExpressionTreeNodeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeNodeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeNodeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::DecodeThis(buffer);
  //  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.	This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataExpressionTreeNodeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataExpressionTreeNode();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataExpressionTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExpressionTreeNodeClass*& obj)
{
  obj = new DataExpressionTreeNodeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataExpressionTreeNode
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExpressionTreeNode*& obj)
{
  obj = new BaseDataExpressionTreeNode;
  return obj->DecodeThis(buffer);
}
/*S BaseDataExpressionTreeObject
 */ 
/*F BaseDataExpressionTreeObject()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExpressionTreeObject::BaseDataExpressionTreeObject()
  : ObjectObject(NULL)
{
  Identification = EXPRESSIONTREE_OBJECT_ID;
  NameTag = EXPRESSIONTREE_OBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataExpressionTreeObject(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExpressionTreeObject::BaseDataExpressionTreeObject(const BaseDataExpressionTreeObject& data)
  : BaseDataExpressionTreeNode(data)
{
  ObjectObject = PointerClone(data.ObjectObject);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeObject::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataExpressionTreeNode::Read(in,objc,name);
  DataExpressionTreeObjectClass *objcfull = (DataExpressionTreeObjectClass *) objc;
  String objnotdefined("Node Constant Object Not Defined");
  result = result && PointerObjectRead(in,(BaseDataObject *&) ObjectObject,
				       objcfull->getObjectClass(),
				       objnotdefined);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExpressionTreeObject::print(ostream& out) const
{
  BaseDataExpressionTreeNode::print(out);
  PointerPrint(out,"Constant Object: ","Constant Object not defined",ObjectObject);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExpressionTreeObject::Clone()
{
  BaseDataExpressionTreeObject *obj = new BaseDataExpressionTreeObject(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExpressionTreeObject::CopyClone(Identify * obj)
{
  BaseDataExpressionTreeObject *objfull = (BaseDataExpressionTreeObject *) obj;
  *this = *objfull;
  BaseDataExpressionTreeNode::CopyClone(obj);
  ObjectObject    = PointerClone(objfull->ObjectObject);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeObject::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataExpressionTreeNode::EncodeThis(buffer);
  result = result && PointerEncode(buffer,ObjectObject);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeObject::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataExpressionTreeNode::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ObjectObject);
  return result;
}
/*F obj = Evaluate(set,setclass,tree,treeclass) . . . . . . . . evaluate node
**
**  DESCRIPTION
**    set: The set of parameter objects
**    setclass: The set of classes
**    tree: The expression tree
**    ctree: The tree class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExpressionTreeObject::Evaluate(BaseDataSetOfObjects *,
						       DataSetOfObjectsClass *,
						       BaseDataExpressionTree *tree,
						       DataExpressionTreeClass *,
						       BaseDataSetOfObjects *,
						       DataSetOfObjectsClass *)
{
  BaseDataObject *ans = NULL;
  if(ObjectObject != NULL) {
    ans = (BaseDataObject *) ObjectObject->Clone();
  } else if(tree->ParameterInList(getAttribute())) {
      ans = (BaseDataObject *) tree->GetParameter(getAttribute())->Clone();
  } else {
    cerr << "Parameter not found: " << getAttribute() << endl;
  }
  return ans;
}
/*F ans = SetObject(obj) . . . . . . . . evaluate node
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeObject::SetObject(BaseDataObject *obj) {
  ObjectObject = obj;
  return true;
}
/*S DataExpressionTreeObjectClass
 */
/*F DataExpressionTreeObjectClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExpressionTreeObjectClass::DataExpressionTreeObjectClass()
  : ObjectClass(NULL)
{
  Identification = EXPRESSIONTREE_OBJECT_ID;
  NameTag = EXPRESSIONTREE_OBJECT_NAME;
  SubClass = EXPRESSIONTREE_NODE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataExpressionTreeObjectClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExpressionTreeObjectClass::DataExpressionTreeObjectClass(const DataExpressionTreeObjectClass& data)
  : DataExpressionTreeNodeClass(data)
{
  ObjectClass = (DataObjectClass *) PointerClone(data.ObjectClass);
} 
 
/*F DataExpressionTreeObjectClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataExpressionTreeObjectClass::DataExpressionTreeObjectClass(const int id, 
							     const String& name,
							     const String& descr)
  : DataExpressionTreeNodeClass(id,name,descr),
    ObjectClass(NULL)
{
  SubClass = EXPRESSIONTREE_NODE_NAME;
  EncodeDecodeClass = EXPRESSIONTREE_OBJECT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataExpressionTreeObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExpressionTreeObjectClass::print(ostream& out) const
{
  DataExpressionTreeNodeClass::print(out);
  PointerPrint(out,"Constant Object Class:","No Constant Object Class defined",ObjectClass);       
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataExpressionTreeObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExpressionTreeObjectClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataExpressionTreeNodeClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) ObjectClass,
				      "Object",set,"Object Class");

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExpressionTreeObjectClass::CopyClone(Identify *  objc)
{
  DataExpressionTreeObjectClass *objcfull = (DataExpressionTreeObjectClass *) objc;
  *this = *objcfull;
  DataExpressionTreeNodeClass::CopyClone(objc);
  ObjectClass = (DataObjectClass *) PointerClone(objcfull->ObjectClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExpressionTreeObjectClass::Clone()
{
  DataExpressionTreeObjectClass* id = new DataExpressionTreeObjectClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataExpressionTreeNodeClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ObjectClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeObjectClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataExpressionTreeNodeClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ObjectClass);
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
BaseDataObject * DataExpressionTreeObjectClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataExpressionTreeObject();
  obj->SetType(Identification);
  return obj;
}
/*F opclass = getObjectClass() . . . . . . . . . . . . . . parameter class
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataObjectClass *DataExpressionTreeObjectClass::getObjectClass()
{
  return ObjectClass;
}

/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataExpressionTreeObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExpressionTreeObjectClass*& obj)
{
  obj = new DataExpressionTreeObjectClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataExpressionTreeObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExpressionTreeObject*& obj)
{
  obj = new BaseDataExpressionTreeObject;
  return obj->DecodeThis(buffer);
}
/*S BaseDataExpressionTreeOperation
 */ 
/*F BaseDataExpressionTreeOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExpressionTreeOperation::BaseDataExpressionTreeOperation()
{
  Identification = EXPRESSIONTREE_ALG_ID;
  NameTag = EXPRESSIONTREE_ALG_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataExpressionTreeOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExpressionTreeOperation::BaseDataExpressionTreeOperation(const BaseDataExpressionTreeOperation& data)
  : BaseDataExpressionTreeNode(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)	. . . . . . . . . . . . . . .  Read in BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataExpressionTreeNode::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExpressionTreeOperation::print(ostream& out) const
{
  BaseDataExpressionTreeNode::print(out);
  // The rest

       return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExpressionTreeOperation::Clone()
{
  BaseDataExpressionTreeOperation *obj = new BaseDataExpressionTreeOperation;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExpressionTreeOperation::CopyClone(Identify * obj)
{
  BaseDataExpressionTreeOperation *objfull = (BaseDataExpressionTreeOperation *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataExpressionTreeNode::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTreeOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataExpressionTreeNode::DecodeThis(buffer);
  // The rest

       return result;
}
/*F obj = Evaluate(set,setclass,tree,treeclass) . . . . . . . . evaluate node
**
**  DESCRIPTION
**    set: The set of parameter objects
**    setclass: The set of classes
**    tree: The expression tree
**    ctree: The tree class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExpressionTreeOperation::Evaluate(BaseDataSetOfObjects *set,
							  DataSetOfObjectsClass *setclass,
							  BaseDataExpressionTree *tree,
							  DataExpressionTreeClass *ctree,
							  BaseDataSetOfObjects *attrs,
							  DataSetOfObjectsClass *attrclass)
{
  BaseDataObject *ans = NULL;
  ObjectList<String> *sons = tree->GetSons(NameTag);
  if(sons->size() > 0) {
      BaseDataObject *obj = tree->GetNextNode(*sons,
					     set,setclass,
					     ctree,attrs,attrclass);
      if(obj != NULL) {
	  ans = tree->DoOperation(getAttribute(),ctree,obj);
	  delete obj;
	  while(ans != NULL && sons->size() > 0) {
	      obj = tree->GetNextNode(*sons,set,setclass,ctree,attrs,attrclass);
	      if(obj != NULL) {
#ifdef DEBUG_LEVEL3
		cout << "Evaluate: Do Operation" << endl;
		cout << "Attribute: " << getAttribute() << endl;
		cout << "obj:" << endl;
		obj->print(cout);
		cout << endl;
		cout << "ans:" << endl;
		ans->print(cout);
		cout << endl;
#endif
		  BaseDataObject *newans = tree->DoOperation(getAttribute(),ctree,ans,obj);
#ifdef DEBUG_LEVEL3
		  cout << "Direct After Evaluation: " << endl;
		  ans->print(cout);
		  cout << endl;
#endif
		  delete obj;
		  if(ans != newans)
		    delete ans;
		  ans = newans;
#ifdef DEBUG_LEVEL3
		  cout << "After Evaluation (reassigned): " << endl;
		  ans->print(cout);
		  cout << endl;
#endif
		} else {
		  cerr << "Error in Expression Argument Evaluation" << endl;
		  ans = NULL;
		}
	    }
	} else {
	  cerr << "Error in Expression Argument Evaluation" << endl;
	  ans = NULL;
	}
    } else {
      cerr << "No arguments given for operation in expression evaluation " << endl;
      ans = NULL;
    }
  delete sons;
#ifdef DEBUG_LEVEL3
		  cout << "Final: " << endl;
		  ans->print(cout);
		  cout << endl;
#endif
  return ans;
}

/*S DataExpressionTreeOperationClass
 */
/*F DataExpressionTreeOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExpressionTreeOperationClass::DataExpressionTreeOperationClass()
{
  Identification = EXPRESSIONTREE_ALG_ID;
  NameTag = EXPRESSIONTREE_ALG_NAME;
  SubClass = EXPRESSIONTREE_NODE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataExpressionTreeOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExpressionTreeOperationClass::DataExpressionTreeOperationClass(const DataExpressionTreeOperationClass& data)
  : DataExpressionTreeNodeClass(data)
{
} 
 
/*F DataExpressionTreeOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataExpressionTreeOperationClass::DataExpressionTreeOperationClass(const int id, 
								   const String& name,
								   const String& descr)
  : DataExpressionTreeNodeClass(id,name,descr)
{
  SubClass = EXPRESSIONTREE_NODE_NAME;
  EncodeDecodeClass = EXPRESSIONTREE_ALG_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataExpressionTreeOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExpressionTreeOperationClass::print(ostream& out) const
{
  DataExpressionTreeNodeClass::print(out);
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataExpressionTreeOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExpressionTreeOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataExpressionTreeNodeClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExpressionTreeOperationClass::CopyClone(Identify *  objc)
{
  DataExpressionTreeOperationClass *objcfull = (DataExpressionTreeOperationClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExpressionTreeOperationClass::Clone()
{
  DataExpressionTreeOperationClass* id = new DataExpressionTreeOperationClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataExpressionTreeNodeClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeOperationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataExpressionTreeNodeClass::DecodeThis(buffer);
  //  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.	This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataExpressionTreeOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataExpressionTreeOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataExpressionTreeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExpressionTreeOperationClass*& obj)
{
  obj = new DataExpressionTreeOperationClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataExpressionTreeOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExpressionTreeOperation*& obj)
{
  obj = new BaseDataExpressionTreeOperation;
  return obj->DecodeThis(buffer);
}
/*S BaseDataExpressionTree
 */ 
/*F BaseDataExpressionTree()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExpressionTree::BaseDataExpressionTree()
  : IDCount(0),
    LocalParameterKeyWord(LOCAL_PARAMETER_KEYWORD)
{
  Identification = EXPRESSIONTREE_TREE_ID;
  NameTag = EXPRESSIONTREE_TREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  Initialisation();
} 
/*F BaseDataExpressionTree(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExpressionTree::BaseDataExpressionTree(const BaseDataExpressionTree& data)
  : BaseDataOperation(data),
    ParametersClass(data.ParametersClass),
    Parameters(data.Parameters),
    IDCount(data.IDCount),
    LocalParameterKeyWord(data.LocalParameterKeyWord)
{
  Initialisation();
}
 
/*F Initialisation()  . . . . . . . . . . . . . . . initialise the expression
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataExpressionTree::Initialisation()
{
  String title("-------------------- Set of Expression Parameters --------------------\n");
  Parameters.setTitle(title);
  String delim("\n");
  Parameters.setDelimitor(delim);
  String title1(" -------------------------- Expression Tree  -------------------------- \n");
  Tree.setTitle(title1);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataExpressionTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)	. . . . . . . . . . . . . . .  Read in BaseDataExpressionTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataExpressionTreeClass *ctree = (DataExpressionTreeClass *) objc;

  bool result = BaseDataOperation::Read(in,objc,name);
  if(CheckReadKeyWord(in,LocalParameterKeyWord)) {
    DataSetOfObjectsClass *simpleparameterclass = ctree->PointerToAllowedClasses();
    result = simpleparameterclass->ReadInClassNamePairsWithoutKeyWord(in);
    if(Parameters.Read(in,simpleparameterclass,name)) {

      StreamObjectInput str(in,' ');
      String next = str.ReadNext();
      if(next == "(") {
	String nodename;
	result = result && CreateFunctionOrConstantNode(in,nodename,ctree,true);
      } else {
	cerr << "ERROR: In ExpressionTree expected '(', got '" << next << "'" << endl;
	result = false;
      }
    } else {
      cerr << "Error read of Expression Tree: " << name << endl;
      result = false;
    }
  } else {
    cerr << "ERROR: failed read of ExpressionTree" << endl;
    result = false;
  }
  return result;
}
 
/*F ans = ReadInExpression(in,ctree) read in expression (top)
**
**  DESCRIPTION
**    in: The input stream
**    ctree: The expressin tree class
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::ReadInExpressionNow(istream& in, DataExpressionTreeClass *ctree)
{
  bool result = true;
  StreamObjectInput str(in,' ');
  String paren = str.ReadNext();
  String nodename;
  if(paren == "(") {
    CreateFunctionOrConstantNode(in,nodename,ctree,true);
  } else {
    cerr << "Expression does not begin with '(': " << endl;
    cerr << paren << endl;
    result = false;
  }
  return result;
  
}
/*F ans = CreateFunctionOrConstantNode()  . .  read in expression
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::CreateFunctionOrConstantNode(istream& in, String& parent, 
							  DataExpressionTreeClass *ctree,
							  bool topnode) {
  StreamObjectInput str(in,' ');
  String op = str.ReadNext();
  bool result = true;
  BaseDataOperation *operation = ctree->GetFunctionNode(op);
  String nodename;
  if(operation != NULL) {
    if(topnode)
      nodename = AddOperationNode(operation);
    else
      nodename = AddOperationNode(operation,parent);
    if(topnode)
      Tree.SetRootNode(nodename);
    result = ReadInExpressionArguments(in,nodename,ctree);
  }
  else {
    DataObjectClass *cls = ctree->GetConstantTypeNode(op);
    if(cls != NULL) {
      nodename = AddConstantObjectNode(in,cls,parent,topnode);
      if(topnode)
	Tree.SetRootNode(nodename);
      String paren = str.ReadNext();
      if(!(paren == ")")) {
	cerr << "End Paren of constant expresion not found, instead '" << paren << "'" << endl;
      }
    } else {
      cerr << "Expected Operation or Class Type, got: '" << op << "'" << endl;
      result = false;
    }
  }
  return result;
}
/*F ans = ReadInExpressionArguments(in,rootop,ctree)  . .  read in expression
**
**  DESCRIPTION
**    in: The input stream
**    rootop: The node name of the root operation
**    ctree: The expression tree class
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::ReadInExpressionArguments(istream& in,
						       String& rootop,
						       DataExpressionTreeClass *ctree)
{
  bool result = true;
  StreamObjectInput str(in,' ');
  String arg = str.ReadNext();
  while(result && !(arg == ")"))
    {
      if(arg == "(") {
	CreateFunctionOrConstantNode(in,rootop,ctree,false);
	}
      else if(ParameterInList(arg))
	{
	  AddParameterNode(arg,rootop);
	}
      else
	{
	  AddVariableNameNode(arg,rootop);
	}
      arg = str.ReadNext();
    }
  return result;
}
/*F ans = AddConstantObjectNode(parameter,parent)
**
**  DESCRIPTION
**    parameter: The parameter name
**    parent: The name of the parent operation
**    name: The name of the node
**
**  REMARKS
**
*/
String BaseDataExpressionTree::AddConstantObjectNode(istream& in, DataObjectClass *cls, String& parent, bool topnode)
{
  BaseDataObject *obj = (BaseDataObject *) cls->BaseDataObjectExample();
  obj->Read(in,cls,cls->NameTag);
  BaseDataExpressionTreeObject *node = new BaseDataExpressionTreeObject();
  node->SetAttribute(obj->NameTag);
  node->SetObject(obj);
  String name;
  if(topnode)
    name = AddExpressionNode(node);
  else
    name = AddExpressionNode(node,parent);
  delete node;
  return name;
}
 
/*F ans = AddParameterNode(parameter,parent)
**
**  DESCRIPTION
**    parameter: The parameter name
**    parent: The name of the parent operation
**    name: The name of the node
**
**  REMARKS
**
*/
String& BaseDataExpressionTree::AddParameterNode(String& parameter, String& parent)
{
  BaseDataExpressionTreeObject obj;
  obj.SetAttribute(parameter);
  return AddExpressionNode(&obj,parent);
}
/*F ans = AddVariableNameNode(variable,parent)
**
**  DESCRIPTION
**    variable: The instance variable name
**    parent: The name of the parent operation
**    name: The name of the node
**
**  REMARKS
**
*/
String& BaseDataExpressionTree::AddVariableNameNode(String& variable, String& parent)
{
  BaseDataExpressionTreeNode obj;
  obj.SetAttribute(variable);
  return AddExpressionNode(&obj,parent);
}
/*F name = AddOperationNode(oper) . . . . . . . . . . . .  read in expression
**
**  DESCRIPTION
**    oper: The operation to add to node
**    name: the name of the node added to the tree
**
**  REMARKS
**
*/
String BaseDataExpressionTree::AddOperationNode(BaseDataOperation *oper)
{
  BaseDataExpressionTreeOperation *toper = new 
    BaseDataExpressionTreeOperation();
  toper->SetAttribute(oper->NameTag);
  String name = AddExpressionNode(toper);
  
  delete toper;

  return name;
}
/*F ans = AddExpressionNode(oper,parent)
**
**  DESCRIPTION
**    oper: The operation to add to the node
**    parent: The parent node
**    name: The name of the node added to the tree
**
**  REMARKS
**
*/
String BaseDataExpressionTree::AddOperationNode(BaseDataOperation *oper,
						 String& parent)
{
  String nodename = AddOperationNode(oper);
  Tree.AddConnection(parent,nodename);
  return nodename;
}
 
/*F name = AddExpressionNode(node) . . . . . . . . . . . . Adds the node to the tree
**
**  DESCRIPTION
**    node: The node to be added
**    name: The name of the node (derived from tree location)
**
**  REMARKS
**
*/
String& BaseDataExpressionTree::AddExpressionNode(BaseDataExpressionTreeNode *node)
{
  String name("N");
  String num = Int2String(IDCount);  
  name.AppendToEnd(num);
  
  node->Identification = IDCount;
  node->NameTag = name;
  
  Tree.AddNode(node);
  IDCount++;
  return node->NameTag;
}
/*F name = AddExpressionNode(node,parent) . . . . . . . Add node under parent
**
**  DESCRIPTION
**    node: The node to be added
**    parent: The parent node name
**    name: The derived node name
**
**  REMARKS
**
*/
String& BaseDataExpressionTree::AddExpressionNode(BaseDataExpressionTreeNode *node,
						 String& parent)
{
  AddExpressionNode(node);
  Tree.AddConnection(parent,node->NameTag);
  return node->NameTag;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataExpressionTree
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExpressionTree::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << endl << " ---- Parameter List ----" << endl;
  ParametersClass.print(out);
  out << " ---- Parameter Values ----" << endl;
  Parameters.print(out);
  Tree.print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTree
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExpressionTree::Clone()
{
  BaseDataExpressionTree *obj = new BaseDataExpressionTree;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionTree
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExpressionTree::CopyClone(Identify * obj)
{
  BaseDataExpressionTree *objfull = (BaseDataExpressionTree *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Encode(buffer,IDCount);
  result = result && ParametersClass.EncodeThis(buffer);
  result = result && Parameters.EncodeThis(buffer);
  result = result && Tree.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Decode(buffer,IDCount);
  result = result && ParametersClass.DecodeThis(buffer);
  result = result && Parameters.DecodeThis(buffer);
  result = result && Tree.DecodeThis(buffer);
  return result;
}
 
/*F obj = GetNextNode(sons,objects,objclass,ctree,attrs,attrclass)  . . . .  evaluate subtree
**
**  DESCRIPTION
**    sons: The list of possible nodes
**    objects: The list of objects for variables
**    objclass: The object class set
**    ctree: the tree class
**    obj: The value of the node (as evaluated from the subtree)
**
**    This routine grabs the first 'son' and evaluates the underlying tree
**    to give an object back.  If the object is NULL, then the operation
**    was not successful.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExpressionTree::GetNextNode(ObjectList<String>& sons,
						    BaseDataSetOfObjects *objects,
						    DataSetOfObjectsClass *objclass,
						    DataExpressionTreeClass *ctree,
						    BaseDataSetOfObjects *attrs,
						    DataSetOfObjectsClass *attrclass)
{
  String next = sons.front();
  sons.pop_front();
  
  BaseDataExpressionTreeObject *node = (BaseDataExpressionTreeObject *) Tree.GetNode(next);
  BaseDataObject *ans = NULL;
  if(node != NULL) {
      ans = node->Evaluate(objects,objclass,this,ctree,attrs,attrclass);
  }
  return ans;
}
/*F node = GetNode(name)  . . . . . . . . . . . get node from expression tree
**
**  DESCRIPTION
**    name: the name of the node
**    node: The node object (NULL if not in tree)
**
**  REMARKS
**
*/
BaseDataExpressionTreeNode *BaseDataExpressionTree::GetNode(String& name)
{
  BaseDataExpressionTreeNode *node = NULL;
  if(Tree.NodeInTree(name))
    {
      node = (BaseDataExpressionTreeNode *) Tree.GetNode(name);
    }
  return node;
}
/*F obj = operator()(x,y,xclass,yclass) . . . . . . . . . . BaseDataExpressionTree
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
BaseDataObject *BaseDataExpressionTree::operator()(BaseDataObject *x, BaseDataObject *y,
						   DataObjectClass *xc, DataObjectClass *yc)
{
  BaseDataSetOfObjects *set = (BaseDataSetOfObjects *) x;
  DataSetOfObjectsClass *setclass = (DataSetOfObjectsClass *) xc;
  BaseDataSetOfObjects *attrs = (BaseDataSetOfObjects *) y;
  DataSetOfObjectsClass *attrclass = (DataSetOfObjectsClass *) yc;
  DataSetOfObjectsClass *clspnts = setclass->PointerToAllowedClasses();
  DataExpressionTreeClass *ctree = (DataExpressionTreeClass *) clspnts->GetObjectClass(GetType());

  

  BaseDataObject *root = Tree.getRootNode();

  ObjectList<String> top;

  top.AddObject(root->NameTag);

  BaseDataObject *ans = GetNextNode(top,set,setclass,ctree,attrs,attrclass);

  return ans;
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . . . . BaseDataExpressionTree
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
BaseDataObject *BaseDataExpressionTree::operator()(BaseDataObject *x,
					     DataObjectClass *xc)
{
  return operator()(x,x,xc,xc);
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . . . . . . BaseDataExpressionTree
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
BaseDataObject *BaseDataExpressionTree::operator()(DataObjectClass *cls,
						  BaseDataObject *x, BaseDataObject *y,
						  DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  return operator()(x,y,xc,yc);
}
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . . . . . . BaseDataExpressionTree
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
BaseDataObject *BaseDataExpressionTree::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
/*F ans = ParameterInList(name) . . . . . . . . . . . . .  is it a parameter?
**
**  DESCRIPTION
**    name: Name of the parameter to check
**    ans: True if parameter is there
**
**  REMARKS
**
*/
bool BaseDataExpressionTree::ParameterInList(String& name)
{
  return Parameters.IsInList(name);
}
 
/*F obj = GetParameter(name)  . . . . . . . . . . . . get the parameter value
**
**  DESCRIPTION
**    name: The name of of the parameter
**    obj: The object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExpressionTree::GetParameter(String& name)
{
  return Parameters.GetObject(name);
}
 
/*F slist = GetSons(nodename) . . . . . . . . . . . . . get list of son names
**
**  DESCRIPTION
**    nodename: The name of the parent node
**    slist: The list of son names
**
**  REMARKS
**
*/
ObjectList<String> *BaseDataExpressionTree::GetSons(String& nodename)
{
  return Tree.GetSons(nodename);
}
 
/*F obj = DoOperation(op,ctree,obj) . . . . . . . . . perform unary operation
**
**  DESCRIPTION
**    op: The name of the operation to perform
**    ctree: The tree class
**    obj: The object on which to perform the operation
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExpressionTree::DoOperation(String& op, DataExpressionTreeClass *ctree,
						    BaseDataObject *obj)
{
  BaseDataObject *ans = NULL;
  DataObjectClass *oclass = ctree->PointerToAllowedClasses()->GetObjectClass(obj->GetType());
  BaseDataOperation *oper = ctree->GetOperation(op);
  if(oper != NULL) {
      ans = oper->operator()(obj,oclass);
    } else {
      cerr << "ERROR: Non valid operation" << endl;
    }
  return ans;
}
/*F obj = DoOperation(op,ctree,obj1,obj2) . . . . .  perform binary operation
**
**  DESCRIPTION
**    op: The name of the operation to perform
**    ctree: The tree class
**    obj1,obj2: The objects on which to perform the operation
**
**  REMARKS
**
*/
BaseDataObject *BaseDataExpressionTree::DoOperation(String& op, DataExpressionTreeClass *ctree,
						    BaseDataObject *obj1,
						    BaseDataObject *obj2)
{
  BaseDataObject *ans = NULL;
  DataObjectClass *oclass1 = ctree->PointerToAllowedClasses()->GetObjectClass(obj1->GetType());
  DataObjectClass *oclass2 = ctree->PointerToAllowedClasses()->GetObjectClass(obj2->GetType());


  BaseDataOperation *oper = ctree->GetOperation(op);
  if(oper != NULL) {
#ifdef DEBUG_LEVEL3
    cout << "=================" << op << " =====================" << endl;
    cout << "Class1: " << oclass1->NameTag << endl;
    cout << "Class2: " << oclass2->NameTag << endl;
    oper->print(cout);
#endif
      ans = oper->operator()(obj1,obj2,oclass1,oclass2);
    }  else  {
      cerr << "Non valid operation" << endl;
    }
  return ans;
}
/*F pclasses = getParameterClasses()  . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ObjectNameClassPairs& BaseDataExpressionTree::getParameterClasses()
{
  return ParametersClass;
}
 
/*F ans = ChangeParameter(parameter) Changes the parameter value
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataExpressionTree::ChangeParameter(BaseDataObject *parameter)
{
  bool result = Parameters.AddObject(parameter);
  return result;
 }
/*S DataExpressionTreeClass
 */
/*F DataExpressionTreeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExpressionTreeClass::DataExpressionTreeClass()
{
  Identification = EXPRESSIONTREE_TREE_ID;
  NameTag = EXPRESSIONTREE_TREE_NAME;
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = NameTag;

  String title(" ------------------- Set of Operations  -------------------\n");
  Operations.setTitle(title);
  String delim("\n");
  Operations.setDelimitor(delim);
  
} 
/*F DataExpressionTreeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExpressionTreeClass::DataExpressionTreeClass(const DataExpressionTreeClass& data)
  : DataOperationClass(data),
    Operations(data.Operations),
    OperationsClass(data.OperationsClass)
{
} 
 
/*F DataExpressionTreeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataExpressionTreeClass::DataExpressionTreeClass(const int id, 
						 const String& name,
						 const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = EXPRESSIONTREE_TREE_NAME;
  String title(" ------------------- Set of Operations  -------------------\n");
  Operations.setTitle(title);
  String delim("\n");
  Operations.setDelimitor(delim);
  
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataExpressionTreeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExpressionTreeClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  OperationsClass.print(out);
  Operations.print(out);
  
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataExpressionTreeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExpressionTreeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) PointerToAllowedClasses();

  ObjectNameClassPairs newpairs;
  OperationsClass = newpairs;

  OperationsClass.Read(in);
  
  oclasses->ReplaceObjectTypes(OperationsClass);
  Operations.Read(in,oclasses,set.NameTag);

  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExpressionTreeClass::CopyClone(Identify *  objc)
{
  DataExpressionTreeClass *objcfull = (DataExpressionTreeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataExpressionTreeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExpressionTreeClass::Clone()
{
  DataExpressionTreeClass* id = new DataExpressionTreeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && Operations.EncodeThis(buffer);
  result = result && OperationsClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionTreeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && Operations.DecodeThis(buffer);
  result = result && OperationsClass.DecodeThis(buffer);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.	This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataExpressionTreeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataExpressionTree();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataExpressionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExpressionTreeClass*& obj)
{
  obj = new DataExpressionTreeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataExpressionTree
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExpressionTree*& obj)
{
  obj = new BaseDataExpressionTree;
  return obj->DecodeThis(buffer);
}
 
/*F PointerToAllowedClasses() . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataSetOfObjectsClass *DataExpressionTreeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOperation *DataExpressionTreeClass::GetFunctionNode(String& name)
{
  BaseDataOperation *op = NULL;
  if(Operations.IsInList(name))
      op = (BaseDataOperation *) Operations.GetObject(name);
  return op;
}
/*F cls = GetConstantTypeNode(name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataObjectClass *DataExpressionTreeClass::GetConstantTypeNode(String& name)
{
  DataObjectClass *cls = NULL;
  if(PointerToAllowedClasses()->IsInList(name))
      cls = (DataObjectClass *) PointerToAllowedClasses()->GetObjectClass(name);
  return cls;
}

/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOperation *DataExpressionTreeClass::GetOperation(String& name)
{
  BaseDataOperation *op = NULL;
  if(Operations.IsInList(name))
    {
      op = (BaseDataOperation *) Operations.GetObject(name);
    }
  else
    {
      cerr << "Operation not found: " << name << endl;
      Operations.print(cerr);
      cerr << endl;
      ObjectList<String> names = Operations.ListOfObjectNames();
      cerr << "Expecting:  " << names.size() << "\n" << endl;
      names.print(cerr);
      cerr << endl;
    }
  
  return op;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool DataExpressionTreeClass::AddOperation(BaseDataOperation *op)
{
  return Operations.AddObject(op);
}
/*S BaseDataExpressionAlgorithm
 */ 
/*F BaseDataExpressionAlgorithm()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExpressionAlgorithm::BaseDataExpressionAlgorithm()
  : VarsAndExpsS("VarsAndExps"),
    instanceNameListS("InstanceNameList")
{
  Identification = EXPRESSIONTREE_ALGOP_ID;
  NameTag = EXPRESSIONTREE_ALGOP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataExpressionAlgorithm(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExpressionAlgorithm::BaseDataExpressionAlgorithm(const BaseDataExpressionAlgorithm& data)
  : BaseDataAlgorithmOperation(data),
    VarsAndExpsS(data.VarsAndExpsS),
    instanceNameListS(data.instanceNameListS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataExpressionAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataExpressionAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExpressionAlgorithm::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExpressionAlgorithm::Clone()
{
  BaseDataExpressionAlgorithm *obj = new BaseDataExpressionAlgorithm(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExpressionAlgorithm::CopyClone(Identify * obj)
{
  BaseDataExpressionAlgorithm *objfull = (BaseDataExpressionAlgorithm *) obj;  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,VarsAndExpsS);
  result = result && Encode(buffer,instanceNameListS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExpressionAlgorithm::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,VarsAndExpsS);
  result = result && Decode(buffer,instanceNameListS);
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
bool BaseDataExpressionAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances*,
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
bool BaseDataExpressionAlgorithm::CheckInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass*)
{
  bool result = true;
  if(run->ParameterInList(VarsAndExpsS))
    {
    }
  else
    {
      cerr << "The Expression Parameters '" << VarsAndExpsS << "' was not in the list of parameters";
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
bool BaseDataExpressionAlgorithm::SetUpInput(BaseDataSetOfInstances *instances,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  VarsAndExps = (BaseDataKeyWords *) run->ParameterValue(VarsAndExpsS);
  if(run->ParameterInList(instanceNameListS))
    {
      instanceNameList = (BaseDataKeyWords *) run->ParameterValue(instanceNameListS)->Clone();
    }
  else
    {
      ObjectList<String> names = instances->ListOfInstanceNames();
      instanceNameList = new BaseDataKeyWords(names);
    }
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
bool BaseDataExpressionAlgorithm::Calculate(BaseDataSetOfInstances *instances,
						DataSetOfInstancesClass *instclasses,
						BaseDataAlgorithmRun*,
						DataAlgorithmRunClass*)
{
  bool result = true;
  bool attrb = false;
  ObjectList<String> keys = VarsAndExps->GetKeyWords();

  
  String source = keys.front();
  if(source == "Attribute")
    attrb = true;

  keys.pop_front();
  if(!(source == "Attribute" || source == "Instance"))
    {
      cerr << "New Attributes cannot be created... Illegal source and destination: " << source <<
	endl;
      result = false;
    }

  while(result && keys.size() > 1)
    {
      String variable = keys.front();
      keys.pop_front();
      String expression = keys.front();
      keys.pop_front();
      if(instances->IsInList(expression)) {
#ifdef DEBUG_LEVEL3
      cout << "Operate on '" << variable << "' with '" << expression << "'" << endl;
#endif
      BaseDataExpressionTree *etree = (BaseDataExpressionTree *) 
	instances->GetObject(expression);
      DataExpressionTreeClass *ctree = (DataExpressionTreeClass *) 
	    instclasses->PointerToAllowedClasses()->GetObjectClass(etree->GetType());
      
      if(attrb)
	result = result && OverAttributes(variable,etree,ctree,instances,instclasses);
      else
	result = result && LoopOverInstances(variable,etree,ctree,instances,instclasses);
      } else {
	cerr << "Expression not found: '" << expression << "' in attributes" << endl;
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
bool BaseDataExpressionAlgorithm::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun*,
							DataAlgorithmRunClass*)
{
  bool result = true;
  
//  run->AddParameter(ctree);

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
bool BaseDataExpressionAlgorithm::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  delete instanceNameList;
  return result;
}
 
/*F ans = OverAttributes(variable,etree,ctree,instances,instclasses)
**
**  DESCRIPTION
**    variable: The name of the new variable
**    etree: The tree expression to evaluate
**    ctree: The tree expression class
**    instances: the instances (for the attributes)
**    instclasses: The classes
**
**  REMARKS
**
*/
bool BaseDataExpressionAlgorithm::OverAttributes(String& variable,
						 BaseDataExpressionTree *etree,
						 DataExpressionTreeClass *,
						 BaseDataSetOfInstances *instances,
						 DataSetOfInstancesClass *instclasses)
{
#ifdef DEBUG_LEVEL3
  cout << "Loop over Attributes: " << etree->NameTag << endl;
  etree->print(cout);
  cout << "----------------------------------------------" << endl;
#endif
  BaseDataObject *obj = etree->operator()(instances,instclasses);
  obj->NameTag = variable;
  return instances->AddObject(obj);
}
/*F ans = OverAttributes(variable,etree,ctree,instances,instclasses)
**
**  DESCRIPTION
**    variable: The name of the new variable
**    etree: The tree expression to evaluate
**    ctree: The tree expression class
**    instances: the instances (for the attributes)
**    instclasses: The classes
**
**  REMARKS
**
*/
bool BaseDataExpressionAlgorithm::LoopOverInstances(String& variable,
						    BaseDataExpressionTree *etree,
						    DataExpressionTreeClass *,
						    BaseDataSetOfInstances *instances,
						    DataSetOfInstancesClass *instclasses)
{
  bool result = true;
  //DataInstanceClass *instclass = (DataInstanceClass *) 
  //  instclasses->PointerToAllowedClasses()->GetObjectClass(INSTANCE_INSTANCE_NAME);
  ObjectList<String> names = instanceNameList->GetKeyWords();
  ObjectList<String>::iterator name;
  for(name = names.begin();
      name != names.end() && result;
      name++)
    {
      BaseDataInstance *inst = instances->GetInstance(*name);
      //BaseDataObject *obj = etree->operator()(inst,instances,instclass,instclasses);
      BaseDataObject *obj = etree->operator()(inst,instances,instclasses,instclasses);
      if(obj != NULL) {
	obj->NameTag = variable;
	result = result && inst->AddAttribute(obj);
      } else {
	cerr << "ERROR in evaluation: no assignment in instance: " << *name << endl;
	result = false;
      }
    }
  
  return result;
}
/*S DataExpressionAlgorithmClass
 */
/*F DataExpressionAlgorithmClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExpressionAlgorithmClass::DataExpressionAlgorithmClass()
{
  Identification = EXPRESSIONTREE_ALGOP_ID;
  NameTag = EXPRESSIONTREE_ALGOP_NAME;
  SubClass = ALGORITHM_OPERATION_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataExpressionAlgorithmClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExpressionAlgorithmClass::DataExpressionAlgorithmClass(const DataExpressionAlgorithmClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataExpressionAlgorithmClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataExpressionAlgorithmClass::DataExpressionAlgorithmClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = ALGORITHM_OPERATION_NAME;
  EncodeDecodeClass = EXPRESSIONTREE_ALGOP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataExpressionAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExpressionAlgorithmClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataExpressionAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataExpressionAlgorithmClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExpressionAlgorithmClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataExpressionAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExpressionAlgorithmClass::CopyClone(Identify *  objc)
{
  DataExpressionAlgorithmClass *objcfull = (DataExpressionAlgorithmClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataExpressionAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExpressionAlgorithmClass::Clone()
    {
      DataExpressionAlgorithmClass* id = new DataExpressionAlgorithmClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataExpressionAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExpressionAlgorithmClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataExpressionAlgorithmClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataExpressionAlgorithm();
}
/*F PointerToAllowedClasses() . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataSetOfObjectsClass *DataExpressionAlgorithmClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataExpressionAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExpressionAlgorithmClass*& obj)
     {
     obj = new DataExpressionAlgorithmClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataExpressionAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExpressionAlgorithm*& obj)
     {
     obj = new BaseDataExpressionAlgorithm;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataParameterizedExpression
 */ 
/*F BaseDataParameterizedExpression()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParameterizedExpression::BaseDataParameterizedExpression()
{
  Identification = EXPRESSIONTREE_PARAM_ID;
  NameTag = EXPRESSIONTREE_PARAM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataParameterizedExpression(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataParameterizedExpression::BaseDataParameterizedExpression(const BaseDataParameterizedExpression& data)
  : BaseDataParameterizedFunction(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataParameterizedExpression
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataParameterizedExpression::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataParameterizedExpression
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataParameterizedExpression::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataParameterizedFunction::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataParameterizedExpression
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataParameterizedExpression::print(ostream& out) const
{
  BaseDataParameterizedFunction::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterizedExpression
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataParameterizedExpression::Clone()
{
  BaseDataParameterizedExpression *obj = new BaseDataParameterizedExpression;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterizedExpression
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataParameterizedExpression::CopyClone(Identify * obj)
{
  BaseDataParameterizedExpression *objfull = (BaseDataParameterizedExpression *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterizedExpression
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedExpression::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterizedExpression
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedExpression::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::DecodeThis(buffer);
  return result;
}
/*F InsertParameter(obj)
**
**  DESCRIPTION
**    obj: The object to be inserted in the expression
**
**  REMARKS
**
*/
bool BaseDataParameterizedExpression::InsertParameter(BaseDataObject *obj)
{
  BaseDataExpressionTree *etree = (BaseDataExpressionTree *) getOperation();
  return etree->ChangeParameter(obj);  
}
/*S DataParameterizedExpressionClass
 */
/*F DataParameterizedExpressionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataParameterizedExpressionClass::DataParameterizedExpressionClass()
{
  Identification = EXPRESSIONTREE_PARAM_ID;
  NameTag = EXPRESSIONTREE_PARAM_NAME;
  SubClass = "ParameterizedFunction";
  EncodeDecodeClass = NameTag;
} 
/*F DataParameterizedExpressionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataParameterizedExpressionClass::DataParameterizedExpressionClass(const DataParameterizedExpressionClass& data)
  : DataParameterizedFunctionClass(data)
{
} 
 
/*F DataParameterizedExpressionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataParameterizedExpressionClass::DataParameterizedExpressionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataParameterizedFunctionClass(id,name,descr)
{
  SubClass = PARAMETERIZED_FUNCTION_NAME;
  EncodeDecodeClass = EXPRESSIONTREE_PARAM_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataParameterizedExpressionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataParameterizedExpressionClass::print(ostream& out) const
{
  DataParameterizedFunctionClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataParameterizedExpressionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataParameterizedExpressionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataParameterizedExpressionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataParameterizedFunctionClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataParameterizedExpressionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataParameterizedExpressionClass::CopyClone(Identify *  objc)
{
  DataParameterizedExpressionClass *objcfull = (DataParameterizedExpressionClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataParameterizedExpressionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataParameterizedExpressionClass::Clone()
    {
      DataParameterizedExpressionClass* id = new DataParameterizedExpressionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterizedExpressionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterizedExpressionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterizedExpressionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterizedExpressionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::DecodeThis(buffer);
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
BaseDataObject * DataParameterizedExpressionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataParameterizedExpression();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataParameterizedExpressionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataParameterizedExpressionClass*& obj)
     {
     obj = new DataParameterizedExpressionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataParameterizedExpression
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataParameterizedExpression*& obj)
     {
     obj = new BaseDataParameterizedExpression;
     return obj->DecodeThis(buffer);
     }

/*S Utilities
 */
/*F InitialSetOfExpressionTreeEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfExpressionTreeEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataParameterizedExpressionClass,BaseDataParameterizedExpression,EXPRESSIONTREE_PARAM_NAME);

  EncodeDecodeRegisterClass(DataExpressionTreeNodeClass,BaseDataExpressionTreeNode,EXPRESSIONTREE_NODE_NAME);
  EncodeDecodeRegisterClass(DataExpressionTreeObjectClass,BaseDataExpressionTreeObject,EXPRESSIONTREE_OBJECT_NAME);
  EncodeDecodeRegisterClass(DataExpressionTreeOperationClass,BaseDataExpressionTreeOperation,EXPRESSIONTREE_ALG_NAME);
  EncodeDecodeRegisterClass(DataExpressionTreeClass,BaseDataExpressionTree,EXPRESSIONTREE_TREE_NAME);
  EncodeDecodeRegisterClass(DataExpressionAlgorithmClass,BaseDataExpressionAlgorithm,EXPRESSIONTREE_ALGOP_NAME);

//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataExpressionTreeNodeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(EXPRESSIONTREE_NODE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,DataExpressionTreeObjectClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(EXPRESSIONTREE_OBJECT_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//
//  bool (*rout3)(CommBuffer&,DataExpressionTreeOperationClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3(EXPRESSIONTREE_ALG_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  bool (*rout4)(CommBuffer&,DataExpressionTreeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout4;
//  SingleDecodeRoutine p4(EXPRESSIONTREE_TREE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p4.StructureName] = p4;
//
//  bool (*rout5)(CommBuffer&,DataExpressionAlgorithmClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout5;
//  SingleDecodeRoutine p5(EXPRESSIONTREE_ALGOP_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p5.StructureName] = p5;
//
//  String s1("Object.");
//  String s11(EXPRESSIONTREE_NODE_NAME);
//  s1.AppendToEnd(s11);
//  bool (*rout11)(CommBuffer&,BaseDataExpressionTreeNode*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s1,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//
//  String s2("Object.");
//  String s21(EXPRESSIONTREE_OBJECT_NAME);
//  s2.AppendToEnd(s21);
//  bool (*rout21)(CommBuffer&,BaseDataExpressionTreeObject*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout21;
//  SingleDecodeRoutine p21(s2,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
//
//  String s3("Object.");
//  String s31(EXPRESSIONTREE_ALG_NAME);
//  s3.AppendToEnd(s31);
//  bool (*rout31)(CommBuffer&,BaseDataExpressionTreeOperation*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout31;
//  SingleDecodeRoutine p31(s3,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p31.StructureName] = p31;
//
//  String s4("Object.");
//  String s41(EXPRESSIONTREE_TREE_NAME);
//  s4.AppendToEnd(s41);
//  bool (*rout41)(CommBuffer&,BaseDataExpressionTree*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout41;
//  SingleDecodeRoutine p41(s4,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p41.StructureName] = p41;
//
//  String s5("Object.");
//  String s51(EXPRESSIONTREE_ALGOP_NAME);
//  s5.AppendToEnd(s51);
//  bool (*rout51)(CommBuffer&,BaseDataExpressionAlgorithm*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout51;
//  SingleDecodeRoutine p51(s5,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p51.StructureName] = p51;
}
/*F AddBasicAlgorithmClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddBaseExpressionTreeClasses(DataSetOfObjectsClass& set)
{
  String nodedescr("Expression Tree Ndde Class");
  String opdescr("Expression Tree Operation Class");
  String objdescr("Expression Tree Object Class");
  String treedescr("Expression Tree  Class");
  String algdescr("Expression Tree Algorithm Class");
  String expdescr("Parameterized Expression Class");

  DataExpressionTreeNodeClass nodeclass(EXPRESSIONTREE_NODE_ID,EXPRESSIONTREE_NODE_NAME,nodedescr);
  DataExpressionTreeOperationClass opclass(EXPRESSIONTREE_ALG_ID,EXPRESSIONTREE_ALG_NAME,opdescr);
  DataExpressionTreeObjectClass objclass(EXPRESSIONTREE_OBJECT_ID,EXPRESSIONTREE_OBJECT_NAME,objdescr);
  DataExpressionTreeClass treeclass(EXPRESSIONTREE_TREE_ID,EXPRESSIONTREE_TREE_NAME,treedescr);
  DataExpressionAlgorithmClass algclass(EXPRESSIONTREE_ALGOP_ID,EXPRESSIONTREE_ALGOP_NAME,algdescr);
  DataParameterizedExpressionClass  expclass(EXPRESSIONTREE_PARAM_ID,EXPRESSIONTREE_PARAM_NAME,expdescr);
  
  set.AddObjectClass(nodeclass);
  set.AddObjectClass(opclass);
  set.AddObjectClass(objclass);
  set.AddObjectClass(treeclass);
  set.AddObjectClass(algclass);
  set.AddObjectClass(expclass);
}
