/*  FILE     DirectedTreeObjects.cc
**  PACKAGE  DirectedTreeObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "DirectedTreeObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
** Version 1.1
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION

#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"

/*S BaseDataTreeNode
 */ 
/*F BaseDataTreeNode()  . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataTreeNode::BaseDataTreeNode()
{
  Identification = DIRECTEDTREE_NODE_ID;
  NameTag = DIRECTEDTREE_NODE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  setPrintName(NameTag);
} 
/*F BaseDataTreeNode(data)  . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataTreeNode::BaseDataTreeNode(const BaseDataTreeNode& data)
  : BaseDataObject(data),
    PrintName(data.PrintName)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . .  Read in BaseDataTreeNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataTreeNode::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  setPrintName(NameTag);
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . .  Read in BaseDataTreeNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataTreeNode::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . .  BaseDataTreeNode
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataTreeNode::print(ostream& out) const
{
  BaseDataObject::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . .  BaseDataTreeNode
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataTreeNode::Clone()
{
  BaseDataTreeNode *obj = new BaseDataTreeNode(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . .  BaseDataTreeNode
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataTreeNode::CopyClone(Identify * obj)
{
  BaseDataTreeNode *objfull = (BaseDataTreeNode *) obj;  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . .  BaseDataTreeNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataTreeNode::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,PrintName);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . .  BaseDataTreeNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataTreeNode::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Decode(buffer,PrintName);
  return result;
}
/*F out = PrintASCIINodeInfo(out,node,prefix,treeclass,nodeclass,instances,instsclass)
**
**  DESCRIPTION
**    out: The output stream
**    node: The node to be printed
**    prefix: The ASCII prefix for the node
**    treeclass: The directed tree class
**    nodeclass: The node class
**    instances: The set of instances
**    instsclass: The instances class
**    
**  REMARKS
**
*/
ostream& BaseDataTreeNode::PrintASCIINodeInfo(ostream& out,
                                              String& prefix,
                                              DataDirectedTreeClass *,
                                              DataObjectClass *,
                                              BaseDataSetOfInstances&,
                                              DataSetOfInstancesClass&)
{
  out << prefix;
  out << getPrintName() << endl;
  return out;
}
 
/*F name = getPrintName()
**
**  DESCRIPTION
**    name: The (shorter and understandable) print name
**    
**  REMARKS
**
*/
String& BaseDataTreeNode::getPrintName()
{
  return PrintName;
}
/*F setPrintName(name)
**
**  DESCRIPTION
**    name: The (shorter and understandable) print name
**
**  REMARKS
**
*/
void BaseDataTreeNode::setPrintName(String& name)
{
  PrintName = name;
}
/*S DataTreeNodeClass
 */
/*F DataTreeNodeClass() . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataTreeNodeClass::DataTreeNodeClass()
{
  Identification = DIRECTEDTREE_NODE_ID;
  NameTag = DIRECTEDTREE_NODE_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataTreeNodeClass(data) . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataTreeNodeClass::DataTreeNodeClass(const DataTreeNodeClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataTreeNodeClass(id,name,descr)  . . . . . . . . . . . . . . constructor
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
DataTreeNodeClass::DataTreeNodeClass(const int id, 
                                     const String& name,
                                     const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DIRECTEDTREE_NODE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . DataTreeNodeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataTreeNodeClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . DataTreeNodeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataTreeNodeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataTreeNodeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . DataTreeNodeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataTreeNodeClass::CopyClone(Identify *  objc)
{
  DataTreeNodeClass *objcfull = (DataTreeNodeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . DataTreeNodeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataTreeNodeClass::Clone()
{
  DataTreeNodeClass* id = new DataTreeNodeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . DataTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataTreeNodeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . DataTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataTreeNodeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataTreeNodeClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataTreeNode();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . DataTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataTreeNodeClass*& obj)
{
  obj = new DataTreeNodeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . .  BaseDataTreeNode
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataTreeNode*& obj)
{
  obj = new BaseDataTreeNode;
  return obj->DecodeThis(buffer);
}

/*S BaseDataDirectedTree
 */ 
/*F BaseDataDirectedTree()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDirectedTree::BaseDataDirectedTree()
  : Root("Root"),
    NodeCount(0)
{
  Identification = DIRECTEDTREE_BASE_ID;
  NameTag = DIRECTEDTREE_BASE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDirectedTree(data)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDirectedTree::BaseDataDirectedTree(const BaseDataDirectedTree& data)
  : BaseDataSetOfObjects(data),
    Tree(data.Tree),
    Root(data.Root),
    NodeCount(data.NodeCount)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . .  Read in BaseDataDirectedTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDirectedTree::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . .  Read in BaseDataDirectedTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The Directed Tree is read in as:
**    1. Keyword: "DirectedTree:"
**    2. Root node
**    3. The class name pairs
**    4. The nodes 
**    5. Keyword: "Connections"
**    6. son and parent pairs (ending with END)
**
**  REMARKS
**
*/
bool BaseDataDirectedTree::Read(istream& in, DataObjectClass* objc, const String& name)
{
  if(objc->getDebugLevel() > 0)
    {
      cout << "Reading in Directed Tree" << endl;
    }
  DataDirectedTreeClass *objclass = (DataDirectedTreeClass *) objc;
  bool result = true;
  StreamObjectInput str(in,' ');

  DataSetOfObjectsClass *oclasses = objclass->PointerToAllowedClasses();
  ObjectNameClassPairs namepairs;

  String key = str.ReadNext();
  if(key == "DirectedTree:")
    {
      Root = str.ReadNext();
      if(objc->getDebugLevel() > 0)
	{
	  cout << "Directed Tree Root Node: '" << Root << "'" << endl;
	}
      key = str.ReadNext();
      if(key == "ClassNamePairs:")
	{
	  result = result && namepairs.Read(in);
	  if(objc->getDebugLevel() > 1)
	    {
	      cout << "Class Name Pairs: " << endl;
	      namepairs.print(cout);
	      cout << endl;
	    }
	  oclasses->ReplaceObjectTypes(namepairs);
	  BaseDataSetOfObjects nodes;
	  nodes.Read(in,oclasses,name);
	  ObjectList<String> names = nodes.ListOfObjectNames();
	  ObjectList<String>::iterator node;
	  for(node = names.begin(); node != names.end(); node++)
	    {
	      if(objc->getDebugLevel() > 1)
		{
		  cout << "Node: " << *node << endl;
		}
	      BaseDataObject *obj = nodes.GetObject(*node);
	      AddNode(obj);
	    }
	  key = str.ReadNext();
	  if(key == "Connections:")
	    {
	      String parent;
	      String son = str.ReadNext();
	      while(!(son == "END"))
		{
		  parent = str.ReadNext();
		  if(parent == "END")
		    {
		      cerr << "Bonds incorrect" << endl;
		      son = parent;
		      result = false;
		    }
		  else
		    {
		      AddConnection(parent,son);
		      son = str.ReadNext();
		    }
		}
	    }
	  else 
	    {
	      cerr << "Expected 'Connections:' and found '" << key << "'" << endl;
	      result = false;
	    }
	}
      else
	{
	  cerr << "Expected 'ClassNamePairs:' and found '" << key << "'" << endl;
	  result = false;
	}
	  
    }
  else
    {
      cerr << "Expected 'DirectedTree:' and found '" << key << "'" << endl;
      result = false;
    }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  BaseDataDirectedTree
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDirectedTree::print(ostream& out) const
{
  out << "\n Begin:------------------------------- Directed Tree -------------------------------\n";
  Tree.print(out);
  out << "\n End:-------------------------------   Directed Tree -------------------------------\n";

  BaseDataSetOfObjects::print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . .  BaseDataDirectedTree
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDirectedTree::Clone()
{
  BaseDataDirectedTree *obj = new BaseDataDirectedTree(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . .  BaseDataDirectedTree
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDirectedTree::CopyClone(Identify * obj)
{
  BaseDataDirectedTree *objfull = (BaseDataDirectedTree *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  BaseDataDirectedTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDirectedTree::EncodeThis(CommBuffer& buffer)
{
  bool result = true;
  result = result && BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && Tree.EncodeThis(buffer);
  result = result && Encode(buffer,Root);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  BaseDataDirectedTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDirectedTree::DecodeThis(CommBuffer& buffer)
{
  bool result = true;
  result = result && BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && Tree.DecodeThis(buffer);
  result = result && Decode(buffer,Root);
  return result;
}
 
/*F AddNode(node) . . . . . . . . . . . . . . . . . . . . .  add node to tree
**
**  DESCRIPTION
**    node: The node to add
**
**  REMARKS
**
*/
void BaseDataDirectedTree::AddNode(BaseDataObject* node)
{
  NodeCount += 1;
  AddObject(node);
  Identify id(node->Identification,node->NameTag);
  Tree.AddNodeToGraph(id,id);
}
/*F name = SetNewNodeName(node,base,parent)
**
**  DESCRIPTION
**    node: The node to name
**    base: The base name of the node (also used as print name)
**    parent: The name of the parent
**    name: The full name created for the node
**    
**  REMARKS
**
*/
String BaseDataDirectedTree::SetNewNodeName(BaseDataTreeNode *node,String& base, String& parent)
{
  String name(parent);
  String check("#");
  name.AppendToEnd(check);
  name.AppendToEnd(base);
  node->NameTag = name;
  node->setPrintName(base);
  return name;
}
/*F setnames = FindLeafNodes()
**
**  DESCRIPTION
**    setnames: The leaf node names
**    
**  REMARKS
**
*/
ObjectList<String> *BaseDataDirectedTree::FindLeafNodes() {
  String& name = getRootNodeName();
  ObjectList<String> *set = new ObjectList<String>();
  AddSonsToSet(set,name);
  return set;
}
/*F AddSonsToSet(setnames,node)
**
**  DESCRIPTION
**    setnames: The leaf node names
**    node: The node sons to add
**    
**  REMARKS
**
*/
void BaseDataDirectedTree::AddSonsToSet(ObjectList<String> *set, const String& nodename) {
  ObjectList<String> *sonset = GetSons(nodename);
  int sonsize = sonset->size();
  cout << "AddSonsToSet: " << nodename << ":  " << sonsize << endl;
  if(sonsize == 0) {
    set->AddObject(nodename);
  } else {
    ObjectList<String>::iterator name;
    for(name = (*sonset).begin(); !(name == (*sonset).end());name++) {
      AddSonsToSet(set,*name);
    }
  }
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
String *Integer2String(int num)
{
  stringstream ostrstr;
  ostrstr << num << '\0';
  String *str = new String(ostrstr.str().c_str());
  return str;
  /*
int siz = 100;
  char* ch = new char[siz];
  stringstream ostrstr;
  ostrstr << num << '\0';

  //  ostrstream ostrstr(ch, siz);

  ostrstr << num << '\0';
  String *str = new String(ch);
  delete ch;
  return str;
  */  
}
/*F name = SetNewNodeName(node,parent)
**
**  DESCRIPTION
**    node: The node to name
**    parent: The name of the parent
**    name: The full name created for the node
**
**  REMARKS
**
*/
String BaseDataDirectedTree::SetNewNodeName(BaseDataTreeNode *node,String& parent)
{
  String *num = Integer2String(NodeCount);
  String base("Node");
  base.AppendToEnd(*num);
  return SetNewNodeName(node,base,parent);
}
/*F name = SetNewNodeName(node,base,parent)
**
**  DESCRIPTION
**    node: The node to name
**
**    The node is named as the root node.
**    
**  REMARKS
**
*/
String BaseDataDirectedTree::SetNewNodeName(BaseDataTreeNode *node)
{
  node->NameTag = Root;
  node->setPrintName(Root);
  return Root;
}
/*F RemoveNode(node)  . . . . . . . . . . . .  remove the node from the graph
**
**  DESCRIPTION
**    node: The name of the node
**
**    This removes the node and all connections associated with the node
**
**  REMARKS
**
*/
void BaseDataDirectedTree::RemoveNode(const String& node)
{
  if(IsInList(node))
    {
      BaseDataObject *obj = GetObject(node);
      Identify id(obj->Identification,obj->NameTag);
      Tree.RemoveGraphNode(id);
      String n = node;
      bool ans = RemoveObject(n);
      if(!ans)
        {
          cerr << "Node already removed: " << node << "\n";
        }
    }
  else
    {
      cerr << "Unknown Node: " << node << "\n";
    }
}
 
/*F SetRootNode(node) . . . . . . . . . . . . . . set node to be root of tree
**
**  DESCRIPTION
**    node: The node to be the root
**  
**  REMARKS
**
*/
void BaseDataDirectedTree::SetRootNode(const String& node)
{
  Root = node;
}
 
/*F AddConnection(parent,son) . . . . . . . .  Add a parent directed to a son
**
**  DESCRIPTION
**    parent: The name of the parent node
**    son: The name of the son node
**
**  REMARKS
**
*/
void BaseDataDirectedTree::AddConnection(const String& parent, const String& son)
{
  if(IsInList(parent))
    {
      if(IsInList(son))
        {
          BaseDataObject *pn = GetObject(parent);
          BaseDataObject *sn = GetObject(son);
          
          Identify pid(pn->Identification,pn->NameTag);
          Identify sid(sn->Identification,sn->NameTag);
          Tree.AddBondToGraph(pid,sid);
        }
      else
        {
          cerr << "Son node not found: " << son << "\n";
        }
    }
  else
    {
      cerr << "Parent node not found: " << parent << "\n";
    }
}
 
/*F RemoveConnection(parent,son)  . . . . . . . . . . . . Remove a connection
**
**  DESCRIPTION
**    parent: The name of 'parent' node
**    son: The name of the 'son' node
**
**  REMARKS
**
*/
void BaseDataDirectedTree::RemoveConnection(const String& parent, const String& son)
{
  if(IsInList(parent))
    {
      if(IsInList(son))
        {
          BaseDataObject *pn = GetObject(parent);
          BaseDataObject *sn = GetObject(son);
          
          Identify pid(pn->Identification,pn->NameTag);
          Identify sid(sn->Identification,sn->NameTag);
          cerr << "****************************************************Cannot Remove Connections at the moment\n";
        }
      else
        {
          cerr << "Son node not found: " << son << "\n";
        }
    }
  else
    {
      cerr << "Parent node not found: " << parent << "\n";
    }
}
 
/*F obj = GetNode(node) . . . . . . . .  get the node information of the tree
**
**  DESCRIPTION
**    node: The name of the node
**    obj: The node information
**
**  REMARKS
**
*/
BaseDataObject* BaseDataDirectedTree::GetNode(const String& node)
{
  BaseDataObject *obj = NULL;
  
  if(IsInList(node))
    {
      obj = GetObject(node);
    }
  else
    {
      cerr << "Node not found: " << node << "\n";
    }
  return obj;
}
 
/*F nlist = GetSons(node) . . . . . . . . . . . . . . . . .  get list of sons
**
**  DESCRIPTION
**    node: The name of the parent node
**    nlist: The list of sons
**
**  REMARKS
**
*/
ObjectList<String> *BaseDataDirectedTree::GetSons(const String& node)
{
  ObjectList<String> *slist = new ObjectList<String>;
  if(IsInList(node))
    {
      BaseDataObject *obj = GetObject(node);
      Identify id(obj->Identification,obj->NameTag);
      SymmetricPairList<Identify> bonds(Tree.Bonds);
      bonds.OnlyWithI(id);
      ObjectList<Identify> nlist;
      bonds.VectorOfSeconds(nlist);
      ObjectList<Identify>::iterator iter;
      for(iter=nlist.begin();
          iter!=nlist.end();
          iter++)
        {
          slist->AddObject((*iter).NameTag);
        }
    }
  else
    {
      cerr << "\n  Node not in Graph: " << node << endl;
    }
  
  return slist;
}
 
/*F name = GetParent(node)  . . . . . . . . . . . . . . . . derive the parent
**
**  DESCRIPTION
**    node: The node son name
**    name: The name of the parent
**
**  REMARKS
**
*/
String& BaseDataDirectedTree::GetParent(const String& node)
{
  String *name;
  
  if(IsInList(node))
    {
      BaseDataObject *obj = GetObject(node);
      Identify id(obj->Identification,obj->NameTag);
      SymmetricPairList<Identify> bonds(Tree.Bonds);
      bonds.OnlyWithJ(id);
      if(bonds.size() > 0)
        name = new String(bonds.front().I.NameTag);
      else
        {
          name = new String(node);
          cerr << "No Parent for node (returning node name: ";
          cerr << node;
          cerr << "\n";
        }
    }
  else 
    {
      cerr << "Node not found (returning node name): ";
      cerr << node;
      cerr << "\n";
      name = new String(node);
    }
  
  return *name;
}
/*F ans = NodeInTree(node)  . . . . . . . . . true if the node is in the tree
**
**  DESCRIPTION
**    node: The name of the node
**    ans: true if the node is in the tree
**
**  REMARKS
**
*/
bool BaseDataDirectedTree::NodeInTree(const String& node)
{
  return IsInList(node);
}
 
/*F node = getRootNode()  . . . . . . . . . . . . .  get the root node object
**
**  DESCRIPTION
**    node: The node object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataDirectedTree::getRootNode()
{
  return GetNode(Root);
}
/*F name = getRootNodeName()  . . . . . . . . . . .  get the root node name
**
**  DESCRIPTION
**    node: The node name
**
**  REMARKS
**
*/
String& BaseDataDirectedTree::getRootNodeName()
{
  return Root;
}
/*F setRootNodeName(name) . . . . . . . . . . . . . .  set the root node name
**
**  DESCRIPTION
**    node: The node name
**
**  REMARKS
**
*/
void BaseDataDirectedTree::setRootNodeName(String& name)
{
  Root = name;
}
/*F out = PrintASCIITree(out,treeclass,nodeclass,instances,instsclass)
**
**  DESCRIPTION
**    out: The output stream
**    treeclass: The directed tree class
**    nodeclass: The node class
**    instances: The set of instances
**    instsclass: The instances class
**
**  REMARKS
**
*/
ostream& BaseDataDirectedTree::PrintASCIITree(ostream& out,
                                              DataDirectedTreeClass *treeclass,
                                              DataObjectClass *nodeclass,
                                              BaseDataSetOfInstances& instances,
                                              DataSetOfInstancesClass& instsclass)
{
  BaseDataTreeNode *rootnode = (BaseDataTreeNode *) getRootNode();
  PrintASCIITitle(treeclass,out);
  PrintASCIISubTree(rootnode,out,0,treeclass,nodeclass,instances,instsclass);
  return out;
}
/*F PrintASCIISubTree(node,out,level,treeclass,nodeclass,instances,instsclass)
**
**  DESCRIPTION
**    node: The node to be printed
**    out: The output stream
**    level: The current level
**    treeclass: The directed tree class
**    nodeclass: The node class
**    instances: The set of instances
**    instsclass: The instances class
**    
**  REMARKS
**
*/
ostream& BaseDataDirectedTree::PrintASCIISubTree(BaseDataTreeNode *node,
                                                 ostream& out,
                                                 unsigned int level,
                                                 DataDirectedTreeClass *treeclass,
                                                 DataObjectClass *nodeclass,
                                                 BaseDataSetOfInstances& instances,
                                                 DataSetOfInstancesClass& instsclass)
{
  String pref = PrintASCIILevelPrefix(treeclass,level);
  node->PrintASCIINodeInfo(out,pref,treeclass,nodeclass,instances,instsclass);
  ObjectList<String> *names = GetSons(node->NameTag);
  ObjectList<String>::iterator name;
  unsigned int newlevel = level + 1;
  
  for(name = names->begin();
      name != names->end();
      name++)
    {
      BaseDataTreeNode* son = (BaseDataTreeNode *) GetNode(*name);
      PrintASCIISubTree(son,out,newlevel,treeclass,nodeclass,instances,instsclass);
    }
  delete names;
  return out;
}
/*F out = PrintASCIITitle(treeclass,out)  . . . . . . . . . . . . . title out
**
**  DESCRIPTION
**    treeclass: The directed tree class
**    out: The output stream
**
**  REMARKS
**
*/
ostream& BaseDataDirectedTree::PrintASCIITitle(DataDirectedTreeClass *treeclass,
                                               ostream& out)
{
  out << "===========================================================================\n";
  out << treeclass->Description << endl;
  out << "===========================================================================\n";
  return out;
}
/*F str = PrintASCIILevelPrefix(treeclass,level)
**
**  DESCRIPTION
**    treeclass: The directed tree class
**    level: The level
**
**  REMARKS
**
*/
String& BaseDataDirectedTree::PrintASCIILevelPrefix(DataDirectedTreeClass *,
                                                    unsigned int level)
{
  String *pref = new String("#DT");
  String levelstring("----:");
  
  pref->AppendToEnd(levelstring);
  for(unsigned int il=0;il < level;il++)
    {
      pref->AppendToEnd(levelstring);
    }
  return *pref;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . .  BaseDataDirectedTree
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
bool BaseDataDirectedTree::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "Graph: " << NameTag << " with " << Tree.Nodes.size();
  out << " Nodes and " << Tree.Bonds.size() << " Bonds" << endl;
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . .  BaseDataDirectedTree
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to read
**
**  REMARKS
**
*/
bool BaseDataDirectedTree::WriteAsASCII(ostream& out, DataObjectClass *dirclass)
{
  //  DataSetOfObjectsClass *oclass = (DataSetOfObjectsClass *) dirclass;
  DataSetOfObjectsClass *classes = StandardAllowedClasses;
  //DataSetOfObjectsClass *classes = oclass->PointerToAllowedClasses();
  out << "DirectedTree:" << endl;
  out << Root << endl;
  ObjectList<String> names = ListOfObjectNames();
  ObjectList<String>::iterator name;
  ObjectNameClassPairs namepairs;
  for(name = names.begin(); name != names.end(); name++)
    {
      BaseDataObject *obj = GetObject(*name);
      DataObjectClass *objc = classes->GetObjectClass(obj->GetType());
      namepairs.AddObject(obj->NameTag,objc->NameTag);
    }
  classes->ReplaceObjectTypes(namepairs);
  namepairs.WriteAsASCII(out);
  
  BaseDataSetOfObjects::WriteAsASCII(out,classes);
  out << endl << "Connections:" << endl;
  SymmetricPairList<Identify>::iterator pair;
  for(pair = Tree.Bonds.begin();
      pair != Tree.Bonds.end();
      pair++)
    {
      out << (*pair).I.NameTag << " " << (*pair).J.NameTag << endl;
    }
  out << "END" << endl;
  return true;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . .  BaseDataDirectedTree
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
bool BaseDataDirectedTree::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  out << "%%%% The Directed Tree: '" << NameTag << "'" << endl;
  cout << "-------------------------------------------" << endl;
  objc->print(cout);
  cout << endl;
  cout << "-------------------------------------------" << endl;

  DataDirectedTreeClass *oclasses = (DataDirectedTreeClass *) objc;

  DataSetOfObjectsClass *classes = oclasses->PointerToAllowedClasses();
  out << "%%%% The set of objects in the Directed Tree" << endl;
  ObjectList<String> names = ListOfObjectNames();
  names.print(cout);
  cout << endl;
  ObjectList<String>::iterator name;
  for(name=names.begin(); name != names.end(); name++)
    {
      
      BaseDataObject *obj = GetObject(*name);
      DataObjectClass *cls = classes->GetObjectClass(obj->GetType());
      
      out << "\\begin{center}" << endl;
      out << "{\\bf " << obj->NameTag << " (" << cls->NameTag << ")}" << endl;
      out << "\\end{center}" << endl;
      cls->print(cout);
      cout << "---------------------------------------------" << endl;
      
      obj->WriteAsLatex(out,cls);
    }

  //BaseDataSetOfObjects::WriteAsLatex(out,classes);
  out << "%%%% The bonds of the Directed Tree" << endl;
  out << "\\begin{tabular}[|l|l|]\\hline" << endl;
  SymmetricPairList< Identify >::iterator pair;
  out << "Parent & Son \\\\\\hline" << endl;

  for(pair = Tree.Bonds.begin();
      pair != Tree.Bonds.end();
      pair++)
    {
      out << (*pair).I.NameTag << " & " << (*pair).J.NameTag << "\\\\\\hline" << endl;
    }
  out << "\\end{tabular}" << endl;
  return true;
}
 
/*F count = getNodeCount()  . . . . . . . . . . . . . . how many node in tree
**
**  DESCRIPTION
**    count: The number of nodes in the tree
**
**  REMARKS
**
*/
unsigned int BaseDataDirectedTree::getNodeCount()
{
  return NodeCount;
}

/*S DataDirectedTreeClass
 */
/*F DataDirectedTreeClass() . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDirectedTreeClass::DataDirectedTreeClass()
  : levelPrefix("    :")
{
  Identification = DIRECTEDTREE_BASE_ID;
  NameTag = DIRECTEDTREE_BASE_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataDirectedTreeClass(data) . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDirectedTreeClass::DataDirectedTreeClass(const DataDirectedTreeClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataDirectedTreeClass(id,name,descr)  . . . . . . . . . . . . constructor
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
DataDirectedTreeClass::DataDirectedTreeClass(const int id, 
                                             const String& name,
                                             const String& descr)
  : DataObjectClass(id,name,descr)

{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DIRECTEDTREE_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . DataDirectedTreeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDirectedTreeClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << NameTag << "  ";
  // the rest
           
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . DataDirectedTreeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDirectedTreeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDirectedTreeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . DataDirectedTreeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDirectedTreeClass::CopyClone(Identify * objc)
{
  DataDirectedTreeClass *objcfull = (DataDirectedTreeClass *) objc;
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . DataDirectedTreeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDirectedTreeClass::Clone()
{
  DataDirectedTreeClass* id = new DataDirectedTreeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . DataDirectedTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDirectedTreeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . DataDirectedTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDirectedTreeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataDirectedTreeClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataDirectedTree();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . DataDirectedTreeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDirectedTreeClass*& obj)
{
  obj = new DataDirectedTreeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  BaseDataDirectedTree
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDirectedTree*& obj)
{
  obj = new BaseDataDirectedTree;
  bool result = obj->DecodeThis(buffer);
  return result;
  
}
/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**    This in the default case points to itself (this).  
**    It is meant for the case where the set of standard objects
**    is some external (possibly global) object.
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataDirectedTreeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
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
bool DataDirectedTreeClass::WriteAsLine(ostream& out)
{
  out << NameTag << ": " << Description << endl;
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . DataObjectClass
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
bool DataDirectedTreeClass::WriteAsASCII(ostream& out)
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
bool DataDirectedTreeClass::WriteAsLatex(ostream& out)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}

/*S Utilities
 */
 
/*F AddDirectedTreeObjects(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddDirectedTreeObjects(DataSetOfObjectsClass& set)
{
  String nodedescr("Directed Tree Node Class");
  String treedescr("Directed Tree Class");
  
  DataTreeNodeClass nodeclass(DIRECTEDTREE_NODE_ID,DIRECTEDTREE_NODE_NAME,nodedescr);
  DataDirectedTreeClass treeclass(DIRECTEDTREE_BASE_ID,DIRECTEDTREE_BASE_NAME,treedescr);
  
  set.AddObjectClass(nodeclass);
  set.AddObjectClass(treeclass);
}

extern void InitialSetOfDirectedTreesEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataTreeNodeClass,BaseDataTreeNode,DIRECTEDTREE_NODE_NAME);
  EncodeDecodeRegisterClass(DataDirectedTreeClass,BaseDataDirectedTree,DIRECTEDTREE_BASE_NAME);
//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataTreeNodeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(DIRECTEDTREE_NODE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,DataDirectedTreeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(DIRECTEDTREE_BASE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//  
//  String s1("Object.");
//  String s11(DIRECTEDTREE_NODE_NAME);
//  s1.AppendToEnd(s11);
//  bool (*rout11)(CommBuffer&,BaseDataTreeNode*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s1,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//
//  String s2("Object.");
//  String s21(DIRECTEDTREE_BASE_NAME);
//  s2.AppendToEnd(s21);
//  bool (*rout21)(CommBuffer&,BaseDataDirectedTree*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout21;
//  SingleDecodeRoutine p21(s2,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
  
}

