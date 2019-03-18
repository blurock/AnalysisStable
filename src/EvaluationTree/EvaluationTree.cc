/*  FILE     EvaluationTree.cc
**  PACKAGE  EvaluationTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "EvaluationTree" package.
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
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "EvaluationTree.hh"

/*S BaseDataEvaluationTree
 */ 
/*F BaseDataEvaluationTree()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataEvaluationTree::BaseDataEvaluationTree()
{
  Identification = EVALUATIONTREE_TREE_ID;
  NameTag = EVALUATIONTREE_TREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataEvaluationTree(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataEvaluationTree::BaseDataEvaluationTree(const BaseDataEvaluationTree& data)
  : BaseDataAlgorithmOperation(data),
    Tree(data.Tree)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataEvaluationTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataEvaluationTree::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataEvaluationTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataEvaluationTree::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  result = result && Tree.Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataEvaluationTree
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataEvaluationTree::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "The Evaluation Tree:\n";
  Tree.print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataEvaluationTree
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataEvaluationTree::Clone()
{
  BaseDataEvaluationTree *obj = new BaseDataEvaluationTree;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataEvaluationTree
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataEvaluationTree::CopyClone(Identify * obj)
{
  BaseDataEvaluationTree *objfull = (BaseDataEvaluationTree *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataEvaluationTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEvaluationTree::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Tree.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataEvaluationTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEvaluationTree::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Tree.DecodeThis(buffer);

  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . .  BaseDataEvaluationTree
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
bool BaseDataEvaluationTree::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  return BaseDataAlgorithmOperation::WriteAsLine(out,objc);
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . .  BaseDataEvaluationTree
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
bool BaseDataEvaluationTree::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  DataEvaluationTreeClass *treeclass = (DataEvaluationTreeClass *) objc;
  bool result = BaseDataAlgorithmOperation::WriteAsASCII(out,objc);
  result = result && Tree.WriteAsASCII(out,&treeclass->TreeClass);
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . .  BaseDataEvaluationTree
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
bool BaseDataEvaluationTree::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  DataEvaluationTreeClass *treeclass = (DataEvaluationTreeClass *) objc;
  bool result = Tree.WriteAsLatex(out,&(treeclass->TreeClass));
  return result;
}
/*S DataEvaluationTreeClass
 */
/*F DataEvaluationTreeClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataEvaluationTreeClass::DataEvaluationTreeClass()
{
  Identification = EVALUATIONTREE_TREE_ID;
  NameTag = EVALUATIONTREE_TREE_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataEvaluationTreeClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataEvaluationTreeClass::DataEvaluationTreeClass(const DataEvaluationTreeClass& data)
  : DataAlgorithmOperationClass(data),
    TreeClass(data.TreeClass)
{
} 
 
/*F DataEvaluationTreeClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataEvaluationTreeClass::DataEvaluationTreeClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = EVALUATIONTREE_TREE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataEvaluationTreeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataEvaluationTreeClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  TreeClass.print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . DataEvaluationTreeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataEvaluationTreeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataEvaluationTreeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  result = result && TreeClass.Read(in,set);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataEvaluationTreeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataEvaluationTreeClass::CopyClone(Identify *  objc)
{
  DataEvaluationTreeClass *objcfull = (DataEvaluationTreeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataEvaluationTreeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataEvaluationTreeClass::Clone()
    {
      DataEvaluationTreeClass* id = new DataEvaluationTreeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataEvaluationTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEvaluationTreeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  result = result && TreeClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataEvaluationTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEvaluationTreeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  result = result && TreeClass.DecodeThis(buffer);

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
BaseDataObject * DataEvaluationTreeClass::BaseDataObjectExample()
{ 
  //cout << "Make EvaluationTree Example\n";
  return (BaseDataObject *) new BaseDataEvaluationTree();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataEvaluationTreeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataEvaluationTreeClass*& obj)
     {
     obj = new DataEvaluationTreeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataEvaluationTree
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataEvaluationTree*& obj)
     {
     obj = new BaseDataEvaluationTree;
     return obj->DecodeThis(buffer);
     }
/*S Utility
 */
 
/*F AddEvaluationClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void AddEvaluationTreeClasses(DataSetOfObjectsClass& set)
{
  String evaldescr("Evaluation Tree Class");
  DataEvaluationTreeClass evalclass(EVALUATIONTREE_TREE_ID,EVALUATIONTREE_TREE_NAME,evaldescr);
  set.AddObjectClass(evalclass);
}
 
/*F InitialEvaluationTreeEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialEvaluationTreeEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataEvaluationTreeClass,BaseDataEvaluationTree,EVALUATIONTREE_TREE_NAME);
  
//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataEvaluationTreeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(EVALUATIONTREE_TREE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  String s11("Object.");
//  String s111(EVALUATIONTREE_TREE_NAME);
//  s11.AppendToEnd(s111);
//  bool (*rout11)(CommBuffer&,BaseDataEvaluationTree*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s11,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
}
