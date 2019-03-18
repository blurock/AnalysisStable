/*  FILE     SubGraphType.hh
**  PACKAGE  SubGraph
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "SubGraph" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef Basis_SUBGRAPHTYPE_HH
#define Basis_SUBGRAPHTYPE_HH

/*C GraphSearchInfo . . . . . . . . . . . . . . . Single Node of Graph Search
**
**  DESCRIPTION
**      This can be considered a node in the search space of solutions.  
**      The information on the node is the start pairs, and the 
**      node lists from which the next set of pairs will be produced.
**
**      It is initialized with the start pairs and node lists and after
**      expansion, the set of pair lists is created (to be used to 
**      create the next level of the search.
**
**  REMARKS
**
*/ 
template <class KeyType, class T>
class GraphSearchInfo
{
public:
  SymmetricPairList<KeyType> Start;
     
  SymmetricSetOfPairSets<KeyType> NextGraphPairs;

  ObjectList<KeyType> NodeList1;
  ObjectList<KeyType> NodeList2;
     
  GraphSearchInfo();
  GraphSearchInfo(const SymmetricPairList<KeyType>& start,
		  const Graph<KeyType,T>& graph1,
		  const Graph<KeyType,T>& graph2);
  GraphSearchInfo(const SymmetricPairList<KeyType>& start,
		  const Graph<KeyType,T>& graph1, 
		  const ObjectList<KeyType>& nodes1,
		  const Graph<KeyType,T>& graph2, 
		  const ObjectList<KeyType>& nodes2);
  virtual ~GraphSearchInfo()
    {
    }
  virtual void CopyClone(GraphSearchInfo<KeyType,T> *graphinfo)
    {
      *this = *graphinfo;
    }
  virtual GraphSearchInfo<KeyType,T> * Clone()
    {
      GraphSearchInfo<KeyType,T> *graphinfo = new GraphSearchInfo<KeyType,T>;
      graphinfo->CopyClone(this);
      return graphinfo;
    }
  virtual ostream& print(ostream& out) const
    {
      out << "From the following Pairs:\n";
      Start.print(out);
      out << "\nThe following were derived:\n";
      out << NextGraphPairs;
      out << "\n";
      return out;
    }
  virtual bool EncodeThis(CommBuffer& buffer)
    {
      bool result = Start.EncodeThis(buffer);
      result = result && NextGraphPairs.EncodeThis(buffer);
      result = result && NodeList1.EncodeThis(buffer);
      result = result && NodeList2.EncodeThis(buffer);
      return result;
    }
  virtual bool DecodeThis(CommBuffer& buffer)
    {
      bool result = Start.DecodeThis(buffer);
      result = result && NextGraphPairs.DecodeThis(buffer);
      result = result && NodeList1.DecodeThis(buffer);
      result = result && NodeList2.DecodeThis(buffer);
      return result;
    }
     
  void RemoveFromGraphNodePairs1(const ObjectList<KeyType>& toremove);
  void RemoveFromGraphNodePairs2(const ObjectList<KeyType>& toremove);
     
};
 
/*C FormNextNode  . . . . . . . . . . . . . . . . . . . . . . .  Help Routine
**
**  DESCRIPTION
**     Given a set of pairs, the operator() procedure
**     forms a new GraphSearchInfo structure for the graph and nodes
**
**     The class is initialized with the two graphs.  The pairlist 
**     is the result of the last iteration.
**
**  REMARKS
**
*/
template <class KeyType, class T>
class FormNextNode
{
  Graph<KeyType,T> Graph1;
  Graph<KeyType,T> Graph2;
public:
  FormNextNode(const Graph<KeyType,T>& graph1,
	       const Graph<KeyType,T>& graph2);
  GraphSearchInfo<KeyType,T> operator()(const SymmetricPairList<KeyType>& start);
};
 
/*C GraphSearch<KeyType,T>  . . . . . . . . .  Basic Graph Search Information
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class KeyType, class T>
class GraphSearch
{
public:
     
  Graph<KeyType,T> Graph1;
  Graph<KeyType,T> Graph2;
  GraphSearchInfo<KeyType,T> InitialState;

  GraphSearch();
  GraphSearch(const Graph<KeyType,T>& graph1,
	      const Graph<KeyType,T>& graph2);
  GraphSearch(const Graph<KeyType,T>& graph1,
	      const ObjectList<KeyType> nodelist1,
	      const Graph<KeyType,T>& graph2,
	      const ObjectList<KeyType> nodelist2);
	  
  ObjectList<T> GetUniqueValueUnion(const ObjectList<KeyType>& nodelist1,
				    const ObjectList<KeyType>& nodelist2);
     
  SymmetricSetOfPairSets<KeyType> GetNextSetOfPairSets(KeyType& key1,
						       ObjectList<KeyType>& nodelist1,
						       KeyType& key2,
						       ObjectList<KeyType>& nodelist2);
     
  GraphSearchInfo<KeyType,T>& NextNodeFromPairList(GraphSearchInfo<KeyType,T>& search);
     
  ObjectList< GraphSearchInfo<KeyType,T> > 
  SeparateSearchNodes(const GraphSearchInfo<KeyType,T>& search);
};
/*C FilterSet . . . . . . . . . . . . . . . . . . . . . . . .  done and to do
**
**  DESCRIPTION
**     The set of GraphSearchInfo classes of those
**     that are done and those that are left to expand
**
**  REMARKS
**
*/
template <class KeyType,class T>
class FilterSet
{
public:
  ObjectList< GraphSearchInfo<KeyType,T> > Done;
  ObjectList< GraphSearchInfo<KeyType,T> > ToDo;
};
/*C FilterDone  . . . . . . . . . . . . . . .  Filter Out Complete PairLists 
**
**  DESCRIPTION
**    
**  REMARKS
**    Note that the copy constructor does not copy the Source field
**
*/
template <class KeyType,class T>
class FilterDone
{
public:     
  GraphSearchInfo<KeyType,T> Source;
  FilterSet<KeyType,T> Filtered;
     
  FilterDone(const FilterDone<KeyType,T>& filter);
  FilterDone(const GraphSearchInfo<KeyType,T> source,
	     FilterSet<KeyType,T>& filtered);
  FilterSet<KeyType,T>  operator()(FilterSet<KeyType,T>& set,
				   GraphSearchInfo<KeyType,T> info);
};
/*C GraphSearchSingleIteration  . . . . . . . . . .  single iteration routine
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class  KeyType,class T>
class GraphSearchSingleIteration
{
public:
  GraphSearch<KeyType,T> GSearch;
  ObjectList< GraphSearchInfo<KeyType,T> > Done;

  GraphSearchSingleIteration();
  GraphSearchSingleIteration(const Graph<KeyType,T>& graph1,
			     const Graph<KeyType,T>& graph2);
  FilterSet<KeyType,T>
  operator()(FilterSet<KeyType,T>& notdone,
	     GraphSearchInfo<KeyType,T>& search);
};

 
/*C SubGraphSearch  . . . . . . . . . . . . . . . . . . . . . complete search
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class KeyType,class T>
class SubGraphSearch
{
public:
     
  GraphSearchSingleIteration<KeyType,T> Iteration;

  SubGraphSearch();
  SubGraphSearch(const Graph<KeyType,T>& graph1,
		 const Graph<KeyType,T>& graph2);
     
  void IterateWithGraphInfoSet(const SymmetricPair<KeyType>& startpair,
			       const ObjectList<KeyType>& nodes1,
			       const ObjectList<KeyType>& nodes2);
  void IterateWithGraphInfoSet(const SymmetricPairList<KeyType>& startpairs);
  void IterateWithGraphInfoSet(const BasicPair<KeyType,KeyType>& startpair);     
  void IterateWithGraphInfoSet(const GraphSearchInfo<KeyType,T>& todo);
  void IterateWithGraphInfoSet(ObjectList< GraphSearchInfo<KeyType,T> > todo);
};



#endif
