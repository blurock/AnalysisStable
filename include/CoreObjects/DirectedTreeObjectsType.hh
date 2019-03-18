/*  FILE     DirectedTreeObjectsType.hh
**  PACKAGE  DirectedTreeObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "DirectedTreeObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_DIRECTEDTREEOBJECTSTYPE_HH
#define CoreObjects_DIRECTEDTREEOBJECTSTYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataTreeNodeClass;
class DataDirectedTreeClass;

/*C BaseDataTreeNode  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the TreeNode class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataTreeNode : public BaseDataObject
{
  String PrintName;
public:
  BaseDataTreeNode();
  BaseDataTreeNode(const BaseDataTreeNode& data);
  String& getPrintName();
  void setPrintName(String& name);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  
  virtual ostream& PrintASCIINodeInfo(ostream& out,
				      String& prefix,
				      DataDirectedTreeClass *,
				      DataObjectClass *,
				      BaseDataSetOfInstances&,
				      DataSetOfInstancesClass&);
};
/*C DataTreeNodeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataTreeNodeClass : public DataObjectClass
{
public:
  DataTreeNodeClass();
  DataTreeNodeClass(const DataTreeNodeClass& data);
  DataTreeNodeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*C BaseDataDirectedTree  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DirectedTree class 
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataDirectedTree : public BaseDataSetOfObjects
{
  BasicIdentifyGraph Tree;
  String Root;
  unsigned int NodeCount;

public:
  BaseDataDirectedTree();
  BaseDataDirectedTree(const BaseDataDirectedTree& data);

  void AddNode(BaseDataObject* node);
  void RemoveNode(const String& node);
  void SetRootNode(const String& node);
  void AddConnection(const String& parent, const String& son);
  void RemoveConnection(const String& node1, const String& node2);
  BaseDataObject* GetNode(const String& node);
  ObjectList<String> *GetSons(const String& node);
  String& GetParent(const String& node);
  bool NodeInTree(const String& node);
  BaseDataObject *getRootNode();
  void setRootNodeName(String& name);
  String& getRootNodeName();
  unsigned int getNodeCount();

  ObjectList<String> *FindLeafNodes();
  void AddSonsToSet(ObjectList<String> *set, const String& nodename);
  String SetNewNodeName(BaseDataTreeNode *node,String& base, String& parent);
  String SetNewNodeName(BaseDataTreeNode *node,String& parent);
  String SetNewNodeName(BaseDataTreeNode *node);
  virtual ostream& PrintASCIITree(ostream& out,
				  DataDirectedTreeClass *treeclass,
				  DataObjectClass *nodeclass,
				  BaseDataSetOfInstances& instances,
				  DataSetOfInstancesClass& instsclass);
  virtual ostream& PrintASCIITitle(DataDirectedTreeClass *treeclass,
				   ostream& out);
  virtual String& PrintASCIILevelPrefix(DataDirectedTreeClass *treeclass,
					unsigned int level);
  virtual ostream& PrintASCIISubTree(BaseDataTreeNode *node,
				     ostream& out,
				     unsigned int level,
				     DataDirectedTreeClass *treeclass,
				     DataObjectClass *nodeclass,
				     BaseDataSetOfInstances& instances,
				     DataSetOfInstancesClass& instsclass);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataDirectedTreeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataDirectedTreeClass : public DataObjectClass
{
public:
  String levelPrefix;
  
  DataDirectedTreeClass();
  DataDirectedTreeClass(const DataDirectedTreeClass& data);
  DataDirectedTreeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();

  virtual bool WriteAsLine(ostream&);
  virtual bool WriteAsASCII(ostream&);
  virtual bool WriteAsLatex(ostream&);
};

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
