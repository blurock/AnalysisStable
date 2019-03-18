/*  FILE     GeneralGraphType.hh
**  PACKAGE  GeneralGraph
**  AUTHOR   Mario Drobics
**
**  CONTENT
**    Class definitions for the "GeneralGraph" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_GENERALGRAPHTYPE_HH
#define CoreObjects_GENERALGRAPHTYPE_HH


void SetUpFullNameClassPairList(BaseDataSetOfObjects *, DataSetOfObjectsClass *, ostream&);
class DataGraphClass;

/*C BaseDataNode  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Node class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataNode : public BaseDataSetOfObjects
{
  ObjectList<String> NeighborNodes;
  ObjectList<String> NeighborEdges;

public:
  BaseDataNode();
  BaseDataNode(const BaseDataNode& data);

  bool addNeighbor(const String& node, const String& edge);
  bool delNeighbor(const String& node, const String& edge);
  ObjectList<String> & getNeighboredNodes();
  ObjectList<String> & getNeighboredEdges();

  bool WriteAsASCII(ostream&, DataObjectClass *);

  const String& getName() const
    {return(NameTag); }
  void setName (const String& newName)
    {NameTag = newName; }

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataNodeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataNodeClass : public DataSetOfObjectsClass
{
public:
  bool DetailedRead;

  DataNodeClass();
  DataNodeClass(const DataNodeClass& data);
  DataNodeClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass *PointerToAllowedClasses();
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataEdge  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Edge class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataEdge : public BaseDataSetOfObjects
{
  String  NodeName1;
  String  NodeName2;

public:
  BaseDataEdge();
  BaseDataEdge(const BaseDataEdge& data);
  BaseDataEdge(const String& node1, const String& node2)
    {setNodes(node1, node2); }
  bool WriteAsASCII(ostream&, DataObjectClass *);
  void setNodes(const String& node1, const String& node2)
    {NodeName1 = node1; NodeName2 = node2; }
  String getNode1()
    {return(NodeName1); }
  String getNode2()
    {return(NodeName2); }
  const String& getName() const
    {return(NameTag); }
  void setName (const String& newName)
    {NameTag = newName; }

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataEdgeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataEdgeClass : public DataSetOfObjectsClass
{
public:
  bool DetailedRead;

  DataEdgeClass();
  DataEdgeClass(const DataEdgeClass& data);
  DataEdgeClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass *PointerToAllowedClasses();
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataGraph  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Graph class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataGraph : public BaseDataObject
{
  unsigned int         NodeCount;
  unsigned int         EdgeCount;
  BaseDataSetOfObjects Nodes;
  BaseDataSetOfObjects Edges;
  bool                 AllowMultipleEdges;
  
public:
  BaseDataGraph();
  BaseDataGraph(const BaseDataGraph& data);

  String genNewNodeName();
  String genNewEdgeName();
  virtual String addNode(DataGraphClass *);
  virtual String addNode(const String& nodeName, DataGraphClass *);
  virtual String addNode(BaseDataNode * newNode);
  virtual String addEdge(const String& node1, const String& node2, DataGraphClass *);
  virtual String addEdge(const String& edgeName, const String& node1, 
			 const String& node2, DataGraphClass *);
  virtual String addEdge(BaseDataEdge * newEdge);
  bool delNode(const String& nodeName);
  bool delEdge(const String& edgeName);
  BaseDataNode * getNode(const String& newNodeName);
  BaseDataEdge * getEdge(const String& newEdgeName);
  BaseDataEdge * getEdge(const String&, const String&);
  BaseDataSetOfObjects *getNodes();
  BaseDataSetOfObjects *getEdges();
  virtual double graphDistance(const String& node1Name, const String& node2Name);
  ObjectList<String> & getNeighboredNodes(const String& nodeName);
  ObjectList<String> & getNeighboredEdges(const String& nodeName);
  
  bool ReadSimple(istream&, DataObjectClass*, const String&);
  bool ReadDetailed(istream&, DataObjectClass*, const String&);
  bool WriteAsASCII(ostream&, DataObjectClass *);
  
  const String& getName() const
    {return(NameTag); }
  void setName (const String& newName)
    {NameTag = newName; }
  bool getAllowMultipleEdges()
    {return(AllowMultipleEdges); }
  void setAllowMultipleEdges (bool newValue)
    {AllowMultipleEdges = newValue;}

  STANDARD_VIRTUAL_METHODS_OBJECT
};

/*C DataGraphClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataGraphClass : public DataObjectClass
{
public:
  DataNodeClass *NodeClass;
  DataEdgeClass *EdgeClass;

  DataGraphClass();
  DataGraphClass(const DataGraphClass& data);
  DataGraphClass(const int id, 
		    const String& name,
		    const String& descr);
  ~DataGraphClass();
  DataSetOfObjectsClass *PointerToAllowedClasses();
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif





