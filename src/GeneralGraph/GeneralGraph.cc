/*  FILE     GeneralGraph.cc
**  PACKAGE  GeneralGraph
**  AUTHOR   Mario Drobics
**
**  CONTENT
**    Exported functions for the "GeneralGraph" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "GeneralGraph.hh"

/*S BaseDataGraph
 */ 
/*F BaseDataGraph()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGraph::BaseDataGraph()
  : NodeCount(0),
    EdgeCount(0),
    AllowMultipleEdges(true)
{
  Identification = GENERALGRAPH_GRAPH_ID;
  NameTag = GENERALGRAPH_GRAPH_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  AllowMultipleEdges = false;
} 
/*F BaseDataGraph(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGraph::BaseDataGraph(const BaseDataGraph& data)
  : BaseDataObject(data),
    NodeCount(data.NodeCount),
    EdgeCount(data.EdgeCount),
    Nodes(data.Nodes),
    Edges(data.Edges),
    AllowMultipleEdges(data.AllowMultipleEdges)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGraph
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGraph::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGraph
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGraph::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataGraphClass *graphclass = (DataGraphClass *) objc;
  bool result = BaseDataObject::Read(in,objc,name);  
  BaseDataNode *node;
  BaseDataEdge *edge;
  bool detailed = true;
  StreamObjectInput str(in,' ');
  String val;
  
  if (result)
    {
      val = str.ReadNext();
      if (val == "Detailed:")
	detailed = true;
      else 
	if (val == "Simple:")
	  detailed = false;
	else
	  {
	    cerr << "Error: Unknown input mode \nOptions: detailed | simple \n";
	    result = false;
	  }
    }

  if (result)
    {
      val = str.ReadNext();
      if (val == "AllowMultipleEdges")
	{
	  AllowMultipleEdges = true;
	  val = str.ReadNext();
	}
      else 
	AllowMultipleEdges = false;
    }

  if (result)
    {
      // Read in Nodes (NodeCount, SetOfObjects)  
      if (val == "NodeCount:")
	{
	  val = str.ReadNext();
	  NodeCount = val.ToInteger();
	  val = str.ReadNext();
	}
      
      DataNodeClass *nodeclass = graphclass->NodeClass;

      if(nodeclass != NULL)
	{
	  nodeclass->DetailedRead = detailed;

	  if (!detailed)
	    {
	      if (!(val == "ClassNamePairs:"))
		cerr << "Error reading ClassNamePairs!" << endl;
	      else
		{
		  ObjectNameClassPairs nodeparameters;
		  nodeparameters.Read(in);
		  nodeclass->ReplaceObjectTypes(nodeparameters);
		  val = str.ReadNext();
		}
	    }
	  
	  while (!(val == "END"))
	    {
	      node = (BaseDataNode*) nodeclass->BaseDataObjectExample();
	      node->setName(val);
	      result = result && node->Read(in,nodeclass,val);
	      result = result && !(addNode(node) == "");
	      val = str.ReadNext();
	      delete node;
	    }
	}
      else
	{
	  cerr << "Node Class not defined: Cannot Read" << endl;
	  result = false;
	}
    }

  if (result)
    {
      // Read in Edges (EdgeCount, SetOfObjects)
      
      val = str.ReadNext();
      if (val == "EdgeCount:")
	{
	  val = str.ReadNext();
	  EdgeCount = val.ToInteger();
	  val = str.ReadNext();
	}
      
      DataEdgeClass *edgeclass = graphclass->EdgeClass;
      if(edgeclass != NULL)
	{
	  edgeclass->DetailedRead = detailed;

	  if (!detailed)
	    {
	      ObjectNameClassPairs edgeparameters;
	      edgeparameters.Read(in);
	      edgeclass->ReplaceObjectTypes(edgeparameters);
	      val = str.ReadNext();
	    }
	  
	  while (!(val == "END"))
	    {
	      edge = (BaseDataEdge*) edgeclass->BaseDataObjectExample();
	      edge->setName(val);
	      result = result && edge->Read(in,edgeclass,val);
	      result = result && !(addEdge(edge) == "");
	      val = str.ReadNext();
	    }
	}
      else
	{
	  cerr << "Edge Class not defined: Not read" << endl;
	  result = false;
	}
    }

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGraph::print(ostream& out) const
{
  BaseDataObject::print(out);

  out << endl;
  if (AllowMultipleEdges) out << "AllowMultipleEdges\n";
  out << "Nodecount: " << NodeCount << "\n";
  out << "Nodes: \n";
  Nodes.print(out);

  out << "\nEdgecount: " << EdgeCount << "\n";
  out << "Edges: \n";
  Edges.print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGraph
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGraph::Clone()
{
  BaseDataGraph *obj = new BaseDataGraph(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGraph
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGraph::CopyClone(Identify * obj)
{
  BaseDataGraph *objfull = (BaseDataGraph *) obj;
  *this = *objfull;
  BaseDataObject::CopyClone(obj);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraph::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  if (result) result = result && Encode(buffer,NodeCount);
  if (result) result = result && Nodes.EncodeThis(buffer);

  if (result) result = result && Encode(buffer,EdgeCount);
  if (result) result = result && Edges.EncodeThis(buffer);

  if (result) result = result && Encode(buffer,AllowMultipleEdges? 1:0);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGraph::DecodeThis(CommBuffer& buffer)
{
  int intBool;

  bool result = BaseDataObject::DecodeThis(buffer);
  if (result) result = result && Decode(buffer,NodeCount);
  if (result) result = result && Nodes.DecodeThis(buffer);

  if (result) result = result && Decode(buffer,EdgeCount);
  if (result) result = result && Edges.DecodeThis(buffer);

  if (result) result = result && Decode(buffer,intBool);
  AllowMultipleEdges = (intBool==1);

  return result;
}

/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataGraph
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
bool BaseDataGraph::WriteAsASCII(ostream& out, DataObjectClass *objClass)
{
  bool result = BaseDataObject::WriteAsASCII(out,objClass);  
  DataGraphClass * objc = (DataGraphClass *) objClass;
  ObjectList<String> nameList;
  ObjectList<String>::iterator nameIterator;
  BaseDataNode * node;
  BaseDataEdge * edge;

  out << "WriteOutput ---------------- Write Output ---------------" << endl;
  out << "Attributes:" << endl;
  out << "Detailed:" << endl;

  if (AllowMultipleEdges) out << "AllowMultipleEdges\n";
 
  out << "NodeCount: " << NodeCount << endl;
  nameList = Nodes.ListOfObjectNames();
  for (nameIterator = nameList.begin(); 
       nameIterator != nameList.end(); 
       nameIterator++)
    {
      node = getNode(*nameIterator);
      node->WriteAsASCII(out,objc->NodeClass);
    }
  out << "END" << endl;
 
  out << "EdgeCount: " << EdgeCount << endl;
  nameList = Edges.ListOfObjectNames();
  for (nameIterator = nameList.begin(); 
       nameIterator != nameList.end(); 
       nameIterator++)
    {
      edge = getEdge(*nameIterator);
      edge->WriteAsASCII(out,objc->EdgeClass);
    }
  out << "END" << endl;

  return result;
}

/*F name = genNewNodeName()  . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    name:     new unique node name
**
**  REMARKS
**
*/
String BaseDataGraph::genNewNodeName()
{
  NodeCount++;
  String newNodeName("N");
  String nodeNumber(Int2String(NodeCount));
  newNodeName.AppendToEnd(nodeNumber);
  return(newNodeName);
}

/*F name = genNewEdgeName()  . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    name:     new unique edge name
**
**  REMARKS
**
*/
String BaseDataGraph::genNewEdgeName()
{
  EdgeCount++;
  String newEdgeName("E");
  String edgeNumber(Int2String(EdgeCount));
  newEdgeName.AppendToEnd(edgeNumber);
  return(newEdgeName);
}

/*F name = addNode() .  . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    name:     name of the new node
**
**  REMARKS
**
*/

String BaseDataGraph::addNode(DataGraphClass* objc)
{
  return(addNode(genNewNodeName(), objc));
}
 
/*F name = addNode(nodeName).  . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    nodeName: name of the node to insert
**
**  REMARKS
**
*/

String BaseDataGraph::addNode(const String& nodeName, DataGraphClass* objc)
{
  String         result;
  DataGraphClass *graphclass = (DataGraphClass *) objc;
  DataNodeClass  *nodeclass  = graphclass->NodeClass;
  BaseDataNode   *newNode    = (BaseDataNode*) nodeclass->BaseDataObjectExample();

  newNode->setName(nodeName);
  result = addNode(newNode);
  
  delete(newNode);

  return(result);
}
 
/*F name = addNode(newNode).  . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    newNode:  node to add
**    name:     name of the new node
**
**  REMARKS
**
*/

String BaseDataGraph::addNode(BaseDataNode * newNode)
{
  String result;

  // add newNode to Nodes
  if (Nodes.IsInList(newNode->getName()))
  {
    cerr << "Error duplicate node <" << newNode
      << "> in routine addNode\n";
    result = "";
  }
  else
  {  Nodes.AddObject(newNode);
     result = newNode->getName();
  }
  
  return(result);
}
 
/*F name = addEdge(node1, node2)  . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    node1:    first node
**    node2:    second node
**    name:     name of the new edge
**
**  REMARKS
**
*/

String BaseDataGraph::addEdge(const String& node1, const String& node2, 
			      DataGraphClass* objc)
{
  return(addEdge(genNewEdgeName(), node1, node2, objc));
}
 
/*F name = addEdge(edgeName, node1, node2) . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    edgeName: name of the edge to insert
**    node1:    first node
**    node2:    second node
**    name:     name of the new edge
**
**  REMARKS
**
*/

String BaseDataGraph::addEdge(const String& edgeName, 
			      const String& node1, const String& node2,
			      DataGraphClass* objc)
{
  String         result;
  DataGraphClass *graphclass = (DataGraphClass *) objc;
  DataEdgeClass  *edgeclass  = graphclass->EdgeClass;
  BaseDataEdge   *newEdge    = (BaseDataEdge*) edgeclass->BaseDataObjectExample();

  newEdge->setNodes(node1, node2);
  newEdge->setName(edgeName);
  result = addEdge(newEdge);
  
  delete(newEdge);

  return(result);
}

/*F name = addEdge(newEdge) . . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    newEdge:  edge to add
**    name:     name of the new edge
**
**  REMARKS
**
*/

String BaseDataGraph::addEdge(BaseDataEdge * newEdge)
{
  String result;
  BaseDataNode * node1;
  BaseDataNode * node2;
  bool error=false;

  // add newEdge to Edges
  if (Edges.IsInList(newEdge->getName()))
  {
    cerr << "Error duplicate edge <" << newEdge->getName()
      << "> in routine addEdge\n";
    result = "";
  }
  else
  {  if (!Nodes.IsInList(newEdge->getNode1()))
       {
	 cerr << "Error adding edge " << newEdge->getName();
	 cerr << ": Node1 '" << newEdge->getNode1() << "' not found\n";
	 result = "";
       }
     else
       if (!Nodes.IsInList(newEdge->getNode2()))
	 {
	   cerr << "Error adding edge " << newEdge->getName();
	   cerr << ": Node2 '" << newEdge->getNode2() << "' not found\n";
	   result = "";
	 }
       else
	 {
	   if (!AllowMultipleEdges)
	     {
	       if (getEdge(newEdge->getNode1(), newEdge->getNode2()) != NULL)
		 {
		   cerr << "Error: Multiple edge from " << getEdge(newEdge->getNode1())
			<< " to " << getEdge(newEdge->getNode2()) << " created.";
		   error = true;
		 }
	     }
	   if (!error)
	     {
	       node1 = getNode(newEdge->getNode1());
	       node1->addNeighbor(newEdge->getNode2(), newEdge->getName());
	       node2 = getNode(newEdge->getNode2());
	       node2->addNeighbor(newEdge->getNode1(), newEdge->getName());
	       Edges.AddObject(newEdge);

	       result = newEdge->getName();
	     }
	   else 
	     result = "";
	 }
  }
  
  return(result);
}
 
/*F err = delNode(nodeName) . . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    nodeName: name of the node to remove
**    err:      error code
**
**  REMARKS
**
*/

bool BaseDataGraph::delNode(const String& nodeName)
{
  // find all edges to nodeName
  //      and remove them
  // find nodeName
  //      and remove node
  //      NodeCount--;

  bool result=1;
  ObjectList<String> nodeEdges;
  ObjectList<String>::iterator edgeIterator;
  String tmpName;
  BaseDataEdge edge;

  if (Nodes.IsInList(nodeName))
    { // remove all edges to the node and the node itself
      nodeEdges = getNeighboredEdges(nodeName);
      for (edgeIterator = nodeEdges.begin(); 
	   edgeIterator != nodeEdges.end();
	   edgeIterator++)
	{
	  result = result && delEdge(*edgeIterator);
	}
      tmpName = nodeName;
      Nodes.RemoveObject(tmpName);
    }
  else
  {
    cerr << "Error finding node <" << nodeName
      << "> in routine delNode\n";
    result = false;
  }

  return(result);
}
 
/*F err = delEdge(edgeName) . . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    edgeName: name of the edge to remove
**    err:      error code
**
**  REMARKS
**
*/

bool BaseDataGraph::delEdge(const String& edgeName)
{
  bool result = true;
  BaseDataNode * node1;
  BaseDataNode * node2;
  BaseDataEdge * edge;
  String tmpName;

  if (Edges.IsInList(edgeName))
    { // remove this edge and remove it from all neighborhood relations
      edge = getEdge(edgeName);
      node1 = getNode(edge->getNode1());
      node2 = getNode(edge->getNode2());
      result = result && node1->delNeighbor(node2->getName(), edgeName);
      result = result && node2->delNeighbor(node1->getName(), edgeName);
      
      tmpName = edgeName;
      if (result) Edges.RemoveObject(tmpName);
    }
  else 
    {
      cerr << "Error finding edge <" << edgeName
	   << "> in routine delEdge\n";
      result = false;
    }

  return(result);
}

 
/*F node = getNode(nodeName)  . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    nodeName: name of the node to remove
**    node:     node with nodeName
**
**  REMARKS
**
*/

BaseDataNode * BaseDataGraph::getNode(const String& newNodeName)
{
  BaseDataNode *node = (BaseDataNode *) Nodes.GetObject(newNodeName);

  return(node);
}
 
/*F edge = getEdge(edgeName)  . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    edgeName: name of the edge to remove
**    edge:     edge with edgeName
**
**  REMARKS
**
*/

BaseDataEdge * BaseDataGraph::getEdge(const String& newEdgeName)
{
  BaseDataEdge *edge = (BaseDataEdge *) Edges.GetObject(newEdgeName);

  return(edge);
}

/*F edge = getEdge(node1, node2). . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    node1:    name of the first node
**    node2:    name of the second node
**    edge:     edge with edgeName
**
**  REMARKS
**
*/

BaseDataEdge * BaseDataGraph::getEdge(const String& node1Name,const String& node2Name)
{
  BaseDataNode *node1;
  ObjectList<String> neighboredEdges;
  ObjectList<String>::iterator iteratorEdge;
  BaseDataEdge *edge = NULL;
  bool breakCond;

  node1 = getNode(node1Name);
  neighboredEdges = node1->getNeighboredEdges();
  
  // find edge to node2
  breakCond = false;
  for (iteratorEdge = neighboredEdges.begin();
       (iteratorEdge != neighboredEdges.end()) && (!breakCond);
       iteratorEdge++)
    {
      edge = getEdge(*iteratorEdge);
      if (((edge->getNode1() == node1Name) && (edge->getNode2() == node2Name)) ||
	  ((edge->getNode1() == node2Name) && (edge->getNode2() == node1Name)))
	breakCond = true;
    }

  if (breakCond == false)
    edge = NULL;

  return(edge);
}

/*F node = getNodes() . . .  . . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    nodes:     list of nodes
**
**  REMARKS
**
*/

BaseDataSetOfObjects * BaseDataGraph::getNodes()
{
  return(&Nodes);
}
 
/*F node = getEdge() . . .  . . . . . . . . . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    edges:     list of edges
**
**  REMARKS
**
*/

BaseDataSetOfObjects * BaseDataGraph::getEdges()
{
  return(&Edges);
}
 
 
 
/*F dist = graphDistance(node1Name, node2Name). . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    node1Name: Name of the first node
**    node2Name: Name of the second node
**    err:       distance between the first and the second node
**
**  REMARKS
**
*/

double BaseDataGraph::graphDistance
       (const String& node1Name, const String& node2Name)
{
  ObjectList<String> nodeQueue;
  BaseDataKeyWords visitedNodes;
  String currentNode;
  ObjectList<String>  neighbors;
  ObjectList<String>::iterator iteratorNode;
  int depth;
  int nodesInDepth;
  double result = -1;

  if (Nodes.IsInList(node1Name) && (Nodes.IsInList(node2Name)))
    {
      // breath first search through the graph starting with node1Name until node2Name is found

      // initialize
      depth = 0;
      nodesInDepth = 1;
      nodeQueue.AddObject(node1Name);
      currentNode = "";

      // loop until found
      while ((nodeQueue.size() != 0) && (currentNode != node2Name))
	{
	  // get new node
	  currentNode = *nodeQueue.begin();
	  nodeQueue.pop_front();
	  nodesInDepth--;

	  // target found?
	  if (currentNode != node2Name)
	    {
	      // been already here
	      if (!visitedNodes.KeyWordInList(currentNode))
		{
		  visitedNodes.AddKeyWord(currentNode);	      
		  neighbors = getNeighboredNodes(currentNode);

		  // add neighbors to queue
		  for (iteratorNode = neighbors.begin();
		       iteratorNode != neighbors.end();
		       iteratorNode++)
		    nodeQueue.AddObject(*iteratorNode);
		}

	      if (nodesInDepth <= 0)
		{
		  depth++;
		  nodesInDepth = nodeQueue.size();
		}
	    }
	  else
	    result = depth;
	}
    }
  //elseestMatchingNodeName
  else
  {
    if (Nodes.IsInList(node1Name))
      cerr << "Error finding node <" << node2Name
	   << "> in routine graphDistance\n";
    else
      cerr << "Error finding node <" << node1Name
	   << "> in routine graphDistance\n";

    result = false;
  }

  return(result);
}

/*F nodeList = getNeighboredNodes(nodeName)  . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    nodeName:   name of the node
**    nodeList:   list of neighbored nodes
**
**  REMARKS
**
*/

ObjectList<String> & BaseDataGraph::getNeighboredNodes(const String& nodeName)
{
  BaseDataNode * node;
  
  node = getNode(nodeName);
  if (node) 
    return (node->getNeighboredNodes());
  else
  {
    cerr << "Error finding node <" << nodeName
      << "> in routine getNeighboredNodes\n";
    return *(new ObjectList<String>());
  }
}

/*F edgeList = getNeighboredNodes(nodeName)  . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    nodeName:   name of the node
**    edgeList:   list of neighbored edges
**
**  REMARKS
**
*/

ObjectList<String> & BaseDataGraph::getNeighboredEdges(const String& nodeName)
{
  BaseDataNode * node;
  
  node = getNode(nodeName);
  if (node) 
    return (node->getNeighboredEdges());
  else
  {
    cerr << "Error finding node <" << nodeName
      << "> in routine getNeighboredEdges\n";
    return *(new ObjectList<String>());
  }
}

 
/*S DataGraphClass
 */
/*F DataGraphClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGraphClass::DataGraphClass()
  : NodeClass(NULL), 
    EdgeClass(NULL)
{
  Identification = GENERALGRAPH_GRAPH_ID;
  NameTag = GENERALGRAPH_GRAPH_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataGraphClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGraphClass::DataGraphClass(const DataGraphClass& data)
  : DataObjectClass(data)
{
  NodeClass = (DataNodeClass*) PointerClone(data.NodeClass);
  EdgeClass = (DataEdgeClass*) PointerClone(data.EdgeClass);
} 
 
/*F DataGraphClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGraphClass::DataGraphClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr),
    NodeClass(NULL), 
    EdgeClass(NULL)
{
  SubClass = "Object";
  EncodeDecodeClass = GENERALGRAPH_GRAPH_NAME;
}

/*F ~DataGraphClass() . . . . . . . . . . . . . . . . . . . empty destructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGraphClass::~DataGraphClass()
{
  if (NodeClass != NULL) delete(NodeClass);
  if (EdgeClass != NULL) delete(EdgeClass);
} 
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGraphClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  PointerPrint(out,"Node Class: ", "No Node Class Defined",NodeClass);
  out << endl;
  PointerPrint(out,"Edge Class: ", "No Edge Class Defined",EdgeClass);
  out << endl;

       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGraphClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGraphClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  StreamObjectInput str(in,' ');
  DataSetOfObjectsClass* allowedClasses = PointerToAllowedClasses();
  String nodeName;
  String edgeName;
  
  if (result) nodeName = str.ReadNext();
  if (result && allowedClasses->IsInList(nodeName))
    NodeClass = (DataNodeClass *) allowedClasses->GetObjectClass(nodeName)->Clone();
  else
    {
      cerr << "Error in DataGraphClass::Read(): Wrong node class.\n";
      result = false;
    }

  if (result) edgeName = str.ReadNext();
  if (result && allowedClasses->IsInList(edgeName))
    EdgeClass = (DataEdgeClass *) allowedClasses->GetObjectClass(edgeName)->Clone();
  else
    {
      cerr << "Error in DataGraphClass::Read(): Wrong edge class.\n";
      result = false;
    }

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGraphClass::CopyClone(Identify *  objc)
{
  DataGraphClass *objcfull = (DataGraphClass *) objc;
  *this = *objcfull;
  DataObjectClass::CopyClone(objc);
  NodeClass = (DataNodeClass*)PointerClone(objcfull->NodeClass);
  EdgeClass = (DataEdgeClass*)PointerClone(objcfull->EdgeClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGraphClass::Clone()
    {
      DataGraphClass* id = new DataGraphClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) NodeClass);
  result = result && PointerEncode(buffer,(BaseDataObject *&) EdgeClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGraphClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer, (BaseDataObject *&) NodeClass);
  result = result && PointerDecode(buffer, (BaseDataObject *&) EdgeClass);
  return result;
}
/*F obj = BaseDataObjectExample(). . . . . . . . . . . . .  create an object
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
BaseDataObject * DataGraphClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataGraph();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGraphClass*& obj)
     {
     obj = new DataGraphClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGraphClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGraph*& obj)
     {
     obj = new BaseDataGraph;
     return obj->DecodeThis(buffer);
     }

/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**    classes: The standard set of object classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataGraphClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}


/*S BaseDataNode
 */ 
/*F BaseDataNode()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNode::BaseDataNode()
{
  Identification = GENERALGRAPH_NODE_ID;
  NameTag = GENERALGRAPH_NODE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNode(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNode::BaseDataNode(const BaseDataNode& data)
  : BaseDataSetOfObjects(data),
    NeighborNodes(data.NeighborNodes),
    NeighborEdges(data.NeighborEdges)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNode::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNode::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataNodeClass *nodec = (DataNodeClass*) objc;
  String val;
  StreamObjectInput str(in,' ');

  if (nodec->DetailedRead)
    {
      val = str.ReadNext();
      if (!(val == "ClassNamePairs:"))
	{
	  cerr << "Error reading ClassNamePairs!" << endl;
	  result = false;
	}
      else
	{
	  ObjectNameClassPairs nodeparameters;
	  nodeparameters.Read(in);
	  nodec->ReplaceObjectTypes(nodeparameters);
	  cout << "Node Parameters:" << endl;
	  nodeparameters.print(cout);
	}
    }

  result = result && BaseDataSetOfObjects::Read(in,nodec,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataNode
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNode::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  // The rest
  out << "Node: " << getName() << "\n";
  out << "Neighbored nodes: ";
  NeighborNodes.print(out);
  out << endl;
  out << "Neighbored edges: ";
  NeighborEdges.print(out);
  out << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataNode
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNode::Clone()
{
  BaseDataNode *obj = new BaseDataNode(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataNode
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNode::CopyClone(Identify * obj)
{
  BaseDataNode *objfull = (BaseDataNode *) obj;
  
  *this = *objfull;
  BaseDataObject::CopyClone(obj);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNode::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  if (result) result = result && NeighborNodes.EncodeThis(buffer);
  if (result) result = result && NeighborEdges.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNode::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  if (result) result = result && NeighborNodes.DecodeThis(buffer);
  if (result) result = result && NeighborEdges.DecodeThis(buffer);
  // The rest

  return result;
}

/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataNode
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
bool BaseDataNode::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass * sobjc = (DataSetOfObjectsClass *) objc;

  out << NameTag << endl;
  SetUpFullNameClassPairList(this, sobjc, out);
  ObjectNameClassPairs namepairs = sobjc->getNameClassPairs();
  namepairs.WriteAsASCII(out);
  BaseDataSetOfObjects::WriteAsASCII(out,objc);
  // Write out extra node info (simple node has none)
  out << endl;
  return(true);
}
 
/*F err = addNeighbor(node, edge). . . . . . . . . . . . . . .  BaseDataNode
**
**  DESCRIPTION
**    node: new neighbor node
**    edge: edge to the new node
**
**  REMARKS
**
*/
bool BaseDataNode::addNeighbor(const String& node, const String& edge)
{
  bool result=1;

  NeighborNodes.AddObject(node);
  NeighborEdges.AddObject(edge);

  if(!result)
    cerr << "Error calling addNeighbor(" << node << "," << edge << ")\n";

  return result;
}
 
/*F err = delNeighbor(node, edge). . . . . . . . . . . . . . .  BaseDataNode
**
**  DESCRIPTION
**    node: neighbor node to remove
**    edge: edge to remove
**
**  REMARKS
**
*/
bool BaseDataNode::delNeighbor(const String& node, const String& edge)
{
  bool result=1;

  NeighborNodes.RemoveObject(node);
  NeighborEdges.RemoveObject(edge);

  if(!result)
    cerr << "Error calling delNeighbor(" << node << "," << edge << ")\n";

  return result;
} 
 
/*F nodes = getNeighboredNodes(). . . . . . . . . . . . . . .  BaseDataNode
**
**  DESCRIPTION
**    nodes: list of neighbored nodes
**
**  REMARKS
**
*/
ObjectList<String> & BaseDataNode::getNeighboredNodes()
{
  return NeighborNodes;
}

/*F edges = getNeighboredEdges(). . . . . . . . . . . . . . .  BaseDataNode
**
**  DESCRIPTION
**    edges: list of neighbored edges
**
**  REMARKS
**
*/
ObjectList<String> & BaseDataNode::getNeighboredEdges()
{
  return NeighborEdges;
}
 
/*S DataNodeClass
 */
/*F DataNodeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNodeClass::DataNodeClass()
{
  Identification = GENERALGRAPH_NODE_ID;
  NameTag = GENERALGRAPH_NODE_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
  ReadAllowedClasses = false;
  ReadClassPairs = false;
} 
/*F DataNodeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNodeClass::DataNodeClass(const DataNodeClass& data)
  : DataSetOfObjectsClass(data)
{
} 
 
/*F DataNodeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataNodeClass::DataNodeClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = GENERALGRAPH_NODE_NAME;
  ReadAllowedClasses = false;
  ReadClassPairs = false;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataNodeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNodeClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataNodeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNodeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNodeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  ReadAllowedClasses = false;
  ReadClassPairs = false;

  bool result = DataSetOfObjectsClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataNodeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNodeClass::CopyClone(Identify *  objc)
{
  DataNodeClass *objcfull = (DataNodeClass *) objc;
  *this = *objcfull;
  DataObjectClass::CopyClone(objc);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataNodeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNodeClass::Clone()
    {
      DataNodeClass* id = new DataNodeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNodeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNodeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample(). . . . . . . . . . . . .  create an object
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
BaseDataObject * DataNodeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataNode();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataNodeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNodeClass*& obj)
     {
     obj = new DataNodeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNode
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNode*& obj)
     {
     obj = new BaseDataNode;
     return obj->DecodeThis(buffer);
     }

/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**    classes: The standard set of object classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataNodeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}


/*S BaseDataEdge
 */ 
/*F BaseDataEdge()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataEdge::BaseDataEdge()
{
  Identification = GENERALGRAPH_EDGE_ID;
  NameTag = GENERALGRAPH_EDGE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataEdge(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataEdge::BaseDataEdge(const BaseDataEdge& data)
  : BaseDataSetOfObjects(data),
    NodeName1(data.NodeName1),
    NodeName2(data.NodeName2)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataEdge
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataEdge::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataEdge
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataEdge::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataEdgeClass *edgec = (DataEdgeClass*) objc;
  StreamObjectInput str(in,' ');
  String val;

  if (edgec->DetailedRead)
    {
      val = str.ReadNext();
      if (!(val == "ClassNamePairs:"))
	{
	  cerr << "Error reading ClassNamePairs!" << endl;
	  result = false;
	}
      else
	{
	  ObjectNameClassPairs edgeparameters;
	  edgeparameters.Read(in);
	  edgec->ReplaceObjectTypes(edgeparameters);
	  cout << "Edge Parameters:" << endl;
	  edgeparameters.print(cout);
	}
    }

  result = result && BaseDataSetOfObjects::Read(in,edgec,name);

  NodeName1 = str.ReadNext();
  NodeName2 = str.ReadNext();
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataEdge
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataEdge::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  // The rest
  out << "Edge: " << getName();
  out << " from node " << NodeName1 << " to " << NodeName2 << "\n";

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataEdge
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataEdge::Clone()
{
  BaseDataEdge *obj = new BaseDataEdge(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataEdge
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataEdge::CopyClone(Identify * obj)
{
  BaseDataEdge *objfull = (BaseDataEdge *) obj;
  
  *this = *objfull;
  BaseDataObject::CopyClone(obj);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataEdge
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEdge::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  if (result) result = result && NodeName1.EncodeThis(buffer);
  if (result) result = result && NodeName2.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataEdge
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEdge::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  if (result) result = result && NodeName1.DecodeThis(buffer);
  if (result) result = result && NodeName2.DecodeThis(buffer);
  // The rest

  return result;
}
 
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataEdge
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
bool BaseDataEdge::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass * sobjc = (DataSetOfObjectsClass *) objc;

  out << NameTag << endl;
  SetUpFullNameClassPairList(this, sobjc, out);
  sobjc->getNameClassPairs().WriteAsASCII(out);
  BaseDataSetOfObjects::WriteAsASCII(out,objc);
  out << endl;
  out << NodeName1 << " " << NodeName2 << endl;
  return(true);
}
 
/*S DataEdgeClass
 */
/*F DataEdgeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataEdgeClass::DataEdgeClass()
{
  Identification = GENERALGRAPH_EDGE_ID;
  NameTag = GENERALGRAPH_EDGE_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
  ReadAllowedClasses = false;
  ReadClassPairs = false;
} 
/*F DataEdgeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataEdgeClass::DataEdgeClass(const DataEdgeClass& data)
  : DataSetOfObjectsClass(data)
{
} 
 
/*F DataEdgeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataEdgeClass::DataEdgeClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = GENERALGRAPH_EDGE_NAME;
  ReadAllowedClasses = false;
  ReadClassPairs = false;

}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataEdgeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataEdgeClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataEdgeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataEdgeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataEdgeClass::Read(istream& in, DataSetOfObjectsClass &set)
{

  bool result = DataSetOfObjectsClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataEdgeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataEdgeClass::CopyClone(Identify *  objc)
{
  DataEdgeClass *objcfull = (DataEdgeClass *) objc;
  *this = *objcfull;
  DataObjectClass::CopyClone(objc);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataEdgeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataEdgeClass::Clone()
    {
      DataEdgeClass* id = new DataEdgeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataEdgeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEdgeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataEdgeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEdgeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample(). . . . . . . . . . . . .  create an object
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
BaseDataObject * DataEdgeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataEdge();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataEdgeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataEdgeClass*& obj)
     {
     obj = new DataEdgeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataEdge
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataEdge*& obj)
     {
     obj = new BaseDataEdge;
     return obj->DecodeThis(buffer);
     }

/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**    classes: The standard set of object classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataEdgeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}


/*F InitialSetOfPopulationEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfGeneralGraphEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataGraphClass,BaseDataGraph,GENERALGRAPH_GRAPH_NAME);
  EncodeDecodeRegisterClass(DataNodeClass,BaseDataNode,GENERALGRAPH_NODE_NAME);
  EncodeDecodeRegisterClass(DataEdgeClass,BaseDataEdge,GENERALGRAPH_EDGE_NAME);
}


/*F AddPopulationClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddGeneralGraphClasses(DataSetOfObjectsClass& set)
{
  String objdescr("Single GeneralGraph Graph");  
  DataGraphClass
    gclass(GENERALGRAPH_GRAPH_ID,GENERALGRAPH_GRAPH_NAME,objdescr);
  set.AddObjectClass(gclass);

  objdescr = "Single GeneralGraph Node";  
  DataNodeClass
    nodeclass(GENERALGRAPH_NODE_ID,GENERALGRAPH_NODE_NAME,objdescr);
  set.AddObjectClass(nodeclass);

  objdescr = "Single GeneralGraph Edge";  
  DataEdgeClass
    edgeclass(GENERALGRAPH_EDGE_ID,GENERALGRAPH_EDGE_NAME,objdescr);
  set.AddObjectClass(edgeclass);
}

/*F SetUpFullClassPairList(set,setclass). . . . . . . . . . .  BaseDataGraph
**
**  DESCRIPTION
**    set:  BaseDataSetOfObjects
**    setclass: DataSetOfObjects
**    out: output stream
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
void SetUpFullNameClassPairList(BaseDataSetOfObjects *cset,
				DataSetOfObjectsClass *setclass,
				ostream& out)
{
  ObjectNameClassPairs namepairs;
  ObjectList<String> names = cset->ListOfObjectNames();
  ObjectList<String>::iterator name;
  BaseDataObject * obj;
  DataObjectClass * cls;
  
  for(name=names.begin(); name != names.end() ; name++)
    {
      obj = cset->GetObject(*name);
      cls = setclass->PointerToAllowedClasses()->GetObjectClass(obj->GetType());
      namepairs.AddObject(obj->NameTag,cls->NameTag);
    }
  setclass->ReplaceObjectTypes(namepairs);
}
