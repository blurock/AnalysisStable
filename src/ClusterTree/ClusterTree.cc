/*  FILE     ClusterTree.cc
**  PACKAGE  ClusterTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "ClusterTree" package.
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
#include "InstanceAlgorithms.hh"
#include "PredicateObjects.hh"
#include "EvaluationTree.hh"
#include "ClusterTree.hh"

/*C CountOfInstanceOnNode . . . . . . . . . . . .  extent of instance on node
**
**  DESCRIPTION
**    operator()(instanceName)
**    - The extent of the instance on the node
**
**  REMARKS
**
*/
class CountOfInstanceOnNode
{
  BaseDataClusterNode& nodeStats;
  
public:
  CountOfInstanceOnNode(BaseDataClusterNode& node)
    : nodeStats(node)
    {
    }
  double operator()(String& instanceName)
    {
      double instnodeprob = nodeStats.ExtentInCluster(instanceName);
      return instnodeprob;
    }
};
/*C MatrixOfCountsInstancesOnNodes  . . . . . . . extent of instances on node
**
**  DESCRIPTION
**    operator()(nodeName,vector)
**    - For each node, the extent of the instances on the node is calculated.
**	The vector of doubles is filled and returned.
**
**  REMARKS
**
*/
class MatrixOfCountsInstancesOnNodes
{
  BaseDataClusterTree& ClusterTree;
  ObjectList<String>& instanceNames;
  
public:
  MatrixOfCountsInstancesOnNodes(ObjectList<String>& names,
				 BaseDataClusterTree& tree)
    : ClusterTree(tree),
    instanceNames(names)
    {
    }
  
  VectorNumeric operator()(String& nodeName, VectorNumeric& probs)
    {
      BaseDataClusterNode* nodeStats = 
	(BaseDataClusterNode *) ClusterTree.Tree.GetNode(nodeName);
      
      CountOfInstanceOnNode calc(*nodeStats);
      
      transform(instanceNames.begin(),instanceNames.end(),
		probs.begin(),
		calc);
      return probs;
    }
};

/*S BaseDataClusterNode
 */ 
/*F BaseDataClusterNode() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataClusterNode::BaseDataClusterNode()
{
  Identification = CLUSTER_NODE_ID;
  NameTag = CLUSTER_NODE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  String title("----------------- Objects On Node --------------------\n");
  ElementClusterAssignment.setTitle(title);
} 
/*F BaseDataClusterNode(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataClusterNode::BaseDataClusterNode(const BaseDataClusterNode& data)
  : BaseDataTreeNode(data),
    Level(data.Level),
    InstanceCount(data.InstanceCount),
    ElementClusterAssignment(data.ElementClusterAssignment)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . Read in BaseDataClusterNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataClusterNode::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  bool result = Read(in,objc,NameTag);

  return result;
}
/*F Read(in,objc,name)	. . . . . . . . . . . . . Read in BaseDataClusterNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataClusterNode::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataClusterNodeClass *nodeclass = (DataClusterNodeClass *) objc;
  bool result = BaseDataTreeNode::Read(in,objc,name);
  StreamObjectInput strinp(in,' ');
  BaseDataLogical *logicvalue;
  DataLogicalClass *logicclass = nodeclass->getLogicClass();
  
  String key = strinp.ReadNext();
  if(key == "ClusterNode:")
    {
      
      String next = strinp.ReadNext();
      while(!(next == "END") && result)
	{
	  logicvalue = (BaseDataLogical *) logicclass->BaseDataObjectExample();
	  logicvalue->Read(in,logicclass,next);
	  logicvalue->NameTag = next;
	  
	  ElementClusterAssignment.AddObject(logicvalue);
	  delete logicvalue;

	  next = strinp.ReadNext();
	}
    }
  else
    {
      cerr << "Expecting 'ClusterNode:', recieved ";
      cerr << key << endl;
      result = false;
    }

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataClusterNode::print(ostream& out) const
{
  BaseDataTreeNode::print(out);
  out << endl << "Number of Instances: " << InstanceCount << endl;
  ElementClusterAssignment.print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataClusterNode::Clone()
{
  BaseDataClusterNode *obj = new BaseDataClusterNode;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataClusterNode::CopyClone(Identify * obj)
{
  BaseDataClusterNode *objfull = (BaseDataClusterNode *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataClusterNode::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::EncodeThis(buffer);
  result = result && ElementClusterAssignment.EncodeThis(buffer);
  result = result && Encode(buffer,Level);
  result = result && Encode(buffer,InstanceCount);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataClusterNode::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::DecodeThis(buffer);
  result = result && ElementClusterAssignment.DecodeThis(buffer);
  result = result && Decode(buffer,Level);
  result = result && Decode(buffer,InstanceCount);

  return result;
}
 
  
/*F ans = ElementInCluster(String& name)  . . . . . .  is element in cluster?
**
**  DESCRIPTION
**    name: The name of the element
**    ans: The logical value (is it in cluster)
**
**  REMARKS
**
*/
BaseDataLogical *  BaseDataClusterNode::ElementInCluster(String& name)
{
  return (BaseDataLogical *) ElementClusterAssignment.GetObject(name);
}
/*F AssignElementToCluster(name,assignment) . . . . . . assignment in cluster
**
**  DESCRIPTION
**    name: The name of the element
**    assignment: The logical value corresponding whether it is in cluster or not
**
**  REMARKS
**
*/
void  BaseDataClusterNode::AssignElementToCluster(String& name, 
						  BaseDataLogical *assignment)
{
  assignment->NameTag = name;
  ElementClusterAssignment.AddObject(assignment);
  InstanceCount = NumberOfElementsInCluster();
}
/*F num = NumberOfElementsInCluster() . . . . . . . . . . . . . . . how many?
**
**  DESCRIPTION
**    num: The number of elements (could be fractional)
**
**  REMARKS
**
*/
double BaseDataClusterNode::NumberOfElementsInCluster()
{
  ObjectList<int> empty;
  ObjectList<String> names = ElementClusterAssignment.ListOfObjectNames(empty);
  double value = 0.0;
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end(); name++)
    {
      value += ExtentInCluster(*name);
    }
  return value;
}
/*F prob = ExtentInCluster(name)  . . . . . . to what extent [0,1] in cluster
**
**  DESCRIPTION
**    name: The name of the element
**    prob: The extent as a number between zero and one
**
**    If the element is not in the list, then zero is returned
**
**  REMARKS
**
*/
double BaseDataClusterNode::ExtentInCluster(String& name)
{
  double value;
  
  if(ElementClusterAssignment.IsInList(name))
    {
      BaseDataLogical *logicvalue = (BaseDataLogical *) ElementClusterAssignment.GetObject(name);
      value = logicvalue->GetValue();
    }
  else
    {
      value = 0.0;
    }
  return value;
}
/*F prob = ProbabilityOfElement(name) . . . . . . . to what extent in cluster
**
**  DESCRIPTION
**    name: The name of the element
**    prob: The probability
**
**    If the element is not in the list, then zero is returned
**
**  REMARKS
**
*/
double BaseDataClusterNode::ProbabilityOfElement(String& name)
{
  return ExtentInCluster(name) / NumberOfElementsInCluster();
}
 
/*F vec = ExtentInCluster(instances)  . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    names: The list of instance names
**    vec: The vector of probabilities that instance is on node
**
**  REMARKS
**
*/
VectorNumeric *BaseDataClusterNode::ExtentInCluster(ObjectList<String>& names)
{
  VectorNumeric *extents = new VectorNumeric(names.size());
  CountOfInstanceOnNode calc(*this);
  
  transform(names.begin(),names.end(),
	    extents->begin(),
	    calc);
  return extents;
}
/*F vec = ExtentInCluster(instances)  . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    names: The list of instance names
**    mat: The matrix(1,n) of probabilities that instance is on node
**    
**  REMARKS
**
*/
MatrixNumeric *BaseDataClusterNode::ExtentInClusterAsMatrix(ObjectList<String>& names)
{
  MatrixNumeric *extents = new MatrixNumeric(1,names.size());
  CountOfInstanceOnNode calc(*this);
  
  transform(names.begin(),names.end(),
	    (*extents)[0].begin(),
	    calc);
  return extents;
}
 
/*F ilist = InstancesOnNode() . . . . . . . . . . . . . .  BaseDataClusterNode
**
**  DESCRIPTION
**    ilist: The list of Instances
**
**  REMARKS
**
*/
ObjectList<String> BaseDataClusterNode::InstancesOnNode()
{
  return ElementClusterAssignment.ListOfObjectNames();
}
/*F setInstanceCount(count)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataClusterNode::setInstanceCount(double count)
{
  InstanceCount = count;
}
/*F count = getInstanceCount()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double BaseDataClusterNode::getInstanceCount()
{
  return InstanceCount;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . BaseDataClusterNode
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
bool BaseDataClusterNode::WriteAsLine(ostream& out, DataObjectClass *objc)
{
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . BaseDataClusterNode
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
bool BaseDataClusterNode::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
    DataClusterNodeClass *clustercls = (DataClusterNodeClass *) objc;
    DataSetOfObjectsClass *classes = clustercls->PointerToAllowedClasses();
    
    SetUpClassNamePairs(&ElementClusterAssignment,classes);
    classes->getNameClassPairs().WriteAsASCII(out);
    bool result = ElementClusterAssignment.WriteAsASCII(out,classes);
    
    return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . BaseDataClusterNode
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
bool BaseDataClusterNode::WriteAsLatex(ostream& out, DataObjectClass*)
{
    return true;
}
/*S DataClusterNodeClass
 */
/*F DataClusterNodeClass()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataClusterNodeClass::DataClusterNodeClass()
{
  Identification = CLUSTER_NODE_ID;
  NameTag = CLUSTER_NODE_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataClusterNodeClass(data)	. . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataClusterNodeClass::DataClusterNodeClass(const DataClusterNodeClass& data)
  : DataTreeNodeClass(data),
    LogicClass(data.LogicClass)
{
} 
 
/*F DataClusterNodeClass(id,name,descr) . . . . . . . . . . . . . constructor
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
DataClusterNodeClass::DataClusterNodeClass(const int id, 
					   const String& name,
					   const String& descr)
  : DataTreeNodeClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = CLUSTER_NODE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .	 DataClusterNodeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataClusterNodeClass::print(ostream& out) const
{
  DataTreeNodeClass::print(out);
  LogicClass.print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . .	 DataClusterNodeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataClusterNodeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataClusterNodeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataTreeNodeClass::Read(in,set);
  LogicClass.Read(in,set);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . .	 DataClusterNodeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataClusterNodeClass::CopyClone(Identify *	 objc)
{
  DataClusterNodeClass *objcfull = (DataClusterNodeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . .	 DataClusterNodeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataClusterNodeClass::Clone()
{
  DataClusterNodeClass* id = new DataClusterNodeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .	 DataClusterNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataClusterNodeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::EncodeThis(buffer);
  result = result && LogicClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .	 DataClusterNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataClusterNodeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::DecodeThis(buffer);
  result = result && LogicClass.DecodeThis(buffer);

  return result;
}
 
/*F logclass = getLogicClass()	. . . . . . . . . . . . . . . . . get pointer
**
**  DESCRIPTION
**    logclass: The pointer to the logical class (not a new object)
**
**  REMARKS
**
*/
DataLogicalClass *DataClusterNodeClass::getLogicClass()
{
  return &LogicClass;
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
BaseDataObject * DataClusterNodeClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataClusterNode();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .	 DataClusterNodeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataClusterNodeClass*& obj)
{
  obj = new DataClusterNodeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . BaseDataClusterNode
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataClusterNode*& obj)
{
  obj = new BaseDataClusterNode;
  return obj->DecodeThis(buffer);
}
 
/*F setLevel(level)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataClusterNode::setLevel(unsigned int level)
{
  Level = level;
}
 
/*F level = getLevel()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
unsigned int BaseDataClusterNode::getLevel()
{
  return Level;
}
/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**    classes: The standard set of object classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataClusterNodeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}


/*S BaseDataClusterTree
 */ 
/*F BaseDataClusterTree()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataClusterTree::BaseDataClusterTree()
  : maxLevelS(CLUSTER_MAX_LEVEL)
{
  Identification = CLUSTER_TREE_ID;
  NameTag = CLUSTER_TREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataClusterTree(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataClusterTree::BaseDataClusterTree(const BaseDataClusterTree& data)
  : BaseDataEvaluationTree(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataClusterTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataClusterTree::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  bool result = Read(in,objc,NameTag);

  return result;
}
/*F Read(in,objc,name)	. . . . . . . . . . . . . . .  Read in BaseDataClusterTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataClusterTree::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataEvaluationTree::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataClusterTree
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataClusterTree::print(ostream& out) const
{
  BaseDataEvaluationTree::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataClusterTree
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataClusterTree::Clone()
{
  BaseDataClusterTree *obj = new BaseDataClusterTree;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataClusterTree
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataClusterTree::CopyClone(Identify * obj)
{
  BaseDataClusterTree *objfull = (BaseDataClusterTree *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataClusterTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataClusterTree::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataEvaluationTree::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataClusterTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataClusterTree::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataEvaluationTree::DecodeThis(buffer);
  // The rest

       return result;
}
/*F InitializeRootNode()  . . . . . . . . . . . . . . initialize cluster tree
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataClusterTree::InitializeRootNode(DataClusterTreeClass *treeclass)
{
  DataClusterNodeClass *nodeclass = treeclass->getNodeClass();
  if(nodeclass == NULL)
    nodeclass = InitializeNodeClass(treeclass->PointerToAllowedClasses());

  BaseDataClusterNode *rootnode = (BaseDataClusterNode *) nodeclass->BaseDataObjectExample();
  Tree.SetNewNodeName(rootnode);
  rootnode->setLevel(0);
  Tree.AddNode(rootnode);
  Tree.SetRootNode(rootnode->NameTag);
}
/*F AddEmptyNode(parent,instance,membership)
**
**  DESCRIPTION
**    parent:  The parent node
      node: The node class
**    instance:
**    membership:
**
**  REMARKS
**
*/
BaseDataClusterNode *BaseDataClusterTree::AddEmptyNode(BaseDataClusterNode *parent,
						       DataClusterNodeClass *nodeclass,
						       BaseDataInstance* instance,
						       BaseDataLogical *membership)
{
  BaseDataClusterNode *node = (BaseDataClusterNode *) nodeclass->BaseDataObjectExample();
  String name = Tree.SetNewNodeName(node,parent->NameTag);
  node->setLevel(parent->getLevel() + 1);
  Tree.AddNode(node);
  Tree.AddConnection(parent->NameTag,node->NameTag);
  return (BaseDataClusterNode *) Tree.GetNode(node->NameTag);
}
 
/*F logic = getLogicType()
**
**  DESCRIPTION
**    logic: The name of the logic class
**
**  REMARKS
**
*/
String BaseDataClusterTree::getLogicType()
{
  return LogicType;
}
/*F TransferClusterTree(tree)
**
**  DESCRIPTION
**    tree: The essential tree information to pass
**
**  REMARKS
**
*/
void BaseDataClusterTree::TransferClusterTree(BaseDataClusterTree *tree)
{
  Count = tree->getInstanceCount();
  LogicType = tree->getLogicType();
  Tree = tree->Tree;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . BaseDataClusterTree
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
bool BaseDataClusterTree::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  return BaseDataEvaluationTree::WriteAsLine(out,objc);
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . BaseDataClusterTree
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
bool BaseDataClusterTree::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result =  BaseDataEvaluationTree::WriteAsASCII(out,objc);
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . BaseDataClusterTree
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
bool BaseDataClusterTree::WriteAsLatex(ostream& out, DataObjectClass *obj)
{
  BaseDataEvaluationTree::WriteAsLatex(out,obj);
    return true;
}
 
/*F max = getMaxLevel() . . . . . . . . . . . . . . . . . BaseDataClusterTree
**
**  DESCRIPTION
**    max: The upper limit to the tree level
**
**  REMARKS
**
*/
unsigned int BaseDataClusterTree::getMaxLevel()
{
  return maxLevel;
}
 
/*S DataClusterTreeClass
 */
/*F DataClusterTreeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataClusterTreeClass::DataClusterTreeClass()
  : NodeClassS(CLUSTER_NODE_NAME),
    NodeClass(NULL)
{
  Identification = CLUSTER_TREE_ID;
  NameTag = CLUSTER_TREE_NAME;
  SubClass = EVALUATIONTREE_TREE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataClusterTreeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataClusterTreeClass::DataClusterTreeClass(const DataClusterTreeClass& data)
  : DataEvaluationTreeClass(data),
    NodeClassS(data.NodeClassS)
{
  NodeClass = (DataClusterNodeClass *) PointerClone(data.NodeClass);
} 
 
/*F DataClusterTreeClass(id,name,descr)	 . . . . . . . . . . . . . . . constructor
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
DataClusterTreeClass::DataClusterTreeClass(const int id, 
					   const String& name,
					   const String& descr)
  : DataEvaluationTreeClass(id,name,descr),
    NodeClassS(CLUSTER_NODE_NAME),
    NodeClass(NULL)
{
  SubClass = EVALUATIONTREE_TREE_NAME;
  EncodeDecodeClass = CLUSTER_TREE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataClusterTreeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataClusterTreeClass::print(ostream& out) const
{
  DataEvaluationTreeClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataClusterTreeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataClusterTreeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataClusterTreeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataEvaluationTreeClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataClusterTreeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataClusterTreeClass::CopyClone(Identify *	 objc)
{
  DataClusterTreeClass *objcfull = (DataClusterTreeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataClusterTreeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataClusterTreeClass::Clone()
{
  DataClusterTreeClass* id = new DataClusterTreeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataClusterTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataClusterTreeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataEvaluationTreeClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataClusterTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataClusterTreeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataEvaluationTreeClass::DecodeThis(buffer);
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
BaseDataObject * DataClusterTreeClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataClusterTree();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataClusterTreeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataClusterTreeClass*& obj)
{
  obj = new DataClusterTreeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataClusterTree
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataClusterTree*& obj)
{
  obj = new BaseDataClusterTree;
  return obj->DecodeThis(buffer);
}
/*F mat = CalculateInstancesOnSubNodes(parent)	. . matrix of instances-nodes
**
**  DESCRIPTION
**    parent: The name of the parent
**    mat: The matrix of nodes versus instances
**
**  REMARKS
**
*/
MatrixNumeric 
BaseDataClusterTree::CalculateInstancesOnSubNodes(String& parent,
						  ObjectList<String>& instancenames)
{
  ObjectList<String> *sons = Tree.GetSons(parent);
  MatrixNumeric instnodemat(sons->size(),instancenames.size());
  MatrixOfCountsInstancesOnNodes calc(instancenames,*this);
  transform(sons->begin(),sons->end(),instnodemat.begin(),instnodemat.begin(),calc);
  delete sons;
  return instnodemat;
}
/*F nclass = InitializeNodeClass(classes)
**
**  DESCRIPTION
**    classes: The possible set of classes
**
**  REMARKS
**
*/
DataClusterNodeClass *BaseDataClusterTree::InitializeNodeClass(DataSetOfObjectsClass* classes)
{

  DataClusterTreeClass *treeclass = (DataClusterTreeClass *) 
    classes->PointerToAllowedClasses()->GetObjectClass(GetType());
  DataClusterNodeClass *nclass;
  nclass = (DataClusterNodeClass *) treeclass->getNodeClass();
  if(nclass == NULL)
    {
      DataClusterNodeClass *nodeclass = (DataClusterNodeClass *)
	classes->PointerToAllowedClasses()->GetObjectClass(treeclass->getNodeClassName());
      nclass = (DataClusterNodeClass *) nodeclass->Clone();
    }
  return nclass;
}
 
/*F logic = InitializeMembership(classes)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogical *BaseDataClusterTree::InitializeMembership(DataSetOfObjectsClass *classes)
{
  DataLogicalClass *logclass = (DataLogicalClass *) classes->PointerToAllowedClasses()->GetObjectClass(LogicType);
  BaseDataLogical *logic = (BaseDataLogical *) logclass->BaseDataObjectExample();
  logic->SetValue(1.0);

  return logic;
}
/*F AddInstanceToCobwebNode(name,instance,iclass) 
**
**  DESCRIPTION
**    instance: The instance to add to the 
**  REMARKS
**
*/
void BaseDataClusterTree::AddInstanceToClusterNode(BaseDataClusterNode* node,
						   BaseDataInstance* instance,
						   BaseDataLogical *membership)
{
  node->AssignElementToCluster(instance->NameTag,membership);
  double count = getInstanceCount();
  setInstanceCount(membership->GetValue() + count);
}
 
/*F setInstanceCount(count)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataClusterTree::setInstanceCount(double count)
{
  Count = count;
}
/*F count = getInstanceCount()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double BaseDataClusterTree::getInstanceCount()
{
  return Count;
}
 
/*F nodeclass = getNodeClass()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataClusterNodeClass *DataClusterTreeClass::getNodeClass()
{
  return NodeClass;
}
 
/*F getNodeClassName(name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataClusterTreeClass::setNodeClassName(String& name)
{
  NodeClassS = name;
}
 
/*F class = getNodeClassName()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
String& DataClusterTreeClass::getNodeClassName()
{
  return NodeClassS;
}
 
/*F setNodeClass(nodeclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataClusterTreeClass::setNodeClass(DataClusterNodeClass *nodeclass)
{
  NodeClass = nodeclass;
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
bool BaseDataClusterTree::CheckInput(BaseDataSetOfInstances*,
				     DataSetOfInstancesClass*,
				     BaseDataAlgorithmRun* run,
				     DataAlgorithmRunClass*)
{
  bool result = true;
  if(!(run->ParameterInList(maxLevelS)))
    {
      cerr << "4 The parameter '"<< maxLevelS << "' was not in the list of parameters\n";
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
**    1. maxLevel: A numeric value (the maximum tree level)
**
**  REMARKS
**
*/
bool BaseDataClusterTree::SetUpInput(BaseDataSetOfInstances* instances,
				     DataSetOfInstancesClass* instancesclass,
				     BaseDataAlgorithmRun* run,
				     DataAlgorithmRunClass* rclass)
{
  bool result = true;
  BaseDataNumeric *level = (BaseDataNumeric *) run->ParameterValue(maxLevelS);
  maxLevel = (int) level->Distance();
  return result;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataSetOfObjectsClass *DataClusterTreeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}

/*S Utilities
 */
/*F CobwebClusterEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void ClusterTreeEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataClusterTreeClass,BaseDataClusterTree,CLUSTER_TREE_NAME);
  EncodeDecodeRegisterClass(DataClusterNodeClass,BaseDataClusterNode,CLUSTER_NODE_NAME);
}
/*F AddClusterTreeClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddClusterTreeClasses(DataSetOfObjectsClass& set)
{
  String clstrtreedescr("The Cluster Tree");
  String clstrnodedescr("The Cluster Node");

  DataClusterTreeClass clstrtreeclass(CLUSTER_TREE_ID,
				      CLUSTER_TREE_NAME,
				      clstrtreedescr);
  DataClusterNodeClass clstrnodeclass(CLUSTER_NODE_ID,
				      CLUSTER_NODE_NAME,
				      clstrnodedescr);

  set.AddObjectClass(clstrtreeclass);
  set.AddObjectClass(clstrnodeclass);

}
