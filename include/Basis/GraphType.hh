/*  FILE     GraphType.hh
**  PACKAGE  Graph
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "Graph" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef STURM_GRAPHTYPE_HH
#define STURM_GRAPHTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

/*C GraphNode<KeyType,T>  . . . . . . . . . . . . . . .  Single Node of Graph
**
**  DESCRIPTION
**     Key: This is the keywordby which the GraphNode is referenced (type KeyType)
**     Value:  This is the value that the node takes (of type T)
**
**     Associated with each GraphNode is the set of Parents and Sons of the node.
**     These are referenced through the keytype
**
**     This class is usually accessed through the Graph class
**
**  REMARKS
**
*/
template <class KeyType, class T>
class GraphNode
{
  KeyType Key;
  T Value;
public:
  ObjectList<KeyType> Sons;
  ObjectList<KeyType> Parents;
     
  // Constructors
       GraphNode();
  GraphNode(const GraphNode& node);
  GraphNode(const T& value,
            const KeyType& key,
            const KeyType& parent);
  GraphNode(const T& value,
            const KeyType& key);
  virtual ~GraphNode()
    {
    }
  
  T getValue()
    {
      return Value;
    }
  
  void setValue(T value)
    {
      Value = value;
    }
  
  virtual void CopyClone(GraphNode<KeyType,T> *graph)
    {
      *this = *graph;
    }
  virtual GraphNode<KeyType,T> *Clone()
    {
      GraphNode<KeyType,T> *graph = new GraphNode<KeyType,T>;
      graph->CopyClone(this);
      return graph;
    }
  virtual ostream& print(ostream& out) const
    {
      out << "GraphNode[";
      out << Key;
      out << "] = ";
      out << Value;
      out << "\nParents =";
      Parents.print(out);
      out << "\nSons =";
      Sons.print(out);
      return out;
    }
  virtual bool EncodeThis(CommBuffer& buffer)
    {
      bool result = Encode(buffer,Key);
      result = result && Encode(buffer,Value);
      result = result && Encode(buffer,Sons);
      result = result && Encode(buffer,Parents);
      return result;
    }
  virtual bool DecodeThis(CommBuffer& buffer)
    {
      bool result = Decode(buffer,Key);
      result = result && Decode(buffer,Value);
      result = result && Decode(buffer,Sons);
      result = result && Decode(buffer,Parents);
      return result;
    }
     
  // Modifiers
       inline void AddSonToNode(const KeyType& son);
  inline void AddParentToNode(const KeyType& parent);
     
  inline T& GraphNodeValue();
  inline KeyType& GetKey();
  inline ObjectList<KeyType> GetNeighborList();
     
};
 
/*C GraphNodeToPair<KeyType,T>  . . . . . . . . . . . . . . . . . . . .  work
**
**  DESCRIPTION
**    A working class to convert a GraphNode to a BasicPair
**    of the key and value of the node
**
**  REMARKS
**
*/
template  <class KeyType, class T>
class GraphNodeToPair
{
public:
  GraphNodeToPair()
    {
    }
     
  BasicPair<KeyType,T> operator()(pair<const KeyType,GraphNode<KeyType,T> >& node)
    {
      KeyType i = node.first;
      T j = node.second.GraphNodeValue();
      //          cout << "GraphNodeToPair " << i << "," << j << "\n";
      return BasicPair<KeyType,T> (i,j);
    }
};
 
/*C GetGraphNodeValue<KeyType,T>  . . . . . . . . . . . . . . . . . . .  work
**
**  DESCRIPTION
**     A work routine to return the value of the node as one loops 
**     through the nodes
**
**  REMARKS
**
*/
template  <class KeyType, class T>
class GetGraphNodeValue
{
public:
  GetGraphNodeValue()
    {
    }
     
  T operator()(pair<const KeyType,GraphNode<KeyType,T> >& node)
    {
      cout << "GetGraphNodeValue\n";
      cout << node.second;
      T j = node.second.GraphNodeValue();
      return j;
    }
};
 
/*C GetGraphNodeKey<KeyType,T>  . . . . . . . . . . . . . . . . . . . .  work
**
**  DESCRIPTION
**    A working routine to return the key as one loops through the nodes
**
**  REMARKS
**
*/
template  <class KeyType, class T>
class GetGraphNodeKey
{
public:
  GetGraphNodeKey()
    {
    }
     
  T operator()(const pair<const KeyType,GraphNode<KeyType,T> >& node)
    {
      T j = node.first;
      return j;
    }
};
/*C Graph<KeyType,T>  . . . . . . . . . . . . . . . . . . . . . . . .  graph 
**
**  DESCRIPTION
**     The fundamental graph class
**
**     A graph is defined by a set of nodes (GraphNodes) and a set of 
**     Bonds.   The graph is built up by adding nodes and bonds.  The
**     routines update the set of nodes and bonds.
**
**     In a certain sense, due to the definition of GraphNode, this is
**     a directed graph where the bonds point from the parent to the
**     son.  However, the definition of Neighbors is the set of both
**     the sons and parents combined
**
**  REMARKS
**
*/
template <class KeyType, class T>
class Graph
{
public:
  SearchableObjectListSimple< KeyType, GraphNode<KeyType,T> > Nodes;
  SymmetricPairList< KeyType > Bonds;
     
  Graph();
  Graph(const Graph& graph);
  virtual ~Graph()
    {
    }
  
  virtual void CopyClone(Graph<KeyType,T> *graph)
    {
      *this = *graph;
    }
  virtual Graph<KeyType,T> *Clone()
    {
      Graph<KeyType,T> *graph = new Graph<KeyType,T>;
      graph->CopyClone(this);
      return graph;
    }
  virtual ostream& print(ostream& out) const
    {
      Nodes.print(out);
      Bonds.print(out);
      out << "\n";
      return out;
    }
  virtual bool EncodeThis(CommBuffer& buffer)
    {
      bool result = Nodes.EncodeThis(buffer);
      result = result && Bonds.EncodeThis(buffer);
      return result;
    }
  virtual bool DecodeThis(CommBuffer& buffer)
    {
      bool result = Nodes.DecodeThis(buffer);
      result = result && Bonds.DecodeThis(buffer);
      return result;
    }
     
  inline void AddNodeToGraph(const KeyType& key, 
                             const T& value,
                             const KeyType& Parent);
  inline void AddNodeToGraph(const KeyType& key, 
                             const T& value);
  inline void AddBondToGraph(const KeyType& parent,
                             const KeyType& son);
  inline GraphNode<KeyType,T>& FindGraphNode(const KeyType& key);
  inline void RemoveGraphNode(const KeyType& key);
     
  inline int NumberOfNodes();
  inline ObjectList<KeyType> NodesMatchingValue(const T& value);
  //friend ostream& operator<<(ostream& out, const Graph& graph);
  inline PairList< KeyType,T > GraphToPairList();
     
  inline PairList< KeyType,T > GraphToPairList(ObjectList<KeyType>& keys);
     
  inline ObjectList<KeyType> GetSetOfGraphKeys() const;
  inline ObjectList<T> GetSetOfUniqueGraphValues();
     
  inline ObjectList<T> GetSetOfUniqueGraphValues(const ObjectList<KeyType>& keys);
     
  inline SetOfPairSets<KeyType,T> GraphEquivalentSets(ObjectList< T > values,
                                                      ObjectList<KeyType>& l,
                                                      KeyType& key);
};
/*C BasicIdentifyGraph  . . . . . . . . . . . . graph with Identify for nodes
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class BasicIdentifyGraph : public Graph<Identify,Identify> 
{
public:
  BasicIdentifyGraph()
    {
    }
  BasicIdentifyGraph(const BasicIdentifyGraph& graph) 
    : Graph<Identify,Identify>(graph)
    {
    }
     
};
 

#endif
